#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback UART_5::init(uint32 baud, e_databits databits, e_stopbits stopbits, e_parity parity, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize)
{
	//	Check if Semaphore is locked
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Lock Semaphore of Tx DMA
	STM32H753BIT6& stm32 = STM32H753BIT6::get();
	m_dma_tx = &stm32.get_dma_1(4);
	if(cmos.semaphore_lock(m_dma_tx) != OK)
	{
		return(FAIL);
	}
	
	
	//	Lock Semaphore of Rx DMA
	m_dma_rx = &stm32.get_dma_1(3);
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
	
	
	//	Reset UART
	RCC& rcc = stm32.get_rcc();
	rcc.module_reset(RCC::e_module::UART_5);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::UART_5, true);
	rcc.set_clockSource(RCC::e_clockSource_uart::BUS_CLOCK, 5);
	uint32 clock_in = rcc.get_clock_apb1();
	
	
	//	Databits
	switch(databits)
	{
		case e_databits::_7:
		{
			bit::clear(*MCU::UART_5::CR1, 12);
			bit::set(*MCU::UART_5::CR1, 28);
		}
		break;
		
		case e_databits::_8:
		{
			bit::clear(*MCU::UART_5::CR1, 12);
			bit::clear(*MCU::UART_5::CR1, 28);
		}
		break;
		
		case e_databits::_9:
		{
			bit::set(*MCU::UART_5::CR1, 12);
			bit::clear(*MCU::UART_5::CR1, 28);
		}
		break;
			
		default:
		{
			return(FAIL);
		}
	}
	
	
	//	Oversampling 16
	bit::clear(*MCU::UART_5::CR1, 15);
	
	
	//	Baud Rate
	*MCU::UART_5::BRR = clock_in / baud;
	
	
	//	Stop Bits
	uint32 temp = *MCU::UART_5::CR2 & 0xFFFFCFFF;
	*MCU::UART_5::CR2 = temp | (((uint32) stopbits) << 12);
	
	
	//	Parity
	temp = *MCU::UART_5::CR1 & 0xFFFFF9FF;
	*MCU::UART_5::CR1 = temp | (((uint32) parity) << 9);
	
	
	//	Enable IDLE Line Interrupt
	bit::set(*MCU::UART_5::CR1, 4);
	
	
	//	Enable RX DMA Mode
	bit::set(*MCU::UART_5::CR3, 6);
	
	
	//	Enable TX DMA Mode
	bit::set(*MCU::UART_5::CR3, 7);
	
	
	//	DMA Multiplexing
	DMAMUX& dmamux = stm32.get_dmamux();
	dmamux.map(DMAMUX::e_input::UART_5_RX_DMA, DMAMUX::e_output::DMA_1_CH3);
	dmamux.map(DMAMUX::e_input::UART_5_TX_DMA, DMAMUX::e_output::DMA_1_CH4);
	
	
	//	Rx DMA Setup
	if(m_dma_rx->transfer((void*) MCU::UART_5::RDR, m_data, I_DMA::e_dataType::UINT8, I_DMA::e_dataType::UINT8, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, m_size, I_DMA::e_priority::VERY_HIGH, false) != OK)
	{
		return(FAIL);
	}
	
	
	//	Subscribe to USART Rx Message Receive Event so that we get waken up by the ISR when Data is received
	cmos.event_subscribe(m_eventID_dataReceived);
	
	
	//	Interrupt
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::UART_5, 10);
	nvic.enable(Interrupt::UART_5);
	
	
	//	UART Enable
	bit::set(*MCU::UART_5::CR1, 0);
	
	
	//	TX Enable
	bit::set(*MCU::UART_5::CR1, 3);
	
	
	//	RX Enable
	bit::set(*MCU::UART_5::CR1, 2);
	
	
	//	Set Flag to enable other Functions
	m_initialized = true;
	return(OK);
}


feedback UART_5::deinit()
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
	if(nvic.disable(Interrupt::UART_5) != OK)
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
	STM32H753BIT6& stm32 = STM32H753BIT6::get();
	RCC& rcc = stm32.get_rcc();
	if(rcc.module_reset(RCC::e_module::UART_5) != OK)
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









CODE_RAM void ISR_UART_5()
{
	UART_5& uart = STM32H753BIT6::get().get_uart_5();
	
	
	//  IDLE Line detected
	if(bit::isSet(*MCU::UART_5::ISR, 4))
	{
		//	Clear Interrupt Flag
		bit::set(*MCU::UART_5::ICR, 4);
		
		
		//	Update Head
		uart.m_head = uart.m_size - *MCU::DMA_1::CH3_NDTR;
		
		
		//	Notify Threads about received Data
		CMOS& cmos = CMOS::get();
		cmos.event_emit(uart.m_eventID_dataReceived);
	}
	
	
	//	Rx Buffer Overrun
	if(bit::isSet(*MCU::UART_5::ISR, 3))
	{
		//	Clear Interrupt Flag
		bit::set(*MCU::UART_5::ICR, 3);
		
		
		//	Reset Rx Buffer
		uart.clear();
	}
}