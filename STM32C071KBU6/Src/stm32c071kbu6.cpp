#include "../Inc/stm32c071kbu6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

INTERRUPT_VECTOR const STM32C071KBU6::s_interruptTable STM32C071KBU6::c_interruptTable =
{
	(uint32) ISR_WWDG,			                                                                                            					// 0x040 Window Watchdog
	(uint32) 0,                                                                                                        						// 0x044 Reserved
	(uint32) ISR_RTC,                                                                                                      				// 0x048 RTC
	(uint32) ISR_FLASH,                                                                                                         	// 0x04C Flash
	(uint32) ISR_RCC_CRS,                                                                                                       	// 0x050 RCC and CRS
	(uint32) ISR_EXTI_0_TO_1,                                                                                        							// 0x054 EXTI 0 to 1
	(uint32) ISR_EXTI_2_TO_3,                                                                                        							// 0x058 EXTI 2 to 3
	(uint32) ISR_EXTI_4_TO_15,                                                                                    								// 0x05C EXTI 4 to 15
	(uint32) ISR_USB,                                                                                                   					// 0x060 USB
	(uint32) ISR_DMA1_CH0,                                                                     																		// 0x064 DMA 1 Channel 0
	(uint32) ISR_DMA1_CH1_CH2,                                                                 																		// 0x068 DMA 1 Channel 1 & 2
	(uint32) ISR_DMA1_CH3_CH4_DMAMUX,                                                                       											// 0x06C DMA 1 Channel 3 & 4 and DMAMUX
	(uint32) ISR_ADC,                                                                          																		// 0x070 ADC
	(uint32) ISR_TIMER_1_BREAK_UPDATE_TRIGGER_COMMUTATION,                                     																		// 0x074 Timer 1 Break Update Trigger Commutation
	(uint32) ISR_TIMER_1_CAPTURE_COMPARE,                                                      																		// 0x078 Timer 1 Capture Compare
	(uint32) ISR_TIMER_2,                                                                                													// 0x07C Timer 2
	(uint32) ISR_TIMER_3,                                                                      																		// 0x080 Timer 3
	(uint32) 0,                                                                                																		// 0x084 Reserved
	(uint32) 0,		                                                                             																		// 0x088 Reserved
	(uint32) ISR_TIMER_14,                                                                     																		// 0x08C Timer 14
	(uint32) 0,                                                                                																		// 0x090 Reserved
	(uint32) ISR_TIMER_16,                                                                     																		// 0x094 Timer 16
	(uint32) ISR_TIMER_17,                                                                     																		// 0x098 Timer 17
	(uint32) ISR_I2C_1,                                                                        																		// 0x09C I2C 1
	(uint32) ISR_I2C_2,                                                                                														// 0x0A0 I2C 2
	(uint32) ISR_SPI_1,                                                                        																		// 0x0A4 SPI 1
	(uint32) ISR_SPI_2,                                                                                														// 0x0A8 SPI 2
	(uint32) ISR_USART_1,                                                                      																		// 0x0AC USART 1
	(uint32) ISR_USART_2,			                                                                 																		// 0x0B0 USART 2
	(uint32) 0,			                                                                           																		// 0x0B4 Reserved
	(uint32) 0,			                                                                           																		// 0x0B8 Reserved
	(uint32) 0                                                                                 																		// 0x0BC Reserved
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void STM32C071KBU6::copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(dest + i) = *(src + i);
	}
}


void STM32C071KBU6::zeroOutRAM(uint32* startAddress, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(startAddress + i) = 0;
	}
}


void STM32C071KBU6::preInit()
{
	typedef void (*f_void)();
	
	extern uint32 __preInitFunctionArray_start__;
	extern uint32 __preInitFunctionArray_size__;
	
	const uint32* start				= (uint32*)	&__preInitFunctionArray_start__;
	const uint32  sizeInBytes	= (uint32)	&__preInitFunctionArray_size__;
	
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		const uint32 jumpAddress = *(start + i);
		if(jumpAddress != 0 && jumpAddress != 0xFFFFFFFF)
		{
			f_void function = (f_void) jumpAddress;
			function();
		}
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

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
	
	
	
	
	
	//	Convenience
	uint32* const				c_memory_SRAM_start	= (uint32*) &__memory_SRAM_start__;
	const uint32				c_memory_SRAM_size	= (uint32)  &__memory_SRAM_size__;
	
	
	
	const uint32* const	c_data_flash_start	= (uint32*) &__cmos_data_flash_start__;
	const uint32				c_data_flash_size		= (uint32)  &__cmos_data_flash_size__;
	uint32* const				c_data_ram_start		= (uint32*) &__cmos_data_ram_start__;
	
	const uint32* const	c_code_flash_start	= (uint32*) &__cmos_code_flash_start__;
	const uint32				c_code_flash_size		= (uint32)  &__cmos_code_flash_size__;
	uint32* const				c_code_ram_start		= (uint32*) &__cmos_code_ram_start__;
	
	
	
	//	Zero Memories - IMPORTANT: Dont clear Stackpointer
	STM32C071KBU6::zeroOutRAM(c_memory_SRAM_start, c_memory_SRAM_size - 128);
	
	
	//	Copy non-zero-initialized Variables to SRAM
	STM32C071KBU6::copy_flashToRAM(c_data_flash_start, c_data_ram_start, c_data_flash_size);
	
	
	//	Copy Code from Flash to SRAM
	STM32C071KBU6::copy_flashToRAM(c_code_flash_start, c_code_ram_start, c_code_flash_size);
	
	
	//	Execute Functions that need to be executed before any Initialization has been done (Bootloader)
	STM32C071KBU6::preInit();
	
	
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RCC_CRS();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_0_TO_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_2_TO_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_4_TO_15();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH1_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH3_CH4_DMAMUX();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ADC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_BREAK_UPDATE_TRIGGER_COMMUTATION();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_CAPTURE_COMPARE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_14();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_16();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_17();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USART_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USART_2();





uint32 __startup__()
{
	STM32C071KBU6& stm32f107rct6 = STM32C071KBU6::get();
	if(stm32f107rct6.startup() != OK)
	{
		return(0);
	}
	return(stm32f107rct6.get_rcc().get_clock_system());
}