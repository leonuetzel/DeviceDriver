#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

Pair<uint16, I_DMA::f_callback> DMA_2::m_channelInfo[c_channel] =
{
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr),
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr),
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr),
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr),
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr)
};

volatile bool DMA_2::m_transferError[c_channel] = {};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void DMA_2::executeCallback(uint8 channel)
{
	//	Get Channel Registers
	const uint32 offset = channel * 0x5;
	volatile uint32* DMA_CCR = MCU::DMA_2::CH0_CR + offset;
	
	
	//	A Transfer Error disables the Channel by Hardware (EN = 0), a completed Transfer leaves it enabled until it is disabled here
	const bool circularMode = bit::isSet(*DMA_CCR, 5);
	m_transferError[channel] = bit::isCleared(*DMA_CCR, 0);
	
	
	//	Reset EN Bit in DMA_CHx_CCR only if Mode is non-circular, else new DMA Requests wont be served
	if(circularMode == false)
	{
		bit::clear(*DMA_CCR, 0);
	}
	
	
	//	Callback, in Circular Mode after every Round
	auto& channelInfo(m_channelInfo[channel]);
	
	I_DMA::f_callback& callback(channelInfo.second());
	if(callback != nullptr)
	{
		callback();
		if(circularMode == false)
		{
			channelInfo.second() = nullptr;
		}
	}
	
	
	//	Wakeup Thread
	CMOS::get().event_emit(channelInfo.first());
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback DMA_2::reset()
{
	//	Check if Channel is valid
	if(m_channel >= c_channel)
	{
		return(FAIL);
	}
	
	
	//	Protect from unauthorized Access
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Get Channel Registers
	const uint32 offset = m_channel * 0x5;
	
	volatile uint32* DMA_CCR	= MCU::DMA_2::CH0_CR		+ offset;
	volatile uint32* DMA_NDTR	= MCU::DMA_2::CH0_NDTR	+ offset;
	volatile uint32* DMA_PAR	= MCU::DMA_2::CH0_PAR		+ offset;
	volatile uint32* DMA_MAR	= MCU::DMA_2::CH0_MAR		+ offset;
	
	
	//	Reset Registers
	*DMA_CCR = 0;
	*DMA_NDTR = 0;
	*DMA_PAR = 0;
	*DMA_MAR = 0;
	bit::set(*MCU::DMA_2::IFCR, m_channel * 4);
	
	
	return(OK);
}


bool DMA_2::is_busy() const
{
	//	The Channel stays enabled until the Interrupt Routine has ended a single Transfer, a Transfer Error disables it by Hardware
	//	A circular Transfer runs until reset(). transfer() refuses the Channel as long as it is busy
	if(m_channel >= c_channel)
	{
		return(false);
	}
	const uint32 offset = m_channel * 0x5;
	return(bit::isSet(*(MCU::DMA_2::CH0_CR + offset), 0));
}


uint16 DMA_2::get_eventID() const
{
	//	executeCallback() emits it at the End of every non-circular Transfer, also without a waiting Thread, and after a Transfer Error:
	//	transfer() always enables the Transfer Complete and the Transfer Error Interrupt of a non-circular Transfer
	if(m_channel >= c_channel)
	{
		return(CMOS::eventID_invalid);
	}
	return(m_channelInfo[m_channel].first());
}


feedback DMA_2::transfer(const void* source, const void* destination, e_dataType sourceType, e_dataType destinationType, bool source_inc, bool dest_inc, e_direction direction, bool circularMode, uint16 numberOfItems, e_priority priority, bool waitForTransferEnd, f_callback callback)
{
	//	Check if Channel is valid
	if(m_channel >= c_channel)
	{
		return(FAIL);
	}
	
	
	//	Check Number of Items to transfer
	if(numberOfItems == 0)
	{
		return(OK);
	}
	
	
	//	Circular Mode and MEMORY_TO_MEMORY isnt allowed simultaneously
	if(circularMode == true && direction == e_direction::MEMORY_TO_MEMORY)
	{
		return(FAIL);
	}
	
	
	//	Protect from unauthorized Access
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Get Channel Registers
	const uint32 offset = m_channel * 0x5;
	
	volatile uint32* DMA_CCR	= MCU::DMA_2::CH0_CR		+ offset;
	volatile uint32* DMA_NDTR	= MCU::DMA_2::CH0_NDTR	+ offset;
	volatile uint32* DMA_PAR	= MCU::DMA_2::CH0_PAR		+ offset;
	volatile uint32* DMA_MAR	= MCU::DMA_2::CH0_MAR		+ offset;
	
	
	//	Channel already used
	if(bit::isSet(*DMA_CCR, 0) == true)
	{
		return(FAIL);
	}
	
	
	//	Set Callback Function
	auto& channelInfo(m_channelInfo[m_channel]);
	channelInfo.second() = callback;
	
	
	//	Clear Interrupt Flags
	uint32 temp = m_channel * 4;
	*MCU::DMA_2::IFCR = 0x0000000F << temp;																	//	IFCR is write-only and reads as 0, so the Flags are written directly
	
	
	
	
	
	//	Write to local Values and transfer at the End to DMA Register
	uint32 CCR	= 0;
	uint32 NDTR	= numberOfItems;
	uint32 PAR	= 0;
	uint32 MAR	= 0;
	
	
	//	Enable Transfer Complete Interrupt: it ends the Transfer, wakes the waiting Thread and calls the Callback
	//	A circular Transfer without Callback and without waiting needs none, else it would come after every Round with nothing to do (e.g. ADC)
	if(circularMode == false || waitForTransferEnd == true || callback != nullptr)
	{
		bit::set(CCR, 1);
	}
	
	
	//	Enable Transfer Error Interrupt
	bit::set(CCR, 3);
	
	
	//	Priority
	CCR |= ((uint32) priority) << 12;
	
	
	//	Circular Mode
	if(circularMode == true)
	{
		bit::set(CCR, 5);
	}
	
	
	//	Direction: DIR (Bit 4) means "read from Memory" and is set for MEMORY_TO_PERIPHERAL only
	//	MEMORY_TO_MEMORY reads from the Peripheral Address with MEM2MEM (Bit 14) set below; the Value 2 of the Direction would set CIRC (Bit 5)
	if(direction == e_direction::MEMORY_TO_PERIPHERAL)
	{
		bit::set(CCR, 4);
	}
	
	
	//	Set Memory Pointers and Increments (MEMORY_TO_MEMORY is essentially the same as PERIPHERAL_TO_MEMORY, so we change direction to save Code Space)
	if(direction == e_direction::MEMORY_TO_MEMORY)
	{
		bit::set(CCR, 14);
		direction = e_direction::PERIPHERAL_TO_MEMORY;
	}
	
	switch(direction)
	{
		case e_direction::PERIPHERAL_TO_MEMORY:
		{
			//	Memory Pointers
			PAR = (uint32) source;
			MAR = (uint32) destination;
			
			
			//	Data Types
			CCR |= ((uint32) sourceType) << 8;
			CCR |= ((uint32) destinationType) << 10;
			
			
			//	Increments
			if(source_inc == true)
			{
				bit::set(CCR, 6);
			}
			if(dest_inc == true)
			{
				bit::set(CCR, 7);
			}
		}
		break;
		
		case e_direction::MEMORY_TO_PERIPHERAL:
		{
			//	Memory Pointers
			PAR = (uint32) destination;
			MAR = (uint32) source;
			
			
			//	Data Types
			CCR |= ((uint32) destinationType) << 8;
			CCR |= ((uint32) sourceType) << 10;
			
			
			//	Increments
			if(source_inc == true)
			{
				bit::set(CCR, 7);
			}
			if(dest_inc == true)
			{
				bit::set(CCR, 6);
			}
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	
	//	Transfer local Values to DMA Registers
	*DMA_CCR	= CCR;
	*DMA_NDTR	= NDTR;
	*DMA_PAR	= PAR;
	*DMA_MAR	= MAR;
	
	
	//	Enable Channel, the Interrupt Routine notes a Transfer Error
	//	Only a waiting Thread needs the Channel Event: it subscribes before the Channel is enabled, so it cannot miss the End
	m_transferError[m_channel] = false;
	if(waitForTransferEnd == false)
	{
		bit::set(*DMA_CCR, 0);
		return(OK);
	}
	cmos.event_subscribe(channelInfo.first());
	cmos.event_listen(channelInfo.first());
	bit::set(*DMA_CCR, 0);
	cmos.sleep_untilEvent(channelInfo.first());
	cmos.event_unsubscribe(channelInfo.first());
	
	
	//	A Transfer Error ends the Transfer as well
	if(m_transferError[m_channel] == true)
	{
		return(FAIL);
	}
	return(OK);
}









//	The Interrupt Routines clear and evaluate only TCIF, HTIF and TEIF, never GIF: clearing GIF in the Clock Cycle of a Transfer Error
//	prevents the automatic Channel Disable and TEIF (Errata Sheets: DMA disable failure and error flag omission upon simultaneous
//	transfer error and global flag clear). GIF stays set, transfer() clears all Flags before the Channel is enabled again.
void ISR_DMA2_CH0()
{
	constexpr uint32 channel = 0;
	constexpr uint32 mask = 0x0000000E << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_2::ISR;
	*MCU::DMA_2::IFCR = mask;
	
	
	//	Check CH0
	if((isr & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


void ISR_DMA2_CH1()
{
	constexpr uint32 channel = 1;
	constexpr uint32 mask = 0x0000000E << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_2::ISR;
	*MCU::DMA_2::IFCR = mask;
	
	
	//	Check CH1
	if((isr & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


void ISR_DMA2_CH2()
{
	constexpr uint32 channel = 2;
	constexpr uint32 mask = 0x0000000E << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_2::ISR;
	*MCU::DMA_2::IFCR = mask;
	
	
	//	Check CH2
	if((isr & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


void ISR_DMA2_CH3()
{
	constexpr uint32 channel = 3;
	constexpr uint32 mask = 0x0000000E << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_2::ISR;
	*MCU::DMA_2::IFCR = mask;
	
	
	//	Check CH3
	if((isr & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


void ISR_DMA2_CH4()
{
	constexpr uint32 channel = 4;
	constexpr uint32 mask = 0x0000000E << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_2::ISR;
	*MCU::DMA_2::IFCR = mask;
	
	
	//	Check CH4
	if((isr & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}