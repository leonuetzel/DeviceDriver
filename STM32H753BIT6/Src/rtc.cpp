#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback RTC::startup()
{
	return(OK);
}







feedback RTC::initClock(e_clockSource clockSource, Time time)
{
	RCC& m_rcc = STM32H753BIT6::get().get_rcc();
	m_rcc.module_clockInit(RCC::e_module::RTC, true);
	
	
	//	Disable Write Protection of Backup Domain
	bit::set(*MCU::PWR::CR1, 8);
	
	
	//	Select Clock Source
	*MCU::RCC::BDCR &= 0xFFFFFCFF;
	switch(clockSource)
	{
		case e_clockSource::LSE:
		{
			*MCU::RCC::BDCR |= 0x00000100;
			m_clockIn = RCC::c_clock_lse;
		}
		break;
			
		case e_clockSource::LSI:
		{
			*MCU::RCC::BDCR |= 0x00000200;
			m_clockIn = m_rcc.c_clock_lsi;
		}
		break;
			
		case e_clockSource::HSE:
		{
			*MCU::RCC::CFGR &= (0xFFFFFFFF - (0x3F << 8));
			*MCU::RCC::CFGR |= (0x8 << 8);
			*MCU::RCC::BDCR |= 0x00000300;
			m_clockIn = RCC::c_clock_hse / 0x8;
		}
		break;
			
		default:
		{
			return(FAIL);
		}
		break;
	}
	
	
	//	Enable RTC Clock
	bit::set(*MCU::RCC::BDCR, 15);
	m_clockSource = clockSource;
	
	
	//	Unlock Write Protection of RTC Registers
	*MCU::RTC::WPR = 0x000000CA;
	*MCU::RTC::WPR = 0x00000053;
	
	
	//	Enter RTC Initialisation Mode
	bit::set(*MCU::RTC::ISR, 7);
	while(bit::isCleared(*MCU::RTC::ISR, 6))
	{
		
	}
	
	
	
	
	*MCU::RTC::PRER = (99 << 16);
	*MCU::RTC::PRER |= 9999;
	
	uint32 year = time.year - 2000;
	*MCU::RTC::TR = ((time.hour / 10) << 20) | ((time.hour % 10) << 16) | ((time.minute / 10) << 12) | ((time.minute % 10) << 8) | ((time.second / 10) << 4) | (time.second % 10);
	*MCU::RTC::DR = ((year / 10) << 20) | ((year % 10) << 16) | (((uint32) (time.get_weekday())) << 13) | ((time.month / 10) << 12) | ((time.month % 10) << 8) | ((time.day / 10) << 4) | (time.day % 10);
	
	
	//	Time Format 24h
	bit::clear(*MCU::RTC::CR, 6);
	
	
	//	Exit RTC Initialisation Mode
	bit::clear(*MCU::RTC::ISR, 7);
	
	
	
	set_alarm();
	
	
	//	Enable Alarm A Interrupt
	bit::set(*MCU::RTC::CR, 12);
	
	
	//	Enable Rising Trigger
	bit::set(*MCU::EXTI::RTSR1, 17);
	
	
	//	Disable Falling Trigger
	bit::clear(*MCU::EXTI::FTSR1, 17);
	
	
	//	Unmask ISR_RTC_ALARM_EXTI Interrupt
	bit::set(*MCU::EXTI::CPUIMR1, 17);
	
	
	//	Lock Write Protection of RTC Registers
	*MCU::RTC::WPR = 0x000000FF;
	
	
	//	Enable Write Protection of Backup Domain
	//bit::clear(*MCU::PWR::CR1, 8);
	return(OK);
}


void RTC::set_alarm()
{
	Time time(read());
	
	//	Disable Write Protection of Backup Domain
	bit::set(*MCU::PWR::CR1, 8);
	
	
	//	Unlock Write Protection of RTC Registers
	*MCU::RTC::WPR = 0x000000CA;
	*MCU::RTC::WPR = 0x00000053;
	
	
	//	Disable Alarm A
	bit::clear(*MCU::RTC::CR, 8);
	
	
	//	Clear Alarm A Flag
	bit::clear(*MCU::RTC::ISR, 8);
	
	while(bit::isCleared(*MCU::RTC::ISR, 0))
	{
		
	}
	
	time++;
	uint32 seconds_tens = time.second / 10;
	uint32 seconds_units = time.second % 10;
	*MCU::RTC::ALRMAR = 0x80808000 | (seconds_tens << 4) | seconds_units;
	
	
	//	Enable Alarm A
	bit::set(*MCU::RTC::CR, 8);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

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