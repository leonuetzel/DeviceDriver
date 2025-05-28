#include "../Inc/rcc.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback RCC::set_busPrescaler(uint32 newClock)
{
	m_divider_core = 1;
	m_divider_ahb  = 1;
	m_divider_apb1 = 1;
	m_divider_apb2 = 1;
	m_divider_apb3 = 1;
	m_divider_apb4 = 1;
	
	
	
	uint32 mask_core = 0x7;
	while(newClock / m_divider_core > c_clock_core_max)																																						//	Core Prescaler
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
	
	
	
	uint32 mask_ahb = 0x7;
	while(m_clock_core / m_divider_ahb > c_clock_ahb_max)																																					//	AHB Prescaler
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
	
	
	
	uint32 mask_apb1 = 0x3;
	while(m_clock_ahb / m_divider_apb1 > c_clock_apb1_max)																																				//	APB1 Prescaler
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
	
	
	
	uint32 mask_apb2 = 0x3;
	while(m_clock_ahb / m_divider_apb2 > c_clock_apb2_max)																																				//	APB2 Prescaler
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
	
	
	
	uint32 mask_apb3 = 0x3;
	while(m_clock_ahb / m_divider_apb3 > c_clock_apb3_max)																																				//	APB3 Prescaler
	{
		m_divider_apb3 *= 2;
		mask_apb3++;
		if(m_divider_apb3 > 16)
		{
			return(FAIL);
		}
	}
	m_clock_apb3 = m_clock_ahb / m_divider_apb3;
	
	
	
	uint32 mask_apb4 = 0x3;
	while(m_clock_ahb / m_divider_apb4 > c_clock_apb4_max)																																				//	APB4 Prescaler
	{
		m_divider_apb4 *= 2;
		mask_apb4++;
		if(m_divider_apb4 > 16)
		{
			return(FAIL);
		}
	}
	m_clock_apb4 = m_clock_ahb / m_divider_apb4;
	
	
	
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

feedback RCC::startup()
{
	return(OK);
}







feedback RCC::HSE_init(bool enable)
{
	if(enable == true)
	{
		bit::clear(*MCU::RCC::CR, 18);																																															//	HSE not bypassed
		bit::set(*MCU::RCC::CR, 19);																																																//	HSE Clock Security System Enable
		bit::set(*MCU::RCC::CR, 16);																																																//	HSE Enable
		while(bit::isCleared(*MCU::RCC::CR, 17))																																										//	Wait for HSE to become stable
		{
			
		}
	}
	else
	{
		bit::clear(*MCU::RCC::CR, 16);																																															//	Try to disable HSE
		if(bit::isSet(*MCU::RCC::CR, 16))																																														//	Check if HSE is disabled
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
		bit::set(*MCU::RCC::CR, 0);																																																	//	Enable HSI
		while(bit::isCleared(*MCU::RCC::CR, 2))																																											//	Wait for HSI to become stable
		{

		}
		
		uint32 mask = 0x0;
		switch(divider)
		{
			case 1:
				mask = 0x0;
				break;
				
			case 2:
				mask = 0x1;
				break;
				
			case 4:
				mask = 0x2;
				break;
				
			case 8:
				mask = 0x3;
				break;
				
			default:
				return(FAIL);
		}
		
		uint32 temp = *MCU::RCC::CR & 0xFFFFFFE7;
		*MCU::RCC::CR = temp | (mask << 3);																																													//	Set new Divider
		if((*MCU::RCC::CR & 0x00000018) != (mask << 3))																																							//	Check for Divider to be set correctly
		{
			return(FAIL);
		}
		while(bit::isCleared(*MCU::RCC::CR, 5))																																											//	Wait for new Frequency to match set one
		{
			
		}
		
		m_divider_hsi = divider;
	}
	else
	{
		bit::clear(*MCU::RCC::CR, 0);																																																//	Try to disable HSI
		if(bit::isSet(*MCU::RCC::CR, 0))																																														//	Check if HSI is disabled
		{
			return(FAIL);
		}
	}
	
	return(OK);
}











feedback RCC::set_clockSource_pll(e_clockSource_pll clockSource)
{
	if(get_clockSource_system() == e_clockSource_system::PLL1)																																		//	Check if PLL1 delivers System Clock
	{
		if(HSI_init(true, 1) != OK)
		{
			return(FAIL);
		}																																																														//	Set HSI as System Clock Source
		set_clockSource_system(e_clockSource_system::HSI);
	}

	uint32 temp_rcc_cr = *MCU::RCC::CR;
	bit::clear(*MCU::RCC::CR, 28);																																																//	Disable all PLLs
	bit::clear(*MCU::RCC::CR, 26);
	bit::clear(*MCU::RCC::CR, 24);


	uint32 mask = (uint32) clockSource;
	if(mask > 0x3)
	{
		return(FAIL);
	}

	uint32 temp = *MCU::RCC::PLL_CKSELR & 0xFFFFFFFC;
	*MCU::RCC::PLL_CKSELR = temp | mask;
	if((*MCU::RCC::PLL_CKSELR & 0x0000000003) != mask)
	{
		return(FAIL);
	}



	if(bit::isSet(temp_rcc_cr, 28))																																																//	Enable PLLs if they have been enabled before
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
	if(clock_out < 150000000 || divider_p > 128 || divider_q > 128 || divider_r > 128 || divider_p % 2 != 0)
	{
		return(FAIL);
	}

	uint32 clock_in = 0;																																																					//	Evaluate PLL Input Frequency
	switch(m_clockSource_pll)
	{
		case e_clockSource_pll::HSI:
			clock_in = c_clock_hsi / m_divider_hsi;
			break;

		case e_clockSource_pll::CSI:
			clock_in = c_clock_csi;
			break;

		case e_clockSource_pll::HSE:
			clock_in = c_clock_hse;
			break;

		default:
			return(FAIL);
	}

	if((clock_out > 420000000 && clock_in < 2000000) || clock_in < 1000000)
	{
		return(FAIL);
	}



	bool pllAsSystemSource = false;																																																//	Check, if PLL 1 is delivering System Clock
	if(get_clockSource_system() == e_clockSource_system::PLL1)
	{
		pllAsSystemSource = true;
		if(HSI_init(true, 1) != OK)
		{
			return(FAIL);
		}
		set_clockSource_system(e_clockSource_system::HSI);
	}
	bit::clear(*MCU::RCC::CR, 24);																																																//	Disable PLL 1
	while(bit::isSet(*MCU::RCC::CR, 25))
	{

	}
	
	
	if(divider_p == 0)																																																						//	Enable or Disable Outputs
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
	
	
	
	uint32 divider_in = 1;
	uint32 clock_in_divided = clock_in / divider_in;

	if(clock_out >= 192000000 && clock_in >= 2000000)																																							//	Select VCO and Input Divider
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

	uint32 mask = 0;																																																							//	Set correct Input Frequency Range
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

	uint32 temp =	*MCU::RCC::PLL_CFGR & 0xFFFFFFF3;
	*MCU::RCC::PLL_CFGR = temp | (mask << 2);



	double multiplier = clock_out / clock_in_divided;																																							//	Compute Multiplier
	if(multiplier < 4 || multiplier > 512)
	{
		return(FAIL);
	}

	uint32 multiplier_int = (uint32) multiplier;
	uint32 multiplier_frac = (uint32) ((multiplier - multiplier_int) * 0x2000);

	temp = *MCU::RCC::PLL1_DIVR & 0xFFFFFE00;																																											//	Write Multiplier Values
	*MCU::RCC::PLL1_DIVR = temp | (multiplier_int - 1);
		
	bit::clear(*MCU::RCC::PLL_CFGR, 0);																																														//	PLL 1 Latch
	temp = *MCU::RCC::PLL1_FRACR & 0xFFFF0007;
	*MCU::RCC::PLL1_FRACR = temp | (multiplier_frac << 3);
	bit::set(*MCU::RCC::PLL_CFGR, 0);

	temp = *MCU::RCC::PLL_CKSELR & 0xFFFFFC0F;																																										//	Write Divider Values
	*MCU::RCC::PLL_CKSELR = temp | (divider_in << 4);

	*MCU::RCC::PLL1_DIVR &= 0x000001FF;
	*MCU::RCC::PLL1_DIVR |= ((divider_r - 1) << 24);
	*MCU::RCC::PLL1_DIVR |= ((divider_q - 1) << 16);
	*MCU::RCC::PLL1_DIVR |= ((divider_p - 1) << 9);

	
	
	bool pll_1_range_wide = false;
	if(m_pll_1_range == e_pll_range::WIDE)
	{
		pll_1_range_wide = true;
	}
	m_pwr.set_voltageLevel(m_pwr.get_requiredVoltageLevel(divider_p, divider_q, divider_r, clock_out, pll_1_range_wide));					//	Adapt Voltage Level according to Frequency
	
	
	
	m_divider_pll_1_p = divider_p;
	m_divider_pll_1_q = divider_q;
	m_divider_pll_1_r = divider_r;
	m_clock_pll_1 = clock_out;
	
	
	
	bit::set(*MCU::RCC::CR, 24);																																																	//	Enable PLL 1
	while(bit::isCleared(*MCU::RCC::CR, 25))																																											//	Wait for PLL 1 to lock
	{

	}

	if(pllAsSystemSource == true)
	{
		set_clockSource_system(e_clockSource_system::PLL1);
	}

	return(OK);
}


feedback RCC::pll_2_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	if(clock_out < 150000000 || divider_p > 128 || divider_q > 128 || divider_r > 128)
	{
		return(FAIL);
	}

	uint32 clock_in = 0;																																																					//	Evaluate PLL Input Frequency
	switch(m_clockSource_pll)
	{
		case e_clockSource_pll::HSI:
			clock_in = c_clock_hsi / m_divider_hsi;
			break;

		case e_clockSource_pll::CSI:
				return(FAIL);
			break;

		case e_clockSource_pll::HSE:
			clock_in = c_clock_hse;
			break;

		default:
			return(FAIL);
	}

	if((clock_out > 420000000 && clock_in < 2000000) || clock_in < 1000000)
	{
		return(FAIL);
	}
	
	
	bit::clear(*MCU::RCC::CR, 26);																																																//	Disable PLL 2
	while(bit::isSet(*MCU::RCC::CR, 27))
	{
		
	}
	
	
	if(divider_p == 0)																																																						//	Enable or Disable Outputs
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
	
	
	
	uint32 divider_in = 1;
	uint32 clock_in_divided = clock_in / divider_in;

	if(clock_out >= 192000000 && clock_in >= 2000000)																																							//	Select VCO and Input Divider
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

	uint32 mask = 0;																																																							//	Set correct Input Frequency Range
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

	uint32 temp =	*MCU::RCC::PLL_CFGR & 0xFFFFFF3F;
	*MCU::RCC::PLL_CFGR = temp | (mask << 6);



	double multiplier = clock_out / clock_in_divided;																																							//	Compute Multiplier
	if(multiplier < 4 || multiplier > 512)
	{
		return(FAIL);
	}

	uint32 multiplier_int = (uint32) multiplier;
	uint32 multiplier_frac = (uint32) ((multiplier - multiplier_int) * 0x2000);

	temp = *MCU::RCC::PLL2_DIVR & 0xFFFFFE00;																																											//	Write Multiplier Values
	*MCU::RCC::PLL2_DIVR = temp | (multiplier_int - 1);

	bit::clear(*MCU::RCC::PLL_CFGR, 4);																																														//	PLL 2 Latch
	temp = *MCU::RCC::PLL2_FRACR & 0xFFFF0007;
	*MCU::RCC::PLL2_FRACR = temp | (multiplier_frac << 3);
	bit::set(*MCU::RCC::PLL_CFGR, 4);
	
	temp = *MCU::RCC::PLL_CKSELR & 0xFFFC0FFF;																																										//	Write Divider Values
	*MCU::RCC::PLL_CKSELR = temp | (divider_in << 12);
	
	*MCU::RCC::PLL2_DIVR &= 0x000001FF;
	*MCU::RCC::PLL2_DIVR |= ((divider_r - 1) << 24);
	*MCU::RCC::PLL2_DIVR |= ((divider_q - 1) << 16);
	*MCU::RCC::PLL2_DIVR |= ((divider_p - 1) << 9);

	m_divider_pll_2_p = divider_p;
	m_divider_pll_2_q = divider_q;
	m_divider_pll_2_r = divider_r;
	m_clock_pll_2 = clock_out;
	
	bit::set(*MCU::RCC::CR, 26);																																																	//	Enable PLL 2
	while(bit::isCleared(*MCU::RCC::CR, 27))																																											//	Wait for PLL 2 to lock
	{
		
	}
	
	return(OK);
}


feedback RCC::pll_3_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	if(clock_out < 150000000 || divider_p > 128 || divider_q > 128 || divider_r > 128)
	{
		return(FAIL);
	}

	uint32 clock_in = 0;																																																					//	Evaluate PLL Input Frequency
	switch(m_clockSource_pll)
	{
		case e_clockSource_pll::HSI:
			clock_in = c_clock_hsi / m_divider_hsi;
			break;

		case e_clockSource_pll::CSI:
			return(FAIL);
			break;

		case e_clockSource_pll::HSE:
			clock_in = c_clock_hse;
			break;

		default:
			return(FAIL);
	}

	if((clock_out > 420000000 && clock_in < 2000000) || clock_in < 1000000)
	{
		return(FAIL);
	}
	
	
	bit::clear(*MCU::RCC::CR, 28);																																																//	Disable PLL 3
	while(bit::isSet(*MCU::RCC::CR, 29))
	{

	}
	
	
	if(divider_p == 0)																																																						//	Enable or Disable Outputs
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
	
	
	
	uint32 divider_in = 1;
	uint32 clock_in_divided = clock_in / divider_in;

	if(clock_out >= 192000000 && clock_in >= 2000000)																																							//	Select VCO and Input Divider
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

	uint32 mask = 0;																																																							//	Set correct Input Frequency Range
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

	uint32 temp =	*MCU::RCC::PLL_CFGR & 0xFFFFF3FF;
	*MCU::RCC::PLL_CFGR = temp | (mask << 10);



	double multiplier = clock_out / clock_in_divided;																																							//	Compute Multiplier
	if(multiplier < 4 || multiplier > 512)
	{
		return(FAIL);
	}

	uint32 multiplier_int = (uint32) multiplier;
	uint32 multiplier_frac = (uint32) ((multiplier - multiplier_int) * 0x2000);

	temp = *MCU::RCC::PLL3_DIVR & 0xFFFFFE00;																																											//	Write Multiplier Values
	*MCU::RCC::PLL3_DIVR = temp | (multiplier_int - 1);

	bit::clear(*MCU::RCC::PLL_CFGR, 8);																																														//	PLL 3 Latch
	temp = *MCU::RCC::PLL3_FRACR & 0xFFFF0007;
	*MCU::RCC::PLL3_FRACR = temp | (multiplier_frac << 3);
	bit::set(*MCU::RCC::PLL_CFGR, 8);
	
	temp = *MCU::RCC::PLL_CKSELR & 0xFC0FFFFF;																																										//	Write Divider Values
	*MCU::RCC::PLL_CKSELR = temp | (divider_in << 20);
	
	*MCU::RCC::PLL3_DIVR &= 0x000001FF;
	*MCU::RCC::PLL3_DIVR |= ((divider_r - 1) << 24);
	*MCU::RCC::PLL3_DIVR |= ((divider_q - 1) << 16);
	*MCU::RCC::PLL3_DIVR |= ((divider_p - 1) << 9);

	m_divider_pll_3_p = divider_p;
	m_divider_pll_3_q = divider_q;
	m_divider_pll_3_r = divider_r;
	m_clock_pll_3 = clock_out;
	
	bit::set(*MCU::RCC::CR, 28);																																																	//	Enable PLL 3
	while(bit::isCleared(*MCU::RCC::CR, 29))																																											//	Wait for PLL 3 to lock
	{
		
	}

	return(OK);
}







RCC::e_clockSource_system RCC::get_clockSource_system()
{
	uint32 mask = (*MCU::RCC::CFGR & 0x00000038) >> 3;
	return((e_clockSource_system) mask);
}


feedback RCC::set_clockSource_system(e_clockSource_system clockSource)
{
	uint32 newClock = 0;
	switch(clockSource)
	{
		case e_clockSource_system::HSI:
			newClock = c_clock_hsi / m_divider_hsi;
			break;

		case e_clockSource_system::CSI:
			newClock = c_clock_csi;
			break;

		case e_clockSource_system::HSE:
			newClock = c_clock_hse;
			break;

		case e_clockSource_system::PLL1:
			newClock = m_clock_pll_1 / m_divider_pll_1_p;
			break;

		default:
			return(FAIL);
	}
	
	
	
	
	
	if(newClock > m_clock_system)
	{
		if(set_busPrescaler(newClock) != OK)
		{
			return(FAIL);
		}
		m_flash.set_waitStates(m_clock_ahb, m_pwr.get_voltageLevel());
		
		uint32 temp = *MCU::RCC::CFGR & 0xFFFFFFF8;																																									//	Switch System Clock Source
		*MCU::RCC::CFGR = temp | (uint32) clockSource;
		
		if(get_clockSource_system() != clockSource)																																									//	Check if Switch was successful
		{
			return(FAIL);
		}
	}
	else
	{
		uint32 temp = *MCU::RCC::CFGR & 0xFFFFFFF8;																																									//	Switch System Clock Source
		*MCU::RCC::CFGR = temp | (uint32) clockSource;
		
		if(get_clockSource_system() != clockSource)																																									//	Check if Switch was successful
		{
			return(FAIL);
		}
		if(set_busPrescaler(newClock) != OK)
		{
			return(FAIL);
		}
		m_flash.set_waitStates(m_clock_ahb, m_pwr.get_voltageLevel());
	}
	
	
	
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
		uint32 mask = (uint32) clockSource;
		if(mask > 0x4)
		{
			return(FAIL);
		}

		uint32 temp = *MCU::RCC::CFGR & 0xFE3FFFFF;
		*MCU::RCC::CFGR = temp | (mask << 22);

		m_clockSource_mco_1 = clockSource;
	}

	if(divider != m_divider_mco_1)
	{
		if(divider > 15)
		{
			return(FAIL);
		}

		uint32 temp = *MCU::RCC::CFGR & 0xFFC3FFFF;
		*MCU::RCC::CFGR = temp | (divider << 18);

		m_divider_mco_1 = divider;
	}

	return(OK);
}


feedback RCC::mco_2_init(e_clockSource_mco_2 clockSource, uint32 divider)
{
	if(clockSource != m_clockSource_mco_2)
	{
		uint32 mask = (uint32) clockSource;
		if(mask > 0x5)
		{
			return(FAIL);
		}

		uint32 temp = *MCU::RCC::CFGR & 0x1FFFFFFF;
		*MCU::RCC::CFGR = temp | (mask << 29);

		m_clockSource_mco_2 = clockSource;
	}

	if(divider != m_divider_mco_2)
	{
		if(divider > 15)
		{
			return(FAIL);
		}

		uint32 temp = *MCU::RCC::CFGR & 0xE1FFFFFF;
		*MCU::RCC::CFGR = temp | (divider << 25);

		m_divider_mco_2 = divider;
	}

	return(OK);
}







feedback RCC::module_clockInit(e_module module, bool enable)
{
	uint32 offset = (((uint32) module) & 0x0000FF00) >> 8;
	volatile uint32* reg = MCU::RCC::AHB3_ENR + offset;
	
	uint32 bit = ((uint32) module) & 0x000000FF;
	
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
	uint32 offset = (((uint32) module) & 0x0000FF00) >> 8;
	volatile uint32* reg = MCU::RCC::AHB3_RSTR + offset;
	
	uint32 bit = ((uint32) module) & 0x000000FF;
	
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







feedback RCC::set_clockSource(e_clockSource_perck clockSource)
{
	uint32 temp = *MCU::RCC::D1_CCIPR & 0xCFFFFFFF;
	uint32 mask = 0;
	switch(clockSource)
	{
		case e_clockSource_perck::HSI:
			mask = 0x0;
			m_clock_perck = c_clock_hsi;
			break;
			
		case e_clockSource_perck::CSI:
			mask = 0x1;
			m_clock_perck = c_clock_csi;
			break;
			
		case e_clockSource_perck::HSE:
			mask = 0x2;
			m_clock_perck = c_clock_hse;
			break;
			
		default:
			return(FAIL);
			break;
	}
	
	*MCU::RCC::D1_CCIPR = temp | (mask << 28);
	m_clockSource_perck = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_adc clockSource)
{
	if(m_clockSource_adc == clockSource)
	{
		return(OK);
	}
	
	uint32 mask = (uint32) clockSource;
	uint32 temp = *MCU::RCC::D3_CCIPR & 0xFFFCFFFF;
	*MCU::RCC::D3_CCIPR = temp | (mask << 16);
	
	m_clockSource_adc = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_sdmmc clockSource)
{
	if(m_clockSource_sdmmc == clockSource)
	{
		return(OK);
	}
	
	uint32 mask = (uint32) clockSource;
	uint32 temp = *MCU::RCC::D1_CCIPR & 0xFFFEFFFF;
	*MCU::RCC::D1_CCIPR = temp | (mask << 16);
	
	m_clockSource_sdmmc = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_uart clockSource, uint32 uartNumber)
{
	if(uartNumber == 1 || uartNumber == 6)
	{
		if(m_clockSource_uart_1_6 == clockSource)
		{
			return(OK);
		}
		uint32 mask = (uint32) clockSource;
		uint32 temp = *MCU::RCC::D2_CCIP2R & 0xFFFFFFC7;
		*MCU::RCC::D2_CCIP2R = temp | (mask << 3);
		
		m_clockSource_uart_1_6 = clockSource;
		return(OK);
	}
	else
	{
		if(m_clockSource_uart_234578 == clockSource)
		{
			return(OK);
		}
		uint32 mask = (uint32) clockSource;
		uint32 temp = *MCU::RCC::D2_CCIP2R & 0xFFFFFFF8;
		*MCU::RCC::D2_CCIP2R = temp | mask;
		
		m_clockSource_uart_234578 = clockSource;
		return(OK);
	}
}


feedback RCC::set_clockSource(e_clockSource_fmc clockSource)
{
	if(m_clockSource_fmc == clockSource)
	{
		return(OK);
	}
	
	uint32 mask = (uint32) clockSource;
	uint32 temp = *MCU::RCC::D1_CCIPR & 0xFFFFFFFC;
	*MCU::RCC::D1_CCIPR = temp | mask;
	
	m_clockSource_fmc = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_can clockSource)
{
	if(m_clockSource_can == clockSource)
	{
		return(OK);
	}
	
	uint32 mask = (uint32) clockSource;
	uint32 temp = *MCU::RCC::D2_CCIP1R & 0xCFFFFFFF;
	*MCU::RCC::D2_CCIP1R = temp | (mask << 28);
	
	m_clockSource_can = clockSource;
	return(OK);
}