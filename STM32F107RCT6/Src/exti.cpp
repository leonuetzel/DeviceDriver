#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void EXTI::afio_set_extiLine(GPIO::e_pin pin)
{
	STM32F107RCT6::get().get_afio().set_extiExternalInterruptPin(pin);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/
