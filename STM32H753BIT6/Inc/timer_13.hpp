#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"
#include "gpio.hpp"





class Timer_13
{
	public:
		
		enum class e_channel
		{
			CHANNEL_1
		};
		
		
		
		
		
	private:
		
		RCC& m_rcc;
		
		constexpr inline Timer_13(RCC& rcc);
		Timer_13(const Timer_13& timer_13) = delete;
		inline ~Timer_13();
		
		
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

constexpr inline Timer_13::Timer_13(RCC& rcc)
	: m_rcc(rcc)
{
	
}


inline Timer_13::~Timer_13()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

