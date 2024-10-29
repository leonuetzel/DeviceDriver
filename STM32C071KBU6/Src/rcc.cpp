#include "../Inc/stm32c071kbu6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void RCC::calculate_clockTree()
{
	//	RM0490 - Rev. 3, Chapter 5.2, Figure 9, Page 108
	
	
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
		m_clock_hsiSystem = m_clock_hsi / m_prescaler_hsiSystem;
		m_clock_hsiKernel = m_clock_hsi / m_prescaler_hsiKernel;
	}
	else
	{
		m_clock_hsi = 0;
		m_clock_hsiSystem = 0;
		m_clock_hsiKernel = 0;
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
	
	
	//	LSE Clock
	if(m_lse_enabled == true)
	{
		m_clock_lse = c_clock_lse;
	}
	else
	{
		m_clock_lse = 0;
	}
	
	
	//	System Clock
	switch(m_clockSource_system)
	{
		case e_clockSource_system::HSI:
		{
			m_clock_system = m_clock_hsiSystem;
		}
		break;
		
		case e_clockSource_system::HSE:
		{
			m_clock_system = m_clock_hse;
		}
		break;
		
		case e_clockSource_system::LSI:
		{
			m_clock_system = m_clock_lsi;
		}
		break;
		
		case e_clockSource_system::LSE:
		{
			m_clock_system = m_clock_lse;
		}
		break;
		
		default:
		{
			return;
		}
		break;
	}
	
	
	//	AHB Clock
	m_clock_ahb = m_clock_system / m_prescaler_ahb;
	
	
	//	APB Clock
	m_clock_apb = m_clock_ahb / m_prescaler_apb;
	
	
	//	APB Timer Clock
	if(m_prescaler_apb == 1)
	{
		m_clock_apb_timer = m_clock_apb;
	}
	else
	{
		m_clock_apb_timer = m_clock_apb * 2;
	}
}


feedback RCC::autoAdjust_AHB_APB_prescaler()
{
	//	Save old State
	const uint32 prescaler_ahb_old = m_prescaler_ahb;
	const uint32 prescaler_apb_old = m_prescaler_apb;
	
	
	//	Compute the best Combination of Prescalers
	constexpr uint32 numberOfPrescaler_ahb = sizeof(c_prescaler_ahb) / sizeof(c_prescaler_ahb[0]);
	constexpr uint32 numberOfPrescaler_apb = sizeof(c_prescaler_apb) / sizeof(c_prescaler_apb[0]);
	
	
	for(uint32 prescalerIndex_ahb = 0; prescalerIndex_ahb < numberOfPrescaler_ahb; prescalerIndex_ahb++)
	{
		m_prescaler_ahb = c_prescaler_ahb[prescalerIndex_ahb];
		
		//	Update Clock Tree and check Constraints
		calculate_clockTree();
		
		if(m_clock_ahb <= c_clock_ahb_max)
		{
			for(uint32 prescalerIndex_apb = 0; prescalerIndex_apb < numberOfPrescaler_apb; prescalerIndex_apb++)
			{
				m_prescaler_apb = c_prescaler_apb[prescalerIndex_apb];
				
				//	Update Clock Tree and check Constraints
				calculate_clockTree();
				
				if(m_clock_apb <= c_clock_apb_max)
				{
					//	Since Prescaler Values are ordered in ascending Order, the first Time we reach this Point here is the Combination with the highest possible Clocks
					//	Write Configuration
					uint32 temp = *MCU::RCC::CFGR & 0xFFFF80FF;
					*MCU::RCC::CFGR = temp | (prescalerIndex_apb << 12) | (prescalerIndex_ahb << 8);
					
					return(OK);
				}
			}
		}
	}
	
	
	//	No valid Configuration was found, so undo Changes
	m_prescaler_ahb = prescaler_ahb_old;
	m_prescaler_apb = prescaler_apb_old;
	
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
		bit::set(*MCU::RCC::CR, 8);
		
		
		//	Wait for HSI to become stable
		while(bit::isCleared(*MCU::RCC::CR, 10))
		{
			
		}
	}
	else
	{
		//	Try to disable HSI
		bit::clear(*MCU::RCC::CR, 8);
		
		
		//	Check if HSI is disabled
		if(bit::isSet(*MCU::RCC::CR, 8))
		{
			return(FAIL);
		}
	}
	
	
	m_hsi_enabled = enable;
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
		//	Enable LSE
		bit::set(*MCU::RCC::CSR1, 0);
		
		
		//	Wait for LSE to become stable
		while(bit::isCleared(*MCU::RCC::CSR1, 1))
		{
			
		}
	}
	else
	{
		//	Try to disable LSE
		bit::clear(*MCU::RCC::CSR1, 0);
		
		
		//	Check if LSE is disabled
		if(bit::isSet(*MCU::RCC::CSR1, 0))
		{
			return(FAIL);
		}
	}
	
	
	m_lse_enabled = enable;
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
		bit::set(*MCU::RCC::CSR2, 0);
		
		
		//	Wait for LSI to become stable
		while(bit::isCleared(*MCU::RCC::CSR2, 1))
		{
			
		}
	}
	else
	{
		//	Try to disable LSI
		bit::clear(*MCU::RCC::CSR2, 0);
		
		
		//	Check if LSI is disabled
		if(bit::isSet(*MCU::RCC::CSR2, 0))
		{
			return(FAIL);
		}
	}
	
	
	m_lsi_enabled = enable;
	calculate_clockTree();
	return(OK);
}







feedback RCC::set_hsiSystem_prescaler(e_prescaler_hsiSystem prescaler)
{
	const uint32 mask = (uint32) prescaler;
	
	uint32 temp = *MCU::RCC::CR & 0xFFFFC7FF;
	*MCU::RCC::CR = temp | (mask << 11);
	
	m_prescaler_hsiSystem = c_prescaler_hsiSystem[(uint32) prescaler];
	
	calculate_clockTree();
	
	return(OK);
}


feedback RCC::set_hsiKernel_prescaler(e_prescaler_hsiKernel prescaler)
{
	const uint32 mask = (uint32) prescaler;
	
	uint32 temp = *MCU::RCC::CR & 0xFFFFFF1F;
	*MCU::RCC::CR = temp | (mask << 5);
	
	m_prescaler_hsiKernel = c_prescaler_hsiKernel[(uint32) prescaler];
	
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
	//	-	APB Prescaler
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
	
	
	//	Auto adjust AHB and APB Prescalers to avoid overclocking the Busses
	//	This must be done before changing the System Clock Source only (and only!) if the new System Clock is higher than the old one
	if(m_clock_system > clock_system_old)
	{
		if(autoAdjust_AHB_APB_prescaler() != OK)
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
			
			autoAdjust_AHB_APB_prescaler();
			
			return(FAIL);
		}
	}
	
	
	//	Switch System Clock Source
	uint32 temp = *MCU::RCC::CFGR & 0xFFFFFFF8;
	*MCU::RCC::CFGR = temp | (uint32) clockSource;
	
	
	//	Check if Switch was successful
	if(get_clockSource_system() != clockSource)
	{
		//	Undo Changes and return
		m_clockSource_system = clockSourceSystemOld;
		calculate_clockTree();
		return(FAIL);
	}
	
	
	//	Auto adjust Flash Wait States, AHB and APB Prescalers
	if(m_clock_system < clock_system_old)
	{
		if(autoAdjust_AHB_APB_prescaler() != OK)
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


void RCC::init_mco(e_clockSource_mco clockSource, e_prescaler_mco prescaler)
{
	//	Set Prescaler before enabling MCO Output
	const uint32 mask_prescaler = (uint32) prescaler;
	
	uint32 temp = *MCU::RCC::CFGR & 0x8FFFFFFF;
	*MCU::RCC::CFGR = temp | (mask_prescaler << 28);
	
	
	//	Enable MCO Output
	const uint32 mask_source = (uint32) clockSource;
	
	temp = *MCU::RCC::CFGR & 0xF8FFFFFF;
	*MCU::RCC::CFGR = temp | (mask_source << 24);
}


void RCC::init_mco2(e_clockSource_mco clockSource, e_prescaler_mco prescaler)
{
	//	Set Prescaler before enabling MCO Output
	const uint32 mask_prescaler = (uint32) prescaler;
	
	uint32 temp = *MCU::RCC::CFGR & 0xFF8FFFFF;
	*MCU::RCC::CFGR = temp | (mask_prescaler << 20);
	
	
	//	Enable MCO Output
	const uint32 mask_source = (uint32) clockSource;
	
	temp = *MCU::RCC::CFGR & 0xFFF8FFFF;
	*MCU::RCC::CFGR = temp | (mask_source << 16);
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
	bit::set(*MCU::RCC::CSR1, 16);
	while(bit::isCleared(*MCU::RCC::CSR1, 16))
	{
		
	}
	bit::clear(*MCU::RCC::CSR1, 16);
	
	return(OK);
}







void RCC::set_clock_hse(uint32 clock)
{
	c_clock_hse = clock;
	calculate_clockTree();
}







void RCC::set_clockSource(e_clockSource_i2c clockSource)
{
	const uint32 mask = (uint32) clockSource;
	
	uint32 temp = *MCU::RCC::CCIPR & 0xFFFFCFFF;
	*MCU::RCC::CCIPR = temp | (mask << 12);
}


feedback RCC::set_clockSource(e_clockSource_adc clockSource)
{
	const uint32 mask = (uint32) clockSource;
	
	uint32 temp = *MCU::RCC::CCIPR & 0x3FFFFFFF;
	*MCU::RCC::CCIPR = temp | (mask << 30);
	
	m_clockSource_adc = clockSource;
	
	calculate_clockTree();
	
	return(OK);
}