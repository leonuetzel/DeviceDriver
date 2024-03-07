#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"
#include "exti.hpp"





class RTC
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline RTC();
		RTC(const RTC& rtc) = delete;
		inline ~RTC();
		
		
		//	Member Functions
		feedback startup();
		void set_alarm();
		
		
		//	Friends
		friend class STM32L010RBT6;
		
		
		
		
		
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

