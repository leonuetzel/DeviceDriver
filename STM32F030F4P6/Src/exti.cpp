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

feedback EXTI::init_GPIO_interrupt(GPIO::e_pin pin, e_edge edge)
{
	const uint8 portNumber = GPIO::get_portNumber(pin);
	const uint8 pinNumber = GPIO::get_pinNumber(pin);
	
	
	volatile uint32* address = MCU::SYSCFG::EXTI_CR1 + pinNumber / 4;
	uint32 mask = portNumber;
	uint32 bitfield_startBit = 4 * (pinNumber % 4);
	uint32 temp = *address & (0xFFFFFFFF - (0x0F << bitfield_startBit));
	*address = temp | (mask << bitfield_startBit);
	
	switch(edge)
	{
		case e_edge::NONE:
			bit::clear(*MCU::EXTI::RTSR, pinNumber);
			bit::clear(*MCU::EXTI::FTSR, pinNumber);
			break;
			
		case e_edge::RISING:
			bit::set(*MCU::EXTI::RTSR, pinNumber);
			bit::clear(*MCU::EXTI::FTSR, pinNumber);
			break;
			
		case e_edge::FALLING:
			bit::clear(*MCU::EXTI::RTSR, pinNumber);
			bit::set(*MCU::EXTI::FTSR, pinNumber);
			break;
			
		case e_edge::TOGGLE:
			bit::set(*MCU::EXTI::RTSR, pinNumber);
			bit::set(*MCU::EXTI::FTSR, pinNumber);
			break;
			
		default:
			return(FAIL);
	}
	
	bit::set(*MCU::EXTI::IMR, pinNumber);
	
	return(OK);
}


feedback EXTI::init_interrupt_internal(e_line line, bool interrupt)
{
	if((uint32) line > 31)
	{
		return(FAIL);
	}
	
	uint32 bit = (uint32) line;
	bit::set(*MCU::EXTI::RTSR, bit);
	bit::clear(*MCU::EXTI::FTSR, bit);
	if(interrupt == true)
	{
		bit::set(*MCU::EXTI::IMR, bit);
	}
	else
	{
		bit::clear(*MCU::EXTI::IMR, bit);
	}
	
	return(OK);
}







feedback EXTI::clear_pendingBit(GPIO::e_pin pin)
{
	bit::set(*MCU::EXTI::PR, GPIO::get_pinNumber(pin));
	
	return(OK);
}


feedback EXTI::clear_pendingBit(e_line line)
{
	if((uint32) line > 32)
	{
		return(FAIL);
	}
	
	uint32 bit = (uint32) line;
	bit::set(*MCU::EXTI::PR, bit);
	
	return(OK);
}