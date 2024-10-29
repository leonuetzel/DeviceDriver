#include "../Inc/hsem.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback HSEM::startup(RCC& rcc, uint8 number)
{
	if(number >= c_number)
	{
		return(FAIL);
	}
	m_number = number;
	
	if(number == 0)
	{
		rcc.module_clockInit(RCC::e_module::HSEM, true);
	}
	return(OK);
}







CODE_RAM feedback HSEM::lock()
{
	if(m_number >= c_number || get_owner() != 0xFF)
	{
		return(FAIL);
	}
	
	volatile uint32* address = MCU::HSEM::R0 + m_number;
	
	uint8 ID = CMOS::get().get_runningThreadID();
	*address = 0x80000300 | ID;																																																		//	Try to lock Semaphore
	
	if(get_owner() != ID)
	{
		return(FAIL);
	}
	return(OK);
}


CODE_RAM feedback HSEM::unlock()
{
	uint8 ID = CMOS::get().get_runningThreadID();
	if(m_number >= c_number || get_owner() != ID)
	{
		return(FAIL);
	}
	
	volatile uint32* address = MCU::HSEM::R0 + m_number;
	*address = 0x00000300 | ID;
	
	if(*address != 0)
	{
		return(FAIL);
	}
	return(OK);
}


CODE_RAM feedback HSEM::force_unlock()
{
	if(m_number >= c_number)
	{
		return(FAIL);
	}
	
	volatile uint32* address = MCU::HSEM::R0 + m_number;
	*address = 0x00000300 | get_owner();
	
	if(*address != 0)
	{
		return(FAIL);
	}
	
	return(OK);
}


CODE_RAM uint8 HSEM::get_owner() const
{
	if(m_number >= c_number)
	{
		return(0xFF);
	}
	
	volatile uint32* address = MCU::HSEM::R0 + m_number;
	if(bit::isCleared(*address, 31))																																															//	Semaphore is free
	{
		return(0xFF);
	}
	return(*address & 0x000000FF);
}