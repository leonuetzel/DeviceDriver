#include "../Inc/stm32c071kbu6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

INTERRUPT_VECTOR const STM32C071KBU6::s_interruptTable STM32C071KBU6::c_interruptTable =
{
	(uint32) ISR_WWDG,			                                                                                            					// 0x040 Window Watchdog
	(uint32) 0,                                                                                                        						// 0x044 Reserved
	(uint32) ISR_RTC,                                                                                                      				// 0x048 RTC
	(uint32) ISR_FLASH,                                                                                                         	// 0x04C Flash
	(uint32) ISR_RCC_CRS,                                                                                                       	// 0x050 RCC and CRS
	(uint32) ISR_EXTI_0_TO_1,                                                                                        							// 0x054 EXTI 0 to 1
	(uint32) ISR_EXTI_2_TO_3,                                                                                        							// 0x058 EXTI 2 to 3
	(uint32) ISR_EXTI_4_TO_15,                                                                                    								// 0x05C EXTI 4 to 15
	(uint32) ISR_USB,                                                                                                   					// 0x060 USB
	(uint32) ISR_DMA1_CH0,                                                                     																		// 0x064 DMA 1 Channel 0
	(uint32) ISR_DMA1_CH1_CH2,                                                                 																		// 0x068 DMA 1 Channel 1 & 2
	(uint32) ISR_DMA1_CH3_CH4_DMAMUX,                                                                       											// 0x06C DMA 1 Channel 3 & 4 and DMAMUX
	(uint32) ISR_ADC,                                                                          																		// 0x070 ADC
	(uint32) ISR_TIMER_1_BREAK_UPDATE_TRIGGER_COMMUTATION,                                     																		// 0x074 Timer 1 Break Update Trigger Commutation
	(uint32) ISR_TIMER_1_CAPTURE_COMPARE,                                                      																		// 0x078 Timer 1 Capture Compare
	(uint32) ISR_TIMER_2,                                                                                													// 0x07C Timer 2
	(uint32) ISR_TIMER_3,                                                                      																		// 0x080 Timer 3
	(uint32) 0,                                                                                																		// 0x084 Reserved
	(uint32) 0,		                                                                             																		// 0x088 Reserved
	(uint32) ISR_TIMER_14,                                                                     																		// 0x08C Timer 14
	(uint32) 0,                                                                                																		// 0x090 Reserved
	(uint32) ISR_TIMER_16,                                                                     																		// 0x094 Timer 16
	(uint32) ISR_TIMER_17,                                                                     																		// 0x098 Timer 17
	(uint32) ISR_I2C_1,                                                                        																		// 0x09C I2C 1
	(uint32) ISR_I2C_2,                                                                                														// 0x0A0 I2C 2
	(uint32) ISR_SPI_1,                                                                        																		// 0x0A4 SPI 1
	(uint32) ISR_SPI_2,                                                                                														// 0x0A8 SPI 2
	(uint32) ISR_USART_1,                                                                      																		// 0x0AC USART 1
	(uint32) ISR_USART_2,			                                                                 																		// 0x0B0 USART 2
	(uint32) 0,			                                                                           																		// 0x0B4 Reserved
	(uint32) 0,			                                                                           																		// 0x0B8 Reserved
	(uint32) 0                                                                                 																		// 0x0BC Reserved
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

bool STM32C071KBU6::startBegin(volatile uint8& state)
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


void STM32C071KBU6::copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(dest + i) = *(src + i);
	}
}


void STM32C071KBU6::zeroOutRAM(uint32* startAddress, uint32 sizeInBytes)
{
	for(uint32 i = 0; i < sizeInBytes / 4; i++)
	{
		*(startAddress + i) = 0;
	}
}


void STM32C071KBU6::preInit()
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

uint8 STM32C071KBU6::get_versionMajor()
{
	//	Compiled into the Library: the Version of the Library, not of the Headers the Application uses
	return(DEVICEDRIVER_VERSION_MAJOR);
}


uint8 STM32C071KBU6::get_versionMinor()
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
	STM32C071KBU6::copy_flashToRAM(c_data_flash_start, c_data_ram_start, c_data_flash_size);
	
	
	//	Copy Code from Flash to SRAM
	STM32C071KBU6::copy_flashToRAM(c_code_flash_start, c_code_ram_start, c_code_flash_size);
	
	
	//	Execute Functions that need to be executed before any Initialization has been done (Bootloader)
	STM32C071KBU6::preInit();
	
	
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
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_RCC_CRS();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_0_TO_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_2_TO_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_EXTI_4_TO_15();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USB();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH0();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH1_CH2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_DMA1_CH3_CH4_DMAMUX();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_ADC();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_BREAK_UPDATE_TRIGGER_COMMUTATION();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_1_CAPTURE_COMPARE();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_3();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_14();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_16();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_TIMER_17();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_I2C_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_SPI_2();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USART_1();
WEAK ALIAS(__dummyInterruptHandler__) NOTHROW void ISR_USART_2();





uint32 __startup__()
{
	STM32C071KBU6& stm32f107rct6 = STM32C071KBU6::get();
	if(stm32f107rct6.startup() != OK)
	{
		return(0);
	}
	return(stm32f107rct6.get_rcc().get_clock_system());
}