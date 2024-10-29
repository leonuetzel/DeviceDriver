#include "../Inc/stm32l451ret6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

const Pair<PWR::e_voltageScaling, RCC::s_clockBoundaries> c_clockBoundaries[2] =
{
	Pair<PWR::e_voltageScaling, RCC::s_clockBoundaries>
	(
		PWR::e_voltageScaling::RANGE1_1V2,
		RCC::s_clockBoundaries
		{
			.c_clock_msi_max =						 48000000,
			.c_clock_hse_max =						 48000000,
			
			.c_clock_pll_vco_min =				 96000000,
			.c_clock_pll_vco_max =				344000000,
			.c_clock_pll_p_min =					  3096800,
			.c_clock_pll_p_max =					 80000000,
			.c_clock_pll_q_min =					 12000000,
			.c_clock_pll_q_max =					 80000000,
			.c_clock_pll_r_min =					 12000000,
			.c_clock_pll_r_max =					 80000000,
			
			.c_clock_pll_sai1_vco_min =		 96000000,
			.c_clock_pll_sai1_vco_max =		344000000,
			.c_clock_pll_sai1_p_min =			  3096800,
			.c_clock_pll_sai1_p_max =			 80000000,
			.c_clock_pll_sai1_q_min =			 12000000,
			.c_clock_pll_sai1_q_max =			 80000000,
			.c_clock_pll_sai1_r_min =			 12000000,
			.c_clock_pll_sai1_r_max =			 80000000
		}
	),
	Pair<PWR::e_voltageScaling, RCC::s_clockBoundaries>
	(
		PWR::e_voltageScaling::RANGE2_1V0,
		RCC::s_clockBoundaries
		{
			.c_clock_msi_max =						 24000000,
			.c_clock_hse_max =						 26000000,
			
			.c_clock_pll_vco_min =				 96000000,
			.c_clock_pll_vco_max =				128000000,
			.c_clock_pll_p_min =					  3096800,
			.c_clock_pll_p_max =					 26000000,
			.c_clock_pll_q_min =					 12000000,
			.c_clock_pll_q_max =					 26000000,
			.c_clock_pll_r_min =					 12000000,
			.c_clock_pll_r_max =					 26000000,
			
			.c_clock_pll_sai1_vco_min =		 96000000,
			.c_clock_pll_sai1_vco_max =		128000000,
			.c_clock_pll_sai1_p_min =			  3096800,
			.c_clock_pll_sai1_p_max =			 26000000,
			.c_clock_pll_sai1_q_min =			 12000000,
			.c_clock_pll_sai1_q_max =			 26000000,
			.c_clock_pll_sai1_r_min =			 12000000,
			.c_clock_pll_sai1_r_max =			 26000000
		}
	)
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void RCC::calculate_clockTree()
{
	//	RM0394 - Rev. 4, Chapter 6.2, Figure 13, Page 180
	
	
	//	HSI16 Clock
	if(m_hsi16_enabled == true)
	{
		m_clock_hsi16 = c_clock_hsi_16;
	}
	else
	{
		m_clock_hsi16 = 0;
	}
	
	
	//	HSI48 Clock
	if(m_hsi48_enabled == true)
	{
		m_clock_hsi48 = c_clock_hsi_48;
	}
	else
	{
		m_clock_hsi48 = 0;
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
	
	
	//	MSI Clock
	if(m_msi_enabled == true)
	{
		m_clock_msi = c_clock_msi[m_msi_range];
	}
	else
	{
		m_clock_msi = 0;
	}
	
	
	//	LSE Clock
	if(m_lse_enabled == true)
	{
		m_clock_lse = c_clock_lse;
	}
	else
	{
		m_clock_lse = 0;
	}
	
	
	//	HSE Clock
	if(m_hse_enabled == true)
	{
		m_clock_hse = c_clock_hse;
	}
	else
	{
		m_clock_hse = 0;
	}
	
	
	
	
	//	PLL Input Clock
	//	Both PLLs have a common Input Clock
	switch(m_clockSource_pllCommon)
	{
		case e_clockSource_pllCommon::NONE:
		{
			m_clock_pll_commonInput = 0;
		}
		break;
		
		case e_clockSource_pllCommon::MSI:
		{
			m_clock_pll_commonInput = m_clock_msi / m_prescaler_pll_commonInput;
		}
		break;
		
		case e_clockSource_pllCommon::HSI16:
		{
			m_clock_pll_commonInput = m_clock_hsi16 / m_prescaler_pll_commonInput;
		}
		break;
		
		case e_clockSource_pllCommon::HSE:
		{
			m_clock_pll_commonInput = m_clock_hse / m_prescaler_pll_commonInput;
		}
		break;
		
		default:
		{
			
		}
		return;
	}
	
	
	//	PLL 1
	if(m_pll_enabled == true)
	{
		m_clock_pll = m_clock_pll_commonInput * m_multiplier_pll;
	}
	else
	{
		m_clock_pll = 0;
	}
	
	
	//	PLL SAI 1
	if(m_pll_sai1_enabled == true)
	{
		m_clock_pll_sai1 = m_clock_pll_commonInput * m_multiplier_pll_sai1;
	}
	else
	{
		m_clock_pll_sai1 = 0;
	}
	
	
	//	System Clock
	switch(m_clockSource_system)
	{
		case e_clockSource_system::MSI:
		{
			m_clock_system = m_clock_msi;
		}
		break;
		
		case e_clockSource_system::HSI16:
		{
			m_clock_system = m_clock_hsi16;
		}
		break;
		
		case e_clockSource_system::HSE:
		{
			m_clock_system = m_clock_hse;
		}
		break;
		
		case e_clockSource_system::PLL_R:
		{
			m_clock_system = m_clock_pll / m_prescaler_pll_r;
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
							const uint32 temp = *MCU::RCC::CFGR & 0xFFFFC00F;
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

feedback RCC::init_hsi16(bool enable)
{
	if(enable == m_hsi16_enabled)
	{
		return(OK);
	}
	
	
	if(enable == true)
	{
		//	Enable HSI16
		bit::set(*MCU::RCC::CR, 8);
		
		
		//	Wait for HSI16 to become stable
		while(bit::isCleared(*MCU::RCC::CR, 10))
		{
			
		}
	}
	else
	{
		//	Try to disable HSI16
		bit::clear(*MCU::RCC::CR, 8);
		
		
		//	Check if HSI16 is disabled
		if(bit::isSet(*MCU::RCC::CR, 8))
		{
			return(FAIL);
		}
	}
	
	
	m_hsi16_enabled = enable;
	calculate_clockTree();
	return(OK);
}


feedback RCC::init_hsi48(bool enable)
{
	if(enable == m_hsi48_enabled)
	{
		return(OK);
	}
	
	
	if(enable == true)
	{
		//	Enable HSI48
		bit::set(*MCU::RCC::CRRCR, 0);
		
		
		//	Wait for HSI48 to become stable
		while(bit::isCleared(*MCU::RCC::CRRCR, 1))
		{
			
		}
	}
	else
	{
		//	Try to disable HSI48
		bit::clear(*MCU::RCC::CRRCR, 0);
		
		
		//	Check if HSI48 is disabled
		if(bit::isSet(*MCU::RCC::CRRCR, 0))
		{
			return(FAIL);
		}
	}
	
	
	m_hsi48_enabled = enable;
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


feedback RCC::init_msi(bool enable, uint8 rangeIndex)
{
	//	Check if Range Index is valid
	if(rangeIndex >= sizeof(c_clock_msi) / sizeof(c_clock_msi[0]))
	{
		return(FAIL);
	}
	
	
	//	Check maximum MSI Clock in Dependance of Voltage Scaling
	STM32L451RET6& stm32 = STM32L451RET6::get();
	PWR& pwr = stm32.get_pwr();
	while(1)
	{
		const PWR::e_voltageScaling voltageScaling = pwr.get_voltageScaling();
		
		
		//	Get Constraints
		s_clockBoundaries clockBoundaries;
		bool found = false;
		for(auto& i: c_clockBoundaries)
		{
			if(i.first() == voltageScaling)
			{
				clockBoundaries = i.second();
				found = true;
				break;
			}
		}
		if(found == false)
		{
			return(FAIL);
		}
		
		
		//	Check for Constraints
		if(c_clock_msi[rangeIndex] > clockBoundaries.c_clock_msi_max)
		{
			//	Try to increase Voltage Scaling to achieve higher Clocks
			if(pwr.voltageScalingIncrease() != OK)
			{
				//	No more Voltage Scaling available, so the Clock can't be achieved
				return(FAIL);
			}
		}
		else
		{
			break;
		}
	}
	
	
	if(enable == m_msi_enabled)
	{
		return(OK);
	}
	
	
	if(enable == true)
	{
		//	MSI Range Setting set by MSIRANGE Bits in RCC::CR
		bit::set(*MCU::RCC::CR, 3);
		
		
		//	Set MSI Range
		const uint32 temp = *MCU::RCC::CR & 0xFFFFFF0F;
		*MCU::RCC::CR = temp | (rangeIndex << 4);
		
		
		//	Enable MSI
		bit::set(*MCU::RCC::CR, 0);
		
		
		//	Wait for MSI to become stable
		while(bit::isCleared(*MCU::RCC::CR, 1))
		{
			
		}
	}
	else
	{
		//	Try to disable MSI
		bit::clear(*MCU::RCC::CR, 0);
		
		
		//	Check if MSI is disabled
		if(bit::isSet(*MCU::RCC::CR, 0))
		{
			return(FAIL);
		}
	}
	
	
	m_msi_range = rangeIndex;
	m_msi_enabled = enable;
	calculate_clockTree();
	return(OK);
}


feedback RCC::init_lse(bool enable)
{
	if(enable == m_lse_enabled)
	{
		return(OK);
	}
	
	
	if(enable == true)
	{
		//	LSE not bypassed
		bit::clear(*MCU::RCC::BDCR, 2);
		
		
		//	LSE Enable
		bit::set(*MCU::RCC::BDCR, 0);
		
		
		//	Wait for LSE to become stable
		while(bit::isCleared(*MCU::RCC::BDCR, 1))
		{
			
		}
		
		
		//	LSE Clock Security System Enable
		bit::set(*MCU::RCC::CR, 5);
	}
	else
	{
		//	Try to disable LSE
		bit::clear(*MCU::RCC::CR, 0);
		
		
		//	Check if LSE is disabled
		if(bit::isSet(*MCU::RCC::CR, 1))
		{
			return(FAIL);
		}
	}
	
	
	m_lse_enabled = enable;
	calculate_clockTree();
	return(OK);
}


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
	//	before or after switching to the new Clock Source
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
		STM32L451RET6& stm32 = STM32L451RET6::get();
		Flash& flash = stm32.get_flash();
		PWR& pwr = stm32.get_pwr();
		if(flash.set_waitStates(m_clock_ahb, pwr.get_voltageScaling()) != OK)
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
	
	
	//	Leave some Time for Clock Source Switch to happen
	CMOS::get().sleep_ms(10);
	
	
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
		STM32L451RET6& stm32 = STM32L451RET6::get();
		Flash& flash = stm32.get_flash();
		PWR& pwr = stm32.get_pwr();
		if(flash.set_waitStates(m_clock_ahb, pwr.get_voltageScaling()) != OK)
		{
			return(FAIL);
		}
	}
	
	
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_pllCommon clockSource)
{
	if(m_clockSource_pllCommon == clockSource)
	{
		return(OK);
	}
	
	
	//	Save old State
	const bool pll_enabled_old = m_pll_enabled;
	const bool pll_sai1_enabled_old = m_pll_sai1_enabled;
	const e_clockSource_pllCommon m_clockSource_pllCommon_old = m_clockSource_pllCommon;
	
	
	//	Calculate new Clocks and check Constraints
	m_clockSource_pllCommon = clockSource;
	calculate_clockTree();
	
	
	//	Check Constraints (if needed in Dependance of the Voltage Scaling)
	if(m_clock_pll_commonInput > c_clock_pll_input_max || m_clock_pll_commonInput < c_clock_pll_input_min)
	{
		//	Undo Changes
		m_pll_enabled = pll_enabled_old;
		m_pll_sai1_enabled = pll_sai1_enabled_old;
		m_clockSource_pllCommon = m_clockSource_pllCommon_old;
		calculate_clockTree();
		
		return(FAIL);
	}
	
	
	//	Check, if PLL is delivering System Clock and switch to HSI16 if so
	bool pllAsSystemSource = false;
	const bool was_HSI16_enabled = m_hsi16_enabled;
	if(m_clockSource_system == e_clockSource_system::PLL_R)
	{
		pllAsSystemSource = true;
		if(init_hsi16(true) != OK)
		{
			//	Undo Changes
			m_pll_enabled = pll_enabled_old;
			m_pll_sai1_enabled = pll_sai1_enabled_old;
			m_clockSource_pllCommon = m_clockSource_pllCommon_old;
			calculate_clockTree();
			
			return(FAIL);
		}
		if(set_clockSource(e_clockSource_system::HSI16) != OK)
		{
			//	Undo Changes
			init_hsi16(was_HSI16_enabled);
			m_pll_enabled = pll_enabled_old;
			m_pll_sai1_enabled = pll_sai1_enabled_old;
			m_clockSource_pllCommon = m_clockSource_pllCommon_old;
			calculate_clockTree();
			
			return(FAIL);
		}
	}
	
	
	//	Disable PLL
	bit::clear(*MCU::RCC::CR, 24);
	
	
	//	Disable PLL SAI 1
	bit::clear(*MCU::RCC::CR, 26);
	
	
	//	Set new Values
	const uint32 temp = *MCU::RCC::PLL_CFGR & 0xFFFFFFFC;
	*MCU::RCC::PLL_CFGR = temp | (uint32) clockSource;
	
	
	//	Enable PLL if it has been enabled before
	if(pll_enabled_old == true)
	{
		//	Enable PLL
		bit::set(*MCU::RCC::CR, 24);
		
		
		//	Wait for PLL to lock
		while(bit::isCleared(*MCU::RCC::CR, 25))
		{
			
		}
	}
	
	
	//	Enable PLL SAI 1 if it has been enabled before
	if(pll_sai1_enabled_old == true)
	{
		//	Enable PLL SAI 1
		bit::set(*MCU::RCC::CR, 26);
		
		
		//	Wait for PLL SAI 1 to lock
		while(bit::isCleared(*MCU::RCC::CR, 27))
		{
			
		}
	}
	
	
	//	Switch back to PLL as System Clock Source if it was before
	if(pllAsSystemSource == true)
	{
		if(set_clockSource(e_clockSource_system::PLL_R) != OK)
		{
			return(FAIL);
		}
		if(init_hsi16(was_HSI16_enabled) != OK)
		{
			return(FAIL);
		}
	}
	
	
	return(OK);
}







feedback RCC::init_pll(uint32 clock_out, uint32 prescaler_p, uint32 prescaler_q, uint32 prescaler_r)
{
	if(m_clock_pll == clock_out && m_pll_enabled == true)
	{
		return(OK);
	}
	
	
	//	Compute Multiplier and check Constraints
	const uint32 multiplier = clock_out / m_clock_pll_commonInput;
	if(multiplier < c_pll_multiplier_min || multiplier > c_pll_multiplier_max)
	{
		return(FAIL);
	}
	if(prescaler_p < 2 || prescaler_p > 31 || prescaler_q % 2 != 0 || prescaler_r % 2 != 0)
	{
		return(FAIL);
	}
	
	
	//	Check Output Clock Constraints in Dependance of Voltage Scaling
	STM32L451RET6& stm32 = STM32L451RET6::get();
	PWR& pwr = stm32.get_pwr();
	while(1)
	{
		const PWR::e_voltageScaling voltageScaling = pwr.get_voltageScaling();
		
		
		//	Get Constraints
		s_clockBoundaries clockBoundaries;
		bool found = false;
		for(auto& i: c_clockBoundaries)
		{
			if(i.first() == voltageScaling)
			{
				clockBoundaries = i.second();
				found = true;
				break;
			}
		}
		if(found == false)
		{
			return(FAIL);
		}
		
		
		//	Check for Constraints
		bool constraintsMet = true;
		if(clock_out < clockBoundaries.c_clock_pll_vco_min || clock_out > clockBoundaries.c_clock_pll_vco_max)
		{
			constraintsMet = false;
		}
		
		const uint32 clock_p = clock_out / prescaler_p;
		if(clock_p < clockBoundaries.c_clock_pll_p_min || clock_p > clockBoundaries.c_clock_pll_p_max)
		{
			constraintsMet = false;
		}
		
		const uint32 clock_q = clock_out / prescaler_q;
		if(clock_q < clockBoundaries.c_clock_pll_q_min || clock_q > clockBoundaries.c_clock_pll_q_max)
		{
			constraintsMet = false;
		}
		
		const uint32 clock_r = clock_out / prescaler_r;
		if(clock_r < clockBoundaries.c_clock_pll_r_min || clock_r > clockBoundaries.c_clock_pll_r_max)
		{
			constraintsMet = false;
		}
		
		
		//	Increase Voltage Scaling if Constraints are not met, else leave the Loop
		if(constraintsMet == false)
		{
			//	Try to increase Voltage Scaling to achieve higher Clocks
			if(pwr.voltageScalingIncrease() != OK)
			{
				//	No more Voltage Scaling available, so the Clock can't be achieved
				return(FAIL);
			}
		}
		else
		{
			break;
		}
	}
	
	
	//	Check, if PLL is delivering System Clock and switch to HSI16 if so
	bool pllAsSystemSource = false;
	const bool was_HSI16_enabled = m_hsi16_enabled;
	if(m_clockSource_system == e_clockSource_system::PLL_R)
	{
		pllAsSystemSource = true;
		if(init_hsi16(true) != OK)
		{
			calculate_clockTree();
			
			return(FAIL);
		}
		if(set_clockSource(e_clockSource_system::HSI16) != OK)
		{
			//	Undo Changes
			init_hsi16(was_HSI16_enabled);
			calculate_clockTree();
			
			return(FAIL);
		}
	}
	
	
	//	Disable PLL
	bit::clear(*MCU::RCC::CR, 24);
	while(bit::isSet(*MCU::RCC::CR, 25))
	{
		
	}
	m_pll_enabled = false;
	
	
	//	Write Multiplier Value and Prescaler Values for the Output Clocks
	const uint32 prescaler_q_mask = (prescaler_q / 2) - 1;
	const uint32 prescaler_r_mask = (prescaler_r / 2) - 1;
	
	uint32 temp = *MCU::RCC::PLL_CFGR & 0x019D80FF;
	*MCU::RCC::PLL_CFGR = temp | (multiplier << 8) | (prescaler_p << 27) | (prescaler_q_mask << 21) | (prescaler_r_mask << 25);
	
	
	//	Enable the Output Clocks
	bit::set(*MCU::RCC::PLL_CFGR, 16);
	bit::set(*MCU::RCC::PLL_CFGR, 20);
	bit::set(*MCU::RCC::PLL_CFGR, 24);
	
	
	//	Enable PLL
	bit::set(*MCU::RCC::CR, 24);
	
	
	//	Wait for PLL to lock
	while(bit::isCleared(*MCU::RCC::CR, 25))
	{
		
	}
	
	
	//	Save new Configuration and Update Clock Tree
	m_multiplier_pll = multiplier;
	m_prescaler_pll_p = prescaler_p;
	m_prescaler_pll_q = prescaler_q;
	m_prescaler_pll_r = prescaler_r;
	m_pll_enabled = true;
	
	calculate_clockTree();
	
	
	//	Switch back to PLL as System Clock Source if it was before
	if(pllAsSystemSource == true)
	{
		if(set_clockSource(e_clockSource_system::PLL_R) != OK)
		{
			return(FAIL);
		}
		if(init_hsi16(was_HSI16_enabled) != OK)
		{
			calculate_clockTree();
			return(FAIL);
		}
	}
	
	
	return(OK);
}


feedback RCC::init_pll_sai1(uint32 clock_out, uint32 prescaler_p, uint32 prescaler_q, uint32 prescaler_r)
{
	if(m_clock_pll_sai1 == clock_out && m_pll_sai1_enabled == true)
	{
		return(OK);
	}
	
	
	//	Compute Multiplier and check Constraints
	const uint32 multiplier = clock_out / m_clock_pll_commonInput;
	if(multiplier < c_pll_sai1_multiplier_min || multiplier > c_pll_sai1_multiplier_max)
	{
		return(FAIL);
	}
	if(prescaler_p < 2 || prescaler_p > 31 || prescaler_q % 2 != 0 || prescaler_r % 2 != 0)
	{
		return(FAIL);
	}
	
	
	//	Check Output Clock Constraints in Dependance of Voltage Scaling
	STM32L451RET6& stm32 = STM32L451RET6::get();
	PWR& pwr = stm32.get_pwr();
	while(1)
	{
		const PWR::e_voltageScaling voltageScaling = pwr.get_voltageScaling();
		
		
		//	Get Constraints
		s_clockBoundaries clockBoundaries;
		bool found = false;
		for(auto& i: c_clockBoundaries)
		{
			if(i.first() == voltageScaling)
			{
				clockBoundaries = i.second();
				found = true;
				break;
			}
		}
		if(found == false)
		{
			return(FAIL);
		}
		
		
		//	Check for Constraints
		bool constraintsMet = true;
		if(clock_out < clockBoundaries.c_clock_pll_sai1_vco_min || clock_out > clockBoundaries.c_clock_pll_sai1_vco_max)
		{
			constraintsMet = false;
		}
		
		const uint32 clock_p = clock_out / prescaler_p;
		if(clock_p < clockBoundaries.c_clock_pll_sai1_p_min || clock_p > clockBoundaries.c_clock_pll_sai1_p_max)
		{
			constraintsMet = false;
		}
		
		const uint32 clock_q = clock_out / prescaler_q;
		if(clock_q < clockBoundaries.c_clock_pll_sai1_q_min || clock_q > clockBoundaries.c_clock_pll_sai1_q_max)
		{
			constraintsMet = false;
		}
		
		const uint32 clock_r = clock_out / prescaler_r;
		if(clock_r < clockBoundaries.c_clock_pll_sai1_r_min || clock_r > clockBoundaries.c_clock_pll_sai1_r_max)
		{
			constraintsMet = false;
		}
		
		
		//	Increase Voltage Scaling if Constraints are not met, else leave the Loop
		if(constraintsMet == false)
		{
			//	Try to increase Voltage Scaling to achieve higher Clocks
			if(pwr.voltageScalingIncrease() != OK)
			{
				//	No more Voltage Scaling available, so the Clock can't be achieved
				return(FAIL);
			}
		}
		else
		{
			break;
		}
	}
	
	
	//	Disable PLL SAI 1
	bit::clear(*MCU::RCC::CR, 26);
	while(bit::isSet(*MCU::RCC::CR, 27))
	{
		
	}
	m_pll_sai1_enabled = false;
	
	
	//	Write Multiplier Value and Prescaler Values for the Output Clocks
	const uint32 prescaler_q_mask = (prescaler_q / 2) - 1;
	const uint32 prescaler_r_mask = (prescaler_r / 2) - 1;
	
	uint32 temp = *MCU::RCC::PLL_SAI1_CFGR & 0x019D80FF;
	*MCU::RCC::PLL_SAI1_CFGR = temp | (multiplier << 8) | (prescaler_p << 27) | (prescaler_q_mask << 21) | (prescaler_r_mask << 25);
	
	
	//	Enable the Output Clocks
	bit::set(*MCU::RCC::PLL_SAI1_CFGR, 16);
	bit::set(*MCU::RCC::PLL_SAI1_CFGR, 20);
	bit::set(*MCU::RCC::PLL_SAI1_CFGR, 24);
	
	
	//	Enable PLL SAI 1
	bit::set(*MCU::RCC::CR, 26);
	
	
	//	Wait for PLL SAI 1 to lock
	while(bit::isCleared(*MCU::RCC::CR, 27))
	{
		
	}
	
	
	//	Save new Configuration and Update Clock Tree
	m_multiplier_pll_sai1 = multiplier;
	m_prescaler_pll_sai_p = prescaler_p;
	m_prescaler_pll_sai_q = prescaler_q;
	m_prescaler_pll_sai_r = prescaler_r;
	m_pll_sai1_enabled = true;
	
	calculate_clockTree();
	
	return(OK);
}







feedback RCC::module_clockInit(e_module module, bool enable)
{
	uint32 module_index = (uint32) module;
	uint32 offset = (module_index & 0x0000FF00) >> 8;
	
	volatile uint32* reg = MCU::RCC::AHB1_ENR + offset;
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
	
	
	volatile uint32* reg = MCU::RCC::AHB1_RSTR + offset;
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







feedback RCC::set_clock_lse(uint32 clock)
{
	if(clock > c_clock_lse_max)
	{
		return(FAIL);
	}
	c_clock_lse = clock;
	calculate_clockTree();
	
	return(OK);
}


feedback RCC::set_clock_hse(uint32 clock)
{
	if(clock < c_clock_hse_min)
	{
		return(FAIL);
	}
	
	
	//	Check maximum HSE Clock in Dependance of Voltage Scaling
	STM32L451RET6& stm32 = STM32L451RET6::get();
	PWR& pwr = stm32.get_pwr();
	while(1)
	{
		const PWR::e_voltageScaling voltageScaling = pwr.get_voltageScaling();
		
		
		//	Get Constraints
		s_clockBoundaries clockBoundaries;
		bool found = false;
		for(auto& i: c_clockBoundaries)
		{
			if(i.first() == voltageScaling)
			{
				clockBoundaries = i.second();
				found = true;
				break;
			}
		}
		if(found == false)
		{
			return(FAIL);
		}
		
		
		//	Check for Constraints
		if(clock > clockBoundaries.c_clock_hse_max)
		{
			//	Try to increase Voltage Scaling to achieve higher Clocks
			if(pwr.voltageScalingIncrease() != OK)
			{
				//	No more Voltage Scaling available, so the Clock can't be achieved
				return(FAIL);
			}
		}
		else
		{
			break;
		}
	}
	
	
	c_clock_hse = clock;
	calculate_clockTree();
	
	return(OK);
}
