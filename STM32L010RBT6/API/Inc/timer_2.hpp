#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"
#include "gpio.hpp"





class Timer_2
{
	public:
		
		enum class e_channel : uint8
		{
			CHANNEL_1,
			CHANNEL_2,
			CHANNEL_3,
			CHANNEL_4
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		RCC& m_rcc;
		
		
		//	Constructor and Destructor
		constexpr inline Timer_2(RCC& rcc);
		Timer_2(const Timer_2& timer_2) = delete;
		inline ~Timer_2();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32L010RBT6;
		
		
		
		
		
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

constexpr inline Timer_2::Timer_2(RCC& rcc)
	: m_rcc(rcc)
{
	
}


inline Timer_2::~Timer_2()
{
	
}







inline feedback Timer_2::startup()
{
	m_rcc.module_reset(RCC::e_module::TIMER_2);
	m_rcc.module_clockInit(RCC::e_module::TIMER_2, true);
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

