#pragma once

#include "cmos.hpp"





class UART_7 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		I_DMA* m_dma_rx;
		
		
		//	Constructor and Destructor
		inline UART_7();
		UART_7(const UART_7& uart_7) = delete;
		inline ~UART_7();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend void ISR_UART_7();
		friend class STM32H753BIT6;
		
		
		
		
		
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

inline UART_7::UART_7()
	:	UART((void*) MCU::UART_7::TDR),
		m_dma_rx(nullptr)
{
	
}


inline UART_7::~UART_7()
{
	deinit();
}







inline feedback UART_7::startup()
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

