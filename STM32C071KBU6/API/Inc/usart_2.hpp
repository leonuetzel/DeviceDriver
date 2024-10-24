#pragma once

#include "cmos.hpp"
#include "registers.hpp"





class USART_2 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		DMA_Software m_dma_tx_software;
		
		
		//	Constructor and Destructor
		inline USART_2();
		USART_2(const USART_2& usart_2) = delete;
		inline ~USART_2();
		
		
		//	Member Functions
		inline feedback startup();
		static inline bool readyForNextTransfer();
		
		
		//	Friends
		friend void ISR_USART_2();
		friend class STM32C071KBU6;
		
		
		
		
		
	public:
		
		feedback init(uint32 baud, e_databits databits, e_stopbits stopbits, e_parity parity, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize) override;
		feedback deinit() override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline USART_2::USART_2()
	:	UART((void*) MCU::USART_2::TDR),
		m_dma_tx_software(readyForNextTransfer)
{
	m_dma_tx = &m_dma_tx_software;
}


inline USART_2::~USART_2()
{
	deinit();
}







inline feedback USART_2::startup()
{
	//	Create Semaphore
	return(CMOS::get().semaphore_create(this));
}


inline bool USART_2::readyForNextTransfer()
{
	return(bit::isSet(*MCU::USART_2::ISR, 7));
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

