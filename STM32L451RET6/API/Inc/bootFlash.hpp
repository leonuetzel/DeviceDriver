#pragma once

#include "defines.hpp"





//	Flash Layout and Flash Functions of the Firmware Update for the STM32L451RET6
//	The Mini-Bootloader (DeviceDriver/Bootloader) and the Driver Update use this File both, so they always agree on the Layout
//	Only Register Accesses, no other Driver: the Bootloader is built without CMOS and DeviceDriver
//
//	Layout in Blocks of c_blockSize Bytes:
//		Block 0								Mini-Bootloader, never overwritten
//		Blocks 1 ... A						Application (linked to c_flashStart + c_blockSize)
//		Block A + 1							Scratch Block of the Swap
//		Blocks A + 2 ... 2A + 1		Download of the new Image; after the Swap the old Image, until the new one is confirmed
//		last two Blocks					Control Blocks: State of the Update (bootControl.hpp)
namespace BootFlash
{
	constexpr uint32 c_flashStart						= 0x08000000;
	constexpr uint32 c_flashSize						= 0x00080000;
	constexpr uint32 c_blockSize						= 2048;
	constexpr uint32 c_numberOfBlocks				= c_flashSize / c_blockSize;
	constexpr uint32 c_numberOfImageBlocks		= (c_numberOfBlocks - 4) / 2;
	constexpr uint32 c_firstImageBlock				= 1;
	constexpr uint32 c_scratchBlock					= c_firstImageBlock + c_numberOfImageBlocks;
	constexpr uint32 c_firstDownloadBlock		= c_scratchBlock + 1;
	constexpr uint32 c_controlBlock0				= c_numberOfBlocks - 2;
	constexpr uint32 c_controlBlock1				= c_numberOfBlocks - 1;
	
	//	Device Identifier (DBGMCU_IDCODE DEV_ID, Reference Manual) in the Image Descriptor
	constexpr uint32 c_deviceID							= 0x462;
	
	//	Stack of the Bootloader: End of the SRAM
	constexpr uint32 c_stackTop							= 0x20020000;
	
	//	Value of erased Flash Memory
	constexpr uint32 c_erased								= 0xFFFFFFFF;
	
	//	Image Descriptor behind the Vector Table (Update::get_descriptorOffset() checks the Offset): Word 2 is the Tag "FLIM", Word 3 the
	//	Limit of the Application - the End of its FLASH Region. Old Code up to the Limit is erased, everything above it is kept
	constexpr uint32 c_descriptorOffset			= 0x400;
	constexpr uint32 c_descriptorLimitTag		= 0x4D494C46;			//	"FLIM"
	
	
	inline bool isUsable();
	inline uint32 get_blockAddress(uint32 block);
	inline void unlock();
	inline void lock();
	inline bool erase(uint32 block);
	inline bool program(uint32 address, uint32 word0, uint32 word1);
	inline bool clearEccError();
	inline void refreshWatchdog();
	inline void startWatchdog();
};



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

namespace BootFlash
{
	//	Flash Interface (RM0394, FLASH; the L451 has one Bank of 256 Pages)
	namespace Register
	{
		volatile uint32* const ACR									= (volatile uint32*) 0x40022000;
		volatile uint32* const KEYR									= (volatile uint32*) 0x40022008;
		volatile uint32* const SR										= (volatile uint32*) 0x40022010;
		volatile uint32* const CR										= (volatile uint32*) 0x40022014;
		volatile uint32* const ECCR									= (volatile uint32*) 0x40022018;
	};
	
	
	//	BSY (Bit 16)
	inline void wait()
	{
		while((*Register::SR & (1u << 16)) != 0)
		{
			
		}
	}
	
	
	//	Instruction and Data Cache may hold the old Contents: they are reset while they are disabled (ICEN/DCEN Bits 9/10, ICRST/DCRST Bits 11/12)
	inline void flushCache()
	{
		const uint32 enabled = *Register::ACR & ((1u << 9) | (1u << 10));
		*Register::ACR = *Register::ACR & ~((1u << 9) | (1u << 10));
		*Register::ACR = *Register::ACR | (1u << 11) | (1u << 12);
		*Register::ACR = *Register::ACR & ~((1u << 11) | (1u << 12));
		*Register::ACR = *Register::ACR | enabled;
	}
	
	
	inline bool isUsable()
	{
		return(true);
	}
	
	
	inline uint32 get_blockAddress(uint32 block)
	{
		return(c_flashStart + block * c_blockSize);
	}
	
	
	inline void unlock()
	{
		if((*Register::CR & (1u << 31)) != 0)
		{
			*Register::KEYR = 0x45670123;
			*Register::KEYR = 0xCDEF89AB;
		}
	}
	
	
	inline void lock()
	{
		wait();
		*Register::CR = *Register::CR | (1u << 31);
	}
	
	
	inline bool erase(uint32 block)
	{
		//	A Block is one Page of 2 KByte: PER, PNB (Bits 10:3), STRT
		wait();
		*Register::SR = 0x0000C3FB;
		*Register::CR = (*Register::CR & ~((1u << 15) | (1u << 11) | (0xFFu << 3) | 0x7u)) | (block << 3) | (1u << 1);
		*Register::CR = *Register::CR | (1u << 16);
		wait();
		*Register::CR = *Register::CR & ~(1u << 1);
		flushCache();
		return((*Register::SR & 0x000003FA) == 0);
	}
	
	
	inline bool program(uint32 address, uint32 word0, uint32 word1)
	{
		//	Double Word (PG): the second Word starts the Programming
		wait();
		*Register::SR = 0x0000C3FB;
		*Register::CR = *Register::CR | (1u << 0);
		*((volatile uint32*) address) = word0;
		*((volatile uint32*) (address + 4)) = word1;
		wait();
		*Register::CR = *Register::CR & ~(1u << 0);
		return((*Register::SR & 0x000003FA) == 0 && *((volatile uint32*) address) == word0 && *((volatile uint32*) (address + 4)) == word1);
	}
	
	
	inline bool clearEccError()
	{
		//	ECCD (FLASH_ECCR Bit 31, rc_w1): two Errors in a Double Word, e.g. one that a Power Failure left half programmed - it causes the NMI
		//	Only ECCD is cleared, ECCIE (Bit 24) keeps its Value
		if((*Register::ECCR & (1u << 31)) == 0)
		{
			return(false);
		}
		*Register::ECCR = (*Register::ECCR & (1u << 24)) | (1u << 31);
		return(true);
	}
	
	
	//	IWDG (Key Register 0x40003000, then PR, RLR, SR)
	inline void refreshWatchdog()
	{
		//	Reload (Key 0xAAAA): needed while the IWDG runs - as hardware Watchdog (Option Bit) from the Reset on, or started below. Else
		//	the IWDG is stopped and the Write has no Effect
		*((volatile uint32*) 0x40003000) = 0x0000AAAA;
	}
	
	
	inline void startWatchdog()
	{
		//	For a new Image on Trial: the longest Timeout (Prescaler 256, PR 6, Reload 0xFFF), so an Image that hangs restarts and is counted.
		//	The Image confirms itself or refreshes the IWDG within it; the Driver Watchdog recognizes it at PR != 0 (a Reset sets PR to 0).
		//	Start, Write Access, Prescaler and Reload, wait until SR has taken them over (some LSI Periods), Reload
		*((volatile uint32*) 0x40003000) = 0x0000CCCC;
		*((volatile uint32*) 0x40003000) = 0x00005555;
		*((volatile uint32*) 0x40003004) = 6;
		*((volatile uint32*) 0x40003008) = 0x0FFF;
		for(uint32 i = 0; i < 100000 && (*((volatile uint32*) 0x4000300C) & 0x7) != 0; i++)
		{
			
		}
		*((volatile uint32*) 0x40003000) = 0x0000AAAA;
	}
};
