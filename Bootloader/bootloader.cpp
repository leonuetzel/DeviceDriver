//	Mini-Bootloader of the Firmware Update with Rollback (DeviceDriver)
//
//	Lies in the first Block of the Flash and is never overwritten. An Update swaps the Application Area and the Download Area Block by
//	Block over the Scratch Block, so the old Image stays in the Download Area until the Application confirms the new one. A new Image
//	that is not confirmed within BootControl::c_maxStarts Starts is swapped back. Every Step is recorded in the Control Blocks
//	(bootControl.hpp): after a Power Failure the Bootloader continues where it stopped.
//
//	Built without CMOS and DeviceDriver (only defines.hpp, bootFlash.hpp and bootControl.hpp): no Interrupts, no Clock Change, no global
//	Variables.

#include "bootControl.hpp"





namespace
{
	[[noreturn]] void halt()
	{
		//	A Flash Error the Bootloader cannot repair: it stops here instead of wearing the Flash out in a Loop (a hardware Watchdog
		//	restarts it)
		BootFlash::lock();
		while(1)
		{
			
		}
	}
	
	
	void check(bool result)
	{
		if(result == false)
		{
			halt();
		}
	}
	
	
	//	CRC-32 (IEEE 802.3) as zlib and the Updater of CMOS compute it: reflected Polynomial 0xEDB88320, Start 0xFFFFFFFF, final Inversion
	uint32 crc32(uint32 firstBlock, uint32 size)
	{
		uint32 crc = 0xFFFFFFFF;
		for(uint32 i = 0; i < size; i++)
		{
			if(i % BootFlash::c_blockSize == 0)
			{
				BootFlash::refreshWatchdog();
			}
			const uint32 block = firstBlock + i / BootFlash::c_blockSize;
			const uint8 byte = *((const volatile uint8*) (BootFlash::get_blockAddress(block) + i % BootFlash::c_blockSize));
			crc ^= byte;
			for(uint32 bit = 0; bit < 8; bit++)
			{
				crc = (crc >> 1) ^ (0xEDB88320 & (0 - (crc & 1)));
			}
		}
		return(~crc);
	}
	
	
	void copyBlock(uint32 source, uint32 destination)
	{
		const uint32 from = BootFlash::get_blockAddress(source);
		const uint32 to = BootFlash::get_blockAddress(destination);
		check(BootFlash::erase(destination));
		for(uint32 offset = 0; offset < BootFlash::c_blockSize; offset += 8)
		{
			const uint32 word0 = *((const volatile uint32*) (from + offset));
			const uint32 word1 = *((const volatile uint32*) (from + offset + 4));
			
			
			//	Erased Words stay erased: nothing to program
			if(word0 != BootFlash::c_erased || word1 != BootFlash::c_erased)
			{
				check(BootFlash::program(to + offset, word0, word1));
			}
		}
		BootFlash::refreshWatchdog();
	}
	
	
	bool swap(uint32 control, BootControl::s_state& state)
	{
		//	Swaps the Blocks of the Image from the first Block of the State on, three recorded Steps per Block. Blocks of the old Image behind
		//	the new one stay untouched, so the Swap back restores it completely. false: the Control Block was full, the State continues in
		//	the other Block
		const uint32 numberOfBlocks = BootControl::get_numberOfBlocks(state.size);
		for(uint32 block = state.firstBlock; block < numberOfBlocks; block++)
		{
			const uint32 unit = BootControl::c_firstRecord + 3 * (block - state.firstBlock);
			if(unit + 3 > BootControl::c_numberOfUnits)
			{
				state.firstBlock = block;
				check(BootControl::change(control, state));
				return(false);
			}
			const uint32 application = BootFlash::c_firstImageBlock + block;
			const uint32 download = BootFlash::c_firstDownloadBlock + block;
			for(uint32 step = 0; step < 3; step++)
			{
				if(BootControl::isSet(control, unit + step) == false)
				{
					//	Application to Scratch Block, Download to Application, Scratch Block to Download
					const uint32 source = (step == 0) ? application : ((step == 1) ? download : BootFlash::c_scratchBlock);
					const uint32 destination = (step == 0) ? BootFlash::c_scratchBlock : ((step == 1) ? application : download);
					copyBlock(source, destination);
					check(BootFlash::program(BootControl::get_unitAddress(control, unit + step), ~BootFlash::c_erased, ~BootFlash::c_erased));
				}
			}
		}
		return(true);
	}
	
	
	void handOver(uint32 control, BootControl::s_state& state)
	{
		//	Before the Application starts: one Header without Units, the other Block erased. A Block with Remains behind its Header (an
		//	interrupted Erase) is written anew
		const uint32 other = BootFlash::c_controlBlock0 + BootFlash::c_controlBlock1 - control;
		if(BootControl::isErased(control, BootControl::c_firstRecord) == false)
		{
			check(BootControl::change(control, state));
		}
		else if(BootControl::isErased(other, 0) == false)
		{
			check(BootFlash::erase(other));
		}
	}
	
	
	void update()
	{
		BootFlash::unlock();
		while(1)
		{
			BootControl::s_state state;
			const uint32 control = BootControl::get_active(state);
			const uint32 numberOfBlocks = BootControl::get_numberOfBlocks(state.size);
			
			
			//	No valid State: Remains of an interrupted Request or of an older Format are erased
			if(control == 0)
			{
				if(BootControl::isErased(BootFlash::c_controlBlock0, 0) == false || BootControl::isErased(BootFlash::c_controlBlock1, 0) == false)
				{
					check(BootControl::erase());
				}
				break;
			}
			if(state.size == 0 || numberOfBlocks > BootFlash::c_numberOfImageBlocks)
			{
				check(BootControl::erase());
				break;
			}
			
			
			if(state.phase == BootControl::c_phaseSwapNew || state.phase == BootControl::c_phaseSwapOld)
			{
				//	Before the first Step the Download must be intact, else the Request is dropped and the old Application stays
				if(state.phase == BootControl::c_phaseSwapNew && state.firstBlock == 0 && BootControl::isSet(control, BootControl::c_firstRecord) == false &&
				   crc32(BootFlash::c_firstDownloadBlock, state.size) != state.crc)
				{
					check(BootControl::erase());
					break;
				}
				if(swap(control, state) == false)
				{
					continue;
				}
				if(state.phase == BootControl::c_phaseSwapNew)
				{
					//	The new Application has to have the CRC of the Download, else the old one is swapped back at once
					state.phase = (crc32(BootFlash::c_firstImageBlock, state.size) == state.crc) ? BootControl::c_phaseTrial : BootControl::c_phaseSwapOld;
				}
				else
				{
					//	The rejected Image is erased
					for(uint32 block = 0; block < numberOfBlocks; block++)
					{
						check(BootFlash::erase(BootFlash::c_firstDownloadBlock + block));
						BootFlash::refreshWatchdog();
					}
					check(BootFlash::erase(BootFlash::c_scratchBlock));
					state.phase = BootControl::c_phaseReverted;
				}
				state.firstBlock = 0;
				check(BootControl::change(control, state));
				continue;
			}
			if(state.phase == BootControl::c_phaseTrial)
			{
				//	Every Start on Trial is a Change with one Start more; after c_maxStarts Starts the old Image is swapped back. The Image starts
				//	with a running IWDG: one that hangs restarts and is counted
				const bool start = state.starts < BootControl::c_maxStarts;
				state.phase = (start == true) ? BootControl::c_phaseTrial : BootControl::c_phaseSwapOld;
				state.starts = (start == true) ? state.starts + 1 : 0;
				check(BootControl::change(control, state));
				if(start == true)
				{
					BootFlash::startWatchdog();
					break;
				}
				continue;
			}
			
			
			//	Reverted, confirmed (Cleanup by the Application) or unknown: the Application starts
			handOver(control, state);
			break;
		}
		BootFlash::lock();
	}
	
	
	[[noreturn]] void systemReset()
	{
		//	SYSRESETREQ in AIRCR (with VECTKEY 0x05FA): the Bootloader starts again, in Thread Mode
		asm volatile("dsb" ::: "memory");
		*((volatile uint32*) 0xE000ED0C) = 0x05FA0004;
		asm volatile("dsb" ::: "memory");
		while(1)
		{
			
		}
	}
	
	
	[[noreturn]] void start()
	{
		//	The Application needs a plausible Vector Table: Stack Pointer aligned, Reset Vector in the Application Area (Thumb)
		const uint32 address = BootFlash::get_blockAddress(BootFlash::c_firstImageBlock);
		const uint32 stackPointer = *((const volatile uint32*) address);
		const uint32 reset = *((const volatile uint32*) (address + 4));
		const uint32 end = BootFlash::get_blockAddress(BootFlash::c_firstImageBlock + BootFlash::c_numberOfImageBlocks - 1) + BootFlash::c_blockSize;
		if(stackPointer == BootFlash::c_erased || (stackPointer & 0x3) != 0 || (reset & 0x1) == 0 || reset < address || reset >= end)
		{
			//	No Application: wait for the Debugger
			while(1)
			{
				
			}
		}
		
		
		//	Vector Table of the Application (VTOR), its Stack Pointer, then its Reset Handler
		*((volatile uint32*) 0xE000ED08) = address;
		asm volatile(
			"msr msp, %0	\n\t"
			"bx %1				\n\t"
			:: "r" (stackPointer), "r" (reset) : "memory");
		while(1)
		{
			
		}
	}
};





extern "C" [[noreturn]] void bootloader_reset()
{
	if(BootFlash::isUsable() == true)
	{
		update();
	}
	start();
}


extern "C" void bootloader_nmi()
{
	//	ECC Double Error of the Flash (L451, G474, C0): a Double Word that a Power Failure left half programmed, e.g. a Unit of a Control
	//	Block. The Read has delivered some Value and the Bootloader continues: an invalid Header is ignored, a half programmed Unit counts as
	//	set (it is written only after its Step). Every other NMI restarts the Microcontroller
	if(BootFlash::clearEccError() == false)
	{
		systemReset();
	}
}


extern "C" [[noreturn]] void bootloader_hardFault()
{
	//	Never continue in the Handler: the Application would run in its Context, without Interrupts
	systemReset();
}


//	Vector Table: Stack Pointer, Reset, NMI and Hard Fault (the Bootloader uses no Interrupts), then the Tag of the Bootloader in the
//	Words of MemManage and BusFault, which it never enables: the Driver Update checks it (BootControl::isBootloaderUsable)
extern "C" __attribute__((section(".vectors"), used)) const uint32 c_bootloaderVectors[6] =
{
	BootFlash::c_stackTop,
	(uint32) &bootloader_reset,
	(uint32) &bootloader_nmi,
	(uint32) &bootloader_hardFault,
	BootControl::c_bootloaderTag,
	BootControl::c_layoutVersion
};
