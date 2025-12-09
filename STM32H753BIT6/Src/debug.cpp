#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback Debug::startup()
{
	*MCU::DBGMCU::APB1_FZ = 0;
	*MCU::DBGMCU::APB2_FZ = 0;
	*MCU::DBGMCU::APB3_FZ = 0;
	*MCU::DBGMCU::APB4_FZ = 0;
	
	
	//	WWDG Stop in Debug Mode
	bit::set(*MCU::DBGMCU::APB3_FZ, 6);
	
	
	//	IWDG Stop in Debug Mode
	bit::set(*MCU::DBGMCU::APB4_FZ, 18);
	
	
	//	RTC Stop in Debug Mode
	bit::set(*MCU::DBGMCU::APB4_FZ, 16);
	
	
	//	Read Device and Revision IDs
	uint32 ID = *MCU::DBGMCU::IDC;
	m_revisionID = (ID >> 16) & 0x0000FFFF;
	m_deviceID = ID & 0x00000FFF;
	
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

