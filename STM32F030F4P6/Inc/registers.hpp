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
	constexpr uint16 EXTI_4_to_15															= 23;
	
	constexpr uint16 DMA_CH0																	= 25;
	constexpr uint16 DMA_CH1_CH2															= 26;
	constexpr uint16 DMA_CH3_CH4															= 27;
	constexpr uint16 ADC																			= 28;
	constexpr uint16 TIMER_1_BRK_UPD_TRG_COMM									= 29;
	constexpr uint16 TIMER_1_CAPTURE_COMPARE									= 30;
	
	constexpr uint16 TIMER_3																	= 32;
	
	
	constexpr uint16 TIMER_14																	= 35;
	
	constexpr uint16 TIMER_16																	= 37;
	constexpr uint16 TIMER_17																	= 38;
	constexpr uint16 I2C_1																		= 39;
	
	constexpr uint16 SPI_1																		= 41;
	
	constexpr uint16 USART_1																	= 43;
};



namespace MCU
{
	namespace BASE
	{
		constexpr uint32 PERIPHERAL									= 0x40000000;
		
		constexpr uint32 APB					        			= PERIPHERAL + 0x00000000;
		
		constexpr uint32 AHB1					        			= PERIPHERAL + 0x00020000;
		constexpr uint32 AHB2					        			= PERIPHERAL + 0x08000000;
		
		
		
		
		
		constexpr uint32 TIMER_3										= APB + 0x00000400;
		constexpr uint32 TIMER_14										= APB + 0x00002000;
		constexpr uint32 RTC												= APB + 0x00002800;
		constexpr uint32 WWDG												= APB + 0x00002C00;
		constexpr uint32 IWDG												= APB + 0x00003000;
		constexpr uint32 I2C_1											= APB + 0x00005400;
		constexpr uint32 PWR												= APB + 0x00007000;
		constexpr uint32 SYSCFG											= APB + 0x00010000;
		constexpr uint32 EXTI												= APB + 0x00010400;
		constexpr uint32 ADC												= APB + 0x00012400;
		constexpr uint32 TIMER_1										= APB + 0x00012C00;
		constexpr uint32 SPI_1											= APB + 0x00013000;
		constexpr uint32 USART_1										= APB + 0x00013800;
		constexpr uint32 TIMER_16										= APB + 0x00014400;
		constexpr uint32 TIMER_17										= APB + 0x00014800;
		constexpr uint32 DBGMCU											= APB + 0x00015800;
		
		constexpr uint32 DMA										    = AHB1 + 0x00000000;
		constexpr uint32 RCC												= AHB1 + 0x00001000;
		constexpr uint32 FLASH				 					   	= AHB1 + 0x00002000;
		constexpr uint32 CRC									    	= AHB1 + 0x00003000;

		constexpr uint32 GPIO_A									    = AHB2 + 0x00000000;
		constexpr uint32 GPIO_B									    = AHB2 + 0x00000400;
		constexpr uint32 GPIO_F									    = AHB2 + 0x00001400;
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
	};
	
	namespace TIMER_14
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x00);
		volatile uint32* const DIER			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_14 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x14);
		volatile uint32* const CCMR1			        	= (volatile uint32* const) (BASE::TIMER_14 + 0x18);
		volatile uint32* const CCER			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x20);
		volatile uint32* const CNT			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x24);
		volatile uint32* const PSC			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x2C);
		volatile uint32* const CCR1			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x34);
		volatile uint32* const OR			        			= (volatile uint32* const) (BASE::TIMER_14 + 0x50);
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
		volatile uint32* const WPR				        	= (volatile uint32* const) (BASE::RTC + 0x24);
		volatile uint32* const SSR				        	= (volatile uint32* const) (BASE::RTC + 0x28);
		volatile uint32* const SHIFTR				        = (volatile uint32* const) (BASE::RTC + 0x2C);
		volatile uint32* const TSTR				        	= (volatile uint32* const) (BASE::RTC + 0x30);
		volatile uint32* const TSDR				        	= (volatile uint32* const) (BASE::RTC + 0x34);
		volatile uint32* const TSSSR				        = (volatile uint32* const) (BASE::RTC + 0x38);
		volatile uint32* const CALR				        	= (volatile uint32* const) (BASE::RTC + 0x3C);
		volatile uint32* const TAFCR				        = (volatile uint32* const) (BASE::RTC + 0x40);
		volatile uint32* const ALRMASSR				      = (volatile uint32* const) (BASE::RTC + 0x44);
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
	
	namespace SYSCFG
	{
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::SYSCFG + 0x00);
		volatile uint32* const EXTI_CR1							= (volatile uint32* const) (BASE::SYSCFG + 0x08);
		volatile uint32* const EXTI_CR2							= (volatile uint32* const) (BASE::SYSCFG + 0x0C);
		volatile uint32* const EXTI_CR3							= (volatile uint32* const) (BASE::SYSCFG + 0x10);
		volatile uint32* const EXTI_CR4							= (volatile uint32* const) (BASE::SYSCFG + 0x14);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::SYSCFG + 0x18);
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
		volatile uint32* const CCR									= (volatile uint32* const) (BASE::ADC + 0x308);
	};
	
	namespace TIMER_1
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x04);
		volatile uint32* const SMCR				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x08);
		volatile uint32* const DIER				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x0C);
		volatile uint32* const SR				        	  = (volatile uint32* const) (BASE::TIMER_1 + 0x10);
		volatile uint32* const EGR				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x14);
		volatile uint32* const CCMR1				        = (volatile uint32* const) (BASE::TIMER_1 + 0x18);
		volatile uint32* const CCMR2				        = (volatile uint32* const) (BASE::TIMER_1 + 0x1C);
		volatile uint32* const CCER				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x20);
		volatile uint32* const CNT				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x24);
		volatile uint32* const PSC				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x28);
		volatile uint32* const ARR				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x2C);
		volatile uint32* const RCR				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x30);
		volatile uint32* const CCR1				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x34);
		volatile uint32* const CCR2				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x38);
		volatile uint32* const CCR3				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x3C);
		volatile uint32* const CCR4				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x40);
		volatile uint32* const BDTR				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x44);
		volatile uint32* const DCR				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x48);
		volatile uint32* const DMAR				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x4C);
	};
	
	namespace SPI_1
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::SPI_1 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::SPI_1 + 0x04);
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::SPI_1 + 0x08);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::SPI_1 + 0x0C);
		volatile uint32* const CRCPOLY				      = (volatile uint32* const) (BASE::SPI_1 + 0x10);
		volatile uint32* const RXCRC				        = (volatile uint32* const) (BASE::SPI_1 + 0x14);
		volatile uint32* const TXCRC				        = (volatile uint32* const) (BASE::SPI_1 + 0x18);
	};
	
	namespace USART_1
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::USART_1 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::USART_1 + 0x04);
		volatile uint32* const CR3				        	= (volatile uint32* const) (BASE::USART_1 + 0x08);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::USART_1 + 0x0C);
		volatile uint32* const RTOR				        	= (volatile uint32* const) (BASE::USART_1 + 0x14);
		volatile uint32* const RQR				        	= (volatile uint32* const) (BASE::USART_1 + 0x18);
		volatile uint32* const ISR				        	= (volatile uint32* const) (BASE::USART_1 + 0x1C);
		volatile uint32* const ICR				        	= (volatile uint32* const) (BASE::USART_1 + 0x20);
		volatile uint32* const RDR				        	= (volatile uint32* const) (BASE::USART_1 + 0x24);
		volatile uint32* const TDR				        	= (volatile uint32* const) (BASE::USART_1 + 0x28);
	};
	
	namespace TIMER_16
	{
		volatile uint32* const CR1                  = (volatile uint32* const) (BASE::TIMER_16 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x04);
		volatile uint32* const DIER				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x0C);
		volatile uint32* const SR				        	  = (volatile uint32* const) (BASE::TIMER_16 + 0x10);
		volatile uint32* const EGR				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x14);
		volatile uint32* const CCMR1				        = (volatile uint32* const) (BASE::TIMER_16 + 0x18);
		volatile uint32* const CCER				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x20);
		volatile uint32* const CNT				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x24);
		volatile uint32* const PSC				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x28);
		volatile uint32* const ARR				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x2C);
		volatile uint32* const RCR				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x30);
		volatile uint32* const CCR1				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x34);
		volatile uint32* const BDTR				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x44);
		volatile uint32* const DCR				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x48);
		volatile uint32* const DMAR				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x4C);
	};
	
	namespace TIMER_17
	{
		volatile uint32* const CR1                  = (volatile uint32* const) (BASE::TIMER_17 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x04);
		volatile uint32* const DIER				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x0C);
		volatile uint32* const SR				        	  = (volatile uint32* const) (BASE::TIMER_17 + 0x10);
		volatile uint32* const EGR				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x14);
		volatile uint32* const CCMR1				        = (volatile uint32* const) (BASE::TIMER_17 + 0x18);
		volatile uint32* const CCER				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x20);
		volatile uint32* const CNT				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x24);
		volatile uint32* const PSC				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x28);
		volatile uint32* const ARR				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x2C);
		volatile uint32* const RCR				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x30);
		volatile uint32* const CCR1				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x34);
		volatile uint32* const BDTR				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x44);
		volatile uint32* const DCR				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x48);
		volatile uint32* const DMAR				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x4C);
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
	};
	
	namespace RCC
	{
		volatile uint32* const CR										= (volatile uint32* const) (BASE::RCC + 0x00);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::RCC + 0x04);
		volatile uint32* const CIR									= (volatile uint32* const) (BASE::RCC + 0x08);
		volatile uint32* const APB2_RSTR						= (volatile uint32* const) (BASE::RCC + 0x0C);
		volatile uint32* const APB1_RSTR						= (volatile uint32* const) (BASE::RCC + 0x10);
		volatile uint32* const AHB_ENR							= (volatile uint32* const) (BASE::RCC + 0x14);
		volatile uint32* const APB2_ENR							= (volatile uint32* const) (BASE::RCC + 0x18);
		volatile uint32* const APB1_ENR							= (volatile uint32* const) (BASE::RCC + 0x1C);
		volatile uint32* const BDCR									= (volatile uint32* const) (BASE::RCC + 0x20);
		volatile uint32* const CSR									= (volatile uint32* const) (BASE::RCC + 0x24);
		volatile uint32* const AHB_RSTR							= (volatile uint32* const) (BASE::RCC + 0x28);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::RCC + 0x2C);
		volatile uint32* const CFGR3								= (volatile uint32* const) (BASE::RCC + 0x30);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::RCC + 0x34);
	};
	
	namespace FLASH
	{
		volatile uint32* const ACR									= (volatile uint32* const) (BASE::FLASH + 0x00);
		volatile uint32* const KEY									= (volatile uint32* const) (BASE::FLASH + 0x04);
		volatile uint32* const OPTKEY								= (volatile uint32* const) (BASE::FLASH + 0x08);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::FLASH + 0x0C);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::FLASH + 0x10);
		volatile uint32* const AR										= (volatile uint32* const) (BASE::FLASH + 0x14);
		volatile uint32* const OBR									= (volatile uint32* const) (BASE::FLASH + 0x1C);
		volatile uint32* const WRPR									= (volatile uint32* const) (BASE::FLASH + 0x20);
	};
	
	namespace CRC
	{
		volatile uint32* const DR										= (volatile uint32* const) (BASE::CRC + 0x00);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::CRC + 0x04);
		volatile uint32* const CR										= (volatile uint32* const) (BASE::CRC + 0x08);
		volatile uint32* const INIT									= (volatile uint32* const) (BASE::CRC + 0x10);
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
	
	namespace GPIO_F
	{
		volatile uint32* const MODE									= (volatile uint32* const) (BASE::GPIO_F + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_F + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_F + 0x08);
		volatile uint32* const PUPD									= (volatile uint32* const) (BASE::GPIO_F + 0x0C);
		volatile uint32* const IDR									= (volatile uint32* const) (BASE::GPIO_F + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_F + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_F + 0x18);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_F + 0x28);
	};
};