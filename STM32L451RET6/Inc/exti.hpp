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
			PVD									= 16,
			RTC_ALARMS					= 18,
			RTC_TAMPER_CSS_LSE	= 19,
			RTC_WAKEUP					= 20,
			COMP1								= 21,
			COMP2								= 22,
			I2C1_WAKEUP					= 23,
			I2C2_WAKEUP					= 24,
			I2C3_WAKEUP					= 25,
			USART1_WAKEUP				= 26,
			USART2_WAKEUP				= 27,
			USART3_WAKEUP				= 28,
			UART4_WAKEUP				= 29,
			LP_UART1_WAKEUP			= 31,
			LP_TIMER1						= 32,
			LP_TIMER2						= 33,
			PVM1_WAKEUP					= 35,
			PVM3_WAKEUP					= 37,
			PVM4_WAKEUP					= 38,
			I2C4_WAKEUP					= 40
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
		friend class STM32L451RET6;
		
		
		
		
		
	public:
		
		feedback init_GPIO_interrupt(GPIO::e_pin pin, e_edge edge);
		feedback init_interrupt_internal(e_line line, bool interrupt);
		feedback init_event_internal(e_line line, bool event);
		
		inline feedback clear_pendingBit(GPIO::e_pin pin);
		feedback clear_pendingBit(e_line line);
		
		inline bool isPending(GPIO::e_pin pin);
		bool isPending(e_line line);
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

inline feedback EXTI::clear_pendingBit(GPIO::e_pin pin)
{
	bit::set(*MCU::EXTI::PR1, GPIO::get_pinNumber(pin));
	
	return(OK);
}


inline bool EXTI::isPending(GPIO::e_pin pin)
{
	return(bit::isSet(*MCU::EXTI::PR1, GPIO::get_pinNumber(pin)));
}