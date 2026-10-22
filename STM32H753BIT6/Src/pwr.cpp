#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback PWR::startup()
{
	return(OK);
}


bool PWR::isRevisionY()
{
	//	REV_ID (DBGMCU_IDC Bits 31:16): 0x1003 Revision Y, 0x2003 Revision V
	return(((*MCU::DBGMCU::IDC >> 16) & 0x0000FFFF) == 0x1003);
}


feedback PWR::waitForVoltage()
{
	//	VOSRDY (PWR_D3CR Bit 13): VCORE has reached the selected Level
	for(uint32 i = 0; i < 1000000; i++)
	{
		if(bit::isSet(*MCU::PWR::D3_CR, 13) == true)
		{
			return(OK);
		}
	}
	return(FAIL);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

uint32 PWR::get_clock_max(e_voltageLevel voltageLevel)
{
	//	Highest CPU and PLL Output Frequency of a Voltage Level (Datasheet, General operating conditions and PLL characteristics)
	switch(voltageLevel)
	{
		case e_voltageLevel::VOS_0:
		{
			return(480000000);
		}
		break;
		
		case e_voltageLevel::VOS_1:
		{
			return(400000000);
		}
		break;
		
		case e_voltageLevel::VOS_2:
		{
			return(300000000);
		}
		break;
		
		default:
		{
			return(200000000);
		}
		break;
	}
}


feedback PWR::get_requiredVoltageLevel(uint32 clock, e_voltageLevel& voltageLevel)
{
	//	The lowest Level that allows the Frequency; VOS0 only from Revision V on
	const e_voltageLevel levels[4] = {e_voltageLevel::VOS_3, e_voltageLevel::VOS_2, e_voltageLevel::VOS_1, e_voltageLevel::VOS_0};
	for(const e_voltageLevel level: levels)
	{
		if(level == e_voltageLevel::VOS_0 && isRevisionY() == true)
		{
			break;
		}
		if(clock <= get_clock_max(level))
		{
			voltageLevel = level;
			return(OK);
		}
	}
	return(FAIL);
}


PWR::e_voltageLevel PWR::get_requiredVoltageLevel(uint32 divider_pll_1_p, uint32 divider_pll_1_q, uint32 divider_pll_1_r, uint32 clock_pll_1, bool pll_1_range_wide)
{
	//	Highest Output of PLL 1; a Divider of 0 means the Output is off
	(void) pll_1_range_wide;
	const uint32 dividers[3] = {divider_pll_1_p, divider_pll_1_q, divider_pll_1_r};
	uint32 clock_max = 0;
	for(const uint32 divider: dividers)
	{
		if(divider != 0)
		{
			clock_max = Math::max(clock_max, clock_pll_1 / divider);
		}
	}
	e_voltageLevel voltageLevel = e_voltageLevel::VOS_0;
	get_requiredVoltageLevel(clock_max, voltageLevel);
	return(voltageLevel);
}


feedback PWR::set_voltageLevel(e_voltageLevel voltageLevel)
{
	if(voltageLevel == m_voltageLevel)																																														//	Set required Voltage Level
	{
		return(OK);
	}
	
	
	//	VOS0 exists from Revision V on, Revision Y runs at most with VOS1
	if(voltageLevel == e_voltageLevel::VOS_0 && isRevisionY() == true)
	{
		return(FAIL);
	}
	
	
	//	Leave VOS0: switch the Overdrive off while the VOS Bits still select VOS1, then wait for VCORE (RM0433, VOS0 activation/deactivation sequence)
	SYSCFG& syscfg = STM32H753BIT6::get().get_syscfg();
	if(m_voltageLevel == e_voltageLevel::VOS_0)
	{
		syscfg.set_overdrive(false);
		m_voltageLevel = e_voltageLevel::VOS_1;
		if(waitForVoltage() != OK)
		{
			return(FAIL);
		}
	}
	
	
	//	VOS0 is VOS1 plus Overdrive
	uint32 mask = (uint32) voltageLevel;
	if(mask > 0x3)
	{
		mask = 0x3;
	}
	
	bit::clear(*MCU::PWR::CR3, 2);																																																//	Enable Supply Configuration Update
	*MCU::PWR::D3_CR = (mask << 14);																																															//	Set Voltage Level
	bit::set(*MCU::PWR::CR3, 2);																																																	//	Lock Supply Configuration
	m_voltageLevel = (voltageLevel == e_voltageLevel::VOS_0) ? e_voltageLevel::VOS_1 : voltageLevel;
	if(waitForVoltage() != OK)																																																		//	Wait for Voltage to settle
	{
		return(FAIL);
	}
	
	if(voltageLevel == e_voltageLevel::VOS_0)
	{
		syscfg.set_overdrive(true);
		if(waitForVoltage() != OK)																																																	//	Wait for Voltage to settle
		{
			return(FAIL);
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