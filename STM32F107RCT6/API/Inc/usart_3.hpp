#pragma once

#include "cmos.hpp"





class USART_3 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		inline USART_3();
		USART_3(const USART_3& usart_3) = delete;
		inline ~USART_3();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend void ISR_USART_3();
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

inline USART_3::USART_3()
	:	UART(Interrupt::USART_3, (void*) MCU::USART_3::DR)
{
	
}


inline USART_3::~USART_3()
{
	
}







inline feedback USART_3::startup()
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

