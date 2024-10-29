#include "../Inc/stm32f030f4p6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback RTC::startup()
{
	//	Reset Backup Domain
	STM32F030F4P6::get().get_rcc().reset_backupDomain();
	
	
	//	Unlock Write Protection of RTC Registers
	*MCU::RTC::WPR = 0x000000CA;
	*MCU::RTC::WPR = 0x00000053;
	
	return(OK);
}







void RTC::set_alarm()
{
	while(bit::isCleared(*MCU::RTC::ISR, 5))
	{
		
	}
	
	uint32 time_reg = *MCU::RTC::TR;
	uint32 second_tens = (time_reg & 0x00000070) >> 4;
	uint32 second_units = time_reg & 0x0000000F;
	
	bit::clear(*MCU::RTC::CR, 8);																																																								//	Disable Alarm A
	while(bit::isCleared(*MCU::RTC::ISR, 0))
	{
		
	}
	
	
	second_units++;
	if(second_units > 9)
	{
		second_units = 0;
		second_tens++;
		if(second_tens > 5)
		{
			second_tens = 0;
		}
	}
	*MCU::RTC::ALRMAR = 0x80808000 | (second_tens << 4) | second_units;
	
	bit::set(*MCU::RTC::CR, 8);																																																								//	Enable Alarm A																																				//	Enable Alarm A
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback RTC::init(RCC::e_clockSource_rtc clockSource, Time time)
{
	//	Clock Source
	STM32F030F4P6& stm32f030f4p6 = STM32F030F4P6::get();
	RCC& rcc = stm32f030f4p6.get_rcc();
	rcc.set_clockSource(clockSource, true);
	
	
	//	Input Clock
	const uint32 clock_in = rcc.get_clock_rtc();
	
	
	//	Enter RTC Initialization Mode
	bit::set(*MCU::RTC::ISR, 7);
	while(bit::isCleared(*MCU::RTC::ISR, 6))
	{
		
	}
	
	
	
	uint32 prescaler_async = clock_in;
	uint32 prescaler_sync = 1;
	if(prescaler_async > 128)
	{
		prescaler_async = 128;
		prescaler_sync = clock_in / prescaler_async;
		if(prescaler_sync > 32768)
		{
			return(FAIL);
		}
	}
	prescaler_async--;
	prescaler_sync--;
	*MCU::RTC::PRER = (prescaler_async << 16);
	*MCU::RTC::PRER |= prescaler_sync;
	
	
	//	Time Register
	uint32 temp = 0;
	temp |= ((time.hour		/ 10) << 20);
	temp |= ((time.hour		% 10) << 16);
	temp |= ((time.minute / 10) << 12);
	temp |= ((time.minute % 10) << 8);
	temp |= ((time.second / 10) << 4);
	temp |= ( time.second % 10);
	*MCU::RTC::TR = temp;
	
	
	//	Date Register
	time.year -= 2000;
	
	temp = 0;
	temp |= ((time.year								/ 10) << 20);
	temp |= ((time.year								% 10) << 16);
	temp |= (((uint32) time.get_weekday())	<< 13);
	temp |= ((time.month							/ 10) << 12);
	temp |= ((time.month							% 10) << 8);
	temp |= ((time.day								/ 10) << 4);
	temp |= ( time.day								% 10);
	*MCU::RTC::DR = temp;
	
	
	//	Time Format 24h
	bit::clear(*MCU::RTC::CR, 6);
	
	
	//	Exit RTC Initialisation Mode
	bit::clear(*MCU::RTC::ISR, 7);
	
	
	
	
	
	set_alarm();
	
	
	//	Enable Alarm A Interrupt
	bit::set(*MCU::RTC::CR, 12);
	EXTI& exti = stm32f030f4p6.get_exti();
	exti.init_interrupt_internal(EXTI::e_line::RTC_ALARM, true);
	
	
	
	return(OK);
}







Time RTC::read()
{
	while(bit::isCleared(*MCU::RTC::ISR, 5))
	{
		
	}
	
	uint32 time_reg = *MCU::RTC::TR;
	uint32 date_reg = *MCU::RTC::DR;
	
	Time time;
	time.year			= ((date_reg & 0x00F00000) >> 20) * 10 + ((date_reg & 0x000F0000) >> 16) + 2000;
	time.month		= ((date_reg & 0x00001000) >> 12) * 10 + ((date_reg & 0x00000F00) >> 8);
	time.day			= ((date_reg & 0x00000030) >> 4 ) * 10 +  (date_reg & 0x0000000F);
	//time.weekday	= (e_weekday) ((date_reg & 0x0000E000) >> 13);
	
	time.hour			= ((time_reg & 0x00300000) >> 20) * 10 + ((time_reg & 0x000F0000) >> 16);
	time.minute		= ((time_reg & 0x00007000) >> 12) * 10 + ((time_reg & 0x00000F00) >> 8);
	time.second		= ((time_reg & 0x00000070) >> 4 ) * 10 +  (time_reg & 0x0000000F);
	
	return(time);
}