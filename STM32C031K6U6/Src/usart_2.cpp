#include "../Inc/stm32c031k6u6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback USART_2::init(uint32 baud, e_databits databits, e_parity parity, e_stopbits stopbits, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize)
{
	//	Check if Mutex is locked
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Word Length: the Parity Bit is the MSB of the Word, so with Parity the Word is one Bit longer than the Databits
	//	Possible are Words with 8 or 9 Bit, 7 Databits are not supported
	uint32 wordLength = 7 + (uint32) databits;
	if(parity != e_parity::NONE)
	{
		wordLength++;
	}
	if(databits == e_databits::_7 || wordLength > 9)
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
	m_txInFlight = 0;
	
	
	//	Reset USART 2
	STM32C031K6U6& stm32 = STM32C031K6U6::get();
	RCC& rcc = stm32.get_rcc();
	rcc.module_reset(RCC::e_module::USART_2);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::USART_2, true);
	uint32 clock_in = rcc.get_clock_apb();
	
	
	//	Word Length M: 0 = 8 Bit, 1 = 9 Bit, including the Parity Bit
	if(wordLength == 8)
	{
		bit::clear(*MCU::USART_2::CR1, 12);
	}
	else
	{
		bit::set(*MCU::USART_2::CR1, 12);
	}
	
	
	//	Baudrate
	*MCU::USART_2::BRR = clock_in / baud;
	
	
	//	Stop Bits
	uint32 temp = *MCU::USART_2::CR2 & 0xFFFFCFFF;
	*MCU::USART_2::CR2 = temp | (((uint32) stopbits) << 12);
	
	
	//	Parity
	temp = *MCU::USART_2::CR1 & 0xFFFFF9FF;
	*MCU::USART_2::CR1 = temp | (((uint32) parity) << 9);
	
	
	//	Enable IDLE Line Interrupt
	bit::set(*MCU::USART_2::CR1, 4);
	
	
	//	Enable RX FIFO not emtpy Interrupt
	bit::set(*MCU::USART_2::CR1, 5);
	
	
	//	Subscribe to USART Rx Message Receive Event so that we get waken up by the ISR when Data is received
	cmos.event_subscribe(m_eventID_dataReceived);
	
	
	//	Interrupt
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::USART_2, 2);
	nvic.enable(Interrupt::USART_2);
	
	
	//	USART 2 Enable
	bit::set(*MCU::USART_2::CR1, 0);
	
	
	//	TX Enable
	bit::set(*MCU::USART_2::CR1, 3);
	
	
	//	RX Enable
	bit::set(*MCU::USART_2::CR1, 2);
	
	
	//	Set Flag to enable other Functions
	m_initialized = true;
	return(OK);
}


feedback USART_2::deinit()
{
	//	Check if all related Mutexes are owned by running Thread
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Wait for the End of the Transmission (TC): tx returns as soon as the DMA is done, but the last Bytes are still in the Data Register
	//	and in the Shift Register then - resetting the USART earlier would cut them off. The Timeout covers 2 Frames at 300 Baud
	uint32 timeout_ms = 100;
	while(m_initialized == true && bit::isCleared(*MCU::USART_2::ISR, 6) == true && timeout_ms > 0)
	{
		cmos.sleep_ms(1);
		timeout_ms--;
	}
	
	
	//	Disable Interrupt
	NVIC& nvic = cmos.get_nvic();
	if(nvic.disable(Interrupt::USART_2) != OK)
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
	m_txInFlight = 0;
	
	
	//	Reset USART
	STM32C031K6U6& stm32 = STM32C031K6U6::get();
	RCC& rcc = stm32.get_rcc();
	if(rcc.module_reset(RCC::e_module::USART_2) != OK)
	{
		return(FAIL);
	}
	
	
	//	Free Mutexes
	if(cmos.mutex_unlock(this) != OK)
	{
		return(FAIL);
	}
	
	
	//	Reset Flag
	m_initialized = false;
	
	
	return(OK);
}









void ISR_USART_2()
{
	USART_2& usart = STM32C031K6U6::get().get_usart_2();
	
	
	//	Data received
	if(bit::isSet(*MCU::USART_2::ISR, 5))
	{
		usart.write(*MCU::USART_2::RDR);
	}
	
	
	//  IDLE Line detected
	if(bit::isSet(*MCU::USART_2::ISR, 4))
	{
		//	Clear Interrupt Flag
		*MCU::USART_2::ICR = 1 << 4;
		
		
		//	Notify Threads about received Data
		CMOS& cmos = CMOS::get();
		cmos.event_emit(usart.m_eventID_dataReceived);
	}
	
	
	//	Rx Buffer Overrun
	if(bit::isSet(*MCU::USART_2::ISR, 3))
	{
		//	Clear Interrupt Flag
		*MCU::USART_2::ICR = 1 << 3;
		
		
		//	The received Bytes stay in the Buffer, only the Bytes arriving during the Overrun are lost
	}
}