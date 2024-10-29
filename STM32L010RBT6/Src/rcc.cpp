#include "../Inc/stm32l010rbt6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void RCC::calculate_clockTree()
{
	//	RM0451 Rev.3 Chapter 7.2 Figure 16
	
	
	//	MSI Clock
	if(m_MSI_enabled == true)
	{
		m_clock_MSI = c_clock_msi[m_MSI_range];
	}
	else
	{
		m_clock_MSI = 0;
	}
	
	
	//	HSI16 Clock
	if(m_HSI16_enabled == true)
	{
		m_clock_HSI16 = c_clock_hsi_16 / m_prescaler_HSI16;
	}
	else
	{
		m_clock_HSI16 = 0;
	}
	
	
	//	LSI Clock
	if(m_LSI_enabled == true)
	{
		m_clock_LSI = c_clock_lsi;
	}
	else
	{
		m_clock_LSI = 0;
	}
	
	
	//	PLL Input Clock
	if(m_clockSource_pll == e_clockSource_pll::HSI_16)
	{
		m_clock_pll_input = m_clock_HSI16;
	}
	else
	{
		m_clock_pll_input = 0;
	}
	
	
	//	PLL Output Clock
	if(m_pll_enabled == true)
	{
		m_clock_pll = (m_multiplier_pll * m_clock_pll_input) / m_prescaler_pll_out;
	}
	else
	{
		m_clock_pll = 0;
	}
	
	
	
	//	System Clock
	if(m_clockSource_system == e_clockSource_system::MSI)
	{
		m_clock_system = m_clock_MSI;
	}
	if(m_clockSource_system == e_clockSource_system::HSI_16)
	{
		m_clock_system = m_clock_HSI16;
	}
	if(m_clockSource_system == e_clockSource_system::PLL)
	{
		m_clock_system = m_clock_pll;
	}
	
	
	//	AHB Clock
	m_clock_ahb = m_clock_system / m_prescaler_ahb;
	
	
	//	APB1 Clock
	m_clock_apb1 = m_clock_ahb / m_prescaler_apb1;
	
	
	//	APB2 Clock
	m_clock_apb2 = m_clock_ahb / m_prescaler_apb2;
	
	
	//	APB1 Timer Clock
	if(m_prescaler_apb1 == 1)
	{
		m_clock_apb1_timer = m_clock_apb1;
	}
	else
	{
		m_clock_apb1_timer = m_clock_apb1 * 2;
	}
	
	
	//	APB2 Timer Clock
	if(m_prescaler_apb2 == 1)
	{
		m_clock_apb2_timer = m_clock_apb2;
	}
	else
	{
		m_clock_apb2_timer = m_clock_apb2 * 2;
	}
	
	
	//	RTC Clock
	if(m_clock_rtc_enabled == true)
	{
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
	}
	else
	{
		m_clock_rtc = 0;
	}
	
	
	//	USART 2 Clock
	if(m_clockSource_usart_2 == e_clockSource_usart_2::BUSCLOCK)
	{
		m_clock_usart_2 = m_clock_apb1;
	}
	if(m_clockSource_usart_2 == e_clockSource_usart_2::SYSTEM_CLOCK)
	{
		m_clock_usart_2 = m_clock_system;
	}
	if(m_clockSource_usart_2 == e_clockSource_usart_2::HSI16)
	{
		m_clock_usart_2 = m_clock_HSI16;
	}
	if(m_clockSource_usart_2 == e_clockSource_usart_2::LSE)
	{
		m_clock_usart_2 = c_clock_lse;
	}
	
	
	//	LPUART 1 Clock
	if(m_clockSource_lpuart_1 == e_clockSource_lpuart_1::BUSCLOCK)
	{
		m_clock_lpuart_1 = m_clock_apb1;
	}
	if(m_clockSource_lpuart_1 == e_clockSource_lpuart_1::SYSTEM_CLOCK)
	{
		m_clock_lpuart_1 = m_clock_system;
	}
	if(m_clockSource_lpuart_1 == e_clockSource_lpuart_1::HSI16)
	{
		m_clock_lpuart_1 = m_clock_HSI16;
	}
	if(m_clockSource_lpuart_1 == e_clockSource_lpuart_1::LSE)
	{
		m_clock_lpuart_1 = c_clock_lse;
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback RCC::MSI_init(bool enable, uint32 range)
{
	//	Boundary Check
	if(range > 6)
	{
		return(FAIL);
	}
	
	
	if(m_MSI_enabled == enable)
	{
		return(OK);
	}
	
	
	if(enable == true)
	{
		//	MSI Frequency
		uint32 temp = *MCU::RCC::ICSCR & 0xFFFF1FFF;
		*MCU::RCC::ICSCR = temp | (range << 13);
		
		
		//	MSI Enable
		bit::set(*MCU::RCC::CR, 8);
		
		
		//	Wait for MSI to become stable
		while(bit::isCleared(*MCU::RCC::CR, 9))
		{
			
		}
		
		
		//	Update MSI Range
		m_MSI_range = range;
	}
	else
	{
		//	Try to disable MSI
		bit::clear(*MCU::RCC::CR, 8);
		
		
		//	Check if MSI is disabled
		if(bit::isSet(*MCU::RCC::CR, 8))
		{
			return(FAIL);
		}
	}
	m_MSI_enabled = enable;
	calculate_clockTree();
	return(OK);
}


feedback RCC::HSI16_init(bool enable)
{
	if(enable == m_HSI16_enabled)
	{
		return(OK);
	}
	
	
	if(enable == true)
	{
		//	Enable HSI_16
		bit::set(*MCU::RCC::CR, 0);
		
		
		//	Wait for HSI_16 to become stable
		while(bit::isCleared(*MCU::RCC::CR, 2))
		{
			
		}
	}
	else
	{
		//	Try to disable HSI_16
		bit::clear(*MCU::RCC::CR, 0);
		
		
		//	Check if HSI_16 is disabled
		if(bit::isSet(*MCU::RCC::CR, 0))
		{
			return(FAIL);
		}
	}
	m_HSI16_enabled = enable;
	calculate_clockTree();
	return(OK);
}


feedback RCC::LSI_init(bool enable)
{
	if(enable == m_LSI_enabled)
	{
		return(OK);
	}
	
	
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
		//	Try to disable LSI
		bit::clear(*MCU::RCC::CSR, 0);
		
		
		//	Wait for LSI to be disabled
		while(bit::isSet(*MCU::RCC::CSR, 1))
		{
			
		}
	}
	m_LSI_enabled = enable;
	calculate_clockTree();
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
	const e_clockSource_system clockSourceSystemOld = m_clockSource_system;
	
	
	//	Update Clock Tree
	m_clockSource_system = clockSource;
	calculate_clockTree();
	
	
	//	Flash Wait States
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
	const bool was_MSI_enabled = m_MSI_enabled;
	if(get_clockSource_system() == e_clockSource_system::PLL)
	{
		//	Set MSI as System Clock Source
		MSI_init(true);
		if(set_clockSource(e_clockSource_system::MSI) != OK)
		{
			MSI_init(was_MSI_enabled);
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
	bit::clear(*MCU::RCC::CFGR, 16);
	
	
	//	Put MSI in its old State if it was changed
	if(MSI_init(was_MSI_enabled) != OK)
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
	
	
	//	Max VCO Clock of PLL depends on Voltage Range (PWR Block)
	const PWR::e_voltageRange voltageRange = STM32L010RBT6::get().get_pwr().get_voltageRange();
	constexpr uint32 c_clock_VCO_max[] = {0, 96000000, 48000000, 24000000};
	const uint32 clock_VCO_max = c_clock_VCO_max[((uint32) voltageRange)];
	
	
	//	Compute Multiplier and Divider
	uint32 smallestDeviation = 0xFFFFFFFF;
	uint32 bestMultiplier = 0;
	uint32 bestDivider = 0;
	for(uint32 divider = 2; divider <= 4; divider++)
	{
		for(uint32 i = 0; i < sizeof(c_pll_multiplier) / sizeof(c_pll_multiplier[0]); i++)
		{
			const uint32 multiplier = c_pll_multiplier[i];
			
			
			//	Check maximum VCO Clock
			const uint32 clock_VCO = m_clock_pll_input * multiplier;
			if(clock_VCO > clock_VCO_max)
			{
				break;
			}
			
			
			//	Check Output Clock
			const uint32 clock_pll_out = clock_VCO / divider;
			if(clock_pll_out >= c_clock_pll_output_min && clock_pll_out <= c_clock_pll_output_max)
			{
				const uint32 deviation = Math::absolute<int32>(((int32) clock_pll_out) - clock_out);
				if(deviation < smallestDeviation)
				{
					//	Save best Configuration
					smallestDeviation = deviation;
					bestMultiplier = i;
					bestDivider = divider;
				}
			}
		}
	}
	
	
	//	Check if valid Configuration has been found
	if(bestDivider == 0)
	{
		return(FAIL);
	}
	
	
	//	Check, if PLL is delivering System Clock
	bool pllAsSystemSource = false;
	const bool was_MSI_enabled = m_MSI_enabled;
	if(get_clockSource_system() == e_clockSource_system::PLL)
	{
		pllAsSystemSource = true;
		if(MSI_init(true) != OK)
		{
			return(FAIL);
		}
		if(set_clockSource(e_clockSource_system::MSI) != OK)
		{
			MSI_init(was_MSI_enabled);
			return(FAIL);
		}
	}
	
	
	//	Disable PLL
	bit::clear(*MCU::RCC::CR, 24);
	while(bit::isSet(*MCU::RCC::CR, 25))
	{
		
	}
	m_pll_enabled = false;
	
	
	//	Write Multiplier and Divider Value
	uint32 temp = *MCU::RCC::CFGR & 0xFF03FFFF;
	*MCU::RCC::CFGR = temp | ((bestDivider - 1) << 22) | (bestMultiplier << 18);
	
	
	m_multiplier_pll = c_pll_multiplier[bestMultiplier];
	m_prescaler_pll_out = bestDivider;
	
	
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
			MSI_init(was_MSI_enabled);
			return(FAIL);
		}
	}
	if(MSI_init(was_MSI_enabled) != OK)
	{
		return(FAIL);
	}
	calculate_clockTree();
	return(OK);
}


void RCC::set_HSI16_prescaler(bool divideBy4)
{
	if(divideBy4 == true)
	{
		bit::set(*MCU::RCC::CR, 3);
		m_prescaler_HSI16 = 4;
	}
	else
	{
		bit::clear(*MCU::RCC::CR, 3);
		m_prescaler_HSI16 = 1;
	}
	calculate_clockTree();
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


feedback RCC::set_prescaler_APB1(uint32 prescaler)
{
	uint32 mask = Math::log2(prescaler) + 3;
	if(mask < 0x3 || mask > 0x7)
	{
		return(FAIL);
	}
	
	uint32 rcc_cfgr = *MCU::RCC::CFGR & 0xFFFFF8FF;
	*MCU::RCC::CFGR = rcc_cfgr | (mask << 8);
	
	m_prescaler_apb1 = prescaler;
	calculate_clockTree();
	
	return(OK);
}


feedback RCC::set_prescaler_APB2(uint32 prescaler)
{
	uint32 mask = Math::log2(prescaler) + 3;
	if(mask < 0x3 || mask > 0x7)
	{
		return(FAIL);
	}
	
	uint32 rcc_cfgr = *MCU::RCC::CFGR & 0xFFFFC7FF;
	*MCU::RCC::CFGR = rcc_cfgr | (mask << 11);
	
	m_prescaler_apb2 = prescaler;
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
	
	volatile uint32* reg = MCU::RCC::IOP_ENR + offset;
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
	
	volatile uint32* reg = MCU::RCC::IOP_RSTR + offset;
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
	bit::set(*MCU::RCC::CSR, 19);
	while(bit::isCleared(*MCU::RCC::CSR, 19))
	{
		
	}
	bit::clear(*MCU::RCC::CSR, 19);
	
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_rtc clockSource, bool enable)
{
	bool calculateNecessary = false;
	
	
	//	Clock Source
	if(m_clockSource_rtc != clockSource)
	{
		uint32 csr = *MCU::RCC::CSR & 0xFFFCFFFF;
		*MCU::RCC::CSR = csr | (((uint32) clockSource) << 16);
		
		m_clockSource_rtc = clockSource;
		calculateNecessary = true;
	}
	
	
	//	Enable
	if(m_clock_rtc_enabled != enable)
	{
		if(enable == true)
		{
			bit::set(*MCU::RCC::CSR, 18);
		}
		else
		{
			bit::clear(*MCU::RCC::CSR, 18);
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


feedback RCC::set_clockSource(e_clockSource_usart_2 clockSource)
{
	if(m_clockSource_usart_2 == clockSource)
	{
		return(OK);
	}
	
	
	uint32 temp = *MCU::RCC::CCIPR & 0xFFFFFFF3;
	*MCU::RCC::CCIPR = temp | (((uint32) clockSource) << 2);
	
	m_clockSource_usart_2 = clockSource;
	calculate_clockTree();
	
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_lpuart_1 clockSource)
{
	if(m_clockSource_lpuart_1 == clockSource)
	{
		return(OK);
	}
	
	
	uint32 temp = *MCU::RCC::CCIPR & 0xFFFFF3FF;
	*MCU::RCC::CCIPR = temp | (((uint32) clockSource) << 10);
	
	m_clockSource_lpuart_1 = clockSource;
	calculate_clockTree();
	
	return(OK);
}