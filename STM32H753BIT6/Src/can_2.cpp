#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

CAN_2* CAN_2::m_this = nullptr;



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback CAN_2::init(uint32 baudRate)
{
	//	Protect from unauthorized Access
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Enable Bus Clock
	STM32H753BIT6& stm32 = STM32H753BIT6::get();
	RCC& rcc = stm32.get_rcc();
	if(rcc.module_clockInit(RCC::e_module::FDCAN, true) != OK)
	{
		return(FAIL);
	}
	
	
	//	CAN Kernel Clock from PLL 1 Q
	if(rcc.set_clockSource(RCC::e_clockSource_can::PLL_1_Q) != OK)
	{
		return(FAIL);
	}
	
	
	//	INIT and CCE Bit to start Initialization
	bit::set(*MCU::FDCAN_2::FDCAN::CCCR, 0);
	bit::set(*MCU::FDCAN_2::FDCAN::CCCR, 1);
	
	
	//	Bypass CAN Clock Calibration with Divider 1
	bit::set(*MCU::FDCAN_1::CCU::CCFG, 6);
	*MCU::FDCAN_1::CCU::CCFG &= 0xFFF0FFFF;
	
	
	//	Check for valid Kernel Clock depending on the Voltage Level
	const uint32 clock_pll1q = rcc.get_clock_pll_1_q();
	PWR& pwr = stm32.get_pwr();
	const PWR::e_voltageLevel voltageLevel = pwr.get_voltageLevel();
	switch(voltageLevel)
	{
		case PWR::e_voltageLevel::VOS_3:
		{
			if(clock_pll1q > 50000000)
			{
				return(FAIL);
			}
		}
		break;
		
		case PWR::e_voltageLevel::VOS_2:
		{
			if(clock_pll1q > 75000000)
			{
				return(FAIL);
			}
		}
		break;
		
		case PWR::e_voltageLevel::VOS_1:
		{
			if(clock_pll1q > 100000000)
			{
				return(FAIL);
			}
		}
		break;
		
		case PWR::e_voltageLevel::VOS_0:
		{
			if(clock_pll1q > 125000000)
			{
				return(FAIL);
			}
		}
		break;
		
		default:
		{
			return(FAIL);
		}
		break;
	}
	
	
	//	Nominal Bit Rate: For Arbitration Phase to be compatible with CAN2.0
	//	Data Bit Rate: For CAN FD only used for the Data Phase to achieve higher Data Rates - we dont do that here
	const uint32 clock_kernel = clock_pll1q;
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
	*MCU::FDCAN_2::FDCAN::NBTP = (SJW << 25) | (bestNBRP << 16) | (bestNTSEG1 << 8) | bestNTSEG2;
	
	
	//	Set up CAN Message RAM
	//	The first Half of the Message RAM is used for CAN 1, the second Half for CAN 2
	//	Message RAM Size is 2560 Words -> 1280 Words for each CAN Controller
	//	CAN 1 starts at Word Offset 0
	//	CAN 2 starts at Word Offset 1280 (2560 Words / 2)
	//	 1x Standard Filter Element	=  1x 1 Word	=	  1 Word
	//	 1x Extended Filter Element	=  1x 2 Words	=	  2 Words
	//	64x Rx FIFO Element					= 64x 4 Words	= 256 Words
	//	32x Tx Element							= 32x 4 Words	= 128 Words
	//	Sum: 1 + 2 + 256 + 128 = 387 Words
	constexpr uint32 offsetCAN2MessageRAMInWords					= 1280;
	
	constexpr uint32 numberOfStandardFilterElements				= 1;
	constexpr uint32 numberOfExtendedFilterElements				= 1;
	constexpr uint32 numberOfRxFIFOElements								= 64;
	constexpr uint32 numberOfTxFIFOElements								= 32;
	
	constexpr uint32 standardFilterElementSizeInWords			= 1;
	constexpr uint32 extendedFilterElementSizeInWords			= 2;
	constexpr uint32 rxFIFOElementSizeInWords							= 4;
	//constexpr uint32 txFIFOElementSizeInWords							= 4;
	
	constexpr uint32 offsetStandardFilterElementsInWords	= offsetCAN2MessageRAMInWords;
	constexpr uint32 offsetExtendedFilterElementsInWords	= offsetStandardFilterElementsInWords + (numberOfStandardFilterElements * standardFilterElementSizeInWords);
	constexpr uint32 offsetRxFIFOElementsInWords					= offsetExtendedFilterElementsInWords + (numberOfExtendedFilterElements * extendedFilterElementSizeInWords);
	constexpr uint32 offsetTxFIFOElementsInWords					= offsetRxFIFOElementsInWords + (numberOfRxFIFOElements * rxFIFOElementSizeInWords);
	
	
	//	Write the Message RAM Configuration for Standard Filter Element
	//	Bit 23-16:	Number of Standard Filter Elements
	//	Bit 15-2:	Standard Filter Element Offset from Message RAM Base Address in Words
	*MCU::FDCAN_2::FDCAN::SIDFC = (numberOfStandardFilterElements << 16) | (offsetStandardFilterElementsInWords << 2);
	
	
	//	Write the Message RAM Configuration for Extended Filter Element
	//	Bit 23-16:	Number of Extended Filter Elements
	//	Bit 15-2:	Extended Filter Element Offset from Message RAM Base Address in Words
	*MCU::FDCAN_2::FDCAN::XIDFC = (numberOfExtendedFilterElements << 16) | (offsetExtendedFilterElementsInWords << 2);
	
	
	//	Write the Message RAM Configuration for Rx FIFO
	//	We take Rx FIFO 0 to collect all Messages, Rx FIFO 1 is not used
	//	Bit 31:	Operation Mode: 0 = Blocking Mode, 1 = Overwrite Mode
	//	Bit 30-24:	Watermark Interrupt Level to avoid Rx FIFO Overflow (0 = disabled)
	//	Bit 22-16:	Number of Rx FIFO Elements
	//	Bit 15-2:	Rx FIFO Offset from Message RAM Base Address in Words
	*MCU::FDCAN_2::FDCAN::RXF0C = (0x00 << 31) | (0x00 << 24) | (numberOfRxFIFOElements << 16) | (offsetRxFIFOElementsInWords << 2);
	
	
	//	Write the Message RAM Configuration for Tx FIFO
	//	Bit 30:			Operation Mode: 0 = FIFO Operation, 1 = Queue Mode
	//	Bit 29-24:	Number of Tx FIFO Elements
	//	Bit 21-16:	Number of dedicated Tx Buffers
	//	Bit 15-2:		Tx FIFO Offset from Message RAM Base Address in Words
	*MCU::FDCAN_2::FDCAN::TXBC = (0x01 << 30) | (numberOfTxFIFOElements << 24) | (0x00 << 16) | (offsetTxFIFOElementsInWords << 2);
	
	
	//	Global Filter Policy
	//	Dont accept any Frames, that are not matching any Filter Element
	//	Apply normal Filters to Standard Remote Frames
	//	Apply normal Filters to Extended Remote Frames
	*MCU::FDCAN_2::FDCAN::GFC = (0x03 << 4) | (0x03 << 2);
	
	
	//	Set up the Standard Filter Element
	//	SF[0] - Bit 31-30:	Filter Type: 0x0 = Standard Filter, 0x1 = Dual ID Filter, 0x2 = Classical Bit Mask Filter, 0x3 = Filter Element disabled
	//	SF[0] - Bit 29-27:	Filter Action:
	//											0x0 = Disable Filter Element
	//											0x1 = Store Match in Rx FIFO 0
	//											0x2 = Store Match in Rx FIFO 1
	//											0x3 = Reject Match
	//											0x4 = Priority Match
	//											0x5 = Priority Match Rx FIFO 0
	//											0x6 = Priority Match Rx FIFO 1
	//											0x7 = Debug Match
	//	SF[0] - Bit 26-16:	Filter ID 1
	//	SF[0] - Bit 15-0:		Filter ID 2
	volatile uint32* const SF = MCU::FDCAN_MSG_RAM + offsetStandardFilterElementsInWords;
	SF[0] = (0x2 << 30) | (0x1 << 27) | (0x00000000 << 16) | (0x00000000 << 0);
	
	
	//	Set up the Extended Filter Element
	//	XF[0] - Bit 31-29:	Filter Action:
	//											0x0 = Disable Filter Element
	//											0x1 = Store Match in Rx FIFO 0
	//											0x2 = Store Match in Rx FIFO 1
	//											0x3 = Reject Match
	//											0x4 = Priority Match
	//											0x5 = Priority Match Rx FIFO 0
	//											0x6 = Priority Match Rx FIFO 1
	//											0x7 = Debug Match
	//	XF[0] - Bit 28-0:		EF1ID (Extended Filter 1 ID)
	//	XF[1] - Bit 31-30:	Filter Type:
	//											0x0 = Range Filter from EF1ID to EF2ID (EF2ID >= EF1ID)
	//											0x1 = Dual ID Filter
	//											0x2 = Classical Bit Mask Filter
	//											0x3 = Range Filter from EF1ID to EF2ID (EF2ID >= EF1ID), FDCAN_XIDAM Mask not applied
	//	XF[1] - Bit 28-0:		EF2ID (Extended Filter 2 ID)
	volatile uint32* const XF = MCU::FDCAN_MSG_RAM + offsetExtendedFilterElementsInWords;
	XF[0] = (0x1 << 29) | (0x00000000 << 0);
	XF[1] = (0x2 << 30) | (0x00000000 << 0);
	
	
	//	The following Interrupts are activated:
	//	Bit 29: Access to reserved Address
	//	Bit 28: Protocol Error in Data Phase
	//	Bit 27: Protocol Error in Arbitration Phase
	//	Bit 25: Bus Off State
	//	Bit 24: Warning Status
	//	Bit 23: Error Passive State
	//	Bit 22: Error Logging Overflow
	//	Bit 17: Message RAM Access Failure
	//	Bit  3: Rx FIFO 0 Message lost
	//	Bit  2: Rx FIFO 0 Full
	//	Bit  0: Rx FIFO 0 New Message
	*MCU::FDCAN_2::FDCAN::IE = 0x3BC2000D;
	
	
	//	Enable Interrupt INT0
	*MCU::FDCAN_2::FDCAN::ILE = 0x00000001;
	
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::FDCAN_2_INT0, 10);
	nvic.enable(Interrupt::FDCAN_2_INT0);
	
	
	//	Start CAN Transmissions by clearing INIT Bit in CCCR Register
	bit::clear(*MCU::FDCAN_2::FDCAN::CCCR, 0);
	
	
	//	Initialize Error Array
	m_errors.erase();
	m_errors[e_error::STUFFING														] = false;
	m_errors[e_error::FORM																] = false;
	m_errors[e_error::ACK																	] = false;
	m_errors[e_error::BIT_RECESSIVE												] = false;
	m_errors[e_error::BIT_DOMINANT												] = false;
	m_errors[e_error::CRC																	] = false;
	m_errors[e_error::SET_BY_SOFTWARE											] = false;
	m_errors[e_error::ACCESS_TO_RESERVED_AREA							] = false;
	m_errors[e_error::PROTOCOL_ERROR_IN_DATA_PHASE				] = false;
	m_errors[e_error::PROTOCOL_ERROR_IN_ARBITRATION_PHASE	] = false;
	m_errors[e_error::WATCHDOG_INTERRUPT									] = false;
	m_errors[e_error::ERROR_LOGGING_OVERFLOW							] = false;
	m_errors[e_error::TIMEOUT															] = false;
	m_errors[e_error::MESSAGE_RAM_ACCESS_FAILURE					] = false;
	m_errors[e_error::TX_EVENT_FIFO_ELEMENT_LOST					] = false;
	m_errors[e_error::RX_FIFO_OVERFLOW										] = false;
	m_errors[e_error::TX_RINGBUFFER_OVERFLOW							] = false;
	m_errors[e_error::RX_RINGBUFFER_OVERFLOW							] = false;
	
	
	return(OK);
}


feedback CAN_2::stop()
{
	bit::set(*MCU::FDCAN_2::FDCAN::CCCR, 0);
	return(OK);
}







feedback CAN_2::tx(const CAN_Frame& canFrame)
{
	//	Check if Tx Buffer is full
	if(bit::isSet(*MCU::FDCAN_2::FDCAN::TXFQS, 21) == true)
	{
		//	Tx Buffer is full
		m_errors[e_error::TX_RINGBUFFER_OVERFLOW] = true;
		return(FAIL);
	}
	
	
	//	Calculate the Start Address of the Tx FIFO
	volatile uint32* T = MCU::FDCAN_MSG_RAM + ((*MCU::FDCAN_2::FDCAN::TXBC & 0x0000FFFC) >> 2);
	
	
	//	The Size of one Tx Element is always 16 Byte (4 Words) because we only use Standard CAN 2.0 (see TXESC Register)
	//	Read the Put-Index and calculate the Start Address of our Tx Element
	constexpr uint32 txElementSizeInWords = 4;
	const uint32 putIndex = (*MCU::FDCAN_2::FDCAN::TXFQS & 0x001F0000) >> 16;
	T += putIndex * txElementSizeInWords;
	
	
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
	bit::set(*MCU::FDCAN_2::FDCAN::TXBAR, putIndex);
	
	
	return(OK);
}


feedback CAN_2::rx(CAN_Frame& canFrame, uint32 fifoID)
{
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
		while(get_numberOfUnread() == 0)
		{
			cmos.event_listen(m_eventID_frameReadyToRead);
			cmos.sleep_untilEvent(m_eventID_frameReadyToRead);
		}
		
		
		//	Get the Get-Index of the Rx FIFO 0, indicating the Offset in the Message RAM
		const uint32 offsetRxFifo0InWords = (*MCU::FDCAN_2::FDCAN::RXF0C & 0x0000FFFC) >> 2;
		const uint32 getIndex = (*MCU::FDCAN_2::FDCAN::RXF0S & 0x00003F00) >> 8;
		volatile uint32* const R = MCU::FDCAN_MSG_RAM + offsetRxFifo0InWords + (getIndex * 4);
		
		
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
		*MCU::FDCAN_2::FDCAN::RXF0A = getIndex;
		
		
		return(OK);
	}
	return(FAIL);
}


uint32 CAN_2::get_numberOfUnread(uint32 fifoID) const
{
	if(fifoID == 0)
	{
		return(*MCU::FDCAN_2::FDCAN::RXF0S & 0x0000007F);
	}
	if(fifoID == 1)
	{
		return(*MCU::FDCAN_2::FDCAN::RXF1S & 0x0000007F);
	}
	return(0);
}


bool CAN_2::is_dataAvailable() const
{
	if(get_numberOfUnread() > 0)
	{
		return(true);
	}
	return(false);
}







uint16 CAN_2::get_eventID()
{
	return(m_eventID_frameReadyToRead);
}


CAN_2::e_state CAN_2::get_state()
{
	//	CAN State Machine
	e_state state = e_state::ERROR_ACTIVE;
	
	
	//	Read Protocol Status Register
	const uint32 PSR = *MCU::FDCAN_2::FDCAN::PSR;
	
	
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


const UniquePairArray<CAN_2::e_error, bool>& CAN_2::get_errors() const
{
	return(m_errors);
}


void CAN_2::clearErrors()
{
	m_errors.erase();
}







uint32 CAN_2::get_baudRate() const
{
	return(m_baudRate);
}







feedback CAN_2::recoverFromBusOffState()
{
	return(init(m_baudRate));
}









void ISR_FDCAN_2_INT0()
{
	if(CAN_2::m_this != nullptr)
	{
		CAN_2& can = *CAN_2::m_this;
		
		
		//	Read Interrupt Status Register
		const uint32 IR = *MCU::FDCAN_2::FDCAN::IR;
		
		
		if(bit::isSet(IR, 29) == true)
		{
			can.m_errors[I_CAN::e_error::ACCESS_TO_RESERVED_AREA] = true;
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 29);
		}
		if(bit::isSet(IR, 28) == true)
		{
			can.m_errors[I_CAN::e_error::PROTOCOL_ERROR_IN_DATA_PHASE] = true;
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 28);
		}
		if(bit::isSet(IR, 27) == true)
		{
			can.m_errors[I_CAN::e_error::PROTOCOL_ERROR_IN_ARBITRATION_PHASE] = true;
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 27);
		}
		if(bit::isSet(IR, 25) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 25);
		}
		if(bit::isSet(IR, 24) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 24);
		}
		if(bit::isSet(IR, 23) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 23);
		}
		if(bit::isSet(IR, 22) == true)
		{
			can.m_errors[I_CAN::e_error::ERROR_LOGGING_OVERFLOW] = true;
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 22);
		}
		if(bit::isSet(IR, 17) == true)
		{
			can.m_errors[I_CAN::e_error::MESSAGE_RAM_ACCESS_FAILURE] = true;
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 17);
		}
		if(bit::isSet(IR, 3) == true)
		{
			can.m_errors[I_CAN::e_error::RX_FIFO_OVERFLOW] = true;
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 3);
		}
		if(bit::isSet(IR, 2) == true)
		{
			//	Rx FIFO 0 Full
			//	Cant do anything, just ignore it
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 2);
		}
		if(bit::isSet(IR, 0) == true)
		{
			//	New Message in Rx FIFO 0
			//	Emit Event so that the CAN_2::rx() Function can read the Frame
			CMOS::get().event_emit(can.m_eventID_frameReadyToRead);
			
			//	Clear the Interrupt Flag
			bit::set(*MCU::FDCAN_2::FDCAN::IR, 0);
		}
	}
}