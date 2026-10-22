#pragma once

#include "bootFlash.hpp"





//	Control Blocks of the Firmware Update with Rollback - identical in all Microcontroller Folders with Mini-Bootloader
//	The Mini-Bootloader (DeviceDriver/Bootloader) and the Driver Update use this File both, so they always agree on Format and State Changes
//
//	The two Control Blocks take Turns: the valid one with the higher Sequence Number is active. A Change writes the new State into the
//	other Block and then erases the old one, so a Power Failure at any Point leaves exactly one valid State.
//
//	Control Block, in Units of 8 Bytes (the smallest programmable Unit of all Microcontrollers):
//		0x00	c_recordMagic, Sequence Number
//		0x08	Size of the Image in Bytes, CRC-32 of the Image
//		0x10	State Word (Phase, Starts, first Block), Check Word over all Values - written last: a Header without it is invalid
//		0x18	only while swapping: one Unit per Step, three Steps per Block (Application to Scratch Block, Download to Application,
//				Scratch Block to Download), each programmed after its Step. A full Block continues in the other Block at its first Block
//
//	The Application reads only the Headers. Reading a half programmed Unit causes an ECC Error (NMI on the L451, G474 and C0), so the
//	Bootloader hands over a clean State: at most one Header without Units, the other Block erased
namespace BootControl
{
	constexpr uint32 c_recordMagic						= 0x32445055;			//	"UPD2"
	constexpr uint32 c_numberOfUnits					= BootFlash::c_blockSize / 8;
	constexpr uint32 c_firstRecord						= 3;
	
	//	Phases of an Update
	constexpr uint32 c_phaseSwapNew					= 1;							//	the new Image is swapped in
	constexpr uint32 c_phaseTrial						= 2;							//	the new Image runs on Trial, its Starts are counted
	constexpr uint32 c_phaseSwapOld					= 3;							//	the old Image is swapped back
	constexpr uint32 c_phaseReverted					= 4;							//	the old Image is back
	constexpr uint32 c_phaseConfirming				= 5;							//	the new Image is confirmed, old Code is still to be erased
	
	//	Starts of a new Image on Trial: the next Start swaps the old Image back
	constexpr uint32 c_maxStarts							= 3;
	
	//	Tag of the Bootloader in Word 4 and 5 of its Vector Table (MemManage and BusFault, which it never enables): the Driver Update
	//	works only with a Bootloader of the same Layout
	constexpr uint32 c_bootloaderTag					= 0x4C424D43;			//	"CMBL"
	constexpr uint32 c_layoutVersion					= 2;
	
	
	struct s_state
	{
		uint32 sequence;
		uint32 size;
		uint32 crc;
		uint32 phase;
		uint32 starts;
		uint32 firstBlock;
	};
	
	
	inline uint32 get_unitAddress(uint32 block, uint32 unit);
	inline bool isSet(uint32 block, uint32 unit);
	inline bool isErased(uint32 block, uint32 firstUnit);
	inline uint32 get_numberOfBlocks(uint32 size);
	inline bool readState(uint32 block, s_state& state);
	inline uint32 get_active(s_state& state);
	inline bool change(uint32 active, s_state& state);
	inline bool start(uint32 size, uint32 crc);
	inline bool erase();
	inline bool isBootloaderUsable();
};



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

namespace BootControl
{
	inline uint32 get_word(uint32 block, uint32 unit, uint32 word)
	{
		return(*((const volatile uint32*) (get_unitAddress(block, unit) + 4 * word)));
	}
	
	
	inline uint32 get_stateWord(const s_state& state)
	{
		return(state.phase | (state.starts << 8) | (state.firstBlock << 16));
	}
	
	
	inline uint32 get_check(const s_state& state)
	{
		return(~(c_recordMagic ^ state.sequence ^ state.size ^ state.crc ^ get_stateWord(state)));
	}
	
	
	inline bool writeState(uint32 block, const s_state& state)
	{
		//	The Check Word last: until it is written, the Header is invalid
		return(BootFlash::program(get_unitAddress(block, 0), c_recordMagic, state.sequence) == true &&
		       BootFlash::program(get_unitAddress(block, 1), state.size, state.crc) == true &&
		       BootFlash::program(get_unitAddress(block, 2), get_stateWord(state), get_check(state)) == true);
	}
	
	
	inline uint32 get_unitAddress(uint32 block, uint32 unit)
	{
		return(BootFlash::get_blockAddress(block) + 8 * unit);
	}
	
	
	inline bool isSet(uint32 block, uint32 unit)
	{
		//	A half programmed Unit counts as set: a Step is recorded only after it is done
		return(get_word(block, unit, 0) != BootFlash::c_erased || get_word(block, unit, 1) != BootFlash::c_erased);
	}
	
	
	inline bool isErased(uint32 block, uint32 firstUnit)
	{
		for(uint32 unit = firstUnit; unit < c_numberOfUnits; unit++)
		{
			if(isSet(block, unit) == true)
			{
				return(false);
			}
		}
		return(true);
	}
	
	
	inline uint32 get_numberOfBlocks(uint32 size)
	{
		return((size + BootFlash::c_blockSize - 1) / BootFlash::c_blockSize);
	}
	
	
	inline bool readState(uint32 block, s_state& state)
	{
		const uint32 word = get_word(block, 2, 0);
		state.sequence = get_word(block, 0, 1);
		state.size = get_word(block, 1, 0);
		state.crc = get_word(block, 1, 1);
		state.phase = word & 0xFF;
		state.starts = (word >> 8) & 0xFF;
		state.firstBlock = word >> 16;
		return(get_word(block, 0, 0) == c_recordMagic && get_word(block, 2, 1) == get_check(state));
	}
	
	
	inline uint32 get_active(s_state& state)
	{
		//	The valid Control Block with the higher Sequence Number, 0 if none is valid (Block 0 is the Bootloader)
		s_state second;
		const bool valid0 = readState(BootFlash::c_controlBlock0, state);
		if(readState(BootFlash::c_controlBlock1, second) == true && (valid0 == false || (int32) (second.sequence - state.sequence) > 0))
		{
			readState(BootFlash::c_controlBlock1, state);
			return(BootFlash::c_controlBlock1);
		}
		return(valid0 == true ? BootFlash::c_controlBlock0 : 0);
	}
	
	
	inline bool change(uint32 active, s_state& state)
	{
		//	The new State into the other Block, then the old Block is erased - only if the new State is written
		const uint32 other = BootFlash::c_controlBlock0 + BootFlash::c_controlBlock1 - active;
		state.sequence++;
		if(BootFlash::erase(other) == false || writeState(other, state) == false)
		{
			return(false);
		}
		return(BootFlash::erase(active));
	}
	
	
	inline bool start(uint32 size, uint32 crc)
	{
		//	Request of a new Update: both Blocks erased, then the first State - a Power Failure in between leaves no valid State
		const s_state state = {1, size, crc, c_phaseSwapNew, 0, 0};
		return(erase() == true && writeState(BootFlash::c_controlBlock0, state) == true);
	}
	
	
	inline bool erase()
	{
		return(BootFlash::erase(BootFlash::c_controlBlock0) == true && BootFlash::erase(BootFlash::c_controlBlock1) == true);
	}
	
	
	inline bool isBootloaderUsable()
	{
		//	The Tag of the Bootloader in Block 0 has to name this Layout: an older Bootloader would misread the Control Blocks
		const uint32 address = BootFlash::get_blockAddress(0);
		return(*((const volatile uint32*) (address + 16)) == c_bootloaderTag && *((const volatile uint32*) (address + 20)) == c_layoutVersion);
	}
};
