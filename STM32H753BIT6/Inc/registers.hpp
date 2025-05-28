#pragma once

#include "cmos.hpp"





namespace Interrupt
{
	constexpr uint16 WWDG																			= 16;
	constexpr uint16 PVD																			= 17;
	constexpr uint16 RTC_TAMPER_CSSLSE												= 18;
	constexpr uint16 RTC_WAKEUP																= 19;
	constexpr uint16 FLASH																		= 20;
	constexpr uint16 RCC 																			= 21;
	constexpr uint16 EXTI_0																		= 22;
	constexpr uint16 EXTI_1																		= 23;
	constexpr uint16 EXTI_2																		= 24;
	constexpr uint16 EXTI_3																		= 25;
	constexpr uint16 EXTI_4																		= 26;
	constexpr uint16 DMA_1_CH0																= 27;
	constexpr uint16 DMA_1_CH1																= 28;
	constexpr uint16 DMA_1_CH2																= 29;
	constexpr uint16 DMA_1_CH3																= 30;
	constexpr uint16 DMA_1_CH4																= 31;
	constexpr uint16 DMA_1_CH5																= 32;
	constexpr uint16 DMA_1_CH6																= 33;
	constexpr uint16 ADC_1_2																	= 34;
	constexpr uint16 FDCAN_1_INT0															= 35;
	constexpr uint16 FDCAN_2_INT0															= 36;
	constexpr uint16 FDCAN_1_INT1															= 37;
	constexpr uint16 FDCAN_2_INT1															= 38;
	constexpr uint16 EXTI_9_TO_5															= 39;
	constexpr uint16 TIMER_1_BREAK														= 40;
	constexpr uint16 TIMER_1_UPDATE														= 41;
	constexpr uint16 TIMER_1_TRIGGER_COMMUTATION							= 42;
	constexpr uint16 TIMER_1_CAPTURE_COMPARE									= 43;
	constexpr uint16 TIMER_2																	= 44;
	constexpr uint16 TIMER_3																	= 45;
	constexpr uint16 TIMER_4																	= 46;
	constexpr uint16 I2C_1_EVENT															= 47;
	constexpr uint16 I2C_1_ERROR															= 48;
	constexpr uint16 I2C_2_EVENT															= 49;
	constexpr uint16 I2C_2_ERROR															= 50;
	constexpr uint16 SPI_1																		= 51;
	constexpr uint16 SPI_2																		= 52;
	constexpr uint16 USART_1																	= 53;
	constexpr uint16 USART_2																	= 54;
	constexpr uint16 USART_3																	= 55;
	constexpr uint16 EXTI_15_TO_10														= 56;
	constexpr uint16 RTC_ALARM_EXTI														= 57;
	
	constexpr uint16 TIMER_8_BREAK_AND_TIMER_12								= 59;
	constexpr uint16 TIMER_8_UPDATE_AND_TIMER_13							= 60;
	constexpr uint16 TIMER_8_TRIGGER_COMMUTATION_AND_TIMER_14	= 61;
	constexpr uint16 TIMER_8_CAPTURE_COMPARE									= 62;
	constexpr uint16 DMA_1_CH7																= 63;
	constexpr uint16 FMC																			= 64;
	constexpr uint16 SDMMC_1																	= 65;
	constexpr uint16 TIMER_5																	= 66;
	constexpr uint16 SPI_3																		= 67;
	constexpr uint16 UART_4																		= 68;
	constexpr uint16 UART_5																		= 69;
	constexpr uint16 TIMER_6_AND_DAC													= 70;
	constexpr uint16 TIMER_7																	= 71;
	constexpr uint16 DMA_2_CH0																= 72;
	constexpr uint16 DMA_2_CH1																= 73;
	constexpr uint16 DMA_2_CH2																= 74;
	constexpr uint16 DMA_2_CH3																= 75;
	constexpr uint16 DMA_2_CH4																= 76;
	constexpr uint16 ETHERNET																	= 77;
	constexpr uint16 ETHERNET_WAKEUP													= 78;
	constexpr uint16 FDCAN_CALIBRATION												= 79;
	constexpr uint16 ARM_CORTEX_M7_SEND_EVEN									= 80;
	
	
	
	constexpr uint16 DMA_2_CH5																= 84;
	constexpr uint16 DMA_2_CH6																= 85;
	constexpr uint16 DMA_2_CH7																= 86;
	constexpr uint16 USART_6																	= 87;
	constexpr uint16 I2C_3_EVENT															= 88;
	constexpr uint16 I2C_3_ERROR															= 89;
	constexpr uint16 USB_HS_EP1_OUT														= 90;
	constexpr uint16 USB_HS_EP1_IN														= 91;
	constexpr uint16 USB_HS_WAKEUP														= 92;
	constexpr uint16 USB_HS																		= 93;
	constexpr uint16 DCMI																			= 94;
	constexpr uint16 CRYPTO																		= 95;
	constexpr uint16 HASH_RNG																	= 96;
	constexpr uint16 FPU																			= 97;
	constexpr uint16 UART_7																		= 98;
	constexpr uint16 UART_8																		= 99;
	constexpr uint16 SPI_4																		= 100;
	constexpr uint16 SPI_5																		= 101;
	constexpr uint16 SPI_6																		= 102;
	constexpr uint16 SAI_1																		= 103;
	constexpr uint16 LTDC																			= 104;
	constexpr uint16 LTDC_ERROR																= 105;
	constexpr uint16 DMA2D																		= 106;
	constexpr uint16 SAI_2																		= 107;
	constexpr uint16 QUADSPI																	= 108;
	constexpr uint16 LP_TIMER_1																= 109;
	constexpr uint16 HDMI_CEC																	= 110;
	constexpr uint16 I2C_4_EVENT															= 111;
	constexpr uint16 I2C_4_ERROR															= 112;
	constexpr uint16 SPDIF																		= 113;
	constexpr uint16 USB_FS_EP1_OUT														= 114;
	constexpr uint16 USB_FS_EP1_IN														= 115;
	constexpr uint16 USB_FS_WAKEUP														= 116;
	constexpr uint16 USB_FS																		= 117;
	constexpr uint16 DMAMUX_1_OVERRUN													= 118;
	constexpr uint16 HR_TIMER_MASTER													= 119;
	constexpr uint16 HR_TIMER_A																= 120;
	constexpr uint16 HR_TIMER_B																= 121;
	constexpr uint16 HR_TIMER_C																= 122;
	constexpr uint16 HR_TIMER_D																= 123;
	constexpr uint16 HR_TIMER_E 															= 124;
	constexpr uint16 HR_TIMER_FAULT														= 125;
	constexpr uint16 DFSDM_FILTER_0														= 126;
	constexpr uint16 DFSDM_FILTER_1														= 127;
	constexpr uint16 DFSDM_FILTER_2														= 128;
	constexpr uint16 DFSDM_FILTER_3														= 129;
	constexpr uint16 SAI_3																		= 130;
	constexpr uint16 SWPMI																		= 131;
	constexpr uint16 TIMER_15																	= 132;
	constexpr uint16 TIMER_16																	= 133;
	constexpr uint16 TIMER_17																	= 134;
	constexpr uint16 MDIOS_WAKEUP															= 135;
	constexpr uint16 MDIOS																		= 136;
	constexpr uint16 JPEG																			= 137;
	constexpr uint16 MDMA																			= 138;
	
	constexpr uint16 SDMMC_2																	= 140;
	constexpr uint16 HSEM																			= 141;
	
	constexpr uint16 ADC_3																		= 143;
	constexpr uint16 DMAMUX_2_OVERRUN													= 144;
	constexpr uint16 BDMA_CH0																	= 145;
	constexpr uint16 BDMA_CH1																	= 146;
	constexpr uint16 BDMA_CH2																	= 147;
	constexpr uint16 BDMA_CH3																	= 148;
	constexpr uint16 BDMA_CH4																	= 149;
	constexpr uint16 BDMA_CH5																	= 150;
	constexpr uint16 BDMA_CH6																	= 151;
	constexpr uint16 BDMA_CH7																	= 152;
	constexpr uint16 COMP_1_2																	= 153;
	constexpr uint16 LP_TIMER_2																= 154;
	constexpr uint16 LP_TIMER_3																= 155;
	constexpr uint16 LP_TIMER_4																= 156;
	constexpr uint16 LP_TIMER_5																= 157;
	constexpr uint16 LP_UART																	= 158;
	constexpr uint16 WWDG_RESET																= 159;
	constexpr uint16 CRS 																			= 160;
	constexpr uint16 RAM_ECC																	= 161;
	constexpr uint16 SAI_4																		= 162;
	
	
	constexpr uint16 WAKEUP_PIN_0_TO_5												= 165;
};



namespace MCU
{
	namespace BASE
	{
		constexpr uint32 PERIPHERAL									= 0x40000000;
		
		constexpr uint32 APB1					        			= PERIPHERAL + 0x00000000;
		constexpr uint32 APB2					        			= PERIPHERAL + 0x00010000;
		constexpr uint32 APB3					        			= PERIPHERAL + 0x10000000;
		constexpr uint32 APB4					        			= PERIPHERAL + 0x18000000;

		constexpr uint32 AHB1					        			= PERIPHERAL + 0x00020000;
		constexpr uint32 AHB2					        			= PERIPHERAL + 0x08022800;
		constexpr uint32 AHB3					        			= PERIPHERAL + 0x11000000;
		constexpr uint32 AHB4					        			= PERIPHERAL + 0x18020000;
		
		
		
		
		
		constexpr uint32 DBGMCU											= 						 0x5C001000;
		constexpr uint32 DCMI												= PERIPHERAL + 0x08020000;
		constexpr uint32 CRYPTO											= PERIPHERAL + 0x08021000;
		constexpr uint32 HASH												= PERIPHERAL + 0x08021400;
		constexpr uint32 RNG												= PERIPHERAL + 0x08021800;
		constexpr uint32 SDMMC_2										= PERIPHERAL + 0x08022400;
		constexpr uint32 QUADSPI_FIFO								= 				   	 0x90000000;
		
		constexpr uint32 TIMER_2										= APB1 + 0x00000000;
		constexpr uint32 TIMER_3										= APB1 + 0x00000400;
		constexpr uint32 TIMER_4										= APB1 + 0x00000800;
		constexpr uint32 TIMER_5										= APB1 + 0x00000C00;
		constexpr uint32 TIMER_6										= APB1 + 0x00001000;
		constexpr uint32 TIMER_7										= APB1 + 0x00001400;
		constexpr uint32 TIMER_12										= APB1 + 0x00001800;
		constexpr uint32 TIMER_13										= APB1 + 0x00001C00;
		constexpr uint32 TIMER_14										= APB1 + 0x00002000;
		constexpr uint32 LP_TIMER_1									= APB1 + 0x00002400;
		constexpr uint32 SPI_2											= APB1 + 0x00003800;
		constexpr uint32 SPI_3											= APB1 + 0x00003C00;
		constexpr uint32 SPDIFRX										= APB1 + 0x00004000;
		constexpr uint32 USART_2										= APB1 + 0x00004400;
		constexpr uint32 USART_3										= APB1 + 0x00004800;
		constexpr uint32 UART_4											= APB1 + 0x00004C00;
		constexpr uint32 UART_5											= APB1 + 0x00005000;
		constexpr uint32 I2C_1											= APB1 + 0x00005400;
		constexpr uint32 I2C_2											= APB1 + 0x00005800;
		constexpr uint32 I2C_3											= APB1 + 0x00005C00;
		constexpr uint32 HDMI_CEC										= APB1 + 0x00006C00;
		constexpr uint32 DAC												= APB1 + 0x00007400;
		constexpr uint32 UART_7											= APB1 + 0x00007800;
		constexpr uint32 UART_8											= APB1 + 0x00007C00;
		constexpr uint32 CRS												= APB1 + 0x00008400;
		constexpr uint32 SWPMI											= APB1 + 0x00008800;
		constexpr uint32 OP													= APB1 + 0x00009000;
		constexpr uint32 MDIOS											= APB1 + 0x00009400;
		constexpr uint32 FDCAN_1										= APB1 + 0x0000A000;
		constexpr uint32 FDCAN_2										= APB1 + 0x0000A400;
		constexpr uint32 FDCAN_CCU									= APB1 + 0x0000A800;
		constexpr uint32 FDCAN_MSG_RAM							= APB1 + 0x0000AC00;
		
		constexpr uint32 TIMER_1			    					= APB2 + 0x00000000;
		constexpr uint32 TIMER_8			    					= APB2 + 0x00000400;
		constexpr uint32 USART_1			   					 	= APB2 + 0x00001000;
		constexpr uint32 USART_6			  					  = APB2 + 0x00001400;
		constexpr uint32 SPI_1			   					 		= APB2 + 0x00003000;
		constexpr uint32 SPI_4			   					 		= APB2 + 0x00003400;
		constexpr uint32 TIMER_15			 					   	= APB2 + 0x00004000;
		constexpr uint32 TIMER_16			 					   	= APB2 + 0x00004400;
		constexpr uint32 TIMER_17			 					   	= APB2 + 0x00004800;
		constexpr uint32 SPI_5			  					  	= APB2 + 0x00005000;
		constexpr uint32 SAI_1			 					   		= APB2 + 0x00005800;
		constexpr uint32 SAI_2			 								= APB2 + 0x00005C00;
		constexpr uint32 SAI_3			 					   		= APB2 + 0x00006000;
		constexpr uint32 DFSDM			  					  	= APB2 + 0x00007000;
		constexpr uint32 HR_TIMER								    = APB2 + 0x00007400;
			constexpr uint32 HR_TIMER_MASTER						= HR_TIMER + 0x000;
			constexpr uint32 HR_TIMER_A									= HR_TIMER + 0x080;
			constexpr uint32 HR_TIMER_B									= HR_TIMER + 0x100;
			constexpr uint32 HR_TIMER_C									= HR_TIMER + 0x180;
			constexpr uint32 HR_TIMER_D									= HR_TIMER + 0x200;
			constexpr uint32 HR_TIMER_E									= HR_TIMER + 0x280;
			constexpr uint32 HR_TIMER_COMMON						= HR_TIMER + 0x380;
		
		constexpr uint32 LTDC				    						= APB3 + 0x00001000;
		constexpr uint32 WWDG			    							= APB3 + 0x00003000;
		
		constexpr uint32 EXTI	    									= APB4 + 0x00000000;
		constexpr uint32 SYSCFG	    								= APB4 + 0x00000400;
		constexpr uint32 LP_UART_1	    						= APB4 + 0x00000C00;
		constexpr uint32 SPI_6	    								= APB4 + 0x00001400;
		constexpr uint32 I2C_4	    								= APB4 + 0x00001C00;
		constexpr uint32 LP_TIMER_2	    						= APB4 + 0x00002400;
		constexpr uint32 LP_TIMER_3	    						= APB4 + 0x00002800;
		constexpr uint32 LP_TIMER_4	    						= APB4 + 0x00002C00;
		constexpr uint32 LP_TIMER_5	   					 		= APB4 + 0x00003000;
		constexpr uint32 COMP	    									= APB4 + 0x00003800;
		constexpr uint32 VREF	    									= APB4 + 0x00003C00;
		constexpr uint32 RTC		    								= APB4 + 0x00004000;
		constexpr uint32 IWDG	    									= APB4 + 0x00004800;
		constexpr uint32 SAI_4	    								= APB4 + 0x00005400;
		
		constexpr uint32 DMA_1									    = AHB1 + 0x00000000;
		constexpr uint32 DMA_2											= AHB1 + 0x00000400;
		constexpr uint32 DMAMUX_1								    = AHB1 + 0x00000800;
		constexpr uint32 ADC_1_2										= AHB1 + 0x00002000;
			constexpr uint32 ADC_1										= ADC_1_2 + 0x000;
			constexpr uint32 ADC_2										= ADC_1_2 + 0x100;
			constexpr uint32 ADC_1_2_COMMON						= ADC_1_2 + 0x300;
		
		constexpr uint32 ETH				 					   		= AHB1 + 0x00008000;
		constexpr uint32 USB_1									    = AHB1 + 0x00020000;
		constexpr uint32 USB_2									    = AHB1 + 0x00060000;
		
		constexpr uint32 SDMMC_2_DELAY							= AHB2 + 0x00000000;
		
		constexpr uint32 GPV				        				= AHB3 + 0x00000000;
		constexpr uint32 MDMA				        				= AHB3 + 0x01000000;
		constexpr uint32 DMA2D				        			= AHB3 + 0x01001000;
		constexpr uint32 FLASH				        			= AHB3 + 0x01002000;
		constexpr uint32 JPEG				        				= AHB3 + 0x01003000;
		constexpr uint32 FMC				        				= AHB3 + 0x01004000;
		constexpr uint32 QUADSPI_CONTROL				    = AHB3 + 0x01005000;
		constexpr uint32 QUADSPI_DELAY							= AHB3 + 0x01006000;
		constexpr uint32 SDMMC_1										= AHB3 + 0x01007000;
		constexpr uint32 SDMMC_1_DELAY							= AHB3 + 0x01008000;
		
		constexpr uint32 GPIO_A				        			= AHB4 + 0x00000000;
		constexpr uint32 GPIO_B				        			= AHB4 + 0x00000400;
		constexpr uint32 GPIO_C				        			= AHB4 + 0x00000800;
		constexpr uint32 GPIO_D				        			= AHB4 + 0x00000C00;
		constexpr uint32 GPIO_E				        			= AHB4 + 0x00001000;
		constexpr uint32 GPIO_F				        			= AHB4 + 0x00001400;
		constexpr uint32 GPIO_G				        			= AHB4 + 0x00001800;
		constexpr uint32 GPIO_H				   			      = AHB4 + 0x00001C00;
		constexpr uint32 GPIO_I				   			      = AHB4 + 0x00002000;
		constexpr uint32 GPIO_J				  			      = AHB4 + 0x00002400;
		constexpr uint32 GPIO_K				 			        = AHB4 + 0x00002800;
		constexpr uint32 RCC				   			    	 	= AHB4 + 0x00004400;
		constexpr uint32 PWR				   			    	  = AHB4 + 0x00004800;
		constexpr uint32 CRC				   			     		= AHB4 + 0x00004C00;
		constexpr uint32 BDMA				   			     		= AHB4 + 0x00005400;
		constexpr uint32 DMAMUX_2							    	= AHB4 + 0x00005800;
		constexpr uint32 ADC_3				      			  = AHB4 + 0x00006000;
			constexpr uint32 ADC_3_COMMON							= ADC_3 + 0x300;
		constexpr uint32 HSEM				    			    	= AHB4 + 0x00006400;
	};
	
	
	
	namespace DBGMCU
	{
		volatile uint32* const IDC			      			= (volatile uint32* const) (BASE::DBGMCU + 0x00);
		volatile uint32* const CR			        			= (volatile uint32* const) (BASE::DBGMCU + 0x04);
		volatile uint32* const APB3_FZ			  			= (volatile uint32* const) (BASE::DBGMCU + 0x34);
		volatile uint32* const APB1_FZ			  			= (volatile uint32* const) (BASE::DBGMCU + 0x3C);
		volatile uint32* const APB2_FZ			  			= (volatile uint32* const) (BASE::DBGMCU + 0x4C);
		volatile uint32* const APB4_FZ			  			= (volatile uint32* const) (BASE::DBGMCU + 0x54);
	};
	
	namespace DCMI
	{
		volatile uint32* const CR			        			= (volatile uint32* const) (BASE::DCMI + 0x00);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::DCMI + 0x04);
		volatile uint32* const RIS			        		= (volatile uint32* const) (BASE::DCMI + 0x08);
		volatile uint32* const IER			        		= (volatile uint32* const) (BASE::DCMI + 0x0C);
		volatile uint32* const MIS			        		= (volatile uint32* const) (BASE::DCMI + 0x10);
		volatile uint32* const ICR			        		= (volatile uint32* const) (BASE::DCMI + 0x14);
		volatile uint32* const ESCR			        		= (volatile uint32* const) (BASE::DCMI + 0x18);
		volatile uint32* const ESUR			        		= (volatile uint32* const) (BASE::DCMI + 0x1C);
		volatile uint32* const CWSTRT			      		= (volatile uint32* const) (BASE::DCMI + 0x20);
		volatile uint32* const CWSIZE			      		= (volatile uint32* const) (BASE::DCMI + 0x24);
		volatile uint32* const DR			        			= (volatile uint32* const) (BASE::DCMI + 0x28);
	};
	
	namespace CRYPTO
	{
		volatile uint32* const CR			        			= (volatile uint32* const) (BASE::CRYPTO + 0x00);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::CRYPTO + 0x04);
		volatile uint32* const DIN			       			= (volatile uint32* const) (BASE::CRYPTO + 0x08);
		volatile uint32* const DOUT			       			= (volatile uint32* const) (BASE::CRYPTO + 0x0C);
		volatile uint32* const DMACR			      		= (volatile uint32* const) (BASE::CRYPTO + 0x10);
		volatile uint32* const IMSCR			      		= (volatile uint32* const) (BASE::CRYPTO + 0x14);
		volatile uint32* const RISR			       			= (volatile uint32* const) (BASE::CRYPTO + 0x18);
		volatile uint32* const MISR			       			= (volatile uint32* const) (BASE::CRYPTO + 0x1C);
		volatile uint32* const K0LR			       			= (volatile uint32* const) (BASE::CRYPTO + 0x20);
		volatile uint32* const K0RR			       			= (volatile uint32* const) (BASE::CRYPTO + 0x24);
		volatile uint32* const K1LR			       			= (volatile uint32* const) (BASE::CRYPTO + 0x28);
		volatile uint32* const K1RR			       			= (volatile uint32* const) (BASE::CRYPTO + 0x2C);
		volatile uint32* const K2LR			       			= (volatile uint32* const) (BASE::CRYPTO + 0x30);
		volatile uint32* const K2RR			       			= (volatile uint32* const) (BASE::CRYPTO + 0x34);
		volatile uint32* const K3LR			       			= (volatile uint32* const) (BASE::CRYPTO + 0x38);
		volatile uint32* const K3RR			       			= (volatile uint32* const) (BASE::CRYPTO + 0x3C);
		volatile uint32* const IV0LR			      		= (volatile uint32* const) (BASE::CRYPTO + 0x40);
		volatile uint32* const IV0RR			      		= (volatile uint32* const) (BASE::CRYPTO + 0x44);
		volatile uint32* const IV1LR			      		= (volatile uint32* const) (BASE::CRYPTO + 0x48);
		volatile uint32* const IV1RR			      		= (volatile uint32* const) (BASE::CRYPTO + 0x4C);
		volatile uint32* const CSGCMCCM0R			  		= (volatile uint32* const) (BASE::CRYPTO + 0x50);
		volatile uint32* const CSGCMCCM1R			  		= (volatile uint32* const) (BASE::CRYPTO + 0x54);
		volatile uint32* const CSGCMCCM2R			  		= (volatile uint32* const) (BASE::CRYPTO + 0x58);
		volatile uint32* const CSGCMCCM3R			  		= (volatile uint32* const) (BASE::CRYPTO + 0x5C);
		volatile uint32* const CSGCMCCM4R			  		= (volatile uint32* const) (BASE::CRYPTO + 0x60);
		volatile uint32* const CSGCMCCM5R			  		= (volatile uint32* const) (BASE::CRYPTO + 0x64);
		volatile uint32* const CSGCMCCM6R			  		= (volatile uint32* const) (BASE::CRYPTO + 0x68);
		volatile uint32* const CSGCMCCM7R			  		= (volatile uint32* const) (BASE::CRYPTO + 0x6C);
		volatile uint32* const CSGCM0R			    		= (volatile uint32* const) (BASE::CRYPTO + 0x70);
		volatile uint32* const CSGCM1R			    		= (volatile uint32* const) (BASE::CRYPTO + 0x74);
		volatile uint32* const CSGCM2R			    		= (volatile uint32* const) (BASE::CRYPTO + 0x78);
		volatile uint32* const CSGCM3R			    		= (volatile uint32* const) (BASE::CRYPTO + 0x7C);
		volatile uint32* const CSGCM4R			    		= (volatile uint32* const) (BASE::CRYPTO + 0x80);
		volatile uint32* const CSGCM5R			    		= (volatile uint32* const) (BASE::CRYPTO + 0x84);
		volatile uint32* const CSGCM6R			    		= (volatile uint32* const) (BASE::CRYPTO + 0x88);
		volatile uint32* const CSGCM7R			    		= (volatile uint32* const) (BASE::CRYPTO + 0x8C);
	}
	
	namespace HASH
	{
		volatile uint32* const CR					      		= (volatile uint32* const) (BASE::HASH + 0x000);
		volatile uint32* const DIN					    		= (volatile uint32* const) (BASE::HASH + 0x004);
		volatile uint32* const STR					    		= (volatile uint32* const) (BASE::HASH + 0x008);
		volatile uint32* const HR0					    		= (volatile uint32* const) (BASE::HASH + 0x00C);
		volatile uint32* const HR1					    		= (volatile uint32* const) (BASE::HASH + 0x010);
		volatile uint32* const HR2					    		= (volatile uint32* const) (BASE::HASH + 0x014);
		volatile uint32* const HR3					    		= (volatile uint32* const) (BASE::HASH + 0x018);
		volatile uint32* const HR4					    		= (volatile uint32* const) (BASE::HASH + 0x01C);
		volatile uint32* const IMR					    		= (volatile uint32* const) (BASE::HASH + 0x020);
		volatile uint32* const SR					      		= (volatile uint32* const) (BASE::HASH + 0x024);
		volatile uint32* const CSR0					    		= (volatile uint32* const) (BASE::HASH + 0x0F8);
		volatile uint32* const CSR1					    		= (volatile uint32* const) (BASE::HASH + 0x0FC);
		volatile uint32* const CSR2					    		= (volatile uint32* const) (BASE::HASH + 0x100);
		volatile uint32* const CSR3					    		= (volatile uint32* const) (BASE::HASH + 0x104);
		volatile uint32* const CSR4					    		= (volatile uint32* const) (BASE::HASH + 0x108);
		volatile uint32* const CSR5					    		= (volatile uint32* const) (BASE::HASH + 0x10C);
		volatile uint32* const CSR6					    		= (volatile uint32* const) (BASE::HASH + 0x110);
		volatile uint32* const CSR7					    		= (volatile uint32* const) (BASE::HASH + 0x114);
		volatile uint32* const CSR8					    		= (volatile uint32* const) (BASE::HASH + 0x118);
		volatile uint32* const CSR9					    		= (volatile uint32* const) (BASE::HASH + 0x11C);
		volatile uint32* const CSR10					  		= (volatile uint32* const) (BASE::HASH + 0x120);
		volatile uint32* const CSR11					  		= (volatile uint32* const) (BASE::HASH + 0x124);
		volatile uint32* const CSR12					  		= (volatile uint32* const) (BASE::HASH + 0x128);
		volatile uint32* const CSR13					  		= (volatile uint32* const) (BASE::HASH + 0x12C);
		volatile uint32* const CSR14					  		= (volatile uint32* const) (BASE::HASH + 0x130);
		volatile uint32* const CSR15					  		= (volatile uint32* const) (BASE::HASH + 0x134);
		volatile uint32* const CSR16					  		= (volatile uint32* const) (BASE::HASH + 0x138);
		volatile uint32* const CSR17					  		= (volatile uint32* const) (BASE::HASH + 0x13C);
		volatile uint32* const CSR18					  		= (volatile uint32* const) (BASE::HASH + 0x140);
		volatile uint32* const CSR19					  		= (volatile uint32* const) (BASE::HASH + 0x144);
		volatile uint32* const CSR20					  		= (volatile uint32* const) (BASE::HASH + 0x148);
		volatile uint32* const CSR21					  		= (volatile uint32* const) (BASE::HASH + 0x14C);
		volatile uint32* const CSR22					  		= (volatile uint32* const) (BASE::HASH + 0x150);
		volatile uint32* const CSR23					  		= (volatile uint32* const) (BASE::HASH + 0x154);
		volatile uint32* const CSR24					  		= (volatile uint32* const) (BASE::HASH + 0x158);
		volatile uint32* const CSR25					  		= (volatile uint32* const) (BASE::HASH + 0x15C);
		volatile uint32* const CSR26					  		= (volatile uint32* const) (BASE::HASH + 0x160);
		volatile uint32* const CSR27					  		= (volatile uint32* const) (BASE::HASH + 0x164);
		volatile uint32* const CSR28					  		= (volatile uint32* const) (BASE::HASH + 0x168);
		volatile uint32* const CSR29					  		= (volatile uint32* const) (BASE::HASH + 0x16C);
		volatile uint32* const CSR30					  		= (volatile uint32* const) (BASE::HASH + 0x170);
		volatile uint32* const CSR31					  		= (volatile uint32* const) (BASE::HASH + 0x174);
		volatile uint32* const CSR32					  		= (volatile uint32* const) (BASE::HASH + 0x178);
		volatile uint32* const CSR33					  		= (volatile uint32* const) (BASE::HASH + 0x17C);
		volatile uint32* const CSR34					  		= (volatile uint32* const) (BASE::HASH + 0x180);
		volatile uint32* const CSR35					  		= (volatile uint32* const) (BASE::HASH + 0x184);
		volatile uint32* const CSR36					  		= (volatile uint32* const) (BASE::HASH + 0x188);
		volatile uint32* const CSR37					  		= (volatile uint32* const) (BASE::HASH + 0x18C);
		volatile uint32* const CSR38					  		= (volatile uint32* const) (BASE::HASH + 0x190);
		volatile uint32* const CSR39					  		= (volatile uint32* const) (BASE::HASH + 0x194);
		volatile uint32* const CSR40					  		= (volatile uint32* const) (BASE::HASH + 0x198);
		volatile uint32* const CSR41					  		= (volatile uint32* const) (BASE::HASH + 0x19C);
		volatile uint32* const CSR42					  		= (volatile uint32* const) (BASE::HASH + 0x1A0);
		volatile uint32* const CSR43					  		= (volatile uint32* const) (BASE::HASH + 0x1A4);
		volatile uint32* const CSR44					  		= (volatile uint32* const) (BASE::HASH + 0x1A8);
		volatile uint32* const CSR45					  		= (volatile uint32* const) (BASE::HASH + 0x1AC);
		volatile uint32* const CSR46					  		= (volatile uint32* const) (BASE::HASH + 0x1B0);
		volatile uint32* const CSR47					  		= (volatile uint32* const) (BASE::HASH + 0x1B4);
		volatile uint32* const CSR48					  		= (volatile uint32* const) (BASE::HASH + 0x1B8);
		volatile uint32* const CSR49					  		= (volatile uint32* const) (BASE::HASH + 0x1BC);
		volatile uint32* const CSR50					  		= (volatile uint32* const) (BASE::HASH + 0x1C0);
		volatile uint32* const CSR51					  		= (volatile uint32* const) (BASE::HASH + 0x1C4);
		volatile uint32* const CSR52					  		= (volatile uint32* const) (BASE::HASH + 0x1C8);
		volatile uint32* const CSR53					  		= (volatile uint32* const) (BASE::HASH + 0x1CC);
		volatile uint32* const HR0_ALT							= (volatile uint32* const) (BASE::HASH + 0x310);
		volatile uint32* const HR1_ALT							= (volatile uint32* const) (BASE::HASH + 0x314);
		volatile uint32* const HR2_ALT							= (volatile uint32* const) (BASE::HASH + 0x318);
		volatile uint32* const HR3_ALT							= (volatile uint32* const) (BASE::HASH + 0x31C);
		volatile uint32* const HR4_ALT				  		= (volatile uint32* const) (BASE::HASH + 0x320);
		volatile uint32* const HR5					    		= (volatile uint32* const) (BASE::HASH + 0x324);
		volatile uint32* const HR6					    		= (volatile uint32* const) (BASE::HASH + 0x328);
		volatile uint32* const HR7					    		= (volatile uint32* const) (BASE::HASH + 0x32C);
	};
	
	namespace RNG
	{
		volatile uint32* const CR					      		= (volatile uint32* const) (BASE::RNG + 0x00);
		volatile uint32* const SR					      		= (volatile uint32* const) (BASE::RNG + 0x04);
		volatile uint32* const DR					      		= (volatile uint32* const) (BASE::RNG + 0x08);
	};
	
	namespace SDMMC_2
	{
		volatile uint32* const POWER					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x00);
		volatile uint32* const CLKCR					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x04);
		volatile uint32* const ARGR					    		= (volatile uint32* const) (BASE::SDMMC_2 + 0x08);
		volatile uint32* const CMDR					    		= (volatile uint32* const) (BASE::SDMMC_2 + 0x0C);
		volatile uint32* const RESP_CMDR						= (volatile uint32* const) (BASE::SDMMC_2 + 0x10);
		volatile uint32* const RESP_1R							= (volatile uint32* const) (BASE::SDMMC_2 + 0x14);
		volatile uint32* const RESP_2R							= (volatile uint32* const) (BASE::SDMMC_2 + 0x18);
		volatile uint32* const RESP_3R							= (volatile uint32* const) (BASE::SDMMC_2 + 0x1C);
		volatile uint32* const RESP_4R							= (volatile uint32* const) (BASE::SDMMC_2 + 0x20);
		volatile uint32* const DTIMER					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x24);
		volatile uint32* const DLENR					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x28);
		volatile uint32* const DCTRLR					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x2C);
		volatile uint32* const DCNTR					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x30);
		volatile uint32* const STAR					    		= (volatile uint32* const) (BASE::SDMMC_2 + 0x34);
		volatile uint32* const ICR					    		= (volatile uint32* const) (BASE::SDMMC_2 + 0x38);
		volatile uint32* const MASKR					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x3C);
		volatile uint32* const ACKTIMER							= (volatile uint32* const) (BASE::SDMMC_2 + 0x40);
		volatile uint32* const IDMA_CTRLR						= (volatile uint32* const) (BASE::SDMMC_2 + 0x50);
		volatile uint32* const IDMA_BSIZER					= (volatile uint32* const) (BASE::SDMMC_2 + 0x54);
		volatile uint32* const IDMA_BASE0R					= (volatile uint32* const) (BASE::SDMMC_2 + 0x58);
		volatile uint32* const IDMA_BASE1R					= (volatile uint32* const) (BASE::SDMMC_2 + 0x5C);
		volatile uint32* const FIFO0R					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x80);
		volatile uint32* const FIFO1R					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x84);
		volatile uint32* const FIFO2R					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x88);
		volatile uint32* const FIFO3R					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x8C);
		volatile uint32* const FIFO4R					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x90);
		volatile uint32* const FIFO5R					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x94);
		volatile uint32* const FIFO6R					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x98);
		volatile uint32* const FIFO7R					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0x9C);
		volatile uint32* const FIFO8R					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0xA0);
		volatile uint32* const FIFO9R					  		= (volatile uint32* const) (BASE::SDMMC_2 + 0xA4);
		volatile uint32* const FIFO10R							= (volatile uint32* const) (BASE::SDMMC_2 + 0xA8);
		volatile uint32* const FIFO11R							= (volatile uint32* const) (BASE::SDMMC_2 + 0xAC);
		volatile uint32* const FIFO12R							= (volatile uint32* const) (BASE::SDMMC_2 + 0xB0);
		volatile uint32* const FIFO13R							= (volatile uint32* const) (BASE::SDMMC_2 + 0xB4);
		volatile uint32* const FIFO14R							= (volatile uint32* const) (BASE::SDMMC_2 + 0xB8);
		volatile uint32* const FIFO15R							= (volatile uint32* const) (BASE::SDMMC_2 + 0xBC);
	};
	
	namespace TIMER_2
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x04);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x08);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_2 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x14);
		volatile uint32* const CCMR1			      		= (volatile uint32* const) (BASE::TIMER_2 + 0x18);
		volatile uint32* const CCMR2			      		= (volatile uint32* const) (BASE::TIMER_2 + 0x1C);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x2C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x34);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x38);
		volatile uint32* const CCR3			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x3C);
		volatile uint32* const CCR4			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x40);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x48);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x4C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x60);
		volatile uint32* const TISEL			      		= (volatile uint32* const) (BASE::TIMER_2 + 0x68);
	};
	
	namespace TIMER_3
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x04);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x08);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_3 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x14);
		volatile uint32* const CCMR1			      		= (volatile uint32* const) (BASE::TIMER_3 + 0x18);
		volatile uint32* const CCMR2			      		= (volatile uint32* const) (BASE::TIMER_3 + 0x1C);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x2C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x34);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x38);
		volatile uint32* const CCR3			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x3C);
		volatile uint32* const CCR4			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x40);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x48);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x4C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x60);
		volatile uint32* const TISEL			      		= (volatile uint32* const) (BASE::TIMER_3 + 0x68);
	};
	
	namespace TIMER_4
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x04);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x08);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_4 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x14);
		volatile uint32* const CCMR1			      		= (volatile uint32* const) (BASE::TIMER_4 + 0x18);
		volatile uint32* const CCMR2			      		= (volatile uint32* const) (BASE::TIMER_4 + 0x1C);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x2C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x34);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x38);
		volatile uint32* const CCR3			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x3C);
		volatile uint32* const CCR4			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x40);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x48);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x4C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x60);
		volatile uint32* const TISEL			      		= (volatile uint32* const) (BASE::TIMER_4 + 0x68);
	};
	
	namespace TIMER_5
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x04);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x08);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_5 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x14);
		volatile uint32* const CCMR1			      		= (volatile uint32* const) (BASE::TIMER_5 + 0x18);
		volatile uint32* const CCMR2			      		= (volatile uint32* const) (BASE::TIMER_5 + 0x1C);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x2C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x34);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x38);
		volatile uint32* const CCR3			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x3C);
		volatile uint32* const CCR4			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x40);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x48);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x4C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x60);
		volatile uint32* const TISEL			      		= (volatile uint32* const) (BASE::TIMER_5 + 0x68);
	};
	
	namespace TIMER_6
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_6 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_6 + 0x04);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_6 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_6 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_6 + 0x14);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_6 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_6 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_6 + 0x2C);
	};
	
	namespace TIMER_7
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_7 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_7 + 0x04);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_7 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_7 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_7 + 0x14);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_7 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_7 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_7 + 0x2C);
	};
	
	namespace TIMER_12
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x04);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x08);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_12 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x14);
		volatile uint32* const CCMR1			      		= (volatile uint32* const) (BASE::TIMER_12 + 0x18);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x2C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x34);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_12 + 0x38);
		volatile uint32* const TISEL			      		= (volatile uint32* const) (BASE::TIMER_12 + 0x68);
	};
	
	namespace TIMER_13
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_13 + 0x00);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_13 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_13 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_13 + 0x14);
		volatile uint32* const CCMR1			      		= (volatile uint32* const) (BASE::TIMER_13 + 0x18);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_13 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_13 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_13 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_13 + 0x2C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_13 + 0x34);
		volatile uint32* const TISEL			      		= (volatile uint32* const) (BASE::TIMER_13 + 0x68);
	};
	
	namespace TIMER_14
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x00);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_14 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x14);
		volatile uint32* const CCMR1			      		= (volatile uint32* const) (BASE::TIMER_14 + 0x18);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x2C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x34);
		volatile uint32* const TISEL			      		= (volatile uint32* const) (BASE::TIMER_14 + 0x68);
	};
	
	namespace LP_TIMER_1
	{
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x00);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x04);
		volatile uint32* const IER				      		= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x08);
		volatile uint32* const CFGR				      		= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x0C);
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x10);
		volatile uint32* const CMP				      		= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x14);
		volatile uint32* const ARR				      		= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x18);
		volatile uint32* const CNT				      		= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x1C);
		volatile uint32* const CFGR2				    		= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x24);
	};
	
	namespace SPI_2
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::SPI_2 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::SPI_2 + 0x04);
		volatile uint32* const CFG1				      		= (volatile uint32* const) (BASE::SPI_2 + 0x08);
		volatile uint32* const CFG2				      		= (volatile uint32* const) (BASE::SPI_2 + 0x0C);
		volatile uint32* const IER				      		= (volatile uint32* const) (BASE::SPI_2 + 0x10);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::SPI_2 + 0x14);
		volatile uint32* const IFCR				      		= (volatile uint32* const) (BASE::SPI_2 + 0x18);
		volatile uint32* const TXDR				      		= (volatile uint32* const) (BASE::SPI_2 + 0x20);
		volatile uint32* const RXDR				      		= (volatile uint32* const) (BASE::SPI_2 + 0x30);
		volatile uint32* const CRCPOLY				  		= (volatile uint32* const) (BASE::SPI_2 + 0x40);
		volatile uint32* const TXCRC				    		= (volatile uint32* const) (BASE::SPI_2 + 0x44);
		volatile uint32* const RXCRC				    		= (volatile uint32* const) (BASE::SPI_2 + 0x48);
		volatile uint32* const UDRDR				    		= (volatile uint32* const) (BASE::SPI_2 + 0x4C);
		volatile uint32* const CFGR				      		= (volatile uint32* const) (BASE::SPI_2 + 0x50);
	};
	
	namespace SPI_3
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::SPI_3 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::SPI_3 + 0x04);
		volatile uint32* const CFG1				      		= (volatile uint32* const) (BASE::SPI_3 + 0x08);
		volatile uint32* const CFG2				      		= (volatile uint32* const) (BASE::SPI_3 + 0x0C);
		volatile uint32* const IER				      		= (volatile uint32* const) (BASE::SPI_3 + 0x10);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::SPI_3 + 0x14);
		volatile uint32* const IFCR				      		= (volatile uint32* const) (BASE::SPI_3 + 0x18);
		volatile uint32* const TXDR				      		= (volatile uint32* const) (BASE::SPI_3 + 0x20);
		volatile uint32* const RXDR				      		= (volatile uint32* const) (BASE::SPI_3 + 0x30);
		volatile uint32* const CRCPOLY				  		= (volatile uint32* const) (BASE::SPI_3 + 0x40);
		volatile uint32* const TXCRC				    		= (volatile uint32* const) (BASE::SPI_3 + 0x44);
		volatile uint32* const RXCRC				    		= (volatile uint32* const) (BASE::SPI_3 + 0x48);
		volatile uint32* const UDRDR				    		= (volatile uint32* const) (BASE::SPI_3 + 0x4C);
		volatile uint32* const CFGR				      		= (volatile uint32* const) (BASE::SPI_3 + 0x50);
	};
	
	namespace SPDIFRX
	{
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::SPDIFRX + 0x00);
		volatile uint32* const IMR				      		= (volatile uint32* const) (BASE::SPDIFRX + 0x04);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::SPDIFRX + 0x08);
		volatile uint32* const IFCR				      		= (volatile uint32* const) (BASE::SPDIFRX + 0x0C);
		volatile uint32* const FMT_DR				    		= (volatile uint32* const) (BASE::SPDIFRX + 0x10);
		volatile uint32* const CSR				      		= (volatile uint32* const) (BASE::SPDIFRX + 0x14);
		volatile uint32* const DIR				      		= (volatile uint32* const) (BASE::SPDIFRX + 0x18);
	};
	
	namespace USART_2
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::USART_2 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::USART_2 + 0x04);
		volatile uint32* const CR3				      		= (volatile uint32* const) (BASE::USART_2 + 0x08);
		volatile uint32* const BRR				      		= (volatile uint32* const) (BASE::USART_2 + 0x0C);
		volatile uint32* const GTPR				      		= (volatile uint32* const) (BASE::USART_2 + 0x10);
		volatile uint32* const RTOR				      		= (volatile uint32* const) (BASE::USART_2 + 0x14);
		volatile uint32* const RQR				      		= (volatile uint32* const) (BASE::USART_2 + 0x18);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::USART_2 + 0x1C);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::USART_2 + 0x20);
		volatile uint32* const RDR				      		= (volatile uint32* const) (BASE::USART_2 + 0x24);
		volatile uint32* const TDR				      		= (volatile uint32* const) (BASE::USART_2 + 0x28);
		volatile uint32* const PRESC				    		= (volatile uint32* const) (BASE::USART_2 + 0x2C);
	};
	
	namespace USART_3
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::USART_3 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::USART_3 + 0x04);
		volatile uint32* const CR3				      		= (volatile uint32* const) (BASE::USART_3 + 0x08);
		volatile uint32* const BRR				      		= (volatile uint32* const) (BASE::USART_3 + 0x0C);
		volatile uint32* const GTPR				      		= (volatile uint32* const) (BASE::USART_3 + 0x10);
		volatile uint32* const RTOR				      		= (volatile uint32* const) (BASE::USART_3 + 0x14);
		volatile uint32* const RQR				      		= (volatile uint32* const) (BASE::USART_3 + 0x18);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::USART_3 + 0x1C);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::USART_3 + 0x20);
		volatile uint32* const RDR				      		= (volatile uint32* const) (BASE::USART_3 + 0x24);
		volatile uint32* const TDR				      		= (volatile uint32* const) (BASE::USART_3 + 0x28);
		volatile uint32* const PRESC				    		= (volatile uint32* const) (BASE::USART_3 + 0x2C);
	};
	
	namespace UART_4
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::UART_4 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::UART_4 + 0x04);
		volatile uint32* const CR3				      		= (volatile uint32* const) (BASE::UART_4 + 0x08);
		volatile uint32* const BRR				      		= (volatile uint32* const) (BASE::UART_4 + 0x0C);
		volatile uint32* const GTPR				      		= (volatile uint32* const) (BASE::UART_4 + 0x10);
		volatile uint32* const RTOR				      		= (volatile uint32* const) (BASE::UART_4 + 0x14);
		volatile uint32* const RQR				      		= (volatile uint32* const) (BASE::UART_4 + 0x18);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::UART_4 + 0x1C);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::UART_4 + 0x20);
		volatile uint32* const RDR				      		= (volatile uint32* const) (BASE::UART_4 + 0x24);
		volatile uint32* const TDR				      		= (volatile uint32* const) (BASE::UART_4 + 0x28);
		volatile uint32* const PRESC				    		= (volatile uint32* const) (BASE::UART_4 + 0x2C);
	};
	
	namespace UART_5
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::UART_5 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::UART_5 + 0x04);
		volatile uint32* const CR3				      		= (volatile uint32* const) (BASE::UART_5 + 0x08);
		volatile uint32* const BRR				      		= (volatile uint32* const) (BASE::UART_5 + 0x0C);
		volatile uint32* const GTPR				      		= (volatile uint32* const) (BASE::UART_5 + 0x10);
		volatile uint32* const RTOR				      		= (volatile uint32* const) (BASE::UART_5 + 0x14);
		volatile uint32* const RQR				      		= (volatile uint32* const) (BASE::UART_5 + 0x18);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::UART_5 + 0x1C);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::UART_5 + 0x20);
		volatile uint32* const RDR				      		= (volatile uint32* const) (BASE::UART_5 + 0x24);
		volatile uint32* const TDR				      		= (volatile uint32* const) (BASE::UART_5 + 0x28);
		volatile uint32* const PRESC				    		= (volatile uint32* const) (BASE::UART_5 + 0x2C);
	};
	
	namespace I2C_1
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::I2C_1 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::I2C_1 + 0x04);
		volatile uint32* const OAR1				      		= (volatile uint32* const) (BASE::I2C_1 + 0x08);
		volatile uint32* const OAR2				      		= (volatile uint32* const) (BASE::I2C_1 + 0x0C);
		volatile uint32* const TIMINGR				  		= (volatile uint32* const) (BASE::I2C_1 + 0x10);
		volatile uint32* const TIMEOUTR				  		= (volatile uint32* const) (BASE::I2C_1 + 0x14);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::I2C_1 + 0x18);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::I2C_1 + 0x1C);
		volatile uint32* const PECR				      		= (volatile uint32* const) (BASE::I2C_1 + 0x20);
		volatile uint32* const RXDR				      		= (volatile uint32* const) (BASE::I2C_1 + 0x24);
		volatile uint32* const TXDR				      		= (volatile uint32* const) (BASE::I2C_1 + 0x28);
	};
	
	namespace I2C_2
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::I2C_2 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::I2C_2 + 0x04);
		volatile uint32* const OAR1				      		= (volatile uint32* const) (BASE::I2C_2 + 0x08);
		volatile uint32* const OAR2				      		= (volatile uint32* const) (BASE::I2C_2 + 0x0C);
		volatile uint32* const TIMINGR				  		= (volatile uint32* const) (BASE::I2C_2 + 0x10);
		volatile uint32* const TIMEOUTR				  		= (volatile uint32* const) (BASE::I2C_2 + 0x14);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::I2C_2 + 0x18);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::I2C_2 + 0x1C);
		volatile uint32* const PECR				      		= (volatile uint32* const) (BASE::I2C_2 + 0x20);
		volatile uint32* const RXDR				      		= (volatile uint32* const) (BASE::I2C_2 + 0x24);
		volatile uint32* const TXDR				      		= (volatile uint32* const) (BASE::I2C_2 + 0x28);
	};
	
	namespace I2C_3
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::I2C_3 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::I2C_3 + 0x04);
		volatile uint32* const OAR1				      		= (volatile uint32* const) (BASE::I2C_3 + 0x08);
		volatile uint32* const OAR2				      		= (volatile uint32* const) (BASE::I2C_3 + 0x0C);
		volatile uint32* const TIMINGR				  		= (volatile uint32* const) (BASE::I2C_3 + 0x10);
		volatile uint32* const TIMEOUTR				  		= (volatile uint32* const) (BASE::I2C_3 + 0x14);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::I2C_3 + 0x18);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::I2C_3 + 0x1C);
		volatile uint32* const PECR				      		= (volatile uint32* const) (BASE::I2C_3 + 0x20);
		volatile uint32* const RXDR				      		= (volatile uint32* const) (BASE::I2C_3 + 0x24);
		volatile uint32* const TXDR				      		= (volatile uint32* const) (BASE::I2C_3 + 0x28);
	};
	
	namespace HDMI_CEC
	{
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::HDMI_CEC + 0x00);
		volatile uint32* const CFGR				      		= (volatile uint32* const) (BASE::HDMI_CEC + 0x04);
		volatile uint32* const TXDR				      		= (volatile uint32* const) (BASE::HDMI_CEC + 0x08);
		volatile uint32* const RXDR				      		= (volatile uint32* const) (BASE::HDMI_CEC + 0x0C);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::HDMI_CEC + 0x10);
		volatile uint32* const IER				      		= (volatile uint32* const) (BASE::HDMI_CEC + 0x14);
	};
	
	namespace DAC
	{
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::DAC + 0x00);
		volatile uint32* const SWTRGR				    		= (volatile uint32* const) (BASE::DAC + 0x04);
		volatile uint32* const DHR12R1				  		= (volatile uint32* const) (BASE::DAC + 0x08);
		volatile uint32* const DHR12L1				  		= (volatile uint32* const) (BASE::DAC + 0x0C);
		volatile uint32* const DHR8R1				    		= (volatile uint32* const) (BASE::DAC + 0x10);
		volatile uint32* const DHR12R2				  		= (volatile uint32* const) (BASE::DAC + 0x14);
		volatile uint32* const DHR12L2				  		= (volatile uint32* const) (BASE::DAC + 0x18);
		volatile uint32* const DHR8R2				    		= (volatile uint32* const) (BASE::DAC + 0x1C);
		volatile uint32* const DHR12RD				  		= (volatile uint32* const) (BASE::DAC + 0x20);
		volatile uint32* const DHR12LD				  		= (volatile uint32* const) (BASE::DAC + 0x24);
		volatile uint32* const DHR8RD				    		= (volatile uint32* const) (BASE::DAC + 0x28);
		volatile uint32* const DOR1				      		= (volatile uint32* const) (BASE::DAC + 0x2C);
		volatile uint32* const DOR2				      		= (volatile uint32* const) (BASE::DAC + 0x30);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::DAC + 0x34);
		volatile uint32* const CCR				      		= (volatile uint32* const) (BASE::DAC + 0x38);
		volatile uint32* const MCR				      		= (volatile uint32* const) (BASE::DAC + 0x3C);
		volatile uint32* const SHSR1				    		= (volatile uint32* const) (BASE::DAC + 0x40);
		volatile uint32* const SHSR2				    		= (volatile uint32* const) (BASE::DAC + 0x44);
		volatile uint32* const SHHR				      		= (volatile uint32* const) (BASE::DAC + 0x48);
		volatile uint32* const SHRR		        			= (volatile uint32* const) (BASE::DAC + 0x4C);
	};
	
	namespace UART_7
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::UART_7 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::UART_7 + 0x04);
		volatile uint32* const CR3				      		= (volatile uint32* const) (BASE::UART_7 + 0x08);
		volatile uint32* const BRR				      		= (volatile uint32* const) (BASE::UART_7 + 0x0C);
		volatile uint32* const GTPR				      		= (volatile uint32* const) (BASE::UART_7 + 0x10);
		volatile uint32* const RTOR				      		= (volatile uint32* const) (BASE::UART_7 + 0x14);
		volatile uint32* const RQR				      		= (volatile uint32* const) (BASE::UART_7 + 0x18);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::UART_7 + 0x1C);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::UART_7 + 0x20);
		volatile uint32* const RDR				      		= (volatile uint32* const) (BASE::UART_7 + 0x24);
		volatile uint32* const TDR				      		= (volatile uint32* const) (BASE::UART_7 + 0x28);
		volatile uint32* const PRESC				    		= (volatile uint32* const) (BASE::UART_7 + 0x2C);
	};
	
	namespace UART_8
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::UART_8 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::UART_8 + 0x04);
		volatile uint32* const CR3				      		= (volatile uint32* const) (BASE::UART_8 + 0x08);
		volatile uint32* const BRR				      		= (volatile uint32* const) (BASE::UART_8 + 0x0C);
		volatile uint32* const GTPR				      		= (volatile uint32* const) (BASE::UART_8 + 0x10);
		volatile uint32* const RTOR				      		= (volatile uint32* const) (BASE::UART_8 + 0x14);
		volatile uint32* const RQR				      		= (volatile uint32* const) (BASE::UART_8 + 0x18);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::UART_8 + 0x1C);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::UART_8 + 0x20);
		volatile uint32* const RDR				      		= (volatile uint32* const) (BASE::UART_8 + 0x24);
		volatile uint32* const TDR				      		= (volatile uint32* const) (BASE::UART_8 + 0x28);
		volatile uint32* const PRESC				    		= (volatile uint32* const) (BASE::UART_8 + 0x2C);
	};
	
	namespace CRS
	{
		volatile uint32* const CR				  		  		= (volatile uint32* const) (BASE::CRS + 0x00);
		volatile uint32* const CFGR						  		= (volatile uint32* const) (BASE::CRS + 0x04);
		volatile uint32* const ISR						  		= (volatile uint32* const) (BASE::CRS + 0x08);
		volatile uint32* const ICR						  		= (volatile uint32* const) (BASE::CRS + 0x0C);
	};
	
	namespace SWPMI
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::SWPMI + 0x00);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::SWPMI + 0x04);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::SWPMI + 0x0C);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::SWPMI + 0x10);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::SWPMI + 0x14);
		volatile uint32* const RFL									= (volatile uint32* const) (BASE::SWPMI + 0x18);
		volatile uint32* const TDR									= (volatile uint32* const) (BASE::SWPMI + 0x1C);
		volatile uint32* const RDR									= (volatile uint32* const) (BASE::SWPMI + 0x20);
		volatile uint32* const OR										= (volatile uint32* const) (BASE::SWPMI + 0x24);
	};
	
	namespace OP
	{
		volatile uint32* const OR										= (volatile uint32* const) (BASE::OP + 0x0C);
	};
	
	namespace OP_1
	{
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::OP + 0x00);
		volatile uint32* const OTR									= (volatile uint32* const) (BASE::OP + 0x04);
		volatile uint32* const HSOTR								= (volatile uint32* const) (BASE::OP + 0x08);
	};
	
	namespace OP_2
	{
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::OP + 0x10);
		volatile uint32* const OTR									= (volatile uint32* const) (BASE::OP + 0x14);
		volatile uint32* const HSOTR								= (volatile uint32* const) (BASE::OP + 0x18);
	};
	
	namespace MDIOS
	{
		volatile uint32* const CR			  						= (volatile uint32* const) (BASE::MDIOS + 0x000);
		volatile uint32* const WRFR									= (volatile uint32* const) (BASE::MDIOS + 0x004);
		volatile uint32* const CWRFR								= (volatile uint32* const) (BASE::MDIOS + 0x008);
		volatile uint32* const RDFR									= (volatile uint32* const) (BASE::MDIOS + 0x00C);
		volatile uint32* const CRDFR								= (volatile uint32* const) (BASE::MDIOS + 0x010);
		volatile uint32* const SR			  						= (volatile uint32* const) (BASE::MDIOS + 0x014);
		volatile uint32* const CLRFR								= (volatile uint32* const) (BASE::MDIOS + 0x018);
		volatile uint32* const DINR0								= (volatile uint32* const) (BASE::MDIOS + 0x100);
		volatile uint32* const DINR1								= (volatile uint32* const) (BASE::MDIOS + 0x104);
		volatile uint32* const DINR2								= (volatile uint32* const) (BASE::MDIOS + 0x108);
		volatile uint32* const DINR3								= (volatile uint32* const) (BASE::MDIOS + 0x10C);
		volatile uint32* const DINR4								= (volatile uint32* const) (BASE::MDIOS + 0x110);
		volatile uint32* const DINR5								= (volatile uint32* const) (BASE::MDIOS + 0x114);
		volatile uint32* const DINR6								= (volatile uint32* const) (BASE::MDIOS + 0x118);
		volatile uint32* const DINR7								= (volatile uint32* const) (BASE::MDIOS + 0x11C);
		volatile uint32* const DINR8								= (volatile uint32* const) (BASE::MDIOS + 0x120);
		volatile uint32* const DINR9								= (volatile uint32* const) (BASE::MDIOS + 0x124);
		volatile uint32* const DINR10								= (volatile uint32* const) (BASE::MDIOS + 0x128);
		volatile uint32* const DINR11								= (volatile uint32* const) (BASE::MDIOS + 0x12C);
		volatile uint32* const DINR12								= (volatile uint32* const) (BASE::MDIOS + 0x130);
		volatile uint32* const DINR13								= (volatile uint32* const) (BASE::MDIOS + 0x134);
		volatile uint32* const DINR14								= (volatile uint32* const) (BASE::MDIOS + 0x138);
		volatile uint32* const DINR15								= (volatile uint32* const) (BASE::MDIOS + 0x13C);
		volatile uint32* const DINR16								= (volatile uint32* const) (BASE::MDIOS + 0x140);
		volatile uint32* const DINR17								= (volatile uint32* const) (BASE::MDIOS + 0x144);
		volatile uint32* const DINR18								= (volatile uint32* const) (BASE::MDIOS + 0x148);
		volatile uint32* const DINR19								= (volatile uint32* const) (BASE::MDIOS + 0x14C);
		volatile uint32* const DINR20								= (volatile uint32* const) (BASE::MDIOS + 0x150);
		volatile uint32* const DINR21								= (volatile uint32* const) (BASE::MDIOS + 0x154);
		volatile uint32* const DINR22								= (volatile uint32* const) (BASE::MDIOS + 0x158);
		volatile uint32* const DINR23								= (volatile uint32* const) (BASE::MDIOS + 0x15C);
		volatile uint32* const DINR24								= (volatile uint32* const) (BASE::MDIOS + 0x160);
		volatile uint32* const DINR25								= (volatile uint32* const) (BASE::MDIOS + 0x164);
		volatile uint32* const DINR26								= (volatile uint32* const) (BASE::MDIOS + 0x168);
		volatile uint32* const DINR27								= (volatile uint32* const) (BASE::MDIOS + 0x16C);
		volatile uint32* const DINR28								= (volatile uint32* const) (BASE::MDIOS + 0x170);
		volatile uint32* const DINR29								= (volatile uint32* const) (BASE::MDIOS + 0x174);
		volatile uint32* const DINR30								= (volatile uint32* const) (BASE::MDIOS + 0x178);
		volatile uint32* const DINR31								= (volatile uint32* const) (BASE::MDIOS + 0x17C);
		volatile uint32* const DOUTR0								= (volatile uint32* const) (BASE::MDIOS + 0x180);
		volatile uint32* const DOUTR1								= (volatile uint32* const) (BASE::MDIOS + 0x184);
		volatile uint32* const DOUTR2								= (volatile uint32* const) (BASE::MDIOS + 0x188);
		volatile uint32* const DOUTR3								= (volatile uint32* const) (BASE::MDIOS + 0x18C);
		volatile uint32* const DOUTR4								= (volatile uint32* const) (BASE::MDIOS + 0x190);
		volatile uint32* const DOUTR5								= (volatile uint32* const) (BASE::MDIOS + 0x194);
		volatile uint32* const DOUTR6								= (volatile uint32* const) (BASE::MDIOS + 0x198);
		volatile uint32* const DOUTR7								= (volatile uint32* const) (BASE::MDIOS + 0x19C);
		volatile uint32* const DOUTR8								= (volatile uint32* const) (BASE::MDIOS + 0x1A0);
		volatile uint32* const DOUTR9								= (volatile uint32* const) (BASE::MDIOS + 0x1A4);
		volatile uint32* const DOUTR10							= (volatile uint32* const) (BASE::MDIOS + 0x1A8);
		volatile uint32* const DOUTR11							= (volatile uint32* const) (BASE::MDIOS + 0x1AC);
		volatile uint32* const DOUTR12							= (volatile uint32* const) (BASE::MDIOS + 0x1B0);
		volatile uint32* const DOUTR13							= (volatile uint32* const) (BASE::MDIOS + 0x1B4);
		volatile uint32* const DOUTR14							= (volatile uint32* const) (BASE::MDIOS + 0x1B8);
		volatile uint32* const DOUTR15							= (volatile uint32* const) (BASE::MDIOS + 0x1BC);
		volatile uint32* const DOUTR16							= (volatile uint32* const) (BASE::MDIOS + 0x1C0);
		volatile uint32* const DOUTR17							= (volatile uint32* const) (BASE::MDIOS + 0x1C4);
		volatile uint32* const DOUTR18							= (volatile uint32* const) (BASE::MDIOS + 0x1C8);
		volatile uint32* const DOUTR19							= (volatile uint32* const) (BASE::MDIOS + 0x1CC);
		volatile uint32* const DOUTR20							= (volatile uint32* const) (BASE::MDIOS + 0x1D0);
		volatile uint32* const DOUTR21							= (volatile uint32* const) (BASE::MDIOS + 0x1D4);
		volatile uint32* const DOUTR22							= (volatile uint32* const) (BASE::MDIOS + 0x1D8);
		volatile uint32* const DOUTR23							= (volatile uint32* const) (BASE::MDIOS + 0x1DC);
		volatile uint32* const DOUTR24							= (volatile uint32* const) (BASE::MDIOS + 0x1E0);
		volatile uint32* const DOUTR25							= (volatile uint32* const) (BASE::MDIOS + 0x1E4);
		volatile uint32* const DOUTR26							= (volatile uint32* const) (BASE::MDIOS + 0x1E8);
		volatile uint32* const DOUTR27							= (volatile uint32* const) (BASE::MDIOS + 0x1EC);
		volatile uint32* const DOUTR28							= (volatile uint32* const) (BASE::MDIOS + 0x1F0);
		volatile uint32* const DOUTR29							= (volatile uint32* const) (BASE::MDIOS + 0x1F4);
		volatile uint32* const DOUTR30							= (volatile uint32* const) (BASE::MDIOS + 0x1F8);
		volatile uint32* const DOUTR31							= (volatile uint32* const) (BASE::MDIOS + 0x1FC);
	};
	
	namespace FDCAN_1
	{
		namespace FDCAN
		{
			volatile uint32* const CREL								= (volatile uint32* const) (BASE::FDCAN_1 + 0x000);
			volatile uint32* const ENDN								= (volatile uint32* const) (BASE::FDCAN_1 + 0x004);
			volatile uint32* const DBTP								= (volatile uint32* const) (BASE::FDCAN_1 + 0x00C);
			volatile uint32* const TEST								= (volatile uint32* const) (BASE::FDCAN_1 + 0x010);
			volatile uint32* const RWD								= (volatile uint32* const) (BASE::FDCAN_1 + 0x014);
			volatile uint32* const CCCR								= (volatile uint32* const) (BASE::FDCAN_1 + 0x018);
			volatile uint32* const NBTP								= (volatile uint32* const) (BASE::FDCAN_1 + 0x01C);
			volatile uint32* const TSCC								= (volatile uint32* const) (BASE::FDCAN_1 + 0x020);
			volatile uint32* const TSCV								= (volatile uint32* const) (BASE::FDCAN_1 + 0x024);
			volatile uint32* const TOCC								= (volatile uint32* const) (BASE::FDCAN_1 + 0x028);
			volatile uint32* const TOCV								= (volatile uint32* const) (BASE::FDCAN_1 + 0x02C);
			volatile uint32* const ECR								= (volatile uint32* const) (BASE::FDCAN_1 + 0x040);
			volatile uint32* const PSR								= (volatile uint32* const) (BASE::FDCAN_1 + 0x044);
			volatile uint32* const TDCR								= (volatile uint32* const) (BASE::FDCAN_1 + 0x048);
			volatile uint32* const IR				  				= (volatile uint32* const) (BASE::FDCAN_1 + 0x050);
			volatile uint32* const IE				  				= (volatile uint32* const) (BASE::FDCAN_1 + 0x054);
			volatile uint32* const ILS								= (volatile uint32* const) (BASE::FDCAN_1 + 0x058);
			volatile uint32* const ILE								= (volatile uint32* const) (BASE::FDCAN_1 + 0x05C);
			volatile uint32* const GFC								= (volatile uint32* const) (BASE::FDCAN_1 + 0x080);
			volatile uint32* const SIDFC							= (volatile uint32* const) (BASE::FDCAN_1 + 0x084);
			volatile uint32* const XIDFC							= (volatile uint32* const) (BASE::FDCAN_1 + 0x088);
			volatile uint32* const XIDAM							= (volatile uint32* const) (BASE::FDCAN_1 + 0x090);
			volatile uint32* const HPMS								= (volatile uint32* const) (BASE::FDCAN_1 + 0x094);
			volatile uint32* const NDAT1							= (volatile uint32* const) (BASE::FDCAN_1 + 0x098);
			volatile uint32* const NDAT2							= (volatile uint32* const) (BASE::FDCAN_1 + 0x09C);
			volatile uint32* const RXF0C							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0A0);
			volatile uint32* const RXF0S							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0A4);
			volatile uint32* const RXF0A							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0A8);
			volatile uint32* const RXBC								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0AC);
			volatile uint32* const RXF1C							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0B0);
			volatile uint32* const RXF1S							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0B4);
			volatile uint32* const RXF1A							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0B8);
			volatile uint32* const RXESC							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0BC);
			volatile uint32* const TXBC								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0C0);
			volatile uint32* const TXFQS							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0C4);
			volatile uint32* const TXESC							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0C8);
			volatile uint32* const TXBRP							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0CC);
			volatile uint32* const TXBAR							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0D0);
			volatile uint32* const TXBCR							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0D4);
			volatile uint32* const TXBTO							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0D8);
			volatile uint32* const TXBCF							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0DC);
			volatile uint32* const TXBTIE							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0E0);
			volatile uint32* const TXBCIE							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0E4);
			volatile uint32* const TXEFC							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0F0);
			volatile uint32* const TXEFS							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0F4);
			volatile uint32* const TXEFA							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0F8);
		};
		
		namespace TTCAN
		{
			volatile uint32* const TMC								= (volatile uint32* const) (BASE::FDCAN_1 + 0x100);
			volatile uint32* const RMC								= (volatile uint32* const) (BASE::FDCAN_1 + 0x104);
			volatile uint32* const OCF								= (volatile uint32* const) (BASE::FDCAN_1 + 0x108);
			volatile uint32* const MLM								= (volatile uint32* const) (BASE::FDCAN_1 + 0x10C);
			volatile uint32* const RCF								= (volatile uint32* const) (BASE::FDCAN_1 + 0x110);
			volatile uint32* const OCN								= (volatile uint32* const) (BASE::FDCAN_1 + 0x114);
			volatile uint32* const GTP								= (volatile uint32* const) (BASE::FDCAN_1 + 0x118);
			volatile uint32* const TMK								= (volatile uint32* const) (BASE::FDCAN_1 + 0x11C);
			volatile uint32* const IR									= (volatile uint32* const) (BASE::FDCAN_1 + 0x120);
			volatile uint32* const IE									= (volatile uint32* const) (BASE::FDCAN_1 + 0x124);
			volatile uint32* const ILS								= (volatile uint32* const) (BASE::FDCAN_1 + 0x128);
			volatile uint32* const OST								= (volatile uint32* const) (BASE::FDCAN_1 + 0x12C);
			volatile uint32* const TURNA							= (volatile uint32* const) (BASE::FDCAN_1 + 0x130);
			volatile uint32* const LGT								= (volatile uint32* const) (BASE::FDCAN_1 + 0x134);
			volatile uint32* const CTC								= (volatile uint32* const) (BASE::FDCAN_1 + 0x138);
			volatile uint32* const CPT								= (volatile uint32* const) (BASE::FDCAN_1 + 0x13C);
			volatile uint32* const CSM								= (volatile uint32* const) (BASE::FDCAN_1 + 0x140);
			volatile uint32* const TS									= (volatile uint32* const) (BASE::FDCAN_1 + 0x300);
		};
		
		namespace CCU
		{
			volatile uint32* const CREL								= (volatile uint32* const) (BASE::FDCAN_CCU + 0x00);
			volatile uint32* const CCFG								= (volatile uint32* const) (BASE::FDCAN_CCU + 0x04);
			volatile uint32* const CSTAT							= (volatile uint32* const) (BASE::FDCAN_CCU + 0x08);
			volatile uint32* const CWD								= (volatile uint32* const) (BASE::FDCAN_CCU + 0x0C);
			volatile uint32* const IR									= (volatile uint32* const) (BASE::FDCAN_CCU + 0x10);
			volatile uint32* const IE									= (volatile uint32* const) (BASE::FDCAN_CCU + 0x14);
		};
	};
	
	namespace FDCAN_2
	{
		namespace FDCAN
		{
			volatile uint32* const CREL								= (volatile uint32* const) (BASE::FDCAN_2 + 0x000);
			volatile uint32* const ENDN								= (volatile uint32* const) (BASE::FDCAN_2 + 0x004);
			volatile uint32* const DBTP								= (volatile uint32* const) (BASE::FDCAN_2 + 0x00C);
			volatile uint32* const TEST								= (volatile uint32* const) (BASE::FDCAN_2 + 0x010);
			volatile uint32* const RWD								= (volatile uint32* const) (BASE::FDCAN_2 + 0x014);
			volatile uint32* const CCCR								= (volatile uint32* const) (BASE::FDCAN_2 + 0x018);
			volatile uint32* const NBTP								= (volatile uint32* const) (BASE::FDCAN_2 + 0x01C);
			volatile uint32* const TSCC								= (volatile uint32* const) (BASE::FDCAN_2 + 0x020);
			volatile uint32* const TSCV								= (volatile uint32* const) (BASE::FDCAN_2 + 0x024);
			volatile uint32* const TOCC								= (volatile uint32* const) (BASE::FDCAN_2 + 0x028);
			volatile uint32* const TOCV								= (volatile uint32* const) (BASE::FDCAN_2 + 0x02C);
			volatile uint32* const ECR								= (volatile uint32* const) (BASE::FDCAN_2 + 0x040);
			volatile uint32* const PSR								= (volatile uint32* const) (BASE::FDCAN_2 + 0x044);
			volatile uint32* const TDCR								= (volatile uint32* const) (BASE::FDCAN_2 + 0x048);
			volatile uint32* const IR									= (volatile uint32* const) (BASE::FDCAN_2 + 0x050);
			volatile uint32* const IE									= (volatile uint32* const) (BASE::FDCAN_2 + 0x054);
			volatile uint32* const ILS								= (volatile uint32* const) (BASE::FDCAN_2 + 0x058);
			volatile uint32* const ILE								= (volatile uint32* const) (BASE::FDCAN_2 + 0x05C);
			volatile uint32* const GFC								= (volatile uint32* const) (BASE::FDCAN_2 + 0x080);
			volatile uint32* const SIDFC							= (volatile uint32* const) (BASE::FDCAN_2 + 0x084);
			volatile uint32* const XIDFC							= (volatile uint32* const) (BASE::FDCAN_2 + 0x088);
			volatile uint32* const XIDAM							= (volatile uint32* const) (BASE::FDCAN_2 + 0x090);
			volatile uint32* const HPMS								= (volatile uint32* const) (BASE::FDCAN_2 + 0x094);
			volatile uint32* const NDAT1							= (volatile uint32* const) (BASE::FDCAN_2 + 0x098);
			volatile uint32* const NDAT2							= (volatile uint32* const) (BASE::FDCAN_2 + 0x09C);
			volatile uint32* const RXF0C							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0A0);
			volatile uint32* const RXF0S							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0A4);
			volatile uint32* const RXF0A							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0A8);
			volatile uint32* const RXBC								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0AC);
			volatile uint32* const RXF1C							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0B0);
			volatile uint32* const RXF1S							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0B4);
			volatile uint32* const RXF1A							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0B8);
			volatile uint32* const RXESC							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0BC);
			volatile uint32* const TXBC								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0C0);
			volatile uint32* const TXFQS							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0C4);
			volatile uint32* const TXESC							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0C8);
			volatile uint32* const TXBRP							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0CC);
			volatile uint32* const TXBAR							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0D0);
			volatile uint32* const TXBCR							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0D4);
			volatile uint32* const TXBTO							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0D8);
			volatile uint32* const TXBCF							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0DC);
			volatile uint32* const TXBTIE							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0E0);
			volatile uint32* const TXBCIE							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0E4);
			volatile uint32* const TXEFC							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0F0);
			volatile uint32* const TXEFS							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0F4);
			volatile uint32* const TXEFA							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0F8);
		};
	};
	
	volatile uint32* const FDCAN_MSG_RAM					= (volatile uint32* const) (BASE::FDCAN_MSG_RAM + 0x000);
	
	namespace TIMER_1
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::TIMER_1 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::TIMER_1 + 0x04);
		volatile uint32* const SMCR									= (volatile uint32* const) (BASE::TIMER_1 + 0x08);
		volatile uint32* const DIER									= (volatile uint32* const) (BASE::TIMER_1 + 0x0C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::TIMER_1 + 0x10);
		volatile uint32* const EGR									= (volatile uint32* const) (BASE::TIMER_1 + 0x14);
		volatile uint32* const CCMR1								= (volatile uint32* const) (BASE::TIMER_1 + 0x18);
		volatile uint32* const CCMR2								= (volatile uint32* const) (BASE::TIMER_1 + 0x1C);
		volatile uint32* const CCER									= (volatile uint32* const) (BASE::TIMER_1 + 0x20);
		volatile uint32* const CNT									= (volatile uint32* const) (BASE::TIMER_1 + 0x24);
		volatile uint32* const PSC									= (volatile uint32* const) (BASE::TIMER_1 + 0x28);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::TIMER_1 + 0x2C);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::TIMER_1 + 0x30);
		volatile uint32* const CCR1									= (volatile uint32* const) (BASE::TIMER_1 + 0x34);
		volatile uint32* const CCR2									= (volatile uint32* const) (BASE::TIMER_1 + 0x38);
		volatile uint32* const CCR3									= (volatile uint32* const) (BASE::TIMER_1 + 0x3C);
		volatile uint32* const CCR4									= (volatile uint32* const) (BASE::TIMER_1 + 0x40);
		volatile uint32* const BDTR									= (volatile uint32* const) (BASE::TIMER_1 + 0x44);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::TIMER_1 + 0x48);
		volatile uint32* const DMAR									= (volatile uint32* const) (BASE::TIMER_1 + 0x4C);
		volatile uint32* const CCMR3								= (volatile uint32* const) (BASE::TIMER_1 + 0x54);
		volatile uint32* const CCR5									= (volatile uint32* const) (BASE::TIMER_1 + 0x58);
		volatile uint32* const CCR6									= (volatile uint32* const) (BASE::TIMER_1 + 0x5C);
		volatile uint32* const AF1									= (volatile uint32* const) (BASE::TIMER_1 + 0x60);
		volatile uint32* const AF2									= (volatile uint32* const) (BASE::TIMER_1 + 0x64);
		volatile uint32* const TISEL								= (volatile uint32* const) (BASE::TIMER_1 + 0x68);
	};
	
	namespace TIMER_8
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::TIMER_8 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::TIMER_8 + 0x04);
		volatile uint32* const SMCR									= (volatile uint32* const) (BASE::TIMER_8 + 0x08);
		volatile uint32* const DIER									= (volatile uint32* const) (BASE::TIMER_8 + 0x0C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::TIMER_8 + 0x10);
		volatile uint32* const EGR									= (volatile uint32* const) (BASE::TIMER_8 + 0x14);
		volatile uint32* const CCMR1								= (volatile uint32* const) (BASE::TIMER_8 + 0x18);
		volatile uint32* const CCMR2								= (volatile uint32* const) (BASE::TIMER_8 + 0x1C);
		volatile uint32* const CCER									= (volatile uint32* const) (BASE::TIMER_8 + 0x20);
		volatile uint32* const CNT									= (volatile uint32* const) (BASE::TIMER_8 + 0x24);
		volatile uint32* const PSC									= (volatile uint32* const) (BASE::TIMER_8 + 0x28);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::TIMER_8 + 0x2C);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::TIMER_8 + 0x30);
		volatile uint32* const CCR1									= (volatile uint32* const) (BASE::TIMER_8 + 0x34);
		volatile uint32* const CCR2									= (volatile uint32* const) (BASE::TIMER_8 + 0x38);
		volatile uint32* const CCR3									= (volatile uint32* const) (BASE::TIMER_8 + 0x3C);
		volatile uint32* const CCR4									= (volatile uint32* const) (BASE::TIMER_8 + 0x40);
		volatile uint32* const BDTR									= (volatile uint32* const) (BASE::TIMER_8 + 0x44);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::TIMER_8 + 0x48);
		volatile uint32* const DMAR									= (volatile uint32* const) (BASE::TIMER_8 + 0x4C);
		volatile uint32* const CCMR3								= (volatile uint32* const) (BASE::TIMER_8 + 0x54);
		volatile uint32* const CCR5									= (volatile uint32* const) (BASE::TIMER_8 + 0x58);
		volatile uint32* const CCR6									= (volatile uint32* const) (BASE::TIMER_8 + 0x5C);
		volatile uint32* const AF1									= (volatile uint32* const) (BASE::TIMER_8 + 0x60);
		volatile uint32* const AF2									= (volatile uint32* const) (BASE::TIMER_8 + 0x64);
		volatile uint32* const TISEL								= (volatile uint32* const) (BASE::TIMER_8 + 0x68);
	};
	
	namespace USART_1
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::USART_1 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::USART_1 + 0x04);
		volatile uint32* const CR3									= (volatile uint32* const) (BASE::USART_1 + 0x08);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::USART_1 + 0x0C);
		volatile uint32* const GTPR									= (volatile uint32* const) (BASE::USART_1 + 0x10);
		volatile uint32* const RTOR									= (volatile uint32* const) (BASE::USART_1 + 0x14);
		volatile uint32* const RQR									= (volatile uint32* const) (BASE::USART_1 + 0x18);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::USART_1 + 0x1C);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::USART_1 + 0x20);
		volatile uint32* const RDR									= (volatile uint32* const) (BASE::USART_1 + 0x24);
		volatile uint32* const TDR									= (volatile uint32* const) (BASE::USART_1 + 0x28);
		volatile uint32* const PRESC								= (volatile uint32* const) (BASE::USART_1 + 0x2C);
	};
	
	namespace USART_6
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::USART_6 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::USART_6 + 0x04);
		volatile uint32* const CR3									= (volatile uint32* const) (BASE::USART_6 + 0x08);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::USART_6 + 0x0C);
		volatile uint32* const GTPR									= (volatile uint32* const) (BASE::USART_6 + 0x10);
		volatile uint32* const RTOR									= (volatile uint32* const) (BASE::USART_6 + 0x14);
		volatile uint32* const RQR									= (volatile uint32* const) (BASE::USART_6 + 0x18);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::USART_6 + 0x1C);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::USART_6 + 0x20);
		volatile uint32* const RDR									= (volatile uint32* const) (BASE::USART_6 + 0x24);
		volatile uint32* const TDR									= (volatile uint32* const) (BASE::USART_6 + 0x28);
		volatile uint32* const PRESC								= (volatile uint32* const) (BASE::USART_6 + 0x2C);
	};
	
	namespace SPI_1
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::SPI_1 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::SPI_1 + 0x04);
		volatile uint32* const CFG1									= (volatile uint32* const) (BASE::SPI_1 + 0x08);
		volatile uint32* const CFG2									= (volatile uint32* const) (BASE::SPI_1 + 0x0C);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::SPI_1 + 0x10);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::SPI_1 + 0x14);
		volatile uint32* const IFCR									= (volatile uint32* const) (BASE::SPI_1 + 0x18);
		volatile uint32* const TXDR									= (volatile uint32* const) (BASE::SPI_1 + 0x20);
		volatile uint32* const RXDR									= (volatile uint32* const) (BASE::SPI_1 + 0x30);
		volatile uint32* const CRCPOLY							= (volatile uint32* const) (BASE::SPI_1 + 0x40);
		volatile uint32* const TXCRC								= (volatile uint32* const) (BASE::SPI_1 + 0x44);
		volatile uint32* const RXCRC								= (volatile uint32* const) (BASE::SPI_1 + 0x48);
		volatile uint32* const UDRDR								= (volatile uint32* const) (BASE::SPI_1 + 0x4C);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::SPI_1 + 0x50);
	};
	
	namespace SPI_4
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::SPI_4 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::SPI_4 + 0x04);
		volatile uint32* const CFG1									= (volatile uint32* const) (BASE::SPI_4 + 0x08);
		volatile uint32* const CFG2									= (volatile uint32* const) (BASE::SPI_4 + 0x0C);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::SPI_4 + 0x10);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::SPI_4 + 0x14);
		volatile uint32* const IFCR									= (volatile uint32* const) (BASE::SPI_4 + 0x18);
		volatile uint32* const TXDR									= (volatile uint32* const) (BASE::SPI_4 + 0x20);
		volatile uint32* const RXDR									= (volatile uint32* const) (BASE::SPI_4 + 0x30);
		volatile uint32* const CRCPOLY							= (volatile uint32* const) (BASE::SPI_4 + 0x40);
		volatile uint32* const TXCRC								= (volatile uint32* const) (BASE::SPI_4 + 0x44);
		volatile uint32* const RXCRC								= (volatile uint32* const) (BASE::SPI_4 + 0x48);
		volatile uint32* const UDRDR								= (volatile uint32* const) (BASE::SPI_4 + 0x4C);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::SPI_4 + 0x50);
	};
	
	namespace TIMER_15
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::TIMER_15 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::TIMER_15 + 0x04);
		volatile uint32* const SMCR									= (volatile uint32* const) (BASE::TIMER_15 + 0x08);
		volatile uint32* const DIER									= (volatile uint32* const) (BASE::TIMER_15 + 0x0C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::TIMER_15 + 0x10);
		volatile uint32* const EGR									= (volatile uint32* const) (BASE::TIMER_15 + 0x14);
		volatile uint32* const CCMR1								= (volatile uint32* const) (BASE::TIMER_15 + 0x18);
		volatile uint32* const CCER									= (volatile uint32* const) (BASE::TIMER_15 + 0x20);
		volatile uint32* const CNT									= (volatile uint32* const) (BASE::TIMER_15 + 0x24);
		volatile uint32* const PSC									= (volatile uint32* const) (BASE::TIMER_15 + 0x28);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::TIMER_15 + 0x2C);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::TIMER_15 + 0x30);
		volatile uint32* const CCR1									= (volatile uint32* const) (BASE::TIMER_15 + 0x34);
		volatile uint32* const CCR2									= (volatile uint32* const) (BASE::TIMER_15 + 0x38);
		volatile uint32* const BDTR									= (volatile uint32* const) (BASE::TIMER_15 + 0x44);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::TIMER_15 + 0x48);
		volatile uint32* const DMAR									= (volatile uint32* const) (BASE::TIMER_15 + 0x4C);
		volatile uint32* const AF1									= (volatile uint32* const) (BASE::TIMER_15 + 0x60);
		volatile uint32* const TISEL								= (volatile uint32* const) (BASE::TIMER_15 + 0x68);
	};
	
	namespace TIMER_16
	{
		volatile uint32* const CR1    							= (volatile uint32* const) (BASE::TIMER_16 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::TIMER_16 + 0x04);
		volatile uint32* const DIER									= (volatile uint32* const) (BASE::TIMER_16 + 0x0C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::TIMER_16 + 0x10);
		volatile uint32* const EGR									= (volatile uint32* const) (BASE::TIMER_16 + 0x14);
		volatile uint32* const CCMR1								= (volatile uint32* const) (BASE::TIMER_16 + 0x18);
		volatile uint32* const CCER									= (volatile uint32* const) (BASE::TIMER_16 + 0x20);
		volatile uint32* const CNT									= (volatile uint32* const) (BASE::TIMER_16 + 0x24);
		volatile uint32* const PSC									= (volatile uint32* const) (BASE::TIMER_16 + 0x28);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::TIMER_16 + 0x2C);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::TIMER_16 + 0x30);
		volatile uint32* const CCR1									= (volatile uint32* const) (BASE::TIMER_16 + 0x34);
		volatile uint32* const BDTR									= (volatile uint32* const) (BASE::TIMER_16 + 0x44);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::TIMER_16 + 0x48);
		volatile uint32* const DMAR									= (volatile uint32* const) (BASE::TIMER_16 + 0x4C);
		volatile uint32* const AF1									= (volatile uint32* const) (BASE::TIMER_16 + 0x60);
		volatile uint32* const TISEL								= (volatile uint32* const) (BASE::TIMER_16 + 0x68);
	};
	
	namespace TIMER_17
	{
		volatile uint32* const CR1    							= (volatile uint32* const) (BASE::TIMER_17 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::TIMER_17 + 0x04);
		volatile uint32* const DIER									= (volatile uint32* const) (BASE::TIMER_17 + 0x0C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::TIMER_17 + 0x10);
		volatile uint32* const EGR									= (volatile uint32* const) (BASE::TIMER_17 + 0x14);
		volatile uint32* const CCMR1								= (volatile uint32* const) (BASE::TIMER_17 + 0x18);
		volatile uint32* const CCER									= (volatile uint32* const) (BASE::TIMER_17 + 0x20);
		volatile uint32* const CNT									= (volatile uint32* const) (BASE::TIMER_17 + 0x24);
		volatile uint32* const PSC									= (volatile uint32* const) (BASE::TIMER_17 + 0x28);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::TIMER_17 + 0x2C);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::TIMER_17 + 0x30);
		volatile uint32* const CCR1									= (volatile uint32* const) (BASE::TIMER_17 + 0x34);
		volatile uint32* const BDTR									= (volatile uint32* const) (BASE::TIMER_17 + 0x44);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::TIMER_17 + 0x48);
		volatile uint32* const DMAR									= (volatile uint32* const) (BASE::TIMER_17 + 0x4C);
		volatile uint32* const AF1									= (volatile uint32* const) (BASE::TIMER_17 + 0x60);
		volatile uint32* const TISEL								= (volatile uint32* const) (BASE::TIMER_17 + 0x68);
	};
	
	namespace SPI_5
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::SPI_5 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::SPI_5 + 0x04);
		volatile uint32* const CFG1									= (volatile uint32* const) (BASE::SPI_5 + 0x08);
		volatile uint32* const CFG2									= (volatile uint32* const) (BASE::SPI_5 + 0x0C);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::SPI_5 + 0x10);
		volatile uint32* const SR				  					= (volatile uint32* const) (BASE::SPI_5 + 0x14);
		volatile uint32* const IFCR									= (volatile uint32* const) (BASE::SPI_5 + 0x18);
		volatile uint32* const TXDR									= (volatile uint32* const) (BASE::SPI_5 + 0x20);
		volatile uint32* const RXDR									= (volatile uint32* const) (BASE::SPI_5 + 0x30);
		volatile uint32* const CRCPOLY							= (volatile uint32* const) (BASE::SPI_5 + 0x40);
		volatile uint32* const TXCRC								= (volatile uint32* const) (BASE::SPI_5 + 0x44);
		volatile uint32* const RXCRC								= (volatile uint32* const) (BASE::SPI_5 + 0x48);
		volatile uint32* const UDRDR								= (volatile uint32* const) (BASE::SPI_5 + 0x4C);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::SPI_5 + 0x50);
	};
	
	namespace SAI_1
	{
		volatile uint32* const GCR									= (volatile uint32* const) (BASE::SAI_1 + 0x00);
		volatile uint32* const A_CR1            		= (volatile uint32* const) (BASE::SAI_1 + 0x04);
		volatile uint32* const A_CR2            		= (volatile uint32* const) (BASE::SAI_1 + 0x08);
		volatile uint32* const A_FRCR           		= (volatile uint32* const) (BASE::SAI_1 + 0x0C);
		volatile uint32* const A_SLOTR          		= (volatile uint32* const) (BASE::SAI_1 + 0x10);
		volatile uint32* const A_IM             		= (volatile uint32* const) (BASE::SAI_1 + 0x14);
		volatile uint32* const A_SR             		= (volatile uint32* const) (BASE::SAI_1 + 0x18);
		volatile uint32* const A_CLRFR          		= (volatile uint32* const) (BASE::SAI_1 + 0x1C);
		volatile uint32* const A_DR             		= (volatile uint32* const) (BASE::SAI_1 + 0x20);
		volatile uint32* const B_CR1            		= (volatile uint32* const) (BASE::SAI_1 + 0x24);
		volatile uint32* const B_CR2            		= (volatile uint32* const) (BASE::SAI_1 + 0x28);
		volatile uint32* const B_FRCR           		= (volatile uint32* const) (BASE::SAI_1 + 0x2C);
		volatile uint32* const B_SLOTR          		= (volatile uint32* const) (BASE::SAI_1 + 0x30);
		volatile uint32* const B_IM             		= (volatile uint32* const) (BASE::SAI_1 + 0x34);
		volatile uint32* const B_SR             		= (volatile uint32* const) (BASE::SAI_1 + 0x38);
		volatile uint32* const B_CLRFR          		= (volatile uint32* const) (BASE::SAI_1 + 0x3C);
		volatile uint32* const B_DR             		= (volatile uint32* const) (BASE::SAI_1 + 0x40);
		volatile uint32* const PDMCR            		= (volatile uint32* const) (BASE::SAI_1 + 0x44);
		volatile uint32* const PDMDLY           		= (volatile uint32* const) (BASE::SAI_1 + 0x48);
	};
	
	namespace SAI_2
	{
		volatile uint32* const GCR									= (volatile uint32* const) (BASE::SAI_2 + 0x00);
		volatile uint32* const A_CR1            		= (volatile uint32* const) (BASE::SAI_2 + 0x04);
		volatile uint32* const A_CR2            		= (volatile uint32* const) (BASE::SAI_2 + 0x08);
		volatile uint32* const A_FRCR           		= (volatile uint32* const) (BASE::SAI_2 + 0x0C);
		volatile uint32* const A_SLOTR          		= (volatile uint32* const) (BASE::SAI_2 + 0x10);
		volatile uint32* const A_IM             		= (volatile uint32* const) (BASE::SAI_2 + 0x14);
		volatile uint32* const A_SR             		= (volatile uint32* const) (BASE::SAI_2 + 0x18);
		volatile uint32* const A_CLRFR          		= (volatile uint32* const) (BASE::SAI_2 + 0x1C);
		volatile uint32* const A_DR             		= (volatile uint32* const) (BASE::SAI_2 + 0x20);
		volatile uint32* const B_CR1            		= (volatile uint32* const) (BASE::SAI_2 + 0x24);
		volatile uint32* const B_CR2            		= (volatile uint32* const) (BASE::SAI_2 + 0x28);
		volatile uint32* const B_FRCR           		= (volatile uint32* const) (BASE::SAI_2 + 0x2C);
		volatile uint32* const B_SLOTR          		= (volatile uint32* const) (BASE::SAI_2 + 0x30);
		volatile uint32* const B_IM             		= (volatile uint32* const) (BASE::SAI_2 + 0x34);
		volatile uint32* const B_SR             		= (volatile uint32* const) (BASE::SAI_2 + 0x38);
		volatile uint32* const B_CLRFR          		= (volatile uint32* const) (BASE::SAI_2 + 0x3C);
		volatile uint32* const B_DR             		= (volatile uint32* const) (BASE::SAI_2 + 0x40);
		volatile uint32* const PDMCR            		= (volatile uint32* const) (BASE::SAI_2 + 0x44);
		volatile uint32* const PDMDLY           		= (volatile uint32* const) (BASE::SAI_2 + 0x48);
	};
	
	namespace SAI_3
	{
		volatile uint32* const GCR									= (volatile uint32* const) (BASE::SAI_3 + 0x00);
		volatile uint32* const A_CR1            		= (volatile uint32* const) (BASE::SAI_3 + 0x04);
		volatile uint32* const A_CR2            		= (volatile uint32* const) (BASE::SAI_3 + 0x08);
		volatile uint32* const A_FRCR           		= (volatile uint32* const) (BASE::SAI_3 + 0x0C);
		volatile uint32* const A_SLOTR          		= (volatile uint32* const) (BASE::SAI_3 + 0x10);
		volatile uint32* const A_IM             		= (volatile uint32* const) (BASE::SAI_3 + 0x14);
		volatile uint32* const A_SR             		= (volatile uint32* const) (BASE::SAI_3 + 0x18);
		volatile uint32* const A_CLRFR          		= (volatile uint32* const) (BASE::SAI_3 + 0x1C);
		volatile uint32* const A_DR             		= (volatile uint32* const) (BASE::SAI_3 + 0x20);
		volatile uint32* const B_CR1            		= (volatile uint32* const) (BASE::SAI_3 + 0x24);
		volatile uint32* const B_CR2            		= (volatile uint32* const) (BASE::SAI_3 + 0x28);
		volatile uint32* const B_FRCR           		= (volatile uint32* const) (BASE::SAI_3 + 0x2C);
		volatile uint32* const B_SLOTR          		= (volatile uint32* const) (BASE::SAI_3 + 0x30);
		volatile uint32* const B_IM             		= (volatile uint32* const) (BASE::SAI_3 + 0x34);
		volatile uint32* const B_SR             		= (volatile uint32* const) (BASE::SAI_3 + 0x38);
		volatile uint32* const B_CLRFR          		= (volatile uint32* const) (BASE::SAI_3 + 0x3C);
		volatile uint32* const B_DR             		= (volatile uint32* const) (BASE::SAI_3 + 0x40);
		volatile uint32* const PDMCR            		= (volatile uint32* const) (BASE::SAI_3 + 0x44);
		volatile uint32* const PDMDLY           		= (volatile uint32* const) (BASE::SAI_3 + 0x48);
	};
	
	namespace DFSDM
	{
		volatile uint32* const CH0_CFGR1						= (volatile uint32* const) (BASE::DFSDM + 0x00);
		volatile uint32* const CH0_CFGR2						= (volatile uint32* const) (BASE::DFSDM + 0x04);
		volatile uint32* const CH0_AWSCDR						= (volatile uint32* const) (BASE::DFSDM + 0x08);
		volatile uint32* const CH0_WDATR						= (volatile uint32* const) (BASE::DFSDM + 0x0C);
		volatile uint32* const CH0_DATINR						= (volatile uint32* const) (BASE::DFSDM + 0x10);
		volatile uint32* const CH1_CFGR1						= (volatile uint32* const) (BASE::DFSDM + 0x20);
		volatile uint32* const CH1_CFGR2						= (volatile uint32* const) (BASE::DFSDM + 0x24);
		volatile uint32* const CH1_AWSCDR						= (volatile uint32* const) (BASE::DFSDM + 0x28);
		volatile uint32* const CH1_WDATR						= (volatile uint32* const) (BASE::DFSDM + 0x2C);
		volatile uint32* const CH1_DATINR						= (volatile uint32* const) (BASE::DFSDM + 0x30);
		volatile uint32* const CH2_CFGR1						= (volatile uint32* const) (BASE::DFSDM + 0x40);
		volatile uint32* const CH2_CFGR2						= (volatile uint32* const) (BASE::DFSDM + 0x44);
		volatile uint32* const CH2_AWSCDR						= (volatile uint32* const) (BASE::DFSDM + 0x48);
		volatile uint32* const CH2_WDATR						= (volatile uint32* const) (BASE::DFSDM + 0x4C);
		volatile uint32* const CH2_DATINR						= (volatile uint32* const) (BASE::DFSDM + 0x50);
		volatile uint32* const CH3_CFGR1						= (volatile uint32* const) (BASE::DFSDM + 0x60);
		volatile uint32* const CH3_CFGR2						= (volatile uint32* const) (BASE::DFSDM + 0x64);
		volatile uint32* const CH3_AWSCDR						= (volatile uint32* const) (BASE::DFSDM + 0x68);
		volatile uint32* const CH3_WDATR						= (volatile uint32* const) (BASE::DFSDM + 0x6C);
		volatile uint32* const CH3_DATINR						= (volatile uint32* const) (BASE::DFSDM + 0x70);
		volatile uint32* const CH4_CFGR1						= (volatile uint32* const) (BASE::DFSDM + 0x80);
		volatile uint32* const CH4_CFGR2						= (volatile uint32* const) (BASE::DFSDM + 0x84);
		volatile uint32* const CH4_AWSCDR						= (volatile uint32* const) (BASE::DFSDM + 0x88);
		volatile uint32* const CH4_WDATR						= (volatile uint32* const) (BASE::DFSDM + 0x8C);
		volatile uint32* const CH4_DATINR						= (volatile uint32* const) (BASE::DFSDM + 0x90);
		volatile uint32* const CH5_CFGR1						= (volatile uint32* const) (BASE::DFSDM + 0xA0);
		volatile uint32* const CH5_CFGR2						= (volatile uint32* const) (BASE::DFSDM + 0xA4);
		volatile uint32* const CH5_AWSCDR						= (volatile uint32* const) (BASE::DFSDM + 0xA8);
		volatile uint32* const CH5_WDATR						= (volatile uint32* const) (BASE::DFSDM + 0xAC);
		volatile uint32* const CH5_DATINR						= (volatile uint32* const) (BASE::DFSDM + 0xB0);
		volatile uint32* const CH6_CFGR1						= (volatile uint32* const) (BASE::DFSDM + 0xC0);
		volatile uint32* const CH6_CFGR2						= (volatile uint32* const) (BASE::DFSDM + 0xC4);
		volatile uint32* const CH6_AWSCDR						= (volatile uint32* const) (BASE::DFSDM + 0xC8);
		volatile uint32* const CH6_WDATR						= (volatile uint32* const) (BASE::DFSDM + 0xCC);
		volatile uint32* const CH6_DATINR						= (volatile uint32* const) (BASE::DFSDM + 0xD0);
		volatile uint32* const CH7_CFGR1						= (volatile uint32* const) (BASE::DFSDM + 0xE0);
		volatile uint32* const CH7_CFGR2						= (volatile uint32* const) (BASE::DFSDM + 0xE4);
		volatile uint32* const CH7_AWSCDR						= (volatile uint32* const) (BASE::DFSDM + 0xE8);
		volatile uint32* const CH7_WDATR						= (volatile uint32* const) (BASE::DFSDM + 0xEC);
		volatile uint32* const CH7_DATINR						= (volatile uint32* const) (BASE::DFSDM + 0xF0);
		
		volatile uint32* const FLT0_CR1							= (volatile uint32* const) (BASE::DFSDM + 0x100);
		volatile uint32* const FLT0_CR2							= (volatile uint32* const) (BASE::DFSDM + 0x104);
		volatile uint32* const FLT0_ISR							= (volatile uint32* const) (BASE::DFSDM + 0x108);
		volatile uint32* const FLT0_ICR							= (volatile uint32* const) (BASE::DFSDM + 0x10C);
		volatile uint32* const FLT0_JCHGR						= (volatile uint32* const) (BASE::DFSDM + 0x110);
		volatile uint32* const FLT0_FCR							= (volatile uint32* const) (BASE::DFSDM + 0x114);
		volatile uint32* const FLT0_JDATAR					= (volatile uint32* const) (BASE::DFSDM + 0x118);
		volatile uint32* const FLT0_RDATAR					= (volatile uint32* const) (BASE::DFSDM + 0x11C);
		volatile uint32* const FLT0_AWHTR						= (volatile uint32* const) (BASE::DFSDM + 0x120);
		volatile uint32* const FLT0_AWLTR						= (volatile uint32* const) (BASE::DFSDM + 0x124);
		volatile uint32* const FLT0_AWSR						= (volatile uint32* const) (BASE::DFSDM + 0x128);
		volatile uint32* const FLT0_AWCFR						= (volatile uint32* const) (BASE::DFSDM + 0x12C);
		volatile uint32* const FLT0_EXMAX						= (volatile uint32* const) (BASE::DFSDM + 0x130);
		volatile uint32* const FLT0_EXMIN						= (volatile uint32* const) (BASE::DFSDM + 0x134);
		volatile uint32* const FLT0_CNVTIMR					= (volatile uint32* const) (BASE::DFSDM + 0x138);
		volatile uint32* const FLT1_CR1							= (volatile uint32* const) (BASE::DFSDM + 0x180);
		volatile uint32* const FLT1_CR2							= (volatile uint32* const) (BASE::DFSDM + 0x184);
		volatile uint32* const FLT1_ISR							= (volatile uint32* const) (BASE::DFSDM + 0x188);
		volatile uint32* const FLT1_ICR							= (volatile uint32* const) (BASE::DFSDM + 0x18C);
		volatile uint32* const FLT1_JCHGR						= (volatile uint32* const) (BASE::DFSDM + 0x190);
		volatile uint32* const FLT1_FCR							= (volatile uint32* const) (BASE::DFSDM + 0x194);
		volatile uint32* const FLT1_JDATAR					= (volatile uint32* const) (BASE::DFSDM + 0x198);
		volatile uint32* const FLT1_RDATAR					= (volatile uint32* const) (BASE::DFSDM + 0x19C);
		volatile uint32* const FLT1_AWHTR						= (volatile uint32* const) (BASE::DFSDM + 0x1A0);
		volatile uint32* const FLT1_AWLTR						= (volatile uint32* const) (BASE::DFSDM + 0x1A4);
		volatile uint32* const FLT1_AWSR						= (volatile uint32* const) (BASE::DFSDM + 0x1A8);
		volatile uint32* const FLT1_AWCFR						= (volatile uint32* const) (BASE::DFSDM + 0x1AC);
		volatile uint32* const FLT1_EXMAX						= (volatile uint32* const) (BASE::DFSDM + 0x1B0);
		volatile uint32* const FLT1_EXMIN						= (volatile uint32* const) (BASE::DFSDM + 0x1B4);
		volatile uint32* const FLT1_CNVTIMR					= (volatile uint32* const) (BASE::DFSDM + 0x1B8);
		volatile uint32* const FLT2_CR1							= (volatile uint32* const) (BASE::DFSDM + 0x200);
		volatile uint32* const FLT2_CR2							= (volatile uint32* const) (BASE::DFSDM + 0x204);
		volatile uint32* const FLT2_ISR							= (volatile uint32* const) (BASE::DFSDM + 0x208);
		volatile uint32* const FLT2_ICR							= (volatile uint32* const) (BASE::DFSDM + 0x20C);
		volatile uint32* const FLT2_JCHGR						= (volatile uint32* const) (BASE::DFSDM + 0x210);
		volatile uint32* const FLT2_FCR							= (volatile uint32* const) (BASE::DFSDM + 0x214);
		volatile uint32* const FLT2_JDATAR					= (volatile uint32* const) (BASE::DFSDM + 0x218);
		volatile uint32* const FLT2_RDATAR					= (volatile uint32* const) (BASE::DFSDM + 0x21C);
		volatile uint32* const FLT2_AWHTR						= (volatile uint32* const) (BASE::DFSDM + 0x220);
		volatile uint32* const FLT2_AWLTR						= (volatile uint32* const) (BASE::DFSDM + 0x224);
		volatile uint32* const FLT2_AWSR						= (volatile uint32* const) (BASE::DFSDM + 0x228);
		volatile uint32* const FLT2_AWCFR						= (volatile uint32* const) (BASE::DFSDM + 0x22C);
		volatile uint32* const FLT2_EXMAX						= (volatile uint32* const) (BASE::DFSDM + 0x230);
		volatile uint32* const FLT2_EXMIN						= (volatile uint32* const) (BASE::DFSDM + 0x234);
		volatile uint32* const FLT2_CNVTIMR					= (volatile uint32* const) (BASE::DFSDM + 0x238);
		volatile uint32* const FLT3_CR1							= (volatile uint32* const) (BASE::DFSDM + 0x280);
		volatile uint32* const FLT3_CR2							= (volatile uint32* const) (BASE::DFSDM + 0x284);
		volatile uint32* const FLT3_ISR							= (volatile uint32* const) (BASE::DFSDM + 0x288);
		volatile uint32* const FLT3_ICR							= (volatile uint32* const) (BASE::DFSDM + 0x28C);
		volatile uint32* const FLT3_JCHGR						= (volatile uint32* const) (BASE::DFSDM + 0x290);
		volatile uint32* const FLT3_FCR							= (volatile uint32* const) (BASE::DFSDM + 0x294);
		volatile uint32* const FLT3_JDATAR					= (volatile uint32* const) (BASE::DFSDM + 0x298);
		volatile uint32* const FLT3_RDATAR					= (volatile uint32* const) (BASE::DFSDM + 0x29C);
		volatile uint32* const FLT3_AWHTR						= (volatile uint32* const) (BASE::DFSDM + 0x2A0);
		volatile uint32* const FLT3_AWLTR						= (volatile uint32* const) (BASE::DFSDM + 0x2A4);
		volatile uint32* const FLT3_AWSR						= (volatile uint32* const) (BASE::DFSDM + 0x2A8);
		volatile uint32* const FLT3_AWCFR						= (volatile uint32* const) (BASE::DFSDM + 0x2AC);
		volatile uint32* const FLT3_EXMAX						= (volatile uint32* const) (BASE::DFSDM + 0x2B0);
		volatile uint32* const FLT3_EXMIN						= (volatile uint32* const) (BASE::DFSDM + 0x2B4);
		volatile uint32* const FLT3_CNVTIMR					= (volatile uint32* const) (BASE::DFSDM + 0x2B8);
	};
	
	namespace HR_TIMER
	{
		volatile uint32* const CR1								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x00);
		volatile uint32* const CR2								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x04);
		volatile uint32* const ISR								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x08);
		volatile uint32* const ICR								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x0C);
		volatile uint32* const IER								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x10);
		volatile uint32* const OENR								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x14);
		volatile uint32* const DISR								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x18);
		volatile uint32* const ODSR								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x1C);
		volatile uint32* const BMCR								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x20);
		volatile uint32* const BMTRG							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x24);
		volatile uint32* const BMCMPR							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x28);
		volatile uint32* const BMPER							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x2C);
		volatile uint32* const EECR1							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x30);
		volatile uint32* const EECR2							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x34);
		volatile uint32* const EECR3							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x38);
		volatile uint32* const ADC1R							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x3C);
		volatile uint32* const ADC2R							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x40);
		volatile uint32* const ADC3R							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x44);
		volatile uint32* const ADC4R							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x48);
		volatile uint32* const FLTIN1R						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x50);
		volatile uint32* const FLTIN2R						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x54);
		volatile uint32* const MASTER_BDUPDR			= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x58);
		volatile uint32* const A_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x5C);
		volatile uint32* const B_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x60);
		volatile uint32* const C_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x64);
		volatile uint32* const D_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x68);
		volatile uint32* const E_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x6C);
		volatile uint32* const BDMADR							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x70);
		
		namespace MASTER
		{
			volatile uint32* const CR									= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x00);
			volatile uint32* const ISR								= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x04);
			volatile uint32* const ICR								= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x08);
			volatile uint32* const DIER								= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x0C);
			volatile uint32* const CNTR								= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x10);
			volatile uint32* const PER								= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x14);
			volatile uint32* const REP								= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x18);
			volatile uint32* const CMP1R							= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x1C);
			volatile uint32* const CMP2R							= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x24);
			volatile uint32* const CMP3R							= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x28);
			volatile uint32* const CMP4R							= (volatile uint32* const) (BASE::HR_TIMER_MASTER + 0x2C);
		};
		
		namespace A
		{
			volatile uint32* const CR									= (volatile uint32* const) (BASE::HR_TIMER_A + 0x00);
			volatile uint32* const ISR								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x04);
			volatile uint32* const ICR								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x08);
			volatile uint32* const DIER								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x0C);
			volatile uint32* const CNT								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x10);
			volatile uint32* const PER								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x14);
			volatile uint32* const REP								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x18);
			volatile uint32* const CMP1								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x1C);
			volatile uint32* const CMP1C							= (volatile uint32* const) (BASE::HR_TIMER_A + 0x20);
			volatile uint32* const CMP2								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x24);
			volatile uint32* const CMP3								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x28);
			volatile uint32* const CMP4								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x2C);
			volatile uint32* const CPT1								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x30);
			volatile uint32* const CPT2								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x34);
			volatile uint32* const DT									= (volatile uint32* const) (BASE::HR_TIMER_A + 0x38);
			volatile uint32* const SET1								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x3C);
			volatile uint32* const RST1								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x40);
			volatile uint32* const SET2								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x44);
			volatile uint32* const RST2								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x48);
			volatile uint32* const EEF1								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x4C);
			volatile uint32* const EEF2								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x50);
			volatile uint32* const RST								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x54);
			volatile uint32* const CHP								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x58);
			volatile uint32* const CPT1CR							= (volatile uint32* const) (BASE::HR_TIMER_A + 0x5C);
			volatile uint32* const CPT2CR							= (volatile uint32* const) (BASE::HR_TIMER_A + 0x60);
			volatile uint32* const OUT								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x64);
			volatile uint32* const FLT								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x68);
		};
		
		namespace B
		{
			volatile uint32* const CR									= (volatile uint32* const) (BASE::HR_TIMER_B + 0x00);
			volatile uint32* const ISR								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x04);
			volatile uint32* const ICR								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x08);
			volatile uint32* const DIER								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x0C);
			volatile uint32* const CNT								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x10);
			volatile uint32* const PER								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x14);
			volatile uint32* const REP								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x18);
			volatile uint32* const CMP1								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x1C);
			volatile uint32* const CMP1C							= (volatile uint32* const) (BASE::HR_TIMER_B + 0x20);
			volatile uint32* const CMP2								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x24);
			volatile uint32* const CMP3								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x28);
			volatile uint32* const CMP4								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x2C);
			volatile uint32* const CPT1								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x30);
			volatile uint32* const CPT2								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x34);
			volatile uint32* const DT									= (volatile uint32* const) (BASE::HR_TIMER_B + 0x38);
			volatile uint32* const SET1								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x3C);
			volatile uint32* const RST1								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x40);
			volatile uint32* const SET2								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x44);
			volatile uint32* const RST2								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x48);
			volatile uint32* const EEF1								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x4C);
			volatile uint32* const EEF2								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x50);
			volatile uint32* const RST								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x54);
			volatile uint32* const CHP								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x58);
			volatile uint32* const CPT1CR							= (volatile uint32* const) (BASE::HR_TIMER_B + 0x5C);
			volatile uint32* const CPT2CR							= (volatile uint32* const) (BASE::HR_TIMER_B + 0x60);
			volatile uint32* const OUT								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x64);
			volatile uint32* const FLT								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x68);
		};
		
		namespace C
		{
			volatile uint32* const CR									= (volatile uint32* const) (BASE::HR_TIMER_C + 0x00);
			volatile uint32* const ISR								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x04);
			volatile uint32* const ICR								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x08);
			volatile uint32* const DIER								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x0C);
			volatile uint32* const CNT								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x10);
			volatile uint32* const PER								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x14);
			volatile uint32* const REP								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x18);
			volatile uint32* const CMP1								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x1C);
			volatile uint32* const CMP1C							= (volatile uint32* const) (BASE::HR_TIMER_C + 0x20);
			volatile uint32* const CMP2								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x24);
			volatile uint32* const CMP3								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x28);
			volatile uint32* const CMP4								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x2C);
			volatile uint32* const CPT1								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x30);
			volatile uint32* const CPT2								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x34);
			volatile uint32* const DT									= (volatile uint32* const) (BASE::HR_TIMER_C + 0x38);
			volatile uint32* const SET1								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x3C);
			volatile uint32* const RST1								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x40);
			volatile uint32* const SET2								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x44);
			volatile uint32* const RST2								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x48);
			volatile uint32* const EEF1								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x4C);
			volatile uint32* const EEF2								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x50);
			volatile uint32* const RST								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x54);
			volatile uint32* const CHP								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x58);
			volatile uint32* const CPT1CR							= (volatile uint32* const) (BASE::HR_TIMER_C + 0x5C);
			volatile uint32* const CPT2CR							= (volatile uint32* const) (BASE::HR_TIMER_C + 0x60);
			volatile uint32* const OUT								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x64);
			volatile uint32* const FLT								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x68);
		};
		
		namespace D
		{
			volatile uint32* const CR									= (volatile uint32* const) (BASE::HR_TIMER_D + 0x00);
			volatile uint32* const ISR								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x04);
			volatile uint32* const ICR								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x08);
			volatile uint32* const DIER								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x0C);
			volatile uint32* const CNT								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x10);
			volatile uint32* const PER								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x14);
			volatile uint32* const REP								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x18);
			volatile uint32* const CMP1								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x1C);
			volatile uint32* const CMP1C							= (volatile uint32* const) (BASE::HR_TIMER_D + 0x20);
			volatile uint32* const CMP2								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x24);
			volatile uint32* const CMP3								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x28);
			volatile uint32* const CMP4								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x2C);
			volatile uint32* const CPT1								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x30);
			volatile uint32* const CPT2								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x34);
			volatile uint32* const DT									= (volatile uint32* const) (BASE::HR_TIMER_D + 0x38);
			volatile uint32* const SET1								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x3C);
			volatile uint32* const RST1								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x40);
			volatile uint32* const SET2								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x44);
			volatile uint32* const RST2								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x48);
			volatile uint32* const EEF1								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x4C);
			volatile uint32* const EEF2								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x50);
			volatile uint32* const RST								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x54);
			volatile uint32* const CHP								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x58);
			volatile uint32* const CPT1CR							= (volatile uint32* const) (BASE::HR_TIMER_D + 0x5C);
			volatile uint32* const CPT2CR							= (volatile uint32* const) (BASE::HR_TIMER_D + 0x60);
			volatile uint32* const OUT								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x64);
			volatile uint32* const FLT								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x68);
		};
		
		namespace E
		{
			volatile uint32* const CR									= (volatile uint32* const) (BASE::HR_TIMER_E + 0x00);
			volatile uint32* const ISR								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x04);
			volatile uint32* const ICR								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x08);
			volatile uint32* const DIER								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x0C);
			volatile uint32* const CNT								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x10);
			volatile uint32* const PER								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x14);
			volatile uint32* const REP								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x18);
			volatile uint32* const CMP1								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x1C);
			volatile uint32* const CMP1C							= (volatile uint32* const) (BASE::HR_TIMER_E + 0x20);
			volatile uint32* const CMP2								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x24);
			volatile uint32* const CMP3								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x28);
			volatile uint32* const CMP4								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x2C);
			volatile uint32* const CPT1								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x30);
			volatile uint32* const CPT2								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x34);
			volatile uint32* const DT									= (volatile uint32* const) (BASE::HR_TIMER_E + 0x38);
			volatile uint32* const SET1								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x3C);
			volatile uint32* const RST1								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x40);
			volatile uint32* const SET2								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x44);
			volatile uint32* const RST2								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x48);
			volatile uint32* const EEF1								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x4C);
			volatile uint32* const EEF2								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x50);
			volatile uint32* const RST								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x54);
			volatile uint32* const CHP								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x58);
			volatile uint32* const CPT1CR							= (volatile uint32* const) (BASE::HR_TIMER_E + 0x5C);
			volatile uint32* const CPT2CR							= (volatile uint32* const) (BASE::HR_TIMER_E + 0x60);
			volatile uint32* const OUT								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x64);
			volatile uint32* const FLT								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x68);
		};
	};
	
	namespace LTDC
	{
		volatile uint32* const SSCR									= (volatile uint32* const) (BASE::LTDC + 0x008);
		volatile uint32* const BPCR									= (volatile uint32* const) (BASE::LTDC + 0x00C);
		volatile uint32* const AWCR									= (volatile uint32* const) (BASE::LTDC + 0x010);
		volatile uint32* const TWCR									= (volatile uint32* const) (BASE::LTDC + 0x014);
		volatile uint32* const GCR									= (volatile uint32* const) (BASE::LTDC + 0x018);
		volatile uint32* const SRCR									= (volatile uint32* const) (BASE::LTDC + 0x024);
		volatile uint32* const BCCR									= (volatile uint32* const) (BASE::LTDC + 0x02C);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::LTDC + 0x034);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::LTDC + 0x038);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::LTDC + 0x03C);
		volatile uint32* const LIPCR								= (volatile uint32* const) (BASE::LTDC + 0x040);
		volatile uint32* const CPSR									= (volatile uint32* const) (BASE::LTDC + 0x044);
		volatile uint32* const CDSR									= (volatile uint32* const) (BASE::LTDC + 0x048);
		volatile uint32* const L1_CR								= (volatile uint32* const) (BASE::LTDC + 0x084);
		volatile uint32* const L1_WHPCR							= (volatile uint32* const) (BASE::LTDC + 0x088);
		volatile uint32* const L1_WVPCR							= (volatile uint32* const) (BASE::LTDC + 0x08C);
		volatile uint32* const L1_CKCR							= (volatile uint32* const) (BASE::LTDC + 0x090);
		volatile uint32* const L1_PFCR							= (volatile uint32* const) (BASE::LTDC + 0x094);
		volatile uint32* const L1_CACR							= (volatile uint32* const) (BASE::LTDC + 0x098);
		volatile uint32* const L1_DCCR							= (volatile uint32* const) (BASE::LTDC + 0x09C);
		volatile uint32* const L1_BFCR							= (volatile uint32* const) (BASE::LTDC + 0x0A0);
		volatile uint32* const L1_CFBAR							= (volatile uint32* const) (BASE::LTDC + 0x0AC);
		volatile uint32* const L1_CFBLR							= (volatile uint32* const) (BASE::LTDC + 0x0B0);
		volatile uint32* const L1_CFBLNR						= (volatile uint32* const) (BASE::LTDC + 0x0B4);
		volatile uint32* const L1_CLUTWR						= (volatile uint32* const) (BASE::LTDC + 0x0C4);
		volatile uint32* const L2_CR								= (volatile uint32* const) (BASE::LTDC + 0x104);
		volatile uint32* const L2_WHPCR							= (volatile uint32* const) (BASE::LTDC + 0x108);
		volatile uint32* const L2_WVPCR							= (volatile uint32* const) (BASE::LTDC + 0x10C);
		volatile uint32* const L2_CKCR							= (volatile uint32* const) (BASE::LTDC + 0x110);
		volatile uint32* const L2_PFCR							= (volatile uint32* const) (BASE::LTDC + 0x114);
		volatile uint32* const L2_CACR							= (volatile uint32* const) (BASE::LTDC + 0x118);
		volatile uint32* const L2_DCCR							= (volatile uint32* const) (BASE::LTDC + 0x11C);
		volatile uint32* const L2_BFCR							= (volatile uint32* const) (BASE::LTDC + 0x120);
		volatile uint32* const L2_CFBAR							= (volatile uint32* const) (BASE::LTDC + 0x12C);
		volatile uint32* const L2_CFBLR							= (volatile uint32* const) (BASE::LTDC + 0x130);
		volatile uint32* const L2_CFBLNR						= (volatile uint32* const) (BASE::LTDC + 0x134);
		volatile uint32* const L2_CLUTWR						= (volatile uint32* const) (BASE::LTDC + 0x144);
	};
	
	namespace WWDG
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::WWDG + 0x00);
		volatile uint32* const CFR									= (volatile uint32* const) (BASE::WWDG + 0x04);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::WWDG + 0x08);
	};
	
	namespace EXTI
	{
		volatile uint32* const RTSR1								= (volatile uint32* const) (BASE::EXTI + 0x00);
		volatile uint32* const FTSR1								= (volatile uint32* const) (BASE::EXTI + 0x04);
		volatile uint32* const SWIER1								= (volatile uint32* const) (BASE::EXTI + 0x08);
		volatile uint32* const D3PMR1								= (volatile uint32* const) (BASE::EXTI + 0x0C);
		volatile uint32* const D3PCR1L							= (volatile uint32* const) (BASE::EXTI + 0x10);
		volatile uint32* const D3PCR1H							= (volatile uint32* const) (BASE::EXTI + 0x14);
		volatile uint32* const RTSR2								= (volatile uint32* const) (BASE::EXTI + 0x20);
		volatile uint32* const FTSR2								= (volatile uint32* const) (BASE::EXTI + 0x24);
		volatile uint32* const SWIER2								= (volatile uint32* const) (BASE::EXTI + 0x28);
		volatile uint32* const D3PMR2								= (volatile uint32* const) (BASE::EXTI + 0x2C);
		volatile uint32* const D3PCR2L							= (volatile uint32* const) (BASE::EXTI + 0x30);
		volatile uint32* const D3PCR2H							= (volatile uint32* const) (BASE::EXTI + 0x34);
		volatile uint32* const RTSR3								= (volatile uint32* const) (BASE::EXTI + 0x40);
		volatile uint32* const FTSR3								= (volatile uint32* const) (BASE::EXTI + 0x44);
		volatile uint32* const SWIER3								= (volatile uint32* const) (BASE::EXTI + 0x48);
		volatile uint32* const D3PMR3								= (volatile uint32* const) (BASE::EXTI + 0x4C);
		volatile uint32* const D3PCR3L							= (volatile uint32* const) (BASE::EXTI + 0x50);
		volatile uint32* const D3PCR3H							= (volatile uint32* const) (BASE::EXTI + 0x54);
		volatile uint32* const CPUIMR1							= (volatile uint32* const) (BASE::EXTI + 0x80);
		volatile uint32* const CPUEMR1							= (volatile uint32* const) (BASE::EXTI + 0x84);
		volatile uint32* const CPUPR1								= (volatile uint32* const) (BASE::EXTI + 0x88);
		volatile uint32* const CPUIMR2							= (volatile uint32* const) (BASE::EXTI + 0x90);
		volatile uint32* const CPUEMR2							= (volatile uint32* const) (BASE::EXTI + 0x94);
		volatile uint32* const CPUPR2								= (volatile uint32* const) (BASE::EXTI + 0x98);
		volatile uint32* const CPUIMR3							= (volatile uint32* const) (BASE::EXTI + 0xA0);
		volatile uint32* const CPUEMR3							= (volatile uint32* const) (BASE::EXTI + 0xA4);
		volatile uint32* const CPUPU3								= (volatile uint32* const) (BASE::EXTI + 0xA8);
	};
	
	namespace SYSCFG
	{
		volatile uint32* const PMCR									= (volatile uint32* const) (BASE::SYSCFG + 0x004);
		volatile uint32* const EXTI_CR1							= (volatile uint32* const) (BASE::SYSCFG + 0x008);
		volatile uint32* const EXTI_CR2							= (volatile uint32* const) (BASE::SYSCFG + 0x00C);
		volatile uint32* const EXTI_CR3							= (volatile uint32* const) (BASE::SYSCFG + 0x010);
		volatile uint32* const EXTI_CR4							= (volatile uint32* const) (BASE::SYSCFG + 0x014);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::SYSCFG + 0x018);
		volatile uint32* const CCSR									= (volatile uint32* const) (BASE::SYSCFG + 0x020);
		volatile uint32* const CCVR									= (volatile uint32* const) (BASE::SYSCFG + 0x024);
		volatile uint32* const CCCR									= (volatile uint32* const) (BASE::SYSCFG + 0x028);
		volatile uint32* const PWRCR								= (volatile uint32* const) (BASE::SYSCFG + 0x02C);
		volatile uint32* const PKGR									= (volatile uint32* const) (BASE::SYSCFG + 0x124);
		volatile uint32* const UR0									= (volatile uint32* const) (BASE::SYSCFG + 0x300);
		volatile uint32* const UR1									= (volatile uint32* const) (BASE::SYSCFG + 0x304);
		volatile uint32* const UR2									= (volatile uint32* const) (BASE::SYSCFG + 0x308);
		volatile uint32* const UR3									= (volatile uint32* const) (BASE::SYSCFG + 0x30C);
		volatile uint32* const UR4									= (volatile uint32* const) (BASE::SYSCFG + 0x310);
		volatile uint32* const UR5									= (volatile uint32* const) (BASE::SYSCFG + 0x314);
		volatile uint32* const UR6									= (volatile uint32* const) (BASE::SYSCFG + 0x318);
		volatile uint32* const UR7									= (volatile uint32* const) (BASE::SYSCFG + 0x31C);
		volatile uint32* const UR8									= (volatile uint32* const) (BASE::SYSCFG + 0x320);
		volatile uint32* const UR9									= (volatile uint32* const) (BASE::SYSCFG + 0x324);
		volatile uint32* const UR10									= (volatile uint32* const) (BASE::SYSCFG + 0x328);
		volatile uint32* const UR11									= (volatile uint32* const) (BASE::SYSCFG + 0x32C);
		volatile uint32* const UR12									= (volatile uint32* const) (BASE::SYSCFG + 0x330);
		volatile uint32* const UR13									= (volatile uint32* const) (BASE::SYSCFG + 0x334);
		volatile uint32* const UR14									= (volatile uint32* const) (BASE::SYSCFG + 0x338);
		volatile uint32* const UR15									= (volatile uint32* const) (BASE::SYSCFG + 0x33C);
		volatile uint32* const UR16									= (volatile uint32* const) (BASE::SYSCFG + 0x340);
		volatile uint32* const UR17									= (volatile uint32* const) (BASE::SYSCFG + 0x344);
	};
	
	namespace LP_UART_1
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::LP_UART_1 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::LP_UART_1 + 0x04);
		volatile uint32* const CR3									= (volatile uint32* const) (BASE::LP_UART_1 + 0x08);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::LP_UART_1 + 0x0C);
		volatile uint32* const RQR									= (volatile uint32* const) (BASE::LP_UART_1 + 0x18);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::LP_UART_1 + 0x1C);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::LP_UART_1 + 0x20);
		volatile uint32* const RDR									= (volatile uint32* const) (BASE::LP_UART_1 + 0x24);
		volatile uint32* const TDR									= (volatile uint32* const) (BASE::LP_UART_1 + 0x28);
		volatile uint32* const PRESC								= (volatile uint32* const) (BASE::LP_UART_1 + 0x2C);
	};
	
	namespace SPI_6
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::SPI_6 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::SPI_6 + 0x04);
		volatile uint32* const CFG1				      		= (volatile uint32* const) (BASE::SPI_6 + 0x08);
		volatile uint32* const CFG2				      		= (volatile uint32* const) (BASE::SPI_6 + 0x0C);
		volatile uint32* const IER				      		= (volatile uint32* const) (BASE::SPI_6 + 0x10);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::SPI_6 + 0x14);
		volatile uint32* const IFCR				      		= (volatile uint32* const) (BASE::SPI_6 + 0x18);
		volatile uint32* const TXDR				      		= (volatile uint32* const) (BASE::SPI_6 + 0x20);
		volatile uint32* const RXDR				      		= (volatile uint32* const) (BASE::SPI_6 + 0x30);
		volatile uint32* const CRCPOLY				  		= (volatile uint32* const) (BASE::SPI_6 + 0x40);
		volatile uint32* const TXCRC				    		= (volatile uint32* const) (BASE::SPI_6 + 0x44);
		volatile uint32* const RXCRC				    		= (volatile uint32* const) (BASE::SPI_6 + 0x48);
		volatile uint32* const UDRDR				    		= (volatile uint32* const) (BASE::SPI_6 + 0x4C);
		volatile uint32* const CFGR				      		= (volatile uint32* const) (BASE::SPI_6 + 0x50);
	};
	
	namespace I2C_4
	{
		volatile uint32* const CR1				      		= (volatile uint32* const) (BASE::I2C_4 + 0x00);
		volatile uint32* const CR2				      		= (volatile uint32* const) (BASE::I2C_4 + 0x04);
		volatile uint32* const OAR1				      		= (volatile uint32* const) (BASE::I2C_4 + 0x08);
		volatile uint32* const OAR2				      		= (volatile uint32* const) (BASE::I2C_4 + 0x0C);
		volatile uint32* const TIMINGR				  		= (volatile uint32* const) (BASE::I2C_4 + 0x10);
		volatile uint32* const TIMEOUTR				  		= (volatile uint32* const) (BASE::I2C_4 + 0x14);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::I2C_4 + 0x18);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::I2C_4 + 0x1C);
		volatile uint32* const PECR				      		= (volatile uint32* const) (BASE::I2C_4 + 0x20);
		volatile uint32* const RXDR				      		= (volatile uint32* const) (BASE::I2C_4 + 0x24);
		volatile uint32* const TXDR				      		= (volatile uint32* const) (BASE::I2C_4 + 0x28);
	};
	
	namespace LP_TIMER_2
	{
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x00);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x04);
		volatile uint32* const IER				      		= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x08);
		volatile uint32* const CFGR				      		= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x0C);
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x10);
		volatile uint32* const CMP				      		= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x14);
		volatile uint32* const ARR				      		= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x18);
		volatile uint32* const CNT				      		= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x1C);
		volatile uint32* const CFGR2				    		= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x24);
	};
	
	namespace LP_TIMER_3
	{
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::LP_TIMER_3 + 0x00);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::LP_TIMER_3 + 0x04);
		volatile uint32* const IER				      		= (volatile uint32* const) (BASE::LP_TIMER_3 + 0x08);
		volatile uint32* const CFGR				      		= (volatile uint32* const) (BASE::LP_TIMER_3 + 0x0C);
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::LP_TIMER_3 + 0x10);
		volatile uint32* const CMP				      		= (volatile uint32* const) (BASE::LP_TIMER_3 + 0x14);
		volatile uint32* const ARR				      		= (volatile uint32* const) (BASE::LP_TIMER_3 + 0x18);
		volatile uint32* const CNT				      		= (volatile uint32* const) (BASE::LP_TIMER_3 + 0x1C);
		volatile uint32* const CFGR2				    		= (volatile uint32* const) (BASE::LP_TIMER_3 + 0x24);
	};
	
	namespace LP_TIMER_4
	{
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::LP_TIMER_4 + 0x00);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::LP_TIMER_4 + 0x04);
		volatile uint32* const IER				      		= (volatile uint32* const) (BASE::LP_TIMER_4 + 0x08);
		volatile uint32* const CFGR				      		= (volatile uint32* const) (BASE::LP_TIMER_4 + 0x0C);
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::LP_TIMER_4 + 0x10);
		volatile uint32* const CMP				      		= (volatile uint32* const) (BASE::LP_TIMER_4 + 0x14);
		volatile uint32* const ARR				      		= (volatile uint32* const) (BASE::LP_TIMER_4 + 0x18);
		volatile uint32* const CNT				      		= (volatile uint32* const) (BASE::LP_TIMER_4 + 0x1C);
		volatile uint32* const CFGR2				    		= (volatile uint32* const) (BASE::LP_TIMER_4 + 0x24);
	};
	
	namespace LP_TIMER_5
	{
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::LP_TIMER_5 + 0x00);
		volatile uint32* const ICR				      		= (volatile uint32* const) (BASE::LP_TIMER_5 + 0x04);
		volatile uint32* const IER				      		= (volatile uint32* const) (BASE::LP_TIMER_5 + 0x08);
		volatile uint32* const CFGR				      		= (volatile uint32* const) (BASE::LP_TIMER_5 + 0x0C);
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::LP_TIMER_5 + 0x10);
		volatile uint32* const CMP				      		= (volatile uint32* const) (BASE::LP_TIMER_5 + 0x14);
		volatile uint32* const ARR				      		= (volatile uint32* const) (BASE::LP_TIMER_5 + 0x18);
		volatile uint32* const CNT				      		= (volatile uint32* const) (BASE::LP_TIMER_5 + 0x1C);
		volatile uint32* const CFGR2				    		= (volatile uint32* const) (BASE::LP_TIMER_5 + 0x24);
	};
	
	namespace COMP
	{
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::COMP + 0x00);
		volatile uint32* const ICFR				      		= (volatile uint32* const) (BASE::COMP + 0x04);
		volatile uint32* const OR				        		= (volatile uint32* const) (BASE::COMP + 0x08);
		volatile uint32* const CFGR1				    		= (volatile uint32* const) (BASE::COMP + 0x0C);
		volatile uint32* const CFGR2				    		= (volatile uint32* const) (BASE::COMP + 0x10);
	};
	
	namespace VREF
	{
		volatile uint32* const CSR				      		= (volatile uint32* const) (BASE::VREF + 0x00);
		volatile uint32* const CCR				      		= (volatile uint32* const) (BASE::VREF + 0x04);
	};
	
	namespace RTC
	{
		volatile uint32* const TR				        		= (volatile uint32* const) (BASE::RTC + 0x00);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::RTC + 0x04);
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::RTC + 0x08);
		volatile uint32* const ISR				      		= (volatile uint32* const) (BASE::RTC + 0x0C);
		volatile uint32* const PRER				      		= (volatile uint32* const) (BASE::RTC + 0x10);
		volatile uint32* const WUTR				      		= (volatile uint32* const) (BASE::RTC + 0x14);
		volatile uint32* const ALRMAR				    		= (volatile uint32* const) (BASE::RTC + 0x1C);
		volatile uint32* const ALRMBR				    		= (volatile uint32* const) (BASE::RTC + 0x20);
		volatile uint32* const WPR				      		= (volatile uint32* const) (BASE::RTC + 0x24);
		volatile uint32* const SSR				      		= (volatile uint32* const) (BASE::RTC + 0x28);
		volatile uint32* const SHIFTR				    		= (volatile uint32* const) (BASE::RTC + 0x2C);
		volatile uint32* const TSTR				      		= (volatile uint32* const) (BASE::RTC + 0x30);
		volatile uint32* const TSDR				      		= (volatile uint32* const) (BASE::RTC + 0x34);
		volatile uint32* const TSSSR				    		= (volatile uint32* const) (BASE::RTC + 0x38);
		volatile uint32* const CALR				      		= (volatile uint32* const) (BASE::RTC + 0x3C);
		volatile uint32* const TAMPCR				    		= (volatile uint32* const) (BASE::RTC + 0x40);
		volatile uint32* const ALRMASSR				  		= (volatile uint32* const) (BASE::RTC + 0x44);
		volatile uint32* const ALRMBSSR				  		= (volatile uint32* const) (BASE::RTC + 0x48);
		volatile uint32* const OR				        		= (volatile uint32* const) (BASE::RTC + 0x4C);
		volatile uint32* const BKP0				      		= (volatile uint32* const) (BASE::RTC + 0x50);
		volatile uint32* const BKP1			        		= (volatile uint32* const) (BASE::RTC + 0x54);
		volatile uint32* const BKP2				      		= (volatile uint32* const) (BASE::RTC + 0x58);
		volatile uint32* const BKP3				      		= (volatile uint32* const) (BASE::RTC + 0x5C);
		volatile uint32* const BKP4				      		= (volatile uint32* const) (BASE::RTC + 0x60);
		volatile uint32* const BKP5				      		= (volatile uint32* const) (BASE::RTC + 0x64);
		volatile uint32* const BKP6				      		= (volatile uint32* const) (BASE::RTC + 0x68);
		volatile uint32* const BKP7				      		= (volatile uint32* const) (BASE::RTC + 0x6C);
		volatile uint32* const BKP8				      		= (volatile uint32* const) (BASE::RTC + 0x70);
		volatile uint32* const BKP9				      		= (volatile uint32* const) (BASE::RTC + 0x74);
		volatile uint32* const BKP10				    		= (volatile uint32* const) (BASE::RTC + 0x78);
		volatile uint32* const BKP11				    		= (volatile uint32* const) (BASE::RTC + 0x7C);
		volatile uint32* const BKP12				    		= (volatile uint32* const) (BASE::RTC + 0x80);
		volatile uint32* const BKP13				    		= (volatile uint32* const) (BASE::RTC + 0x84);
		volatile uint32* const BKP14				    		= (volatile uint32* const) (BASE::RTC + 0x88);
		volatile uint32* const BKP15				    		= (volatile uint32* const) (BASE::RTC + 0x8C);
		volatile uint32* const BKP16				    		= (volatile uint32* const) (BASE::RTC + 0x90);
		volatile uint32* const BKP17				    		= (volatile uint32* const) (BASE::RTC + 0x94);
		volatile uint32* const BKP18				    		= (volatile uint32* const) (BASE::RTC + 0x98);
		volatile uint32* const BKP19				    		= (volatile uint32* const) (BASE::RTC + 0x9C);
		volatile uint32* const BKP20				    		= (volatile uint32* const) (BASE::RTC + 0xA0);
		volatile uint32* const BKP21				    		= (volatile uint32* const) (BASE::RTC + 0xA4);
		volatile uint32* const BKP22				    		= (volatile uint32* const) (BASE::RTC + 0xA8);
		volatile uint32* const BKP23				    		= (volatile uint32* const) (BASE::RTC + 0xAC);
		volatile uint32* const BKP24				    		= (volatile uint32* const) (BASE::RTC + 0xB0);
		volatile uint32* const BKP25				    		= (volatile uint32* const) (BASE::RTC + 0xB4);
		volatile uint32* const BKP26				    		= (volatile uint32* const) (BASE::RTC + 0xB8);
		volatile uint32* const BKP27				    		= (volatile uint32* const) (BASE::RTC + 0xBC);
		volatile uint32* const BKP28				    		= (volatile uint32* const) (BASE::RTC + 0xC0);
		volatile uint32* const BKP29				    		= (volatile uint32* const) (BASE::RTC + 0xC4);
		volatile uint32* const BKP30				    		= (volatile uint32* const) (BASE::RTC + 0xC8);
		volatile uint32* const BKP31				    		= (volatile uint32* const) (BASE::RTC + 0xCC);
	}
	
	namespace IWDG
	{
		volatile uint32* const KR				        		= (volatile uint32* const) (BASE::IWDG + 0x00);
		volatile uint32* const PR				        		= (volatile uint32* const) (BASE::IWDG + 0x04);
		volatile uint32* const RLR				      		= (volatile uint32* const) (BASE::IWDG + 0x08);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::IWDG + 0x0C);
		volatile uint32* const WINR				      		= (volatile uint32* const) (BASE::IWDG + 0x10);
	};
	
	namespace SAI_4
	{
		volatile uint32* const GCR									= (volatile uint32* const) (BASE::SAI_4 + 0x00);
		volatile uint32* const A_CR1            		= (volatile uint32* const) (BASE::SAI_4 + 0x04);
		volatile uint32* const A_CR2            		= (volatile uint32* const) (BASE::SAI_4 + 0x08);
		volatile uint32* const A_FRCR           		= (volatile uint32* const) (BASE::SAI_4 + 0x0C);
		volatile uint32* const A_SLOTR          		= (volatile uint32* const) (BASE::SAI_4 + 0x10);
		volatile uint32* const A_IM             		= (volatile uint32* const) (BASE::SAI_4 + 0x14);
		volatile uint32* const A_SR             		= (volatile uint32* const) (BASE::SAI_4 + 0x18);
		volatile uint32* const A_CLRFR          		= (volatile uint32* const) (BASE::SAI_4 + 0x1C);
		volatile uint32* const A_DR             		= (volatile uint32* const) (BASE::SAI_4 + 0x20);
		volatile uint32* const B_CR1            		= (volatile uint32* const) (BASE::SAI_4 + 0x24);
		volatile uint32* const B_CR2            		= (volatile uint32* const) (BASE::SAI_4 + 0x28);
		volatile uint32* const B_FRCR           		= (volatile uint32* const) (BASE::SAI_4 + 0x2C);
		volatile uint32* const B_SLOTR          		= (volatile uint32* const) (BASE::SAI_4 + 0x30);
		volatile uint32* const B_IM             		= (volatile uint32* const) (BASE::SAI_4 + 0x34);
		volatile uint32* const B_SR             		= (volatile uint32* const) (BASE::SAI_4 + 0x38);
		volatile uint32* const B_CLRFR          		= (volatile uint32* const) (BASE::SAI_4 + 0x3C);
		volatile uint32* const B_DR             		= (volatile uint32* const) (BASE::SAI_4 + 0x40);
		volatile uint32* const PDMCR            		= (volatile uint32* const) (BASE::SAI_4 + 0x44);
		volatile uint32* const PDMDLY           		= (volatile uint32* const) (BASE::SAI_4 + 0x48);
	};
	
	namespace DMA_1
	{
		volatile uint32* const LISR									= (volatile uint32* const) (BASE::DMA_1 + 0x00);
		volatile uint32* const HISR									= (volatile uint32* const) (BASE::DMA_1 + 0x04);
		volatile uint32* const LIFCR								= (volatile uint32* const) (BASE::DMA_1 + 0x08);
		volatile uint32* const HIFCR								= (volatile uint32* const) (BASE::DMA_1 + 0x0C);
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x10);
		volatile uint32* const CH0_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x14);
		volatile uint32* const CH0_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x18);
		volatile uint32* const CH0_M0AR							= (volatile uint32* const) (BASE::DMA_1 + 0x1C);
		volatile uint32* const CH0_M1AR							= (volatile uint32* const) (BASE::DMA_1 + 0x20);
		volatile uint32* const CH0_FCR							= (volatile uint32* const) (BASE::DMA_1 + 0x24);
		volatile uint32* const CH1_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x28);
		volatile uint32* const CH1_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x2C);
		volatile uint32* const CH1_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x30);
		volatile uint32* const CH1_M0AR							= (volatile uint32* const) (BASE::DMA_1 + 0x34);
		volatile uint32* const CH1_M1AR							= (volatile uint32* const) (BASE::DMA_1 + 0x38);
		volatile uint32* const CH1_FCR							= (volatile uint32* const) (BASE::DMA_1 + 0x3C);
		volatile uint32* const CH2_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x40);
		volatile uint32* const CH2_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x44);
		volatile uint32* const CH2_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x48);
		volatile uint32* const CH2_M0AR							= (volatile uint32* const) (BASE::DMA_1 + 0x4C);
		volatile uint32* const CH2_M1AR							= (volatile uint32* const) (BASE::DMA_1 + 0x50);
		volatile uint32* const CH2_FCR							= (volatile uint32* const) (BASE::DMA_1 + 0x54);
		volatile uint32* const CH3_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x58);
		volatile uint32* const CH3_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x5C);
		volatile uint32* const CH3_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x60);
		volatile uint32* const CH3_M0AR							= (volatile uint32* const) (BASE::DMA_1 + 0x64);
		volatile uint32* const CH3_M1AR							= (volatile uint32* const) (BASE::DMA_1 + 0x68);
		volatile uint32* const CH3_FCR							= (volatile uint32* const) (BASE::DMA_1 + 0x6C);
		volatile uint32* const CH4_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x70);
		volatile uint32* const CH4_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x74);
		volatile uint32* const CH4_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x78);
		volatile uint32* const CH4_M0AR							= (volatile uint32* const) (BASE::DMA_1 + 0x7C);
		volatile uint32* const CH4_M1AR							= (volatile uint32* const) (BASE::DMA_1 + 0x80);
		volatile uint32* const CH4_FCR							= (volatile uint32* const) (BASE::DMA_1 + 0x84);
		volatile uint32* const CH5_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x88);
		volatile uint32* const CH5_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x8C);
		volatile uint32* const CH5_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x90);
		volatile uint32* const CH5_M0AR							= (volatile uint32* const) (BASE::DMA_1 + 0x94);
		volatile uint32* const CH5_M1AR							= (volatile uint32* const) (BASE::DMA_1 + 0x98);
		volatile uint32* const CH5_FCR							= (volatile uint32* const) (BASE::DMA_1 + 0x9C);
		volatile uint32* const CH6_CR								= (volatile uint32* const) (BASE::DMA_1 + 0xA0);
		volatile uint32* const CH6_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0xA4);
		volatile uint32* const CH6_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0xA8);
		volatile uint32* const CH6_M0AR							= (volatile uint32* const) (BASE::DMA_1 + 0xAC);
		volatile uint32* const CH6_M1AR							= (volatile uint32* const) (BASE::DMA_1 + 0xB0);
		volatile uint32* const CH6_FCR							= (volatile uint32* const) (BASE::DMA_1 + 0xB4);
		volatile uint32* const CH7_CR								= (volatile uint32* const) (BASE::DMA_1 + 0xB8);
		volatile uint32* const CH7_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0xBC);
		volatile uint32* const CH7_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0xC0);
		volatile uint32* const CH7_M0AR							= (volatile uint32* const) (BASE::DMA_1 + 0xC4);
		volatile uint32* const CH7_M1AR							= (volatile uint32* const) (BASE::DMA_1 + 0xC8);
		volatile uint32* const CH7_FCR							= (volatile uint32* const) (BASE::DMA_1 + 0xCC);
	};
	
	namespace DMA_2
	{
		volatile uint32* const LISR									= (volatile uint32* const) (BASE::DMA_2 + 0x00);
		volatile uint32* const HISR									= (volatile uint32* const) (BASE::DMA_2 + 0x04);
		volatile uint32* const LIFCR								= (volatile uint32* const) (BASE::DMA_2 + 0x08);
		volatile uint32* const HIFCR								= (volatile uint32* const) (BASE::DMA_2 + 0x0C);
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x10);
		volatile uint32* const CH0_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x14);
		volatile uint32* const CH0_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x18);
		volatile uint32* const CH0_M0AR							= (volatile uint32* const) (BASE::DMA_2 + 0x1C);
		volatile uint32* const CH0_M1AR							= (volatile uint32* const) (BASE::DMA_2 + 0x20);
		volatile uint32* const CH0_FCR							= (volatile uint32* const) (BASE::DMA_2 + 0x24);
		volatile uint32* const CH1_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x28);
		volatile uint32* const CH1_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x2C);
		volatile uint32* const CH1_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x30);
		volatile uint32* const CH1_M0AR							= (volatile uint32* const) (BASE::DMA_2 + 0x34);
		volatile uint32* const CH1_M1AR							= (volatile uint32* const) (BASE::DMA_2 + 0x38);
		volatile uint32* const CH1_FCR							= (volatile uint32* const) (BASE::DMA_2 + 0x3C);
		volatile uint32* const CH2_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x40);
		volatile uint32* const CH2_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x44);
		volatile uint32* const CH2_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x48);
		volatile uint32* const CH2_M0AR							= (volatile uint32* const) (BASE::DMA_2 + 0x4C);
		volatile uint32* const CH2_M1AR							= (volatile uint32* const) (BASE::DMA_2 + 0x50);
		volatile uint32* const CH2_FCR							= (volatile uint32* const) (BASE::DMA_2 + 0x54);
		volatile uint32* const CH3_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x58);
		volatile uint32* const CH3_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x5C);
		volatile uint32* const CH3_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x60);
		volatile uint32* const CH3_M0AR							= (volatile uint32* const) (BASE::DMA_2 + 0x64);
		volatile uint32* const CH3_M1AR							= (volatile uint32* const) (BASE::DMA_2 + 0x68);
		volatile uint32* const CH3_FCR							= (volatile uint32* const) (BASE::DMA_2 + 0x6C);
		volatile uint32* const CH4_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x70);
		volatile uint32* const CH4_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x74);
		volatile uint32* const CH4_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x78);
		volatile uint32* const CH4_M0AR							= (volatile uint32* const) (BASE::DMA_2 + 0x7C);
		volatile uint32* const CH4_M1AR							= (volatile uint32* const) (BASE::DMA_2 + 0x80);
		volatile uint32* const CH4_FCR							= (volatile uint32* const) (BASE::DMA_2 + 0x84);
		volatile uint32* const CH5_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x88);
		volatile uint32* const CH5_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x8C);
		volatile uint32* const CH5_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x90);
		volatile uint32* const CH5_M0AR							= (volatile uint32* const) (BASE::DMA_2 + 0x94);
		volatile uint32* const CH5_M1AR							= (volatile uint32* const) (BASE::DMA_2 + 0x98);
		volatile uint32* const CH5_FCR							= (volatile uint32* const) (BASE::DMA_2 + 0x9C);
		volatile uint32* const CH6_CR								= (volatile uint32* const) (BASE::DMA_2 + 0xA0);
		volatile uint32* const CH6_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0xA4);
		volatile uint32* const CH6_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0xA8);
		volatile uint32* const CH6_M0AR							= (volatile uint32* const) (BASE::DMA_2 + 0xAC);
		volatile uint32* const CH6_M1AR							= (volatile uint32* const) (BASE::DMA_2 + 0xB0);
		volatile uint32* const CH6_FCR							= (volatile uint32* const) (BASE::DMA_2 + 0xB4);
		volatile uint32* const CH7_CR								= (volatile uint32* const) (BASE::DMA_2 + 0xB8);
		volatile uint32* const CH7_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0xBC);
		volatile uint32* const CH7_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0xC0);
		volatile uint32* const CH7_M0AR							= (volatile uint32* const) (BASE::DMA_2 + 0xC4);
		volatile uint32* const CH7_M1AR							= (volatile uint32* const) (BASE::DMA_2 + 0xC8);
		volatile uint32* const CH7_FCR							= (volatile uint32* const) (BASE::DMA_2 + 0xCC);
	};
	
	namespace DMAMUX_1
	{
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x000);
		volatile uint32* const CH1_CR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x004);
		volatile uint32* const CH2_CR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x008);
		volatile uint32* const CH3_CR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x00C);
		volatile uint32* const CH4_CR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x010);
		volatile uint32* const CH5_CR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x014);
		volatile uint32* const CH6_CR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x018);
		volatile uint32* const CH7_CR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x01C);
		volatile uint32* const CH8_CR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x020);
		volatile uint32* const CH9_CR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x024);
		volatile uint32* const CH10_CR							= (volatile uint32* const) (BASE::DMAMUX_1 + 0x028);
		volatile uint32* const CH11_CR							= (volatile uint32* const) (BASE::DMAMUX_1 + 0x02C);
		volatile uint32* const CH12_CR							= (volatile uint32* const) (BASE::DMAMUX_1 + 0x030);
		volatile uint32* const CH13_CR							= (volatile uint32* const) (BASE::DMAMUX_1 + 0x034);
		volatile uint32* const CH14_CR							= (volatile uint32* const) (BASE::DMAMUX_1 + 0x038);
		volatile uint32* const CH15_CR							= (volatile uint32* const) (BASE::DMAMUX_1 + 0x03C);
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::DMAMUX_1 + 0x080);
		volatile uint32* const CFR									= (volatile uint32* const) (BASE::DMAMUX_1 + 0x084);
		volatile uint32* const RG_CH0_CR						= (volatile uint32* const) (BASE::DMAMUX_1 + 0x100);
		volatile uint32* const RG_CH1_CR						= (volatile uint32* const) (BASE::DMAMUX_1 + 0x104);
		volatile uint32* const RG_CH2_CR						= (volatile uint32* const) (BASE::DMAMUX_1 + 0x108);
		volatile uint32* const RG_CH3_CR						= (volatile uint32* const) (BASE::DMAMUX_1 + 0x10C);
		volatile uint32* const RG_SR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x140);
		volatile uint32* const RG_CFR								= (volatile uint32* const) (BASE::DMAMUX_1 + 0x144);
	};
	
	namespace ADC_1
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC_1 + 0x00);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC_1 + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::ADC_1 + 0x08);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::ADC_1 + 0x0C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC_1 + 0x10);
		volatile uint32* const SMPR1								= (volatile uint32* const) (BASE::ADC_1 + 0x14);
		volatile uint32* const SMPR2								= (volatile uint32* const) (BASE::ADC_1 + 0x18);
		volatile uint32* const PCSEL								= (volatile uint32* const) (BASE::ADC_1 + 0x1C);
		volatile uint32* const LTR1									= (volatile uint32* const) (BASE::ADC_1 + 0x20);
		volatile uint32* const HTR1									= (volatile uint32* const) (BASE::ADC_1 + 0x24);
		volatile uint32* const SQR1									= (volatile uint32* const) (BASE::ADC_1 + 0x30);
		volatile uint32* const SQR2									= (volatile uint32* const) (BASE::ADC_1 + 0x34);
		volatile uint32* const SQR3									= (volatile uint32* const) (BASE::ADC_1 + 0x38);
		volatile uint32* const SQR4									= (volatile uint32* const) (BASE::ADC_1 + 0x3C);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::ADC_1 + 0x40);
		volatile uint32* const JSQR									= (volatile uint32* const) (BASE::ADC_1 + 0x4C);
		volatile uint32* const OFR1									= (volatile uint32* const) (BASE::ADC_1 + 0x60);
		volatile uint32* const OFR2									= (volatile uint32* const) (BASE::ADC_1 + 0x64);
		volatile uint32* const OFR3									= (volatile uint32* const) (BASE::ADC_1 + 0x68);
		volatile uint32* const OFR4									= (volatile uint32* const) (BASE::ADC_1 + 0x6C);
		volatile uint32* const JDR1									= (volatile uint32* const) (BASE::ADC_1 + 0x80);
		volatile uint32* const JDR2									= (volatile uint32* const) (BASE::ADC_1 + 0x84);
		volatile uint32* const JDR3									= (volatile uint32* const) (BASE::ADC_1 + 0x88);
		volatile uint32* const JDR4									= (volatile uint32* const) (BASE::ADC_1 + 0x8C);
		volatile uint32* const AWD2CR								= (volatile uint32* const) (BASE::ADC_1 + 0xA0);
		volatile uint32* const AWD3CR								= (volatile uint32* const) (BASE::ADC_1 + 0xA4);
		volatile uint32* const LTR2									= (volatile uint32* const) (BASE::ADC_1 + 0xB0);
		volatile uint32* const HTR2									= (volatile uint32* const) (BASE::ADC_1 + 0xB4);
		volatile uint32* const LTR3									= (volatile uint32* const) (BASE::ADC_1 + 0xB8);
		volatile uint32* const HTR3									= (volatile uint32* const) (BASE::ADC_1 + 0xBC);
		volatile uint32* const DIFSEL								= (volatile uint32* const) (BASE::ADC_1 + 0xC0);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC_1 + 0xC4);
		volatile uint32* const CALFACT2							= (volatile uint32* const) (BASE::ADC_1 + 0xC8);
	};
	
	namespace ADC_2
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC_2 + 0x00);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC_2 + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::ADC_2 + 0x08);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::ADC_2 + 0x0C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC_2 + 0x10);
		volatile uint32* const SMPR1								= (volatile uint32* const) (BASE::ADC_2 + 0x14);
		volatile uint32* const SMPR2								= (volatile uint32* const) (BASE::ADC_2 + 0x18);
		volatile uint32* const PCSEL								= (volatile uint32* const) (BASE::ADC_2 + 0x1C);
		volatile uint32* const LTR1									= (volatile uint32* const) (BASE::ADC_2 + 0x20);
		volatile uint32* const HTR1									= (volatile uint32* const) (BASE::ADC_2 + 0x24);
		volatile uint32* const SQR1									= (volatile uint32* const) (BASE::ADC_2 + 0x30);
		volatile uint32* const SQR2									= (volatile uint32* const) (BASE::ADC_2 + 0x34);
		volatile uint32* const SQR3									= (volatile uint32* const) (BASE::ADC_2 + 0x38);
		volatile uint32* const SQR4									= (volatile uint32* const) (BASE::ADC_2 + 0x3C);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::ADC_2 + 0x40);
		volatile uint32* const JSQR									= (volatile uint32* const) (BASE::ADC_2 + 0x4C);
		volatile uint32* const OFR1									= (volatile uint32* const) (BASE::ADC_2 + 0x60);
		volatile uint32* const OFR2									= (volatile uint32* const) (BASE::ADC_2 + 0x64);
		volatile uint32* const OFR3									= (volatile uint32* const) (BASE::ADC_2 + 0x68);
		volatile uint32* const OFR4									= (volatile uint32* const) (BASE::ADC_2 + 0x6C);
		volatile uint32* const JDR1									= (volatile uint32* const) (BASE::ADC_2 + 0x80);
		volatile uint32* const JDR2									= (volatile uint32* const) (BASE::ADC_2 + 0x84);
		volatile uint32* const JDR3									= (volatile uint32* const) (BASE::ADC_2 + 0x88);
		volatile uint32* const JDR4									= (volatile uint32* const) (BASE::ADC_2 + 0x8C);
		volatile uint32* const AWD2CR								= (volatile uint32* const) (BASE::ADC_2 + 0xA0);
		volatile uint32* const AWD3CR								= (volatile uint32* const) (BASE::ADC_2 + 0xA4);
		volatile uint32* const LTR2									= (volatile uint32* const) (BASE::ADC_2 + 0xB0);
		volatile uint32* const HTR2									= (volatile uint32* const) (BASE::ADC_2 + 0xB4);
		volatile uint32* const LTR3									= (volatile uint32* const) (BASE::ADC_2 + 0xB8);
		volatile uint32* const HTR3									= (volatile uint32* const) (BASE::ADC_2 + 0xBC);
		volatile uint32* const DIFSEL								= (volatile uint32* const) (BASE::ADC_2 + 0xC0);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC_2 + 0xC4);
		volatile uint32* const CALFACT2							= (volatile uint32* const) (BASE::ADC_2 + 0xC8);
	};
	
	namespace ADC_1_2_COMMON
	{
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::ADC_1_2_COMMON + 0x00);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::ADC_1_2_COMMON + 0x08);
		volatile uint32* const CDR									= (volatile uint32* const) (BASE::ADC_1_2_COMMON + 0x0C);
		volatile uint32* const CDR2									= (volatile uint32* const) (BASE::ADC_1_2_COMMON + 0x10);
	};
	
	namespace ETH
	{
		volatile uint32* const MAC_CR								= (volatile uint32* const) (BASE::ETH + 0x0000);
		volatile uint32* const MAC_ECR							= (volatile uint32* const) (BASE::ETH + 0x0004);
		volatile uint32* const MAC_PFR							= (volatile uint32* const) (BASE::ETH + 0x0008);
		volatile uint32* const MAC_WTR							= (volatile uint32* const) (BASE::ETH + 0x000C);
		volatile uint32* const MAC_HT0R							= (volatile uint32* const) (BASE::ETH + 0x0010);
		volatile uint32* const MAC_HT1R							= (volatile uint32* const) (BASE::ETH + 0x0014);
		volatile uint32* const MAC_VTR							= (volatile uint32* const) (BASE::ETH + 0x0050);
		volatile uint32* const MAC_VHTR							= (volatile uint32* const) (BASE::ETH + 0x0054);
		volatile uint32* const MAC_VIR							= (volatile uint32* const) (BASE::ETH + 0x0060);
		volatile uint32* const MAC_IVIR							= (volatile uint32* const) (BASE::ETH + 0x0064);
		volatile uint32* const MAC_QTXFCR						= (volatile uint32* const) (BASE::ETH + 0x0070);
		volatile uint32* const MAC_RXFCR						= (volatile uint32* const) (BASE::ETH + 0x0090);
		volatile uint32* const MAC_ISR							= (volatile uint32* const) (BASE::ETH + 0x00B0);
		volatile uint32* const MAC_IER							= (volatile uint32* const) (BASE::ETH + 0x00B4);
		volatile uint32* const MAC_RXTXSR						= (volatile uint32* const) (BASE::ETH + 0x00B8);
		volatile uint32* const MAC_PCSR							= (volatile uint32* const) (BASE::ETH + 0x00C0);
		volatile uint32* const MAC_RWKPFR						= (volatile uint32* const) (BASE::ETH + 0x00C4);
		volatile uint32* const MAC_LCSR							= (volatile uint32* const) (BASE::ETH + 0x00D0);
		volatile uint32* const MAC_LTCR							= (volatile uint32* const) (BASE::ETH + 0x00D4);
		volatile uint32* const MAC_LETR							= (volatile uint32* const) (BASE::ETH + 0x00D8);
		volatile uint32* const MAC_1USTCR						= (volatile uint32* const) (BASE::ETH + 0x00DC);
		volatile uint32* const MAC_VR								= (volatile uint32* const) (BASE::ETH + 0x0110);
		volatile uint32* const MAC_DR								= (volatile uint32* const) (BASE::ETH + 0x0114);
		volatile uint32* const MAC_HWF1R						= (volatile uint32* const) (BASE::ETH + 0x0120);
		volatile uint32* const MAC_HWF2R						= (volatile uint32* const) (BASE::ETH + 0x0124);
		volatile uint32* const MAC_MDIOAR						= (volatile uint32* const) (BASE::ETH + 0x0200);
		volatile uint32* const MAC_MDIODR						= (volatile uint32* const) (BASE::ETH + 0x0204);
		volatile uint32* const MAC_A0HR							= (volatile uint32* const) (BASE::ETH + 0x0300);
		volatile uint32* const MAC_A0LR							= (volatile uint32* const) (BASE::ETH + 0x0304);
		volatile uint32* const MAC_A1HR							= (volatile uint32* const) (BASE::ETH + 0x0308);
		volatile uint32* const MAC_A1LR							= (volatile uint32* const) (BASE::ETH + 0x030C);
		volatile uint32* const MAC_A2HR							= (volatile uint32* const) (BASE::ETH + 0x0310);
		volatile uint32* const MAC_A2LR							= (volatile uint32* const) (BASE::ETH + 0x0314);
		volatile uint32* const MAC_A3HR							= (volatile uint32* const) (BASE::ETH + 0x0318);
		volatile uint32* const MAC_A3LR							= (volatile uint32* const) (BASE::ETH + 0x031C);
		volatile uint32* const MMC_CTRL							= (volatile uint32* const) (BASE::ETH + 0x0700);
		volatile uint32* const MMC_RX_INT						= (volatile uint32* const) (BASE::ETH + 0x0704);
		volatile uint32* const MMC_TX_INT						= (volatile uint32* const) (BASE::ETH + 0x0708);
		volatile uint32* const MMC_RX_INTMASK				= (volatile uint32* const) (BASE::ETH + 0x070C);
		volatile uint32* const MMC_TX_INTMASK				= (volatile uint32* const) (BASE::ETH + 0x0710);
		volatile uint32* const TX_SCOL							= (volatile uint32* const) (BASE::ETH + 0x074C);
		volatile uint32* const TX_MCOL							= (volatile uint32* const) (BASE::ETH + 0x0750);
		volatile uint32* const TX_CNT								= (volatile uint32* const) (BASE::ETH + 0x0768);
		volatile uint32* const RX_CRC_ERR						= (volatile uint32* const) (BASE::ETH + 0x0794);
		volatile uint32* const RX_ALI_ERR						= (volatile uint32* const) (BASE::ETH + 0x0798);
		volatile uint32* const RX_UNICAST						= (volatile uint32* const) (BASE::ETH + 0x07C4);
		volatile uint32* const TX_LPI_USEC_CNTR			= (volatile uint32* const) (BASE::ETH + 0x07EC);
		volatile uint32* const TX_LPI_TRAN_CNTR			= (volatile uint32* const) (BASE::ETH + 0x07F0);
		volatile uint32* const RX_LPI_USEC_CNTR			= (volatile uint32* const) (BASE::ETH + 0x07F4);
		volatile uint32* const RX_LPI_TRAN_CNTR			= (volatile uint32* const) (BASE::ETH + 0x07F8);
		volatile uint32* const MAC_L3L4C0R					= (volatile uint32* const) (BASE::ETH + 0x0900);
		volatile uint32* const MAC_L4A0R						= (volatile uint32* const) (BASE::ETH + 0x0904);
		volatile uint32* const MAC_L3A00R						= (volatile uint32* const) (BASE::ETH + 0x0910);
		volatile uint32* const MAC_L3A10R						= (volatile uint32* const) (BASE::ETH + 0x0914);
		volatile uint32* const MAC_L3A20R						= (volatile uint32* const) (BASE::ETH + 0x0918);
		volatile uint32* const MAC_L3A30R						= (volatile uint32* const) (BASE::ETH + 0x091C);
		volatile uint32* const MAC_L3L4C1R					= (volatile uint32* const) (BASE::ETH + 0x0930);
		volatile uint32* const MAC_L4A1R						= (volatile uint32* const) (BASE::ETH + 0x0934);
		volatile uint32* const MAC_L3A01R						= (volatile uint32* const) (BASE::ETH + 0x0940);
		volatile uint32* const MAC_L3A11R						= (volatile uint32* const) (BASE::ETH + 0x0944);
		volatile uint32* const MAC_L3A21R						= (volatile uint32* const) (BASE::ETH + 0x0948);
		volatile uint32* const MAC_L3A31R						= (volatile uint32* const) (BASE::ETH + 0x094C);
		volatile uint32* const MAC_ARPAR						= (volatile uint32* const) (BASE::ETH + 0x0AE0);
		volatile uint32* const MAC_TSCR							= (volatile uint32* const) (BASE::ETH + 0x0B00);
		volatile uint32* const MAC_SSIR							= (volatile uint32* const) (BASE::ETH + 0x0B04);
		volatile uint32* const MAC_STSR							= (volatile uint32* const) (BASE::ETH + 0x0B08);
		volatile uint32* const MAC_STNR							= (volatile uint32* const) (BASE::ETH + 0x0B0C);
		volatile uint32* const MAC_STSUR						= (volatile uint32* const) (BASE::ETH + 0x0B10);
		volatile uint32* const MAC_STNUR						= (volatile uint32* const) (BASE::ETH + 0x0B14);
		volatile uint32* const MAC_TSAR							= (volatile uint32* const) (BASE::ETH + 0x0B18);
		volatile uint32* const MAC_TSSR							= (volatile uint32* const) (BASE::ETH + 0x0B20);
		volatile uint32* const MAC_TXT_SSNR					= (volatile uint32* const) (BASE::ETH + 0x0B30);
		volatile uint32* const MAC_TXT_SSSR					= (volatile uint32* const) (BASE::ETH + 0x0B34);
		volatile uint32* const MAC_ACR							= (volatile uint32* const) (BASE::ETH + 0x0B40);
		volatile uint32* const MAC_ATSNR						= (volatile uint32* const) (BASE::ETH + 0x0B48);
		volatile uint32* const MAC_ATSSR						= (volatile uint32* const) (BASE::ETH + 0x0B4C);
		volatile uint32* const MAC_TSIACR						= (volatile uint32* const) (BASE::ETH + 0x0B50);
		volatile uint32* const MAC_TSEACR						= (volatile uint32* const) (BASE::ETH + 0x0B54);
		volatile uint32* const MAC_TSICNR						= (volatile uint32* const) (BASE::ETH + 0x0B58);
		volatile uint32* const MAC_TSECNR						= (volatile uint32* const) (BASE::ETH + 0x0B5C);
		volatile uint32* const MAC_PPS_CR						= (volatile uint32* const) (BASE::ETH + 0x0B70);
		volatile uint32* const MAC_PPS_TTSR					= (volatile uint32* const) (BASE::ETH + 0x0B80);
		volatile uint32* const MAC_PPS_TTNR					= (volatile uint32* const) (BASE::ETH + 0x0B84);
		volatile uint32* const MAC_PPS_IR						= (volatile uint32* const) (BASE::ETH + 0x0B88);
		volatile uint32* const MAC_PPS_WR						= (volatile uint32* const) (BASE::ETH + 0x0B8C);
		volatile uint32* const MAC_POCR							= (volatile uint32* const) (BASE::ETH + 0x0BC0);
		volatile uint32* const MAC_SPI0R						= (volatile uint32* const) (BASE::ETH + 0x0BC4);
		volatile uint32* const MAC_SPI1R						= (volatile uint32* const) (BASE::ETH + 0x0BC8);
		volatile uint32* const MAC_SPI2R						= (volatile uint32* const) (BASE::ETH + 0x0BCC);
		volatile uint32* const MAC_LMIR							= (volatile uint32* const) (BASE::ETH + 0x0BD0);
		volatile uint32* const MTL_OMR							= (volatile uint32* const) (BASE::ETH + 0x0C00);
		volatile uint32* const MTL_ISR							= (volatile uint32* const) (BASE::ETH + 0x0C20);
		volatile uint32* const MTL_TXQ_OMR					= (volatile uint32* const) (BASE::ETH + 0x0D00);
		volatile uint32* const MTL_TXQ_UR						= (volatile uint32* const) (BASE::ETH + 0x0D04);
		volatile uint32* const MTL_TXQ_DR						= (volatile uint32* const) (BASE::ETH + 0x0D08);
		volatile uint32* const MTL_QICSR						= (volatile uint32* const) (BASE::ETH + 0x0D2C);
		volatile uint32* const MTL_RXQ_OMR					= (volatile uint32* const) (BASE::ETH + 0x0D30);
		volatile uint32* const MTL_RXQ_MPOCR				= (volatile uint32* const) (BASE::ETH + 0x0D34);
		volatile uint32* const MTL_RXQ_DR						= (volatile uint32* const) (BASE::ETH + 0x0D38);
		volatile uint32* const DMA_MR								= (volatile uint32* const) (BASE::ETH + 0x1000);
		volatile uint32* const DMA_SBMR							= (volatile uint32* const) (BASE::ETH + 0x1004);
		volatile uint32* const DMA_ISR							= (volatile uint32* const) (BASE::ETH + 0x1008);
		volatile uint32* const DMA_DSR							= (volatile uint32* const) (BASE::ETH + 0x100C);
		volatile uint32* const DMA_CH_CR						= (volatile uint32* const) (BASE::ETH + 0x1100);
		volatile uint32* const DMA_CH_TX_CR					= (volatile uint32* const) (BASE::ETH + 0x1104);
		volatile uint32* const DMA_CH_RX_CR					= (volatile uint32* const) (BASE::ETH + 0x1108);
		volatile uint32* const DMA_CH_TX_DLAR				= (volatile uint32* const) (BASE::ETH + 0x1114);
		volatile uint32* const DMA_CH_RX_DLAR				= (volatile uint32* const) (BASE::ETH + 0x111C);
		volatile uint32* const DMA_CH_TX_DTPR				= (volatile uint32* const) (BASE::ETH + 0x1120);
		volatile uint32* const DMA_CH_RX_DTPR				= (volatile uint32* const) (BASE::ETH + 0x1128);
		volatile uint32* const DMA_CH_TX_DRLR				= (volatile uint32* const) (BASE::ETH + 0x112C);
		volatile uint32* const DMA_CH_RX_DRLR				= (volatile uint32* const) (BASE::ETH + 0x1130);
		volatile uint32* const DMA_CH_IER						= (volatile uint32* const) (BASE::ETH + 0x1134);
		volatile uint32* const DMA_CH_RX_IWTR				= (volatile uint32* const) (BASE::ETH + 0x1138);
		volatile uint32* const DMA_CH_CA_TX_DR			= (volatile uint32* const) (BASE::ETH + 0x1144);
		volatile uint32* const DMA_CH_CA_RX_DR			= (volatile uint32* const) (BASE::ETH + 0x114C);
		volatile uint32* const DMA_CH_CA_TX_BR			= (volatile uint32* const) (BASE::ETH + 0x1154);
		volatile uint32* const DMA_CH_CA_RX_BR			= (volatile uint32* const) (BASE::ETH + 0x115C);
		volatile uint32* const DMA_CH_SR						= (volatile uint32* const) (BASE::ETH + 0x1160);
		volatile uint32* const DMA_CH_MFCR					= (volatile uint32* const) (BASE::ETH + 0x116C);
	};
	
	namespace USB_1
	{
		namespace GLOBAL
		{
			volatile uint32* const OTG_CTL							= (volatile uint32* const) (BASE::USB_1 + 0x000);
			volatile uint32* const OTG_INT							= (volatile uint32* const) (BASE::USB_1 + 0x004);
			volatile uint32* const AHB_CFG							= (volatile uint32* const) (BASE::USB_1 + 0x008);
			volatile uint32* const USB_CFG							= (volatile uint32* const) (BASE::USB_1 + 0x00C);
			volatile uint32* const RST_CTL							= (volatile uint32* const) (BASE::USB_1 + 0x010);
			volatile uint32* const INT_STS							= (volatile uint32* const) (BASE::USB_1 + 0x014);
			volatile uint32* const INT_MSK							= (volatile uint32* const) (BASE::USB_1 + 0x018);
			volatile uint32* const RX_STSR							= (volatile uint32* const) (BASE::USB_1 + 0x01C);
			volatile uint32* const RX_STSP							= (volatile uint32* const) (BASE::USB_1 + 0x020);
			volatile uint32* const RX_FSIZ							= (volatile uint32* const) (BASE::USB_1 + 0x024);
			volatile uint32* const HNPTFSIZ_DIEPTXF0		= (volatile uint32* const) (BASE::USB_1 + 0x028);
			volatile uint32* const HNPTXSTS							= (volatile uint32* const) (BASE::USB_1 + 0x02C);
			volatile uint32* const GCCFG								= (volatile uint32* const) (BASE::USB_1 + 0x038);
			volatile uint32* const CID									= (volatile uint32* const) (BASE::USB_1 + 0x03C);
			volatile uint32* const LPM_CFG							= (volatile uint32* const) (BASE::USB_1 + 0x054);
			volatile uint32* const HPTX_FSIZ						= (volatile uint32* const) (BASE::USB_1 + 0x100);
			volatile uint32* const DIEP_TXF1						= (volatile uint32* const) (BASE::USB_1 + 0x104);
			volatile uint32* const DIEP_TXF2						= (volatile uint32* const) (BASE::USB_1 + 0x108);
			volatile uint32* const DIEP_TXF3						= (volatile uint32* const) (BASE::USB_1 + 0x10C);
			volatile uint32* const DIEP_TXF4						= (volatile uint32* const) (BASE::USB_1 + 0x110);
			volatile uint32* const DIEP_TXF5						= (volatile uint32* const) (BASE::USB_1 + 0x114);
			volatile uint32* const DIEP_TXF6						= (volatile uint32* const) (BASE::USB_1 + 0x118);
			volatile uint32* const DIEP_TXF7						= (volatile uint32* const) (BASE::USB_1 + 0x11C);
			volatile uint32* const DIEP_TXF8						= (volatile uint32* const) (BASE::USB_1 + 0x120);
		};
		
		namespace HOST
		{
			volatile uint32* const CFG									= (volatile uint32* const) (BASE::USB_1 + 0x400);
			volatile uint32* const FIR									= (volatile uint32* const) (BASE::USB_1 + 0x404);
			volatile uint32* const FNUM									= (volatile uint32* const) (BASE::USB_1 + 0x408);
			volatile uint32* const PTX_STS							= (volatile uint32* const) (BASE::USB_1 + 0x410);
			volatile uint32* const AINT									= (volatile uint32* const) (BASE::USB_1 + 0x414);
			volatile uint32* const AINT_MSK							= (volatile uint32* const) (BASE::USB_1 + 0x418);
			volatile uint32* const PRT									= (volatile uint32* const) (BASE::USB_1 + 0x440);
			
			
			volatile uint32* const CHAR0								= (volatile uint32* const) (BASE::USB_1 + 0x500);
			volatile uint32* const SPLT0								= (volatile uint32* const) (BASE::USB_1 + 0x504);
			volatile uint32* const INT0									= (volatile uint32* const) (BASE::USB_1 + 0x508);
			volatile uint32* const INTMSK0							= (volatile uint32* const) (BASE::USB_1 + 0x50C);
			volatile uint32* const TSIZ0								= (volatile uint32* const) (BASE::USB_1 + 0x510);
			volatile uint32* const DMA0									= (volatile uint32* const) (BASE::USB_1 + 0x514);
			
			volatile uint32* const CHAR1								= (volatile uint32* const) (BASE::USB_1 + 0x520);
			volatile uint32* const SPLT1								= (volatile uint32* const) (BASE::USB_1 + 0x524);
			volatile uint32* const INT1									= (volatile uint32* const) (BASE::USB_1 + 0x528);
			volatile uint32* const INTMSK1							= (volatile uint32* const) (BASE::USB_1 + 0x52C);
			volatile uint32* const TSIZ1								= (volatile uint32* const) (BASE::USB_1 + 0x530);
			volatile uint32* const DMA1									= (volatile uint32* const) (BASE::USB_1 + 0x534);
			
			volatile uint32* const CHAR2								= (volatile uint32* const) (BASE::USB_1 + 0x540);
			volatile uint32* const SPLT2								= (volatile uint32* const) (BASE::USB_1 + 0x544);
			volatile uint32* const INT2									= (volatile uint32* const) (BASE::USB_1 + 0x548);
			volatile uint32* const INTMSK2							= (volatile uint32* const) (BASE::USB_1 + 0x54C);
			volatile uint32* const TSIZ2								= (volatile uint32* const) (BASE::USB_1 + 0x550);
			volatile uint32* const DMA2									= (volatile uint32* const) (BASE::USB_1 + 0x554);
			
			volatile uint32* const CHAR3								= (volatile uint32* const) (BASE::USB_1 + 0x560);
			volatile uint32* const SPLT3								= (volatile uint32* const) (BASE::USB_1 + 0x564);
			volatile uint32* const INT3									= (volatile uint32* const) (BASE::USB_1 + 0x568);
			volatile uint32* const INTMSK3							= (volatile uint32* const) (BASE::USB_1 + 0x56C);
			volatile uint32* const TSIZ3								= (volatile uint32* const) (BASE::USB_1 + 0x570);
			volatile uint32* const DMA3									= (volatile uint32* const) (BASE::USB_1 + 0x574);
			
			volatile uint32* const CHAR4								= (volatile uint32* const) (BASE::USB_1 + 0x580);
			volatile uint32* const SPLT4								= (volatile uint32* const) (BASE::USB_1 + 0x584);
			volatile uint32* const INT4									= (volatile uint32* const) (BASE::USB_1 + 0x588);
			volatile uint32* const INTMSK4							= (volatile uint32* const) (BASE::USB_1 + 0x58C);
			volatile uint32* const TSIZ4								= (volatile uint32* const) (BASE::USB_1 + 0x590);
			volatile uint32* const DMA4									= (volatile uint32* const) (BASE::USB_1 + 0x594);
			
			volatile uint32* const CHAR5								= (volatile uint32* const) (BASE::USB_1 + 0x5A0);
			volatile uint32* const SPLT5								= (volatile uint32* const) (BASE::USB_1 + 0x5A4);
			volatile uint32* const INT5									= (volatile uint32* const) (BASE::USB_1 + 0x5A8);
			volatile uint32* const INTMSK5							= (volatile uint32* const) (BASE::USB_1 + 0x5AC);
			volatile uint32* const TSIZ5								= (volatile uint32* const) (BASE::USB_1 + 0x5B0);
			volatile uint32* const DMA5									= (volatile uint32* const) (BASE::USB_1 + 0x5B4);
			
			volatile uint32* const CHAR6								= (volatile uint32* const) (BASE::USB_1 + 0x5C0);
			volatile uint32* const SPLT6								= (volatile uint32* const) (BASE::USB_1 + 0x5C4);
			volatile uint32* const INT6									= (volatile uint32* const) (BASE::USB_1 + 0x5C8);
			volatile uint32* const INTMSK6							= (volatile uint32* const) (BASE::USB_1 + 0x5CC);
			volatile uint32* const TSIZ6								= (volatile uint32* const) (BASE::USB_1 + 0x5D0);
			volatile uint32* const DMA6									= (volatile uint32* const) (BASE::USB_1 + 0x5D4);
			
			volatile uint32* const CHAR7								= (volatile uint32* const) (BASE::USB_1 + 0x5E0);
			volatile uint32* const SPLT7								= (volatile uint32* const) (BASE::USB_1 + 0x5E4);
			volatile uint32* const INT7									= (volatile uint32* const) (BASE::USB_1 + 0x5E8);
			volatile uint32* const INTMSK7							= (volatile uint32* const) (BASE::USB_1 + 0x5EC);
			volatile uint32* const TSIZ7 								= (volatile uint32* const) (BASE::USB_1 + 0x5F0);
			volatile uint32* const DMA7									= (volatile uint32* const) (BASE::USB_1 + 0x5F4);
			
			volatile uint32* const CHAR8								= (volatile uint32* const) (BASE::USB_1 + 0x600);
			volatile uint32* const SPLT8								= (volatile uint32* const) (BASE::USB_1 + 0x604);
			volatile uint32* const INT8									= (volatile uint32* const) (BASE::USB_1 + 0x608);
			volatile uint32* const INTMSK8							= (volatile uint32* const) (BASE::USB_1 + 0x60C);
			volatile uint32* const TSIZ8								= (volatile uint32* const) (BASE::USB_1 + 0x610);
			volatile uint32* const DMA8									= (volatile uint32* const) (BASE::USB_1 + 0x614);
			
			volatile uint32* const CHAR9								= (volatile uint32* const) (BASE::USB_1 + 0x620);
			volatile uint32* const SPLT9								= (volatile uint32* const) (BASE::USB_1 + 0x624);
			volatile uint32* const INT9									= (volatile uint32* const) (BASE::USB_1 + 0x628);
			volatile uint32* const INTMSK9							= (volatile uint32* const) (BASE::USB_1 + 0x62C);
			volatile uint32* const TSIZ9								= (volatile uint32* const) (BASE::USB_1 + 0x630);
			volatile uint32* const DMA9									= (volatile uint32* const) (BASE::USB_1 + 0x634);
			
			volatile uint32* const CHAR10								= (volatile uint32* const) (BASE::USB_1 + 0x640);
			volatile uint32* const SPLT10								= (volatile uint32* const) (BASE::USB_1 + 0x644);
			volatile uint32* const INT10								= (volatile uint32* const) (BASE::USB_1 + 0x648);
			volatile uint32* const INTMSK10							= (volatile uint32* const) (BASE::USB_1 + 0x64C);
			volatile uint32* const TSIZ10								= (volatile uint32* const) (BASE::USB_1 + 0x650);
			volatile uint32* const DMA10								= (volatile uint32* const) (BASE::USB_1 + 0x654);
			
			volatile uint32* const CHAR11								= (volatile uint32* const) (BASE::USB_1 + 0x660);
			volatile uint32* const SPLT11								= (volatile uint32* const) (BASE::USB_1 + 0x664);
			volatile uint32* const INT11								= (volatile uint32* const) (BASE::USB_1 + 0x668);
			volatile uint32* const INTMSK11							= (volatile uint32* const) (BASE::USB_1 + 0x66C);
			volatile uint32* const TSIZ11								= (volatile uint32* const) (BASE::USB_1 + 0x670);
			volatile uint32* const DMA11								= (volatile uint32* const) (BASE::USB_1 + 0x674);
			
			volatile uint32* const CHAR12								= (volatile uint32* const) (BASE::USB_1 + 0x680);
			volatile uint32* const SPLT12								= (volatile uint32* const) (BASE::USB_1 + 0x684);
			volatile uint32* const INT12								= (volatile uint32* const) (BASE::USB_1 + 0x688);
			volatile uint32* const INTMSK12							= (volatile uint32* const) (BASE::USB_1 + 0x68C);
			volatile uint32* const TSIZ12								= (volatile uint32* const) (BASE::USB_1 + 0x690);
			volatile uint32* const DMA12								= (volatile uint32* const) (BASE::USB_1 + 0x694);
			
			volatile uint32* const CHAR13								= (volatile uint32* const) (BASE::USB_1 + 0x6A0);
			volatile uint32* const SPLT13								= (volatile uint32* const) (BASE::USB_1 + 0x6A4);
			volatile uint32* const INT13								= (volatile uint32* const) (BASE::USB_1 + 0x6A8);
			volatile uint32* const INTMSK13							= (volatile uint32* const) (BASE::USB_1 + 0x6AC);
			volatile uint32* const TSIZ13								= (volatile uint32* const) (BASE::USB_1 + 0x6B0);
			volatile uint32* const DMA13								= (volatile uint32* const) (BASE::USB_1 + 0x6B4);
			
			volatile uint32* const CHAR14								= (volatile uint32* const) (BASE::USB_1 + 0x6C0);
			volatile uint32* const SPLT14								= (volatile uint32* const) (BASE::USB_1 + 0x6C4);
			volatile uint32* const INT14								= (volatile uint32* const) (BASE::USB_1 + 0x6C8);
			volatile uint32* const INTMSK14							= (volatile uint32* const) (BASE::USB_1 + 0x6CC);
			volatile uint32* const TSIZ14								= (volatile uint32* const) (BASE::USB_1 + 0x6D0);
			volatile uint32* const DMA14								= (volatile uint32* const) (BASE::USB_1 + 0x6D4);
			
			volatile uint32* const CHAR15								= (volatile uint32* const) (BASE::USB_1 + 0x6E0);
			volatile uint32* const SPLT15								= (volatile uint32* const) (BASE::USB_1 + 0x6E4);
			volatile uint32* const INT15								= (volatile uint32* const) (BASE::USB_1 + 0x6E8);
			volatile uint32* const INTMSK15							= (volatile uint32* const) (BASE::USB_1 + 0x6EC);
			volatile uint32* const TSIZ15								= (volatile uint32* const) (BASE::USB_1 + 0x6F0);
			volatile uint32* const DMA15								= (volatile uint32* const) (BASE::USB_1 + 0x6F4);
		};
		
		namespace DEVICE
		{
			volatile uint32* const CFG									= (volatile uint32* const) (BASE::USB_1 + 0x800);
			volatile uint32* const CTL									= (volatile uint32* const) (BASE::USB_1 + 0x804);
			volatile uint32* const STS									= (volatile uint32* const) (BASE::USB_1 + 0x808);
			volatile uint32* const IEPMSK								= (volatile uint32* const) (BASE::USB_1 + 0x810);
			volatile uint32* const OEPMSK								= (volatile uint32* const) (BASE::USB_1 + 0x814);
			volatile uint32* const AINT									= (volatile uint32* const) (BASE::USB_1 + 0x818);
			volatile uint32* const AINTMSK							= (volatile uint32* const) (BASE::USB_1 + 0x81C);
			volatile uint32* const VBUS_DIS							= (volatile uint32* const) (BASE::USB_1 + 0x828);
			volatile uint32* const VBUS_PULSE						= (volatile uint32* const) (BASE::USB_1 + 0x82C);
			volatile uint32* const THR_CTL							= (volatile uint32* const) (BASE::USB_1 + 0x830);
			volatile uint32* const IEP_EMPMSK						= (volatile uint32* const) (BASE::USB_1 + 0x834);
			volatile uint32* const EACH_INT							= (volatile uint32* const) (BASE::USB_1 + 0x838);
			volatile uint32* const EACH_INTMSK					= (volatile uint32* const) (BASE::USB_1 + 0x83C);
			volatile uint32* const IEP_EACH_MSK1				= (volatile uint32* const) (BASE::USB_1 + 0x844);
			volatile uint32* const OEP_EACH_MSK1				= (volatile uint32* const) (BASE::USB_1 + 0x884);
			
			
			volatile uint32* const IEP_CTL0							= (volatile uint32* const) (BASE::USB_1 + 0x900);
			volatile uint32* const IEP_INT0							= (volatile uint32* const) (BASE::USB_1 + 0x908);
			volatile uint32* const IEP_TSIZ0						= (volatile uint32* const) (BASE::USB_1 + 0x910);
			volatile uint32* const IEP_DMA0							= (volatile uint32* const) (BASE::USB_1 + 0x914);
			volatile uint32* const TX_FSTS0							= (volatile uint32* const) (BASE::USB_1 + 0x918);
			
			volatile uint32* const IEP_CTL1							= (volatile uint32* const) (BASE::USB_1 + 0x920);
			volatile uint32* const IEP_INT1							= (volatile uint32* const) (BASE::USB_1 + 0x928);
			volatile uint32* const IEP_TSIZ1						= (volatile uint32* const) (BASE::USB_1 + 0x930);
			volatile uint32* const IEP_DMA1							= (volatile uint32* const) (BASE::USB_1 + 0x934);
			volatile uint32* const TX_FSTS1							= (volatile uint32* const) (BASE::USB_1 + 0x938);
			
			volatile uint32* const IEP_CTL2							= (volatile uint32* const) (BASE::USB_1 + 0x940);
			volatile uint32* const IEP_INT2							= (volatile uint32* const) (BASE::USB_1 + 0x948);
			volatile uint32* const IEP_TSIZ2						= (volatile uint32* const) (BASE::USB_1 + 0x950);
			volatile uint32* const IEP_DMA2							= (volatile uint32* const) (BASE::USB_1 + 0x954);
			volatile uint32* const TX_FSTS2							= (volatile uint32* const) (BASE::USB_1 + 0x958);
			
			volatile uint32* const IEP_CTL3							= (volatile uint32* const) (BASE::USB_1 + 0x960);
			volatile uint32* const IEP_INT3							= (volatile uint32* const) (BASE::USB_1 + 0x968);
			volatile uint32* const IEP_TSIZ3						= (volatile uint32* const) (BASE::USB_1 + 0x970);
			volatile uint32* const IEP_DMA3							= (volatile uint32* const) (BASE::USB_1 + 0x974);
			volatile uint32* const TX_FSTS3							= (volatile uint32* const) (BASE::USB_1 + 0x978);
			
			volatile uint32* const IEP_CTL4							= (volatile uint32* const) (BASE::USB_1 + 0x980);
			volatile uint32* const IEP_INT4							= (volatile uint32* const) (BASE::USB_1 + 0x988);
			volatile uint32* const IEP_TSIZ4						= (volatile uint32* const) (BASE::USB_1 + 0x990);
			volatile uint32* const IEP_DMA4							= (volatile uint32* const) (BASE::USB_1 + 0x994);
			volatile uint32* const TX_FSTS4							= (volatile uint32* const) (BASE::USB_1 + 0x998);
			
			volatile uint32* const IEP_CTL5							= (volatile uint32* const) (BASE::USB_1 + 0x9A0);
			volatile uint32* const IEP_INT5							= (volatile uint32* const) (BASE::USB_1 + 0x9A8);
			volatile uint32* const IEP_TSIZ5						= (volatile uint32* const) (BASE::USB_1 + 0x9B0);
			volatile uint32* const IEP_DMA5							= (volatile uint32* const) (BASE::USB_1 + 0x9B4);
			volatile uint32* const TX_FSTS5							= (volatile uint32* const) (BASE::USB_1 + 0x9B8);
			
			volatile uint32* const IEP_CTL6							= (volatile uint32* const) (BASE::USB_1 + 0x9C0);
			volatile uint32* const IEP_INT6							= (volatile uint32* const) (BASE::USB_1 + 0x9C8);
			volatile uint32* const IEP_TSIZ6						= (volatile uint32* const) (BASE::USB_1 + 0x9D0);
			volatile uint32* const IEP_DMA6							= (volatile uint32* const) (BASE::USB_1 + 0x9D4);
			volatile uint32* const TX_FSTS6							= (volatile uint32* const) (BASE::USB_1 + 0x9D8);
			
			volatile uint32* const IEP_CTL7							= (volatile uint32* const) (BASE::USB_1 + 0x9E0);
			volatile uint32* const IEP_INT7							= (volatile uint32* const) (BASE::USB_1 + 0x9E8);
			volatile uint32* const IEP_TSIZ7						= (volatile uint32* const) (BASE::USB_1 + 0x9F0);
			volatile uint32* const IEP_DMA7							= (volatile uint32* const) (BASE::USB_1 + 0x9F4);
			volatile uint32* const TX_FSTS7							= (volatile uint32* const) (BASE::USB_1 + 0x9F8);
			
			volatile uint32* const IEP_CTL8							= (volatile uint32* const) (BASE::USB_1 + 0xA00);
			volatile uint32* const IEP_INT8							= (volatile uint32* const) (BASE::USB_1 + 0xA08);
			volatile uint32* const IEP_TSIZ8						= (volatile uint32* const) (BASE::USB_1 + 0xA10);
			volatile uint32* const IEP_DMA8							= (volatile uint32* const) (BASE::USB_1 + 0xA14);
			volatile uint32* const TX_FSTS8							= (volatile uint32* const) (BASE::USB_1 + 0xA18);
			
			
			volatile uint32* const OEP_CTL0							= (volatile uint32* const) (BASE::USB_1 + 0xB00);
			volatile uint32* const OEP_INT0							= (volatile uint32* const) (BASE::USB_1 + 0xB08);
			volatile uint32* const OEP_TSIZ0						= (volatile uint32* const) (BASE::USB_1 + 0xB10);
			volatile uint32* const OEP_DMA0							= (volatile uint32* const) (BASE::USB_1 + 0xB14);
			
			volatile uint32* const OEP_CTL1							= (volatile uint32* const) (BASE::USB_1 + 0xB20);
			volatile uint32* const OEP_INT1							= (volatile uint32* const) (BASE::USB_1 + 0xB28);
			volatile uint32* const OEP_TSIZ1						= (volatile uint32* const) (BASE::USB_1 + 0xB30);
			volatile uint32* const OEP_DMA1							= (volatile uint32* const) (BASE::USB_1 + 0xB34);
			
			volatile uint32* const OEP_CTL2							= (volatile uint32* const) (BASE::USB_1 + 0xB40);
			volatile uint32* const OEP_INT2							= (volatile uint32* const) (BASE::USB_1 + 0xB48);
			volatile uint32* const OEP_TSIZ2						= (volatile uint32* const) (BASE::USB_1 + 0xB50);
			volatile uint32* const OEP_DMA2							= (volatile uint32* const) (BASE::USB_1 + 0xB54);
			
			volatile uint32* const OEP_CTL3							= (volatile uint32* const) (BASE::USB_1 + 0xB60);
			volatile uint32* const OEP_INT3							= (volatile uint32* const) (BASE::USB_1 + 0xB68);
			volatile uint32* const OEP_TSIZ3						= (volatile uint32* const) (BASE::USB_1 + 0xB70);
			volatile uint32* const OEP_DMA3							= (volatile uint32* const) (BASE::USB_1 + 0xB74);
			
			volatile uint32* const OEP_CTL4							= (volatile uint32* const) (BASE::USB_1 + 0xB80);
			volatile uint32* const OEP_INT4							= (volatile uint32* const) (BASE::USB_1 + 0xB88);
			volatile uint32* const OEP_TSIZ4						= (volatile uint32* const) (BASE::USB_1 + 0xB90);
			volatile uint32* const OEP_DMA4							= (volatile uint32* const) (BASE::USB_1 + 0xB94);
			
			volatile uint32* const OEP_CTL5							= (volatile uint32* const) (BASE::USB_1 + 0xBA0);
			volatile uint32* const OEP_INT5							= (volatile uint32* const) (BASE::USB_1 + 0xBA8);
			volatile uint32* const OEP_TSIZ5						= (volatile uint32* const) (BASE::USB_1 + 0xBB0);
			volatile uint32* const OEP_DMA5							= (volatile uint32* const) (BASE::USB_1 + 0xBB4);
			
			volatile uint32* const OEP_CTL6							= (volatile uint32* const) (BASE::USB_1 + 0xBC0);
			volatile uint32* const OEP_INT6							= (volatile uint32* const) (BASE::USB_1 + 0xBC8);
			volatile uint32* const OEP_TSIZ6						= (volatile uint32* const) (BASE::USB_1 + 0xBD0);
			volatile uint32* const OEP_DMA6							= (volatile uint32* const) (BASE::USB_1 + 0xBD4);
			
			volatile uint32* const OEP_CTL7							= (volatile uint32* const) (BASE::USB_1 + 0xBE0);
			volatile uint32* const OEP_INT7							= (volatile uint32* const) (BASE::USB_1 + 0xBE8);
			volatile uint32* const OEP_TSIZ7						= (volatile uint32* const) (BASE::USB_1 + 0xBF0);
			volatile uint32* const OEP_DMA7							= (volatile uint32* const) (BASE::USB_1 + 0xBF4);
			
			volatile uint32* const OEP_CTL8							= (volatile uint32* const) (BASE::USB_1 + 0xC00);
			volatile uint32* const OEP_INT8							= (volatile uint32* const) (BASE::USB_1 + 0xC08);
			volatile uint32* const OEP_TSIZ8						= (volatile uint32* const) (BASE::USB_1 + 0xC10);
			volatile uint32* const OEP_DMA8							= (volatile uint32* const) (BASE::USB_1 + 0xC14);
		};
		
		namespace GLOBAL
		{
			volatile uint32* const PCGC_CTL							= (volatile uint32* const) (BASE::USB_1 + 0xE00);
		};
	};
	
	namespace USB_2
	{
		namespace GLOBAL
		{
			volatile uint32* const OTG_CTL							= (volatile uint32* const) (BASE::USB_1 + 0x000);
			volatile uint32* const OTG_INT							= (volatile uint32* const) (BASE::USB_1 + 0x004);
			volatile uint32* const AHB_CFG							= (volatile uint32* const) (BASE::USB_1 + 0x008);
			volatile uint32* const USB_CFG							= (volatile uint32* const) (BASE::USB_1 + 0x00C);
			volatile uint32* const RST_CTL							= (volatile uint32* const) (BASE::USB_1 + 0x010);
			volatile uint32* const INT_STS							= (volatile uint32* const) (BASE::USB_1 + 0x014);
			volatile uint32* const INT_MSK							= (volatile uint32* const) (BASE::USB_1 + 0x018);
			volatile uint32* const RX_STSR							= (volatile uint32* const) (BASE::USB_1 + 0x01C);
			volatile uint32* const RX_STSP							= (volatile uint32* const) (BASE::USB_1 + 0x020);
			volatile uint32* const RX_FSIZ							= (volatile uint32* const) (BASE::USB_1 + 0x024);
			volatile uint32* const HNPTFSIZ_DIEPTXF0		= (volatile uint32* const) (BASE::USB_1 + 0x028);
			volatile uint32* const HNPTXSTS							= (volatile uint32* const) (BASE::USB_1 + 0x02C);
			volatile uint32* const GCCFG								= (volatile uint32* const) (BASE::USB_1 + 0x038);
			volatile uint32* const CID									= (volatile uint32* const) (BASE::USB_1 + 0x03C);
			volatile uint32* const LPM_CFG							= (volatile uint32* const) (BASE::USB_1 + 0x054);
			volatile uint32* const HPTX_FSIZ						= (volatile uint32* const) (BASE::USB_1 + 0x100);
			volatile uint32* const DIEP_TXF1						= (volatile uint32* const) (BASE::USB_1 + 0x104);
			volatile uint32* const DIEP_TXF2						= (volatile uint32* const) (BASE::USB_1 + 0x108);
			volatile uint32* const DIEP_TXF3						= (volatile uint32* const) (BASE::USB_1 + 0x10C);
			volatile uint32* const DIEP_TXF4						= (volatile uint32* const) (BASE::USB_1 + 0x110);
			volatile uint32* const DIEP_TXF5						= (volatile uint32* const) (BASE::USB_1 + 0x114);
			volatile uint32* const DIEP_TXF6						= (volatile uint32* const) (BASE::USB_1 + 0x118);
			volatile uint32* const DIEP_TXF7						= (volatile uint32* const) (BASE::USB_1 + 0x11C);
			volatile uint32* const DIEP_TXF8						= (volatile uint32* const) (BASE::USB_1 + 0x120);
		};
		
		namespace HOST
		{
			volatile uint32* const CFG									= (volatile uint32* const) (BASE::USB_1 + 0x400);
			volatile uint32* const FIR									= (volatile uint32* const) (BASE::USB_1 + 0x404);
			volatile uint32* const FNUM									= (volatile uint32* const) (BASE::USB_1 + 0x408);
			volatile uint32* const PTX_STS							= (volatile uint32* const) (BASE::USB_1 + 0x410);
			volatile uint32* const AINT									= (volatile uint32* const) (BASE::USB_1 + 0x414);
			volatile uint32* const AINT_MSK							= (volatile uint32* const) (BASE::USB_1 + 0x418);
			volatile uint32* const PRT									= (volatile uint32* const) (BASE::USB_1 + 0x440);
			
			
			volatile uint32* const CHAR0								= (volatile uint32* const) (BASE::USB_1 + 0x500);
			volatile uint32* const SPLT0								= (volatile uint32* const) (BASE::USB_1 + 0x504);
			volatile uint32* const INT0									= (volatile uint32* const) (BASE::USB_1 + 0x508);
			volatile uint32* const INTMSK0							= (volatile uint32* const) (BASE::USB_1 + 0x50C);
			volatile uint32* const TSIZ0								= (volatile uint32* const) (BASE::USB_1 + 0x510);
			volatile uint32* const DMA0									= (volatile uint32* const) (BASE::USB_1 + 0x514);
			
			volatile uint32* const CHAR1								= (volatile uint32* const) (BASE::USB_1 + 0x520);
			volatile uint32* const SPLT1								= (volatile uint32* const) (BASE::USB_1 + 0x524);
			volatile uint32* const INT1									= (volatile uint32* const) (BASE::USB_1 + 0x528);
			volatile uint32* const INTMSK1							= (volatile uint32* const) (BASE::USB_1 + 0x52C);
			volatile uint32* const TSIZ1								= (volatile uint32* const) (BASE::USB_1 + 0x530);
			volatile uint32* const DMA1									= (volatile uint32* const) (BASE::USB_1 + 0x534);
			
			volatile uint32* const CHAR2								= (volatile uint32* const) (BASE::USB_1 + 0x540);
			volatile uint32* const SPLT2								= (volatile uint32* const) (BASE::USB_1 + 0x544);
			volatile uint32* const INT2									= (volatile uint32* const) (BASE::USB_1 + 0x548);
			volatile uint32* const INTMSK2							= (volatile uint32* const) (BASE::USB_1 + 0x54C);
			volatile uint32* const TSIZ2								= (volatile uint32* const) (BASE::USB_1 + 0x550);
			volatile uint32* const DMA2									= (volatile uint32* const) (BASE::USB_1 + 0x554);
			
			volatile uint32* const CHAR3								= (volatile uint32* const) (BASE::USB_1 + 0x560);
			volatile uint32* const SPLT3								= (volatile uint32* const) (BASE::USB_1 + 0x564);
			volatile uint32* const INT3									= (volatile uint32* const) (BASE::USB_1 + 0x568);
			volatile uint32* const INTMSK3							= (volatile uint32* const) (BASE::USB_1 + 0x56C);
			volatile uint32* const TSIZ3								= (volatile uint32* const) (BASE::USB_1 + 0x570);
			volatile uint32* const DMA3									= (volatile uint32* const) (BASE::USB_1 + 0x574);
			
			volatile uint32* const CHAR4								= (volatile uint32* const) (BASE::USB_1 + 0x580);
			volatile uint32* const SPLT4								= (volatile uint32* const) (BASE::USB_1 + 0x584);
			volatile uint32* const INT4									= (volatile uint32* const) (BASE::USB_1 + 0x588);
			volatile uint32* const INTMSK4							= (volatile uint32* const) (BASE::USB_1 + 0x58C);
			volatile uint32* const TSIZ4								= (volatile uint32* const) (BASE::USB_1 + 0x590);
			volatile uint32* const DMA4									= (volatile uint32* const) (BASE::USB_1 + 0x594);
			
			volatile uint32* const CHAR5								= (volatile uint32* const) (BASE::USB_1 + 0x5A0);
			volatile uint32* const SPLT5								= (volatile uint32* const) (BASE::USB_1 + 0x5A4);
			volatile uint32* const INT5									= (volatile uint32* const) (BASE::USB_1 + 0x5A8);
			volatile uint32* const INTMSK5							= (volatile uint32* const) (BASE::USB_1 + 0x5AC);
			volatile uint32* const TSIZ5								= (volatile uint32* const) (BASE::USB_1 + 0x5B0);
			volatile uint32* const DMA5									= (volatile uint32* const) (BASE::USB_1 + 0x5B4);
			
			volatile uint32* const CHAR6								= (volatile uint32* const) (BASE::USB_1 + 0x5C0);
			volatile uint32* const SPLT6								= (volatile uint32* const) (BASE::USB_1 + 0x5C4);
			volatile uint32* const INT6									= (volatile uint32* const) (BASE::USB_1 + 0x5C8);
			volatile uint32* const INTMSK6							= (volatile uint32* const) (BASE::USB_1 + 0x5CC);
			volatile uint32* const TSIZ6								= (volatile uint32* const) (BASE::USB_1 + 0x5D0);
			volatile uint32* const DMA6									= (volatile uint32* const) (BASE::USB_1 + 0x5D4);
			
			volatile uint32* const CHAR7								= (volatile uint32* const) (BASE::USB_1 + 0x5E0);
			volatile uint32* const SPLT7								= (volatile uint32* const) (BASE::USB_1 + 0x5E4);
			volatile uint32* const INT7									= (volatile uint32* const) (BASE::USB_1 + 0x5E8);
			volatile uint32* const INTMSK7							= (volatile uint32* const) (BASE::USB_1 + 0x5EC);
			volatile uint32* const TSIZ7 								= (volatile uint32* const) (BASE::USB_1 + 0x5F0);
			volatile uint32* const DMA7									= (volatile uint32* const) (BASE::USB_1 + 0x5F4);
			
			volatile uint32* const CHAR8								= (volatile uint32* const) (BASE::USB_1 + 0x600);
			volatile uint32* const SPLT8								= (volatile uint32* const) (BASE::USB_1 + 0x604);
			volatile uint32* const INT8									= (volatile uint32* const) (BASE::USB_1 + 0x608);
			volatile uint32* const INTMSK8							= (volatile uint32* const) (BASE::USB_1 + 0x60C);
			volatile uint32* const TSIZ8								= (volatile uint32* const) (BASE::USB_1 + 0x610);
			volatile uint32* const DMA8									= (volatile uint32* const) (BASE::USB_1 + 0x614);
			
			volatile uint32* const CHAR9								= (volatile uint32* const) (BASE::USB_1 + 0x620);
			volatile uint32* const SPLT9								= (volatile uint32* const) (BASE::USB_1 + 0x624);
			volatile uint32* const INT9									= (volatile uint32* const) (BASE::USB_1 + 0x628);
			volatile uint32* const INTMSK9							= (volatile uint32* const) (BASE::USB_1 + 0x62C);
			volatile uint32* const TSIZ9								= (volatile uint32* const) (BASE::USB_1 + 0x630);
			volatile uint32* const DMA9									= (volatile uint32* const) (BASE::USB_1 + 0x634);
			
			volatile uint32* const CHAR10								= (volatile uint32* const) (BASE::USB_1 + 0x640);
			volatile uint32* const SPLT10								= (volatile uint32* const) (BASE::USB_1 + 0x644);
			volatile uint32* const INT10								= (volatile uint32* const) (BASE::USB_1 + 0x648);
			volatile uint32* const INTMSK10							= (volatile uint32* const) (BASE::USB_1 + 0x64C);
			volatile uint32* const TSIZ10								= (volatile uint32* const) (BASE::USB_1 + 0x650);
			volatile uint32* const DMA10								= (volatile uint32* const) (BASE::USB_1 + 0x654);
			
			volatile uint32* const CHAR11								= (volatile uint32* const) (BASE::USB_1 + 0x660);
			volatile uint32* const SPLT11								= (volatile uint32* const) (BASE::USB_1 + 0x664);
			volatile uint32* const INT11								= (volatile uint32* const) (BASE::USB_1 + 0x668);
			volatile uint32* const INTMSK11							= (volatile uint32* const) (BASE::USB_1 + 0x66C);
			volatile uint32* const TSIZ11								= (volatile uint32* const) (BASE::USB_1 + 0x670);
			volatile uint32* const DMA11								= (volatile uint32* const) (BASE::USB_1 + 0x674);
			
			volatile uint32* const CHAR12								= (volatile uint32* const) (BASE::USB_1 + 0x680);
			volatile uint32* const SPLT12								= (volatile uint32* const) (BASE::USB_1 + 0x684);
			volatile uint32* const INT12								= (volatile uint32* const) (BASE::USB_1 + 0x688);
			volatile uint32* const INTMSK12							= (volatile uint32* const) (BASE::USB_1 + 0x68C);
			volatile uint32* const TSIZ12								= (volatile uint32* const) (BASE::USB_1 + 0x690);
			volatile uint32* const DMA12								= (volatile uint32* const) (BASE::USB_1 + 0x694);
			
			volatile uint32* const CHAR13								= (volatile uint32* const) (BASE::USB_1 + 0x6A0);
			volatile uint32* const SPLT13								= (volatile uint32* const) (BASE::USB_1 + 0x6A4);
			volatile uint32* const INT13								= (volatile uint32* const) (BASE::USB_1 + 0x6A8);
			volatile uint32* const INTMSK13							= (volatile uint32* const) (BASE::USB_1 + 0x6AC);
			volatile uint32* const TSIZ13								= (volatile uint32* const) (BASE::USB_1 + 0x6B0);
			volatile uint32* const DMA13								= (volatile uint32* const) (BASE::USB_1 + 0x6B4);
			
			volatile uint32* const CHAR14								= (volatile uint32* const) (BASE::USB_1 + 0x6C0);
			volatile uint32* const SPLT14								= (volatile uint32* const) (BASE::USB_1 + 0x6C4);
			volatile uint32* const INT14								= (volatile uint32* const) (BASE::USB_1 + 0x6C8);
			volatile uint32* const INTMSK14							= (volatile uint32* const) (BASE::USB_1 + 0x6CC);
			volatile uint32* const TSIZ14								= (volatile uint32* const) (BASE::USB_1 + 0x6D0);
			volatile uint32* const DMA14								= (volatile uint32* const) (BASE::USB_1 + 0x6D4);
			
			volatile uint32* const CHAR15								= (volatile uint32* const) (BASE::USB_1 + 0x6E0);
			volatile uint32* const SPLT15								= (volatile uint32* const) (BASE::USB_1 + 0x6E4);
			volatile uint32* const INT15								= (volatile uint32* const) (BASE::USB_1 + 0x6E8);
			volatile uint32* const INTMSK15							= (volatile uint32* const) (BASE::USB_1 + 0x6EC);
			volatile uint32* const TSIZ15								= (volatile uint32* const) (BASE::USB_1 + 0x6F0);
			volatile uint32* const DMA15								= (volatile uint32* const) (BASE::USB_1 + 0x6F4);
		};
		
		namespace DEVICE
		{
			volatile uint32* const CFG									= (volatile uint32* const) (BASE::USB_1 + 0x800);
			volatile uint32* const CTL									= (volatile uint32* const) (BASE::USB_1 + 0x804);
			volatile uint32* const STS									= (volatile uint32* const) (BASE::USB_1 + 0x808);
			volatile uint32* const IEPMSK								= (volatile uint32* const) (BASE::USB_1 + 0x810);
			volatile uint32* const OEPMSK								= (volatile uint32* const) (BASE::USB_1 + 0x814);
			volatile uint32* const AINT									= (volatile uint32* const) (BASE::USB_1 + 0x818);
			volatile uint32* const AINTMSK							= (volatile uint32* const) (BASE::USB_1 + 0x81C);
			volatile uint32* const VBUS_DIS							= (volatile uint32* const) (BASE::USB_1 + 0x828);
			volatile uint32* const VBUS_PULSE						= (volatile uint32* const) (BASE::USB_1 + 0x82C);
			volatile uint32* const THR_CTL							= (volatile uint32* const) (BASE::USB_1 + 0x830);
			volatile uint32* const IEP_EMPMSK						= (volatile uint32* const) (BASE::USB_1 + 0x834);
			volatile uint32* const EACH_INT							= (volatile uint32* const) (BASE::USB_1 + 0x838);
			volatile uint32* const EACH_INTMSK					= (volatile uint32* const) (BASE::USB_1 + 0x83C);
			volatile uint32* const IEP_EACH_MSK1				= (volatile uint32* const) (BASE::USB_1 + 0x844);
			volatile uint32* const OEP_EACH_MSK1				= (volatile uint32* const) (BASE::USB_1 + 0x884);
			
			
			volatile uint32* const IEP_CTL0							= (volatile uint32* const) (BASE::USB_1 + 0x900);
			volatile uint32* const IEP_INT0							= (volatile uint32* const) (BASE::USB_1 + 0x908);
			volatile uint32* const IEP_TSIZ0						= (volatile uint32* const) (BASE::USB_1 + 0x910);
			volatile uint32* const IEP_DMA0							= (volatile uint32* const) (BASE::USB_1 + 0x914);
			volatile uint32* const TX_FSTS0							= (volatile uint32* const) (BASE::USB_1 + 0x918);
			
			volatile uint32* const IEP_CTL1							= (volatile uint32* const) (BASE::USB_1 + 0x920);
			volatile uint32* const IEP_INT1							= (volatile uint32* const) (BASE::USB_1 + 0x928);
			volatile uint32* const IEP_TSIZ1						= (volatile uint32* const) (BASE::USB_1 + 0x930);
			volatile uint32* const IEP_DMA1							= (volatile uint32* const) (BASE::USB_1 + 0x934);
			volatile uint32* const TX_FSTS1							= (volatile uint32* const) (BASE::USB_1 + 0x938);
			
			volatile uint32* const IEP_CTL2							= (volatile uint32* const) (BASE::USB_1 + 0x940);
			volatile uint32* const IEP_INT2							= (volatile uint32* const) (BASE::USB_1 + 0x948);
			volatile uint32* const IEP_TSIZ2						= (volatile uint32* const) (BASE::USB_1 + 0x950);
			volatile uint32* const IEP_DMA2							= (volatile uint32* const) (BASE::USB_1 + 0x954);
			volatile uint32* const TX_FSTS2							= (volatile uint32* const) (BASE::USB_1 + 0x958);
			
			volatile uint32* const IEP_CTL3							= (volatile uint32* const) (BASE::USB_1 + 0x960);
			volatile uint32* const IEP_INT3							= (volatile uint32* const) (BASE::USB_1 + 0x968);
			volatile uint32* const IEP_TSIZ3						= (volatile uint32* const) (BASE::USB_1 + 0x970);
			volatile uint32* const IEP_DMA3							= (volatile uint32* const) (BASE::USB_1 + 0x974);
			volatile uint32* const TX_FSTS3							= (volatile uint32* const) (BASE::USB_1 + 0x978);
			
			volatile uint32* const IEP_CTL4							= (volatile uint32* const) (BASE::USB_1 + 0x980);
			volatile uint32* const IEP_INT4							= (volatile uint32* const) (BASE::USB_1 + 0x988);
			volatile uint32* const IEP_TSIZ4						= (volatile uint32* const) (BASE::USB_1 + 0x990);
			volatile uint32* const IEP_DMA4							= (volatile uint32* const) (BASE::USB_1 + 0x994);
			volatile uint32* const TX_FSTS4							= (volatile uint32* const) (BASE::USB_1 + 0x998);
			
			volatile uint32* const IEP_CTL5							= (volatile uint32* const) (BASE::USB_1 + 0x9A0);
			volatile uint32* const IEP_INT5							= (volatile uint32* const) (BASE::USB_1 + 0x9A8);
			volatile uint32* const IEP_TSIZ5						= (volatile uint32* const) (BASE::USB_1 + 0x9B0);
			volatile uint32* const IEP_DMA5							= (volatile uint32* const) (BASE::USB_1 + 0x9B4);
			volatile uint32* const TX_FSTS5							= (volatile uint32* const) (BASE::USB_1 + 0x9B8);
			
			volatile uint32* const IEP_CTL6							= (volatile uint32* const) (BASE::USB_1 + 0x9C0);
			volatile uint32* const IEP_INT6							= (volatile uint32* const) (BASE::USB_1 + 0x9C8);
			volatile uint32* const IEP_TSIZ6						= (volatile uint32* const) (BASE::USB_1 + 0x9D0);
			volatile uint32* const IEP_DMA6							= (volatile uint32* const) (BASE::USB_1 + 0x9D4);
			volatile uint32* const TX_FSTS6							= (volatile uint32* const) (BASE::USB_1 + 0x9D8);
			
			volatile uint32* const IEP_CTL7							= (volatile uint32* const) (BASE::USB_1 + 0x9E0);
			volatile uint32* const IEP_INT7							= (volatile uint32* const) (BASE::USB_1 + 0x9E8);
			volatile uint32* const IEP_TSIZ7						= (volatile uint32* const) (BASE::USB_1 + 0x9F0);
			volatile uint32* const IEP_DMA7							= (volatile uint32* const) (BASE::USB_1 + 0x9F4);
			volatile uint32* const TX_FSTS7							= (volatile uint32* const) (BASE::USB_1 + 0x9F8);
			
			volatile uint32* const IEP_CTL8							= (volatile uint32* const) (BASE::USB_1 + 0xA00);
			volatile uint32* const IEP_INT8							= (volatile uint32* const) (BASE::USB_1 + 0xA08);
			volatile uint32* const IEP_TSIZ8						= (volatile uint32* const) (BASE::USB_1 + 0xA10);
			volatile uint32* const IEP_DMA8							= (volatile uint32* const) (BASE::USB_1 + 0xA14);
			volatile uint32* const TX_FSTS8							= (volatile uint32* const) (BASE::USB_1 + 0xA18);
			
			
			volatile uint32* const OEP_CTL0							= (volatile uint32* const) (BASE::USB_1 + 0xB00);
			volatile uint32* const OEP_INT0							= (volatile uint32* const) (BASE::USB_1 + 0xB08);
			volatile uint32* const OEP_TSIZ0						= (volatile uint32* const) (BASE::USB_1 + 0xB10);
			volatile uint32* const OEP_DMA0							= (volatile uint32* const) (BASE::USB_1 + 0xB14);
			
			volatile uint32* const OEP_CTL1							= (volatile uint32* const) (BASE::USB_1 + 0xB20);
			volatile uint32* const OEP_INT1							= (volatile uint32* const) (BASE::USB_1 + 0xB28);
			volatile uint32* const OEP_TSIZ1						= (volatile uint32* const) (BASE::USB_1 + 0xB30);
			volatile uint32* const OEP_DMA1							= (volatile uint32* const) (BASE::USB_1 + 0xB34);
			
			volatile uint32* const OEP_CTL2							= (volatile uint32* const) (BASE::USB_1 + 0xB40);
			volatile uint32* const OEP_INT2							= (volatile uint32* const) (BASE::USB_1 + 0xB48);
			volatile uint32* const OEP_TSIZ2						= (volatile uint32* const) (BASE::USB_1 + 0xB50);
			volatile uint32* const OEP_DMA2							= (volatile uint32* const) (BASE::USB_1 + 0xB54);
			
			volatile uint32* const OEP_CTL3							= (volatile uint32* const) (BASE::USB_1 + 0xB60);
			volatile uint32* const OEP_INT3							= (volatile uint32* const) (BASE::USB_1 + 0xB68);
			volatile uint32* const OEP_TSIZ3						= (volatile uint32* const) (BASE::USB_1 + 0xB70);
			volatile uint32* const OEP_DMA3							= (volatile uint32* const) (BASE::USB_1 + 0xB74);
			
			volatile uint32* const OEP_CTL4							= (volatile uint32* const) (BASE::USB_1 + 0xB80);
			volatile uint32* const OEP_INT4							= (volatile uint32* const) (BASE::USB_1 + 0xB88);
			volatile uint32* const OEP_TSIZ4						= (volatile uint32* const) (BASE::USB_1 + 0xB90);
			volatile uint32* const OEP_DMA4							= (volatile uint32* const) (BASE::USB_1 + 0xB94);
			
			volatile uint32* const OEP_CTL5							= (volatile uint32* const) (BASE::USB_1 + 0xBA0);
			volatile uint32* const OEP_INT5							= (volatile uint32* const) (BASE::USB_1 + 0xBA8);
			volatile uint32* const OEP_TSIZ5						= (volatile uint32* const) (BASE::USB_1 + 0xBB0);
			volatile uint32* const OEP_DMA5							= (volatile uint32* const) (BASE::USB_1 + 0xBB4);
			
			volatile uint32* const OEP_CTL6							= (volatile uint32* const) (BASE::USB_1 + 0xBC0);
			volatile uint32* const OEP_INT6							= (volatile uint32* const) (BASE::USB_1 + 0xBC8);
			volatile uint32* const OEP_TSIZ6						= (volatile uint32* const) (BASE::USB_1 + 0xBD0);
			volatile uint32* const OEP_DMA6							= (volatile uint32* const) (BASE::USB_1 + 0xBD4);
			
			volatile uint32* const OEP_CTL7							= (volatile uint32* const) (BASE::USB_1 + 0xBE0);
			volatile uint32* const OEP_INT7							= (volatile uint32* const) (BASE::USB_1 + 0xBE8);
			volatile uint32* const OEP_TSIZ7						= (volatile uint32* const) (BASE::USB_1 + 0xBF0);
			volatile uint32* const OEP_DMA7							= (volatile uint32* const) (BASE::USB_1 + 0xBF4);
			
			volatile uint32* const OEP_CTL8							= (volatile uint32* const) (BASE::USB_1 + 0xC00);
			volatile uint32* const OEP_INT8							= (volatile uint32* const) (BASE::USB_1 + 0xC08);
			volatile uint32* const OEP_TSIZ8						= (volatile uint32* const) (BASE::USB_1 + 0xC10);
			volatile uint32* const OEP_DMA8							= (volatile uint32* const) (BASE::USB_1 + 0xC14);
		};
		
		namespace GLOBAL
		{
			volatile uint32* const PCGC_CTL							= (volatile uint32* const) (BASE::USB_1 + 0xE00);
		};
	};
	
	namespace SDMMC_2_DELAY
	{
		volatile uint32* const DELAY_CR							= (volatile uint32* const) (BASE::SDMMC_2_DELAY + 0x00);
		volatile uint32* const DELAY_CFGR						= (volatile uint32* const) (BASE::SDMMC_2_DELAY + 0x04);
	};
	
	namespace GPV
	{
		volatile uint32* const PERIPH_ID_4					= (volatile uint32* const) (BASE::GPV + 0x01FD0);
		volatile uint32* const PERIPH_ID_5					= (volatile uint32* const) (BASE::GPV + 0x01FD4);
		volatile uint32* const PERIPH_ID_6					= (volatile uint32* const) (BASE::GPV + 0x01FD8);
		volatile uint32* const PERIPH_ID_7					= (volatile uint32* const) (BASE::GPV + 0x01FDC);
		volatile uint32* const PERIPH_ID_0					= (volatile uint32* const) (BASE::GPV + 0x01FE0);
		volatile uint32* const PERIPH_ID_1					= (volatile uint32* const) (BASE::GPV + 0x01FE4);
		volatile uint32* const PERIPH_ID_2					= (volatile uint32* const) (BASE::GPV + 0x01FE8);
		volatile uint32* const PERIPH_ID_3					= (volatile uint32* const) (BASE::GPV + 0x01FEC);
		volatile uint32* const COMP_ID0							= (volatile uint32* const) (BASE::GPV + 0x01FF0);
		volatile uint32* const COMP_ID1							= (volatile uint32* const) (BASE::GPV + 0x01FF4);
		volatile uint32* const COMP_ID2							= (volatile uint32* const) (BASE::GPV + 0x01FF8);
		volatile uint32* const COMP_ID3							= (volatile uint32* const) (BASE::GPV + 0x01FFC);
		volatile uint32* const TARG1_FN_MOD_ISS_BM	= (volatile uint32* const) (BASE::GPV + 0x02008);
		volatile uint32* const TARG1_FN_MOD2				= (volatile uint32* const) (BASE::GPV + 0x02024);
		volatile uint32* const TARG1_FN_MOD_LB			= (volatile uint32* const) (BASE::GPV + 0x0202C);
		volatile uint32* const TARG1_FN_MOD					= (volatile uint32* const) (BASE::GPV + 0x02108);
		volatile uint32* const TARG2_FN_MOD_ISS_BM	= (volatile uint32* const) (BASE::GPV + 0x03008);
		volatile uint32* const TARG2_FN_MOD2				= (volatile uint32* const) (BASE::GPV + 0x03024);
		volatile uint32* const TARG2_FN_MOD_LB			= (volatile uint32* const) (BASE::GPV + 0x0302C);
		volatile uint32* const TARG2_FN_MOD					= (volatile uint32* const) (BASE::GPV + 0x03108);
		volatile uint32* const TARG3_FN_MOD_ISS_BM	= (volatile uint32* const) (BASE::GPV + 0x04008);
		volatile uint32* const TARG4_FN_MOD_ISS_BM	= (volatile uint32* const) (BASE::GPV + 0x05008);
		volatile uint32* const TARG5_FN_MOD_ISS_BM	= (volatile uint32* const) (BASE::GPV + 0x06008);
		volatile uint32* const TARG6_FN_MOD_ISS_BM	= (volatile uint32* const) (BASE::GPV + 0x07008);
		volatile uint32* const TARG7_FN_MOD_ISS_BM	= (volatile uint32* const) (BASE::GPV + 0x08008);
		volatile uint32* const TARG7_FN_MOD2				= (volatile uint32* const) (BASE::GPV + 0x08024);
		volatile uint32* const TARG7_FN_MOD					= (volatile uint32* const) (BASE::GPV + 0x08108);
		volatile uint32* const INI1_FN_MOD2					= (volatile uint32* const) (BASE::GPV + 0x42024);
		volatile uint32* const INI1_FN_MOD_AHB			= (volatile uint32* const) (BASE::GPV + 0x42028);
		volatile uint32* const INI1_READ_QOS				= (volatile uint32* const) (BASE::GPV + 0x42100);
		volatile uint32* const INI1_WRITE_QOS				= (volatile uint32* const) (BASE::GPV + 0x42104);
		volatile uint32* const INI1_FN_MOD					= (volatile uint32* const) (BASE::GPV + 0x42108);
		volatile uint32* const INI2_READ_QOS				= (volatile uint32* const) (BASE::GPV + 0x43100);
		volatile uint32* const INI2_WRITE_QOS				= (volatile uint32* const) (BASE::GPV + 0x43104);
		volatile uint32* const INI2_FN_MOD					= (volatile uint32* const) (BASE::GPV + 0x43108);
		volatile uint32* const INI3_FN_MOD2					= (volatile uint32* const) (BASE::GPV + 0x44024);
		volatile uint32* const INI3_FN_MOD_AHB			= (volatile uint32* const) (BASE::GPV + 0x44028);
		volatile uint32* const INI3_READ_QOS				= (volatile uint32* const) (BASE::GPV + 0x44100);
		volatile uint32* const INI3_WRITE_QOS				= (volatile uint32* const) (BASE::GPV + 0x44104);
		volatile uint32* const INI3_FN_MOD					= (volatile uint32* const) (BASE::GPV + 0x44108);
		volatile uint32* const INI4_READ_QOS				= (volatile uint32* const) (BASE::GPV + 0x45100);
		volatile uint32* const INI4_WRITE_QOS				= (volatile uint32* const) (BASE::GPV + 0x45104);
		volatile uint32* const INI4_FN_MOD					= (volatile uint32* const) (BASE::GPV + 0x45108);
		volatile uint32* const INI5_READ_QOS				= (volatile uint32* const) (BASE::GPV + 0x46100);
		volatile uint32* const INI5_WRITE_QOS				= (volatile uint32* const) (BASE::GPV + 0x46104);
		volatile uint32* const INI5_FN_MOD					= (volatile uint32* const) (BASE::GPV + 0x46108);
		volatile uint32* const INI6_READ_QOS				= (volatile uint32* const) (BASE::GPV + 0x47100);
		volatile uint32* const INI6_WRITE_QOS				= (volatile uint32* const) (BASE::GPV + 0x47104);
		volatile uint32* const INI6_FN_MOD					= (volatile uint32* const) (BASE::GPV + 0x47108);
	};
	
	namespace MDMA
	{
		
		volatile uint32* const GISR0								= (volatile uint32* const) (BASE::MDMA + 0x000);
		
		
		volatile uint32* const CH0_ISR							= (volatile uint32* const) (BASE::MDMA + 0x040);
		volatile uint32* const CH0_IFCR							= (volatile uint32* const) (BASE::MDMA + 0x044);
		volatile uint32* const CH0_ESR							= (volatile uint32* const) (BASE::MDMA + 0x048);
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::MDMA + 0x04C);
		volatile uint32* const CH0_TCR							= (volatile uint32* const) (BASE::MDMA + 0x050);
		volatile uint32* const CH0_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x054);
		volatile uint32* const CH0_SAR							= (volatile uint32* const) (BASE::MDMA + 0x058);
		volatile uint32* const CH0_DAR							= (volatile uint32* const) (BASE::MDMA + 0x05C);
		volatile uint32* const CH0_BRUR							= (volatile uint32* const) (BASE::MDMA + 0x060);
		volatile uint32* const CH0_LAR							= (volatile uint32* const) (BASE::MDMA + 0x064);
		volatile uint32* const CH0_TBR							= (volatile uint32* const) (BASE::MDMA + 0x068);
		volatile uint32* const CH0_MAR							= (volatile uint32* const) (BASE::MDMA + 0x070);
		volatile uint32* const CH0_MDR							= (volatile uint32* const) (BASE::MDMA + 0x074);
		
		volatile uint32* const CH1_ISR							= (volatile uint32* const) (BASE::MDMA + 0x080);
		volatile uint32* const CH1_IFCR							= (volatile uint32* const) (BASE::MDMA + 0x084);
		volatile uint32* const CH1_ESR							= (volatile uint32* const) (BASE::MDMA + 0x088);
		volatile uint32* const CH1_CR								= (volatile uint32* const) (BASE::MDMA + 0x08C);
		volatile uint32* const CH1_TCR							= (volatile uint32* const) (BASE::MDMA + 0x090);
		volatile uint32* const CH1_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x094);
		volatile uint32* const CH1_SAR							= (volatile uint32* const) (BASE::MDMA + 0x098);
		volatile uint32* const CH1_DAR							= (volatile uint32* const) (BASE::MDMA + 0x09C);
		volatile uint32* const CH1_BRUR							= (volatile uint32* const) (BASE::MDMA + 0x0A0);
		volatile uint32* const CH1_LAR							= (volatile uint32* const) (BASE::MDMA + 0x0A4);
		volatile uint32* const CH1_TBR							= (volatile uint32* const) (BASE::MDMA + 0x0A8);
		volatile uint32* const CH1_MAR							= (volatile uint32* const) (BASE::MDMA + 0x0B0);
		volatile uint32* const CH1_MDR							= (volatile uint32* const) (BASE::MDMA + 0x0B4);
		
		volatile uint32* const CH2_ISR							= (volatile uint32* const) (BASE::MDMA + 0x0C0);
		volatile uint32* const CH2_IFCR							= (volatile uint32* const) (BASE::MDMA + 0x0C4);
		volatile uint32* const CH2_ESR							= (volatile uint32* const) (BASE::MDMA + 0x0C8);
		volatile uint32* const CH2_CR								= (volatile uint32* const) (BASE::MDMA + 0x0CC);
		volatile uint32* const CH2_TCR							= (volatile uint32* const) (BASE::MDMA + 0x0D0);
		volatile uint32* const CH2_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x0D4);
		volatile uint32* const CH2_SAR							= (volatile uint32* const) (BASE::MDMA + 0x0D8);
		volatile uint32* const CH2_DAR							= (volatile uint32* const) (BASE::MDMA + 0x0DC);
		volatile uint32* const CH2_BRUR							= (volatile uint32* const) (BASE::MDMA + 0x0E0);
		volatile uint32* const CH2_LAR							= (volatile uint32* const) (BASE::MDMA + 0x0E4);
		volatile uint32* const CH2_TBR							= (volatile uint32* const) (BASE::MDMA + 0x0E8);
		volatile uint32* const CH2_MAR							= (volatile uint32* const) (BASE::MDMA + 0x0F0);
		volatile uint32* const CH2_MDR							= (volatile uint32* const) (BASE::MDMA + 0x0F4);
		
		volatile uint32* const CH3_ISR							= (volatile uint32* const) (BASE::MDMA + 0x100);
		volatile uint32* const CH3_IFCR							= (volatile uint32* const) (BASE::MDMA + 0x104);
		volatile uint32* const CH3_ESR							= (volatile uint32* const) (BASE::MDMA + 0x108);
		volatile uint32* const CH3_CR								= (volatile uint32* const) (BASE::MDMA + 0x10C);
		volatile uint32* const CH3_TCR							= (volatile uint32* const) (BASE::MDMA + 0x110);
		volatile uint32* const CH3_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x114);
		volatile uint32* const CH3_SAR							= (volatile uint32* const) (BASE::MDMA + 0x118);
		volatile uint32* const CH3_DAR							= (volatile uint32* const) (BASE::MDMA + 0x11C);
		volatile uint32* const CH3_BRUR							= (volatile uint32* const) (BASE::MDMA + 0x120);
		volatile uint32* const CH3_LAR							= (volatile uint32* const) (BASE::MDMA + 0x124);
		volatile uint32* const CH3_TBR							= (volatile uint32* const) (BASE::MDMA + 0x128);
		volatile uint32* const CH3_MAR							= (volatile uint32* const) (BASE::MDMA + 0x130);
		volatile uint32* const CH3_MDR							= (volatile uint32* const) (BASE::MDMA + 0x134);
		
		volatile uint32* const CH4_ISR							= (volatile uint32* const) (BASE::MDMA + 0x140);
		volatile uint32* const CH4_IFCR							= (volatile uint32* const) (BASE::MDMA + 0x144);
		volatile uint32* const CH4_ESR							= (volatile uint32* const) (BASE::MDMA + 0x148);
		volatile uint32* const CH4_CR								= (volatile uint32* const) (BASE::MDMA + 0x14C);
		volatile uint32* const CH4_TCR							= (volatile uint32* const) (BASE::MDMA + 0x150);
		volatile uint32* const CH4_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x154);
		volatile uint32* const CH4_SAR							= (volatile uint32* const) (BASE::MDMA + 0x158);
		volatile uint32* const CH4_DAR							= (volatile uint32* const) (BASE::MDMA + 0x15C);
		volatile uint32* const CH4_BRUR							= (volatile uint32* const) (BASE::MDMA + 0x160);
		volatile uint32* const CH4_LAR							= (volatile uint32* const) (BASE::MDMA + 0x164);
		volatile uint32* const CH4_TBR							= (volatile uint32* const) (BASE::MDMA + 0x168);
		volatile uint32* const CH4_MAR							= (volatile uint32* const) (BASE::MDMA + 0x170);
		volatile uint32* const CH4_MDR							= (volatile uint32* const) (BASE::MDMA + 0x174);
		
		volatile uint32* const CH5_ISR							= (volatile uint32* const) (BASE::MDMA + 0x180);
		volatile uint32* const CH5_IFCR							= (volatile uint32* const) (BASE::MDMA + 0x184);
		volatile uint32* const CH5_ESR							= (volatile uint32* const) (BASE::MDMA + 0x188);
		volatile uint32* const CH5_CR								= (volatile uint32* const) (BASE::MDMA + 0x18C);
		volatile uint32* const CH5_TCR							= (volatile uint32* const) (BASE::MDMA + 0x190);
		volatile uint32* const CH5_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x194);
		volatile uint32* const CH5_SAR							= (volatile uint32* const) (BASE::MDMA + 0x198);
		volatile uint32* const CH5_DAR							= (volatile uint32* const) (BASE::MDMA + 0x19C);
		volatile uint32* const CH5_BRUR							= (volatile uint32* const) (BASE::MDMA + 0x1A0);
		volatile uint32* const CH5_LAR							= (volatile uint32* const) (BASE::MDMA + 0x1A4);
		volatile uint32* const CH5_TBR							= (volatile uint32* const) (BASE::MDMA + 0x1A8);
		volatile uint32* const CH5_MAR							= (volatile uint32* const) (BASE::MDMA + 0x1B0);
		volatile uint32* const CH5_MDR							= (volatile uint32* const) (BASE::MDMA + 0x1B4);
		
		volatile uint32* const CH6_ISR							= (volatile uint32* const) (BASE::MDMA + 0x1C0);
		volatile uint32* const CH6_IFCR							= (volatile uint32* const) (BASE::MDMA + 0x1C4);
		volatile uint32* const CH6_ESR							= (volatile uint32* const) (BASE::MDMA + 0x1C8);
		volatile uint32* const CH6_CR								= (volatile uint32* const) (BASE::MDMA + 0x1CC);
		volatile uint32* const CH6_TCR							= (volatile uint32* const) (BASE::MDMA + 0x1D0);
		volatile uint32* const CH6_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x1D4);
		volatile uint32* const CH6_SAR							= (volatile uint32* const) (BASE::MDMA + 0x1D8);
		volatile uint32* const CH6_DAR							= (volatile uint32* const) (BASE::MDMA + 0x1DC);
		volatile uint32* const CH6_BRUR							= (volatile uint32* const) (BASE::MDMA + 0x1E0);
		volatile uint32* const CH6_LAR							= (volatile uint32* const) (BASE::MDMA + 0x1E4);
		volatile uint32* const CH6_TBR							= (volatile uint32* const) (BASE::MDMA + 0x1E8);
		volatile uint32* const CH6_MAR							= (volatile uint32* const) (BASE::MDMA + 0x1F0);
		volatile uint32* const CH6_MDR							= (volatile uint32* const) (BASE::MDMA + 0x1F4);
		
		volatile uint32* const CH7_ISR							= (volatile uint32* const) (BASE::MDMA + 0x200);
		volatile uint32* const CH7_IFCR							= (volatile uint32* const) (BASE::MDMA + 0x204);
		volatile uint32* const CH7_ESR							= (volatile uint32* const) (BASE::MDMA + 0x208);
		volatile uint32* const CH7_CR								= (volatile uint32* const) (BASE::MDMA + 0x20C);
		volatile uint32* const CH7_TCR							= (volatile uint32* const) (BASE::MDMA + 0x210);
		volatile uint32* const CH7_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x214);
		volatile uint32* const CH7_SAR							= (volatile uint32* const) (BASE::MDMA + 0x218);
		volatile uint32* const CH7_DAR							= (volatile uint32* const) (BASE::MDMA + 0x21C);
		volatile uint32* const CH7_BRUR							= (volatile uint32* const) (BASE::MDMA + 0x220);
		volatile uint32* const CH7_LAR							= (volatile uint32* const) (BASE::MDMA + 0x224);
		volatile uint32* const CH7_TBR							= (volatile uint32* const) (BASE::MDMA + 0x228);
		volatile uint32* const CH7_MAR							= (volatile uint32* const) (BASE::MDMA + 0x230);
		volatile uint32* const CH7_MDR							= (volatile uint32* const) (BASE::MDMA + 0x234);
		
		volatile uint32* const CH8_ISR							= (volatile uint32* const) (BASE::MDMA + 0x240);
		volatile uint32* const CH8_IFCR							= (volatile uint32* const) (BASE::MDMA + 0x244);
		volatile uint32* const CH8_ESR							= (volatile uint32* const) (BASE::MDMA + 0x248);
		volatile uint32* const CH8_CR								= (volatile uint32* const) (BASE::MDMA + 0x24C);
		volatile uint32* const CH8_TCR							= (volatile uint32* const) (BASE::MDMA + 0x250);
		volatile uint32* const CH8_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x254);
		volatile uint32* const CH8_SAR							= (volatile uint32* const) (BASE::MDMA + 0x258);
		volatile uint32* const CH8_DAR							= (volatile uint32* const) (BASE::MDMA + 0x25C);
		volatile uint32* const CH8_BRUR							= (volatile uint32* const) (BASE::MDMA + 0x260);
		volatile uint32* const CH8_LAR							= (volatile uint32* const) (BASE::MDMA + 0x264);
		volatile uint32* const CH8_TBR							= (volatile uint32* const) (BASE::MDMA + 0x268);
		volatile uint32* const CH8_MAR							= (volatile uint32* const) (BASE::MDMA + 0x270);
		volatile uint32* const CH8_MDR							= (volatile uint32* const) (BASE::MDMA + 0x274);
		
		volatile uint32* const CH9_ISR							= (volatile uint32* const) (BASE::MDMA + 0x280);
		volatile uint32* const CH9_IFCR							= (volatile uint32* const) (BASE::MDMA + 0x284);
		volatile uint32* const CH9_ESR							= (volatile uint32* const) (BASE::MDMA + 0x288);
		volatile uint32* const CH9_CR								= (volatile uint32* const) (BASE::MDMA + 0x28C);
		volatile uint32* const CH9_TCR							= (volatile uint32* const) (BASE::MDMA + 0x290);
		volatile uint32* const CH9_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x294);
		volatile uint32* const CH9_SAR							= (volatile uint32* const) (BASE::MDMA + 0x298);
		volatile uint32* const CH9_DAR							= (volatile uint32* const) (BASE::MDMA + 0x29C);
		volatile uint32* const CH9_BRUR							= (volatile uint32* const) (BASE::MDMA + 0x2A0);
		volatile uint32* const CH9_LAR							= (volatile uint32* const) (BASE::MDMA + 0x2A4);
		volatile uint32* const CH9_TBR							= (volatile uint32* const) (BASE::MDMA + 0x2A8);
		volatile uint32* const CH9_MAR							= (volatile uint32* const) (BASE::MDMA + 0x2B0);
		volatile uint32* const CH9_MDR							= (volatile uint32* const) (BASE::MDMA + 0x2B4);
		
		volatile uint32* const CH10_ISR							= (volatile uint32* const) (BASE::MDMA + 0x2C0);
		volatile uint32* const CH10_IFCR						= (volatile uint32* const) (BASE::MDMA + 0x2C4);
		volatile uint32* const CH10_ESR							= (volatile uint32* const) (BASE::MDMA + 0x2C8);
		volatile uint32* const CH10_CR							= (volatile uint32* const) (BASE::MDMA + 0x2CC);
		volatile uint32* const CH10_TCR							= (volatile uint32* const) (BASE::MDMA + 0x2D0);
		volatile uint32* const CH10_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x2D4);
		volatile uint32* const CH10_SAR							= (volatile uint32* const) (BASE::MDMA + 0x2D8);
		volatile uint32* const CH10_DAR							= (volatile uint32* const) (BASE::MDMA + 0x2DC);
		volatile uint32* const CH10_BRUR						= (volatile uint32* const) (BASE::MDMA + 0x2E0);
		volatile uint32* const CH10_LAR							= (volatile uint32* const) (BASE::MDMA + 0x2E4);
		volatile uint32* const CH10_TBR							= (volatile uint32* const) (BASE::MDMA + 0x2E8);
		volatile uint32* const CH10_MAR							= (volatile uint32* const) (BASE::MDMA + 0x2F0);
		volatile uint32* const CH10_MDR							= (volatile uint32* const) (BASE::MDMA + 0x2F4);
		
		volatile uint32* const CH11_ISR							= (volatile uint32* const) (BASE::MDMA + 0x300);
		volatile uint32* const CH11_IFCR						= (volatile uint32* const) (BASE::MDMA + 0x304);
		volatile uint32* const CH11_ESR							= (volatile uint32* const) (BASE::MDMA + 0x308);
		volatile uint32* const CH11_CR							= (volatile uint32* const) (BASE::MDMA + 0x30C);
		volatile uint32* const CH11_TCR							= (volatile uint32* const) (BASE::MDMA + 0x310);
		volatile uint32* const CH11_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x314);
		volatile uint32* const CH11_SAR							= (volatile uint32* const) (BASE::MDMA + 0x318);
		volatile uint32* const CH11_DAR							= (volatile uint32* const) (BASE::MDMA + 0x31C);
		volatile uint32* const CH11_BRUR						= (volatile uint32* const) (BASE::MDMA + 0x320);
		volatile uint32* const CH11_LAR							= (volatile uint32* const) (BASE::MDMA + 0x324);
		volatile uint32* const CH11_TBR							= (volatile uint32* const) (BASE::MDMA + 0x328);
		volatile uint32* const CH11_MAR							= (volatile uint32* const) (BASE::MDMA + 0x330);
		volatile uint32* const CH11_MDR							= (volatile uint32* const) (BASE::MDMA + 0x334);
		
		volatile uint32* const CH12_ISR							= (volatile uint32* const) (BASE::MDMA + 0x340);
		volatile uint32* const CH12_IFCR						= (volatile uint32* const) (BASE::MDMA + 0x344);
		volatile uint32* const CH12_ESR							= (volatile uint32* const) (BASE::MDMA + 0x348);
		volatile uint32* const CH12_CR							= (volatile uint32* const) (BASE::MDMA + 0x34C);
		volatile uint32* const CH12_TCR							= (volatile uint32* const) (BASE::MDMA + 0x350);
		volatile uint32* const CH12_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x354);
		volatile uint32* const CH12_SAR							= (volatile uint32* const) (BASE::MDMA + 0x358);
		volatile uint32* const CH12_DAR							= (volatile uint32* const) (BASE::MDMA + 0x35C);
		volatile uint32* const CH12_BRUR						= (volatile uint32* const) (BASE::MDMA + 0x360);
		volatile uint32* const CH12_LAR							= (volatile uint32* const) (BASE::MDMA + 0x364);
		volatile uint32* const CH12_TBR							= (volatile uint32* const) (BASE::MDMA + 0x368);
		volatile uint32* const CH12_MAR							= (volatile uint32* const) (BASE::MDMA + 0x370);
		volatile uint32* const CH12_MDR							= (volatile uint32* const) (BASE::MDMA + 0x374);
		
		volatile uint32* const CH13_ISR							= (volatile uint32* const) (BASE::MDMA + 0x380);
		volatile uint32* const CH13_IFCR						= (volatile uint32* const) (BASE::MDMA + 0x384);
		volatile uint32* const CH13_ESR							= (volatile uint32* const) (BASE::MDMA + 0x388);
		volatile uint32* const CH13_CR							= (volatile uint32* const) (BASE::MDMA + 0x38C);
		volatile uint32* const CH13_TCR							= (volatile uint32* const) (BASE::MDMA + 0x390);
		volatile uint32* const CH13_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x394);
		volatile uint32* const CH13_SAR							= (volatile uint32* const) (BASE::MDMA + 0x398);
		volatile uint32* const CH13_DAR							= (volatile uint32* const) (BASE::MDMA + 0x39C);
		volatile uint32* const CH13_BRUR						= (volatile uint32* const) (BASE::MDMA + 0x3A0);
		volatile uint32* const CH13_LAR							= (volatile uint32* const) (BASE::MDMA + 0x3A4);
		volatile uint32* const CH13_TBR							= (volatile uint32* const) (BASE::MDMA + 0x3A8);
		volatile uint32* const CH13_MAR							= (volatile uint32* const) (BASE::MDMA + 0x3B0);
		volatile uint32* const CH13_MDR							= (volatile uint32* const) (BASE::MDMA + 0x3B4);
		
		volatile uint32* const CH14_ISR							= (volatile uint32* const) (BASE::MDMA + 0x3C0);
		volatile uint32* const CH14_IFCR						= (volatile uint32* const) (BASE::MDMA + 0x3C4);
		volatile uint32* const CH14_ESR							= (volatile uint32* const) (BASE::MDMA + 0x3C8);
		volatile uint32* const CH14_CR							= (volatile uint32* const) (BASE::MDMA + 0x3CC);
		volatile uint32* const CH14_TCR							= (volatile uint32* const) (BASE::MDMA + 0x3D0);
		volatile uint32* const CH14_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x3D4);
		volatile uint32* const CH14_SAR							= (volatile uint32* const) (BASE::MDMA + 0x3D8);
		volatile uint32* const CH14_DAR							= (volatile uint32* const) (BASE::MDMA + 0x3DC);
		volatile uint32* const CH14_BRUR						= (volatile uint32* const) (BASE::MDMA + 0x3E0);
		volatile uint32* const CH14_LAR							= (volatile uint32* const) (BASE::MDMA + 0x3E4);
		volatile uint32* const CH14_TBR							= (volatile uint32* const) (BASE::MDMA + 0x3E8);
		volatile uint32* const CH14_MAR							= (volatile uint32* const) (BASE::MDMA + 0x3F0);
		volatile uint32* const CH14_MDR							= (volatile uint32* const) (BASE::MDMA + 0x3F4);
		
		volatile uint32* const CH15_ISR							= (volatile uint32* const) (BASE::MDMA + 0x400);
		volatile uint32* const CH15_IFCR						= (volatile uint32* const) (BASE::MDMA + 0x404);
		volatile uint32* const CH15_ESR							= (volatile uint32* const) (BASE::MDMA + 0x408);
		volatile uint32* const CH15_CR							= (volatile uint32* const) (BASE::MDMA + 0x40C);
		volatile uint32* const CH15_TCR							= (volatile uint32* const) (BASE::MDMA + 0x410);
		volatile uint32* const CH15_BNDTR						= (volatile uint32* const) (BASE::MDMA + 0x414);
		volatile uint32* const CH15_SAR							= (volatile uint32* const) (BASE::MDMA + 0x418);
		volatile uint32* const CH15_DAR							= (volatile uint32* const) (BASE::MDMA + 0x41C);
		volatile uint32* const CH15_BRUR						= (volatile uint32* const) (BASE::MDMA + 0x420);
		volatile uint32* const CH15_LAR							= (volatile uint32* const) (BASE::MDMA + 0x424);
		volatile uint32* const CH15_TBR							= (volatile uint32* const) (BASE::MDMA + 0x428);
		volatile uint32* const CH15_MAR							= (volatile uint32* const) (BASE::MDMA + 0x430);
		volatile uint32* const CH15_MDR							= (volatile uint32* const) (BASE::MDMA + 0x434);
	};
	
	namespace DMA2D
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::DMA2D + 0x000);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::DMA2D + 0x004);
		volatile uint32* const IFCR									= (volatile uint32* const) (BASE::DMA2D + 0x008);
		volatile uint32* const FG_MAR								= (volatile uint32* const) (BASE::DMA2D + 0x00C);
		volatile uint32* const FG_OR								= (volatile uint32* const) (BASE::DMA2D + 0x010);
		volatile uint32* const BG_MAR								= (volatile uint32* const) (BASE::DMA2D + 0x014);
		volatile uint32* const BG_OR								= (volatile uint32* const) (BASE::DMA2D + 0x018);
		volatile uint32* const FG_PFC_CR						= (volatile uint32* const) (BASE::DMA2D + 0x01C);
		volatile uint32* const FG_COLR							= (volatile uint32* const) (BASE::DMA2D + 0x020);
		volatile uint32* const BG_PFC_CR						= (volatile uint32* const) (BASE::DMA2D + 0x024);
		volatile uint32* const BG_COLR							= (volatile uint32* const) (BASE::DMA2D + 0x028);
		volatile uint32* const FG_CMAR							= (volatile uint32* const) (BASE::DMA2D + 0x02C);
		volatile uint32* const BG_CMAR							= (volatile uint32* const) (BASE::DMA2D + 0x030);
		volatile uint32* const O_PFC_CR							= (volatile uint32* const) (BASE::DMA2D + 0x034);
		volatile uint32* const O_COLR								= (volatile uint32* const) (BASE::DMA2D + 0x038);
		volatile uint32* const O_MAR								= (volatile uint32* const) (BASE::DMA2D + 0x03C);
		volatile uint32* const O_OR									= (volatile uint32* const) (BASE::DMA2D + 0x040);
		volatile uint32* const NLR									= (volatile uint32* const) (BASE::DMA2D + 0x044);
		volatile uint32* const LWR									= (volatile uint32* const) (BASE::DMA2D + 0x048);
		volatile uint32* const AMTCR								= (volatile uint32* const) (BASE::DMA2D + 0x04C);
		volatile uint32* const FG_CLUT							= (volatile uint32* const) (BASE::DMA2D + 0x400);
		volatile uint32* const BG_CLUT							= (volatile uint32* const) (BASE::DMA2D + 0x800);
	};
	
	namespace FLASH_1
	{
		volatile uint32* const ACR									= (volatile uint32* const) (BASE::FLASH + 0x000);
		volatile uint32* const KEY									= (volatile uint32* const) (BASE::FLASH + 0x004);
		volatile uint32* const OPTKEY								= (volatile uint32* const) (BASE::FLASH + 0x008);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::FLASH + 0x00C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::FLASH + 0x010);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::FLASH + 0x014);
		volatile uint32* const OPT_CR								= (volatile uint32* const) (BASE::FLASH + 0x018);
		volatile uint32* const OPT_SR_CUR						= (volatile uint32* const) (BASE::FLASH + 0x01C);
		volatile uint32* const OPT_SR_PRG						= (volatile uint32* const) (BASE::FLASH + 0x020);
		volatile uint32* const OPT_CCR							= (volatile uint32* const) (BASE::FLASH + 0x024);
		volatile uint32* const PRAR_CUR							= (volatile uint32* const) (BASE::FLASH + 0x028);
		volatile uint32* const PRAR_PRG							= (volatile uint32* const) (BASE::FLASH + 0x02C);
		volatile uint32* const SCAR_CUR							= (volatile uint32* const) (BASE::FLASH + 0x030);
		volatile uint32* const SCAR_PRG							= (volatile uint32* const) (BASE::FLASH + 0x034);
		volatile uint32* const WPSN_CURR						= (volatile uint32* const) (BASE::FLASH + 0x038);
		volatile uint32* const WPSN_PRGR						= (volatile uint32* const) (BASE::FLASH + 0x03C);
		volatile uint32* const BOOT_CURR						= (volatile uint32* const) (BASE::FLASH + 0x040);
		volatile uint32* const BOOT_PRGR						= (volatile uint32* const) (BASE::FLASH + 0x044);
		volatile uint32* const CRC_CR								= (volatile uint32* const) (BASE::FLASH + 0x050);
		volatile uint32* const CRC_SADDR						= (volatile uint32* const) (BASE::FLASH + 0x054);
		volatile uint32* const CRC_EADDR						= (volatile uint32* const) (BASE::FLASH + 0x058);
		volatile uint32* const CRC_DATA							= (volatile uint32* const) (BASE::FLASH + 0x05C);
		volatile uint32* const ECC_FAR							= (volatile uint32* const) (BASE::FLASH + 0x060);
	};
	
	namespace FLASH_2
	{
		volatile uint32* const ACR									= (volatile uint32* const) (BASE::FLASH + 0x100);
		volatile uint32* const KEY									= (volatile uint32* const) (BASE::FLASH + 0x104);
		volatile uint32* const OPTKEY								= (volatile uint32* const) (BASE::FLASH + 0x108);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::FLASH + 0x10C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::FLASH + 0x110);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::FLASH + 0x114);
		volatile uint32* const OPT_CR								= (volatile uint32* const) (BASE::FLASH + 0x118);
		volatile uint32* const OPT_SR_CUR						= (volatile uint32* const) (BASE::FLASH + 0x11C);
		volatile uint32* const OPT_SR_PRG						= (volatile uint32* const) (BASE::FLASH + 0x120);
		volatile uint32* const OPT_CCR							= (volatile uint32* const) (BASE::FLASH + 0x124);
		volatile uint32* const PRAR_CUR							= (volatile uint32* const) (BASE::FLASH + 0x128);
		volatile uint32* const PRAR_PRG							= (volatile uint32* const) (BASE::FLASH + 0x12C);
		volatile uint32* const SCAR_CUR							= (volatile uint32* const) (BASE::FLASH + 0x130);
		volatile uint32* const SCAR_PRG							= (volatile uint32* const) (BASE::FLASH + 0x134);
		volatile uint32* const WPSN_CURR						= (volatile uint32* const) (BASE::FLASH + 0x138);
		volatile uint32* const WPSN_PRGR						= (volatile uint32* const) (BASE::FLASH + 0x13C);
		volatile uint32* const BOOT_CURR						= (volatile uint32* const) (BASE::FLASH + 0x140);
		volatile uint32* const BOOT_PRG							= (volatile uint32* const) (BASE::FLASH + 0x144);
		volatile uint32* const CRC_CR								= (volatile uint32* const) (BASE::FLASH + 0x150);
		volatile uint32* const CRC_SADDR						= (volatile uint32* const) (BASE::FLASH + 0x154);
		volatile uint32* const CRC_EADDR						= (volatile uint32* const) (BASE::FLASH + 0x158);
		volatile uint32* const CRC_DATAR						= (volatile uint32* const) (BASE::FLASH + 0x15C);
		volatile uint32* const ECC_FAR							= (volatile uint32* const) (BASE::FLASH + 0x160);
	};
	
	namespace JPEG
	{
		volatile uint32* const CONFR0								= (volatile uint32* const) (BASE::JPEG + 0x000);
		volatile uint32* const CONFR1								= (volatile uint32* const) (BASE::JPEG + 0x004);
		volatile uint32* const CONFR2								= (volatile uint32* const) (BASE::JPEG + 0x008);
		volatile uint32* const CONFR3								= (volatile uint32* const) (BASE::JPEG + 0x00C);
		volatile uint32* const CONFR4								= (volatile uint32* const) (BASE::JPEG + 0x010);
		volatile uint32* const CONFR5								= (volatile uint32* const) (BASE::JPEG + 0x014);
		volatile uint32* const CONFR6								= (volatile uint32* const) (BASE::JPEG + 0x018);
		volatile uint32* const CONFR7								= (volatile uint32* const) (BASE::JPEG + 0x01C);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::JPEG + 0x030);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::JPEG + 0x034);
		volatile uint32* const CFR									= (volatile uint32* const) (BASE::JPEG + 0x038);
		volatile uint32* const DIR									= (volatile uint32* const) (BASE::JPEG + 0x040);
		volatile uint32* const DOR									= (volatile uint32* const) (BASE::JPEG + 0x044);
		
		
		volatile uint32* const QMEM0_0							= (volatile uint32* const) (BASE::JPEG + 0x050);
		volatile uint32* const QMEM0_1							= (volatile uint32* const) (BASE::JPEG + 0x054);
		volatile uint32* const QMEM0_2							= (volatile uint32* const) (BASE::JPEG + 0x058);
		volatile uint32* const QMEM0_3							= (volatile uint32* const) (BASE::JPEG + 0x05C);
		volatile uint32* const QMEM0_4							= (volatile uint32* const) (BASE::JPEG + 0x060);
		volatile uint32* const QMEM0_5							= (volatile uint32* const) (BASE::JPEG + 0x064);
		volatile uint32* const QMEM0_6							= (volatile uint32* const) (BASE::JPEG + 0x068);
		volatile uint32* const QMEM0_7							= (volatile uint32* const) (BASE::JPEG + 0x06C);
		volatile uint32* const QMEM0_8							= (volatile uint32* const) (BASE::JPEG + 0x070);
		volatile uint32* const QMEM0_9							= (volatile uint32* const) (BASE::JPEG + 0x074);
		volatile uint32* const QMEM0_10							= (volatile uint32* const) (BASE::JPEG + 0x078);
		volatile uint32* const QMEM0_11							= (volatile uint32* const) (BASE::JPEG + 0x07C);
		volatile uint32* const QMEM0_12							= (volatile uint32* const) (BASE::JPEG + 0x080);
		volatile uint32* const QMEM0_13							= (volatile uint32* const) (BASE::JPEG + 0x084);
		volatile uint32* const QMEM0_14							= (volatile uint32* const) (BASE::JPEG + 0x088);
		volatile uint32* const QMEM0_15							= (volatile uint32* const) (BASE::JPEG + 0x08C);
		
		volatile uint32* const QMEM1_0							= (volatile uint32* const) (BASE::JPEG + 0x090);
		volatile uint32* const QMEM1_1							= (volatile uint32* const) (BASE::JPEG + 0x094);
		volatile uint32* const QMEM1_2							= (volatile uint32* const) (BASE::JPEG + 0x098);
		volatile uint32* const QMEM1_3							= (volatile uint32* const) (BASE::JPEG + 0x09C);
		volatile uint32* const QMEM1_4							= (volatile uint32* const) (BASE::JPEG + 0x0A0);
		volatile uint32* const QMEM1_5							= (volatile uint32* const) (BASE::JPEG + 0x0A4);
		volatile uint32* const QMEM1_6							= (volatile uint32* const) (BASE::JPEG + 0x0A8);
		volatile uint32* const QMEM1_7							= (volatile uint32* const) (BASE::JPEG + 0x0AC);
		volatile uint32* const QMEM1_8							= (volatile uint32* const) (BASE::JPEG + 0x0B0);
		volatile uint32* const QMEM1_9							= (volatile uint32* const) (BASE::JPEG + 0x0B4);
		volatile uint32* const QMEM1_10							= (volatile uint32* const) (BASE::JPEG + 0x0B8);
		volatile uint32* const QMEM1_11							= (volatile uint32* const) (BASE::JPEG + 0x0BC);
		volatile uint32* const QMEM1_12							= (volatile uint32* const) (BASE::JPEG + 0x0C0);
		volatile uint32* const QMEM1_13							= (volatile uint32* const) (BASE::JPEG + 0x0C4);
		volatile uint32* const QMEM1_14							= (volatile uint32* const) (BASE::JPEG + 0x0C8);
		volatile uint32* const QMEM1_15							= (volatile uint32* const) (BASE::JPEG + 0x0CC);
		
		volatile uint32* const QMEM2_0							= (volatile uint32* const) (BASE::JPEG + 0x0D0);
		volatile uint32* const QMEM2_1							= (volatile uint32* const) (BASE::JPEG + 0x0D4);
		volatile uint32* const QMEM2_2							= (volatile uint32* const) (BASE::JPEG + 0x0D8);
		volatile uint32* const QMEM2_3							= (volatile uint32* const) (BASE::JPEG + 0x0DC);
		volatile uint32* const QMEM2_4							= (volatile uint32* const) (BASE::JPEG + 0x0E0);
		volatile uint32* const QMEM2_5							= (volatile uint32* const) (BASE::JPEG + 0x0E4);
		volatile uint32* const QMEM2_6							= (volatile uint32* const) (BASE::JPEG + 0x0E8);
		volatile uint32* const QMEM2_7							= (volatile uint32* const) (BASE::JPEG + 0x0EC);
		volatile uint32* const QMEM2_8							= (volatile uint32* const) (BASE::JPEG + 0x0F0);
		volatile uint32* const QMEM2_9							= (volatile uint32* const) (BASE::JPEG + 0x0F4);
		volatile uint32* const QMEM2_10							= (volatile uint32* const) (BASE::JPEG + 0x0F8);
		volatile uint32* const QMEM2_11							= (volatile uint32* const) (BASE::JPEG + 0x0FC);
		volatile uint32* const QMEM2_12							= (volatile uint32* const) (BASE::JPEG + 0x100);
		volatile uint32* const QMEM2_13							= (volatile uint32* const) (BASE::JPEG + 0x104);
		volatile uint32* const QMEM2_14							= (volatile uint32* const) (BASE::JPEG + 0x108);
		volatile uint32* const QMEM2_15							= (volatile uint32* const) (BASE::JPEG + 0x10C);
		
		volatile uint32* const QMEM3_0							= (volatile uint32* const) (BASE::JPEG + 0x110);
		volatile uint32* const QMEM3_1							= (volatile uint32* const) (BASE::JPEG + 0x114);
		volatile uint32* const QMEM3_2							= (volatile uint32* const) (BASE::JPEG + 0x118);
		volatile uint32* const QMEM3_3							= (volatile uint32* const) (BASE::JPEG + 0x11C);
		volatile uint32* const QMEM3_4							= (volatile uint32* const) (BASE::JPEG + 0x120);
		volatile uint32* const QMEM3_5							= (volatile uint32* const) (BASE::JPEG + 0x124);
		volatile uint32* const QMEM3_6							= (volatile uint32* const) (BASE::JPEG + 0x128);
		volatile uint32* const QMEM3_7							= (volatile uint32* const) (BASE::JPEG + 0x12C);
		volatile uint32* const QMEM3_8							= (volatile uint32* const) (BASE::JPEG + 0x130);
		volatile uint32* const QMEM3_9							= (volatile uint32* const) (BASE::JPEG + 0x134);
		volatile uint32* const QMEM3_10							= (volatile uint32* const) (BASE::JPEG + 0x138);
		volatile uint32* const QMEM3_11							= (volatile uint32* const) (BASE::JPEG + 0x13C);
		volatile uint32* const QMEM3_12							= (volatile uint32* const) (BASE::JPEG + 0x140);
		volatile uint32* const QMEM3_13							= (volatile uint32* const) (BASE::JPEG + 0x144);
		volatile uint32* const QMEM3_14							= (volatile uint32* const) (BASE::JPEG + 0x148);
		volatile uint32* const QMEM3_15							= (volatile uint32* const) (BASE::JPEG + 0x14C);
		
		
		volatile uint32* const HUFF_MIN0						= (volatile uint32* const) (BASE::JPEG + 0x150);
		volatile uint32* const HUFF_MIN1						= (volatile uint32* const) (BASE::JPEG + 0x154);
		volatile uint32* const HUFF_MIN2						= (volatile uint32* const) (BASE::JPEG + 0x158);
		volatile uint32* const HUFF_MIN3						= (volatile uint32* const) (BASE::JPEG + 0x15C);
		volatile uint32* const HUFF_MIN4						= (volatile uint32* const) (BASE::JPEG + 0x160);
		volatile uint32* const HUFF_MIN5						= (volatile uint32* const) (BASE::JPEG + 0x164);
		volatile uint32* const HUFF_MIN6						= (volatile uint32* const) (BASE::JPEG + 0x168);
		volatile uint32* const HUFF_MIN7						= (volatile uint32* const) (BASE::JPEG + 0x16C);
		volatile uint32* const HUFF_MIN8						= (volatile uint32* const) (BASE::JPEG + 0x170);
		volatile uint32* const HUFF_MIN9						= (volatile uint32* const) (BASE::JPEG + 0x174);
		volatile uint32* const HUFF_MIN10						= (volatile uint32* const) (BASE::JPEG + 0x178);
		volatile uint32* const HUFF_MIN11						= (volatile uint32* const) (BASE::JPEG + 0x17C);
		volatile uint32* const HUFF_MIN12						= (volatile uint32* const) (BASE::JPEG + 0x180);
		volatile uint32* const HUFF_MIN13						= (volatile uint32* const) (BASE::JPEG + 0x184);
		volatile uint32* const HUFF_MIN14						= (volatile uint32* const) (BASE::JPEG + 0x188);
		volatile uint32* const HUFF_MIN15						= (volatile uint32* const) (BASE::JPEG + 0x18C);
		
		
		volatile uint32* const HUFF_BASE0						= (volatile uint32* const) (BASE::JPEG + 0x190);
		volatile uint32* const HUFF_BASE1						= (volatile uint32* const) (BASE::JPEG + 0x194);
		volatile uint32* const HUFF_BASE2						= (volatile uint32* const) (BASE::JPEG + 0x198);
		volatile uint32* const HUFF_BASE3						= (volatile uint32* const) (BASE::JPEG + 0x19C);
		volatile uint32* const HUFF_BASE4						= (volatile uint32* const) (BASE::JPEG + 0x1A0);
		volatile uint32* const HUFF_BASE5						= (volatile uint32* const) (BASE::JPEG + 0x1A4);
		volatile uint32* const HUFF_BASE6						= (volatile uint32* const) (BASE::JPEG + 0x1A8);
		volatile uint32* const HUFF_BASE7						= (volatile uint32* const) (BASE::JPEG + 0x1AC);
		volatile uint32* const HUFF_BASE8						= (volatile uint32* const) (BASE::JPEG + 0x1B0);
		volatile uint32* const HUFF_BASE9						= (volatile uint32* const) (BASE::JPEG + 0x1B4);
		volatile uint32* const HUFF_BASE10					= (volatile uint32* const) (BASE::JPEG + 0x1B8);
		volatile uint32* const HUFF_BASE11					= (volatile uint32* const) (BASE::JPEG + 0x1BC);
		volatile uint32* const HUFF_BASE12					= (volatile uint32* const) (BASE::JPEG + 0x1C0);
		volatile uint32* const HUFF_BASE13					= (volatile uint32* const) (BASE::JPEG + 0x1C4);
		volatile uint32* const HUFF_BASE14					= (volatile uint32* const) (BASE::JPEG + 0x1C8);
		volatile uint32* const HUFF_BASE15					= (volatile uint32* const) (BASE::JPEG + 0x1CC);
		volatile uint32* const HUFF_BASE16					= (volatile uint32* const) (BASE::JPEG + 0x1D0);
		volatile uint32* const HUFF_BASE17					= (volatile uint32* const) (BASE::JPEG + 0x1D4);
		volatile uint32* const HUFF_BASE18					= (volatile uint32* const) (BASE::JPEG + 0x1D8);
		volatile uint32* const HUFF_BASE19					= (volatile uint32* const) (BASE::JPEG + 0x1DC);
		volatile uint32* const HUFF_BASE20					= (volatile uint32* const) (BASE::JPEG + 0x1E0);
		volatile uint32* const HUFF_BASE21					= (volatile uint32* const) (BASE::JPEG + 0x1E4);
		volatile uint32* const HUFF_BASE22					= (volatile uint32* const) (BASE::JPEG + 0x1E8);
		volatile uint32* const HUFF_BASE23					= (volatile uint32* const) (BASE::JPEG + 0x1EC);
		volatile uint32* const HUFF_BASE24					= (volatile uint32* const) (BASE::JPEG + 0x1F0);
		volatile uint32* const HUFF_BASE25					= (volatile uint32* const) (BASE::JPEG + 0x1F4);
		volatile uint32* const HUFF_BASE26					= (volatile uint32* const) (BASE::JPEG + 0x1F8);
		volatile uint32* const HUFF_BASE27					= (volatile uint32* const) (BASE::JPEG + 0x1FC);
		volatile uint32* const HUFF_BASE28					= (volatile uint32* const) (BASE::JPEG + 0x200);
		volatile uint32* const HUFF_BASE29					= (volatile uint32* const) (BASE::JPEG + 0x204);
		volatile uint32* const HUFF_BASE30					= (volatile uint32* const) (BASE::JPEG + 0x208);
		volatile uint32* const HUFF_BASE31					= (volatile uint32* const) (BASE::JPEG + 0x20C);
		
		
		volatile uint32* const HUFF_SYMB0						= (volatile uint32* const) (BASE::JPEG + 0x210);
		volatile uint32* const HUFF_SYMB1						= (volatile uint32* const) (BASE::JPEG + 0x210);
		volatile uint32* const HUFF_SYMB2						= (volatile uint32* const) (BASE::JPEG + 0x210);
		volatile uint32* const HUFF_SYMB3						= (volatile uint32* const) (BASE::JPEG + 0x210);
		volatile uint32* const HUFF_SYMB4						= (volatile uint32* const) (BASE::JPEG + 0x220);
		volatile uint32* const HUFF_SYMB5						= (volatile uint32* const) (BASE::JPEG + 0x220);
		volatile uint32* const HUFF_SYMB6						= (volatile uint32* const) (BASE::JPEG + 0x220);
		volatile uint32* const HUFF_SYMB7						= (volatile uint32* const) (BASE::JPEG + 0x220);
		volatile uint32* const HUFF_SYMB8						= (volatile uint32* const) (BASE::JPEG + 0x230);
		volatile uint32* const HUFF_SYMB9						= (volatile uint32* const) (BASE::JPEG + 0x230);
		volatile uint32* const HUFF_SYMB10					= (volatile uint32* const) (BASE::JPEG + 0x230);
		volatile uint32* const HUFF_SYMB11					= (volatile uint32* const) (BASE::JPEG + 0x230);
		volatile uint32* const HUFF_SYMB12					= (volatile uint32* const) (BASE::JPEG + 0x240);
		volatile uint32* const HUFF_SYMB13					= (volatile uint32* const) (BASE::JPEG + 0x240);
		volatile uint32* const HUFF_SYMB14					= (volatile uint32* const) (BASE::JPEG + 0x240);
		volatile uint32* const HUFF_SYMB15					= (volatile uint32* const) (BASE::JPEG + 0x240);
		volatile uint32* const HUFF_SYMB16					= (volatile uint32* const) (BASE::JPEG + 0x250);
		volatile uint32* const HUFF_SYMB17					= (volatile uint32* const) (BASE::JPEG + 0x250);
		volatile uint32* const HUFF_SYMB18					= (volatile uint32* const) (BASE::JPEG + 0x250);
		volatile uint32* const HUFF_SYMB19					= (volatile uint32* const) (BASE::JPEG + 0x250);
		volatile uint32* const HUFF_SYMB20					= (volatile uint32* const) (BASE::JPEG + 0x260);
		volatile uint32* const HUFF_SYMB21					= (volatile uint32* const) (BASE::JPEG + 0x260);
		volatile uint32* const HUFF_SYMB22					= (volatile uint32* const) (BASE::JPEG + 0x260);
		volatile uint32* const HUFF_SYMB23					= (volatile uint32* const) (BASE::JPEG + 0x260);
		volatile uint32* const HUFF_SYMB24					= (volatile uint32* const) (BASE::JPEG + 0x270);
		volatile uint32* const HUFF_SYMB25					= (volatile uint32* const) (BASE::JPEG + 0x270);
		volatile uint32* const HUFF_SYMB26					= (volatile uint32* const) (BASE::JPEG + 0x270);
		volatile uint32* const HUFF_SYMB27					= (volatile uint32* const) (BASE::JPEG + 0x270);
		volatile uint32* const HUFF_SYMB28					= (volatile uint32* const) (BASE::JPEG + 0x280);
		volatile uint32* const HUFF_SYMB29					= (volatile uint32* const) (BASE::JPEG + 0x280);
		volatile uint32* const HUFF_SYMB30					= (volatile uint32* const) (BASE::JPEG + 0x280);
		volatile uint32* const HUFF_SYMB31					= (volatile uint32* const) (BASE::JPEG + 0x280);
		volatile uint32* const HUFF_SYMB32					= (volatile uint32* const) (BASE::JPEG + 0x290);
		volatile uint32* const HUFF_SYMB33					= (volatile uint32* const) (BASE::JPEG + 0x290);
		volatile uint32* const HUFF_SYMB34					= (volatile uint32* const) (BASE::JPEG + 0x290);
		volatile uint32* const HUFF_SYMB35					= (volatile uint32* const) (BASE::JPEG + 0x290);
		volatile uint32* const HUFF_SYMB36					= (volatile uint32* const) (BASE::JPEG + 0x2A0);
		volatile uint32* const HUFF_SYMB37					= (volatile uint32* const) (BASE::JPEG + 0x2A0);
		volatile uint32* const HUFF_SYMB38					= (volatile uint32* const) (BASE::JPEG + 0x2A0);
		volatile uint32* const HUFF_SYMB39					= (volatile uint32* const) (BASE::JPEG + 0x2A0);
		volatile uint32* const HUFF_SYMB40					= (volatile uint32* const) (BASE::JPEG + 0x2B0);
		volatile uint32* const HUFF_SYMB41					= (volatile uint32* const) (BASE::JPEG + 0x2B0);
		volatile uint32* const HUFF_SYMB42					= (volatile uint32* const) (BASE::JPEG + 0x2B0);
		volatile uint32* const HUFF_SYMB43					= (volatile uint32* const) (BASE::JPEG + 0x2B0);
		volatile uint32* const HUFF_SYMB44					= (volatile uint32* const) (BASE::JPEG + 0x2C0);
		volatile uint32* const HUFF_SYMB45					= (volatile uint32* const) (BASE::JPEG + 0x2C0);
		volatile uint32* const HUFF_SYMB46					= (volatile uint32* const) (BASE::JPEG + 0x2C0);
		volatile uint32* const HUFF_SYMB47					= (volatile uint32* const) (BASE::JPEG + 0x2C0);
		volatile uint32* const HUFF_SYMB48					= (volatile uint32* const) (BASE::JPEG + 0x2D0);
		volatile uint32* const HUFF_SYMB49					= (volatile uint32* const) (BASE::JPEG + 0x2D0);
		volatile uint32* const HUFF_SYMB50					= (volatile uint32* const) (BASE::JPEG + 0x2D0);
		volatile uint32* const HUFF_SYMB51					= (volatile uint32* const) (BASE::JPEG + 0x2D0);
		volatile uint32* const HUFF_SYMB52					= (volatile uint32* const) (BASE::JPEG + 0x2E0);
		volatile uint32* const HUFF_SYMB53					= (volatile uint32* const) (BASE::JPEG + 0x2E0);
		volatile uint32* const HUFF_SYMB54					= (volatile uint32* const) (BASE::JPEG + 0x2E0);
		volatile uint32* const HUFF_SYMB55					= (volatile uint32* const) (BASE::JPEG + 0x2E0);
		volatile uint32* const HUFF_SYMB56					= (volatile uint32* const) (BASE::JPEG + 0x2F0);
		volatile uint32* const HUFF_SYMB57					= (volatile uint32* const) (BASE::JPEG + 0x2F0);
		volatile uint32* const HUFF_SYMB58					= (volatile uint32* const) (BASE::JPEG + 0x2F0);
		volatile uint32* const HUFF_SYMB59					= (volatile uint32* const) (BASE::JPEG + 0x2F0);
		volatile uint32* const HUFF_SYMB60					= (volatile uint32* const) (BASE::JPEG + 0x300);
		volatile uint32* const HUFF_SYMB61					= (volatile uint32* const) (BASE::JPEG + 0x304);
		volatile uint32* const HUFF_SYMB62					= (volatile uint32* const) (BASE::JPEG + 0x308);
		volatile uint32* const HUFF_SYMB63					= (volatile uint32* const) (BASE::JPEG + 0x30C);
		volatile uint32* const HUFF_SYMB64					= (volatile uint32* const) (BASE::JPEG + 0x310);
		volatile uint32* const HUFF_SYMB65					= (volatile uint32* const) (BASE::JPEG + 0x314);
		volatile uint32* const HUFF_SYMB66					= (volatile uint32* const) (BASE::JPEG + 0x318);
		volatile uint32* const HUFF_SYMB67					= (volatile uint32* const) (BASE::JPEG + 0x31C);
		volatile uint32* const HUFF_SYMB68					= (volatile uint32* const) (BASE::JPEG + 0x320);
		volatile uint32* const HUFF_SYMB69					= (volatile uint32* const) (BASE::JPEG + 0x324);
		volatile uint32* const HUFF_SYMB70					= (volatile uint32* const) (BASE::JPEG + 0x328);
		volatile uint32* const HUFF_SYMB71					= (volatile uint32* const) (BASE::JPEG + 0x32C);
		volatile uint32* const HUFF_SYMB72					= (volatile uint32* const) (BASE::JPEG + 0x330);
		volatile uint32* const HUFF_SYMB73					= (volatile uint32* const) (BASE::JPEG + 0x334);
		volatile uint32* const HUFF_SYMB74					= (volatile uint32* const) (BASE::JPEG + 0x338);
		volatile uint32* const HUFF_SYMB75					= (volatile uint32* const) (BASE::JPEG + 0x33C);
		volatile uint32* const HUFF_SYMB76					= (volatile uint32* const) (BASE::JPEG + 0x340);
		volatile uint32* const HUFF_SYMB77					= (volatile uint32* const) (BASE::JPEG + 0x344);
		volatile uint32* const HUFF_SYMB78					= (volatile uint32* const) (BASE::JPEG + 0x348);
		volatile uint32* const HUFF_SYMB79					= (volatile uint32* const) (BASE::JPEG + 0x34C);
		volatile uint32* const HUFF_SYMB80					= (volatile uint32* const) (BASE::JPEG + 0x350);
		volatile uint32* const HUFF_SYMB81					= (volatile uint32* const) (BASE::JPEG + 0x354);
		volatile uint32* const HUFF_SYMB82					= (volatile uint32* const) (BASE::JPEG + 0x358);
		volatile uint32* const HUFF_SYMB83					= (volatile uint32* const) (BASE::JPEG + 0x35C);
		
		
		volatile uint32* const DHTMEM								= (volatile uint32* const) (BASE::JPEG + 0x360);
		volatile uint32* const HUFF_ENC_AC0					= (volatile uint32* const) (BASE::JPEG + 0x500);
		volatile uint32* const HUFF_ENC_AC1					= (volatile uint32* const) (BASE::JPEG + 0x660);
		volatile uint32* const HUFF_ENC_DC0					= (volatile uint32* const) (BASE::JPEG + 0x7C0);
		volatile uint32* const HUFF_ENC_DC1					= (volatile uint32* const) (BASE::JPEG + 0x7E0);
	};
	
	namespace FMC
	{
		volatile uint32* const BCR1									= (volatile uint32* const) (BASE::FMC + 0x000);
		volatile uint32* const BTR1									= (volatile uint32* const) (BASE::FMC + 0x004);
		volatile uint32* const BCR2									= (volatile uint32* const) (BASE::FMC + 0x008);
		volatile uint32* const BTR2									= (volatile uint32* const) (BASE::FMC + 0x00C);
		volatile uint32* const BCR3									= (volatile uint32* const) (BASE::FMC + 0x010);
		volatile uint32* const BTR3									= (volatile uint32* const) (BASE::FMC + 0x014);
		volatile uint32* const BCR4									= (volatile uint32* const) (BASE::FMC + 0x018);
		volatile uint32* const BTR4									= (volatile uint32* const) (BASE::FMC + 0x01C);
		volatile uint32* const PCR									= (volatile uint32* const) (BASE::FMC + 0x080);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::FMC + 0x084);
		volatile uint32* const PMEM									= (volatile uint32* const) (BASE::FMC + 0x088);
		volatile uint32* const PATT									= (volatile uint32* const) (BASE::FMC + 0x08C);
		volatile uint32* const ECCR									= (volatile uint32* const) (BASE::FMC + 0x094);
		volatile uint32* const BWTR1								= (volatile uint32* const) (BASE::FMC + 0x104);
		volatile uint32* const BWTR2								= (volatile uint32* const) (BASE::FMC + 0x10C);
		volatile uint32* const BWTR3								= (volatile uint32* const) (BASE::FMC + 0x114);
		volatile uint32* const BWTR4								= (volatile uint32* const) (BASE::FMC + 0x11C);
		volatile uint32* const SDCR1								= (volatile uint32* const) (BASE::FMC + 0x140);
		volatile uint32* const SDCR2								= (volatile uint32* const) (BASE::FMC + 0x144);
		volatile uint32* const SDTR1								= (volatile uint32* const) (BASE::FMC + 0x148);
		volatile uint32* const SDTR2								= (volatile uint32* const) (BASE::FMC + 0x14C);
		volatile uint32* const SDCMR								= (volatile uint32* const) (BASE::FMC + 0x150);
		volatile uint32* const SDRTR								= (volatile uint32* const) (BASE::FMC + 0x154);
		volatile uint32* const SDSR									= (volatile uint32* const) (BASE::FMC + 0x158);
	};
	
	namespace QUADSPI
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x000);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x004);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x008);
		volatile uint32* const FCR									= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x00C);
		volatile uint32* const DLR									= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x010);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x014);
		volatile uint32* const AR										= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x018);
		volatile uint32* const ABR									= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x01C);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x020);
		volatile uint32* const PSMKR								= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x024);
		volatile uint32* const PSMAR								= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x028);
		volatile uint32* const PIR									= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x02C);
		volatile uint32* const LPTR									= (volatile uint32* const) (BASE::QUADSPI_CONTROL + 0x030);
		
		namespace DELAY
		{
			volatile uint32* const CR									= (volatile uint32* const) (BASE::QUADSPI_DELAY + 0x00);
			volatile uint32* const CFGR								= (volatile uint32* const) (BASE::QUADSPI_DELAY + 0x04);
		};
	};
	
	namespace SDMMC_1
	{
		volatile uint32* const POWER					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x00);
		volatile uint32* const CLKCR					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x04);
		volatile uint32* const ARGR					        = (volatile uint32* const) (BASE::SDMMC_1 + 0x08);
		volatile uint32* const CMDR					        = (volatile uint32* const) (BASE::SDMMC_1 + 0x0C);
		volatile uint32* const RESP_CMDR					  = (volatile uint32* const) (BASE::SDMMC_1 + 0x10);
		volatile uint32* const RESP_1R					    = (volatile uint32* const) (BASE::SDMMC_1 + 0x14);
		volatile uint32* const RESP_2R					    = (volatile uint32* const) (BASE::SDMMC_1 + 0x18);
		volatile uint32* const RESP_3R					    = (volatile uint32* const) (BASE::SDMMC_1 + 0x1C);
		volatile uint32* const RESP_4R					    = (volatile uint32* const) (BASE::SDMMC_1 + 0x20);
		volatile uint32* const DTIMER					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x24);
		volatile uint32* const DLENR					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x28);
		volatile uint32* const DCTRLR					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x2C);
		volatile uint32* const DCNTR					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x30);
		volatile uint32* const STAR					        = (volatile uint32* const) (BASE::SDMMC_1 + 0x34);
		volatile uint32* const ICR					        = (volatile uint32* const) (BASE::SDMMC_1 + 0x38);
		volatile uint32* const MASKR					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x3C);
		volatile uint32* const ACKTIMER					    = (volatile uint32* const) (BASE::SDMMC_1 + 0x40);
		volatile uint32* const IDMA_CTRLR					  = (volatile uint32* const) (BASE::SDMMC_1 + 0x50);
		volatile uint32* const IDMA_BSIZER					= (volatile uint32* const) (BASE::SDMMC_1 + 0x54);
		volatile uint32* const IDMA_BASE0R					= (volatile uint32* const) (BASE::SDMMC_1 + 0x58);
		volatile uint32* const IDMA_BASE1R					= (volatile uint32* const) (BASE::SDMMC_1 + 0x5C);
		volatile uint32* const FIFO0R					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x80);
		volatile uint32* const FIFO1R					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x84);
		volatile uint32* const FIFO2R					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x88);
		volatile uint32* const FIFO3R					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x8C);
		volatile uint32* const FIFO4R					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x90);
		volatile uint32* const FIFO5R					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x94);
		volatile uint32* const FIFO6R					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x98);
		volatile uint32* const FIFO7R					      = (volatile uint32* const) (BASE::SDMMC_1 + 0x9C);
		volatile uint32* const FIFO8R					      = (volatile uint32* const) (BASE::SDMMC_1 + 0xA0);
		volatile uint32* const FIFO9R					      = (volatile uint32* const) (BASE::SDMMC_1 + 0xA4);
		volatile uint32* const FIFO10R					    = (volatile uint32* const) (BASE::SDMMC_1 + 0xA8);
		volatile uint32* const FIFO11R					    = (volatile uint32* const) (BASE::SDMMC_1 + 0xAC);
		volatile uint32* const FIFO12R					    = (volatile uint32* const) (BASE::SDMMC_1 + 0xB0);
		volatile uint32* const FIFO13R					    = (volatile uint32* const) (BASE::SDMMC_1 + 0xB4);
		volatile uint32* const FIFO14R					    = (volatile uint32* const) (BASE::SDMMC_1 + 0xB8);
		volatile uint32* const FIFO15R					    = (volatile uint32* const) (BASE::SDMMC_1 + 0xBC);
		
		namespace DELAY
		{
			volatile uint32* const CR									= (volatile uint32* const) (BASE::SDMMC_1_DELAY + 0x00);
			volatile uint32* const CFGR								= (volatile uint32* const) (BASE::SDMMC_1_DELAY + 0x04);
		};
	};
	
	namespace GPIO_A
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_A + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_A + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_A + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_A + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_A + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_A + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_A + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_A + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_A + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_A + 0x24);
	}
	
	namespace GPIO_B
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_B + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_B + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_B + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_B + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_B + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_B + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_B + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_B + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_B + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_B + 0x24);
	};
	
	namespace GPIO_C
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_C + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_C + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_C + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_C + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_C + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_C + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_C + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_C + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_C + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_C + 0x24);
	};
	
	namespace GPIO_D
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_D + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_D + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_D + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_D + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_D + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_D + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_D + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_D + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_D + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_D + 0x24);
	};
	
	namespace GPIO_E
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_E + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_E + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_E + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_E + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_E + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_E + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_E + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_E + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_E + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_E + 0x24);
	};
	
	namespace GPIO_F
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_F + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_F + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_F + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_F + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_F + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_F + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_F + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_F + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_F + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_F + 0x24);
	};
	
	namespace GPIO_G
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_G + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_G + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_G + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_G + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_G + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_G + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_G + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_G + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_G + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_G + 0x24);
	};
	
	namespace GPIO_H
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_H + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_H + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_H + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_H + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_H + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_H + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_H + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_H + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_H + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_H + 0x24);
	};
	
	namespace GPIO_I
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_I + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_I + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_I + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_I + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_I + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_I + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_I + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_I + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_I + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_I + 0x24);
	};
	
	namespace GPIO_J
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_J + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_J + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_J + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_J + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_J + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_J + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_J + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_J + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_J + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_J + 0x24);
	};
	
	namespace GPIO_K
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_K + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_K + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_K + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_K + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_K + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_K + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_K + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_K + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_K + 0x20);
	};
	
	namespace RCC
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::RCC + 0x000);
		volatile uint32* const ICSCR								= (volatile uint32* const) (BASE::RCC + 0x004);
		volatile uint32* const CRRCR								= (volatile uint32* const) (BASE::RCC + 0x008);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::RCC + 0x010);
		volatile uint32* const D1_CFGR							= (volatile uint32* const) (BASE::RCC + 0x018);
		volatile uint32* const D2_CFGR							= (volatile uint32* const) (BASE::RCC + 0x01C);
		volatile uint32* const D3_CFGR							= (volatile uint32* const) (BASE::RCC + 0x020);
		volatile uint32* const PLL_CKSELR						= (volatile uint32* const) (BASE::RCC + 0x028);
		volatile uint32* const PLL_CFGR							= (volatile uint32* const) (BASE::RCC + 0x02C);
		volatile uint32* const PLL1_DIVR						= (volatile uint32* const) (BASE::RCC + 0x030);
		volatile uint32* const PLL1_FRACR						= (volatile uint32* const) (BASE::RCC + 0x034);
		volatile uint32* const PLL2_DIVR						= (volatile uint32* const) (BASE::RCC + 0x038);
		volatile uint32* const PLL2_FRACR						= (volatile uint32* const) (BASE::RCC + 0x03C);
		volatile uint32* const PLL3_DIVR						= (volatile uint32* const) (BASE::RCC + 0x040);
		volatile uint32* const PLL3_FRACR						= (volatile uint32* const) (BASE::RCC + 0x044);
		volatile uint32* const D1_CCIPR							= (volatile uint32* const) (BASE::RCC + 0x04C);
		volatile uint32* const D2_CCIP1R						= (volatile uint32* const) (BASE::RCC + 0x050);
		volatile uint32* const D2_CCIP2R						= (volatile uint32* const) (BASE::RCC + 0x054);
		volatile uint32* const D3_CCIPR							= (volatile uint32* const) (BASE::RCC + 0x058);
		volatile uint32* const CIER									= (volatile uint32* const) (BASE::RCC + 0x060);
		volatile uint32* const CIFR									= (volatile uint32* const) (BASE::RCC + 0x064);
		volatile uint32* const CICR									= (volatile uint32* const) (BASE::RCC + 0x068);
		volatile uint32* const BDCR									= (volatile uint32* const) (BASE::RCC + 0x070);
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::RCC + 0x074);
		volatile uint32* const AHB3_RSTR						= (volatile uint32* const) (BASE::RCC + 0x07C);
		volatile uint32* const AHB1_RSTR						= (volatile uint32* const) (BASE::RCC + 0x080);
		volatile uint32* const AHB2_RSTR						= (volatile uint32* const) (BASE::RCC + 0x084);
		volatile uint32* const AHB4_RSTR						= (volatile uint32* const) (BASE::RCC + 0x088);
		volatile uint32* const APB3_RSTR						= (volatile uint32* const) (BASE::RCC + 0x08C);
		volatile uint32* const APB1_LRSTR						= (volatile uint32* const) (BASE::RCC + 0x090);
		volatile uint32* const APB1_HRSTR						= (volatile uint32* const) (BASE::RCC + 0x094);
		volatile uint32* const APB2_RSTR						= (volatile uint32* const) (BASE::RCC + 0x098);
		volatile uint32* const APB4_RSTR						= (volatile uint32* const) (BASE::RCC + 0x09C);
		volatile uint32* const GCR									= (volatile uint32* const) (BASE::RCC + 0x0A0);
		volatile uint32* const D3_AMR								= (volatile uint32* const) (BASE::RCC + 0x0A8);
		volatile uint32* const RSR									= (volatile uint32* const) (BASE::RCC + 0x0D0);
		volatile uint32* const AHB3_ENR							= (volatile uint32* const) (BASE::RCC + 0x0D4);
		volatile uint32* const AHB1_ENR							= (volatile uint32* const) (BASE::RCC + 0x0D8);
		volatile uint32* const AHB2_ENR							= (volatile uint32* const) (BASE::RCC + 0x0DC);
		volatile uint32* const AHB4_ENR							= (volatile uint32* const) (BASE::RCC + 0x0E0);
		volatile uint32* const APB3_ENR							= (volatile uint32* const) (BASE::RCC + 0x0E4);
		volatile uint32* const APB1_LENR						= (volatile uint32* const) (BASE::RCC + 0x0E8);
		volatile uint32* const APB1_HENR						= (volatile uint32* const) (BASE::RCC + 0x0EC);
		volatile uint32* const APB2_ENR							= (volatile uint32* const) (BASE::RCC + 0x0F0);
		volatile uint32* const APB4_ENR							= (volatile uint32* const) (BASE::RCC + 0x0F4);
		volatile uint32* const AHB3_LPENR						= (volatile uint32* const) (BASE::RCC + 0x0FC);
		volatile uint32* const AHB1_LPENR						= (volatile uint32* const) (BASE::RCC + 0x100);
		volatile uint32* const AHB2_LPENR						= (volatile uint32* const) (BASE::RCC + 0x104);
		volatile uint32* const AHB4_LPENR						= (volatile uint32* const) (BASE::RCC + 0x108);
		volatile uint32* const APB3_LPENR						= (volatile uint32* const) (BASE::RCC + 0x10C);
		volatile uint32* const APB1_LLPENR					= (volatile uint32* const) (BASE::RCC + 0x110);
		volatile uint32* const APB1_HLPENR					= (volatile uint32* const) (BASE::RCC + 0x114);
		volatile uint32* const APB2_LPENR						= (volatile uint32* const) (BASE::RCC + 0x118);
		volatile uint32* const APB4_LPENR						= (volatile uint32* const) (BASE::RCC + 0x11C);
		volatile uint32* const C1_AHB3_ENR					= (volatile uint32* const) (BASE::RCC + 0x134);
		volatile uint32* const C1_AHB1_ENR					= (volatile uint32* const) (BASE::RCC + 0x138);
		volatile uint32* const C1_AHB2_ENR					= (volatile uint32* const) (BASE::RCC + 0x13C);
		volatile uint32* const C1_AHB4_ENR					= (volatile uint32* const) (BASE::RCC + 0x140);
		volatile uint32* const C1_APB3_ENR					= (volatile uint32* const) (BASE::RCC + 0x144);
		volatile uint32* const C1_APB1_LENR					= (volatile uint32* const) (BASE::RCC + 0x148);
		volatile uint32* const C1_APB1_HENR					= (volatile uint32* const) (BASE::RCC + 0x14C);
		volatile uint32* const C1_APB2_ENR					= (volatile uint32* const) (BASE::RCC + 0x150);
		volatile uint32* const C1_APB4_ENR					= (volatile uint32* const) (BASE::RCC + 0x154);
		volatile uint32* const C1_AHB3_LPENR				= (volatile uint32* const) (BASE::RCC + 0x15C);
		volatile uint32* const C1_AHB1_LPENR				= (volatile uint32* const) (BASE::RCC + 0x160);
		volatile uint32* const C1_AHB2_LPENR				= (volatile uint32* const) (BASE::RCC + 0x164);
		volatile uint32* const C1_AHB4_LPENR				= (volatile uint32* const) (BASE::RCC + 0x168);
		volatile uint32* const C1_APB3_LPENR				= (volatile uint32* const) (BASE::RCC + 0x16C);
		volatile uint32* const C1_APB1_LLPENR				= (volatile uint32* const) (BASE::RCC + 0x170);
		volatile uint32* const C1_APB1_HLPENR				= (volatile uint32* const) (BASE::RCC + 0x174);
		volatile uint32* const C1_APB2_LPENR				= (volatile uint32* const) (BASE::RCC + 0x178);
		volatile uint32* const C1_APB4_LPENR				= (volatile uint32* const) (BASE::RCC + 0x17C);
	};
	
	namespace PWR
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::PWR + 0x00);
		volatile uint32* const CSR1									= (volatile uint32* const) (BASE::PWR + 0x04);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::PWR + 0x08);
		volatile uint32* const CR3									= (volatile uint32* const) (BASE::PWR + 0x0C);
		volatile uint32* const CPU_CR								= (volatile uint32* const) (BASE::PWR + 0x10);
		volatile uint32* const D3_CR								= (volatile uint32* const) (BASE::PWR + 0x18);
		volatile uint32* const WKUP_CR							= (volatile uint32* const) (BASE::PWR + 0x20);
		volatile uint32* const WKUP_FR							= (volatile uint32* const) (BASE::PWR + 0x24);
		volatile uint32* const WKUP_EPR							= (volatile uint32* const) (BASE::PWR + 0x28);
	};
	
	namespace CRC
	{
		volatile uint32* const DR										= (volatile uint32* const) (BASE::CRC + 0x00);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::CRC + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::CRC + 0x08);
		volatile uint32* const INIT									= (volatile uint32* const) (BASE::CRC + 0x10);
		volatile uint32* const POL									= (volatile uint32* const) (BASE::CRC + 0x14);
	};
	
	namespace BDMA
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::BDMA + 0x00);
		volatile uint32* const IFCR									= (volatile uint32* const) (BASE::BDMA + 0x04);
		
		
		volatile uint32* const CH0_CCR							= (volatile uint32* const) (BASE::BDMA + 0x08);
		volatile uint32* const CH0_CNDTR						= (volatile uint32* const) (BASE::BDMA + 0x0C);
		volatile uint32* const CH0_CPAR							= (volatile uint32* const) (BASE::BDMA + 0x10);
		volatile uint32* const CH0_CM0AR						= (volatile uint32* const) (BASE::BDMA + 0x14);
		volatile uint32* const CH0_CM1AR						= (volatile uint32* const) (BASE::BDMA + 0x18);
		
		volatile uint32* const CH1_CCR							= (volatile uint32* const) (BASE::BDMA + 0x1C);
		volatile uint32* const CH1_CNDTR						= (volatile uint32* const) (BASE::BDMA + 0x20);
		volatile uint32* const CH1_CPAR							= (volatile uint32* const) (BASE::BDMA + 0x24);
		volatile uint32* const CH1_CM0AR						= (volatile uint32* const) (BASE::BDMA + 0x28);
		volatile uint32* const CH1_CM1AR						= (volatile uint32* const) (BASE::BDMA + 0x2C);
		
		volatile uint32* const CH2_CCR							= (volatile uint32* const) (BASE::BDMA + 0x30);
		volatile uint32* const CH2_CNDTR						= (volatile uint32* const) (BASE::BDMA + 0x34);
		volatile uint32* const CH2_CPAR							= (volatile uint32* const) (BASE::BDMA + 0x38);
		volatile uint32* const CH2_CM0AR						= (volatile uint32* const) (BASE::BDMA + 0x3C);
		volatile uint32* const CH2_CM1AR						= (volatile uint32* const) (BASE::BDMA + 0x40);
		
		volatile uint32* const CH3_CCR							= (volatile uint32* const) (BASE::BDMA + 0x44);
		volatile uint32* const CH3_CNDTR						= (volatile uint32* const) (BASE::BDMA + 0x48);
		volatile uint32* const CH3_CPAR							= (volatile uint32* const) (BASE::BDMA + 0x4C);
		volatile uint32* const CH3_CM0AR						= (volatile uint32* const) (BASE::BDMA + 0x50);
		volatile uint32* const CH3_CM1AR						= (volatile uint32* const) (BASE::BDMA + 0x54);
		
		volatile uint32* const CH4_CCR							= (volatile uint32* const) (BASE::BDMA + 0x58);
		volatile uint32* const CH4_CNDTR						= (volatile uint32* const) (BASE::BDMA + 0x5C);
		volatile uint32* const CH4_CPAR							= (volatile uint32* const) (BASE::BDMA + 0x60);
		volatile uint32* const CH4_CM0AR						= (volatile uint32* const) (BASE::BDMA + 0x64);
		volatile uint32* const CH4_CM1AR						= (volatile uint32* const) (BASE::BDMA + 0x68);
		
		volatile uint32* const CH5_CCR							= (volatile uint32* const) (BASE::BDMA + 0x6C);
		volatile uint32* const CH5_CNDTR						= (volatile uint32* const) (BASE::BDMA + 0x70);
		volatile uint32* const CH5_CPAR							= (volatile uint32* const) (BASE::BDMA + 0x74);
		volatile uint32* const CH5_CM0AR						= (volatile uint32* const) (BASE::BDMA + 0x78);
		volatile uint32* const CH5_CM1AR						= (volatile uint32* const) (BASE::BDMA + 0x7C);
		
		volatile uint32* const CH6_CCR							= (volatile uint32* const) (BASE::BDMA + 0x80);
		volatile uint32* const CH6_CNDTR						= (volatile uint32* const) (BASE::BDMA + 0x84);
		volatile uint32* const CH6_CPAR							= (volatile uint32* const) (BASE::BDMA + 0x88);
		volatile uint32* const CH6_CM0AR						= (volatile uint32* const) (BASE::BDMA + 0x8C);
		volatile uint32* const CH6_CM1AR						= (volatile uint32* const) (BASE::BDMA + 0x90);
		
		volatile uint32* const CH7_CCR							= (volatile uint32* const) (BASE::BDMA + 0x94);
		volatile uint32* const CH7_CNDTR						= (volatile uint32* const) (BASE::BDMA + 0x98);
		volatile uint32* const CH7_CPAR							= (volatile uint32* const) (BASE::BDMA + 0x9C);
		volatile uint32* const CH7_CM0AR						= (volatile uint32* const) (BASE::BDMA + 0xA0);
		volatile uint32* const CH7_CM1AR						= (volatile uint32* const) (BASE::BDMA + 0xA4);
	};
	
	namespace DMAMUX_2
	{
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMAMUX_2 + 0x000);
		volatile uint32* const CH1_CR								= (volatile uint32* const) (BASE::DMAMUX_2 + 0x004);
		volatile uint32* const CH2_CR								= (volatile uint32* const) (BASE::DMAMUX_2 + 0x008);
		volatile uint32* const CH3_CR								= (volatile uint32* const) (BASE::DMAMUX_2 + 0x00C);
		volatile uint32* const CH4_CR								= (volatile uint32* const) (BASE::DMAMUX_2 + 0x010);
		volatile uint32* const CH5_CR								= (volatile uint32* const) (BASE::DMAMUX_2 + 0x014);
		volatile uint32* const CH6_CR								= (volatile uint32* const) (BASE::DMAMUX_2 + 0x018);
		volatile uint32* const CH7_CR								= (volatile uint32* const) (BASE::DMAMUX_2 + 0x01C);
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::DMAMUX_2 + 0x080);
		volatile uint32* const CFR									= (volatile uint32* const) (BASE::DMAMUX_2 + 0x084);
		volatile uint32* const RG_CH0_CR						= (volatile uint32* const) (BASE::DMAMUX_2 + 0x100);
		volatile uint32* const RG_CH1_CR						= (volatile uint32* const) (BASE::DMAMUX_2 + 0x104);
		volatile uint32* const RG_CH2_CR						= (volatile uint32* const) (BASE::DMAMUX_2 + 0x108);
		volatile uint32* const RG_CH3_CR						= (volatile uint32* const) (BASE::DMAMUX_2 + 0x10C);
		volatile uint32* const RG_SR								= (volatile uint32* const) (BASE::DMAMUX_2 + 0x140);
		volatile uint32* const RG_CFR								= (volatile uint32* const) (BASE::DMAMUX_2 + 0x144);
	};
	
	namespace ADC_3
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC_3 + 0x00);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC_3 + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::ADC_3 + 0x08);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::ADC_3 + 0x0C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC_3 + 0x10);
		volatile uint32* const SMPR1								= (volatile uint32* const) (BASE::ADC_3 + 0x14);
		volatile uint32* const SMPR2								= (volatile uint32* const) (BASE::ADC_3 + 0x18);
		volatile uint32* const PCSEL								= (volatile uint32* const) (BASE::ADC_3 + 0x1C);
		volatile uint32* const LTR1									= (volatile uint32* const) (BASE::ADC_3 + 0x20);
		volatile uint32* const HTR1									= (volatile uint32* const) (BASE::ADC_3 + 0x24);
		volatile uint32* const SQR1									= (volatile uint32* const) (BASE::ADC_3 + 0x30);
		volatile uint32* const SQR2									= (volatile uint32* const) (BASE::ADC_3 + 0x34);
		volatile uint32* const SQR3									= (volatile uint32* const) (BASE::ADC_3 + 0x38);
		volatile uint32* const SQR4									= (volatile uint32* const) (BASE::ADC_3 + 0x3C);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::ADC_3 + 0x40);
		volatile uint32* const JSQR									= (volatile uint32* const) (BASE::ADC_3 + 0x4C);
		volatile uint32* const OFR1									= (volatile uint32* const) (BASE::ADC_3 + 0x60);
		volatile uint32* const OFR2									= (volatile uint32* const) (BASE::ADC_3 + 0x64);
		volatile uint32* const OFR3									= (volatile uint32* const) (BASE::ADC_3 + 0x68);
		volatile uint32* const OFR4									= (volatile uint32* const) (BASE::ADC_3 + 0x6C);
		volatile uint32* const JDR1									= (volatile uint32* const) (BASE::ADC_3 + 0x80);
		volatile uint32* const JDR2									= (volatile uint32* const) (BASE::ADC_3 + 0x84);
		volatile uint32* const JDR3									= (volatile uint32* const) (BASE::ADC_3 + 0x88);
		volatile uint32* const JDR4									= (volatile uint32* const) (BASE::ADC_3 + 0x8C);
		volatile uint32* const AWD2CR								= (volatile uint32* const) (BASE::ADC_3 + 0xA0);
		volatile uint32* const AWD3CR								= (volatile uint32* const) (BASE::ADC_3 + 0xA4);
		volatile uint32* const LTR2									= (volatile uint32* const) (BASE::ADC_3 + 0xB0);
		volatile uint32* const HTR2									= (volatile uint32* const) (BASE::ADC_3 + 0xB4);
		volatile uint32* const LTR3									= (volatile uint32* const) (BASE::ADC_3 + 0xB8);
		volatile uint32* const HTR3									= (volatile uint32* const) (BASE::ADC_3 + 0xBC);
		volatile uint32* const DIFSEL								= (volatile uint32* const) (BASE::ADC_3 + 0xC0);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC_3 + 0xC4);
		volatile uint32* const CALFACT2							= (volatile uint32* const) (BASE::ADC_3 + 0xC8);
		
		namespace COMMON
		{
			volatile uint32* const CSR								= (volatile uint32* const) (BASE::ADC_3_COMMON + 0x00);
			volatile uint32* const CCR								= (volatile uint32* const) (BASE::ADC_3_COMMON + 0x08);
			volatile uint32* const CDR								= (volatile uint32* const) (BASE::ADC_3_COMMON + 0x0C);
			volatile uint32* const CDR2								= (volatile uint32* const) (BASE::ADC_3_COMMON + 0x10);
		};
	};
	
	namespace HSEM
	{
		volatile uint32* const R0										= (volatile uint32* const) (BASE::HSEM + 0x000);
		volatile uint32* const R1										= (volatile uint32* const) (BASE::HSEM + 0x004);
		volatile uint32* const R2										= (volatile uint32* const) (BASE::HSEM + 0x008);
		volatile uint32* const R3										= (volatile uint32* const) (BASE::HSEM + 0x00C);
		volatile uint32* const R4										= (volatile uint32* const) (BASE::HSEM + 0x010);
		volatile uint32* const R5										= (volatile uint32* const) (BASE::HSEM + 0x014);
		volatile uint32* const R6										= (volatile uint32* const) (BASE::HSEM + 0x018);
		volatile uint32* const R7										= (volatile uint32* const) (BASE::HSEM + 0x01C);
		volatile uint32* const R8										= (volatile uint32* const) (BASE::HSEM + 0x020);
		volatile uint32* const R9										= (volatile uint32* const) (BASE::HSEM + 0x024);
		volatile uint32* const R10									= (volatile uint32* const) (BASE::HSEM + 0x028);
		volatile uint32* const R11									= (volatile uint32* const) (BASE::HSEM + 0x02C);
		volatile uint32* const R12									= (volatile uint32* const) (BASE::HSEM + 0x030);
		volatile uint32* const R13									= (volatile uint32* const) (BASE::HSEM + 0x034);
		volatile uint32* const R14									= (volatile uint32* const) (BASE::HSEM + 0x038);
		volatile uint32* const R15									= (volatile uint32* const) (BASE::HSEM + 0x03C);
		volatile uint32* const R16									= (volatile uint32* const) (BASE::HSEM + 0x040);
		volatile uint32* const R17									= (volatile uint32* const) (BASE::HSEM + 0x044);
		volatile uint32* const R18									= (volatile uint32* const) (BASE::HSEM + 0x048);
		volatile uint32* const R19									= (volatile uint32* const) (BASE::HSEM + 0x04C);
		volatile uint32* const R20									= (volatile uint32* const) (BASE::HSEM + 0x050);
		volatile uint32* const R21									= (volatile uint32* const) (BASE::HSEM + 0x054);
		volatile uint32* const R22									= (volatile uint32* const) (BASE::HSEM + 0x058);
		volatile uint32* const R23									= (volatile uint32* const) (BASE::HSEM + 0x05C);
		volatile uint32* const R24									= (volatile uint32* const) (BASE::HSEM + 0x060);
		volatile uint32* const R25									= (volatile uint32* const) (BASE::HSEM + 0x064);
		volatile uint32* const R26									= (volatile uint32* const) (BASE::HSEM + 0x068);
		volatile uint32* const R27									= (volatile uint32* const) (BASE::HSEM + 0x06C);
		volatile uint32* const R28									= (volatile uint32* const) (BASE::HSEM + 0x070);
		volatile uint32* const R29									= (volatile uint32* const) (BASE::HSEM + 0x074);
		volatile uint32* const R30									= (volatile uint32* const) (BASE::HSEM + 0x078);
		volatile uint32* const R31									= (volatile uint32* const) (BASE::HSEM + 0x07C);
		
		volatile uint32* const RLR0									= (volatile uint32* const) (BASE::HSEM + 0x080);
		volatile uint32* const RLR1									= (volatile uint32* const) (BASE::HSEM + 0x084);
		volatile uint32* const RLR2									= (volatile uint32* const) (BASE::HSEM + 0x088);
		volatile uint32* const RLR3									= (volatile uint32* const) (BASE::HSEM + 0x08C);
		volatile uint32* const RLR4									= (volatile uint32* const) (BASE::HSEM + 0x090);
		volatile uint32* const RLR5									= (volatile uint32* const) (BASE::HSEM + 0x094);
		volatile uint32* const RLR6									= (volatile uint32* const) (BASE::HSEM + 0x098);
		volatile uint32* const RLR7									= (volatile uint32* const) (BASE::HSEM + 0x09C);
		volatile uint32* const RLR8									= (volatile uint32* const) (BASE::HSEM + 0x0A0);
		volatile uint32* const RLR9									= (volatile uint32* const) (BASE::HSEM + 0x0A4);
		volatile uint32* const RLR10								= (volatile uint32* const) (BASE::HSEM + 0x0A8);
		volatile uint32* const RLR11								= (volatile uint32* const) (BASE::HSEM + 0x0AC);
		volatile uint32* const RLR12								= (volatile uint32* const) (BASE::HSEM + 0x0B0);
		volatile uint32* const RLR13								= (volatile uint32* const) (BASE::HSEM + 0x0B4);
		volatile uint32* const RLR14								= (volatile uint32* const) (BASE::HSEM + 0x0B8);
		volatile uint32* const RLR15								= (volatile uint32* const) (BASE::HSEM + 0x0BC);
		volatile uint32* const RLR16								= (volatile uint32* const) (BASE::HSEM + 0x0C0);
		volatile uint32* const RLR17								= (volatile uint32* const) (BASE::HSEM + 0x0C4);
		volatile uint32* const RLR18								= (volatile uint32* const) (BASE::HSEM + 0x0C8);
		volatile uint32* const RLR19								= (volatile uint32* const) (BASE::HSEM + 0x0CC);
		volatile uint32* const RLR20								= (volatile uint32* const) (BASE::HSEM + 0x0D0);
		volatile uint32* const RLR21								= (volatile uint32* const) (BASE::HSEM + 0x0D4);
		volatile uint32* const RLR22								= (volatile uint32* const) (BASE::HSEM + 0x0D8);
		volatile uint32* const RLR23								= (volatile uint32* const) (BASE::HSEM + 0x0DC);
		volatile uint32* const RLR24								= (volatile uint32* const) (BASE::HSEM + 0x0E0);
		volatile uint32* const RLR25								= (volatile uint32* const) (BASE::HSEM + 0x0E4);
		volatile uint32* const RLR26								= (volatile uint32* const) (BASE::HSEM + 0x0E8);
		volatile uint32* const RLR27								= (volatile uint32* const) (BASE::HSEM + 0x0EC);
		volatile uint32* const RLR28								= (volatile uint32* const) (BASE::HSEM + 0x0F0);
		volatile uint32* const RLR29								= (volatile uint32* const) (BASE::HSEM + 0x0F4);
		volatile uint32* const RLR30								= (volatile uint32* const) (BASE::HSEM + 0x0F8);
		volatile uint32* const RLR31								= (volatile uint32* const) (BASE::HSEM + 0x0FC);
		
		volatile uint32* const IER									= (volatile uint32* const) (BASE::HSEM + 0x100);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::HSEM + 0x104);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::HSEM + 0x108);
		volatile uint32* const MISR									= (volatile uint32* const) (BASE::HSEM + 0x10C);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::HSEM + 0x140);
		volatile uint32* const KEYR									= (volatile uint32* const) (BASE::HSEM + 0x144);
	};
};