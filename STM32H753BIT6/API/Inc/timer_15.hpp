#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"
#include "gpio.hpp"





class Timer_15
{
	public:
		
		enum class e_channel
		{
			CHANNEL_1,
			CHANNEL_2
		};
		
		
		
		
		
	private:
		
		RCC& m_rcc;
		
		constexpr inline Timer_15(RCC& rcc);
		Timer_15(const Timer_15& timer_15) = delete;
		inline ~Timer_15();
		
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup();
		
		feedback init(uint32 frequency, bool enableInterrupt);
		
		void init_pwm(e_channel channel);
		void set_pwm(e_channel channel, uint32 dutycycle_ppm);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Timer_15::Timer_15(RCC& rcc)
	: m_rcc(rcc)
{
	
}


inline Timer_15::~Timer_15()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

