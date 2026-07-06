#include "../Inc/stm32c071kbu6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback EXTI::init_interrupt_GPIO(MCU::PIN pin, e_edge edge)
{
	GPIO& gpio = STM32C071KBU6::get().get_gpio();
	const uint32 port = gpio.get_portNumber(pin);
	const uint32 pinNumber = gpio.get_pinNumber(pin);
	
	
	//	Pin Selection
	volatile uint32* address = MCU::EXTI::EXTI_CR1 + pinNumber / 4;
	uint32 mask = (uint32) port;
	uint32 bitfield_startBit = 8 * (pinNumber % 4);
	uint32 temp = *address & (0xFFFFFFFF - (0x0F << bitfield_startBit));
	*address = temp | (mask << bitfield_startBit);
	
	
	//	Edge Selection
	if(bit::isSet((uint32) edge, 0) == true)
	{
		bit::set(*MCU::EXTI::RTSR1, pinNumber);
	}
	else
	{
		bit::clear(*MCU::EXTI::RTSR1, pinNumber);
	}
	
	if(bit::isSet((uint32) edge, 1) == true)
	{
		bit::set(*MCU::EXTI::FTSR1, pinNumber);
	}
	else
	{
		bit::clear(*MCU::EXTI::FTSR1, pinNumber);
	}
	
	
	//	Event Masking
	bit::set(*MCU::EXTI::IMR1, pinNumber);
	
	
	return(OK);
}



void EXTI::softwareTrigger(MCU::PIN pin)
{
	GPIO& gpio = STM32C071KBU6::get().get_gpio();
	const uint32 pinNumber = gpio.get_pinNumber(pin);
	softwareTrigger(pinNumber);
}







bool EXTI::isPendingRisingEdge(MCU::PIN pin)
{
	GPIO& gpio = STM32C071KBU6::get().get_gpio();
	const uint32 pinNumber = gpio.get_pinNumber(pin);
	return(bit::isSet(*MCU::EXTI::RPR1, pinNumber));
}


bool EXTI::isPendingFallingEdge(MCU::PIN pin)
{
	GPIO& gpio = STM32C071KBU6::get().get_gpio();
	const uint32 pinNumber = gpio.get_pinNumber(pin);
	return(bit::isSet(*MCU::EXTI::FPR1, pinNumber));
}







feedback EXTI::clear_pendingBitRisingEdge(MCU::PIN pin)
{
	GPIO& gpio = STM32C071KBU6::get().get_gpio();
	const uint32 pinNumber = gpio.get_pinNumber(pin);
	*MCU::EXTI::RPR1 = 1 << pinNumber;
	return(OK);
}


feedback EXTI::clear_pendingBitFallingEdge(MCU::PIN pin)
{
	GPIO& gpio = STM32C071KBU6::get().get_gpio();
	const uint32 pinNumber = gpio.get_pinNumber(pin);
	*MCU::EXTI::FPR1 = 1 << pinNumber;
	return(OK);
}