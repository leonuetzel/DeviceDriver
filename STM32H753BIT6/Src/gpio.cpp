#include "../Inc/gpio.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback GPIO::startup(RCC& rcc)
{
	rcc.module_reset(RCC::e_module::GPIO_A);
	rcc.module_clockInit(RCC::e_module::GPIO_A, true);
	
	rcc.module_reset(RCC::e_module::GPIO_B);
	rcc.module_clockInit(RCC::e_module::GPIO_B, true);
	
	rcc.module_reset(RCC::e_module::GPIO_C);
	rcc.module_clockInit(RCC::e_module::GPIO_C, true);
	
	rcc.module_reset(RCC::e_module::GPIO_D);
	rcc.module_clockInit(RCC::e_module::GPIO_D, true);
	
	rcc.module_reset(RCC::e_module::GPIO_E);
	rcc.module_clockInit(RCC::e_module::GPIO_E, true);
	
	rcc.module_reset(RCC::e_module::GPIO_F);
	rcc.module_clockInit(RCC::e_module::GPIO_F, true);
	
	rcc.module_reset(RCC::e_module::GPIO_G);
	rcc.module_clockInit(RCC::e_module::GPIO_G, true);
	
	rcc.module_reset(RCC::e_module::GPIO_H);
	rcc.module_clockInit(RCC::e_module::GPIO_H, true);
	
	rcc.module_reset(RCC::e_module::GPIO_I);
	rcc.module_clockInit(RCC::e_module::GPIO_I, true);
	
	rcc.module_reset(RCC::e_module::GPIO_J);
	rcc.module_clockInit(RCC::e_module::GPIO_J, true);
	
	rcc.module_reset(RCC::e_module::GPIO_K);
	rcc.module_clockInit(RCC::e_module::GPIO_K, true);
	
	return(OK);
}







CODE_RAM feedback GPIO::init_pin(e_pin pin, e_mode mode, e_speed speed, e_pupd pupd)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	
	
	const uint32 offset = port * 0x00000100;
	volatile uint32* reg_mode = MCU::GPIO_A::MODE + offset;
	volatile uint32* reg_otype = MCU::GPIO_A::OTYPE + offset;
	volatile uint32* reg_ospeed = MCU::GPIO_A::OSPEED + offset;
	volatile uint32* reg_pupd = MCU::GPIO_A::PUPD + offset;
	
	
	uint32 mask = 0x0;
	switch(mode)
	{
		case e_mode::IN:
			mask = 0x0;
			break;

		case e_mode::OUT_GP_PP:
			mask = 0x1;
			break;

		case e_mode::OUT_GP_OD:
			mask = 0x1;
			break;

		case e_mode::AF_PP:
			mask = 0x2;
			break;

		case e_mode::AF_OD:
			mask = 0x2;
			break;

		case e_mode::ANALOG:
			mask = 0x3;
			break;

		default:
			return(FAIL);
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
			mask = 0x0;
			break;

		case e_speed::MEDIUM:
			mask = 0x1;
			break;

		case e_speed::HIGH:
			mask = 0x2;
			break;

		case e_speed::VERY_HIGH:
			mask = 0x3;
			break;

		default:
			return(FAIL);
	}
	
	temp = *reg_ospeed & (0xFFFFFFFF - (0x03 << (2 * pinNumber)));
	*reg_ospeed = temp | (mask << (2 * pinNumber));
	
	
	
	switch(pupd)
	{
		case e_pupd::NONE:
			mask = 0x0;
			break;

		case e_pupd::PULL_UP:
			mask = 0x1;
			break;

		case e_pupd::PULL_DOWN:
			mask = 0x2;
			break;

		default:
			return(FAIL);
	}
	
	temp = *reg_pupd & (0xFFFFFFFF - (0x03 << (2 * pinNumber)));
	*reg_pupd = temp | (mask << (2 * pinNumber));
	
	
	
	return(OK);
}


CODE_RAM void GPIO::set_pin(e_pin pin)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	volatile uint32* address = MCU::GPIO_A::BSRR + port * 0x00000100;
	bit::set(*address, pinNumber);
}


CODE_RAM void GPIO::clear_pin(e_pin pin)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	volatile uint32* address = MCU::GPIO_A::BSRR + port * 0x00000100;
	bit::set(*address, pinNumber + 16);
}


CODE_RAM void GPIO::toggle_pin(e_pin pin)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	volatile uint32* address = MCU::GPIO_A::ODR + port * 0x00000100;
	if(bit::isSet(*address, pinNumber))
	{
		clear_pin(pin);
	}
	else
	{
		set_pin(pin);
	}
}


CODE_RAM bool GPIO::get_pinLevel(e_pin pin)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	volatile uint32* address = MCU::GPIO_A::IDR + port * 0x00000100;
	if(bit::isSet(*address, pinNumber))
	{
		return(true);
	}
	return(false);
}


CODE_RAM feedback GPIO::set_AF(e_AF alternateFunction)
{
	uint32 port = (((uint32) alternateFunction) & 0x00000F00) >> 8;
	
	uint32 mask = ((uint32) alternateFunction) & 0x000000FF;
	uint8 pin = (mask & 0xF0) >> 4;
	uint32 offset = 0;
	
	if(pin < 8)
	{
		volatile uint32* address = MCU::GPIO_A::AFRL + port * 0x00000100;
		offset = 4 * pin;
		uint32 temp = *address & (0xFFFFFFFF - (0x0000000F << offset));
		*address = temp | ((mask & 0x0F) << offset);
	}
	else
	{
		pin -= 8;
		volatile uint32* address = MCU::GPIO_A::AFRH + port * 0x00000100;
		offset = 4 * pin;
		uint32 temp = *address & (0xFFFFFFFF - (0x0000000F << offset));
		*address = temp | ((mask & 0x0F) << offset);
	}
	
	return(OK);
}