#pragma once

#include "cmos.hpp"





namespace Interrupt
{
	constexpr uint16 WWDG													= 16;
	constexpr uint16 PVM													= 17;
	constexpr uint16 RTC_TAMPER_STAMP_CSS_LSE			= 18;
	constexpr uint16 WKUP													= 19;
	constexpr uint16 FLASH												= 20;
	constexpr uint16 RCC													= 21;
	constexpr uint16 EXTI_0												= 22;
	constexpr uint16 EXTI_1												= 23;
	constexpr uint16 EXTI_2												= 24;
	constexpr uint16 EXTI_3												= 25;
	constexpr uint16 EXTI_4												= 26;
	constexpr uint16 DMA_1_CH0										= 27;
	constexpr uint16 DMA_1_CH1										= 28;
	constexpr uint16 DMA_1_CH2										= 29;
	constexpr uint16 DMA_1_CH3										= 30;
	constexpr uint16 DMA_1_CH4										= 31;
	constexpr uint16 DMA_1_CH5										= 32;
	constexpr uint16 DMA_1_CH6										= 33;
	constexpr uint16 ADC_1_2											= 34;
	constexpr uint16 CAN_1_TX											= 35;
	constexpr uint16 CAN_1_RX0										= 36;
	constexpr uint16 CAN_1_RX1										= 37;
	constexpr uint16 CAN_1_SCE										= 38;
	constexpr uint16 EXTI_9_TO_5									= 39;
	constexpr uint16 TIMER_1_BREAK_TIMER_15				= 40;
	constexpr uint16 TIMER_1_UPDATE_TIMER_16			= 41;
	constexpr uint16 TIMER_1_TRIGGER_COMMUTATION	= 42;
	constexpr uint16 TIMER_1_CAPTURE_COMPARE			= 43;
	constexpr uint16 TIMER_2											= 44;
	constexpr uint16 TIMER_3											= 45;
	
	constexpr uint16 I2C_1_EVENT									= 47;
	constexpr uint16 I2C_1_ERROR									= 48;
	constexpr uint16 I2C_2_EVENT									= 49;
	constexpr uint16 I2C_2_ERROR									= 50;
	constexpr uint16 SPI_1												= 51;
	constexpr uint16 SPI_2												= 52;
	constexpr uint16 USART_1											= 53;
	constexpr uint16 USART_2											= 54;
	constexpr uint16 USART_3											= 55;
	constexpr uint16 EXTI_15_TO_10								= 56;
	constexpr uint16 RTC_ALARM										= 57;
	
	
	
	
	
	
	
	constexpr uint16 SDMMC_1											= 65;
	
	constexpr uint16 SPI_3												= 67;
	constexpr uint16 UART_4												= 68;
	
	constexpr uint16 TIMER_6_DAC_UNDERRUN					= 70;
	
	constexpr uint16 DMA_2_CH0										= 72;
	constexpr uint16 DMA_2_CH1										= 73;
	constexpr uint16 DMA_2_CH2										= 74;
	constexpr uint16 DMA_2_CH3										= 75;
	constexpr uint16 DMA_2_CH4										= 76;
	constexpr uint16 DFSDM_1_FLT_0								= 77;
	constexpr uint16 DFSDM_1_FLT_1								= 78;
	
	constexpr uint16 COMP													= 80;
	constexpr uint16 LP_TIMER_1										= 81;
	constexpr uint16 LP_TIMER_2										= 82;
	
	constexpr uint16 DMA_2_CH5										= 84;
	constexpr uint16 DMA_2_CH6										= 85;
	constexpr uint16 LPUART_1											= 86;
	constexpr uint16 QUADSPI											= 87;
	constexpr uint16 I2C_3_EVENT									= 88;
	constexpr uint16 I2C_3_ERROR									= 89;
	constexpr uint16 SAI_1												= 90;
	
	
	constexpr uint16 TSC													= 93;
	
	constexpr uint16 AES													= 95;
	constexpr uint16 RNG													= 96;
	constexpr uint16 FPU													= 97;
	constexpr uint16 CRS													= 98;
	constexpr uint16 I2C_4_EVENT									= 99;
	constexpr uint16 I2C_4_ERROR									= 100;
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
		
		
		
		
		
		constexpr uint32 TIMER_2										= APB1 + 0x00000000;
		constexpr uint32 TIMER_3										= APB1 + 0x00000400;
		constexpr uint32 TIMER_6										= APB1 + 0x00001000;
		constexpr uint32 RTC												= APB1 + 0x00002800;
		constexpr uint32 WWDG												= APB1 + 0x00002C00;
		constexpr uint32 IWDG												= APB1 + 0x00003000;
		constexpr uint32 SPI_2											= APB1 + 0x00003800;
		constexpr uint32 SPI_3											= APB1 + 0x00003C00;
		constexpr uint32 USART_2										= APB1 + 0x00004400;
		constexpr uint32 USART_3										= APB1 + 0x00004800;
		constexpr uint32 USART_4										= APB1 + 0x00004C00;
		constexpr uint32 I2C_1											= APB1 + 0x00005400;
		constexpr uint32 I2C_2											= APB1 + 0x00005800;
		constexpr uint32 I2C_3											= APB1 + 0x00005C00;
		constexpr uint32 CRS												= APB1 + 0x00006000;
		constexpr uint32 CAN_1											= APB1 + 0x00006400;
		constexpr uint32 PWR												= APB1 + 0x00007000;
		constexpr uint32 DAC_1											= APB1 + 0x00007400;
		constexpr uint32 OPAMP											= APB1 + 0x00007800;
		constexpr uint32 LP_TIMER_1									= APB1 + 0x00007C00;
		constexpr uint32 LP_UART_1									= APB1 + 0x00008000;
		constexpr uint32 I2C_4											= APB1 + 0x00008400;
		constexpr uint32 LP_TIMER_2									= APB1 + 0x00009400;
		
		constexpr uint32 SYSCFG											= APB2 + 0x00000000;
		constexpr uint32 VREFBUF										= APB2 + 0x00000030;
		constexpr uint32 COMP												= APB2 + 0x00000200;
		constexpr uint32 EXTI												= APB2 + 0x00000400;
		constexpr uint32 FIREWALL										= APB2 + 0x00001C00;
		constexpr uint32 SDMMC_1										= APB2 + 0x00002800;
		constexpr uint32 TIMER_1										= APB2 + 0x00002C00;
		constexpr uint32 SPI_1											= APB2 + 0x00003000;
		constexpr uint32 USART_1										= APB2 + 0x00003800;
		constexpr uint32 TIMER_15										= APB2 + 0x00004000;
		constexpr uint32 TIMER_16										= APB2 + 0x00004400;
		constexpr uint32 SAI_1											= APB2 + 0x00005400;
		constexpr uint32 DFSDM_1										= APB2 + 0x00006000;
		
		constexpr uint32 DMA_1											= AHB1 + 0x00000000;
		constexpr uint32 DMA_2											= AHB1 + 0x00000400;
		constexpr uint32 RCC												= AHB1 + 0x00001000;
		constexpr uint32 FLASH				 							= AHB1 + 0x00002000;
		constexpr uint32 CRC												= AHB1 + 0x00003000;
		constexpr uint32 TSC												= AHB1 + 0x00004000;

		constexpr uint32 GPIO_A									    = AHB2 + 0x00000000;
		constexpr uint32 GPIO_B									    = AHB2 + 0x00000400;
		constexpr uint32 GPIO_C									    = AHB2 + 0x00000800;
		constexpr uint32 GPIO_D									    = AHB2 + 0x00000C00;
		constexpr uint32 GPIO_H									    = AHB2 + 0x00001C00;
		constexpr uint32 ADC_1									    = AHB2 + 0x08040000;
		constexpr uint32 ADC_COMMON									= AHB2 + 0x08040300;
		constexpr uint32 RNG									    	= AHB2 + 0x08040800;
		
		constexpr uint32 DBGMCU											= CORE::BASE::CORE + 0x00042000;
	};
	
	
	
	namespace TIMER_2
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x04);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x08);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_2 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x14);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_2 + 0x18);
		volatile uint32* const CCMR2			        	= (volatile uint32* const) (BASE::TIMER_2 + 0x1C);
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
		volatile uint32* const OR1			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x50);
		volatile uint32* const OR2			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x60);
	};
	
	namespace TIMER_3
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x04);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x08);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_3 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x14);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_3 + 0x18);
		volatile uint32* const CCMR2			        	= (volatile uint32* const) (BASE::TIMER_3 + 0x1C);
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
		volatile uint32* const OR1			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x50);
		volatile uint32* const OR2			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x60);
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
	
	namespace RTC
	{
		volatile uint32* const TR				        		= (volatile uint32* const) (BASE::RTC + 0x00);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::RTC + 0x04);
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::RTC + 0x08);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::RTC + 0x0C);
		volatile uint32* const PRER				        	= (volatile uint32* const) (BASE::RTC + 0x10);
		volatile uint32* const WUTR				        	= (volatile uint32* const) (BASE::RTC + 0x14);
		volatile uint32* const ALRMAR				        = (volatile uint32* const) (BASE::RTC + 0x1C);
		volatile uint32* const ALRMBR				        = (volatile uint32* const) (BASE::RTC + 0x20);
		volatile uint32* const WPR				        	= (volatile uint32* const) (BASE::RTC + 0x24);
		volatile uint32* const SSR				        	= (volatile uint32* const) (BASE::RTC + 0x28);
		volatile uint32* const SHIFTR				        = (volatile uint32* const) (BASE::RTC + 0x2C);
		volatile uint32* const TSTR				        	= (volatile uint32* const) (BASE::RTC + 0x30);
		volatile uint32* const TSDR				        	= (volatile uint32* const) (BASE::RTC + 0x34);
		volatile uint32* const TSSSR				        = (volatile uint32* const) (BASE::RTC + 0x38);
		volatile uint32* const CALR				        	= (volatile uint32* const) (BASE::RTC + 0x3C);
		volatile uint32* const TAMPCR				        = (volatile uint32* const) (BASE::RTC + 0x40);
		volatile uint32* const ALRMASSR				      = (volatile uint32* const) (BASE::RTC + 0x44);
		volatile uint32* const ALRMBSSR				      = (volatile uint32* const) (BASE::RTC + 0x48);
		volatile uint32* const OR				      			= (volatile uint32* const) (BASE::RTC + 0x4C);
		volatile uint32* const BKP_0				      	= (volatile uint32* const) (BASE::RTC + 0x50);
		volatile uint32* const BKP_1				      	= (volatile uint32* const) (BASE::RTC + 0x54);
		volatile uint32* const BKP_2				      	= (volatile uint32* const) (BASE::RTC + 0x58);
		volatile uint32* const BKP_3				      	= (volatile uint32* const) (BASE::RTC + 0x5C);
		volatile uint32* const BKP_4				      	= (volatile uint32* const) (BASE::RTC + 0x60);
		volatile uint32* const BKP_5				      	= (volatile uint32* const) (BASE::RTC + 0x64);
		volatile uint32* const BKP_6				      	= (volatile uint32* const) (BASE::RTC + 0x68);
		volatile uint32* const BKP_7				      	= (volatile uint32* const) (BASE::RTC + 0x6C);
		volatile uint32* const BKP_8				      	= (volatile uint32* const) (BASE::RTC + 0x70);
		volatile uint32* const BKP_9				      	= (volatile uint32* const) (BASE::RTC + 0x74);
		volatile uint32* const BKP_10				      	= (volatile uint32* const) (BASE::RTC + 0x78);
		volatile uint32* const BKP_11				      	= (volatile uint32* const) (BASE::RTC + 0x7C);
		volatile uint32* const BKP_12				      	= (volatile uint32* const) (BASE::RTC + 0x80);
		volatile uint32* const BKP_13				      	= (volatile uint32* const) (BASE::RTC + 0x84);
		volatile uint32* const BKP_14				      	= (volatile uint32* const) (BASE::RTC + 0x88);
		volatile uint32* const BKP_15				      	= (volatile uint32* const) (BASE::RTC + 0x8C);
		volatile uint32* const BKP_16				      	= (volatile uint32* const) (BASE::RTC + 0x90);
		volatile uint32* const BKP_17				      	= (volatile uint32* const) (BASE::RTC + 0x94);
		volatile uint32* const BKP_18				      	= (volatile uint32* const) (BASE::RTC + 0x98);
		volatile uint32* const BKP_19				      	= (volatile uint32* const) (BASE::RTC + 0x9C);
		volatile uint32* const BKP_20				      	= (volatile uint32* const) (BASE::RTC + 0xA0);
		volatile uint32* const BKP_21				      	= (volatile uint32* const) (BASE::RTC + 0xA4);
		volatile uint32* const BKP_22				      	= (volatile uint32* const) (BASE::RTC + 0xA8);
		volatile uint32* const BKP_23				      	= (volatile uint32* const) (BASE::RTC + 0xAC);
		volatile uint32* const BKP_24				      	= (volatile uint32* const) (BASE::RTC + 0xB0);
		volatile uint32* const BKP_25				      	= (volatile uint32* const) (BASE::RTC + 0xB4);
		volatile uint32* const BKP_26				      	= (volatile uint32* const) (BASE::RTC + 0xB8);
		volatile uint32* const BKP_27				      	= (volatile uint32* const) (BASE::RTC + 0xBC);
		volatile uint32* const BKP_28				      	= (volatile uint32* const) (BASE::RTC + 0xC0);
		volatile uint32* const BKP_29				      	= (volatile uint32* const) (BASE::RTC + 0xC4);
		volatile uint32* const BKP_30				      	= (volatile uint32* const) (BASE::RTC + 0xC8);
		volatile uint32* const BKP_31				      	= (volatile uint32* const) (BASE::RTC + 0xCC);
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
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::SPI_2 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::SPI_2 + 0x04);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::SPI_2 + 0x08);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::SPI_2 + 0x0C);
		volatile uint32* const CRCPR				      	= (volatile uint32* const) (BASE::SPI_2 + 0x10);
		volatile uint32* const RXCRC				        = (volatile uint32* const) (BASE::SPI_2 + 0x14);
		volatile uint32* const TXCRC				        = (volatile uint32* const) (BASE::SPI_2 + 0x18);
	};
	
	namespace SPI_3
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::SPI_3 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::SPI_3 + 0x04);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::SPI_3 + 0x08);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::SPI_3 + 0x0C);
		volatile uint32* const CRCPR				      	= (volatile uint32* const) (BASE::SPI_3 + 0x10);
		volatile uint32* const RXCRC				        = (volatile uint32* const) (BASE::SPI_3 + 0x14);
		volatile uint32* const TXCRC				        = (volatile uint32* const) (BASE::SPI_3 + 0x18);
	};
	
	namespace USART_2
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::USART_2 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::USART_2 + 0x04);
		volatile uint32* const CR3				        	= (volatile uint32* const) (BASE::USART_2 + 0x08);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::USART_2 + 0x0C);
		volatile uint32* const GTPR				        	= (volatile uint32* const) (BASE::USART_2 + 0x10);
		volatile uint32* const RTOR				        	= (volatile uint32* const) (BASE::USART_2 + 0x14);
		volatile uint32* const RQR				        	= (volatile uint32* const) (BASE::USART_2 + 0x18);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::USART_2 + 0x1C);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::USART_2 + 0x20);
		volatile uint32* const RDR				        	= (volatile uint32* const) (BASE::USART_2 + 0x24);
		volatile uint32* const TDR				        	= (volatile uint32* const) (BASE::USART_2 + 0x28);
	};
	
	namespace USART_3
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::USART_3 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::USART_3 + 0x04);
		volatile uint32* const CR3				        	= (volatile uint32* const) (BASE::USART_3 + 0x08);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::USART_3 + 0x0C);
		volatile uint32* const GTPR				        	= (volatile uint32* const) (BASE::USART_3 + 0x10);
		volatile uint32* const RTOR				        	= (volatile uint32* const) (BASE::USART_3 + 0x14);
		volatile uint32* const RQR				        	= (volatile uint32* const) (BASE::USART_3 + 0x18);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::USART_3 + 0x1C);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::USART_3 + 0x20);
		volatile uint32* const RDR				        	= (volatile uint32* const) (BASE::USART_3 + 0x24);
		volatile uint32* const TDR				        	= (volatile uint32* const) (BASE::USART_3 + 0x28);
	};
	
	namespace USART_4
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::USART_4 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::USART_4 + 0x04);
		volatile uint32* const CR3				        	= (volatile uint32* const) (BASE::USART_4 + 0x08);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::USART_4 + 0x0C);
		volatile uint32* const GTPR				        	= (volatile uint32* const) (BASE::USART_4 + 0x10);
		volatile uint32* const RTOR				        	= (volatile uint32* const) (BASE::USART_4 + 0x14);
		volatile uint32* const RQR				        	= (volatile uint32* const) (BASE::USART_4 + 0x18);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::USART_4 + 0x1C);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::USART_4 + 0x20);
		volatile uint32* const RDR				        	= (volatile uint32* const) (BASE::USART_4 + 0x24);
		volatile uint32* const TDR				        	= (volatile uint32* const) (BASE::USART_4 + 0x28);
	};
	
	namespace I2C_1
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::I2C_1 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::I2C_1 + 0x04);
		volatile uint32* const OAR1				        	= (volatile uint32* const) (BASE::I2C_1 + 0x08);
		volatile uint32* const OAR2				        	= (volatile uint32* const) (BASE::I2C_1 + 0x0C);
		volatile uint32* const TIMINGR				      = (volatile uint32* const) (BASE::I2C_1 + 0x10);
		volatile uint32* const TIMEOUTR				      = (volatile uint32* const) (BASE::I2C_1 + 0x14);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::I2C_1 + 0x18);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::I2C_1 + 0x1C);
		volatile uint32* const PECR				        	= (volatile uint32* const) (BASE::I2C_1 + 0x20);
		volatile uint32* const RXDR				        	= (volatile uint32* const) (BASE::I2C_1 + 0x24);
		volatile uint32* const TXDR				        	= (volatile uint32* const) (BASE::I2C_1 + 0x28);
	};
	
	namespace I2C_2
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::I2C_2 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::I2C_2 + 0x04);
		volatile uint32* const OAR1				        	= (volatile uint32* const) (BASE::I2C_2 + 0x08);
		volatile uint32* const OAR2				        	= (volatile uint32* const) (BASE::I2C_2 + 0x0C);
		volatile uint32* const TIMINGR				      = (volatile uint32* const) (BASE::I2C_2 + 0x10);
		volatile uint32* const TIMEOUTR				      = (volatile uint32* const) (BASE::I2C_2 + 0x14);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::I2C_2 + 0x18);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::I2C_2 + 0x1C);
		volatile uint32* const PECR				        	= (volatile uint32* const) (BASE::I2C_2 + 0x20);
		volatile uint32* const RXDR				        	= (volatile uint32* const) (BASE::I2C_2 + 0x24);
		volatile uint32* const TXDR				        	= (volatile uint32* const) (BASE::I2C_2 + 0x28);
	};
	
	namespace I2C_3
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::I2C_3 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::I2C_3 + 0x04);
		volatile uint32* const OAR1				        	= (volatile uint32* const) (BASE::I2C_3 + 0x08);
		volatile uint32* const OAR2				        	= (volatile uint32* const) (BASE::I2C_3 + 0x0C);
		volatile uint32* const TIMINGR				      = (volatile uint32* const) (BASE::I2C_3 + 0x10);
		volatile uint32* const TIMEOUTR				      = (volatile uint32* const) (BASE::I2C_3 + 0x14);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::I2C_3 + 0x18);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::I2C_3 + 0x1C);
		volatile uint32* const PECR				        	= (volatile uint32* const) (BASE::I2C_3 + 0x20);
		volatile uint32* const RXDR				        	= (volatile uint32* const) (BASE::I2C_3 + 0x24);
		volatile uint32* const TXDR				        	= (volatile uint32* const) (BASE::I2C_3 + 0x28);
	};
	
	namespace CRS
	{
		volatile uint32* const CR				        		= (volatile uint32* const) (BASE::CRS + 0x00);
		volatile uint32* const CFGR				        	= (volatile uint32* const) (BASE::CRS + 0x04);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::CRS + 0x08);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::CRS + 0x0C);
	};
	
	namespace CAN_1
	{
		volatile uint32* const MCR						      = (volatile uint32* const) (BASE::CAN_1 + 0x00);
		volatile uint32* const MSR						      = (volatile uint32* const) (BASE::CAN_1 + 0x04);
		volatile uint32* const TSR						      = (volatile uint32* const) (BASE::CAN_1 + 0x08);
		volatile uint32* const RF0R					        = (volatile uint32* const) (BASE::CAN_1 + 0x0C);
		volatile uint32* const RF1R					        = (volatile uint32* const) (BASE::CAN_1 + 0x10);
		volatile uint32* const IER						      = (volatile uint32* const) (BASE::CAN_1 + 0x14);
		volatile uint32* const ESR					        = (volatile uint32* const) (BASE::CAN_1 + 0x18);
		volatile uint32* const BTR					        = (volatile uint32* const) (BASE::CAN_1 + 0x1C);
		
		volatile uint32* const TI0R					        = (volatile uint32* const) (BASE::CAN_1 + 0x180);
		volatile uint32* const TDT0R				        = (volatile uint32* const) (BASE::CAN_1 + 0x184);
		volatile uint32* const TDL0R				        = (volatile uint32* const) (BASE::CAN_1 + 0x188);
		volatile uint32* const TDH0R				        = (volatile uint32* const) (BASE::CAN_1 + 0x18C);
		volatile uint32* const TI1R			           	= (volatile uint32* const) (BASE::CAN_1 + 0x190);
		volatile uint32* const TDT1R				        = (volatile uint32* const) (BASE::CAN_1 + 0x194);
		volatile uint32* const TDL1R		        		= (volatile uint32* const) (BASE::CAN_1 + 0x198);
		volatile uint32* const TDH1R		        		= (volatile uint32* const) (BASE::CAN_1 + 0x19C);
		volatile uint32* const TI2R		        			= (volatile uint32* const) (BASE::CAN_1 + 0x1A0);
		volatile uint32* const TDT2R		        		= (volatile uint32* const) (BASE::CAN_1 + 0x1A4);
		volatile uint32* const TDL2R	           		= (volatile uint32* const) (BASE::CAN_1 + 0x1A8);
		volatile uint32* const TDH2R	        			= (volatile uint32* const) (BASE::CAN_1 + 0x1AC);
		volatile uint32* const RI0R	        				= (volatile uint32* const) (BASE::CAN_1 + 0x1B0);
		volatile uint32* const RDT0R		        		= (volatile uint32* const) (BASE::CAN_1 + 0x1B4);
		volatile uint32* const RDL0R		        		= (volatile uint32* const) (BASE::CAN_1 + 0x1B8);
		volatile uint32* const RDH0R		        		= (volatile uint32* const) (BASE::CAN_1 + 0x1BC);
		volatile uint32* const RI1R		        			= (volatile uint32* const) (BASE::CAN_1 + 0x1C0);
		volatile uint32* const RDT1R		        		= (volatile uint32* const) (BASE::CAN_1 + 0x1C4);
		volatile uint32* const RDL1R		           	= (volatile uint32* const) (BASE::CAN_1 + 0x1C8);
		volatile uint32* const RDH1R		        		= (volatile uint32* const) (BASE::CAN_1 + 0x1CC);
		volatile uint32* const FMR			        		= (volatile uint32* const) (BASE::CAN_1 + 0x200);
		volatile uint32* const FM1R		        			= (volatile uint32* const) (BASE::CAN_1 + 0x204);
		volatile uint32* const FS1R		        			= (volatile uint32* const) (BASE::CAN_1 + 0x20C);
		volatile uint32* const FFA1R		        		= (volatile uint32* const) (BASE::CAN_1 + 0x214);
		volatile uint32* const FA1R		           		= (volatile uint32* const) (BASE::CAN_1 + 0x21C);
		volatile uint32* const F0R1		        			= (volatile uint32* const) (BASE::CAN_1 + 0x240);
		volatile uint32* const F0R2		        			= (volatile uint32* const) (BASE::CAN_1 + 0x244);
		volatile uint32* const F1R1		        			= (volatile uint32* const) (BASE::CAN_1 + 0x248);
		volatile uint32* const F1R2			        		= (volatile uint32* const) (BASE::CAN_1 + 0x24C);
		volatile uint32* const F2R1		        			= (volatile uint32* const) (BASE::CAN_1 + 0x250);
		volatile uint32* const F2R2		        			= (volatile uint32* const) (BASE::CAN_1 + 0x254);
		volatile uint32* const F3R1		        			= (volatile uint32* const) (BASE::CAN_1 + 0x258);
		volatile uint32* const F3R2		        			= (volatile uint32* const) (BASE::CAN_1 + 0x25C);
		volatile uint32* const F4R1		        			= (volatile uint32* const) (BASE::CAN_1 + 0x260);
		volatile uint32* const F4R2		        			= (volatile uint32* const) (BASE::CAN_1 + 0x264);
		volatile uint32* const F5R1		        			= (volatile uint32* const) (BASE::CAN_1 + 0x268);
		volatile uint32* const F5R2		        			= (volatile uint32* const) (BASE::CAN_1 + 0x26C);
		volatile uint32* const F6R1		        			= (volatile uint32* const) (BASE::CAN_1 + 0x270);
		volatile uint32* const F6R2		        			= (volatile uint32* const) (BASE::CAN_1 + 0x274);
		volatile uint32* const F7R1		        			= (volatile uint32* const) (BASE::CAN_1 + 0x278);
		volatile uint32* const F7R2		        			= (volatile uint32* const) (BASE::CAN_1 + 0x27C);
		volatile uint32* const F8R1		        			= (volatile uint32* const) (BASE::CAN_1 + 0x280);
		volatile uint32* const F8R2		        			= (volatile uint32* const) (BASE::CAN_1 + 0x284);
		volatile uint32* const F9R1		        			= (volatile uint32* const) (BASE::CAN_1 + 0x288);
		volatile uint32* const F9R2		        			= (volatile uint32* const) (BASE::CAN_1 + 0x28C);
		volatile uint32* const F10R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x290);
		volatile uint32* const F10R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x294);
		volatile uint32* const F11R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x298);
		volatile uint32* const F11R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x29C);
		volatile uint32* const F12R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2A0);
		volatile uint32* const F12R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2A4);
		volatile uint32* const F13R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2A8);
		volatile uint32* const F13R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2AC);
		volatile uint32* const F14R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2B0);
		volatile uint32* const F14R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2B4);
		volatile uint32* const F15R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2B8);
		volatile uint32* const F15R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2BC);
		volatile uint32* const F16R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2C0);
		volatile uint32* const F16R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2C4);
		volatile uint32* const F17R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2C8);
		volatile uint32* const F17R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2CC);
		volatile uint32* const F18R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2D0);
		volatile uint32* const F18R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2D4);
		volatile uint32* const F19R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2D8);
		volatile uint32* const F19R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2DC);
		volatile uint32* const F20R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2E0);
		volatile uint32* const F20R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2E4);
		volatile uint32* const F21R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2E8);
		volatile uint32* const F21R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2EC);
		volatile uint32* const F22R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2F0);
		volatile uint32* const F22R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2F4);
		volatile uint32* const F23R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2F8);
		volatile uint32* const F23R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x2FC);
		volatile uint32* const F24R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x300);
		volatile uint32* const F24R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x304);
		volatile uint32* const F25R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x308);
		volatile uint32* const F25R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x30C);
		volatile uint32* const F26R1		        		= (volatile uint32* const) (BASE::CAN_1 + 0x310);
		volatile uint32* const F26R2		        		= (volatile uint32* const) (BASE::CAN_1 + 0x314);
		volatile uint32* const F27R1			        	= (volatile uint32* const) (BASE::CAN_1 + 0x318);
		volatile uint32* const F27R2			        	= (volatile uint32* const) (BASE::CAN_1 + 0x31C);
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
		volatile uint32* const PUCRH								= (volatile uint32* const) (BASE::PWR + 0x58);
		volatile uint32* const PDCRH								= (volatile uint32* const) (BASE::PWR + 0x5C);
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
	};
	
	namespace OPAMP
	{
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::OPAMP + 0x00);
		volatile uint32* const OTR									= (volatile uint32* const) (BASE::OPAMP + 0x04);
		volatile uint32* const LPOTR								= (volatile uint32* const) (BASE::OPAMP + 0x08);
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
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x24);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::LP_TIMER_1 + 0x28);
	};
	
	namespace LP_UART_1
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::LP_UART_1 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::LP_UART_1 + 0x04);
		volatile uint32* const CR3				        	= (volatile uint32* const) (BASE::LP_UART_1 + 0x08);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::LP_UART_1 + 0x0C);
		volatile uint32* const RQR				        	= (volatile uint32* const) (BASE::LP_UART_1 + 0x18);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::LP_UART_1 + 0x1C);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::LP_UART_1 + 0x20);
		volatile uint32* const RDR				        	= (volatile uint32* const) (BASE::LP_UART_1 + 0x24);
		volatile uint32* const TDR				        	= (volatile uint32* const) (BASE::LP_UART_1 + 0x28);
	};
	
	namespace I2C_4
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::I2C_4 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::I2C_4 + 0x04);
		volatile uint32* const OAR1				        	= (volatile uint32* const) (BASE::I2C_4 + 0x08);
		volatile uint32* const OAR2				        	= (volatile uint32* const) (BASE::I2C_4 + 0x0C);
		volatile uint32* const TIMINGR				      = (volatile uint32* const) (BASE::I2C_4 + 0x10);
		volatile uint32* const TIMEOUTR				      = (volatile uint32* const) (BASE::I2C_4 + 0x14);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::I2C_4 + 0x18);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::I2C_4 + 0x1C);
		volatile uint32* const PECR				        	= (volatile uint32* const) (BASE::I2C_4 + 0x20);
		volatile uint32* const RXDR				        	= (volatile uint32* const) (BASE::I2C_4 + 0x24);
		volatile uint32* const TXDR				        	= (volatile uint32* const) (BASE::I2C_4 + 0x28);
	};
	
	namespace LP_TIMER_2
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x00);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x04);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x08);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x0C);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x10);
		volatile uint32* const CMP									= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x14);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x18);
		volatile uint32* const CNT									= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x1C);
		volatile uint32* const OR										= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x20);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x24);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::LP_TIMER_2 + 0x28);
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
	
	namespace VREF
	{
		volatile uint32* const CSR				      		= (volatile uint32* const) (BASE::VREFBUF + 0x00);
		volatile uint32* const CCR				      		= (volatile uint32* const) (BASE::VREFBUF + 0x04);
	};
	
	namespace COMP
	{
		volatile uint32* const COMP1_CSR				    = (volatile uint32* const) (BASE::COMP + 0x00);
		volatile uint32* const COMP2_CSR				    = (volatile uint32* const) (BASE::COMP + 0x04);
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
	
	namespace FIREWALL
	{
		volatile uint32* const CSSA									= (volatile uint32* const) (BASE::FIREWALL + 0x00);
		volatile uint32* const CSL									= (volatile uint32* const) (BASE::FIREWALL + 0x04);
		volatile uint32* const NVDSSA								= (volatile uint32* const) (BASE::FIREWALL + 0x08);
		volatile uint32* const NVDSL								= (volatile uint32* const) (BASE::FIREWALL + 0x0C);
		volatile uint32* const VDSSA								= (volatile uint32* const) (BASE::FIREWALL + 0x10);
		volatile uint32* const VDSL									= (volatile uint32* const) (BASE::FIREWALL + 0x14);
		volatile uint32* const CR				  					= (volatile uint32* const) (BASE::FIREWALL + 0x20);
	};
	
	namespace SDMMC_1
	{
		volatile uint32* const POWER								= (volatile uint32* const) (BASE::SDMMC_1 + 0x00);
		volatile uint32* const CLKCR								= (volatile uint32* const) (BASE::SDMMC_1 + 0x04);
		volatile uint32* const ARGR									= (volatile uint32* const) (BASE::SDMMC_1 + 0x08);
		volatile uint32* const CMDR									= (volatile uint32* const) (BASE::SDMMC_1 + 0x0C);
		volatile uint32* const RESP_CMDR						= (volatile uint32* const) (BASE::SDMMC_1 + 0x10);
		volatile uint32* const RESP_1R							= (volatile uint32* const) (BASE::SDMMC_1 + 0x14);
		volatile uint32* const RESP_2R							= (volatile uint32* const) (BASE::SDMMC_1 + 0x18);
		volatile uint32* const RESP_3R							= (volatile uint32* const) (BASE::SDMMC_1 + 0x1C);
		volatile uint32* const RESP_4R							= (volatile uint32* const) (BASE::SDMMC_1 + 0x20);
		volatile uint32* const DTIMER								= (volatile uint32* const) (BASE::SDMMC_1 + 0x24);
		volatile uint32* const DLENR								= (volatile uint32* const) (BASE::SDMMC_1 + 0x28);
		volatile uint32* const DCTRLR								= (volatile uint32* const) (BASE::SDMMC_1 + 0x2C);
		volatile uint32* const DCNTR								= (volatile uint32* const) (BASE::SDMMC_1 + 0x30);
		volatile uint32* const STAR									= (volatile uint32* const) (BASE::SDMMC_1 + 0x34);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::SDMMC_1 + 0x38);
		volatile uint32* const MASKR								= (volatile uint32* const) (BASE::SDMMC_1 + 0x3C);
		volatile uint32* const FIFOCNT							= (volatile uint32* const) (BASE::SDMMC_1 + 0x48);
		volatile uint32* const FIFO									= (volatile uint32* const) (BASE::SDMMC_1 + 0x80);
	};
	
	namespace TIMER_1
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x04);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x08);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_1 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x14);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_1 + 0x18);
		volatile uint32* const CCMR2			        	= (volatile uint32* const) (BASE::TIMER_1 + 0x1C);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x2C);
		volatile uint32* const RCR			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x30);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x34);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x38);
		volatile uint32* const CCR3			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x3C);
		volatile uint32* const CCR4			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x40);
		volatile uint32* const BDTR			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x44);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x48);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x4C);
		volatile uint32* const OR1			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x50);
		volatile uint32* const CCMR3			        	= (volatile uint32* const) (BASE::TIMER_1 + 0x54);
		volatile uint32* const CCR5			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x58);
		volatile uint32* const CCR6			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x5C);
		volatile uint32* const OR2			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x60);
		volatile uint32* const OR3			        		= (volatile uint32* const) (BASE::TIMER_1 + 0x64);
	};
	
	namespace SPI_1
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::SPI_1 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::SPI_1 + 0x04);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::SPI_1 + 0x08);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::SPI_1 + 0x0C);
		volatile uint32* const CRCPR				      	= (volatile uint32* const) (BASE::SPI_1 + 0x10);
		volatile uint32* const RXCRC				        = (volatile uint32* const) (BASE::SPI_1 + 0x14);
		volatile uint32* const TXCRC				        = (volatile uint32* const) (BASE::SPI_1 + 0x18);
	};
	
	namespace USART_1
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::USART_1 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::USART_1 + 0x04);
		volatile uint32* const CR3				        	= (volatile uint32* const) (BASE::USART_1 + 0x08);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::USART_1 + 0x0C);
		volatile uint32* const GTPR				        	= (volatile uint32* const) (BASE::USART_1 + 0x10);
		volatile uint32* const RTOR				        	= (volatile uint32* const) (BASE::USART_1 + 0x14);
		volatile uint32* const RQR				        	= (volatile uint32* const) (BASE::USART_1 + 0x18);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::USART_1 + 0x1C);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::USART_1 + 0x20);
		volatile uint32* const RDR				        	= (volatile uint32* const) (BASE::USART_1 + 0x24);
		volatile uint32* const TDR				        	= (volatile uint32* const) (BASE::USART_1 + 0x28);
	};
	
	namespace TIMER_15
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x04);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_15 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x14);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_15 + 0x18);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x2C);
		volatile uint32* const RCR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x30);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x34);
		volatile uint32* const BDTR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x44);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x48);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x4C);
		volatile uint32* const OR1			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x50);
		volatile uint32* const OR2			        		= (volatile uint32* const) (BASE::TIMER_15 + 0x60);
	};
	
	namespace TIMER_16
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x04);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_16 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x14);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_16 + 0x18);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x2C);
		volatile uint32* const RCR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x30);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x34);
		volatile uint32* const BDTR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x44);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x48);
		volatile uint32* const DMAR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x4C);
		volatile uint32* const OR1			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x50);
		volatile uint32* const OR2			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x60);
	};
	
	namespace SAI_1
	{
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
	};
	
	namespace DFSDM_1
	{
		volatile uint32* const CH0_CFGR1						= (volatile uint32* const) (BASE::DFSDM_1 + 0x00);
		volatile uint32* const CH0_CFGR2						= (volatile uint32* const) (BASE::DFSDM_1 + 0x04);
		volatile uint32* const CH0_AWSCDR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x08);
		volatile uint32* const CH0_WDATR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x0C);
		volatile uint32* const CH0_DATINR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x10);
		volatile uint32* const CH1_CFGR1						= (volatile uint32* const) (BASE::DFSDM_1 + 0x20);
		volatile uint32* const CH1_CFGR2						= (volatile uint32* const) (BASE::DFSDM_1 + 0x24);
		volatile uint32* const CH1_AWSCDR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x28);
		volatile uint32* const CH1_WDATR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x2C);
		volatile uint32* const CH1_DATINR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x30);
		volatile uint32* const CH2_CFGR1						= (volatile uint32* const) (BASE::DFSDM_1 + 0x40);
		volatile uint32* const CH2_CFGR2						= (volatile uint32* const) (BASE::DFSDM_1 + 0x44);
		volatile uint32* const CH2_AWSCDR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x48);
		volatile uint32* const CH2_WDATR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x4C);
		volatile uint32* const CH2_DATINR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x50);
		volatile uint32* const CH3_CFGR1						= (volatile uint32* const) (BASE::DFSDM_1 + 0x60);
		volatile uint32* const CH3_CFGR2						= (volatile uint32* const) (BASE::DFSDM_1 + 0x64);
		volatile uint32* const CH3_AWSCDR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x68);
		volatile uint32* const CH3_WDATR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x6C);
		volatile uint32* const CH3_DATINR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x70);
		
		volatile uint32* const FLT0_CR1							= (volatile uint32* const) (BASE::DFSDM_1 + 0x100);
		volatile uint32* const FLT0_CR2							= (volatile uint32* const) (BASE::DFSDM_1 + 0x104);
		volatile uint32* const FLT0_ISR							= (volatile uint32* const) (BASE::DFSDM_1 + 0x108);
		volatile uint32* const FLT0_ICR							= (volatile uint32* const) (BASE::DFSDM_1 + 0x10C);
		volatile uint32* const FLT0_JCHGR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x110);
		volatile uint32* const FLT0_FCR							= (volatile uint32* const) (BASE::DFSDM_1 + 0x114);
		volatile uint32* const FLT0_JDATAR					= (volatile uint32* const) (BASE::DFSDM_1 + 0x118);
		volatile uint32* const FLT0_RDATAR					= (volatile uint32* const) (BASE::DFSDM_1 + 0x11C);
		volatile uint32* const FLT0_AWHTR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x120);
		volatile uint32* const FLT0_AWLTR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x124);
		volatile uint32* const FLT0_AWSR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x128);
		volatile uint32* const FLT0_AWCFR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x12C);
		volatile uint32* const FLT0_EXMAX						= (volatile uint32* const) (BASE::DFSDM_1 + 0x130);
		volatile uint32* const FLT0_EXMIN						= (volatile uint32* const) (BASE::DFSDM_1 + 0x134);
		volatile uint32* const FLT0_CNVTIMR					= (volatile uint32* const) (BASE::DFSDM_1 + 0x138);
		volatile uint32* const FLT1_CR1							= (volatile uint32* const) (BASE::DFSDM_1 + 0x180);
		volatile uint32* const FLT1_CR2							= (volatile uint32* const) (BASE::DFSDM_1 + 0x184);
		volatile uint32* const FLT1_ISR							= (volatile uint32* const) (BASE::DFSDM_1 + 0x188);
		volatile uint32* const FLT1_ICR							= (volatile uint32* const) (BASE::DFSDM_1 + 0x18C);
		volatile uint32* const FLT1_JCHGR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x190);
		volatile uint32* const FLT1_FCR							= (volatile uint32* const) (BASE::DFSDM_1 + 0x194);
		volatile uint32* const FLT1_JDATAR					= (volatile uint32* const) (BASE::DFSDM_1 + 0x198);
		volatile uint32* const FLT1_RDATAR					= (volatile uint32* const) (BASE::DFSDM_1 + 0x19C);
		volatile uint32* const FLT1_AWHTR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x1A0);
		volatile uint32* const FLT1_AWLTR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x1A4);
		volatile uint32* const FLT1_AWSR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x1A8);
		volatile uint32* const FLT1_AWCFR						= (volatile uint32* const) (BASE::DFSDM_1 + 0x1AC);
		volatile uint32* const FLT1_EXMAX						= (volatile uint32* const) (BASE::DFSDM_1 + 0x1B0);
		volatile uint32* const FLT1_EXMIN						= (volatile uint32* const) (BASE::DFSDM_1 + 0x1B4);
		volatile uint32* const FLT1_CNVTIMR					= (volatile uint32* const) (BASE::DFSDM_1 + 0x1B8);
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
		
		volatile uint32* const CSELR								= (volatile uint32* const) (BASE::DMA_1 + 0xA8);
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
		
		volatile uint32* const CSELR								= (volatile uint32* const) (BASE::DMA_2 + 0xA8);
	};
	
	namespace RCC
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::RCC + 0x00);
		volatile uint32* const ICSCR								= (volatile uint32* const) (BASE::RCC + 0x04);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::RCC + 0x08);
		volatile uint32* const PLL_CFGR							= (volatile uint32* const) (BASE::RCC + 0x0C);
		volatile uint32* const PLL_SAI1_CFGR				= (volatile uint32* const) (BASE::RCC + 0x10);
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
	};
	
	namespace CRC
	{
		volatile uint32* const DR										= (volatile uint32* const) (BASE::CRC + 0x00);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::CRC + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::CRC + 0x08);
		volatile uint32* const INIT									= (volatile uint32* const) (BASE::CRC + 0x10);
		volatile uint32* const POL									= (volatile uint32* const) (BASE::CRC + 0x14);
	};
	
	namespace TSC
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::TSC + 0x00);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::TSC + 0x04);
		volatile uint32* const ICR									= (volatile uint32* const) (BASE::TSC + 0x08);
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::TSC + 0x0C);
		volatile uint32* const IO_HCR								= (volatile uint32* const) (BASE::TSC + 0x10);
		volatile uint32* const IO_ASCR							= (volatile uint32* const) (BASE::TSC + 0x18);
		volatile uint32* const IO_SCR								= (volatile uint32* const) (BASE::TSC + 0x20);
		volatile uint32* const IO_CCR								= (volatile uint32* const) (BASE::TSC + 0x28);
		volatile uint32* const IO_GCSR							= (volatile uint32* const) (BASE::TSC + 0x30);
		volatile uint32* const IO_G1CR							= (volatile uint32* const) (BASE::TSC + 0x34);
		volatile uint32* const IO_G2CR							= (volatile uint32* const) (BASE::TSC + 0x38);
		volatile uint32* const IO_G3CR							= (volatile uint32* const) (BASE::TSC + 0x3C);
		volatile uint32* const IO_G4CR							= (volatile uint32* const) (BASE::TSC + 0x40);
		volatile uint32* const IO_G5CR							= (volatile uint32* const) (BASE::TSC + 0x44);
		volatile uint32* const IO_G6CR							= (volatile uint32* const) (BASE::TSC + 0x48);
		volatile uint32* const IO_G7CR							= (volatile uint32* const) (BASE::TSC + 0x4C);
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
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_H + 0x28);
	};
	
	namespace ADC_1
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC_1 + 0x000);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC_1 + 0x004);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::ADC_1 + 0x008);
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::ADC_1 + 0x00C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC_1 + 0x010);
		volatile uint32* const SMPR1								= (volatile uint32* const) (BASE::ADC_1 + 0x014);
		volatile uint32* const SMPR2								= (volatile uint32* const) (BASE::ADC_1 + 0x018);
		volatile uint32* const TR1									= (volatile uint32* const) (BASE::ADC_1 + 0x020);
		volatile uint32* const TR2									= (volatile uint32* const) (BASE::ADC_1 + 0x024);
		volatile uint32* const TR3									= (volatile uint32* const) (BASE::ADC_1 + 0x028);
		volatile uint32* const SQR1									= (volatile uint32* const) (BASE::ADC_1 + 0x030);
		volatile uint32* const SQR2									= (volatile uint32* const) (BASE::ADC_1 + 0x034);
		volatile uint32* const SQR3									= (volatile uint32* const) (BASE::ADC_1 + 0x038);
		volatile uint32* const SQR4									= (volatile uint32* const) (BASE::ADC_1 + 0x03C);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::ADC_1 + 0x040);
		volatile uint32* const JSQR									= (volatile uint32* const) (BASE::ADC_1 + 0x04C);
		volatile uint32* const OFR1									= (volatile uint32* const) (BASE::ADC_1 + 0x060);
		volatile uint32* const OFR2									= (volatile uint32* const) (BASE::ADC_1 + 0x064);
		volatile uint32* const OFR3									= (volatile uint32* const) (BASE::ADC_1 + 0x068);
		volatile uint32* const OFR4									= (volatile uint32* const) (BASE::ADC_1 + 0x06C);
		volatile uint32* const JDR1									= (volatile uint32* const) (BASE::ADC_1 + 0x080);
		volatile uint32* const JDR2									= (volatile uint32* const) (BASE::ADC_1 + 0x084);
		volatile uint32* const JDR3									= (volatile uint32* const) (BASE::ADC_1 + 0x088);
		volatile uint32* const JDR4									= (volatile uint32* const) (BASE::ADC_1 + 0x08C);
		volatile uint32* const AWD2CR								= (volatile uint32* const) (BASE::ADC_1 + 0x0A0);
		volatile uint32* const AWD3CR								= (volatile uint32* const) (BASE::ADC_1 + 0x0A4);
		volatile uint32* const DIFSEL								= (volatile uint32* const) (BASE::ADC_1 + 0x0B0);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC_1 + 0x0B4);
	};
	
	namespace ADC_COMMON
	{
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::ADC_COMMON + 0x00);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::ADC_COMMON + 0x08);
		volatile uint32* const CDR									= (volatile uint32* const) (BASE::ADC_COMMON + 0x0C);
	}
	
	namespace RNG
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::RNG + 0x00);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::RNG + 0x04);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::RNG + 0x08);
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