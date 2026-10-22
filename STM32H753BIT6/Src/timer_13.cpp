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
	//	ARR is at most 0xFFFE, so that CCR = ARR + 1 (100 % Duty Cycle) still fits into the 16 Bit Register
	while((clock_divided / frequency) - 1 > 0x0000FFFE)
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
	
	
	//	Update Event: loads the Prescaler, it is buffered and would only be used after the first Overflow otherwise
	//	URS is set, so the Update Event does not trigger the Interrupt
	*MCU::TIMER_13::EGR = 1;
	
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


void Timer_13::set_pwm(e_channel channel, uint32 dutycycle_ppm)
{
	//	The Output is active while the Counter is below CCR (PWM Mode 1), so 100 % needs CCR = ARR + 1
	if(dutycycle_ppm > 1000000)
	{
		dutycycle_ppm = 1000000;
	}
	uint32 ccr_temp = ((uint64) dutycycle_ppm * ((uint64) *MCU::TIMER_13::ARR + 1)) / 1000000;
	
	switch(channel)
	{
		case e_channel::CHANNEL_1:
			*MCU::TIMER_13::CCR1 = ccr_temp;
			break;
			
		default:
			return;
	}
}