#include "../Inc/timer_17.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback Timer_17::startup()
{
	return(OK);
}







feedback Timer_17::init(uint32 frequency, bool enableInterrupt)
{
	uint32 clock = m_rcc.get_clock_apb2_timer();
	
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


	m_rcc.module_clockInit(RCC::e_module::TIMER_17, true);

	*MCU::TIMER_17::PSC = prescaler - 1;
	*MCU::TIMER_17::ARR = (clock_divided / frequency) - 1;

	if(enableInterrupt == true)
	{
		bit::set(*MCU::TIMER_17::DIER, 0);
	}
	else
	{
		bit::clear(*MCU::TIMER_17::DIER, 0);
	}


	bit::set(*MCU::TIMER_17::CR1, 2);                                                                                             //  Only OVF/UVF triggers Interrupt
	
	bit::set(*MCU::TIMER_17::CR1, 0);                                                                                             //  Enable Timer
	
	bit::set(*MCU::TIMER_17::BDTR, 15);																																														//	Enable Main Outputs
	return(OK);
}







void Timer_17::init_pwm(e_channel channel)
{
	switch(channel)
	{
		case e_channel::CHANNEL_1:
			*MCU::TIMER_17::CCMR1 &= 0xFF00;
			*MCU::TIMER_17::CCMR1 |= 0x60;
			bit::clear(*MCU::TIMER_17::CCER, 1);                                                                                      //  Channel 1 Active High
			bit::set(*MCU::TIMER_17::CCER, 0);                                                                                        //  Channel 1 Enable
			break;
			
		default:
			return;
	}
}


CODE_RAM void Timer_17::set_pwm(e_channel channel, uint32 dutycycle_ppm)
{
	uint32 ccr_temp = ((uint64) dutycycle_ppm * *MCU::TIMER_17::ARR) / 1000000;
	
	switch(channel)
	{
		case e_channel::CHANNEL_1:
			*MCU::TIMER_17::CCR1 = ccr_temp;
			break;
			
		default:
			return;
	}
}