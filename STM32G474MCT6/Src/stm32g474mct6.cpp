#include "../Inc/stm32g474mct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

INTERRUPT_VECTOR const STM32G474MCT6::s_interruptTable STM32G474MCT6::c_interruptTable =
{
	(uint32) ISR_WWDG,                           																																									// 0x040 Window Watchdog
	(uint32) ISR_PVD_PVM,                                  																																				// 0x044 PVD/PVM1/PVM2 through EXTI 16/40/41
	(uint32) ISR_RTC_TAMPER_CSS_LSE,                            																																	// 0x048 RTC Tamper or CSS on LSE through EXTI 19
	(uint32) ISR_RTC_WKUP,                          																																							// 0x04C RTC WKUP
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
	(uint32) ISR_USB_HIGH_PRIORITY,                                  																															// 0x08C USB High Priority Interrupts
	(uint32) ISR_USB_LOW_PRIORITY,                       																																					// 0x090 USB Low Priority Interrupts
	(uint32) ISR_FDCAN_1_IT0,                                  																																		// 0x094 FDCAN 1 IT1
	(uint32) ISR_FDCAN_1_IT1,                                  																																		// 0x098 FDCAN 1 IT0
	(uint32) ISR_EXTI_9_TO_5,                          																																						// 0x09C External Interrupt 5 - 9
	(uint32) ISR_TIMER_1_BREAK_TIMER_15,                                  																												// 0x0A0 Timer 1 Break & Timer 15
	(uint32) ISR_TIMER_1_UPDATE_TIMER_16,                          																																// 0x0A4 Timer 1 Update & Timer 16
	(uint32) ISR_TIMER_1_TRIGGER_COMMUTATION_DIRECTION_INDEX_TIMER_17,                                  													// 0x0A8 Timer 1 Trigger & Commutation, Direction Change, Index
	(uint32) ISR_TIMER_1_CAPTURE_COMPARE,                                  																												// 0x0AC Timer 1 Capture Compare
	(uint32) ISR_TIMER_2,                        																																									// 0x0B0 Timer 2
	(uint32) ISR_TIMER_3,                                  																																				// 0x0B4 Timer 3
	(uint32) ISR_TIMER_4,                                  																																				// 0x0B8 Timer 4
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
	(uint32) ISR_USB_WAKEUP,                                  																																		// 0x0E8 USB Wakeup
	(uint32) ISR_TIMER_8_BREAK_TRANSITIONERROR_INDEXERROR,                                  																			// 0x0EC Timer 8 Break, Transition Error, Index Error
	(uint32) ISR_TIMER_8_UPDATE,                                  																																// 0x0F0 Timer 8 Update
	(uint32) ISR_TIMER_8_TRIGGER_COMMUTATION_DIRECTION_INDEX,                                  																		// 0x0F4 Timer 8 Trigger & Commutation, Direction Change, Index
	(uint32) ISR_TIMER_8_CAPTURE_COMPARE,                                  																												// 0x0F8 Timer 8 Capture Compare
	(uint32) ISR_ADC_3,                                  																																					// 0x0FC ADC 3
	(uint32) ISR_FSMC,                                  																																					// 0x100 FSMC
	(uint32) ISR_LP_TIMER_1,                                  																																		// 0x104 Low Power Timer 1
	(uint32) ISR_TIMER_5,                                  																																				// 0x108 Timer 5
	(uint32) ISR_SPI_3,                                  																																					// 0x10C SPI 3
	(uint32) ISR_UART_4,                                  																																				// 0x110 UART 4
	(uint32) ISR_UART_5,                                  																																				// 0x114 UART 5
	(uint32) ISR_TIMER_6_DAC_UNDERRUN,                                  																													// 0x118 Timer 6 DAC Underrun
	(uint32) ISR_TIMER_7_DAC_UNDERRUN,                                  																													// 0x11C Timer 7 DAC Underrun
	(uint32) ISR_DMA_2_CH0,                                  																																			// 0x120 DMA 2 CH0
	(uint32) ISR_DMA_2_CH1,                                  																																			// 0x124 DMA 2 CH1
	(uint32) ISR_DMA_2_CH2,                                  																																			// 0x128 DMA 2 CH2
	(uint32) ISR_DMA_2_CH3,                                  																																			// 0x12C DMA 2 CH3
	(uint32) ISR_DMA_2_CH4,                                  																																			// 0x130 DMA 2 CH4
	(uint32) ISR_ADC_4,                                  																																					// 0x134 ADC 4
	(uint32) ISR_ADC_5,                                  																																					// 0x138 ADC 5
	(uint32) ISR_UCPD,                                  																																					// 0x13C USB-C Power Delivery
	(uint32) ISR_COMP_1_2_3,                                  																																		// 0x140 Comparator 1, 2 & 3
	(uint32) ISR_COMP_4_5_6,                                  																																		// 0x144 Comparator 4, 5 & 6
	(uint32) ISR_COMP_7,                                  																																				// 0x148 Comparator 7
	(uint32) ISR_HR_TIMER_MASTER,                                  																																// 0x14C High Resolution Timer Master
	(uint32) ISR_HR_TIMER_A,                                  																																		// 0x150 High Resolution Timer A
	(uint32) ISR_HR_TIMER_B,                                  																																		// 0x154 High Resolution Timer B
	(uint32) ISR_HR_TIMER_C,                                  																																		// 0x158 High Resolution Timer C
	(uint32) ISR_HR_TIMER_D,                                  																																		// 0x15C High Resolution Timer D
	(uint32) ISR_HR_TIMER_E,                                  																																		// 0x160 High Resolution Timer E
	(uint32) ISR_HR_TIMER_FAULT,                                  																																// 0x164 High Resolution Timer Fault
	(uint32) ISR_HR_TIMER_F,                                  																																		// 0x168 High Resolution Timer F
	(uint32) ISR_CRS,                                  																																						// 0x16C Clock Recovery System
	(uint32) ISR_SAI,                                  																																						// 0x170 Serial Audio Interface
	(uint32) ISR_TIMER_20_BREAK_TRANSITIONERROR_INDEXERROR,                                  																			// 0x174 Timer 20 Break, Transition Error, Index Error
	(uint32) ISR_TIMER_20_UPDATE,                                  																																// 0x178 Timer 20 Update
	(uint32) ISR_TIMER_20_TRIGGER_COMMUTATION_DIRECTION_INDEX,                                  																	// 0x17C Timer 20 Trigger & Commutation, Direction Change, Index
	(uint32) ISR_TIMER_20_CAPTURE_COMPARE,                                  																											// 0x180 Timer 20 Capture Compare
	(uint32) ISR_FPU,                                  																																						// 0x184 FPU
	(uint32) ISR_I2C_4_EVENT,                                  																																		// 0x188 I2C 4 Event
	(uint32) ISR_I2C_4_ERROR,                                  																																		// 0x18C I2C 4 Error
	(uint32) ISR_SPI_4,                                  																																					// 0x190 SPI 4
	(uint32) ISR_AES,                                  																																						// 0x194 AES
	(uint32) ISR_FDCAN_2_IT0,                                  																																		// 0x198 FDCAN 2 IT0
	(uint32) ISR_FDCAN_2_IT1,                                  																																		// 0x19C FDCAN 2 IT1
	(uint32) ISR_FDCAN_3_IT0,                                  																																		// 0x1A0 FDCAN 3 IT0
	(uint32) ISR_FDCAN_3_IT1,                                  																																		// 0x1A4 FDCAN 3 IT1
	(uint32) ISR_RNG,                                  																																						// 0x1A8 Random Number Generator
	(uint32) ISR_LPUART_1,                                  																																			// 0x1AC Low Power UART 1
	(uint32) ISR_I2C_3_EVENT,                                  																																		// 0x1B0 I2C 3 Event
	(uint32) ISR_I2C_3_ERROR,                                  																																		// 0x1B4 I2C 3 Error
	(uint32) ISR_DMAMUX_OVERRUN,                                  																																// 0x1B8 DMAMUX Overrun
	(uint32) ISR_QUADSPI,                                  																																				// 0x1BC QUADSPI
	(uint32) ISR_DMA_1_CH7,                                  																																			// 0x1C0 DMA 1 CH7
	(uint32) ISR_DMA_2_CH5,                                  																																			// 0x1C4 DMA 2 CH5
	(uint32) ISR_DMA_2_CH6,                                  																																			// 0x1C8 DMA 2 CH6
	(uint32) ISR_DMA_2_CH7,                                  																																			// 0x1CC DMA 2 CH7
	(uint32) ISR_CORDIC,                                  																																				// 0x1D0 CORDIC (Coordinate Rotation Digital Computer)
	(uint32) ISR_FMAC,                                  																																					// 0x1D4 FMAC (Filter Math Accelerator)
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

void STM32G474MCT6::copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(dest + i) = *(src + i);
	}
}


void STM32G474MCT6::zeroOutRAM(uint32* startAddress, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(startAddress + i) = 0;
	}
}


void STM32G474MCT6::preInit()
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

STM32G474MCT6& STM32G474MCT6::get()
{
	static STM32G474MCT6 stm32;
	return(stm32);
}









void EXCEPTION_RESET()
{
	//	External Symbols
	extern uint32 __memory_SRAM_1_start__;
	extern uint32 __memory_SRAM_1_size__;
	
	extern uint32 __memory_SRAM_2_start__;
	extern uint32 __memory_SRAM_2_size__;
	
	extern uint32 __memory_SRAM_CCM_start__;
	extern uint32 __memory_SRAM_CCM_size__;
	
	
	
	extern uint32 __cmos_data_flash_start__;
	extern uint32 __cmos_data_flash_size__;
	extern uint32 __cmos_data_ram_start__;
	
	extern uint32 __cmos_code_flash_start__;
	extern uint32 __cmos_code_flash_size__;
	extern uint32 __cmos_code_ram_start__;
	
	extern uint32 __cmos_heap_start__;
	extern uint32 __cmos_heap_size__;
	
	
	
	
	
	//	Convenience
	uint32* const				c_memory_SRAM_1_start		= (uint32*) &__memory_SRAM_1_start__;
	const uint32				c_memory_SRAM_1_size		= (uint32)  &__memory_SRAM_1_size__;
	
	uint32* const				c_memory_SRAM_2_start		= (uint32*) &__memory_SRAM_2_start__;
	const uint32				c_memory_SRAM_2_size		= (uint32)  &__memory_SRAM_2_size__;
	
	uint32* const				c_memory_SRAM_CCM_start	= (uint32*) &__memory_SRAM_CCM_start__;
	const uint32				c_memory_SRAM_CCM_size	= (uint32)  &__memory_SRAM_CCM_size__;
	
	
	
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
	STM32G474MCT6::zeroOutRAM(c_memory_SRAM_1_start, c_memory_SRAM_1_size - c_stackpointerMemoryInBytes);
	
	STM32G474MCT6::zeroOutRAM(c_memory_SRAM_2_start, c_memory_SRAM_2_size);
	STM32G474MCT6::zeroOutRAM(c_memory_SRAM_CCM_start, c_memory_SRAM_CCM_size);
	
	
	//	Set Stackpointer to reserved Stack Memory
	asm volatile
	(
		"msr msp, %[in_a]"
			:
			:	[in_a] "r" (c_heap_start + c_heap_size / 4)
			:
	);
	
	
	//	Zero Memory that couldnt be cleared before Stackpointer Moving
	STM32G474MCT6::zeroOutRAM(c_memory_SRAM_1_start + (c_memory_SRAM_1_size - c_stackpointerMemoryInBytes) / 4, c_stackpointerMemoryInBytes);
	
	
	//	Copy non-zero-initialized Variables to SRAM
	STM32G474MCT6::copy_flashToRAM(c_data_flash_start, c_data_ram_start, c_data_flash_size);
	
	
	//	Copy Code from Flash to SRAM
	STM32G474MCT6::copy_flashToRAM(c_code_flash_start, c_code_ram_start, c_code_flash_size);
	
	
	//	Execute Functions that need to be executed before any Initialization has been done (Bootloader)
	STM32G474MCT6::preInit();
	
	
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_PVD_PVM();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RTC_TAMPER_CSS_LSE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RTC_WKUP();
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_HIGH_PRIORITY();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_LOW_PRIORITY();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_1_IT0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_1_IT1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_9_TO_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_BREAK_TIMER_15();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_UPDATE_TIMER_16();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_TRIGGER_COMMUTATION_DIRECTION_INDEX_TIMER_17();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_CAPTURE_COMPARE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_4();
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_WAKEUP();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_8_BREAK_TRANSITIONERROR_INDEXERROR();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_8_UPDATE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_8_TRIGGER_COMMUTATION_DIRECTION_INDEX();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_8_CAPTURE_COMPARE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ADC_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FSMC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_TIMER_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_UART_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_UART_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_6_DAC_UNDERRUN();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_7_DAC_UNDERRUN();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ADC_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ADC_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_UCPD();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_COMP_1_2_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_COMP_4_5_6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_COMP_7();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_MASTER();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_A();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_B();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_C();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_D();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_E();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_FAULT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_F();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CRS();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SAI();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_20_BREAK_TRANSITIONERROR_INDEXERROR();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_20_UPDATE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_20_TRIGGER_COMMUTATION_DIRECTION_INDEX();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_20_CAPTURE_COMPARE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FPU();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_4_EVENT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_4_ERROR();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_AES();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_2_IT0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_2_IT1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_3_IT0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_3_IT1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RNG();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LPUART_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_3_EVENT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_3_ERROR();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMAMUX_OVERRUN();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_QUADSPI();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_1_CH7();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH7();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CORDIC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FMAC();





uint32 __startup__()
{
	STM32G474MCT6& stm32 = STM32G474MCT6::get();
	if(stm32.startup() != OK)
	{
		return(0);
	}
	return(stm32.get_rcc().get_clock_system());
}