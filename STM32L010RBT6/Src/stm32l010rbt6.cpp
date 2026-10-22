#include "../Inc/stm32l010rbt6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

INTERRUPT_VECTOR const STM32L010RBT6::s_interruptTable STM32L010RBT6::c_interruptTable =
{
	(uint32) ISR_WWDG,                           																																									// 0x40 Window Watchdog
	(uint32) 0,                                  																																									// 0x44 Reserved
	(uint32) ISR_RTC,                            																																									// 0x48 RTC
	(uint32) ISR_FLASH,                          																																									// 0x4C Flash
	(uint32) ISR_RCC,                            																																									// 0x50 RCC
	(uint32) ISR_EXTI_0_TO_1,                    																																									// 0x54 External Interrupt 0 - 1
	(uint32) ISR_EXTI_2_TO_3,                    																																									// 0x58 External Interrupt 2 - 3
	(uint32) ISR_EXTI_4_TO_15,                   																																									// 0x5C External Interrupt 4 - 15
	(uint32) 0,                                  																																									// 0x60 Reserved
	(uint32) ISR_DMA_CH0,                        																																									// 0x64 DMA Channel 0
	(uint32) ISR_DMA_CH1_CH2,                    																																									// 0x68 DMA Channel 1 - 2
	(uint32) ISR_DMA_CH3_TO_CH6,                 																																									// 0x6C DMA Channel 3 - 6
	(uint32) ISR_ADC,                            																																									// 0x70 ADC
	(uint32) ISR_LP_TIMER_1,                     																																									// 0x74 Low Power Timer 1
	(uint32) 0,                                  																																									// 0x78 Reserved
	(uint32) ISR_TIMER_2,                        																																									// 0x7C Timer 2
	(uint32) 0,                                  																																									// 0x80 Reserved
	(uint32) 0,                                  																																									// 0x84 Reserved
	(uint32) 0,                                  																																									// 0x88 Reserved
	(uint32) 0,                                  																																									// 0x8C Reserved
	(uint32) ISR_TIMER_21,                       																																									// 0x90 Timer 21
	(uint32) 0,                                  																																									// 0x94 Reserved
	(uint32) ISR_TIMER_22,                                  																																			// 0x98 Timer 22
	(uint32) ISR_I2C_1,                          																																									// 0x9C I2C 1
	(uint32) 0,                                  																																									// 0xA0 Reserved
	(uint32) ISR_SPI_1,                          																																									// 0xA4 SPI 1
	(uint32) 0,                                  																																									// 0xA8 Reserved
	(uint32) 0,                                  																																									// 0xAC Reserved
	(uint32) ISR_USART_2,                        																																									// 0xB0 USART 2
	(uint32) ISR_LPUART_1,                                  																																			// 0xB4 Low Power UART 1
	(uint32) 0,                                  																																									// 0xB8 Reserved
	(uint32) 0,                                  																																									// 0xBC Reserved
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

bool STM32L010RBT6::startBegin(volatile uint8& state)
{
	//	Check and Change of the State with Interrupts disabled for a few Instructions: no Thread Switch in between, so exactly one Caller
	//	gets true and starts the Peripheral. Not longer: startup() creates Mutexes and Events through the SVC of CMOS, that needs Interrupts
	//	Approved Exception to "no Interrupt Lock": ARMv6-M has no exclusive Instructions (LDREXB/STREXB), the Lock lasts 4 ... 6 Instructions
	//	and only at the first Call of a Getter - the SysTick stays pending, no Tick is lost
	uint32 primask;
	asm volatile("mrs %[out_a], primask" : [out_a] "=r" (primask) : : "memory");
	asm volatile("cpsid i" : : : "memory");
	const uint8 old = state;
	if(old == c_notStarted)
	{
		state = c_starting;
	}
	asm volatile("msr primask, %[in_a]" : : [in_a] "r" (primask) : "memory");
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


void STM32L010RBT6::copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(dest + i) = *(src + i);
	}
}


void STM32L010RBT6::zeroOutRAM(uint32* startAddress, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(startAddress + i) = 0;
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

uint8 STM32L010RBT6::get_versionMajor()
{
	//	Compiled into the Library: the Version of the Library, not of the Headers the Application uses
	return(DEVICEDRIVER_VERSION_MAJOR);
}


uint8 STM32L010RBT6::get_versionMinor()
{
	return(DEVICEDRIVER_VERSION_MINOR);
}


STM32L010RBT6& STM32L010RBT6::get()
{
	static STM32L010RBT6 stm32l010rbt6;
	return(stm32l010rbt6);
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
		//	GCC puts Inline Assembler on Thumb-1 (armv6-m) into the divided Syntax, the three-Operand Forms of adds need the unified one
		//	GCC switches back to unified Syntax by itself after the Block
		".syntax unified								\n\t"
		
		
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
	
	
	
	
	
	//	Copy non-zero-initialized Variables to SRAM
	STM32L010RBT6::copy_flashToRAM(c_data_flash_start, c_data_ram_start, c_data_flash_size);
	
	
	//	Copy Code from Flash to SRAM
	STM32L010RBT6::copy_flashToRAM(c_code_flash_start, c_code_ram_start, c_code_flash_size);
	
	
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RTC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_FLASH();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RCC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_0_TO_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_2_TO_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_4_TO_15();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_CH1_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA_CH3_TO_CH6();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ADC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LP_TIMER_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_21();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_22();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USART_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_LPUART_1();





uint32 __startup__()
{
	STM32L010RBT6& stm32l010rbt6 = STM32L010RBT6::get();
	if(stm32l010rbt6.startup() != OK)
	{
		return(0);
	}
	return(stm32l010rbt6.get_rcc().get_clock_system());
}