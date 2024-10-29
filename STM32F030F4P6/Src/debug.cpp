#include "../Inc/stm32f030f4p6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

void Debug::freeze_onDebug(e_module module, bool freeze)
{
	uint32 bit = (uint32) module & 0x0FF;
	uint32* reg = (uint32*) MCU::DBGMCU::APB1_FZ;
	reg += (((uint32) module) & 0xF00) >> 8;
	
	if(freeze == true)
	{
		bit::set(*reg, bit);
	}
	else
	{
		bit::clear(*reg, bit);
	}
}