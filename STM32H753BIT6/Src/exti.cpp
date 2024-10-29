#include "../Inc/exti.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback EXTI::startup()
{
	return(OK);
}







feedback EXTI::init_GPIO_interrupt(GPIO::e_pin pin, e_edge edge)
{
	const uint32 port = GPIO::get_portNumber(pin);
	const uint32 pinNumber = GPIO::get_pinNumber(pin);
	
	
	
	volatile uint32* address = MCU::SYSCFG::EXTI_CR1 + pinNumber / 4;
	uint32 mask = (uint32) port;
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
	
	set_GPIO_interrupt_state(pin, true);
	
	return(OK);
}


feedback EXTI::set_GPIO_interrupt_state(GPIO::e_pin pin, bool enable)
{
	const uint32 pinNumber = GPIO::get_pinNumber(pin);
	
	if(enable == true)
	{
		bit::set(*MCU::EXTI::CPUIMR1, pinNumber);
	}
	else
	{
		bit::clear(*MCU::EXTI::CPUIMR1, pinNumber);
	}
	return(OK);
}


CODE_RAM void EXTI::softwareTrigger(uint32 eventNumber)
{
	if(eventNumber < 22)
	{
		bit::set(*MCU::EXTI::SWIER1, eventNumber);
	}
	if(eventNumber == 49 || eventNumber == 51)
	{
		bit::set(*MCU::EXTI::SWIER2, eventNumber - 32);
	}
	if(eventNumber == 82 || eventNumber == 84 || eventNumber == 85 || eventNumber == 86)
	{
		bit::set(*MCU::EXTI::SWIER3, eventNumber - 64);
	}
}