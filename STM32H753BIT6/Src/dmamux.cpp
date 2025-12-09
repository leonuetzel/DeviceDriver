#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback DMAMUX::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback DMAMUX::map(e_input input, e_output output)
{
	volatile uint32* baseAddress = nullptr;
	
	uint32 dmamux = (((uint32) output) && 0xF0) >> 4;
	switch(dmamux)
	{
		case 0:
			baseAddress = MCU::DMAMUX_1::CH0_CR;
			break;
			
		case 1:
			baseAddress = MCU::DMAMUX_2::CH0_CR;
			break;
			
		default:
			return(FAIL);
	}
	
	volatile uint32* channelAddress = baseAddress + (((uint32) output) & 0x0F);
	*channelAddress = ((uint32) input) & 0xFF;
	
	return(OK);
}