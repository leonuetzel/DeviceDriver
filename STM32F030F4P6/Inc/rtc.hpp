#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"
#include "exti.hpp"





class RTC
{
	public:
		
		
		
		
		
		
		
	private:
		
		constexpr inline RTC();
		RTC(const RTC& rtc) = delete;
		inline ~RTC();
		
		feedback startup();
		
		void set_alarm();
		
		friend class STM32F030F4P6;
		
		
		
		
		
	public:
		
		feedback init(RCC::e_clockSource_rtc clockSource, Time time);
		
		Time read();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline RTC::RTC()
{
	
}


inline RTC::~RTC()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

