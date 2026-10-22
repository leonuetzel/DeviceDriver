#include "../Inc/stm32f103c8t6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback RCC::set_busPrescaler()
{
	uint32 divider_ahb = 1;
	uint32 divider_apb1 = 1;
	uint32 divider_apb2 = 1;
	
	
	
	uint32 mask_ahb = 0x7;																																																			//	AHB Prescaler
	while(m_clock_system / divider_ahb > c_clock_ahb_max)
	{
		divider_ahb *= 2;
		mask_ahb++;
		if(divider_ahb == 32)
		{
			divider_ahb *= 2;
		}
		if(divider_ahb > 512)
		{
			return(FAIL);
		}
	}
	
	
	
	uint32 mask_apb1 = 0x3;																																																			//	APB1 Prescaler
	while(m_clock_system / divider_apb1 > c_clock_apb1_max)
	{
		divider_apb1 *= 2;
		mask_apb1++;
		if(divider_apb1 > 16)
		{
			return(FAIL);
		}
	}
	
	
	
	uint32 mask_apb2 = 0x3;																																																			//	APB2 Prescaler
	while(m_clock_system / divider_apb2 > c_clock_apb2_max)
	{
		divider_apb2 *= 2;
		mask_apb2++;
		if(divider_apb2 > 16)
		{
			return(FAIL);
		}
	}
	
	
	
	
	
	m_clock_ahb = m_clock_system / divider_ahb;
	
	m_clock_apb1 = m_clock_system / divider_apb1;
	m_clock_apb1_timer = m_clock_apb1;
	if(divider_apb1 != 1)
	{
		m_clock_apb1_timer *= 2;
	}
	
	m_clock_apb2 = m_clock_system / divider_apb2;
	m_clock_apb2_timer = m_clock_apb2;
	if(divider_apb2 != 1)
	{
		m_clock_apb2_timer *= 2;
	}
	
	
	
	uint32 temp = *MCU::RCC::CFGR & 0xFFFFC00F;
	*MCU::RCC::CFGR = temp | (mask_ahb << 4) | (mask_apb1 << 8) | (mask_apb2 << 11);
	
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback RCC::HSE_init(bool enable)
{
	if(enable == true)
	{
		//	HSE not bypassed
		bit::clear(*MCU::RCC::CR, 18);
		
		
		//	HSE Clock Security CMOS Enable
		bit::set(*MCU::RCC::CR, 19);
		
		
		//	HSE Enable
		bit::set(*MCU::RCC::CR, 16);
		
		
		//	Wait for HSE to become stable
		while(bit::isCleared(*MCU::RCC::CR, 17))
		{
			
		}
	}
	else
	{
		//	Try to disable HSE
		bit::clear(*MCU::RCC::CR, 16);
		
		
		//	Check if HSE is disabled
		if(bit::isSet(*MCU::RCC::CR, 16))
		{
			return(FAIL);
		}
	}
	
	return(OK);
}


feedback RCC::HSI_init(bool enable)
{
	if(enable == true)
	{
		//	Enable HSI
		bit::set(*MCU::RCC::CR, 0);
		
		
		//	Wait for HSI to become stable
		while(bit::isCleared(*MCU::RCC::CR, 1))
		{
			
		}
	}
	else
	{
		//	Try to disable HSI
		bit::clear(*MCU::RCC::CR, 0);
		
		
		//	Check if HSI is disabled
		if(bit::isSet(*MCU::RCC::CR, 0))
		{
			return(FAIL);
		}
	}
	
	return(OK);
}


feedback RCC::LSI_init(bool enable)
{
	if(enable == true)
	{
		//	Enable LSI
		bit::set(*MCU::RCC::CSR, 0);
		
		
		//	Wait for LSI to become stable
		while(bit::isCleared(*MCU::RCC::CSR, 1))
		{
			
		}
	}
	else
	{
		//	Try to disable HSI
		bit::clear(*MCU::RCC::CSR, 0);
		
		
		//	Check if HSI is disabled
		if(bit::isSet(*MCU::RCC::CSR, 0))
		{
			return(FAIL);
		}
	}
	
	return(OK);
}







feedback RCC::set_clockSource(e_clockSource_system clockSource)
{
	uint32 clock_new = 0;
	switch(clockSource)
	{
		case e_clockSource_system::HSI:
		{
			clock_new = c_clock_hsi;
		}
		break;
		
		case e_clockSource_system::HSE:
		{
			clock_new = m_clock_hse;
		}
		break;
		
		case e_clockSource_system::PLL:
		{
			clock_new = m_clock_pll;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	
	//	A higher System Clock needs the Bus Prescalers and Flash Wait States before the Switch, a lower one afterwards,
	//	otherwise the Busses or the Flash run out of Specification in between
	const uint32 clock_system_old = m_clock_system;
	m_clock_system = clock_new;
	if(m_clock_system > clock_system_old)
	{
		if(set_busPrescaler() != OK || m_flash.set_waitStates(m_clock_system) != OK)
		{
			//	Undo Changes and return
			m_clock_system = clock_system_old;
			set_busPrescaler();
			return(FAIL);
		}
	}
	
	
	//	Switch System Clock Source and wait for the Switch: SWS follows SW after some Clock Cycles of both Clock Sources
	uint32 temp = *MCU::RCC::CFGR & 0xFFFFFFFC;
	*MCU::RCC::CFGR = temp | (uint32) clockSource;
	uint32 timeout = 100000;
	while(get_clockSource_system() != clockSource)
	{
		timeout--;
		if(timeout == 0)
		{
			//	Undo Changes and return, the higher Flash Wait States may stay
			temp = *MCU::RCC::CFGR & 0xFFFFFFFC;
			*MCU::RCC::CFGR = temp | (uint32) m_clockSource_system;
			m_clock_system = clock_system_old;
			set_busPrescaler();
			return(FAIL);
		}
	}
	m_clockSource_system = clockSource;
	
	
	//	Lower System Clock: Bus Prescalers and Flash Wait States afterwards
	if(m_clock_system < clock_system_old)
	{
		if(set_busPrescaler() != OK || m_flash.set_waitStates(m_clock_system) != OK)
		{
			return(FAIL);
		}
	}
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_pll clockSource)
{
	if(m_clockSource_pll == clockSource)
	{
		return(OK);
	}
	
	
	//	Check if PLL delivers System Clock
	if(get_clockSource_system() == e_clockSource_system::PLL)
	{
		HSI_init(true);
		set_clockSource(e_clockSource_system::HSI);
	}
	
	uint32 temp_rcc_cr = *MCU::RCC::CR;
	
	
	//	Disable PLL
	bit::clear(*MCU::RCC::CR, 24);
	
	
	if(clockSource == e_clockSource_pll::HSI_DIV2)
	{
		if(c_clock_hsi / 2 < 1000000 || c_clock_hsi / 2 > 25000000)
		{
			return(FAIL);
		}
		bit::clear(*MCU::RCC::CFGR, 16);
	}
	else
	{
		if(m_clock_hse / m_divider_hse < 1000000 || m_clock_hse / m_divider_hse > 25000000)
		{
			return(FAIL);
		}
		bit::set(*MCU::RCC::CFGR, 16);
	}
	
	
	//	Enable PLL if it has been enabled before
	if(bit::isSet(temp_rcc_cr, 24))
	{
		bit::set(*MCU::RCC::CR, 24);
		while(bit::isCleared(*MCU::RCC::CR, 25))
		{
			
		}
	}

	m_clockSource_pll = clockSource;

	return(OK);
}


feedback RCC::pll_set_HSE_DIV(uint32 divider)
{
	if(bit::isSet(*MCU::RCC::CR, 24) || divider > 2)
	{
		return(FAIL);
	}
	
	if(divider == 1)
	{
		bit::clear(*MCU::RCC::CFGR, 17);
	}
	else
	{
		bit::set(*MCU::RCC::CFGR, 17);
	}
	m_divider_hse = divider;
	
	return(OK);
}


feedback RCC::pll_init(uint32 clock_out)
{
	if(clock_out < 16000000 || clock_out > 72000000)
	{
		return(FAIL);
	}
	
	
	//	Evaluate PLL Input Frequency
	uint32 clock_in = 0;
	switch(m_clockSource_pll)
	{
		case e_clockSource_pll::HSI_DIV2:
		{
			clock_in = c_clock_hsi / 2;
		}
		break;
		
		case e_clockSource_pll::HSE:
		{
			clock_in = m_clock_hse / m_divider_hse;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	if(clock_in < 1000000 || clock_in > 25000000)
	{
		return(FAIL);
	}
	
	
	//	Compute Multiplier, before the PLL is switched off
	uint32 multiplier = clock_out / clock_in;
	if(multiplier < 2 || multiplier > 16)
	{
		return(FAIL);
	}
	
	
	//	Check, if PLL is delivering System Clock
	bool pllAsSystemSource = false;
	if(get_clockSource_system() == e_clockSource_system::PLL)
	{
		pllAsSystemSource = true;
		HSI_init(true);
		set_clockSource(e_clockSource_system::HSI);
	}
	
	
	//	Disable PLL
	bit::clear(*MCU::RCC::CR, 24);
	while(bit::isSet(*MCU::RCC::CR, 25))
	{
		
	}
	
	
	
	
	//	Write Multiplier Value
	uint32 temp = *MCU::RCC::CFGR & 0xFFC3FFFF;
	*MCU::RCC::CFGR = temp | ((multiplier - 2) << 18);
	
	m_clock_pll = clock_in * multiplier;
	
	
	//	Enable PLL
	bit::set(*MCU::RCC::CR, 24);
	
	
	//	Wait for PLL to lock
	while(bit::isCleared(*MCU::RCC::CR, 25))
	{
		
	}
	
	if(pllAsSystemSource == true)
	{
		set_clockSource(e_clockSource_system::PLL);
	}
	
	return(OK);
}







feedback RCC::module_clockInit(e_module module, bool enable)
{
	uint32 module_index = (uint32) module;
	uint32 offset = (module_index & 0x0000FF00) >> 8;
	volatile uint32* reg = MCU::RCC::AHB_ENR + offset;
	
	uint32 bit = module_index & 0x000000FF;
	
	if(enable == true)
	{
		//	The Clock of the Peripheral is active some Clock Cycles after its Enable Bit (2 on the L4/G4, RM0394): the dummy Read delays the
		//	first Access to the Peripheral, as the ST HAL does it on every STM32
		bit::set(*reg, bit);
		(void) *reg;
		return(OK);
	}
	if(enable == false)
	{
		bit::clear(*reg, bit);
		return(OK);
	}
	
	return(FAIL);
}


feedback RCC::module_reset(e_module module)
{
	uint32 module_index = (uint32) module;
	uint32 offset = (module_index & 0x0000FF00) >> 8;
	
	
	//	No *MCU::RCC::AHB_RSTR on this Chip
	if(offset == 0)
	{
		return(FAIL);
	}
	offset--;
	volatile uint32* reg = MCU::RCC::APB2_RSTR + offset;
	uint32 bit = module_index & 0x000000FF;
	
	bit::set(*reg, bit);
	while(bit::isCleared(*reg, bit))
	{
		
	}
	bit::clear(*reg, bit);
	while(bit::isSet(*reg, bit))
	{
		
	}
	
	return(OK);
}







feedback RCC::LSE_init(bool enable)
{
	//	The LSE belongs to the Backup Domain: its Write Protection (PWR, DBP) has to be disabled
	if(enable == true)
	{
		//	LSE is already running
		if(bit::isSet(*MCU::RCC::BDCR, 1) == true)
		{
			return(OK);
		}
		
		
		//	LSE not bypassed (Crystal), it can only be changed while the LSE is off
		bit::clear(*MCU::RCC::BDCR, 2);
		
		
		//	LSE Enable
		bit::set(*MCU::RCC::BDCR, 0);
		
		
		//	Wait for LSE to become stable: a Crystal needs up to some Seconds to start (Datasheet, tSU(LSE))
		CMOS& cmos = CMOS::get();
		const uint64 timestampStart = cmos.get_timestamp();
		while(bit::isCleared(*MCU::RCC::BDCR, 1) == true)
		{
			if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 5000)
			{
				//	No Crystal, or the Backup Domain is write protected
				bit::clear(*MCU::RCC::BDCR, 0);
				return(FAIL);
			}
		}
	}
	else
	{
		//	LSE Disable
		bit::clear(*MCU::RCC::BDCR, 0);
	}
	return(OK);
}


feedback RCC::reset_backupDomain()
{
	bit::set(*MCU::RCC::BDCR, 16);
	while(bit::isCleared(*MCU::RCC::BDCR, 16))
	{
		
	}
	bit::clear(*MCU::RCC::BDCR, 16);
	
	return(OK);
}


feedback RCC::set_rtc_clock(bool enable)
{
	if(enable == true)
	{
		bit::set(*MCU::RCC::BDCR, 15);
	}
	else
	{
		bit::clear(*MCU::RCC::BDCR, 15);
	}
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_rtc clockSource)
{
	uint32 temp = *MCU::RCC::BDCR & 0xFFFFFCFF;
	*MCU::RCC::BDCR = temp | ((uint32) clockSource << 8);
	
	return(OK);
}


feedback RCC::set_clock_HSE(uint32 clock)
{
	//	Crystal 4 ... 16 MHz, external Clock 1 ... 25 MHz (Datasheet)
	if(clock < 1000000 || clock > 25000000)
	{
		return(FAIL);
	}
	
	
	//	The Clocks are calculated when the Clock Source is switched: the HSE must not deliver the System Clock now
	if(m_clockSource_system == e_clockSource_system::HSE || (m_clockSource_system == e_clockSource_system::PLL && m_clockSource_pll == e_clockSource_pll::HSE))
	{
		return(FAIL);
	}
	m_clock_hse = clock;
	return(OK);
}


feedback RCC::set_prescaler(e_prescaler_adc prescaler)
{
	uint32 temp = *MCU::RCC::CFGR & 0xFFFF3FFF;
	*MCU::RCC::CFGR = temp | ((uint32) prescaler << 14);
	
	return(OK);
}