#pragma once

#include "cmos.hpp"
#include "registers.hpp"





class LP_UART_1 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		I_DMA* m_dma_rx;
		
		
		//	Constructor and Destructor
		inline LP_UART_1();
		LP_UART_1(const LP_UART_1& lpuart_1) = delete;
		inline ~LP_UART_1();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend void ISR_LPUART_1();
		friend class STM32L010RBT6;
		
		
		
		
		
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

inline LP_UART_1::LP_UART_1()
	:	UART((void*) MCU::LP_UART_1::TDR),
		m_dma_rx(nullptr)
{
	
}


inline LP_UART_1::~LP_UART_1()
{
	deinit();
}







inline feedback LP_UART_1::startup()
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

