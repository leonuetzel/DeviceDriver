#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





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
		
		RCC& m_rcc;
		
		uint32 m_clockIn;
		e_clockSource m_clockSource;
		
		constexpr inline RTC(RCC& rcc);
		RTC(const RTC& rtc) = delete;
		inline ~RTC();
		
		feedback initClock(e_clockSource clockSource, Time time);
		void set_alarm();
		
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup();
		
		Time read();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline RTC::RTC(RCC& rcc)
	: m_rcc(rcc),
		m_clockIn(0),
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

