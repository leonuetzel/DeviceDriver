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

feedback I2C_2::init(e_mode mode, RCC::e_clockSource_i2c_2 clockSource, bool analogFilterEnable, uint8 digitalFilterLength)
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
		case RCC::e_clockSource_i2c_2::APB1:
		{
			clock_in = rcc.get_clock_apb1();
		}
		break;
		
		case RCC::e_clockSource_i2c_2::SYSTEM:
		{
			clock_in = rcc.get_clock_system();
		}
		break;
		
		case RCC::e_clockSource_i2c_2::HSI16:
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
		
		
		//	SDADEL Constraints
		const uint32 SDADEL_min = (t_f_max + t_hd_dat_min - t_af_min - (DNF + 3) * t_i2cclk) / t_PRESC;
		const uint32 SDADEL_max = (t_hd_dat_max - t_af_max - (DNF + 4) * t_i2cclk) / t_PRESC;
		
		
		//	SCLDEL Constraints
		const uint32 SCLDEL_min = (t_r_max + t_su_dat_min) / t_PRESC - 1;
		
		
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
											*MCU::I2C_2::TIMINGR = timingRegister;
											
											
											//	Analog Filters
											if(analogFilterEnable == false)
											{
												bit::set(*MCU::I2C_2::CR1, 12);
											}
											else
											{
												bit::clear(*MCU::I2C_2::CR1, 12);
											}
											
											
											//	Digital Filters
											const uint32 temp = *MCU::I2C_2::CR1 & 0xFFFFF0FF;
											*MCU::I2C_2::CR1 = temp | (digitalFilterLength << 8);
											
											
											//	Enable I2C
											bit::set(*MCU::I2C_2::CR1, 0);
											
											
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
			else
			{
				//	Check if Bus is not busy anymore (only needed when we transmit no Data, so TXIS Bit will never be set)
				//	This means, that we received an ACK
				if(numberOfBytes == 0 && timeWaited_ms >= timeout_ms / 2)
				{
					if(bit::isCleared(*MCU::I2C_2::ISR, 15))
					{
						break;
					}
				}
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
			else
			{
				//	Check if Bus is not busy anymore (only needed when we transmit no Data, so TXIS Bit will never be set)
				//	This means, that we received an ACK
				if(numberOfBytes == 0 && timeWaited_ms >= timeout_ms / 2)
				{
					if(bit::isCleared(*MCU::I2C_2::ISR, 15))
					{
						break;
					}
				}
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
