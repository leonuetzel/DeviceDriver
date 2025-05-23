#include "../Inc/timer_1.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback Timer_1::startup()
{
	return(OK);
}







feedback Timer_1::init(uint32 frequency, bool enableInterrupt)
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


	m_rcc.module_clockInit(RCC::e_module::TIMER_1, true);

	*MCU::TIMER_1::PSC = prescaler - 1;
	*MCU::TIMER_1::ARR = (clock_divided / frequency) - 1;

	if(enableInterrupt == true)
	{
		bit::set(*MCU::TIMER_1::DIER, 0);
	}
	else
	{
		bit::clear(*MCU::TIMER_1::DIER, 0);
	}


	bit::set(*MCU::TIMER_1::CR1, 2);                                                                                              //  Only OVF/UVF triggers Interrupt
	
	bit::set(*MCU::TIMER_1::CR1, 0);                                                                                              //  Enable Timer
	
	bit::set(*MCU::TIMER_1::BDTR, 15);																																														//	Enable Main Outputs
	return(OK);
}







void Timer_1::init_pwm(e_channel channel)
{
	switch(channel)
	{
		case e_channel::CHANNEL_1:
			*MCU::TIMER_1::CCMR1 &= 0xFF00;
			*MCU::TIMER_1::CCMR1 |= 0x60;
			bit::clear(*MCU::TIMER_1::CCER, 1);                                                                                      //  Channel 1 Active High
			bit::set(*MCU::TIMER_1::CCER, 0);                                                                                        //  Channel 1 Enable
			break;
		
		case e_channel::CHANNEL_2:
			*MCU::TIMER_1::CCMR1 &= 0x00FF;
			*MCU::TIMER_1::CCMR1 |= (0x60 << 8);
			bit::clear(*MCU::TIMER_1::CCER, 5);                                                                                      //  Channel 2 Active High
			bit::set(*MCU::TIMER_1::CCER, 4);                                                                                        //  Channel 2 Enable
			break;
			
		case e_channel::CHANNEL_3:
			*MCU::TIMER_1::CCMR2 &= 0xFF00;
			*MCU::TIMER_1::CCMR2 |= 0x60;
			bit::clear(*MCU::TIMER_1::CCER, 9);                                                                                      //  Channel 3 Active High
			bit::set(*MCU::TIMER_1::CCER, 8);                                                                                        //  Channel 3 Enable
			break;

		case e_channel::CHANNEL_4:
			*MCU::TIMER_1::CCMR2 &= 0x00FF;
			*MCU::TIMER_1::CCMR2 |= (0x60 << 8);
			bit::clear(*MCU::TIMER_1::CCER, 13);                                                                                     //  Channel 4 Active High
			bit::set(*MCU::TIMER_1::CCER, 12);                                                                                       //  Channel 4 Enable
			break;
			
		default:
			return;
	}
}


CODE_RAM void Timer_1::set_pwm(e_channel channel, uint32 dutycycle_ppm)
{
	uint32 ccr_temp = ((uint64) dutycycle_ppm * *MCU::TIMER_1::ARR) / 1000000;
	
	switch(channel)
	{
		case e_channel::CHANNEL_1:
			*MCU::TIMER_1::CCR1 = ccr_temp;
			break;

		case e_channel::CHANNEL_2:
			*MCU::TIMER_1::CCR2 = ccr_temp;
			break;
			
		case e_channel::CHANNEL_3:
			*MCU::TIMER_1::CCR3 = ccr_temp;
			break;
			
		case e_channel::CHANNEL_4:
			*MCU::TIMER_1::CCR4 = ccr_temp;
			break;

		default:
			return;
	}
}