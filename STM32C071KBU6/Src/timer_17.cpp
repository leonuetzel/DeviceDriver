#include "../Inc/stm32c071kbu6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback Timer_17::init(uint32 frequency, bool interrupt)
{
	uint32 clock = m_rcc.get_clock_apb_timer();
	
	uint32 prescaler = 1;
	uint32 clock_divided = clock;
	//	ARR is at most 0xFFFE, so that CCR = ARR + 1 (100 % Duty Cycle) still fits into a 16 Bit Register
	while((clock_divided / frequency) - 1 > 0x0000FFFE)
	{
		prescaler++;
		if(prescaler > 0x0000FFFF)
		{
			return(FAIL);
		}
		clock_divided = clock / prescaler;
	}
	
	*MCU::TIMER_17::PSC = prescaler - 1;
	*MCU::TIMER_17::ARR = (clock_divided / frequency) - 1;
	
	if(interrupt == true)
	{
		bit::set(*MCU::TIMER_17::DIER, 0);
	}
	else
	{
		bit::clear(*MCU::TIMER_17::DIER, 0);
	}
	
	
	//  Only OVF/UVF triggers Interrupt
	bit::set(*MCU::TIMER_17::CR1, 2);
	
	
	//	Update Event: loads the Prescaler, it is buffered and would only be used after the first Overflow otherwise
	//	URS is set, so the Update Event does not trigger the Interrupt
	*MCU::TIMER_17::EGR = 1;
	
	
	//	Main Output Enable
	bit::set(*MCU::TIMER_17::BDTR, 15);
	
	
	//  Enable Timer
	bit::set(*MCU::TIMER_17::CR1, 0);
	
	
	return(OK);
}







void Timer_17::init_pwm(e_channel channel)
{
	switch(channel)
	{
		case e_channel::CHANNEL_1:
		{
			*MCU::TIMER_17::CCMR1 &= 0xFF00;
			*MCU::TIMER_17::CCMR1 |= 0x60;
			
			
			//  Channel 1 Active High
			bit::clear(*MCU::TIMER_17::CCER, 1);
			
			
			//  Channel 1 Enable
			bit::set(*MCU::TIMER_17::CCER, 0);
		}
		break;
		
		default:
		{
			return;
		}
	}
}


void Timer_17::set_pwm(e_channel channel, uint32 dutycycle_ppm)
{
	//	The Output is active while the Counter is below CCR (PWM Mode 1), so 100 % needs CCR = ARR + 1
	if(dutycycle_ppm > 1000000)
	{
		dutycycle_ppm = 1000000;
	}
	uint32 ccr_temp = ((uint64) dutycycle_ppm * ((uint64) *MCU::TIMER_17::ARR + 1)) / 1000000;
	
	switch(channel)
	{
		case e_channel::CHANNEL_1:
		{
			*MCU::TIMER_17::CCR1 = ccr_temp;
		}
		break;
		
		default:
		{
			return;
		}
	}
}