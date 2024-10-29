#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"
#include "gpio.hpp"





class EXTI
{
	public:
		
		enum class e_edge
		{
			NONE,
			RISING,
			FALLING,
			TOGGLE
		};
		
		enum class e_line
		{
			RTC_ALARM							= 17,
			RTC_TAMPER_TIMESTAMP	= 19
		};
		
		
		
		
		
	private:
		
		constexpr inline EXTI();
		EXTI(const EXTI& exti) = delete;
		inline ~EXTI();
		
		inline feedback startup();
		
		friend class STM32F030F4P6;
		
		
		
		
		
	public:
		
		feedback init_GPIO_interrupt(GPIO::e_pin pin, e_edge edge);
		feedback init_interrupt_internal(e_line line, bool interrupt);
		
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

