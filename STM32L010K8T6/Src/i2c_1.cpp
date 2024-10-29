#include "../Inc/i2c_1.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback I2C_1::init()
{
	//	Select APB1 Clock as Kernel Clock
	*MCU::RCC::CCIPR &= 0xFFFFCFFF;
	
	
	//	PRESC = 14, SCLDEL = 9, SDADEL = 15, SCLH = 38, SCLL = 38
	*MCU::I2C_1::TIMINGR = 0xE09F2626;
	
	
	//	Enable I2C_1
	bit::set(*MCU::I2C_1::CR1, 0);
	
	return(OK);
}







CODE_RAM feedback I2C_1::start(uint8 slaveAddress, bool write, uint8 numberOfBytes)
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
	
	*MCU::I2C_1::CR2 = 0x02003000 | (numberOfBytes << 16) | (writeMask << 10) | (slaveAddress << 1);
	
	if(write == true)
	{
		//	Wait for TX Buffer to be free
		while(bit::isCleared(*MCU::I2C_1::ISR, 1))
		{
			//	Check if NACK received
			if(bit::isSet(*MCU::I2C_1::ISR, 4))
			{
				//	Clear NACK Flag
				bit::set(*MCU::I2C_1::ICR, 4);
				return(FAIL);
			}
		}
	}
	else
	{
		//	Wait for RX Buffer to be not empty
		while(bit::isCleared(*MCU::I2C_1::ISR, 2))
		{
			//	Check if NACK received
			if(bit::isSet(*MCU::I2C_1::ISR, 4))
			{
				//	Clear NACK Flag
				bit::set(*MCU::I2C_1::ICR, 4);
				return(FAIL);
			}
		}
	}
	
	
	return(OK);
}


CODE_RAM void I2C_1::stop()
{
	bit::set(*MCU::I2C_1::CR2, 14);
}


CODE_RAM feedback I2C_1::tx(uint8 data)
{
	if((*MCU::I2C_1::CR2 & 0x00FF0000) == 0)
	{
		return(FAIL);
	}
	
	//	Wait for TX Buffer to be free
	while(bit::isCleared(*MCU::I2C_1::ISR, 1))
	{
		//	Check if NACK received
		if(bit::isSet(*MCU::I2C_1::ISR, 4))
		{
			//	Clear NACK Flag
			bit::set(*MCU::I2C_1::ICR, 4);
			return(FAIL);
		}
	}
	
	*MCU::I2C_1::TXDR = data;
	
	return(OK);
}


CODE_RAM uint8 I2C_1::rx()
{
	while(bit::isCleared(*MCU::I2C_1::ISR, 2))
	{
		
	}
	
	uint8 data = *MCU::I2C_1::RXDR & 0x000000FF;
	
	return(data);
}