#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class RTC
{
	public:
	
	
	
	
	
	
	
	private:
		
		//	Static Member
		static constexpr uint8 c_daysOfMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		
		
		//	Non-static Member
		uint16 m_eventID_alarm;
		bool m_synchronized;
		
		
		//	Constructor and Destructor
		constexpr inline RTC();
		RTC(const RTC& rtc) = delete;
		inline ~RTC();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		static feedback check_time(const Time& time);
		static constexpr inline bool is_leapYear(uint32 year);
		static uint32 get_seconds(const Time& time);
		static Time get_time(uint32 seconds);
		static bool is_enabled();
		static bool enable_backupDomainWrite();
		static void restore_backupDomainWrite(bool writeProtected);
		feedback synchronize();
		feedback enter_configurationMode(bool& writeProtected);
		feedback exit_configurationMode(bool writeProtected);
		
		
		//	Friends
		friend class STM32F107RCT6;
		friend void ISR_RTC_ALARM_EXTI();
	
	
	
	
	
	public:
		
		feedback init(RCC::e_clockSource_rtc clockSource, Time time = Time());
		feedback set_time(Time time);
		Time read();
		
		feedback set_alarm(Time time);
		feedback disable_alarm();
		inline uint16 get_eventID_alarm() const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline RTC::RTC()
	:	m_eventID_alarm(CMOS::eventID_invalid),
		m_synchronized(false)
{
	
}


inline RTC::~RTC()
{
	
}


inline feedback RTC::startup(RCC&)
{
	//	The Backup Domain is not reset: the RTC keeps running over a Reset of the Microcontroller, init() only sets it if necessary
	m_eventID_alarm = CMOS::get().event_create();
	return(OK);
}


constexpr inline bool RTC::is_leapYear(uint32 year)
{
	//	Gregorian Calendar: divisible by 4, but not by 100 - except if divisible by 400
	return((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline uint16 RTC::get_eventID_alarm() const
{
	return(m_eventID_alarm);
}
