#include "../Inc/stm32g474mct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback I2C_1::begin(uint8 slaveAddress, bool write, uint8 numberOfBytes, bool autoEnd, uint32 timeout_ms)
{
	//	Only the Thread that has locked the Bus with cmos.mutex_lock(&i2c) may use it
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false || slaveAddress > 0x7F)
	{
		return(FAIL);
	}
	const uint64 timestampStart = cmos.get_timestamp();
	
	
	//	The previous Transfer has to be over: ended with a Stop Condition (BUSY = 0) or waiting for a Repeated Start (TC = 1)
	while(bit::isSet(*MCU::I2C_1::ISR, 15) == true && bit::isCleared(*MCU::I2C_1::ISR, 6) == true)
	{
		if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > timeout_ms)
		{
			//	The Bus hangs, e.g. not all Bytes of the last Transfer were read: the Software Reset releases SCL and SDA
			reset();
			return(FAIL);
		}
	}
	
	
	//	Clear STOPF and NACKF of the previous Transfer, a Transfer without Data is evaluated with them
	*MCU::I2C_1::ICR = (1 << 5) | (1 << 4);
	
	
	//	START with Address, Direction (RD_WRN) and Number of Bytes; AUTOEND sends the Stop Condition after the last Byte
	const uint32 autoEndMask = autoEnd == true ? (1 << 25) : 0;
	const uint32 readMask = write == true ? 0 : (1 << 10);
	*MCU::I2C_1::CR2 = autoEndMask | (1 << 13) | (((uint32) numberOfBytes) << 16) | readMask | (((uint32) slaveAddress) << 1);
	
	
	//	Without Data only the Address is sent, TXIS and RXNE are never set: with AUTOEND the Transfer ends with STOPF, else with TC
	//	After a NACK the Hardware sends the Stop Condition itself, NACKF then tells that the Slave has not answered (e.g. ACK Polling of an EEPROM)
	if(numberOfBytes == 0)
	{
		while(bit::isCleared(*MCU::I2C_1::ISR, 5) == true && (autoEnd == true || bit::isCleared(*MCU::I2C_1::ISR, 6) == true))
		{
			//	Check for Timeout
			if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > timeout_ms)
			{
				return(FAIL);
			}
		}
		const bool acknowledged = bit::isCleared(*MCU::I2C_1::ISR, 4);
		
		
		//	Clear STOPF and NACKF
		*MCU::I2C_1::ICR = (1 << 5) | (1 << 4);
		if(acknowledged == false)
		{
			return(FAIL);
		}
		return(OK);
	}
	
	
	//	Wait for the first Byte: TX Buffer free (TXIS) when writing, RX Buffer not empty (RXNE) when reading
	const uint32 bitReady = write == true ? 1 : 2;
	while(bit::isCleared(*MCU::I2C_1::ISR, bitReady))
	{
		//	Check for Timeout
		if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > timeout_ms)
		{
			return(FAIL);
		}
		
		
		//	Check if NACK received
		if(bit::isSet(*MCU::I2C_1::ISR, 4))
		{
			//	Clear NACK Flag
			bit::set(*MCU::I2C_1::ICR, 4);
			return(FAIL);
		}
	}
	return(OK);
}


void I2C_1::reset()
{
	//	Software Reset: PE = 0 resets the State Machine and the Flags, the Configuration stays (PE must stay 0 for 3 APB Cycles: write, read back, write)
	bit::clear(*MCU::I2C_1::CR1, 0);
	while(bit::isSet(*MCU::I2C_1::CR1, 0) == true)
	{
		
	}
	bit::set(*MCU::I2C_1::CR1, 0);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback I2C_1::init(e_mode mode, RCC::e_clockSource_i2c_1 clockSource, bool analogFilterEnable, uint8 digitalFilterLength)
{
	//	Boundary Check
	if(digitalFilterLength > 15 || (uint8) mode > 2)
	{
		return(FAIL);
	}
	
	
	//	Select I2C Input Clock
	RCC& rcc = STM32G474MCT6::get().get_rcc();
	rcc.set_clockSource(clockSource);
	uint32 clock_in = 0;
	switch(clockSource)
	{
		case RCC::e_clockSource_i2c_1::APB1:
		{
			clock_in = rcc.get_clock_apb1();
		}
		break;
		
		case RCC::e_clockSource_i2c_1::SYSTEM:
		{
			clock_in = rcc.get_clock_system();
		}
		break;
		
		case RCC::e_clockSource_i2c_1::HSI16:
		{
			clock_in = rcc.get_clock_hsi16();
		}
		break;
		
		default:
		{
			return(FAIL);
		}
		break;
	}
	
	
	//	RM0490, Rev.3, Chapter 23.4.5, Page 598ff
	//	All Timing Values are in Picoseconds
	uint32 t_af_min = 0;
	uint32 t_af_max = 0;
	if(analogFilterEnable == true)
	{
		t_af_min = 50000;
		t_af_max = 260000;
	}
	
	
	//	Values for Standard Mode
	//	All Timing Values are in Picoseconds
	uint32 t_hd_dat_min	= 0;
	uint32 t_hd_dat_max	= 0;
	//uint32 t_vd_dat_max	= 0;
	uint32 t_su_dat_min	= 0;
	uint32 t_r_max			= 0;
	uint32 t_f_max			= 0;
	uint32 t_low_min		= 0;
	uint32 t_high_min		= 0;
	{
		constexpr uint32 table_t_hd_dat_min[]	= {0,				      0,       0};
		constexpr uint32 table_t_hd_dat_max[]	= {3450000,	 900000,  450000};
		//constexpr uint32 table_t_vd_dat_max[]	= {3450000,  900000,  450000};
		constexpr uint32 table_t_su_dat_min[]	= { 250000,  100000,   50000};
		constexpr uint32 table_t_r_max[]			= {1000000,  300000,  120000};
		constexpr uint32 table_t_f_max[]			= { 300000,  300000,  120000};
		constexpr uint32 table_t_low_min[]		= {4700000, 1300000,  500000};
		constexpr uint32 table_t_high_min[]		= {4000000,  600000,  260000};
		
		const uint32 index = (uint32) mode;
		t_hd_dat_min	= table_t_hd_dat_min[index];
		t_hd_dat_max	= table_t_hd_dat_max[index];
		//t_vd_dat_max	= table_t_vd_dat_max[index];
		t_su_dat_min	= table_t_su_dat_min[index];
		t_r_max				= table_t_r_max[index];
		t_f_max				= table_t_f_max[index];
		t_low_min 		= table_t_low_min[index];
		t_high_min 		= table_t_high_min[index];
	}
	
	
	//	Compute best Parameters
	//	All Timing Values are in Picoseconds
	const uint32 DNF = digitalFilterLength;
	const uint32 t_i2cclk = 1000000000000 / clock_in;
	for(uint32 PRESC = 0; PRESC < 16; PRESC++)
	{
		//	t_PRESC
		const uint32 t_PRESC = (PRESC + 1) * t_i2cclk;
		
		
		//	SDADEL Constraints: the Minimum is max(0, …) rounded up, the Maximum at least 0 (shortest possible Data Hold Time)
		//	Computed with Sign, because the Differences become negative for slow I2C Clocks or fast Modes
		const int64 SDADEL_min_ps = (int64) t_f_max + t_hd_dat_min - t_af_min - (int64) (DNF + 3) * t_i2cclk;
		const int64 SDADEL_max_ps = (int64) t_hd_dat_max - t_af_max - (int64) (DNF + 4) * t_i2cclk;
		const uint32 SDADEL_min = SDADEL_min_ps <= 0 ? 0 : (uint32) ((SDADEL_min_ps + t_PRESC - 1) / t_PRESC);
		const uint32 SDADEL_max = SDADEL_max_ps <= 0 ? 0 : (uint32) (SDADEL_max_ps / t_PRESC);
		
		
		//	SCLDEL Constraints: (SCLDEL + 1) x t_PRESC covers t_r + t_SU;DAT (rounded up, never below 0)
		const uint32 SCLDEL_ticks = (t_r_max + t_su_dat_min + t_PRESC - 1) / t_PRESC;
		const uint32 SCLDEL_min = SCLDEL_ticks > 0 ? SCLDEL_ticks - 1 : 0;
		
		
		for(uint32 SDADEL = 0; SDADEL < 16; SDADEL++)
		{
			if(SDADEL >= SDADEL_min && SDADEL <= SDADEL_max)
			{
				for(uint32 SCLDEL = 0; SCLDEL < 16; SCLDEL++)
				{
					if(SCLDEL >= SCLDEL_min)
					{
						for(uint32 SCLH = 0; SCLH < 256; SCLH++)
						{
							if(t_high_min <= t_af_min + (DNF + 3) * t_i2cclk + (SCLH + 1) * t_PRESC)
							{
								for(uint32 SCLL = 0; SCLL < 256; SCLL++)
								{
									if(t_low_min <= t_af_min + (DNF + 3) * t_i2cclk + (SCLL + 1) * t_PRESC)
									{
										if(SCLL == SCLH)
										{
											uint32 timingRegister = (PRESC << 28) | (SCLDEL << 20) | (SDADEL << 16) | (SCLH << 8) | SCLL;
											//	TIMINGR, ANFOFF and DNF can only be written while the Peripheral is disabled (PE = 0), e.g. for a second init
											bit::clear(*MCU::I2C_1::CR1, 0);
											*MCU::I2C_1::TIMINGR = timingRegister;
											
											
											//	Analog Filters
											if(analogFilterEnable == false)
											{
												bit::set(*MCU::I2C_1::CR1, 12);
											}
											else
											{
												bit::clear(*MCU::I2C_1::CR1, 12);
											}
											
											
											//	Digital Filters
											const uint32 temp = *MCU::I2C_1::CR1 & 0xFFFFF0FF;
											*MCU::I2C_1::CR1 = temp | (digitalFilterLength << 8);
											
											
											//	Enable I2C
											bit::set(*MCU::I2C_1::CR1, 0);
											
											
											return(OK);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return(FAIL);
}







feedback I2C_1::start(uint8 slaveAddress, bool write, uint8 numberOfBytes, uint32 timeout_ms)
{
	//	The Hardware sends the Stop Condition after the last Byte (AUTOEND)
	return(begin(slaveAddress, write, numberOfBytes, true, timeout_ms));
}


feedback I2C_1::start_withoutStop(uint8 slaveAddress, bool write, uint8 numberOfBytes, uint32 timeout_ms)
{
	//	After the last Byte the Hardware holds SCL low (TC): the next start() sends a Repeated Start, stop() ends the Transfer
	return(begin(slaveAddress, write, numberOfBytes, false, timeout_ms));
}


void I2C_1::stop()
{
	if(CMOS::get().mutex_isOwnedByRunningThread(this) == false)
	{
		return;
	}
	
	
	//	Stop Condition after the current Byte, only while the Bus is in use (BUSY)
	if(bit::isSet(*MCU::I2C_1::ISR, 15) == true)
	{
		bit::set(*MCU::I2C_1::CR2, 14);
	}
}


feedback I2C_1::tx(uint8 data, uint32 timeout_ms)
{
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false || (*MCU::I2C_1::CR2 & 0x00FF0000) == 0)
	{
		return(FAIL);
	}
	
	
	//	Timeout
	const uint64 timestampStart = cmos.get_timestamp();
	
	
	//	Wait for TX Buffer to be free
	while(bit::isCleared(*MCU::I2C_1::ISR, 1))
	{
		//	Check for Timeout
		const int64 timeWaited_ms = cmos.getMilliSecondsSinceTimestamp(timestampStart);
		if(timeWaited_ms > timeout_ms)
		{
			return(FAIL);
		}
		
		
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


uint8 I2C_1::rx(uint32 timeout_ms)
{
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(0);
	}
	
	
	//	Timeout
	const uint64 timestampStart = cmos.get_timestamp();
	
	
	while(bit::isCleared(*MCU::I2C_1::ISR, 2))
	{
		//	Check for Timeout
		const int64 timeWaited_ms = cmos.getMilliSecondsSinceTimestamp(timestampStart);
		if(timeWaited_ms > timeout_ms)
		{
			return(0);
		}
	}
	
	uint8 data = *MCU::I2C_1::RXDR & 0x000000FF;
	
	return(data);
}
