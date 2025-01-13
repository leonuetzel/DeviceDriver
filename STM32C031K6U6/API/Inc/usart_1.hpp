#pragma once

#include "cmos.hpp"
#include "registers.hpp"





class USART_1 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		I_DMA* m_dma_rx;
		
		
		//	Constructor and Destructor
		inline USART_1();
		USART_1(const USART_1& usart_1) = delete;
		inline ~USART_1();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend void ISR_USART_1();
		friend class STM32C031K6U6;
		
		
		
		
		
	public:
		
		feedback init(uint32 baud, e_databits databits, e_parity parity, e_stopbits stopbits, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize) override;
		feedback deinit() override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline USART_1::USART_1()
	:	UART((void*) MCU::USART_1::TDR),
		m_dma_rx(nullptr)
{
	
}


inline USART_1::~USART_1()
{
	deinit();
}







inline feedback USART_1::startup()
{
	//	Create Semaphore
	return(CMOS::get().semaphore_create(this));
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

