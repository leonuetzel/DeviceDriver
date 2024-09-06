#pragma once

#include "cmos.hpp"





class UART_7 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
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
		
		feedback init(uint32 baud, e_databits databits, e_stopbits stopbits, e_parity parity, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize) override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline UART_7::UART_7()
	:	UART((void*) MCU::UART_7::TDR)
{
	
}


inline UART_7::~UART_7()
{
	
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

