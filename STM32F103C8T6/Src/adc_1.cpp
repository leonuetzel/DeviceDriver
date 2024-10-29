#include "../Inc/stm32f103c8t6.hpp"





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
	if(cmos.semaphore_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	
	
	//	Reset ADC 1
	STM32F103C8T6& stm32f103c8t6 = STM32F103C8T6::get();
	RCC& rcc = stm32f103c8t6.get_rcc();
	rcc.module_reset(RCC::e_module::ADC);
	
	
	//	Enable Clock
	rcc.module_clockInit(RCC::e_module::ADC, true);
	
	
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
	
	
	//  CH0-CH9, CH10 (Temperature Sensor) and CH11 (VREF_INT)
	*MCU::ADC_1::SQR1 = 0x00B00000;
	*MCU::ADC_1::SQR2 = 0x2304A0E6;
	*MCU::ADC_1::SQR3 = 0x0A418820;
	
	*MCU::ADC_1::SMPR1 = 0x006C0000;
	*MCU::ADC_1::SMPR2 = 0x3FFFFFFF;
	
	
	//	DMA
	I_DMA& dma = stm32f103c8t6.get_dma(0);
	if(cmos.semaphore_lock(&dma) != OK)
	{
		return(FAIL);
	}
	if(dma.transfer((void*) MCU::ADC_1::DR, m_value, I_DMA::e_dataType::UINT16, I_DMA::e_dataType::UINT16, false, true, I_DMA::e_direction::PERIPHERAL_TO_MEMORY, true, c_numberOfValues, I_DMA::e_priority::VERY_HIGH, false) != OK)
	{
		return(FAIL);
	}
	
	
	//	Start Conversion
	start();
	
	
	return(OK);
}