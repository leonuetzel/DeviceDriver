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

void AFIO::set_debugConfiguration(e_debugConfiguration debugConfiguration)
{
	STM32F107RCT6::get().get_rcc().module_clockInit(RCC::e_module::AFIO, true);
	
	uint32 afio_mapr = *MCU::AFIO::MAPR;
	afio_mapr &= 0xF8FFFFFF;
	*MCU::AFIO::MAPR = afio_mapr | (((uint32) debugConfiguration) << 24);
}


void AFIO::set_extiExternalInterruptPin(MCU::PIN pin)
{
	GPIO& gpio = STM32F107RCT6::get().get_gpio();
	const uint32 portNumber = gpio.get_portNumber(pin);
	const uint32 pinNumber = gpio.get_pinNumber(pin);
	
	
	volatile uint32* address = MCU::AFIO::EXTICR1 + pinNumber / 4;
	uint32 bitfield_startBit = 4 * (pinNumber % 4);
	uint32 temp = *address & (0xFFFFFFFF - (0x0F << bitfield_startBit));
	*address = temp | (portNumber << bitfield_startBit);
}