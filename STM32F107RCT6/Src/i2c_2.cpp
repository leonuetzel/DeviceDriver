#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback I2C_2::begin(uint8 slaveAddress, bool write, uint8 numberOfBytes, bool autoEnd, uint32 timeout_ms)
{
	//	Only the Thread that has locked the Bus with cmos.mutex_lock(&i2c) may use it
	//	A Reception always ends with NACK and Stop Condition: the I2C of the F1 has no Transfer Counter that could hold the Bus after it
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false || slaveAddress > 0x7F || (write == false && autoEnd == false))
	{
		return(FAIL);
	}
	const uint64 timestampStart = cmos.get_timestamp();
	
	
	//	The Stop Condition of the previous Transfer has to be sent (STOP is cleared by the Hardware then)
	//	Without own Transfer the Bus has to be free (BUSY): else another Master uses it, or it hangs and needs a Reset of the Peripheral
	while(bit::isSet(*MCU::I2C_2::CR1, 9) == true || (m_active == false && bit::isSet(*MCU::I2C_2::SR2, 1) == true))
	{
		if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > timeout_ms)
		{
			init(m_mode);
			return(FAIL);
		}
	}
	m_remaining = 0;
	m_pendingValid = false;
	
	
	//	Acknowledge every received Byte; POS only for the Reception of 2 Bytes
	bit::clear(*MCU::I2C_2::CR1, 11);
	bit::set(*MCU::I2C_2::CR1, 10);
	
	
	//	Start Condition, after a Transfer without Stop it is a Repeated Start
	//	If it fails, a running Transfer without Stop is ended with a Stop Condition (end() in wait()), else no Stop is requested
	bit::set(*MCU::I2C_2::CR1, 8);
	if(wait(0, timestampStart, timeout_ms) != OK)
	{
		//	Withdraw the Start Request, e.g. while a Slave holds SDA low
		bit::clear(*MCU::I2C_2::CR1, 8);
		return(FAIL);
	}
	m_active = true;
	
	
	//	Slave Address with Direction: reading SR1 and writing DR clears SB; ADDR is only set after an ACK of the Slave
	*MCU::I2C_2::DR = (uint8) ((slaveAddress << 1) | (write == true ? 0 : 1));
	if(wait(1, timestampStart, timeout_ms) != OK)
	{
		return(FAIL);
	}
	
	
	//	Without Data only the Address is sent (e.g. ACK Polling of an EEPROM); ADDR is cleared by reading SR1 and SR2
	if(numberOfBytes == 0)
	{
		(void) *MCU::I2C_2::SR1;
		(void) *MCU::I2C_2::SR2;
		if(autoEnd == true)
		{
			end();
		}
		return(OK);
	}
	m_remaining = numberOfBytes;
	m_read = (write == false);
	m_autoEnd = autoEnd;
	if(write == true)
	{
		(void) *MCU::I2C_2::SR1;
		(void) *MCU::I2C_2::SR2;
		return(OK);
	}
	
	
	//	Reception (RM0008, I2C master receiver, Method 2): the ACK Bit has to be set before the Byte, whose Acknowledge it controls, is received
	if(numberOfBytes == 1)
	{
		//	1 Byte: NACK, clear ADDR and request the Stop Condition without Interruption (ES022 2.8.1, EV6_3)
		bit::clear(*MCU::I2C_2::CR1, 10);
		NVIC& nvic = cmos.get_nvic();
		nvic.disable_allExceptions();
		(void) *MCU::I2C_2::SR1;
		(void) *MCU::I2C_2::SR2;
		bit::set(*MCU::I2C_2::CR1, 9);
		nvic.enable_allExceptions();
		m_active = false;
	}
	else if(numberOfBytes == 2)
	{
		//	2 Bytes: with POS the cleared ACK Bit applies to the second Byte (EV6_1); SCL is held low until ADDR is cleared
		bit::clear(*MCU::I2C_2::CR1, 10);
		bit::set(*MCU::I2C_2::CR1, 11);
		(void) *MCU::I2C_2::SR1;
		(void) *MCU::I2C_2::SR2;
	}
	else
	{
		(void) *MCU::I2C_2::SR1;
		(void) *MCU::I2C_2::SR2;
	}
	return(OK);
}


feedback I2C_2::wait(uint32 bitNumber, uint64 timestampStart, uint32 timeout_ms)
{
	CMOS& cmos = CMOS::get();
	while(bit::isCleared(*MCU::I2C_2::SR1, bitNumber) == true)
	{
		//	NACK (AF), Arbitration lost (ARLO) or Bus Error (BERR) end the Transfer; the Flags are cleared by writing 0
		constexpr uint32 errors = (1 << 10) | (1 << 9) | (1 << 8);
		if((*MCU::I2C_2::SR1 & errors) != 0)
		{
			*MCU::I2C_2::SR1 = ~errors;
			end();
			return(FAIL);
		}
		if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > timeout_ms)
		{
			end();
			return(FAIL);
		}
	}
	return(OK);
}


void I2C_2::end()
{
	//	Stop Condition after the current Byte: ends a Transfer, also an incomplete one, and frees the Bus
	if(m_active == true)
	{
		bit::set(*MCU::I2C_2::CR1, 9);
	}
	m_active = false;
	m_remaining = 0;
	m_pendingValid = false;
	bit::clear(*MCU::I2C_2::CR1, 11);
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
	//	ES022 2.8.5: between 88 and 100 kHz the Setup Time of a Repeated Start can be too short, so T_high and T_low are 5.7µs each (at most 88 kHz)
	
	//	CCR_SM = 5.7µs x clock_apb1 [MHz], rounded up
	//	TRISE_SM	= t_r(SCL)_SM [µs] / T_PCLK1 [µs] + 1 = t_r(SCL)_SM [µs] x clock_apb1 [MHz] + 1
	//	TRISE_SM	= 1µs x clock_apb1 [MHz] + 1
	
	
	//	Calculations for Fast Mode 400 kHz (F/S = 1, DUTY = 0: T_low = 2 x T_high)
	//	T_high_FM	= 300ns + 600ns		= 900ns
	//	T_low_FM	= 300ns + 1300ns	= 1600ns
	
	//	CCR_FM	= T_high_FM [µs] / T_PCLK1 [µs] = 0.9µs x clock_apb1 [MHz], rounded up
	//	T_low is then 2 x 0.9µs = 1.8µs, more than T_low_FM, so the SCL Frequency is about 370 kHz
	//	TRISE_FM	= t_r(SCL)_FM [µs] / T_PCLK1 [µs] + 1 = t_r(SCL)_FM [µs] x clock_apb1 [MHz] + 1
	//	TRISE_FM	= 0.3µs x clock_apb1 [MHz] + 1
	
	
	//	Calculation: t = 1 / f -> a Multiplication with t is equal to a Division by f
	//	This Way, we dont need any floating Point here
	const uint32 clock_apb1 = rcc.get_clock_apb1();
	uint32 CCR = 0;
	uint32 TRISE = 0;
	uint32 fastMode = 0;
	switch(mode)
	{
		case e_mode::STANDARD_100KHZ:
		{
			//	PCLK1 must be at least 2 MHz, CCR at least 4; rounded up, so that the Times are not shorter than required
			if(clock_apb1 < 2000000)
			{
				return(FAIL);
			}
			CCR = (57 * (uint64) clock_apb1 + 9999999) / 10000000;
			TRISE = clock_apb1 / 1000000 + 1;
			if(CCR < 0x04)
			{
				return(FAIL);
			}
		}
		break;
		
		case e_mode::FAST_400KHZ:
		{
			//	PCLK1 must be at least 4 MHz
			if(clock_apb1 < 4000000)
			{
				return(FAIL);
			}
			CCR = (9 * (uint64) clock_apb1 + 9999999) / 10000000;
			TRISE = clock_apb1 / 3333333 + 1;
			fastMode = 1;
		}
		break;
		
		default:
		{
			//	Fast Mode Plus and faster: not supported by the I2C of the F1
			return(FAIL);
		}
	}
	
	
	//	CCR has 12 Bit
	if(CCR > 0x0FFF)
	{
		return(FAIL);
	}
	
	
	//	Write Timing Values: F/S (Bit 15) selects the Fast Mode, DUTY (Bit 14) stays 0
	uint32 temp = *MCU::I2C_2::CCR & 0xFFFF3000;
	*MCU::I2C_2::CCR = temp | (fastMode << 15) | CCR;
	
	temp = *MCU::I2C_2::TRISE & 0xFFFFFFC0;
	*MCU::I2C_2::TRISE = temp | TRISE;
	
	
	//	I2C Input Clock
	temp = *MCU::I2C_2::CR2 & 0xFFFFFFC0;
	*MCU::I2C_2::CR2 = temp | (clock_apb1 / 1000000);
	
	
	//	Enable I2C
	bit::set(*MCU::I2C_2::CR1, 0);
	
	
	//	No Transfer is running
	m_mode = mode;
	m_active = false;
	m_remaining = 0;
	m_pendingValid = false;
	return(OK);
}







feedback I2C_2::start(uint8 slaveAddress, bool write, uint8 numberOfBytes, uint32 timeout_ms)
{
	//	The Stop Condition follows the last Byte
	return(begin(slaveAddress, write, numberOfBytes, true, timeout_ms));
}


feedback I2C_2::start_withoutStop(uint8 slaveAddress, bool write, uint8 numberOfBytes, uint32 timeout_ms)
{
	//	Only for Writing: after the last Byte SCL stays low, the next start() sends a Repeated Start, stop() ends the Transfer
	return(begin(slaveAddress, write, numberOfBytes, false, timeout_ms));
}


void I2C_2::stop()
{
	if(CMOS::get().mutex_isOwnedByRunningThread(this) == false)
	{
		return;
	}
	end();
}


feedback I2C_2::tx(uint8 data, uint32 timeout_ms)
{
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false || m_active == false || m_read == true || m_remaining == 0)
	{
		return(FAIL);
	}
	const uint64 timestampStart = cmos.get_timestamp();
	
	
	//	Wait for the Data Register to be empty (TxE), then write
	if(wait(7, timestampStart, timeout_ms) != OK)
	{
		return(FAIL);
	}
	*MCU::I2C_2::DR = data;
	m_remaining--;
	
	
	//	Last Byte: wait until it has been sent and acknowledged (BTF), then the Stop Condition - without Stop the Bus stays occupied
	if(m_remaining == 0)
	{
		if(wait(2, timestampStart, timeout_ms) != OK)
		{
			return(FAIL);
		}
		if(m_autoEnd == true)
		{
			end();
		}
	}
	return(OK);
}


uint8 I2C_2::rx(uint32 timeout_ms)
{
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false || m_read == false || m_remaining == 0)
	{
		return(0);
	}
	
	
	//	A Byte that the End of the Reception has read already
	if(m_pendingValid == true)
	{
		m_pendingValid = false;
		m_remaining--;
		return(m_pending);
	}
	
	
	const uint64 timestampStart = cmos.get_timestamp();
	NVIC& nvic = cmos.get_nvic();
	uint8 data = 0;
	if(m_remaining == 3)
	{
		//	Byte N-2 in DR, N-1 in the Shift Register (BTF): NACK for Byte N, then read N-2, Stop Condition and read N-1 without Interruption (ES022 2.8.2)
		if(wait(2, timestampStart, timeout_ms) != OK)
		{
			return(0);
		}
		bit::clear(*MCU::I2C_2::CR1, 10);
		nvic.disable_allExceptions();
		data = (uint8) *MCU::I2C_2::DR;
		bit::set(*MCU::I2C_2::CR1, 9);
		m_pending = (uint8) *MCU::I2C_2::DR;
		nvic.enable_allExceptions();
		m_pendingValid = true;
		m_active = false;
	}
	else if(m_remaining == 2)
	{
		//	Reception of 2 Bytes: Byte 1 in DR, Byte 2 in the Shift Register (BTF), then Stop Condition and both read without Interruption (ES022 2.8.2)
		if(wait(2, timestampStart, timeout_ms) != OK)
		{
			return(0);
		}
		nvic.disable_allExceptions();
		bit::set(*MCU::I2C_2::CR1, 9);
		data = (uint8) *MCU::I2C_2::DR;
		m_pending = (uint8) *MCU::I2C_2::DR;
		nvic.enable_allExceptions();
		m_pendingValid = true;
		m_active = false;
	}
	else
	{
		//	Bytes up to N-3, and the last Byte
		if(wait(6, timestampStart, timeout_ms) != OK)
		{
			return(0);
		}
		data = (uint8) *MCU::I2C_2::DR;
	}
	m_remaining--;
	if(m_remaining == 0)
	{
		bit::clear(*MCU::I2C_2::CR1, 11);
	}
	return(data);
}
