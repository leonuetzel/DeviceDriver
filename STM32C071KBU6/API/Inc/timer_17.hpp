#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"
#include "gpio.hpp"





class Timer_17
{
	public:
		
		enum class e_channel : uint8
		{
			CHANNEL_1
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		RCC& m_rcc;
		
		
		//	Constructor and Destructor
		constexpr inline Timer_17(RCC& rcc);
		Timer_17(const Timer_17& timer_17) = delete;
		inline ~Timer_17();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32C071KBU6;
		
		
		
		
		
	public:
		
		feedback init(uint32 frequency, bool interrupt);
		
		void init_pwm(e_channel channel);
		void set_pwm(e_channel channel, uint32 dutycycle_ppm);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Timer_17::Timer_17(RCC& rcc)
	: m_rcc(rcc)
{
	
}


inline Timer_17::~Timer_17()
{
	
}







inline feedback Timer_17::startup()
{
	m_rcc.module_reset(RCC::e_module::TIMER_17);
	m_rcc.module_clockInit(RCC::e_module::TIMER_17, true);
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

