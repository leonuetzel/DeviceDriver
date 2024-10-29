#include "../Inc/backupSRAM.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback BackupSRAM::startup()
{
	writeProtection(false);
	
	bit::set(*MCU::RCC::BDCR, 16);																																																//  Reset Backup Domain
	while(bit::isCleared(*MCU::RCC::BDCR, 16))
	{
		
	}
	bit::clear(*MCU::RCC::BDCR, 16);
	
	m_rcc.module_clockInit(RCC::e_module::BKP_RAM, true);
	
	bit::set(*MCU::PWR::CR2, 0);																																																	//	Enable Backup Domain Power Regulator
	while(bit::isCleared(*MCU::PWR::CR2, 16))																																											//	Wait for Backup Domain Power Regulator to be ready
	{
		
	}
	
	return(OK);
}







void BackupSRAM::writeProtection(bool enable)
{
	if(enable == true)
	{
		bit::clear(*MCU::PWR::CR1, 8);																																															//	Enable Write Protection of Backup Domain
		while(bit::isSet(*MCU::PWR::CR1, 8))
		{
			
		}
	}
	else
	{
		bit::set(*MCU::PWR::CR1, 8);																																																//	Disable Write Protection of Backup Domain
		while(bit::isCleared(*MCU::PWR::CR1, 8))
		{
			
		}
	}
}