#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback ADC_1::init(uint32 clock, uint16 valueBuffer[c_numberOfValues])
{
	//	Protect from unauthorized Access
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	init() runs once: while the ADC converts, its DMA Channel runs circularly. A second Call returns FAIL before it changes
	//	anything - otherwise it would reset the ADC and then fail at the busy Channel, and the Conversion would stop
	if(STM32F107RCT6::get().get_dma_1(0).is_busy() == true)
	{
		return(FAIL);
	}
	
	
	//	Reset ADC 1
	STM32F107RCT6& stm32f107rct6 = STM32F107RCT6::get();
	RCC& rcc = stm32f107rct6.get_rcc();
	rcc.module_reset(RCC::e_module::ADC_1);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::ADC_1, true);
	
	
	//	Value Buffer
	if(valueBuffer == nullptr)
	{
		return(FAIL);
	}
	m_value = valueBuffer;
	
	
	//	Clock
	uint32 clock_in = rcc.get_clock_apb2();
	if(clock > c_clock_max || clock_in / 8 > clock)
	{
		return(FAIL);
	}
	
	uint32 prescaler = 2;
	for(uint32 i = 0; i < 3; i++)
	{
		if(clock_in / prescaler > clock)
		{
			prescaler += 2;
		}
	}
	
	rcc.set_prescaler((RCC::e_prescaler_adc) ((prescaler / 2) - 1));
	m_clock = clock;
	
	
	//	Enable
	if(enable() == FAIL)
	{
		return(FAIL);
	}
	
	
	//	Calibrate
	if(calibrate() == FAIL)
	{
		return(FAIL);
	}
	
	
	//	Scan Mode enabled
	bit::set(*MCU::ADC_1::CR1, 8);
	
	
	//	Enable VREF_INT and Temperature Sensor
	bit::set(*MCU::ADC_1::CR2, 23);
	
	
	//	Enable DMA
	bit::set(*MCU::ADC_1::CR2, 8);
	
	
	//	Continuous Conversion
	bit::set(*MCU::ADC_1::CR2, 1);
	
	
	//  CH0-CH15
	*MCU::ADC_1::SQR1 = 0x00F7B9AC;
	*MCU::ADC_1::SQR2 = 0x16A4A0E6;
	*MCU::ADC_1::SQR3 = 0x0A418820;
	
	//	Sampling Time 239.5 Cycles: the Temperature Sensor and VREF_INT need 17.1µs (Datasheet, TS_temp and TS_vrefint), that is 239.5 Cycles at 14MHz
	*MCU::ADC_1::SMPR1 = 0x00FFFFFF;
	
	
	//	The regular Sequence has at most 16 Conversions, so CH16 (Temperature Sensor) and CH17 (VREF_INT) are converted as injected Group
	//	JAUTO converts it after each regular Sequence; with 4 injected Conversions (JL = 3) JDR1 belongs to JSQ1 ... JDR4 to JSQ4
	//	JSQ1 = CH16, JSQ2 = CH17, JSQ3 = CH16, JSQ4 = CH17 -> JDR1 = Temperature Sensor, JDR2 = VREF_INT
	*MCU::ADC_1::JSQR = (3 << 20) | (17 << 15) | (16 << 10) | (17 << 5) | 16;
	bit::set(*MCU::ADC_1::CR1, 10);
	*MCU::ADC_1::SMPR2 = 0x3FFFFFFF;
	
	
	//	DMA
	I_DMA& dma = stm32f107rct6.get_dma_1(0);
	if(cmos.mutex_lock(&dma) != OK)
	{
		return(FAIL);
	}
	if(dma.transfer((void*) MCU::ADC_1::DR, m_value, I_DMA::e_dataType::UINT16, I_DMA::e_dataType::UINT16, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, 16, I_DMA::e_priority::VERY_HIGH, false) != OK)
	{
		cmos.mutex_unlock(&dma);
		return(FAIL);
	}
	
	
	//	Start Conversion
	start();
	
	
	return(OK);
}