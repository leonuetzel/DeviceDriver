#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





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
		inline feedback startup(RCC& rcc);
		void set_alarm(uint32 value);
		void enter();
		void exit();
		
		
		//	Friends
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		feedback init(RCC::e_clockSource_rtc clockSource);
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







inline feedback RTC::startup(RCC& rcc)
{
	rcc.reset_backupDomain();
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

