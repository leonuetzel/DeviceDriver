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

feedback Flash::set_waitStates(uint32 clock_ahb)
{
	//	LATENCY (Bits 2:0) is replaced, the other Bits (e.g. the Prefetch Buffer) are kept
	uint32 temp = *MCU::FLASH::ACR & 0xFFFFFFF8;
	if(clock_ahb > 24000000)
	{
		*MCU::FLASH::ACR = temp | 0x1;
		m_waitStates = 1;
	}
	else
	{
		*MCU::FLASH::ACR = temp;
		m_waitStates = 0;
	}
	
	return(OK);
}


feedback Flash::set_prefetchBuffer(bool active)
{
	if(active == true)
	{
		if(bit::isCleared(*MCU::FLASH::ACR, 4))
		{
			bit::set(*MCU::FLASH::ACR, 4);
		}
	}
	else
	{
		bit::clear(*MCU::FLASH::ACR, 4);
	}
	
	return(OK);
}