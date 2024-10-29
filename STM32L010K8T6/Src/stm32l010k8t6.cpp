#include "../Inc/stm32l010k8t6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

INTERRUPT_VECTOR const STM32L010K8T6::s_interruptTable STM32L010K8T6::c_interruptTable =
{
	(uint32) ISR_WWDG,                           																																									// 0x40 Window Watchdog
	(uint32) 0,                                  																																									// 0x44 Reserved
	(uint32) ISR_RTC,                            																																									// 0x48 RTC
	(uint32) ISR_FLASH,                          																																									// 0x4C Flash
	(uint32) ISR_RCC,                            																																									// 0x50 RCC
	(uint32) ISR_EXTI_0_TO_1,                    																																									// 0x54 External Interrupt 0 - 1
	(uint32) ISR_EXTI_2_TO_3,                    																																									// 0x58 External Interrupt 2 - 3
	(uint32) ISR_EXTI_4_TO_15,                   																																									// 0x5C External Interrupt 4 - 15
	(uint32) 0,                                  																																									// 0x60 Reserved
	(uint32) ISR_DMA_CH0,                        																																									// 0x64 DMA Channel 0
	(uint32) ISR_DMA_CH1_CH2,                    																																									// 0x68 DMA Channel 1 - 2
	(uint32) ISR_DMA_CH3_TO_CH6,                 																																									// 0x6C DMA Channel 3 - 6
	(uint32) ISR_ADC,                            																																									// 0x70 ADC
	(uint32) ISR_LP_TIMER_1,                     																																									// 0x74 Low Power Timer 1
	(uint32) 0,                                  																																									// 0x78 Reserved
	(uint32) ISR_TIMER_2,                        																																									// 0x7C Timer 2
	(uint32) 0,                                  																																									// 0x80 Reserved
	(uint32) 0,                                  																																									// 0x84 Reserved
	(uint32) 0,                                  																																									// 0x88 Reserved
	(uint32) 0,                                  																																									// 0x8C Reserved
	(uint32) ISR_TIMER_21,                       																																									// 0x90 Timer 21
	(uint32) 0,                                  																																									// 0x94 Reserved
	(uint32) 0,                                  																																									// 0x98 Reserved
	(uint32) ISR_I2C_1,                          																																									// 0x9C I2C 1
	(uint32) 0,                                  																																									// 0xA0 Reserved
	(uint32) ISR_SPI_1,                          																																									// 0xA4 SPI 1
	(uint32) 0,                                  																																									// 0xA8 Reserved
	(uint32) 0,                                  																																									// 0xAC Reserved
	(uint32) ISR_USART_2,                        																																									// 0xB0 USART 2
	(uint32) 0,                                  																																									// 0xB4 Reserved
	(uint32) 0,                                  																																									// 0xB8 Reserved
	(uint32) 0,                                  																																									// 0xBC Reserved
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void STM32L010K8T6::copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(dest + i) = *(src + i);
	}
}


void STM32L010K8T6::zeroOutRAM(uint32* startAddress, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(startAddress + i) = 0;
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

STM32L010K8T6& STM32L010K8T6::get()
{
	static STM32L010K8T6 stm32l010k8t6;
	return(stm32l010k8t6);
}









void EXCEPTION_RESET()
{
	//	External Symbols
	extern uint32 __memory_SRAM_start__;
	extern uint32 __memory_SRAM_size__;
	
	
	
	extern uint32 __cmos_data_flash_start__;
	extern uint32 __cmos_data_flash_size__;
	extern uint32 __cmos_data_ram_start__;
	
	extern uint32 __cmos_code_flash_start__;
	extern uint32 __cmos_code_flash_size__;
	extern uint32 __cmos_code_ram_start__;
	
	extern uint32 __cmos_heap_start__;
	extern uint32 __cmos_heap_size__;
	
	
	
	
	
	//	Convenience
	uint32* const				c_memory_SRAM_start	= (uint32*) &__memory_SRAM_start__;
	const uint32				c_memory_SRAM_size	= (uint32)  &__memory_SRAM_size__;
	
	
	
	const uint32* const	c_data_flash_start	= (uint32*) &__cmos_data_flash_start__;
	const uint32				c_data_flash_size		= (uint32)  &__cmos_data_flash_size__;
	uint32* const				c_data_ram_start		= (uint32*) &__cmos_data_ram_start__;
	
	const uint32* const	c_code_flash_start	= (uint32*) &__cmos_code_flash_start__;
	const uint32				c_code_flash_size		= (uint32)  &__cmos_code_flash_size__;
	uint32* const				c_code_ram_start		= (uint32*) &__cmos_code_ram_start__;
	
	const uint32* const	c_heap_start				= (uint32*) &__cmos_heap_start__;
	const uint32				c_heap_size					= (uint32)  &__cmos_heap_size__;
	
	
	
	
	
	//	Enable SRAM Clock in RCC
	bit::set(*MCU::RCC::AHB_ENR, 2);
	
	
	//	Zero Memories - IMPORTANT: Dont clear Stackpointer
	constexpr uint32 c_stackpointerMemoryInBytes = 128;
	STM32L010K8T6::zeroOutRAM(c_memory_SRAM_start, c_memory_SRAM_size - c_stackpointerMemoryInBytes);
	
	
	//	Set Stackpointer to reserved Stack Memory
	asm volatile
	(
		"msr msp, %[in_a]"
			:
			:	[in_a] "r" (c_heap_start + c_heap_size / 4)
			:
	);
	
	
	//	Zero Memory that couldnt be cleared before Stackpointer Moving
	STM32L010K8T6::zeroOutRAM(c_memory_SRAM_start + (c_memory_SRAM_size - c_stackpointerMemoryInBytes) / 4, c_stackpointerMemoryInBytes);
	
	
	//	Copy non-zero-initialized Variables to SRAM
	STM32L010K8T6::copy_flashToRAM(c_data_flash_start, c_data_ram_start, c_data_flash_size);
	
	
	//	Copy Code from Flash to SRAM
	STM32L010K8T6::copy_flashToRAM(c_code_flash_start, c_code_ram_start, c_code_flash_size);
	
	
	//	Start OS
	CMOS& cmos = CMOS::get();
	cmos.run();
	
	
	//	Reset if CMOS ever returns
	cmos.reset();
}





extern "C"
{
	void __dummyInterruptHandler__()
	{
		while(1)
		{
			
		}
	}
}

WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_WWDG();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RTC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FLASH();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RCC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_0_TO_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_2_TO_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_4_TO_15();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_CH1_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_CH3_TO_CH6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ADC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_TIMER_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_21();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USART_2();





uint32 __startup__()
{
	STM32L010K8T6& stm32l010k8t6 = STM32L010K8T6::get();
	if(stm32l010k8t6.startup() != OK)
	{
		return(0);
	}
	return(stm32l010k8t6.get_rcc().get_clock_system());
}