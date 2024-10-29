#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class Timer_3
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
		constexpr inline Timer_3();
		Timer_3(const Timer_3& timer_3) = delete;
		inline ~Timer_3();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32F103C8T6;
		
		
		
		
		
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

constexpr inline Timer_3::Timer_3()
{
	
}


inline Timer_3::~Timer_3()
{
	
}








inline feedback Timer_3::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void Timer_3::init_pwm(e_channel channel)
{
	volatile uint16* reg_ccmr = (volatile uint16*) MCU::TIMER_3::CCMR1 + (uint32) channel;
	*reg_ccmr = 0x0060;
	
	uint32 bit = 4 * (uint32) channel;
	
	
	//	Channel Active High
	bit::set(*MCU::TIMER_3::CCER, bit);
	
	
	//	Channel Enable
	bit::clear(*MCU::TIMER_3::CCER, bit + 1);
}


inline void Timer_3::set_pwm(e_channel channel, uint32 dutycycle_ppm)
{
	volatile uint32* reg_ccr = MCU::TIMER_3::CCR1 + (uint32) channel;
	*reg_ccr = ((uint64) dutycycle_ppm * *MCU::TIMER_3::ARR) / 1000000;
}