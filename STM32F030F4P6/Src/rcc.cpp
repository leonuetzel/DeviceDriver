#include "../Inc/stm32f030f4p6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void RCC::calculate_clockTree()
{
	//	RM0360 Rev.4 Chapter 7.2 Figure 10
	
	
	//	PLL Input Clock
	if(m_clockSource_pll == e_clockSource_pll::HSI_DIV2)
	{
		m_clock_pll_input = c_clock_hsi_8 / 2;
	}
	else
	{
		m_clock_pll_input = m_clock_HSE / m_prescaler_HSE_pll;
	}
	
	
	//	PLL Output Clock
	m_clock_pll = m_multiplier_pll * m_clock_pll_input;
	
	
	//	System Clock
	if(m_clockSource_system == e_clockSource_system::HSI_8)
	{
		m_clock_system = c_clock_hsi_8;
	}
	if(m_clockSource_system == e_clockSource_system::HSE)
	{
		m_clock_system = m_clock_HSE;
	}
	if(m_clockSource_system == e_clockSource_system::PLL)
	{
		m_clock_system = m_clock_pll;
	}
	
	
	//	AHB Clock
	m_clock_ahb = m_clock_system / m_prescaler_ahb;
	
	
	//	APB Clock
	m_clock_apb = m_clock_ahb / m_prescaler_apb;
	
	
	//	RTC Clock
	if(m_clockSource_rtc == e_clockSource_rtc::NONE)
	{
		m_clock_rtc = 0;
	}
	if(m_clockSource_rtc == e_clockSource_rtc::LSE)
	{
		m_clock_rtc = c_clock_lse;
	}
	if(m_clockSource_rtc == e_clockSource_rtc::LSI)
	{
		m_clock_rtc = c_clock_lsi;
	}
	if(m_clockSource_rtc == e_clockSource_rtc::HSE_DIV32)
	{
		m_clock_rtc = m_clock_HSE / 32;
	}
	
	
	//	USART 1 Clock
	if(m_clockSource_usart_1 == e_clockSource_usart_1::BUSCLOCK)
	{
		m_clock_usart_1 = m_clock_apb;
	}
	if(m_clockSource_usart_1 == e_clockSource_usart_1::SYSTEM_CLOCK)
	{
		m_clock_usart_1 = m_clock_system;
	}
	if(m_clockSource_usart_1 == e_clockSource_usart_1::HSI)
	{
		m_clock_usart_1 = c_clock_hsi_8;
	}
	if(m_clockSource_usart_1 == e_clockSource_usart_1::LSE)
	{
		m_clock_usart_1 = c_clock_lse;
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback RCC::HSE_init(bool enable)
{
	if(m_HSE_enabled == enable)
	{
		return(OK);
	}
	
	
	if(enable == true)
	{
		//	HSE not bypassed
		bit::clear(*MCU::RCC::CR, 18);
		
		
		//	HSE Clock Security System Enable
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
	m_HSE_enabled = enable;
	return(OK);
}


feedback RCC::HSI8_init(bool enable)
{
	if(m_HSI8_enabled == enable)
	{
		return(OK);
	}
	
	
	if(enable == true)
	{
		//	Enable HSI_8
		bit::set(*MCU::RCC::CR, 0);
		
		
		//	Wait for HSI_8 to become stable
		while(bit::isCleared(*MCU::RCC::CR, 1))
		{
			
		}
	}
	else
	{
		//	Try to disable HSI_8
		bit::clear(*MCU::RCC::CR, 0);
		
		
		//	Check if HSI_8 is disabled
		if(bit::isSet(*MCU::RCC::CR, 0))
		{
			return(FAIL);
		}
	}
	m_HSI8_enabled = enable;
	return(OK);
}


feedback RCC::HSI14_init(bool enable)
{
	if(enable == m_HSI14_enabled)
	{
		return(OK);
	}
	
	
	if(enable == true)
	{
		//	Enable HSI_14
		bit::set(*MCU::RCC::CR2, 0);
		
		
		//	Wait for HSI_14 to become stable
		while(bit::isCleared(*MCU::RCC::CR2, 1))
		{
			
		}
	}
	else
	{
		//	Try to disable HSI_14
		bit::clear(*MCU::RCC::CR2, 0);
		
		
		//	Check if HSI_14 is disabled
		if(bit::isSet(*MCU::RCC::CR2, 0))
		{
			return(FAIL);
		}
	}
	m_HSI14_enabled = enable;
	return(OK);
}







RCC::e_clockSource_system RCC::get_clockSource_system()
{
	uint32 mask = (*MCU::RCC::CFGR & 0x0000000C) >> 2;
	return((e_clockSource_system) mask);
}


feedback RCC::set_clockSource(e_clockSource_system clockSource)
{
	if(m_clockSource_system == clockSource)
	{
		return(OK);
	}
	
	
	//	Save old Clock Source in case it fails
	e_clockSource_system clockSourceSystemOld = m_clockSource_system;
	
	
	//	Update Clock Tree
	m_clockSource_system = clockSource;
	calculate_clockTree();
	
	if(m_flash.set_waitStates(m_clock_system) != OK)
	{
		//	Undo Changes and return
		m_clockSource_system = clockSourceSystemOld;
		calculate_clockTree();
		return(FAIL);
	}
	
	
	//	Switch System Clock Source
	uint32 temp = *MCU::RCC::CFGR & 0xFFFFFFFC;
	*MCU::RCC::CFGR = temp | (uint32) clockSource;
	
	
	//	Check if Switch was successful
	if(get_clockSource_system() != clockSource)
	{
		//	Undo Changes and return
		m_clockSource_system = clockSourceSystemOld;
		calculate_clockTree();
		return(FAIL);
	}
	

	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_pll clockSource)
{
	if(m_clockSource_pll == clockSource)
	{
		return(OK);
	}
	
	
	//	Save old Setting
	e_clockSource_pll clockSource_pll_old = m_clockSource_pll;
	
	
	//	Set new Setting
	m_clockSource_pll = clockSource;
	calculate_clockTree();
	
	
	//	Check if PLL delivers System Clock
	bool wasHSI8_enabled = m_HSI8_enabled;
	if(get_clockSource_system() == e_clockSource_system::PLL)
	{
		//	Set HSI_8 as System Clock Source
		HSI8_init(true);
		if(set_clockSource(e_clockSource_system::HSI_8) != OK)
		{
			HSI8_init(wasHSI8_enabled);
			m_clockSource_pll = clockSource_pll_old;
			calculate_clockTree();
			return(FAIL);
		}
	}
	
	uint32 temp_rcc_cr = *MCU::RCC::CR;
	
	
	//	Disable PLL
	bit::clear(*MCU::RCC::CR, 24);
	m_pll_enabled = false;
	
	
	//	Select PLL Clock Source
	//	Make sure that PLL Input Clock is inside the Boundaries (Datasheet Chapter 6.3.9)
	if(clockSource == e_clockSource_pll::HSE)
	{
		if(m_clock_pll_input < c_clock_pll_input_min || m_clock_pll_input > c_clock_pll_input_max || m_HSE_enabled == false)
		{
			m_clockSource_pll = clockSource_pll_old;
			calculate_clockTree();
			return(FAIL);
		}
		bit::set(*MCU::RCC::CFGR, 16);
	}
	else
	{
		bit::clear(*MCU::RCC::CFGR, 16);
	}
	
	
	//	Put HSI8 in its old State if it was changed
	if(HSI8_init(wasHSI8_enabled) != OK)
	{
		m_clockSource_pll = clockSource_pll_old;
		calculate_clockTree();
		return(FAIL);
	}
	
	
	//	Enable PLL if it has been enabled before
	if(bit::isSet(temp_rcc_cr, 24))
	{
		//	Enable
		bit::set(*MCU::RCC::CR, 24);
		
		
		//	Wait for PLL to lock
		while(bit::isCleared(*MCU::RCC::CR, 25))
		{
			
		}
		m_pll_enabled = true;
	}
	return(OK);
}


feedback RCC::set_prescaler_HSE_pll(uint32 prescaler)
{
	if(m_prescaler_HSE_pll == prescaler)
	{
		return(OK);
	}
	
	
	if(bit::isSet(*MCU::RCC::CR, 24))
	{
		return(FAIL);
	}
	
	uint32 temp = *MCU::RCC::CFGR2 & 0xFFFFFFF0;
	*MCU::RCC::CFGR2 = temp | (prescaler - 1);
	
	m_prescaler_HSE_pll = prescaler;
	calculate_clockTree();
	
	return(OK);
}


feedback RCC::pll_init(uint32 clock_out)
{
	if(m_clock_pll == clock_out && m_pll_enabled == true)
	{
		return(OK);
	}
	
	
	//	Check Output Clock Boundaries
	if(clock_out < c_clock_pll_output_min || clock_out > c_clock_pll_output_max)
	{
		return(FAIL);
	}
	
	
	//	Check Input Clock Boundaries
	if(m_clock_pll_input < c_clock_pll_input_min || m_clock_pll_input > c_clock_pll_input_max)
	{
		return(FAIL);
	}
	
	
	//	Compute Multiplier
	uint32 multiplier = clock_out / m_clock_pll_input;
	if(multiplier < 2 || multiplier > 16)
	{
		return(FAIL);
	}
	
	
	//	Check, if PLL is delivering System Clock
	bool pllAsSystemSource = false;
	bool wasHSI8_enabled = m_HSI8_enabled;
	if(get_clockSource_system() == e_clockSource_system::PLL)
	{
		pllAsSystemSource = true;
		if(HSI8_init(true) != OK)
		{
			return(FAIL);
		}
		if(set_clockSource(e_clockSource_system::HSI_8) != OK)
		{
			HSI8_init(wasHSI8_enabled);
			return(FAIL);
		}
	}
	
	
	//	Disable PLL
	bit::clear(*MCU::RCC::CR, 24);
	while(bit::isSet(*MCU::RCC::CR, 25))
	{
		
	}
	m_pll_enabled = false;
	
	
	//	Write Multiplier Value
	uint32 temp = *MCU::RCC::CFGR & 0xFFC3FFFF;
	*MCU::RCC::CFGR = temp | ((multiplier - 2) << 18);
	
	m_multiplier_pll = multiplier;
	calculate_clockTree();
	
	
	//	Enable PLL
	bit::set(*MCU::RCC::CR, 24);
	
	
	//	Wait for PLL to lock
	while(bit::isCleared(*MCU::RCC::CR, 25))
	{
		
	}
	m_pll_enabled = true;
	
	
	if(pllAsSystemSource == true)
	{
		if(set_clockSource(e_clockSource_system::PLL) != OK)
		{
			HSI8_init(wasHSI8_enabled);
			return(FAIL);
		}
	}
	return(HSI8_init(wasHSI8_enabled));
}


feedback RCC::set_prescaler_AHB(uint32 prescaler)
{
	uint32 mask = Math::log2(prescaler) + 7;
	if(prescaler > 16)
	{
		mask--;
	}
	if(mask < 0x7 || mask > 0xF)
	{
		return(FAIL);
	}
	
	uint32 rcc_cfgr = *MCU::RCC::CFGR & 0xFFFFFF0F;
	*MCU::RCC::CFGR = rcc_cfgr | (mask << 4);
	
	m_prescaler_ahb = prescaler;
	calculate_clockTree();
	
	return(OK);
}


feedback RCC::set_prescaler_APB(uint32 prescaler)
{
	uint32 mask = Math::log2(prescaler) + 3;
	if(mask < 0x3 || mask > 0x7)
	{
		return(FAIL);
	}
	
	uint32 rcc_cfgr = *MCU::RCC::CFGR & 0xFFFFF8FF;
	*MCU::RCC::CFGR = rcc_cfgr | (mask << 8);
	
	m_prescaler_apb = prescaler;
	calculate_clockTree();
	
	return(OK);
}







void RCC::clear_resetFlags()
{
	bit::set(*MCU::RCC::CSR, 24);
}







feedback RCC::module_clockInit(e_module module, bool enable)
{
	uint32 module_index = (uint32) module;
	uint32 offset = (module_index & 0x0000FF00) >> 8;
	volatile uint32* reg = MCU::RCC::AHB_ENR + offset;
	
	uint32 bit = module_index & 0x000000FF;
	
	if(enable == true)
	{
		bit::set(*reg, bit);
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
	volatile uint32* reg = MCU::RCC::AHB_RSTR + offset;
	if(offset != 0)
	{
		reg = MCU::RCC::APB2_RSTR + (offset - 1);
	}
	
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







feedback RCC::reset_backupDomain()
{
	bit::set(*MCU::RCC::BDCR, 16);
	while(bit::isCleared(*MCU::RCC::BDCR, 16))
	{
		
	}
	bit::clear(*MCU::RCC::BDCR, 16);
	
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_rtc clockSource, bool enable)
{
	bool calculateNecessary = false;
	
	
	//	Clock Source
	if(m_clockSource_rtc != clockSource)
	{
		uint32 bdcr = *MCU::RCC::BDCR & 0xFFFFFCFF;
		*MCU::RCC::BDCR = bdcr | (((uint32) clockSource) << 8);
		
		m_clockSource_rtc = clockSource;
		calculateNecessary = true;
	}
	
	
	//	Enable
	if(m_clock_rtc_enabled != enable)
	{
		if(enable == true)
		{
			bit::set(*MCU::RCC::BDCR, 15);
		}
		else
		{
			bit::clear(*MCU::RCC::BDCR, 15);
		}
		
		m_clock_rtc_enabled = enable;
		calculateNecessary = true;
	}
	
	
	if(calculateNecessary == true)
	{
		calculate_clockTree();
	}
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_usart_1 clockSource)
{
	if(m_clockSource_usart_1 == clockSource)
	{
		return(OK);
	}
	
	
	uint32 temp = *MCU::RCC::CFGR3 & 0xFFFFFFFC;
	*MCU::RCC::CFGR3 = temp | ((uint32) clockSource);
	
	m_clockSource_usart_1 = clockSource;
	calculate_clockTree();
	
	return(OK);
}







feedback RCC::set_clock_HSE(uint32 clock)
{
	if(clock < c_clock_HSE_min || clock > c_clock_HSE_max)
	{
		return(FAIL);
	}
	
	m_clock_HSE = clock;
	calculate_clockTree();
	return(OK);
}