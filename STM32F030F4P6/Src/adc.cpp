#include "../Inc/stm32f030f4p6.hpp"





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
	if(CMOS::get().semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Reset ADC
	STM32F030F4P6& stm32f030f4p6 = STM32F030F4P6::get();
	RCC& rcc = stm32f030f4p6.get_rcc();
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
		case e_clockSource::HSI_14:
		{
			clock = RCC::c_clock_hsi_14;
		}
		break;
		
		case e_clockSource::AHB_DIV_2:
		{
			clock = rcc.get_clock_ahb() / 2;
		}
		break;
		
		case e_clockSource::AHB_DIV_4:
		{
			clock = rcc.get_clock_ahb() / 4;
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
	
	
	//	Enable Temperature Sensor
	bit::set(*MCU::ADC::CCR, 23);
	
	
	//	Select CH0-CH7, CH9, CH16 (Temperature Sensor) and CH17 (VREF_INT) for Conversion
	*MCU::ADC::CHSELR = 0x000302FF;
	
	
	//	Scan Direction from CH0 to CH17 (Upward Scan)
	bit::clear(*MCU::ADC::CFGR1, 2);
	
	
	//	Sampling Time: (7.5 + 12.5) ADCCLK = 20 ADCCLK => @12MHz => 600kHz / Channel 
	*MCU::ADC::SMPR = 0x00000001;
	
	
	//	Continious Conversion Mode
	bit::set(*MCU::ADC::CFGR1, 13);
	
	
	//	DMA Circular Mode
	bit::set(*MCU::ADC::CFGR1, 1);
	
	
	//	DMA Enable
	bit::set(*MCU::ADC::CFGR1, 0);
	
	
	//	DMA
	I_DMA& dma = stm32f030f4p6.get_dma(0);
	dma.transfer((void*) MCU::ADC::DR, m_value, I_DMA::e_dataType::UINT16, I_DMA::e_dataType::UINT16, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, c_numberOfValues, I_DMA::e_priority::VERY_HIGH, false); 
	
	
	//	Start Conversion
	bit::set(*MCU::ADC::CR, 2);
	
	
	return(OK);
}