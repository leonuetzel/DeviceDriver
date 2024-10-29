#include "../Inc/stm32f103c8t6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

void AFIO::set_debugConfiguration(e_debugConfiguration debugConfiguration)
{
	STM32F103C8T6::get().get_rcc().module_clockInit(RCC::e_module::AFIO, true);
	
	uint32 afio_mapr = *MCU::AFIO::MAPR;
	afio_mapr &= 0xF8FFFFFF;
	*MCU::AFIO::MAPR = afio_mapr | (((uint32) debugConfiguration) << 24);
}