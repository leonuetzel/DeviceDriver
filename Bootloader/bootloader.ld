/*	Linker Script of the Mini-Bootloader: one Block of 2 KByte at the Start of the Flash, no initialized or zeroed Variables	*/

ENTRY(bootloader_reset)

MEMORY
{
	FLASH			(rx)	: ORIGIN = 0x08000000, LENGTH = 2K
	SRAM			(rwx)	: ORIGIN = 0x20000000, LENGTH = 1K
}

SECTIONS
{
	.text :
	{
		KEEP(*(.vectors))
		*(.text*)
		*(.rodata*)
	} > FLASH
	
	.data :
	{
		*(.data*)
		*(.bss*)
		*(COMMON)
	} > SRAM
	
	/DISCARD/ :
	{
		*(.ARM.exidx*)
		*(.ARM.extab*)
		*(.init_array*)
		*(.fini_array*)
	}
}

/*	The Bootloader has no Startup Code: it must not use global Variables	*/
ASSERT(SIZEOF(.data) == 0, "The Bootloader must not have global Variables")
