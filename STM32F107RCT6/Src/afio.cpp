#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





void AFIO::write_mapr(uint32 mask, uint32 value)
{
	//	AFIO_MAPR can only be written with the AFIO Clock on
	STM32F107RCT6::get().get_rcc().module_clockInit(RCC::e_module::AFIO, true);
	
	
	//	SWJ_CFG (Bit 26-24) is write-only and reads as undefined: every Write sets it from m_debugConfiguration,
	//	else a Read-Modify-Write would switch the JTAG Pins on again
	const uint32 mapr = *MCU::AFIO::MAPR & ~(mask | 0x07000000);
	*MCU::AFIO::MAPR = mapr | (value & mask) | (((uint32) m_debugConfiguration) << 24);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

void AFIO::set_debugConfiguration(e_debugConfiguration debugConfiguration)
{
	//	The Configuration is kept: every later Write of AFIO_MAPR sets it again (see write_mapr)
	m_debugConfiguration = debugConfiguration;
	write_mapr(0, 0);
}


feedback AFIO::set_remap(e_remap remap, uint32 value)
{
	//	value is the Content of the Field, e.g. 0 = no Remap, 1 = Remap; for Fields with 2 Bits partial (1 or 2) and full Remap (3)
	const uint32 position = ((uint32) remap) & 0x0000001F;
	const uint32 numberOfBits = (((uint32) remap) >> 5) & 0x00000007;
	if(value >= (((uint32) 1) << numberOfBits))
	{
		return(FAIL);
	}
	const uint32 mask = ((((uint32) 1) << numberOfBits) - 1) << position;
	write_mapr(mask, value << position);
	return(OK);
}


void AFIO::set_extiExternalInterruptPin(MCU::PIN pin)
{
	//	EXTICR can only be written with the AFIO Clock on
	STM32F107RCT6::get().get_rcc().module_clockInit(RCC::e_module::AFIO, true);


	GPIO& gpio = STM32F107RCT6::get().get_gpio();
	const uint32 portNumber = gpio.get_portNumber(pin);
	const uint32 pinNumber = gpio.get_pinNumber(pin);
	
	
	volatile uint32* address = MCU::AFIO::EXTICR1 + pinNumber / 4;
	uint32 bitfield_startBit = 4 * (pinNumber % 4);
	uint32 temp = *address & (0xFFFFFFFF - (0x0F << bitfield_startBit));
	*address = temp | (portNumber << bitfield_startBit);
}