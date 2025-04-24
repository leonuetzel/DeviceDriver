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

feedback CAN_1::init(uint32 baudRate, uint32 rxBufferSize, uint32 txBufferSize)
{
	//	Protect from unauthorized Access
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Check for Constraints
	if(rxBufferSize == 0 || txBufferSize == 0)
	{
		return(FAIL);
	}
	
	
	//	Clear Errors
	clearErrors();
	
	
	//	Initialize Buffers and create Semaphores for thread-safe Access to them
	if(m_rxBuffer != nullptr)
	{
		//	Free Memory of old Rx Buffer
		delete m_rxBuffer;
		
		
		//	Delete the corresponding Semaphore (needs to be locked by this Thread to erase)
		if(cmos.semaphore_lock(m_rxBuffer) != OK)
		{
			return(FAIL);
		}
		if(cmos.semaphore_erase(m_rxBuffer) != OK)
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
	if(cmos.semaphore_create(m_rxBuffer) != OK)
	{
		return(FAIL);
	}
	
	
	if(m_txBuffer != nullptr)
	{
		//	Free Memory of old Tx Buffer
		delete m_txBuffer;
		
		
		//	Delete the corresponding Semaphore (needs to be locked by this Thread to erase)
		if(cmos.semaphore_lock(m_txBuffer) != OK)
		{
			return(FAIL);
		}
		if(cmos.semaphore_erase(m_txBuffer) != OK)
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
	if(cmos.semaphore_create(m_txBuffer) != OK)
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
	
	
	//	No valid Configuration found
	if(smallestDeviationBaudRateInPromille == 0xFFFFFFFF)
	{
		return(FAIL);
	}
	
	
	//	Write Values
	uint32 temp = *MCU::CAN_1::BTR & 0xFF80FC00;
	*MCU::CAN_1::BTR = temp | (bestTS2 << 20) | (bestTS1 << 16) | bestBRP;
	
	
	//	Enable Auto-Recovering on Tx Errors
	bit::set(*MCU::CAN_1::MCR, 6);
	
	
	//	Un-freeze CAN during Debug
	bit::clear(*MCU::CAN_1::MCR, 16);
	
	
	//	Filtering: Pass all IDs
	//	Deactivate Filter Bank 0 so we can modify it
	bit::clear(*MCU::CAN_1::FA1R, 0);
	
	
	//	Single 32-Bit Scale Configuration
	bit::set(*MCU::CAN_1::FS1R, 0);
	
	
	//	Filter Mode "Identifier Mask"
	bit::clear(*MCU::CAN_1::FM1R, 0);
	
	
	//	Set Mask and Identifier to '0', letting all IDs pass
	*MCU::CAN_1::F0R1 = 0;
	*MCU::CAN_1::F0R2 = 0;
	
	
	//	Enable Filter Bank 0
	bit::set(*MCU::CAN_1::FA1R, 0);
	
	
	//	Set Filter Mode to active
	bit::clear(*MCU::CAN_1::FMR, 0);
	
	
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
	
	
	//	Set CAN to Normal Operation
	bit::clear(*MCU::CAN_1::MCR, 0);
	
	
	//	Exit from Sleep Mode
	bit::clear(*MCU::CAN_1::MCR, 1);
	
	
	//	Enable all 4 Interrupt Vectors
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::CAN_1_TX,		10);
	nvic.setPriority(Interrupt::CAN_1_RX0,	10);
	nvic.setPriority(Interrupt::CAN_1_RX1,	10);
	nvic.setPriority(Interrupt::CAN_1_SCE,		10);
	nvic.enable(Interrupt::CAN_1_TX);
	nvic.enable(Interrupt::CAN_1_RX0);
	nvic.enable(Interrupt::CAN_1_RX1);
	nvic.enable(Interrupt::CAN_1_SCE);
	
	
	//	Save Baud Rate
	m_baudRate = baudRateCalculated;
	
	
	return(OK);
}







feedback CAN_1::tx(const CAN_Frame& canFrame)
{
	CMOS& cmos = CMOS::get();
	
	
	//	Maximum Packet Data Size is 8 Byte
	if(canFrame.dataSize > 8)
	{
		return(FAIL);
	}
	
	
	//	Lock Semaphore
	if(cmos.semaphore_lock(m_txBuffer) != OK)
	{
		//	Unlock Semaphore
		cmos.semaphore_unlock(m_txBuffer);
		
		
		return(FAIL);
	}
	
	
	//	Always first write the CAN Frame into the Tx Buffer
	//	This is necessary because the Tx ISR might interrupt us in the Middle of checking if the Tx ISR is active
	//	And that would lead to a Race Condition
	if(m_txBuffer->write(canFrame) != OK)
	{
		//	Unlock Semaphore
		cmos.semaphore_unlock(m_txBuffer);
		
		
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
			//	Read Frame back from Tx Buffer
			CAN_Frame canFrameReadBack = m_txBuffer->read();
			
			
			//	Set Tx ISR active Flag because writeToTxMailbox will trigger the Tx ISR
			m_txISR_active = true;
			
			
			//	Write Frame to Tx Mailbox
			if(writeToTxMailbox(canFrameReadBack) != OK)
			{
				//	Unlock Semaphore
				cmos.semaphore_unlock(m_txBuffer);
				return(FAIL);
			}
		}
	}
	
	
	//	Unlock Semaphore
	return(cmos.semaphore_unlock(m_txBuffer));
}


feedback CAN_1::rx(CAN_Frame& canFrame)
{
	if(m_rxBuffer == nullptr)
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
		
		
		//	Lock Semaphore
		if(cmos.semaphore_lock(m_rxBuffer) != OK)
		{
			cmos.semaphore_unlock(m_rxBuffer);
			return(FAIL);
		}
		
		
		//	Read Frame and unlock Semaphore
		if(m_rxBuffer->is_empty() == false)
		{
			canFrame = m_rxBuffer->read();
			return(cmos.semaphore_unlock(m_rxBuffer));
		}
		
		
		//	Unlock Semaphore
		if(cmos.semaphore_unlock(m_rxBuffer) != OK)
		{
			return(FAIL);
		}
	}
	return(FAIL);
}


uint32 CAN_1::get_numberOfUnread() const
{
	return(m_rxBuffer->get_numberOfUnread());
}


bool CAN_1::is_dataAvailable() const
{
	if(m_rxBuffer->is_empty() == true)
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


const UniqueArray<CAN_1::e_error>& CAN_1::get_errors() const
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
	if(get_state() == CAN_1::e_state::BUS_OFF)
	{
		return(init(m_baudRate, m_rxBuffer->get_size(), m_txBuffer->get_size()));
	}
	return(OK);
}









void ISR_CAN_1_TX()
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


void ISR_CAN_1_RX_0()
{
	if(CAN_1::m_this != nullptr)
	{
		CAN_1& can = *CAN_1::m_this;
		if(bit::isSet(*MCU::CAN_1::RF0R, 4) == true)
		{
			can.m_errors += I_CAN::e_error::RX_FIFO_OVERFLOW;
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
						can.m_rxBuffer->write(canFrame);
						emitEvent = true;
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


void ISR_CAN_1_RX_1()
{
	if(CAN_1::m_this != nullptr)
	{
		CAN_1& can = *CAN_1::m_this;
		if(bit::isSet(*MCU::CAN_1::RF1R, 4) == true)
		{
			can.m_errors += I_CAN::e_error::RX_FIFO_OVERFLOW;
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
						can.m_rxBuffer->write(canFrame);
						emitEvent = true;
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
			can.m_errors += (CAN_1::e_error) LEC;
		}
		
		
		//	Clear Interrupt Flag
		bit::set(*MCU::CAN_1::MSR, 2);
	}
}