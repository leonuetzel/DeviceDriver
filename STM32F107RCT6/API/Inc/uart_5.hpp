#pragma once

#include "cmos.hpp"





class UART_5 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		DMA_Software m_dma_tx_software;
		
		
		//	Constructor and Destructor
		inline UART_5();
		UART_5(const UART_5& uart_5) = delete;
		inline ~UART_5();
		
		
		//	Member Functions
		inline feedback startup();
		static inline bool readyForNextTransfer();
		
		
		//	Friends
		friend void ISR_UART_5();
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		feedback init(uint32 baud, e_databits databits, e_stopbits stopbits, e_parity parity, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize) override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline UART_5::UART_5()
	:	UART(Interrupt::UART_5, (void*) MCU::UART_5::DR),
		m_dma_tx_software(readyForNextTransfer)
{
	
}


inline UART_5::~UART_5()
{
	
}







inline feedback UART_5::startup()
{
	//	Create Semaphore
	return(CMOS::get().semaphore_create(this));
}


inline bool UART_5::readyForNextTransfer()
{
	return(bit::isSet(*MCU::UART_5::SR, 7));
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

