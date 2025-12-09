#include "../Inc/stm32g474mct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

CAN_1* CAN_1::m_this = nullptr;



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback CAN_1::init(uint32 baudRate, const Array<s_filterElement>& standardfilterElements, const Array<s_filterElement>& extendedfilterElements)
{
	//	Boundary Check
	if(standardfilterElements.get_size() > numberOfStandardFilterElements || extendedfilterElements.get_size() > numberOfExtendedFilterElements)
	{
		return(FAIL);
	}
	
	
	//	Protect from unauthorized Access
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Enable Bus Clock
	STM32G474MCT6& stm32 = STM32G474MCT6::get();
	RCC& rcc = stm32.get_rcc();
	if(rcc.module_clockInit(RCC::e_module::FDCAN_1_2_3, true) != OK)
	{
		return(FAIL);
	}
	
	
	//	CAN Kernel Clock from PLL Q
	rcc.set_clockSource(RCC::e_clockSource_can::PLL_Q);
	
	
	//	INIT and CCE Bit to start Initialization
	bit::set(*MCU::FDCAN_1::CCCR, 0);
	bit::set(*MCU::FDCAN_1::CCCR, 1);
	
	
	//	Set the Clock Divider to 1 (this is shared to all FDCAN Instances and located in FDCAN 1)
	*MCU::FDCAN_1::CKDIV = 0x00000000;
	
	
	//	Check for valid Kernel Clock depending on the Voltage Level
	const uint32 clock_pll_q = rcc.get_clock_pll_q();
	
	
	//	Nominal Bit Rate: For Arbitration Phase to be compatible with CAN2.0
	//	Data Bit Rate: For CAN FD only used for the Data Phase to achieve higher Data Rates - we dont do that here
	const uint32 clock_kernel = clock_pll_q;
	uint32 smallestDeviationBaudRateInPromille = 0xFFFFFFFF;
	uint32 smallestDeviationSamplePointInPromille = 0xFFFFFFFF;
	bool perfectConfigurationFound = false;
	uint32 bestNBRP = 0;
	uint32 bestNTSEG1 = 0;
	uint32 bestNTSEG2 = 0;
	uint32 baudRateCalculated = 0;
	for(uint32 NBRP = 0; NBRP < 512; NBRP++)
	{
		if(perfectConfigurationFound == true)
		{
			//	Perfect Configuration found - no need to search further
			break;
		}
		for(uint32 NTSEG1 = 0; NTSEG1 < 256; NTSEG1 += 8)
		{
			if(perfectConfigurationFound == true)
			{
				//	Perfect Configuration found - no need to search further
				break;
			}
			for(uint32 NTSEG2 = 0; NTSEG2 < 128; NTSEG2 += 2)
			{
				//	Calculate Time Quantum
				const uint32 clock_timeQuantum = clock_kernel / (NBRP + 1);
				
				
				//	Calculate Baud Rate
				baudRateCalculated = clock_timeQuantum / ((NTSEG1 + NTSEG2 + 3));
				
				const uint32 deviationBaudRateInPromille = (1000 * Math::absolute<int64>(((int64) baudRateCalculated) - baudRate)) / baudRate;
				if(deviationBaudRateInPromille <= smallestDeviationBaudRateInPromille)
				{
					//	Calculate Sample Point
					const uint32 samplePointPromille = (1000 * (NTSEG1 + 2)) / (NTSEG1 + NTSEG2 + 3);
					const uint32 deviationSamplePointInPromille = (1000 * Math::absolute<int32>(((int32) samplePointPromille) - 875)) / 875;
					if(deviationSamplePointInPromille < 100)
					{
						if(deviationBaudRateInPromille == smallestDeviationBaudRateInPromille)
						{
							if(deviationSamplePointInPromille < smallestDeviationSamplePointInPromille)
							{
								//	Better Configuration found - save it
								smallestDeviationBaudRateInPromille = deviationBaudRateInPromille;
								smallestDeviationSamplePointInPromille = deviationSamplePointInPromille;
								
								bestNBRP = NBRP;
								bestNTSEG1 = NTSEG1;
								bestNTSEG2 = NTSEG2;
							}
						}
						else
						{
							//	Better Configuration found - save it
							smallestDeviationBaudRateInPromille = deviationBaudRateInPromille;
							smallestDeviationSamplePointInPromille = deviationSamplePointInPromille;
							
							bestNBRP = NBRP;
							bestNTSEG1 = NTSEG1;
							bestNTSEG2 = NTSEG2;
							
							if(smallestDeviationBaudRateInPromille == 0 && smallestDeviationSamplePointInPromille == 0)
							{
								//	Perfect Configuration found - no need to search further
								break;
							}
						}
						
					}
				}
			}
		}
	}
	
	
	//	Calculate the best Configuration
	const uint32 clock_timeQuantum = clock_kernel / (bestNBRP + 1);
	baudRateCalculated = clock_timeQuantum / ((bestNTSEG1 + bestNTSEG2 + 3));
	
	//	No valid Configuration found
	if(smallestDeviationBaudRateInPromille == 0xFFFFFFFF)
	{
		return(FAIL);
	}
	
	
	//	Set SJW to NTSEG2 / 2 because we dont know how to calculate it correctly
	//	SJW must be < NTSEG2 and < 128
	uint32 SJW = (bestNTSEG2) / 2;
	if(SJW > 127)
	{
		SJW = 127;
	}
	
	
	//	Write Clock Configuration to FDCAN
	*MCU::FDCAN_1::NBTP = (SJW << 25) | (bestNBRP << 16) | (bestNTSEG1 << 8) | bestNTSEG2;
	
	
	//	Global Filter Policy
	//	Dont accept any Frames, that are not matching any Filter Element
	//	Apply normal Filters to Standard Remote Frames
	//	Apply normal Filters to Extended Remote Frames
	//	Operate Rx FIFO 0 in blocking Mode (meaning that in Case of an Overflow no old Messages are overwritten)
	//	Operate Rx FIFO 1 in blocking Mode (meaning that in Case of an Overflow no old Messages are overwritten)
	//	Set Number of Standard Filter Elements
	//	Set Number of Extended Filter Elements
	*MCU::FDCAN_1::RXGFC = (0x03 << 4) | (0x03 << 2);
	*MCU::FDCAN_1::RXGFC |= (standardfilterElements.get_size() << 16);
	*MCU::FDCAN_1::RXGFC |= (extendedfilterElements.get_size() << 24);
	
	
	//	Set up CAN Message RAM
	//	The Message RAM consists of 212 Words (= 848 Bytes) per each CAN Controller
	//	Standard Filter Element		28 Elements		28 Words	112 Bytes
	//	Extended Filter Element		 8 Elements		16 Words	 64 Bytes
	//	Rx FIFO 0									 3 Elements	 	54 Words	216 Bytes
	//	Rx FIFO 1									 3 Elements	 	54 Words	216 Bytes
	//	Tx Event FIFO							 3 Elements		 6 Words	 24 Bytes
	//	Tx Buffer									 3 Elements		54 Words	216 Bytes
	//	Sum																		 212 Words	848 Bytes
	
	//	Set up the Standard Filter Elements
	for(uint32 i = 0; i < standardfilterElements.get_size(); i++)
	{
		const s_filterElement& filterElement = standardfilterElements[i];
		uint32 filterElementInRAM = 0;
		
		
		//	Filter Type
		switch(filterElement.type)
		{
			case e_filterType::RANGE:
			{
				bit::clear(filterElementInRAM, 30);
				bit::clear(filterElementInRAM, 31);
			}
			break;
			
			case e_filterType::DUAL_ID:
			{
				bit::set(filterElementInRAM, 30);
				bit::clear(filterElementInRAM, 31);
			}
			break;
			
			case e_filterType::MASK:
			{
				bit::clear(filterElementInRAM, 30);
				bit::set(filterElementInRAM, 31);
			}
			break;
			
			default:
			{
				//	Invalid Filter Type
				return(FAIL);
			}
			break;
		}
		
		
		//	Filter Behavior
		switch(filterElement.behavior)
		{
			case e_filterBehavior::DISABLED:
			{
				filterElementInRAM |= (0x0 << 27);
			}
			break;
			
			case e_filterBehavior::STORE_IN_RX_FIFO_0:
			{
				filterElementInRAM |= (0x1 << 27);
			}
			break;
			
			case e_filterBehavior::STORE_IN_RX_FIFO_1:
			{
				filterElementInRAM |= (0x2 << 27);
			}
			break;
			
			case e_filterBehavior::REJECT_ID:
			{
				filterElementInRAM |= (0x3 << 27);
			}
			break;
			
			case e_filterBehavior::SET_PRIORITY:
			{
				filterElementInRAM |= (0x4 << 27);
			}
			break;
			
			case e_filterBehavior::SET_PRIORITY_AND_STORE_IN_RX_FIFO_0:
			{
				filterElementInRAM |= (0x5 << 27);
			}
			break;
			
			case e_filterBehavior::SET_PRIORITY_AND_STORE_IN_RX_FIFO_1:
			{
				filterElementInRAM |= (0x6 << 27);
			}
			break;
			
			default:
			{
				//	Invalid Filter Behavior
				return(FAIL);
			}
			break;
		}
		
		
		//	Filter IDs / Mask
		filterElementInRAM |= (filterElement.ID1_or_filter	& 0x000007FF) << 16;
		filterElementInRAM |= (filterElement.ID2_or_mask		& 0x000007FF) << 0;
		
		
		//	Write Filter Element to Message RAM
		*(MCU::FDCAN_1::MSG_RAM + i) = filterElementInRAM;
	}
	
	
	//	Set up the Extended Filter Elements
	for(uint32 i = 0; i < extendedfilterElements.get_size(); i++)
	{
		const s_filterElement& filterElement = extendedfilterElements[i];
		uint32 filterElementInRAM[2] = {0, 0};
		
		
		//	Filter Type
		switch(filterElement.type)
		{
			case e_filterType::RANGE:
			{
				bit::clear(filterElementInRAM[1], 30);
				bit::clear(filterElementInRAM[1], 31);
			}
			break;
			
			case e_filterType::DUAL_ID:
			{
				bit::set(filterElementInRAM[1], 30);
				bit::clear(filterElementInRAM[1], 31);
			}
			break;
			
			case e_filterType::MASK:
			{
				bit::clear(filterElementInRAM[1], 30);
				bit::set(filterElementInRAM[1], 31);
			}
			break;
			
			default:
			{
				//	Invalid Filter Type
				return(FAIL);
			}
			break;
		}
		
		
		//	Filter Behavior
		switch(filterElement.behavior)
		{
			case e_filterBehavior::DISABLED:
			{
				filterElementInRAM[0] |= (0x0 << 29);
			}
			break;
			
			case e_filterBehavior::STORE_IN_RX_FIFO_0:
			{
				filterElementInRAM[0] |= (0x1 << 29);
			}
			break;
			
			case e_filterBehavior::STORE_IN_RX_FIFO_1:
			{
				filterElementInRAM[0] |= (0x2 << 29);
			}
			break;
			
			case e_filterBehavior::REJECT_ID:
			{
				filterElementInRAM[0] |= (0x3 << 29);
			}
			break;
			
			case e_filterBehavior::SET_PRIORITY:
			{
				filterElementInRAM[0] |= (0x4 << 29);
			}
			break;
			
			case e_filterBehavior::SET_PRIORITY_AND_STORE_IN_RX_FIFO_0:
			{
				filterElementInRAM[0] |= (0x5 << 29);
			}
			break;
			
			case e_filterBehavior::SET_PRIORITY_AND_STORE_IN_RX_FIFO_1:
			{
				filterElementInRAM[0] |= (0x6 << 29);
			}
			break;
			
			default:
			{
				//	Invalid Filter Behavior
				return(FAIL);
			}
			break;
		}
		
		
		//	Filter IDs / Mask
		filterElementInRAM[0] |= (filterElement.ID1_or_filter	& 0x1FFFFFFF) << 0;
		filterElementInRAM[1] |= (filterElement.ID2_or_mask		& 0x1FFFFFFF) << 0;
		
		
		//	Write Filter Element to Message RAM
		*(MCU::FDCAN_1::MSG_RAM + 28 + (i * 2)) = filterElementInRAM[0];
	}
	
	
	//	The following Interrupts are activated:
	//	Bit 23: Access to reserved Address
	//	Bit 22: Protocol Error in Data Phase
	//	Bit 21: Protocol Error in Arbitration Phase
	//	Bit 19: Bus Off State
	//	Bit 18: Warning Status
	//	Bit 17: Error Passive State
	//	Bit 16: Error Logging Overflow
	//	Bit 14: Message RAM Access Failure
	//	Bit  6: High Priority Message received
	//	Bit  5: Rx FIFO 1 Message lost
	//	Bit  4: Rx FIFO 1 Full
	//	Bit  3: Rx FIFO 1 New Message
	//	Bit  2: Rx FIFO 0 Message lost
	//	Bit  1: Rx FIFO 0 Full
	//	Bit  0: Rx FIFO 0 New Message
	*MCU::FDCAN_1::IE = 0x00EF407F;
	
	
	//	INT0: All RX FIFO related Interrupts
	//	INT1: All Error Interrupts
	*MCU::FDCAN_1::ILS = 0x00000078;
	
	
	//	Enable Interrupt INT0 and INT1
	*MCU::FDCAN_1::ILE = 0x00000003;
	
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::FDCAN_1_IT0, 10);
	nvic.setPriority(Interrupt::FDCAN_1_IT1, 10);
	nvic.enable(Interrupt::FDCAN_1_IT0);
	nvic.enable(Interrupt::FDCAN_1_IT1);
	
	
	//	Start CAN Transmissions by clearing INIT Bit in CCCR Register
	bit::clear(*MCU::FDCAN_1::CCCR, 0);
	
	
	//	Save Baud Rate
	m_baudRate = baudRateCalculated;
	
	
	//	Save Filter Elements
	m_standardFilterElements = standardfilterElements;
	m_extendedFilterElements = extendedfilterElements;
	
	
	return(OK);
}


feedback CAN_1::stop()
{
	bit::set(*MCU::FDCAN_1::CCCR, 0);
	return(OK);
}







feedback CAN_1::tx(const CAN_Frame& canFrame)
{
	//	Check if Tx Buffer is full
	if(bit::isSet(*MCU::FDCAN_1::TX_FQS, 21) == true)
	{
		//	Tx Buffer is full
		m_errors[e_error::TX_RINGBUFFER_OVERFLOW] = true;
		return(FAIL);
	}
	
	
	//	Calculate the Start Address of the Tx FIFO Buffer Element
	const uint32 putIndex = ((*MCU::FDCAN_1::TX_FQS & 0x00030000) >> 16);
	volatile uint32* T = MCU::FDCAN_1::MSG_RAM + 0x9E + 0x12 * putIndex;
	
	
	//	T0
	if(canFrame.extendedID == true)
	{
		T[0] = (0x01 << 30) | (canFrame.ID & 0x1FFFFFFF);
	}
	else
	{
		T[0] = (canFrame.ID & 0x000007FF) << 18;
	}
	
	if(canFrame.remoteTransmissionRequest == true)
	{
		bit::set(T[0], 29);
	}
	
	
	//	T1
	T[1] = (canFrame.dataSize) << 16;
	
	
	//	T2 & T3
	T[2] = 0;
	T[3] = 0;
	for(uint32 i = 0; i < canFrame.dataSize; i++)
	{
		if(i < 4)
		{
			T[2] |= (canFrame.data[i] << (8 * i));
		}
		else
		{
			T[3] |= (canFrame.data[i] << (8 * (i - 4)));
		}
	}
	
	
	//	Request Transmission
	bit::set(*MCU::FDCAN_1::TX_BAR, putIndex);
	
	
	return(OK);
}


feedback CAN_1::rx(CAN_Frame& canFrame, uint32 fifoID)
{
	if(fifoID > 1)
	{
		return(FAIL);
	}
	
	
	//	Subscribe to Frame Ready Event
	CMOS& cmos = CMOS::get();
	if(cmos.event_subscribe(m_eventID_frameReadyToRead) != OK)
	{
		return(FAIL);
	}
	
	
	while(1)
	{
		//	Wait for a Frame to be ready to read
		//	This is indicated by the Rx FIFO 0 Fill Level
		while(get_numberOfUnread(fifoID) == 0)
		{
			cmos.event_listen(m_eventID_frameReadyToRead);
			cmos.sleep_untilEvent(m_eventID_frameReadyToRead);
		}
		
		
		//	Get the Rx FIFO Element, indicating the Offset in the Message RAM
		volatile uint32* RX_FnS = MCU::FDCAN_1::RX_F0S;
		if(fifoID == 1)
		{
			RX_FnS = MCU::FDCAN_1::RX_F1S;
		}
		const uint32 getIndex = (*RX_FnS & 0x00000300) >> 8;
		volatile uint32* const R = MCU::FDCAN_1::MSG_RAM + 0x2C + 0x36 * fifoID + 0x12 * getIndex;
		
		
		//	Check for FDCAN Frame (not supported by this Implementation)
		if(bit::isSet(R[1], 21) == true || bit::isSet(R[1], 20) == true)
		{
			return(FAIL);
		}
		
		
		canFrame.extendedID = bit::isSet(R[0], 30);
		canFrame.remoteTransmissionRequest = bit::isSet(R[0], 29);
		if(canFrame.extendedID == true)
		{
			canFrame.ID = R[0] & 0x1FFFFFFF;
		}
		else
		{
			canFrame.ID = (R[0] >> 18) & 0x000007FF;
		}
		canFrame.dataSize = (R[1] >> 16) & 0x0000000F;
		canFrame.timeStamp = R[1] & 0x0000FFFF;
		
		for(uint32 i = 0; i < canFrame.dataSize; i++)
		{
			if(i < 4)
			{
				canFrame.data[i] = (R[2] >> (8 * i)) & 0xFF;
			}
			else
			{
				canFrame.data[i] = (R[3] >> (8 * (i - 4))) & 0xFF;
			}
		}
		
		
		//	Set the Acknowledge Index to indicate the last read Message to the CAN Controller
		volatile uint32* RX_FnA = MCU::FDCAN_1::RX_F0A;
		if(fifoID == 1)
		{
			RX_FnA = MCU::FDCAN_1::RX_F1A;
		}
		*RX_FnA = getIndex;
		
		
		return(OK);
	}
	return(FAIL);
}


uint32 CAN_1::get_numberOfUnread(uint32 fifoID) const
{
	if(fifoID == 0)
	{
		return(*MCU::FDCAN_1::RX_F0S & 0x0000000F);
	}
	if(fifoID == 1)
	{
		return(*MCU::FDCAN_1::RX_F1S & 0x0000000F);
	}
	return(0);
}


bool CAN_1::is_dataAvailable() const
{
	if(get_numberOfUnread(0) > 0 || get_numberOfUnread(1) > 0)
	{
		return(true);
	}
	return(false);
}







uint16 CAN_1::get_eventID()
{
	return(m_eventID_frameReadyToRead);
}


CAN_1::e_state CAN_1::get_state()
{
	//	CAN State Machine
	e_state state = e_state::ERROR_ACTIVE;
	
	
	//	Read Protocol Status Register
	const uint32 PSR = *MCU::FDCAN_1::PSR;
	
	
	//	Read Last Error Code
	const uint8 LEC = PSR & 0x00000007;
	if(LEC < 0x7)
	{
		m_errors[(e_error) LEC] = true;
	}
	
	
	//	Error Passive State
	if(bit::isSet(PSR, 5) == true)
	{
		state = e_state::ERROR_PASSIVE;
	}
	
	
	//	Bus Off State
	if(bit::isSet(PSR, 7) == true)
	{
		state = e_state::BUS_OFF;
	}
	m_state = state;
	
	
	return(m_state);
}


const UniquePairArray<CAN_1::e_error, bool>& CAN_1::get_errors() const
{
	return(m_errors);
}


void CAN_1::clearErrors()
{
	m_errors.erase();
}







uint32 CAN_1::get_baudRate() const
{
	return(m_baudRate);
}







feedback CAN_1::recoverFromBusOffState()
{
	return(init(m_baudRate, m_standardFilterElements, m_extendedFilterElements));
}









void ISR_FDCAN_1_IT0()
{
	if(CAN_1::m_this != nullptr)
	{
		CAN_1& can = *CAN_1::m_this;
		
		
		//	Read Interrupt Status Register
		const uint32 IR = *MCU::FDCAN_1::IR;
		
		
		//	High Priority Message received
		if(bit::isSet(IR, 6) == true)
		{
			//	Emit Event so that the CAN_1::rx() Function can read the Frame
			CMOS::get().event_emit(can.m_eventID_frameReadyToRead);
		}
		
		
		//	Rx FIFO 1 Message lost
		if(bit::isSet(IR, 5) == true)
		{
			can.m_errors[I_CAN::e_error::RX_FIFO_OVERFLOW] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 5;
		}
		
		
		//	Rx FIFO 1 Full
		if(bit::isSet(IR, 4) == true)
		{
			//	Cant do anything, just ignore it
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 4;
		}
		
		
		//	Rx FIFO 1 New Message
		if(bit::isSet(IR, 3) == true)
		{
			//	Emit Event so that the CAN_1::rx() Function can read the Frame
			CMOS::get().event_emit(can.m_eventID_frameReadyToRead);
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 3;
		}
		
		
		//	Rx FIFO 0 Message lost
		if(bit::isSet(IR, 2) == true)
		{
			can.m_errors[I_CAN::e_error::RX_FIFO_OVERFLOW] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 2;
		}
		
		//	Rx FIFO 0 Full
		if(bit::isSet(IR, 1) == true)
		{
			//	Cant do anything, just ignore it
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 1;
		}
		
		
		//	Rx FIFO 0 New Message
		if(bit::isSet(IR, 0) == true)
		{
			//	Emit Event so that the CAN_1::rx() Function can read the Frame
			CMOS::get().event_emit(can.m_eventID_frameReadyToRead);
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 0;
		}
	}
}


void ISR_FDCAN_1_IT1()
{
	if(CAN_1::m_this != nullptr)
	{
		CAN_1& can = *CAN_1::m_this;
		
		
		//	Read Interrupt Status Register
		const uint32 IR = *MCU::FDCAN_1::IR;
		
		
		//	Error: Access to reserved Area
		if(bit::isSet(IR, 23) == true)
		{
			can.m_errors[I_CAN::e_error::ACCESS_TO_RESERVED_AREA] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 23;
		}
		
		
		//	Error: Protocol Error in Data Phase
		if(bit::isSet(IR, 22) == true)
		{
			can.m_errors[I_CAN::e_error::PROTOCOL_ERROR_IN_DATA_PHASE] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 22;
		}
		
		
		//	Error: Protocol Error in Arbitration Phase
		if(bit::isSet(IR, 21) == true)
		{
			can.m_errors[I_CAN::e_error::PROTOCOL_ERROR_IN_ARBITRATION_PHASE] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 21;
		}
		
		
		//	Error: Bus Off State
		if(bit::isSet(IR, 19) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 19;
		}
		
		
		//	Error: Warning Status
		if(bit::isSet(IR, 18) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 18;
		}
		
		
		//	Error: Error Passive State
		if(bit::isSet(IR, 17) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 17;
		}
		
		
		//	Error: Error Logging Overflow
		if(bit::isSet(IR, 16) == true)
		{
			can.m_errors[I_CAN::e_error::ERROR_LOGGING_OVERFLOW] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 16;
		}
		
		
		//	Error: Message RAM Access Failure
		if(bit::isSet(IR, 14) == true)
		{
			can.m_errors[I_CAN::e_error::MESSAGE_RAM_ACCESS_FAILURE] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::IR = 1 << 14;
		}
	}
}