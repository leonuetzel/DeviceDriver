#include "../Inc/stm32g474mct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback DMAMUX::startup()
{
	RCC& rcc = STM32G474MCT6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::DMAMUX, true);
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback DMAMUX::map(e_input input, e_output output)
{
	volatile uint32* baseAddress = MCU::DMAMUX::CH0_CR;
	
	volatile uint32* channelAddress = baseAddress + (((uint32) output) & 0x0F);
	*channelAddress = ((uint32) input) & 0xFF;
	
	return(OK);
}