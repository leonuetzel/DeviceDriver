#include "../Inc/stm32l010rbt6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback PWR::set_voltageRange(e_voltageRange range)
{
	//	Wait for VOSF Bit to be reset
	while(bit::isSet(*MCU::PWR::CSR, 4) == true)
	{
		
	}
	
	
	//	Bitmask to write
	const uint32 mask = ((uint32) range) << 11;
	
	
	//	Set Voltage Range
	uint32 temp = *MCU::PWR::CR & 0xFFFFE7FF;
	*MCU::PWR::CR = temp | mask;
	
	
	//	Wait for VOSF Bit to be reset
	while(bit::isSet(*MCU::PWR::CSR, 4) == true)
	{
		
	}
	
	
	//	Check if Voltage Range has been set correctly
	if((*MCU::PWR::CR & 0x00001800) != mask)
	{
		return(FAIL);
	}
	
	
	//	Update internal State
	m_voltageRange = range;
	return(OK);
}