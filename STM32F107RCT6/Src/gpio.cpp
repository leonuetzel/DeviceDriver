#include "../Inc/stm32f107rct6.hpp"





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
	const uint32 port = ((uint32) pin) >> 4;
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	
	
	
	const uint32 offset = port * 0x00000100;
	volatile uint32* reg_cr = (uint32*) NULL;
	volatile uint32* reg_odr = MCU::GPIO_A::ODR + offset;
	
	if(pinNumber < 8)
	{
		reg_cr = MCU::GPIO_A::CRL;
	}
	else
	{
		reg_cr = MCU::GPIO_A::CRH;
	}
	reg_cr += offset;
	
	
	
	uint32 mask = 0x8;
	switch(mode)
	{
		case e_mode::IN:
			switch(pupd)
			{
				case e_pupd::NONE:
					mask = 0x4;
					break;
					
				case e_pupd::PULL_UP:
					bit::set(*reg_odr, pinNumber);
					break;
					
				case e_pupd::PULL_DOWN:
					bit::clear(*reg_odr, pinNumber);
					break;
					
				default:
					return(FAIL);
			}
			break;
			
		case e_mode::OUT_GP_PP:
			mask = 0x0;
			break;
			
		case e_mode::OUT_GP_OD:
			mask = 0x4;
			break;
			
		case e_mode::AF_PP:
			mask = 0x8;
			break;
			
		case e_mode::AF_OD:
			mask = 0xC;
			break;
			
		case e_mode::ANALOG:
			mask = 0x0;
			break;
			
		default:
			return(FAIL);
	}
	
	if(mode != e_mode::IN && mode != e_mode::ANALOG)
	{
		mask |= (uint32) speed;
	}
	const uint32 pinNumberModified = pinNumber & 0x7;
	uint32 temp = *reg_cr & (0xFFFFFFFF - (0x0F << (4 * pinNumberModified)));
	*reg_cr = temp | (mask << (4 * pinNumberModified));
	
	
	
	return(OK);
}