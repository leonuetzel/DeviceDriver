#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback RTC::check_time(const Time& time)
{
	//	The Counter holds the Seconds since 2000-01-01 00:00:00 - the Years 2000 ... 2099 like the Calendar RTCs of the other Microcontrollers
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


uint32 RTC::get_seconds(const Time& time)
{
	//	Days since 2000-01-01: the full Years, the full Months of this Year, the Days of this Month
	uint32 days = 0;
	for(uint32 year = 2000; year < time.year; year++)
	{
		days += (is_leapYear(year) == true) ? 366 : 365;
	}
	for(uint32 month = 1; month < time.month; month++)
	{
		days += c_daysOfMonth[month - 1];
		if(month == 2 && is_leapYear(time.year) == true)
		{
			days++;
		}
	}
	days += time.day - 1;
	
	
	//	Up to the Year 2099 the Seconds fit into 32 Bit
	return(days * 86400 + time.hour * 3600 + time.minute * 60 + time.second);
}


Time RTC::get_time(uint32 seconds)
{
	Time time;
	time.second = seconds % 60;
	seconds /= 60;
	time.minute = seconds % 60;
	seconds /= 60;
	time.hour = seconds % 24;
	uint32 days = seconds / 24;
	
	
	//	Full Years since 2000
	uint16 year = 2000;
	while(1)
	{
		const uint32 daysOfYear = (is_leapYear(year) == true) ? 366 : 365;
		if(days < daysOfYear)
		{
			break;
		}
		days -= daysOfYear;
		year++;
	}
	
	
	//	Full Months of this Year
	uint8 month = 1;
	while(month < 12)
	{
		uint32 daysOfMonth = c_daysOfMonth[month - 1];
		if(month == 2 && is_leapYear(year) == true)
		{
			daysOfMonth++;
		}
		if(days < daysOfMonth)
		{
			break;
		}
		days -= daysOfMonth;
		month++;
	}
	
	time.year = year;
	time.month = month;
	time.day = days + 1;
	return(time);
}


bool RTC::is_enabled()
{
	//	RTCEN in RCC_BDCR - it belongs to the Backup Domain and keeps its Value over a Reset of the Microcontroller
	return(bit::isSet(*MCU::RCC::BDCR, 15));
}


bool RTC::enable_backupDomainWrite()
{
	//	The RTC Registers are write protected as long as DBP in PWR_CR is 0 - the previous State is restored afterwards
	const bool writeProtected = bit::isCleared(*MCU::PWR::CR, 8);
	bit::set(*MCU::PWR::CR, 8);
	return(writeProtected);
}


void RTC::restore_backupDomainWrite(bool writeProtected)
{
	if(writeProtected == true)
	{
		bit::clear(*MCU::PWR::CR, 8);
	}
}


feedback RTC::synchronize()
{
	//	After a Reset the APB Interface of the RTC has to be synchronized before the Registers can be read (RSF, RM0008 RTC)
	const bool writeProtected = enable_backupDomainWrite();
	bit::clear(*MCU::RTC::CRL, 3);
	restore_backupDomainWrite(writeProtected);
	
	CMOS& cmos = CMOS::get();
	const uint64 timestampStart = cmos.get_timestamp();
	while(bit::isCleared(*MCU::RTC::CRL, 3))
	{
		//	RSF comes with the next Edge of the RTC Clock - without a running RTC Clock never
		if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 100)
		{
			return(FAIL);
		}
	}
	m_synchronized = true;
	return(OK);
}


feedback RTC::enter_configurationMode(bool& writeProtected)
{
	writeProtected = enable_backupDomainWrite();
	
	
	//	Wait for the last Write Operation to complete (RTOFF), then enter the Configuration Mode
	CMOS& cmos = CMOS::get();
	const uint64 timestampStart = cmos.get_timestamp();
	while(bit::isCleared(*MCU::RTC::CRL, 5))
	{
		if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 100)
		{
			restore_backupDomainWrite(writeProtected);
			return(FAIL);
		}
	}
	bit::set(*MCU::RTC::CRL, 4);
	return(OK);
}


feedback RTC::exit_configurationMode(bool writeProtected)
{
	//	Leaving the Configuration Mode starts the Write Operation, it ends with RTOFF
	bit::clear(*MCU::RTC::CRL, 4);
	
	CMOS& cmos = CMOS::get();
	const uint64 timestampStart = cmos.get_timestamp();
	feedback result = OK;
	while(bit::isCleared(*MCU::RTC::CRL, 5))
	{
		if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 100)
		{
			result = FAIL;
			break;
		}
	}
	restore_backupDomainWrite(writeProtected);
	return(result);
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
	
	
	//	Reset of the Backup Domain, LSE and RCC_BDCR need the Write Access to the Backup Domain until init() returns
	struct BackupDomainAccess
	{
		const bool writeProtected;
		BackupDomainAccess() : writeProtected(RTC::enable_backupDomainWrite()) {}
		~BackupDomainAccess() { RTC::restore_backupDomainWrite(writeProtected); }
	} backupDomainAccess;
	
	
	//	Clock Source of the RTC that has been selected before (RTCSEL in RCC_BDCR, Backup Domain)
	STM32F107RCT6& stm32f107rct6 = STM32F107RCT6::get();
	RCC& rcc = stm32f107rct6.get_rcc();
	const uint32 clockSource_running = (*MCU::RCC::BDCR >> 8) & 0x00000003;
	const bool runningBefore = (clockSource_running == (uint32) clockSource && is_enabled() == true);
	
	
	//	The Clock Source can only be changed by a Reset of the Backup Domain, it also clears the Backup Registers
	if(clockSource_running != 0 && clockSource_running != (uint32) clockSource)
	{
		rcc.reset_backupDomain();
	}
	
	
	//	The selected Oscillator has to run: the RTC needs its Clock already for the Configuration
	//	A running LSE is kept, the LSI has to be started again after every Reset
	if(clockSource == RCC::e_clockSource_rtc::LSE && rcc.init_lse(true) != OK)
	{
		return(FAIL);
	}
	if(clockSource == RCC::e_clockSource_rtc::LSI && rcc.init_lsi(true) != OK)
	{
		return(FAIL);
	}
	
	
	//	Clock
	uint32 clock_in = 0;
	switch(clockSource)
	{
		case RCC::e_clockSource_rtc::LSE:
		{
			clock_in = RCC::c_clock_lse;
		}
		break;
		
		case RCC::e_clockSource_rtc::LSI:
		{
			clock_in = RCC::c_clock_lsi;
		}
		break;
		
		case RCC::e_clockSource_rtc::HSE_DIV128:
		{
			clock_in = rcc.get_clock_hse() / 128;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	//	PRL has 20 Bit: PRLH holds Bits 19:16, PRLL Bits 15:0
	if(clock_in == 0 || clock_in - 1 > 0x000FFFFF)
	{
		return(FAIL);
	}
	
	
	//	Select and enable the RTC Clock
	const bool writeProtected = enable_backupDomainWrite();
	rcc.set_clockSource(clockSource);
	rcc.set_rtc_clock(true);
	restore_backupDomainWrite(writeProtected);
	if(synchronize() != OK)
	{
		return(FAIL);
	}
	
	
	//	The Clock keeps running: same Clock Source and enabled - only init() enables the RTC (the Prescaler can not be read back)
	if(runningBefore == true)
	{
		return(OK);
	}
	
	
	//	Set the Prescaler and the Time
	bool writeProtected_2 = false;
	if(enter_configurationMode(writeProtected_2) != OK)
	{
		return(FAIL);
	}
	*MCU::RTC::PRLH = ((clock_in - 1) >> 16) & 0x0000000F;
	*MCU::RTC::PRLL = (clock_in - 1) & 0x0000FFFF;
	
	const uint32 seconds = get_seconds(time);
	*MCU::RTC::CNTH = (seconds >> 16) & 0x0000FFFF;
	*MCU::RTC::CNTL = seconds & 0x0000FFFF;
	
	//  Clear the Flags of Overflow, Alarm and Second
	bit::clear(*MCU::RTC::CRL, 2);
	bit::clear(*MCU::RTC::CRL, 1);
	bit::clear(*MCU::RTC::CRL, 0);
	return(exit_configurationMode(writeProtected_2));
}


feedback RTC::set_time(Time time)
{
	if(check_time(time) != OK || is_enabled() == false)
	{
		return(FAIL);
	}
	
	
	const uint32 seconds = get_seconds(time);
	bool writeProtected = false;
	if(enter_configurationMode(writeProtected) != OK)
	{
		return(FAIL);
	}
	*MCU::RTC::CNTH = (seconds >> 16) & 0x0000FFFF;
	*MCU::RTC::CNTL = seconds & 0x0000FFFF;
	return(exit_configurationMode(writeProtected));
}


Time RTC::read()
{
	//	A Time with the Year 0 is invalid: the RTC is not running
	const Time invalid(0, 0, 0, 0, 0, 0);
	if(is_enabled() == false || (m_synchronized == false && synchronize() != OK))
	{
		return(invalid);
	}
	
	
	//	The Counter is read in two Halves: if the high Half changes in between, the low Half is read again
	uint32 high = *MCU::RTC::CNTH & 0x0000FFFF;
	uint32 low = *MCU::RTC::CNTL & 0x0000FFFF;
	const uint32 high_2 = *MCU::RTC::CNTH & 0x0000FFFF;
	if(high_2 != high)
	{
		high = high_2;
		low = *MCU::RTC::CNTL & 0x0000FFFF;
	}
	return(get_time((high << 16) | low));
}


feedback RTC::set_alarm(Time time)
{
	//	The Alarm compares the full Counter, so Date and Time are part of the Comparison
	if(check_time(time) != OK || is_enabled() == false)
	{
		return(FAIL);
	}
	
	
	const uint32 seconds = get_seconds(time);
	bool writeProtected = false;
	if(enter_configurationMode(writeProtected) != OK)
	{
		return(FAIL);
	}
	*MCU::RTC::ALRH = (seconds >> 16) & 0x0000FFFF;
	*MCU::RTC::ALRL = seconds & 0x0000FFFF;
	
	//	Clear the Alarm Flag and enable the Alarm Interrupt
	bit::clear(*MCU::RTC::CRL, 1);
	bit::set(*MCU::RTC::CRH, 1);
	if(exit_configurationMode(writeProtected) != OK)
	{
		return(FAIL);
	}
	
	
	//	The Alarm reaches the Interrupt over EXTI Line 17 (rising Edge), an old pending Event is cleared first
	bit::set(*MCU::EXTI::RTSR, 17);
	bit::clear(*MCU::EXTI::FTSR, 17);
	*MCU::EXTI::PR = 1 << 17;
	bit::set(*MCU::EXTI::IMR, 17);
	
	NVIC& nvic = CMOS::get().get_nvic();
	nvic.setPriority(Interrupt::RTC_ALARM_EXTI, 10);
	nvic.enable(Interrupt::RTC_ALARM_EXTI);
	return(OK);
}


feedback RTC::disable_alarm()
{
	//	Mask the EXTI Line first, so that no Alarm comes while the Alarm is disabled
	bit::clear(*MCU::EXTI::IMR, 17);
	
	
	//	Disable the Alarm Interrupt of the RTC
	const bool writeProtected = enable_backupDomainWrite();
	bit::clear(*MCU::RTC::CRH, 1);
	restore_backupDomainWrite(writeProtected);
	return(OK);
}










void ISR_RTC_ALARM_EXTI()
{
	//	Alarm
	if(bit::isSet(*MCU::RTC::CRL, 1) == true)
	{
		//	Clear the Alarm Flag (rc_w0), the Backup Domain must be writable for it
		const bool writeProtected = RTC::enable_backupDomainWrite();
		bit::clear(*MCU::RTC::CRL, 1);
		RTC::restore_backupDomainWrite(writeProtected);
		
		
		//	Notify the Threads - the Alarm comes once, the Counter passes the Alarm Value only once
		RTC& rtc = STM32F107RCT6::get().get_rtc();
		CMOS::get().event_emit(rtc.m_eventID_alarm);
	}
	
	
	//	Clear the pending EXTI Line 17 - after the Flag of the RTC, else the Line would be pending again
	*MCU::EXTI::PR = 1 << 17;
}
