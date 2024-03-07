#pragma once

#include "cmos.hpp"





namespace Interrupt
{
	constexpr uint16 WWDG																			= 16;
	
	constexpr uint16 RTC																			= 18;
	constexpr uint16 FLASH																		= 19;
	constexpr uint16 RCC 																			= 20;
	constexpr uint16 EXTI_0_TO_1															= 21;
	constexpr uint16 EXTI_2_TO_3															= 22;
	constexpr uint16 EXTI_4_TO_15															= 23;
	
	constexpr uint16 DMA_CH0																	= 25;
	constexpr uint16 DMA_CH1_CH2															= 26;
	constexpr uint16 DMA_CH3_TO_CH6														= 27;
	constexpr uint16 ADC																			= 28;
	constexpr uint16 LP_TIMER_1																= 29;
	
	constexpr uint16 TIMER_2																	= 31;
	
	
	
	
	constexpr uint16 TIMER_21																	= 36;
	
	constexpr uint16 TIMER_22																	= 38;
	constexpr uint16 I2C_1																		= 39;
	
	constexpr uint16 SPI_1																		= 41;
	
	
	constexpr uint16 USART_2																	= 44;
	constexpr uint16 LP_UART_1																= 45;
};



namespace MCU
{
	namespace BASE
	{
		constexpr uint32 PERIPHERAL									= 0x40000000;
		
		constexpr uint32 APB1					        			= PERIPHERAL + 0x00000000;
		constexpr uint32 APB2					        			= PERIPHERAL + 0x00010000;
		constexpr uint32 AHB					        			= PERIPHERAL + 0x00020000;
		constexpr uint32 IOPORT					        		= PERIPHERAL + 0x10000000;
		
		
		
		
		
		constexpr uint32 TIMER_2										= APB1 + 0x00000000;
		constexpr uint32 RTC												= APB1 + 0x00002800;
		constexpr uint32 WWDG												= APB1 + 0x00002C00;
		constexpr uint32 IWDG												= APB1 + 0x00003000;
		constexpr uint32 USART_2										= APB1 + 0x00004400;
		constexpr uint32 LP_UART_1										= APB1 + 0x00004800;
		constexpr uint32 I2C_1											= APB1 + 0x00005400;
		constexpr uint32 PWR												= APB1 + 0x00007000;
		constexpr uint32 LP_TIMER_1									= APB1 + 0x00007C00;
		
		constexpr uint32 SYSCFG											= APB2 + 0x00000000;
		constexpr uint32 EXTI												= APB2 + 0x00000400;
		constexpr uint32 TIMER_21										= APB2 + 0x00000800;
		constexpr uint32 TIMER_22										= APB2 + 0x00001400;
		constexpr uint32 FW													= APB2 + 0x00001C00;
		constexpr uint32 ADC												= APB2 + 0x00002400;
		constexpr uint32 SPI_1											= APB2 + 0x00003000;
		constexpr uint32 DBGMCU											= APB2 + 0x00005800;
		
		constexpr uint32 DMA										    = AHB + 0x00000000;
		constexpr uint32 RCC												= AHB + 0x00001000;
		constexpr uint32 FLASH				 					   	= AHB + 0x00002000;
		constexpr uint32 CRC									    	= AHB + 0x00003000;

		constexpr uint32 GPIO_A									    = IOPORT + 0x00000000;
		constexpr uint32 GPIO_B									    = IOPORT + 0x00000400;
		constexpr uint32 GPIO_C									    = IOPORT + 0x00000800;
		constexpr uint32 GPIO_D									    = IOPORT + 0x00000C00;
		constexpr uint32 GPIO_H									    = IOPORT + 0x00001C00;
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
		volatile uint32* const OR			        			= (volatile uint32* const) (BASE::TIMER_2 + 0x50);
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
	
	namespace PWR
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::PWR + 0x00);
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::PWR + 0x04);
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
	};
	
	namespace SYSCFG
	{
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::SYSCFG + 0x00);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::SYSCFG + 0x04);
		volatile uint32* const EXTI_CR1							= (volatile uint32* const) (BASE::SYSCFG + 0x08);
		volatile uint32* const EXTI_CR2							= (volatile uint32* const) (BASE::SYSCFG + 0x0C);
		volatile uint32* const EXTI_CR3							= (volatile uint32* const) (BASE::SYSCFG + 0x10);
		volatile uint32* const EXTI_CR4							= (volatile uint32* const) (BASE::SYSCFG + 0x14);
		volatile uint32* const CFGR3								= (volatile uint32* const) (BASE::SYSCFG + 0x20);
	};
	
	namespace EXTI
	{
		volatile uint32* const IMR									= (volatile uint32* const) (BASE::EXTI + 0x00);
		volatile uint32* const EMR									= (volatile uint32* const) (BASE::EXTI + 0x04);
		volatile uint32* const RTSR									= (volatile uint32* const) (BASE::EXTI + 0x08);
		volatile uint32* const FTSR									= (volatile uint32* const) (BASE::EXTI + 0x0C);
		volatile uint32* const SWIER								= (volatile uint32* const) (BASE::EXTI + 0x10);
		volatile uint32* const PR										= (volatile uint32* const) (BASE::EXTI + 0x14);
	};
	
	namespace TIMER_21
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x04);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x08);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_21 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x14);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_21 + 0x18);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x2C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x34);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_21 + 0x38);
		volatile uint32* const OR			        			= (volatile uint32* const) (BASE::TIMER_21 + 0x50);
	};
	
	namespace TIMER_22
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x04);
		volatile uint32* const SMCR			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x08);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_22 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x14);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_22 + 0x18);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x2C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x34);
		volatile uint32* const CCR2			        		= (volatile uint32* const) (BASE::TIMER_22 + 0x38);
		volatile uint32* const OR			        			= (volatile uint32* const) (BASE::TIMER_22 + 0x50);
	};
	
	namespace ADC
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC + 0x000);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC + 0x004);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::ADC + 0x008);
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::ADC + 0x00C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC + 0x010);
		volatile uint32* const SMPR									= (volatile uint32* const) (BASE::ADC + 0x014);
		volatile uint32* const TR										= (volatile uint32* const) (BASE::ADC + 0x020);
		volatile uint32* const CHSELR								= (volatile uint32* const) (BASE::ADC + 0x028);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::ADC + 0x040);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC + 0x0B4);
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::ADC + 0x308);
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
	
	namespace DBGMCU
	{
		volatile uint32* const IDC			        		= (volatile uint32* const) (BASE::DBGMCU + 0x00);
		volatile uint32* const CR			        			= (volatile uint32* const) (BASE::DBGMCU + 0x04);
		volatile uint32* const APB1_FZ			        = (volatile uint32* const) (BASE::DBGMCU + 0x08);
		volatile uint32* const APB2_FZ			        = (volatile uint32* const) (BASE::DBGMCU + 0x0C);
	}
	
	namespace DMA
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::DMA + 0x00);
		volatile uint32* const IFCR									= (volatile uint32* const) (BASE::DMA + 0x04);
		
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMA + 0x08);
		volatile uint32* const CH0_NDTR							= (volatile uint32* const) (BASE::DMA + 0x0C);
		volatile uint32* const CH0_PAR							= (volatile uint32* const) (BASE::DMA + 0x10);
		volatile uint32* const CH0_MAR							= (volatile uint32* const) (BASE::DMA + 0x14);
		
		volatile uint32* const CH1_CR								= (volatile uint32* const) (BASE::DMA + 0x1C);
		volatile uint32* const CH1_NDTR							= (volatile uint32* const) (BASE::DMA + 0x20);
		volatile uint32* const CH1_PAR							= (volatile uint32* const) (BASE::DMA + 0x24);
		volatile uint32* const CH1_MAR							= (volatile uint32* const) (BASE::DMA + 0x28);
		
		volatile uint32* const CH2_CR								= (volatile uint32* const) (BASE::DMA + 0x30);
		volatile uint32* const CH2_NDTR							= (volatile uint32* const) (BASE::DMA + 0x34);
		volatile uint32* const CH2_PAR							= (volatile uint32* const) (BASE::DMA + 0x38);
		volatile uint32* const CH2_MAR							= (volatile uint32* const) (BASE::DMA + 0x3C);
		
		volatile uint32* const CH3_CR								= (volatile uint32* const) (BASE::DMA + 0x44);
		volatile uint32* const CH3_NDTR							= (volatile uint32* const) (BASE::DMA + 0x48);
		volatile uint32* const CH3_PAR							= (volatile uint32* const) (BASE::DMA + 0x4C);
		volatile uint32* const CH3_MAR							= (volatile uint32* const) (BASE::DMA + 0x50);
		
		volatile uint32* const CH4_CR								= (volatile uint32* const) (BASE::DMA + 0x58);
		volatile uint32* const CH4_NDTR							= (volatile uint32* const) (BASE::DMA + 0x5C);
		volatile uint32* const CH4_PAR							= (volatile uint32* const) (BASE::DMA + 0x60);
		volatile uint32* const CH4_MAR							= (volatile uint32* const) (BASE::DMA + 0x64);
		
		volatile uint32* const CH5_CR								= (volatile uint32* const) (BASE::DMA + 0x6C);
		volatile uint32* const CH5_NDTR							= (volatile uint32* const) (BASE::DMA + 0x70);
		volatile uint32* const CH5_PAR							= (volatile uint32* const) (BASE::DMA + 0x74);
		volatile uint32* const CH5_MAR							= (volatile uint32* const) (BASE::DMA + 0x78);
		
		volatile uint32* const CH6_CR								= (volatile uint32* const) (BASE::DMA + 0x80);
		volatile uint32* const CH6_NDTR							= (volatile uint32* const) (BASE::DMA + 0x84);
		volatile uint32* const CH6_PAR							= (volatile uint32* const) (BASE::DMA + 0x88);
		volatile uint32* const CH6_MAR							= (volatile uint32* const) (BASE::DMA + 0x8C);
		
		volatile uint32* const CSELR								= (volatile uint32* const) (BASE::DMA + 0xA8);
	};
	
	namespace RCC
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::RCC + 0x00);
		volatile uint32* const ICSCR								= (volatile uint32* const) (BASE::RCC + 0x04);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::RCC + 0x0C);
		volatile uint32* const CIER									= (volatile uint32* const) (BASE::RCC + 0x10);
		volatile uint32* const CIFR									= (volatile uint32* const) (BASE::RCC + 0x14);
		volatile uint32* const CICR									= (volatile uint32* const) (BASE::RCC + 0x18);
		volatile uint32* const IOP_RSTR							= (volatile uint32* const) (BASE::RCC + 0x1C);
		volatile uint32* const AHB_RSTR							= (volatile uint32* const) (BASE::RCC + 0x20);
		volatile uint32* const APB2_RSTR						= (volatile uint32* const) (BASE::RCC + 0x24);
		volatile uint32* const APB1_RSTR						= (volatile uint32* const) (BASE::RCC + 0x28);
		volatile uint32* const IOP_ENR							= (volatile uint32* const) (BASE::RCC + 0x2C);
		volatile uint32* const AHB_ENR							= (volatile uint32* const) (BASE::RCC + 0x30);
		volatile uint32* const APB2_ENR							= (volatile uint32* const) (BASE::RCC + 0x34);
		volatile uint32* const APB1_ENR							= (volatile uint32* const) (BASE::RCC + 0x38);
		volatile uint32* const IOP_SM_ENR						= (volatile uint32* const) (BASE::RCC + 0x3C);
		volatile uint32* const AHB_SM_ENR						= (volatile uint32* const) (BASE::RCC + 0x40);
		volatile uint32* const APB2_SM_ENR					= (volatile uint32* const) (BASE::RCC + 0x44);
		volatile uint32* const APB1_SM_ENR					= (volatile uint32* const) (BASE::RCC + 0x48);
		volatile uint32* const CCIPR								= (volatile uint32* const) (BASE::RCC + 0x4C);
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::RCC + 0x50);
	};
	
	namespace FLASH
	{
		volatile uint32* const ACR									= (volatile uint32* const) (BASE::FLASH + 0x00);
		volatile uint32* const PECR									= (volatile uint32* const) (BASE::FLASH + 0x04);
		volatile uint32* const PD_KEY								= (volatile uint32* const) (BASE::FLASH + 0x08);
		volatile uint32* const PE_KEY								= (volatile uint32* const) (BASE::FLASH + 0x0C);
		volatile uint32* const PRG_KEY							= (volatile uint32* const) (BASE::FLASH + 0x10);
		volatile uint32* const OPT_KEY							= (volatile uint32* const) (BASE::FLASH + 0x14);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::FLASH + 0x18);
		volatile uint32* const OPTR									= (volatile uint32* const) (BASE::FLASH + 0x1C);
		volatile uint32* const WRPROT_1							= (volatile uint32* const) (BASE::FLASH + 0x20);
		volatile uint32* const WRPROT_2							= (volatile uint32* const) (BASE::FLASH + 0x80);
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
};