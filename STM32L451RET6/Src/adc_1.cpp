#include "../Inc/stm32l451ret6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

CODE_RAM void ADC_1::callback()
{
	ADC_1& adc_1 = STM32L451RET6::get().get_adc_1();
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
	
	
	//	Enable ADC by setting ADEN Bit
	bit::set(*MCU::ADC_1::CR, 0);
	
	
	//	Wait for ADRDY to be set
	while(bit::isCleared(*MCU::ADC_1::ISR, 0))
	{
		
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
	if(CMOS::get().semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Reset ADC
	STM32L451RET6& stm32 = STM32L451RET6::get();
	RCC& rcc = stm32.get_rcc();
	rcc.module_reset(RCC::e_module::ADC);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::ADC, true);
	
	
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
		case e_clockSource::SYSTEM_PLLSAI1:
		{
			clock = rcc.get_clock_adc();
		}
		break;
			
		case e_clockSource::AHB2_DIV_1:
		{
			//	Check for AHB 2 Prescaler to be set to 1 (RM0394 Rev. 4 - Chapter 6.2.12)
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
		case PWR::e_voltageScaling::RANGE1_1V2:
		{
			if(clock < 140000 || clock > 80000000)
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
		
		default:
		{
			return(FAIL);
		}
	}
	
	
	//	Write Clock Source and Prescaler
	const uint32 temp = *MCU::ADC_COMMON::CCR & 0xFFC0FFFF;
	*MCU::ADC_COMMON::CCR = temp | (prescalerIndex << 18) | (((uint32) clockSource) << 16);
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
	
	
	//	Enable VREF_INT which is connected to ADC 1 CH0
	bit::set(*MCU::ADC_COMMON::CCR, 22);
	
	
	//	Enable the Temperature Sensor which is connected to ADC 1 CH17
	bit::set(*MCU::ADC_COMMON::CCR, 23);
	
	
	//	Enable the VBAT Monitoring which is connected to ADC 1 CH18
	bit::set(*MCU::ADC_COMMON::CCR, 24);
	
	
	//	Select CH0 (VREF_INT) and CH1-CH15 (regular analog Pins) for regular Conversions
	*MCU::ADC_1::SQR1 = ( 3 << 24) | ( 2 << 18) | ( 1 << 12) | ( 0 << 6) | (15 << 0);
	*MCU::ADC_1::SQR2 = ( 8 << 24) | ( 7 << 18) | ( 6 << 12) | ( 5 << 6) | ( 4 << 0);
	*MCU::ADC_1::SQR3 = (13 << 24) | (12 << 18) | (11 << 12) | (10 << 6) | ( 9 << 0);
	*MCU::ADC_1::SQR4 =																				 (15 << 6) | (14 << 0);
	
	
	//	Enable injected Conversions - this Bit needs to be cleared before the JSQR Register is written, because changing this Bit resets the JSQR Register
	bit::clear(*MCU::ADC_1::CFGR1, 31);
	
	
	//	Select CH16 (regular analog Pin), CH17 (Temperature Sensor) and CH18 (VBAT Monitoring) for injected Conversions
	*MCU::ADC_1::JSQR = (18 << 20) | (17 << 14) | (16 << 8) | (2 << 0);
	
	
	//	Enable automatic injected Group Conversions after regular Group Conversions
	bit::set(*MCU::ADC_1::CFGR1, 25);
	
	
	//	Time needed for a Conversion of all Channels:
	//	17 Channel @ 12.5 +  12.5 =  25 ADCCLK
	//	 1 Channel @ 12.5 +  92.5 = 105 ADCCLK
	//	 1 Channel @ 12.5 + 247.5 = 260 ADCCLK
	//	Sum = 425 + 105 + 260 = 790 ADCCLK
	//	@20MHz ADC Clock => 1 ADCCLK = 50ns
	//	=> 790 ADCCLK = 39.5µs => 25.32kHz
	*MCU::ADC_1::SMPR1 = (2 << 27) | (2 << 24) | (2 << 21) | (2 << 18) | (2 << 15) | (2 << 12) | (2 << 9) | (2 << 6) | (2 << 3) | (2 << 0);
	*MCU::ADC_1::SMPR2 = 						 (6 << 24) | (5 << 21) | (2 << 18) | (2 << 15) | (2 << 12) | (2 << 9) | (2 << 6) | (2 << 3) | (2 << 0);
	
	
	//	Continuous Conversion Mode
	bit::set(*MCU::ADC_1::CFGR1, 13);
	
	
	//	DMA Circular Mode
	bit::set(*MCU::ADC_1::CFGR1, 1);
	
	
	//	DMA Enable
	bit::set(*MCU::ADC_1::CFGR1, 0);
	
	
	//	DMA
	DMA_1& dma = stm32.get_dma_1(0);
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_lock(&dma) != OK)
	{
		return(FAIL);
	}
	dma.set_requestMapping(DMA_1::e_requestMapping::CH0_ADC1);
	if(dma.transfer((void*) MCU::ADC_1::DR, m_value, I_DMA::e_dataType::UINT16, I_DMA::e_dataType::UINT16, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, 16, I_DMA::e_priority::VERY_HIGH, false, callback) != OK)
	{
		return(FAIL);
	}
	
	
	//	Start Conversion by setting ADSTART Bit (dont use the JADSTART Bit because of Auto-Injection Mode -> RM0394 Rev. 4 - Chapter 16.4.19)
	bit::set(*MCU::ADC_1::CR, 2);
	
	
	return(OK);
}