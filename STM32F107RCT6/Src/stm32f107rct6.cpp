#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

INTERRUPT_VECTOR const STM32F107RCT6::s_interruptTable STM32F107RCT6::c_interruptTable =
{
	(uint32) ISR_WWDG,			                                                                                            					// 0x040 Window Watchdog
	(uint32) ISR_PVD,                                                                                                        			// 0x044 PVD through EXTI Line
	(uint32) ISR_TAMPER,                                                                                                      		// 0x048 Tamper
	(uint32) ISR_RTC,                                                                                                         		// 0x04C RTC
	(uint32) ISR_FLASH,                                                                                                       		// 0x050 Flash
	(uint32) ISR_RCC,                                                                                                         		// 0x054 RCC
	(uint32) ISR_EXTI_0,                                                                                                      		// 0x058 External Interrupt 0
	(uint32) ISR_EXTI_1,                                                                                                      		// 0x05C External Interrupt 1
	(uint32) ISR_EXTI_2,                                                                                                      		// 0x060 External Interrupt 2
	(uint32) ISR_EXTI_3,                                                                                                      		// 0x064 External Interrupt 3
	(uint32) ISR_EXTI_4,                                                                                                      		// 0x068 External Interrupt 4
	(uint32) ISR_DMA1_CH0,                                                                                                     		// 0x06C DMA 1 Channel 0
	(uint32) ISR_DMA1_CH1,                                                                                                     		// 0x070 DMA 1 Channel 1
	(uint32) ISR_DMA1_CH2,                                                                                                     		// 0x074 DMA 1 Channel 2
	(uint32) ISR_DMA1_CH3,                                                                                                     		// 0x078 DMA 1 Channel 3
	(uint32) ISR_DMA1_CH4,                                                                                                     		// 0x07C DMA 1 Channel 4
	(uint32) ISR_DMA1_CH5,                                                                                                     		// 0x080 DMA 1 Channel 5
	(uint32) ISR_DMA1_CH6,                                                                                                     		// 0x084 DMA 1 Channel 6
	(uint32) ISR_ADC,		                                                                                                					// 0x088 ADC
	(uint32) ISR_CAN1_TX,                                                                                                      		// 0x08C CAN 1 Tx
	(uint32) ISR_CAN1_RX_0,                                                                                                    		// 0x090 CAN 1 Rx 0
	(uint32) ISR_CAN1_RX_1,                                                                                                    		// 0x094 CAN 1 Rx 1
	(uint32) ISR_CAN1_SCE,                                                                                                     		// 0x098 CAN 1 SCE
	(uint32) ISR_EXTI_9_TO_5,                                                                                                 		// 0x09C External Interrupt 9 to 5
	(uint32) ISR_TIMER_1_BREAK,                                                                                               		// 0x0A0 Timer 1 Break
	(uint32) ISR_TIMER_1_UPDATE,                                                                                              		// 0x0A4 Timer 1 Update
	(uint32) ISR_TIMER_1_TRIGGER_COMMUTATION,                                                                                 		// 0x0A8 Timer 1 Trigger and Commutation
	(uint32) ISR_TIMER_1_CAPTURE_COMPARE,                                                                                     		// 0x0AC Timer 1 Capture Compare
	(uint32) ISR_TIMER_2,			                                                                                            				// 0x0B0 Timer 2
	(uint32) ISR_TIMER_3,			                                                                                            				// 0x0B4 Timer 3
	(uint32) ISR_TIMER_4,			                                                                                            				// 0x0B8 Timer 4
	(uint32) ISR_I2C_1_EVENT,                                                                                                 		// 0x0BC I2C 1 Event
	(uint32) ISR_I2C_1_ERROR,                                                                                                 		// 0x0C0 I2C 1 Error
	(uint32) ISR_I2C_2_EVENT,                                                                                                 		// 0x0C4 I2C 2 Event
	(uint32) ISR_I2C_2_ERROR,                                                                                                 		// 0x0C8 I2C 2 Error
	(uint32) ISR_SPI_1,		                                                                                                				// 0x0CC SPI 1
	(uint32) ISR_SPI_2,		                                                                                                				// 0x0D0 SPI 2
	(uint32) ISR_USART_1,  		                                                                                            				// 0x0D4 USART 1
	(uint32) ISR_USART_2,		                                                                                                			// 0x0D8 USART 2
	(uint32) ISR_USART_3,			                                                                                            				// 0x0DC USART 3
	(uint32) ISR_EXTI_15_TO_10,                                                                                               		// 0x0E0 External Interrupt 15 to 10
	(uint32) ISR_RTC_ALARM_EXTI,                                                                                              		// 0x0E4 RTC Alarm through External Interrupt
	(uint32) ISR_USB_OTG_WAKEUP,                                                                                             			// 0x0E8 USB OTG Wakeup
	(uint32) 0,                                                                                                               		// 0x0EC Reserved
	(uint32) 0,                                                                                                               		// 0x0F0 Reserved
	(uint32) 0,                                                                                                               		// 0x0F4 Reserved
	(uint32) 0,                                                                                                               		// 0x0F8 Reserved
	(uint32) 0,                                                                                                               		// 0x0FC Reserved
	(uint32) 0,                                                                                                               		// 0x100 Reserved
	(uint32) 0,                                                                                                               		// 0x104 Reserved
	(uint32) ISR_TIMER_5,                                                                                                         // 0x108 Timer 5
	(uint32) ISR_SPI_3,                                                                                                           // 0x10C SPI 3
	(uint32) ISR_UART_4,                                                                                                          // 0x110 UART 4
	(uint32) ISR_UART_5,                                                                                                          // 0x114 UART 5
	(uint32) ISR_TIMER_6,                                                                                                         // 0x118 Timer 6
	(uint32) ISR_TIMER_7,                                                                                                         // 0x11C Timer 7
	(uint32) ISR_DMA2_CH0,                                                                                                        // 0x120 DMA 1 Channel 0
	(uint32) ISR_DMA2_CH1,                                                                                                        // 0x124 DMA 1 Channel 1
	(uint32) ISR_DMA2_CH2,                                                                                                        // 0x128 DMA 1 Channel 2
	(uint32) ISR_DMA2_CH3,                                                                                                        // 0x12C DMA 1 Channel 3
	(uint32) ISR_DMA2_CH4,                                                                                                        // 0x130 DMA 1 Channel 4
	(uint32) ISR_ETHERNET,                                                                                                        // 0x134 Ethernet
	(uint32) ISR_ETHERNET_WAKEUP,                                                                                                 // 0x138 Ethernet Wakeup
	(uint32) ISR_CAN2_TX,                                                                                                         // 0x13C CAN 2 Tx
	(uint32) ISR_CAN2_RX_0,                                                                                                       // 0x140 CAN 2 Rx 0
	(uint32) ISR_CAN2_RX_1,                                                                                                       // 0x144 CAN 2 Rx 1
	(uint32) ISR_CAN2_SCE,                                                                                                        // 0x148 CAN 2 SCE
	(uint32) ISR_USB_OTG                                                                                                          // 0x14C USB OTG
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void STM32F107RCT6::copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(dest + i) = *(src + i);
	}
}


void STM32F107RCT6::zeroOutRAM(uint32* startAddress, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(startAddress + i) = 0;
	}
}


void STM32F107RCT6::preInit()
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

void EXCEPTION_RESET()
{
	//	External Symbols
	extern uint32 __memory_SRAM_start__;
	extern uint32 __memory_SRAM_size__;
	
	
	
	extern uint32 __cmos_data_flash_start__;
	extern uint32 __cmos_data_flash_size__;
	extern uint32 __cmos_data_ram_start__;
	
	extern uint32 __cmos_code_flash_start__;
	extern uint32 __cmos_code_flash_size__;
	extern uint32 __cmos_code_ram_start__;
	
	
	
	
	
	//	Convenience
	uint32* const				c_memory_SRAM_start	= (uint32*) &__memory_SRAM_start__;
	const uint32				c_memory_SRAM_size	= (uint32)  &__memory_SRAM_size__;
	
	
	
	const uint32* const	c_data_flash_start	= (uint32*) &__cmos_data_flash_start__;
	const uint32				c_data_flash_size		= (uint32)  &__cmos_data_flash_size__;
	uint32* const				c_data_ram_start		= (uint32*) &__cmos_data_ram_start__;
	
	const uint32* const	c_code_flash_start	= (uint32*) &__cmos_code_flash_start__;
	const uint32				c_code_flash_size		= (uint32)  &__cmos_code_flash_size__;
	uint32* const				c_code_ram_start		= (uint32*) &__cmos_code_ram_start__;
	
	
	
	
	
	//	Enable SRAM Clock in RCC
	bit::set(*MCU::RCC::AHB_ENR, 2);
	
	
	//	Zero Memories - IMPORTANT: Dont clear Stackpointer
	STM32F107RCT6::zeroOutRAM(c_memory_SRAM_start, c_memory_SRAM_size - 128);
	
	
	//	Copy non-zero-initialized Variables to SRAM
	STM32F107RCT6::copy_flashToRAM(c_data_flash_start, c_data_ram_start, c_data_flash_size);
	
	
	//	Copy Code from Flash to SRAM
	STM32F107RCT6::copy_flashToRAM(c_code_flash_start, c_code_ram_start, c_code_flash_size);
	
	
	//	Execute Functions that need to be executed before any Initialization has been done (Bootloader)
	STM32F107RCT6::preInit();
	
	
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_PVD();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TAMPER();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RTC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FLASH();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RCC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ADC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN1_TX();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN1_RX_0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN1_RX_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN1_SCE();
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_OTG_WAKEUP();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_UART_4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_UART_5();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_7();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA2_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA2_CH1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA2_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA2_CH3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA2_CH4();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ETHERNET();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ETHERNET_WAKEUP();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN2_TX();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN2_RX_0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN2_RX_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_CAN2_SCE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB_OTG();





uint32 __startup__()
{
	STM32F107RCT6& stm32f107rct6 = STM32F107RCT6::get();
	if(stm32f107rct6.startup() != OK)
	{
		return(0);
	}
	return(stm32f107rct6.get_rcc().get_clock_system());
}
