#pragma once

#include "cmos.hpp"





namespace Interrupt
{
	constexpr uint16 WWDG																			= 16;
	constexpr uint16 PVD																			= 17;
	constexpr uint16 TAMPER																		= 18;
	constexpr uint16 RTC																			= 19;
	constexpr uint16 FLASH																		= 20;
	constexpr uint16 RCC																			= 21;
	constexpr uint16 EXTI_0																		= 22;
	constexpr uint16 EXTI_1																		= 23;
	constexpr uint16 EXTI_2																		= 24;
	constexpr uint16 EXTI_3																		= 25;
	constexpr uint16 EXTI_4																		= 26;
	constexpr uint16 DMA_CH0																	= 27;
	constexpr uint16 DMA_CH1																	= 28;
	constexpr uint16 DMA_CH2																	= 29;
	constexpr uint16 DMA_CH3																	= 30;
	constexpr uint16 DMA_CH4																	= 31;
	constexpr uint16 DMA_CH5																	= 32;
	constexpr uint16 DMA_CH6																	= 33;
	constexpr uint16 ADC																			= 34;
	constexpr uint16 CAN_TX																		= 35;
	constexpr uint16 CAN_RX_0																	= 36;
	constexpr uint16 CAN_RX_1																	= 37;
	constexpr uint16 CAN_SCE																	= 38;
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
};



namespace MCU
{
	namespace BASE
	{
		constexpr uint32 PERIPHERAL									= 0x40000000;
		
		constexpr uint32 APB1					        			= PERIPHERAL + 0x00000000;
		constexpr uint32 APB2					        			= PERIPHERAL + 0x00010000;

		constexpr uint32 AHB					        			= PERIPHERAL + 0x00018000;
		
		
		
		
		
		constexpr uint32 DBGMCU											= 0xE0042004;
		
		constexpr uint32 TIMER_2										= APB1 + 0x00000000;
		constexpr uint32 TIMER_3										= APB1 + 0x00000400;
		constexpr uint32 TIMER_4										= APB1 + 0x00000800;
		constexpr uint32 TIMER_5										= APB1 + 0x00000C00;
		constexpr uint32 RTC		    								= APB1 + 0x00002800;
		constexpr uint32 WWDG		    								= APB1 + 0x00002C00;
		constexpr uint32 IWDG		    								= APB1 + 0x00003000;
		constexpr uint32 SPI_2		    							= APB1 + 0x00003800;
		constexpr uint32 USART_2										= APB1 + 0x00004400;
		constexpr uint32 USART_3										= APB1 + 0x00004800;
		constexpr uint32 I2C_1			    						= APB1 + 0x00005400;
		constexpr uint32 I2C_2			    						= APB1 + 0x00005800;
		constexpr uint32 CAN			    							= APB1 + 0x00006400;
		constexpr uint32 BKP	    									= APB1 + 0x00006C00;
		constexpr uint32 PWR	    									= APB1 + 0x00007000;
		
		constexpr uint32 AFIO		    								= APB2 + 0x00000000;
		constexpr uint32 EXTI		    								= APB2 + 0x00000400;
		constexpr uint32 GPIO_A		    							= APB2 + 0x00000800;
		constexpr uint32 GPIO_B		    							= APB2 + 0x00000C00;
		constexpr uint32 GPIO_C		    							= APB2 + 0x00001000;
		constexpr uint32 GPIO_D		    							= APB2 + 0x00001400;
		constexpr uint32 ADC_1		    							= APB2 + 0x00002400;
		constexpr uint32 TIMER_1	    							= APB2 + 0x00002C00;
		constexpr uint32 SPI_1		    							= APB2 + 0x00003000;
		constexpr uint32 USART_1	    							= APB2 + 0x00003800;
		
		constexpr uint32 DMA			        					= AHB	 + 0x00008000;
		constexpr uint32 RCC			    							= AHB	 + 0x00009000;
		constexpr uint32 FLASH			    						= AHB	 + 0x0000A000;
		constexpr uint32 CRC			    							= AHB	 + 0x0000B000;
	};
	
	
	
	namespace DBGMCU
	{
		volatile uint32* const CR			      				= (volatile uint32* const) (BASE::DBGMCU + 0x00);
	};
	
	namespace TIMER_2
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x00);
		volatile uint32* const CR2	                = (volatile uint32* const) (BASE::TIMER_2 + 0x04);
		volatile uint32* const SMCR				    			= (volatile uint32* const) (BASE::TIMER_2 + 0x08);
		volatile uint32* const DIER					    		= (volatile uint32* const) (BASE::TIMER_2 + 0x0C);
		volatile uint32* const SR		    	    			= (volatile uint32* const) (BASE::TIMER_2 + 0x10);
		volatile uint32* const EGR			    	    	= (volatile uint32* const) (BASE::TIMER_2 + 0x14);
		volatile uint32* const CCMR1		     				= (volatile uint32* const) (BASE::TIMER_2 + 0x18);
		volatile uint32* const CCMR2		    				= (volatile uint32* const) (BASE::TIMER_2 + 0x1C);
		volatile uint32* const CCER			    				= (volatile uint32* const) (BASE::TIMER_2 + 0x20);
		volatile uint32* const CNT				     	    = (volatile uint32* const) (BASE::TIMER_2 + 0x24);
		volatile uint32* const PSC					        = (volatile uint32* const) (BASE::TIMER_2 + 0x28);
		volatile uint32* const ARR				          = (volatile uint32* const) (BASE::TIMER_2 + 0x2C);
		volatile uint32* const CCR1					    		= (volatile uint32* const) (BASE::TIMER_2 + 0x34);
		volatile uint32* const CCR2				    			= (volatile uint32* const) (BASE::TIMER_2 + 0x38);
		volatile uint32* const CCR3				    			= (volatile uint32* const) (BASE::TIMER_2 + 0x3C);
		volatile uint32* const CCR4				    			= (volatile uint32* const) (BASE::TIMER_2 + 0x40);
		volatile uint32* const DCR			        		= (volatile uint32* const) (BASE::TIMER_2 + 0x48);
		volatile uint32* const DMAR				    			= (volatile uint32* const) (BASE::TIMER_2 + 0x4C);
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
	};
	
	namespace TIMER_4
	{
		volatile uint32* const CR1	        				= (volatile uint32* const) (BASE::TIMER_4 + 0x00);
		volatile uint32* const CR2			         		= (volatile uint32* const) (BASE::TIMER_4 + 0x04);
		volatile uint32* const SMCR				    			= (volatile uint32* const) (BASE::TIMER_4 + 0x08);
		volatile uint32* const DIER				    			= (volatile uint32* const) (BASE::TIMER_4 + 0x0C);
		volatile uint32* const SR				           	= (volatile uint32* const) (BASE::TIMER_4 + 0x10);
		volatile uint32* const EGR				         	= (volatile uint32* const) (BASE::TIMER_4 + 0x14);
		volatile uint32* const CCMR1		    				= (volatile uint32* const) (BASE::TIMER_4 + 0x18);
		volatile uint32* const CCMR2			    			= (volatile uint32* const) (BASE::TIMER_4 + 0x1C);
		volatile uint32* const CCER		    					= (volatile uint32* const) (BASE::TIMER_4 + 0x20);
		volatile uint32* const CNT				        	= (volatile uint32* const) (BASE::TIMER_4 + 0x24);
		volatile uint32* const PSC					        = (volatile uint32* const) (BASE::TIMER_4 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_4 + 0x2C);
		volatile uint32* const CCR1				    			= (volatile uint32* const) (BASE::TIMER_4 + 0x34);
		volatile uint32* const CCR2			     				= (volatile uint32* const) (BASE::TIMER_4 + 0x38);
		volatile uint32* const CCR3			    				= (volatile uint32* const) (BASE::TIMER_4 + 0x3C);
		volatile uint32* const CCR4			    				= (volatile uint32* const) (BASE::TIMER_4 + 0x40);
		volatile uint32* const DCR				        	= (volatile uint32* const) (BASE::TIMER_4 + 0x48);
		volatile uint32* const DMAR					    		= (volatile uint32* const) (BASE::TIMER_4 + 0x4C);
	};
	
	namespace TIMER_5
	{
		volatile uint32* const CR1	        				= (volatile uint32* const) (BASE::TIMER_5 + 0x00);
		volatile uint32* const CR2			         		= (volatile uint32* const) (BASE::TIMER_5 + 0x04);
		volatile uint32* const SMCR				    			= (volatile uint32* const) (BASE::TIMER_5 + 0x08);
		volatile uint32* const DIER				    			= (volatile uint32* const) (BASE::TIMER_5 + 0x0C);
		volatile uint32* const SR				           	= (volatile uint32* const) (BASE::TIMER_5 + 0x10);
		volatile uint32* const EGR				         	= (volatile uint32* const) (BASE::TIMER_5 + 0x14);
		volatile uint32* const CCMR1		    				= (volatile uint32* const) (BASE::TIMER_5 + 0x18);
		volatile uint32* const CCMR2			    			= (volatile uint32* const) (BASE::TIMER_5 + 0x1C);
		volatile uint32* const CCER		    					= (volatile uint32* const) (BASE::TIMER_5 + 0x20);
		volatile uint32* const CNT				        	= (volatile uint32* const) (BASE::TIMER_5 + 0x24);
		volatile uint32* const PSC					        = (volatile uint32* const) (BASE::TIMER_5 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_5 + 0x2C);
		volatile uint32* const CCR1				    			= (volatile uint32* const) (BASE::TIMER_5 + 0x34);
		volatile uint32* const CCR2			     				= (volatile uint32* const) (BASE::TIMER_5 + 0x38);
		volatile uint32* const CCR3			    				= (volatile uint32* const) (BASE::TIMER_5 + 0x3C);
		volatile uint32* const CCR4			    				= (volatile uint32* const) (BASE::TIMER_5 + 0x40);
		volatile uint32* const DCR				        	= (volatile uint32* const) (BASE::TIMER_5 + 0x48);
		volatile uint32* const DMAR					    		= (volatile uint32* const) (BASE::TIMER_5 + 0x4C);
	};
	
	namespace RTC
	{
		volatile uint32* const CRH				        	= (volatile uint32* const) (BASE::RTC + 0x00);
		volatile uint32* const CRL						      = (volatile uint32* const) (BASE::RTC + 0x04);
		volatile uint32* const PRLH				        	= (volatile uint32* const) (BASE::RTC + 0x08);
		volatile uint32* const PRLL					       	= (volatile uint32* const) (BASE::RTC + 0x0C);
		volatile uint32* const DIVH					        = (volatile uint32* const) (BASE::RTC + 0x10);
		volatile uint32* const DIVL        					= (volatile uint32* const) (BASE::RTC + 0x14);
		volatile uint32* const CNTH		        			= (volatile uint32* const) (BASE::RTC + 0x18);
		volatile uint32* const CNTL		        			= (volatile uint32* const) (BASE::RTC + 0x1C);
		volatile uint32* const ALRH				        	= (volatile uint32* const) (BASE::RTC + 0x20);
		volatile uint32* const ALRL        					= (volatile uint32* const) (BASE::RTC + 0x24);
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
	};
	
	namespace SPI_2
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::SPI_2 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::SPI_2 + 0x04);
		volatile uint32* const SR		        				= (volatile uint32* const) (BASE::SPI_2 + 0x08);
		volatile uint32* const DR		        				= (volatile uint32* const) (BASE::SPI_2 + 0x0C);
		volatile uint32* const CRCPR		        		= (volatile uint32* const) (BASE::SPI_2 + 0x10);
		volatile uint32* const RXCRCR	    					= (volatile uint32* const) (BASE::SPI_2 + 0x14);
		volatile uint32* const TXCRCR	    					= (volatile uint32* const) (BASE::SPI_2 + 0x18);
		volatile uint32* const I2SCFGR		    			= (volatile uint32* const) (BASE::SPI_2 + 0x1C);
		volatile uint32* const I2SPR		        		= (volatile uint32* const) (BASE::SPI_2 + 0x20);
	};
	
	namespace USART_2
	{
		volatile uint32* const SR				        		= (volatile uint32* const) (BASE::USART_2 + 0x00);
		volatile uint32* const DR			        			= (volatile uint32* const) (BASE::USART_2 + 0x04);
		volatile uint32* const BRR			        		= (volatile uint32* const) (BASE::USART_2 + 0x08);
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::USART_2 + 0x0C);
		volatile uint32* const CR2			           	= (volatile uint32* const) (BASE::USART_2 + 0x10);
		volatile uint32* const CR3			        		= (volatile uint32* const) (BASE::USART_2 + 0x14);
		volatile uint32* const GTPR		       				= (volatile uint32* const) (BASE::USART_2 + 0x18);
	};
	
	namespace USART_3
	{
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::USART_3 + 0x00);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::USART_3 + 0x04);
		volatile uint32* const BRR			        		= (volatile uint32* const) (BASE::USART_3 + 0x08);
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::USART_3 + 0x0C);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::USART_3 + 0x10);
		volatile uint32* const CR3			    	    	= (volatile uint32* const) (BASE::USART_3 + 0x14);
		volatile uint32* const GTPR		        			= (volatile uint32* const) (BASE::USART_3 + 0x18);
	};
	
	namespace I2C_1
	{
		volatile uint32* const CR1			    	    	= (volatile uint32* const) (BASE::I2C_1 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::I2C_1 + 0x04);
		volatile uint32* const OAR1			        		= (volatile uint32* const) (BASE::I2C_1 + 0x08);
		volatile uint32* const OAR2			        		= (volatile uint32* const) (BASE::I2C_1 + 0x0C);
		volatile uint32* const DR			        			= (volatile uint32* const) (BASE::I2C_1 + 0x10);
		volatile uint32* const SR1			        		= (volatile uint32* const) (BASE::I2C_1 + 0x14);
		volatile uint32* const SR2			        		= (volatile uint32* const) (BASE::I2C_1 + 0x18);
		volatile uint32* const CCR			        		= (volatile uint32* const) (BASE::I2C_1 + 0x1C);
		volatile uint32* const TRISE		    	    	= (volatile uint32* const) (BASE::I2C_1 + 0x20);
	};
	
	namespace I2C_2
	{
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::I2C_2 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::I2C_2 + 0x04);
		volatile uint32* const OAR1			        		= (volatile uint32* const) (BASE::I2C_2 + 0x08);
		volatile uint32* const OAR2			        		= (volatile uint32* const) (BASE::I2C_2 + 0x0C);
		volatile uint32* const DR			        			= (volatile uint32* const) (BASE::I2C_2 + 0x10);
		volatile uint32* const SR1			        		= (volatile uint32* const) (BASE::I2C_2 + 0x14);
		volatile uint32* const SR2			        		= (volatile uint32* const) (BASE::I2C_2 + 0x18);
		volatile uint32* const CCR			        		= (volatile uint32* const) (BASE::I2C_2 + 0x1C);
		volatile uint32* const TRISE			        	= (volatile uint32* const) (BASE::I2C_2 + 0x20);
	};
	
	namespace CAN
	{
		volatile uint32* const MCR						      = (volatile uint32* const) (BASE::CAN + 0x00);
		volatile uint32* const MSR						      = (volatile uint32* const) (BASE::CAN + 0x04);
		volatile uint32* const TSR						      = (volatile uint32* const) (BASE::CAN + 0x08);
		volatile uint32* const RF0R					        = (volatile uint32* const) (BASE::CAN + 0x0C);
		volatile uint32* const RF1R					        = (volatile uint32* const) (BASE::CAN + 0x10);
		volatile uint32* const IER						      = (volatile uint32* const) (BASE::CAN + 0x14);
		volatile uint32* const ESR					        = (volatile uint32* const) (BASE::CAN + 0x18);
		volatile uint32* const BTR					        = (volatile uint32* const) (BASE::CAN + 0x1C);
		
		volatile uint32* const TI0R					        = (volatile uint32* const) (BASE::CAN + 0x180);
		volatile uint32* const TDT0R				        = (volatile uint32* const) (BASE::CAN + 0x184);
		volatile uint32* const TDL0R				        = (volatile uint32* const) (BASE::CAN + 0x188);
		volatile uint32* const TDH0R				        = (volatile uint32* const) (BASE::CAN + 0x18C);
		volatile uint32* const TI1R			           	= (volatile uint32* const) (BASE::CAN + 0x190);
		volatile uint32* const TDT1R				        = (volatile uint32* const) (BASE::CAN + 0x194);
		volatile uint32* const TDL1R		        		= (volatile uint32* const) (BASE::CAN + 0x198);
		volatile uint32* const TDH1R		        		= (volatile uint32* const) (BASE::CAN + 0x19C);
		volatile uint32* const TI2R		        			= (volatile uint32* const) (BASE::CAN + 0x1A0);
		volatile uint32* const TDT2R		        		= (volatile uint32* const) (BASE::CAN + 0x1A4);
		volatile uint32* const TDL2R	           		= (volatile uint32* const) (BASE::CAN + 0x1A8);
		volatile uint32* const TDH2R	        			= (volatile uint32* const) (BASE::CAN + 0x1AC);
		volatile uint32* const RI0R	        				= (volatile uint32* const) (BASE::CAN + 0x1B0);
		volatile uint32* const RDT0R		        		= (volatile uint32* const) (BASE::CAN + 0x1B4);
		volatile uint32* const RDL0R		        		= (volatile uint32* const) (BASE::CAN + 0x1B8);
		volatile uint32* const RDH0R		        		= (volatile uint32* const) (BASE::CAN + 0x1BC);
		volatile uint32* const RI1R		        			= (volatile uint32* const) (BASE::CAN + 0x1C0);
		volatile uint32* const RDT1R		        		= (volatile uint32* const) (BASE::CAN + 0x1C4);
		volatile uint32* const RDL1R		           	= (volatile uint32* const) (BASE::CAN + 0x1C8);
		volatile uint32* const RDH1R		        		= (volatile uint32* const) (BASE::CAN + 0x1CC);
		volatile uint32* const FMR			        		= (volatile uint32* const) (BASE::CAN + 0x200);
		volatile uint32* const FM1R		        			= (volatile uint32* const) (BASE::CAN + 0x204);
		volatile uint32* const FS1R		        			= (volatile uint32* const) (BASE::CAN + 0x20C);
		volatile uint32* const FFA1R		        		= (volatile uint32* const) (BASE::CAN + 0x214);
		volatile uint32* const FA1R		           		= (volatile uint32* const) (BASE::CAN + 0x21C);
		volatile uint32* const F0R1		        			= (volatile uint32* const) (BASE::CAN + 0x240);
		volatile uint32* const F0R2		        			= (volatile uint32* const) (BASE::CAN + 0x244);
		volatile uint32* const F1R1		        			= (volatile uint32* const) (BASE::CAN + 0x248);
		volatile uint32* const F1R2			        		= (volatile uint32* const) (BASE::CAN + 0x24C);
		volatile uint32* const F27R1			        	= (volatile uint32* const) (BASE::CAN + 0x318);
		volatile uint32* const F27R2			        	= (volatile uint32* const) (BASE::CAN + 0x31C);
	}
	
	namespace BKP
	{
		volatile uint32* const DR1					        = (volatile uint32* const) (BASE::BKP + 0x04);
		volatile uint32* const DR2					        = (volatile uint32* const) (BASE::BKP + 0x08);
		volatile uint32* const DR3					        = (volatile uint32* const) (BASE::BKP + 0x0C);
		volatile uint32* const DR4					        = (volatile uint32* const) (BASE::BKP + 0x10);
		volatile uint32* const DR5				        	= (volatile uint32* const) (BASE::BKP + 0x14);
		volatile uint32* const DR6					        = (volatile uint32* const) (BASE::BKP + 0x18);
		volatile uint32* const DR7				         	= (volatile uint32* const) (BASE::BKP + 0x1C);
		volatile uint32* const DR8					        = (volatile uint32* const) (BASE::BKP + 0x20);
		volatile uint32* const DR9					        = (volatile uint32* const) (BASE::BKP + 0x24);
		volatile uint32* const DR10			        		= (volatile uint32* const) (BASE::BKP + 0x28);
		volatile uint32* const RTC_CR			        	= (volatile uint32* const) (BASE::BKP + 0x2C);
		volatile uint32* const CR					        	= (volatile uint32* const) (BASE::BKP + 0x30);
		volatile uint32* const CSR					        = (volatile uint32* const) (BASE::BKP + 0x34);
		volatile uint32* const DR11				        	= (volatile uint32* const) (BASE::BKP + 0x40);
		volatile uint32* const DR12				        	= (volatile uint32* const) (BASE::BKP + 0x44);
		volatile uint32* const DR13				        	= (volatile uint32* const) (BASE::BKP + 0x48);
		volatile uint32* const DR14        					= (volatile uint32* const) (BASE::BKP + 0x4C);
		volatile uint32* const DR15        					= (volatile uint32* const) (BASE::BKP + 0x50);
		volatile uint32* const DR16		    	    		= (volatile uint32* const) (BASE::BKP + 0x54);
		volatile uint32* const DR17	    	    			= (volatile uint32* const) (BASE::BKP + 0x58);
		volatile uint32* const DR18					        = (volatile uint32* const) (BASE::BKP + 0x5C);
		volatile uint32* const DR19        					= (volatile uint32* const) (BASE::BKP + 0x60);
		volatile uint32* const DR20		        			= (volatile uint32* const) (BASE::BKP + 0x64);
		volatile uint32* const DR21				        	= (volatile uint32* const) (BASE::BKP + 0x68);
		volatile uint32* const DR22			        		= (volatile uint32* const) (BASE::BKP + 0x6C);
		volatile uint32* const DR23            			= (volatile uint32* const) (BASE::BKP + 0x70);
		volatile uint32* const DR24					        = (volatile uint32* const) (BASE::BKP + 0x74);
		volatile uint32* const DR25        					= (volatile uint32* const) (BASE::BKP + 0x78);
		volatile uint32* const DR26		        			= (volatile uint32* const) (BASE::BKP + 0x7C);
		volatile uint32* const DR27				        	= (volatile uint32* const) (BASE::BKP + 0x80);
		volatile uint32* const DR28        					= (volatile uint32* const) (BASE::BKP + 0x84);
		volatile uint32* const DR29		        			= (volatile uint32* const) (BASE::BKP + 0x88);
		volatile uint32* const DR30				        	= (volatile uint32* const) (BASE::BKP + 0x8C);
		volatile uint32* const DR31        					= (volatile uint32* const) (BASE::BKP + 0x90);
		volatile uint32* const DR32		        			= (volatile uint32* const) (BASE::BKP + 0x94);
		volatile uint32* const DR33				        	= (volatile uint32* const) (BASE::BKP + 0x98);
		volatile uint32* const DR34        					= (volatile uint32* const) (BASE::BKP + 0x9C);
		volatile uint32* const DR35				        	= (volatile uint32* const) (BASE::BKP + 0xA0);
		volatile uint32* const DR36		        			= (volatile uint32* const) (BASE::BKP + 0xA4);
		volatile uint32* const DR37        					= (volatile uint32* const) (BASE::BKP + 0xA8);
		volatile uint32* const DR38		        			= (volatile uint32* const) (BASE::BKP + 0xAC);
		volatile uint32* const DR39				        	= (volatile uint32* const) (BASE::BKP + 0xB0);
		volatile uint32* const DR40        					= (volatile uint32* const) (BASE::BKP + 0xB4);
		volatile uint32* const DR41		        			= (volatile uint32* const) (BASE::BKP + 0xB8);
		volatile uint32* const DR42				        	= (volatile uint32* const) (BASE::BKP + 0xBC);
	};
	
	namespace PWR
	{
		volatile uint32* const CR					        	= (volatile uint32* const) (BASE::PWR + 0x00);
		volatile uint32* const CSR						      = (volatile uint32* const) (BASE::PWR + 0x04);
	};
	
	namespace AFIO
	{
		volatile uint32* const EVCR       					= (volatile uint32* const) (BASE::AFIO + 0x00);
		volatile uint32* const MAPR		        			= (volatile uint32* const) (BASE::AFIO + 0x04);
		volatile uint32* const EXTICR1			        = (volatile uint32* const) (BASE::AFIO + 0x08);
		volatile uint32* const EXTICR2					    = (volatile uint32* const) (BASE::AFIO + 0x0C);
		volatile uint32* const EXTICR3				    	= (volatile uint32* const) (BASE::AFIO + 0x10);
		volatile uint32* const EXTICR4					    = (volatile uint32* const) (BASE::AFIO + 0x14);
		volatile uint32* const MAPR2					      = (volatile uint32* const) (BASE::AFIO + 0x1C);
	};
	
	namespace EXTI
	{
		volatile uint32* const IMR		        			= (volatile uint32* const) (BASE::EXTI + 0x00);
		volatile uint32* const EMR        					= (volatile uint32* const) (BASE::EXTI + 0x04);
		volatile uint32* const RTSR				        	= (volatile uint32* const) (BASE::EXTI + 0x08);
		volatile uint32* const FTSR       					= (volatile uint32* const) (BASE::EXTI + 0x0C);
		volatile uint32* const SWIER		        		= (volatile uint32* const) (BASE::EXTI + 0x10);
		volatile uint32* const PR					        	= (volatile uint32* const) (BASE::EXTI + 0x14);
	};
	
	namespace GPIO_A
	{
		volatile uint32* const CRL	        				= (volatile uint32* const) (BASE::GPIO_A + 0x00);
		volatile uint32* const CRH			        		= (volatile uint32* const) (BASE::GPIO_A + 0x04);
		volatile uint32* const IDR					        = (volatile uint32* const) (BASE::GPIO_A + 0x08);
		volatile uint32* const ODR      						= (volatile uint32* const) (BASE::GPIO_A + 0x0C);
		volatile uint32* const BSRR		        			= (volatile uint32* const) (BASE::GPIO_A + 0x10);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::GPIO_A + 0x14);
		volatile uint32* const LCKR					        = (volatile uint32* const) (BASE::GPIO_A + 0x18);
	};
	
	namespace GPIO_B
	{
		volatile uint32* const CRL      						= (volatile uint32* const) (BASE::GPIO_B + 0x00);
		volatile uint32* const CRH		            	= (volatile uint32* const) (BASE::GPIO_B + 0x04);
		volatile uint32* const IDR					        = (volatile uint32* const) (BASE::GPIO_B + 0x08);
		volatile uint32* const ODR      						= (volatile uint32* const) (BASE::GPIO_B + 0x0C);
		volatile uint32* const BSRR		        			= (volatile uint32* const) (BASE::GPIO_B + 0x10);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::GPIO_B + 0x14);
		volatile uint32* const LCKR     						= (volatile uint32* const) (BASE::GPIO_B + 0x18);
	};
	
	namespace GPIO_C
	{
		volatile uint32* const CRL      						= (volatile uint32* const) (BASE::GPIO_C + 0x00);
		volatile uint32* const CRH		            	= (volatile uint32* const) (BASE::GPIO_C + 0x04);
		volatile uint32* const IDR					        = (volatile uint32* const) (BASE::GPIO_C + 0x08);
		volatile uint32* const ODR      						= (volatile uint32* const) (BASE::GPIO_C + 0x0C);
		volatile uint32* const BSRR		        			= (volatile uint32* const) (BASE::GPIO_C + 0x10);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::GPIO_C + 0x14);
		volatile uint32* const LCKR     						= (volatile uint32* const) (BASE::GPIO_C + 0x18);
	};
	
	namespace GPIO_D
	{
		volatile uint32* const CRL      						= (volatile uint32* const) (BASE::GPIO_D + 0x00);
		volatile uint32* const CRH		            	= (volatile uint32* const) (BASE::GPIO_D + 0x04);
		volatile uint32* const IDR					        = (volatile uint32* const) (BASE::GPIO_D + 0x08);
		volatile uint32* const ODR      						= (volatile uint32* const) (BASE::GPIO_D + 0x0C);
		volatile uint32* const BSRR		        			= (volatile uint32* const) (BASE::GPIO_D + 0x10);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::GPIO_D + 0x14);
		volatile uint32* const LCKR     						= (volatile uint32* const) (BASE::GPIO_D + 0x18);
	};
	
	namespace ADC_1
	{
		volatile uint32* const SR		        				= (volatile uint32* const) (BASE::ADC_1 + 0x00);
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::ADC_1 + 0x04);
		volatile uint32* const CR2       						= (volatile uint32* const) (BASE::ADC_1 + 0x08);
		volatile uint32* const SMPR1		        		= (volatile uint32* const) (BASE::ADC_1 + 0x0C);
		volatile uint32* const SMPR2				        = (volatile uint32* const) (BASE::ADC_1 + 0x10);
		volatile uint32* const JOFR1		        		= (volatile uint32* const) (BASE::ADC_1 + 0x14);
		volatile uint32* const JOFR2     		    		= (volatile uint32* const) (BASE::ADC_1 + 0x18);
		volatile uint32* const JOFR3					      = (volatile uint32* const) (BASE::ADC_1 + 0x1C);
		volatile uint32* const JOFR4     						= (volatile uint32* const) (BASE::ADC_1 + 0x20);
		volatile uint32* const HTR		        			= (volatile uint32* const) (BASE::ADC_1 + 0x24);
		volatile uint32* const LTR				        	= (volatile uint32* const) (BASE::ADC_1 + 0x28);
		volatile uint32* const SQR1      						= (volatile uint32* const) (BASE::ADC_1 + 0x2C);
		volatile uint32* const SQR2		        			= (volatile uint32* const) (BASE::ADC_1 + 0x30);
		volatile uint32* const SQR3				        	= (volatile uint32* const) (BASE::ADC_1 + 0x34);
		volatile uint32* const JSQR      						= (volatile uint32* const) (BASE::ADC_1 + 0x38);
		volatile uint32* const JDR1		        			= (volatile uint32* const) (BASE::ADC_1 + 0x3C);
		volatile uint32* const JDR2				      		= (volatile uint32* const) (BASE::ADC_1 + 0x40);
		volatile uint32* const JDR3      						= (volatile uint32* const) (BASE::ADC_1 + 0x44);
		volatile uint32* const JDR4		        			= (volatile uint32* const) (BASE::ADC_1 + 0x48);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::ADC_1 + 0x4C);
	};
	
	namespace TIMER_1
	{
		volatile uint32* const CR1		        			= (volatile uint32* const) (BASE::TIMER_1 + 0x00);
		volatile uint32* const CR2				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x04);
		volatile uint32* const SMCR					    		= (volatile uint32* const) (BASE::TIMER_1 + 0x08);
		volatile uint32* const DIER    							= (volatile uint32* const) (BASE::TIMER_1 + 0x0C);
		volatile uint32* const SR		    	        	= (volatile uint32* const) (BASE::TIMER_1 + 0x10);
		volatile uint32* const EGR     	    		 	  = (volatile uint32* const) (BASE::TIMER_1 + 0x14);
		volatile uint32* const CCMR1	        			= (volatile uint32* const) (BASE::TIMER_1 + 0x18);
		volatile uint32* const CCMR2			        	= (volatile uint32* const) (BASE::TIMER_1 + 0x1C);
		volatile uint32* const CCER					    		= (volatile uint32* const) (BASE::TIMER_1 + 0x20);
		volatile uint32* const CNT     							= (volatile uint32* const) (BASE::TIMER_1 + 0x24);
		volatile uint32* const PSC		        			= (volatile uint32* const) (BASE::TIMER_1 + 0x28);
		volatile uint32* const ARR				        	= (volatile uint32* const) (BASE::TIMER_1 + 0x2C);
		volatile uint32* const RCR					        = (volatile uint32* const) (BASE::TIMER_1 + 0x30);
		volatile uint32* const CCR1		    					= (volatile uint32* const) (BASE::TIMER_1 + 0x34);
		volatile uint32* const CCR2        	    		= (volatile uint32* const) (BASE::TIMER_1 + 0x38);
		volatile uint32* const CCR3				    			= (volatile uint32* const) (BASE::TIMER_1 + 0x3C);
		volatile uint32* const CCR4					    		= (volatile uint32* const) (BASE::TIMER_1 + 0x40);
		volatile uint32* const BDTR    							= (volatile uint32* const) (BASE::TIMER_1 + 0x44);
		volatile uint32* const DCR		        			= (volatile uint32* const) (BASE::TIMER_1 + 0x48);
		volatile uint32* const DMAR			    				= (volatile uint32* const) (BASE::TIMER_1 + 0x4C);
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
		volatile uint32* const SR       						= (volatile uint32* const) (BASE::USART_1 + 0x00);
		volatile uint32* const DR		        				= (volatile uint32* const) (BASE::USART_1 + 0x04);
		volatile uint32* const BRR				        	= (volatile uint32* const) (BASE::USART_1 + 0x08);
		volatile uint32* const CR1  	    					= (volatile uint32* const) (BASE::USART_1 + 0x0C);
		volatile uint32* const CR2	    	    			= (volatile uint32* const) (BASE::USART_1 + 0x10);
		volatile uint32* const CR3				        	= (volatile uint32* const) (BASE::USART_1 + 0x14);
		volatile uint32* const GTPR     						= (volatile uint32* const) (BASE::USART_1 + 0x18);
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
		
		volatile uint32* const CH3_CR      				  = (volatile uint32* const) (BASE::DMA + 0x44);
		volatile uint32* const CH3_NDTR	    			  = (volatile uint32* const) (BASE::DMA + 0x48);
		volatile uint32* const CH3_PAR			        = (volatile uint32* const) (BASE::DMA + 0x4C);
		volatile uint32* const CH3_MAR					    = (volatile uint32* const) (BASE::DMA + 0x50);
		
		volatile uint32* const CH4_CR      			    = (volatile uint32* const) (BASE::DMA + 0x58);
		volatile uint32* const CH4_NDTR	    		    = (volatile uint32* const) (BASE::DMA + 0x5C);
		volatile uint32* const CH4_PAR			        = (volatile uint32* const) (BASE::DMA + 0x60);
		volatile uint32* const CH4_MAR					    = (volatile uint32* const) (BASE::DMA + 0x64);
		
		volatile uint32* const CH5_CR      			    = (volatile uint32* const) (BASE::DMA + 0x6C);
		volatile uint32* const CH5_NDTR	    		    = (volatile uint32* const) (BASE::DMA + 0x70);
		volatile uint32* const CH5_PAR			        = (volatile uint32* const) (BASE::DMA + 0x74);
		volatile uint32* const CH5_MAR					    = (volatile uint32* const) (BASE::DMA + 0x78);
		
		volatile uint32* const CH6_CR      				  = (volatile uint32* const) (BASE::DMA + 0x80);
		volatile uint32* const CH6_NDTR	    			  = (volatile uint32* const) (BASE::DMA + 0x84);
		volatile uint32* const CH6_PAR			        = (volatile uint32* const) (BASE::DMA + 0x88);
		volatile uint32* const CH6_MAR					    = (volatile uint32* const) (BASE::DMA + 0x8C);
	};
	
	namespace RCC
	{
		volatile uint32* const CR      							= (volatile uint32* const) (BASE::RCC + 0x00);
		volatile uint32* const CFGR	        				= (volatile uint32* const) (BASE::RCC + 0x04);
		volatile uint32* const CIR				        	= (volatile uint32* const) (BASE::RCC + 0x08);
		volatile uint32* const APB2_RSTR				    = (volatile uint32* const) (BASE::RCC + 0x0C);
		volatile uint32* const APB1_RSTR					  = (volatile uint32* const) (BASE::RCC + 0x10);
		volatile uint32* const AHB_ENR      				= (volatile uint32* const) (BASE::RCC + 0x14);
		volatile uint32* const APB2_ENR		        	= (volatile uint32* const) (BASE::RCC + 0x18);
		volatile uint32* const APB1_ENR				      = (volatile uint32* const) (BASE::RCC + 0x1C);
		volatile uint32* const BDCR	    	    			= (volatile uint32* const) (BASE::RCC + 0x20);
		volatile uint32* const CSR	    	    			= (volatile uint32* const) (BASE::RCC + 0x24);
	};
	
	namespace FLASH
	{
		volatile uint32* const ACR      						= (volatile uint32* const) (BASE::FLASH + 0x00);
		volatile uint32* const KEYR      						= (volatile uint32* const) (BASE::FLASH + 0x04);
		volatile uint32* const OPT_KEYR      				= (volatile uint32* const) (BASE::FLASH + 0x08);
		volatile uint32* const SR      							= (volatile uint32* const) (BASE::FLASH + 0x0C);
		volatile uint32* const CR      							= (volatile uint32* const) (BASE::FLASH + 0x10);
		volatile uint32* const AR      							= (volatile uint32* const) (BASE::FLASH + 0x14);
		volatile uint32* const OBR      						= (volatile uint32* const) (BASE::FLASH + 0x1C);
		volatile uint32* const WRPR      						= (volatile uint32* const) (BASE::FLASH + 0x20);
	};
	
	namespace CRC
	{
		volatile uint32* const DR      							= (volatile uint32* const) (BASE::CRC + 0x00);
		volatile uint32* const IDR      						= (volatile uint32* const) (BASE::CRC + 0x04);
		volatile uint32* const CR      							= (volatile uint32* const) (BASE::CRC + 0x08);
	};
};