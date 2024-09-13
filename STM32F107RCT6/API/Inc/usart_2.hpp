#pragma once

#include "cmos.hpp"
#include "registers.hpp"





class USART_2 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		inline USART_2();
		USART_2(const USART_2& usart_2) = delete;
		inline ~USART_2();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend void ISR_USART_2();
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

inline USART_2::USART_2()
	:	UART((void*) MCU::USART_2::DR)
{
	
}


inline USART_2::~USART_2()
{
	
}







inline feedback USART_2::startup()
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
