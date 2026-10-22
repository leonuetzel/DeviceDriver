#include "../Inc/stm32l451ret6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

CAN_1* CAN_1::m_this = nullptr;



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback CAN_1::extractFrame(CAN_Frame& canFrame, uint32 RI, uint32 RDT, uint32 RDL, uint32 RDH)
{
	//	CAN ID
	if(bit::isCleared(RI, 2) == true)
	{
		//	Standard ID (11 Bit)
		canFrame.ID = (RI & 0xFFE00000) >> 21;
		canFrame.extendedID = false;
	}
	else
	{
		//	Extended ID (29 Bit)
		canFrame.ID = (RI & 0xFFFFFFF8) >> 3;
		canFrame.extendedID = true;
	}
	
	
	//	Remote Transmission Request
	if(bit::isSet(RI, 1) == true)
	{
		canFrame.remoteTransmissionRequest = true;
	}
	else
	{
		canFrame.remoteTransmissionRequest = false;
	}
	
	
	//	Timestamp
	canFrame.timeStamp = (RDT & 0xFFFF0000) >> 16;
	
	
	//	Data Length Code
	const uint32 dataLengthCode = RDT & 0x0000000F;
	if(dataLengthCode > 8)
	{
		//	Maximum CAN Data Length is 8 Byte
		return(FAIL);
	}
	canFrame.dataSize = dataLengthCode;
	
	
	//	Payload
	for(uint32 j = 0; j < dataLengthCode; j++)
	{
		if(j < 4)
		{
			const uint32 shift = 8 * j;
			const uint32 mask = 0x000000FF << shift;
			canFrame.data[j] = (RDL & mask) >> shift;
		}
		else
		{
			const uint32 shift = 8 * (j - 4);
			const uint32 mask = 0x000000FF << shift;
			canFrame.data[j] = (RDH & mask) >> shift;
		}
	}
	return(OK);
}


bool CAN_1::get_rangeAsMask(const s_filterElement& filterElement, uint32 id_max, uint32& mask)
{
	//	A Range of 2^n IDs that starts at a Multiple of 2^n is a Mask Filter: e.g. 0x000 ... 0x7FF (all standard IDs) or 0x100 ... 0x1FF
	if(filterElement.ID2_or_mask < filterElement.ID1_or_filter || filterElement.ID2_or_mask > id_max)
	{
		return(false);
	}
	const uint32 numberOfIDs = filterElement.ID2_or_mask - filterElement.ID1_or_filter + 1;
	if((numberOfIDs & (numberOfIDs - 1)) != 0 || (filterElement.ID1_or_filter & (numberOfIDs - 1)) != 0)
	{
		return(false);
	}
	mask = id_max & ~(numberOfIDs - 1);
	return(true);
}


feedback CAN_1::check_filters(const Array<s_filterElement>& standardFilterElements, const Array<s_filterElement>& extendedFilterElements)
{
	//	Every Filter Element takes Filter Banks (get_numberOfFilterBanks), all together at most the Banks of this CAN
	//	The bxCAN has no rejecting Filters and no Priority Marker; a Range only works if it is a Mask (get_rangeAsMask)
	uint32 numberOfBanks = 0;
	for(uint32 list = 0; list < 2; list++)
	{
		const bool extended = (list == 1);
		const Array<s_filterElement>& filterElements = (extended == false) ? standardFilterElements : extendedFilterElements;
		const uint32 id_max = (extended == false) ? 0x000007FF : 0x1FFFFFFF;
		for(uint32 i = 0; i < filterElements.get_size(); i++)
		{
			const s_filterElement& filterElement = filterElements[i];
			if(filterElement.behavior == e_filterBehavior::DISABLED)
			{
				continue;
			}
			uint32 mask = 0;
			if((filterElement.type == e_filterType::RANGE && get_rangeAsMask(filterElement, id_max, mask) == false) || filterElement.behavior == e_filterBehavior::REJECT_ID || filterElement.behavior == e_filterBehavior::SET_PRIORITY)
			{
				return(FAIL);
			}
			if(filterElement.ID1_or_filter > id_max || filterElement.ID2_or_mask > id_max)
			{
				return(FAIL);
			}
		}
		numberOfBanks += get_numberOfFilterBanks(filterElements, extended);
	}
	if(numberOfBanks > c_numberOfFilterBanks)
	{
		return(FAIL);
	}
	return(OK);
}


uint32 CAN_1::get_numberOfFilterBanks(const Array<s_filterElement>& filterElements, bool extended)
{
	//	An empty List lets all Frames of its Kind pass: one Bank that only compares the IDE Bit
	if(filterElements.get_size() == 0)
	{
		return(1);
	}
	
	
	//	Mask: one Bank with 32 Bit; Dual ID: one Bank with two 16 Bit Masks (standard ID) or two Banks with 32 Bit (extended ID)
	uint32 numberOfBanks = 0;
	for(uint32 i = 0; i < filterElements.get_size(); i++)
	{
		const s_filterElement& filterElement = filterElements[i];
		if(filterElement.behavior == e_filterBehavior::DISABLED)
		{
			continue;
		}
		numberOfBanks += (filterElement.type == e_filterType::DUAL_ID && extended == true) ? 2 : 1;
	}
	return(numberOfBanks);
}


void CAN_1::set_filterBank(uint32 bank, bool scale_32Bit, uint32 register_1, uint32 register_2, bool fifo_1)
{
	//	Mask Mode in both Scales: the RTR Bit is never compared, so Data and Remote Frames pass
	volatile uint32* const filterRegisters = MCU::CAN_1::F0R1 + 2 * bank;
	if(scale_32Bit == true)
	{
		bit::set(*MCU::CAN_1::FS1R, bank);
	}
	else
	{
		bit::clear(*MCU::CAN_1::FS1R, bank);
	}
	bit::clear(*MCU::CAN_1::FM1R, bank);
	if(fifo_1 == true)
	{
		bit::set(*MCU::CAN_1::FFA1R, bank);
	}
	else
	{
		bit::clear(*MCU::CAN_1::FFA1R, bank);
	}
	filterRegisters[0] = register_1;
	filterRegisters[1] = register_2;
	bit::set(*MCU::CAN_1::FA1R, bank);
}


void CAN_1::program_filters(const Array<s_filterElement>& standardFilterElements, const Array<s_filterElement>& extendedFilterElements)
{
	//	The Filters can only be changed in the Filter Initialization Mode (FINIT), meanwhile no Frame passes
	bit::set(*MCU::CAN_1::FMR, 0);
	
	//	All Banks of this CAN off, check_filters has made sure that the Elements fit
	for(uint32 bank = c_firstFilterBank; bank < c_firstFilterBank + c_numberOfFilterBanks; bank++)
	{
		bit::clear(*MCU::CAN_1::FA1R, bank);
	}
	
	
	//	Register Layout 32 Bit: STID[10:0] in Bits 31:21, EXID[17:0] in Bits 20:3, IDE Bit 2, RTR Bit 1
	//	Register Layout 16 Bit: STID[10:0] in Bits 15:5, RTR Bit 4, IDE Bit 3, EXID[17:15] in Bits 2:0
	uint32 bank = c_firstFilterBank;
	for(uint32 list = 0; list < 2; list++)
	{
		const bool extended = (list == 1);
		const Array<s_filterElement>& filterElements = (extended == false) ? standardFilterElements : extendedFilterElements;
		const uint32 ide = (extended == true) ? (1 << 2) : 0;
		
		
		//	Empty List: all Frames of this Kind pass, only the IDE Bit is compared
		if(filterElements.get_size() == 0)
		{
			set_filterBank(bank, true, ide, (1 << 2), false);
			bank++;
			continue;
		}
		
		
		for(uint32 i = 0; i < filterElements.get_size(); i++)
		{
			const s_filterElement& filterElement = filterElements[i];
			if(filterElement.behavior == e_filterBehavior::DISABLED)
			{
				continue;
			}
			const bool fifo_1 = (filterElement.behavior == e_filterBehavior::STORE_IN_RX_FIFO_1 || filterElement.behavior == e_filterBehavior::SET_PRIORITY_AND_STORE_IN_RX_FIFO_1);
			
			if(filterElement.type == e_filterType::MASK || filterElement.type == e_filterType::RANGE)
			{
				//	ID and Mask, the IDE Bit has to match - a Range is a Mask here, check_filters has made sure that it is one
				uint32 mask = filterElement.ID2_or_mask;
				if(filterElement.type == e_filterType::RANGE)
				{
					get_rangeAsMask(filterElement, (extended == true) ? 0x1FFFFFFF : 0x000007FF, mask);
				}
				const uint32 shift = (extended == true) ? 3 : 21;
				set_filterBank(bank, true, (filterElement.ID1_or_filter << shift) | ide, (mask << shift) | (1 << 2), fifo_1);
				bank++;
			}
			else if(extended == false)
			{
				//	Dual standard ID: two 16 Bit Filters, every ID with its full Mask and the IDE Bit (Mask in the upper Half Word)
				const uint32 mask = (0x000007FF << 5) | (1 << 3);
				set_filterBank(bank, false, (mask << 16) | (filterElement.ID1_or_filter << 5), (mask << 16) | (filterElement.ID2_or_mask << 5), fifo_1);
				bank++;
			}
			else
			{
				//	Dual extended ID: one 32 Bit Bank per ID with the full Mask and the IDE Bit
				const uint32 mask = (((uint32) 0x1FFFFFFF) << 3) | (1 << 2);
				set_filterBank(bank, true, (filterElement.ID1_or_filter << 3) | ide, mask, fifo_1);
				bank++;
				set_filterBank(bank, true, (filterElement.ID2_or_mask << 3) | ide, mask, fifo_1);
				bank++;
			}
		}
	}
	
	
	//	Leave the Filter Initialization Mode, the Filters are active
	bit::clear(*MCU::CAN_1::FMR, 0);
}







feedback CAN_1::writeToTxMailbox(const CAN_Frame& canFrame)
{
	for(uint32 i = 0; i < 3; i++)
	{
		volatile uint32* TIxR = MCU::CAN_1::TI0R + 4 * i;
		
		
		//	Check if Mailbox is empty
		if(bit::isCleared(*TIxR, 0) == true)
		{
			//	Mailbox empty -> Write to it
			volatile uint32* TDTxR = MCU::CAN_1::TDT0R + 4 * i;
			volatile uint32* TDLxR = MCU::CAN_1::TDL0R + 4 * i;
			volatile uint32* TDHxR = MCU::CAN_1::TDH0R + 4 * i;
			
			
			uint32 TI = 0;
			uint32 TDT = 0;
			uint32 TDL = 0;
			uint32 TDH = 0;
			
			
			//	CAN ID
			if(canFrame.extendedID == false)
			{
				TI = (canFrame.ID << 21);
			}
			else
			{
				TI = ((canFrame.ID & 0x1FFFFFFF) << 3) | (1 << 2);
			}
			
			
			//	Remote Transmission Request
			if(canFrame.remoteTransmissionRequest == true)
			{
				bit::set(TI, 1);
			}
			
			
			//	Request Transmission of this Mailbox -> Requires TIxR to be written as last Register
			//	because after setting this Bit, write Access is blocked until it is cleared by Hardware
			bit::set(TI, 0);
			
			
			//	Data Length Code
			const uint32 numberOfByte = canFrame.dataSize;
			TDT = numberOfByte;
			
			
			//	Payload
			for(uint32 i = 0; i < numberOfByte; i++)
			{
				if(i < 4)
				{
					const uint32 shift = 8 * i;
					TDL |= (canFrame.data[i] << shift);
				}
				else
				{
					const uint32 shift = 8 * (i - 4);
					TDH |= (canFrame.data[i] << shift);
				}
			}
			
			
			//	Write Values
			//	TIxR has to be written last because it starts Transmission and therefore the Registers get write-protected automatically
			*TDTxR	= TDT;
			*TDLxR	= TDL;
			*TDHxR	= TDH;
			*TIxR		= TI;
			
			
			return(OK);
		}
	}
	return(FAIL);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback CAN_1::init(uint32 baudRate, const Array<s_filterElement>& standardfilterElements, const Array<s_filterElement>& extendedfilterElements, bool silentMode, uint32 rxBufferSize, uint32 txBufferSize)
{
	//	Boundary Check
	if(standardfilterElements.get_size() > numberOfStandardFilterElements || extendedfilterElements.get_size() > numberOfExtendedFilterElements)
	{
		return(FAIL);
	}
	
	
	//	Filters that the bxCAN can not do are rejected before anything is changed
	if(check_filters(standardfilterElements, extendedfilterElements) != OK)
	{
		return(FAIL);
	}
	
	
	//	Protect from unauthorized Access
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Check for Constraints
	if(rxBufferSize == 0 || txBufferSize == 0)
	{
		return(FAIL);
	}
	
	
	//	Disable the Interrupts while the Buffers and the Error List are replaced: the Interrupt Routines must not access them in between
	//	init enables them again at the End
	NVIC& nvic = cmos.get_nvic();
	nvic.disable(Interrupt::CAN_1_TX);
	nvic.disable(Interrupt::CAN_1_RX0);
	nvic.disable(Interrupt::CAN_1_RX1);
	nvic.disable(Interrupt::CAN_1_SCE);
	m_txISR_active = false;
	
	
	//	Clear Errors
	clearErrors();
	
	
	//	Initialize Buffers and create Mutexes for thread-safe Access to them
	if(m_rxBuffer != nullptr)
	{
		//	Free Memory of old Rx Buffer
		delete m_rxBuffer;
		
		
		//	Delete the corresponding Mutex (needs to be locked by this Thread to erase)
		if(cmos.mutex_lock(m_rxBuffer) != OK)
		{
			return(FAIL);
		}
		if(cmos.mutex_erase(m_rxBuffer) != OK)
		{
			return(FAIL);
		}
	}
	m_rxBuffer = new RingbufferDynamic<CAN_Frame>(rxBufferSize);
	if(m_rxBuffer == nullptr)
	{
		return(FAIL);
	}
	if(m_rxBuffer->is_valid() != true)
	{
		return(FAIL);
	}
	if(cmos.mutex_create(m_rxBuffer) != OK)
	{
		return(FAIL);
	}
	
	
	if(m_txBuffer != nullptr)
	{
		//	Free Memory of old Tx Buffer
		delete m_txBuffer;
		
		
		//	Delete the corresponding Mutex (needs to be locked by this Thread to erase)
		if(cmos.mutex_lock(m_txBuffer) != OK)
		{
			return(FAIL);
		}
		if(cmos.mutex_erase(m_txBuffer) != OK)
		{
			return(FAIL);
		}
	}
	m_txBuffer = new RingbufferDynamic<CAN_Frame>(txBufferSize);
	if(m_txBuffer == nullptr)
	{
		return(FAIL);
	}
	if(m_txBuffer->is_valid() != true)
	{
		return(FAIL);
	}
	if(cmos.mutex_create(m_txBuffer) != OK)
	{
		return(FAIL);
	}
	
	
	//	Disable Bus Clock
	RCC& rcc = STM32L451RET6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::CAN_1, false);
	
	
	//	Reset CAN
	rcc.module_reset(RCC::e_module::CAN_1);
	
	
	//	Enable Bus Clock
	rcc.module_clockInit(RCC::e_module::CAN_1, true);
	
	
	//	Reset Can Master
	bit::set(*MCU::CAN_1::MCR, 15);
	while(bit::isSet(*MCU::CAN_1::MCR, 15) == true)
	{
		
	}
	
	
	//	RM0008 Rev. 21, Chapter 24.4.1, Page 657
	//	Enter Software Initialization Mode
	bit::set(*MCU::CAN_1::MCR, 0);
	while(bit::isCleared(*MCU::CAN_1::MSR, 0) == true)
	{
		
	}
	
	
	//	Sample Point is recommended at 87.5%
	//	RM0008 Rev. 21, Chapter 24.7.7, Page 671, Figure 234
	//	Bit Timings (CAN 1 is located on APB1)
	//	t_PCLK = 1 / clock_apb1
	//	Baud Rate = 1 / Nominal Bit Time
	//	Nominal Bit Time = t_q + t_BS1 + t_BS2
	//	t_q is a "Time Quantum"
	//		t_q		= (BRP[9:0] + 1) x t_PCLK = (BRP[9:0] + 1) / clock_apb1
	//		t_BS1	= t_q x (TS1[3:0] + 1)
	//		t_BS2	= t_q x (TS2[2:0] + 1)
	
	//	Re-arranging these Formulas yields:
	//	Baud Rate = clock_apb1 / ((BRP + 1) x (TS1 + TS2 + 3))
	//	Sample Point [‰] = 1000 x (TS1 + 2) / (TS1 + TS2 + 3)
	const uint32 clock_apb1 = rcc.get_clock_apb1();
	
	uint32 smallestDeviationBaudRateInPromille = 0xFFFFFFFF;
	uint32 smallestDeviationSamplePointInPromille = 0xFFFFFFFF;
	uint32 bestBRP = 0;
	uint32 bestTS1 = 0;
	uint32 bestTS2 = 0;
	uint32 baudRateCalculated = 0;
	for(uint32 BRP = 0; BRP < 1024; BRP++)
	{
		for(uint32 TS1 = 0; TS1 < 16; TS1++)
		{
			for(uint32 TS2 = 0; TS2 < 8; TS2++)
			{
				//	Calculate Baud Rate
				baudRateCalculated = clock_apb1 / ((BRP + 1) * (TS1 + TS2 + 3));
				
				const uint32 deviationBaudRateInPromille = (1000 * Math::absolute<int64>(((int64) baudRateCalculated) - baudRate)) / baudRate;
				if(deviationBaudRateInPromille <= smallestDeviationBaudRateInPromille)
				{
					//	Calculate Sample Point
					const uint32 samplePointPromille = (1000 * (TS1 + 2)) / (TS1 + TS2 + 3);
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
								
								bestBRP = BRP;
								bestTS1 = TS1;
								bestTS2 = TS2;
							}
						}
						else
						{
							//	Better Configuration found - save it
							smallestDeviationBaudRateInPromille = deviationBaudRateInPromille;
							smallestDeviationSamplePointInPromille = deviationSamplePointInPromille;
							
							bestBRP = BRP;
							bestTS1 = TS1;
							bestTS2 = TS2;
						}
						
					}
				}
			}
		}
	}
	baudRateCalculated = clock_apb1 / ((bestBRP + 1) * (bestTS1 + bestTS2 + 3));
	
	
	//	No valid Configuration found, or the Baud Rate deviates too much
	//	CAN tolerates at most 1.58 % Clock Deviation (ISO 11898-1), more than 15 Promille cannot work reliably
	if(smallestDeviationBaudRateInPromille > 15)
	{
		return(FAIL);
	}
	
	
	//	Write Values
	uint32 temp = *MCU::CAN_1::BTR & 0xFF80FC00;
	*MCU::CAN_1::BTR = temp | (bestTS2 << 20) | (bestTS1 << 16) | bestBRP;
	
	
	//	Silent Mode
	if(silentMode == true)
	{
		bit::set(*MCU::CAN_1::BTR, 31);
	}
	else
	{
		bit::clear(*MCU::CAN_1::BTR, 31);
	}
	m_silentMode = silentMode;
	
	
	//	Enable Auto-Recovering on Tx Errors
	bit::set(*MCU::CAN_1::MCR, 6);
	
	
	//	Un-freeze CAN during Debug
	bit::clear(*MCU::CAN_1::MCR, 16);
	
	
	//	Filters: an empty List lets all Frames of its Kind (standard or extended ID) pass
	program_filters(standardfilterElements, extendedfilterElements);
	
	
	//	Enable Error Interrupt (when any Error is pending in CAN_ESR)
	bit::set(*MCU::CAN_1::IER, 15);
	
	
	//	Enable LEC (Last Error Code) Interrupt
	bit::set(*MCU::CAN_1::IER, 11);
	
	
	//	Enable Bus Off (entered when too much Errors occured on Tx Side) Interrupt
	bit::set(*MCU::CAN_1::IER, 10);
	
	
	//	Enable Error Passive (when too much Errors occured on Rx Side) Interrupt
	bit::set(*MCU::CAN_1::IER, 9);
	
	
	//	Enable Rx FIFO 1 Overrun Interrupt
	bit::set(*MCU::CAN_1::IER, 6);
	
	
	//	Enable Rx FIFO 1 Message Pending Interrupt
	bit::set(*MCU::CAN_1::IER, 4);
	
	
	//	Enable Rx FIFO 0 Overrun Interrupt
	bit::set(*MCU::CAN_1::IER, 3);
	
	
	//	Enable Rx FIFO 0 Message Pending Interrupt
	bit::set(*MCU::CAN_1::IER, 1);
	
	
	//	Enable Tx Mailbox Empty Interrupt
	bit::set(*MCU::CAN_1::IER, 0);
	
	
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
	
	
	//	Set CAN to Normal Operation
	bit::clear(*MCU::CAN_1::MCR, 0);
	
	
	//	Exit from Sleep Mode
	bit::clear(*MCU::CAN_1::MCR, 1);
	
	
	//	Enable all 4 Interrupt Vectors
	nvic.setPriority(Interrupt::CAN_1_TX,		10);
	nvic.setPriority(Interrupt::CAN_1_RX0,	10);
	nvic.setPriority(Interrupt::CAN_1_RX1,	10);
	nvic.setPriority(Interrupt::CAN_1_SCE,	10);
	nvic.enable(Interrupt::CAN_1_TX);
	nvic.enable(Interrupt::CAN_1_RX0);
	nvic.enable(Interrupt::CAN_1_RX1);
	nvic.enable(Interrupt::CAN_1_SCE);
	
	
	//	Save Baud Rate
	m_baudRate = baudRateCalculated;
	
	
	//	Save Filter Elements
	m_standardFilterElements = standardfilterElements;
	m_extendedFilterElements = extendedfilterElements;
	
	
	return(OK);
}


feedback CAN_1::stop()
{
	bit::set(*MCU::CAN_1::MCR, 0);
	return(OK);
}







feedback CAN_1::tx(const CAN_Frame& canFrame)
{
	CMOS& cmos = CMOS::get();
	
	
	//	Maximum Packet Data Size is 8 Byte, the Driver must be initialized
	if(canFrame.dataSize > 8 || m_txBuffer == nullptr)
	{
		return(FAIL);
	}
	
	
	//	Lock Mutex
	if(cmos.mutex_lock(m_txBuffer) != OK)
	{
		//	Unlock Mutex
		cmos.mutex_unlock(m_txBuffer);
		
		
		return(FAIL);
	}
	
	
	//	Always first write the CAN Frame into the Tx Buffer
	//	This is necessary because the Tx ISR might interrupt us in the Middle of checking if the Tx ISR is active
	//	And that would lead to a Race Condition
	if(m_txBuffer->write(canFrame) != OK)
	{
		m_errors[e_error::TX_RINGBUFFER_OVERFLOW] = true;
		
		
		//	Unlock Mutex
		cmos.mutex_unlock(m_txBuffer);
		
		
		return(FAIL);
	}
	
	
	//	Then check for an active Tx ISR
	//	Read the Frame back from the Tx Buffer and write it myself into the Tx Mailbox if the Tx ISR isnt active anymore
	//	This will trigger the Tx ISR for subsequent Frames
	if(m_txISR_active == false)
	{
		//	Check for an empty Tx Buffer in case the Tx ISR interrupted us and emptied the Tx Buffer
		if(m_txBuffer->is_empty() == false)
		{
			//	Copy the Frame from the Tx Buffer, it is only removed once it is in a Tx Mailbox
			//	The Tx Interrupt is masked meanwhile: it must not take the same Frame from the Buffer again
			NVIC& nvic = cmos.get_nvic();
			nvic.disable(Interrupt::CAN_1_TX);
			CAN_Frame canFrameReadBack;
			if(m_txBuffer->peek(0, canFrameReadBack) == OK)
			{
				//	Set Tx ISR active Flag because writeToTxMailbox will trigger the Tx ISR
				m_txISR_active = true;
				
				
				//	Write Frame to Tx Mailbox
				//	If all 3 Mailboxes are still pending, the Frame stays in the Tx Buffer: every pending Mailbox triggers the Tx ISR when it is done
				//	and the Tx ISR transmits the Frame then, so the Frame is queued like with an active Tx ISR
				if(writeToTxMailbox(canFrameReadBack) == OK)
				{
					m_txBuffer->read();
				}
			}
			nvic.enable(Interrupt::CAN_1_TX);
		}
	}
	
	
	//	Unlock Mutex
	return(cmos.mutex_unlock(m_txBuffer));
}


feedback CAN_1::rx(CAN_Frame& canFrame, uint32 fifoID)
{
	if(m_rxBuffer == nullptr || fifoID > 0)
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
		while(m_rxBuffer->is_empty() == true)
		{
			cmos.event_listen(m_eventID_frameReadyToRead);
			cmos.sleep_untilEvent(m_eventID_frameReadyToRead);
		}
		
		
		//	Lock Mutex
		if(cmos.mutex_lock(m_rxBuffer) != OK)
		{
			cmos.mutex_unlock(m_rxBuffer);
			return(FAIL);
		}
		
		
		//	Read Frame and unlock Mutex
		if(m_rxBuffer->is_empty() == false)
		{
			canFrame = m_rxBuffer->read();
			return(cmos.mutex_unlock(m_rxBuffer));
		}
		
		
		//	Unlock Mutex
		if(cmos.mutex_unlock(m_rxBuffer) != OK)
		{
			return(FAIL);
		}
	}
	return(FAIL);
}


uint32 CAN_1::get_numberOfUnread(uint32 fifoID) const
{
	if(fifoID > 0 || m_rxBuffer == nullptr)
	{
		return(0);
	}
	return(m_rxBuffer->get_numberOfUnread());
}


bool CAN_1::is_dataAvailable() const
{
	if(m_rxBuffer == nullptr || m_rxBuffer->is_empty() == true)
	{
		return(false);
	}
	return(true);
}







uint16 CAN_1::get_eventID()
{
	return(m_eventID_frameReadyToRead);
}


CAN_1::e_state CAN_1::get_state()
{
	//	CAN State Machine
	CAN_1::e_state state = CAN_1::e_state::ERROR_ACTIVE;
	
	
	//	Read Error Status Register
	const uint32 ESR = *MCU::CAN_1::ESR;
	
	
	//	Rx Error Counter too high -> Error Passive State
	if(bit::isSet(ESR, 1) == true)
	{
		state = CAN_1::e_state::ERROR_PASSIVE;
	}
	
	
	//	Tx Error Counter too high -> Bus Off State
	if(bit::isSet(ESR, 2) == true)
	{
		state = CAN_1::e_state::BUS_OFF;
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







feedback CAN_1::recoverFromBusOffState()
{
	//	init sets ABOM (Automatic Bus-Off Management): the Controller leaves Bus-Off by itself after 128 Occurrences of 11 recessive Bits
	//	Without ABOM, setting and clearing INRQ starts the Recovery (bxCAN, Bus-Off recovery)
	//	Buffers, Filters and Bit Timing stay unchanged, so any Thread can call this Function, not only the one owning the Driver
	if(get_state() != CAN_1::e_state::BUS_OFF || bit::isSet(*MCU::CAN_1::MCR, 6) == true)
	{
		return(OK);
	}
	bit::set(*MCU::CAN_1::MCR, 0);
	uint32 timeout = 100000;
	while(bit::isCleared(*MCU::CAN_1::MSR, 0) == true)
	{
		timeout--;
		if(timeout == 0)
		{
			return(FAIL);
		}
	}
	bit::clear(*MCU::CAN_1::MCR, 0);
	return(OK);
}









CODE_RAM void ISR_CAN_1_TX()
{
	if(CAN_1::m_this == nullptr)
	{
		return;
	}
	CAN_1& can = *CAN_1::m_this;
	if(can.m_txBuffer == nullptr)
	{
		return;
	}
	if(can.m_txBuffer->is_valid() != true)
	{
		return;
	}
	
	
	
	//	Search for a free Tx Mailbox (but only one, dont clear all Request Completed Flags, else this ISR wont be called again)
	bool anyTxMailboxFree = false;
	for(uint32 i = 0; i < 3; i++)
	{
		const uint32 bit = 8 * i;
		
		//	Tx Mailbox i Request completed
		if(bit::isSet(*MCU::CAN_1::TSR, bit) == true)
		{
			//	Clear Request completed Bit by writing 1 to it
			*MCU::CAN_1::TSR = (1 << bit);
			
			
			anyTxMailboxFree = true;
			break;
		}
	}
	
	
	//	Transmit next Frame
	if(anyTxMailboxFree == true)
	{
		if(can.m_txBuffer->is_empty() == false)
		{
			//	Transmit Frame
			CAN_Frame canFrame = can.m_txBuffer->read();
			while(can.writeToTxMailbox(canFrame) != OK)
			{
				
			}
		}
		else
		{
			//	No more Frames to transmit - note that this ISR wont be called again because we havent triggered a Tx Request in this ISR
			can.m_txISR_active = false;
		}
	}
	else
	{
		//	No free Slot - note that this ISR wont be called again because we havent triggered a Tx Request in this ISR
		can.m_txISR_active = false;
	}
}


CODE_RAM void ISR_CAN_1_RX0()
{
	if(CAN_1::m_this != nullptr)
	{
		CAN_1& can = *CAN_1::m_this;
		if(bit::isSet(*MCU::CAN_1::RF0R, 4) == true)
		{
			can.m_errors[I_CAN::e_error::RX_FIFO_OVERFLOW] = true;
		}
		
		
		if(can.m_rxBuffer != nullptr)
		{
			if(can.m_rxBuffer->is_valid() == true)
			{
				bool emitEvent = false;
				
				
				const uint32 numberOfMessagesInFIFO = *MCU::CAN_1::RF0R & 0x00000003;
				for(uint32 i = 0 ; i < numberOfMessagesInFIFO; i++)
				{
					const uint32 RI		= *MCU::CAN_1::RI0R;
					const uint32 RDT	= *MCU::CAN_1::RDT0R;
					const uint32 RDL	= *MCU::CAN_1::RDL0R;
					const uint32 RDH	= *MCU::CAN_1::RDH0R;
					
					
					//	Release FIFO Rx Mail
					bit::set(*MCU::CAN_1::RF0R, 5);
					
					
					//	Reserve Memory for CAN Frame
					CAN_Frame canFrame;
					
					
					//	Extract CAN Frame
					if(can.extractFrame(canFrame, RI, RDT, RDL, RDH) == OK)
					{
						if(can.m_rxBuffer->write(canFrame) == OK)
						{
							emitEvent = true;
						}
						else
						{
							//	Software Rx Buffer full, the Frame is lost
							can.m_errors[I_CAN::e_error::RX_RINGBUFFER_OVERFLOW] = true;
						}
					}
				}
				
				
				if(emitEvent == true)
				{
					CMOS::get().event_emit(can.m_eventID_frameReadyToRead);
				}
			}
		}
	}
}


CODE_RAM void ISR_CAN_1_RX1()
{
	if(CAN_1::m_this != nullptr)
	{
		CAN_1& can = *CAN_1::m_this;
		if(bit::isSet(*MCU::CAN_1::RF1R, 4) == true)
		{
			can.m_errors[I_CAN::e_error::RX_FIFO_OVERFLOW] = true;
		}
		
		
		if(can.m_rxBuffer != nullptr)
		{
			if(can.m_rxBuffer->is_valid() == true)
			{
				bool emitEvent = false;
				
				
				const uint32 numberOfMessagesInFIFO = *MCU::CAN_1::RF1R & 0x00000003;
				for(uint32 i = 0 ; i < numberOfMessagesInFIFO; i++)
				{
					const uint32 RI		= *MCU::CAN_1::RI1R;
					const uint32 RDT	= *MCU::CAN_1::RDT1R;
					const uint32 RDL	= *MCU::CAN_1::RDL1R;
					const uint32 RDH	= *MCU::CAN_1::RDH1R;
					
					
					//	Release FIFO Rx Mail
					bit::set(*MCU::CAN_1::RF1R, 5);
					
					
					//	Reserve Memory for CAN Frame
					CAN_Frame canFrame;
					
					
					//	Extract CAN Frame
					if(can.extractFrame(canFrame, RI, RDT, RDL, RDH) == OK)
					{
						if(can.m_rxBuffer->write(canFrame) == OK)
						{
							emitEvent = true;
						}
						else
						{
							//	Software Rx Buffer full, the Frame is lost
							can.m_errors[I_CAN::e_error::RX_RINGBUFFER_OVERFLOW] = true;
						}
					}
				}
				
				
				if(emitEvent == true)
				{
					CMOS::get().event_emit(can.m_eventID_frameReadyToRead);
				}
			}
		}
	}
}


void ISR_CAN_1_SCE()
{
	if(CAN_1::m_this != nullptr)
	{
		CAN_1& can = *CAN_1::m_this;
		
		
		//	Read Error Status Register
		const uint32 ESR = *MCU::CAN_1::ESR;
		
		
		//	CAN State Machine
		CAN_1::e_state state = CAN_1::e_state::ERROR_ACTIVE;
		
		
		//	Rx Error Counter too high -> Error Passive State
		if(bit::isSet(ESR, 1) == true)
		{
			state = CAN_1::e_state::ERROR_PASSIVE;
		}
		
		
		//	Tx Error Counter too high -> Bus Off State
		if(bit::isSet(ESR, 2) == true)
		{
			state = CAN_1::e_state::BUS_OFF;
		}
		can.m_state = state;
		
		
		//	Last Error Code (LEC)
		const uint8 LEC = (ESR & 0x00000070) >> 4;
		if(LEC > 0)
		{
			can.m_errors[(CAN_1::e_error) LEC] = true;
		}
		
		
		//	Clear Interrupt Flag
		bit::set(*MCU::CAN_1::MSR, 2);
	}
}