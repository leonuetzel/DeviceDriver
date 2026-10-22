#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

CAN_1* CAN_1::m_this = nullptr;





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback CAN_1::calculate_bitTiming(uint32 clock, uint32 bitRate, uint32 samplePoint_permille, uint32 deviation_max_permille, uint32 prescaler_max, uint32 segment1_max, uint32 segment2_max, uint32& prescaler, uint32& segment1, uint32& segment2, uint32& bitRateCalculated)
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


feedback CAN_1::write_filters(volatile uint32* standardFilters, volatile uint32* extendedFilters, const Array<s_filterElement>& standardFilterElements, const Array<s_filterElement>& extendedFilterElements)
{
	//	Filter Element (RM0433, FDCAN Message RAM): Type (SFT/EFT) 0 = Range, 1 = Dual ID, 2 = classic Bit Mask
	//	Action (SFEC/EFEC) 0 = disabled, 1 = Rx FIFO 0, 2 = Rx FIFO 1, 3 = reject, 4 = Priority, 5 = Priority and Rx FIFO 0, 6 = Priority and Rx FIFO 1
	//	Only Rx FIFO 0 is configured: the Actions for Rx FIFO 1 store in Rx FIFO 0, so rx() receives all Frames
	for(uint32 list = 0; list < 2; list++)
	{
		const bool extended = (list == 1);
		const Array<s_filterElement>& filterElements = (extended == false) ? standardFilterElements : extendedFilterElements;
		const uint32 id_max = (extended == false) ? 0x000007FF : 0x1FFFFFFF;
		for(uint32 i = 0; i < filterElements.get_size(); i++)
		{
			const s_filterElement& filterElement = filterElements[i];
			if(filterElement.ID1_or_filter > id_max || filterElement.ID2_or_mask > id_max)
			{
				return(FAIL);
			}
			
			
			uint32 type = 0;
			switch(filterElement.type)
			{
				case e_filterType::RANGE:		type = 0x0;		break;
				case e_filterType::DUAL_ID:	type = 0x1;		break;
				case e_filterType::MASK:		type = 0x2;		break;
				default:										return(FAIL);
			}
			uint32 action = 0;
			switch(filterElement.behavior)
			{
				case e_filterBehavior::DISABLED:															action = 0x0;		break;
				case e_filterBehavior::STORE_IN_RX_FIFO_0:										action = 0x1;		break;
				case e_filterBehavior::STORE_IN_RX_FIFO_1:										action = 0x1;		break;
				case e_filterBehavior::REJECT_ID:															action = 0x3;		break;
				case e_filterBehavior::SET_PRIORITY:													action = 0x4;		break;
				case e_filterBehavior::SET_PRIORITY_AND_STORE_IN_RX_FIFO_0:		action = 0x5;		break;
				case e_filterBehavior::SET_PRIORITY_AND_STORE_IN_RX_FIFO_1:		action = 0x5;		break;
				default:																											return(FAIL);
			}
			
			
			if(extended == false)
			{
				//	Standard Filter Element: Type 31:30, Action 29:27, ID 1 26:16, ID 2 or Mask 10:0
				standardFilters[i] = (type << 30) | (action << 27) | (filterElement.ID1_or_filter << 16) | filterElement.ID2_or_mask;
			}
			else
			{
				//	Extended Filter Element: F0 Action 31:29 and ID 1 28:0, F1 Type 31:30 and ID 2 or Mask 28:0
				extendedFilters[2 * i]			= (action << 29) | filterElement.ID1_or_filter;
				extendedFilters[2 * i + 1]	= (type << 30) | filterElement.ID2_or_mask;
			}
		}
	}
	return(OK);
}


feedback CAN_1::init_controller(uint32 nominalBitRate, uint32 dataBitRate, const Array<s_filterElement>& standardFilterElements, const Array<s_filterElement>& extendedFilterElements, bool silentMode, uint32 samplePoint_nominal_permille, uint32 samplePoint_data_permille)
{
	//	Boundary Check - the Data Bit Rate of CAN FD is at least the nominal one
	const bool fd = (dataBitRate != 0);
	if(standardFilterElements.get_size() > numberOfStandardFilterElements || extendedFilterElements.get_size() > numberOfExtendedFilterElements)
	{
		return(FAIL);
	}
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
	bit::set(*MCU::FDCAN_1::FDCAN::CCCR, 0);
	bit::set(*MCU::FDCAN_1::FDCAN::CCCR, 1);
	
	
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
	const uint32 clock_kernel = clock_pll1q;
	
	
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
	*MCU::FDCAN_1::FDCAN::NBTP = ((sjw - 1) << 25) | ((prescaler - 1) << 16) | ((segment1 - 1) << 8) | (segment2 - 1);
	
	
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
		*MCU::FDCAN_1::FDCAN::TDCR = (tdcOffset << 8);
		*MCU::FDCAN_1::FDCAN::DBTP = ((tdc == true) ? (1 << 23) : 0) | ((data_prescaler - 1) << 16) | ((data_segment1 - 1) << 8) | ((data_segment2 - 1) << 4) | (data_sjw - 1);
		
		
		//	CAN FD Operation (FDOE) with Bit Rate Switching (BRSE), ISO CAN FD (NISO = 0)
		bit::set(*MCU::FDCAN_1::FDCAN::CCCR, 8);
		bit::set(*MCU::FDCAN_1::FDCAN::CCCR, 9);
		bit::clear(*MCU::FDCAN_1::FDCAN::CCCR, 15);
	}
	else
	{
		//	Classic CAN: no CAN FD Frames
		bit::clear(*MCU::FDCAN_1::FDCAN::CCCR, 8);
		bit::clear(*MCU::FDCAN_1::FDCAN::CCCR, 9);
	}
	
	
	//	Silent Mode
	if(silentMode == true)
	{
		bit::set(*MCU::FDCAN_1::FDCAN::CCCR, 5);
	}
	else
	{
		bit::clear(*MCU::FDCAN_1::FDCAN::CCCR, 5);
	}
	m_silentMode = silentMode;
	
	
	//	Set up CAN Message RAM
	//	The first Half of the Message RAM is used for CAN 1, the second Half for CAN 2
	//	Message RAM Size is 2560 Words -> 1280 Words for each CAN Controller, CAN 1 starts at Word Offset 0, CAN 2 at Word Offset 1280
	//	Filters: 1 Word per standard, 2 Words per extended Filter Element (at most 128 + 128 Words)
	//	Rx FIFO 0 and Tx FIFO: Elements of 4 Words (2 Words Header, 8 Byte Data) or for CAN FD 18 Words (64 Byte Data)
	//	Classic CAN: 64 Rx and 32 Tx Elements = 384 Words; CAN FD: 32 Rx and 16 Tx Elements = 864 Words; with the Filters at most 1120 Words
	constexpr uint32 offsetMessageRAMInWords							= 0;
	const uint32 elementSizeInWords												= (fd == true) ? 18 : 4;
	const uint32 numberOfRxFIFOElements										= (fd == true) ? 32 : 64;
	const uint32 numberOfTxFIFOElements										= (fd == true) ? 16 : 32;
	const uint32 offsetStandardFilterElementsInWords			= offsetMessageRAMInWords;
	const uint32 offsetExtendedFilterElementsInWords			= offsetStandardFilterElementsInWords + standardFilterElements.get_size();
	const uint32 offsetRxFIFOElementsInWords							= offsetExtendedFilterElementsInWords + 2 * extendedFilterElements.get_size();
	const uint32 offsetTxFIFOElementsInWords							= offsetRxFIFOElementsInWords + numberOfRxFIFOElements * elementSizeInWords;
	
	
	//	Element Sizes of Rx FIFO 0/1, Rx Buffers (RXESC) and Tx Buffers (TXESC): 0 = 8 Byte, 7 = 64 Byte Data
	const uint32 dataFieldSize = (fd == true) ? 0x7 : 0x0;
	*MCU::FDCAN_1::FDCAN::RXESC = (dataFieldSize << 8) | (dataFieldSize << 4) | dataFieldSize;
	*MCU::FDCAN_1::FDCAN::TXESC = dataFieldSize;
	
	
	//	Standard Filter Elements: Number (LSS, Bit 23-16) and Offset in Words (FLSSA, Bit 15-2)
	*MCU::FDCAN_1::FDCAN::SIDFC = (standardFilterElements.get_size() << 16) | (offsetStandardFilterElementsInWords << 2);
	
	
	//	Extended Filter Elements: Number (LSE, Bit 22-16) and Offset in Words (FLESA, Bit 15-2)
	*MCU::FDCAN_1::FDCAN::XIDFC = (extendedFilterElements.get_size() << 16) | (offsetExtendedFilterElementsInWords << 2);
	
	
	//	Rx FIFO 0 collects all Frames, Rx FIFO 1 is not used
	//	Bit 31:			Operation Mode: 0 = Blocking Mode, 1 = Overwrite Mode
	//	Bit 30-24:	Watermark Interrupt Level (0 = disabled)
	//	Bit 22-16:	Number of Rx FIFO Elements
	//	Bit 15-2:		Rx FIFO Offset from Message RAM Base Address in Words
	*MCU::FDCAN_1::FDCAN::RXF0C = (0x00 << 31) | (0x00 << 24) | (numberOfRxFIFOElements << 16) | (offsetRxFIFOElementsInWords << 2);
	*MCU::FDCAN_1::FDCAN::RXF1C = 0;
	
	
	//	Tx FIFO
	//	Bit 30:			Operation Mode: 0 = FIFO Operation, 1 = Queue Mode
	//	Bit 29-24:	Number of Tx FIFO Elements
	//	Bit 21-16:	Number of dedicated Tx Buffers
	//	Bit 15-2:		Tx FIFO Offset from Message RAM Base Address in Words
	*MCU::FDCAN_1::FDCAN::TXBC = (0x01 << 30) | (numberOfTxFIFOElements << 24) | (0x00 << 16) | (offsetTxFIFOElementsInWords << 2);
	
	
	//	Global Filter Policy: Frames without a matching Filter Element are rejected (ANFS/ANFE = 3), with an empty List all Frames of its Kind
	//	go into Rx FIFO 0 (0); the normal Filters also apply to Remote Frames
	const uint32 nonMatching_standard = (standardFilterElements.get_size() == 0) ? 0x0 : 0x3;
	const uint32 nonMatching_extended = (extendedFilterElements.get_size() == 0) ? 0x0 : 0x3;
	*MCU::FDCAN_1::FDCAN::GFC = (nonMatching_standard << 4) | (nonMatching_extended << 2);
	
	
	//	Filter Elements in the Message RAM
	if(write_filters(MCU::FDCAN_MSG_RAM + offsetStandardFilterElementsInWords, MCU::FDCAN_MSG_RAM + offsetExtendedFilterElementsInWords, standardFilterElements, extendedFilterElements) != OK)
	{
		return(FAIL);
	}
	
	
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
	*MCU::FDCAN_1::FDCAN::IE = 0x3BC2000D;
	
	
	//	Enable Interrupt INT0
	*MCU::FDCAN_1::FDCAN::ILE = 0x00000001;
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::FDCAN_1_INT0, 10);
	nvic.enable(Interrupt::FDCAN_1_INT0);
	
	
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
	
	
	//	Save the Configuration before the Controller starts: tx() and rx() use the Element Size
	m_baudRate = nominalBitRateCalculated;
	m_dataBitRate = dataBitRateCalculated;
	m_elementSizeInWords = elementSizeInWords;
	m_standardFilterElements = standardFilterElements;
	m_extendedFilterElements = extendedFilterElements;
	
	
	//	Start CAN Transmissions by clearing INIT Bit in CCCR Register
	bit::clear(*MCU::FDCAN_1::FDCAN::CCCR, 0);
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback CAN_1::init(uint32 baudRate, const Array<s_filterElement>& standardfilterElements, const Array<s_filterElement>& extendedfilterElements, bool silentMode, uint32, uint32)
{
	//	Classic CAN with the Sample Point at 87.5 % - the Rx and Tx FIFOs lie in the Message RAM, there are no Software Buffers
	return(init_controller(baudRate, 0, standardfilterElements, extendedfilterElements, silentMode, 875, 0));
}


feedback CAN_1::init(uint32 nominalBitRate, uint32 dataBitRate, const Array<s_filterElement>& standardFilterElements, const Array<s_filterElement>& extendedFilterElements, bool silentMode, uint32, uint32, uint16 samplePoint_nominal_permille, uint16 samplePoint_data_permille)
{
	//	CAN FD: classic CAN Frames and CAN FD Frames with up to 64 Byte, the Data Phase with the Data Bit Rate (BRS)
	if(dataBitRate == 0)
	{
		return(FAIL);
	}
	return(init_controller(nominalBitRate, dataBitRate, standardFilterElements, extendedFilterElements, silentMode, samplePoint_nominal_permille, samplePoint_data_permille));
}


feedback CAN_1::stop()
{
	bit::set(*MCU::FDCAN_1::FDCAN::CCCR, 0);
	return(OK);
}


feedback CAN_1::tx(const CAN_Frame& canFrame)
{
	//	Maximum Data Size of a classic CAN Frame is 8 Byte
	if(canFrame.dataSize > 8)
	{
		return(FAIL);
	}
	return(tx(CAN_FD_Frame(canFrame)));
}


feedback CAN_1::tx(const CAN_FD_Frame& canFDFrame)
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
	
	
	//	Check if Tx Buffer is full
	if(bit::isSet(*MCU::FDCAN_1::FDCAN::TXFQS, 21) == true)
	{
		//	Tx Buffer is full
		m_errors[e_error::TX_RINGBUFFER_OVERFLOW] = true;
		nvic.enable_allExceptions();
		return(FAIL);
	}
	
	
	//	Start Address of our Tx Element: Tx FIFO Start and Put-Index, the Element Size depends on the Mode (TXESC)
	const uint32 putIndex = (*MCU::FDCAN_1::FDCAN::TXFQS & 0x001F0000) >> 16;
	volatile uint32* const T = MCU::FDCAN_MSG_RAM + ((*MCU::FDCAN_1::FDCAN::TXBC & 0x0000FFFC) >> 2) + putIndex * m_elementSizeInWords;
	
	
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
	bit::set(*MCU::FDCAN_1::FDCAN::TXBAR, putIndex);
	nvic.enable_allExceptions();
	return(OK);
}


feedback CAN_1::rx(CAN_Frame& canFrame, uint32 fifoID)
{
	//	A CAN FD Frame with up to 8 Byte is delivered like a classic Frame, a longer one is read and dropped
	CAN_FD_Frame canFDFrame;
	if(rx(canFDFrame, fifoID) != OK || canFDFrame.dataSize > 8)
	{
		return(FAIL);
	}
	canFrame.extendedID = canFDFrame.extendedID;
	canFrame.ID = canFDFrame.ID;
	canFrame.remoteTransmissionRequest = canFDFrame.remoteTransmissionRequest;
	canFrame.timeStamp = canFDFrame.timeStamp;
	canFrame.dataSize = canFDFrame.dataSize;
	for(uint32 i = 0; i < 8; i++)
	{
		canFrame.data[i] = canFDFrame.data[i];
	}
	return(OK);
}


feedback CAN_1::rx(CAN_FD_Frame& canFDFrame, uint32 fifoID)
{
	//	Only Rx FIFO 0 is configured, init stores all Frames there
	if(fifoID != 0)
	{
		return(FAIL);
	}
	
	
	//	Subscribe to Frame Ready Event
	CMOS& cmos = CMOS::get();
	if(cmos.event_subscribe(m_eventID_frameReadyToRead) != OK)
	{
		return(FAIL);
	}
	
	
	//	Wait for a Frame to be ready to read, this is indicated by the Rx FIFO Fill Level
	//	Listen to the Event before the Fill Level is checked: a Frame arriving in between is then noticed
	while(1)
	{
		cmos.event_listen(m_eventID_frameReadyToRead);
		if(get_numberOfUnread(0) != 0)
		{
			break;
		}
		cmos.sleep_untilEvent(m_eventID_frameReadyToRead);
	}
	
	
	//	Rx Element at the Get-Index of the Rx FIFO 0
	const uint32 offsetRxFifoInWords = (*MCU::FDCAN_1::FDCAN::RXF0C & 0x0000FFFC) >> 2;
	const uint32 getIndex = (*MCU::FDCAN_1::FDCAN::RXF0S & 0x00003F00) >> 8;
	volatile uint32* const R = MCU::FDCAN_MSG_RAM + offsetRxFifoInWords + getIndex * m_elementSizeInWords;
	
	
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
	*MCU::FDCAN_1::FDCAN::RXF0A = getIndex;
	return(OK);
}


uint32 CAN_1::get_numberOfUnread(uint32 fifoID) const
{
	if(fifoID == 0)
	{
		return(*MCU::FDCAN_1::FDCAN::RXF0S & 0x0000007F);
	}
	if(fifoID == 1)
	{
		return(*MCU::FDCAN_1::FDCAN::RXF1S & 0x0000007F);
	}
	return(0);
}


bool CAN_1::is_dataAvailable() const
{
	if(get_numberOfUnread() > 0)
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
	const uint32 PSR = *MCU::FDCAN_1::FDCAN::PSR;
	
	
	//	Read Last Error Code
	const uint8 LEC = PSR & 0x00000007;
	//	0 = no Error, 7 = no Change: only 1 ... 6 are Errors (another Key would be inserted into m_errors, also in the Interrupt)
	if(LEC > 0 && LEC < 0x7)
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
	for(auto& i: m_errors)
	{
		i.second() = false;
	}
}







uint32 CAN_1::get_baudRate() const
{
	return(m_baudRate);
}


uint32 CAN_1::get_dataBitRate() const
{
	//	0 in the classic CAN Mode
	return(m_dataBitRate);
}







feedback CAN_1::recoverFromBusOffState()
{
	//	In Bus-Off the FDCAN sets INIT (CCCR Bit 0) by itself. Clearing it starts the Recovery: after 129 Times 11 recessive Bits the FDCAN
	//	takes Part in the Bus again (RM0433, FDCAN Bus-Off Recovery). Configuration, Filters and Buffers stay unchanged,
	//	so any Thread can call this Function, not only the one owning the Driver
	if(bit::isCleared(*MCU::FDCAN_1::FDCAN::PSR, 7) == true)
	{
		return(OK);
	}
	bit::clear(*MCU::FDCAN_1::FDCAN::CCCR, 0);
	return(OK);
}









CODE_RAM void ISR_FDCAN_1_INT0()
{
	if(CAN_1::m_this != nullptr)
	{
		CAN_1& can = *CAN_1::m_this;
		
		
		//	Read Interrupt Status Register
		const uint32 IR = *MCU::FDCAN_1::FDCAN::IR;
		
		
		if(bit::isSet(IR, 29) == true)
		{
			can.m_errors[I_CAN::e_error::ACCESS_TO_RESERVED_AREA] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 29);
		}
		if(bit::isSet(IR, 28) == true)
		{
			can.m_errors[I_CAN::e_error::PROTOCOL_ERROR_IN_DATA_PHASE] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 28);
		}
		if(bit::isSet(IR, 27) == true)
		{
			can.m_errors[I_CAN::e_error::PROTOCOL_ERROR_IN_ARBITRATION_PHASE] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 27);
		}
		if(bit::isSet(IR, 25) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 25);
		}
		if(bit::isSet(IR, 24) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 24);
		}
		if(bit::isSet(IR, 23) == true)
		{
			can.get_state();
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 23);
		}
		if(bit::isSet(IR, 22) == true)
		{
			can.m_errors[I_CAN::e_error::ERROR_LOGGING_OVERFLOW] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 22);
		}
		if(bit::isSet(IR, 17) == true)
		{
			can.m_errors[I_CAN::e_error::MESSAGE_RAM_ACCESS_FAILURE] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 17);
		}
		if(bit::isSet(IR, 3) == true)
		{
			can.m_errors[I_CAN::e_error::RX_FIFO_OVERFLOW] = true;
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 3);
		}
		if(bit::isSet(IR, 2) == true)
		{
			//	Rx FIFO 0 Full
			//	Cant do anything, just ignore it
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 2);
		}
		if(bit::isSet(IR, 0) == true)
		{
			//	New Message in Rx FIFO 0
			//	Emit Event so that the CAN_1::rx() Function can read the Frame
			CMOS::get().event_emit(can.m_eventID_frameReadyToRead);
			
			//	Clear the Interrupt Flag
			*MCU::FDCAN_1::FDCAN::IR = (1 << 0);
		}
	}
}