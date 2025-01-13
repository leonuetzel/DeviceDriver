#include "../Inc/stm32l010rbt6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback LP_UART_1::init(uint32 baud, e_databits databits, e_parity parity, e_stopbits stopbits, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize)
{
	//	Check if Semaphore is locked
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Lock Semaphore of Tx DMA
	STM32L010RBT6& stm32 = STM32L010RBT6::get();
	{
		DMA& dma_tx = stm32.get_dma(6);
		m_dma_tx = &dma_tx;
		dma_tx.set_requestMapping(DMA::e_requestMapping::CH6_LPUART1TX);
	}
	if(cmos.semaphore_lock(m_dma_tx) != OK)
	{
		return(FAIL);
	}
	
	
	//	Lock Semaphore of Rx DMA
	{
		DMA& dma_rx = stm32.get_dma(5);
		m_dma_rx = &dma_rx;
		dma_rx.set_requestMapping(DMA::e_requestMapping::CH5_LPUART1RX);
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
	
	
	//	Reset LPUART
	RCC& rcc = stm32.get_rcc();
	rcc.module_reset(RCC::e_module::LP_UART_1);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::LP_UART_1, true);
	rcc.set_clockSource(RCC::e_clockSource_lpuart_1::SYSTEM_CLOCK);
	
	
	//	Databits
	switch(databits)
	{
		case e_databits::_7:
		{
			bit::clear(*MCU::LP_UART_1::CR1, 12);
			bit::set(*MCU::LP_UART_1::CR1, 28);
		}
		break;
		
		case e_databits::_8:
		{
			bit::clear(*MCU::LP_UART_1::CR1, 12);
			bit::clear(*MCU::LP_UART_1::CR1, 28);
		}
		break;
		
		case e_databits::_9:
		{
			bit::set(*MCU::LP_UART_1::CR1, 12);
			bit::clear(*MCU::LP_UART_1::CR1, 28);
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	
	//	Baud Rate
	//	Ratio Input Clock to Baudrate must be in the Range 3...4096
	//	Chapter 22.7.4 in RM 0451 Rev. 3)
	uint32 clock_ratio = rcc.get_clock_system() / baud;
	if(clock_ratio < 3 || clock_ratio > 4096)
	{
		return(FAIL);
	}
	*MCU::LP_UART_1::BRR = 256 * clock_ratio;
	
	
	//	Stop Bits
	uint32 temp = *MCU::LP_UART_1::CR2 & 0xFFFFCFFF;
	*MCU::LP_UART_1::CR2 = temp | (((uint32) stopbits) << 12);
	
	
	//	Parity
	temp = *MCU::LP_UART_1::CR1 & 0xFFFFF9FF;
	*MCU::LP_UART_1::CR1 = temp | (((uint32) parity) << 9);
	
	
	//	Enable IDLE Line Interrupt
	bit::set(*MCU::LP_UART_1::CR1, 4);
	
	
	//	Enable RX DMA Mode
	bit::set(*MCU::LP_UART_1::CR3, 6);
	
	
	//	Enable TX DMA Mode
	bit::set(*MCU::LP_UART_1::CR3, 7);
	
	
	//	Rx DMA Setup
	if(m_dma_rx->transfer((void*) MCU::LP_UART_1::RDR, m_data, I_DMA::e_dataType::UINT8, I_DMA::e_dataType::UINT8, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, m_size, I_DMA::e_priority::VERY_HIGH, false) != OK)
	{
		return(FAIL);
	}
	
	
	//	Subscribe to USART Rx Message Receive Event so that we get waken up by the ISR when Data is received
	cmos.event_subscribe(m_eventID_dataReceived);
	
	
	//	Interrupt
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::LP_UART_1, 10);
	nvic.enable(Interrupt::LP_UART_1);
	
	
	//	LPUART 1 Enable
	bit::set(*MCU::LP_UART_1::CR1, 0);
	
	
	//	TX Enable
	bit::set(*MCU::LP_UART_1::CR1, 3);
	
	
	//	RX Enable
	bit::set(*MCU::LP_UART_1::CR1, 2);
	
	
	//	Set Flag to enable other Functions
	m_initialized = true;
	return(OK);
}


feedback LP_UART_1::deinit()
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
	if(nvic.disable(Interrupt::LP_UART_1) != OK)
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
	STM32L010RBT6& stm32 = STM32L010RBT6::get();
	RCC& rcc = stm32.get_rcc();
	if(rcc.module_reset(RCC::e_module::LP_UART_1) != OK)
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









void ISR_LPUART_1()
{
	LP_UART_1& uart = STM32L010RBT6::get().get_lpuart_1();
	
	
	//  IDLE Line detected
	if(bit::isSet(*MCU::LP_UART_1::ISR, 4))
	{
		//	Clear Interrupt Flag
		bit::set(*MCU::LP_UART_1::ICR, 4);
		
		
		//	Update Head
		uart.m_head = uart.m_size - *MCU::DMA::CH5_NDTR;
		
		
		//	Notify Threads about received Data
		CMOS& cmos = CMOS::get();
		cmos.event_emit(uart.m_eventID_dataReceived);
	}
	
	
	//	Rx Buffer Overrun
	if(bit::isSet(*MCU::LP_UART_1::ISR, 3))
	{
		//	Clear Interrupt Flag
		bit::set(*MCU::LP_UART_1::ICR, 3);
		
		
		//	Reset Rx Buffer
		uart.clear();
	}
}