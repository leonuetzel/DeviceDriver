#include "../Inc/rtc.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback RTC::initClock(e_clockSource clockSource, Time time)
{
	m_rcc.module_clockInit(RCC::e_module::RTC, true);
	
	bit::set(*MCU::PWR::CR1, 8);																																																	//	Disable Write Protection of Backup Domain
	
	*MCU::RCC::BDCR &= 0xFFFFFCFF;																																																//	Select Clock Source
	switch(clockSource)
	{
		case e_clockSource::LSE:
			*MCU::RCC::BDCR |= 0x00000100;
			m_clockIn = RCC::c_clock_lse;
			break;
			
		case e_clockSource::LSI:
			*MCU::RCC::BDCR |= 0x00000200;
			m_clockIn = m_rcc.c_clock_lsi;
			break;
			
		case e_clockSource::HSE:
			*MCU::RCC::CFGR &= (0xFFFFFFFF - (0x3F << 8));
			*MCU::RCC::CFGR |= (0x8 << 8);
			*MCU::RCC::BDCR |= 0x00000300;
			m_clockIn = RCC::c_clock_hse / 0x8;
			break;
			
		default:
			return(FAIL);
	}
	
	bit::set(*MCU::RCC::BDCR, 15);																																																//	Enable RTC Clock
	m_clockSource = clockSource;
	
	*MCU::RTC::WPR = 0x000000CA;																																																	//	Unlock Write Protection of RTC Registers
	*MCU::RTC::WPR = 0x00000053;
	
	bit::set(*MCU::RTC::ISR, 7);																																																	//	Enter RTC Initialisation Mode
	while(bit::isCleared(*MCU::RTC::ISR, 6))
	{
		
	}
	
	
	
	
	*MCU::RTC::PRER = (99 << 16);
	*MCU::RTC::PRER |= 9999;
	
	uint32 year = time.year - 2000;
	*MCU::RTC::TR = ((time.hour / 10) << 20) | ((time.hour % 10) << 16) | ((time.minute / 10) << 12) | ((time.minute % 10) << 8) | ((time.second / 10) << 4) | (time.second % 10);
	*MCU::RTC::DR = ((year / 10) << 20) | ((year % 10) << 16) | (((uint32) (time.get_weekday())) << 13) | ((time.month / 10) << 12) | ((time.month % 10) << 8) | ((time.day / 10) << 4) | (time.day % 10);
	
	bit::clear(*MCU::RTC::CR, 6);																																																	//	Time Format 24h
	
	bit::clear(*MCU::RTC::ISR, 7);																																																//	Exit RTC Initialisation Mode
	
	set_alarm();
	bit::set(*MCU::RTC::CR, 12);																																																	//	Enable Alarm A Interrupt
	bit::set(*MCU::EXTI::RTSR1, 17);																																															//	Enable Rising Trigger
	bit::clear(*MCU::EXTI::FTSR1, 17);																																														//	Disable Falling Trigger
	bit::set(*MCU::EXTI::CPUIMR1, 17);																																														//	Unmask *MCU::RTC::ALARM_EXTI Interrupt
	
	
	*MCU::RTC::WPR = 0x000000FF;																																																	//	Lock Write Protection of RTC Registers
	//bit::clear(*MCU::PWR::CR1, 8);																																															//	Enable Write Protection of Backup Domain
	
	
	
	return(OK);
}


void RTC::set_alarm()
{
	Time time(read());
	
	bit::set(*MCU::PWR::CR1, 8);																																																	//	Disable Write Protection of Backup Domain
	
	*MCU::RTC::WPR = 0x000000CA;																																																	//	Unlock Write Protection of RTC Registers
	*MCU::RTC::WPR = 0x00000053;
	
	bit::clear(*MCU::RTC::CR, 8);																																																	//	Disable Alarm A
	bit::clear(*MCU::RTC::ISR, 8);																																																//	Clear Alarm A Flag
	
	while(bit::isCleared(*MCU::RTC::ISR, 0))
	{
		
	}
	
	time++;
	uint32 seconds_tens = time.second / 10;
	uint32 seconds_units = time.second % 10;
	*MCU::RTC::ALRMAR = 0x80808000 | (seconds_tens << 4) | seconds_units;
	
	bit::set(*MCU::RTC::CR, 8);																																																		//	Enable Alarm A																																				//	Enable Alarm A
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback RTC::startup()
{
	return(OK);
}







CODE_RAM Time RTC::read()
{
	while(bit::isCleared(*MCU::RTC::ISR, 5))
	{
		
	}
	
	uint32 time_1 = *MCU::RTC::TR;
	uint32 date_1 = *MCU::RTC::DR;
	
	bit::clear(*MCU::RTC::ISR, 5);
	while(bit::isCleared(*MCU::RTC::ISR, 5))
	{
		
	}
	
	uint32 time_2 = *MCU::RTC::TR;
	uint32 date_2 = *MCU::RTC::DR;
	
	if(time_1 != time_2 || date_1 != date_2)
	{
		return(Time(0, 0, 0, 0, 0, 0));
	}
	
	uint16 year		= ((date_1 & 0x00F00000) >> 20) * 10 + ((date_1 & 0x000F0000) >> 16) + 2000;
	uint8 month		= ((date_1 & 0x00001000) >> 12) * 10 + ((date_1 & 0x00000F00) >> 8);
	uint8 day			= ((date_1 & 0x00000030) >> 4 ) * 10 +  (date_1 & 0x0000000F);
	//time.weekday	= (e_weekday) ((date_1 & 0x0000E000) >> 13);
	
	uint8 hour		= ((time_1 & 0x00300000) >> 20) * 10 + ((time_1 & 0x000F0000) >> 16);
	uint8 minute	= ((time_1 & 0x00007000) >> 12) * 10 + ((time_1 & 0x00000F00) >> 8);
	uint8 second	= ((time_1 & 0x00000070) >> 4 ) * 10 +  (time_1 & 0x0000000F);
	
	return(Time(second, minute, hour, day, month, year));
}