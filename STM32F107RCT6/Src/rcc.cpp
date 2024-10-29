#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void RCC::calculate_clockTree()
{
	//	RM0008 - Rev. 21, Chapter 8.2, Figure 11, Page 126
	
	
	//	HSE Clock
	if(m_hse_enabled == true)
	{
		m_clock_hse = c_clock_hse;
	}
	else
	{
		m_clock_hse = 0;
	}
	
	
	//	HSI Clock
	if(m_hsi_enabled == true)
	{
		m_clock_hsi = c_clock_hsi;
	}
	else
	{
		m_clock_hsi = 0;
	}
	
	
	//	LSI Clock
	if(m_lsi_enabled == true)
	{
		m_clock_lsi = c_clock_lsi;
	}
	else
	{
		m_clock_lsi = 0;
	}
	
	
	//	PLL 2
	//	Needs to be calculated before PLL 1 because it can act as Input for PLL 1
	m_clock_pll_2_3_input = m_clock_hse / m_prescaler_pll_2_3_input;
	
	if(m_pll_2_enabled == true)
	{
		m_clock_pll_2 = m_clock_pll_2_3_input * m_multiplier_pll_2;
	}
	else
	{
		m_clock_pll_2 = 0;
	}
	
	
	//	PLL 1
	switch(m_clockSource_pll_1)
	{
		case e_clockSource_pll_1::HSI_DIV2:
		{
			m_clock_pll_1_input = m_clock_hsi / 2;
		}
		break;
		
		case e_clockSource_pll_1::HSE:
		{
			m_clock_pll_1_input = m_clock_hse / m_prescaler_pll_1_input;
		}
		break;
		
		case e_clockSource_pll_1::PLL2:
		{
			m_clock_pll_1_input = m_clock_pll_2 / m_prescaler_pll_1_input;
		}
		break;
		
		default:
		{
			
		}
		return;
	}
	
	if(m_pll_1_enabled == true)
	{
		m_clock_pll_1 = m_clock_pll_1_input * m_multiplier_pll_1;
	}
	else
	{
		m_clock_pll_1 = 0;
	}
	
	
	//	PLL 3
	if(m_pll_3_enabled == true)
	{
		m_clock_pll_3 = m_clock_pll_2_3_input * m_multiplier_pll_3;
	}
	else
	{
		m_clock_pll_3 = 0;
	}
	
	
	//	System Clock
	switch(m_clockSource_system)
	{
		case e_clockSource_system::HSI:
		{
			m_clock_system = m_clock_hsi;
		}
		break;
		
		case e_clockSource_system::HSE:
		{
			m_clock_system = m_clock_hse;
		}
		break;
		
		case e_clockSource_system::PLL_1:
		{
			m_clock_system = m_clock_pll_1;
		}
		break;
		
		default:
		{
			
		}
		return;
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
}


feedback RCC::autoAdjust_AHB_APB1_APB2_prescaler()
{
	//	Save old State
	const uint32 prescaler_ahb_old = m_prescaler_ahb;
	const uint32 prescaler_apb1_old = m_prescaler_apb1;
	const uint32 prescaler_apb2_old = m_prescaler_apb2;
	
	
	//	Compute the best Combination of Prescalers
	constexpr uint32 numberOfPrescaler_ahb = sizeof(c_prescaler_ahb) / sizeof(c_prescaler_ahb[0]);
	constexpr uint32 numberOfPrescaler_apb1 = sizeof(c_prescaler_apb1) / sizeof(c_prescaler_apb1[0]);
	constexpr uint32 numberOfPrescaler_apb2 = sizeof(c_prescaler_apb2) / sizeof(c_prescaler_apb2[0]);
	
	
	for(uint32 prescalerIndex_ahb = 0; prescalerIndex_ahb < numberOfPrescaler_ahb; prescalerIndex_ahb++)
	{
		m_prescaler_ahb = c_prescaler_ahb[prescalerIndex_ahb];
		
		//	Update Clock Tree and check Constraints
		calculate_clockTree();
		
		if(m_clock_ahb <= c_clock_ahb_max)
		{
			for(uint32 prescalerIndex_apb1 = 0; prescalerIndex_apb1 < numberOfPrescaler_apb1; prescalerIndex_apb1++)
			{
				m_prescaler_apb1 = c_prescaler_apb1[prescalerIndex_apb1];
				
				//	Update Clock Tree and check Constraints
				calculate_clockTree();
				
				if(m_clock_apb1 <= c_clock_apb1_max)
				{
					for(uint32 prescalerIndex_apb2 = 0; prescalerIndex_apb2 < numberOfPrescaler_apb2; prescalerIndex_apb2++)
					{
						m_prescaler_apb2 = c_prescaler_apb2[prescalerIndex_apb2];
						
						//	Update Clock Tree and check Constraints
						calculate_clockTree();
						
						if(m_clock_apb2 <= c_clock_apb2_max)
						{
							//	Since Prescaler Values are ordered in ascending Order, the first Time we reach this Point here is the Combination with the highest possible Clocks
							//	Write Configuration
							uint32 temp = *MCU::RCC::CFGR & 0xFFFFC00F;
							*MCU::RCC::CFGR = temp | (prescalerIndex_apb2 << 11) | (prescalerIndex_apb1 << 8) | (prescalerIndex_ahb << 4);
							
							return(OK);
						}
					}
				}
			}
		}
	}
	
	
	//	No valid Configuration was found, so undo Changes
	m_prescaler_ahb = prescaler_ahb_old;
	m_prescaler_apb1 = prescaler_apb1_old;
	m_prescaler_apb2 = prescaler_apb2_old;
	
	calculate_clockTree();
	return(FAIL);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback RCC::init_hse(bool enable)
{
	if(enable == m_hse_enabled)
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
	
	
	m_hse_enabled = enable;
	calculate_clockTree();
	return(OK);
}


feedback RCC::init_hsi(bool enable)
{
	if(enable == m_hsi_enabled)
	{
		return(OK);
	}
	
	
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
	
	
	m_hsi_enabled = enable;
	calculate_clockTree();
	return(OK);
}


feedback RCC::init_lsi(bool enable)
{
	if(enable == m_lsi_enabled)
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
		
		
		//	Check if LSI is disabled
		if(bit::isSet(*MCU::RCC::CSR, 0))
		{
			return(FAIL);
		}
	}
	
	
	m_lsi_enabled = enable;
	calculate_clockTree();
	return(OK);
}







feedback RCC::set_clockSource(e_clockSource_system clockSource)
{
	if(m_clockSource_system == clockSource)
	{
		return(OK);
	}
	
	
	//	Save old Clock Source in case it fails
	const e_clockSource_system clockSourceSystemOld = m_clockSource_system;
	
	
	//	Save old System Clock to know, if we need to set new
	//	-	AHB Prescaler
	//	-	APB1 Prescaler
	//	- APB2 Prescaler
	//	-	Flash Wait States
	//	before or after switching to the knew Clock Source
	//	This depends on if the new System Clock is higher or lower than the old one
	//	because changing these Values while the old Clock is active can lead to overclocking these Modules/Busses
	//	The changing of these Values must be done in the written Order, because Flash Module is Part of AHB Bus and therefore adjusts its Timings
	//	in Dependance of AHB Clock
	const uint32 clock_system_old = m_clock_system;
	
	
	//	Update Clock Tree
	m_clockSource_system = clockSource;
	calculate_clockTree();
	
	
	//	Auto adjust AHB, APB1 and APB2 Prescalers to avoid overclocking the Busses
	//	This must be done before changing the System Clock Source only (and only!) if the new System Clock is higher than the old one
	if(m_clock_system > clock_system_old)
	{
		if(autoAdjust_AHB_APB1_APB2_prescaler() != OK)
		{
			//	Undo Changes and return
			m_clockSource_system = clockSourceSystemOld;
			
			calculate_clockTree();
			
			return(FAIL);
		}
	}
	
	
	//	Flash Wait States
	//	This must be done before changing the System Clock Source only (and only!) if the new System Clock is higher than the old one
	if(m_clock_system > clock_system_old)
	{
		if(m_flash.set_waitStates(m_clock_ahb) != OK)
		{
			//	Undo Changes and return
			m_clockSource_system = clockSourceSystemOld;
			
			calculate_clockTree();
			
			autoAdjust_AHB_APB1_APB2_prescaler();
			
			return(FAIL);
		}
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
	
	
	//	Auto adjust Flash Wait States, AHB, APB1 and APB2 Prescalers
	if(m_clock_system < clock_system_old)
	{
		if(autoAdjust_AHB_APB1_APB2_prescaler() != OK)
		{
			return(FAIL);
		}
		
		
		//	Flash Wait States
		if(m_flash.set_waitStates(m_clock_ahb) != OK)
		{
			return(FAIL);
		}
	}
	
	
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_pll_1 clockSource)
{
	if(m_clockSource_pll_1 == clockSource)
	{
		return(OK);
	}
	
	
	//	Check if PLL 1 is enabled
	if(m_pll_1_enabled == true)
	{
		return(FAIL);
	}
	
	
	//	Set new Clock Source - only allowed if PLL 1 is disabled because init_pll_1() will check if the new Clocks meet the Constraints
	m_clockSource_pll_1 = clockSource;
	calculate_clockTree();
	
	
	//	Set new Values
	//	Bit 0 of the Enum is equal to RCC_CFGR:16
	//	Bit 1 of the Enum is equal to RCC_CFGR2:16
	const uint32 clockSourceRaw = (uint32) clockSource;
	if(bit::isSet(clockSourceRaw, 0) == true)
	{
		bit::set(*MCU::RCC::CFGR, 16);
	}
	else
	{
		bit::clear(*MCU::RCC::CFGR, 16);
	}
	
	if(bit::isSet(clockSourceRaw, 1) == true)
	{
		bit::set(*MCU::RCC::CFGR2, 16);
	}
	else
	{
		bit::clear(*MCU::RCC::CFGR2, 16);
	}
	
	
	return(OK);
}


void RCC::set_clockSource(e_clockSource_mco clockSource)
{
	const uint32 temp = *MCU::RCC::CFGR & 0xF0FFFFFF;
	*MCU::RCC::CFGR = temp | (((uint32) clockSource) << 24);
}


feedback RCC::init_pll_1(uint32 clock_out)
{
	if(m_clock_pll_1 == clock_out && m_pll_1_enabled == true)
	{
		return(OK);
	}
	
	
	//	Check Output Clock Boundaries
	if(clock_out < c_clock_pll_1_output_min || clock_out > c_clock_pll_1_output_max)
	{
		return(FAIL);
	}
	
	
	//	Save old Setup in Case it fails
	const float multiplier_old = m_multiplier_pll_1;
	const uint8 prescaler_old = m_prescaler_pll_1_input;
	const bool enabled_old = m_pll_1_enabled;
	
	
	//	Set "m_pll_1_enabled" to true, so the Computation using "calculate_clockTree()" works
	m_pll_1_enabled = true;
	
	
	//	Compute best Combination of Multiplier and Input Prescaler
	uint32 bestPrescalerIndex = 0;
	uint32 bestMultiplierIndex = 0;
	uint32 smallestDeviation = 0xFFFFFFFF;
	
	constexpr uint32 numberOfPrescalers = sizeof(c_prescaler_pll_1_input) / sizeof(c_prescaler_pll_1_input[0]);
	constexpr uint32 numberOfMultipliers = sizeof(c_multiplier_pll_1) / sizeof(c_multiplier_pll_1[0]);
	
	
	if(m_clockSource_pll_1 == e_clockSource_pll_1::HSI_DIV2)
	{
		//	Input Prescaler is fixed for HSI Input, so we can leave the Input Prescaler at it's old Value
		bestPrescalerIndex = prescaler_old;
		
		
		//	Check if Clocks meet the Constraints
		calculate_clockTree();
		if(m_clock_pll_1_input < c_clock_pll_1_input_min || m_clock_pll_1_input > c_clock_pll_1_input_max)
		{
			//	Undo Changes
			m_prescaler_pll_1_input = prescaler_old;
			m_multiplier_pll_1 = multiplier_old;
			m_pll_1_enabled = enabled_old;
			
			calculate_clockTree();
			
			return(FAIL);
		}
		
		
		for(uint32 multiplierIndex = 0; multiplierIndex < numberOfMultipliers; multiplierIndex++)
		{
			m_multiplier_pll_1 = c_multiplier_pll_1[multiplierIndex];
			
			
			//	Update Clock Tree and check if Clocks meet the Constraints
			calculate_clockTree();
			
			if(m_clock_pll_1 < c_clock_pll_1_output_min || m_clock_pll_1 > c_clock_pll_1_output_max)
			{
				continue;
			}
			
			
			//	Check Deviation from desired Clock
			const uint32 deviation = Math::absolute<int32>(((int32) m_clock_pll_1) - clock_out);
			if(deviation < smallestDeviation)
			{
				//	Save best Configuration
				bestMultiplierIndex = multiplierIndex;
				smallestDeviation = deviation;
			}
		}
	}
	else
	{
		for(uint32 prescalerIndex = 0; prescalerIndex < numberOfPrescalers; prescalerIndex++)
		{
			m_prescaler_pll_1_input = c_prescaler_pll_1_input[prescalerIndex];
			
			
			//	Update Clock Tree and check if Clocks meet the Constraints
			calculate_clockTree();
			if(m_clock_pll_1_input < c_clock_pll_1_input_min || m_clock_pll_1_input > c_clock_pll_1_input_max)
			{
				continue;
			}
			
			
			for(uint32 multiplierIndex = 0; multiplierIndex < numberOfMultipliers; multiplierIndex++)
			{
				m_multiplier_pll_1 = c_multiplier_pll_1[multiplierIndex];
				
				
				//	Update Clock Tree and check if Clocks meet the Constraints
				calculate_clockTree();
				
				if(m_clock_pll_1 < c_clock_pll_1_output_min || m_clock_pll_1 > c_clock_pll_1_output_max)
				{
					continue;
				}
				
				
				//	Check Deviation from desired Clock
				const uint32 deviation = Math::absolute<int32>(((int32) m_clock_pll_1) - clock_out);
				if(deviation < smallestDeviation)
				{
					//	Save best Configuration
					bestPrescalerIndex = prescalerIndex;
					bestMultiplierIndex = multiplierIndex;
					smallestDeviation = deviation;
				}
			}
		}
	}
	
	
	//	Check if valid Configuration has been found
	if(smallestDeviation == 0xFFFFFFFF)
	{
		//	Undo Changes
		m_prescaler_pll_1_input = prescaler_old;
		m_multiplier_pll_1 = multiplier_old;
		m_pll_1_enabled = enabled_old;
		
		calculate_clockTree();
		
		return(FAIL);
	}
	
	
	//	Check, if PLL 1 is delivering System Clock and switch to HSI if so
	bool pllAsSystemSource = false;
	const bool was_HSI_enabled = m_hsi_enabled;
	if(m_clockSource_system == e_clockSource_system::PLL_1)
	{
		pllAsSystemSource = true;
		if(init_hsi(true) != OK)
		{
			//	Undo Changes
			m_prescaler_pll_1_input = prescaler_old;
			m_multiplier_pll_1 = multiplier_old;
			m_pll_1_enabled = enabled_old;
			
			calculate_clockTree();
			
			return(FAIL);
		}
		if(set_clockSource(e_clockSource_system::HSI) != OK)
		{
			//	Undo Changes
			init_hsi(was_HSI_enabled);
			
			m_prescaler_pll_1_input = prescaler_old;
			m_multiplier_pll_1 = multiplier_old;
			m_pll_1_enabled = enabled_old;
			
			calculate_clockTree();
			
			return(FAIL);
		}
	}
	
	
	//	Disable PLL 1
	bit::clear(*MCU::RCC::CR, 24);
	while(bit::isSet(*MCU::RCC::CR, 25))
	{
		
	}
	m_pll_1_enabled = false;
	
	
	//	Write Multiplier Value
	uint32 temp = *MCU::RCC::CFGR & 0xFFC3FFFF;
	*MCU::RCC::CFGR = temp | (bestMultiplierIndex << 18);
	
	
	//	Write Input Prescaler Value
	temp = *MCU::RCC::CFGR2 & 0xFFFFFFF0;
	*MCU::RCC::CFGR2 = temp | bestPrescalerIndex;
	
	
	//	Enable PLL 1
	bit::set(*MCU::RCC::CR, 24);
	
	
	//	Wait for PLL 1 to lock
	while(bit::isCleared(*MCU::RCC::CR, 25))
	{
		
	}
	m_pll_1_enabled = true;
	
	
	//	Save new Configuration and Update Clock Tree
	m_multiplier_pll_1 = c_multiplier_pll_1[bestMultiplierIndex];
	m_prescaler_pll_1_input = c_prescaler_pll_1_input[bestPrescalerIndex];
	
	calculate_clockTree();
	
	
	//	Switch back to PLL 1 as System Clock Source if it was before
	if(pllAsSystemSource == true)
	{
		if(set_clockSource(e_clockSource_system::PLL_1) != OK)
		{
			return(FAIL);
		}
		if(init_hsi(was_HSI_enabled) != OK)
		{
			return(FAIL);
		}
	}
	
	
	return(OK);
}


feedback RCC::init_pll_2_3(uint32 clock_out_pll2, uint32 clock_out_pll3)
{
	if(m_clock_pll_2 == clock_out_pll2 && m_pll_2_enabled == true && m_clock_pll_3 == clock_out_pll3 && m_pll_3_enabled == true)
	{
		return(OK);
	}
	
	
	//	Check Output Clock Boundaries
	if(clock_out_pll2 < c_clock_pll_2_output_min || clock_out_pll2 > c_clock_pll_2_output_max)
	{
		return(FAIL);
	}
	if(clock_out_pll3 < c_clock_pll_3_output_min || clock_out_pll3 > c_clock_pll_3_output_max)
	{
		return(FAIL);
	}
	
	
	//	Save old Setup in Case it fails
	const float multiplier_pll2_old = m_multiplier_pll_2;
	const float multiplier_pll3_old = m_multiplier_pll_3;
	const uint8 prescaler_old = m_prescaler_pll_2_3_input;
	const bool enabled_pll2_old = m_pll_2_enabled;
	const bool enabled_pll3_old = m_pll_3_enabled;
	
	
	//	Set "m_pll_2_enabled" and "m_pll_3_enabled" to true, so the Computation using "calculate_clockTree()" works
	m_pll_2_enabled = true;
	m_pll_3_enabled = true;
	
	
	//	Compute best Combination of Multiplier and Input Prescaler
	uint32 bestPrescalerIndex = 0;
	uint32 bestMultiplierPll2Index = 0;
	uint32 bestMultiplierPll3Index = 0;
	uint32 smallestDeviation = 0xFFFFFFFF;
	
	constexpr uint32 numberOfPrescalers = sizeof(c_prescaler_pll_2_3_input) / sizeof(c_prescaler_pll_2_3_input[0]);
	constexpr uint32 numberOfMultipliersPll2 = sizeof(c_multiplier_pll_2) / sizeof(c_multiplier_pll_2[0]);
	constexpr uint32 numberOfMultipliersPll3 = sizeof(c_multiplier_pll_3) / sizeof(c_multiplier_pll_3[0]);
	
	
	for(uint32 prescalerIndex = 0; prescalerIndex < numberOfPrescalers; prescalerIndex++)
	{
		m_prescaler_pll_2_3_input = c_prescaler_pll_2_3_input[prescalerIndex];
		
		
		//	Update Clock Tree and check if Clocks meet the Constraints
		calculate_clockTree();
		if(m_clock_pll_2_3_input < c_clock_pll_2_3_input_min || m_clock_pll_2_3_input > c_clock_pll_2_3_input_max)
		{
			continue;
		}
		
		
		for(uint32 multiplierPll2Index = 0; multiplierPll2Index < numberOfMultipliersPll2; multiplierPll2Index++)
		{
			m_multiplier_pll_2 = c_multiplier_pll_2[multiplierPll2Index];
			
			
			for(uint32 multiplierPll3Index = 0; multiplierPll3Index < numberOfMultipliersPll3; multiplierPll3Index++)
			{
				m_multiplier_pll_3 = c_multiplier_pll_3[multiplierPll3Index];
				
				
				//	Update Clock Tree and check if Clocks meet the Constraints
				calculate_clockTree();
				
				if(m_clock_pll_2 < c_clock_pll_2_output_min || m_clock_pll_2 > c_clock_pll_2_output_max)
				{
					continue;
				}
				
				if(m_clock_pll_3 < c_clock_pll_3_output_min || m_clock_pll_3 > c_clock_pll_3_output_max)
				{
					continue;
				}
				
				
				//	Check Deviation from desired Clock
				const uint32 deviation_pll2 = Math::absolute<int32>(((int32) m_clock_pll_2) - clock_out_pll2);
				const uint32 deviation_pll3 = Math::absolute<int32>(((int32) m_clock_pll_3) - clock_out_pll3);
				const uint32 deviation = deviation_pll2 + deviation_pll3;
				
				if(deviation < smallestDeviation)
				{
					//	Save best Configuration
					bestPrescalerIndex = prescalerIndex;
					bestMultiplierPll2Index = multiplierPll2Index;
					bestMultiplierPll3Index = multiplierPll3Index;
					smallestDeviation = deviation;
				}
			}
		}
	}
	
	
	//	Check if valid Configuration has been found
	if(smallestDeviation == 0xFFFFFFFF)
	{
		//	Undo Changes
		m_prescaler_pll_2_3_input = prescaler_old;
		m_multiplier_pll_2 = multiplier_pll2_old;
		m_multiplier_pll_3 = multiplier_pll3_old;
		m_pll_2_enabled = enabled_pll2_old;
		m_pll_3_enabled = enabled_pll3_old;
		
		calculate_clockTree();
		
		return(FAIL);
	}
	
	
	//	Check, if PLL 2 is acting as input for PLL 1 and if PLL 1 is delivering System Clock and switch to HSI if so
	bool pllAsSystemSource = false;
	const bool was_HSI_enabled = m_hsi_enabled;
	if(m_clockSource_pll_1 == e_clockSource_pll_1::PLL2 && m_clockSource_system == e_clockSource_system::PLL_1)
	{
		pllAsSystemSource = true;
		if(init_hsi(true) != OK)
		{
			//	Undo Changes
			m_prescaler_pll_2_3_input = prescaler_old;
			m_multiplier_pll_2 = multiplier_pll2_old;
			m_multiplier_pll_3 = multiplier_pll3_old;
			m_pll_2_enabled = enabled_pll2_old;
			m_pll_3_enabled = enabled_pll3_old;
			
			calculate_clockTree();
			
			return(FAIL);
		}
		if(set_clockSource(e_clockSource_system::HSI) != OK)
		{
			//	Undo Changes
			init_hsi(was_HSI_enabled);
			
			m_prescaler_pll_2_3_input = prescaler_old;
			m_multiplier_pll_2 = multiplier_pll2_old;
			m_multiplier_pll_3 = multiplier_pll3_old;
			m_pll_2_enabled = enabled_pll2_old;
			m_pll_3_enabled = enabled_pll3_old;
			
			calculate_clockTree();
			
			return(FAIL);
		}
	}
	
	
	//	Disable PLL 2
	bit::clear(*MCU::RCC::CR, 26);
	while(bit::isSet(*MCU::RCC::CR, 27))
	{
		
	}
	m_pll_2_enabled = false;
	
	
	//	Disable PLL 3
	bit::clear(*MCU::RCC::CR, 28);
	while(bit::isSet(*MCU::RCC::CR, 29))
	{
		
	}
	m_pll_3_enabled = false;
	
	
	//	Write Multiplier and Prescaler Values
	uint32 temp = *MCU::RCC::CFGR2 & 0xFFFF000F;
	*MCU::RCC::CFGR2 = temp | (bestMultiplierPll3Index << 12) | (bestMultiplierPll2Index << 8) | (bestPrescalerIndex << 4);
	
	
	//	Enable PLL 2
	bit::set(*MCU::RCC::CR, 26);
	
	
	//	Wait for PLL 2 to lock
	while(bit::isCleared(*MCU::RCC::CR, 27))
	{
		
	}
	m_pll_2_enabled = true;
	
	
	//	Enable PLL 3
	bit::set(*MCU::RCC::CR, 28);
	
	
	//	Wait for PLL 3 to lock
	while(bit::isCleared(*MCU::RCC::CR, 29))
	{
		
	}
	m_pll_3_enabled = true;
	
	
	//	Save new Configuration and Update Clock Tree
	m_multiplier_pll_2 = c_multiplier_pll_2[bestMultiplierPll2Index];
	m_multiplier_pll_3 = c_multiplier_pll_3[bestMultiplierPll3Index];
	m_prescaler_pll_2_3_input = c_prescaler_pll_2_3_input[bestPrescalerIndex];
	
	calculate_clockTree();
	
	
	//	Re-initialize PLL 1 with new Values Switch back to PLL 1 as System Clock Source if it was before
	if(pllAsSystemSource == true)
	{
		if(set_clockSource(e_clockSource_system::PLL_1) != OK)
		{
			return(FAIL);
		}
		if(init_hsi(was_HSI_enabled) != OK)
		{
			return(FAIL);
		}
	}
	
	
	return(OK);
}







feedback RCC::module_clockInit(e_module module, bool enable)
{
	uint32 module_index = (uint32) module;
	uint32 offset = (module_index & 0x0000FF00) >> 8;
	volatile uint32* reg = MCU::RCC::AHB_ENR + offset;
	
	const uint32 bit = module_index & 0x000000FF;
	
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
	
	
	
	volatile uint32* reg = nullptr;
	if(offset == 0)
	{
		//	MCU::RCC::AHB_RSTR is not in the continuous Register Space like the ENR Registers so we need to handle it separately
		reg = MCU::RCC::AHB_RSTR;
	}
	else
	{
		offset--;
		reg = MCU::RCC::APB2_RSTR + offset;
	}
	
	const uint32 bit = module_index & 0x000000FF;
	
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


feedback RCC::set_prescaler(e_prescaler_adc prescaler)
{
	uint32 temp = *MCU::RCC::CFGR & 0xFFFF3FFF;
	*MCU::RCC::CFGR = temp | ((uint32) prescaler << 14);
	
	return(OK);
}







void RCC::set_clock_hse(uint32 clock)
{
	c_clock_hse = clock;
	calculate_clockTree();
}