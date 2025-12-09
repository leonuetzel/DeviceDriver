#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback Timer_13::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback Timer_13::init(uint32 frequency, bool enableInterrupt)
{
	RCC& rcc = STM32H753BIT6::get().get_rcc();
	const uint32 clock = rcc.get_clock_apb1_timer();
	
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
	
	
	rcc.module_clockInit(RCC::e_module::TIMER_13, true);
	
	*MCU::TIMER_13::PSC = prescaler - 1;
	*MCU::TIMER_13::ARR = (clock_divided / frequency) - 1;
	
	if(enableInterrupt == true)
	{
		bit::set(*MCU::TIMER_13::DIER, 0);
	}
	else
	{
		bit::clear(*MCU::TIMER_13::DIER, 0);
	}
	
	
	bit::set(*MCU::TIMER_13::CR1, 2);                                                                                             //  Only OVF/UVF triggers Interrupt
	
	bit::set(*MCU::TIMER_13::CR1, 0);                                                                                             //  Enable Timer
	return(OK);
}







void Timer_13::init_pwm(e_channel channel)
{
	switch(channel)
	{
		case e_channel::CHANNEL_1:
			*MCU::TIMER_13::CCMR1 &= 0xFF00;
			*MCU::TIMER_13::CCMR1 |= 0x60;
			bit::clear(*MCU::TIMER_13::CCER, 1);                                                                                      //  Channel 1 Active High
			bit::set(*MCU::TIMER_13::CCER, 0);                                                                                        //  Channel 1 Enable
			break;
			
		default:
			return;
	}
}


CODE_RAM void Timer_13::set_pwm(e_channel channel, uint32 dutycycle_ppm)
{
	uint32 ccr_temp = ((uint64) dutycycle_ppm * *MCU::TIMER_13::ARR) / 1000000;
	
	switch(channel)
	{
		case e_channel::CHANNEL_1:
			*MCU::TIMER_13::CCR1 = ccr_temp;
			break;
			
		default:
			return;
	}
}