#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback SYSCFG::startup()
{
	STM32H753BIT6::get().get_rcc().module_clockInit(RCC::e_module::SYSCFG, true);
	if(set_overdrive(false) != OK)
	{
		return(FAIL);
	}
	
	m_package = (e_package) (*MCU::SYSCFG::PKGR & 0x0000000F);
	
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback SYSCFG::set_overdrive(bool enable)
{
	if(enable == true)
	{
		bit::set(*MCU::SYSCFG::PWRCR, 0);
	}
	else
	{
		bit::clear(*MCU::SYSCFG::PWRCR, 0);
	}
	
	m_overdriveEnabled = enable;
	return(OK);
}


bool SYSCFG::get_overdriveEnabled()
{
	return(m_overdriveEnabled);
}


SYSCFG::e_package SYSCFG::get_package()
{
	return(m_package);
}