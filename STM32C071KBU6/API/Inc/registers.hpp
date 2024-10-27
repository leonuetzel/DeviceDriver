#pragma once

#include "cmos.hpp"





namespace Interrupt
{
	constexpr uint16 WWDG																			= 16;
	
	constexpr uint16 RTC																			= 18;
	constexpr uint16 FLASH																		= 19;
	constexpr uint16 RCC_CRS																	= 20;
	constexpr uint16 EXTI_0_TO_1															= 21;
	constexpr uint16 EXTI_2_TO_3															= 22;
	constexpr uint16 EXTI_4_TO_15_DMAMUX											= 23;
	constexpr uint16 USB																			= 24;
	constexpr uint16 DMA1_CH0																	= 25;
	constexpr uint16 DMA1_CH1_CH2															= 26;
	constexpr uint16 DMA1_CH3_CH4_DMAMUX											= 27;
	constexpr uint16 ADC																			= 28;
	constexpr uint16 TIMER_1_BREAK_UPDATE_TRIGGER_COMMUTATION	= 29;
	constexpr uint16 TIMER_1_CAPTURE_COMPARE									= 30;
	constexpr uint16 TIMER_2																	= 31;
	constexpr uint16 TIMER_3																	= 32;
	
	
	constexpr uint16 TIMER_14																	= 35;
	
	constexpr uint16 TIMER_16																	= 37;
	constexpr uint16 TIMER_17																	= 38;
	constexpr uint16 I2C_1																		= 39;
	constexpr uint16 I2C_2																		= 40;
	constexpr uint16 SPI_1																		= 41;
	constexpr uint16 SPI_2																		= 42;
	constexpr uint16 USART_1																	= 43;
	constexpr uint16 USART_2																	= 44;
};



namespace MCU
{
	namespace BASE
	{
		constexpr uint32 PERIPHERAL									= 0x40000000;
		
		constexpr uint32 APB					        			= PERIPHERAL + 0x00000000;
		constexpr uint32 AHB					        			= PERIPHERAL + 0x00020000;
		constexpr uint32 IOPORT					        		= PERIPHERAL + 0x10000000;
		
		
		
		
		
		constexpr uint32 TIMER_2										= APB 		+ 0x00000000;
		constexpr uint32 TIMER_3										= APB 		+ 0x00000400;
		constexpr uint32 TIMER_14										= APB 		+ 0x00002000;
		constexpr uint32 RTC		    								= APB 		+ 0x00002800;
		constexpr uint32 WWDG		    								= APB 		+ 0x00002C00;
		constexpr uint32 IWDG		    								= APB 		+ 0x00003000;
		constexpr uint32 SPI_2		    							= APB 		+ 0x00003800;
		constexpr uint32 USART_2										= APB 		+ 0x00004400;
		constexpr uint32 I2C_1			    						= APB 		+ 0x00005400;
		constexpr uint32 I2C_2		    							= APB 		+ 0x00005800;
		constexpr uint32 USB		    								= APB 		+ 0x00005C00;
		constexpr uint32 CRS		    								= APB 		+ 0x00006C00;
		constexpr uint32 PWR	    									= APB 		+ 0x00007000;
		constexpr uint32 USB_SRAM	    							= APB 		+ 0x00009800;
		constexpr uint32 SYSCFG	    								= APB 		+ 0x00010000;
		constexpr uint32 ADC	    									= APB 		+ 0x00012400;
		constexpr uint32 TIMER_1										= APB 		+ 0x00012C00;
		constexpr uint32 SPI_1											= APB 		+ 0x00013000;
		constexpr uint32 USART_1										= APB 		+ 0x00013800;
		constexpr uint32 TIMER_16										= APB 		+ 0x00014400;
		constexpr uint32 TIMER_17										= APB 		+ 0x00014800;
		constexpr uint32 DBG												= APB 		+ 0x00015800;
		
		constexpr uint32 DMA			        					= AHB	 		+ 0x00000000;
		constexpr uint32 DMAMUX			        				= AHB	 		+ 0x00000800;
		constexpr uint32 RCC			    							= AHB	 		+ 0x00001000;
		constexpr uint32 EXTI			    							= AHB	 		+ 0x00001800;
		constexpr uint32 FLASH			    						= AHB	 		+ 0x00002000;
		constexpr uint32 CRC			    							= AHB	 		+ 0x00003000;
		
		constexpr uint32 GPIO_A			    						= IOPORT	+ 0x00000000;
		constexpr uint32 GPIO_B			    						= IOPORT	+ 0x00000400;
		constexpr uint32 GPIO_C			    						= IOPORT	+ 0x00000800;
		constexpr uint32 GPIO_F			    						= IOPORT	+ 0x00001400;
	};
	
	
	
	namespace TIMER_2
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::TIMER_2 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::TIMER_2 + 0x04);
		volatile uint32* const SMCR			    				= (volatile uint32* const) (BASE::TIMER_2 + 0x08);
		volatile uint32* const DIER		    					= (volatile uint32* const) (BASE::TIMER_2 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_2 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x14);
		volatile uint32* const CCMR1		    				= (volatile uint32* const) (BASE::TIMER_2 + 0x18);
		volatile uint32* const CCMR2		    				= (volatile uint32* const) (BASE::TIMER_2 + 0x1C);
		volatile uint32* const CCER		    					= (volatile uint32* const) (BASE::TIMER_2 + 0x20);
		volatile uint32* const CNT		        			= (volatile uint32* const) (BASE::TIMER_2 + 0x24);
		volatile uint32* const PSC		        			= (volatile uint32* const) (BASE::TIMER_2 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x2C);
		volatile uint32* const CCR1		    					= (volatile uint32* const) (BASE::TIMER_2 + 0x34);
		volatile uint32* const CCR2				    			= (volatile uint32* const) (BASE::TIMER_2 + 0x38);
		volatile uint32* const CCR3		   		    		= (volatile uint32* const) (BASE::TIMER_2 + 0x3C);
		volatile uint32* const CCR4		    					= (volatile uint32* const) (BASE::TIMER_2 + 0x40);
		volatile uint32* const DCR				        	= (volatile uint32* const) (BASE::TIMER_2 + 0x48);
		volatile uint32* const DMAR		    					= (volatile uint32* const) (BASE::TIMER_2 + 0x4C);
		volatile uint32* const AF1		    					= (volatile uint32* const) (BASE::TIMER_2 + 0x60);
		volatile uint32* const TISEL		    				= (volatile uint32* const) (BASE::TIMER_2 + 0x68);
	};
	
	namespace TIMER_3
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::TIMER_3 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::TIMER_3 + 0x04);
		volatile uint32* const SMCR			    				= (volatile uint32* const) (BASE::TIMER_3 + 0x08);
		volatile uint32* const DIER		    					= (volatile uint32* const) (BASE::TIMER_3 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_3 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x14);
		volatile uint32* const CCMR1		    				= (volatile uint32* const) (BASE::TIMER_3 + 0x18);
		volatile uint32* const CCMR2		    				= (volatile uint32* const) (BASE::TIMER_3 + 0x1C);
		volatile uint32* const CCER		    					= (volatile uint32* const) (BASE::TIMER_3 + 0x20);
		volatile uint32* const CNT		        			= (volatile uint32* const) (BASE::TIMER_3 + 0x24);
		volatile uint32* const PSC		        			= (volatile uint32* const) (BASE::TIMER_3 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_3 + 0x2C);
		volatile uint32* const CCR1		    					= (volatile uint32* const) (BASE::TIMER_3 + 0x34);
		volatile uint32* const CCR2				    			= (volatile uint32* const) (BASE::TIMER_3 + 0x38);
		volatile uint32* const CCR3		   		    		= (volatile uint32* const) (BASE::TIMER_3 + 0x3C);
		volatile uint32* const CCR4		    					= (volatile uint32* const) (BASE::TIMER_3 + 0x40);
		volatile uint32* const DCR				        	= (volatile uint32* const) (BASE::TIMER_3 + 0x48);
		volatile uint32* const DMAR		    					= (volatile uint32* const) (BASE::TIMER_3 + 0x4C);
		volatile uint32* const AF1		    					= (volatile uint32* const) (BASE::TIMER_3 + 0x60);
		volatile uint32* const TISEL		    				= (volatile uint32* const) (BASE::TIMER_3 + 0x68);
	};
	
	namespace TIMER_14
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::TIMER_14 + 0x00);
		volatile uint32* const DIER		    					= (volatile uint32* const) (BASE::TIMER_14 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_14 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x14);
		volatile uint32* const CCMR1		    				= (volatile uint32* const) (BASE::TIMER_14 + 0x18);
		volatile uint32* const CCER		    					= (volatile uint32* const) (BASE::TIMER_14 + 0x20);
		volatile uint32* const CNT		        			= (volatile uint32* const) (BASE::TIMER_14 + 0x24);
		volatile uint32* const PSC		        			= (volatile uint32* const) (BASE::TIMER_14 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_14 + 0x2C);
		volatile uint32* const CCR1		    					= (volatile uint32* const) (BASE::TIMER_14 + 0x34);
		volatile uint32* const TISEL		    				= (volatile uint32* const) (BASE::TIMER_14 + 0x68);
	};
	
	namespace RTC
	{
		volatile uint32* const TR				    				= (volatile uint32* const) (BASE::RTC + 0x00);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::RTC + 0x04);
		volatile uint32* const SSR				  				= (volatile uint32* const) (BASE::RTC + 0x08);
		volatile uint32* const ICSR									= (volatile uint32* const) (BASE::RTC + 0x0C);
		volatile uint32* const PRER									= (volatile uint32* const) (BASE::RTC + 0x10);
		volatile uint32* const CR        						= (volatile uint32* const) (BASE::RTC + 0x18);
		volatile uint32* const WPR		      				= (volatile uint32* const) (BASE::RTC + 0x24);
		volatile uint32* const CALR		      				= (volatile uint32* const) (BASE::RTC + 0x28);
		volatile uint32* const SHIFTR								= (volatile uint32* const) (BASE::RTC + 0x2C);
		volatile uint32* const TSTR        					= (volatile uint32* const) (BASE::RTC + 0x30);
		volatile uint32* const TSDR        					= (volatile uint32* const) (BASE::RTC + 0x34);
		volatile uint32* const TSSSR        				= (volatile uint32* const) (BASE::RTC + 0x38);
		volatile uint32* const ALRMAR       				= (volatile uint32* const) (BASE::RTC + 0x40);
		volatile uint32* const ALRMASSR     				= (volatile uint32* const) (BASE::RTC + 0x44);
		volatile uint32* const SR        						= (volatile uint32* const) (BASE::RTC + 0x50);
		volatile uint32* const MISR        					= (volatile uint32* const) (BASE::RTC + 0x54);
		volatile uint32* const SCR        					= (volatile uint32* const) (BASE::RTC + 0x5C);
	};
	
	namespace WWDG
	{
		volatile uint32* const CR					        	= (volatile uint32* const) (BASE::WWDG + 0x00);
		volatile uint32* const CFR        					= (volatile uint32* const) (BASE::WWDG + 0x04);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::WWDG + 0x08);
	};
	
	namespace IWDG
	{
		volatile uint32* const KR				        		= (volatile uint32* const) (BASE::IWDG + 0x00);
		volatile uint32* const PR				        		= (volatile uint32* const) (BASE::IWDG + 0x04);
		volatile uint32* const RLR		        			= (volatile uint32* const) (BASE::IWDG + 0x08);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::IWDG + 0x0C);
		volatile uint32* const WINR			        		= (volatile uint32* const) (BASE::IWDG + 0x10);
	};
	
	namespace SPI_2
	{
		volatile uint32* const CR1		    			    = (volatile uint32* const) (BASE::SPI_2 + 0x00);
		volatile uint32* const CR2       						= (volatile uint32* const) (BASE::SPI_2 + 0x04);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::SPI_2 + 0x08);
		volatile uint32* const DR					        	= (volatile uint32* const) (BASE::SPI_2 + 0x0C);
		volatile uint32* const CRCPR     						= (volatile uint32* const) (BASE::SPI_2 + 0x10);
		volatile uint32* const RXCRCR	    					= (volatile uint32* const) (BASE::SPI_2 + 0x14);
		volatile uint32* const TXCRCR		    				= (volatile uint32* const) (BASE::SPI_2 + 0x18);
		volatile uint32* const I2SCFGR			    		= (volatile uint32* const) (BASE::SPI_2 + 0x1C);
		volatile uint32* const I2SPR     						= (volatile uint32* const) (BASE::SPI_2 + 0x20);
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
	
	namespace I2C_1
	{
		volatile uint32* const CR1			  					= (volatile uint32* const) (BASE::I2C_1 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::I2C_1 + 0x04);
		volatile uint32* const OAR1			  					= (volatile uint32* const) (BASE::I2C_1 + 0x08);
		volatile uint32* const OAR2			  					= (volatile uint32* const) (BASE::I2C_1 + 0x0C);
		volatile uint32* const TIMINGR							= (volatile uint32* const) (BASE::I2C_1 + 0x10);
		volatile uint32* const TIMEOUTR							= (volatile uint32* const) (BASE::I2C_1 + 0x14);
		volatile uint32* const ISR			  					= (volatile uint32* const) (BASE::I2C_1 + 0x18);
		volatile uint32* const ICR			  					= (volatile uint32* const) (BASE::I2C_1 + 0x1C);
		volatile uint32* const PECR			  					= (volatile uint32* const) (BASE::I2C_1 + 0x20);
		volatile uint32* const RXDR			  					= (volatile uint32* const) (BASE::I2C_1 + 0x24);
		volatile uint32* const TXDR			  					= (volatile uint32* const) (BASE::I2C_1 + 0x28);
	};
	
	namespace I2C_2
	{
		volatile uint32* const CR1			  					= (volatile uint32* const) (BASE::I2C_2 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::I2C_2 + 0x04);
		volatile uint32* const OAR1			  					= (volatile uint32* const) (BASE::I2C_2 + 0x08);
		volatile uint32* const OAR2			  					= (volatile uint32* const) (BASE::I2C_2 + 0x0C);
		volatile uint32* const TIMINGR							= (volatile uint32* const) (BASE::I2C_2 + 0x10);
		volatile uint32* const TIMEOUTR							= (volatile uint32* const) (BASE::I2C_2 + 0x14);
		volatile uint32* const ISR			  					= (volatile uint32* const) (BASE::I2C_2 + 0x18);
		volatile uint32* const ICR			  					= (volatile uint32* const) (BASE::I2C_2 + 0x1C);
		volatile uint32* const PECR			  					= (volatile uint32* const) (BASE::I2C_2 + 0x20);
		volatile uint32* const RXDR			  					= (volatile uint32* const) (BASE::I2C_2 + 0x24);
		volatile uint32* const TXDR			  					= (volatile uint32* const) (BASE::I2C_2 + 0x28);
	};
	
	namespace USB
	{
		volatile uint32* const CHEP0			  					= (volatile uint32* const) (BASE::USB + 0x00);
		volatile uint32* const CHEP1									= (volatile uint32* const) (BASE::USB + 0x04);
		volatile uint32* const CHEP2			  					= (volatile uint32* const) (BASE::USB + 0x08);
		volatile uint32* const CHEP3			  					= (volatile uint32* const) (BASE::USB + 0x0C);
		volatile uint32* const CHEP4			  					= (volatile uint32* const) (BASE::USB + 0x10);
		volatile uint32* const CHEP5			  					= (volatile uint32* const) (BASE::USB + 0x14);
		volatile uint32* const CHEP6			  					= (volatile uint32* const) (BASE::USB + 0x18);
		volatile uint32* const CHEP7			  					= (volatile uint32* const) (BASE::USB + 0x1C);
		volatile uint32* const CNTR			  						= (volatile uint32* const) (BASE::USB + 0x40);
		volatile uint32* const ISTR			  						= (volatile uint32* const) (BASE::USB + 0x44);
		volatile uint32* const FNR			  						= (volatile uint32* const) (BASE::USB + 0x48);
		volatile uint32* const DADDR			  					= (volatile uint32* const) (BASE::USB + 0x4C);
		volatile uint32* const LPMCSR			  					= (volatile uint32* const) (BASE::USB + 0x54);
		volatile uint32* const BCDR			  						= (volatile uint32* const) (BASE::USB + 0x58);
		
		namespace SRAM
		{
			volatile uint32* const CHEP0_TXRX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x00);
			volatile uint32* const CHEP0_RXTX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x04);
			volatile uint32* const CHEP1_TXRX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x08);
			volatile uint32* const CHEP1_RXTX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x0C);
			volatile uint32* const CHEP2_TXRX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x10);
			volatile uint32* const CHEP2_RXTX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x14);
			volatile uint32* const CHEP3_TXRX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x18);
			volatile uint32* const CHEP3_RXTX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x1C);
			volatile uint32* const CHEP4_TXRX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x20);
			volatile uint32* const CHEP4_RXTX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x24);
			volatile uint32* const CHEP5_TXRX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x28);
			volatile uint32* const CHEP5_RXTX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x2C);
			volatile uint32* const CHEP6_TXRX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x30);
			volatile uint32* const CHEP6_RXTX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x34);
			volatile uint32* const CHEP7_TXRX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x38);
			volatile uint32* const CHEP7_RXTX_BD				= (volatile uint32* const) (BASE::USB_SRAM + 0x3C);
		};
	};
	
	namespace CRS
	{
		volatile uint32* const CR			  						= (volatile uint32* const) (BASE::CRS + 0x00);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::CRS + 0x04);
		volatile uint32* const ISR			  					= (volatile uint32* const) (BASE::CRS + 0x08);
		volatile uint32* const ICR			  					= (volatile uint32* const) (BASE::CRS + 0x0C);
	};
	
	namespace PWR
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::PWR + 0x00);
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
		volatile uint32* const PUCRF								= (volatile uint32* const) (BASE::PWR + 0x48);
		volatile uint32* const PDCRF								= (volatile uint32* const) (BASE::PWR + 0x4C);
		volatile uint32* const BKP0R								= (volatile uint32* const) (BASE::PWR + 0x70);
		volatile uint32* const BKP1R								= (volatile uint32* const) (BASE::PWR + 0x74);
		volatile uint32* const BKP2R								= (volatile uint32* const) (BASE::PWR + 0x78);
		volatile uint32* const BKP3R								= (volatile uint32* const) (BASE::PWR + 0x7C);
	};
	
	namespace SYSCFG
	{
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::SYSCFG + 0x00);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::SYSCFG + 0x18);
		volatile uint32* const CFGR3								= (volatile uint32* const) (BASE::SYSCFG + 0x3C);
		volatile uint32* const ITLINE_0							= (volatile uint32* const) (BASE::SYSCFG + 0x80);
		volatile uint32* const ITLINE_2							= (volatile uint32* const) (BASE::SYSCFG + 0x88);
		volatile uint32* const ITLINE_3							= (volatile uint32* const) (BASE::SYSCFG + 0x8C);
		volatile uint32* const ITLINE_4							= (volatile uint32* const) (BASE::SYSCFG + 0x90);
		volatile uint32* const ITLINE_5							= (volatile uint32* const) (BASE::SYSCFG + 0x94);
		volatile uint32* const ITLINE_6							= (volatile uint32* const) (BASE::SYSCFG + 0x98);
		volatile uint32* const ITLINE_7							= (volatile uint32* const) (BASE::SYSCFG + 0x9C);
		volatile uint32* const ITLINE_9							= (volatile uint32* const) (BASE::SYSCFG + 0xA4);
		volatile uint32* const ITLINE_10						= (volatile uint32* const) (BASE::SYSCFG + 0xA8);
		volatile uint32* const ITLINE_11						= (volatile uint32* const) (BASE::SYSCFG + 0xAC);
		volatile uint32* const ITLINE_12						= (volatile uint32* const) (BASE::SYSCFG + 0xB0);
		volatile uint32* const ITLINE_13						= (volatile uint32* const) (BASE::SYSCFG + 0xB4);
		volatile uint32* const ITLINE_14						= (volatile uint32* const) (BASE::SYSCFG + 0xB8);
		volatile uint32* const ITLINE_16						= (volatile uint32* const) (BASE::SYSCFG + 0xC0);
		volatile uint32* const ITLINE_19						= (volatile uint32* const) (BASE::SYSCFG + 0xCC);
		volatile uint32* const ITLINE_21						= (volatile uint32* const) (BASE::SYSCFG + 0xD4);
		volatile uint32* const ITLINE_22						= (volatile uint32* const) (BASE::SYSCFG + 0xD8);
		volatile uint32* const ITLINE_23						= (volatile uint32* const) (BASE::SYSCFG + 0xDC);
		volatile uint32* const ITLINE_25						= (volatile uint32* const) (BASE::SYSCFG + 0xE4);
		volatile uint32* const ITLINE_27						= (volatile uint32* const) (BASE::SYSCFG + 0xEC);
		volatile uint32* const ITLINE_28						= (volatile uint32* const) (BASE::SYSCFG + 0xF0);
	};
	
	namespace ADC
	{
		volatile uint32* const ISR									= (volatile uint32* const) (BASE::ADC + 0x000);
		volatile uint32* const IER									= (volatile uint32* const) (BASE::ADC + 0x004);
		volatile uint32* const CR     							= (volatile uint32* const) (BASE::ADC + 0x008);
		volatile uint32* const CFGR1								= (volatile uint32* const) (BASE::ADC + 0x00C);
		volatile uint32* const CFGR2								= (volatile uint32* const) (BASE::ADC + 0x010);
		volatile uint32* const SMPR									= (volatile uint32* const) (BASE::ADC + 0x014);
		volatile uint32* const AWD1TR 							= (volatile uint32* const) (BASE::ADC + 0x020);
		volatile uint32* const AWD2TR								= (volatile uint32* const) (BASE::ADC + 0x024);
		volatile uint32* const CHSELR 							= (volatile uint32* const) (BASE::ADC + 0x028);
		volatile uint32* const AWD3TR								= (volatile uint32* const) (BASE::ADC + 0x02C);
		volatile uint32* const DR										= (volatile uint32* const) (BASE::ADC + 0x040);
		volatile uint32* const AWD2CR								= (volatile uint32* const) (BASE::ADC + 0x0A0);
		volatile uint32* const AWD3CR								= (volatile uint32* const) (BASE::ADC + 0x0A4);
		volatile uint32* const CALFACT							= (volatile uint32* const) (BASE::ADC + 0x0B4);
		volatile uint32* const CCR    							= (volatile uint32* const) (BASE::ADC + 0x308);
	};
	
	namespace TIMER_1
	{
		volatile uint32* const CR1									= (volatile uint32* const) (BASE::TIMER_1 + 0x00);
		volatile uint32* const CR2									= (volatile uint32* const) (BASE::TIMER_1 + 0x04);
		volatile uint32* const SMCR									= (volatile uint32* const) (BASE::TIMER_1 + 0x08);
		volatile uint32* const DIER 								= (volatile uint32* const) (BASE::TIMER_1 + 0x0C);
		volatile uint32* const SR										= (volatile uint32* const) (BASE::TIMER_1 + 0x10);
		volatile uint32* const EGR  								= (volatile uint32* const) (BASE::TIMER_1 + 0x14);
		volatile uint32* const CCMR1								= (volatile uint32* const) (BASE::TIMER_1 + 0x18);
		volatile uint32* const CCMR2								= (volatile uint32* const) (BASE::TIMER_1 + 0x1C);
		volatile uint32* const CCER									= (volatile uint32* const) (BASE::TIMER_1 + 0x20);
		volatile uint32* const CNT  								= (volatile uint32* const) (BASE::TIMER_1 + 0x24);
		volatile uint32* const PSC									= (volatile uint32* const) (BASE::TIMER_1 + 0x28);
		volatile uint32* const ARR									= (volatile uint32* const) (BASE::TIMER_1 + 0x2C);
		volatile uint32* const RCR									= (volatile uint32* const) (BASE::TIMER_1 + 0x30);
		volatile uint32* const CCR1									= (volatile uint32* const) (BASE::TIMER_1 + 0x34);
		volatile uint32* const CCR2 								= (volatile uint32* const) (BASE::TIMER_1 + 0x38);
		volatile uint32* const CCR3									= (volatile uint32* const) (BASE::TIMER_1 + 0x3C);
		volatile uint32* const CCR4									= (volatile uint32* const) (BASE::TIMER_1 + 0x40);
		volatile uint32* const BDTR 								= (volatile uint32* const) (BASE::TIMER_1 + 0x44);
		volatile uint32* const DCR									= (volatile uint32* const) (BASE::TIMER_1 + 0x48);
		volatile uint32* const DMAR									= (volatile uint32* const) (BASE::TIMER_1 + 0x4C);
		volatile uint32* const CCMR3								= (volatile uint32* const) (BASE::TIMER_1 + 0x54);
		volatile uint32* const CCR5									= (volatile uint32* const) (BASE::TIMER_1 + 0x58);
		volatile uint32* const CCR6									= (volatile uint32* const) (BASE::TIMER_1 + 0x5C);
		volatile uint32* const AF1									= (volatile uint32* const) (BASE::TIMER_1 + 0x60);
		volatile uint32* const AF2									= (volatile uint32* const) (BASE::TIMER_1 + 0x64);
		volatile uint32* const TISEL								= (volatile uint32* const) (BASE::TIMER_1 + 0x68);
	};
	
	namespace SPI_1
	{
		volatile uint32* const CR1		    			    = (volatile uint32* const) (BASE::SPI_1 + 0x00);
		volatile uint32* const CR2       						= (volatile uint32* const) (BASE::SPI_1 + 0x04);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::SPI_1 + 0x08);
		volatile uint32* const DR					        	= (volatile uint32* const) (BASE::SPI_1 + 0x0C);
		volatile uint32* const CRCPR     						= (volatile uint32* const) (BASE::SPI_1 + 0x10);
		volatile uint32* const RXCRCR	    					= (volatile uint32* const) (BASE::SPI_1 + 0x14);
		volatile uint32* const TXCRCR		    				= (volatile uint32* const) (BASE::SPI_1 + 0x18);
		volatile uint32* const I2SCFGR			    		= (volatile uint32* const) (BASE::SPI_1 + 0x1C);
		volatile uint32* const I2SPR     						= (volatile uint32* const) (BASE::SPI_1 + 0x20);
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
	
	namespace TIMER_16
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x04);
		volatile uint32* const DIER		    					= (volatile uint32* const) (BASE::TIMER_16 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_16 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x14);
		volatile uint32* const CCMR1		    				= (volatile uint32* const) (BASE::TIMER_16 + 0x18);
		volatile uint32* const CCER		    					= (volatile uint32* const) (BASE::TIMER_16 + 0x20);
		volatile uint32* const CNT		        			= (volatile uint32* const) (BASE::TIMER_16 + 0x24);
		volatile uint32* const PSC		        			= (volatile uint32* const) (BASE::TIMER_16 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x2C);
		volatile uint32* const RCR			        		= (volatile uint32* const) (BASE::TIMER_16 + 0x30);
		volatile uint32* const CCR1		    					= (volatile uint32* const) (BASE::TIMER_16 + 0x34);
		volatile uint32* const BDTR				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x44);
		volatile uint32* const DCR				        	= (volatile uint32* const) (BASE::TIMER_16 + 0x48);
		volatile uint32* const DMAR		    					= (volatile uint32* const) (BASE::TIMER_16 + 0x4C);
		volatile uint32* const AF1		    					= (volatile uint32* const) (BASE::TIMER_16 + 0x60);
		volatile uint32* const TISEL		    				= (volatile uint32* const) (BASE::TIMER_16 + 0x68);
	};
	
	namespace TIMER_17
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x04);
		volatile uint32* const DIER		    					= (volatile uint32* const) (BASE::TIMER_17 + 0x0C);
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::TIMER_17 + 0x10);
		volatile uint32* const EGR			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x14);
		volatile uint32* const CCMR1		    				= (volatile uint32* const) (BASE::TIMER_17 + 0x18);
		volatile uint32* const CCER		    					= (volatile uint32* const) (BASE::TIMER_17 + 0x20);
		volatile uint32* const CNT		        			= (volatile uint32* const) (BASE::TIMER_17 + 0x24);
		volatile uint32* const PSC		        			= (volatile uint32* const) (BASE::TIMER_17 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x2C);
		volatile uint32* const RCR			        		= (volatile uint32* const) (BASE::TIMER_17 + 0x30);
		volatile uint32* const CCR1		    					= (volatile uint32* const) (BASE::TIMER_17 + 0x34);
		volatile uint32* const BDTR				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x44);
		volatile uint32* const DCR				        	= (volatile uint32* const) (BASE::TIMER_17 + 0x48);
		volatile uint32* const DMAR		    					= (volatile uint32* const) (BASE::TIMER_17 + 0x4C);
		volatile uint32* const AF1		    					= (volatile uint32* const) (BASE::TIMER_17 + 0x60);
		volatile uint32* const TISEL		    				= (volatile uint32* const) (BASE::TIMER_17 + 0x68);
	};
	
	namespace DBG
	{
		volatile uint32* const ID_CODE			      	= (volatile uint32* const) (BASE::DBG + 0x00);
		volatile uint32* const CR			      				= (volatile uint32* const) (BASE::DBG + 0x04);
		volatile uint32* const APB_FZ1			      	= (volatile uint32* const) (BASE::DBG + 0x08);
		volatile uint32* const APB_FZ2			      	= (volatile uint32* const) (BASE::DBG + 0x0C);
	};
	
	
	
	
	
	namespace DMA
	{
		volatile uint32* const ISR	        				= (volatile uint32* const) (BASE::DMA + 0x00);
		volatile uint32* const IFCR			        		= (volatile uint32* const) (BASE::DMA + 0x04);
		
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMA + 0x08);
		volatile uint32* const CH0_NDTR							= (volatile uint32* const) (BASE::DMA + 0x0C);
		volatile uint32* const CH0_PAR							= (volatile uint32* const) (BASE::DMA + 0x10);
		volatile uint32* const CH0_MAR							= (volatile uint32* const) (BASE::DMA + 0x14);
		
		volatile uint32* const CH1_CR      				  = (volatile uint32* const) (BASE::DMA + 0x1C);
		volatile uint32* const CH1_NDTR	    			  = (volatile uint32* const) (BASE::DMA + 0x20);
		volatile uint32* const CH1_PAR			        = (volatile uint32* const) (BASE::DMA + 0x24);
		volatile uint32* const CH1_MAR					    = (volatile uint32* const) (BASE::DMA + 0x28);
		
		volatile uint32* const CH2_CR      					= (volatile uint32* const) (BASE::DMA + 0x30);
		volatile uint32* const CH2_NDTR	    			  = (volatile uint32* const) (BASE::DMA + 0x34);
		volatile uint32* const CH2_PAR			        = (volatile uint32* const) (BASE::DMA + 0x38);
		volatile uint32* const CH2_MAR					    = (volatile uint32* const) (BASE::DMA + 0x3C);
		
		volatile uint32* const CH3_CR      					= (volatile uint32* const) (BASE::DMA + 0x44);
		volatile uint32* const CH3_NDTR	    			  = (volatile uint32* const) (BASE::DMA + 0x48);
		volatile uint32* const CH3_PAR			        = (volatile uint32* const) (BASE::DMA + 0x4C);
		volatile uint32* const CH3_MAR					    = (volatile uint32* const) (BASE::DMA + 0x50);
		
		volatile uint32* const CH4_CR      					= (volatile uint32* const) (BASE::DMA + 0x58);
		volatile uint32* const CH4_NDTR	    			  = (volatile uint32* const) (BASE::DMA + 0x5C);
		volatile uint32* const CH4_PAR			        = (volatile uint32* const) (BASE::DMA + 0x60);
		volatile uint32* const CH4_MAR					    = (volatile uint32* const) (BASE::DMA + 0x64);
	};
	
	namespace DMAMUX
	{
		volatile uint32* const CH0_CR	  						= (volatile uint32* const) (BASE::DMAMUX + 0x000);
		volatile uint32* const CH1_CR	  						= (volatile uint32* const) (BASE::DMAMUX + 0x000);
		volatile uint32* const CH2_CR	  						= (volatile uint32* const) (BASE::DMAMUX + 0x000);
		volatile uint32* const CSR	  							= (volatile uint32* const) (BASE::DMAMUX + 0x080);
		volatile uint32* const CFR    							= (volatile uint32* const) (BASE::DMAMUX + 0x084);
		volatile uint32* const RG_CH0_CR						= (volatile uint32* const) (BASE::DMAMUX + 0x100);
		volatile uint32* const RG_CH1_CR						= (volatile uint32* const) (BASE::DMAMUX + 0x104);
		volatile uint32* const RG_CH2_CR						= (volatile uint32* const) (BASE::DMAMUX + 0x108);
		volatile uint32* const RG_CH3_CR						= (volatile uint32* const) (BASE::DMAMUX + 0x10C);
		volatile uint32* const RG_SR	  						= (volatile uint32* const) (BASE::DMAMUX + 0x140);
		volatile uint32* const RG_CFR								= (volatile uint32* const) (BASE::DMAMUX + 0x144);
	};
	
	namespace RCC
	{
		volatile uint32* const CR      							= (volatile uint32* const) (BASE::RCC + 0x00);
		volatile uint32* const ICSCR	      				= (volatile uint32* const) (BASE::RCC + 0x04);
		volatile uint32* const CFGR									= (volatile uint32* const) (BASE::RCC + 0x08);
		volatile uint32* const CIER									= (volatile uint32* const) (BASE::RCC + 0x18);
		volatile uint32* const CIFR									= (volatile uint32* const) (BASE::RCC + 0x1C);
		volatile uint32* const CICR      						= (volatile uint32* const) (BASE::RCC + 0x20);
		volatile uint32* const IOP_RSTR							= (volatile uint32* const) (BASE::RCC + 0x24);
		volatile uint32* const AHB_RSTR							= (volatile uint32* const) (BASE::RCC + 0x28);
		volatile uint32* const APB_RSTR1						= (volatile uint32* const) (BASE::RCC + 0x2C);
		volatile uint32* const APB_RSTR2						= (volatile uint32* const) (BASE::RCC + 0x30);
		volatile uint32* const IOP_ENR	  					= (volatile uint32* const) (BASE::RCC + 0x34);
		volatile uint32* const AHB_ENR	  					= (volatile uint32* const) (BASE::RCC + 0x38);
		volatile uint32* const APB_ENR1	  					= (volatile uint32* const) (BASE::RCC + 0x3C);
		volatile uint32* const APB_ENR2	  					= (volatile uint32* const) (BASE::RCC + 0x40);
		volatile uint32* const IOP_SMENR						= (volatile uint32* const) (BASE::RCC + 0x44);
		volatile uint32* const AHB_SMENR						= (volatile uint32* const) (BASE::RCC + 0x48);
		volatile uint32* const APB_SMENR1						= (volatile uint32* const) (BASE::RCC + 0x4C);
		volatile uint32* const APB_SMENR2						= (volatile uint32* const) (BASE::RCC + 0x50);
		volatile uint32* const CCIPR	    					= (volatile uint32* const) (BASE::RCC + 0x54);
		volatile uint32* const CSR1	    						= (volatile uint32* const) (BASE::RCC + 0x5C);
		volatile uint32* const CSR2	    						= (volatile uint32* const) (BASE::RCC + 0x60);
	};
	
	namespace EXTI
	{
		volatile uint32* const RTSR1		        		= (volatile uint32* const) (BASE::EXTI + 0x00);
		volatile uint32* const FTSR1		        		= (volatile uint32* const) (BASE::EXTI + 0x04);
		volatile uint32* const SWIER1		        		= (volatile uint32* const) (BASE::EXTI + 0x08);
		volatile uint32* const RPR1		        			= (volatile uint32* const) (BASE::EXTI + 0x0C);
		volatile uint32* const FPR1		        			= (volatile uint32* const) (BASE::EXTI + 0x10);
		volatile uint32* const EXTI_CR1		        	= (volatile uint32* const) (BASE::EXTI + 0x60);
		volatile uint32* const EXTI_CR2		        	= (volatile uint32* const) (BASE::EXTI + 0x64);
		volatile uint32* const EXTI_CR3		        	= (volatile uint32* const) (BASE::EXTI + 0x68);
		volatile uint32* const EXTI_CR4        			= (volatile uint32* const) (BASE::EXTI + 0x6C);
		volatile uint32* const IMR1				        	= (volatile uint32* const) (BASE::EXTI + 0x80);
		volatile uint32* const EMR1       					= (volatile uint32* const) (BASE::EXTI + 0x84);
	};
	
	namespace FLASH
	{
		volatile uint32* const ACR      						= (volatile uint32* const) (BASE::FLASH + 0x00);
		volatile uint32* const KEYR      						= (volatile uint32* const) (BASE::FLASH + 0x08);
		volatile uint32* const OPT_KEYR   					= (volatile uint32* const) (BASE::FLASH + 0x0C);
		volatile uint32* const SR      							= (volatile uint32* const) (BASE::FLASH + 0x10);
		volatile uint32* const CR      							= (volatile uint32* const) (BASE::FLASH + 0x14);
		volatile uint32* const OPTR      						= (volatile uint32* const) (BASE::FLASH + 0x20);
		volatile uint32* const PCROP1ASR  					= (volatile uint32* const) (BASE::FLASH + 0x24);
		volatile uint32* const PCRAP1AER  					= (volatile uint32* const) (BASE::FLASH + 0x28);
		volatile uint32* const WRP1AR     					= (volatile uint32* const) (BASE::FLASH + 0x2C);
		volatile uint32* const WRP1BR     					= (volatile uint32* const) (BASE::FLASH + 0x30);
		volatile uint32* const PCROP1BSR  					= (volatile uint32* const) (BASE::FLASH + 0x34);
		volatile uint32* const PCROP1BER  					= (volatile uint32* const) (BASE::FLASH + 0x38);
		volatile uint32* const SECR      						= (volatile uint32* const) (BASE::FLASH + 0x80);
	};
	
	namespace CRC
	{
		volatile uint32* const DR      							= (volatile uint32* const) (BASE::CRC + 0x00);
		volatile uint32* const IDR      						= (volatile uint32* const) (BASE::CRC + 0x04);
		volatile uint32* const CR      							= (volatile uint32* const) (BASE::CRC + 0x08);
		volatile uint32* const INIT      						= (volatile uint32* const) (BASE::CRC + 0x10);
		volatile uint32* const POL      						= (volatile uint32* const) (BASE::CRC + 0x14);
	};
	
	
	
	
	
	namespace GPIO_A
	{
		volatile uint32* const MODE    							= (volatile uint32* const) (BASE::GPIO_A + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_A + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_A + 0x08);
		volatile uint32* const PUPD    							= (volatile uint32* const) (BASE::GPIO_A + 0x0C);
		volatile uint32* const IDR		  						= (volatile uint32* const) (BASE::GPIO_A + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_A + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_A + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_A + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_A + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_A + 0x24);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_A + 0x28);
	};
	
	namespace GPIO_B
	{
		volatile uint32* const MODE    							= (volatile uint32* const) (BASE::GPIO_B + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_B + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_B + 0x08);
		volatile uint32* const PUPD    							= (volatile uint32* const) (BASE::GPIO_B + 0x0C);
		volatile uint32* const IDR		  						= (volatile uint32* const) (BASE::GPIO_B + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_B + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_B + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_B + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_B + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_B + 0x24);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_B + 0x28);
	};
	
	namespace GPIO_C
	{
		volatile uint32* const MODE    							= (volatile uint32* const) (BASE::GPIO_C + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_C + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_C + 0x08);
		volatile uint32* const PUPD    							= (volatile uint32* const) (BASE::GPIO_C + 0x0C);
		volatile uint32* const IDR		  						= (volatile uint32* const) (BASE::GPIO_C + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_C + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_C + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_C + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_C + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_C + 0x24);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_C + 0x28);
	};
	
	namespace GPIO_F
	{
		volatile uint32* const MODE    							= (volatile uint32* const) (BASE::GPIO_F + 0x00);
		volatile uint32* const OTYPE								= (volatile uint32* const) (BASE::GPIO_F + 0x04);
		volatile uint32* const OSPEED								= (volatile uint32* const) (BASE::GPIO_F + 0x08);
		volatile uint32* const PUPD    							= (volatile uint32* const) (BASE::GPIO_F + 0x0C);
		volatile uint32* const IDR		  						= (volatile uint32* const) (BASE::GPIO_F + 0x10);
		volatile uint32* const ODR									= (volatile uint32* const) (BASE::GPIO_F + 0x14);
		volatile uint32* const BSRR									= (volatile uint32* const) (BASE::GPIO_F + 0x18);
		volatile uint32* const LCKR									= (volatile uint32* const) (BASE::GPIO_F + 0x1C);
		volatile uint32* const AFRL									= (volatile uint32* const) (BASE::GPIO_F + 0x20);
		volatile uint32* const AFRH									= (volatile uint32* const) (BASE::GPIO_F + 0x24);
		volatile uint32* const BRR									= (volatile uint32* const) (BASE::GPIO_F + 0x28);
	};
};