#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

INTERRUPT_VECTOR const STM32H753BIT6::s_interruptTable STM32H753BIT6::c_interruptTable =
{
	(uint32) ISR_WWDG,                                                                                                        		// 0x040 Window Watchdog
	(uint32) ISR_PVD_PVM,                                                                                                     		// 0x044 PVD through EXTI Line
	(uint32) ISR_RTC_TAMPER_CSSLSE,                                                                                          			// 0x048 RTC Tamper, CSS LSE
	(uint32) ISR_RTC_WAKEUP,                                                                                                  		// 0x04C RTC Wakeup
	(uint32) ISR_FLASH,                                                                                                       		// 0x050 Flash
	(uint32) ISR_RCC,                                                                                                         		// 0x054 RCC
	(uint32) ISR_EXTI_0,                                                                                                      		// 0x058 External Interrupt 0
	(uint32) ISR_EXTI_1,                                                                                                      		// 0x05C External Interrupt 1
	(uint32) ISR_EXTI_2,                                                                                                      		// 0x060 External Interrupt 2
	(uint32) ISR_EXTI_3,                                                                                                      		// 0x064 External Interrupt 3
	(uint32) ISR_EXTI_4,                                                                                                      		// 0x068 External Interrupt 4
	(uint32) ISR_DMA_1_CH0,                                                                                                   		// 0x06C DMA 1 Channel 0
	(uint32) ISR_DMA_1_CH1,                                                                                                   		// 0x070 DMA 1 Channel 1
	(uint32) ISR_DMA_1_CH2,                                                                                                   		// 0x074 DMA 1 Channel 2
	(uint32) ISR_DMA_1_CH3,                                                                                                   		// 0x078 DMA 1 Channel 3
	(uint32) ISR_DMA_1_CH4,                                                                                                   		// 0x07C DMA 1 Channel 4
	(uint32) ISR_DMA_1_CH5,                                                                                                   		// 0x080 DMA 1 Channel 5
	(uint32) ISR_DMA_1_CH6,                                                                                                   		// 0x084 DMA 1 Channel 6
	(uint32) ISR_ADC_1_2,                                                                                                     		// 0x088 ADC 1 and ADC 2
	(uint32) ISR_FDCAN_1_INT0,                                                                                                		// 0x08C FDCAN 1 Interrupt 0
	(uint32) ISR_FDCAN_2_INT0,                                                                                                		// 0x090 FDCAN 2 Interrupt 0
	(uint32) ISR_FDCAN_1_INT1,                                                                                                		// 0x094 FDCAN 1 Interrupt 1
	(uint32) ISR_FDCAN_2_INT1,                                                                                                		// 0x098 FDCAN 2 Interrupt 1
	(uint32) ISR_EXTI_9_TO_5,                                                                                                 		// 0x09C External Interrupt 9 to 5
	(uint32) ISR_TIMER_1_BREAK,                                                                                               		// 0x0A0 Timer 1 Break
	(uint32) ISR_TIMER_1_UPDATE,                                                                                              		// 0x0A4 Timer 1 Update
	(uint32) ISR_TIMER_1_TRIGGER_COMMUTATION,                                                                                 		// 0x0A8 Timer 1 Trigger and Commutation
	(uint32) ISR_TIMER_1_CAPTURE_COMPARE,                                                                                     		// 0x0AC Timer 1 Capture Compare
	(uint32) ISR_TIMER_2,                                                                                                     		// 0x0B0 Timer 2
	(uint32) ISR_TIMER_3,                                                                                                     		// 0x0B4 Timer 3
	(uint32) ISR_TIMER_4,                                                                                                     		// 0x0B8 Timer 4
	(uint32) ISR_I2C_1_EVENT,                                                                                                 		// 0x0BC I2C 1 Event
	(uint32) ISR_I2C_1_ERROR,                                                                                                 		// 0x0C0 I2C 1 Error
	(uint32) ISR_I2C_2_EVENT,                                                                                                 		// 0x0C4 I2C 2 Event
	(uint32) ISR_I2C_2_ERROR,                                                                                                 		// 0x0C8 I2C 2 Error
	(uint32) ISR_SPI_1,                                                                                                       		// 0x0CC SPI 1
	(uint32) ISR_SPI_2,                                                                                                       		// 0x0D0 SPI 2
	(uint32) ISR_USART_1,                                                                                                     		// 0x0D4 USART 1
	(uint32) ISR_USART_2,                                                                                                     		// 0x0D8 USART 2
	(uint32) ISR_USART_3,                                                                                                     		// 0x0DC USART 3
	(uint32) ISR_EXTI_15_TO_10,                                                                                               		// 0x0E0 External Interrupt 15 to 10
	(uint32) ISR_RTC_ALARM_EXTI,                                                                                              		// 0x0E4 RTC Alarm through External Interrupt
	(uint32) 0,                                                                                                               		// 0x0E8 Reserved
	(uint32) ISR_TIMER_8_BREAK_AND_TIMER_12,                                                                                  		// 0x0EC Timer 8 Break and Timer 12
	(uint32) ISR_TIMER_8_UPDATE_AND_TIMER_13,                                                                                 		// 0x0F0 Timer 8 Update and TImer 13
	(uint32) ISR_TIMER_8_TRIGGER_COMMUTATION_AND_TIMER_14,                                                                    		// 0x0F4 Timer 8 Trigger and Commutation and Timer 14
	(uint32) ISR_TIMER_8_CAPTURE_COMPARE,                                                                                     		// 0x0F8 Timer 8 Capture Compare
	(uint32) ISR_DMA_1_CH7,                                                                                                   		// 0x0FC DMA 1 Channel 7
	(uint32) ISR_FMC,                                                                                                         		// 0x100 FMC
	(uint32) ISR_SDMMC_1,                                                                                                     		// 0x104 SDMMC 1
	(uint32) ISR_TIMER_5,                                                                                                     		// 0x108 Timer 5
	(uint32) ISR_SPI_3,                                                                                                       		// 0x10C SPI 3
	(uint32) ISR_UART_4,                                                                                                      		// 0x110 UART 4
	(uint32) ISR_UART_5,                                                                                                      		// 0x114 UART 5
	(uint32) ISR_TIMER_6_AND_DAC,                                                                                             		// 0x118 Timer 6 and DAC Underrun Error
	(uint32) ISR_TIMER_7,                                                                                                     		// 0x11C Timer 7
	(uint32) ISR_DMA_2_CH0,                                                                                                   		// 0x120 DMA 2 Channel 0
	(uint32) ISR_DMA_2_CH1,                                                                                                   		// 0x124 DMA 2 Channel 1
	(uint32) ISR_DMA_2_CH2,                                                                                                   		// 0x128 DMA 2 Channel 2
	(uint32) ISR_DMA_2_CH3,                                                                                                   		// 0x12C DMA 2 Channel 3
	(uint32) ISR_DMA_2_CH4,                                                                                                   		// 0x130 DMA 2 Channel 4
	(uint32) ISR_ETHERNET,                                                                                                    		// 0x134 Ethernet Global
	(uint32) ISR_ETHERNET_WAKEUP,                                                                                             		// 0x138 Ethernet Wakeup
	(uint32) ISR_FDCAN_CALIBRATION,                                                                                           		// 0x13C FDCAN Calibration
	(uint32) ISR_ARM_CORTEX_M7_SEND_EVEN,                                                                                     		// 0x140 ARM Cortex M7 Send Even Interrupt
	(uint32) 0,                                                                                                               		// 0x144 Reserved
	(uint32) 0,                                                                                                               		// 0x148 Reserved
	(uint32) 0,                                                                                                               		// 0x14C Reserved
	(uint32) ISR_DMA_2_CH5,                                                                                                   		// 0x150 DMA 2 Channel 5
	(uint32) ISR_DMA_2_CH6,                                                                                                   		// 0x154 DMA 2 Channel 6
	(uint32) ISR_DMA_2_CH7,                                                                                                   		// 0x158 DMA 2 Channel 7
	(uint32) ISR_USART_6,                                                                                                    			// 0x15C USART 6
	(uint32) ISR_I2C_3_EVENT,                                                                                                 		// 0x160 I2C 3 Event
	(uint32) ISR_I2C_3_ERROR,                                                                                                 		// 0x164 I2C 3 Error
	(uint32) ISR_USB_HS_EP1_OUT,                                                                                          				// 0x168 USB OTG High Speed EP1 OUT
	(uint32) ISR_USB_HS_EP1_IN,                                                                                          					// 0x16C USB OTG High Speed EP1 IN
	(uint32) ISR_USB_HS_WAKEUP,                                                                                           				// 0x170 USB OTG High Speed Wakeup
	(uint32) ISR_USB_HS,                                                                                                  				// 0x174 USB OTG High Speed Global
	(uint32) ISR_DCMI,                                                                                                        		// 0x178 Digital Camera Interface
	(uint32) ISR_CRYPTO,                                                                                                      		// 0x17C Cryptographic Processor
	(uint32) ISR_HASH_RNG,                                                                                                    		// 0x180 Hash Processor and True Random Number Generator
	(uint32) ISR_FPU,                                                                                                         		// 0x184 CPU Floating Point Unit (not present in Rev. V, see Errata Sheet ES0396 Section 2.1.2)
	(uint32) ISR_UART_7,                                                                                                      		// 0x188 UART 7
	(uint32) ISR_UART_8,                                                                                                      		// 0x18C UART 8
	(uint32) ISR_SPI_4,                                                                                                       		// 0x190 SPI 4
	(uint32) ISR_SPI_5,                                                                                                       		// 0x194 SPI 5
	(uint32) ISR_SPI_6,                                                                                                       		// 0x198 SPI 6
	(uint32) ISR_SAI_1,                                                                                                       		// 0x19C SAI 1
	(uint32) ISR_LTDC,                                                                                                     				// 0x1A0 LTDC Controller Global
	(uint32) ISR_LTDC_ERROR,                                                                                               				// 0x1A4 LTDC Controller Error
	(uint32) ISR_DMA2D,                                                                                                       		// 0x1A8 DMA2D
	(uint32) ISR_SAI_2,                                                                                                       		// 0x1AC SAI 2
	(uint32) ISR_QUADSPI,                                                                                                     		// 0x1B0 Quad SPI
	(uint32) ISR_LP_TIMER_1,                                                                                                  		// 0x1B4 Low Power Timer 1
	(uint32) ISR_HDMI_CEC,                                                                                                    		// 0x1B8 HDMI CEC
	(uint32) ISR_I2C_4_EVENT,                                                                                                 		// 0x1BC I2C 4 Event
	(uint32) ISR_I2C_4_ERROR,                                                                                                 		// 0x1C0 I2C 4 Error
	(uint32) ISR_SPDIF,                                                                                                       		// 0x1C4 SPDIF
	(uint32) ISR_USB_FS_EP1_OUT,                                                                                          				// 0x1C8 USB OTG Full Speed EP1 OUT
	(uint32) ISR_USB_FS_EP1_IN,                                                                                           				// 0x1CC USB OTG Full Speed EP1 IN
	(uint32) ISR_USB_FS_WAKEUP,                                                                                           				// 0x1D0 USB OTG Full Speed Wakeup
	(uint32) ISR_USB_FS,                                                                                                  				// 0x1D4 USB OTG Full Speed Global
	(uint32) ISR_DMAMUX_1_OVERRUN,                                                                                            		// 0x1D8 DMAMUX 1 Overrun
	(uint32) ISR_HR_TIMER_MASTER,                                                                                       					// 0x1DC High Resolution Timer Master Timer
	(uint32) ISR_HR_TIMER_A,                                                                                                  		// 0x1E0 High Resolution Timer Channel A
	(uint32) ISR_HR_TIMER_B,                                                                                                  		// 0x1E4 High Resolution Timer Channel B
	(uint32) ISR_HR_TIMER_C,                                                                                                  		// 0x1E8 High Resolution Timer Channel C
	(uint32) ISR_HR_TIMER_D,                                                                                                  		// 0x1EC High Resolution Timer Channel D
	(uint32) ISR_HR_TIMER_E,                                                                                                  		// 0x1F0 High Resolution Timer Channel E
	(uint32) ISR_HR_TIMER_FAULT,                                                                                              		// 0x1F4 High Resolution Timer Fault
	(uint32) ISR_DFSDM_FILTER_0,                                                                                              		// 0x1F8 DFSDM Filter 0
	(uint32) ISR_DFSDM_FILTER_1,                                                                                              		// 0x1FC DFSDM Filter 1
	(uint32) ISR_DFSDM_FILTER_2,                                                                                              		// 0x200 DFSDM Filter 2
	(uint32) ISR_DFSDM_FILTER_3,                                                                                              		// 0x204 DFSDM Filter 3
	(uint32) ISR_SAI_3,                                                                                                       		// 0x208 SAI 3
	(uint32) ISR_SWPMI,                                                                                                       		// 0x20C SWPMI
	(uint32) ISR_TIMER_15,                                                                                                    		// 0x210 Timer 15
	(uint32) ISR_TIMER_16,                                                                                                    		// 0x214 Timer 16
	(uint32) ISR_TIMER_17,                                                                                                    		// 0x218 Timer 17
	(uint32) ISR_MDIOS_WAKEUP,                                                                                                		// 0x21C MDIOS Wakeup
	(uint32) ISR_MDIOS,                                                                                                       		// 0x220 MDIOS Global
	(uint32) ISR_JPEG,                                                                                                       			// 0x224 JPEG
	(uint32) ISR_MDMA,                                                                                                        		// 0x228 MDMA
	(uint32) 0,                                                                                                               		// 0x22C Reserved
	(uint32) ISR_SDMMC_2,                                                                                                     		// 0x230 SDMMC 2
	(uint32) ISR_HSEM,                                                                                                        		// 0x234 HSEM
	(uint32) 0,                                                                                                               		// 0x238 Reserved
	(uint32) ISR_ADC_3,                                                                                                       		// 0x23C ADC 3
	(uint32) ISR_DMAMUX_2_OVERRUN,                                                                                            		// 0x240 DMAMUX 2 Overrun
	(uint32) ISR_BDMA_CH0,                                                                                                    		// 0x244 BDMA Channel 0
	(uint32) ISR_BDMA_CH1,                                                                                                    		// 0x248 BDMA Channel 1
	(uint32) ISR_BDMA_CH2,                                                                                                    		// 0x24C BDMA Channel 2
	(uint32) ISR_BDMA_CH3,                                                                                                    		// 0x250 BDMA Channel 3
	(uint32) ISR_BDMA_CH4,                                                                                                    		// 0x254 BDMA Channel 4
	(uint32) ISR_BDMA_CH5,                                                                                                    		// 0x258 BDMA Channel 5
	(uint32) ISR_BDMA_CH6,                                                                                                    		// 0x25C BDMA Channel 6
	(uint32) ISR_BDMA_CH7,                                                                                                   			// 0x260 BDMA Channel 7
	(uint32) ISR_COMP_1_2,                                                                                                   			// 0x264 Comparator 1 and 2
	(uint32) ISR_LP_TIMER_2,                                                                                                  		// 0x268 Low Power Timer 2
	(uint32) ISR_LP_TIMER_3,                                                                                                  		// 0x26C Low Power Timer 3
	(uint32) ISR_LP_TIMER_4,                                                                                                  		// 0x270 Low Power Timer 4
	(uint32) ISR_LP_TIMER_5,                                                                                                  		// 0x274 Low Power Timer 5
	(uint32) ISR_LP_UART,                                                                                                     		// 0x278 Low Power UART
	(uint32) ISR_WWDG_RESET,                                                                                                  		// 0x27C Window Watchdog Reset
	(uint32) ISR_CRS,                  					                                                                     							// 0x280 Clock Recovery System
	(uint32) ISR_RAM_ECC,                                                                                                     		// 0x284 ECC Diagnostic for RAMECC D1 to D3
	(uint32) ISR_SAI_4,                                                                                                       		// 0x288 SAI 4 Global
	(uint32) 0,                                                                                                               		// 0x28C Reserved
	(uint32) 0,                                                                                                               		// 0x290 Reserved
	(uint32) ISR_WAKEUP_PIN_0_TO_5,	                                                                                           		// 0x294 Wakeup Pins 0 to 5
	(uint32) 0,                                                                                                               		// 0x298 Reserved
	(uint32) 0,                                                                                                               		// 0x29C Reserved
	(uint32) 0,                                                                                                               		// 0x2A0 Reserved
	(uint32) 0,                                                                                                               		// 0x2A4 Reserved
	(uint32) 0,                                                                                                               		// 0x2A8 Reserved
	(uint32) 0,                                                                                                               		// 0x2AC Reserved
	(uint32) 0,                                                                                                               		// 0x2B0 Reserved
	(uint32) 0,                                                                                                               		// 0x2B4 Reserved
	(uint32) 0,                                                                                                               		// 0x2B8 Reserved
	(uint32) 0,                                                                                                               		// 0x2BC Reserved
	(uint32) 0,                                                                                                               		// 0x2C0 Reserved
	(uint32) 0,                                                                                                               		// 0x2C4 Reserved
	(uint32) 0,                                                                                                               		// 0x2C8 Reserved
	(uint32) 0,                                                                                                               		// 0x2CC Reserved
	(uint32) 0,                                                                                                               		// 0x2D0 Reserved
	(uint32) 0,                                                                                                               		// 0x2D4 Reserved
	(uint32) 0,                                                                                                               		// 0x2D8 Reserved
	(uint32) 0,                                                                                                               		// 0x2DC Reserved
	(uint32) 0,                                                                                                               		// 0x2E0 Reserved
	(uint32) 0,                                                                                                               		// 0x2E4 Reserved
	(uint32) 0,                                                                                                               		// 0x2E8 Reserved
	(uint32) 0,                                                                                                               		// 0x2EC Reserved
	(uint32) 0,                                                                                                               		// 0x2F0 Reserved
	(uint32) 0,                                                                                                               		// 0x2F4 Reserved
	(uint32) 0,                                                                                                               		// 0x2F8 Reserved
	(uint32) 0,                                                                                                               		// 0x2FC Reserved
	(uint32) 0,                                                                                                               		// 0x300 Reserved
	(uint32) 0,                                                                                                               		// 0x304 Reserved
	(uint32) 0,                                                                                                               		// 0x308 Reserved
	(uint32) 0,                                                                                                               		// 0x30C Reserved
	(uint32) 0,                                                                                                               		// 0x310 Reserved
	(uint32) 0,                                                                                                               		// 0x314 Reserved
	(uint32) 0,                                                                                                               		// 0x318 Reserved
	(uint32) 0,                                                                                                               		// 0x31C Reserved
	(uint32) 0,                                                                                                               		// 0x320 Reserved
	(uint32) 0,                                                                                                               		// 0x324 Reserved
	(uint32) 0,                                                                                                               		// 0x328 Reserved
	(uint32) 0,                                                                                                               		// 0x32C Reserved
	(uint32) 0,                                                                                                               		// 0x330 Reserved
	(uint32) 0,                                                                                                               		// 0x334 Reserved
	(uint32) 0,                                                                                                               		// 0x338 Reserved
	(uint32) 0,                                                                                                               		// 0x33C Reserved
	(uint32) 0,                                                                                                               		// 0x340 Reserved
	(uint32) 0,                                                                                                               		// 0x344 Reserved
	(uint32) 0,                                                                                                               		// 0x348 Reserved
	(uint32) 0,                                                                                                               		// 0x34C Reserved
	(uint32) 0,                                                                                                               		// 0x350 Reserved
	(uint32) 0,                                                                                                               		// 0x354 Reserved
	(uint32) 0,                                                                                                               		// 0x358 Reserved
	(uint32) 0,                                                                                                               		// 0x35C Reserved
	(uint32) 0,                                                                                                               		// 0x360 Reserved
	(uint32) 0,                                                                                                               		// 0x364 Reserved
	(uint32) 0,                                                                                                               		// 0x368 Reserved
	(uint32) 0,                                                                                                               		// 0x36C Reserved
	(uint32) 0,                                                                                                               		// 0x370 Reserved
	(uint32) 0,                                                                                                               		// 0x374 Reserved
	(uint32) 0,                                                                                                               		// 0x378 Reserved
	(uint32) 0,                                                                                                               		// 0x37C Reserved
	(uint32) 0,                                                                                                               		// 0x380 Reserved
	(uint32) 0,                                                                                                               		// 0x384 Reserved
	(uint32) 0,                                                                                                               		// 0x388 Reserved
	(uint32) 0,                                                                                                               		// 0x38C Reserved
	(uint32) 0,                                                                                                               		// 0x390 Reserved
	(uint32) 0,                                                                                                               		// 0x394 Reserved
	(uint32) 0,                                                                                                               		// 0x398 Reserved
	(uint32) 0,                                                                                                               		// 0x39C Reserved
	(uint32) 0,                                                                                                               		// 0x3A0 Reserved
	(uint32) 0,                                                                                                               		// 0x3A4 Reserved
	(uint32) 0,                                                                                                               		// 0x3A8 Reserved
	(uint32) 0,                                                                                                               		// 0x3AC Reserved
	(uint32) 0,                                                                                                               		// 0x3B0 Reserved
	(uint32) 0,                                                                                                               		// 0x3B4 Reserved
	(uint32) 0,                                                                                                               		// 0x3B8 Reserved
	(uint32) 0,                                                                                                               		// 0x3BC Reserved
	(uint32) 0,                                                                                                               		// 0x3C0 Reserved
	(uint32) 0,                                                                                                               		// 0x3C4 Reserved
	(uint32) 0,                                                                                                               		// 0x3C8 Reserved
	(uint32) 0,                                                                                                               		// 0x3CC Reserved
	(uint32) 0,                                                                                                               		// 0x3D0 Reserved
	(uint32) 0,                                                                                                               		// 0x3D4 Reserved
	(uint32) 0,                                                                                                               		// 0x3D8 Reserved
	(uint32) 0,                                                                                                               		// 0x3DC Reserved
	(uint32) 0,                                                                                                               		// 0x3E0 Reserved
	(uint32) 0,                                                                                                               		// 0x3E4 Reserved
	(uint32) 0,                                                                                                               		// 0x3E8 Reserved
	(uint32) 0,                                                                                                               		// 0x3EC Reserved
	(uint32) 0,                                                                                                               		// 0x3F0 Reserved
	(uint32) 0,                                                                                                               		// 0x3F4 Reserved
	(uint32) 0,                                                                                                               		// 0x3F8 Reserved
	(uint32) 0                                                                                                               			// 0x3FC Reserved
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void STM32H753BIT6::copy_flashToRAM(const uint32* const src, uint32* const dest, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(dest + i) = *(src + i);
	}
}


void STM32H753BIT6::zeroOutRAM(uint32* const startAddress, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(startAddress + i) = 0;
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback STM32H753BIT6::startup()
{
	if(m_debug.startup() != OK)
	{
		return(FAIL);
	}
	if(m_syscfg.startup() != OK)
	{
		return(FAIL);
	}
	if(m_pwr.startup() != OK)
	{
		return(FAIL);
	}
	if(m_flash.startup() != OK)
	{
		return(FAIL);
	}
	if(m_rcc.startup() != OK)
	{
		return(FAIL);
	}
	if(m_backupSRAM.startup() != OK)
	{
		return(FAIL);
	}
	if(m_gpio.startup() != OK)
	{
		return(FAIL);
	}
	for(uint32 i = 0; i < HSEM::c_number; i++)
	{
		if(m_hsem[i].startup(i) != OK)
		{
			return(FAIL);
		}
	}
	if(m_rtc.startup() != OK)
	{
		return(FAIL);
	}
	
	
	if(m_exti.startup() != OK)
	{
		return(FAIL);
	}
	if(m_vrefbuf.startup() != OK)
	{
		return(FAIL);
	}
	
	
	if(m_dma2d.startup() != OK)
	{
		return(FAIL);
	}
	if(m_mdma.startup() != OK)
	{
		return(FAIL);
	}
	if(m_dmamux.startup() != OK)
	{
		return(FAIL);
	}
	for(uint32 i = 0; i < DMA_1::c_channel; i++)
	{
		if(m_dma_1[i].startup(i) != OK)
		{
			return(FAIL);
		}
	}
	for(uint32 i = 0; i < DMA_2::c_channel; i++)
	{
		if(m_dma_2[i].startup(i) != OK)
		{
			return(FAIL);
		}
	}
	
	
	if(m_adc_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_adc_2.startup() != OK)
	{
		return(FAIL);
	}
	if(m_adc_3.startup() != OK)
	{
		return(FAIL);
	}
	
	
	if(m_timer_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_2.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_3.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_12.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_13.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_15.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_16.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_17.startup() != OK)
	{
		return(FAIL);
	}
	
	
	if(m_usart_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_uart_5.startup() != OK)
	{
		return(FAIL);
	}
	if(m_uart_7.startup() != OK)
	{
		return(FAIL);
	}
	
	
	if(m_fmc.startup() != OK)
	{
		return(FAIL);
	}
	if(m_ltdc.startup() != OK)
	{
		return(FAIL);
	}
	
	
	if(m_i2c_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_i2c_2.startup() != OK)
	{
		return(FAIL);
	}
	
	
	if(m_sdmmc_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_sdmmc_2.startup() != OK)
	{
		return(FAIL);
	}
	
	
	if(m_can_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_can_2.startup() != OK)
	{
		return(FAIL);
	}
	
	
	return(OK);
}









void EXCEPTION_RESET()
{
	//	External Symbols
	extern uint32 __memory_SRAM_ITCM_start__;
	extern uint32 __memory_SRAM_ITCM_size__;
	extern uint32 __memory_SRAM_DTCM_start__;
	extern uint32 __memory_SRAM_DTCM_size__;
	extern uint32 __memory_SRAM_AXI_start__;
	extern uint32 __memory_SRAM_AXI_size__;
	extern uint32 __memory_SRAM_1_start__;
	extern uint32 __memory_SRAM_1_size__;
	extern uint32 __memory_SRAM_2_start__;
	extern uint32 __memory_SRAM_2_size__;
	extern uint32 __memory_SRAM_3_start__;
	extern uint32 __memory_SRAM_3_size__;
	extern uint32 __memory_SRAM_4_start__;
	extern uint32 __memory_SRAM_4_size__;
	
	
	
	extern uint32 __cmos_data_flash_start__;
	extern uint32 __cmos_data_flash_size__;
	extern uint32 __cmos_data_ram_start__;
	
	extern uint32 __cmos_code_flash_start__;
	extern uint32 __cmos_code_flash_size__;
	extern uint32 __cmos_code_ram_start__;
	
	
	
	
	
	//	Convenience
	uint32* const				c_memory_SRAM_ITCM_start				= (uint32*) &__memory_SRAM_ITCM_start__;
	const uint32				c_memory_SRAM_ITCM_size					= (uint32)  &__memory_SRAM_ITCM_size__;
	uint32* const				c_memory_SRAM_DTCM_start				= (uint32*) &__memory_SRAM_DTCM_start__;
	const uint32				c_memory_SRAM_DTCM_size					= (uint32)  &__memory_SRAM_DTCM_size__;
	uint32* const				c_memory_SRAM_AXI_start					= (uint32*) &__memory_SRAM_AXI_start__;
	const uint32				c_memory_SRAM_AXI_size					= (uint32)  &__memory_SRAM_AXI_size__;
	uint32* const				c_memory_SRAM_1_start						= (uint32*) &__memory_SRAM_1_start__;
	const uint32				c_memory_SRAM_1_size						= (uint32)  &__memory_SRAM_1_size__;
	uint32* const				c_memory_SRAM_2_start						= (uint32*) &__memory_SRAM_2_start__;
	const uint32				c_memory_SRAM_2_size						= (uint32)  &__memory_SRAM_2_size__;
	uint32* const				c_memory_SRAM_3_start						= (uint32*) &__memory_SRAM_3_start__;
	const uint32				c_memory_SRAM_3_size						= (uint32)  &__memory_SRAM_3_size__;
	uint32* const				c_memory_SRAM_4_start						= (uint32*) &__memory_SRAM_4_start__;
	const uint32				c_memory_SRAM_4_size						= (uint32)  &__memory_SRAM_4_size__;
	
	
	
	const uint32* const	c_data_flash_start							= (uint32*) &__cmos_data_flash_start__;
	const uint32				c_data_flash_size								= (uint32)  &__cmos_data_flash_size__;
	uint32* const				c_data_ram_start								= (uint32*) &__cmos_data_ram_start__;
	
	const uint32* const	c_code_flash_start							= (uint32*) &__cmos_code_flash_start__;
	const uint32				c_code_flash_size								= (uint32)  &__cmos_code_flash_size__;
	uint32* const				c_code_ram_start								= (uint32*) &__cmos_code_ram_start__;
	
	
	
	
	
	//	Enable SRAM 1 Clock in RCC
	bit::set(*MCU::RCC::AHB2_ENR, 29);
	
	
	//	Enable SRAM 2 Clock in RCC
	bit::set(*MCU::RCC::AHB2_ENR, 30);
	
	
	//	Enable SRAM 3 Clock in RCC
	bit::set(*MCU::RCC::AHB2_ENR, 31);
	
	
	//	Enable BackupSRAM Clock in RCC
	bit::set(*MCU::RCC::AHB4_ENR, 28);
	
	
	//	Zero Memories
	STM32H753BIT6::zeroOutRAM(c_memory_SRAM_ITCM_start,	c_memory_SRAM_ITCM_size);
	STM32H753BIT6::zeroOutRAM(c_memory_SRAM_DTCM_start,	c_memory_SRAM_DTCM_size);
	STM32H753BIT6::zeroOutRAM(c_memory_SRAM_AXI_start, 	c_memory_SRAM_AXI_size);
	STM32H753BIT6::zeroOutRAM(c_memory_SRAM_1_start,		c_memory_SRAM_1_size);
	STM32H753BIT6::zeroOutRAM(c_memory_SRAM_2_start,		c_memory_SRAM_2_size);
	STM32H753BIT6::zeroOutRAM(c_memory_SRAM_3_start,		c_memory_SRAM_3_size);
	STM32H753BIT6::zeroOutRAM(c_memory_SRAM_4_start,		c_memory_SRAM_4_size);
	
	
	//	Copy non-zero-initialized Variables to SRAM
	STM32H753BIT6::copy_flashToRAM(c_data_flash_start, c_data_ram_start, c_data_flash_size);
	
	
	//	Copy Code from Flash to SRAM
	STM32H753BIT6::copy_flashToRAM(c_code_flash_start, c_code_ram_start, c_code_flash_size);
	
	
	//	Start OS
	CMOS& cmos = CMOS::get();
	cmos.run();
	
	
	//	Reset if System ever returns
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RTC_TAMPER_CSSLSE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RTC_WAKEUP();
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_1_INT0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_2_INT0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_1_INT1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_2_INT1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_9_TO_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_BREAK();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_UPDATE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_TRIGGER_COMMUTATION();
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RTC_ALARM_EXTI();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_8_BREAK_AND_TIMER_12();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_8_UPDATE_AND_TIMER_13();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_8_TRIGGER_COMMUTATION_AND_TIMER_14();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_8_CAPTURE_COMPARE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_1_CH7();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FMC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SDMMC_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_UART_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_UART_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_6_AND_DAC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_7();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ETHERNET();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ETHERNET_WAKEUP();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FDCAN_CALIBRATION();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ARM_CORTEX_M7_SEND_EVEN();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_2_CH7();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USART_6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_3_EVENT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_3_ERROR();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_HS_EP1_OUT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_HS_EP1_IN();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_HS_WAKEUP();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_HS();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DCMI();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CRYPTO();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HASH_RNG();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FPU();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_UART_7();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_UART_8();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SAI_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LTDC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LTDC_ERROR();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA2D();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SAI_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_QUADSPI();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_TIMER_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HDMI_CEC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_4_EVENT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_4_ERROR();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPDIF();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_FS_EP1_OUT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_FS_EP1_IN();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_FS_WAKEUP();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_FS();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMAMUX_1_OVERRUN();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_MASTER();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_A();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_B();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_C();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_D();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_E();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HR_TIMER_FAULT();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DFSDM_FILTER_0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DFSDM_FILTER_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DFSDM_FILTER_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DFSDM_FILTER_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SAI_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SWPMI();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_15();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_16();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_17();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_MDIOS_WAKEUP();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_MDIOS();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_JPEG();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_MDMA();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SDMMC_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_HSEM();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ADC_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMAMUX_2_OVERRUN();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_BDMA_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_BDMA_CH1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_BDMA_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_BDMA_CH3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_BDMA_CH4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_BDMA_CH5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_BDMA_CH6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_BDMA_CH7();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_COMP_1_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_TIMER_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_TIMER_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_TIMER_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_TIMER_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_UART();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_WWDG_RESET();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CRS();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RAM_ECC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SAI_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_WAKEUP_PIN_0_TO_5();





uint32 __startup__()
{
	STM32H753BIT6& stm32h753bit6 = STM32H753BIT6::get();
	if(stm32h753bit6.startup() != OK)
	{
		return(0);
	}
	uint32 clock = stm32h753bit6.get_rcc().get_clock_core();
	
	
	
	//	Revision Y Error: See Errata Sheet ES0396 Rev. 9 Section 2.2.3
	const uint16 c_revisionID = stm32h753bit6.get_debug().get_revisionID();
	if(c_revisionID == 0x1003)
	{
		clock *= 8;
	}
	return(clock * 8);
}