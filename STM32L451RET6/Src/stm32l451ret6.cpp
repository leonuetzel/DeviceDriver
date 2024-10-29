#include "../Inc/stm32l451ret6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

INTERRUPT_VECTOR const STM32L451RET6::s_interruptTable STM32L451RET6::c_interruptTable =
{
	(uint32) ISR_WWDG,                           																																									// 0x040 Window Watchdog
	(uint32) ISR_PVM,                                  																																						// 0x044 PVD/PVM1/PVM2/PMV3/PMV4 through EXTI 16/35/36/37/38
	(uint32) ISR_RTC_TAMPER_STAMP_CSS_LSE,                            																														// 0x048 RTC Tamper/Timestamp or CSS on LSE through EXTI 19
	(uint32) ISR_WKUP,                          																																									// 0x04C RTC WKUP
	(uint32) ISR_FLASH,                            																																								// 0x050 Flash
	(uint32) ISR_RCC,                    																																													// 0x054 RCC
	(uint32) ISR_EXTI_0,                    																																											// 0x058 External Interrupt 0
	(uint32) ISR_EXTI_1,                   																																												// 0x05C External Interrupt 1
	(uint32) ISR_EXTI_2,                                  																																				// 0x060 External Interrupt 2
	(uint32) ISR_EXTI_3,                        																																									// 0x064 External Interrupt 3
	(uint32) ISR_EXTI_4,                    																																											// 0x068 External Interrupt 4
	(uint32) ISR_DMA_1_CH0,                 																																											// 0x06C DMA 1 CH0
	(uint32) ISR_DMA_1_CH1,                            																																						// 0x070 DMA 1 CH1
	(uint32) ISR_DMA_1_CH2,                     																																									// 0x074 DMA 1 CH2
	(uint32) ISR_DMA_1_CH3,                                  																																			// 0x078 DMA 1 CH3
	(uint32) ISR_DMA_1_CH4,                        																																								// 0x07C DMA 1 CH4
	(uint32) ISR_DMA_1_CH5,                                  																																			// 0x080 DMA 1 CH5
	(uint32) ISR_DMA_1_CH6,                                  																																			// 0x084 DMA 1 CH6
	(uint32) ISR_ADC_1_2,                                  																																				// 0x088 ADC 1 & 2
	(uint32) ISR_CAN_1_TX,                                  																																			// 0x08C CAN 1 Tx
	(uint32) ISR_CAN_1_RX0,                       																																								// 0x090 CAN 1 RX 0
	(uint32) ISR_CAN_1_RX1,                                  																																			// 0x094 CAN 1 RX 1
	(uint32) ISR_CAN_1_SCE,                                  																																			// 0x098 CAN 1 SCE
	(uint32) ISR_EXTI_9_TO_5,                          																																						// 0x09C External Interrupt 5 - 9
	(uint32) ISR_TIMER_1_BREAK_TIMER_15,                                  																												// 0x0A0 Timer 1 Break & Timer 15
	(uint32) ISR_TIMER_1_UPDATE_TIMER_16,                          																																// 0x0A4 Timer 1 Update & Timer 16
	(uint32) ISR_TIMER_1_TRIGGER_COMMUTATION,                                  																										// 0x0A8 Timer 1 Trigger & Commutation
	(uint32) ISR_TIMER_1_CAPTURE_COMPARE,                                  																												// 0x0AC Timer 1 Capture Compare
	(uint32) ISR_TIMER_2,                        																																									// 0x0B0 Timer 2
	(uint32) ISR_TIMER_3,                                  																																				// 0x0B4 Timer 3
	(uint32) 0,                                  																																									// 0x0B8 Reserved
	(uint32) ISR_I2C_1_EVENT,                                  																																		// 0x0BC I2C 1 Event
	(uint32) ISR_I2C_1_ERROR,                                  																																		// 0x0C0 I2C 1 Error
	(uint32) ISR_I2C_2_EVENT,                                  																																		// 0x0C4 I2C 2 Event
	(uint32) ISR_I2C_2_ERROR,                                  																																		// 0x0C8 I2C 2 Error
	(uint32) ISR_SPI_1,                                  																																					// 0x0CC SPI 1
	(uint32) ISR_SPI_2,                                  																																					// 0x0D0 SPI 2
	(uint32) ISR_USART_1,                                  																																				// 0x0D4 USART 1
	(uint32) ISR_USART_2,                                  																																				// 0x0D8 USART 2
	(uint32) ISR_USART_3,                                  																																				// 0x0DC USART 3
	(uint32) ISR_EXTI_15_TO_10,                                  																																	// 0x0E0 External Interrupt 10 - 15
	(uint32) ISR_RTC_ALARM,                                  																																			// 0x0E4 RTC Alarm
	(uint32) 0,                                  																																									// 0x0E8 Reserved
	(uint32) 0,                                  																																									// 0x0EC Reserved
	(uint32) 0,                                  																																									// 0x0F0 Reserved
	(uint32) 0,                                  																																									// 0x0F4 Reserved
	(uint32) 0,                                  																																									// 0x0F8 Reserved
	(uint32) 0,                                  																																									// 0x0FC Reserved
	(uint32) 0,                                  																																									// 0x100 Reserved
	(uint32) ISR_SDMMC_1,                                  																																				// 0x104 SDMMC 1
	(uint32) 0,                                  																																									// 0x108 Reserved
	(uint32) ISR_SPI_3,                                  																																					// 0x10C SPI 3
	(uint32) ISR_UART_4,                                  																																				// 0x110 UART 4
	(uint32) 0,                                  																																									// 0x114 Reserved
	(uint32) ISR_TIMER_6_DAC_UNDERRUN,                                  																													// 0x118 Timer 6 DAC Underrun
	(uint32) 0,                                  																																									// 0x11C Reserved
	(uint32) ISR_DMA_2_CH0,                                  																																			// 0x120 DMA 2 CH0
	(uint32) ISR_DMA_2_CH1,                                  																																			// 0x124 DMA 2 CH1
	(uint32) ISR_DMA_2_CH2,                                  																																			// 0x128 DMA 2 CH2
	(uint32) ISR_DMA_2_CH3,                                  																																			// 0x12C DMA 2 CH3
	(uint32) ISR_DMA_2_CH4,                                  																																			// 0x130 DMA 2 CH4
	(uint32) ISR_DFSDM_1_FLT_0,                                  																																	// 0x134 DFSDM 1 FLT 0
	(uint32) ISR_DFSDM_1_FLT_1,                                  																																	// 0x138 DFSDM 1 FLT 1
	(uint32) 0,                                  																																									// 0x13C Reserved
	(uint32) ISR_COMP,                                  																																					// 0x140 Comparator
	(uint32) ISR_LP_TIMER_1,                                  																																		// 0x144 Low Power Timer 1
	(uint32) ISR_LP_TIMER_2,                                  																																		// 0x148 Low Power Timer 2
	(uint32) 0,                                  																																									// 0x14C Reserved
	(uint32) ISR_DMA_2_CH5,                                  																																			// 0x150 DMA 2 CH5
	(uint32) ISR_DMA_2_CH6,                                  																																			// 0x154 DMA 2 CH6
	(uint32) ISR_LPUART_1,                                  																																			// 0x158 Low Power UART 1
	(uint32) ISR_QUADSPI,                                  																																				// 0x15C QUADSPI
	(uint32) ISR_I2C_3_EVENT,                                  																																		// 0x160 I2C 3 Event
	(uint32) ISR_I2C_3_ERROR,                                  																																		// 0x164 I2C 3 Error
	(uint32) ISR_SAI_1,                                  																																					// 0x168 Serial Audio Interface 1
	(uint32) 0,                                  																																									// 0x16C Reserved
	(uint32) 0,                                  																																									// 0x170 Reserved
	(uint32) ISR_TSC,                                  																																						// 0x174 Touch Sense Controller
	(uint32) 0,                                  																																									// 0x178 Reserved
	(uint32) 0,                                  																																									// 0x17C Reserved
	(uint32) ISR_RNG,                                  																																						// 0x180 Random Number Generator
	(uint32) ISR_FPU,                                  																																						// 0x184 FPU
	(uint32) ISR_CRS,                                  																																						// 0x188 Clock Recovery System
	(uint32) ISR_I2C_4_EVENT,                                  																																		// 0x18C I2C 4 Event
	(uint32) ISR_I2C_4_ERROR,                                  																																		// 0x190 I2C 4 Error
	(uint32) 0,                                  																																									// 0x194 Reserved
	(uint32) 0,                                  																																									// 0x198 Reserved
	(uint32) 0,                                  																																									// 0x19C Reserved
	(uint32) 0,                                  																																									// 0x1A0 Reserved
	(uint32) 0,                                  																																									// 0x1A4 Reserved
	(uint32) 0,                                  																																									// 0x1A8 Reserved
	(uint32) 0,                                  																																									// 0x1AC Reserved
	(uint32) 0,                                  																																									// 0x1B0 Reserved
	(uint32) 0,                                  																																									// 0x1B4 Reserved
	(uint32) 0,                                  																																									// 0x1B8 Reserved
	(uint32) 0,                                  																																									// 0x1BC Reserved
	(uint32) 0,                                  																																									// 0x1C0 Reserved
	(uint32) 0,                                  																																									// 0x1C4 Reserved
	(uint32) 0,                                  																																									// 0x1C8 Reserved
	(uint32) 0,                                  																																									// 0x1CC Reserved
	(uint32) 0,                                  																																									// 0x1D0 Reserved
	(uint32) 0,                                  																																									// 0x1D4 Reserved
	(uint32) 0,                                  																																									// 0x1D8 Reserved
	(uint32) 0,                                  																																									// 0x1DC Reserved
	(uint32) 0,                                  																																									// 0x1E0 Reserved
	(uint32) 0,                                  																																									// 0x1E4 Reserved
	(uint32) 0,                                  																																									// 0x1E8 Reserved
	(uint32) 0,                                  																																									// 0x1EC Reserved
	(uint32) 0,                                  																																									// 0x1F0 Reserved
	(uint32) 0,                                  																																									// 0x1F4 Reserved
	(uint32) 0,                                  																																									// 0x1F8 Reserved
	(uint32) 0,                                  																																									// 0x1FC Reserved
	(uint32) 0,                                  																																									// 0x200 Reserved
	(uint32) 0,                                  																																									// 0x204 Reserved
	(uint32) 0,                                  																																									// 0x208 Reserved
	(uint32) 0,                                  																																									// 0x20C Reserved
	(uint32) 0,                                  																																									// 0x210 Reserved
	(uint32) 0,                                  																																									// 0x214 Reserved
	(uint32) 0,                                  																																									// 0x218 Reserved
	(uint32) 0,                                  																																									// 0x21C Reserved
	(uint32) 0,                                  																																									// 0x220 Reserved
	(uint32) 0,                                  																																									// 0x224 Reserved
	(uint32) 0,                                  																																									// 0x228 Reserved
	(uint32) 0,                                  																																									// 0x22C Reserved
	(uint32) 0,                                  																																									// 0x230 Reserved
	(uint32) 0,                                  																																									// 0x234 Reserved
	(uint32) 0,                                  																																									// 0x238 Reserved
	(uint32) 0,                                  																																									// 0x23C Reserved
	(uint32) 0,                                  																																									// 0x240 Reserved
	(uint32) 0,                                  																																									// 0x244 Reserved
	(uint32) 0,                                  																																									// 0x248 Reserved
	(uint32) 0,                                  																																									// 0x24C Reserved
	(uint32) 0,                                  																																									// 0x250 Reserved
	(uint32) 0,                                  																																									// 0x254 Reserved
	(uint32) 0,                                  																																									// 0x258 Reserved
	(uint32) 0,                                  																																									// 0x25C Reserved
	(uint32) 0,                                  																																									// 0x260 Reserved
	(uint32) 0,                                  																																									// 0x264 Reserved
	(uint32) 0,                                  																																									// 0x268 Reserved
	(uint32) 0,                                  																																									// 0x26C Reserved
	(uint32) 0,                                  																																									// 0x270 Reserved
	(uint32) 0,                                  																																									// 0x274 Reserved
	(uint32) 0,                                  																																									// 0x278 Reserved
	(uint32) 0,                                  																																									// 0x27C Reserved
	(uint32) 0,                                  																																									// 0x280 Reserved
	(uint32) 0,                                  																																									// 0x284 Reserved
	(uint32) 0,                                  																																									// 0x288 Reserved
	(uint32) 0,                                  																																									// 0x28C Reserved
	(uint32) 0,                                  																																									// 0x290 Reserved
	(uint32) 0,                                  																																									// 0x294 Reserved
	(uint32) 0,                                  																																									// 0x298 Reserved
	(uint32) 0,                                  																																									// 0x29C Reserved
	(uint32) 0,                                  																																									// 0x2A0 Reserved
	(uint32) 0,                                  																																									// 0x2A4 Reserved
	(uint32) 0,                                  																																									// 0x2A8 Reserved
	(uint32) 0,                                  																																									// 0x2AC Reserved
	(uint32) 0,                                  																																									// 0x2B0 Reserved
	(uint32) 0,                                  																																									// 0x2B4 Reserved
	(uint32) 0,                                  																																									// 0x2B8 Reserved
	(uint32) 0,                                  																																									// 0x2BC Reserved
	(uint32) 0,                                  																																									// 0x2C0 Reserved
	(uint32) 0,                                  																																									// 0x2C4 Reserved
	(uint32) 0,                                  																																									// 0x2C8 Reserved
	(uint32) 0,                                  																																									// 0x2CC Reserved
	(uint32) 0,                                  																																									// 0x2D0 Reserved
	(uint32) 0,                                  																																									// 0x2D4 Reserved
	(uint32) 0,                                  																																									// 0x2D8 Reserved
	(uint32) 0,                                  																																									// 0x2DC Reserved
	(uint32) 0,                                  																																									// 0x2E0 Reserved
	(uint32) 0,                                  																																									// 0x2E4 Reserved
	(uint32) 0,                                  																																									// 0x2E8 Reserved
	(uint32) 0,                                  																																									// 0x2EC Reserved
	(uint32) 0,                                  																																									// 0x2F0 Reserved
	(uint32) 0,                                  																																									// 0x2F4 Reserved
	(uint32) 0,                                  																																									// 0x2F8 Reserved
	(uint32) 0,                                  																																									// 0x2FC Reserved
	(uint32) 0,                                  																																									// 0x300 Reserved
	(uint32) 0,                                  																																									// 0x304 Reserved
	(uint32) 0,                                  																																									// 0x308 Reserved
	(uint32) 0,                                  																																									// 0x30C Reserved
	(uint32) 0,                                  																																									// 0x310 Reserved
	(uint32) 0,                                  																																									// 0x314 Reserved
	(uint32) 0,                                  																																									// 0x318 Reserved
	(uint32) 0,                                  																																									// 0x31C Reserved
	(uint32) 0,                                  																																									// 0x320 Reserved
	(uint32) 0,                                  																																									// 0x324 Reserved
	(uint32) 0,                                  																																									// 0x328 Reserved
	(uint32) 0,                                  																																									// 0x32C Reserved
	(uint32) 0,                                  																																									// 0x330 Reserved
	(uint32) 0,                                  																																									// 0x334 Reserved
	(uint32) 0,                                  																																									// 0x338 Reserved
	(uint32) 0,                                  																																									// 0x33C Reserved
	(uint32) 0,                                  																																									// 0x340 Reserved
	(uint32) 0,                                  																																									// 0x344 Reserved
	(uint32) 0,                                  																																									// 0x348 Reserved
	(uint32) 0,                                  																																									// 0x34C Reserved
	(uint32) 0,                                  																																									// 0x350 Reserved
	(uint32) 0,                                  																																									// 0x354 Reserved
	(uint32) 0,                                  																																									// 0x358 Reserved
	(uint32) 0,                                  																																									// 0x35C Reserved
	(uint32) 0,                                  																																									// 0x360 Reserved
	(uint32) 0,                                  																																									// 0x364 Reserved
	(uint32) 0,                                  																																									// 0x368 Reserved
	(uint32) 0,                                  																																									// 0x36C Reserved
	(uint32) 0,                                  																																									// 0x370 Reserved
	(uint32) 0,                                  																																									// 0x374 Reserved
	(uint32) 0,                                  																																									// 0x378 Reserved
	(uint32) 0,                                  																																									// 0x37C Reserved
	(uint32) 0,                                  																																									// 0x380 Reserved
	(uint32) 0,                                  																																									// 0x384 Reserved
	(uint32) 0,                                  																																									// 0x388 Reserved
	(uint32) 0,                                  																																									// 0x38C Reserved
	(uint32) 0,                                  																																									// 0x390 Reserved
	(uint32) 0,                                  																																									// 0x394 Reserved
	(uint32) 0,                                  																																									// 0x398 Reserved
	(uint32) 0,                                  																																									// 0x39C Reserved
	(uint32) 0,                                  																																									// 0x3A0 Reserved
	(uint32) 0,                                  																																									// 0x3A4 Reserved
	(uint32) 0,                                  																																									// 0x3A8 Reserved
	(uint32) 0,                                  																																									// 0x3AC Reserved
	(uint32) 0,                                  																																									// 0x3B0 Reserved
	(uint32) 0,                                  																																									// 0x3B4 Reserved
	(uint32) 0,                                  																																									// 0x3B8 Reserved
	(uint32) 0,                                  																																									// 0x3BC Reserved
	(uint32) 0,                                  																																									// 0x3C0 Reserved
	(uint32) 0,                                  																																									// 0x3C4 Reserved
	(uint32) 0,                                  																																									// 0x3C8 Reserved
	(uint32) 0,                                  																																									// 0x3CC Reserved
	(uint32) 0,                                  																																									// 0x3D0 Reserved
	(uint32) 0,                                  																																									// 0x3D4 Reserved
	(uint32) 0,                                  																																									// 0x3D8 Reserved
	(uint32) 0,                                  																																									// 0x3DC Reserved
	(uint32) 0,                                  																																									// 0x3E0 Reserved
	(uint32) 0,                                  																																									// 0x3E4 Reserved
	(uint32) 0,                                  																																									// 0x3E8 Reserved
	(uint32) 0,                                  																																									// 0x3EC Reserved
	(uint32) 0,                                  																																									// 0x3F0 Reserved
	(uint32) 0,                                  																																									// 0x3F4 Reserved
	(uint32) 0,                                  																																									// 0x3F8 Reserved
	(uint32) 0                                  																																									// 0x3FC Reserved
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void STM32L451RET6::copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(dest + i) = *(src + i);
	}
}


void STM32L451RET6::zeroOutRAM(uint32* startAddress, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(startAddress + i) = 0;
	}
}


void STM32L451RET6::preInit()
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

STM32L451RET6& STM32L451RET6::get()
{
	static STM32L451RET6 stm32;
	return(stm32);
}









void EXCEPTION_RESET()
{
	//	External Symbols
	extern uint32 __memory_SRAM_1_start__;
	extern uint32 __memory_SRAM_1_size__;
	
	
	
	extern uint32 __cmos_data_flash_start__;
	extern uint32 __cmos_data_flash_size__;
	extern uint32 __cmos_data_ram_start__;
	
	extern uint32 __cmos_code_flash_start__;
	extern uint32 __cmos_code_flash_size__;
	extern uint32 __cmos_code_ram_start__;
	
	extern uint32 __cmos_heap_start__;
	extern uint32 __cmos_heap_size__;
	
	
	
	
	
	//	Convenience
	uint32* const				c_memory_SRAM_start	= (uint32*) &__memory_SRAM_1_start__;
	const uint32				c_memory_SRAM_size	= (uint32)  &__memory_SRAM_1_size__;
	
	
	
	const uint32* const	c_data_flash_start	= (uint32*) &__cmos_data_flash_start__;
	const uint32				c_data_flash_size		= (uint32)  &__cmos_data_flash_size__;
	uint32* const				c_data_ram_start		= (uint32*) &__cmos_data_ram_start__;
	
	const uint32* const	c_code_flash_start	= (uint32*) &__cmos_code_flash_start__;
	const uint32				c_code_flash_size		= (uint32)  &__cmos_code_flash_size__;
	uint32* const				c_code_ram_start		= (uint32*) &__cmos_code_ram_start__;
	
	const uint32* const	c_heap_start				= (uint32*) &__cmos_heap_start__;
	const uint32				c_heap_size					= (uint32)  &__cmos_heap_size__;
	
	
	
	
	
	//	Zero Memories - IMPORTANT: Dont clear Stackpointer
	constexpr uint32 c_stackpointerMemoryInBytes = 128;
	STM32L451RET6::zeroOutRAM(c_memory_SRAM_start, c_memory_SRAM_size - c_stackpointerMemoryInBytes);
	
	
	//	Set Stackpointer to reserved Stack Memory
	asm volatile
	(
		"msr msp, %[in_a]"
			:
			:	[in_a] "r" (c_heap_start + c_heap_size / 4)
			:
	);
	
	
	//	Zero Memory that couldnt be cleared before Stackpointer Moving
	STM32L451RET6::zeroOutRAM(c_memory_SRAM_start + (c_memory_SRAM_size - c_stackpointerMemoryInBytes) / 4, c_stackpointerMemoryInBytes);
	
	
	//	Copy non-zero-initialized Variables to SRAM
	STM32L451RET6::copy_flashToRAM(c_data_flash_start, c_data_ram_start, c_data_flash_size);
	
	
	//	Copy Code from Flash to SRAM
	STM32L451RET6::copy_flashToRAM(c_code_flash_start, c_code_ram_start, c_code_flash_size);
	
	
	//	Execute Functions that need to be executed before any Initialization has been done (Bootloader)
	STM32L451RET6::preInit();
	
	
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_PVM();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RTC_TAMPER_STAMP_CSS_LSE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_WKUP();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FLASH();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RCC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_1_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_1_CH1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_1_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_1_CH3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_1_CH4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_1_CH5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_1_CH6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ADC_1_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN_1_TX();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN_1_RX0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN_1_RX1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN_1_SCE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_9_TO_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_BREAK_TIMER_15();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_UPDATE_TIMER_16();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_TRIGGER_COMMUTATION();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_CAPTURE_COMPARE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_1_EVENT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_1_ERROR();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_2_EVENT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_2_ERROR();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USART_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USART_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USART_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_15_TO_10();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RTC_ALARM();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SDMMC_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_UART_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_6_DAC_UNDERRUN();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DFSDM_1_FLT_0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DFSDM_1_FLT_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_COMP();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_TIMER_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_TIMER_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LPUART_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_QUADSPI();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_3_EVENT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_3_ERROR();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SAI_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TSC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RNG();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FPU();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CRS();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_4_EVENT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_4_ERROR();





uint32 __startup__()
{
	STM32L451RET6& stm32 = STM32L451RET6::get();
	if(stm32.startup() != OK)
	{
		return(0);
	}
	return(stm32.get_rcc().get_clock_system());
}