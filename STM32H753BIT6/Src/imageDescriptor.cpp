#include "../Inc/stm32h753bit6.hpp"





//	Image Descriptor of the Firmware Update: the Linker Template places it behind the Vector Table (KEEP(*(.imageDescriptor)))
//	and takes it from the Library with EXTERN(__cmos_imageDescriptor__), so that every Image of this Microcontroller carries it.
//	The Updater accepts only Images whose Descriptor names the same Microcontroller.
//	Then two erased Flash Words (32 Bytes 0xFF, aligned like the Descriptor at 0x400): Update::commit() programs the first in the new
//	Bank (installed by an Update, on Trial), Update::confirm() the second. Update::write() leaves Flash Words of only 0xFF out, so they
//	stay programmable (ECC). The reserved Words fill the first Flash Word, the Tag behind marks Images that have T and C
struct s_imageDescriptor
{
	uint32 magic;
	uint32 deviceID;
	uint32 reserved[6];
	uint32 trial[8];
	uint32 confirmed[8];
	uint32 flagTag;
};

extern "C" SECTION(imageDescriptor) __attribute__((used)) const s_imageDescriptor __cmos_imageDescriptor__ =
{
	I_UpdateMemory::c_descriptorMagic,
	Update::c_deviceID,
	{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
	{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
	{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
	Update::c_flagTag
};

static_assert(sizeof(s_imageDescriptor) == Update::c_flagTagOffset + 4, "Layout of the Image Descriptor");
