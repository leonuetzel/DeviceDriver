#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback I2C_2::start(uint8 slaveAddress, uint32 timeout_ms, bool clearADDR)
{
	//	Enable I2C Interrupt
	CMOS& cmos = CMOS::get();
	NVIC& nvic = cmos.get_nvic();
	nvic.enable(Interrupt::I2C_2_EVENT);
	
	
	//	Send Start Condition
	bit::set(*MCU::I2C_2::CR1, 8);
	
	
	//	Wait for Start Condition to be generated
	while(bit::isCleared(*MCU::I2C_2::SR1, 0))
	{
		
	}
	
	
	//	Listen to TxE Event
	cmos.event_listen(m_eventID_TxE);
	
	
	//	Send 8-Bit Slave Address
	*MCU::I2C_2::DR = slaveAddress;
	
	
	//	Wait for Slave Address to be transmitted
	//	Bit ADDR in SR1 Register will be set only if there was an ACK received, but not if there was a NACK
	//	Read SR2 Register after reading SR1 Register to clear the ADDR Bit in SR1
	uint64 timestamp = cmos.get_ticks();
	while(1)
	{
		//	Slave Address has been transmitted + ACK received
		if(bit::isSet(*MCU::I2C_2::SR1, 1))
		{
			break;
		}
		
		
		//	Timeout Check
		bool timeout = false;
		if(cmos.get_ticks() - timestamp > (cmos.c_clock_systick / 1000) * timeout_ms)
		{
			timeout = true;
		}
		
		
		//	Slave Address has been transmitted + NACK received
		if(bit::isSet(*MCU::I2C_2::SR1, 10) || timeout == true)
		{
			//	Send STOP Condition to release the Bus
			stop();
			
			
			return(FAIL);
		}
	}
	
	
	//	Clear ADDR Bit by reading SR2 Register
	//	This is normally needed but due to Errors (see Errata Sheet and/or Appnote AN2824, Rev. 4, Chapter 1.2.1, Page 5)
	//	the Rx Routine needs to be able to omit this
	if(clearADDR == true)
	{
		*MCU::I2C_2::SR2;
	}
	
	
	return(OK);
}


inline void I2C_2::stop()
{
	bit::set(*MCU::I2C_2::CR1, 9);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback I2C_2::init(e_mode mode)
{
	//	Enable I2C Bus Clock
	RCC& rcc = STM32F107RCT6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::I2C_2, true);
	
	
	//	Disable I2C
	bit::clear(*MCU::I2C_2::CR1, 0);
	
	
	//	Reset I2C
	rcc.module_reset(RCC::e_module::I2C_2);
	
	
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
	uint32 temp = *MCU::I2C_2::CCR & 0xFFFFF000;
	*MCU::I2C_2::CCR = temp | CCR;
	
	temp = *MCU::I2C_2::TRISE & 0xFFFFFFC0;
	*MCU::I2C_2::TRISE = temp | TRISE;
	
	
	//	I2C Input Clock
	temp = *MCU::I2C_2::CR2 & 0xFFFFFFC0;
	*MCU::I2C_2::CR2 = temp | (clock_apb1 / 1000000);
	
	
	//	Enable Interrupt on Tx Buffer empty and Rx Buffer empty
	bit::set(*MCU::I2C_2::CR2, 10);
	bit::set(*MCU::I2C_2::CR2, 9);
	
	
	//	Enable Interrupt on Errors
	bit::set(*MCU::I2C_2::CR2, 8);
	
	
	//	Interrupts (Event Interrupt will be enabled every Time we need it and disabled in the ISR)
	NVIC& nvic = CMOS::get().get_nvic();
	nvic.setPriority(Interrupt::I2C_2_EVENT, 10);
	nvic.setPriority(Interrupt::I2C_2_ERROR, 10);
	nvic.enable(Interrupt::I2C_2_ERROR);
	
	
	//	Enable I2C
	bit::set(*MCU::I2C_2::CR1, 0);
	
	
	return(OK);
}







CODE_RAM feedback I2C_2::tx(uint8 slaveAddress, uint8 data, uint32 timeout_ms)
{
	//	Check for Constraints on 7-Bit Slave Address
	if(slaveAddress > 0x7F)
	{
		return(FAIL);
	}
	
	
	//	Clear Error Buffer
	m_errors.erase();
	
	
	//	Subscribe to Events
	CMOS& cmos = CMOS::get();
	cmos.event_subscribe(m_eventID_error);
	cmos.event_subscribe(m_eventID_TxE);
	
	
	//	Start Condition and Slave Address
	if(start(slaveAddress << 1, timeout_ms) != OK)
	{
		//	Unsubscribe from Events
		cmos.event_unsubscribe(m_eventID_error);
		cmos.event_unsubscribe(m_eventID_TxE);
		
		
		return(FAIL);
	}
	
	
	//	Enable I2C Interrupt
	NVIC& nvic = cmos.get_nvic();
	nvic.enable(Interrupt::I2C_2_EVENT);
	
	
	//	Sleep
	while(1)
	{
		const uint16 eventID = cmos.sleep_untilEvent();
		
		
		if(eventID == m_eventID_error)
		{
			//	Unsubscribe from Events
			cmos.event_unsubscribe(m_eventID_error);
			cmos.event_unsubscribe(m_eventID_TxE);
			
			
			//	Check for NACK
			if(m_errors.contains(e_error::ACKNOWLEDGE_FAILURE) == true)
			{
				//	Send STOP Condition on NACK to release the Bus
				stop();
			}
			
			
			return(FAIL);
		}
		if(eventID == m_eventID_TxE)
		{
			//	Listen to TxE Event
			cmos.event_listen(m_eventID_TxE);
			
			
			//	Write Data to Tx Buffer
			*MCU::I2C_2::DR = data;
			
			
			//	Enable Event Interrupt again
			nvic.enable(Interrupt::I2C_2_EVENT);
			
			
			break;
		}
		
		
		//	Enable Event Interrupt again
		nvic.enable(Interrupt::I2C_2_EVENT);
	}
	
	
	//	Wait for last Data Byte to be shifted out
	uint64 timestamp = cmos.get_ticks();
	while(bit::isCleared(*MCU::I2C_2::SR1, 7))
	{
		if(m_errors.get_size() > 0)
		{
			return(FAIL);
		}
		
		
		constexpr uint32 timeoutWorkaroundInMilliseconds = 1;
		if(cmos.get_ticks() - timestamp >= timeoutWorkaroundInMilliseconds * (cmos.c_clock_systick / 1000))
		{
			break;
		}
	}
	
	
	//	Send STOP Condition
	stop();
	
	
	//	Unsubscribe from Events
	cmos.event_unsubscribe(m_eventID_error);
	cmos.event_unsubscribe(m_eventID_TxE);
	
	
	return(OK);
}


CODE_RAM feedback I2C_2::tx(uint8 slaveAddress, const Array<uint8>& data, uint32 timeout_ms)
{
	//	Check for Constraints on 7-Bit Slave Address
	if(slaveAddress > 0x7F)
	{
		return(FAIL);
	}
	
	
	//	Clear Error Buffer
	m_errors.erase();
	
	
	//	Subscribe to Events
	CMOS& cmos = CMOS::get();
	cmos.event_subscribe(m_eventID_error);
	cmos.event_subscribe(m_eventID_TxE);
	
	
	//	Start Condition and Slave Address
	if(start(slaveAddress << 1, timeout_ms) != OK)
	{
		//	Unsubscribe from Events
		cmos.event_unsubscribe(m_eventID_error);
		cmos.event_unsubscribe(m_eventID_TxE);
		
		
		return(FAIL);
	}
	
	
	NVIC& nvic = cmos.get_nvic();
	for(auto& i: data)
	{
		//	Enable I2C Interrupt
		nvic.enable(Interrupt::I2C_2_EVENT);
		
		
		//	Sleep
		while(1)
		{
			const uint16 eventID = cmos.sleep_untilEvent();
			
			
			if(eventID == m_eventID_error)
			{
				//	Unsubscribe from Events
				cmos.event_unsubscribe(m_eventID_error);
				cmos.event_unsubscribe(m_eventID_TxE);
				
				
				//	Check for NACK
				if(m_errors.contains(e_error::ACKNOWLEDGE_FAILURE) == true)
				{
					//	Send STOP Condition on NACK to release the Bus
					stop();
				}
				
				
				return(FAIL);
			}
			if(eventID == m_eventID_TxE)
			{
				//	Listen to TxE Event
				cmos.event_listen(m_eventID_TxE);
				
				
				//	Write Data to Tx Buffer
				*MCU::I2C_2::DR = i;
				
				
				//	Enable Event Interrupt again
				nvic.enable(Interrupt::I2C_2_EVENT);
				
				
				break;
			}
			
			
			//	Enable Event Interrupt again
			nvic.enable(Interrupt::I2C_2_EVENT);
		}
	}
	
	
	//	Wait for last Data Byte to be shifted out
	uint64 timestamp = cmos.get_ticks();
	while(bit::isCleared(*MCU::I2C_2::SR1, 7))
	{
		if(m_errors.get_size() > 0)
		{
			return(FAIL);
		}
		
		
		constexpr uint32 timeoutWorkaroundInMilliseconds = 1;
		if(cmos.get_ticks() - timestamp >= timeoutWorkaroundInMilliseconds * (cmos.c_clock_systick / 1000))
		{
			break;
		}
	}
	
	
	//	Send STOP Condition
	stop();
	
	
	//	Unsubscribe from Events
	cmos.event_unsubscribe(m_eventID_error);
	cmos.event_unsubscribe(m_eventID_TxE);
	
	
	return(OK);
}


CODE_RAM Array<uint8> I2C_2::rx(uint8 slaveAddress, uint32 numberOfByte, uint32 timeout_ms)
{
	//	8 Bit Slave Address
	const uint8 slaveAddress_8bit = (slaveAddress << 1) | 0x01;
	
	
	//	POS = 0
	bit::clear(*MCU::I2C_2::CR1, 11);
	
	
	//	ACK each received Byte
	bit::set(*MCU::I2C_2::CR1, 10);
	
	
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
			while(bit::isCleared(*MCU::I2C_2::SR1, 6) == true)
			{
				//	Check for Timeout
				const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
				if(timeWaited_ms > timeout_ms)
				{
					return(Array<uint8>());
				}
			}
			data[i] = *MCU::I2C_2::DR;
		}
		
		
		//	Wait for 2 more Byte to be received
		const uint64 timestampStart = ticks;
		while(bit::isCleared(*MCU::I2C_2::SR1, 2) == true)
		{
			//	Check for Timeout (doubled because of 2 Byte to be received)
			const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
			if(timeWaited_ms > 2 * timeout_ms)
			{
				return(Array<uint8>());
			}
		}
		
		
		//	Prepare to send a NACK
		bit::clear(*MCU::I2C_2::CR1, 10);
		
		
		//	Read next Byte
		data[numberOfByte - 3] = *MCU::I2C_2::DR;
		
		
		//	Disable Interrupts
		nvic.disable_allExceptions();
		
		
		//	Prepare to send a STOP Condition
		stop();
		
		
		//	Read next Byte
		data[numberOfByte - 2] = *MCU::I2C_2::DR;
		
		
		//	Enable Interrupts
		nvic.enable_allExceptions();
		
		
		//	Read last Byte
		data[numberOfByte - 1] = *MCU::I2C_2::DR;
	}
	if(numberOfByte == 2)
	{
		//	Send START Condition
		start(slaveAddress_8bit, timeout_ms, false);
		
		
		//	Send NACK on the next (not the current) Byte received
		bit::set(*MCU::I2C_2::CR1, 11);
		
		
		//	Disable Interrupts
		nvic.disable_allExceptions();
		
		
		//	Clear ADDR Bit by reading the SR2 Register
		*MCU::I2C_2::SR2;
		
		
		//	Prepare to send a NACK
		bit::clear(*MCU::I2C_2::CR1, 10);
		
		
		//	Enable Interrupts
		nvic.enable_allExceptions();
		
		
		//	Wait until 2 Byte are received
		const uint64 timestampStart = ticks;
		while(bit::isCleared(*MCU::I2C_2::SR1, 2) == true)
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
		data[0] = *MCU::I2C_2::DR;
		
		
		//	Enable Interrupts
		nvic.enable_allExceptions();
		
		
		//	Read last Byte
		data[1] = *MCU::I2C_2::DR;
	}
	if(numberOfByte == 1)
	{
		//	Send START Condition
		start(slaveAddress_8bit, timeout_ms, false);
		
		
		//	Prepare to send a NACK
		bit::clear(*MCU::I2C_2::CR1, 10);
		
		
		//	Disable Interrupts
		nvic.disable_allExceptions();
		
		
		//	Clear ADDR Bit by reading the SR2 Register
		*MCU::I2C_2::SR2;
		
		
		//	Prepare to send a STOP Condition
		stop();
		
		
		//	Enable Interrupts
		nvic.enable_allExceptions();
		
		
		//	Wait until 1 Byte is received
		const uint64 timestampStart = ticks;
		while(bit::isCleared(*MCU::I2C_2::SR1, 6) == true)
		{
			//	Check for Timeout
			const uint32 timeWaited_ms = (ticks - timestampStart) / (CMOS::c_clock_systick / 1000);
			if(timeWaited_ms > timeout_ms)
			{
				return(Array<uint8>());
			}
		}
		
		
		//	Read Byte
		data[0] = *MCU::I2C_2::DR;
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









void ISR_I2C_2_EVENT()
{
	I2C_2& i2c = STM32F107RCT6::get().get_i2c_2();
	
	
	//	Read Status Registers
	const uint32 SR1 = *MCU::I2C_2::SR1;
	
	
	//	Deactivate I2C Interrupt to avoid endless looping, but only if a valid Status Flag has been set
	bool validFlag = false;
	CMOS& cmos = CMOS::get();
	
	
	//	SB (Start Bit sent)
	if(bit::isSet(SR1, 0) == true)
	{
		validFlag = true;
	}
	
	
	//	ADDR (Address sent)
	if(bit::isSet(SR1, 1) == true)
	{
		validFlag = true;
	}
	
	
	//	BTF (Byte Transfer finished)
	if(bit::isSet(SR1, 2) == true)
	{
		validFlag = true;
	}
	
	
	//	ADDR10 (10 Bit Address sent)
	if(bit::isSet(SR1, 3) == true)
	{
		validFlag = true;
	}
	
	
	//	STOPF (Stop received)
	if(bit::isSet(SR1, 4) == true)
	{
		validFlag = true;
	}
	
	
	//	RxNE (Rx not empty)
	if(bit::isSet(SR1, 6) == true)
	{
		validFlag = true;
		
		
		//	Emit RxNE Event
		cmos.event_emit(i2c.m_eventID_RxNE);
	}
	
	
	//	TxE (Tx empty)
	if(bit::isSet(SR1, 7) == true)
	{
		validFlag = true;
		
		
		//	Emit TxE Event
		cmos.event_emit(i2c.m_eventID_TxE);
	}
	
	
	if(validFlag == true)
	{
		NVIC& nvic = cmos.get_nvic();
		nvic.disable(Interrupt::I2C_2_EVENT);
	}
}


void ISR_I2C_2_ERROR()
{
	I2C_2& i2c = STM32F107RCT6::get().get_i2c_2();
	
	
	//	Read Status Register
	const uint32 SR1 = *MCU::I2C_2::SR1;
	
	
	//	AF (Acknowledge Failure)
	if(bit::isSet(SR1, 10) == true)
	{
		//	Clear AF Bit
		bit::clear(*MCU::I2C_2::SR1, 10);
		
		
		//	Log Error
		i2c.m_errors += I2C_2::e_error::ACKNOWLEDGE_FAILURE;
		
		
		//	Emit Error Event
		CMOS::get().event_emit(i2c.m_eventID_error);
	}
	
	
	//	ARLO (Arbitration lost)
	if(bit::isSet(SR1, 9) == true)
	{
		//	Clear ARLO Bit
		bit::clear(*MCU::I2C_2::SR1, 9);
		
		
		//	Log Error
		i2c.m_errors += I2C_2::e_error::ARBITRATION_LOST;
		
		
		//	Emit Error Event
		CMOS::get().event_emit(i2c.m_eventID_error);
	}
	
	
	//	BERR (Bus Error)
	if(bit::isSet(SR1, 8) == true)
	{
		//	Clear BERR Bit
		bit::clear(*MCU::I2C_2::SR1, 8);
		
		
		//	Log Error
		i2c.m_errors += I2C_2::e_error::BUS_ERROR;
		
		
		//	Emit Error Event
		CMOS::get().event_emit(i2c.m_eventID_error);
	}
}