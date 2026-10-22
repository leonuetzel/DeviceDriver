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
		uint16 m_eventID_alarm;
		
		
		//	Constructor and Destructor
		constexpr inline RTC();
		RTC(const RTC& rtc) = delete;
		inline ~RTC();
		
		
		//	Member Functions
		feedback startup();
		
		static feedback check_time(const Time& time);
		static feedback calculate_prescaler(uint32 clock, uint32& prescaler_async, uint32& prescaler_sync);
		static bool is_enabled();
		static bool enable_backupDomainWrite();
		static void restore_backupDomainWrite(bool writeProtected);
		feedback enter_initializationMode(bool& writeProtected);
		void exit_initializationMode(bool writeProtected);
		
		
		//	Friends
		friend class STM32H753BIT6;
		friend void ISR_RTC_ALARM_EXTI();
	
	
	
	
	
	public:
		
		feedback init(e_clockSource clockSource, Time time);
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
	:	m_eventID_alarm(CMOS::eventID_invalid)
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

inline uint16 RTC::get_eventID_alarm() const
{
	return(m_eventID_alarm);
}
