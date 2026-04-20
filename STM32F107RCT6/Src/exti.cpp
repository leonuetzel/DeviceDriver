#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void EXTI::afio_set_extiLine(MCU::PIN pin)
{
	STM32F107RCT6::get().get_afio().set_extiExternalInterruptPin(pin);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback EXTI::init_interrupt_GPIO(MCU::PIN pin, e_edge edge)
{
	//	AFIO Pin Selection
	afio_set_extiLine(pin);
	
	
	//	Edge Selection
	GPIO& gpio = STM32F107RCT6::get().get_gpio();
	const uint32 pinNumber = gpio.get_pinNumber(pin);
	if(bit::isSet((uint32) edge, 0) == true)
	{
		bit::set(*MCU::EXTI::RTSR, pinNumber);
	}
	else
	{
		bit::clear(*MCU::EXTI::RTSR, pinNumber);
	}
	
	if(bit::isSet((uint32) edge, 1) == true)
	{
		bit::set(*MCU::EXTI::FTSR, pinNumber);
	}
	else
	{
		bit::set(*MCU::EXTI::FTSR, pinNumber);
	}
	
	
	//	Event Masking
	bit::set(*MCU::EXTI::IMR, pinNumber);
	
	
	return(OK);
}


feedback EXTI::clear_pendingBit(MCU::PIN pin)
{
	GPIO& gpio = STM32F107RCT6::get().get_gpio();
	const uint32 pinNumber = gpio.get_pinNumber(pin);
	
	bit::set(*MCU::EXTI::PR, pinNumber);
	
	return(OK);
}