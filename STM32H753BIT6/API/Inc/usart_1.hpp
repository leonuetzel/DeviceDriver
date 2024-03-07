#pragma once

#include "cmos.hpp"





class USART_1 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		inline USART_1();
		USART_1(const USART_1& usart_1) = delete;
		inline ~USART_1();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend void ISR_USART_1();
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

inline USART_1::USART_1()
	:	UART(Interrupt::USART_1, (void*) MCU::USART_1::TDR)
{
	
}


inline USART_1::~USART_1()
{
	
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

