#pragma once

#include "defines.hpp"





//	Flash Layout and Flash Functions of the Firmware Update for the STM32F103C8T6
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
	constexpr uint32 c_flashSize						= 0x00010000;
	constexpr uint32 c_blockSize						= 2048;
	constexpr uint32 c_numberOfBlocks				= c_flashSize / c_blockSize;
	constexpr uint32 c_numberOfImageBlocks		= (c_numberOfBlocks - 4) / 2;
	constexpr uint32 c_firstImageBlock				= 1;
	constexpr uint32 c_scratchBlock					= c_firstImageBlock + c_numberOfImageBlocks;
	constexpr uint32 c_firstDownloadBlock		= c_scratchBlock + 1;
	constexpr uint32 c_controlBlock0				= c_numberOfBlocks - 2;
	constexpr uint32 c_controlBlock1				= c_numberOfBlocks - 1;
	
	//	Device Identifier (DBGMCU_IDCODE DEV_ID, Reference Manual) in the Image Descriptor
	constexpr uint32 c_deviceID							= 0x410;
	
	//	Stack of the Bootloader: End of the SRAM
	constexpr uint32 c_stackTop							= 0x20005000;
	
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
	//	Flash Interface (RM0008, Flash Programming PM0075): Pages of 1024 Bytes, programmed in Half Words
	namespace Register
	{
		volatile uint32* const KEYR									= (volatile uint32*) 0x40022004;
		volatile uint32* const SR										= (volatile uint32*) 0x4002200C;
		volatile uint32* const CR										= (volatile uint32*) 0x40022010;
		volatile uint32* const AR										= (volatile uint32*) 0x40022014;
	};
	constexpr uint32 c_pageSize							= 1024;
	
	
	//	BSY (Bit 0); it rises one Cycle after STRT (ES022 2.2.7): the Callers read FLASH_CR back before
	inline void wait()
	{
		while((*Register::SR & (1u << 0)) != 0)
		{
			
		}
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
		if((*Register::CR & (1u << 7)) != 0)
		{
			*Register::KEYR = 0x45670123;
			*Register::KEYR = 0xCDEF89AB;
		}
	}
	
	
	inline void lock()
	{
		wait();
		*Register::CR = *Register::CR | (1u << 7);
	}
	
	
	inline bool erase(uint32 block)
	{
		//	Every Page of the Block: PER, Address in FLASH_AR, STRT; EOP, WRPRTERR and PGERR are cleared by writing 1
		bool result = true;
		for(uint32 address = get_blockAddress(block); address < get_blockAddress(block) + c_blockSize; address += c_pageSize)
		{
			wait();
			*Register::SR = (1u << 5) | (1u << 4) | (1u << 2);
			*Register::CR = *Register::CR | (1u << 1);
			*Register::AR = address;
			*Register::CR = *Register::CR | (1u << 6);
			(void) *Register::CR;
			wait();
			*Register::CR = *Register::CR & ~(1u << 1);
			if((*Register::SR & ((1u << 4) | (1u << 2))) != 0)
			{
				result = false;
			}
		}
		return(result);
	}
	
	
	inline bool program(uint32 address, uint32 word0, uint32 word1)
	{
		//	Four Half Words (PG), each one starts its own Programming
		const uint16 halfWords[4] = {(uint16) word0, (uint16) (word0 >> 16), (uint16) word1, (uint16) (word1 >> 16)};
		bool result = true;
		wait();
		*Register::SR = (1u << 5) | (1u << 4) | (1u << 2);
		*Register::CR = *Register::CR | (1u << 0);
		for(uint32 i = 0; i < 4; i++)
		{
			*((volatile uint16*) (address + 2 * i)) = halfWords[i];
			(void) *Register::CR;
			wait();
			if((*Register::SR & ((1u << 4) | (1u << 2))) != 0)
			{
				result = false;
			}
		}
		*Register::CR = *Register::CR & ~(1u << 0);
		return(result == true && *((volatile uint32*) address) == word0 && *((volatile uint32*) (address + 4)) == word1);
	}
	
	
	inline bool clearEccError()
	{
		//	The Flash of the F1 has no ECC (RM0008): no Flash Error causes the NMI
		return(false);
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
