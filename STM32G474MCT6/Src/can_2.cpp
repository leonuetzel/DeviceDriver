#include "../Inc/stm32g474mct6.hpp"





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

feedback CAN_2::calculate_bitTiming(uint32 clock, uint32 bitRate, uint32 samplePoint_permille, uint32 deviation_max_permille, uint32 prescaler_max, uint32 segment1_max, uint32 segment2_max, uint32& prescaler, uint32& segment1, uint32& segment2, uint32& bitRateCalculated)
{
	//	Bit Time = 1 + Segment 1 + Segment 2 Time Quanta (Synchronization, Propagation and Phase 1, Phase 2), the Sample Point lies behind Segment 1
	//	The best Configuration has the smallest Deviation of the Bit Rate, then of the Sample Point; with the same Result the smaller Prescaler wins
	//	(more Time Quanta per Bit)
	if(bitRate == 0 || clock == 0)
	{
		return(FAIL);
	}
	uint32 deviation_bitRate_best = 0xFFFFFFFF;
	uint32 deviation_samplePoint_best = 0xFFFFFFFF;
	for(uint32 brp = 1; brp <= prescaler_max; brp++)
	{
		const uint32 numberOfQuanta = clock / (brp * bitRate);
		for(uint32 n = numberOfQuanta; n <= numberOfQuanta + 1; n++)
		{
			if(n < 4 || n > 1 + segment1_max + segment2_max)
			{
				continue;
			}
			
			
			//	Segment 1 for the Sample Point, then Segment 2 is the Rest - both within the Register Limits
			uint32 s1 = (n * samplePoint_permille + 500) / 1000;
			s1 = (s1 > 1) ? s1 - 1 : 1;
			if(s1 > segment1_max)
			{
				s1 = segment1_max;
			}
			if(n - 1 - s1 > segment2_max)
			{
				s1 = n - 1 - segment2_max;
			}
			if(s1 < 1 || s1 > segment1_max || n - 1 - s1 < 1)
			{
				continue;
			}
			const uint32 s2 = n - 1 - s1;
			
			
			const uint32 rate = clock / (brp * n);
			const uint32 difference_bitRate = (rate > bitRate) ? rate - bitRate : bitRate - rate;
			const uint32 deviation_bitRate = (uint32) ((1000 * (uint64) difference_bitRate) / bitRate);
			const uint32 samplePoint = (1000 * (1 + s1)) / n;
			const uint32 deviation_samplePoint = (samplePoint > samplePoint_permille) ? samplePoint - samplePoint_permille : samplePoint_permille - samplePoint;
			if(deviation_bitRate < deviation_bitRate_best || (deviation_bitRate == deviation_bitRate_best && deviation_samplePoint < deviation_samplePoint_best))
			{
				deviation_bitRate_best = deviation_bitRate;
				deviation_samplePoint_best = deviation_samplePoint;
				prescaler = brp;
				segment1 = s1;
				segment2 = s2;
				bitRateCalculated = rate;
			}
		}
	}
	
	
	//	CAN tolerates at most 1.58 % Clock Deviation in the Arbitration Phase (ISO 11898-1), the Data Phase of CAN FD less
	if(deviation_bitRate_best > deviation_max_permille)
	{
		return(FAIL);
	}
	return(OK);
}


feedback CAN_2::init_controller(uint32 nominalBitRate, uint32 dataBitRate, const Array<s_filterElement>& standardfilterElements, const Array<s_filterElement>& extendedfilterElements, bool silentMode, uint32 samplePoint_nominal_permille, uint32 samplePoint_data_permille)
{
	//	Boundary Check
	if(standardfilterElements.get_size() > numberOfStandardFilterElements || extendedfilterElements.get_size() > numberOfExtendedFilterElements)
	{
		return(FAIL);
	}
	
	
	//	CAN FD: the Data Bit Rate is at least the nominal one; Sample Points between 50 % and 95 %
	const bool fd = (dataBitRate != 0);
	if(samplePoint_nominal_permille < 500 || samplePoint_nominal_permille > 950)
	{
		return(FAIL);
	}
	if(fd == true && (dataBitRate < nominalBitRate || samplePoint_data_permille < 500 || samplePoint_data_permille > 950))
	{
		return(FAIL);
	}
	
	
	//	Protect from unauthorized Access
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
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
	bit::set(*MCU::FDCAN_2::CCCR, 0);
	bit::set(*MCU::FDCAN_2::CCCR, 1);
	
	
	//	Set the Clock Divider to 1 (this is shared to all FDCAN Instances and located in FDCAN 1)
	*MCU::FDCAN_1::CKDIV = 0x00000000;
	
	
	//	Check for valid Kernel Clock depending on the Voltage Level
	const uint32 clock_pll_q = rcc.get_clock_pll_q();
	
	
	//	Kernel Clock of the FDCAN (PLL Q, CKDIV = 1)
	const uint32 clock_kernel = clock_pll_q;
	
	
	//	Nominal Bit Rate (Arbitration Phase, and the whole classic CAN Frame): NBRP 9 Bit, NTSEG1 8 Bit, NTSEG2 7 Bit (Register Values + 1)
	uint32 prescaler = 0;
	uint32 segment1 = 0;
	uint32 segment2 = 0;
	uint32 nominalBitRateCalculated = 0;
	if(calculate_bitTiming(clock_kernel, nominalBitRate, samplePoint_nominal_permille, 15, 512, 256, 128, prescaler, segment1, segment2, nominalBitRateCalculated) != OK)
	{
		return(FAIL);
	}
	
	//	The Resynchronization Jump Width is the Phase Segment 2 - the most a Node can correct
	const uint32 sjw = (segment2 > 128) ? 128 : segment2;
	*MCU::FDCAN_2::NBTP = ((sjw - 1) << 25) | ((prescaler - 1) << 16) | ((segment1 - 1) << 8) | (segment2 - 1);
	
	
	//	Data Bit Rate (Data Phase of CAN FD Frames with BRS): DBRP 5 Bit, DTSEG1 5 Bit, DTSEG2 4 Bit, DSJW 4 Bit
	uint32 dataBitRateCalculated = 0;
	if(fd == true)
	{
		uint32 data_prescaler = 0;
		uint32 data_segment1 = 0;
		uint32 data_segment2 = 0;
		if(calculate_bitTiming(clock_kernel, dataBitRate, samplePoint_data_permille, 5, 32, 32, 16, data_prescaler, data_segment1, data_segment2, dataBitRateCalculated) != OK)
		{
			return(FAIL);
		}
		const uint32 data_sjw = (data_segment2 > 16) ? 16 : data_segment2;
		
		
		//	Transmitter Delay Compensation above 1 MBit/s: the Delay of the Transceiver would else reach the Sample Point of the Data Phase
		//	It is only possible with DBRP 0 or 1; the Offset is the Position of the Sample Point in Kernel Clock Cycles (TDCO 7 Bit)
		const bool tdc = (dataBitRateCalculated > 1000000 && data_prescaler <= 2);
		uint32 tdcOffset = data_prescaler * data_segment1;
		if(tdcOffset > 127)
		{
			tdcOffset = 127;
		}
		*MCU::FDCAN_2::TDCR = (tdcOffset << 8);
		*MCU::FDCAN_2::DBTP = ((tdc == true) ? (1 << 23) : 0) | ((data_prescaler - 1) << 16) | ((data_segment1 - 1) << 8) | ((data_segment2 - 1) << 4) | (data_sjw - 1);
		
		
		//	CAN FD Operation (FDOE) with Bit Rate Switching (BRSE), ISO CAN FD (NISO = 0)
		bit::set(*MCU::FDCAN_2::CCCR, 8);
		bit::set(*MCU::FDCAN_2::CCCR, 9);
		bit::clear(*MCU::FDCAN_2::CCCR, 15);
	}
	else
	{
		//	Classic CAN: no CAN FD Frames
		bit::clear(*MCU::FDCAN_2::CCCR, 8);
		bit::clear(*MCU::FDCAN_2::CCCR, 9);
	}
	
	
	//	Silent Mode
	if(silentMode == true)
	{
		bit::set(*MCU::FDCAN_2::CCCR, 5);
	}
	else
	{
		bit::clear(*MCU::FDCAN_2::CCCR, 5);
	}
	m_silentMode = silentMode;
	
	
	//	Global Filter Policy
	//	Frames without a matching Filter Element: rejected (ANFS/ANFE = 3) - with an empty List all Frames of its Kind go into FIFO 0 (0)
	//	Apply normal Filters to Standard Remote Frames
	//	Apply normal Filters to Extended Remote Frames
	//	Operate Rx FIFO 0 in blocking Mode (meaning that in Case of an Overflow no old Messages are overwritten)
	//	Operate Rx FIFO 1 in blocking Mode (meaning that in Case of an Overflow no old Messages are overwritten)
	//	Set Number of Standard Filter Elements
	//	Set Number of Extended Filter Elements
	const uint32 nonMatching_standard = (standardfilterElements.get_size() == 0) ? 0x0 : 0x3;
	const uint32 nonMatching_extended = (extendedfilterElements.get_size() == 0) ? 0x0 : 0x3;
	*MCU::FDCAN_2::RXGFC = (nonMatching_standard << 4) | (nonMatching_extended << 2);
	*MCU::FDCAN_2::RXGFC |= (standardfilterElements.get_size() << 16);
	*MCU::FDCAN_2::RXGFC |= (extendedfilterElements.get_size() << 24);
	
	
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
		*(MCU::FDCAN_2::MSG_RAM + i) = filterElementInRAM;
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
		*(MCU::FDCAN_2::MSG_RAM + 28 + (i * 2)) = filterElementInRAM[0];
		*(MCU::FDCAN_2::MSG_RAM + 28 + (i * 2) + 1) = filterElementInRAM[1];
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
	*MCU::FDCAN_2::IE = 0x00EF407F;
	
	
	//	INT0: All RX FIFO related Interrupts
	//	INT1: All Error Interrupts
	*MCU::FDCAN_2::ILS = 0x00000078;
	
	
	//	Enable Interrupt INT0 and INT1
	*MCU::FDCAN_2::ILE = 0x00000003;
	
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::FDCAN_2_IT0, 10);
	nvic.setPriority(Interrupt::FDCAN_2_IT1, 10);
	nvic.enable(Interrupt::FDCAN_2_IT0);
	nvic.enable(Interrupt::FDCAN_2_IT1);
	
	
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
	
	
	//	Start CAN Transmissions by clearing INIT Bit in CCCR Register
	bit::clear(*MCU::FDCAN_2::CCCR, 0);
	
	
	//	Save Baud Rate
	m_baudRate = nominalBitRateCalculated;
	m_dataBitRate = dataBitRateCalculated;
	
	
	//	Save Filter Elements
	m_standardFilterElements = standardfilterElements;
	m_extendedFilterElements = extendedfilterElements;
	
	
	return(OK);
}


feedback CAN_2::init(uint32 baudRate, const Array<s_filterElement>& standardfilterElements, const Array<s_filterElement>& extendedfilterElements, bool silentMode, uint32, uint32)
{
	//	Classic CAN with the Sample Point at 87.5 % - the Rx FIFOs and Tx Buffers lie in the Message RAM, there are no Software Buffers
	return(init_controller(baudRate, 0, standardfilterElements, extendedfilterElements, silentMode, 875, 0));
}


feedback CAN_2::init(uint32 nominalBitRate, uint32 dataBitRate, const Array<s_filterElement>& standardFilterElements, const Array<s_filterElement>& extendedFilterElements, bool silentMode, uint32, uint32, uint16 samplePoint_nominal_permille, uint16 samplePoint_data_permille)
{
	//	CAN FD: classic CAN Frames and CAN FD Frames with up to 64 Byte, the Data Phase with the Data Bit Rate (BRS)
	if(dataBitRate == 0)
	{
		return(FAIL);
	}
	return(init_controller(nominalBitRate, dataBitRate, standardFilterElements, extendedFilterElements, silentMode, samplePoint_nominal_permille, samplePoint_data_permille));
}


feedback CAN_2::stop()
{
	bit::set(*MCU::FDCAN_2::CCCR, 0);
	return(OK);
}







feedback CAN_2::tx(const CAN_Frame& canFrame)
{
	//	Maximum Data Size of a classic CAN Frame is 8 Byte
	if(canFrame.dataSize > 8)
	{
		return(FAIL);
	}
	return(tx(CAN_FD_Frame(canFrame)));
}


feedback CAN_2::tx(const CAN_FD_Frame& canFDFrame)
{
	//	CAN FD Frames need the CAN FD Mode and have no Remote Frames; classic CAN Frames carry at most 8 Byte
	if(canFDFrame.fdFormat == true)
	{
		if(m_dataBitRate == 0 || canFDFrame.remoteTransmissionRequest == true || canFDFrame.dataSize > CAN_FD_Frame::c_dataSize_max)
		{
			return(FAIL);
		}
	}
	else if(canFDFrame.dataSize > 8)
	{
		return(FAIL);
	}
	
	
	//	Data Length Code: a CAN FD Frame is filled up with 0 to the next valid Length (12, 16, 20, 24, 32, 48 or 64 Byte)
	const uint32 dlc = (canFDFrame.fdFormat == true) ? CAN_FD_Frame::get_dlc(canFDFrame.dataSize) : canFDFrame.dataSize;
	uint32 numberOfBytes = (canFDFrame.fdFormat == true) ? CAN_FD_Frame::get_dataSize(dlc) : canFDFrame.dataSize;
	if(canFDFrame.remoteTransmissionRequest == true)
	{
		numberOfBytes = 0;
	}
	
	
	//	Several Threads may transmit: the Put Index is read, the Element written and the Request set without Interruption
	NVIC& nvic = CMOS::get().get_nvic();
	nvic.disable_allExceptions();
	
	
	//	Check if the Tx Buffers are full
	if(bit::isSet(*MCU::FDCAN_2::TX_FQS, 21) == true)
	{
		m_errors[e_error::TX_RINGBUFFER_OVERFLOW] = true;
		nvic.enable_allExceptions();
		return(FAIL);
	}
	
	
	//	Tx Buffers start at Word 0x9E of the Message RAM of this Instance, every Element has 18 Words (RM0440, FDCAN Message RAM)
	const uint32 putIndex = ((*MCU::FDCAN_2::TX_FQS & 0x00030000) >> 16);
	volatile uint32* const T = MCU::FDCAN_2::MSG_RAM + 0x9E + 0x12 * putIndex;
	
	
	//	T0: XTD Bit 30, RTR Bit 29, ID (standard: Bit 28-18)
	uint32 t0 = 0;
	if(canFDFrame.extendedID == true)
	{
		t0 = (0x01 << 30) | (canFDFrame.ID & 0x1FFFFFFF);
	}
	else
	{
		t0 = (canFDFrame.ID & 0x000007FF) << 18;
	}
	if(canFDFrame.remoteTransmissionRequest == true)
	{
		bit::set(t0, 29);
	}
	T[0] = t0;
	
	
	//	T1: FDF Bit 21, BRS Bit 20, DLC Bit 19-16
	uint32 t1 = dlc << 16;
	if(canFDFrame.fdFormat == true)
	{
		bit::set(t1, 21);
		if(canFDFrame.bitRateSwitch == true)
		{
			bit::set(t1, 20);
		}
	}
	T[1] = t1;
	
	
	//	Data: 4 Byte per Word, the first Byte in the lowest Bits - the Message RAM only allows Word Access
	for(uint32 word = 0; word < (numberOfBytes + 3) / 4; word++)
	{
		uint32 value = 0;
		for(uint32 i = 0; i < 4; i++)
		{
			const uint32 index = 4 * word + i;
			if(index < canFDFrame.dataSize)
			{
				value |= ((uint32) canFDFrame.data[index]) << (8 * i);
			}
		}
		T[2 + word] = value;
	}
	
	
	//	Request Transmission
	bit::set(*MCU::FDCAN_2::TX_BAR, putIndex);
	nvic.enable_allExceptions();
	return(OK);
}


feedback CAN_2::rx(CAN_FD_Frame& canFDFrame, uint32 fifoID)
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
	
	
	//	Wait for a Frame in the Rx FIFO - listen to the Event before the Fill Level is checked: a Frame arriving in between is then noticed
	while(1)
	{
		cmos.event_listen(m_eventID_frameReadyToRead);
		if(get_numberOfUnread(fifoID) != 0)
		{
			break;
		}
		cmos.sleep_untilEvent(m_eventID_frameReadyToRead);
	}
	
	
	//	Rx FIFO 0 starts at Word 0x2C, Rx FIFO 1 at Word 0x62 of the Message RAM of this Instance, every Element has 18 Words
	volatile uint32* const RX_FnS = (fifoID == 1) ? MCU::FDCAN_2::RX_F1S : MCU::FDCAN_2::RX_F0S;
	const uint32 getIndex = (*RX_FnS & 0x00000300) >> 8;
	volatile uint32* const R = MCU::FDCAN_2::MSG_RAM + 0x2C + 0x36 * fifoID + 0x12 * getIndex;
	
	
	//	R0: ESI Bit 31, XTD Bit 30, RTR Bit 29, ID (standard: Bit 28-18)
	const uint32 r0 = R[0];
	const uint32 r1 = R[1];
	canFDFrame.errorStateIndicator = bit::isSet(r0, 31);
	canFDFrame.extendedID = bit::isSet(r0, 30);
	canFDFrame.remoteTransmissionRequest = bit::isSet(r0, 29);
	if(canFDFrame.extendedID == true)
	{
		canFDFrame.ID = r0 & 0x1FFFFFFF;
	}
	else
	{
		canFDFrame.ID = (r0 >> 18) & 0x000007FF;
	}
	
	
	//	R1: FDF Bit 21, BRS Bit 20, DLC Bit 19-16, Time Stamp Bit 15-0
	canFDFrame.fdFormat = bit::isSet(r1, 21);
	canFDFrame.bitRateSwitch = bit::isSet(r1, 20);
	canFDFrame.timeStamp = r1 & 0x0000FFFF;
	const uint8 dlc = (r1 >> 16) & 0x0000000F;
	if(canFDFrame.fdFormat == true)
	{
		canFDFrame.dataSize = CAN_FD_Frame::get_dataSize(dlc);
	}
	else
	{
		//	A classic CAN Frame may have a DLC of 9 ... 15, that means 8 Byte
		canFDFrame.dataSize = (dlc > 8) ? 8 : dlc;
	}
	
	
	//	Data: 4 Byte per Word, a Remote Frame has none
	const uint32 numberOfBytes = (canFDFrame.remoteTransmissionRequest == true) ? 0 : canFDFrame.dataSize;
	for(uint32 i = 0; i < CAN_FD_Frame::c_dataSize_max; i++)
	{
		canFDFrame.data[i] = 0;
	}
	for(uint32 word = 0; word < (numberOfBytes + 3) / 4; word++)
	{
		const uint32 value = R[2 + word];
		for(uint32 i = 0; i < 4 && 4 * word + i < numberOfBytes; i++)
		{
			canFDFrame.data[4 * word + i] = (value >> (8 * i)) & 0xFF;
		}
	}
	
	
	//	Set the Acknowledge Index to indicate the last read Message to the CAN Controller
	volatile uint32* const RX_FnA = (fifoID == 1) ? MCU::FDCAN_2::RX_F1A : MCU::FDCAN_2::RX_F0A;
	*RX_FnA = getIndex;
	return(OK);
}


feedback CAN_2::rx(CAN_Frame& canFrame, uint32 fifoID)
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
		volatile uint32* RX_FnS = MCU::FDCAN_2::RX_F0S;
		if(fifoID == 1)
		{
			RX_FnS = MCU::FDCAN_2::RX_F1S;
		}
		const uint32 getIndex = (*RX_FnS & 0x00000300) >> 8;
		volatile uint32* const R = MCU::FDCAN_2::MSG_RAM + 0x2C + 0x36 * fifoID + 0x12 * getIndex;
		
		
		//	Check for FDCAN Frame (not supported by this Implementation)
		//	The Element is released anyway, otherwise it would block the FIFO for every following Call
		if(bit::isSet(R[1], 21) == true || bit::isSet(R[1], 20) == true)
		{
			if(fifoID == 1)
			{
				*MCU::FDCAN_2::RX_F1A = getIndex;
			}
			else
			{
				*MCU::FDCAN_2::RX_F0A = getIndex;
			}
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
		if(canFrame.dataSize > 8)
		{
			//	A classic CAN Frame with DLC 9 to 15 carries 8 Data Bytes
			canFrame.dataSize = 8;
		}
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
		volatile uint32* RX_FnA = MCU::FDCAN_2::RX_F0A;
		if(fifoID == 1)
		{
			RX_FnA = MCU::FDCAN_2::RX_F1A;
		}
		*RX_FnA = getIndex;
		
		
		return(OK);
	}
	return(FAIL);
}


uint32 CAN_2::get_numberOfUnread(uint32 fifoID) const
{
	if(fifoID == 0)
	{
		return(*MCU::FDCAN_2::RX_F0S & 0x0000000F);
	}
	if(fifoID == 1)
	{
		return(*MCU::FDCAN_2::RX_F1S & 0x0000000F);
	}
	return(0);
}


bool CAN_2::is_dataAvailable() const
{
	if(get_numberOfUnread(0) > 0 || get_numberOfUnread(1) > 0)
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
	const uint32 PSR = *MCU::FDCAN_2::PSR;
	
	
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
	for(auto& i: m_errors)
	{
		i.second() = false;
	}
}







uint32 CAN_2::get_baudRate() const
{
	return(m_baudRate);
}


uint32 CAN_2::get_dataBitRate() const
{
	//	0 in the classic CAN Mode
	return(m_dataBitRate);
}







feedback CAN_2::recoverFromBusOffState()
{
	//	In Bus-Off the FDCAN sets INIT (CCCR Bit 0) by itself. Clearing it starts the Recovery: after 129 Times 11 recessive Bits the FDCAN
	//	takes Part in the Bus again (RM0440, FDCAN Bus-Off Recovery). Configuration, Filters and Buffers stay unchanged,
	//	so any Thread can call this Function, not only the one owning the Driver
	if(bit::isCleared(*MCU::FDCAN_2::PSR, 7) == true)
	{
		return(OK);
	}
	bit::clear(*MCU::FDCAN_2::CCCR, 0);
	return(OK);
}









CODE_RAM void ISR_FDCAN_2_IT0()
{
	if(CAN_2::m_this != nullptr)
	{
		CAN_2& can = *CAN_2::m_this;
		
		
		//	Read Interrupt Status Register
		const uint32 IR = *MCU::FDCAN_2::IR;
		
		
		//	High Priority Message received
		if(bit::isSet(IR, 6) == true)
		{
			//	Emit Event so that the CAN_2::rx() Function can read the Frame
			CMOS::get().event_emit(can.m_eventID_frameReadyToRead);
			
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 6;
		}
		
		
		//	Rx FIFO 1 Message lost
		if(bit::isSet(IR, 5) == true)
		{
			can.m_errors[I_CAN::e_error::RX_FIFO_OVERFLOW] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 5;
		}
		
		
		//	Rx FIFO 1 Full
		if(bit::isSet(IR, 4) == true)
		{
			//	Cant do anything, just ignore it
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 4;
		}
		
		
		//	Rx FIFO 1 New Message
		if(bit::isSet(IR, 3) == true)
		{
			//	Emit Event so that the CAN_2::rx() Function can read the Frame
			CMOS::get().event_emit(can.m_eventID_frameReadyToRead);
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 3;
		}
		
		
		//	Rx FIFO 0 Message lost
		if(bit::isSet(IR, 2) == true)
		{
			can.m_errors[I_CAN::e_error::RX_FIFO_OVERFLOW] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 2;
		}
		
		//	Rx FIFO 0 Full
		if(bit::isSet(IR, 1) == true)
		{
			//	Cant do anything, just ignore it
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 1;
		}
		
		
		//	Rx FIFO 0 New Message
		if(bit::isSet(IR, 0) == true)
		{
			//	Emit Event so that the CAN_2::rx() Function can read the Frame
			CMOS::get().event_emit(can.m_eventID_frameReadyToRead);
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 0;
		}
	}
}


CODE_RAM void ISR_FDCAN_2_IT1()
{
	if(CAN_2::m_this != nullptr)
	{
		CAN_2& can = *CAN_2::m_this;
		
		
		//	Read Interrupt Status Register
		const uint32 IR = *MCU::FDCAN_2::IR;
		
		
		//	Error: Access to reserved Area
		if(bit::isSet(IR, 23) == true)
		{
			can.m_errors[I_CAN::e_error::ACCESS_TO_RESERVED_AREA] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 23;
		}
		
		
		//	Error: Protocol Error in Data Phase
		if(bit::isSet(IR, 22) == true)
		{
			can.m_errors[I_CAN::e_error::PROTOCOL_ERROR_IN_DATA_PHASE] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 22;
		}
		
		
		//	Error: Protocol Error in Arbitration Phase
		if(bit::isSet(IR, 21) == true)
		{
			can.m_errors[I_CAN::e_error::PROTOCOL_ERROR_IN_ARBITRATION_PHASE] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 21;
		}
		
		
		//	Error: Bus Off State
		if(bit::isSet(IR, 19) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 19;
		}
		
		
		//	Error: Warning Status
		if(bit::isSet(IR, 18) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 18;
		}
		
		
		//	Error: Error Passive State
		if(bit::isSet(IR, 17) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 17;
		}
		
		
		//	Error: Error Logging Overflow
		if(bit::isSet(IR, 16) == true)
		{
			can.m_errors[I_CAN::e_error::ERROR_LOGGING_OVERFLOW] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 16;
		}
		
		
		//	Error: Message RAM Access Failure
		if(bit::isSet(IR, 14) == true)
		{
			can.m_errors[I_CAN::e_error::MESSAGE_RAM_ACCESS_FAILURE] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_2::IR = 1 << 14;
		}
	}
}