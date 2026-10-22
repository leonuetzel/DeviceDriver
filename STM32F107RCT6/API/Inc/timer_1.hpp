#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class Timer_1
{
	public:
		
		enum class e_channel
		{
			CHANNEL_1									= 0x0,
			CHANNEL_2									= 0x1,
			CHANNEL_3									= 0x2,
			CHANNEL_4									= 0x3
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline Timer_1();
		Timer_1(const Timer_1& timer_1) = delete;
		inline ~Timer_1();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		feedback init(uint32 frequency, bool interrupt);
		
		inline void init_pwm(e_channel channel);
		inline void set_pwm(e_channel channel, uint32 dutycycle_ppm);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Timer_1::Timer_1()
{
	
}


inline Timer_1::~Timer_1()
{
	
}







inline feedback Timer_1::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void Timer_1::init_pwm(e_channel channel)
{
	//	PWM Mode 1 (OCxM = 110): Channels 1 and 3 use the lower, Channels 2 and 4 the upper Byte of CCMR1 and CCMR2
	volatile uint32* reg_ccmr = MCU::TIMER_1::CCMR1 + (uint32) channel / 2;
	const uint32 shift = 8 * ((uint32) channel % 2);
	*reg_ccmr = (*reg_ccmr & ~(0x000000FF << shift)) | (0x00000060 << shift);
	
	uint32 bit = 4 * (uint32) channel;
	
	
	//	Channel Active High
	bit::set(*MCU::TIMER_1::CCER, bit);
	
	
	//	Channel Enable
	bit::clear(*MCU::TIMER_1::CCER, bit + 1);
}


inline void Timer_1::set_pwm(e_channel channel, uint32 dutycycle_ppm)
{
	volatile uint32* reg_ccr = MCU::TIMER_1::CCR1 + (uint32) channel;
	//	The Output is active while the Counter is below CCR (PWM Mode 1), so 100 % needs CCR = ARR + 1
	if(dutycycle_ppm > 1000000)
	{
		dutycycle_ppm = 1000000;
	}
	*reg_ccr = ((uint64) dutycycle_ppm * ((uint64) *MCU::TIMER_1::ARR + 1)) / 1000000;
}