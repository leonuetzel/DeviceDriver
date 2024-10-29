#include "../Inc/pwr.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback PWR::startup()
{
	return(OK);
}







PWR::e_voltageLevel PWR::get_requiredVoltageLevel(uint32 divider_pll_1_p, uint32 divider_pll_1_q, uint32 divider_pll_1_r, uint32 clock_pll_1, bool pll_1_range_wide)
{
	uint32 divider_smallest = Math::min(divider_pll_1_p, divider_pll_1_q, divider_pll_1_r);																				//	Compute Maximum Frequency
	uint32 clock_max = clock_pll_1 / divider_smallest;
	
	e_voltageLevel voltage_level = e_voltageLevel::VOS_3;
	
	if(pll_1_range_wide == false)																																																	//	Compute required Voltage Level
	{
		if(clock_max > 200000000)
		{
			voltage_level = e_voltageLevel::VOS_2;
		}
	}
	else
	{
		if(clock_max > 200000000)
		{
			if(clock_max <= 300000000)
			{
				voltage_level = e_voltageLevel::VOS_2;
			}
			else
			{
				if(clock_max <= 400000000)
				{
					voltage_level = e_voltageLevel::VOS_1;
				}
				else
				{
					voltage_level = e_voltageLevel::VOS_0;
				}
			}
		}
	}
	
	return(voltage_level);
}


feedback PWR::set_voltageLevel(e_voltageLevel voltageLevel)
{
	if(voltageLevel == m_voltageLevel)																																														//	Set required Voltage Level
	{
		return(OK);
	}
	
	if(m_voltageLevel == e_voltageLevel::VOS_0)																																										//	Deactivate Voltage Scaling 0
	{
		m_syscfg.set_overdrive(false);
	}
	
	
	
	uint32 mask = (uint32) voltageLevel;
	if(mask > 0x3)
	{
		mask = 0x3;
	}
	
	bit::clear(*MCU::PWR::CR3, 2);																																																//	Enable Supply Configuration Update
	*MCU::PWR::D3_CR = (mask << 14);																																															//	Set Voltage Level
	bit::set(*MCU::PWR::CR3, 2);																																																	//	Lock Supply Configuration
	while(bit::isCleared(*MCU::PWR::D3_CR, 13))																																										//	Wait for Voltage to settle
	{
		
	}
	
	if(voltageLevel == e_voltageLevel::VOS_0)
	{
		m_syscfg.set_overdrive(true);
		while(bit::isCleared(*MCU::PWR::D3_CR, 13))																																									//	Wait for Voltage to settle
		{
			
		}
	}
	
	m_voltageLevel = voltageLevel;

	return(OK);
}


PWR::e_voltageLevel PWR::get_voltageLevel()
{
	return(m_voltageLevel);
}


void PWR::enable_ECC()
{
	*MCU::FLASH_1::KEY = 0x45670123;																																															//	Unlock FLASH_1_CR
	*MCU::FLASH_1::KEY = 0xCDEF89AB;
	
	bit::set(*MCU::FLASH_1::CR, 26);																																															//	Enable Bank 1 ECC Double Detection Error Interrupt
	bit::set(*MCU::FLASH_1::CR, 25);																																															//	Enable Bank 1 ECC Single Correction Error Interrupt
	
	bit::set(*MCU::FLASH_1::CR, 0);																																																//	Lock FLASH_1_CR
}