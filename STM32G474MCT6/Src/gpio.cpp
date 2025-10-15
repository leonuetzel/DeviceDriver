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

CODE_RAM feedback GPIO::init_pin(MCU::PIN pin, e_mode mode, e_speed speed, e_pupd pupd)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	
	
	const uint32 offset = port * 0x00000100;
	volatile uint32* reg_mode = MCU::GPIO_A::MODE + offset;
	volatile uint32* reg_otype = MCU::GPIO_A::OTYPE + offset;
	volatile uint32* reg_ospeed = MCU::GPIO_A::OSPEED + offset;
	volatile uint32* reg_pupd = MCU::GPIO_A::PUPD + offset;
	
	
	//	"mode" Parameter:
	//	Bit 2 - 1: MODE Field of GPIO::MODE Register
	//							00 = Input
	//							01 = General Purpose Output
	//							10 = Alternate Function
	//							11 = Analog Mode
	//	Bit 0: OT Bit of GPIO::OTYPE Register
	//							0 = Output Push-Pull
	//							1 = Output Open-Drain
	
	
	//	Mode
	uint32 mask = (((uint32) mode) & 0x6) >> 1;
	
	uint32 temp = *reg_mode & (0xFFFFFFFF - (0x03 << (2 * pinNumber)));
	*reg_mode = temp | (mask << (2 * pinNumber));
	
	
	//	Output Type
	if(bit::isSet(((uint32) mode), 0) == true)
	{
		bit::set(*reg_otype, pinNumber);
	}
	else
	{
		bit::clear(*reg_otype, pinNumber);
	}
	
	
	//	Speed
	mask = ((uint32) speed);
	temp = *reg_ospeed & (0xFFFFFFFF - (0x03 << (2 * pinNumber)));
	*reg_ospeed = temp | (mask << (2 * pinNumber));
	
	
	//	Pull-Up / Pull-Down
	mask = ((uint32) pupd);
	temp = *reg_pupd & (0xFFFFFFFF - (0x03 << (2 * pinNumber)));
	*reg_pupd = temp | (mask << (2 * pinNumber));
	
	
	
	return(OK);
}