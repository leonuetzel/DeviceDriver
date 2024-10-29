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
	constexpr uint16 DMA1_CH0																	= 27;
	constexpr uint16 DMA1_CH1																	= 28;
	constexpr uint16 DMA1_CH2																	= 29;
	constexpr uint16 DMA1_CH3																	= 30;
	constexpr uint16 DMA1_CH4																	= 31;
	constexpr uint16 DMA1_CH5																	= 32;
	constexpr uint16 DMA1_CH6																	= 33;
	constexpr uint16 ADC																			= 34;
	constexpr uint16 CAN1_TX																	= 35;
	constexpr uint16 CAN1_RX0																	= 36;
	constexpr uint16 CAN1_RX1																	= 37;
	constexpr uint16 CAN1_SCE																	= 38;
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
	constexpr uint16 USB_OTG_WAKEUP														= 58;
	
	
	
	
	
	
	
	constexpr uint16 TIMER_5																	= 66;
	constexpr uint16 SPI_3																		= 67;
	constexpr uint16 UART_4																		= 68;
	constexpr uint16 UART_5																		= 69;
	constexpr uint16 TIMER_6																	= 70;
	constexpr uint16 TIMER_7																	= 71;
	constexpr uint16 DMA2_CH0																	= 72;
	constexpr uint16 DMA2_CH1																	= 73;
	constexpr uint16 DMA2_CH2																	= 74;
	constexpr uint16 DMA2_CH3																	= 75;
	constexpr uint16 DMA2_CH4																	= 76;
	constexpr uint16 ETHERNET																	= 77;
	constexpr uint16 ETHERNET_WAKEUP													= 78;
	constexpr uint16 CAN2_TX																	= 79;
	constexpr uint16 CAN2_RX0																	= 80;
	constexpr uint16 CAN2_RX1																	= 81;
	constexpr uint16 CAN2_SCE																	= 82;
	constexpr uint16 USB_OTG																	= 83;
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
		constexpr uint32 TIMER_6										= APB1 + 0x00001000;
		constexpr uint32 TIMER_7										= APB1 + 0x00001400;
		constexpr uint32 RTC		    								= APB1 + 0x00002800;
		constexpr uint32 WWDG		    								= APB1 + 0x00002C00;
		constexpr uint32 IWDG		    								= APB1 + 0x00003000;
		constexpr uint32 SPI_2		    							= APB1 + 0x00003800;
		constexpr uint32 SPI_3		    							= APB1 + 0x00003C00;
		constexpr uint32 USART_2										= APB1 + 0x00004400;
		constexpr uint32 USART_3										= APB1 + 0x00004800;
		constexpr uint32 UART_4											= APB1 + 0x00004C00;
		constexpr uint32 UART_5											= APB1 + 0x00005000;
		constexpr uint32 I2C_1			    						= APB1 + 0x00005400;
		constexpr uint32 I2C_2			    						= APB1 + 0x00005800;
		constexpr uint32 CAN_1			    						= APB1 + 0x00006400;
		constexpr uint32 CAN_2			    						= APB1 + 0x00006800;
		constexpr uint32 BKP	    									= APB1 + 0x00006C00;
		constexpr uint32 PWR	    									= APB1 + 0x00007000;
		constexpr uint32 DAC	    									= APB1 + 0x00007400;
		
		constexpr uint32 AFIO		    								= APB2 + 0x00000000;
		constexpr uint32 EXTI		    								= APB2 + 0x00000400;
		constexpr uint32 GPIO_A		    							= APB2 + 0x00000800;
		constexpr uint32 GPIO_B		    							= APB2 + 0x00000C00;
		constexpr uint32 GPIO_C		    							= APB2 + 0x00001000;
		constexpr uint32 GPIO_D		    							= APB2 + 0x00001400;
		constexpr uint32 ADC_1		    							= APB2 + 0x00002400;
		constexpr uint32 ADC_2		    							= APB2 + 0x00002800;
		constexpr uint32 TIMER_1	    							= APB2 + 0x00002C00;
		constexpr uint32 SPI_1		    							= APB2 + 0x00003000;
		constexpr uint32 USART_1	    							= APB2 + 0x00003800;
		
		constexpr uint32 DMA_1			        				= AHB	 + 0x00008000;
		constexpr uint32 DMA_2			        				= AHB	 + 0x00008400;
		constexpr uint32 RCC			    							= AHB	 + 0x00009000;
		constexpr uint32 FLASH			    						= AHB	 + 0x0000A000;
		constexpr uint32 CRC			    							= AHB	 + 0x0000B000;
		constexpr uint32 ETHERNET			    					= AHB	 + 0x00010000;
		constexpr uint32 USB_OTG			    					= AHB	 + 0x0FFE8000;
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
	
	namespace TIMER_6
	{
		volatile uint32* const CR1	        				= (volatile uint32* const) (BASE::TIMER_6 + 0x00);
		volatile uint32* const CR2			         		= (volatile uint32* const) (BASE::TIMER_6 + 0x04);
		volatile uint32* const DIER				    			= (volatile uint32* const) (BASE::TIMER_6 + 0x0C);
		volatile uint32* const SR				           	= (volatile uint32* const) (BASE::TIMER_6 + 0x10);
		volatile uint32* const EGR				         	= (volatile uint32* const) (BASE::TIMER_6 + 0x14);
		volatile uint32* const CNT				        	= (volatile uint32* const) (BASE::TIMER_6 + 0x24);
		volatile uint32* const PSC					        = (volatile uint32* const) (BASE::TIMER_6 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_6 + 0x2C);
	};
	
	namespace TIMER_7
	{
		volatile uint32* const CR1	        				= (volatile uint32* const) (BASE::TIMER_7 + 0x00);
		volatile uint32* const CR2			         		= (volatile uint32* const) (BASE::TIMER_7 + 0x04);
		volatile uint32* const DIER				    			= (volatile uint32* const) (BASE::TIMER_7 + 0x0C);
		volatile uint32* const SR				           	= (volatile uint32* const) (BASE::TIMER_7 + 0x10);
		volatile uint32* const EGR				         	= (volatile uint32* const) (BASE::TIMER_7 + 0x14);
		volatile uint32* const CNT				        	= (volatile uint32* const) (BASE::TIMER_7 + 0x24);
		volatile uint32* const PSC					        = (volatile uint32* const) (BASE::TIMER_7 + 0x28);
		volatile uint32* const ARR			        		= (volatile uint32* const) (BASE::TIMER_7 + 0x2C);
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
	
	namespace SPI_3
	{
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::SPI_3 + 0x00);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::SPI_3 + 0x04);
		volatile uint32* const SR		        				= (volatile uint32* const) (BASE::SPI_3 + 0x08);
		volatile uint32* const DR		        				= (volatile uint32* const) (BASE::SPI_3 + 0x0C);
		volatile uint32* const CRCPR		        		= (volatile uint32* const) (BASE::SPI_3 + 0x10);
		volatile uint32* const RXCRCR	    					= (volatile uint32* const) (BASE::SPI_3 + 0x14);
		volatile uint32* const TXCRCR	    					= (volatile uint32* const) (BASE::SPI_3 + 0x18);
		volatile uint32* const I2SCFGR		    			= (volatile uint32* const) (BASE::SPI_3 + 0x1C);
		volatile uint32* const I2SPR		        		= (volatile uint32* const) (BASE::SPI_3 + 0x20);
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
	
	namespace UART_4
	{
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::UART_4 + 0x00);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::UART_4 + 0x04);
		volatile uint32* const BRR			        		= (volatile uint32* const) (BASE::UART_4 + 0x08);
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::UART_4 + 0x0C);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::UART_4 + 0x10);
		volatile uint32* const CR3			    	    	= (volatile uint32* const) (BASE::UART_4 + 0x14);
		volatile uint32* const GTPR		        			= (volatile uint32* const) (BASE::UART_4 + 0x18);
	};
	
	namespace UART_5
	{
		volatile uint32* const SR			        			= (volatile uint32* const) (BASE::UART_5 + 0x00);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::UART_5 + 0x04);
		volatile uint32* const BRR			        		= (volatile uint32* const) (BASE::UART_5 + 0x08);
		volatile uint32* const CR1			        		= (volatile uint32* const) (BASE::UART_5 + 0x0C);
		volatile uint32* const CR2			        		= (volatile uint32* const) (BASE::UART_5 + 0x10);
		volatile uint32* const CR3			    	    	= (volatile uint32* const) (BASE::UART_5 + 0x14);
		volatile uint32* const GTPR		        			= (volatile uint32* const) (BASE::UART_5 + 0x18);
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
	
	namespace CAN_2
	{
		volatile uint32* const MCR						      = (volatile uint32* const) (BASE::CAN_2 + 0x00);
		volatile uint32* const MSR						      = (volatile uint32* const) (BASE::CAN_2 + 0x04);
		volatile uint32* const TSR						      = (volatile uint32* const) (BASE::CAN_2 + 0x08);
		volatile uint32* const RF0R					        = (volatile uint32* const) (BASE::CAN_2 + 0x0C);
		volatile uint32* const RF1R					        = (volatile uint32* const) (BASE::CAN_2 + 0x10);
		volatile uint32* const IER						      = (volatile uint32* const) (BASE::CAN_2 + 0x14);
		volatile uint32* const ESR					        = (volatile uint32* const) (BASE::CAN_2 + 0x18);
		volatile uint32* const BTR					        = (volatile uint32* const) (BASE::CAN_2 + 0x1C);
		
		volatile uint32* const TI0R					        = (volatile uint32* const) (BASE::CAN_2 + 0x180);
		volatile uint32* const TDT0R				        = (volatile uint32* const) (BASE::CAN_2 + 0x184);
		volatile uint32* const TDL0R				        = (volatile uint32* const) (BASE::CAN_2 + 0x188);
		volatile uint32* const TDH0R				        = (volatile uint32* const) (BASE::CAN_2 + 0x18C);
		volatile uint32* const TI1R			           	= (volatile uint32* const) (BASE::CAN_2 + 0x190);
		volatile uint32* const TDT1R				        = (volatile uint32* const) (BASE::CAN_2 + 0x194);
		volatile uint32* const TDL1R		        		= (volatile uint32* const) (BASE::CAN_2 + 0x198);
		volatile uint32* const TDH1R		        		= (volatile uint32* const) (BASE::CAN_2 + 0x19C);
		volatile uint32* const TI2R		        			= (volatile uint32* const) (BASE::CAN_2 + 0x1A0);
		volatile uint32* const TDT2R		        		= (volatile uint32* const) (BASE::CAN_2 + 0x1A4);
		volatile uint32* const TDL2R	           		= (volatile uint32* const) (BASE::CAN_2 + 0x1A8);
		volatile uint32* const TDH2R	        			= (volatile uint32* const) (BASE::CAN_2 + 0x1AC);
		volatile uint32* const RI0R	        				= (volatile uint32* const) (BASE::CAN_2 + 0x1B0);
		volatile uint32* const RDT0R		        		= (volatile uint32* const) (BASE::CAN_2 + 0x1B4);
		volatile uint32* const RDL0R		        		= (volatile uint32* const) (BASE::CAN_2 + 0x1B8);
		volatile uint32* const RDH0R		        		= (volatile uint32* const) (BASE::CAN_2 + 0x1BC);
		volatile uint32* const RI1R		        			= (volatile uint32* const) (BASE::CAN_2 + 0x1C0);
		volatile uint32* const RDT1R		        		= (volatile uint32* const) (BASE::CAN_2 + 0x1C4);
		volatile uint32* const RDL1R		           	= (volatile uint32* const) (BASE::CAN_2 + 0x1C8);
		volatile uint32* const RDH1R		        		= (volatile uint32* const) (BASE::CAN_2 + 0x1CC);
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
	
	namespace DAC
	{
		volatile uint32* const CR					        	= (volatile uint32* const) (BASE::DAC + 0x00);
		volatile uint32* const SW_TRIG					    = (volatile uint32* const) (BASE::DAC + 0x04);
		volatile uint32* const CH0_DHR12R					  = (volatile uint32* const) (BASE::DAC + 0x08);
		volatile uint32* const CH0_DHR12L					  = (volatile uint32* const) (BASE::DAC + 0x0C);
		volatile uint32* const CH0_DHR8R					  = (volatile uint32* const) (BASE::DAC + 0x10);
		volatile uint32* const CH1_DHR12R					  = (volatile uint32* const) (BASE::DAC + 0x14);
		volatile uint32* const CH1_DHR12L					  = (volatile uint32* const) (BASE::DAC + 0x18);
		volatile uint32* const CH1_DHR8R					  = (volatile uint32* const) (BASE::DAC + 0x1C);
		volatile uint32* const DUAL_DHR12R					= (volatile uint32* const) (BASE::DAC + 0x20);
		volatile uint32* const DUAL_DHR12L					= (volatile uint32* const) (BASE::DAC + 0x24);
		volatile uint32* const DUAL_DHR8R					  = (volatile uint32* const) (BASE::DAC + 0x28);
		volatile uint32* const CH0_DOR					    = (volatile uint32* const) (BASE::DAC + 0x2C);
		volatile uint32* const CH1_DOR					    = (volatile uint32* const) (BASE::DAC + 0x30);
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
	
	namespace ADC_2
	{
		volatile uint32* const SR		        				= (volatile uint32* const) (BASE::ADC_2 + 0x00);
		volatile uint32* const CR1				        	= (volatile uint32* const) (BASE::ADC_2 + 0x04);
		volatile uint32* const CR2       						= (volatile uint32* const) (BASE::ADC_2 + 0x08);
		volatile uint32* const SMPR1		        		= (volatile uint32* const) (BASE::ADC_2 + 0x0C);
		volatile uint32* const SMPR2				        = (volatile uint32* const) (BASE::ADC_2 + 0x10);
		volatile uint32* const JOFR1		        		= (volatile uint32* const) (BASE::ADC_2 + 0x14);
		volatile uint32* const JOFR2     		    		= (volatile uint32* const) (BASE::ADC_2 + 0x18);
		volatile uint32* const JOFR3					      = (volatile uint32* const) (BASE::ADC_2 + 0x1C);
		volatile uint32* const JOFR4     						= (volatile uint32* const) (BASE::ADC_2 + 0x20);
		volatile uint32* const HTR		        			= (volatile uint32* const) (BASE::ADC_2 + 0x24);
		volatile uint32* const LTR				        	= (volatile uint32* const) (BASE::ADC_2 + 0x28);
		volatile uint32* const SQR1      						= (volatile uint32* const) (BASE::ADC_2 + 0x2C);
		volatile uint32* const SQR2		        			= (volatile uint32* const) (BASE::ADC_2 + 0x30);
		volatile uint32* const SQR3				        	= (volatile uint32* const) (BASE::ADC_2 + 0x34);
		volatile uint32* const JSQR      						= (volatile uint32* const) (BASE::ADC_2 + 0x38);
		volatile uint32* const JDR1		        			= (volatile uint32* const) (BASE::ADC_2 + 0x3C);
		volatile uint32* const JDR2				      		= (volatile uint32* const) (BASE::ADC_2 + 0x40);
		volatile uint32* const JDR3      						= (volatile uint32* const) (BASE::ADC_2 + 0x44);
		volatile uint32* const JDR4		        			= (volatile uint32* const) (BASE::ADC_2 + 0x48);
		volatile uint32* const DR				        		= (volatile uint32* const) (BASE::ADC_2 + 0x4C);
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
	
	namespace DMA_1
	{
		volatile uint32* const ISR	        				= (volatile uint32* const) (BASE::DMA_1 + 0x00);
		volatile uint32* const IFCR			        		= (volatile uint32* const) (BASE::DMA_1 + 0x04);
		
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMA_1 + 0x08);
		volatile uint32* const CH0_NDTR							= (volatile uint32* const) (BASE::DMA_1 + 0x0C);
		volatile uint32* const CH0_PAR							= (volatile uint32* const) (BASE::DMA_1 + 0x10);
		volatile uint32* const CH0_MAR							= (volatile uint32* const) (BASE::DMA_1 + 0x14);
		
		volatile uint32* const CH1_CR      				  = (volatile uint32* const) (BASE::DMA_1 + 0x1C);
		volatile uint32* const CH1_NDTR	    			  = (volatile uint32* const) (BASE::DMA_1 + 0x20);
		volatile uint32* const CH1_PAR			        = (volatile uint32* const) (BASE::DMA_1 + 0x24);
		volatile uint32* const CH1_MAR					    = (volatile uint32* const) (BASE::DMA_1 + 0x28);
		
		volatile uint32* const CH2_CR      					= (volatile uint32* const) (BASE::DMA_1 + 0x30);
		volatile uint32* const CH2_NDTR	    			  = (volatile uint32* const) (BASE::DMA_1 + 0x34);
		volatile uint32* const CH2_PAR			        = (volatile uint32* const) (BASE::DMA_1 + 0x38);
		volatile uint32* const CH2_MAR					    = (volatile uint32* const) (BASE::DMA_1 + 0x3C);
		
		volatile uint32* const CH3_CR      				  = (volatile uint32* const) (BASE::DMA_1 + 0x44);
		volatile uint32* const CH3_NDTR	    			  = (volatile uint32* const) (BASE::DMA_1 + 0x48);
		volatile uint32* const CH3_PAR			        = (volatile uint32* const) (BASE::DMA_1 + 0x4C);
		volatile uint32* const CH3_MAR					    = (volatile uint32* const) (BASE::DMA_1 + 0x50);
		
		volatile uint32* const CH4_CR      			    = (volatile uint32* const) (BASE::DMA_1 + 0x58);
		volatile uint32* const CH4_NDTR	    		    = (volatile uint32* const) (BASE::DMA_1 + 0x5C);
		volatile uint32* const CH4_PAR			        = (volatile uint32* const) (BASE::DMA_1 + 0x60);
		volatile uint32* const CH4_MAR					    = (volatile uint32* const) (BASE::DMA_1 + 0x64);
		
		volatile uint32* const CH5_CR      			    = (volatile uint32* const) (BASE::DMA_1 + 0x6C);
		volatile uint32* const CH5_NDTR	    		    = (volatile uint32* const) (BASE::DMA_1 + 0x70);
		volatile uint32* const CH5_PAR			        = (volatile uint32* const) (BASE::DMA_1 + 0x74);
		volatile uint32* const CH5_MAR					    = (volatile uint32* const) (BASE::DMA_1 + 0x78);
		
		volatile uint32* const CH6_CR      				  = (volatile uint32* const) (BASE::DMA_1 + 0x80);
		volatile uint32* const CH6_NDTR	    			  = (volatile uint32* const) (BASE::DMA_1 + 0x84);
		volatile uint32* const CH6_PAR			        = (volatile uint32* const) (BASE::DMA_1 + 0x88);
		volatile uint32* const CH6_MAR					    = (volatile uint32* const) (BASE::DMA_1 + 0x8C);
	};
	
	namespace DMA_2
	{
		volatile uint32* const ISR	        				= (volatile uint32* const) (BASE::DMA_2 + 0x00);
		volatile uint32* const IFCR			        		= (volatile uint32* const) (BASE::DMA_2 + 0x04);
		
		volatile uint32* const CH0_CR								= (volatile uint32* const) (BASE::DMA_2 + 0x08);
		volatile uint32* const CH0_NDTR							= (volatile uint32* const) (BASE::DMA_2 + 0x0C);
		volatile uint32* const CH0_PAR							= (volatile uint32* const) (BASE::DMA_2 + 0x10);
		volatile uint32* const CH0_MAR							= (volatile uint32* const) (BASE::DMA_2 + 0x14);
		
		volatile uint32* const CH1_CR      				  = (volatile uint32* const) (BASE::DMA_2 + 0x1C);
		volatile uint32* const CH1_NDTR	    			  = (volatile uint32* const) (BASE::DMA_2 + 0x20);
		volatile uint32* const CH1_PAR			        = (volatile uint32* const) (BASE::DMA_2 + 0x24);
		volatile uint32* const CH1_MAR					    = (volatile uint32* const) (BASE::DMA_2 + 0x28);
		
		volatile uint32* const CH2_CR      					= (volatile uint32* const) (BASE::DMA_2 + 0x30);
		volatile uint32* const CH2_NDTR	    			  = (volatile uint32* const) (BASE::DMA_2 + 0x34);
		volatile uint32* const CH2_PAR			        = (volatile uint32* const) (BASE::DMA_2 + 0x38);
		volatile uint32* const CH2_MAR					    = (volatile uint32* const) (BASE::DMA_2 + 0x3C);
		
		volatile uint32* const CH3_CR      				  = (volatile uint32* const) (BASE::DMA_2 + 0x44);
		volatile uint32* const CH3_NDTR	    			  = (volatile uint32* const) (BASE::DMA_2 + 0x48);
		volatile uint32* const CH3_PAR			        = (volatile uint32* const) (BASE::DMA_2 + 0x4C);
		volatile uint32* const CH3_MAR					    = (volatile uint32* const) (BASE::DMA_2 + 0x50);
		
		volatile uint32* const CH4_CR      			    = (volatile uint32* const) (BASE::DMA_2 + 0x58);
		volatile uint32* const CH4_NDTR	    		    = (volatile uint32* const) (BASE::DMA_2 + 0x5C);
		volatile uint32* const CH4_PAR			        = (volatile uint32* const) (BASE::DMA_2 + 0x60);
		volatile uint32* const CH4_MAR					    = (volatile uint32* const) (BASE::DMA_2 + 0x64);
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
		volatile uint32* const AHB_RSTR	    	    	= (volatile uint32* const) (BASE::RCC + 0x28);
		volatile uint32* const CFGR2	    	    		= (volatile uint32* const) (BASE::RCC + 0x2C);
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
	
	namespace ETHERNET
	{
		namespace MAC
		{
			volatile uint32* const CR      						= (volatile uint32* const) (BASE::ETHERNET + 0x00);
			volatile uint32* const FFR      					= (volatile uint32* const) (BASE::ETHERNET + 0x04);
			volatile uint32* const HTHR      					= (volatile uint32* const) (BASE::ETHERNET + 0x08);
			volatile uint32* const HTLR      					= (volatile uint32* const) (BASE::ETHERNET + 0x0C);
			volatile uint32* const MII_AR      				= (volatile uint32* const) (BASE::ETHERNET + 0x10);
			volatile uint32* const MII_DR      				= (volatile uint32* const) (BASE::ETHERNET + 0x14);
			volatile uint32* const FCR      					= (volatile uint32* const) (BASE::ETHERNET + 0x18);
			volatile uint32* const VLANTR      				= (volatile uint32* const) (BASE::ETHERNET + 0x1C);
			volatile uint32* const RWUFFR      				= (volatile uint32* const) (BASE::ETHERNET + 0x28);
			volatile uint32* const PMT_CSR      			= (volatile uint32* const) (BASE::ETHERNET + 0x2C);
			volatile uint32* const SR      						= (volatile uint32* const) (BASE::ETHERNET + 0x38);
			volatile uint32* const IMR      					= (volatile uint32* const) (BASE::ETHERNET + 0x3C);
			volatile uint32* const A0HR      					= (volatile uint32* const) (BASE::ETHERNET + 0x40);
			volatile uint32* const A0LR      					= (volatile uint32* const) (BASE::ETHERNET + 0x44);
			volatile uint32* const A1HR      					= (volatile uint32* const) (BASE::ETHERNET + 0x48);
			volatile uint32* const A1LR      					= (volatile uint32* const) (BASE::ETHERNET + 0x4C);
			volatile uint32* const A2HR      					= (volatile uint32* const) (BASE::ETHERNET + 0x50);
			volatile uint32* const A2LR      					= (volatile uint32* const) (BASE::ETHERNET + 0x54);
			volatile uint32* const A3HR      					= (volatile uint32* const) (BASE::ETHERNET + 0x58);
			volatile uint32* const A3LR      					= (volatile uint32* const) (BASE::ETHERNET + 0x5C);
		};
		
		namespace MMC
		{
			volatile uint32* const CR      						= (volatile uint32* const) (BASE::ETHERNET + 0x100);
			volatile uint32* const RIR      					= (volatile uint32* const) (BASE::ETHERNET + 0x104);
			volatile uint32* const TIR      					= (volatile uint32* const) (BASE::ETHERNET + 0x108);
			volatile uint32* const RIMR      					= (volatile uint32* const) (BASE::ETHERNET + 0x10C);
			volatile uint32* const TIMR      					= (volatile uint32* const) (BASE::ETHERNET + 0x110);
			volatile uint32* const TGFSCCR      			= (volatile uint32* const) (BASE::ETHERNET + 0x14C);
			volatile uint32* const TGFMSCCR      			= (volatile uint32* const) (BASE::ETHERNET + 0x150);
			volatile uint32* const TGFCR      				= (volatile uint32* const) (BASE::ETHERNET + 0x168);
			volatile uint32* const RFCECR      				= (volatile uint32* const) (BASE::ETHERNET + 0x194);
			volatile uint32* const RFAECR      				= (volatile uint32* const) (BASE::ETHERNET + 0x198);
			volatile uint32* const RGUFCR      				= (volatile uint32* const) (BASE::ETHERNET + 0x1C4);
		};
		
		namespace PTP
		{
			volatile uint32* const TSCR      					= (volatile uint32* const) (BASE::ETHERNET + 0x700);
			volatile uint32* const SSIR      					= (volatile uint32* const) (BASE::ETHERNET + 0x704);
			volatile uint32* const TSHR      					= (volatile uint32* const) (BASE::ETHERNET + 0x708);
			volatile uint32* const TSLR      					= (volatile uint32* const) (BASE::ETHERNET + 0x70C);
			volatile uint32* const TSHUR      				= (volatile uint32* const) (BASE::ETHERNET + 0x710);
			volatile uint32* const TSLUR      				= (volatile uint32* const) (BASE::ETHERNET + 0x714);
			volatile uint32* const TSAR      					= (volatile uint32* const) (BASE::ETHERNET + 0x718);
			volatile uint32* const TTHR      					= (volatile uint32* const) (BASE::ETHERNET + 0x71C);
			volatile uint32* const TTLR      					= (volatile uint32* const) (BASE::ETHERNET + 0x720);
		};
		
		namespace DMA
		{
			volatile uint32* const BMR      					= (volatile uint32* const) (BASE::ETHERNET + 0x1000);
			volatile uint32* const TPDR     					= (volatile uint32* const) (BASE::ETHERNET + 0x1004);
			volatile uint32* const RPDR     					= (volatile uint32* const) (BASE::ETHERNET + 0x1008);
			volatile uint32* const RDLAR    					= (volatile uint32* const) (BASE::ETHERNET + 0x100C);
			volatile uint32* const TDLAR    					= (volatile uint32* const) (BASE::ETHERNET + 0x1010);
			volatile uint32* const SR      						= (volatile uint32* const) (BASE::ETHERNET + 0x1014);
			volatile uint32* const OMR      					= (volatile uint32* const) (BASE::ETHERNET + 0x1018);
			volatile uint32* const IER      					= (volatile uint32* const) (BASE::ETHERNET + 0x101C);
			volatile uint32* const MFBOCR   					= (volatile uint32* const) (BASE::ETHERNET + 0x1020);
			volatile uint32* const CHTDR    					= (volatile uint32* const) (BASE::ETHERNET + 0x1048);
			volatile uint32* const CHRDR    					= (volatile uint32* const) (BASE::ETHERNET + 0x104C);
			volatile uint32* const CHTBAR   					= (volatile uint32* const) (BASE::ETHERNET + 0x1050);
			volatile uint32* const CHRBAR   					= (volatile uint32* const) (BASE::ETHERNET + 0x1054);
		};
	}
	
	namespace USB_OTG
	{
		namespace GLOBAL
		{
			volatile uint32* const OTG_CTL							= (volatile uint32* const) (BASE::USB_OTG + 0x0000);
			volatile uint32* const OTG_INT							= (volatile uint32* const) (BASE::USB_OTG + 0x0004);
			volatile uint32* const AHB_CFG							= (volatile uint32* const) (BASE::USB_OTG + 0x0008);
			volatile uint32* const USB_CFG							= (volatile uint32* const) (BASE::USB_OTG + 0x000C);
			volatile uint32* const RST_CTL							= (volatile uint32* const) (BASE::USB_OTG + 0x0010);
			volatile uint32* const INT_STS							= (volatile uint32* const) (BASE::USB_OTG + 0x0014);
			volatile uint32* const INT_MSK							= (volatile uint32* const) (BASE::USB_OTG + 0x0018);
			volatile uint32* const RX_STSR							= (volatile uint32* const) (BASE::USB_OTG + 0x001C);
			volatile uint32* const RX_STSP							= (volatile uint32* const) (BASE::USB_OTG + 0x0020);
			volatile uint32* const RX_FSIZ							= (volatile uint32* const) (BASE::USB_OTG + 0x0024);
			volatile uint32* const HNPTFSIZ_DIEPTXF0		= (volatile uint32* const) (BASE::USB_OTG + 0x0028);
			volatile uint32* const HNPTXSTS							= (volatile uint32* const) (BASE::USB_OTG + 0x002C);
			volatile uint32* const GCCFG								= (volatile uint32* const) (BASE::USB_OTG + 0x0038);
			volatile uint32* const CID									= (volatile uint32* const) (BASE::USB_OTG + 0x003C);
			volatile uint32* const HPTX_FSIZ						= (volatile uint32* const) (BASE::USB_OTG + 0x0100);
			volatile uint32* const DIEP_TXF1						= (volatile uint32* const) (BASE::USB_OTG + 0x0104);
			volatile uint32* const DIEP_TXF2						= (volatile uint32* const) (BASE::USB_OTG + 0x0108);
			volatile uint32* const DIEP_TXF3						= (volatile uint32* const) (BASE::USB_OTG + 0x010C);
		};
		
		namespace HOST
		{
			volatile uint32* const CFG									= (volatile uint32* const) (BASE::USB_OTG + 0x0400);
			volatile uint32* const FIR									= (volatile uint32* const) (BASE::USB_OTG + 0x0404);
			volatile uint32* const FNUM									= (volatile uint32* const) (BASE::USB_OTG + 0x0408);
			volatile uint32* const PTX_STS							= (volatile uint32* const) (BASE::USB_OTG + 0x0410);
			volatile uint32* const AINT									= (volatile uint32* const) (BASE::USB_OTG + 0x0414);
			volatile uint32* const AINT_MSK							= (volatile uint32* const) (BASE::USB_OTG + 0x0418);
			volatile uint32* const PRT									= (volatile uint32* const) (BASE::USB_OTG + 0x0440);
			
			
			volatile uint32* const CHAR0								= (volatile uint32* const) (BASE::USB_OTG + 0x0500);
			volatile uint32* const INT0									= (volatile uint32* const) (BASE::USB_OTG + 0x0508);
			volatile uint32* const INTMSK0							= (volatile uint32* const) (BASE::USB_OTG + 0x050C);
			volatile uint32* const TSIZ0								= (volatile uint32* const) (BASE::USB_OTG + 0x0510);
			
			volatile uint32* const CHAR1								= (volatile uint32* const) (BASE::USB_OTG + 0x0520);
			volatile uint32* const INT1									= (volatile uint32* const) (BASE::USB_OTG + 0x0528);
			volatile uint32* const INTMSK1							= (volatile uint32* const) (BASE::USB_OTG + 0x052C);
			volatile uint32* const TSIZ1								= (volatile uint32* const) (BASE::USB_OTG + 0x0530);
			
			volatile uint32* const CHAR2								= (volatile uint32* const) (BASE::USB_OTG + 0x0540);
			volatile uint32* const INT2									= (volatile uint32* const) (BASE::USB_OTG + 0x0548);
			volatile uint32* const INTMSK2							= (volatile uint32* const) (BASE::USB_OTG + 0x054C);
			volatile uint32* const TSIZ2								= (volatile uint32* const) (BASE::USB_OTG + 0x0550);
			
			volatile uint32* const CHAR3								= (volatile uint32* const) (BASE::USB_OTG + 0x0560);
			volatile uint32* const INT3									= (volatile uint32* const) (BASE::USB_OTG + 0x0568);
			volatile uint32* const INTMSK3							= (volatile uint32* const) (BASE::USB_OTG + 0x056C);
			volatile uint32* const TSIZ3								= (volatile uint32* const) (BASE::USB_OTG + 0x0570);
			
			volatile uint32* const CHAR4								= (volatile uint32* const) (BASE::USB_OTG + 0x0580);
			volatile uint32* const INT4									= (volatile uint32* const) (BASE::USB_OTG + 0x0588);
			volatile uint32* const INTMSK4							= (volatile uint32* const) (BASE::USB_OTG + 0x058C);
			volatile uint32* const TSIZ4								= (volatile uint32* const) (BASE::USB_OTG + 0x0590);
			
			volatile uint32* const CHAR5								= (volatile uint32* const) (BASE::USB_OTG + 0x05A0);
			volatile uint32* const INT5									= (volatile uint32* const) (BASE::USB_OTG + 0x05A8);
			volatile uint32* const INTMSK5							= (volatile uint32* const) (BASE::USB_OTG + 0x05AC);
			volatile uint32* const TSIZ5								= (volatile uint32* const) (BASE::USB_OTG + 0x05B0);
			
			volatile uint32* const CHAR6								= (volatile uint32* const) (BASE::USB_OTG + 0x05C0);
			volatile uint32* const INT6									= (volatile uint32* const) (BASE::USB_OTG + 0x05C8);
			volatile uint32* const INTMSK6							= (volatile uint32* const) (BASE::USB_OTG + 0x05CC);
			volatile uint32* const TSIZ6								= (volatile uint32* const) (BASE::USB_OTG + 0x05D0);
			
			volatile uint32* const CHAR7								= (volatile uint32* const) (BASE::USB_OTG + 0x05E0);
			volatile uint32* const INT7									= (volatile uint32* const) (BASE::USB_OTG + 0x05E8);
			volatile uint32* const INTMSK7							= (volatile uint32* const) (BASE::USB_OTG + 0x05EC);
			volatile uint32* const TSIZ7 								= (volatile uint32* const) (BASE::USB_OTG + 0x05F0);
			
			
			volatile uint32* const FIFO_0								= (volatile uint32* const) (BASE::USB_OTG + 0x1000);
			volatile uint32* const FIFO_1								= (volatile uint32* const) (BASE::USB_OTG + 0x2000);
			volatile uint32* const FIFO_2								= (volatile uint32* const) (BASE::USB_OTG + 0x3000);
			volatile uint32* const FIFO_3								= (volatile uint32* const) (BASE::USB_OTG + 0x4000);
			volatile uint32* const FIFO_4								= (volatile uint32* const) (BASE::USB_OTG + 0x5000);
			volatile uint32* const FIFO_5								= (volatile uint32* const) (BASE::USB_OTG + 0x6000);
			volatile uint32* const FIFO_6								= (volatile uint32* const) (BASE::USB_OTG + 0x7000);
			volatile uint32* const FIFO_7								= (volatile uint32* const) (BASE::USB_OTG + 0x8000);
		};
		
		namespace DEVICE
		{
			volatile uint32* const CFG									= (volatile uint32* const) (BASE::USB_OTG + 0x0800);
			volatile uint32* const CTL									= (volatile uint32* const) (BASE::USB_OTG + 0x0804);
			volatile uint32* const STS									= (volatile uint32* const) (BASE::USB_OTG + 0x0808);
			volatile uint32* const IEPMSK								= (volatile uint32* const) (BASE::USB_OTG + 0x0810);
			volatile uint32* const OEPMSK								= (volatile uint32* const) (BASE::USB_OTG + 0x0814);
			volatile uint32* const AINT									= (volatile uint32* const) (BASE::USB_OTG + 0x0818);
			volatile uint32* const AINTMSK							= (volatile uint32* const) (BASE::USB_OTG + 0x081C);
			volatile uint32* const VBUS_DIS							= (volatile uint32* const) (BASE::USB_OTG + 0x0828);
			volatile uint32* const VBUS_PULSE						= (volatile uint32* const) (BASE::USB_OTG + 0x082C);
			volatile uint32* const IEP_EMPMSK						= (volatile uint32* const) (BASE::USB_OTG + 0x0834);
			
			
			volatile uint32* const IEP_CTL0							= (volatile uint32* const) (BASE::USB_OTG + 0x0900);
			volatile uint32* const IEP_INT0							= (volatile uint32* const) (BASE::USB_OTG + 0x0908);
			volatile uint32* const IEP_TSIZ0						= (volatile uint32* const) (BASE::USB_OTG + 0x0910);
			volatile uint32* const TX_FSTS0							= (volatile uint32* const) (BASE::USB_OTG + 0x0918);
			
			volatile uint32* const IEP_CTL1							= (volatile uint32* const) (BASE::USB_OTG + 0x0920);
			volatile uint32* const IEP_INT1							= (volatile uint32* const) (BASE::USB_OTG + 0x0928);
			volatile uint32* const IEP_TSIZ1						= (volatile uint32* const) (BASE::USB_OTG + 0x0930);
			volatile uint32* const TX_FSTS1							= (volatile uint32* const) (BASE::USB_OTG + 0x0938);
			
			volatile uint32* const IEP_CTL2							= (volatile uint32* const) (BASE::USB_OTG + 0x0940);
			volatile uint32* const IEP_INT2							= (volatile uint32* const) (BASE::USB_OTG + 0x0948);
			volatile uint32* const IEP_TSIZ2						= (volatile uint32* const) (BASE::USB_OTG + 0x0950);
			volatile uint32* const TX_FSTS2							= (volatile uint32* const) (BASE::USB_OTG + 0x0958);
			
			volatile uint32* const IEP_CTL3							= (volatile uint32* const) (BASE::USB_OTG + 0x0960);
			volatile uint32* const IEP_INT3							= (volatile uint32* const) (BASE::USB_OTG + 0x0968);
			volatile uint32* const IEP_TSIZ3						= (volatile uint32* const) (BASE::USB_OTG + 0x0970);
			volatile uint32* const TX_FSTS3							= (volatile uint32* const) (BASE::USB_OTG + 0x0978);
			
			
			volatile uint32* const OEP_CTL0							= (volatile uint32* const) (BASE::USB_OTG + 0x0B00);
			volatile uint32* const OEP_INT0							= (volatile uint32* const) (BASE::USB_OTG + 0x0B08);
			volatile uint32* const OEP_TSIZ0						= (volatile uint32* const) (BASE::USB_OTG + 0x0B10);
			
			volatile uint32* const OEP_CTL1							= (volatile uint32* const) (BASE::USB_OTG + 0x0B20);
			volatile uint32* const OEP_INT1							= (volatile uint32* const) (BASE::USB_OTG + 0x0B28);
			volatile uint32* const OEP_TSIZ1						= (volatile uint32* const) (BASE::USB_OTG + 0x0B30);
			
			volatile uint32* const OEP_CTL2							= (volatile uint32* const) (BASE::USB_OTG + 0x0B40);
			volatile uint32* const OEP_INT2							= (volatile uint32* const) (BASE::USB_OTG + 0x0B48);
			volatile uint32* const OEP_TSIZ2						= (volatile uint32* const) (BASE::USB_OTG + 0x0B50);
			
			volatile uint32* const OEP_CTL3							= (volatile uint32* const) (BASE::USB_OTG + 0x0B60);
			volatile uint32* const OEP_INT3							= (volatile uint32* const) (BASE::USB_OTG + 0x0B68);
			volatile uint32* const OEP_TSIZ3						= (volatile uint32* const) (BASE::USB_OTG + 0x0B70);
			
			
			volatile uint32* const FIFO_0								= (volatile uint32* const) (BASE::USB_OTG + 0x1000);
			volatile uint32* const FIFO_1								= (volatile uint32* const) (BASE::USB_OTG + 0x2000);
			volatile uint32* const FIFO_2								= (volatile uint32* const) (BASE::USB_OTG + 0x3000);
			volatile uint32* const FIFO_3								= (volatile uint32* const) (BASE::USB_OTG + 0x4000);
		};
		
		volatile uint32* const PCGCCTL								= (volatile uint32* const) (BASE::USB_OTG + 0x0E00);
	}
};