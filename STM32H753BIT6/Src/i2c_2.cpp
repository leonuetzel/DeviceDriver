#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback I2C_2::startup()
{
	RCC& rcc = STM32H753BIT6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::I2C_2, true);
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback I2C_2::init()
{
	//	Select APB1 Clock as Kernel Clock
	*MCU::RCC::D2_CCIP2R &= 0xFFFFCFFF;
	
	
	//	PRESC = 14, SCLDEL = 9, SDADEL = 15, SCLH = 38, SCLL = 38
	*MCU::I2C_2::TIMINGR = 0xE09F2626;
	
	
	//	Enable I2C_2
	bit::set(*MCU::I2C_2::CR1, 0);
	
	
	return(OK);
}







CODE_RAM feedback I2C_2::start(uint8 slaveAddress, bool write, uint8 numberOfBytes, uint32 timeout_ms)
{
	if(slaveAddress > 0x7F)
	{
		return(FAIL);
	}
	
	uint8 writeMask = 0;
	
	if(write == false)
	{
		writeMask = 1;
	}
	
	*MCU::I2C_2::CR2 = 0x02003000 | (numberOfBytes << 16) | (writeMask << 10) | (slaveAddress << 1);
	
	
	volatile uint64& ticks = CMOS::get().get_ticks();
	const uint64 timestampStart = ticks;
	if(write == true)
	{
		//	Wait for TX Buffer to be free
		while(bit::isCleared(*MCU::I2C_2::ISR, 1))
		{
			//	Check for Timeout
			const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
			if(timeWaited_ms > timeout_ms)
			{
				return(FAIL);
			}
			
			
			//	Check if NACK received
			if(bit::isSet(*MCU::I2C_2::ISR, 4))
			{
				//	Clear NACK Flag
				bit::set(*MCU::I2C_2::ICR, 4);
				return(FAIL);
			}
		}
	}
	else
	{
		//	Wait for RX Buffer to be not empty
		while(bit::isCleared(*MCU::I2C_2::ISR, 2))
		{
			//	Check for Timeout
			const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
			if(timeWaited_ms > timeout_ms)
			{
				return(FAIL);
			}
			
			
			//	Check if NACK received
			if(bit::isSet(*MCU::I2C_2::ISR, 4))
			{
				//	Clear NACK Flag
				bit::set(*MCU::I2C_2::ICR, 4);
				return(FAIL);
			}
		}
	}
	
	
	return(OK);
}


CODE_RAM void I2C_2::stop()
{
	bit::set(*MCU::I2C_2::CR2, 14);
}


CODE_RAM feedback I2C_2::tx(uint8 data, uint32 timeout_ms)
{
	if((*MCU::I2C_2::CR2 & 0x00FF0000) == 0)
	{
		return(FAIL);
	}
	
	
	//	Timeout
	volatile uint64& ticks = CMOS::get().get_ticks();
	const uint64 timestampStart = ticks;
	
	
	//	Wait for TX Buffer to be free
	while(bit::isCleared(*MCU::I2C_2::ISR, 1))
	{
		//	Check for Timeout
		const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
		if(timeWaited_ms > timeout_ms)
		{
			return(FAIL);
		}
		
		
		//	Check if NACK received
		if(bit::isSet(*MCU::I2C_2::ISR, 4))
		{
			//	Clear NACK Flag
			bit::set(*MCU::I2C_2::ICR, 4);
			return(FAIL);
		}
	}
	
	*MCU::I2C_2::TXDR = data;
	
	return(OK);
}


CODE_RAM uint8 I2C_2::rx(uint32 timeout_ms)
{
	//	Timeout
	volatile uint64& ticks = CMOS::get().get_ticks();
	const uint64 timestampStart = ticks;
	
	
	while(bit::isCleared(*MCU::I2C_2::ISR, 2))
	{
		//	Check for Timeout
		const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
		if(timeWaited_ms > timeout_ms)
		{
			return(0);
		}
	}
	
	uint8 data = *MCU::I2C_2::RXDR & 0x000000FF;
	
	return(data);
}