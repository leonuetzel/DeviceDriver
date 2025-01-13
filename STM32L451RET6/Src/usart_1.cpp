#include "../Inc/stm32l451ret6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback USART_1::init(uint32 baud, e_databits databits, e_parity parity, e_stopbits stopbits, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize)
{
	//	Check if Semaphore is locked
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Lock Semaphore of Tx DMA
	STM32L451RET6& stm32 = STM32L451RET6::get();
	{
		DMA_1& dma_tx = stm32.get_dma_1(3);
		m_dma_tx = &dma_tx;
		dma_tx.set_requestMapping(DMA_1::e_requestMapping::CH3_USART1TX);
	}
	if(cmos.semaphore_lock(m_dma_tx) != OK)
	{
		return(FAIL);
	}
	
	
	//	Lock Semaphore of Rx DMA
	{
		DMA_1& dma_rx = stm32.get_dma_1(4);
		m_dma_rx = &dma_rx;
		dma_rx.set_requestMapping(DMA_1::e_requestMapping::CH4_USART1RX);
	}
	if(cmos.semaphore_lock(m_dma_rx) != OK)
	{
		return(FAIL);
	}
	
	
	//	Rx and Tx Buffer
	if(rxBufferSize <= 0 || rxBuffer == nullptr || txBufferSize <= 0 || txBuffer == nullptr)
	{
		return(FAIL);
	}
	m_data = rxBuffer;
	m_size = rxBufferSize;
	clear();
	m_txBuffer = RingbufferExternal<uint8>(txBuffer, txBufferSize);
	
	
	//	Reset USART
	RCC& rcc = stm32.get_rcc();
	rcc.module_reset(RCC::e_module::USART_1);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::USART_1, true);
	const uint32 clock_in = rcc.get_clock_usart_1();
	
	
	//	Databits
	switch(databits)
	{
		case e_databits::_7:
		{
			bit::clear(*MCU::USART_1::CR1, 12);
			bit::set(*MCU::USART_1::CR1, 28);
		}
		break;
		
		case e_databits::_8:
		{
			bit::clear(*MCU::USART_1::CR1, 12);
			bit::clear(*MCU::USART_1::CR1, 28);
		}
		break;
		
		case e_databits::_9:
		{
			bit::set(*MCU::USART_1::CR1, 12);
			bit::clear(*MCU::USART_1::CR1, 28);
		}
		break;
		
		default:
		{
			return(FAIL);
		}
		break;
	}
	
	
	//	Baudrate
	*MCU::USART_1::BRR = clock_in / baud;
	
	
	//	Stop Bits
	uint32 temp = *MCU::USART_1::CR2 & 0xFFFFCFFF;
	*MCU::USART_1::CR2 = temp | (((uint32) stopbits) << 12);
	
	
	//	Parity
	temp = *MCU::USART_1::CR1 & 0xFFFFF9FF;
	*MCU::USART_1::CR1 = temp | (((uint32) parity) << 9);
	
	
	//	Enable IDLE Line Interrupt
	bit::set(*MCU::USART_1::CR1, 4);
	
	
	//	Enable RX DMA Mode
	bit::set(*MCU::USART_1::CR3, 6);
	
	
	//	Enable TX DMA Mode
	bit::set(*MCU::USART_1::CR3, 7);
	
	
	//	Rx DMA Setup
	if(m_dma_rx->transfer((void*) MCU::USART_1::RDR, m_data, I_DMA::e_dataType::UINT8, I_DMA::e_dataType::UINT8, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, m_size, I_DMA::e_priority::VERY_HIGH, false) != OK)
	{
		return(FAIL);
	}
	
	
	//	Subscribe to USART Rx Message Receive Event so that we get waken up by the ISR when Data is received
	cmos.event_subscribe(m_eventID_dataReceived);
	
	
	//	Interrupt
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::USART_1, 2);
	nvic.enable(Interrupt::USART_1);
	
	
	//	USART Enable
	bit::set(*MCU::USART_1::CR1, 0);
	
	
	//	TX Enable
	bit::set(*MCU::USART_1::CR1, 3);
	
	
	//	RX Enable
	bit::set(*MCU::USART_1::CR1, 2);
	
	
	//	Set Flag to enable other Functions
	m_initialized = true;
	return(OK);
}


feedback USART_1::deinit()
{
	//	Check if all related Semaphores are owned by running Thread
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	if(cmos.semaphore_isOwnedByRunningThread(m_dma_tx) == false)
	{
		return(FAIL);
	}
	if(cmos.semaphore_isOwnedByRunningThread(m_dma_rx) == false)
	{
		return(FAIL);
	}
	
	
	//	Disable Interrupt
	NVIC& nvic = cmos.get_nvic();
	if(nvic.disable(Interrupt::USART_1) != OK)
	{
		return(FAIL);
	}
	
	
	//	Reset DMA Rx Channel
	if(m_dma_rx->reset() != OK)
	{
		return(FAIL);
	}
	
	
	//	Reset DMA Tx Channel
	if(m_dma_tx->reset() != OK)
	{
		return(FAIL);
	}
	
	
	//	Reset Rx Buffer
	reset();
	
	
	//	Reset Tx Buffer
	m_txBuffer.reset();
	
	
	//	Reset USART
	STM32L451RET6& stm32 = STM32L451RET6::get();
	RCC& rcc = stm32.get_rcc();
	if(rcc.module_reset(RCC::e_module::USART_1) != OK)
	{
		return(FAIL);
	}
	
	
	//	Free Semaphores
	if(cmos.semaphore_unlock(m_dma_rx) != OK)
	{
		return(FAIL);
	}
	if(cmos.semaphore_unlock(m_dma_tx) != OK)
	{
		return(FAIL);
	}
	if(cmos.semaphore_unlock(this) != OK)
	{
		return(FAIL);
	}
	
	
	//	Reset Flag
	m_initialized = false;
	
	
	return(OK);
}









void ISR_USART_1()
{
	USART_1& usart = STM32L451RET6::get().get_usart_1();
	
	
	//  IDLE Line detected
	if(bit::isSet(*MCU::USART_1::ISR, 4))
	{
		//	Clear Interrupt Flag
		*MCU::USART_1::ICR = 1 << 4;
		
		
		//	Update Head
		usart.m_head = usart.m_size - *MCU::DMA_1::CH4_NDTR;
		
		
		//	Notify Threads about received Data
		CMOS& cmos = CMOS::get();
		cmos.event_emit(usart.m_eventID_dataReceived);
	}
	
	
	//	Rx Buffer Overrun
	if(bit::isSet(*MCU::USART_1::ISR, 3))
	{
		//	Clear Interrupt Flag
		*MCU::USART_1::ICR = 1 << 3;
		
		
		//	Reset Rx Buffer
		usart.clear();
	}
}