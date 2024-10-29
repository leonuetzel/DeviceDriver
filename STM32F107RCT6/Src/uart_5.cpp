#include "../Inc/stm32f107rct6.hpp"





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
	
	
	//	Check for valid Number of Databits
	if(databits == e_databits::_7)
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
	STM32F107RCT6& stm32 = STM32F107RCT6::get();
	RCC& rcc = stm32.get_rcc();
	rcc.module_reset(RCC::e_module::UART_5);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::UART_5, true);
	uint32 clock_in = rcc.get_clock_apb1();
	
	
	//	Databits
	if(databits == e_databits::_8)
	{
		bit::clear(*MCU::UART_5::CR1, 12);
	}
	else
	{
		bit::set(*MCU::UART_5::CR1, 12);
	}
	
	
	//	Baudrate
	*MCU::UART_5::BRR = clock_in / baud;
	
	
	//	Stop Bits
	uint32 temp = *MCU::UART_5::CR2 & 0xFFFFCFFF;
	*MCU::UART_5::CR2 = temp | (((uint32) stopbits) << 12);
	
	
	//	Parity
	temp = *MCU::UART_5::CR1 & 0xFFFFF9FF;
	*MCU::UART_5::CR1 = temp | (((uint32) parity) << 9);
	
	
	//	Enable IDLE Line Interrupt
	bit::set(*MCU::UART_5::CR1, 4);
	
	
	//	Enable RX FIFO not emtpy Interrupt
	bit::set(*MCU::UART_5::CR1, 5);
	
	
	//	Interrupt
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::UART_5, 10);
	nvic.enable(Interrupt::UART_5);
	
	
	//	UART Enable
	bit::set(*MCU::UART_5::CR1, 13);
	
	
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
	
	
	//	Disable Interrupt
	NVIC& nvic = cmos.get_nvic();
	if(nvic.disable(Interrupt::UART_5) != OK)
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
	STM32F107RCT6& stm32 = STM32F107RCT6::get();
	RCC& rcc = stm32.get_rcc();
	if(rcc.module_reset(RCC::e_module::UART_5) != OK)
	{
		return(FAIL);
	}
	
	
	//	Free Semaphores
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









void ISR_UART_5()
{
	UART_5& uart = STM32F107RCT6::get().get_uart_5();
	
	
	//	Data received
	if(bit::isSet(*MCU::UART_5::SR, 5))
	{
		uart.write(*MCU::UART_5::DR);
	}
	
	
	//  IDLE Line detected
	if(bit::isSet(*MCU::UART_5::SR, 4))
	{
		//	Clear IDLE Line Flag
		*MCU::UART_5::DR;
		
		
		//	Notify Threads about received Data
		CMOS& cmos = CMOS::get();
		cmos.event_emit(uart.m_eventID_dataReceived);
	}
	
	
	//	Rx Buffer Overrun
	if(bit::isSet(*MCU::UART_5::SR, 3))
	{
		//	Clear Rx Buffer Overrun Flag
		*MCU::UART_5::DR;
		
		
		//	Reset Rx Buffer
		uart.clear();
	}
}