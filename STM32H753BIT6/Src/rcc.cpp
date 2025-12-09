#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback RCC::startup()
{
	return(OK);
}


feedback RCC::set_busPrescaler(uint32 newClock)
{
	m_divider_core = 1;
	m_divider_ahb  = 1;
	m_divider_apb1 = 1;
	m_divider_apb2 = 1;
	m_divider_apb3 = 1;
	m_divider_apb4 = 1;
	
	
	//	Core Prescaler
	uint32 mask_core = 0x7;
	while(newClock / m_divider_core > c_clock_core_max)
	{
		m_divider_core *= 2;
		mask_core++;
		if(m_divider_core == 32)
		{
			m_divider_core *= 2;
		}
		if(m_divider_core > 512)
		{
			return(FAIL);
		}
	}
	m_clock_core = newClock / m_divider_core;
	
	
	//	AHB Prescaler
	uint32 mask_ahb = 0x7;
	while(m_clock_core / m_divider_ahb > c_clock_ahb_max)
	{
		m_divider_ahb *= 2;
		mask_ahb++;
		if(m_divider_ahb == 32)
		{
			m_divider_ahb *= 2;
		}
		if(m_divider_ahb > 512)
		{
			return(FAIL);
		}
	}
	m_clock_ahb = m_clock_core / m_divider_ahb;
	
	
	//	APB1 Prescaler
	uint32 mask_apb1 = 0x3;
	while(m_clock_ahb / m_divider_apb1 > c_clock_apb1_max)
	{
		m_divider_apb1 *= 2;
		mask_apb1++;
		if(m_divider_apb1 > 16)
		{
			return(FAIL);
		}
	}
	m_clock_apb1 = m_clock_ahb / m_divider_apb1;
	m_clock_apb1_timer = m_clock_apb1;
	if(m_divider_apb1 != 1)
	{
		m_clock_apb1_timer *= 2;
	}
	
	
	//	APB2 Prescaler
	uint32 mask_apb2 = 0x3;
	while(m_clock_ahb / m_divider_apb2 > c_clock_apb2_max)
	{
		m_divider_apb2 *= 2;
		mask_apb2++;
		if(m_divider_apb2 > 16)
		{
			return(FAIL);
		}
	}
	m_clock_apb2 = m_clock_ahb / m_divider_apb2;
	m_clock_apb2_timer = m_clock_apb2;
	if(m_divider_apb2 != 1)
	{
		m_clock_apb2_timer *= 2;
	}
	
	
	//	APB3 Prescaler
	uint32 mask_apb3 = 0x3;
	while(m_clock_ahb / m_divider_apb3 > c_clock_apb3_max)
	{
		m_divider_apb3 *= 2;
		mask_apb3++;
		if(m_divider_apb3 > 16)
		{
			return(FAIL);
		}
	}
	m_clock_apb3 = m_clock_ahb / m_divider_apb3;
	
	
	//	APB4 Prescaler
	uint32 mask_apb4 = 0x3;
	while(m_clock_ahb / m_divider_apb4 > c_clock_apb4_max)
	{
		m_divider_apb4 *= 2;
		mask_apb4++;
		if(m_divider_apb4 > 16)
		{
			return(FAIL);
		}
	}
	m_clock_apb4 = m_clock_ahb / m_divider_apb4;
	
	
	//	Write Prescalers to Registers
	uint32 temp = 0;
	
	temp |= (mask_core << 8);
	temp |= (mask_apb3 << 4);
	temp |= mask_ahb;
	*MCU::RCC::D1_CFGR = temp;
	
	temp = 0;
	temp |= (mask_apb2 << 8);
	temp |= (mask_apb1 << 4);
	*MCU::RCC::D2_CFGR = temp;
	
	*MCU::RCC::D3_CFGR = (mask_apb4 << 4);
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
	
	return(OK);
}


feedback RCC::HSI_init(bool enable, uint8 divider)
{
	if(enable == true)
	{
		//	Enable HSI
		bit::set(*MCU::RCC::CR, 0);
		
		
		//	Wait for HSI to become stable
		while(bit::isCleared(*MCU::RCC::CR, 2))
		{

		}
		
		
		//	Set new Divider
		const uint32 mask = Math::log2((uint32) divider);
		bit::fieldWrite(*MCU::RCC::CR, 3, 2, mask);
		
		
		//	Check for Divider to be set correctly
		if(bit::fieldRead(*MCU::RCC::CR, 3, 2) != mask)
		{
			return(FAIL);
		}
		
		
		//	Wait for new Frequency to match set one
		while(bit::isCleared(*MCU::RCC::CR, 5))
		{
			
		}
		
		m_divider_hsi = divider;
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











feedback RCC::set_clockSource_pll(e_clockSource_pll clockSource)
{
	//	Check if PLL1 delivers System Clock
	if(get_clockSource_system() == e_clockSource_system::PLL1)
	{
		if(HSI_init(true, 1) != OK)
		{
			return(FAIL);
		}
		
		
		//	Set HSI as System Clock Source
		set_clockSource_system(e_clockSource_system::HSI);
	}
	
	
	//	Disable all PLLs
	const uint32 temp_rcc_cr = *MCU::RCC::CR;
	bit::clear(*MCU::RCC::CR, 28);
	bit::clear(*MCU::RCC::CR, 26);
	bit::clear(*MCU::RCC::CR, 24);
	
	
	//	Boundary Check
	uint32 mask = (uint32) clockSource;
	if(mask > 0x3)
	{
		return(FAIL);
	}
	
	
	//	Set new Clock Source
	bit::fieldWrite(*MCU::RCC::PLL_CKSELR, 0, 2, mask);
	if(bit::fieldRead(*MCU::RCC::PLL_CKSELR, 0, 2) != mask)
	{
		return(FAIL);
	}
	
	
	//	Enable PLLs if they have been enabled before
	if(bit::isSet(temp_rcc_cr, 28))
	{
		bit::set(*MCU::RCC::CR, 28);
		while(bit::isCleared(*MCU::RCC::CR, 29))
		{

		}
	}
	if(bit::isSet(temp_rcc_cr, 26))
	{
		bit::set(*MCU::RCC::CR, 26);
		while(bit::isCleared(*MCU::RCC::CR, 27))
		{

		}
	}
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


feedback RCC::pll_1_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	//	Boundary Check
	if(clock_out < 150000000 || divider_p > 128 || divider_q > 128 || divider_r > 128 || divider_p % 2 != 0)
	{
		return(FAIL);
	}
	
	
	//	Evaluate PLL Input Frequency
	uint32 clock_in = 0;
	switch(m_clockSource_pll)
	{
		case e_clockSource_pll::HSI:
		{
			clock_in = c_clock_hsi / m_divider_hsi;
		}
		break;
		
		case e_clockSource_pll::CSI:
		{
			clock_in = c_clock_csi;
		}
		break;
		
		case e_clockSource_pll::HSE:
		{
			clock_in = c_clock_hse;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
		break;
	}
	
	
	//	Check Input and Output Frequency Ranges
	if((clock_out > 420000000 && clock_in < 2000000) || clock_in < 1000000)
	{
		return(FAIL);
	}
	
	
	//	Check, if PLL 1 is delivering System Clock
	bool pllAsSystemSource = false;
	if(get_clockSource_system() == e_clockSource_system::PLL1)
	{
		pllAsSystemSource = true;
		if(HSI_init(true, 1) != OK)
		{
			return(FAIL);
		}
		set_clockSource_system(e_clockSource_system::HSI);
	}
	
	
	//	Disable PLL 1
	bit::clear(*MCU::RCC::CR, 24);
	while(bit::isSet(*MCU::RCC::CR, 25))
	{
		
	}
	
	
	//	Enable or Disable Outputs
	if(divider_p == 0)
	{
		bit::clear(*MCU::RCC::PLL_CFGR, 16);
	}
	else
	{
		bit::set(*MCU::RCC::PLL_CFGR, 16);
	}
	if(divider_q == 0)
	{
		bit::clear(*MCU::RCC::PLL_CFGR, 17);
	}
	else
	{
		bit::set(*MCU::RCC::PLL_CFGR, 17);
	}
	if(divider_r == 0)
	{
		bit::clear(*MCU::RCC::PLL_CFGR, 18);
	}
	else
	{
		bit::set(*MCU::RCC::PLL_CFGR, 18);
	}
	
	
	//	Select VCO and Input Divider
	uint32 divider_in = 1;
	uint32 clock_in_divided = clock_in / divider_in;
	
	if(clock_out >= 192000000 && clock_in >= 2000000)
	{
		m_pll_1_range = e_pll_range::WIDE;
		bit::clear(*MCU::RCC::PLL_CFGR, 1);
		while(clock_in_divided > 16000000)
		{
			divider_in++;
			if(divider_in > 63)
			{
				return(FAIL);
			}
			clock_in_divided = clock_in / divider_in;
		}
	}
	else
	{
		m_pll_1_range = e_pll_range::MEDIUM;
		bit::set(*MCU::RCC::PLL_CFGR, 1);
		while(clock_in_divided > 2000000)
		{
			divider_in++;
			if(divider_in > 63)
			{
				return(FAIL);
			}
			clock_in_divided = clock_in / divider_in;
		}
	}
	
	
	//	Set correct Input Frequency Range
	uint32 mask = 0;
	if(clock_in_divided > 1000000 && clock_in_divided <= 2000000)
	{
		mask = 0x0;
	}
	else
	{
		if(clock_in_divided > 2000000 && clock_in_divided <= 4000000)
		{
			mask = 0x1;
		}
		else
		{
			if(clock_in_divided > 4000000 && clock_in_divided <= 8000000)
			{
				mask = 0x2;
			}
			else
			{
				if(clock_in_divided > 8000000 && clock_in_divided <= 16000000)
				{
					mask = 0x3;
				}
			}
		}
	}
	bit::fieldWrite(*MCU::RCC::PLL_CFGR, 2, 2, mask);
	
	
	//	Compute Multiplier
	const double multiplier = clock_out / clock_in_divided;
	if(multiplier < 4 || multiplier > 512)
	{
		return(FAIL);
	}
	
	const uint32 multiplier_int = (uint32) multiplier;
	const uint32 multiplier_frac = (uint32) ((multiplier - multiplier_int) * 0x2000);
	
	
	//	Write Multiplier Values
	bit::fieldWrite(*MCU::RCC::PLL1_DIVR, 0, 9, multiplier_int - 1);
	
	
	//	PLL 1 Latch
	bit::clear(*MCU::RCC::PLL_CFGR, 0);
	bit::fieldWrite(*MCU::RCC::PLL1_FRACR, 3, 13, multiplier_frac);
	bit::set(*MCU::RCC::PLL_CFGR, 0);
	
	
	//	Write Divider Values
	bit::fieldWrite(*MCU::RCC::PLL_CKSELR, 4, 6, divider_in);
	bit::fieldWrite(*MCU::RCC::PLL1_DIVR,  9, 7, divider_p - 1);
	bit::fieldWrite(*MCU::RCC::PLL1_DIVR, 16, 7, divider_q - 1);
	bit::fieldWrite(*MCU::RCC::PLL1_DIVR, 24, 7, divider_r - 1);
	
	
	//	Adapt Voltage Level according to Frequency
	bool pll_1_range_wide = false;
	if(m_pll_1_range == e_pll_range::WIDE)
	{
		pll_1_range_wide = true;
	}
	
	PWR& pwr = STM32H753BIT6::get().get_pwr();
	pwr.set_voltageLevel(pwr.get_requiredVoltageLevel(divider_p, divider_q, divider_r, clock_out, pll_1_range_wide));
	
	
	//	Store Settings
	m_divider_pll_1_p = divider_p;
	m_divider_pll_1_q = divider_q;
	m_divider_pll_1_r = divider_r;
	m_clock_pll_1 = clock_out;
	
	
	//	Enable PLL 1
	bit::set(*MCU::RCC::CR, 24);
	
	
	//	Wait for PLL 1 to lock
	while(bit::isCleared(*MCU::RCC::CR, 25))
	{
		
	}
	
	
	//	Reapply PLL 1 as System Clock Source
	if(pllAsSystemSource == true)
	{
		set_clockSource_system(e_clockSource_system::PLL1);
	}
	return(OK);
}


feedback RCC::pll_2_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	//	Boundary Check
	if(clock_out < 150000000 || divider_p > 128 || divider_q > 128 || divider_r > 128)
	{
		return(FAIL);
	}
	
	
	//	Evaluate PLL Input Frequency
	uint32 clock_in = 0;
	switch(m_clockSource_pll)
	{
		case e_clockSource_pll::HSI:
		{
			clock_in = c_clock_hsi / m_divider_hsi;
		}
		break;
		
		case e_clockSource_pll::CSI:
		{
			return(FAIL);
		}
		break;
		
		case e_clockSource_pll::HSE:
		{
			clock_in = c_clock_hse;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
		break;
	}
	
	
	//	Check Input and Output Frequency Ranges
	if((clock_out > 420000000 && clock_in < 2000000) || clock_in < 1000000)
	{
		return(FAIL);
	}
	
	
	//	Disable PLL 2
	bit::clear(*MCU::RCC::CR, 26);
	while(bit::isSet(*MCU::RCC::CR, 27))
	{
		
	}
	
	
	//	Enable or Disable Outputs
	if(divider_p == 0)
	{
		bit::clear(*MCU::RCC::PLL_CFGR, 19);
	}
	else
	{
		bit::set(*MCU::RCC::PLL_CFGR, 19);
	}
	if(divider_q == 0)
	{
		bit::clear(*MCU::RCC::PLL_CFGR, 20);
	}
	else
	{
		bit::set(*MCU::RCC::PLL_CFGR, 20);
	}
	if(divider_r == 0)
	{
		bit::clear(*MCU::RCC::PLL_CFGR, 21);
	}
	else
	{
		bit::set(*MCU::RCC::PLL_CFGR, 21);
	}
	
	
	//	Select VCO and Input Divider
	uint32 divider_in = 1;
	uint32 clock_in_divided = clock_in / divider_in;
	
	if(clock_out >= 192000000 && clock_in >= 2000000)
	{
		m_pll_2_range = e_pll_range::WIDE;
		bit::clear(*MCU::RCC::PLL_CFGR, 5);
		while(clock_in_divided > 16000000)
		{
			divider_in++;
			if(divider_in > 63)
			{
				return(FAIL);
			}
			clock_in_divided = clock_in / divider_in;
		}
	}
	else
	{
		m_pll_2_range = e_pll_range::MEDIUM;
		bit::set(*MCU::RCC::PLL_CFGR, 5);
		while(clock_in_divided > 2000000)
		{
			divider_in++;
			if(divider_in > 63)
			{
				return(FAIL);
			}
			clock_in_divided = clock_in / divider_in;
		}
	}
	
	
	//	Set correct Input Frequency Range
	uint32 mask = 0;
	if(clock_in_divided > 1000000 && clock_in_divided <= 2000000)
	{
		mask = 0x0;
	}
	else
	{
		if(clock_in_divided > 2000000 && clock_in_divided <= 4000000)
		{
			mask = 0x1;
		}
		else
		{
			if(clock_in_divided > 4000000 && clock_in_divided <= 8000000)
			{
				mask = 0x2;
			}
			else
			{
				if(clock_in_divided > 8000000 && clock_in_divided <= 16000000)
				{
					mask = 0x3;
				}
			}
		}
	}
	bit::fieldWrite(*MCU::RCC::PLL_CFGR, 6, 2, mask);
	
	
	//	Compute Multiplier
	const double multiplier = clock_out / clock_in_divided;
	if(multiplier < 4 || multiplier > 512)
	{
		return(FAIL);
	}

	const uint32 multiplier_int = (uint32) multiplier;
	const uint32 multiplier_frac = (uint32) ((multiplier - multiplier_int) * 0x2000);
	
	
	//	Write Multiplier Values
	bit::fieldWrite(*MCU::RCC::PLL2_DIVR, 0, 9, multiplier_int - 1);
	
	
	//	PLL 2 Latch
	bit::clear(*MCU::RCC::PLL_CFGR, 4);
	bit::fieldWrite(*MCU::RCC::PLL2_FRACR, 3, 13, multiplier_frac);
	bit::set(*MCU::RCC::PLL_CFGR, 4);
	
	
	//	Write Divider Values
	bit::fieldWrite(*MCU::RCC::PLL_CKSELR, 12, 6, divider_in);
	bit::fieldWrite(*MCU::RCC::PLL2_DIVR,  9, 7, divider_p - 1);
	bit::fieldWrite(*MCU::RCC::PLL2_DIVR, 16, 7, divider_q - 1);
	bit::fieldWrite(*MCU::RCC::PLL2_DIVR, 24, 7, divider_r - 1);
	
	
	//	Store Settings
	m_divider_pll_2_p = divider_p;
	m_divider_pll_2_q = divider_q;
	m_divider_pll_2_r = divider_r;
	m_clock_pll_2 = clock_out;
	
	
	//	Enable PLL 2
	bit::set(*MCU::RCC::CR, 26);
	
	
	//	Wait for PLL 2 to lock
	while(bit::isCleared(*MCU::RCC::CR, 27))
	{
		
	}
	return(OK);
}


feedback RCC::pll_3_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	//	Boundary Check
	if(clock_out < 150000000 || divider_p > 128 || divider_q > 128 || divider_r > 128)
	{
		return(FAIL);
	}
	
	
	//	Evaluate PLL Input Frequency
	uint32 clock_in = 0;
	switch(m_clockSource_pll)
	{
		case e_clockSource_pll::HSI:
		{
			clock_in = c_clock_hsi / m_divider_hsi;
		}
		break;
		
		case e_clockSource_pll::CSI:
		{
			return(FAIL);
		}
		break;
		
		case e_clockSource_pll::HSE:
		{
			clock_in = c_clock_hse;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
		break;
	}
	
	
	//	Check Input and Output Frequency Ranges
	if((clock_out > 420000000 && clock_in < 2000000) || clock_in < 1000000)
	{
		return(FAIL);
	}
	
	
	//	Disable PLL 3
	bit::clear(*MCU::RCC::CR, 28);
	while(bit::isSet(*MCU::RCC::CR, 29))
	{
		
	}
	
	
	//	Enable or Disable Outputs
	if(divider_p == 0)
	{
		bit::clear(*MCU::RCC::PLL_CFGR, 22);
	}
	else
	{
		bit::set(*MCU::RCC::PLL_CFGR, 22);
	}
	if(divider_q == 0)
	{
		bit::clear(*MCU::RCC::PLL_CFGR, 23);
	}
	else
	{
		bit::set(*MCU::RCC::PLL_CFGR, 23);
	}
	if(divider_r == 0)
	{
		bit::clear(*MCU::RCC::PLL_CFGR, 24);
	}
	else
	{
		bit::set(*MCU::RCC::PLL_CFGR, 24);
	}
	
	
	//	Select VCO and Input Divider
	uint32 divider_in = 1;
	uint32 clock_in_divided = clock_in / divider_in;
	
	if(clock_out >= 192000000 && clock_in >= 2000000)
	{
		m_pll_3_range = e_pll_range::WIDE;
		bit::clear(*MCU::RCC::PLL_CFGR, 9);
		while(clock_in_divided > 16000000)
		{
			divider_in++;
			if(divider_in > 63)
			{
				return(FAIL);
			}
			clock_in_divided = clock_in / divider_in;
		}
	}
	else
	{
		m_pll_3_range = e_pll_range::MEDIUM;
		bit::set(*MCU::RCC::PLL_CFGR, 9);
		while(clock_in_divided > 2000000)
		{
			divider_in++;
			if(divider_in > 63)
			{
				return(FAIL);
			}
			clock_in_divided = clock_in / divider_in;
		}
	}
	
	
	//	Set correct Input Frequency Range
	uint32 mask = 0;
	if(clock_in_divided > 1000000 && clock_in_divided <= 2000000)
	{
		mask = 0x0;
	}
	else
	{
		if(clock_in_divided > 2000000 && clock_in_divided <= 4000000)
		{
			mask = 0x1;
		}
		else
		{
			if(clock_in_divided > 4000000 && clock_in_divided <= 8000000)
			{
				mask = 0x2;
			}
			else
			{
				if(clock_in_divided > 8000000 && clock_in_divided <= 16000000)
				{
					mask = 0x3;
				}
			}
		}
	}
	bit::fieldWrite(*MCU::RCC::PLL_CFGR, 10, 2, mask);
	
	
	//	Compute Multiplier
	const double multiplier = clock_out / clock_in_divided;
	if(multiplier < 4 || multiplier > 512)
	{
		return(FAIL);
	}
	
	const uint32 multiplier_int = (uint32) multiplier;
	const uint32 multiplier_frac = (uint32) ((multiplier - multiplier_int) * 0x2000);
	
	
	//	Write Multiplier Values
	bit::fieldWrite(*MCU::RCC::PLL3_DIVR, 0, 9, multiplier_int - 1);
	
	
	//	PLL 3 Latch
	bit::clear(*MCU::RCC::PLL_CFGR, 8);
	bit::fieldWrite(*MCU::RCC::PLL3_FRACR, 3, 13, multiplier_frac);
	bit::set(*MCU::RCC::PLL_CFGR, 8);
	
	
	//	Write Divider Values
	bit::fieldWrite(*MCU::RCC::PLL_CKSELR, 20, 6, divider_in);
	bit::fieldWrite(*MCU::RCC::PLL3_DIVR,  9, 7, divider_p - 1);
	bit::fieldWrite(*MCU::RCC::PLL3_DIVR, 16, 7, divider_q - 1);
	bit::fieldWrite(*MCU::RCC::PLL3_DIVR, 24, 7, divider_r - 1);
	
	
	//	Store Settings
	m_divider_pll_3_p = divider_p;
	m_divider_pll_3_q = divider_q;
	m_divider_pll_3_r = divider_r;
	m_clock_pll_3 = clock_out;
	
	
	//	Enable PLL 3
	bit::set(*MCU::RCC::CR, 28);
	
	
	//	Wait for PLL 3 to lock
	while(bit::isCleared(*MCU::RCC::CR, 29))
	{
		
	}
	return(OK);
}







RCC::e_clockSource_system RCC::get_clockSource_system()
{
	const uint32 bits = bit::fieldRead(*MCU::RCC::CFGR, 3, 3);
	return((e_clockSource_system) bits);
}


feedback RCC::set_clockSource_system(e_clockSource_system clockSource)
{
	uint32 newClock = 0;
	switch(clockSource)
	{
		case e_clockSource_system::HSI:
		{
			newClock = c_clock_hsi / m_divider_hsi;
		}
		break;
		
		case e_clockSource_system::CSI:
		{
			newClock = c_clock_csi;
		}
		break;
		
		case e_clockSource_system::HSE:
		{
			newClock = c_clock_hse;
		}
		break;
		
		case e_clockSource_system::PLL1:
		{
			newClock = m_clock_pll_1 / m_divider_pll_1_p;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
		break;
	}
	
	
	STM32H753BIT6& stm32 = STM32H753BIT6::get();
	Flash& flash = stm32.get_flash();
	PWR& pwr = stm32.get_pwr();
	if(newClock > m_clock_system)
	{
		if(set_busPrescaler(newClock) != OK)
		{
			return(FAIL);
		}
		
		
		flash.set_waitStates(m_clock_ahb, pwr.get_voltageLevel());
		
		
		//	Switch System Clock Source
		bit::fieldWrite(*MCU::RCC::CFGR, 0, 3, (uint32) clockSource);
		
		
		//	Check if Switch was successful
		if(get_clockSource_system() != clockSource)
		{
			return(FAIL);
		}
	}
	else
	{
		//	Switch System Clock Source
		bit::fieldWrite(*MCU::RCC::CFGR, 0, 3, (uint32) clockSource);
		
		
		//	Check if Switch was successful
		if(get_clockSource_system() != clockSource)
		{
			return(FAIL);
		}
		if(set_busPrescaler(newClock) != OK)
		{
			return(FAIL);
		}
		flash.set_waitStates(m_clock_ahb, pwr.get_voltageLevel());
	}
	
	
	//	Store Settings
	m_clock_system = newClock;
	m_clockSource_system = clockSource;
	
	return(OK);
}







RCC::e_resetReason RCC::check_resetReason()
{
	static uint32 temp;
	e_resetReason resetReason = e_resetReason::NONE;
	
	
	
	if(temp == 0)
	{
		temp = *MCU::RCC::RSR & 0x55FB0000;
	}
	
	
	
	if(bit::isSet(temp, 30))
	{
		bit::clear(temp, 30);
		resetReason = e_resetReason::ILLEGAL_D1DSTANDBY_OR_CPUCSTOP;
	}
	else if(bit::isSet(temp, 28))
	{
		bit::clear(temp, 28);
		resetReason = e_resetReason::WWDG;
	}
	else if(bit::isSet(temp, 26))
	{
		bit::clear(temp, 26);
		resetReason = e_resetReason::IWDG;
	}
	else if(bit::isSet(temp, 24))
	{
		bit::clear(temp, 24);
		resetReason = e_resetReason::CPU_FLAG;
	}
	else if(bit::isSet(temp, 23))
	{
		bit::clear(temp, 23);
		resetReason = e_resetReason::POWER_ON_OFF;
	}
	else if(bit::isSet(temp, 22))
	{
		bit::clear(temp, 22);
		resetReason = e_resetReason::PIN;
	}
	else if(bit::isSet(temp, 21))
	{
		bit::clear(temp, 21);
		resetReason = e_resetReason::BROWNOUT;
	}
	else if(bit::isSet(temp, 20))
	{
		bit::clear(temp, 20);
		resetReason = e_resetReason::D2_POWERSWITCH_FLAG;
	}
	else if(bit::isSet(temp, 19))
	{
		bit::clear(temp, 19);
		resetReason = e_resetReason::D1_POWERSWITCH_FLAG;
	}
	else if(bit::isSet(temp, 17))
	{
		bit::clear(temp, 17);
		resetReason = e_resetReason::CPU;
	}
	
	if(temp == 0)
	{
		bit::set(*MCU::RCC::RSR, 16);																																																//  Clear Reset Flags
	}
	
	return(resetReason);
}







feedback RCC::mco_1_init(e_clockSource_mco_1 clockSource, uint32 divider)
{
	if(clockSource != m_clockSource_mco_1)
	{
		//	Boundary Check
		const uint32 mask = (uint32) clockSource;
		if(mask > 0x4)
		{
			return(FAIL);
		}
		
		
		//	Write Clock Source
		bit::fieldWrite(*MCU::RCC::CFGR, 22, 3, mask);
		
		
		//	Store Setting
		m_clockSource_mco_1 = clockSource;
	}
	
	if(divider != m_divider_mco_1)
	{
		//	Boundary Check
		if(divider > 15)
		{
			return(FAIL);
		}
		
		
		//	Write Divider
		bit::fieldWrite(*MCU::RCC::CFGR, 18, 4, divider);
		
		
		//	Store Setting
		m_divider_mco_1 = divider;
	}
	return(OK);
}


feedback RCC::mco_2_init(e_clockSource_mco_2 clockSource, uint32 divider)
{
	if(clockSource != m_clockSource_mco_2)
	{
		//	Boundary Check
		const uint32 mask = (uint32) clockSource;
		if(mask > 0x5)
		{
			return(FAIL);
		}
		
		
		//	Write Clock Source
		bit::fieldWrite(*MCU::RCC::CFGR, 29, 3, mask);
		
		
		//	Store Setting
		m_clockSource_mco_2 = clockSource;
	}

	if(divider != m_divider_mco_2)
	{
		//	Boundary Check
		if(divider > 15)
		{
			return(FAIL);
		}
		
		
		//	Write Divider
		bit::fieldWrite(*MCU::RCC::CFGR, 25, 4, divider);
		
		
		//	Store Setting
		m_divider_mco_2 = divider;
	}
	return(OK);
}







feedback RCC::module_clockInit(e_module module, bool enable)
{
	const uint32 offset = (((uint32) module) & 0x0000FF00) >> 8;
	volatile uint32* reg = MCU::RCC::AHB3_ENR + offset;
	
	const uint32 bit = ((uint32) module) & 0x000000FF;
	
	if(enable == true)
	{
		bit::set(*reg, bit);
	}
	else
	{
		bit::clear(*reg, bit);
	}
	return(OK);
}


feedback RCC::module_reset(e_module module)
{
	const uint32 offset = (((uint32) module) & 0x0000FF00) >> 8;
	volatile uint32* reg = MCU::RCC::AHB3_RSTR + offset;
	
	const uint32 bit = ((uint32) module) & 0x000000FF;
	
	
	//	Set Reset Bit
	bit::set(*reg, bit);
	while(bit::isCleared(*reg, bit))
	{
		
	}
	
	
	//	Clear Reset Bit
	bit::clear(*reg, bit);
	while(bit::isSet(*reg, bit))
	{
		
	}
	return(OK);
}







feedback RCC::set_clockSource(e_clockSource_perck clockSource)
{
	//	Determine Bit Mask
	uint32 mask = 0x0;
	switch(clockSource)
	{
		case e_clockSource_perck::HSI:
		{
			mask = 0x0;
			m_clock_perck = c_clock_hsi;
		}
		break;
		
		case e_clockSource_perck::CSI:
		{
			mask = 0x1;
			m_clock_perck = c_clock_csi;
		}
		break;
		
		case e_clockSource_perck::HSE:
		{
			mask = 0x2;
			m_clock_perck = c_clock_hse;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
		break;
	}
	
	
	//	Write Clock Source
	bit::fieldWrite(*MCU::RCC::D1_CCIPR, 28, 2, mask);
	
	
	//	Store Setting
	m_clockSource_perck = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_adc clockSource)
{
	//	Check if Clock Source is already set
	if(m_clockSource_adc == clockSource)
	{
		return(OK);
	}
	
	
	//	Write Clock Source
	bit::fieldWrite(*MCU::RCC::D3_CCIPR, 16, 2, (uint32) clockSource);
	
	
	//	Store Setting
	m_clockSource_adc = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_sdmmc clockSource)
{
	//	Check if Clock Source is already set
	if(m_clockSource_sdmmc == clockSource)
	{
		return(OK);
	}
	
	
	//	Write Clock Source
	bit::fieldWrite(*MCU::RCC::D1_CCIPR, 16, 2, (uint32) clockSource);
	
	
	//	Store Setting
	m_clockSource_sdmmc = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_uart clockSource, uint32 uartNumber)
{
	//	Check which UART is selected, because UART1 and UART6 share the same Bits
	if(uartNumber == 1 || uartNumber == 6)
	{
		//	Check if Clock Source is already set
		if(m_clockSource_uart_1_6 == clockSource)
		{
			return(OK);
		}
		
		
		//	Write Clock Source
		bit::fieldWrite(*MCU::RCC::D2_CCIP2R, 3, 3, (uint32) clockSource);
		
		
		//	Store Setting
		m_clockSource_uart_1_6 = clockSource;
		return(OK);
	}
	else
	{
		//	Check if Clock Source is already set
		if(m_clockSource_uart_234578 == clockSource)
		{
			return(OK);
		}
		
		
		//	Write Clock Source
		bit::fieldWrite(*MCU::RCC::D2_CCIP2R, 0, 3, (uint32) clockSource);
		
		
		//	Store Setting
		m_clockSource_uart_234578 = clockSource;
		return(OK);
	}
}


feedback RCC::set_clockSource(e_clockSource_fmc clockSource)
{
	//	Check if Clock Source is already set
	if(m_clockSource_fmc == clockSource)
	{
		return(OK);
	}
	
	
	//	Write Clock Source
	bit::fieldWrite(*MCU::RCC::D1_CCIPR, 0, 2, (uint32) clockSource);
	
	
	//	Store Setting
	m_clockSource_fmc = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_can clockSource)
{
	//	Check if Clock Source is already set
	if(m_clockSource_can == clockSource)
	{
		return(OK);
	}
	
	
	//	Write Clock Source
	bit::fieldWrite(*MCU::RCC::D2_CCIP1R, 28, 2, (uint32) clockSource);
	
	
	//	Store Setting
	m_clockSource_can = clockSource;
	return(OK);
}