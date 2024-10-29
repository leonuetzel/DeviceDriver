#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"





class SYSCFG
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline SYSCFG();
		SYSCFG(const SYSCFG& syscfg) = delete;
		inline ~SYSCFG();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32L451RET6;
		
		
		
		
		
	public:
		
		constexpr inline void selectPinForEXTI(GPIO::e_pin pin);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline SYSCFG::SYSCFG()
{
	
}


inline SYSCFG::~SYSCFG()
{
	
}







inline feedback SYSCFG::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::SYSCFG, true);
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

constexpr inline void SYSCFG::selectPinForEXTI(GPIO::e_pin pin)
{
	const uint8 portNumber = GPIO::get_portNumber(pin);
	const uint8 pinNumber = GPIO::get_pinNumber(pin);
	
	const uint32 registerOffset = pinNumber / 4;
	const uint32 bitOffset = (pinNumber % 4) * 4;
	
	const uint32 maskClearing = 0xFFFFFFFF - (0x07 << bitOffset);
	
	uint32* const EXTI_CR = (uint32* const) MCU::SYSCFG::EXTI_CR1 + registerOffset;
	
	const uint32 temp = *EXTI_CR & maskClearing;
	*EXTI_CR = temp | (portNumber << bitOffset);
}