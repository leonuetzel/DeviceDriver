#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback RCC::startup()
{
	//	Reset Flags: a Snapshot for get_resetFlags(), then cleared (RMVF, Bit 16), so that the next Reset shows only its own Flags
	//	On the H7 RMVF is set AND reset by Software (RM0433): while it stays set, the Flags stay cleared and the next Reset would not show
	m_resetFlags = *MCU::RCC::RSR;
	bit::set(*MCU::RCC::RSR, 16);
	bit::clear(*MCU::RCC::RSR, 16);
	
	
	return(OK);
}


feedback RCC::set_busPrescaler(uint32 newClock, PWR::e_voltageLevel voltageLevel)
{
	//	Limits of the Voltage Level (Datasheet, General operating conditions): CPU, AHB = CPU / 2, APB = CPU / 4
	//	VOS0: 480 / 240 / 120 MHz, VOS1: 400 / 200 / 100 MHz, VOS2: 300 / 150 / 75 MHz, VOS3: 200 / 100 / 50 MHz
	const uint32 clock_core_max = Math::min(c_clock_core_max, PWR::get_clock_max(voltageLevel));
	const uint32 clock_ahb_max = clock_core_max / 2;
	const uint32 clock_apb_max = clock_core_max / 4;
	
	m_divider_core = 1;
	m_divider_ahb  = 1;
	m_divider_apb1 = 1;
	m_divider_apb2 = 1;
	m_divider_apb3 = 1;
	m_divider_apb4 = 1;
	
	
	//	Core Prescaler
	uint32 mask_core = 0x7;
	while(newClock / m_divider_core > clock_core_max)
	{
		m_divider_core *= 2;
		mask_core++;
		if(m_divider_core == 32)
		{
			m_divider_core *= 2;
		}
		if(m_divider_core > 512)
		{
			return(FAIL);
		}
	}
	m_clock_core = newClock / m_divider_core;
	
	
	//	AHB Prescaler
	uint32 mask_ahb = 0x7;
	while(m_clock_core / m_divider_ahb > clock_ahb_max)
	{
		m_divider_ahb *= 2;
		mask_ahb++;
		if(m_divider_ahb == 32)
		{
			m_divider_ahb *= 2;
		}
		if(m_divider_ahb > 512)
		{
			return(FAIL);
		}
	}
	m_clock_ahb = m_clock_core / m_divider_ahb;
	
	
	//	APB1 Prescaler
	uint32 mask_apb1 = 0x3;
	while(m_clock_ahb / m_divider_apb1 > clock_apb_max)
	{
		m_divider_apb1 *= 2;
		mask_apb1++;
		if(m_divider_apb1 > 16)
		{
			return(FAIL);
		}
	}
	m_clock_apb1 = m_clock_ahb / m_divider_apb1;
	m_clock_apb1_timer = m_clock_apb1;
	if(m_divider_apb1 != 1)
	{
		m_clock_apb1_timer *= 2;
	}
	
	
	//	APB2 Prescaler
	uint32 mask_apb2 = 0x3;
	while(m_clock_ahb / m_divider_apb2 > clock_apb_max)
	{
		m_divider_apb2 *= 2;
		mask_apb2++;
		if(m_divider_apb2 > 16)
		{
			return(FAIL);
		}
	}
	m_clock_apb2 = m_clock_ahb / m_divider_apb2;
	m_clock_apb2_timer = m_clock_apb2;
	if(m_divider_apb2 != 1)
	{
		m_clock_apb2_timer *= 2;
	}
	
	
	//	APB3 Prescaler
	uint32 mask_apb3 = 0x3;
	while(m_clock_ahb / m_divider_apb3 > clock_apb_max)
	{
		m_divider_apb3 *= 2;
		mask_apb3++;
		if(m_divider_apb3 > 16)
		{
			return(FAIL);
		}
	}
	m_clock_apb3 = m_clock_ahb / m_divider_apb3;
	
	
	//	APB4 Prescaler
	uint32 mask_apb4 = 0x3;
	while(m_clock_ahb / m_divider_apb4 > clock_apb_max)
	{
		m_divider_apb4 *= 2;
		mask_apb4++;
		if(m_divider_apb4 > 16)
		{
			return(FAIL);
		}
	}
	m_clock_apb4 = m_clock_ahb / m_divider_apb4;
	
	
	//	Write Prescalers to Registers
	uint32 temp = 0;
	
	temp |= (mask_core << 8);
	temp |= (mask_apb3 << 4);
	temp |= mask_ahb;
	*MCU::RCC::D1_CFGR = temp;
	
	temp = 0;
	temp |= (mask_apb2 << 8);
	temp |= (mask_apb1 << 4);
	*MCU::RCC::D2_CFGR = temp;
	
	*MCU::RCC::D3_CFGR = (mask_apb4 << 4);
	return(OK);
}


bool RCC::waitForBit(volatile uint32* reg, uint32 bitNumber, bool state, uint32 numberOfLoops)
{
	for(uint32 i = 0; i < numberOfLoops; i++)
	{
		if(bit::isSet(*reg, bitNumber) == state)
		{
			return(true);
		}
	}
	return(false);
}


feedback RCC::get_clock_pllInput(uint32& clock_in)
{
	//	The Oscillator has to run, otherwise no PLL can lock
	switch(m_clockSource_pll)
	{
		case e_clockSource_pll::HSI:
		{
			clock_in = c_clock_hsi / m_divider_hsi;
			return(bit::isSet(*MCU::RCC::CR, 2) == true ? OK : FAIL);
		}
		break;
		
		case e_clockSource_pll::CSI:
		{
			clock_in = c_clock_csi;
			return(bit::isSet(*MCU::RCC::CR, 8) == true ? OK : FAIL);
		}
		break;
		
		case e_clockSource_pll::HSE:
		{
			clock_in = m_clock_hse;
			return(bit::isSet(*MCU::RCC::CR, 17) == true ? OK : FAIL);
		}
		break;
		
		default:
		{
			clock_in = 0;
			return(FAIL);
		}
		break;
	}
}


feedback RCC::calculate_pll(uint32 clock_in, uint32 clock_vco, s_pll& pll)
{
	//	Wide VCO Range (VCOH): Reference 2 ... 16 MHz, VCO 192 MHz ... 960 MHz (Revision Y: 836 MHz)
	//	Medium VCO Range (VCOL): Reference 1 ... 2 MHz, VCO 150 ... 420 MHz, no fractional Mode (Datasheet, PLL characteristics)
	const bool revisionY = ((*MCU::DBGMCU::IDC >> 16) & 0x0000FFFF) == 0x1003;
	const uint64 vcoMax_wide = revisionY == true ? 836000000 : c_clock_pll_1_max;
	const bool wide = clock_vco >= 192000000 && clock_vco <= vcoMax_wide;
	const bool medium = clock_vco >= 150000000 && clock_vco <= 420000000;
	if(clock_in == 0 || (wide == false && medium == false))
	{
		return(FAIL);
	}
	
	
	//	Step 0: Integer Mode, wide Range, exactly the wished Frequency
	//	Step 1: Fractional Mode (FRACN, 13 Bit), wide Range
	//	Step 2: Integer Mode, medium Range, exactly the wished Frequency (only below 192 MHz: the wide Range covers the rest)
	//	Step 3: Integer Mode, medium Range, the smallest Deviation
	//	Within a Step the highest Reference wins (smallest Input Divider): it gives the lowest Jitter
	for(uint32 step = 0; step < 4; step++)
	{
		const bool rangeWide = (step < 2);
		if((rangeWide == true && wide == false) || (rangeWide == false && medium == false))
		{
			continue;
		}
		const uint64 reference_min = rangeWide == true ? 2000000 : 1000000;
		const uint64 reference_max = rangeWide == true ? 16000000 : 2000000;
		const uint64 vco_min = rangeWide == true ? 192000000 : 150000000;
		const uint64 vco_max = rangeWide == true ? vcoMax_wide : 420000000;
		uint64 deviation_best = 0xFFFFFFFFFFFFFFFF;
		for(uint32 divider_in = 1; divider_in <= 63; divider_in++)
		{
			//	Reference = clock_in / divider_in, compared without Rounding; a Reference of 2 MHz belongs to the medium Range (RM0433, PLLs)
			if((uint64) clock_in > reference_max * divider_in)
			{
				continue;
			}
			if((uint64) clock_in < reference_min * divider_in || (rangeWide == true && (uint64) clock_in == reference_min * divider_in))
			{
				break;
			}
			
			
			//	VCO = Reference * (DIVN + FRACN / 8192): the Multiplier in Steps of 1 / 8192
			uint64 multiplier_scaled = 0;
			if(step == 1)
			{
				multiplier_scaled = ((uint64) clock_vco * divider_in * 8192 + clock_in / 2) / clock_in;
			}
			else
			{
				multiplier_scaled = (((uint64) clock_vco * divider_in + clock_in / 2) / clock_in) * 8192;
			}
			const uint64 multiplier = multiplier_scaled / 8192;
			if(multiplier < 4 || multiplier > 512)
			{
				continue;
			}
			const uint64 vco = ((uint64) clock_in * multiplier_scaled + (uint64) divider_in * 4096) / ((uint64) divider_in * 8192);
			if(vco < vco_min || vco > vco_max)
			{
				continue;
			}
			const uint64 deviation = vco > clock_vco ? vco - clock_vco : clock_vco - vco;
			const bool exact = (uint64) clock_in * multiplier_scaled == (uint64) clock_vco * divider_in * 8192;
			if((step == 0 || step == 2) && exact == false)
			{
				continue;
			}
			if(step == 3 && deviation >= deviation_best)
			{
				continue;
			}
			
			
			//	Input Range (PLLxRGE) of the Reference: 1 ... 2, 2 ... 4, 4 ... 8 or 8 ... 16 MHz
			uint32 inputRange = 3;
			if((uint64) clock_in <= 2000000ull * divider_in)
			{
				inputRange = 0;
			}
			else if((uint64) clock_in <= 4000000ull * divider_in)
			{
				inputRange = 1;
			}
			else if((uint64) clock_in <= 8000000ull * divider_in)
			{
				inputRange = 2;
			}
			pll.divider_in = divider_in;
			pll.multiplier = (uint32) multiplier;
			pll.fraction = (uint32) (multiplier_scaled % 8192);
			pll.clock_vco = (uint32) vco;
			pll.inputRange = inputRange;
			pll.range = rangeWide == true ? e_pll_range::WIDE : e_pll_range::MEDIUM;
			deviation_best = deviation;
			if(step != 3)
			{
				return(OK);
			}
		}
		if(step == 3 && deviation_best != 0xFFFFFFFFFFFFFFFF)
		{
			return(OK);
		}
	}
	return(FAIL);
}


feedback RCC::check_pllDividers(uint32 pllNumber, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	//	0 switches the Output off; PLL 1 P allows only even Dividers (RM0433, RCC_PLL1DIVR)
	if(divider_p > 128 || divider_q > 128 || divider_r > 128)
	{
		return(FAIL);
	}
	if(pllNumber == 1 && divider_p % 2 != 0)
	{
		return(FAIL);
	}
	return(OK);
}


uint32 RCC::get_clock_pllOutputMax(uint32 clock_vco, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	const uint32 dividers[3] = {divider_p, divider_q, divider_r};
	uint32 divider_min = 0;
	for(const uint32 divider: dividers)
	{
		if(divider != 0 && (divider_min == 0 || divider < divider_min))
		{
			divider_min = divider;
		}
	}
	if(divider_min == 0)
	{
		return(0);
	}
	return(clock_vco / divider_min);
}


uint32 RCC::get_clock_pllsOutputMax(uint32 pllNumberExcluded)
{
	//	Highest Frequency of all Outputs of the running PLLs, without the given PLL
	uint32 clock_max = 0;
	if(pllNumberExcluded != 1 && bit::isSet(*MCU::RCC::CR, 24) == true)
	{
		clock_max = Math::max(clock_max, get_clock_pllOutputMax(m_clock_pll_1, m_divider_pll_1_p, m_divider_pll_1_q, m_divider_pll_1_r));
	}
	if(pllNumberExcluded != 2 && bit::isSet(*MCU::RCC::CR, 26) == true)
	{
		clock_max = Math::max(clock_max, get_clock_pllOutputMax(m_clock_pll_2, m_divider_pll_2_p, m_divider_pll_2_q, m_divider_pll_2_r));
	}
	if(pllNumberExcluded != 3 && bit::isSet(*MCU::RCC::CR, 28) == true)
	{
		clock_max = Math::max(clock_max, get_clock_pllOutputMax(m_clock_pll_3, m_divider_pll_3_p, m_divider_pll_3_q, m_divider_pll_3_r));
	}
	return(clock_max);
}


feedback RCC::adapt_voltageLevel(PWR::e_voltageLevel voltageLevel)
{
	STM32H753BIT6& stm32 = STM32H753BIT6::get();
	PWR& pwr = stm32.get_pwr();
	Flash& flash = stm32.get_flash();
	const PWR::e_voltageLevel voltageLevel_current = pwr.get_voltageLevel();
	if(voltageLevel == voltageLevel_current)
	{
		return(OK);
	}
	
	
	//	Higher Voltage: first the Voltage, then the Wait States, which may become fewer
	if((uint32) voltageLevel > (uint32) voltageLevel_current)
	{
		if(pwr.set_voltageLevel(voltageLevel) != OK)
		{
			return(FAIL);
		}
		return(flash.set_waitStates(m_clock_ahb, voltageLevel));
	}
	
	
	//	Lower Voltage: first the Bus Clocks within the Limits of the new Level and the Wait States for them, then the Voltage
	if(set_busPrescaler(m_clock_system, voltageLevel) != OK || flash.set_waitStates(m_clock_ahb, voltageLevel) != OK)
	{
		set_busPrescaler(m_clock_system, voltageLevel_current);
		flash.set_waitStates(m_clock_ahb, voltageLevel_current);
		return(FAIL);
	}
	return(pwr.set_voltageLevel(voltageLevel));
}


feedback RCC::switchSystemClockToHSI(bool& switched)
{
	//	PLL 1 can only be stopped or reconfigured while it does not deliver the System Clock
	switched = false;
	if(get_clockSource_system() != e_clockSource_system::PLL1)
	{
		return(OK);
	}
	if(HSI_init(true, m_divider_hsi) != OK || set_clockSource_system(e_clockSource_system::HSI) != OK)
	{
		return(FAIL);
	}
	switched = true;
	return(OK);
}


feedback RCC::stop_pll(uint32 pllNumber)
{
	//	PLLxON (CR Bit 24, 26, 28); PLLxRDY follows after some Cycles
	const uint32 bitOn = 24 + 2 * (pllNumber - 1);
	bit::clear(*MCU::RCC::CR, bitOn);
	if(waitForBit(MCU::RCC::CR, bitOn + 1, false, c_loops_oscillator) == false)
	{
		return(FAIL);
	}
	return(OK);
}


feedback RCC::start_pll(uint32 pllNumber, const s_pll& pll, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	volatile uint32* const DIVR[3] = {MCU::RCC::PLL1_DIVR, MCU::RCC::PLL2_DIVR, MCU::RCC::PLL3_DIVR};
	volatile uint32* const FRACR[3] = {MCU::RCC::PLL1_FRACR, MCU::RCC::PLL2_FRACR, MCU::RCC::PLL3_FRACR};
	const uint32 index = pllNumber - 1;
	
	
	//	The PLL has to be off: DIVM, DIVN, the Ranges and the Output Dividers can only be written then (RM0433, PLLs)
	if(bit::isSet(*MCU::RCC::CR, 25 + 2 * index) == true)
	{
		return(FAIL);
	}
	
	
	//	Input Divider DIVMx (RCC_PLLCKSELR Bits 9:4, 17:12, 25:20)
	bit::fieldWrite(*MCU::RCC::PLL_CKSELR, 4 + 8 * index, 6, pll.divider_in);
	
	
	//	RCC_PLLCFGR: PLLxFRACEN, PLLxVCOSEL (0 = wide, 1 = medium), PLLxRGE; DIVPxEN, DIVQxEN, DIVRxEN
	bit::clear(*MCU::RCC::PLL_CFGR, 4 * index);
	if(pll.range == e_pll_range::WIDE)
	{
		bit::clear(*MCU::RCC::PLL_CFGR, 4 * index + 1);
	}
	else
	{
		bit::set(*MCU::RCC::PLL_CFGR, 4 * index + 1);
	}
	bit::fieldWrite(*MCU::RCC::PLL_CFGR, 4 * index + 2, 2, pll.inputRange);
	const uint32 dividers[3] = {divider_p, divider_q, divider_r};
	uint32 divr = pll.multiplier - 1;
	for(uint32 i = 0; i < 3; i++)
	{
		//	An unused Output gets the Enable Bit and the Divider 0 (RM0433, PLLs)
		if(dividers[i] == 0)
		{
			bit::clear(*MCU::RCC::PLL_CFGR, 16 + 3 * index + i);
		}
		else
		{
			bit::set(*MCU::RCC::PLL_CFGR, 16 + 3 * index + i);
			divr |= (dividers[i] - 1) << (9 + 7 * i + (i == 2 ? 1 : 0));
		}
	}
	*DIVR[index] = divr;
	
	
	//	Fraction FRACNx (Bits 15:3), taken over with the Transition of PLLxFRACEN from 0 to 1; with 0 the PLL works in Integer Mode
	*FRACR[index] = pll.fraction << 3;
	bit::set(*MCU::RCC::PLL_CFGR, 4 * index);
	
	
	//	Enable PLL and wait for Lock (at most 166 µs, Datasheet)
	bit::set(*MCU::RCC::CR, 24 + 2 * index);
	if(waitForBit(MCU::RCC::CR, 25 + 2 * index, true, c_loops_oscillator) == false)
	{
		bit::clear(*MCU::RCC::CR, 24 + 2 * index);
		return(FAIL);
	}
	return(OK);
}


feedback RCC::init_pll(uint32 pllNumber, uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	uint32* const clock_pll[3] = {&m_clock_pll_1, &m_clock_pll_2, &m_clock_pll_3};
	uint32* const divider[3][3] =
	{
		{&m_divider_pll_1_p, &m_divider_pll_1_q, &m_divider_pll_1_r},
		{&m_divider_pll_2_p, &m_divider_pll_2_q, &m_divider_pll_2_r},
		{&m_divider_pll_3_p, &m_divider_pll_3_q, &m_divider_pll_3_r}
	};
	e_pll_range* const range[3] = {&m_pll_1_range, &m_pll_2_range, &m_pll_3_range};
	const uint32 index = pllNumber - 1;
	
	
	//	Check everything before the running Configuration is touched
	uint32 clock_in = 0;
	s_pll pll = {};
	if(check_pllDividers(pllNumber, divider_p, divider_q, divider_r) != OK || get_clock_pllInput(clock_in) != OK || calculate_pll(clock_in, clock_out, pll) != OK)
	{
		return(FAIL);
	}
	const uint32 clock_outputMax = get_clock_pllOutputMax(pll.clock_vco, divider_p, divider_q, divider_r);
	if(pll.range == e_pll_range::MEDIUM && clock_outputMax > 210000000)
	{
		//	Medium VCO Range: Outputs up to 210 MHz (Datasheet, PLL characteristics)
		return(FAIL);
	}
	
	
	//	Voltage Level for the highest Output of all PLLs (Datasheet: PLL Outputs and CPU 480 / 400 / 300 / 200 MHz in VOS0 ... VOS3)
	PWR& pwr = STM32H753BIT6::get().get_pwr();
	PWR::e_voltageLevel voltageLevel = PWR::e_voltageLevel::VOS_3;
	if(pwr.get_requiredVoltageLevel(Math::max(clock_outputMax, get_clock_pllsOutputMax(pllNumber)), voltageLevel) != OK)
	{
		return(FAIL);
	}
	if((uint32) voltageLevel > (uint32) pwr.get_voltageLevel() && adapt_voltageLevel(voltageLevel) != OK)
	{
		return(FAIL);
	}
	
	
	//	PLL 1 delivers the System Clock: meanwhile the HSI does
	bool switched = false;
	if(pllNumber == 1 && switchSystemClockToHSI(switched) != OK)
	{
		return(FAIL);
	}
	
	
	//	Reconfigure: stop, write, start
	feedback result = stop_pll(pllNumber);
	if(result == OK)
	{
		result = start_pll(pllNumber, pll, divider_p, divider_q, divider_r);
	}
	if(result == OK)
	{
		*clock_pll[index] = pll.clock_vco;
		*divider[index][0] = divider_p;
		*divider[index][1] = divider_q;
		*divider[index][2] = divider_r;
		*range[index] = pll.range;
	}
	else
	{
		//	The PLL stays off and delivers no Clock
		*clock_pll[index] = 0;
	}
	
	
	//	A lower Voltage Level is set when the old Outputs have stopped
	if(result == OK && (uint32) voltageLevel < (uint32) pwr.get_voltageLevel())
	{
		result = adapt_voltageLevel(voltageLevel);
	}
	
	
	//	Back to PLL 1 as System Clock
	if(switched == true && result == OK)
	{
		result = set_clockSource_system(e_clockSource_system::PLL1);
	}
	return(result);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/


feedback RCC::HSE_init(bool enable)
{
	if(enable == true)
	{
		//	A running HSE is kept
		if(bit::isSet(*MCU::RCC::CR, 17) == true)
		{
			return(OK);
		}
		
		
		//	HSE not bypassed
		bit::clear(*MCU::RCC::CR, 18);
		
		
		//	HSE Clock Security System Enable
		bit::set(*MCU::RCC::CR, 19);
		
		
		//	HSE Enable
		bit::set(*MCU::RCC::CR, 16);
		
		
		//	Wait for HSE to become stable (a Crystal needs some Milliseconds); without Crystal the HSE is switched off again
		if(waitForBit(MCU::RCC::CR, 17, true, 10 * c_loops_oscillator) == false)
		{
			bit::clear(*MCU::RCC::CR, 16);
			return(FAIL);
		}
	}
	else
	{
		//	Try to disable HSE
		bit::clear(*MCU::RCC::CR, 16);
		
		
		//	Check if HSE is disabled
		if(bit::isSet(*MCU::RCC::CR, 16))
		{
			return(FAIL);
		}
	}
	
	return(OK);
}


feedback RCC::init_lse(bool enable)
{
	//	The LSE belongs to the Backup Domain: its Write Protection (DBP in PWR_CR1) is lifted for the Access and restored afterwards
	const bool writeProtected = bit::isCleared(*MCU::PWR::CR1, 8);
	bit::set(*MCU::PWR::CR1, 8);
	while(bit::isCleared(*MCU::PWR::CR1, 8))
	{
		
	}
	
	
	feedback result = OK;
	if(enable == true)
	{
		//	A running LSE is kept: it survives a Reset of the Microcontroller
		if(bit::isCleared(*MCU::RCC::BDCR, 1) == true)
		{
			//	Crystal, not bypassed (LSEBYP can only be changed while the LSE is off), lowest Drive (LSEDRV = 0)
			bit::clear(*MCU::RCC::BDCR, 2);
			bit::set(*MCU::RCC::BDCR, 0);
			
			
			//	A Crystal needs up to some Seconds to start (Datasheet, tSU(LSE))
			CMOS& cmos = CMOS::get();
			const uint64 timestampStart = cmos.get_timestamp();
			while(bit::isCleared(*MCU::RCC::BDCR, 1) == true)
			{
				if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 5000)
				{
					//	No Crystal
					bit::clear(*MCU::RCC::BDCR, 0);
					result = FAIL;
					break;
				}
			}
		}
	}
	else
	{
		bit::clear(*MCU::RCC::BDCR, 0);
	}
	
	
	if(writeProtected == true)
	{
		bit::clear(*MCU::PWR::CR1, 8);
	}
	return(result);
}


feedback RCC::init_lsi(bool enable)
{
	if(enable == true)
	{
		//	LSI Enable (RCC_CSR), it is ready after some 100 Microseconds (Datasheet, tSU(LSI))
		bit::set(*MCU::RCC::CSR, 0);
		CMOS& cmos = CMOS::get();
		const uint64 timestampStart = cmos.get_timestamp();
		while(bit::isCleared(*MCU::RCC::CSR, 1) == true)
		{
			if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 10)
			{
				bit::clear(*MCU::RCC::CSR, 0);
				return(FAIL);
			}
		}
	}
	else
	{
		bit::clear(*MCU::RCC::CSR, 0);
	}
	return(OK);
}


feedback RCC::HSI_init(bool enable, uint8 divider)
{
	if(enable == true)
	{
		//	HSIDIV: 1, 2, 4 or 8
		if(divider != 1 && divider != 2 && divider != 4 && divider != 8)
		{
			return(FAIL);
		}
		
		
		//	A running PLL takes the HSI as Reference: a new Divider would change its Frequency
		const bool pllRunning = (*MCU::RCC::CR & ((1 << 24) | (1 << 26) | (1 << 28))) != 0;
		if(divider != m_divider_hsi && m_clockSource_pll == e_clockSource_pll::HSI && pllRunning == true)
		{
			return(FAIL);
		}
		
		
		//	Enable HSI and wait for it to become stable
		bit::set(*MCU::RCC::CR, 0);
		if(waitForBit(MCU::RCC::CR, 2, true, c_loops_oscillator) == false)
		{
			return(FAIL);
		}
		if(divider == m_divider_hsi)
		{
			return(OK);
		}
		
		
		//	The HSI delivers the System Clock: a higher Frequency needs the Bus Prescalers and Wait States first, a lower one afterwards
		const uint32 clock_new = c_clock_hsi / divider;
		const bool system = get_clockSource_system() == e_clockSource_system::HSI;
		STM32H753BIT6& stm32 = STM32H753BIT6::get();
		const PWR::e_voltageLevel voltageLevel = stm32.get_pwr().get_voltageLevel();
		if(system == true && clock_new > m_clock_system)
		{
			if(set_busPrescaler(clock_new, voltageLevel) != OK || stm32.get_flash().set_waitStates(m_clock_ahb, voltageLevel) != OK)
			{
				set_busPrescaler(m_clock_system, voltageLevel);
				return(FAIL);
			}
		}
		
		
		//	Set new Divider and wait for the new Frequency (HSIDIVF)
		const uint32 mask = Math::log2((uint32) divider);
		bit::fieldWrite(*MCU::RCC::CR, 3, 2, mask);
		if(bit::fieldRead(*MCU::RCC::CR, 3, 2) != mask || waitForBit(MCU::RCC::CR, 5, true, c_loops_oscillator) == false)
		{
			return(FAIL);
		}
		if(system == true && clock_new < m_clock_system)
		{
			set_busPrescaler(clock_new, voltageLevel);
			stm32.get_flash().set_waitStates(m_clock_ahb, voltageLevel);
		}
		
		
		//	Store the new Clocks: hsi_ck and hsi_ker_ck both come after the Divider
		m_divider_hsi = divider;
		if(system == true)
		{
			m_clock_system = clock_new;
		}
		if(m_clockSource_perck == e_clockSource_perck::HSI)
		{
			m_clock_perck = clock_new;
		}
	}
	else
	{
		//	Try to disable HSI
		bit::clear(*MCU::RCC::CR, 0);
		
		
		//	Check if HSI is disabled
		if(bit::isSet(*MCU::RCC::CR, 0))
		{
			return(FAIL);
		}
	}
	
	return(OK);
}


feedback RCC::init_csi(bool enable)
{
	if(enable == true)
	{
		//	CSION (CR Bit 7), CSIRDY (Bit 8)
		bit::set(*MCU::RCC::CR, 7);
		if(waitForBit(MCU::RCC::CR, 8, true, c_loops_oscillator) == false)
		{
			return(FAIL);
		}
	}
	else
	{
		//	The Hardware keeps the CSI on while it is used (System Clock, PLL Reference)
		bit::clear(*MCU::RCC::CR, 7);
		if(bit::isSet(*MCU::RCC::CR, 7))
		{
			return(FAIL);
		}
	}
	return(OK);
}











feedback RCC::set_clockSource_pll(e_clockSource_pll clockSource)
{
	//	Boundary Check
	const uint32 mask = (uint32) clockSource;
	if(mask > 0x3)
	{
		return(FAIL);
	}
	
	
	//	The current Source: the PLLs keep running
	if(clockSource == m_clockSource_pll && bit::fieldRead(*MCU::RCC::PLL_CKSELR, 0, 2) == mask)
	{
		return(OK);
	}
	
	
	//	The new Reference has to run, else no PLL could lock
	const uint32 bitReady[3] = {2, 8, 17};
	if(clockSource != e_clockSource_pll::NONE && bit::isCleared(*MCU::RCC::CR, bitReady[mask]) == true)
	{
		return(FAIL);
	}
	const bool running[3] = {bit::isSet(*MCU::RCC::CR, 24), bit::isSet(*MCU::RCC::CR, 26), bit::isSet(*MCU::RCC::CR, 28)};
	if(clockSource == e_clockSource_pll::NONE && (running[0] == true || running[1] == true || running[2] == true))
	{
		return(FAIL);
	}
	
	
	//	PLLSRC can only be changed while all PLLs are off; PLL 1 must not deliver the System Clock then
	bool switched = false;
	if(switchSystemClockToHSI(switched) != OK)
	{
		return(FAIL);
	}
	for(uint32 pllNumber = 1; pllNumber <= 3; pllNumber++)
	{
		if(stop_pll(pllNumber) != OK)
		{
			return(FAIL);
		}
	}
	
	
	//	Set new Clock Source
	bit::fieldWrite(*MCU::RCC::PLL_CKSELR, 0, 2, mask);
	if(bit::fieldRead(*MCU::RCC::PLL_CKSELR, 0, 2) != mask)
	{
		return(FAIL);
	}
	m_clockSource_pll = clockSource;
	
	
	//	The PLLs that were running start again with the same Frequencies, the Dividers computed for the new Reference
	feedback result = OK;
	if(running[0] == true && pll_1_init(m_clock_pll_1, m_divider_pll_1_p, m_divider_pll_1_q, m_divider_pll_1_r) != OK)
	{
		result = FAIL;
	}
	if(running[1] == true && pll_2_init(m_clock_pll_2, m_divider_pll_2_p, m_divider_pll_2_q, m_divider_pll_2_r) != OK)
	{
		result = FAIL;
	}
	if(running[2] == true && pll_3_init(m_clock_pll_3, m_divider_pll_3_p, m_divider_pll_3_q, m_divider_pll_3_r) != OK)
	{
		result = FAIL;
	}
	
	
	//	Back to PLL 1 as System Clock
	if(switched == true && bit::isSet(*MCU::RCC::CR, 25) == true)
	{
		if(set_clockSource_system(e_clockSource_system::PLL1) != OK)
		{
			result = FAIL;
		}
	}
	return(result);
}


feedback RCC::pll_1_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	return(init_pll(1, clock_out, divider_p, divider_q, divider_r));
}


feedback RCC::pll_2_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	return(init_pll(2, clock_out, divider_p, divider_q, divider_r));
}


feedback RCC::pll_3_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r)
{
	return(init_pll(3, clock_out, divider_p, divider_q, divider_r));
}









RCC::e_clockSource_system RCC::get_clockSource_system()
{
	const uint32 bits = bit::fieldRead(*MCU::RCC::CFGR, 3, 3);
	return((e_clockSource_system) bits);
}


feedback RCC::set_clock_hse(uint32 clock)
{
	//	Crystal 4 ... 48 MHz, external Clock up to 50 MHz (Datasheet)
	if(clock < 4000000 || clock > 50000000)
	{
		return(FAIL);
	}
	
	
	//	Only while the HSE is off (HSEON = 0): then no Clock depends on it yet
	if(bit::isSet(*MCU::RCC::CR, 16) == true)
	{
		return(FAIL);
	}
	m_clock_hse = clock;
	return(OK);
}


feedback RCC::set_clockSource_system(e_clockSource_system clockSource)
{
	//	The new Source has to run (HSIRDY, CSIRDY, HSERDY, PLL1RDY) and PLL 1 needs its P Output
	uint32 newClock = 0;
	uint32 bitReady = 0;
	switch(clockSource)
	{
		case e_clockSource_system::HSI:
		{
			newClock = c_clock_hsi / m_divider_hsi;
			bitReady = 2;
		}
		break;
		
		case e_clockSource_system::CSI:
		{
			newClock = c_clock_csi;
			bitReady = 8;
		}
		break;
		
		case e_clockSource_system::HSE:
		{
			newClock = m_clock_hse;
			bitReady = 17;
		}
		break;
		
		case e_clockSource_system::PLL1:
		{
			if(m_divider_pll_1_p == 0)
			{
				return(FAIL);
			}
			newClock = m_clock_pll_1 / m_divider_pll_1_p;
			bitReady = 25;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
		break;
	}
	if(bit::isCleared(*MCU::RCC::CR, bitReady) == true)
	{
		return(FAIL);
	}
	
	
	STM32H753BIT6& stm32 = STM32H753BIT6::get();
	Flash& flash = stm32.get_flash();
	PWR& pwr = stm32.get_pwr();
	const PWR::e_voltageLevel voltageLevel = pwr.get_voltageLevel();
	if(newClock > PWR::get_clock_max(voltageLevel))
	{
		return(FAIL);
	}
	if(newClock > m_clock_system)
	{
		//	Higher Frequency: Bus Prescalers and Wait States before the Switch
		if(set_busPrescaler(newClock, voltageLevel) != OK || flash.set_waitStates(m_clock_ahb, voltageLevel) != OK)
		{
			set_busPrescaler(m_clock_system, voltageLevel);
			return(FAIL);
		}
		
		
		//	Switch System Clock Source and wait for it: SWS follows SW after some Clock Cycles of both Clock Sources
		const uint32 clockSourceOld = *MCU::RCC::CFGR & 0x00000007;
		bit::fieldWrite(*MCU::RCC::CFGR, 0, 3, (uint32) clockSource);
		uint32 timeout = 100000;
		while(get_clockSource_system() != clockSource)
		{
			timeout--;
			if(timeout == 0)
			{
				//	Undo the Switch
				bit::fieldWrite(*MCU::RCC::CFGR, 0, 3, clockSourceOld);
				set_busPrescaler(m_clock_system, voltageLevel);
				return(FAIL);
			}
		}
	}
	else
	{
		//	Switch System Clock Source and wait for it: SWS follows SW after some Clock Cycles of both Clock Sources
		const uint32 clockSourceOld = *MCU::RCC::CFGR & 0x00000007;
		bit::fieldWrite(*MCU::RCC::CFGR, 0, 3, (uint32) clockSource);
		uint32 timeout = 100000;
		while(get_clockSource_system() != clockSource)
		{
			timeout--;
			if(timeout == 0)
			{
				//	Undo the Switch
				bit::fieldWrite(*MCU::RCC::CFGR, 0, 3, clockSourceOld);
				return(FAIL);
			}
		}
		
		
		//	Lower Frequency: Bus Prescalers and Wait States after the Switch
		if(set_busPrescaler(newClock, voltageLevel) != OK)
		{
			return(FAIL);
		}
		flash.set_waitStates(m_clock_ahb, voltageLevel);
	}
	
	
	//	Store Settings
	m_clock_system = newClock;
	m_clockSource_system = clockSource;
	
	return(OK);
}







RCC::e_resetReason RCC::check_resetReason()
{
	static uint32 temp;
	e_resetReason resetReason = e_resetReason::NONE;
	
	
	
	if(temp == 0)
	{
		temp = *MCU::RCC::RSR & 0x55FB0000;
	}
	
	
	
	if(bit::isSet(temp, 30))
	{
		bit::clear(temp, 30);
		resetReason = e_resetReason::ILLEGAL_D1DSTANDBY_OR_CPUCSTOP;
	}
	else if(bit::isSet(temp, 28))
	{
		bit::clear(temp, 28);
		resetReason = e_resetReason::WWDG;
	}
	else if(bit::isSet(temp, 26))
	{
		bit::clear(temp, 26);
		resetReason = e_resetReason::IWDG;
	}
	else if(bit::isSet(temp, 24))
	{
		bit::clear(temp, 24);
		resetReason = e_resetReason::CPU_FLAG;
	}
	else if(bit::isSet(temp, 23))
	{
		bit::clear(temp, 23);
		resetReason = e_resetReason::POWER_ON_OFF;
	}
	else if(bit::isSet(temp, 22))
	{
		bit::clear(temp, 22);
		resetReason = e_resetReason::PIN;
	}
	else if(bit::isSet(temp, 21))
	{
		bit::clear(temp, 21);
		resetReason = e_resetReason::BROWNOUT;
	}
	else if(bit::isSet(temp, 20))
	{
		bit::clear(temp, 20);
		resetReason = e_resetReason::D2_POWERSWITCH_FLAG;
	}
	else if(bit::isSet(temp, 19))
	{
		bit::clear(temp, 19);
		resetReason = e_resetReason::D1_POWERSWITCH_FLAG;
	}
	else if(bit::isSet(temp, 17))
	{
		bit::clear(temp, 17);
		resetReason = e_resetReason::CPU;
	}
	
	if(temp == 0)
	{
		bit::set(*MCU::RCC::RSR, 16);																																																//  Clear Reset Flags
	}
	
	return(resetReason);
}







feedback RCC::mco_1_init(e_clockSource_mco_1 clockSource, uint32 divider)
{
	if(clockSource != m_clockSource_mco_1)
	{
		//	Boundary Check
		const uint32 mask = (uint32) clockSource;
		if(mask > 0x4)
		{
			return(FAIL);
		}
		
		
		//	Write Clock Source
		bit::fieldWrite(*MCU::RCC::CFGR, 22, 3, mask);
		
		
		//	Store Setting
		m_clockSource_mco_1 = clockSource;
	}
	
	if(divider != m_divider_mco_1)
	{
		//	Boundary Check
		if(divider > 15)
		{
			return(FAIL);
		}
		
		
		//	Write Divider
		bit::fieldWrite(*MCU::RCC::CFGR, 18, 4, divider);
		
		
		//	Store Setting
		m_divider_mco_1 = divider;
	}
	return(OK);
}


feedback RCC::mco_2_init(e_clockSource_mco_2 clockSource, uint32 divider)
{
	if(clockSource != m_clockSource_mco_2)
	{
		//	Boundary Check
		const uint32 mask = (uint32) clockSource;
		if(mask > 0x5)
		{
			return(FAIL);
		}
		
		
		//	Write Clock Source
		bit::fieldWrite(*MCU::RCC::CFGR, 29, 3, mask);
		
		
		//	Store Setting
		m_clockSource_mco_2 = clockSource;
	}

	if(divider != m_divider_mco_2)
	{
		//	Boundary Check
		if(divider > 15)
		{
			return(FAIL);
		}
		
		
		//	Write Divider
		bit::fieldWrite(*MCU::RCC::CFGR, 25, 4, divider);
		
		
		//	Store Setting
		m_divider_mco_2 = divider;
	}
	return(OK);
}







feedback RCC::module_clockInit(e_module module, bool enable)
{
	const uint32 offset = (((uint32) module) & 0x0000FF00) >> 8;
	volatile uint32* reg = MCU::RCC::AHB3_ENR + offset;
	
	const uint32 bit = ((uint32) module) & 0x000000FF;
	
	if(enable == true)
	{
		//	The Clock of the Peripheral is active some Clock Cycles after its Enable Bit (2 on the L4/G4, RM0394): the dummy Read delays the
		//	first Access to the Peripheral, as the ST HAL does it on every STM32
		bit::set(*reg, bit);
		(void) *reg;
	}
	else
	{
		bit::clear(*reg, bit);
	}
	return(OK);
}


feedback RCC::module_reset(e_module module)
{
	const uint32 offset = (((uint32) module) & 0x0000FF00) >> 8;
	volatile uint32* reg = MCU::RCC::AHB3_RSTR + offset;
	
	const uint32 bit = ((uint32) module) & 0x000000FF;
	
	
	//	Set Reset Bit: some Modules have none (e.g. SRAM 1 ... 3, Backup RAM, WWDG), then the Bit stays 0
	bit::set(*reg, bit);
	if(bit::isCleared(*reg, bit) == true)
	{
		return(FAIL);
	}
	
	
	//	Clear Reset Bit
	bit::clear(*reg, bit);
	return(OK);
}







feedback RCC::set_clockSource(e_clockSource_perck clockSource)
{
	//	Determine Bit Mask
	uint32 mask = 0x0;
	switch(clockSource)
	{
		case e_clockSource_perck::HSI:
		{
			mask = 0x0;
			m_clock_perck = c_clock_hsi / m_divider_hsi;
		}
		break;
		
		case e_clockSource_perck::CSI:
		{
			mask = 0x1;
			m_clock_perck = c_clock_csi;
		}
		break;
		
		case e_clockSource_perck::HSE:
		{
			mask = 0x2;
			m_clock_perck = m_clock_hse;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
		break;
	}
	
	
	//	Write Clock Source
	bit::fieldWrite(*MCU::RCC::D1_CCIPR, 28, 2, mask);
	
	
	//	Store Setting
	m_clockSource_perck = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_adc clockSource)
{
	//	Check if Clock Source is already set
	if(m_clockSource_adc == clockSource)
	{
		return(OK);
	}
	
	
	//	Write Clock Source
	bit::fieldWrite(*MCU::RCC::D3_CCIPR, 16, 2, (uint32) clockSource);
	
	
	//	Store Setting
	m_clockSource_adc = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_sdmmc clockSource)
{
	//	Check if Clock Source is already set
	if(m_clockSource_sdmmc == clockSource)
	{
		return(OK);
	}
	
	
	//	Write Clock Source
	bit::fieldWrite(*MCU::RCC::D1_CCIPR, 16, 2, (uint32) clockSource);
	
	
	//	Store Setting
	m_clockSource_sdmmc = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_uart clockSource, uint32 uartNumber)
{
	//	Check which UART is selected, because UART1 and UART6 share the same Bits
	if(uartNumber == 1 || uartNumber == 6)
	{
		//	Check if Clock Source is already set
		if(m_clockSource_uart_1_6 == clockSource)
		{
			return(OK);
		}
		
		
		//	Write Clock Source
		bit::fieldWrite(*MCU::RCC::D2_CCIP2R, 3, 3, (uint32) clockSource);
		
		
		//	Store Setting
		m_clockSource_uart_1_6 = clockSource;
		return(OK);
	}
	else
	{
		//	Check if Clock Source is already set
		if(m_clockSource_uart_234578 == clockSource)
		{
			return(OK);
		}
		
		
		//	Write Clock Source
		bit::fieldWrite(*MCU::RCC::D2_CCIP2R, 0, 3, (uint32) clockSource);
		
		
		//	Store Setting
		m_clockSource_uart_234578 = clockSource;
		return(OK);
	}
}


feedback RCC::set_clockSource(e_clockSource_fmc clockSource)
{
	//	Check if Clock Source is already set
	if(m_clockSource_fmc == clockSource)
	{
		return(OK);
	}
	
	
	//	Write Clock Source
	bit::fieldWrite(*MCU::RCC::D1_CCIPR, 0, 2, (uint32) clockSource);
	
	
	//	Store Setting
	m_clockSource_fmc = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_can clockSource)
{
	//	Check if Clock Source is already set
	if(m_clockSource_can == clockSource)
	{
		return(OK);
	}
	
	
	//	Write Clock Source
	bit::fieldWrite(*MCU::RCC::D2_CCIP1R, 28, 2, (uint32) clockSource);
	
	
	//	Store Setting
	m_clockSource_can = clockSource;
	return(OK);
}


feedback RCC::set_clockSource(e_clockSource_i2c clockSource)
{
	//	Boundary Check
	const uint32 mask = (uint32) clockSource;
	if(mask > 0x3)
	{
		return(FAIL);
	}
	
	
	//	I2C123SEL (RCC_D2CCIP2R Bits 13:12), shared by I2C 1, 2 and 3
	bit::fieldWrite(*MCU::RCC::D2_CCIP2R, 12, 2, mask);
	
	
	//	Store Setting
	m_clockSource_i2c = clockSource;
	return(OK);
}


uint32 RCC::get_clock_i2c()
{
	//	Kernel Clock of I2C 1, 2 and 3; 0 if the Source is off
	switch(m_clockSource_i2c)
	{
		case e_clockSource_i2c::BUS_CLOCK:
		{
			return(m_clock_apb1);
		}
		break;
		
		case e_clockSource_i2c::PLL_3_R:
		{
			return(bit::isSet(*MCU::RCC::CR, 29) == true ? get_clock_pll_3_r() : 0);
		}
		break;
		
		case e_clockSource_i2c::HSI:
		{
			return(bit::isSet(*MCU::RCC::CR, 2) == true ? get_clock_hsi() : 0);
		}
		break;
		
		case e_clockSource_i2c::CSI:
		{
			return(bit::isSet(*MCU::RCC::CR, 8) == true ? c_clock_csi : 0);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
}
