#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback Watchdog::startup(const RCC& rcc)
{
	//	Last Reset by this Watchdog: IWDG1RSTF (Bit 26) in the Snapshot that RCC::startup() took before it cleared the Reset Flags (RM0433)
	m_resetByWatchdog = ((rcc.get_resetFlags() >> 26) & 0x1) != 0;
	
	
	//	It runs since the Reset with the Values of PR and RLR as hardware Watchdog (Option Bit IWDG1_SW = 0, OPT_SR_CUR Bit 4), or the
	//	Start has started it for a new Image on Trial (Update, Prescaler 6): a Reset sets PR to 0. The Application only has to refresh it
	const bool hardware = ((*MCU::FLASH_1::OPT_SR_CUR >> 4) & 0x1) == 0;
	if(hardware == true || (*MCU::IWDG::PR & 0x7) != 0)
	{
		m_running = true;
		
		//	Started for an Image on Trial, not by the Option Bit: Update::confirm() hands it over to CMOS (isAutomatic)
		m_trial = (hardware == false);
		const uint32 prescaler = *MCU::IWDG::PR & 0x7;
		m_timeout_ms = timeout_ms(prescaler > c_prescaler_max ? c_prescaler_max : prescaler, *MCU::IWDG::RLR & c_reload_max);
	}
	return(CMOS::get().set_watchdog(this));
}


feedback Watchdog::configure(uint32 prescaler, uint32 reload)
{
	//	Start (Key 0xCCCC, it also switches the LSI on), Write Access (0x5555), new Prescaler and Reload; they are taken over when the Update
	//	Flags in SR are cleared (some LSI Periods), then the Counter is reloaded with the new Value (0xAAAA)
	*MCU::IWDG::KR = 0xCCCC;
	*MCU::IWDG::KR = 0x5555;
	*MCU::IWDG::PR = prescaler;
	*MCU::IWDG::RLR = reload;
	for(uint32 i = 0; (*MCU::IWDG::SR & 0x7) != 0; i++)
	{
		if(i >= c_loops_update)
		{
			return(FAIL);
		}
	}
	*MCU::IWDG::KR = 0xAAAA;
	m_running = true;
	m_timeout_ms = timeout_ms(prescaler, reload);
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback Watchdog::start(uint32 timeout_ms)
{
	if(timeout_ms == 0 || timeout_ms > get_timeoutMaximum_ms())
	{
		return(FAIL);
	}
	
	
	//	The Application takes the Watchdog over: CMOS no longer refreshes it
	m_trial = false;
	m_automatic = false;
	
	
	//	The smallest Prescaler whose Reload Value reaches the Timeout gives the finest Steps; the Timeout is rounded up
	for(uint32 prescaler = 0; prescaler <= c_prescaler_max; prescaler++)
	{
		const uint32 period = 1000 * (4u << prescaler);
		const uint32 ticks = (timeout_ms * c_clock_lsi + period - 1) / period;
		if(ticks <= c_reload_max + 1)
		{
			return(configure(prescaler, ticks - 1));
		}
	}
	return(FAIL);
}


feedback Watchdog::refresh()
{
	if(m_running == false)
	{
		return(FAIL);
	}
	*MCU::IWDG::KR = 0xAAAA;
	return(OK);
}


bool Watchdog::isRunning() const
{
	return(m_running);
}


uint32 Watchdog::get_timeout_ms() const
{
	if(m_running == false)
	{
		return(0);
	}
	return(m_timeout_ms);
}


uint32 Watchdog::get_timeoutMaximum_ms() const
{
	//	Rounded down: start() reaches every Value up to here (e.g. 26214 ms at 40 kHz, the exact Maximum is 26214.4 ms)
	return(((c_reload_max + 1) * (4u << c_prescaler_max) * 1000) / c_clock_lsi);
}


bool Watchdog::wasLastResetCause() const
{
	return(m_resetByWatchdog);
}


bool Watchdog::isAutomatic() const
{
	return(m_automatic);
}
