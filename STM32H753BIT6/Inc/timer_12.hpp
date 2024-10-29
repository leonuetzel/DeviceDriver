#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"
#include "gpio.hpp"





class Timer_12
{
	public:
		
		enum class e_channel
		{
			CHANNEL_1,
			CHANNEL_2
		};
		
		
		
		
		
	private:
		
		RCC& m_rcc;
		
		constexpr inline Timer_12(RCC& rcc);
		Timer_12(const Timer_12& timer_12) = delete;
		inline ~Timer_12();
		
		
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

constexpr inline Timer_12::Timer_12(RCC& rcc)
	: m_rcc(rcc)
{
	
}


inline Timer_12::~Timer_12()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

