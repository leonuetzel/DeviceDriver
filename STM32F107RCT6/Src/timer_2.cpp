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

feedback Timer_2::init(uint32 frequency, bool interrupt)
{
	//	Reset Timer
	RCC& rcc = STM32F107RCT6::get().get_rcc();
	rcc.module_reset(RCC::e_module::TIMER_2);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::TIMER_2, true);
	
	
	//	Clock
	uint32 clock = rcc.get_clock_apb1_timer();
	
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
	
	
	*MCU::TIMER_2::PSC = prescaler - 1;
	*MCU::TIMER_2::ARR = (clock_divided / frequency) - 1;

	if(interrupt == true)
	{
		bit::set(*MCU::TIMER_2::DIER, 0);
	}
	else
	{
		bit::clear(*MCU::TIMER_2::DIER, 0);
	}
	
	
	//  Only OVF/UVF triggers Interrupt
	bit::set(*MCU::TIMER_2::CR1, 2);
	
	
	//  Enable Timer
	bit::set(*MCU::TIMER_2::CR1, 0);
	
	
	return(OK);
}