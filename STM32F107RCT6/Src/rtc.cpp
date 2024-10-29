#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void RTC::set_alarm(uint32 value)
{
	enter();
	*MCU::RTC::ALRH = value & 0xFFFF0000;
	*MCU::RTC::ALRL = value & 0x0000FFFF;
	exit();
}


void RTC::enter()
{
	//	Disable Backup Domain Write Protection
	STM32F107RCT6::get().get_pwr().set_backupDomain_writeProtection(false);
	
	
	//  Wait for last Operation to complete
	while(bit::isCleared(*MCU::RTC::CRL, 5))
	{
		
	}
	
	
	//  Enter Configuration Mode
	bit::set(*MCU::RTC::CRL, 4);
}


void RTC::exit()
{
	//  Wait for last Operation to complete
	while(bit::isCleared(*MCU::RTC::CRL, 5))
	{
		
	}
	
	
	//  Exit Configuration Mode
	bit::clear(*MCU::RTC::CRL, 4);
	
	
	//	Enable Backup Domain Write Protection
	STM32F107RCT6::get().get_pwr().set_backupDomain_writeProtection(true);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback RTC::init(RCC::e_clockSource_rtc clockSource)
{
	//	Enter Configuration Mode
	enter();
	
	
	//	Reset Backup Domain
	STM32F107RCT6& stm32f107rct6 = STM32F107RCT6::get();
	RCC& rcc = stm32f107rct6.get_rcc();
	rcc.reset_backupDomain();
	
	
	//	Clock Source
	rcc.set_clockSource(clockSource);
	rcc.set_rtc_clock(true);
	
	
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
	
	
	//	Prescaler
	if(clock_in > 0x0003FFFF)
	{
		return(FAIL);
	}
	
	*MCU::RTC::PRLH = (clock_in - 1) & 0x00030000;
	*MCU::RTC::PRLL = (clock_in - 1) & 0x0000FFFF;
	
	*MCU::RTC::CNTH = 1 & 0xFFFF0000;
	*MCU::RTC::CNTL = 1 & 0x0000FFFF;
	
	
	//  Clear Pending Flags
	bit::clear(*MCU::RTC::CRL, 2);
	bit::clear(*MCU::RTC::CRL, 1);
	bit::clear(*MCU::RTC::CRL, 0);
	
	
	//	Enable Second Interrupt
	bit::set(*MCU::RTC::CRH, 0);
	
	
	//  Enable RTC
	bit::set(*MCU::RCC::BDCR, 15);
	
	
	//	Exit Configuration Mode
	exit();
	
	
	return(OK);
}