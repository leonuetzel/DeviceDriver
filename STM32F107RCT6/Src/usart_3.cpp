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

feedback USART_3::init(uint32 baud, e_databits databits, e_parity parity, e_stopbits stopbits, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize)
{
	//	Check if Mutex is locked
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Check the Parameters before the DMA Channels are locked, so that a Failure does not leave them locked
	if(rxBufferSize <= 0 || rxBuffer == nullptr || txBufferSize <= 0 || txBuffer == nullptr)
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
	
	
	//	Lock Mutex of Tx DMA
	STM32F107RCT6& stm32 = STM32F107RCT6::get();
	m_dma_tx = &stm32.get_dma_1(1);
	if(cmos.mutex_lock(m_dma_tx) != OK)
	{
		return(FAIL);
	}
	
	
	//	Lock Mutex of Rx DMA
	m_dma_rx = &stm32.get_dma_1(2);
	if(cmos.mutex_lock(m_dma_rx) != OK)
	{
		cmos.mutex_unlock(m_dma_tx);
		return(FAIL);
	}
	
	
	//	Rx and Tx Buffer
	m_data = rxBuffer;
	m_size = rxBufferSize;
	reset();
	m_txBuffer = RingbufferExternal<uint8>(txBuffer, txBufferSize);
	m_txInFlight = 0;
	
	
	//	Reset USART
	RCC& rcc = stm32.get_rcc();
	rcc.module_reset(RCC::e_module::USART_3);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::USART_3, true);
	uint32 clock_in = rcc.get_clock_apb1();
	
	
	//	Word Length M: 0 = 8 Bit, 1 = 9 Bit, including the Parity Bit
	if(wordLength == 8)
	{
		bit::clear(*MCU::USART_3::CR1, 12);
	}
	else
	{
		bit::set(*MCU::USART_3::CR1, 12);
	}
	
	
	//	Baudrate
	*MCU::USART_3::BRR = clock_in / baud;
	
	
	//	Stop Bits
	uint32 temp = *MCU::USART_3::CR2 & 0xFFFFCFFF;
	*MCU::USART_3::CR2 = temp | (((uint32) stopbits) << 12);
	
	
	//	Parity
	temp = *MCU::USART_3::CR1 & 0xFFFFF9FF;
	*MCU::USART_3::CR1 = temp | (((uint32) parity) << 9);
	
	
	//	Enable IDLE Line Interrupt
	bit::set(*MCU::USART_3::CR1, 4);
	
	
	//	Enable RX DMA Mode
	bit::set(*MCU::USART_3::CR3, 6);
	
	
	//	Enable TX DMA Mode
	bit::set(*MCU::USART_3::CR3, 7);
	
	
	//	Rx DMA Setup
	if(m_dma_rx->transfer((void*) MCU::USART_3::DR, m_data, I_DMA::e_dataType::UINT8, I_DMA::e_dataType::UINT8, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, m_size, I_DMA::e_priority::VERY_HIGH, false) != OK)
	{
		cmos.mutex_unlock(m_dma_rx);
		cmos.mutex_unlock(m_dma_tx);
		return(FAIL);
	}
	
	
	//	Subscribe to USART Rx Message Receive Event so that we get waken up by the ISR when Data is received
	cmos.event_subscribe(m_eventID_dataReceived);
	
	
	//	Interrupt
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::USART_3, 10);
	nvic.enable(Interrupt::USART_3);
	
	
	//	USART Enable
	bit::set(*MCU::USART_3::CR1, 13);
	
	
	//	TX Enable
	bit::set(*MCU::USART_3::CR1, 3);
	
	
	//	RX Enable
	bit::set(*MCU::USART_3::CR1, 2);
	
	
	//	Set Flag to enable other Functions
	m_initialized = true;
	return(OK);
}


feedback USART_3::deinit()
{
	//	Check if all related Mutexes are owned by running Thread
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	if(cmos.mutex_isOwnedByRunningThread(m_dma_tx) == false)
	{
		return(FAIL);
	}
	if(cmos.mutex_isOwnedByRunningThread(m_dma_rx) == false)
	{
		return(FAIL);
	}
	
	
	//	Wait for the End of the Transmission (TC): tx returns as soon as the DMA is done, but the last Bytes are still in the Data Register
	//	and in the Shift Register then - resetting the USART earlier would cut them off. The Timeout covers 2 Frames at 300 Baud
	uint32 timeout_ms = 100;
	while(m_initialized == true && bit::isCleared(*MCU::USART_3::SR, 6) == true && timeout_ms > 0)
	{
		cmos.sleep_ms(1);
		timeout_ms--;
	}
	
	
	//	Disable Interrupt
	NVIC& nvic = cmos.get_nvic();
	if(nvic.disable(Interrupt::USART_3) != OK)
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
	m_txInFlight = 0;
	
	
	//	Reset USART
	STM32F107RCT6& stm32 = STM32F107RCT6::get();
	RCC& rcc = stm32.get_rcc();
	if(rcc.module_reset(RCC::e_module::USART_3) != OK)
	{
		return(FAIL);
	}
	
	
	//	Free Mutexes
	if(cmos.mutex_unlock(m_dma_rx) != OK)
	{
		return(FAIL);
	}
	if(cmos.mutex_unlock(m_dma_tx) != OK)
	{
		return(FAIL);
	}
	if(cmos.mutex_unlock(this) != OK)
	{
		return(FAIL);
	}
	
	
	//	Reset Flag
	m_initialized = false;
	
	
	return(OK);
}









void ISR_USART_3()
{
	USART_3& usart = STM32F107RCT6::get().get_usart_3();
	
	
	//  IDLE Line detected
	if(bit::isSet(*MCU::USART_3::SR, 4))
	{
		//	Clear IDLE Line Flag
		*MCU::USART_3::DR;
		
		
		//	Update Head
		//	The DMA writes the received Data into the Buffer by itself, NDTR counts the remaining Elements until the End of the Buffer
		usart.set_writePosition(usart.m_size - *MCU::DMA_1::CH2_NDTR);
		
		
		//	Notify Threads about received Data
		CMOS& cmos = CMOS::get();
		cmos.event_emit(usart.m_eventID_dataReceived);
	}
	
	
	//	Rx Buffer Overrun
	if(bit::isSet(*MCU::USART_3::SR, 3))
	{
		//	Clear Rx Buffer Overrun Flag
		*MCU::USART_3::DR;
		
		
		//	The received Bytes stay in the Buffer, only the Bytes arriving during the Overrun are lost
	}
}