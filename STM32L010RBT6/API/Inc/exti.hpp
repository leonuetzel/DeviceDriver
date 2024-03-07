#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"
#include "gpio.hpp"





class EXTI
{
	public:
		
		enum class e_edge : uint8
		{
			NONE,
			RISING,
			FALLING,
			TOGGLE
		};
		
		enum class e_line : uint8
		{
			RTC_ALARM											= 17,
			RTC_TAMPER_TIMESTAMP_CSS_LSE	= 19,
			RTC_WAKEUP										= 20,
			I2C1_WAKEUP										= 23,
			USART2_WAKEUP									= 26,
			LPTIMER1_WAKEUP								= 29
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline EXTI();
		EXTI(const EXTI& exti) = delete;
		inline ~EXTI();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32L010RBT6;
		
		
		
		
		
	public:
		
		feedback init_GPIO_interrupt(GPIO::e_pin pin, e_edge edge);
		feedback init_interrupt_internal(e_line line, bool interrupt);
		feedback init_event_internal(e_line line, bool event);
		
		feedback clear_pendingBit(GPIO::e_pin pin);
		feedback clear_pendingBit(e_line line);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline EXTI::EXTI()
{
	
}


inline EXTI::~EXTI()
{
	
}







inline feedback EXTI::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

