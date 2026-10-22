#include "../Inc/stm32l010k8t6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback RTC::startup()
{
	//	The Backup Domain is not reset: the RTC keeps running over a Reset of the Microcontroller, init() only sets it if necessary
	m_eventID_alarm = CMOS::get().event_create();
	return(OK);
}


feedback RTC::check_time(const Time& time)
{
	//	The Date Register holds the Years 2000 ... 2099 and a Weekday (0 is forbidden), so the Date must be valid
	if(time.get_weekday() == Time::e_weekday::INVALID || time.year < 2000 || time.year > 2099)
	{
		return(FAIL);
	}
	if(time.hour > 23 || time.minute > 59 || time.second > 59)
	{
		return(FAIL);
	}
	return(OK);
}


feedback RTC::calculate_prescaler(uint32 clock, uint32& prescaler_async, uint32& prescaler_sync)
{
	//	1 Hz for the Calendar: clock = (PREDIV_A + 1) * (PREDIV_S + 1) with PREDIV_A + 1 up to 128 and PREDIV_S + 1 up to 32768
	//	A high asynchronous Prescaler saves Power, so the largest Divider without Remainder is taken (LSE 32768 Hz: 128 * 256)
	for(uint32 divider_async = 128; divider_async > 0; divider_async--)
	{
		if(clock % divider_async == 0 && clock / divider_async <= 32768)
		{
			prescaler_async = divider_async - 1;
			prescaler_sync = clock / divider_async - 1;
			return(OK);
		}
	}
	
	
	//	No exact Divider: the asynchronous Prescaler divides by 128 and the synchronous one is rounded
	const uint32 divider_sync = (clock + 64) / 128;
	if(divider_sync == 0 || divider_sync > 32768)
	{
		return(FAIL);
	}
	prescaler_async = 127;
	prescaler_sync = divider_sync - 1;
	return(OK);
}


bool RTC::is_enabled()
{
	//	RTCEN in RCC_CSR - it belongs to the Backup Domain and keeps its Value over a Reset of the Microcontroller
	return(bit::isSet(*MCU::RCC::CSR, 18));
}


feedback RTC::enter_initializationMode()
{
	//	Unlock the Write Protection of the RTC Registers
	*MCU::RTC::WPR = 0x000000CA;
	*MCU::RTC::WPR = 0x00000053;
	
	
	//	Enter the Initialization Mode: the Calendar stops until the Mode is left, INITF tells that the Registers can be written
	bit::set(*MCU::RTC::ISR, 7);
	CMOS& cmos = CMOS::get();
	const uint64 timestampStart = cmos.get_timestamp();
	while(bit::isCleared(*MCU::RTC::ISR, 6))
	{
		//	INITF comes after at most 2 Cycles of the RTC Clock - without a running RTC Clock never
		if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 100)
		{
			exit_initializationMode();
			return(FAIL);
		}
	}
	return(OK);
}


void RTC::exit_initializationMode()
{
	//	Leave the Initialization Mode, the Calendar starts again after 4 Cycles of the RTC Clock
	bit::clear(*MCU::RTC::ISR, 7);
	
	
	//	Lock the Write Protection of the RTC Registers
	*MCU::RTC::WPR = 0x000000FF;
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback RTC::init(RCC::e_clockSource_rtc clockSource, Time time)
{
	if(clockSource == RCC::e_clockSource_rtc::NONE || check_time(time) != OK)
	{
		return(FAIL);
	}
	
	
	//	Clock Source of the RTC that has been selected before (RTCSEL in RCC_CSR, Backup Domain)
	STM32L010K8T6& stm32l010k8t6 = STM32L010K8T6::get();
	RCC& rcc = stm32l010k8t6.get_rcc();
	const uint32 clockSource_running = ((*MCU::RCC::CSR) >> 16) & 0x00000003;
	
	
	//	The Clock Source can only be changed by a Reset of the Backup Domain, it sets the whole RTC to its Reset Values
	if(clockSource_running != 0 && clockSource_running != (uint32) clockSource)
	{
		rcc.reset_backupDomain();
	}
	
	
	//	The selected Oscillator has to run: the RTC needs its Clock already for the Configuration
	//	A running LSE is kept, the LSI has to be started again after every Reset
	if(clockSource == RCC::e_clockSource_rtc::LSE && rcc.LSE_init(true) != OK)
	{
		return(FAIL);
	}
	if(clockSource == RCC::e_clockSource_rtc::LSI && rcc.LSI_init(true) != OK)
	{
		return(FAIL);
	}
	
	
	//	Select and enable the RTC Clock - for a running RTC this only brings the RCC Driver up to date
	const bool runningBefore = (clockSource_running == (uint32) clockSource && is_enabled() == true);
	rcc.set_clockSource(clockSource, true);
	
	
	//	Prescaler for 1 Hz
	uint32 prescaler_async = 0;
	uint32 prescaler_sync = 0;
	if(calculate_prescaler(rcc.get_clock_rtc(), prescaler_async, prescaler_sync) != OK)
	{
		return(FAIL);
	}
	const uint32 prer = (prescaler_async << 16) | prescaler_sync;
	
	
	//	The Clock keeps running: same Clock Source, enabled and with the same Prescaler - only init() sets these
	if(runningBefore == true && (*MCU::RTC::PRER & 0x007F7FFF) == prer)
	{
		return(OK);
	}
	
	
	//	Set the Prescaler and the Time
	if(enter_initializationMode() != OK)
	{
		return(FAIL);
	}
	
	//	The synchronous Prescaler has to be written first, then the asynchronous one (two separate Write Accesses)
	*MCU::RTC::PRER = prescaler_sync;
	*MCU::RTC::PRER = prer;
	
	//	Time Format 24h
	bit::clear(*MCU::RTC::CR, 6);
	
	exit_initializationMode();
	
	return(set_time(time));
}


feedback RTC::set_time(Time time)
{
	if(check_time(time) != OK || is_enabled() == false)
	{
		return(FAIL);
	}
	
	
	//	Time Register (BCD)
	uint32 tr = 0;
	tr |= ((time.hour		/ 10) << 20);
	tr |= ((time.hour		% 10) << 16);
	tr |= ((time.minute / 10) << 12);
	tr |= ((time.minute % 10) << 8);
	tr |= ((time.second / 10) << 4);
	tr |= ( time.second % 10);
	
	
	//	Date Register (BCD), the Weekday is calculated from the full Year, before 2000 is subtracted
	const Time::e_weekday weekday = time.get_weekday();
	const uint32 year = time.year - 2000;
	uint32 dr = 0;
	dr |= ((year				/ 10) << 20);
	dr |= ((year				% 10) << 16);
	dr |= (((uint32) weekday)	<< 13);
	dr |= ((time.month	/ 10) << 12);
	dr |= ((time.month	% 10) << 8);
	dr |= ((time.day		/ 10) << 4);
	dr |= ( time.day		% 10);
	
	
	if(enter_initializationMode() != OK)
	{
		return(FAIL);
	}
	*MCU::RTC::TR = tr;
	*MCU::RTC::DR = dr;
	exit_initializationMode();
	
	
	//	The Initialization Mode has cleared RSF: read() waits until the Shadow Registers show the new Time
	return(OK);
}


Time RTC::read()
{
	//	A Time with the Year 0 is invalid: the RTC is not running
	const Time invalid(0, 0, 0, 0, 0, 0);
	if(is_enabled() == false)
	{
		return(invalid);
	}
	
	
	//	The Shadow Registers are synchronized with the Calendar every Second Clock Cycle of the RTC (RSF) - after a Reset not yet
	CMOS& cmos = CMOS::get();
	const uint64 timestampStart = cmos.get_timestamp();
	while(bit::isCleared(*MCU::RTC::ISR, 5))
	{
		if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 10)
		{
			return(invalid);
		}
	}
	
	
	//	Reading TR locks DR until it is read, so both belong to the same Second
	const uint32 tr = *MCU::RTC::TR;
	const uint32 dr = *MCU::RTC::DR;
	
	Time time;
	time.year		= ((dr & 0x00F00000) >> 20) * 10 + ((dr & 0x000F0000) >> 16) + 2000;
	time.month	= ((dr & 0x00001000) >> 12) * 10 + ((dr & 0x00000F00) >> 8);
	time.day		= ((dr & 0x00000030) >> 4 ) * 10 +  (dr & 0x0000000F);
	time.hour		= ((tr & 0x00300000) >> 20) * 10 + ((tr & 0x000F0000) >> 16);
	time.minute	= ((tr & 0x00007000) >> 12) * 10 + ((tr & 0x00000F00) >> 8);
	time.second	= ((tr & 0x00000070) >> 4 ) * 10 +  (tr & 0x0000000F);
	return(time);
}


feedback RTC::set_alarm(Time time)
{
	//	Alarm A compares Day of the Month, Hour, Minute and Second - Month and Year are not part of the Comparison
	if(check_time(time) != OK || is_enabled() == false)
	{
		return(FAIL);
	}
	
	
	//	Unlock the Write Protection of the RTC Registers
	*MCU::RTC::WPR = 0x000000CA;
	*MCU::RTC::WPR = 0x00000053;
	
	
	//	Disable Alarm A, ALRAWF tells that ALRMAR can be written
	bit::clear(*MCU::RTC::CR, 8);
	CMOS& cmos = CMOS::get();
	const uint64 timestampStart = cmos.get_timestamp();
	while(bit::isCleared(*MCU::RTC::ISR, 0))
	{
		if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 100)
		{
			*MCU::RTC::WPR = 0x000000FF;
			return(FAIL);
		}
	}
	
	
	//	All Masks (MSK1 ... MSK4) cleared, WDSEL = 0: Day of the Month
	uint32 alrmar = 0;
	alrmar |= ((time.day		/ 10) << 28);
	alrmar |= ((time.day		% 10) << 24);
	alrmar |= ((time.hour		/ 10) << 20);
	alrmar |= ((time.hour		% 10) << 16);
	alrmar |= ((time.minute / 10) << 12);
	alrmar |= ((time.minute % 10) << 8);
	alrmar |= ((time.second / 10) << 4);
	alrmar |= ( time.second % 10);
	*MCU::RTC::ALRMAR = alrmar;
	
	
	//	Clear the Alarm Flag (rc_w0, INIT stays 0), enable the Alarm and its Interrupt
	*MCU::RTC::ISR = ~((uint32) ((1 << 8) | (1 << 7)));
	bit::set(*MCU::RTC::CR, 12);
	bit::set(*MCU::RTC::CR, 8);
	
	
	//	Lock the Write Protection of the RTC Registers
	*MCU::RTC::WPR = 0x000000FF;
	
	
	//	The Alarm reaches the Interrupt over EXTI Line 17 (rising Edge), an old pending Event is cleared first
	EXTI& exti = STM32L010K8T6::get().get_exti();
	exti.clear_pendingBit(EXTI::e_line::RTC_ALARM);
	exti.init_interrupt_internal(EXTI::e_line::RTC_ALARM, true);
	
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::RTC, 10);
	nvic.enable(Interrupt::RTC);
	return(OK);
}


feedback RTC::disable_alarm()
{
	//	Mask the EXTI Line first, so that no Alarm comes while the Alarm is disabled
	EXTI& exti = STM32L010K8T6::get().get_exti();
	exti.init_interrupt_internal(EXTI::e_line::RTC_ALARM, false);
	
	
	//	Disable Alarm A and its Interrupt
	*MCU::RTC::WPR = 0x000000CA;
	*MCU::RTC::WPR = 0x00000053;
	bit::clear(*MCU::RTC::CR, 12);
	bit::clear(*MCU::RTC::CR, 8);
	*MCU::RTC::WPR = 0x000000FF;
	return(OK);
}










void ISR_RTC()
{
	//	Alarm A
	if(bit::isSet(*MCU::RTC::ISR, 8) == true)
	{
		//	Clear the Alarm Flag: RTC_ISR[13:8] are not write protected, INIT stays 0
		*MCU::RTC::ISR = ~((uint32) ((1 << 8) | (1 << 7)));
		
		
		//	The Alarm comes once: the EXTI Line is masked, set_alarm unmasks it again
		//	Without this, the Alarm would come again every Month, when Day, Hour, Minute and Second match
		bit::clear(*MCU::EXTI::IMR, 17);
		
		
		//	Notify the Threads
		RTC& rtc = STM32L010K8T6::get().get_rtc();
		CMOS::get().event_emit(rtc.m_eventID_alarm);
	}
	
	
	//	Clear the pending EXTI Line 17 - after the Flag of the RTC, else the Line would be pending again
	*MCU::EXTI::PR = 1 << 17;
}
