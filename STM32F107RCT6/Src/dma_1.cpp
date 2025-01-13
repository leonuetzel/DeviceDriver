#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

Pair<uint16, I_DMA::f_callback> DMA_1::m_channelInfo[c_channel] =
{
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr),
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr),
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr),
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr),
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr),
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr),
	Pair<uint16, I_DMA::f_callback>(CMOS::eventID_invalid, nullptr)
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void DMA_1::executeCallback(uint8 channel)
{
	//	Get Channel Registers
	const uint32 offset = channel * 0x5;
	volatile uint32* DMA_CCR = MCU::DMA_1::CH0_CR + offset;
	
	
	//	Reset EN Bit in DMA_CHx_CCR only if Mode is non-circular, else new DMA Requests wont be served
	if(bit::isCleared(*DMA_CCR, 5) == true)
	{
		bit::clear(*DMA_CCR, 0);
	}
	
	
	//	Callback
	auto& channelInfo(m_channelInfo[channel]);
	
	I_DMA::f_callback& callback(channelInfo.second());
	if(callback != nullptr)
	{
		callback();
		channelInfo.second() = nullptr;
	}
	
	
	//	Wakeup Thread
	CMOS::get().event_emit(channelInfo.first());
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback DMA_1::reset()
{
	//	Check if Channel is valid
	if(m_channel >= c_channel)
	{
		return(FAIL);
	}
	
	
	//	Protect from unauthorized Access
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Get Channel Registers
	const uint32 offset = m_channel * 0x5;
	
	volatile uint32* DMA_CCR	= MCU::DMA_1::CH0_CR		+ offset;
	volatile uint32* DMA_NDTR	= MCU::DMA_1::CH0_NDTR	+ offset;
	volatile uint32* DMA_PAR	= MCU::DMA_1::CH0_PAR		+ offset;
	volatile uint32* DMA_MAR	= MCU::DMA_1::CH0_MAR		+ offset;
	
	
	//	Reset Registers
	*DMA_CCR = 0;
	*DMA_NDTR = 0;
	*DMA_PAR = 0;
	*DMA_MAR = 0;
	bit::set(*MCU::DMA_1::IFCR, m_channel * 4);
	
	
	return(OK);
}


CODE_RAM feedback DMA_1::transfer(const void* source, const void* destination, e_dataType sourceType, e_dataType destinationType, bool source_inc, bool dest_inc, e_direction direction, bool circularMode, uint16 numberOfItems, e_priority priority, bool waitForTransferEnd, f_callback callback)
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
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Get Channel Registers
	const uint32 offset = m_channel * 0x5;
	
	volatile uint32* DMA_CCR	= MCU::DMA_1::CH0_CR		+ offset;
	volatile uint32* DMA_NDTR	= MCU::DMA_1::CH0_NDTR	+ offset;
	volatile uint32* DMA_PAR	= MCU::DMA_1::CH0_PAR		+ offset;
	volatile uint32* DMA_MAR	= MCU::DMA_1::CH0_MAR		+ offset;
	
	
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
	*MCU::DMA_1::IFCR = *MCU::DMA_1::IFCR & (0x0000000F << temp);
	
	
	
	
	
	//	Write to local Values and transfer at the End to DMA Register
	uint32 CCR	= 0;
	uint32 NDTR	= numberOfItems;
	uint32 PAR	= 0;
	uint32 MAR	= 0;
	
	
	//	Enable Transfer Complete Interrupt
	bit::set(CCR, 1);
	
	
	//	Enable Transfer Error Interrupt
	bit::set(CCR, 3);
	
	
	//	Priority
	CCR |= ((uint32) priority) << 12;
	
	
	//	Circular Mode
	if(circularMode == true)
	{
		bit::set(CCR, 5);
	}
	
	
	//	Direction
	CCR |= ((uint32) direction) << 4;
	
	
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
	
	
	//	Subscribe and listen to Channel Event
	cmos.event_subscribe(channelInfo.first());
	cmos.event_listen(channelInfo.first());
	
	
	//	Enable Channel
	bit::set(*DMA_CCR, 0);
	
	
	if(waitForTransferEnd == true)
	{
		cmos.sleep_untilEvent(channelInfo.first());
	}
	
	
	//	Unsubscribe from the Channel Event
	cmos.event_unsubscribe(channelInfo.first());
	
	
	return(OK);
}









CODE_RAM void ISR_DMA1_CH0()
{
	constexpr uint32 channel = 0;
	constexpr uint32 mask = 0x0000000F << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_1::ISR;
	*MCU::DMA_1::IFCR = mask;
	
	
	//	Check CH0
	if((isr & mask) != 0)
	{
		DMA_1::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA1_CH1()
{
	constexpr uint32 channel = 1;
	constexpr uint32 mask = 0x0000000F << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_1::ISR;
	*MCU::DMA_1::IFCR = mask;
	
	
	//	Check CH1
	if((isr & mask) != 0)
	{
		DMA_1::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA1_CH2()
{
	constexpr uint32 channel = 2;
	constexpr uint32 mask = 0x0000000F << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_1::ISR;
	*MCU::DMA_1::IFCR = mask;
	
	
	//	Check CH2
	if((isr & mask) != 0)
	{
		DMA_1::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA1_CH3()
{
	constexpr uint32 channel = 3;
	constexpr uint32 mask = 0x0000000F << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_1::ISR;
	*MCU::DMA_1::IFCR = mask;
	
	
	//	Check CH3
	if((isr & mask) != 0)
	{
		DMA_1::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA1_CH4()
{
	constexpr uint32 channel = 4;
	constexpr uint32 mask = 0x0000000F << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_1::ISR;
	*MCU::DMA_1::IFCR = mask;
	
	
	//	Check CH4
	if((isr & mask) != 0)
	{
		DMA_1::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA1_CH5()
{
	constexpr uint32 channel = 5;
	constexpr uint32 mask = 0x0000000F << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_1::ISR;
	*MCU::DMA_1::IFCR = mask;
	
	
	//	Check CH5
	if((isr & mask) != 0)
	{
		DMA_1::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA1_CH6()
{
	constexpr uint32 channel = 6;
	constexpr uint32 mask = 0x0000000F << (4 * channel);
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	uint32 isr = *MCU::DMA_1::ISR;
	*MCU::DMA_1::IFCR = mask;
	
	
	//	Check CH6
	if((isr & mask) != 0)
	{
		DMA_1::executeCallback(channel);
	}
}