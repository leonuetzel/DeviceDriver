#pragma once

#include "cmos.hpp"





class RTC
{
	public:
		
		enum class e_clockSource
		{
			NONE,
			LSE,
			LSI,
			HSE
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		uint32 m_clockIn;
		e_clockSource m_clockSource;
		
		
		//	Constructor and Destructor
		constexpr inline RTC();
		RTC(const RTC& rtc) = delete;
		inline ~RTC();
		
		
		//	Member Functions
		feedback startup();
		
		feedback initClock(e_clockSource clockSource, Time time);
		void set_alarm();
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		Time read();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline RTC::RTC()
	: m_clockIn(0),
		m_clockSource(e_clockSource::NONE)
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

