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

bool STM32F107RCT6::startBegin(volatile uint8& state)
{
	//	Check and Change of the State as one exclusive Access (LDREXB/STREXB, ARMv7-M), without disabling Interrupts: an Exception or a Thread
	//	Switch between the two Instructions clears the exclusive Monitor, STREXB fails and the Check is repeated. So exactly one Caller gets
	//	true and starts the Peripheral
	uint8 old = c_notStarted;
	uint32 failed = 0;
	do
	{
		asm volatile("ldrexb %[out_a], [%[in_a]]" : [out_a] "=r" (old) : [in_a] "r" (&state) : "memory");
		if(old != c_notStarted)
		{
			asm volatile("clrex" : : : "memory");
			break;
		}
		asm volatile("strexb %[out_a], %[in_a], [%[in_b]]" : [out_a] "=&r" (failed) : [in_a] "r" ((uint32) c_starting), [in_b] "r" (&state) : "memory");
	}
	while(failed != 0);
	if(old == c_notStarted)
	{
		return(true);
	}


	//	Another Thread starts it right now: wait until it is started. An Interrupt (IPSR != 0) cannot wait for a Thread - but there the
	//	Peripheral is already in Use, because its Interrupt is only enabled by its Driver
	uint32 ipsr;
	asm volatile("mrs %[out_a], ipsr" : [out_a] "=r" (ipsr) : : "memory");
	CMOS& cmos = CMOS::get();
	while(state != c_started && (ipsr & 0x1FF) == 0)
	{
		cmos.sleep_ms(1);
	}
	return(false);
}


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

uint8 STM32F107RCT6::get_versionMajor()
{
	//	Compiled into the Library: the Version of the Library, not of the Headers the Application uses
	return(DEVICEDRIVER_VERSION_MAJOR);
}


uint8 STM32F107RCT6::get_versionMinor()
{
	return(DEVICEDRIVER_VERSION_MINOR);
}


//	Assembler: sets a Memory Region to zero, Word by Word - start and size are the Linker Symbols of its Address and of its Size in Bytes
//	It uses only r0 (Address), r1 (End) and r2 (0) and no Stack; the local Labels 1 and 2 can be used again
#define ZERO_RAM_ASM(start, size)					\
	"ldr r0, =" start "					\n\t"	\
	"ldr r1, =" size "					\n\t"	\
	"adds r1, r0, r1					\n\t"	\
	"movs r2, #0							\n\t"	\
	"1:											\n\t"	\
	"cmp r0, r1							\n\t"	\
	"bhs 2f									\n\t"	\
	"str r2, [r0]							\n\t"	\
	"adds r0, r0, #4					\n\t"	\
	"b 1b										\n\t"	\
	"2:											\n\t"


//	Reset Handler, Part 1: sets the SRAM to zero and moves the Stack Pointer to the upper End of the Stack Pool of CMOS, then calls Part 2
//	The Function is naked and written in Assembler, it uses no Stack: the initial Stack Pointer of the Vector Table points into the SRAM that is
//	zeroed here. The Stack Pool is unused until CMOS::run() creates the first Thread, and Stack::reserve takes the Blocks from its lower End:
//	Part 2, CMOS::run(), the global Constructors and all Interrupts run on its upper End, until main() starts on its own Stack
NAKED void EXCEPTION_RESET()
{
	asm volatile
	(
		//	Zero SRAM
		ZERO_RAM_ASM("__memory_SRAM_start__", "__memory_SRAM_size__")
		
		
		//	Stack Pointer to the upper End of the Stack Pool (__cmos_stack_start__ + __cmos_stack_size__)
		"ldr r0, =__cmos_stack_start__			\n\t"
		"ldr r1, =__cmos_stack_size__			\n\t"
		"adds r0, r0, r1								\n\t"
		"msr msp, r0									\n\t"
		
		
		//	Part 2, it never returns - the Literals of the ldr Instructions follow directly behind
		"bl __resetHandler__						\n\t"
		"b .												\n\t"
		".ltorg											\n\t"
	);
}





//	Reset Handler, Part 2: runs on the Stack Pool of CMOS, the SRAM is zero
extern "C" void __resetHandler__()
{
	//	External Symbols
	extern uint32 __cmos_data_flash_start__;
	extern uint32 __cmos_data_flash_size__;
	extern uint32 __cmos_data_ram_start__;
	
	extern uint32 __cmos_code_flash_start__;
	extern uint32 __cmos_code_flash_size__;
	extern uint32 __cmos_code_ram_start__;
	
	
	
	
	
	//	Convenience
	const uint32* const	c_data_flash_start	= (uint32*) &__cmos_data_flash_start__;
	const uint32				c_data_flash_size		= (uint32)  &__cmos_data_flash_size__;
	uint32* const				c_data_ram_start		= (uint32*) &__cmos_data_ram_start__;
	
	const uint32* const	c_code_flash_start	= (uint32*) &__cmos_code_flash_start__;
	const uint32				c_code_flash_size		= (uint32)  &__cmos_code_flash_size__;
	uint32* const				c_code_ram_start		= (uint32*) &__cmos_code_ram_start__;
	
	
	
	
	
	//	Enable SRAM Clock in RCC (SRAMEN: SRAM Clock during Sleep Mode)
	bit::set(*MCU::RCC::AHB_ENR, 2);
	
	
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
