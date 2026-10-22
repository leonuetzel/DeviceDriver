#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

CODE_RAM void ADC_1::callback()
{
	//	The DMA Driver has invalidated the 16 Values of the regular Channels before this Callback (Data Cache)
	//	The injected Channels are written by the CPU into the next Cache Line
	ADC_1& adc_1 = STM32H753BIT6::get().get_adc_1();
	adc_1.m_value[16] = *MCU::ADC_1::JDR1;
	adc_1.m_value[17] = *MCU::ADC_1::JDR2;
	adc_1.m_value[18] = *MCU::ADC_1::JDR3;
	adc_1.m_value[19] = *MCU::ADC_1::JDR4;
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback ADC_1::init(uint32 clock, uint16 valueBuffer[c_valueBufferSize], e_clockSource clockSource, VREFBUF::e_mode referenceMode, VREFBUF::e_voltage referenceVoltage)
{
	//	Protect from unauthorized Access
	if(CMOS::get().mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	init() runs once: while the ADC converts, its DMA Channel runs circularly. A second Call returns FAIL before it changes
	//	anything - otherwise it would reset the ADC and then fail at the busy Channel, and the Conversion would stop
	if(STM32H753BIT6::get().get_dma_1(0).is_busy() == true)
	{
		return(FAIL);
	}
	
	
	//	Check Clock
	if(clock > c_clock_max)
	{
		return(FAIL);
	}
	
	
	//	Enable Clock
	STM32H753BIT6& stm32h753bit6 = STM32H753BIT6::get();
	RCC& rcc = stm32h753bit6.get_rcc();
	rcc.module_clockInit(RCC::e_module::ADC_1_2, true);
	
	
	//	Value Buffer
	//	The DMA writes its first 32 Bytes, with the Data Cache on they must own their Cache Line (see cacheMaintenance.hpp)
	if(valueBuffer == nullptr || CacheMaintenance::ownsCacheLines(valueBuffer, 16 * sizeof(uint16)) == false)
	{
		return(FAIL);
	}
	m_value = valueBuffer;
	
	
	//	Voltage Reference: external at VREF+ or the internal Buffer (VREFBUF) - VREF+ is shared by all ADCs and the DAC,
	//	so it must not change while another ADC is running (ADEN)
	if(referenceMode != VREFBUF::e_mode::EXTERNAL && referenceMode != VREFBUF::e_mode::INTERNAL)
	{
		return(FAIL);
	}
	VREFBUF& vrefbuf = stm32h753bit6.get_vrefbuf();
	const bool referenceChanges = (vrefbuf.get_mode() != referenceMode || (referenceMode == VREFBUF::e_mode::INTERNAL && vrefbuf.get_voltage() != referenceVoltage));
	if(referenceChanges == true && (bit::isSet(*MCU::ADC_2::CR, 0) == true || bit::isSet(*MCU::ADC_3::CR, 0) == true))
	{
		return(FAIL);
	}
	if(referenceMode == VREFBUF::e_mode::INTERNAL && vrefbuf.set_voltage(referenceVoltage) != OK)
	{
		return(FAIL);
	}
	if(vrefbuf.set_mode(referenceMode) != OK)
	{
		return(FAIL);
	}
	
	
	//	Stop Deep Power Down Mode
	bit::clear(*MCU::ADC_1::CR, 29);
	
	
	//	Enable Internal Voltage Regulator
	bit::set(*MCU::ADC_1::CR, 28);
	
	
	//	Wait 10us for Internal Voltage Regulator to Start up - the shortest Sleep is 1 ms, init() runs only once
	CMOS& cmos = CMOS::get();
	cmos.sleep_ms(1);
	
	
	//	Make sure that ADC is disabled before changing Configuration
	bit::clear(*MCU::ADC_1::CR, 0);
	
	
	//	ADC Clock: clock is the Maximum of the ADC Clock (fadc_ker_ck) as in the Datasheet (RM0433 Rev 9, ADC clocks)
	//	Revision V divides the Input Clock by 2 for the analog ADC and allows up to 50 MHz, Revision Y uses it directly and allows 36 MHz
	const bool revisionY = ((*MCU::DBGMCU::IDC >> 16) & 0x0000FFFF) == 0x1003;
	const uint32 divider_analog = (revisionY == true) ? 1 : 2;
	if(revisionY == true && clock > 36000000)
	{
		return(FAIL);
	}
	uint32 clock_in = 0;
	uint32 mask_PRESC = 0x0;
	uint32 mask_CKMODE = (uint32) clockSource;
	
	if(clockSource == e_clockSource::KERNEL)
	{
		uint32 clock_kernel = 0;
		switch(rcc.get_clockSource_adc())
		{
			case RCC::e_clockSource_adc::PLL_2_P:
				clock_kernel = rcc.get_clock_pll_2_p();
				break;
				
			case RCC::e_clockSource_adc::PLL_3_R:
				clock_kernel = rcc.get_clock_pll_3_r();
				break;
				
			case RCC::e_clockSource_adc::PERCK:
				clock_kernel = rcc.get_clock_perck();
				break;
				
			default:
				return(FAIL);
		}
		
		
		//	The smallest Prescaler that keeps the ADC Clock at or below clock - a slower Kernel Clock is used undivided
		uint32 i = 0;
		while(clock_kernel / c_prescaler[i] / divider_analog > clock)
		{
			i++;
			if(i >= 12)
			{
				return(FAIL);
			}
		}
		clock_in = clock_kernel / c_prescaler[i];
		mask_PRESC = i;
	}
	else
	{
		//	Synchronous Clock (CKMODE), divided by 1, 2 or 4 without the Prescaler, so it must not exceed the requested Maximum itself
		//	Revision V takes adc_sclk (sys_ck with the AHB Prescaler 1, otherwise sys_ck / 2), Revision Y the AHB Clock
		//	AHB_DIV_1 needs the AHB Prescaler 1, the Clock has a Duty Cycle of 50 % only then
		const uint32 clock_ahb = rcc.get_clock_ahb();
		const bool ahbPrescaler1 = (rcc.get_clock_core() == clock_ahb);
		uint32 clock_sync = clock_ahb;
		if(revisionY == false)
		{
			clock_sync = (ahbPrescaler1 == true) ? rcc.get_clock_system() : rcc.get_clock_system() / 2;
		}
		uint32 divider = 0;
		switch(clockSource)
		{
			case e_clockSource::AHB_DIV_1:
				if(ahbPrescaler1 == false)
				{
					return(FAIL);
				}
				divider = 1;
				break;
				
			case e_clockSource::AHB_DIV_2:
				divider = 2;
				break;
				
			case e_clockSource::AHB_DIV_4:
				divider = 4;
				break;
				
			default:
				return(FAIL);
		}
		clock_in = clock_sync / divider;
		if(clock_in / divider_analog > clock)
		{
			return(FAIL);
		}
		mask_PRESC = 0x0;
	}
	
	
	//	ADC_1 and ADC_2 share the Clock Configuration (ADC12_CCR): while ADC_2 is running, its Clock must not change
	if(bit::isSet(*MCU::ADC_2::CR, 0) == true && (*MCU::ADC_1_2_COMMON::CCR & 0x003F0000) != ((mask_PRESC << 18) | (mask_CKMODE << 16)))
	{
		return(FAIL);
	}
	uint32 temp = *MCU::ADC_1_2_COMMON::CCR & 0xFFC0FFFF;
	*MCU::ADC_1_2_COMMON::CCR = temp | (mask_PRESC << 18) | (mask_CKMODE << 16);
	m_clock = clock_in / divider_analog;
	
	
	//	Boost Mode for the ADC Clock (RM0433 Rev 9, ADC_CR BOOST): Revision V has two Bits for 6.25, 12.5, 25 and 50 MHz,
	//	Revision Y one Bit, required above 20 MHz
	uint32 mask_boost = 0x0;
	if(revisionY == true)
	{
		mask_boost = (m_clock > 20000000) ? 0x1 : 0x0;
	}
	else if(m_clock > 25000000)
	{
		mask_boost = 0x3;
	}
	else if(m_clock > 12500000)
	{
		mask_boost = 0x2;
	}
	else if(m_clock > 6250000)
	{
		mask_boost = 0x1;
	}
	temp = *MCU::ADC_1::CR & 0xFFFFFCFF;
	*MCU::ADC_1::CR = temp | (mask_boost << 8);
	
	
	//	Calibrate for Single Ended Input
	bit::clear(*MCU::ADC_1::CR, 30);
	
	
	//	Linearity Correction Calibration and Offset Calibration
	bit::set(*MCU::ADC_1::CR, 16);
	
	
	//	Start Calibration
	bit::set(*MCU::ADC_1::CR, 31);
	
	
	//	Wait for Calibration to finish, it runs with the ADC Clock configured above
	const uint64 timestampCalibration = cmos.get_timestamp();
	while(bit::isSet(*MCU::ADC_1::CR, 31))
	{
		if(cmos.getMilliSecondsSinceTimestamp(timestampCalibration) > 100)
		{
			return(FAIL);
		}
	}
	
	
	//	Configure all Channels in Single Ended Mode
	*MCU::ADC_1::DIFSEL = 0x00000000;
	
	
	//	Enable Auto Injected Queue
	bit::clear(*MCU::ADC_1::CFGR, 31);
	
	
	//	Preselect all Channels
	*MCU::ADC_1::PCSEL = 0x000FFFFF;
	
	
	//	ADC Resolution 16 Bit
	*MCU::ADC_1::CFGR &= 0xFFFFFFE3;
	
	
	//	Sampling Time 387,5 ADC Cycles + 1,5 ADC Cycles --> f = 111,11 kHz
	*MCU::ADC_1::SMPR1 = 0x36DB6DB6;
	*MCU::ADC_1::SMPR2 = 0x36DB6DB6;
	
	
	//	Sample all Channels
	*MCU::ADC_1::SQR1 = 0x0308100F;
	*MCU::ADC_1::SQR2 = 0x081C6144;
	*MCU::ADC_1::SQR3 = 0x0D30B289;
	*MCU::ADC_1::SQR4 = 0x000003CE;
	*MCU::ADC_1::JSQR = 0x9A48A003;
	
	
	//	Enable Auto Injected Group Conversion
	bit::set(*MCU::ADC_1::CFGR, 25);
	
	
	//	Enable Continious Mode
	bit::set(*MCU::ADC_1::CFGR, 13);
	
	
	//	ADC Circular DMA Mode
	bit::set(*MCU::ADC_1::CFGR, 1);
	bit::set(*MCU::ADC_1::CFGR, 0);
	
	
	//	DMA Multiplexing
	DMAMUX& dmamux = stm32h753bit6.get_dmamux();
	dmamux.map(DMAMUX::e_input::ADC_1_DMA, DMAMUX::e_output::DMA_1_CH0);
	
	
	//	DMA
	I_DMA& dma = stm32h753bit6.get_dma_1(0);
	if(cmos.mutex_lock(&dma) != OK)
	{
		return(FAIL);
	}
	if(dma.transfer((void*) MCU::ADC_1::DR, m_value, I_DMA::e_dataType::UINT16, I_DMA::e_dataType::UINT16, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, 16, I_DMA::e_priority::VERY_HIGH, false, callback) != OK)
	{
		cmos.mutex_unlock(&dma);
		return(FAIL);
	}
	
	
	//	Clear ADC Ready Flag
	bit::set(*MCU::ADC_1::ISR, 0);
	
	
	//	Enable ADC
	bit::set(*MCU::ADC_1::CR, 0);
	
	
	//	Wait for ADC to be ready
	const uint64 timestampReady = cmos.get_timestamp();
	while(bit::isCleared(*MCU::ADC_1::ISR, 0))
	{
		if(cmos.getMilliSecondsSinceTimestamp(timestampReady) > 100)
		{
			//	The ADC does not start: stop the DMA Channel and release it
			dma.reset();
			cmos.mutex_unlock(&dma);
			return(FAIL);
		}
	}
	
	
	//	Clear ADC Ready Flag (optional)
	bit::set(*MCU::ADC_1::ISR, 0);
	
	
	//	Start Regular Group Conversion
	bit::set(*MCU::ADC_1::CR, 2);
	
	
	return(OK);
}