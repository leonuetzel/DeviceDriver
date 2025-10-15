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
			RTC_ALARM						= 17,
			USB_WAKEUP					= 18,
			RTC_TAMPER_CSS_LSE	= 19,
			RTC_WAKEUP					= 20,
			COMP1								= 21,
			COMP2								= 22,
			I2C1_WAKEUP					= 23,
			I2C2_WAKEUP					= 24,
			USART1_WAKEUP				= 25,
			USART2_WAKEUP				= 26,
			I2C3_WAKEUP					= 27,
			USART3_WAKEUP				= 28,
			COMP3								= 29,
			COMP4								= 30,
			COMP5								= 31,
			COMP6								= 32,
			COMP7								= 33,
			UART4								= 34,
			UART5								= 35,
			LPUART1							= 36,
			LPTIMER1						= 37,
			PVM1								= 40,
			PVM2								= 41,
			I2C4								= 42,
			UCPD								= 43
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
		friend class STM32G474MCT6;
		
		
		
		
		
	public:
		
		feedback init_GPIO_interrupt(MCU::PIN pin, e_edge edge);
		feedback init_interrupt_internal(e_line line, bool interrupt);
		feedback init_event_internal(e_line line, bool event);
		
		feedback clear_pendingBit(MCU::PIN pin);
		feedback clear_pendingBit(e_line line);
		
		bool isPending(MCU::PIN pin);
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

