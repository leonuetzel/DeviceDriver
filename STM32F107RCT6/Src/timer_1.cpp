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

feedback Timer_1::init(uint32 frequency, bool interrupt)
{
	//	Reset Timer 1
	RCC& rcc = STM32F107RCT6::get().get_rcc();
	rcc.module_reset(RCC::e_module::TIMER_1);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::TIMER_1, true);
	
	
	//	Clock
	uint32 clock = rcc.get_clock_apb2_timer();
	
	uint32 prescaler = 1;
	uint32 clock_divided = clock;
	while((clock_divided / frequency) - 1 > 0x0000FFFF)
	{
		prescaler++;
		if(prescaler > 0x0000FFFF)
		{
			return(FAIL);
		}
		clock_divided = clock / prescaler;
	}
	
	
	*MCU::TIMER_1::PSC = prescaler - 1;
	*MCU::TIMER_1::ARR = (clock_divided / frequency) - 1;

	if(interrupt == true)
	{
		bit::set(*MCU::TIMER_1::DIER, 0);
	}
	else
	{
		bit::clear(*MCU::TIMER_1::DIER, 0);
	}
	
	
	//  Only OVF/UVF triggers Interrupt
	bit::set(*MCU::TIMER_1::CR1, 2);
	
	
	//	Enable Main Output
	bit::set(*MCU::TIMER_1::BDTR, 15);
	
	
	//  Enable Timer
	bit::set(*MCU::TIMER_1::CR1, 0);
	
	
	return(OK);
}