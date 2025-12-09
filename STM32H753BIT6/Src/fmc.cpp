#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback FMC::startup()
{
	RCC& rcc = STM32H753BIT6::get().get_rcc();
	rcc.module_reset(RCC::e_module::FMC);
	rcc.module_clockInit(RCC::e_module::FMC, true);
	
	
	//	Disable NOR/PSRAM Bank1 (enabled by Default after Reset)
	bit::clear(*MCU::FMC::BCR1, 0);
	
	return(OK);
}


feedback FMC::memory_check(uint32 startAddress, uint32 sizeInBytes, uint32 pattern)
{
	if(sizeInBytes < 4)
	{
		return(FAIL);
	}
	
	for(uint32 i = startAddress; i < startAddress + sizeInBytes; i += 4)
	{
		*((uint32*) i) = pattern;
	}
	for(uint32 i = startAddress; i < startAddress + sizeInBytes; i += 4)
	{
		if(*((uint32*) i) != pattern)
		{
			return(FAIL);
		}
	}
	
	for(uint32 i = startAddress; i < startAddress + sizeInBytes; i += 4)
	{
		*((uint32*) i) = 0;
	}
	
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/









feedback FMC::init(RCC::e_clockSource_fmc clockSource, e_SDRAM_bank bank, s_SDRAM_config memoryData)
{
	if(memoryData.t_RCD_rowToColumnDelay == 0 || memoryData.t_RP_rowPrechargeDelay == 0 || memoryData.t_WR_recoveryDelay == 0 || memoryData.t_RC_rowCycleDelay == 0)
	{
		return(FAIL);
	}
	if(memoryData.t_RAS_selfRefreshTime == 0 || memoryData.t_XSR_exitSelfRefreshDelay == 0 || memoryData.t_MRD_loadModeRegisterToActive == 0)
	{
		return(FAIL);
	}
	if(memoryData.t_WR_recoveryDelay < memoryData.t_RAS_selfRefreshTime - memoryData.t_RCD_rowToColumnDelay)
	{
		return(FAIL);
	}
	if(memoryData.t_WR_recoveryDelay < memoryData.t_RC_rowCycleDelay - memoryData.t_RCD_rowToColumnDelay - memoryData.t_RP_rowPrechargeDelay)
	{
		return(FAIL);
	}
	
	CMOS& cmos = CMOS::get();
	RCC& rcc = STM32H753BIT6::get().get_rcc();
	rcc.set_clockSource(clockSource);
	
	volatile uint32* fmc_sdcr	= MCU::FMC::SDCR1 + (uint32) bank;
	volatile uint32* fmc_sdtr	= MCU::FMC::SDTR1 + (uint32) bank;
	
	
	
	//	Common to both SDRAM Banks
	uint32 mask = 0;
	mask |= (((uint32) memoryData.readPipeDelay)					<< 13);
	if(memoryData.readBurst == true)
	{
		bit::set(mask, 12);
	}
	mask |= (((uint32) memoryData.clockDivision)					<< 10);
	
	*MCU::FMC::SDCR1 = mask;
	
	
	//	Configuration
	mask = *fmc_sdcr & 0xFFFFFC00;
	if(memoryData.writeProtection == true)
	{
		bit::set(mask, 9);
	}
	mask |= (((uint32) memoryData.CAS_Latency)						<< 7);
	mask |= (((uint32) memoryData.numberOfInternalBanks)	<< 6);
	mask |= (((uint32) memoryData.dataBusWidth)						<< 4);
	mask |= (((uint32) memoryData.rowAddressBits)					<< 2);
	mask |= (((uint32) memoryData.columnAddressBits)			<< 0);
	
	*fmc_sdcr = mask;
	
	
	//	Timing
	mask = 0;
	mask |= (((memoryData.t_RCD_rowToColumnDelay					- 1) & 0xF) << 24);
	mask |= (((memoryData.t_RP_rowPrechargeDelay					- 1) & 0xF) << 20);
	mask |= (((memoryData.t_WR_recoveryDelay							- 1) & 0xF) << 16);
	mask |= (((memoryData.t_RC_rowCycleDelay							- 1) & 0xF) << 12);
	mask |= (((memoryData.t_RAS_selfRefreshTime						- 1) & 0xF) << 8);
	mask |= (((memoryData.t_XSR_exitSelfRefreshDelay			- 1) & 0xF) << 4);
	mask |= (((memoryData.t_MRD_loadModeRegisterToActive	- 1) & 0xF) << 0);
	
	*fmc_sdtr = mask;
	
	
	//	Enable FMC
	bit::set(*MCU::FMC::BCR1, 31);
	
	
	//	Output CLK and wait >100µs
	if(bank == e_SDRAM_bank::BANK_1)
	{
		*MCU::FMC::SDCMR = 0x00000011;
	}
	else
	{
		*MCU::FMC::SDCMR = 0x00000009;
	}
	cmos.sleep_ms(100);
	
	
	//	Precharge All Command
	if(bank == e_SDRAM_bank::BANK_1)
	{
		*MCU::FMC::SDCMR = 0x00000012;
	}
	else
	{
		*MCU::FMC::SDCMR = 0x0000000A;
	}
	cmos.sleep_ms(100);
	
	
	//	Auto Refresh Command (9 Auto Refresh Cycles)
	mask = 0;
	if(bank == e_SDRAM_bank::BANK_1)
	{
		mask = 0x00000113;
	}
	else
	{
		mask = 0x0000010B;
	}
	for(uint32 i = 0; i < 8; i++)
	{
		*MCU::FMC::SDCMR = mask;
		cmos.sleep_ms(100);
	}
	
	
	//	Load Mode Register
	const uint16 loadModeRegister = 0b1000000000 | (((uint16) memoryData.CAS_Latency) << 4);
	if(bank == e_SDRAM_bank::BANK_1)
	{
		*MCU::FMC::SDCMR = 0x00000114 | (loadModeRegister << 9);
	}
	else
	{
		*MCU::FMC::SDCMR = 0x0000010C | (loadModeRegister << 9);
	}
	cmos.sleep_ms(100);
	
	
	//	Set Refresh Rate
	uint32 clock = 0;
	switch(rcc.get_clockSource_fmc())
	{
		case RCC::e_clockSource_fmc::BUS_CLOCK:
			clock = rcc.get_clock_ahb();
			break;
			
		case RCC::e_clockSource_fmc::PLL_1_Q:
			clock = rcc.get_clock_pll_1_q();
			break;
			
		case RCC::e_clockSource_fmc::PLL_2_R:
			clock = rcc.get_clock_pll_2_r();
			break;
			
		case RCC::e_clockSource_fmc::PERCK:
			clock = rcc.get_clock_perck();
			break;
			
		default:
			return(FAIL);
	}
	
	switch(memoryData.clockDivision)
	{
		case FMC::e_clockDivision::DIV_2:
			clock /= 2;
			break;
			
		case FMC::e_clockDivision::DIV_3:
			clock /= 3;
			break;
			
		default:
		return(FAIL);
	}
	
	
	//	Calculate Address and Size
	uint32 startAddress = 0xC0000000;
	if(bank == e_SDRAM_bank::BANK_2)
	{
		startAddress = 0xD0000000;
	}
	
	uint32 exponent = 0;
	switch(memoryData.rowAddressBits)
	{
		case e_rowAddressBits::_11:
			exponent = 11;
			break;
			
		case e_rowAddressBits::_12:
			exponent = 12;
			break;
			
		case e_rowAddressBits::_13:
			exponent = 13;
			break;
			
		default:
			return(FAIL);
	}
	
	float numberOfRows = Math::power<uint32, uint32>(2, exponent);
	
	switch(memoryData.columnAddressBits)
	{
		case e_columnAddressBits::_8:
			exponent += 8;
			break;
			
		case e_columnAddressBits::_9:
			exponent += 9;
			break;
			
		case e_columnAddressBits::_10:
			exponent += 10;
			break;
			
		case e_columnAddressBits::_11:
			exponent += 11;
			break;
			
		default:
			return(FAIL);
	}
	
	uint32 factor = 0;
	switch(memoryData.numberOfInternalBanks)
	{
		case e_numberOfInternalBanks::_2:
			factor = 2;
			break;
			
		case e_numberOfInternalBanks::_4:
			factor = 4;
			break;
			
		default:
			return(FAIL);
	}
	
	switch(memoryData.dataBusWidth)
	{
		case e_dataBusWidth::_8_BIT:
			factor *= 1;
			break;
			
		case e_dataBusWidth::_16_BIT:
			factor *= 2;
			break;
			
		case e_dataBusWidth::_32_BIT:
			factor *= 4;
			break;
			
		default:
			return(FAIL);
	}
	
	const uint32 memorySize = factor * Math::power<uint32, uint32>(2, exponent);
	
	
	
	uint32 value = (64.0e-3 / numberOfRows) * ((float) clock) - 20.0;
	if(value == (uint32) (memoryData.t_WR_recoveryDelay + memoryData.t_RP_rowPrechargeDelay + memoryData.t_RC_rowCycleDelay + memoryData.t_RCD_rowToColumnDelay + 4))
	{
		value--;
	}
	*MCU::FMC::SDRTR = value << 1;
	
	
	if(memory_check(startAddress, memorySize, 0x00000000) != OK)
	{
		return(FAIL);
	}
	if(memory_check(startAddress, memorySize, 0xFFFFFFFF) != OK)
	{
		return(FAIL);
	}
	if(memory_check(startAddress, memorySize, 0xAAAAAAAA) != OK)
	{
		return(FAIL);
	}
	if(memory_check(startAddress, memorySize, 0x55555555) != OK)
	{
		return(FAIL);
	}
	
	
	if(bank == e_SDRAM_bank::BANK_1)
	{
		m_sdram_1 = memoryData;
	}
	else
	{
		m_sdram_2 = memoryData;
	}
	
	return(OK);
}