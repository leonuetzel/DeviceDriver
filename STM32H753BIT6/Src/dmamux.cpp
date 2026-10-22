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
	
	//	Bits 7:4 of the Output select the DMAMUX (0 = DMAMUX1 for DMA1 and DMA2, 1 = DMAMUX2 for the BDMA), Bits 3:0 its Channel
	uint32 dmamux = (((uint32) output) & 0xF0) >> 4;
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