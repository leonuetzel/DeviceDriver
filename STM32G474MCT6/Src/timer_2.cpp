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

feedback Timer_2::init(uint32 frequency, bool interrupt)
{
	uint32 clock = m_rcc.get_clock_apb1_timer();
	
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







void Timer_2::init_pwm(e_channel channel)
{
	switch(channel)
	{
		case e_channel::CHANNEL_1:
		{
			*MCU::TIMER_2::CCMR1 &= 0xFF00;
			*MCU::TIMER_2::CCMR1 |= 0x60;
			
			
			//  Channel 1 Active High
			bit::clear(*MCU::TIMER_2::CCER, 1);
			
			
			//  Channel 1 Enable
			bit::set(*MCU::TIMER_2::CCER, 0);
		}
		break;
		
		case e_channel::CHANNEL_2:
		{
			*MCU::TIMER_2::CCMR1 &= 0x00FF;
			*MCU::TIMER_2::CCMR1 |= (0x60 << 8);
			
			
			//  Channel 2 Active High
			bit::clear(*MCU::TIMER_2::CCER, 5);
			
			
			//  Channel 2 Enable
			bit::set(*MCU::TIMER_2::CCER, 4);
		}
		break;
			
		case e_channel::CHANNEL_3:
		{
			*MCU::TIMER_2::CCMR2 &= 0xFF00;
			*MCU::TIMER_2::CCMR2 |= 0x60;
			
			
			//  Channel 3 Active High
			bit::clear(*MCU::TIMER_2::CCER, 9);
			
			
			//  Channel 3 Enable
			bit::set(*MCU::TIMER_2::CCER, 8);
		}
		break;

		case e_channel::CHANNEL_4:
		{
			*MCU::TIMER_2::CCMR2 &= 0x00FF;
			*MCU::TIMER_2::CCMR2 |= (0x60 << 8);
			
			
			//  Channel 4 Active High
			bit::clear(*MCU::TIMER_2::CCER, 13);
			
			
			//  Channel 4 Enable
			bit::set(*MCU::TIMER_2::CCER, 12);
		}
		break;
		
		default:
		{
			return;
		}
	}
}


void Timer_2::set_pwm(e_channel channel, uint32 dutycycle_ppm)
{
	uint32 ccr_temp = ((uint64) dutycycle_ppm * *MCU::TIMER_2::ARR) / 1000000;
	
	switch(channel)
	{
		case e_channel::CHANNEL_1:
		{
			*MCU::TIMER_2::CCR1 = ccr_temp;
		}
		break;
		
		case e_channel::CHANNEL_2:
		{
			*MCU::TIMER_2::CCR2 = ccr_temp;
		}
		break;
		
		case e_channel::CHANNEL_3:
		{
			*MCU::TIMER_2::CCR3 = ccr_temp;
		}
		break;
		
		case e_channel::CHANNEL_4:
		{
			*MCU::TIMER_2::CCR4 = ccr_temp;
		}
		break;
		
		default:
		{
			return;
		}
	}
}