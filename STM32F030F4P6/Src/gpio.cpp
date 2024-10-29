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

CODE_RAM feedback GPIO::init_pin(e_pin pin, e_mode mode, e_speed speed, e_pupd pupd)
{
	const uint8 pinNumber = get_pinNumber(pin);
	
	uint32 offset = get_portNumber(pin) * 0x00000100;
	volatile uint32* reg_mode		= MCU::GPIO_A::MODE		+ offset;
	volatile uint32* reg_otype	= MCU::GPIO_A::OTYPE	+ offset;
	volatile uint32* reg_ospeed	= MCU::GPIO_A::OSPEED	+ offset;
	volatile uint32* reg_pupd		= MCU::GPIO_A::PUPD		+ offset;
	
	
	uint32 mask = 0x0;
	switch(mode)
	{
		case e_mode::IN:
		{
			mask = 0x0;
		}
		break;
				
		case e_mode::OUT_GP_PP:
		{
			mask = 0x1;
		}
		break;
		
		case e_mode::OUT_GP_OD:
		{
			mask = 0x1;
		}
		break;
		
		case e_mode::AF_PP:
		{
			mask = 0x2;
		}
		break;
		
		case e_mode::AF_OD:
		{
			mask = 0x2;
		}
		break;
		
		case e_mode::ANALOG:
		{
			mask = 0x3;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	uint32 temp = *reg_mode & (0xFFFFFFFF - (0x03 << (2 * pinNumber)));
	*reg_mode = temp | (mask << (2 * pinNumber));
	
	
	
	if(mode == e_mode::OUT_GP_OD || mode == e_mode::AF_OD)
	{
		bit::set(*reg_otype, pinNumber);
	}
	else
	{
		bit::clear(*reg_otype, pinNumber);
	}
	

	switch(speed)
	{
		case e_speed::LOW:
		{
			mask = 0x0;
		}
		break;
		
		case e_speed::MEDIUM:
		{
			mask = 0x1;
		}
		break;
		
		case e_speed::HIGH:
		{
			mask = 0x3;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	temp = *reg_ospeed & (0xFFFFFFFF - (0x03 << (2 * pinNumber)));
	*reg_ospeed = temp | (mask << (2 * pinNumber));
	
	
	
	switch(pupd)
	{
		case e_pupd::NONE:
		{
			mask = 0x0;
		}
		break;
		
		case e_pupd::PULL_UP:
		{
			mask = 0x1;
		}
		break;
		
		case e_pupd::PULL_DOWN:
		{
			mask = 0x2;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	temp = *reg_pupd & (0xFFFFFFFF - (0x03 << (2 * pinNumber)));
	*reg_pupd = temp | (mask << (2 * pinNumber));
	
	
	
	return(OK);
}