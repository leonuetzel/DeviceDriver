#include "../Inc/vrefbuf.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback VREFBUF::startup()
{
	m_rcc.module_clockInit(RCC::e_module::VREF, true);
	
	return(OK);
}







feedback VREFBUF::set_mode(e_mode mode)
{
	if(mode == m_mode)
	{
		return(OK);
	}
	
	
	
	uint32 mask = (uint32) mode;
	
	uint32 temp = *MCU::VREF::CSR & 0xFFFFFFFC;																																										//	Set Mode
	*MCU::VREF::CSR = temp | mask;
	
	if(mode == e_mode::INTERNAL)
	{
		while(bit::isCleared(*MCU::VREF::CSR, 3))																																										//	Wait for Voltage Reference Buffer to reach requested Level
		{
			
		}
	}
	
	m_mode = mode;
	
	return(OK);
}


feedback VREFBUF::set_voltage(e_voltage voltage)
{
	if(m_mode != e_mode::INTERNAL)																																																//	Voltage Reference Buffer only enabled in Internal Mode
	{
		return(FAIL);
	}
	
	uint32 mask = (uint32) voltage;
	if(mask > 0x3)
	{
		return(FAIL);
	}
	
	uint32 temp = *MCU::VREF::CSR & 0xFFFFFF8F;																																										//	Set Voltage
	*MCU::VREF::CSR = temp | (mask << 4);
	
	while(bit::isCleared(*MCU::VREF::CSR, 3))																																											//	Wait for Voltage Reference Buffer to reach requested Level
	{
		
	}
	
	m_voltage = voltage;
	
	return(OK);
}