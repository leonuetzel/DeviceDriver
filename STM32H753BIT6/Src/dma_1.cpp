#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

//	First: Event ID
//	Second: Callback Function
//	Third: IsCircular Mode Transfer - dont set callback to nullptr after Transfer if true
Triplet<uint16, I_DMA::f_callback, bool> DMA_1::m_channelInfo[c_channel] =
{
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false),
	Triplet<uint16, I_DMA::f_callback, bool>(CMOS::eventID_invalid, nullptr, false)
};


//	Memory written by the Channel: Address and Size in Bytes, for the Cache Maintenance at the End of a Transfer
Pair<const void*, uint32> DMA_1::m_writtenMemory[c_channel];

volatile bool DMA_1::m_transferError[c_channel] = {};

bool DMA_1::m_usartWorkaround = false;



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback DMA_1::startup(uint8 channel)
{
	//	Check Channel Boundaries
	if(m_channel != c_channel || channel >= c_channel)
	{
		return(FAIL);
	}
	
	m_channel = channel;
	
	
	//	Create Mutex
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_create(this) != OK)
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
		nvic.setPriority(Interrupt::DMA_1_CH0, 10);
		nvic.setPriority(Interrupt::DMA_1_CH1, 10);
		nvic.setPriority(Interrupt::DMA_1_CH2, 10);
		nvic.setPriority(Interrupt::DMA_1_CH3, 10);
		nvic.setPriority(Interrupt::DMA_1_CH4, 10);
		nvic.setPriority(Interrupt::DMA_1_CH5, 10);
		nvic.setPriority(Interrupt::DMA_1_CH6, 10);
		nvic.setPriority(Interrupt::DMA_1_CH7, 10);
		
		nvic.enable(Interrupt::DMA_1_CH0);
		nvic.enable(Interrupt::DMA_1_CH1);
		nvic.enable(Interrupt::DMA_1_CH2);
		nvic.enable(Interrupt::DMA_1_CH3);
		nvic.enable(Interrupt::DMA_1_CH4);
		nvic.enable(Interrupt::DMA_1_CH5);
		nvic.enable(Interrupt::DMA_1_CH6);
		nvic.enable(Interrupt::DMA_1_CH7);
		
		
		RCC& rcc = STM32H753BIT6::get().get_rcc();
		rcc.module_clockInit(RCC::e_module::DMA_1, true);
		
		
		//	ES0392 2.20.4 (Revisions X and V, not Y = 0x1003), see transfer()
		const uint32 revisionID = (*MCU::DBGMCU::IDC >> 16) & 0x0000FFFF;
		m_usartWorkaround = (revisionID != 0x1003);
	}
	return(OK);
}


CODE_RAM void DMA_1::executeCallback(uint8 channel, bool transferError)
{
	//	A Transfer Error disables the Stream by Hardware, transfer() returns FAIL then
	m_transferError[channel] = transferError;
	
	
	//	Get Channel Registers
	const uint32 offset = channel * 0x6;
	volatile uint32* DMA_CCR = MCU::DMA_1::CH0_CR + offset;
	
	
	//	Reset EN Bit in DMA_CHx_CCR only if Mode is non-circular, else new DMA Requests wont be served
	if(bit::isCleared(*DMA_CCR, 8) == true)
	{
		bit::clear(*DMA_CCR, 0);
	}
	
	
	//	Cache Maintenance: the CPU reads the Memory written by the Channel only after this, in Circular Mode after every Round
	//	A finished non-circular Transfer is forgotten, the CPU may write the Memory afterwards
	auto& writtenMemory(m_writtenMemory[channel]);
	CacheMaintenance::afterWrite(writtenMemory.first(), writtenMemory.second());
	if(bit::isCleared(*DMA_CCR, 8) == true)
	{
		writtenMemory.second() = 0;
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

feedback DMA_1::reset()
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
	const uint32 offset = m_channel * 0x6;
	
	volatile uint32* DMA_CCR	= MCU::DMA_1::CH0_CR		+ offset;
	volatile uint32* DMA_NDTR	= MCU::DMA_1::CH0_NDTR	+ offset;
	volatile uint32* DMA_PAR	= MCU::DMA_1::CH0_PAR		+ offset;
	volatile uint32* DMA_M0AR	= MCU::DMA_1::CH0_M0AR	+ offset;
	volatile uint32* DMA_M1AR	= MCU::DMA_1::CH0_M1AR	+ offset;
	
	
	//	Disable the Channel: it finishes the current Data Item first, its other Registers can only be written afterwards (RM0433, 15.3.19)
	//	The Wait is limited (some Milliseconds): a Stream that does not stop, e.g. locked as described in ES0392 2.20.4, must not block the Caller forever
	const bool active = bit::isSet(*DMA_CCR, 0);
	*DMA_CCR = 0;
	uint32 timeout = 100000;
	while(bit::isSet(*DMA_CCR, 0) == true)
	{
		timeout--;
		if(timeout == 0)
		{
			return(FAIL);
		}
	}
	
	
	//	Cache Maintenance: the CPU may read what an aborted Transfer has written so far
	auto& writtenMemory(m_writtenMemory[m_channel]);
	if(active == true)
	{
		CacheMaintenance::afterWrite(writtenMemory.first(), writtenMemory.second());
	}
	writtenMemory.second() = 0;
	
	
	//	Reset Registers
	*DMA_NDTR = 0;
	*DMA_PAR = 0;
	*DMA_M0AR = 0;
	*DMA_M1AR = 0;
	
	constexpr uint8 isrRegisterOffset[4] = {0, 6, 16, 22};
	const uint32 mask = 0x3D << isrRegisterOffset[m_channel % 4];
	if(m_channel < 4)
	{
		*MCU::DMA_1::LIFCR = mask;
	}
	else
	{
		*MCU::DMA_1::HIFCR = mask;
	}
	
	
	return(OK);
}


bool DMA_1::is_busy() const
{
	//	The Stream stays enabled until a single Transfer has ended or a Transfer Error has stopped it: the Hardware clears EN, the Interrupt
	//	Routine follows at once (RM0433, DMA_SxCR). A circular Transfer runs until reset(). transfer() refuses the Stream as long as it is busy
	if(m_channel >= c_channel)
	{
		return(false);
	}
	const uint32 offset = m_channel * 0x6;
	return(bit::isSet(*(MCU::DMA_1::CH0_CR + offset), 0));
}


uint16 DMA_1::get_eventID() const
{
	//	executeCallback() emits it at the End of every non-circular Transfer, also without a waiting Thread, and after a Transfer Error:
	//	transfer() always enables the Transfer Complete and the Transfer Error Interrupt of a non-circular Transfer
	if(m_channel >= c_channel)
	{
		return(CMOS::eventID_invalid);
	}
	return(m_channelInfo[m_channel].first());
}


feedback DMA_1::transfer(const void* source, const void* destination, e_dataType sourceType, e_dataType destinationType, bool source_inc, bool dest_inc, e_direction direction, bool circularMode, uint16 numberOfItems, e_priority priority, bool waitForTransferEnd, f_callback callback)
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
	
	
	//	The DMA does not reach the TCM of the Core: Buffers in the DTCM (Variables and Stacks of the Linker Script Template) or ITCM
	//	are refused, the Transfer would else end with a Transfer Error. The Memory Side is the Source, the Destination or both
	const uint32 sizeInBytes_source = (source_inc == true) ? ((uint32) numberOfItems << (uint32) sourceType) : (1 << (uint32) sourceType);
	const uint32 sizeInBytes_destination = (dest_inc == true) ? ((uint32) numberOfItems << (uint32) destinationType) : (1 << (uint32) destinationType);
	if(direction != e_direction::PERIPHERAL_TO_MEMORY && CacheMaintenance::isReachableByDMA(source, sizeInBytes_source) == false)
	{
		return(FAIL);
	}
	if(direction != e_direction::MEMORY_TO_PERIPHERAL && CacheMaintenance::isReachableByDMA(destination, sizeInBytes_destination) == false)
	{
		return(FAIL);
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
	const uint32 offset = m_channel * 0x6;
	
	volatile uint32* DMA_CCR	= MCU::DMA_1::CH0_CR		+ offset;
	volatile uint32* DMA_NDTR	= MCU::DMA_1::CH0_NDTR	+ offset;
	volatile uint32* DMA_PAR	= MCU::DMA_1::CH0_PAR		+ offset;
	volatile uint32* DMA_MAR	= MCU::DMA_1::CH0_M0AR	+ offset;
	
	
	//	Channel already used
	if(bit::isSet(*DMA_CCR, 0) == true)
	{
		return(FAIL);
	}
	
	
	//	Set Callback Function
	auto& channelInfo(m_channelInfo[m_channel]);
	channelInfo.second() = callback;
	channelInfo.third() = circularMode;
	
	
	//	Clear Interrupt Flags: the Flags of the Streams 0 ... 3 (4 ... 7) start at Bit 0, 6, 16 and 22 (RM0433, DMA_LISR/HISR)
	constexpr uint8 isrRegisterOffset[4] = {0, 6, 16, 22};
	const uint32 flagMask = 0x0000003D << isrRegisterOffset[m_channel % 4];
	if(m_channel < 4)
	{
		*MCU::DMA_1::LIFCR = flagMask;
	}
	else
	{
		*MCU::DMA_1::HIFCR = flagMask;
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
	
	
	//	Memory read and written by the Channel, for the Cache Maintenance
	//	The Channel transfers numberOfItems Items of the Peripheral Data Size: in Direct Mode the Memory Data Size is forced to it, in MEMORY_TO_MEMORY the FIFO packs them
	//	A Memory Pointer that is not incremented accesses one Item only
	const bool memoryToMemory = direction == e_direction::MEMORY_TO_MEMORY;
	const uint32 itemSize_max = 1u << ((uint32) (sourceType > destinationType ? sourceType : destinationType));
	const void* readMemory = nullptr;
	uint32 readMemory_sizeInBytes = 0;
	const void* writtenMemory = nullptr;
	uint32 writtenMemory_sizeInBytes = 0;
	
	
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
			
			
			//	Memory for the Cache Maintenance
			writtenMemory = destination;
			writtenMemory_sizeInBytes = dest_inc == true ? numberOfItems * (1u << (uint32) sourceType) : itemSize_max;
			if(memoryToMemory == true)
			{
				readMemory = source;
				readMemory_sizeInBytes = source_inc == true ? numberOfItems * (1u << (uint32) sourceType) : itemSize_max;
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
			
			
			//	Memory for the Cache Maintenance
			readMemory = source;
			readMemory_sizeInBytes = source_inc == true ? numberOfItems * (1u << (uint32) destinationType) : itemSize_max;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	
	//	Cache Maintenance and Barrier before the Channel is enabled (see cacheMaintenance.hpp)
	//	The Interrupt Routine invalidates the written Memory when the Transfer has ended
	auto& writtenMemoryInfo(m_writtenMemory[m_channel]);
	writtenMemoryInfo.first() = writtenMemory;
	writtenMemoryInfo.second() = writtenMemory_sizeInBytes;
	CacheMaintenance::beforeRead(readMemory, readMemory_sizeInBytes);
	CacheMaintenance::beforeWrite(writtenMemory, writtenMemory_sizeInBytes);
	
	
	//	ES0392 2.20.4 (Revisions X and V): a Stream serving a USART can stay locked, if another Transfer runs at the same Time
	//	Workaround: the alternative Peripheral Protocol with Bit 20 of DMA_SxCR (reserved in RM0433), only for USART/UART Requests
	if(m_usartWorkaround == true)
	{
		const uint32 request = *(MCU::DMAMUX_1::CH0_CR + m_channel) & 0x000000FF;
		const bool requestFromUSART = (request >= 41 && request <= 46) || (request >= 63 && request <= 66) || request == 71 || request == 72 || (request >= 79 && request <= 82);
		if(requestFromUSART == true)
		{
			bit::set(CCR, 20);
		}
	}
	
	
	//	Enable Transfer Complete Interrupt: it ends the Transfer, wakes the waiting Thread, calls the Callback and invalidates the written Memory
	//	A circular Transfer without Callback and without waiting needs none for Memory that is not cacheable (an MPU Region without Cache), else it would come
	//	after every Round with nothing to do. The Attributes of the MPU decide, not the State of the Data Cache: it may be switched on later
	if(circularMode == false || waitForTransferEnd == true || callback != nullptr ||
		 (writtenMemory_sizeInBytes > 0 && Cache::isCacheable(writtenMemory, writtenMemory_sizeInBytes) == true))
	{
		bit::set(CCR, 4);
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









CODE_RAM void ISR_DMA_1_CH0()
{
	constexpr uint8 channel = 0;
	constexpr uint32 mask = 0x0000003D;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_1::LISR;
	*MCU::DMA_1::LIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_1::executeCallback(channel, (ISR & mask & DMA_1::c_transferErrorFlags) != 0);
	}
}


CODE_RAM void ISR_DMA_1_CH1()
{
	constexpr uint8 channel = 1;
	constexpr uint32 mask = 0x00000F40;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_1::LISR;
	*MCU::DMA_1::LIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_1::executeCallback(channel, (ISR & mask & DMA_1::c_transferErrorFlags) != 0);
	}
}


CODE_RAM void ISR_DMA_1_CH2()
{
	constexpr uint8 channel = 2;
	constexpr uint32 mask = 0x003D0000;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_1::LISR;
	*MCU::DMA_1::LIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_1::executeCallback(channel, (ISR & mask & DMA_1::c_transferErrorFlags) != 0);
	}
}


CODE_RAM void ISR_DMA_1_CH3()
{
	constexpr uint8 channel = 3;
	constexpr uint32 mask = 0x0F400000;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_1::LISR;
	*MCU::DMA_1::LIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_1::executeCallback(channel, (ISR & mask & DMA_1::c_transferErrorFlags) != 0);
	}
}


CODE_RAM void ISR_DMA_1_CH4()
{
	constexpr uint8 channel = 4;
	constexpr uint32 mask = 0x0000003D;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_1::HISR;
	*MCU::DMA_1::HIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_1::executeCallback(channel, (ISR & mask & DMA_1::c_transferErrorFlags) != 0);
	}
}


CODE_RAM void ISR_DMA_1_CH5()
{
	constexpr uint8 channel = 5;
	constexpr uint32 mask = 0x00000F40;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_1::HISR;
	*MCU::DMA_1::HIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_1::executeCallback(channel, (ISR & mask & DMA_1::c_transferErrorFlags) != 0);
	}
}


CODE_RAM void ISR_DMA_1_CH6()
{
	constexpr uint8 channel = 6;
	constexpr uint32 mask = 0x003D0000;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_1::HISR;
	*MCU::DMA_1::HIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_1::executeCallback(channel, (ISR & mask & DMA_1::c_transferErrorFlags) != 0);
	}
}


CODE_RAM void ISR_DMA_1_CH7()
{
	constexpr uint8 channel = 7;
	constexpr uint32 mask = 0x0F400000;
	
	
	//	Save Copy of ISR Register and clear Interrupt Flags
	const uint32 ISR = *MCU::DMA_1::HISR;
	*MCU::DMA_1::HIFCR = mask;
	
	
	//	Check Channel
	if((ISR & mask) != 0)
	{
		DMA_1::executeCallback(channel, (ISR & mask & DMA_1::c_transferErrorFlags) != 0);
	}
}