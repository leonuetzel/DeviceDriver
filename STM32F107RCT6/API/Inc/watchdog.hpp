#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"





//	Independent Watchdog (IWDG): runs from the LSI and resets the Microcontroller if it is not refreshed within its Timeout
//	get_watchdog() of the Microcontroller Class creates it at the first Call and registers it at CMOS (CMOS::get().get_watchdog()).
//	The Application starts it; once started, it cannot be stopped
class Watchdog: public I_Watchdog
{
	public:
		
		//	Nominal Frequency of the LSI (Datasheet): the real Frequency varies, and with it the Timeout
		static constexpr uint32 c_clock_lsi							= 40000;
	
	
	
	
	
	private:
		
		//	Static Member
		static constexpr uint32 c_prescaler_max					= 6;				//	Division 4 * 2^PR, at most 256
		static constexpr uint32 c_reload_max						= 0xFFF;
		static constexpr uint32 c_loops_update					= 100000;
		
		
		//	Non-static Member
		uint32 m_timeout_ms;
		bool m_running;
		bool m_resetByWatchdog;
		bool m_trial;
		bool m_automatic;
		
		
		//	Constructor and Destructor
		constexpr inline Watchdog();
		Watchdog(const Watchdog& watchdog) = delete;
		inline ~Watchdog();
		
		
		//	Member Functions
		feedback startup(const RCC& rcc);
		feedback configure(uint32 prescaler, uint32 reload);
		static constexpr inline uint32 timeout_ms(uint32 prescaler, uint32 reload);
		inline void handOver();
		
		
		//	Friends
		friend class STM32F107RCT6;
		friend class Update;
	
	
	
	
	
	public:
		
		feedback start(uint32 timeout_ms) override;
		feedback refresh() override;
		bool isRunning() const override;
		uint32 get_timeout_ms() const override;
		uint32 get_timeoutMaximum_ms() const override;
		bool wasLastResetCause() const override;
		bool isAutomatic() const override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Watchdog::Watchdog()
	:	m_timeout_ms(0),
		m_running(false),
		m_resetByWatchdog(false),
		m_trial(false),
		m_automatic(false)
{
	
}


inline Watchdog::~Watchdog()
{
	
}


inline void Watchdog::handOver()
{
	//	The Update is confirmed: a Watchdog that runs only for the Trial goes to CMOS, which refreshes it from now on (isAutomatic)
	if(m_trial == true)
	{
		m_automatic = true;
	}
}


constexpr inline uint32 Watchdog::timeout_ms(uint32 prescaler, uint32 reload)
{
	//	(RLR + 1) Periods of the LSI divided by 4 * 2^PR, rounded up to whole Milliseconds - at most 4096 * 256 * 1000, it fits into 32 Bit
	return(((reload + 1) * (4u << prescaler) * 1000 + c_clock_lsi - 1) / c_clock_lsi);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/
