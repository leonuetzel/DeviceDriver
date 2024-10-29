#include "../Inc/stm32c031k6u6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback ADC::enable()
{
	//	Clear ADRDY Bit
	bit::set(*MCU::ADC::ISR, 0);
	
	
	//	Enable ADC
	bit::set(*MCU::ADC::CR, 0);
	
	
	//	Wait for ADRDY to be set
	while(bit::isCleared(*MCU::ADC::ISR, 0))
	{
		
	}
	
	return(OK);
}


feedback ADC::disable()
{
	//	ADSTART and ADDIS Bits must only be accessed if ADEN = 1 and ADDIS = 0
	if(bit::isCleared(*MCU::ADC::CR, 0) || bit::isSet(*MCU::ADC::CR, 1))
	{
		return(FAIL);
	}
	
	
	//	Check if ADC operating and stop if so
	if(bit::isSet(*MCU::ADC::CR, 2))
	{
		bit::set(*MCU::ADC::CR, 4);
		while(bit::isSet(*MCU::ADC::CR, 4))
		{
			
		}
	}
	
	
	//	Disable ADC
	bit::set(*MCU::ADC::CR, 1);
	
	
	//	Wait for ADC to be disabled
	while(bit::isSet(*MCU::ADC::CR, 0))
	{
		
	}
	
	
	//	Clear ADRDY Bit
	bit::clear(*MCU::ADC::ISR, 0);
	
	return(OK);
}







feedback ADC::calibrate()
{
	//	ADC and DMA must be disabled (ADEN = 0 and DMAEN = 0) for Calibration
	if(bit::isSet(*MCU::ADC::CR, 0) || bit::isSet(*MCU::ADC::CFGR1, 0))
	{
		return(FAIL);
	}
	
	
	//	ADC Voltage Regulator must be enabled and Auto-Off Mode must be disabled
	if(bit::isCleared(*MCU::ADC::CR, 28) == true || bit::isSet(*MCU::ADC::CFGR1, 15) == true)
	{
		return(FAIL);
	}
	
	
	//	Start Calibration
	bit::set(*MCU::ADC::CR, 31);
	
	
	//	Wait for Calibration to finish
	while(bit::isSet(*MCU::ADC::CR, 31))
	{
		
	}
	
	
	//	Store Calibration Factor
	m_calibrationFactor = *MCU::ADC::DR & 0x0000007F;
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback ADC::init(e_clockSource clockSource, uint16 valueBuffer[c_numberOfValues])
{
	//	Protect from unauthorized Access
	if(CMOS::get().semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Reset ADC
	STM32C031K6U6& stm32 = STM32C031K6U6::get();
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
		case e_clockSource::KERNEL:
		{
			clock = rcc.get_clock_adc();
		}
		break;
			
		case e_clockSource::APB_DIV_2:
		{
			clock = rcc.get_clock_apb() / 2;
		}
		break;
			
		case e_clockSource::APB_DIV_4:
		{
			clock = rcc.get_clock_apb() / 4;
		}
		break;
		
		case e_clockSource::APB:
		{
			clock = rcc.get_clock_apb();
		}
		break;
		
		default:
		{
			return(FAIL);
		}
	}
	
	
	//	Clock
	if(clock > c_clock_max)
	{
		return(FAIL);
	}
	uint32 temp = *MCU::ADC::CFGR2 & 0x3FFFFFFF;
	*MCU::ADC::CFGR2 = temp | (((uint32) clockSource) << 30);
	m_clock = clock;
	
	
	//	Startup ADC Voltage Regulator
	bit::set(*MCU::ADC::CR, 28);
	CMOS::get().sleep_ms(1);
	
	
	//	Calibrate
	if(calibrate() == FAIL)
	{
		return(FAIL);
	}
	
	
	//	Enable
	if(enable() == FAIL)
	{
		return(FAIL);
	}
	
	
	//	Enable VREF_INT
	bit::set(*MCU::ADC::CCR, 22);
	
	
	//	Enable Temperature Sensor
	bit::set(*MCU::ADC::CCR, 23);
	
	
	//	Select CH0-CH8, CH9 (Temperature Sensor), CH10 (VREF_INT), CH11-CH14, CH15 (VCC_A), CH16 (GND_A) and CH17-CH19 for Conversion
	bit::clear(*MCU::ADC::CFGR1, 21);
	*MCU::ADC::CHSELR = 0x000FFFFF;
	
	
	//	Scan Direction from CH0 to CH19 (Upward Scan)
	bit::clear(*MCU::ADC::CFGR1, 2);
	
	
	//	Sampling Time
	//	1 ADCCLK = 1 / 24MHz = 41.67ns
	//	Temperature Sensor needs	>5µs Sample Time	=> 5µs / 41.67ns = min. 120 ADCCLK
	//	VREF_INT needs						>4µs Sample Time	=> 4µs / 41.67ns = min.  96 ADCCLK
	//	Sampling Time per Channel is (12.5 + x) ADCCLK
	//	=> Slow Sampling Time will be (160.5 + 12.5) ADCCLK = 173 ADCCLK = 7.21µs
	//	=> Fast Sampling Time will be (  1.5 + 12.5) ADCCLK =  14 ADCCLK = 583ns
	//	Slow Sampling Time: CH9 and CH10				=> 2 Channels
	//	Fast Sampling Time: CH0-CH8, CH1-CH19		=> 18 Channels
	//	Sample Time needed to measure all Channels one Time: 2 x 7.21µs + 18 x 583ns = 14.42µs + 10.5µs = 24.92µs
	//	Sample Rate: 1 / 24.92µs = 40.1kHz
	*MCU::ADC::SMPR = 0x00060000 | (0x7 << 4) | (0x0 << 0);
	
	
	//	Continuous Conversion Mode
	bit::set(*MCU::ADC::CFGR1, 13);
	
	
	//	DMA Circular Mode
	bit::set(*MCU::ADC::CFGR1, 1);
	
	
	//	DMA Enable
	bit::set(*MCU::ADC::CFGR1, 0);
	
	
	//	DMA Multiplexing
	DMAMUX& dmamux = stm32.get_dmamux();
	dmamux.map(DMAMUX::e_input::ADC_DMA, DMAMUX::e_output::DMA_CH0);
	
	
	//	DMA
	DMA& dma = stm32.get_dma(0);
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_lock(&dma) != OK)
	{
		return(FAIL);
	}
	if(dma.transfer((void*) MCU::ADC::DR, m_value, I_DMA::e_dataType::UINT16, I_DMA::e_dataType::UINT16, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, c_numberOfValues, I_DMA::e_priority::VERY_HIGH, false) != OK)
	{
		return(FAIL);
	} 
	
	
	//	Start Conversion
	bit::set(*MCU::ADC::CR, 2);
	
	
	return(OK);
}