#pragma once

#include "cmos.hpp"
#include "stm32l010rbt6.hpp"





class LP_UART_1 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
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
		
		feedback reset();
		feedback init(uint32 baud, e_databits databits, e_stopbits stopbits, e_parity parity, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize) override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline LP_UART_1::LP_UART_1()
	:	UART(Interrupt::LP_UART_1, (void*) MCU::LP_UART_1::TDR)
{
	
}


inline LP_UART_1::~LP_UART_1()
{
	
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

