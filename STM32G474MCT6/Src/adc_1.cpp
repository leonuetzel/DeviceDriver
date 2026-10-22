#include "../Inc/stm32g474mct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

CODE_RAM void ADC_1::callback()
{
	ADC_1& adc_1 = STM32G474MCT6::get().get_adc_1();
	adc_1.m_value[16] = *MCU::ADC_1::JDR1;
	adc_1.m_value[17] = *MCU::ADC_1::JDR2;
	adc_1.m_value[18] = *MCU::ADC_1::JDR3;
}



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback ADC_1::enable()
{
	//	Exit Deep-Power-Down Mode
	bit::clear(*MCU::ADC_1::CR, 29);
	
	
	//	Enable ADC Internal Voltage Regulator and wait for t_adcvreg_stup (20us)
	bit::set(*MCU::ADC_1::CR, 28);
	CMOS::get().sleep_ms(1);
	
	
	//	Clear ADRDY Bit
	bit::set(*MCU::ADC_1::ISR, 0);
	
	
	//	Enable ADC by setting ADEN Bit and wait for ADRDY to be set
	//	ADEN set within 4 ADC Clock Cycles after the End of a Calibration is reset by the Calibration Logic (as ES0387 Rev 11, 2.11.1 describes for the L4 ADC), so it is set again
	bit::set(*MCU::ADC_1::CR, 0);
	while(bit::isCleared(*MCU::ADC_1::ISR, 0))
	{
		if(bit::isCleared(*MCU::ADC_1::CR, 0))
		{
			bit::set(*MCU::ADC_1::CR, 0);
		}
	}
	
	return(OK);
}


feedback ADC_1::disable()
{
	//	ADDIS Bit must only be accessed if ADEN = 1
	if(bit::isCleared(*MCU::ADC_1::CR, 0))
	{
		return(FAIL);
	}
	
	
	//	Check if regular ADC Conversion is ongoing and stop if so
	if(bit::isSet(*MCU::ADC_1::CR, 2))
	{
		bit::set(*MCU::ADC_1::CR, 4);
		while(bit::isSet(*MCU::ADC_1::CR, 4))
		{
			
		}
	}
	
	
	//	Check if injected ADC Conversion is ongoing and stop if so
	if(bit::isSet(*MCU::ADC_1::CR, 3))
	{
		bit::set(*MCU::ADC_1::CR, 5);
		while(bit::isSet(*MCU::ADC_1::CR, 5))
		{
			
		}
	}
	
	
	//	Disable ADC by setting ADDIS Bit
	bit::set(*MCU::ADC_1::CR, 1);
	
	
	//	Wait for ADC to be disabled
	while(bit::isSet(*MCU::ADC_1::CR, 0))
	{
		
	}
	
	
	//	Clear ADRDY Bit
	bit::clear(*MCU::ADC_1::ISR, 0);
	
	return(OK);
}







feedback ADC_1::calibrateForSingleEnded()
{
	//	Exit Deep-Power-Down Mode
	bit::clear(*MCU::ADC_1::CR, 29);
	
	
	//	Enable ADC Internal Voltage Regulator and wait for t_adcvreg_stup (20us)
	bit::set(*MCU::ADC_1::CR, 28);
	CMOS::get().sleep_ms(1);
	
	
	//	ADC and DMA must be disabled (ADEN = 0 and DMAEN = 0) for Calibration
	if(bit::isSet(*MCU::ADC_1::CR, 0) || bit::isSet(*MCU::ADC_1::CFGR1, 0))
	{
		return(FAIL);
	}
	
	
	//	Single Ended Calibration
	bit::clear(*MCU::ADC_1::CR, 30);
	
	
	//	Start Calibration
	bit::set(*MCU::ADC_1::CR, 31);
	
	
	//	Wait for Calibration to finish
	while(bit::isSet(*MCU::ADC_1::CR, 31))
	{
		
	}
	
	
	//	Store Calibration Factor
	m_calibrationFactor = *MCU::ADC_1::CALFACT & 0x0000007F;
	return(OK);
}


feedback ADC_1::calibrateForDifferential()
{
	//	Exit Deep-Power-Down Mode
	bit::clear(*MCU::ADC_1::CR, 29);
	
	
	//	Enable ADC Internal Voltage Regulator and wait for t_adcvreg_stup (20us)
	bit::set(*MCU::ADC_1::CR, 28);
	CMOS::get().sleep_ms(1);
	
	
	//	ADC and DMA must be disabled (ADEN = 0 and DMAEN = 0) for Calibration
	if(bit::isSet(*MCU::ADC_1::CR, 0) || bit::isSet(*MCU::ADC_1::CFGR1, 0))
	{
		return(FAIL);
	}
	
	
	//	Differential Calibration
	bit::set(*MCU::ADC_1::CR, 30);
	
	
	//	Start Calibration
	bit::set(*MCU::ADC_1::CR, 31);
	
	
	//	Wait for Calibration to finish
	while(bit::isSet(*MCU::ADC_1::CR, 31))
	{
		
	}
	
	
	//	Store Calibration Factor
	m_calibrationFactor = (*MCU::ADC_1::CALFACT & 0x007F0000) >> 16;
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback ADC_1::init(e_clockSource clockSource, uint16 valueBuffer[c_numberOfValues], uint8 prescalerIndex)
{
	//	Boundary Check
	if(prescalerIndex >= sizeof(c_prescaler) / sizeof(c_prescaler[0]))
	{
		return(FAIL);
	}
	
	
	//	Protect from unauthorized Access
	if(CMOS::get().mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	init() runs once: while the ADC converts, its DMA Channel runs circularly. A second Call returns FAIL before it changes
	//	anything - otherwise it would reset the ADC and then fail at the busy Channel, and the Conversion would stop
	if(STM32G474MCT6::get().get_dma_1(0).is_busy() == true)
	{
		return(FAIL);
	}
	
	
	//	Reset ADC
	STM32G474MCT6& stm32 = STM32G474MCT6::get();
	RCC& rcc = stm32.get_rcc();
	rcc.module_reset(RCC::e_module::ADC_1_2);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::ADC_1_2, true);
	
	
	//	Value Buffer
	if(valueBuffer == nullptr)
	{
		return(FAIL);
	}
	m_value = valueBuffer;
	
	
	//	Clock Source
	uint32 clock = 0;
	switch(clockSource)
	{
		//	The Prescaler acts on the asynchronous Clocks only (CKMODE = 00)
		case e_clockSource::PLL_P:
		{
			clock = rcc.get_clock_pll_p() / c_prescaler[prescalerIndex];
		}
		break;
		
		case e_clockSource::SYSTEM:
		{
			clock = rcc.get_clock_system() / c_prescaler[prescalerIndex];
		}
		break;
			
		case e_clockSource::AHB2_DIV_1:
		{
			//	Check for AHB 2 Prescaler to be set to 1 (RM0440 Rev. 9 - Chapter 7.2.11)
			if(rcc.get_clock_ahb() != rcc.get_clock_system())
			{
				return(FAIL);
			}
			clock = rcc.get_clock_ahb();
		}
		break;
			
		case e_clockSource::AHB2_DIV_2:
		{
			clock = rcc.get_clock_ahb() / 2;
		}
		break;
		
		case e_clockSource::AHB2_DIV_4:
		{
			clock = rcc.get_clock_ahb() / 4;
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	
	//	Clock Boundary Check
	PWR& pwr = stm32.get_pwr();
	switch(pwr.get_voltageScaling())
	{
		case PWR::e_voltageScaling::RANGE1_1V28:
		{
			if(clock < 140000 || clock > 42000000)
			{
				return(FAIL);
			}
		}
		break;
		
		case PWR::e_voltageScaling::RANGE1_1V2:
		{
			if(clock < 140000 || clock > 42000000)
			{
				return(FAIL);
			}
		}
		break;
		
		case PWR::e_voltageScaling::RANGE2_1V0:
		{
			if(clock < 140000 || clock > 26000000)
			{
				return(FAIL);
			}
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	
	//	Write Clock Source and Prescaler
	const uint32 temp = *MCU::ADC_1_2_COMMON::CCR & 0xFFC0FFFF;
	*MCU::ADC_1_2_COMMON::CCR = temp | (prescalerIndex << 18) | ((((uint32) clockSource) & 0x03) << 16);
	rcc.set_clockSource((RCC::e_clockSource_adc12) (((uint32) clockSource) >> 4));
	m_clock = clock;
	
	
	//	Calibrate
	if(calibrateForSingleEnded() != OK)
	{
		return(FAIL);
	}
	
	
	//	Enable
	if(enable() != OK)
	{
		return(FAIL);
	}
	
	
	//	Enable VREF_INT which is connected to ADC 1 CH18 (RM0440)
	bit::set(*MCU::ADC_1_2_COMMON::CCR, 22);
	
	
	//	Enable the Temperature Sensor which is connected to ADC 1 CH16
	bit::set(*MCU::ADC_1_2_COMMON::CCR, 23);
	
	
	//	Enable the VBAT Monitoring (VBAT / 3) which is connected to ADC 1 CH17
	bit::set(*MCU::ADC_1_2_COMMON::CCR, 24);
	
	
	//	Select CH0-CH15 for regular Conversions
	*MCU::ADC_1::SQR1 = ( 3 << 24) | ( 2 << 18) | ( 1 << 12) | ( 0 << 6) | (15 << 0);
	*MCU::ADC_1::SQR2 = ( 8 << 24) | ( 7 << 18) | ( 6 << 12) | ( 5 << 6) | ( 4 << 0);
	*MCU::ADC_1::SQR3 = (13 << 24) | (12 << 18) | (11 << 12) | (10 << 6) | ( 9 << 0);
	*MCU::ADC_1::SQR4 =																				 (15 << 6) | (14 << 0);
	
	
	//	Enable injected Conversions - this Bit needs to be cleared before the JSQR Register is written, because changing this Bit resets the JSQR Register
	bit::clear(*MCU::ADC_1::CFGR1, 31);
	
	
	//	Select CH16 (Temperature Sensor), CH17 (VBAT / 3) and CH18 (VREF_INT) for injected Conversions
	//	JSQ1 starts at Bit 9, JSQ2 at Bit 15 and JSQ3 at Bit 21, JL = 2 means 3 Conversions
	*MCU::ADC_1::JSQR = (18 << 21) | (17 << 15) | (16 << 9) | (2 << 0);
	
	
	//	Enable automatic injected Group Conversions after regular Group Conversions
	bit::set(*MCU::ADC_1::CFGR1, 25);
	
	
	//	Sampling Times: the internal Channels need at least 5 µs (Temperature Sensor, CH16), 12 µs (VBAT, CH17) and 4 µs (VREF_INT, CH18),
	//	so they get the longest Sampling Time of 640.5 ADCCLK (12 µs for VBAT up to 53 MHz ADC Clock), the other Channels 12.5 ADCCLK
	//	Time needed for a Conversion of all Channels:
	//	16 Channel @ 12.5 +  12.5 =  25 ADCCLK
	//	 3 Channel @ 12.5 + 640.5 = 653 ADCCLK
	//	Sum = 400 + 1959 = 2359 ADCCLK
	//	@20MHz ADC Clock => 1 ADCCLK = 50ns
	//	=> 2359 ADCCLK = 118µs => 8.48kHz
	*MCU::ADC_1::SMPR1 = (2 << 27) | (2 << 24) | (2 << 21) | (2 << 18) | (2 << 15) | (2 << 12) | (2 << 9) | (2 << 6) | (2 << 3) | (2 << 0);
	*MCU::ADC_1::SMPR2 = 						 (7 << 24) | (7 << 21) | (7 << 18) | (2 << 15) | (2 << 12) | (2 << 9) | (2 << 6) | (2 << 3) | (2 << 0);
	
	
	//	Continuous Conversion Mode
	bit::set(*MCU::ADC_1::CFGR1, 13);
	
	
	//	DMA Circular Mode
	bit::set(*MCU::ADC_1::CFGR1, 1);
	
	
	//	DMA Enable
	bit::set(*MCU::ADC_1::CFGR1, 0);
	
	
	//	DMA
	DMA_1& dma = stm32.get_dma_1(0);
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(&dma) != OK)
	{
		return(FAIL);
	}
	DMAMUX& dmamux = stm32.get_dmamux();
	dmamux.map(DMAMUX::e_input::ADC_1, DMAMUX::e_output::DMA_1_CH0);
	if(dma.transfer((void*) MCU::ADC_1::DR, m_value, I_DMA::e_dataType::UINT16, I_DMA::e_dataType::UINT16, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, 16, I_DMA::e_priority::VERY_HIGH, false, callback) != OK)
	{
		cmos.mutex_unlock(&dma);
		return(FAIL);
	}
	
	
	//	Start Conversion by setting ADSTART Bit (dont use the JADSTART Bit because of Auto-Injection Mode -> RM0394 Rev. 4 - Chapter 16.4.19)
	bit::set(*MCU::ADC_1::CR, 2);
	
	
	return(OK);
}