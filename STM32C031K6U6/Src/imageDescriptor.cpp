#include "../Inc/stm32c031k6u6.hpp"





//	Image Descriptor of the Firmware Update: the Linker Template places it behind the Vector Table (KEEP(*(.imageDescriptor)))
//	and takes it from the Library with EXTERN(__cmos_imageDescriptor__), so that every Image of this Microcontroller carries it.
//	The Updater accepts only Images whose Descriptor names the same Microcontroller.
//	Word 2 and 3: Tag and Limit of the Application, the End of its FLASH Region (Linker Script: __cmos_flashLimit__ = ORIGIN(FLASH) +
//	LENGTH(FLASH)). The Bootloader erases old Code up to the Limit and keeps everything above it (Data of the Application).
//	The Symbol is weak: without it the Limit is 0, then the Bootloader erases nothing in the Application Area.
//	A Pointer, not (uint32) &Symbol: only an Address Constant is placed in the Flash, a converted Value would be computed at Runtime
extern "C" const uint8 __cmos_flashLimit__[] __attribute__((weak));

struct s_imageDescriptor
{
	uint32 magic;
	uint32 deviceID;
	uint32 limitTag;
	const uint8* limit;
};

extern "C" SECTION(imageDescriptor) __attribute__((used)) const s_imageDescriptor __cmos_imageDescriptor__ =
{
	I_UpdateMemory::c_descriptorMagic,
	BootFlash::c_deviceID,
	BootFlash::c_descriptorLimitTag,
	__cmos_flashLimit__
};
