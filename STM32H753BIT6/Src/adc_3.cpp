#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

CODE_RAM void ADC_3::callback()
{
	/*
	Cache& cache = CMOS::get().get_cache();																																											//	Cache Maintenance
	cache.DCache_invalidate((uint32*) ADC_3::m_value, sizeof(ADC_3::m_value));
	*/
	ADC_3& adc_3 = STM32H753BIT6::get().get_adc_3();
	adc_3.m_value[16] = *MCU::ADC_3::JDR1;
	adc_3.m_value[17] = *MCU::ADC_3::JDR2;
	adc_3.m_value[18] = *MCU::ADC_3::JDR3;
	adc_3.m_value[19] = *MCU::ADC_3::JDR4;
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback ADC_3::init(uint32 clock, uint16 valueBuffer[c_valueBufferSize], e_clockSource clockSource)
{
	//	Protect from unauthorized Access
	if(CMOS::get().semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Check Clock
	if(clock > c_clock_max)
	{
		return(FAIL);
	}
	
	
	//	Reset ADC 3
	STM32H753BIT6& stm32h753bit6 = STM32H753BIT6::get();
	RCC& rcc = stm32h753bit6.get_rcc();
	rcc.module_reset(RCC::e_module::ADC_3);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::ADC_3, true);
	
	
	//	Value Buffer
	if(valueBuffer == nullptr)
	{
		return(FAIL);
	}
	m_value = valueBuffer;
	
	
	//	Voltage Reference
	VREFBUF& vrefbuf = stm32h753bit6.get_vrefbuf();
	if(vrefbuf.set_mode(VREFBUF::e_mode::EXTERNAL) != OK)
	{
		return(FAIL);
	}
	
	
	//	Stop Deep Power Down Mode
	bit::clear(*MCU::ADC_3::CR, 29);
	
	
	//	Enable Internal Voltage Regulator
	bit::set(*MCU::ADC_3::CR, 28);
	
	
	//	Wait 10us for Internal Voltage Regulator to Start up
	CMOS& cmos = CMOS::get();
	cmos.sleep_100us(1);
	
	
	//	Make sure, ADC is disabled before changing Configuration
	bit::clear(*MCU::ADC_3::CR, 0);
	
	
	//	Calibrate in Single Ended Mode
	bit::clear(*MCU::ADC_3::CR, 30);
	
	
	//	Calibrate with Linearity Calibration
	bit::set(*MCU::ADC_3::CR, 16);
	
	
	//	Start Calibration
	bit::set(*MCU::ADC_3::CR, 31);
	
	
	//	Wait for Calibration to finish
	while(bit::isSet(*MCU::ADC_3::CR, 31))
	{
		
	}
	
	
	//	ADC Clock
	uint32 clock_in = 0;
	uint32 mask_PRESC = 0x0;
	uint32 mask_CKMODE = (uint32) clockSource;
	
	if(clockSource == e_clockSource::KERNEL)
	{
		uint32 clock_kernel = 0;
		
		RCC::e_clockSource_adc kernel_clock = rcc.get_clockSource_adc();
		
		switch(kernel_clock)
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
		
		if(clock_kernel < clock)
		{
			return(FAIL);
		}
		
		uint32 i = 0;
		while(clock_kernel / c_prescaler[i] > clock)
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
	
	if(clockSource == e_clockSource::AHB_DIV_1)
	{
		uint32 clock_core = rcc.get_clock_core();
		uint32 clock_ahb = rcc.get_clock_ahb();
		if(clock_core / clock_ahb != 1)
		{
			return(FAIL);
		}
		if(clock_ahb < clock)
		{
			return(FAIL);
		}
		
		clock_in = clock_ahb;
		mask_PRESC = 0x0;
	}
	
	if(clockSource == e_clockSource::AHB_DIV_2)
	{
		uint32 clock_ahb = rcc.get_clock_ahb();
		if(clock_ahb / 2 < clock)
		{
			return(FAIL);
		}
		
		clock_in = clock_ahb / 2;
		mask_PRESC = 0x0;
	}
	
	if(clockSource == e_clockSource::AHB_DIV_4)
	{
		uint32 clock_ahb = rcc.get_clock_ahb();
		if(clock_ahb / 4 < clock)
		{
			return(FAIL);
		}
		
		clock_in = clock_ahb / 4;
		mask_PRESC = 0x0;
	}
	
	uint32 temp = *MCU::ADC_3::COMMON::CCR & 0xFFC0FFFF;
	*MCU::ADC_3::COMMON::CCR = temp | (mask_PRESC << 18) | (mask_CKMODE << 16);
	m_clock = clock_in;
	
	
	//	Enter Boost Mode depending on Frequency
	uint32 mask_boost = 0x0;
	if(m_clock <= 6250000)
	{
		mask_boost = 0x0;
	}
	else
	{
		if(m_clock <= 12500000)
		{
			mask_boost = 0x1;
		}
		else
		{
			if(m_clock <= 25000000)
			{
				mask_boost = 0x2;
			}
			else
			{
				mask_boost = 0x3;
			}
		}
	}
	temp = *MCU::ADC_3::CR & 0xFFFFFCFF;
	*MCU::ADC_3::CR = temp | (mask_boost << 8);
	
	
	//	Calibrate for Single Ended Input
	bit::clear(*MCU::ADC_3::CR, 30);
	
	
	//	Linearity Correction Calibration and Offset Calibration
	bit::set(*MCU::ADC_3::CR, 16);
	
	
	//	Start Calibration
	bit::set(*MCU::ADC_3::CR, 31);
	
	
	//	Wait for Calibration to finish
	while(bit::isSet(*MCU::ADC_3::CR, 31))
	{
		
	}
	
	
	//	Configure all Channels in Single Ended Mode
	*MCU::ADC_3::DIFSEL = 0x00000000;
	
	
	//	VBAT Enable
	bit::set(*MCU::ADC_3::COMMON::CCR, 24);
	
	
	//	Temperature Sensor Enable
	bit::set(*MCU::ADC_3::COMMON::CCR, 23);
	
	
	//	Internal Reference Voltage Enable
	bit::set(*MCU::ADC_3::COMMON::CCR, 22);
	
	
	//	Enable Auto Injected Queue
	bit::clear(*MCU::ADC_3::CFGR, 31);
	
	
	//	Preselect all Channels
	*MCU::ADC_3::PCSEL = 0x000FFFFF;
	
	
	//	ADC Resolution 16 Bit
	*MCU::ADC_3::CFGR &= 0xFFFFFFE3;
	
	
	//	Sampling Time 387,5 ADC Cycles + 1,5 ADC Cycles --> f = 111,11 kHz
	*MCU::ADC_3::SMPR1 = 0x36DB6DB6;
	*MCU::ADC_3::SMPR2 = 0x36DB6DB6;
	
	
	//	Sample all Channels
	*MCU::ADC_3::SQR1 = 0x0308100F;
	*MCU::ADC_3::SQR2 = 0x081C6144;
	*MCU::ADC_3::SQR3 = 0x0D30B289;
	*MCU::ADC_3::SQR4 = 0x000003CE;
	*MCU::ADC_3::JSQR = 0x9A48A003;
	
	
	//	Enable Auto Injected Group Conversion
	bit::set(*MCU::ADC_3::CFGR, 25);
	
	
	//	Enable Continious Mode
	bit::set(*MCU::ADC_3::CFGR, 13);
	
	
	//	ADC Circular DMA Mode
	bit::set(*MCU::ADC_3::CFGR, 1);
	bit::set(*MCU::ADC_3::CFGR, 0);
	
	
	//	DMA Multiplexing
	DMAMUX& dmamux = stm32h753bit6.get_dmamux();
	dmamux.map(DMAMUX::e_input::ADC_3_DMA, DMAMUX::e_output::DMA_1_CH2);
	
	
	//	DMA
	I_DMA& dma = stm32h753bit6.get_dma_1(2);
	if(cmos.semaphore_lock(&dma) != OK)
	{
		return(FAIL);
	}
	if(dma.transfer((void*) MCU::ADC_3::DR, m_value, I_DMA::e_dataType::UINT16, I_DMA::e_dataType::UINT16, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, 16, I_DMA::e_priority::VERY_HIGH, false, callback) != OK)
	{
		return(FAIL);
	}
	
	
	//	Clear ADC Ready Flag
	bit::set(*MCU::ADC_3::ISR, 0);
	
	
	//	Enable ADC
	bit::set(*MCU::ADC_3::CR, 0);
	
	
	//	Wait for ADC to be ready
	while(bit::isCleared(*MCU::ADC_3::ISR, 0))
	{
		
	}
	
	
	//	Clear ADC Ready Flag (optional)
	bit::set(*MCU::ADC_3::ISR, 0);
	
	
	//	Start Regular Group Conversion
	bit::set(*MCU::ADC_3::CR, 2);
	
	
	return(OK);
}