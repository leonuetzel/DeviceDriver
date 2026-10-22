#include "../Inc/stm32l010k8t6.hpp"





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
	
	
	//	Start Calibration
	bit::set(*MCU::ADC::CR, 31);
	
	
	//	Wait for Calibration to finish
	while(bit::isSet(*MCU::ADC::CR, 31))
	{
		
	}
	
	
	//	Store Calibration Factor
	m_calibrationFactor = *MCU::ADC::DR & 0x0000003F;
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback ADC::init(e_clockSource clockSource, uint16 valueBuffer[c_numberOfValues])
{
	//	Protect from unauthorized Access
	if(CMOS::get().mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	init() runs once: while the ADC converts, its DMA Channel runs circularly. A second Call returns FAIL before it changes
	//	anything - otherwise it would reset the ADC and then fail at the busy Channel, and the Conversion would stop
	if(STM32L010K8T6::get().get_dma(0).is_busy() == true)
	{
		return(FAIL);
	}
	
	
	//	Reset ADC
	STM32L010K8T6& stm32l010k8t6 = STM32L010K8T6::get();
	RCC& rcc = stm32l010k8t6.get_rcc();
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
		case e_clockSource::HSI_16:
		{
			clock = rcc.get_clock_HSI16();
		}
		break;
			
		case e_clockSource::APB2_DIV_2:
		{
			clock = rcc.get_clock_apb2() / 2;
		}
		break;
			
		case e_clockSource::APB2_DIV_4:
		{
			clock = rcc.get_clock_apb2() / 4;
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
	
	
	//	Select CH0-CH7, CH8, CH9 and CH17 (VREF_INT) for Conversion
	*MCU::ADC::CHSELR = 0x000203FF;
	
	
	//	Scan Direction from CH0 to CH17 (Upward Scan)
	bit::clear(*MCU::ADC::CFGR1, 2);
	
	
	//	Sampling Time for all Channels: VREF_INT needs at least 5 µs (Datasheet, TS_vrefint), so the shortest Setting that lasts 5 µs at the ADC Clock
	//	SMP 0 ... 7 = 1.5, 3.5, 7.5, 12.5, 19.5, 39.5, 79.5, 160.5 ADCCLK (RM0451, ADC_SMPR), here in half Cycles: 5 µs are clock / 100000 half Cycles
	//	@16MHz: 160.5 ADCCLK = 10 µs, a Conversion lasts (160.5 + 12.5) ADCCLK = 10.8 µs per Channel
	constexpr uint16 halfCycles[8] = {3, 7, 15, 25, 39, 79, 159, 321};
	uint32 sampleTime = 7;
	for(uint32 i = 0; i < 8; i++)
	{
		if(((uint32) halfCycles[i]) * 100000 >= m_clock)
		{
			sampleTime = i;
			break;
		}
	}
	*MCU::ADC::SMPR = sampleTime;
	
	
	//	Continious Conversion Mode
	bit::set(*MCU::ADC::CFGR1, 13);
	
	
	//	DMA Circular Mode
	bit::set(*MCU::ADC::CFGR1, 1);
	
	
	//	DMA Enable
	bit::set(*MCU::ADC::CFGR1, 0);
	
	
	//	DMA
	DMA& dma = stm32l010k8t6.get_dma(0);
	//	transfer() needs the Mutex of the Channel: it is locked and kept as long as the ADC runs
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(&dma) != OK)
	{
		return(FAIL);
	}
	dma.set_requestMapping(DMA::e_requestMapping::CH0_ADC);
	if(dma.transfer((void*) MCU::ADC::DR, m_value, I_DMA::e_dataType::UINT16, I_DMA::e_dataType::UINT16, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, c_numberOfValues, I_DMA::e_priority::VERY_HIGH, false) != OK)
	{
		cmos.mutex_unlock(&dma);
		return(FAIL);
	}
	
	
	//	Start Conversion
	bit::set(*MCU::ADC::CR, 2);
	
	
	return(OK);
}
