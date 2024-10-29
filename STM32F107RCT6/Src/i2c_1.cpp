#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback I2C_1::start(uint8 slaveAddress, uint32 timeout_ms, bool clearADDR)
{
	//	Send Start Condition
	bit::set(*MCU::I2C_1::CR1, 8);
	
	
	//	Wait for Start Condition to be generated
	while(bit::isCleared(*MCU::I2C_1::SR1, 0) == true)
	{
		
	}
	
	
	//	Send 8-Bit Slave Address
	*MCU::I2C_1::DR = slaveAddress;
	
	
	//	Wait for Slave Address to be transmitted
	//	Bit ADDR in SR1 Register will be set only if there was an ACK received, but not if there was a NACK
	//	Read SR2 Register after reading SR1 Register to clear the ADDR Bit in SR1
	uint32 timeoutCounter = 0;
	CMOS& cmos = CMOS::get();
	while(bit::isCleared(*MCU::I2C_1::SR1, 1) == true)
	{
		//	Check for NACK or Timeout
		if(bit::isSet(*MCU::I2C_1::SR1, 10) == true || timeoutCounter > timeout_ms)
		{
			//	Send STOP Condition on NACK to release the Bus
			stop();
			
			
			return(FAIL);
		}
		
		
		//	Sleep
		timeoutCounter++;
		cmos.sleep_ms(1);
	}
	
	
	//	Clear ADDR Bit by reading SR2 Register
	//	This is normally needed but due to Errors (see Errata Sheet and/or Appnote AN2824, Rev. 4, Chapter 1.2.1, Page 5)
	//	the Rx Routine needs to be able to omit this
	if(clearADDR == true)
	{
		*MCU::I2C_1::SR2;
	}
	
	
	return(OK);
}


inline void I2C_1::stop()
{
	bit::set(*MCU::I2C_1::CR1, 9);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback I2C_1::init(e_mode mode)
{
	//	Enable I2C Bus Clock
	RCC& rcc = STM32F107RCT6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::I2C_1, true);
	
	
	//	Disable I2C
	bit::clear(*MCU::I2C_1::CR1, 0);
	
	
	//	Reset I2C
	rcc.module_reset(RCC::e_module::I2C_1);
	
	
	//	Timings
	//	Standard Mode 100 kHz / SMBus
	//		T_high	= CCR x T_PCLK1
	//		T_low		= CCR x T_PCLK1
	//	Fast Mode 400 kHz
	//		T_high	= CCR x T_PCLK1
	//		T_low		= 2 x CCR x T_PCLK1
	
	//	T_high	= t_r(SCL) + t_w(SCLH)
	//	T_low		= t_f(SCL) + t_w(SCLL)
	
	//	Values taken from Datasheet DocID15274 Rev. 10, Chapter 5.3.16, Table 41, Page 64
	//	Parameter			Standard Mode 100 kHz			Fast Mode 400 kHz
	//	t_r(SCL)			1000ns										300ns
	//	t_f(SCL)			300ns											300ns
	//	t_w(SCLH)			4000ns										600ns
	//	t_w(SCLL)			4700ns										1300ns
	
	//	T_PCLK1 [µs] = 1 / clock_apb1 [MHz]
	
	
	
	//	Calculations for Standard Mode 100 kHz
	//	T_high_SM	= 1000ns + 4000ns	= 5000ns
	//	T_low_SM	= 300ns + 4700ns	= 5000ns
	
	//	CCR_tHigh_SM	= T_high_SM [µs]	/ T_PCLK1 [µs] = T_high_SM [µs]	x clock_apb1 [MHz]
	//	CCR_tLow_SM		= T_low_SM [µs]		/ T_PCLK1 [µs] = T_low_SM [µs]	x clock_apb1 [MHz]
	//	T_high_SM == T_low_SM -> CCR_tHigh_SM == CCR_tLow_SM == CCR_SM
	//	CCR_SM = 5µs x clock_apb1 [MHz]
	//	TRISE_SM	= t_r(SCL)_SM [µs] / T_PCLK1 [µs] + 1 = t_r(SCL)_SM [µs] x clock_apb1 [MHz] + 1
	//	TRISE_SM	= 1µs x clock_apb1 [MHz] + 1
	
	
	//	Calculations for Fast Mode 400 kHz
	//	T_high_FM	= 300ns + 600ns		= 900ns
	//	T_low_FM	= 300ns + 1300ns	= 2600ns
	
	//	CCR_tHigh_FM	= T_high_FM [µs]	/ T_PCLK1 [µs]				= T_high_FM [µs]	x clock_apb1 [MHz]				= 0.9µs x clock_apb1 [MHz]
	//	CCR_tLow_FM		= T_low_FM [µs]		/ (T_PCLK1 [µs] x 2)	= T_low_FM [µs]		x clock_apb1 [MHz] x 0.5	= 1.3µs x clock_apb1 [MHz]
	//	CCR_FM is taken as Medium Value between 0.9µs and 1.3µs
	//	CCR_FM = 1.25µs x clock_apb1 [MHz]
	//	TRISE_FM	= t_r(SCL)_FM [µs] / T_PCLK1 [µs] + 1 = t_r(SCL)_FM [µs] x clock_apb1 [MHz] + 1
	//	TRISE_FM	= 0.3µs x clock_apb1 [MHz] + 1
	
	
	//	Calculation: t = 1 / f -> a Multiplication with t is equal to a Division by f
	//	This Way, we dont need any floating Point here
	const uint32 clock_apb1 = rcc.get_clock_apb1();
	uint32 CCR = 0;
	uint32 TRISE = 0;
	switch(mode)
	{
		case e_mode::STANDARD_100KHZ:
		{
			CCR = clock_apb1 / 200000;
			TRISE = clock_apb1 / 1000000 + 1;
		}
		break;
		
		case e_mode::FAST_400KHZ:
		{
			CCR = clock_apb1 / 800000;
			TRISE = clock_apb1 / 3333333 + 1;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	
	//	Restriction: CCR >= 0x04
	if(CCR < 0x04)
	{
		return(FAIL);
	}
	
	
	//	Write Timing Values
	uint32 temp = *MCU::I2C_1::CCR & 0xFFFFF000;
	*MCU::I2C_1::CCR = temp | CCR;
	
	temp = *MCU::I2C_1::TRISE & 0xFFFFFFC0;
	*MCU::I2C_1::TRISE = temp | TRISE;
	
	
	//	I2C Input Clock
	temp = *MCU::I2C_1::CR2 & 0xFFFFFFC0;
	*MCU::I2C_1::CR2 = temp | (clock_apb1 / 1000000);
	
	
	//	Enable I2C
	bit::set(*MCU::I2C_1::CR1, 0);
	
	
	return(OK);
}







CODE_RAM feedback I2C_1::tx(uint8 slaveAddress, uint8 data, uint32 timeout_ms)
{
	//	Check for Constraints on 7-Bit Slave Address
	if(slaveAddress > 0x7F)
	{
		return(FAIL);
	}
	
	
	//	Send Start Condition
	const uint8 slaveAddress_8bit = slaveAddress << 1;
	if(start(slaveAddress_8bit, timeout_ms) != OK)
	{
		return(FAIL);
	}
	
	
	//	Write Data to Tx Buffer
	*MCU::I2C_1::DR = data;
	
	
	//	Wait for Tx Buffer to be empty of NACK received
	uint32 timeoutCounter = 0;
	CMOS& cmos = CMOS::get();
	while(bit::isCleared(*MCU::I2C_1::SR1, 7) == true)
	{
		//	Check for NACK or Timeout
		if(bit::isSet(*MCU::I2C_1::SR1, 10) == true || timeoutCounter > timeout_ms)
		{
			//	Send STOP Condition on NACK to release the Bus
			stop();
			
			
			//	Reset NACK Flag (AF Acknowledge Failure Bit)
			bit::clear(*MCU::I2C_1::SR1, 10);
			
			
			return(FAIL);
		}
		
		
		//	Sleep
		timeoutCounter++;
		cmos.sleep_ms(1);
	}
	
	
	//	Check for NACK or Timeout
	if(bit::isSet(*MCU::I2C_1::SR1, 10) == true)
	{
		//	Send STOP Condition on NACK to release the Bus
		stop();
		
		
		//	Reset NACK Flag (AF Acknowledge Failure Bit)
		bit::clear(*MCU::I2C_1::SR1, 10);
		
		
		return(FAIL);
	}
	
	
	//	Send STOP Condition
	stop();
	
	
	return(OK);
}


CODE_RAM feedback I2C_1::tx(uint8 slaveAddress, const Array<uint8>& data, uint32 timeout_ms)
{
	//	Check for Constraints on 7-Bit Slave Address
	if(slaveAddress > 0x7F)
	{
		return(FAIL);
	}
	
	
	//	Send Start Condition
	const uint8 slaveAddress_8bit = slaveAddress << 1;
	if(start(slaveAddress_8bit, timeout_ms) != OK)
	{
		return(FAIL);
	}
	
	
	for(auto& i: data)
	{
		//	Write Data to Tx Buffer
		*MCU::I2C_1::DR = i;
		
		
		//	Wait for Tx Buffer to be empty of NACK received
		uint32 timeoutCounter = 0;
		CMOS& cmos = CMOS::get();
		while(bit::isCleared(*MCU::I2C_1::SR1, 7) == true)
		{
			//	Check for NACK or Timeout
			if(bit::isSet(*MCU::I2C_1::SR1, 10) == true || timeoutCounter > timeout_ms)
			{
				//	Send STOP Condition on NACK to release the Bus
				stop();
				
				
				//	Reset NACK Flag (AF Acknowledge Failure Bit)
				bit::clear(*MCU::I2C_1::SR1, 10);
				
				
				return(FAIL);
			}
			
			
			//	Sleep
			timeoutCounter++;
			cmos.sleep_ms(1);
		}
	}
	
	
	//	Check for NACK or Timeout
	if(bit::isSet(*MCU::I2C_1::SR1, 10) == true)
	{
		//	Send STOP Condition on NACK to release the Bus
		stop();
		
		
		//	Reset NACK Flag (AF Acknowledge Failure Bit)
		bit::clear(*MCU::I2C_1::SR1, 10);
		
		
		return(FAIL);
	}
	
	
	//	Send STOP Condition
	stop();
	
	
	return(OK);
}


CODE_RAM Array<uint8> I2C_1::rx(uint8 slaveAddress, uint32 numberOfByte, uint32 timeout_ms)
{
	//	8 Bit Slave Address
	const uint8 slaveAddress_8bit = (slaveAddress << 1) | 0x01;
	
	
	//	POS = 0
	bit::clear(*MCU::I2C_1::CR1, 11);
	
	
	//	ACK each received Byte
	bit::set(*MCU::I2C_1::CR1, 10);
	
	
	volatile uint64& ticks = CMOS::get().get_ticks();
	NVIC& nvic = CMOS::get().get_nvic();
	Array<uint8> data(0, numberOfByte);
	if(numberOfByte > 2)
	{
		//	Send START Condition
		start(slaveAddress_8bit, timeout_ms);
		
		
		//	Receive Bytes until only 3 Byte are left to receive
		for(uint32 i = 0; i < numberOfByte - 3; i++)
		{
			//	Wait for next Byte
			const uint64 timestampStart = ticks;
			while(bit::isCleared(*MCU::I2C_1::SR1, 6) == true)
			{
				//	Check for Timeout
				const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
				if(timeWaited_ms > timeout_ms)
				{
					return(Array<uint8>());
				}
			}
			data[i] = *MCU::I2C_1::DR;
		}
		
		
		//	Wait for 2 more Byte to be received
		const uint64 timestampStart = ticks;
		while(bit::isCleared(*MCU::I2C_1::SR1, 2) == true)
		{
			//	Check for Timeout (doubled because of 2 Byte to be received)
			const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
			if(timeWaited_ms > 2 * timeout_ms)
			{
				return(Array<uint8>());
			}
		}
		
		
		//	Prepare to send a NACK
		bit::clear(*MCU::I2C_1::CR1, 10);
		
		
		//	Read next Byte
		data[numberOfByte - 3] = *MCU::I2C_1::DR;
		
		
		//	Disable Interrupts
		nvic.disable_allExceptions();
		
		
		//	Prepare to send a STOP Condition
		stop();
		
		
		//	Read next Byte
		data[numberOfByte - 2] = *MCU::I2C_1::DR;
		
		
		//	Enable Interrupts
		nvic.enable_allExceptions();
		
		
		//	Read last Byte
		data[numberOfByte - 1] = *MCU::I2C_1::DR;
	}
	if(numberOfByte == 2)
	{
		//	Send START Condition
		start(slaveAddress_8bit, timeout_ms, false);
		
		
		//	Send NACK on the next (not the current) Byte received
		bit::set(*MCU::I2C_1::CR1, 11);
		
		
		//	Disable Interrupts
		nvic.disable_allExceptions();
		
		
		//	Clear ADDR Bit by reading the SR2 Register
		*MCU::I2C_1::SR2;
		
		
		//	Prepare to send a NACK
		bit::clear(*MCU::I2C_1::CR1, 10);
		
		
		//	Enable Interrupts
		nvic.enable_allExceptions();
		
		
		//	Wait until 2 Byte are received
		const uint64 timestampStart = ticks;
		while(bit::isCleared(*MCU::I2C_1::SR1, 2) == true)
		{
			//	Check for Timeout (doubled because of 2 Byte to be received)
			const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
			if(timeWaited_ms > 2 * timeout_ms)
			{
				return(Array<uint8>());
			}
		}
		
		
		//	Disable Interrupts
		nvic.disable_allExceptions();
		
		
		//	Prepare to send a STOP Condition
		stop();
		
		
		//	Read first Byte
		data[0] = *MCU::I2C_1::DR;
		
		
		//	Enable Interrupts
		nvic.enable_allExceptions();
		
		
		//	Read last Byte
		data[1] = *MCU::I2C_1::DR;
	}
	if(numberOfByte == 1)
	{
		//	Send START Condition
		start(slaveAddress_8bit, timeout_ms, false);
		
		
		//	Prepare to send a NACK
		bit::clear(*MCU::I2C_1::CR1, 10);
		
		
		//	Disable Interrupts
		nvic.disable_allExceptions();
		
		
		//	Clear ADDR Bit by reading the SR2 Register
		*MCU::I2C_1::SR2;
		
		
		//	Prepare to send a STOP Condition
		stop();
		
		
		//	Enable Interrupts
		nvic.enable_allExceptions();
		
		
		//	Wait until 1 Byte is received
		const uint64 timestampStart = ticks;
		while(bit::isCleared(*MCU::I2C_1::SR1, 6) == true)
		{
			//	Check for Timeout
			const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
			if(timeWaited_ms > timeout_ms)
			{
				return(Array<uint8>());
			}
		}
		
		
		//	Read Byte
		data[0] = *MCU::I2C_1::DR;
	}
	if(numberOfByte == 0)
	{
		//	Send START Condition
		start(slaveAddress_8bit, timeout_ms, false);
		
		
		//	Send STOP Condition
		stop();
	}
	
	
	return(data);
}