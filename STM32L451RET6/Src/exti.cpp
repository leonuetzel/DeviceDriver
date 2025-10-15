#include "../Inc/stm32l451ret6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback EXTI::init_GPIO_interrupt(MCU::PIN pin, e_edge edge)
{
	GPIO& gpio = STM32L451RET6::get().get_gpio();
	const uint8 portNumber = gpio.get_portNumber(pin);
	const uint8 pinNumber = gpio.get_pinNumber(pin);
	
	
	volatile uint32* address = MCU::SYSCFG::EXTI_CR1 + pinNumber / 4;
	uint32 mask = portNumber;
	uint32 bitfield_startBit = 4 * (pinNumber % 4);
	uint32 temp = *address & (0xFFFFFFFF - (0x0F << bitfield_startBit));
	*address = temp | (mask << bitfield_startBit);
	
	switch(edge)
	{
		case e_edge::NONE:
			bit::clear(*MCU::EXTI::RTSR1, pinNumber);
			bit::clear(*MCU::EXTI::FTSR1, pinNumber);
			break;
			
		case e_edge::RISING:
			bit::set(*MCU::EXTI::RTSR1, pinNumber);
			bit::clear(*MCU::EXTI::FTSR1, pinNumber);
			break;
			
		case e_edge::FALLING:
			bit::clear(*MCU::EXTI::RTSR1, pinNumber);
			bit::set(*MCU::EXTI::FTSR1, pinNumber);
			break;
			
		case e_edge::TOGGLE:
			bit::set(*MCU::EXTI::RTSR1, pinNumber);
			bit::set(*MCU::EXTI::FTSR1, pinNumber);
			break;
			
		default:
			return(FAIL);
	}
	
	bit::set(*MCU::EXTI::IMR1, pinNumber);
	
	return(OK);
}


feedback EXTI::init_interrupt_internal(e_line line, bool interrupt)
{
	//	Boundary check
	if((uint32) line > 40)
	{
		return(FAIL);
	}
	
	
	//	Get Registers
	const uint32 registerOffset = ((uint32) line) / 32;
	const uint32 bit = ((uint32) line) % 32;
	
	
	uint32* const RTSR	= (uint32* const) MCU::EXTI::RTSR1	+ 0x20 * registerOffset;
	uint32* const FTSR	= (uint32* const) MCU::EXTI::FTSR1	+ 0x20 * registerOffset;
	uint32* const IMR		= (uint32* const) MCU::EXTI::IMR1		+ 0x20 * registerOffset;
	
	
	//	Configure
	bit::set(*RTSR, bit);
	bit::clear(*FTSR, bit);
	
	if(interrupt == true)
	{
		bit::set(*IMR, bit);
	}
	else
	{
		bit::clear(*IMR, bit);
	}
	
	return(OK);
}


feedback EXTI::init_event_internal(e_line line, bool event)
{
	//	Boundary check
	if((uint32) line > 40)
	{
		return(FAIL);
	}
	
	
	//	Get Registers
	const uint32 registerOffset = ((uint32) line) / 32;
	const uint32 bit = ((uint32) line) % 32;
	
	
	uint32* const RTSR	= (uint32* const) MCU::EXTI::RTSR1	+ 0x20 * registerOffset;
	uint32* const FTSR	= (uint32* const) MCU::EXTI::FTSR1	+ 0x20 * registerOffset;
	uint32* const EMR		= (uint32* const) MCU::EXTI::EMR1		+ 0x20 * registerOffset;
	
	
	//	Configure
	bit::set(*RTSR, bit);
	bit::clear(*FTSR, bit);
	
	if(event == true)
	{
		bit::set(*EMR, bit);
	}
	else
	{
		bit::clear(*EMR, bit);
	}
	
	return(OK);
}







feedback EXTI::clear_pendingBit(MCU::PIN pin)
{
	GPIO& gpio = STM32L451RET6::get().get_gpio();
	*MCU::EXTI::PR1 = 1 << gpio.get_pinNumber(pin);
	return(OK);
}


feedback EXTI::clear_pendingBit(e_line line)
{
	//	Boundary Check
	if((uint32) line > 40)
	{
		return(FAIL);
	}
	
	
	//	Get Register
	const uint32 registerOffset = ((uint32) line) / 32;
	const uint32 bit = ((uint32) line) % 32;
	
	
	uint32* const PR = (uint32* const) MCU::EXTI::PR1 + 0x20 * registerOffset;
	
	
	//	Clear pending Bit by writing 1 to it
	*PR = 1 << bit;
	
	return(OK);
}


bool EXTI::isPending(MCU::PIN pin)
{
	GPIO& gpio = STM32L451RET6::get().get_gpio();
	return(bit::isSet(*MCU::EXTI::PR1, gpio.get_pinNumber(pin)));
}


bool EXTI::isPending(e_line line)
{
	//	Boundary Check
	if((uint32) line > 40)
	{
		return(false);
	}
	
	
	//	Get Register
	const uint32 registerOffset = ((uint32) line) / 32;
	const uint32 bit = ((uint32) line) % 32;
	
	
	uint32* const PR = (uint32* const) MCU::EXTI::PR1 + 0x20 * registerOffset;
	
	
	//	Check pending Bit
	return(bit::isSet(*PR, bit));
}