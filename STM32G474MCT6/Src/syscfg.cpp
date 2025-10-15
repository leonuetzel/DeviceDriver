#include "../Inc/stm32g474mct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

void SYSCFG::selectPinForEXTI(MCU::PIN pin)
{
	GPIO& gpio = STM32G474MCT6::get().get_gpio();
	const uint8 portNumber = gpio.get_portNumber(pin);
	const uint8 pinNumber = gpio.get_pinNumber(pin);
	
	const uint32 registerOffset = pinNumber / 4;
	const uint32 bitOffset = (pinNumber % 4) * 4;
	
	const uint32 maskClearing = 0xFFFFFFFF - (0x07 << bitOffset);
	
	uint32* const EXTI_CR = (uint32* const) MCU::SYSCFG::EXTI_CR1 + registerOffset;
	
	const uint32 temp = *EXTI_CR & maskClearing;
	*EXTI_CR = temp | (portNumber << bitOffset);
}