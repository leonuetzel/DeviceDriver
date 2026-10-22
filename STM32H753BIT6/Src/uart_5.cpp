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

feedback UART_5::init(uint32 baud, e_databits databits, e_parity parity, e_stopbits stopbits, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize)
{
	//	Check if Mutex is locked
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Check the Parameters before the DMA Channels are locked, so that a Failure does not leave them locked
	//	With the Data Cache on, the Rx Buffer is invalidated after every Reception and must own its Cache Lines (see cacheMaintenance.hpp)
	if(rxBufferSize <= 0 || rxBuffer == nullptr || txBufferSize <= 0 || txBuffer == nullptr)
	{
		return(FAIL);
	}
	if(CacheMaintenance::ownsCacheLines(rxBuffer, rxBufferSize) == false)
	{
		return(FAIL);
	}
	
	
	//	Word Length: the Parity Bit is the MSB of the Word, so with Parity the Word is one Bit longer than the Databits
	//	Possible are Words with 7, 8 or 9 Bit
	uint32 wordLength = 7 + (uint32) databits;
	if(parity != e_parity::NONE)
	{
		wordLength++;
	}
	if(wordLength > 9)
	{
		return(FAIL);
	}
	
	
	//	Lock Mutex of Tx DMA
	//	UART_5 uses DMA2 Stream 1 (Tx) and Stream 0 (Rx): the Streams of DMA1 belong to the ADCs, USART_1 and UART_7
	STM32H753BIT6& stm32 = STM32H753BIT6::get();
	m_dma_tx = &stm32.get_dma_2(1);
	if(cmos.mutex_lock(m_dma_tx) != OK)
	{
		return(FAIL);
	}
	
	
	//	Lock Mutex of Rx DMA
	m_dma_rx = &stm32.get_dma_2(0);
	if(cmos.mutex_lock(m_dma_rx) != OK)
	{
		cmos.mutex_unlock(m_dma_tx);
		return(FAIL);
	}
	
	
	//	Rx and Tx Buffer
	//	With the Data Cache on, the Rx Buffer is invalidated after every Reception and must own its Cache Lines (see cacheMaintenance.hpp)
	m_data = rxBuffer;
	m_size = rxBufferSize;
	reset();
	m_txBuffer = RingbufferExternal<uint8>(txBuffer, txBufferSize);
	m_txInFlight = 0;
	
	
	//	Reset UART
	RCC& rcc = stm32.get_rcc();
	rcc.module_reset(RCC::e_module::UART_5);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::UART_5, true);
	rcc.set_clockSource(RCC::e_clockSource_uart::BUS_CLOCK, 5);
	uint32 clock_in = rcc.get_clock_apb1();
	
	
	//	Databits
	//	Word Length M[1:0]: 10 = 7 Bit, 00 = 8 Bit, 01 = 9 Bit, including the Parity Bit
	if(wordLength == 7)
	{
		bit::clear(*MCU::UART_5::CR1, 12);
		bit::set(*MCU::UART_5::CR1, 28);
	}
	else if(wordLength == 8)
	{
		bit::clear(*MCU::UART_5::CR1, 12);
		bit::clear(*MCU::UART_5::CR1, 28);
	}
	else
	{
		bit::set(*MCU::UART_5::CR1, 12);
		bit::clear(*MCU::UART_5::CR1, 28);
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
	dmamux.map(DMAMUX::e_input::UART_5_RX_DMA, DMAMUX::e_output::DMA_2_CH0);
	dmamux.map(DMAMUX::e_input::UART_5_TX_DMA, DMAMUX::e_output::DMA_2_CH1);
	
	
	//	Rx DMA Setup
	if(m_dma_rx->transfer((void*) MCU::UART_5::RDR, m_data, I_DMA::e_dataType::UINT8, I_DMA::e_dataType::UINT8, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, m_size, I_DMA::e_priority::VERY_HIGH, false) != OK)
	{
		cmos.mutex_unlock(m_dma_rx);
		cmos.mutex_unlock(m_dma_tx);
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
	while(m_initialized == true && bit::isCleared(*MCU::UART_5::ISR, 6) == true && timeout_ms > 0)
	{
		cmos.sleep_ms(1);
		timeout_ms--;
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
	m_txInFlight = 0;
	
	
	//	Reset USART
	STM32H753BIT6& stm32 = STM32H753BIT6::get();
	RCC& rcc = stm32.get_rcc();
	if(rcc.module_reset(RCC::e_module::UART_5) != OK)
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









CODE_RAM void ISR_UART_5()
{
	UART_5& uart = STM32H753BIT6::get().get_uart_5();
	
	
	//  IDLE Line detected
	if(bit::isSet(*MCU::UART_5::ISR, 4))
	{
		//	Clear Interrupt Flag
		bit::set(*MCU::UART_5::ICR, 4);
		
		
		//	Cache Maintenance: the CPU reads the received Data only after this
		//	The whole Buffer is invalidated, the CPU never writes it
		CacheMaintenance::afterWrite(uart.m_data, uart.m_size);
		
		
		//	Update Head
		//	The DMA writes the received Data into the Buffer by itself, NDTR counts the remaining Elements until the End of the Buffer
		uart.set_writePosition(uart.m_size - *MCU::DMA_2::CH0_NDTR);
		
		
		//	Notify Threads about received Data
		CMOS& cmos = CMOS::get();
		cmos.event_emit(uart.m_eventID_dataReceived);
	}
	
	
	//	Rx Buffer Overrun
	if(bit::isSet(*MCU::UART_5::ISR, 3))
	{
		//	Clear Interrupt Flag
		bit::set(*MCU::UART_5::ICR, 3);
		
		
		//	The received Bytes stay in the Buffer, only the Bytes arriving during the Overrun are lost
	}
}