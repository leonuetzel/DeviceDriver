#pragma once

#include "cmos.hpp"





namespace Interrupt
{
	constexpr uint16 WWDG																									= 16;
	constexpr uint16 PVD_PVM																							= 17;
	constexpr uint16 RTC_TAMPER_CSS_LSE																		= 18;
	constexpr uint16 RTC_WKUP																							= 19;
	constexpr uint16 FLASH																								= 20;
	constexpr uint16 RCC																									= 21;
	constexpr uint16 EXTI_0																								= 22;
	constexpr uint16 EXTI_1																								= 23;
	constexpr uint16 EXTI_2																								= 24;
	constexpr uint16 EXTI_3																								= 25;
	constexpr uint16 EXTI_4																								= 26;
	constexpr uint16 DMA_1_CH0																						= 27;
	constexpr uint16 DMA_1_CH1																						= 28;
	constexpr uint16 DMA_1_CH2																						= 29;
	constexpr uint16 DMA_1_CH3																						= 30;
	constexpr uint16 DMA_1_CH4																						= 31;
	constexpr uint16 DMA_1_CH5																						= 32;
	constexpr uint16 DMA_1_CH6																						= 33;
	constexpr uint16 ADC_1_2																							= 34;
	constexpr uint16 USB_HIGH_PRIORITY																		= 35;
	constexpr uint16 USB_LOW_PRIORITY																			= 36;
	constexpr uint16 FDCAN_1_IT0																					= 37;
	constexpr uint16 FDCAN_1_IT1																					= 38;
	constexpr uint16 EXTI_9_TO_5																					= 39;
	constexpr uint16 TIMER_1_BREAK_TIMER_15																= 40;
	constexpr uint16 TIMER_1_UPDATE_TIMER_16															= 41;
	constexpr uint16 TIMER_1_TRIGGER_COMMUTATION_DIRECTION_INDEX_TIMER_17	= 42;
	constexpr uint16 TIMER_1_CAPTURE_COMPARE															= 43;
	constexpr uint16 TIMER_2																							= 44;
	constexpr uint16 TIMER_3																							= 45;
	constexpr uint16 TIMER_4																							= 46;
	constexpr uint16 I2C_1_EVENT																					= 47;
	constexpr uint16 I2C_1_ERROR																					= 48;
	constexpr uint16 I2C_2_EVENT																					= 49;
	constexpr uint16 I2C_2_ERROR																					= 50;
	constexpr uint16 SPI_1																								= 51;
	constexpr uint16 SPI_2																								= 52;
	constexpr uint16 USART_1																							= 53;
	constexpr uint16 USART_2																							= 54;
	constexpr uint16 USART_3																							= 55;
	constexpr uint16 EXTI_15_TO_10																				= 56;
	constexpr uint16 RTC_ALARM																						= 57;
	constexpr uint16 USB_WAKEUP																						= 58;
	constexpr uint16 TIMER_8_BREAK_TRANSITIONERROR_INDEXERROR							= 59;
	constexpr uint16 TIMER_8_UPDATE																				= 60;
	constexpr uint16 TIMER_8_TRIGGER_COMMUTATION_DIRECTION_INDEX					= 61;
	constexpr uint16 TIMER_8_CAPTURE_COMPARE															= 62;
	constexpr uint16 ADC_3																								= 63;
	constexpr uint16 FSMC																									= 64;
	constexpr uint16 LP_TIMER_1																						= 65;
	constexpr uint16 TIMER_5																							= 66;	
	constexpr uint16 SPI_3																								= 67;
	constexpr uint16 UART_4																								= 68;
	constexpr uint16 UART_5																								= 69;
	constexpr uint16 TIMER_6_DAC_UNDERRUN																	= 70;
	constexpr uint16 TIMER_7_DAC_UNDERRUN																	= 71;
	constexpr uint16 DMA_2_CH0																						= 72;
	constexpr uint16 DMA_2_CH1																						= 73;
	constexpr uint16 DMA_2_CH2																						= 74;
	constexpr uint16 DMA_2_CH3																						= 75;
	constexpr uint16 DMA_2_CH4																						= 76;
	constexpr uint16 ADC_4																								= 77;
	constexpr uint16 ADC_5																								= 78;
	constexpr uint16 UCPD																									= 79;
	constexpr uint16 COMP_1_2_3																						= 80;
	constexpr uint16 COMP_4_5_6																						= 81;
	constexpr uint16 COMP_7																								= 82;
	constexpr uint16 HR_TIMER_MASTER																			= 83;
	constexpr uint16 HR_TIMER_A																						= 84;
	constexpr uint16 HR_TIMER_B																						= 85;
	constexpr uint16 HR_TIMER_C																						= 86;
	constexpr uint16 HR_TIMER_D																						= 87;
	constexpr uint16 HR_TIMER_E																						= 88;
	constexpr uint16 HR_TIMER_FAULT																				= 89;
	constexpr uint16 HR_TIMER_F																						= 90;
	constexpr uint16 CRS																									= 91;
	constexpr uint16 SAI 																									= 92;
	constexpr uint16 TIMER_20_BREAK_TRANSITIONERROR_INDEXERROR						= 93;
	constexpr uint16 TIMER_20_UPDATE																			= 94;
	constexpr uint16 TIMER_20_TRIGGER_COMMUTATION_DIRECTION_INDEX					= 95;
	constexpr uint16 TIMER_20_CAPTURE_COMPARE															= 96;
	constexpr uint16 FPU																									= 97;
	constexpr uint16 I2C_4_EVENT																					= 98;
	constexpr uint16 I2C_4_ERROR																					= 99;
	constexpr uint16 SPI_4																								= 100;
	constexpr uint16 AES																									= 101;
	constexpr uint16 FDCAN_2_IT0																					= 102;
	constexpr uint16 FDCAN_2_IT1																					= 103;
	constexpr uint16 FDCAN_3_IT0																					= 104;
	constexpr uint16 FDCAN_3_IT1																					= 105;
	constexpr uint16 RNG																									= 106;
	constexpr uint16 LPUART_1																							= 107;
	constexpr uint16 I2C_3_EVENT																					= 108;
	constexpr uint16 I2C_3_ERROR																					= 109;
	constexpr uint16 DMAMUX_OVERRUN																				= 110;
	constexpr uint16 QUADSPI																							= 111;
	constexpr uint16 DMA_1_CH7																						= 112;
	constexpr uint16 DMA_2_CH5																						= 113;
	constexpr uint16 DMA_2_CH6																						= 114;
	constexpr uint16 DMA_2_CH7																						= 115;
	constexpr uint16 CORDIC																								= 116;
	constexpr uint16 FMAC																									= 117;
};



namespace MCU
{
	namespace BASE
	{
		constexpr uint32 PERIPHERAL									= 0x40000000;
		
		constexpr uint32 APB1					        			= PERIPHERAL + 0x00000000;
		constexpr uint32 APB2					        			= PERIPHERAL + 0x00010000;
		constexpr uint32 AHB1					        			= PERIPHERAL + 0x00020000;
		constexpr uint32 AHB2					        			= PERIPHERAL + 0x08000000;
		constexpr uint32 AHB3					        			= PERIPHERAL + 0xA0000000;
		
		
		
		
		
		constexpr uint32 TIMER_2										= APB1 + 0x00000000;
		constexpr uint32 TIMER_3										= APB1 + 0x00000400;
		constexpr uint32 TIMER_4										= APB1 + 0x00000800;
		constexpr uint32 TIMER_5										= APB1 + 0x00000C00;
		constexpr uint32 TIMER_6										= APB1 + 0x00001000;
		constexpr uint32 TIMER_7										= APB1 + 0x00001400;
		constexpr uint32 CRS												= APB1 + 0x00002000;
		constexpr uint32 TAMPER								    	= APB1 + 0x00002400;
		constexpr uint32 RTC												= APB1 + 0x00002800;
		constexpr uint32 WWDG												= APB1 + 0x00002C00;
		constexpr uint32 IWDG												= APB1 + 0x00003000;
		constexpr uint32 SPI_2											= APB1 + 0x00003800;
		constexpr uint32 SPI_3											= APB1 + 0x00003C00;
		constexpr uint32 USART_2										= APB1 + 0x00004400;
		constexpr uint32 USART_3										= APB1 + 0x00004800;
		constexpr uint32 UART_4											= APB1 + 0x00004C00;
		constexpr uint32 UART_5											= APB1 + 0x00005000;
		constexpr uint32 I2C_1											= APB1 + 0x00005400;
		constexpr uint32 I2C_2											= APB1 + 0x00005800;
		constexpr uint32 USB												= APB1 + 0x00005C00;
		constexpr uint32 FDCAN_1										= APB1 + 0x00006400;
		constexpr uint32 FDCAN_2										= APB1 + 0x00006800;
		constexpr uint32 FDCAN_3										= APB1 + 0x00006C00;
		constexpr uint32 PWR												= APB1 + 0x00007000;
		constexpr uint32 I2C_3											= APB1 + 0x00007800;
		constexpr uint32 LP_TIMER_1									= APB1 + 0x00007C00;
		constexpr uint32 LP_UART_1									= APB1 + 0x00008000;
		constexpr uint32 I2C_4											= APB1 + 0x00008400;
		constexpr uint32 UCPD												= APB1 + 0x0000A000;
		constexpr uint32 FDCAN_MSG_RAM							= APB1 + 0x0000A400;
		
		constexpr uint32 SYSCFG											= APB2 + 0x00000000;
		constexpr uint32 VREFBUF										= APB2 + 0x00000030;
		constexpr uint32 COMP												= APB2 + 0x00000200;
		constexpr uint32 OPAMP											= APB2 + 0x00000300;
		constexpr uint32 EXTI												= APB2 + 0x00000400;
		constexpr uint32 TIMER_1										= APB2 + 0x00002C00;
		constexpr uint32 SPI_1											= APB2 + 0x00003000;
		constexpr uint32 TIMER_8										= APB2 + 0x00003400;
		constexpr uint32 USART_1										= APB2 + 0x00003800;
		constexpr uint32 SPI_4											= APB2 + 0x00003C00;
		constexpr uint32 TIMER_15										= APB2 + 0x00004000;
		constexpr uint32 TIMER_16										= APB2 + 0x00004400;
		constexpr uint32 TIMER_17										= APB2 + 0x00004800;
		constexpr uint32 TIMER_20										= APB2 + 0x00005000;
		constexpr uint32 SAI_1											= APB2 + 0x00005400;
		constexpr uint32 HR_TIMER										= APB2 + 0x00006800;
			constexpr uint32 HR_TIMER_MASTER						= HR_TIMER + 0x000;
			constexpr uint32 HR_TIMER_A									= HR_TIMER + 0x080;
			constexpr uint32 HR_TIMER_B									= HR_TIMER + 0x100;
			constexpr uint32 HR_TIMER_C									= HR_TIMER + 0x180;
			constexpr uint32 HR_TIMER_D									= HR_TIMER + 0x200;
			constexpr uint32 HR_TIMER_E									= HR_TIMER + 0x280;
			constexpr uint32 HR_TIMER_F									= HR_TIMER + 0x300;
			constexpr uint32 HR_TIMER_COMMON						= HR_TIMER + 0x380;
		
		constexpr uint32 DMA_1											= AHB1 + 0x00000000;
		constexpr uint32 DMA_2											= AHB1 + 0x00000400;
		constexpr uint32 DMAMUX											= AHB1 + 0x00000800;
		constexpr uint32 CORDIC											= AHB1 + 0x00000C00;
		constexpr uint32 RCC												= AHB1 + 0x00001000;
		constexpr uint32 FMAC												= AHB1 + 0x00001400;
		constexpr uint32 FLASH				 							= AHB1 + 0x00002000;
		constexpr uint32 CRC												= AHB1 + 0x00003000;

		constexpr uint32 GPIO_A									    = AHB2 + 0x00000000;
		constexpr uint32 GPIO_B									    = AHB2 + 0x00000400;
		constexpr uint32 GPIO_C									    = AHB2 + 0x00000800;
		constexpr uint32 GPIO_D									    = AHB2 + 0x00000C00;
		constexpr uint32 GPIO_E									    = AHB2 + 0x00001000;
		constexpr uint32 GPIO_F									    = AHB2 + 0x00001400;
		constexpr uint32 GPIO_G									    = AHB2 + 0x00001800;
		constexpr uint32 ADC_1											= AHB2 + 0x08000000;
		constexpr uint32 ADC_2											= AHB2 + 0x08000100;
		constexpr uint32 ADC_1_2_COMMON							= AHB2 + 0x08000300;
		constexpr uint32 ADC_3											= AHB2 + 0x08000400;
		constexpr uint32 ADC_4											= AHB2 + 0x08000500;
		constexpr uint32 ADC_5											= AHB2 + 0x08000600;
		constexpr uint32 ADC_3_4_5_COMMON						= AHB2 + 0x08000700;
		constexpr uint32 DAC_1											= AHB2 + 0x08000800;
		constexpr uint32 DAC_2											= AHB2 + 0x08000C00;
		constexpr uint32 DAC_3											= AHB2 + 0x08001000;
		constexpr uint32 DAC_4											= AHB2 + 0x08001400;
		constexpr uint32 AES												= AHB2 + 0x08060000;
		constexpr uint32 RNG									    	= AHB2 + 0x08060800;
		
		constexpr uint32 FSMC												= AHB3 + 0x00000000;
		constexpr uint32 QUADSPI										= AHB3 + 0x00001000;
		
		constexpr uint32 DBGMCU											= CORE::BASE::CORE + 0x00042000;
	};
	
	
	
	namespace TIMER_2
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x000);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x004);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x008);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x00C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_2 + 0x010);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x014);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_2 + 0x018);
		volatile uint32* const CCMR2			        	= (volatile uint32* const) (BASE::TIMER_2 + 0x01C);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x020);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x024);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x028);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x02C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x034);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x038);
		volatile uint32* const CCR3			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x03C);
		volatile uint32* const CCR4			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x040);
		volatile uint32* const ECR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x058);
		volatile uint32* const TISEL			        	= (volatile uint32* const) (BASE::TIMER_2 + 0x05C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x060);
		volatile uint32* const AF2			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x064);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x3DC);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x3E0);
		
	};
	
	namespace TIMER_3
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x000);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x004);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x008);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x00C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_3 + 0x010);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x014);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_3 + 0x018);
		volatile uint32* const CCMR2			        	= (volatile uint32* const) (BASE::TIMER_3 + 0x01C);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x020);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x024);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x028);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x02C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x034);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x038);
		volatile uint32* const CCR3			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x03C);
		volatile uint32* const CCR4			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x040);
		volatile uint32* const ECR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x058);
		volatile uint32* const TISEL			        	= (volatile uint32* const) (BASE::TIMER_3 + 0x05C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x060);
		volatile uint32* const AF2			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x064);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x3DC);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x3E0);
	};
	
	namespace TIMER_4
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x000);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x004);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x008);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x00C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_4 + 0x010);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x014);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_4 + 0x018);
		volatile uint32* const CCMR2			        	= (volatile uint32* const) (BASE::TIMER_4 + 0x01C);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x020);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x024);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x028);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x02C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x034);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x038);
		volatile uint32* const CCR3			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x03C);
		volatile uint32* const CCR4			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x040);
		volatile uint32* const ECR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x058);
		volatile uint32* const TISEL			        	= (volatile uint32* const) (BASE::TIMER_4 + 0x05C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x060);
		volatile uint32* const AF2			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x064);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x3DC);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x3E0);
	};
	
	namespace TIMER_5
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x000);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x004);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x008);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x00C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_5 + 0x010);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x014);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_5 + 0x018);
		volatile uint32* const CCMR2			        	= (volatile uint32* const) (BASE::TIMER_5 + 0x01C);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x020);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x024);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x028);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x02C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x034);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x038);
		volatile uint32* const CCR3			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x03C);
		volatile uint32* const CCR4			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x040);
		volatile uint32* const ECR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x058);
		volatile uint32* const TISEL			        	= (volatile uint32* const) (BASE::TIMER_5 + 0x05C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x060);
		volatile uint32* const AF2			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x064);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x3DC);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x3E0);
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
	
	namespace CRS
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::CRS + 0x00);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::CRS + 0x04);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::CRS + 0x08);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::CRS + 0x0C);
	};
	
	namespace TAMPER
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::TAMPER + 0x000);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::TAMPER + 0x004);
		volatile uint32* const FLTCR								= (volatile uint32* const) (BASE::TAMPER + 0x00C);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::TAMPER + 0x02C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::TAMPER + 0x030);
		volatile uint32* const MISR									= (volatile uint32* const) (BASE::TAMPER + 0x034);
		volatile uint32* const SCR									= (volatile uint32* const) (BASE::TAMPER + 0x03C);
		volatile uint32* const BKP0R								= (volatile uint32* const) (BASE::TAMPER + 0x100);
		volatile uint32* const BKP1R								= (volatile uint32* const) (BASE::TAMPER + 0x104);
		volatile uint32* const BKP2R								= (volatile uint32* const) (BASE::TAMPER + 0x108);
		volatile uint32* const BKP3R								= (volatile uint32* const) (BASE::TAMPER + 0x10C);
		volatile uint32* const BKP4R								= (volatile uint32* const) (BASE::TAMPER + 0x110);
		volatile uint32* const BKP5R								= (volatile uint32* const) (BASE::TAMPER + 0x114);
		volatile uint32* const BKP6R								= (volatile uint32* const) (BASE::TAMPER + 0x118);
		volatile uint32* const BKP7R								= (volatile uint32* const) (BASE::TAMPER + 0x11C);
		volatile uint32* const BKP8R								= (volatile uint32* const) (BASE::TAMPER + 0x120);
		volatile uint32* const BKP9R								= (volatile uint32* const) (BASE::TAMPER + 0x124);
		volatile uint32* const BKP10R								= (volatile uint32* const) (BASE::TAMPER + 0x128);
		volatile uint32* const BKP11R								= (volatile uint32* const) (BASE::TAMPER + 0x12C);
		volatile uint32* const BKP12R								= (volatile uint32* const) (BASE::TAMPER + 0x130);
		volatile uint32* const BKP13R								= (volatile uint32* const) (BASE::TAMPER + 0x134);
		volatile uint32* const BKP14R								= (volatile uint32* const) (BASE::TAMPER + 0x138);
		volatile uint32* const BKP15R								= (volatile uint32* const) (BASE::TAMPER + 0x13C);
		volatile uint32* const BKP16R								= (volatile uint32* const) (BASE::TAMPER + 0x140);
		volatile uint32* const BKP17R								= (volatile uint32* const) (BASE::TAMPER + 0x144);
		volatile uint32* const BKP18R								= (volatile uint32* const) (BASE::TAMPER + 0x148);
		volatile uint32* const BKP19R								= (volatile uint32* const) (BASE::TAMPER + 0x14C);
		volatile uint32* const BKP20R								= (volatile uint32* const) (BASE::TAMPER + 0x150);
		volatile uint32* const BKP21R								= (volatile uint32* const) (BASE::TAMPER + 0x154);
		volatile uint32* const BKP22R								= (volatile uint32* const) (BASE::TAMPER + 0x158);
		volatile uint32* const BKP23R								= (volatile uint32* const) (BASE::TAMPER + 0x15C);
		volatile uint32* const BKP24R								= (volatile uint32* const) (BASE::TAMPER + 0x160);
		volatile uint32* const BKP25R								= (volatile uint32* const) (BASE::TAMPER + 0x164);
		volatile uint32* const BKP26R								= (volatile uint32* const) (BASE::TAMPER + 0x168);
		volatile uint32* const BKP27R								= (volatile uint32* const) (BASE::TAMPER + 0x16C);
		volatile uint32* const BKP28R								= (volatile uint32* const) (BASE::TAMPER + 0x170);
		volatile uint32* const BKP29R								= (volatile uint32* const) (BASE::TAMPER + 0x174);
		volatile uint32* const BKP30R								= (volatile uint32* const) (BASE::TAMPER + 0x178);
		volatile uint32* const BKP31R								= (volatile uint32* const) (BASE::TAMPER + 0x17C);
	};
	
	namespace RTC
	{
		volatile uint32* const TR				        		= (volatile uint32* const) (BASE::RTC + 0x00);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::RTC + 0x04);
		volatile uint32* const SSR				        	= (volatile uint32* const) (BASE::RTC + 0x08);
		volatile uint32* const ICSR				        	= (volatile uint32* const) (BASE::RTC + 0x0C);
		volatile uint32* const PRER				        	= (volatile uint32* const) (BASE::RTC + 0x10);
		volatile uint32* const WUTR				        	= (volatile uint32* const) (BASE::RTC + 0x14);
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::RTC + 0x18);
		volatile uint32* const WPR				        	= (volatile uint32* const) (BASE::RTC + 0x24);
		volatile uint32* const CALR				        	= (volatile uint32* const) (BASE::RTC + 0x28);
		volatile uint32* const SHIFTR				        = (volatile uint32* const) (BASE::RTC + 0x2C);
		volatile uint32* const TSTR				        	= (volatile uint32* const) (BASE::RTC + 0x30);
		volatile uint32* const TSDR				        	= (volatile uint32* const) (BASE::RTC + 0x34);
		volatile uint32* const TSSSR				        = (volatile uint32* const) (BASE::RTC + 0x38);
		volatile uint32* const ALRMAR				        = (volatile uint32* const) (BASE::RTC + 0x40);
		volatile uint32* const ALRMASSR				      = (volatile uint32* const) (BASE::RTC + 0x44);
		volatile uint32* const ALRMBR				        = (volatile uint32* const) (BASE::RTC + 0x48);
		volatile uint32* const ALRMBSSR				      = (volatile uint32* const) (BASE::RTC + 0x4C);
		volatile uint32* const SR				      			= (volatile uint32* const) (BASE::RTC + 0x50);
		volatile uint32* const MISR				      		= (volatile uint32* const) (BASE::RTC + 0x54);
		volatile uint32* const SCR				      		= (volatile uint32* const) (BASE::RTC + 0x5C);
	};
	
	namespace WWDG
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::WWDG + 0x00);
		volatile uint32* const CFR									= (volatile uint32* const) (BASE::WWDG + 0x04);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::WWDG + 0x08);
	};
	
	namespace IWDG
	{
		volatile uint32* const KR				        		= (volatile uint32* const) (BASE::IWDG + 0x00);
		volatile uint32* const PR				        		= (volatile uint32* const) (BASE::IWDG + 0x04);
		volatile uint32* const RLR				        	= (volatile uint32* const) (BASE::IWDG + 0x08);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::IWDG + 0x0C);
		volatile uint32* const WINR				        	= (volatile uint32* const) (BASE::IWDG + 0x10);
	};
	
	namespace SPI_2
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::SPI_2 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::SPI_2 + 0x04);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::SPI_2 + 0x08);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::SPI_2 + 0x0C);
		volatile uint32* const CRCPR								= (volatile uint32* const) (BASE::SPI_2 + 0x10);
		volatile uint32* const RXCRC								= (volatile uint32* const) (BASE::SPI_2 + 0x14);
		volatile uint32* const TXCRC								= (volatile uint32* const) (BASE::SPI_2 + 0x18);
		volatile uint32* const I2S_CFGR							= (volatile uint32* const) (BASE::SPI_2 + 0x1C);
		volatile uint32* const I2S_PR								= (volatile uint32* const) (BASE::SPI_2 + 0x20);
	};
	
	namespace SPI_3
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::SPI_3 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::SPI_3 + 0x04);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::SPI_3 + 0x08);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::SPI_3 + 0x0C);
		volatile uint32* const CRCPR								= (volatile uint32* const) (BASE::SPI_3 + 0x10);
		volatile uint32* const RXCRC								= (volatile uint32* const) (BASE::SPI_3 + 0x14);
		volatile uint32* const TXCRC								= (volatile uint32* const) (BASE::SPI_3 + 0x18);
		volatile uint32* const I2S_CFGR							= (volatile uint32* const) (BASE::SPI_3 + 0x1C);
		volatile uint32* const I2S_PR								= (volatile uint32* const) (BASE::SPI_3 + 0x20);
	};
	
	namespace USART_2
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::USART_2 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::USART_2 + 0x04);
		volatile uint32* const CR3									= (volatile uint32* const) (BASE::USART_2 + 0x08);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::USART_2 + 0x0C);
		volatile uint32* const GTPR									= (volatile uint32* const) (BASE::USART_2 + 0x10);
		volatile uint32* const RTOR									= (volatile uint32* const) (BASE::USART_2 + 0x14);
		volatile uint32* const RQR									= (volatile uint32* const) (BASE::USART_2 + 0x18);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::USART_2 + 0x1C);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::USART_2 + 0x20);
		volatile uint32* const RDR									= (volatile uint32* const) (BASE::USART_2 + 0x24);
		volatile uint32* const TDR									= (volatile uint32* const) (BASE::USART_2 + 0x28);
		volatile uint32* const PRESC								= (volatile uint32* const) (BASE::USART_2 + 0x2C);
	};
	
	namespace USART_3
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::USART_3 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::USART_3 + 0x04);
		volatile uint32* const CR3									= (volatile uint32* const) (BASE::USART_3 + 0x08);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::USART_3 + 0x0C);
		volatile uint32* const GTPR									= (volatile uint32* const) (BASE::USART_3 + 0x10);
		volatile uint32* const RTOR									= (volatile uint32* const) (BASE::USART_3 + 0x14);
		volatile uint32* const RQR									= (volatile uint32* const) (BASE::USART_3 + 0x18);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::USART_3 + 0x1C);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::USART_3 + 0x20);
		volatile uint32* const RDR									= (volatile uint32* const) (BASE::USART_3 + 0x24);
		volatile uint32* const TDR									= (volatile uint32* const) (BASE::USART_3 + 0x28);
		volatile uint32* const PRESC								= (volatile uint32* const) (BASE::USART_3 + 0x2C);
	};
	
	namespace UART_4
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::UART_4 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::UART_4 + 0x04);
		volatile uint32* const CR3									= (volatile uint32* const) (BASE::UART_4 + 0x08);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::UART_4 + 0x0C);
		volatile uint32* const GTPR									= (volatile uint32* const) (BASE::UART_4 + 0x10);
		volatile uint32* const RTOR									= (volatile uint32* const) (BASE::UART_4 + 0x14);
		volatile uint32* const RQR									= (volatile uint32* const) (BASE::UART_4 + 0x18);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::UART_4 + 0x1C);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::UART_4 + 0x20);
		volatile uint32* const RDR									= (volatile uint32* const) (BASE::UART_4 + 0x24);
		volatile uint32* const TDR									= (volatile uint32* const) (BASE::UART_4 + 0x28);
		volatile uint32* const PRESC								= (volatile uint32* const) (BASE::UART_4 + 0x2C);
	};
	
	namespace UART_5
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::UART_5 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::UART_5 + 0x04);
		volatile uint32* const CR3									= (volatile uint32* const) (BASE::UART_5 + 0x08);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::UART_5 + 0x0C);
		volatile uint32* const GTPR									= (volatile uint32* const) (BASE::UART_5 + 0x10);
		volatile uint32* const RTOR									= (volatile uint32* const) (BASE::UART_5 + 0x14);
		volatile uint32* const RQR									= (volatile uint32* const) (BASE::UART_5 + 0x18);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::UART_5 + 0x1C);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::UART_5 + 0x20);
		volatile uint32* const RDR									= (volatile uint32* const) (BASE::UART_5 + 0x24);
		volatile uint32* const TDR									= (volatile uint32* const) (BASE::UART_5 + 0x28);
		volatile uint32* const PRESC								= (volatile uint32* const) (BASE::UART_5 + 0x2C);
	};
	
	namespace I2C_1
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::I2C_1 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::I2C_1 + 0x04);
		volatile uint32* const OAR1									= (volatile uint32* const) (BASE::I2C_1 + 0x08);
		volatile uint32* const OAR2									= (volatile uint32* const) (BASE::I2C_1 + 0x0C);
		volatile uint32* const TIMINGR							= (volatile uint32* const) (BASE::I2C_1 + 0x10);
		volatile uint32* const TIMEOUTR							= (volatile uint32* const) (BASE::I2C_1 + 0x14);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::I2C_1 + 0x18);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::I2C_1 + 0x1C);
		volatile uint32* const PECR									= (volatile uint32* const) (BASE::I2C_1 + 0x20);
		volatile uint32* const RXDR									= (volatile uint32* const) (BASE::I2C_1 + 0x24);
		volatile uint32* const TXDR									= (volatile uint32* const) (BASE::I2C_1 + 0x28);
	};
	
	namespace I2C_2
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::I2C_2 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::I2C_2 + 0x04);
		volatile uint32* const OAR1									= (volatile uint32* const) (BASE::I2C_2 + 0x08);
		volatile uint32* const OAR2									= (volatile uint32* const) (BASE::I2C_2 + 0x0C);
		volatile uint32* const TIMINGR							= (volatile uint32* const) (BASE::I2C_2 + 0x10);
		volatile uint32* const TIMEOUTR							= (volatile uint32* const) (BASE::I2C_2 + 0x14);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::I2C_2 + 0x18);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::I2C_2 + 0x1C);
		volatile uint32* const PECR									= (volatile uint32* const) (BASE::I2C_2 + 0x20);
		volatile uint32* const RXDR									= (volatile uint32* const) (BASE::I2C_2 + 0x24);
		volatile uint32* const TXDR									= (volatile uint32* const) (BASE::I2C_2 + 0x28);
	};
	
	namespace USB
	{
		volatile uint32* const EP0R									= (volatile uint32* const) (BASE::USB + 0x00);
		volatile uint32* const EP1R									= (volatile uint32* const) (BASE::USB + 0x04);
		volatile uint32* const EP2R									= (volatile uint32* const) (BASE::USB + 0x08);
		volatile uint32* const EP3R									= (volatile uint32* const) (BASE::USB + 0x0C);
		volatile uint32* const EP4R									= (volatile uint32* const) (BASE::USB + 0x10);
		volatile uint32* const EP5R									= (volatile uint32* const) (BASE::USB + 0x14);
		volatile uint32* const EP6R									= (volatile uint32* const) (BASE::USB + 0x18);
		volatile uint32* const EP7R									= (volatile uint32* const) (BASE::USB + 0x1C);
		volatile uint32* const CNTR									= (volatile uint32* const) (BASE::USB + 0x40);
		volatile uint32* const ISTR									= (volatile uint32* const) (BASE::USB + 0x44);
		volatile uint32* const FNR									= (volatile uint32* const) (BASE::USB + 0x48);
		volatile uint32* const DADDR								= (volatile uint32* const) (BASE::USB + 0x4C);
		volatile uint32* const BTABLE								= (volatile uint32* const) (BASE::USB + 0x50);
		volatile uint32* const LPMCSR								= (volatile uint32* const) (BASE::USB + 0x54);
		volatile uint32* const BCDR									= (volatile uint32* const) (BASE::USB + 0x58);
	};
	
	namespace FDCAN_1
	{
		volatile uint32* const CREL									= (volatile uint32* const) (BASE::FDCAN_1 + 0x000);
		volatile uint32* const ENDN									= (volatile uint32* const) (BASE::FDCAN_1 + 0x004);
		volatile uint32* const DBTP									= (volatile uint32* const) (BASE::FDCAN_1 + 0x00C);
		volatile uint32* const TEST									= (volatile uint32* const) (BASE::FDCAN_1 + 0x010);
		volatile uint32* const RWD									= (volatile uint32* const) (BASE::FDCAN_1 + 0x014);
		volatile uint32* const CCCR									= (volatile uint32* const) (BASE::FDCAN_1 + 0x018);
		volatile uint32* const NBTP									= (volatile uint32* const) (BASE::FDCAN_1 + 0x01C);
		volatile uint32* const TSCC									= (volatile uint32* const) (BASE::FDCAN_1 + 0x020);
		volatile uint32* const TSCV									= (volatile uint32* const) (BASE::FDCAN_1 + 0x024);
		volatile uint32* const TOCC									= (volatile uint32* const) (BASE::FDCAN_1 + 0x028);
		volatile uint32* const TOCV									= (volatile uint32* const) (BASE::FDCAN_1 + 0x02C);
		volatile uint32* const ECR									= (volatile uint32* const) (BASE::FDCAN_1 + 0x040);
		volatile uint32* const PSR									= (volatile uint32* const) (BASE::FDCAN_1 + 0x044);
		volatile uint32* const TDCR									= (volatile uint32* const) (BASE::FDCAN_1 + 0x048);
		volatile uint32* const IR										= (volatile uint32* const) (BASE::FDCAN_1 + 0x050);
		volatile uint32* const IE										= (volatile uint32* const) (BASE::FDCAN_1 + 0x054);
		volatile uint32* const ILS									= (volatile uint32* const) (BASE::FDCAN_1 + 0x058);
		volatile uint32* const ILE									= (volatile uint32* const) (BASE::FDCAN_1 + 0x05C);
		volatile uint32* const RXGFC								= (volatile uint32* const) (BASE::FDCAN_1 + 0x080);
		volatile uint32* const XIDAM								= (volatile uint32* const) (BASE::FDCAN_1 + 0x084);
		volatile uint32* const HPMS									= (volatile uint32* const) (BASE::FDCAN_1 + 0x088);
		volatile uint32* const RX_F0S								= (volatile uint32* const) (BASE::FDCAN_1 + 0x090);
		volatile uint32* const RX_F0A								= (volatile uint32* const) (BASE::FDCAN_1 + 0x094);
		volatile uint32* const RX_F1S								= (volatile uint32* const) (BASE::FDCAN_1 + 0x098);
		volatile uint32* const RX_F1A								= (volatile uint32* const) (BASE::FDCAN_1 + 0x09C);
		volatile uint32* const TX_BC								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0C0);
		volatile uint32* const TX_FQS								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0C4);
		volatile uint32* const TX_BRP								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0C8);
		volatile uint32* const TX_BAR								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0CC);
		volatile uint32* const TX_BCR								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0D0);
		volatile uint32* const TX_BTO								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0D4);
		volatile uint32* const TX_BCF								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0D8);
		volatile uint32* const TX_BTIE							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0DC);
		volatile uint32* const TX_BCIE							= (volatile uint32* const) (BASE::FDCAN_1 + 0x0E0);
		volatile uint32* const TX_EFS								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0E4);
		volatile uint32* const TX_EFA								= (volatile uint32* const) (BASE::FDCAN_1 + 0x0E8);
		volatile uint32* const CKDIV								= (volatile uint32* const) (BASE::FDCAN_1 + 0x100);
		
		volatile uint32* const MSG_RAM							= (volatile uint32* const) (BASE::FDCAN_MSG_RAM + 0x000);
	}
	
	namespace FDCAN_2
	{
		volatile uint32* const CREL									= (volatile uint32* const) (BASE::FDCAN_2 + 0x000);
		volatile uint32* const ENDN									= (volatile uint32* const) (BASE::FDCAN_2 + 0x004);
		volatile uint32* const DBTP									= (volatile uint32* const) (BASE::FDCAN_2 + 0x00C);
		volatile uint32* const TEST									= (volatile uint32* const) (BASE::FDCAN_2 + 0x010);
		volatile uint32* const RWD									= (volatile uint32* const) (BASE::FDCAN_2 + 0x014);
		volatile uint32* const CCCR									= (volatile uint32* const) (BASE::FDCAN_2 + 0x018);
		volatile uint32* const NBTP									= (volatile uint32* const) (BASE::FDCAN_2 + 0x01C);
		volatile uint32* const TSCC									= (volatile uint32* const) (BASE::FDCAN_2 + 0x020);
		volatile uint32* const TSCV									= (volatile uint32* const) (BASE::FDCAN_2 + 0x024);
		volatile uint32* const TOCC									= (volatile uint32* const) (BASE::FDCAN_2 + 0x028);
		volatile uint32* const TOCV									= (volatile uint32* const) (BASE::FDCAN_2 + 0x02C);
		volatile uint32* const ECR									= (volatile uint32* const) (BASE::FDCAN_2 + 0x040);
		volatile uint32* const PSR									= (volatile uint32* const) (BASE::FDCAN_2 + 0x044);
		volatile uint32* const TDCR									= (volatile uint32* const) (BASE::FDCAN_2 + 0x048);
		volatile uint32* const IR										= (volatile uint32* const) (BASE::FDCAN_2 + 0x050);
		volatile uint32* const IE										= (volatile uint32* const) (BASE::FDCAN_2 + 0x054);
		volatile uint32* const ILS									= (volatile uint32* const) (BASE::FDCAN_2 + 0x058);
		volatile uint32* const ILE									= (volatile uint32* const) (BASE::FDCAN_2 + 0x05C);
		volatile uint32* const RXGFC								= (volatile uint32* const) (BASE::FDCAN_2 + 0x080);
		volatile uint32* const XIDAM								= (volatile uint32* const) (BASE::FDCAN_2 + 0x084);
		volatile uint32* const HPMS									= (volatile uint32* const) (BASE::FDCAN_2 + 0x088);
		volatile uint32* const RX_F0S								= (volatile uint32* const) (BASE::FDCAN_2 + 0x090);
		volatile uint32* const RX_F0A								= (volatile uint32* const) (BASE::FDCAN_2 + 0x094);
		volatile uint32* const RX_F1S								= (volatile uint32* const) (BASE::FDCAN_2 + 0x098);
		volatile uint32* const RX_F1A								= (volatile uint32* const) (BASE::FDCAN_2 + 0x09C);
		volatile uint32* const TX_BC								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0C0);
		volatile uint32* const TX_FQS								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0C4);
		volatile uint32* const TX_BRP								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0C8);
		volatile uint32* const TX_BAR								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0CC);
		volatile uint32* const TX_BCR								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0D0);
		volatile uint32* const TX_BTO								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0D4);
		volatile uint32* const TX_BCF								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0D8);
		volatile uint32* const TX_BTIE							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0DC);
		volatile uint32* const TX_BCIE							= (volatile uint32* const) (BASE::FDCAN_2 + 0x0E0);
		volatile uint32* const TX_EFS								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0E4);
		volatile uint32* const TX_EFA								= (volatile uint32* const) (BASE::FDCAN_2 + 0x0E8);
		
		volatile uint32* const MSG_RAM							= (volatile uint32* const) (BASE::FDCAN_MSG_RAM + 0x350);
	}
	
	namespace FDCAN_3
	{
		volatile uint32* const CREL									= (volatile uint32* const) (BASE::FDCAN_3 + 0x000);
		volatile uint32* const ENDN									= (volatile uint32* const) (BASE::FDCAN_3 + 0x004);
		volatile uint32* const DBTP									= (volatile uint32* const) (BASE::FDCAN_3 + 0x00C);
		volatile uint32* const TEST									= (volatile uint32* const) (BASE::FDCAN_3 + 0x010);
		volatile uint32* const RWD									= (volatile uint32* const) (BASE::FDCAN_3 + 0x014);
		volatile uint32* const CCCR									= (volatile uint32* const) (BASE::FDCAN_3 + 0x018);
		volatile uint32* const NBTP									= (volatile uint32* const) (BASE::FDCAN_3 + 0x01C);
		volatile uint32* const TSCC									= (volatile uint32* const) (BASE::FDCAN_3 + 0x020);
		volatile uint32* const TSCV									= (volatile uint32* const) (BASE::FDCAN_3 + 0x024);
		volatile uint32* const TOCC									= (volatile uint32* const) (BASE::FDCAN_3 + 0x028);
		volatile uint32* const TOCV									= (volatile uint32* const) (BASE::FDCAN_3 + 0x02C);
		volatile uint32* const ECR									= (volatile uint32* const) (BASE::FDCAN_3 + 0x040);
		volatile uint32* const PSR									= (volatile uint32* const) (BASE::FDCAN_3 + 0x044);
		volatile uint32* const TDCR									= (volatile uint32* const) (BASE::FDCAN_3 + 0x048);
		volatile uint32* const IR										= (volatile uint32* const) (BASE::FDCAN_3 + 0x050);
		volatile uint32* const IE										= (volatile uint32* const) (BASE::FDCAN_3 + 0x054);
		volatile uint32* const ILS									= (volatile uint32* const) (BASE::FDCAN_3 + 0x058);
		volatile uint32* const ILE									= (volatile uint32* const) (BASE::FDCAN_3 + 0x05C);
		volatile uint32* const RXGFC								= (volatile uint32* const) (BASE::FDCAN_3 + 0x080);
		volatile uint32* const XIDAM								= (volatile uint32* const) (BASE::FDCAN_3 + 0x084);
		volatile uint32* const HPMS									= (volatile uint32* const) (BASE::FDCAN_3 + 0x088);
		volatile uint32* const RX_F0S								= (volatile uint32* const) (BASE::FDCAN_3 + 0x090);
		volatile uint32* const RX_F0A								= (volatile uint32* const) (BASE::FDCAN_3 + 0x094);
		volatile uint32* const RX_F1S								= (volatile uint32* const) (BASE::FDCAN_3 + 0x098);
		volatile uint32* const RX_F1A								= (volatile uint32* const) (BASE::FDCAN_3 + 0x09C);
		volatile uint32* const TX_BC								= (volatile uint32* const) (BASE::FDCAN_3 + 0x0C0);
		volatile uint32* const TX_FQS								= (volatile uint32* const) (BASE::FDCAN_3 + 0x0C4);
		volatile uint32* const TX_BRP								= (volatile uint32* const) (BASE::FDCAN_3 + 0x0C8);
		volatile uint32* const TX_BAR								= (volatile uint32* const) (BASE::FDCAN_3 + 0x0CC);
		volatile uint32* const TX_BCR								= (volatile uint32* const) (BASE::FDCAN_3 + 0x0D0);
		volatile uint32* const TX_BTO								= (volatile uint32* const) (BASE::FDCAN_3 + 0x0D4);
		volatile uint32* const TX_BCF								= (volatile uint32* const) (BASE::FDCAN_3 + 0x0D8);
		volatile uint32* const TX_BTIE							= (volatile uint32* const) (BASE::FDCAN_3 + 0x0DC);
		volatile uint32* const TX_BCIE							= (volatile uint32* const) (BASE::FDCAN_3 + 0x0E0);
		volatile uint32* const TX_EFS								= (volatile uint32* const) (BASE::FDCAN_3 + 0x0E4);
		volatile uint32* const TX_EFA								= (volatile uint32* const) (BASE::FDCAN_3 + 0x0E8);
		
		volatile uint32* const MSG_RAM							= (volatile uint32* const) (BASE::FDCAN_MSG_RAM + 0x6A0);
	}
	
	namespace PWR
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::PWR + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::PWR + 0x04);
		volatile uint32* const CR3									= (volatile uint32* const) (BASE::PWR + 0x08);
		volatile uint32* const CR4									= (volatile uint32* const) (BASE::PWR + 0x0C);
		volatile uint32* const SR1									= (volatile uint32* const) (BASE::PWR + 0x10);
		volatile uint32* const SR2									= (volatile uint32* const) (BASE::PWR + 0x14);
		volatile uint32* const SCR									= (volatile uint32* const) (BASE::PWR + 0x18);
		volatile uint32* const PUCRA								= (volatile uint32* const) (BASE::PWR + 0x20);
		volatile uint32* const PDCRA								= (volatile uint32* const) (BASE::PWR + 0x24);
		volatile uint32* const PUCRB								= (volatile uint32* const) (BASE::PWR + 0x28);
		volatile uint32* const PDCRB								= (volatile uint32* const) (BASE::PWR + 0x2C);
		volatile uint32* const PUCRC								= (volatile uint32* const) (BASE::PWR + 0x30);
		volatile uint32* const PDCRC								= (volatile uint32* const) (BASE::PWR + 0x34);
		volatile uint32* const PUCRD								= (volatile uint32* const) (BASE::PWR + 0x38);
		volatile uint32* const PDCRD								= (volatile uint32* const) (BASE::PWR + 0x3C);
		volatile uint32* const PUCRE								= (volatile uint32* const) (BASE::PWR + 0x40);
		volatile uint32* const PDCRE								= (volatile uint32* const) (BASE::PWR + 0x44);
		volatile uint32* const PUCRF								= (volatile uint32* const) (BASE::PWR + 0x48);
		volatile uint32* const PDCRF								= (volatile uint32* const) (BASE::PWR + 0x4C);
		volatile uint32* const PUCRG								= (volatile uint32* const) (BASE::PWR + 0x50);
		volatile uint32* const PDCRG								= (volatile uint32* const) (BASE::PWR + 0x54);
		volatile uint32* const CR5									= (volatile uint32* const) (BASE::PWR + 0x80);
	};
	
	namespace I2C_3
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::I2C_3 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::I2C_3 + 0x04);
		volatile uint32* const OAR1									= (volatile uint32* const) (BASE::I2C_3 + 0x08);
		volatile uint32* const OAR2									= (volatile uint32* const) (BASE::I2C_3 + 0x0C);
		volatile uint32* const TIMINGR							= (volatile uint32* const) (BASE::I2C_3 + 0x10);
		volatile uint32* const TIMEOUTR							= (volatile uint32* const) (BASE::I2C_3 + 0x14);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::I2C_3 + 0x18);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::I2C_3 + 0x1C);
		volatile uint32* const PECR									= (volatile uint32* const) (BASE::I2C_3 + 0x20);
		volatile uint32* const RXDR									= (volatile uint32* const) (BASE::I2C_3 + 0x24);
		volatile uint32* const TXDR									= (volatile uint32* const) (BASE::I2C_3 + 0x28);
	};
	
	namespace LP_TIMER_1
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x00);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x04);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x08);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x0C);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x10);
		volatile uint32* const CMP									= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x14);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x18);
		volatile uint32* const CNT									= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x1C);
		volatile uint32* const OR										= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x20);
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
	};
	
	namespace I2C_4
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::I2C_4 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::I2C_4 + 0x04);
		volatile uint32* const OAR1									= (volatile uint32* const) (BASE::I2C_4 + 0x08);
		volatile uint32* const OAR2									= (volatile uint32* const) (BASE::I2C_4 + 0x0C);
		volatile uint32* const TIMINGR							= (volatile uint32* const) (BASE::I2C_4 + 0x10);
		volatile uint32* const TIMEOUTR							= (volatile uint32* const) (BASE::I2C_4 + 0x14);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::I2C_4 + 0x18);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::I2C_4 + 0x1C);
		volatile uint32* const PECR									= (volatile uint32* const) (BASE::I2C_4 + 0x20);
		volatile uint32* const RXDR									= (volatile uint32* const) (BASE::I2C_4 + 0x24);
		volatile uint32* const TXDR									= (volatile uint32* const) (BASE::I2C_4 + 0x28);
	};
	
	namespace UCPD
	{
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::UCPD + 0x00);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::UCPD + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::UCPD + 0x0C);
		volatile uint32* const IMR									= (volatile uint32* const) (BASE::UCPD + 0x10);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::UCPD + 0x14);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::UCPD + 0x18);
		volatile uint32* const TX_ORDSETR						= (volatile uint32* const) (BASE::UCPD + 0x1C);
		volatile uint32* const TX_PAYSZR						= (volatile uint32* const) (BASE::UCPD + 0x20);
		volatile uint32* const TX_DR								= (volatile uint32* const) (BASE::UCPD + 0x24);
		volatile uint32* const RX_ORDSETR						= (volatile uint32* const) (BASE::UCPD + 0x28);
		volatile uint32* const RX_PAYSZR						= (volatile uint32* const) (BASE::UCPD + 0x2C);
		volatile uint32* const RX_DR								= (volatile uint32* const) (BASE::UCPD + 0x30);
		volatile uint32* const RX_ORDEXTR1					= (volatile uint32* const) (BASE::UCPD + 0x34);
		volatile uint32* const RX_ORDEXTR2					= (volatile uint32* const) (BASE::UCPD + 0x38);
	};
	
	
	
	
	
	namespace SYSCFG
	{
		volatile uint32* const MEMRMP								= (volatile uint32* const) (BASE::SYSCFG + 0x00);
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::SYSCFG + 0x04);
		volatile uint32* const EXTI_CR1							= (volatile uint32* const) (BASE::SYSCFG + 0x08);
		volatile uint32* const EXTI_CR2							= (volatile uint32* const) (BASE::SYSCFG + 0x0C);
		volatile uint32* const EXTI_CR3							= (volatile uint32* const) (BASE::SYSCFG + 0x10);
		volatile uint32* const EXTI_CR4							= (volatile uint32* const) (BASE::SYSCFG + 0x14);
		volatile uint32* const SCSR									= (volatile uint32* const) (BASE::SYSCFG + 0x18);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::SYSCFG + 0x1C);
		volatile uint32* const SWPR									= (volatile uint32* const) (BASE::SYSCFG + 0x20);
		volatile uint32* const SKR									= (volatile uint32* const) (BASE::SYSCFG + 0x24);
	};
	
	namespace VREFBUF
	{
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::VREFBUF + 0x00);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::VREFBUF + 0x04);
	};
	
	namespace COMP
	{
		volatile uint32* const C1_CSR								= (volatile uint32* const) (BASE::COMP + 0x00);
		volatile uint32* const C2_CSR								= (volatile uint32* const) (BASE::COMP + 0x04);
		volatile uint32* const C3_CSR								= (volatile uint32* const) (BASE::COMP + 0x08);
		volatile uint32* const C4_CSR								= (volatile uint32* const) (BASE::COMP + 0x0C);
		volatile uint32* const C5_CSR								= (volatile uint32* const) (BASE::COMP + 0x10);
		volatile uint32* const C6_CSR								= (volatile uint32* const) (BASE::COMP + 0x14);
		volatile uint32* const C7_CSR								= (volatile uint32* const) (BASE::COMP + 0x18);
	};
	
	namespace OPAMP
	{
		volatile uint32* const CSR1									= (volatile uint32* const) (BASE::OPAMP + 0x00);
		volatile uint32* const CSR2									= (volatile uint32* const) (BASE::OPAMP + 0x04);
		volatile uint32* const CSR3									= (volatile uint32* const) (BASE::OPAMP + 0x08);
		volatile uint32* const CSR4									= (volatile uint32* const) (BASE::OPAMP + 0x0C);
		volatile uint32* const CSR5									= (volatile uint32* const) (BASE::OPAMP + 0x10);
		volatile uint32* const CSR6									= (volatile uint32* const) (BASE::OPAMP + 0x14);
		volatile uint32* const TCMR1								= (volatile uint32* const) (BASE::OPAMP + 0x18);
		volatile uint32* const TCMR2								= (volatile uint32* const) (BASE::OPAMP + 0x1C);
		volatile uint32* const TCMR3								= (volatile uint32* const) (BASE::OPAMP + 0x20);
		volatile uint32* const TCMR4								= (volatile uint32* const) (BASE::OPAMP + 0x24);
		volatile uint32* const TCMR5								= (volatile uint32* const) (BASE::OPAMP + 0x28);
		volatile uint32* const TCMR6								= (volatile uint32* const) (BASE::OPAMP + 0x2C);
	};
	
	namespace EXTI
	{
		volatile uint32* const IMR1									= (volatile uint32* const) (BASE::EXTI + 0x00);
		volatile uint32* const EMR1									= (volatile uint32* const) (BASE::EXTI + 0x04);
		volatile uint32* const RTSR1								= (volatile uint32* const) (BASE::EXTI + 0x08);
		volatile uint32* const FTSR1								= (volatile uint32* const) (BASE::EXTI + 0x0C);
		volatile uint32* const SWIER1								= (volatile uint32* const) (BASE::EXTI + 0x10);
		volatile uint32* const PR1									= (volatile uint32* const) (BASE::EXTI + 0x14);
		volatile uint32* const IMR2									= (volatile uint32* const) (BASE::EXTI + 0x20);
		volatile uint32* const EMR2									= (volatile uint32* const) (BASE::EXTI + 0x24);
		volatile uint32* const RTSR2								= (volatile uint32* const) (BASE::EXTI + 0x28);
		volatile uint32* const FTSR2								= (volatile uint32* const) (BASE::EXTI + 0x2C);
		volatile uint32* const SWIER2								= (volatile uint32* const) (BASE::EXTI + 0x30);
		volatile uint32* const PR2									= (volatile uint32* const) (BASE::EXTI + 0x34);
	};
	
	namespace TIMER_1
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::TIMER_1 + 0x000);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::TIMER_1 + 0x004);
		volatile uint32* const SMCR									= (volatile uint32* const) (BASE::TIMER_1 + 0x008);
		volatile uint32* const DIER									= (volatile uint32* const) (BASE::TIMER_1 + 0x00C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::TIMER_1 + 0x010);
		volatile uint32* const EGR									= (volatile uint32* const) (BASE::TIMER_1 + 0x014);
		volatile uint32* const CCMR1								= (volatile uint32* const) (BASE::TIMER_1 + 0x018);
		volatile uint32* const CCMR2								= (volatile uint32* const) (BASE::TIMER_1 + 0x01C);
		volatile uint32* const CCER									= (volatile uint32* const) (BASE::TIMER_1 + 0x020);
		volatile uint32* const CNT									= (volatile uint32* const) (BASE::TIMER_1 + 0x024);
		volatile uint32* const PSC									= (volatile uint32* const) (BASE::TIMER_1 + 0x028);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::TIMER_1 + 0x02C);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::TIMER_1 + 0x030);
		volatile uint32* const CCR1									= (volatile uint32* const) (BASE::TIMER_1 + 0x034);
		volatile uint32* const CCR2									= (volatile uint32* const) (BASE::TIMER_1 + 0x038);
		volatile uint32* const CCR3									= (volatile uint32* const) (BASE::TIMER_1 + 0x03C);
		volatile uint32* const CCR4									= (volatile uint32* const) (BASE::TIMER_1 + 0x040);
		volatile uint32* const BDTR									= (volatile uint32* const) (BASE::TIMER_1 + 0x044);
		volatile uint32* const CCR5									= (volatile uint32* const) (BASE::TIMER_1 + 0x048);
		volatile uint32* const CCR6									= (volatile uint32* const) (BASE::TIMER_1 + 0x04C);
		volatile uint32* const CCMR3								= (volatile uint32* const) (BASE::TIMER_1 + 0x050);
		volatile uint32* const DTR2									= (volatile uint32* const) (BASE::TIMER_1 + 0x054);
		volatile uint32* const ECR									= (volatile uint32* const) (BASE::TIMER_1 + 0x058);
		volatile uint32* const TISEL								= (volatile uint32* const) (BASE::TIMER_1 + 0x05C);
		volatile uint32* const AF1									= (volatile uint32* const) (BASE::TIMER_1 + 0x060);
		volatile uint32* const AF2									= (volatile uint32* const) (BASE::TIMER_1 + 0x064);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::TIMER_1 + 0x3DC);
		volatile uint32* const DMAR									= (volatile uint32* const) (BASE::TIMER_1 + 0x3E0);
	};
	
	namespace SPI_1
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::SPI_1 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::SPI_1 + 0x04);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::SPI_1 + 0x08);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::SPI_1 + 0x0C);
		volatile uint32* const CRCPR								= (volatile uint32* const) (BASE::SPI_1 + 0x10);
		volatile uint32* const RXCRC								= (volatile uint32* const) (BASE::SPI_1 + 0x14);
		volatile uint32* const TXCRC								= (volatile uint32* const) (BASE::SPI_1 + 0x18);
	};
	
	namespace TIMER_8
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::TIMER_8 + 0x000);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::TIMER_8 + 0x004);
		volatile uint32* const SMCR									= (volatile uint32* const) (BASE::TIMER_8 + 0x008);
		volatile uint32* const DIER									= (volatile uint32* const) (BASE::TIMER_8 + 0x00C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::TIMER_8 + 0x010);
		volatile uint32* const EGR									= (volatile uint32* const) (BASE::TIMER_8 + 0x014);
		volatile uint32* const CCMR1								= (volatile uint32* const) (BASE::TIMER_8 + 0x018);
		volatile uint32* const CCMR2								= (volatile uint32* const) (BASE::TIMER_8 + 0x01C);
		volatile uint32* const CCER									= (volatile uint32* const) (BASE::TIMER_8 + 0x020);
		volatile uint32* const CNT									= (volatile uint32* const) (BASE::TIMER_8 + 0x024);
		volatile uint32* const PSC									= (volatile uint32* const) (BASE::TIMER_8 + 0x028);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::TIMER_8 + 0x02C);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::TIMER_8 + 0x030);
		volatile uint32* const CCR1									= (volatile uint32* const) (BASE::TIMER_8 + 0x034);
		volatile uint32* const CCR2									= (volatile uint32* const) (BASE::TIMER_8 + 0x038);
		volatile uint32* const CCR3									= (volatile uint32* const) (BASE::TIMER_8 + 0x03C);
		volatile uint32* const CCR4									= (volatile uint32* const) (BASE::TIMER_8 + 0x040);
		volatile uint32* const BDTR									= (volatile uint32* const) (BASE::TIMER_8 + 0x044);
		volatile uint32* const CCR5									= (volatile uint32* const) (BASE::TIMER_8 + 0x048);
		volatile uint32* const CCR6									= (volatile uint32* const) (BASE::TIMER_8 + 0x04C);
		volatile uint32* const CCMR3								= (volatile uint32* const) (BASE::TIMER_8 + 0x050);
		volatile uint32* const DTR2									= (volatile uint32* const) (BASE::TIMER_8 + 0x054);
		volatile uint32* const ECR									= (volatile uint32* const) (BASE::TIMER_8 + 0x058);
		volatile uint32* const TISEL								= (volatile uint32* const) (BASE::TIMER_8 + 0x05C);
		volatile uint32* const AF1									= (volatile uint32* const) (BASE::TIMER_8 + 0x060);
		volatile uint32* const AF2									= (volatile uint32* const) (BASE::TIMER_8 + 0x064);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::TIMER_8 + 0x3DC);
		volatile uint32* const DMAR									= (volatile uint32* const) (BASE::TIMER_8 + 0x3E0);
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
	
	namespace SPI_4
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::SPI_4 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::SPI_4 + 0x04);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::SPI_4 + 0x08);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::SPI_4 + 0x0C);
		volatile uint32* const CRCPR								= (volatile uint32* const) (BASE::SPI_4 + 0x10);
		volatile uint32* const RXCRC								= (volatile uint32* const) (BASE::SPI_4 + 0x14);
		volatile uint32* const TXCRC								= (volatile uint32* const) (BASE::SPI_4 + 0x18);
	};
	
	namespace TIMER_15
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x000);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x004);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x00C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_15 + 0x010);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x014);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_15 + 0x018);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x020);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x024);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x028);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x02C);
		volatile uint32* const RCR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x030);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x034);
		volatile uint32* const BDTR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x044);
		volatile uint32* const DTR2			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x054);
		volatile uint32* const TISEL			        	= (volatile uint32* const) (BASE::TIMER_15 + 0x05C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x060);
		volatile uint32* const AF2			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x064);
		volatile uint32* const OR1			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x068);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x3DC);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x3E0);
	};
	
	namespace TIMER_16
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x000);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x004);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x00C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_16 + 0x010);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x014);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_16 + 0x018);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x020);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x024);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x028);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x02C);
		volatile uint32* const RCR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x030);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x034);
		volatile uint32* const BDTR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x044);
		volatile uint32* const DTR2			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x054);
		volatile uint32* const TISEL			        	= (volatile uint32* const) (BASE::TIMER_16 + 0x05C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x060);
		volatile uint32* const AF2			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x064);
		volatile uint32* const OR1			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x068);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x3DC);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x3E0);
	};
	
	namespace TIMER_17
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x000);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x004);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x00C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_17 + 0x010);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x014);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_17 + 0x018);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x020);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x024);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x028);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x02C);
		volatile uint32* const RCR			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x030);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x034);
		volatile uint32* const BDTR			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x044);
		volatile uint32* const DTR2			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x054);
		volatile uint32* const TISEL			        	= (volatile uint32* const) (BASE::TIMER_17 + 0x05C);
		volatile uint32* const AF1			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x060);
		volatile uint32* const AF2			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x064);
		volatile uint32* const OR1			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x068);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x3DC);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x3E0);
	};
	
	namespace TIMER_20
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::TIMER_20 + 0x000);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::TIMER_20 + 0x004);
		volatile uint32* const SMCR									= (volatile uint32* const) (BASE::TIMER_20 + 0x008);
		volatile uint32* const DIER									= (volatile uint32* const) (BASE::TIMER_20 + 0x00C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::TIMER_20 + 0x010);
		volatile uint32* const EGR									= (volatile uint32* const) (BASE::TIMER_20 + 0x014);
		volatile uint32* const CCMR1								= (volatile uint32* const) (BASE::TIMER_20 + 0x018);
		volatile uint32* const CCMR2								= (volatile uint32* const) (BASE::TIMER_20 + 0x01C);
		volatile uint32* const CCER									= (volatile uint32* const) (BASE::TIMER_20 + 0x020);
		volatile uint32* const CNT									= (volatile uint32* const) (BASE::TIMER_20 + 0x024);
		volatile uint32* const PSC									= (volatile uint32* const) (BASE::TIMER_20 + 0x028);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::TIMER_20 + 0x02C);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::TIMER_20 + 0x030);
		volatile uint32* const CCR1									= (volatile uint32* const) (BASE::TIMER_20 + 0x034);
		volatile uint32* const CCR2									= (volatile uint32* const) (BASE::TIMER_20 + 0x038);
		volatile uint32* const CCR3									= (volatile uint32* const) (BASE::TIMER_20 + 0x03C);
		volatile uint32* const CCR4									= (volatile uint32* const) (BASE::TIMER_20 + 0x040);
		volatile uint32* const BDTR									= (volatile uint32* const) (BASE::TIMER_20 + 0x044);
		volatile uint32* const CCR5									= (volatile uint32* const) (BASE::TIMER_20 + 0x048);
		volatile uint32* const CCR6									= (volatile uint32* const) (BASE::TIMER_20 + 0x04C);
		volatile uint32* const CCMR3								= (volatile uint32* const) (BASE::TIMER_20 + 0x050);
		volatile uint32* const DTR2									= (volatile uint32* const) (BASE::TIMER_20 + 0x054);
		volatile uint32* const ECR									= (volatile uint32* const) (BASE::TIMER_20 + 0x058);
		volatile uint32* const TISEL								= (volatile uint32* const) (BASE::TIMER_20 + 0x05C);
		volatile uint32* const AF1									= (volatile uint32* const) (BASE::TIMER_20 + 0x060);
		volatile uint32* const AF2									= (volatile uint32* const) (BASE::TIMER_20 + 0x064);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::TIMER_20 + 0x3DC);
		volatile uint32* const DMAR									= (volatile uint32* const) (BASE::TIMER_20 + 0x3E0);
	};
	
	namespace SAI_1
	{
		volatile uint32* const A_CR1								= (volatile uint32* const) (BASE::SAI_1 + 0x04);
		volatile uint32* const A_CR2  							= (volatile uint32* const) (BASE::SAI_1 + 0x08);
		volatile uint32* const A_FRCR 							= (volatile uint32* const) (BASE::SAI_1 + 0x0C);
		volatile uint32* const A_SLOTR							= (volatile uint32* const) (BASE::SAI_1 + 0x10);
		volatile uint32* const A_IM   							= (volatile uint32* const) (BASE::SAI_1 + 0x14);
		volatile uint32* const A_SR   							= (volatile uint32* const) (BASE::SAI_1 + 0x18);
		volatile uint32* const A_CLRFR							= (volatile uint32* const) (BASE::SAI_1 + 0x1C);
		volatile uint32* const A_DR   							= (volatile uint32* const) (BASE::SAI_1 + 0x20);
		volatile uint32* const B_CR1  							= (volatile uint32* const) (BASE::SAI_1 + 0x24);
		volatile uint32* const B_CR2  							= (volatile uint32* const) (BASE::SAI_1 + 0x28);
		volatile uint32* const B_FRCR 							= (volatile uint32* const) (BASE::SAI_1 + 0x2C);
		volatile uint32* const B_SLOTR							= (volatile uint32* const) (BASE::SAI_1 + 0x30);
		volatile uint32* const B_IM   							= (volatile uint32* const) (BASE::SAI_1 + 0x34);
		volatile uint32* const B_SR   							= (volatile uint32* const) (BASE::SAI_1 + 0x38);
		volatile uint32* const B_CLRFR							= (volatile uint32* const) (BASE::SAI_1 + 0x3C);
		volatile uint32* const B_DR   							= (volatile uint32* const) (BASE::SAI_1 + 0x40);
		volatile uint32* const PDM_CR 							= (volatile uint32* const) (BASE::SAI_1 + 0x44);
		volatile uint32* const PDM_DLY							= (volatile uint32* const) (BASE::SAI_1 + 0x48);
	};
	
	namespace HR_TIMER
	{
		volatile uint32* const CR1								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x00);
		volatile uint32* const CR2								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x04);
		volatile uint32* const ISR								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x08);
		volatile uint32* const ICR								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x0C);
		volatile uint32* const IER								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x10);
		volatile uint32* const OENR								= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x14);
		volatile uint32* const ODISR							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x18);
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
		volatile uint32* const DLLCR							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x4C);
		volatile uint32* const FLTIN1							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x50);
		volatile uint32* const FLTIN2							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x54);
		volatile uint32* const MASTER_BDUPDR			= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x58);
		volatile uint32* const A_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x5C);
		volatile uint32* const B_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x60);
		volatile uint32* const C_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x64);
		volatile uint32* const D_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x68);
		volatile uint32* const E_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x6C);
		volatile uint32* const BDMADR							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x70);
		volatile uint32* const F_BDUPDR						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x74);
		volatile uint32* const ADC_ER							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x78);
		volatile uint32* const ADC_UR							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x7C);
		volatile uint32* const ADC_PS1						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x80);
		volatile uint32* const ADC_PS2						= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x84);
		volatile uint32* const FLTIN3							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x88);
		volatile uint32* const FLTIN4							= (volatile uint32* const) (BASE::HR_TIMER_COMMON + 0x8C);
		
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
			volatile uint32* const CR2								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x6C);
			volatile uint32* const EEF3								= (volatile uint32* const) (BASE::HR_TIMER_A + 0x70);
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
			volatile uint32* const CR2								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x6C);
			volatile uint32* const EEF3								= (volatile uint32* const) (BASE::HR_TIMER_B + 0x70);
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
			volatile uint32* const CR2								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x6C);
			volatile uint32* const EEF3								= (volatile uint32* const) (BASE::HR_TIMER_C + 0x70);
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
			volatile uint32* const CR2								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x6C);
			volatile uint32* const EEF3								= (volatile uint32* const) (BASE::HR_TIMER_D + 0x70);
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
			volatile uint32* const CR2								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x6C);
			volatile uint32* const EEF3								= (volatile uint32* const) (BASE::HR_TIMER_E + 0x70);
		};
		
		namespace F
		{
			volatile uint32* const CR									= (volatile uint32* const) (BASE::HR_TIMER_F + 0x00);
			volatile uint32* const ISR								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x04);
			volatile uint32* const ICR								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x08);
			volatile uint32* const DIER								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x0C);
			volatile uint32* const CNT								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x10);
			volatile uint32* const PER								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x14);
			volatile uint32* const REP								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x18);
			volatile uint32* const CMP1								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x1C);
			volatile uint32* const CMP1C							= (volatile uint32* const) (BASE::HR_TIMER_F + 0x20);
			volatile uint32* const CMP2								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x24);
			volatile uint32* const CMP3								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x28);
			volatile uint32* const CMP4								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x2C);
			volatile uint32* const CPT1								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x30);
			volatile uint32* const CPT2								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x34);
			volatile uint32* const DT									= (volatile uint32* const) (BASE::HR_TIMER_F + 0x38);
			volatile uint32* const SET1								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x3C);
			volatile uint32* const RST1								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x40);
			volatile uint32* const SET2								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x44);
			volatile uint32* const RST2								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x48);
			volatile uint32* const EEF1								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x4C);
			volatile uint32* const EEF2								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x50);
			volatile uint32* const RST								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x54);
			volatile uint32* const CHP								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x58);
			volatile uint32* const CPT1CR							= (volatile uint32* const) (BASE::HR_TIMER_F + 0x5C);
			volatile uint32* const CPT2CR							= (volatile uint32* const) (BASE::HR_TIMER_F + 0x60);
			volatile uint32* const OUT								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x64);
			volatile uint32* const FLT								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x68);
			volatile uint32* const CR2								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x6C);
			volatile uint32* const EEF3								= (volatile uint32* const) (BASE::HR_TIMER_F + 0x70);
		};
	};
	
	
	
	
	
	namespace DMA_1
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::DMA_1 + 0x00);
		volatile uint32* const IFCR									= (volatile uint32* const) (BASE::DMA_1 + 0x04);
		
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x08);
		volatile uint32* const CH0_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x0C);
		volatile uint32* const CH0_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x10);
		volatile uint32* const CH0_MAR							= (volatile uint32* const) (BASE::DMA_1 + 0x14);
		
		volatile uint32* const CH1_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x1C);
		volatile uint32* const CH1_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x20);
		volatile uint32* const CH1_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x24);
		volatile uint32* const CH1_MAR							= (volatile uint32* const) (BASE::DMA_1 + 0x28);
		
		volatile uint32* const CH2_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x30);
		volatile uint32* const CH2_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x34);
		volatile uint32* const CH2_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x38);
		volatile uint32* const CH2_MAR							= (volatile uint32* const) (BASE::DMA_1 + 0x3C);
		
		volatile uint32* const CH3_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x44);
		volatile uint32* const CH3_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x48);
		volatile uint32* const CH3_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x4C);
		volatile uint32* const CH3_MAR							= (volatile uint32* const) (BASE::DMA_1 + 0x50);
		
		volatile uint32* const CH4_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x58);
		volatile uint32* const CH4_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x5C);
		volatile uint32* const CH4_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x60);
		volatile uint32* const CH4_MAR							= (volatile uint32* const) (BASE::DMA_1 + 0x64);
		
		volatile uint32* const CH5_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x6C);
		volatile uint32* const CH5_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x70);
		volatile uint32* const CH5_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x74);
		volatile uint32* const CH5_MAR							= (volatile uint32* const) (BASE::DMA_1 + 0x78);
		
		volatile uint32* const CH6_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x80);
		volatile uint32* const CH6_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x84);
		volatile uint32* const CH6_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x88);
		volatile uint32* const CH6_MAR							= (volatile uint32* const) (BASE::DMA_1 + 0x8C);
		
		volatile uint32* const CH7_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x94);
		volatile uint32* const CH7_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x98);
		volatile uint32* const CH7_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x9C);
		volatile uint32* const CH7_MAR							= (volatile uint32* const) (BASE::DMA_1 + 0xA0);
	};
	
	namespace DMA_2
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::DMA_2 + 0x00);
		volatile uint32* const IFCR									= (volatile uint32* const) (BASE::DMA_2 + 0x04);
		
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x08);
		volatile uint32* const CH0_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x0C);
		volatile uint32* const CH0_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x10);
		volatile uint32* const CH0_MAR							= (volatile uint32* const) (BASE::DMA_2 + 0x14);
		
		volatile uint32* const CH1_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x1C);
		volatile uint32* const CH1_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x20);
		volatile uint32* const CH1_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x24);
		volatile uint32* const CH1_MAR							= (volatile uint32* const) (BASE::DMA_2 + 0x28);
		
		volatile uint32* const CH2_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x30);
		volatile uint32* const CH2_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x34);
		volatile uint32* const CH2_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x38);
		volatile uint32* const CH2_MAR							= (volatile uint32* const) (BASE::DMA_2 + 0x3C);
		
		volatile uint32* const CH3_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x44);
		volatile uint32* const CH3_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x48);
		volatile uint32* const CH3_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x4C);
		volatile uint32* const CH3_MAR							= (volatile uint32* const) (BASE::DMA_2 + 0x50);
		
		volatile uint32* const CH4_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x58);
		volatile uint32* const CH4_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x5C);
		volatile uint32* const CH4_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x60);
		volatile uint32* const CH4_MAR							= (volatile uint32* const) (BASE::DMA_2 + 0x64);
		
		volatile uint32* const CH5_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x6C);
		volatile uint32* const CH5_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x70);
		volatile uint32* const CH5_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x74);
		volatile uint32* const CH5_MAR							= (volatile uint32* const) (BASE::DMA_2 + 0x78);
		
		volatile uint32* const CH6_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x80);
		volatile uint32* const CH6_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x84);
		volatile uint32* const CH6_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x88);
		volatile uint32* const CH6_MAR							= (volatile uint32* const) (BASE::DMA_2 + 0x8C);
		
		volatile uint32* const CH7_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x94);
		volatile uint32* const CH7_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x98);
		volatile uint32* const CH7_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x9C);
		volatile uint32* const CH7_MAR							= (volatile uint32* const) (BASE::DMA_2 + 0xA0);
	};
	
	namespace DMAMUX
	{
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMAMUX + 0x000);
		volatile uint32* const CH1_CR								= (volatile uint32* const) (BASE::DMAMUX + 0x004);
		volatile uint32* const CH2_CR								= (volatile uint32* const) (BASE::DMAMUX + 0x008);
		volatile uint32* const CH3_CR								= (volatile uint32* const) (BASE::DMAMUX + 0x00C);
		volatile uint32* const CH4_CR								= (volatile uint32* const) (BASE::DMAMUX + 0x010);
		volatile uint32* const CH5_CR								= (volatile uint32* const) (BASE::DMAMUX + 0x014);
		volatile uint32* const CH6_CR								= (volatile uint32* const) (BASE::DMAMUX + 0x018);
		volatile uint32* const CH7_CR								= (volatile uint32* const) (BASE::DMAMUX + 0x01C);
		volatile uint32* const CH8_CR								= (volatile uint32* const) (BASE::DMAMUX + 0x020);
		volatile uint32* const CH9_CR								= (volatile uint32* const) (BASE::DMAMUX + 0x024);
		volatile uint32* const CH10_CR							= (volatile uint32* const) (BASE::DMAMUX + 0x028);
		volatile uint32* const CH11_CR							= (volatile uint32* const) (BASE::DMAMUX + 0x02C);
		volatile uint32* const CH12_CR							= (volatile uint32* const) (BASE::DMAMUX + 0x030);
		volatile uint32* const CH13_CR							= (volatile uint32* const) (BASE::DMAMUX + 0x034);
		volatile uint32* const CH14_CR							= (volatile uint32* const) (BASE::DMAMUX + 0x038);
		volatile uint32* const CH15_CR							= (volatile uint32* const) (BASE::DMAMUX + 0x03C);
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::DMAMUX + 0x080);
		volatile uint32* const CFR									= (volatile uint32* const) (BASE::DMAMUX + 0x084);
		volatile uint32* const RG_CH0_CR						= (volatile uint32* const) (BASE::DMAMUX + 0x100);
		volatile uint32* const RG_CH1_CR						= (volatile uint32* const) (BASE::DMAMUX + 0x104);
		volatile uint32* const RG_CH2_CR						= (volatile uint32* const) (BASE::DMAMUX + 0x108);
		volatile uint32* const RG_CH3_CR						= (volatile uint32* const) (BASE::DMAMUX + 0x10C);
		volatile uint32* const RG_SR								= (volatile uint32* const) (BASE::DMAMUX + 0x140);
		volatile uint32* const RG_CFR								= (volatile uint32* const) (BASE::DMAMUX + 0x144);
	};
	
	namespace CORDIC
	{
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::CORDIC + 0x00);
		volatile uint32* const WDATA								= (volatile uint32* const) (BASE::CORDIC + 0x04);
		volatile uint32* const RDATA								= (volatile uint32* const) (BASE::CORDIC + 0x08);
	};
	
	namespace RCC
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::RCC + 0x00);
		volatile uint32* const ICSCR								= (volatile uint32* const) (BASE::RCC + 0x04);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::RCC + 0x08);
		volatile uint32* const PLL_CFGR							= (volatile uint32* const) (BASE::RCC + 0x0C);
		volatile uint32* const CIER									= (volatile uint32* const) (BASE::RCC + 0x18);
		volatile uint32* const CIFR									= (volatile uint32* const) (BASE::RCC + 0x1C);
		volatile uint32* const CICR									= (volatile uint32* const) (BASE::RCC + 0x20);
		volatile uint32* const AHB1_RSTR						= (volatile uint32* const) (BASE::RCC + 0x28);
		volatile uint32* const AHB2_RSTR						= (volatile uint32* const) (BASE::RCC + 0x2C);
		volatile uint32* const AHB3_RSTR						= (volatile uint32* const) (BASE::RCC + 0x30);
		volatile uint32* const APB1_RSTR1						= (volatile uint32* const) (BASE::RCC + 0x38);
		volatile uint32* const APB1_RSTR2						= (volatile uint32* const) (BASE::RCC + 0x3C);
		volatile uint32* const APB2_RSTR						= (volatile uint32* const) (BASE::RCC + 0x40);
		volatile uint32* const AHB1_ENR							= (volatile uint32* const) (BASE::RCC + 0x48);
		volatile uint32* const AHB2_ENR							= (volatile uint32* const) (BASE::RCC + 0x4C);
		volatile uint32* const AHB3_ENR							= (volatile uint32* const) (BASE::RCC + 0x50);
		volatile uint32* const APB1_ENR1						= (volatile uint32* const) (BASE::RCC + 0x58);
		volatile uint32* const APB1_ENR2						= (volatile uint32* const) (BASE::RCC + 0x5C);
		volatile uint32* const APB2_ENR							= (volatile uint32* const) (BASE::RCC + 0x60);
		volatile uint32* const AHB1_SM_ENR					= (volatile uint32* const) (BASE::RCC + 0x68);
		volatile uint32* const AHB2_SM_ENR					= (volatile uint32* const) (BASE::RCC + 0x6C);
		volatile uint32* const AHB3_SM_ENR					= (volatile uint32* const) (BASE::RCC + 0x70);
		volatile uint32* const APB1_SM_ENR1					= (volatile uint32* const) (BASE::RCC + 0x78);
		volatile uint32* const APB1_SM_ENR2					= (volatile uint32* const) (BASE::RCC + 0x7C);
		volatile uint32* const APB2_SM_ENR					= (volatile uint32* const) (BASE::RCC + 0x80);
		volatile uint32* const CCIPR								= (volatile uint32* const) (BASE::RCC + 0x88);
		volatile uint32* const BDCR									= (volatile uint32* const) (BASE::RCC + 0x90);
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::RCC + 0x94);
		volatile uint32* const CRRCR								= (volatile uint32* const) (BASE::RCC + 0x98);
		volatile uint32* const CCIPR2								= (volatile uint32* const) (BASE::RCC + 0x9C);
	};
	
	namespace FMAC
	{
		volatile uint32* const X1BUFCFG							= (volatile uint32* const) (BASE::FMAC + 0x00);
		volatile uint32* const X2BUFCFG							= (volatile uint32* const) (BASE::FMAC + 0x04);
		volatile uint32* const YBUFCFG							= (volatile uint32* const) (BASE::FMAC + 0x08);
		volatile uint32* const PARAM								= (volatile uint32* const) (BASE::FMAC + 0x0C);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::FMAC + 0x10);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::FMAC + 0x14);
		volatile uint32* const WDATA								= (volatile uint32* const) (BASE::FMAC + 0x18);
		volatile uint32* const RDATA								= (volatile uint32* const) (BASE::FMAC + 0x1C);
	};
	
	namespace FLASH
	{
		volatile uint32* const ACR									= (volatile uint32* const) (BASE::FLASH + 0x00);
		volatile uint32* const PD_KEY								= (volatile uint32* const) (BASE::FLASH + 0x04);
		volatile uint32* const KEY									= (volatile uint32* const) (BASE::FLASH + 0x08);
		volatile uint32* const OPT_KEY							= (volatile uint32* const) (BASE::FLASH + 0x0C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::FLASH + 0x10);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::FLASH + 0x14);
		volatile uint32* const ECCR									= (volatile uint32* const) (BASE::FLASH + 0x18);
		volatile uint32* const OPTR									= (volatile uint32* const) (BASE::FLASH + 0x20);
		volatile uint32* const PCROP1SR							= (volatile uint32* const) (BASE::FLASH + 0x24);
		volatile uint32* const PCROP1ER							= (volatile uint32* const) (BASE::FLASH + 0x28);
		volatile uint32* const WRP1AR								= (volatile uint32* const) (BASE::FLASH + 0x2C);
		volatile uint32* const WRP1BR								= (volatile uint32* const) (BASE::FLASH + 0x30);
		volatile uint32* const PCROP2SR							= (volatile uint32* const) (BASE::FLASH + 0x44);
		volatile uint32* const PCROP2ER							= (volatile uint32* const) (BASE::FLASH + 0x48);
		volatile uint32* const WRP2AR								= (volatile uint32* const) (BASE::FLASH + 0x4C);
		volatile uint32* const WRP2BR								= (volatile uint32* const) (BASE::FLASH + 0x50);
		volatile uint32* const SEC1R								= (volatile uint32* const) (BASE::FLASH + 0x70);
		volatile uint32* const SEC2R								= (volatile uint32* const) (BASE::FLASH + 0x74);
	};
	
	namespace CRC
	{
		volatile uint32* const DR										= (volatile uint32* const) (BASE::CRC + 0x00);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::CRC + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::CRC + 0x08);
		volatile uint32* const INIT									= (volatile uint32* const) (BASE::CRC + 0x10);
		volatile uint32* const POL									= (volatile uint32* const) (BASE::CRC + 0x14);
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
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_A + 0x28);
	};
	
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
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_B + 0x28);
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
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_C + 0x28);
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
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_D + 0x28);
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
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_E + 0x28);
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
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_F + 0x28);
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
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_G + 0x28);
	};
	
	namespace ADC_1
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC_1 + 0x00);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC_1 + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::ADC_1 + 0x08);
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::ADC_1 + 0x0C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC_1 + 0x10);
		volatile uint32* const SMPR1								= (volatile uint32* const) (BASE::ADC_1 + 0x14);
		volatile uint32* const SMPR2								= (volatile uint32* const) (BASE::ADC_1 + 0x18);
		volatile uint32* const TR1									= (volatile uint32* const) (BASE::ADC_1 + 0x20);
		volatile uint32* const TR2									= (volatile uint32* const) (BASE::ADC_1 + 0x24);
		volatile uint32* const TR3									= (volatile uint32* const) (BASE::ADC_1 + 0x28);
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
		volatile uint32* const DIFSEL								= (volatile uint32* const) (BASE::ADC_1 + 0xB0);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC_1 + 0xB4);
		volatile uint32* const GCOMP								= (volatile uint32* const) (BASE::ADC_1 + 0xC0);
	};
	
	namespace ADC_2
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC_2 + 0x00);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC_2 + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::ADC_2 + 0x08);
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::ADC_2 + 0x0C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC_2 + 0x10);
		volatile uint32* const SMPR1								= (volatile uint32* const) (BASE::ADC_2 + 0x14);
		volatile uint32* const SMPR2								= (volatile uint32* const) (BASE::ADC_2 + 0x18);
		volatile uint32* const TR1									= (volatile uint32* const) (BASE::ADC_2 + 0x20);
		volatile uint32* const TR2									= (volatile uint32* const) (BASE::ADC_2 + 0x24);
		volatile uint32* const TR3									= (volatile uint32* const) (BASE::ADC_2 + 0x28);
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
		volatile uint32* const DIFSEL								= (volatile uint32* const) (BASE::ADC_2 + 0xB0);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC_2 + 0xB4);
		volatile uint32* const GCOMP								= (volatile uint32* const) (BASE::ADC_2 + 0xC0);
	};
	
	namespace ADC_1_2_COMMON
	{
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::ADC_1_2_COMMON + 0x00);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::ADC_1_2_COMMON + 0x08);
		volatile uint32* const CDR									= (volatile uint32* const) (BASE::ADC_1_2_COMMON + 0x0C);
	};
	
	namespace ADC_3
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC_3 + 0x00);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC_3 + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::ADC_3 + 0x08);
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::ADC_3 + 0x0C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC_3 + 0x10);
		volatile uint32* const SMPR1								= (volatile uint32* const) (BASE::ADC_3 + 0x14);
		volatile uint32* const SMPR2								= (volatile uint32* const) (BASE::ADC_3 + 0x18);
		volatile uint32* const TR1									= (volatile uint32* const) (BASE::ADC_3 + 0x20);
		volatile uint32* const TR2									= (volatile uint32* const) (BASE::ADC_3 + 0x24);
		volatile uint32* const TR3									= (volatile uint32* const) (BASE::ADC_3 + 0x28);
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
		volatile uint32* const DIFSEL								= (volatile uint32* const) (BASE::ADC_3 + 0xB0);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC_3 + 0xB4);
		volatile uint32* const GCOMP								= (volatile uint32* const) (BASE::ADC_3 + 0xC0);
	};
	
	namespace ADC_4
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC_4 + 0x00);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC_4 + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::ADC_4 + 0x08);
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::ADC_4 + 0x0C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC_4 + 0x10);
		volatile uint32* const SMPR1								= (volatile uint32* const) (BASE::ADC_4 + 0x14);
		volatile uint32* const SMPR2								= (volatile uint32* const) (BASE::ADC_4 + 0x18);
		volatile uint32* const TR1									= (volatile uint32* const) (BASE::ADC_4 + 0x20);
		volatile uint32* const TR2									= (volatile uint32* const) (BASE::ADC_4 + 0x24);
		volatile uint32* const TR3									= (volatile uint32* const) (BASE::ADC_4 + 0x28);
		volatile uint32* const SQR1									= (volatile uint32* const) (BASE::ADC_4 + 0x30);
		volatile uint32* const SQR2									= (volatile uint32* const) (BASE::ADC_4 + 0x34);
		volatile uint32* const SQR3									= (volatile uint32* const) (BASE::ADC_4 + 0x38);
		volatile uint32* const SQR4									= (volatile uint32* const) (BASE::ADC_4 + 0x3C);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::ADC_4 + 0x40);
		volatile uint32* const JSQR									= (volatile uint32* const) (BASE::ADC_4 + 0x4C);
		volatile uint32* const OFR1									= (volatile uint32* const) (BASE::ADC_4 + 0x60);
		volatile uint32* const OFR2									= (volatile uint32* const) (BASE::ADC_4 + 0x64);
		volatile uint32* const OFR3									= (volatile uint32* const) (BASE::ADC_4 + 0x68);
		volatile uint32* const OFR4									= (volatile uint32* const) (BASE::ADC_4 + 0x6C);
		volatile uint32* const JDR1									= (volatile uint32* const) (BASE::ADC_4 + 0x80);
		volatile uint32* const JDR2									= (volatile uint32* const) (BASE::ADC_4 + 0x84);
		volatile uint32* const JDR3									= (volatile uint32* const) (BASE::ADC_4 + 0x88);
		volatile uint32* const JDR4									= (volatile uint32* const) (BASE::ADC_4 + 0x8C);
		volatile uint32* const AWD2CR								= (volatile uint32* const) (BASE::ADC_4 + 0xA0);
		volatile uint32* const AWD3CR								= (volatile uint32* const) (BASE::ADC_4 + 0xA4);
		volatile uint32* const DIFSEL								= (volatile uint32* const) (BASE::ADC_4 + 0xB0);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC_4 + 0xB4);
		volatile uint32* const GCOMP								= (volatile uint32* const) (BASE::ADC_4 + 0xC0);
	};
	
	namespace ADC_5
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC_5 + 0x00);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC_5 + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::ADC_5 + 0x08);
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::ADC_5 + 0x0C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC_5 + 0x10);
		volatile uint32* const SMPR1								= (volatile uint32* const) (BASE::ADC_5 + 0x14);
		volatile uint32* const SMPR2								= (volatile uint32* const) (BASE::ADC_5 + 0x18);
		volatile uint32* const TR1									= (volatile uint32* const) (BASE::ADC_5 + 0x20);
		volatile uint32* const TR2									= (volatile uint32* const) (BASE::ADC_5 + 0x24);
		volatile uint32* const TR3									= (volatile uint32* const) (BASE::ADC_5 + 0x28);
		volatile uint32* const SQR1									= (volatile uint32* const) (BASE::ADC_5 + 0x30);
		volatile uint32* const SQR2									= (volatile uint32* const) (BASE::ADC_5 + 0x34);
		volatile uint32* const SQR3									= (volatile uint32* const) (BASE::ADC_5 + 0x38);
		volatile uint32* const SQR4									= (volatile uint32* const) (BASE::ADC_5 + 0x3C);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::ADC_5 + 0x40);
		volatile uint32* const JSQR									= (volatile uint32* const) (BASE::ADC_5 + 0x4C);
		volatile uint32* const OFR1									= (volatile uint32* const) (BASE::ADC_5 + 0x60);
		volatile uint32* const OFR2									= (volatile uint32* const) (BASE::ADC_5 + 0x64);
		volatile uint32* const OFR3									= (volatile uint32* const) (BASE::ADC_5 + 0x68);
		volatile uint32* const OFR4									= (volatile uint32* const) (BASE::ADC_5 + 0x6C);
		volatile uint32* const JDR1									= (volatile uint32* const) (BASE::ADC_5 + 0x80);
		volatile uint32* const JDR2									= (volatile uint32* const) (BASE::ADC_5 + 0x84);
		volatile uint32* const JDR3									= (volatile uint32* const) (BASE::ADC_5 + 0x88);
		volatile uint32* const JDR4									= (volatile uint32* const) (BASE::ADC_5 + 0x8C);
		volatile uint32* const AWD2CR								= (volatile uint32* const) (BASE::ADC_5 + 0xA0);
		volatile uint32* const AWD3CR								= (volatile uint32* const) (BASE::ADC_5 + 0xA4);
		volatile uint32* const DIFSEL								= (volatile uint32* const) (BASE::ADC_5 + 0xB0);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC_5 + 0xB4);
		volatile uint32* const GCOMP								= (volatile uint32* const) (BASE::ADC_5 + 0xC0);
	};
	
	namespace ADC_3_4_5_COMMON
	{
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::ADC_3_4_5_COMMON + 0x00);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::ADC_3_4_5_COMMON + 0x08);
		volatile uint32* const CDR									= (volatile uint32* const) (BASE::ADC_3_4_5_COMMON + 0x0C);
	};
	
	namespace DAC_1
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::DAC_1 + 0x00);
		volatile uint32* const SWTRGR								= (volatile uint32* const) (BASE::DAC_1 + 0x04);
		volatile uint32* const DHR12R1							= (volatile uint32* const) (BASE::DAC_1 + 0x08);
		volatile uint32* const DHR12L1							= (volatile uint32* const) (BASE::DAC_1 + 0x0C);
		volatile uint32* const DHR8R1								= (volatile uint32* const) (BASE::DAC_1 + 0x10);
		volatile uint32* const DHR12R2							= (volatile uint32* const) (BASE::DAC_1 + 0x14);
		volatile uint32* const DHR12L2							= (volatile uint32* const) (BASE::DAC_1 + 0x18);
		volatile uint32* const DHR8R2								= (volatile uint32* const) (BASE::DAC_1 + 0x1C);
		volatile uint32* const DHR12RD							= (volatile uint32* const) (BASE::DAC_1 + 0x20);
		volatile uint32* const DHR12LD							= (volatile uint32* const) (BASE::DAC_1 + 0x24);
		volatile uint32* const DHR8RD								= (volatile uint32* const) (BASE::DAC_1 + 0x28);
		volatile uint32* const DOR1									= (volatile uint32* const) (BASE::DAC_1 + 0x2C);
		volatile uint32* const DOR2									= (volatile uint32* const) (BASE::DAC_1 + 0x30);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::DAC_1 + 0x34);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::DAC_1 + 0x38);
		volatile uint32* const MCR									= (volatile uint32* const) (BASE::DAC_1 + 0x3C);
		volatile uint32* const SHSR1								= (volatile uint32* const) (BASE::DAC_1 + 0x40);
		volatile uint32* const SHSR2								= (volatile uint32* const) (BASE::DAC_1 + 0x44);
		volatile uint32* const SHHR									= (volatile uint32* const) (BASE::DAC_1 + 0x48);
		volatile uint32* const SHRR									= (volatile uint32* const) (BASE::DAC_1 + 0x4C);
		volatile uint32* const STR1									= (volatile uint32* const) (BASE::DAC_1 + 0x58);
		volatile uint32* const STR2									= (volatile uint32* const) (BASE::DAC_1 + 0x5C);
		volatile uint32* const STMODR								= (volatile uint32* const) (BASE::DAC_1 + 0x60);
	};
	
	namespace DAC_2
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::DAC_2 + 0x00);
		volatile uint32* const SWTRGR								= (volatile uint32* const) (BASE::DAC_2 + 0x04);
		volatile uint32* const DHR12R1							= (volatile uint32* const) (BASE::DAC_2 + 0x08);
		volatile uint32* const DHR12L1							= (volatile uint32* const) (BASE::DAC_2 + 0x0C);
		volatile uint32* const DHR8R1								= (volatile uint32* const) (BASE::DAC_2 + 0x10);
		volatile uint32* const DHR12R2							= (volatile uint32* const) (BASE::DAC_2 + 0x14);
		volatile uint32* const DHR12L2							= (volatile uint32* const) (BASE::DAC_2 + 0x18);
		volatile uint32* const DHR8R2								= (volatile uint32* const) (BASE::DAC_2 + 0x1C);
		volatile uint32* const DHR12RD							= (volatile uint32* const) (BASE::DAC_2 + 0x20);
		volatile uint32* const DHR12LD							= (volatile uint32* const) (BASE::DAC_2 + 0x24);
		volatile uint32* const DHR8RD								= (volatile uint32* const) (BASE::DAC_2 + 0x28);
		volatile uint32* const DOR1									= (volatile uint32* const) (BASE::DAC_2 + 0x2C);
		volatile uint32* const DOR2									= (volatile uint32* const) (BASE::DAC_2 + 0x30);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::DAC_2 + 0x34);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::DAC_2 + 0x38);
		volatile uint32* const MCR									= (volatile uint32* const) (BASE::DAC_2 + 0x3C);
		volatile uint32* const SHSR1								= (volatile uint32* const) (BASE::DAC_2 + 0x40);
		volatile uint32* const SHSR2								= (volatile uint32* const) (BASE::DAC_2 + 0x44);
		volatile uint32* const SHHR									= (volatile uint32* const) (BASE::DAC_2 + 0x48);
		volatile uint32* const SHRR									= (volatile uint32* const) (BASE::DAC_2 + 0x4C);
		volatile uint32* const STR1									= (volatile uint32* const) (BASE::DAC_2 + 0x58);
		volatile uint32* const STR2									= (volatile uint32* const) (BASE::DAC_2 + 0x5C);
		volatile uint32* const STMODR								= (volatile uint32* const) (BASE::DAC_2 + 0x60);
	};
	
	namespace DAC_3
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::DAC_3 + 0x00);
		volatile uint32* const SWTRGR								= (volatile uint32* const) (BASE::DAC_3 + 0x04);
		volatile uint32* const DHR12R1							= (volatile uint32* const) (BASE::DAC_3 + 0x08);
		volatile uint32* const DHR12L1							= (volatile uint32* const) (BASE::DAC_3 + 0x0C);
		volatile uint32* const DHR8R1								= (volatile uint32* const) (BASE::DAC_3 + 0x10);
		volatile uint32* const DHR12R2							= (volatile uint32* const) (BASE::DAC_3 + 0x14);
		volatile uint32* const DHR12L2							= (volatile uint32* const) (BASE::DAC_3 + 0x18);
		volatile uint32* const DHR8R2								= (volatile uint32* const) (BASE::DAC_3 + 0x1C);
		volatile uint32* const DHR12RD							= (volatile uint32* const) (BASE::DAC_3 + 0x20);
		volatile uint32* const DHR12LD							= (volatile uint32* const) (BASE::DAC_3 + 0x24);
		volatile uint32* const DHR8RD								= (volatile uint32* const) (BASE::DAC_3 + 0x28);
		volatile uint32* const DOR1									= (volatile uint32* const) (BASE::DAC_3 + 0x2C);
		volatile uint32* const DOR2									= (volatile uint32* const) (BASE::DAC_3 + 0x30);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::DAC_3 + 0x34);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::DAC_3 + 0x38);
		volatile uint32* const MCR									= (volatile uint32* const) (BASE::DAC_3 + 0x3C);
		volatile uint32* const SHSR1								= (volatile uint32* const) (BASE::DAC_3 + 0x40);
		volatile uint32* const SHSR2								= (volatile uint32* const) (BASE::DAC_3 + 0x44);
		volatile uint32* const SHHR									= (volatile uint32* const) (BASE::DAC_3 + 0x48);
		volatile uint32* const SHRR									= (volatile uint32* const) (BASE::DAC_3 + 0x4C);
		volatile uint32* const STR1									= (volatile uint32* const) (BASE::DAC_3 + 0x58);
		volatile uint32* const STR2									= (volatile uint32* const) (BASE::DAC_3 + 0x5C);
		volatile uint32* const STMODR								= (volatile uint32* const) (BASE::DAC_3 + 0x60);
	};
	
	namespace DAC_4
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::DAC_4 + 0x00);
		volatile uint32* const SWTRGR								= (volatile uint32* const) (BASE::DAC_4 + 0x04);
		volatile uint32* const DHR12R1							= (volatile uint32* const) (BASE::DAC_4 + 0x08);
		volatile uint32* const DHR12L1							= (volatile uint32* const) (BASE::DAC_4 + 0x0C);
		volatile uint32* const DHR8R1								= (volatile uint32* const) (BASE::DAC_4 + 0x10);
		volatile uint32* const DHR12R2							= (volatile uint32* const) (BASE::DAC_4 + 0x14);
		volatile uint32* const DHR12L2							= (volatile uint32* const) (BASE::DAC_4 + 0x18);
		volatile uint32* const DHR8R2								= (volatile uint32* const) (BASE::DAC_4 + 0x1C);
		volatile uint32* const DHR12RD							= (volatile uint32* const) (BASE::DAC_4 + 0x20);
		volatile uint32* const DHR12LD							= (volatile uint32* const) (BASE::DAC_4 + 0x24);
		volatile uint32* const DHR8RD								= (volatile uint32* const) (BASE::DAC_4 + 0x28);
		volatile uint32* const DOR1									= (volatile uint32* const) (BASE::DAC_4 + 0x2C);
		volatile uint32* const DOR2									= (volatile uint32* const) (BASE::DAC_4 + 0x30);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::DAC_4 + 0x34);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::DAC_4 + 0x38);
		volatile uint32* const MCR									= (volatile uint32* const) (BASE::DAC_4 + 0x3C);
		volatile uint32* const SHSR1								= (volatile uint32* const) (BASE::DAC_4 + 0x40);
		volatile uint32* const SHSR2								= (volatile uint32* const) (BASE::DAC_4 + 0x44);
		volatile uint32* const SHHR									= (volatile uint32* const) (BASE::DAC_4 + 0x48);
		volatile uint32* const SHRR									= (volatile uint32* const) (BASE::DAC_4 + 0x4C);
		volatile uint32* const STR1									= (volatile uint32* const) (BASE::DAC_4 + 0x58);
		volatile uint32* const STR2									= (volatile uint32* const) (BASE::DAC_4 + 0x5C);
		volatile uint32* const STMODR								= (volatile uint32* const) (BASE::DAC_4 + 0x60);
	};
	
	namespace AES
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::AES + 0x00);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::AES + 0x04);
		volatile uint32* const DIN									= (volatile uint32* const) (BASE::AES + 0x08);
		volatile uint32* const DOUT									= (volatile uint32* const) (BASE::AES + 0x0C);
		volatile uint32* const KEY0									= (volatile uint32* const) (BASE::AES + 0x10);
		volatile uint32* const KEY1									= (volatile uint32* const) (BASE::AES + 0x14);
		volatile uint32* const KEY2									= (volatile uint32* const) (BASE::AES + 0x18);
		volatile uint32* const KEY3									= (volatile uint32* const) (BASE::AES + 0x1C);
		volatile uint32* const IVR0									= (volatile uint32* const) (BASE::AES + 0x20);
		volatile uint32* const IVR1									= (volatile uint32* const) (BASE::AES + 0x24);
		volatile uint32* const IVR2									= (volatile uint32* const) (BASE::AES + 0x28);
		volatile uint32* const IVR3									= (volatile uint32* const) (BASE::AES + 0x2C);
		volatile uint32* const KEY4									= (volatile uint32* const) (BASE::AES + 0x30);
		volatile uint32* const KEY5									= (volatile uint32* const) (BASE::AES + 0x34);
		volatile uint32* const KEY6									= (volatile uint32* const) (BASE::AES + 0x38);
		volatile uint32* const KEY7									= (volatile uint32* const) (BASE::AES + 0x3C);
		volatile uint32* const SUSP0								= (volatile uint32* const) (BASE::AES + 0x40);
		volatile uint32* const SUSP1								= (volatile uint32* const) (BASE::AES + 0x44);
		volatile uint32* const SUSP2								= (volatile uint32* const) (BASE::AES + 0x48);
		volatile uint32* const SUSP3								= (volatile uint32* const) (BASE::AES + 0x4C);
		volatile uint32* const SUSP4								= (volatile uint32* const) (BASE::AES + 0x50);
		volatile uint32* const SUSP5								= (volatile uint32* const) (BASE::AES + 0x54);
		volatile uint32* const SUSP6								= (volatile uint32* const) (BASE::AES + 0x58);
		volatile uint32* const SUSP7								= (volatile uint32* const) (BASE::AES + 0x5C);
	}
	
	namespace RNG
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::RNG + 0x00);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::RNG + 0x04);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::RNG + 0x08);
	}
	
	
	
	
	
	namespace FSMC
	{
		volatile uint32* const BCR1									= (volatile uint32* const) (BASE::FSMC + 0x000);
		volatile uint32* const BTR1									= (volatile uint32* const) (BASE::FSMC + 0x004);
		volatile uint32* const BCR2									= (volatile uint32* const) (BASE::FSMC + 0x008);
		volatile uint32* const BTR2									= (volatile uint32* const) (BASE::FSMC + 0x00C);
		volatile uint32* const BCR3									= (volatile uint32* const) (BASE::FSMC + 0x010);
		volatile uint32* const BTR3									= (volatile uint32* const) (BASE::FSMC + 0x014);
		volatile uint32* const BCR4									= (volatile uint32* const) (BASE::FSMC + 0x018);
		volatile uint32* const BTR4									= (volatile uint32* const) (BASE::FSMC + 0x01C);
		volatile uint32* const PCSCNTR							= (volatile uint32* const) (BASE::FSMC + 0x020);
		volatile uint32* const PCR									= (volatile uint32* const) (BASE::FSMC + 0x080);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::FSMC + 0x084);
		volatile uint32* const PMEM									= (volatile uint32* const) (BASE::FSMC + 0x088);
		volatile uint32* const PATT									= (volatile uint32* const) (BASE::FSMC + 0x08C);
		volatile uint32* const ECCR									= (volatile uint32* const) (BASE::FSMC + 0x094);
		volatile uint32* const BWTR1								= (volatile uint32* const) (BASE::FSMC + 0x104);
		volatile uint32* const BWTR2								= (volatile uint32* const) (BASE::FSMC + 0x10C);
		volatile uint32* const BWTR3								= (volatile uint32* const) (BASE::FSMC + 0x114);
		volatile uint32* const BWTR4								= (volatile uint32* const) (BASE::FSMC + 0x11C);
	}
	
	namespace QUADSPI
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::QUADSPI + 0x00);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::QUADSPI + 0x04);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::QUADSPI + 0x08);
		volatile uint32* const FCR									= (volatile uint32* const) (BASE::QUADSPI + 0x0C);
		volatile uint32* const DLR									= (volatile uint32* const) (BASE::QUADSPI + 0x10);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::QUADSPI + 0x14);
		volatile uint32* const AR										= (volatile uint32* const) (BASE::QUADSPI + 0x18);
		volatile uint32* const ABR									= (volatile uint32* const) (BASE::QUADSPI + 0x1C);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::QUADSPI + 0x20);
		volatile uint32* const PSMKR								= (volatile uint32* const) (BASE::QUADSPI + 0x24);
		volatile uint32* const PSMAR								= (volatile uint32* const) (BASE::QUADSPI + 0x28);
		volatile uint32* const PIR									= (volatile uint32* const) (BASE::QUADSPI + 0x2C);
		volatile uint32* const LPTR									= (volatile uint32* const) (BASE::QUADSPI + 0x30);
	}
	
	
	
	
	
	namespace DBGMCU
	{
		volatile uint32* const IDC			        		= (volatile uint32* const) (BASE::DBGMCU + 0x00);
		volatile uint32* const CR			        			= (volatile uint32* const) (BASE::DBGMCU + 0x04);
		volatile uint32* const APB1_FZ1			        = (volatile uint32* const) (BASE::DBGMCU + 0x08);
		volatile uint32* const APB1_FZ2			        = (volatile uint32* const) (BASE::DBGMCU + 0x0C);
		volatile uint32* const APB2_FZ			        = (volatile uint32* const) (BASE::DBGMCU + 0x10);
	}
};