#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

//	First: Event ID
//	Second: Callback Function
//	Third: IsCircular Mode Transfer - dont set callback to nullptr after Transfer if true
Triplet<uint16, I_DMA::f_callback, bool> DMA_2::m_channelInfo[c_channel] =
{
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false)
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback DMA_2::startup(uint8 channel)
{
	//	Check Channel Boundaries
	if(m_channel != c_channel || channel >= c_channel)
	{
		return(FAIL);
	}
	
	m_channel = channel;
	
	
	//	Create Semaphore
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_create(this) != OK)
	{
		return(FAIL);
	}
	
	
	//	Create Event
	auto& channelInfo = m_channelInfo[m_channel];
	channelInfo.first() = cmos.event_create();
	
	
	//	Init Interrupts only once
	if(channel == 0)
	{
		NVIC& nvic = cmos.get_nvic();
		nvic.setPriority(Interrupt::DMA_2_CH0, 10);
		nvic.setPriority(Interrupt::DMA_2_CH1, 10);
		nvic.setPriority(Interrupt::DMA_2_CH2, 10);
		nvic.setPriority(Interrupt::DMA_2_CH3, 10);
		nvic.setPriority(Interrupt::DMA_2_CH4, 10);
		nvic.setPriority(Interrupt::DMA_2_CH5, 10);
		nvic.setPriority(Interrupt::DMA_2_CH6, 10);
		nvic.setPriority(Interrupt::DMA_2_CH7, 10);
		
		nvic.enable(Interrupt::DMA_2_CH0);
		nvic.enable(Interrupt::DMA_2_CH1);
		nvic.enable(Interrupt::DMA_2_CH2);
		nvic.enable(Interrupt::DMA_2_CH3);
		nvic.enable(Interrupt::DMA_2_CH4);
		nvic.enable(Interrupt::DMA_2_CH5);
		nvic.enable(Interrupt::DMA_2_CH6);
		nvic.enable(Interrupt::DMA_2_CH7);
		
		
		RCC& rcc = STM32H753BIT6::get().get_rcc();
		rcc.module_clockInit(RCC::e_module::DMA_2, true);
	}
	return(OK);
}


CODE_RAM void DMA_2::executeCallback(uint8 channel)
{
	//	Get Channel Registers
	const uint32 offset = channel * 0x6;
	volatile uint32* DMA_CCR = MCU::DMA_2::CH0_CR + offset;
	
	
	//	Reset EN Bit in DMA_CHx_CCR only if Mode is non-circular, else new DMA Requests wont be served
	if(bit::isCleared(*DMA_CCR, 8) == true)
	{
		bit::clear(*DMA_CCR, 0);
	}
	
	
	//	Callback
	auto& channelInfo(m_channelInfo[channel]);
	
	I_DMA::f_callback& callback(channelInfo.second());
	if(callback != nullptr)
	{
		callback();
		if(channelInfo.third() == false)
		{
			callback = nullptr;
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
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Get Channel Registers
	const uint32 offset = m_channel * 0x6;
	
	volatile uint32* DMA_CCR	= MCU::DMA_2::CH0_CR		+ offset;
	volatile uint32* DMA_NDTR	= MCU::DMA_2::CH0_NDTR	+ offset;
	volatile uint32* DMA_PAR	= MCU::DMA_2::CH0_PAR		+ offset;
	volatile uint32* DMA_M0AR	= MCU::DMA_2::CH0_M0AR	+ offset;
	volatile uint32* DMA_M1AR	= MCU::DMA_2::CH0_M1AR	+ offset;
	
	
	//	Reset Registers
	*DMA_CCR = 0;
	*DMA_NDTR = 0;
	*DMA_PAR = 0;
	*DMA_M0AR = 0;
	*DMA_M1AR = 0;
	
	constexpr uint8 isrRegisterOffset[4] = {0, 6, 16, 22};
	const uint32 mask = 0x3D << isrRegisterOffset[m_channel % 4];
	if(m_channel < 4)
	{
		*MCU::DMA_2::LIFCR = mask;
	}
	else
	{
		*MCU::DMA_2::HIFCR = mask;
	}
	
	
	return(OK);
}


CODE_RAM feedback DMA_2::transfer(const void* source, const void* destination, e_dataType sourceType, e_dataType destinationType, bool source_inc, bool dest_inc, e_direction direction, bool circularMode, uint16 numberOfItems, e_priority priority, bool waitForTransferEnd, f_callback callback)
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
	const uint32 offset = m_channel * 0x6;
	
	volatile uint32* DMA_CCR	= MCU::DMA_2::CH0_CR		+ offset;
	volatile uint32* DMA_NDTR	= MCU::DMA_2::CH0_NDTR	+ offset;
	volatile uint32* DMA_PAR	= MCU::DMA_2::CH0_PAR		+ offset;
	volatile uint32* DMA_MAR	= MCU::DMA_2::CH0_M0AR	+ offset;
	
	
	//	Channel already used
	if(bit::isSet(*DMA_CCR, 0) == true)
	{
		return(FAIL);
	}
	
	
	//	Set Callback Function
	auto& channelInfo(m_channelInfo[m_channel]);
	channelInfo.second() = callback;
	channelInfo.third() = circularMode;
	
	
	//	Clear Interrupt Flags
	uint32 temp = (m_channel & 0x3) * 8;
	if(m_channel < 4)
	{
		*MCU::DMA_2::LIFCR = *MCU::DMA_2::LISR & (0x0000003D << temp);
	}
	else
	{
		*MCU::DMA_2::HIFCR = *MCU::DMA_2::HISR & (0x0000003D << temp);
	}
	
	
	
	
	
	//	Write to local Values and transfer at the End to DMA Register
	uint32 CCR	= 0;
	uint32 NDTR	= numberOfItems;
	uint32 PAR	= 0;
	uint32 MAR	= 0;
	
	
	//	Enable Transfer Complete Interrupt
	bit::set(CCR, 4);
	
	
	//	Enable Transfer Error Interrupt
	bit::set(CCR, 2);
	
	
	//	Priority
	CCR |= ((uint32) priority) << 16;
	
	
	//	Circular Mode
	if(circularMode == true)
	{
		bit::set(CCR, 8);
	}
	
	
	//	Direction
	CCR |= ((uint32) direction) << 6;
	
	
	//	Set Memory Pointers and Increments (MEMORY_TO_MEMORY is essentially the same as PERIPERHAL_TO_MEMORY, so we change direction to save Code Space)
	if(direction == e_direction::MEMORY_TO_MEMORY)
	{
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
			CCR |= ((uint32) sourceType) << 11;
			CCR |= ((uint32) destinationType) << 13;
			
			
			//	Increments
			if(source_inc == true)
			{
				bit::set(CCR, 9);
			}
			if(dest_inc == true)
			{
				bit::set(CCR, 10);
			}
		}
		break;
		
		case e_direction::MEMORY_TO_PERIPHERAL:
		{
			//	Memory Pointers
			PAR = (uint32) destination;
			MAR = (uint32) source;
			
			
			//	Data Types
			CCR |= ((uint32) destinationType) << 11;
			CCR |= ((uint32) sourceType) << 13;
			
			
			//	Increments
			if(source_inc == true)
			{
				bit::set(CCR, 10);
			}
			if(dest_inc == true)
			{
				bit::set(CCR, 9);
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









CODE_RAM void ISR_DMA_2_CH0()
{
	constexpr uint8 channel = 0;
	constexpr uint32 mask = 0x0000003D;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_2::LISR;
	*MCU::DMA_2::LIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA_2_CH1()
{
	constexpr uint8 channel = 1;
	constexpr uint32 mask = 0x00000F40;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_2::LISR;
	*MCU::DMA_2::LIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA_2_CH2()
{
	constexpr uint8 channel = 2;
	constexpr uint32 mask = 0x003D0000;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_2::LISR;
	*MCU::DMA_2::LIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA_2_CH3()
{
	constexpr uint8 channel = 0;
	constexpr uint32 mask = 0x0F400000;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_2::LISR;
	*MCU::DMA_2::LIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA_2_CH4()
{
	constexpr uint8 channel = 4;
	constexpr uint32 mask = 0x0000003D;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_2::HISR;
	*MCU::DMA_2::HIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA_2_CH5()
{
	constexpr uint8 channel = 5;
	constexpr uint32 mask = 0x00000F40;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_2::HISR;
	*MCU::DMA_2::HIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA_2_CH6()
{
	constexpr uint8 channel = 6;
	constexpr uint32 mask = 0x003D0000;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_2::HISR;
	*MCU::DMA_2::HIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}


CODE_RAM void ISR_DMA_2_CH7()
{
	constexpr uint8 channel = 7;
	constexpr uint32 mask = 0x0F400000;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_2::HISR;
	*MCU::DMA_2::HIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_2::executeCallback(channel);
	}
}