#include "../Inc/stm32f103c8t6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

namespace
{
	void refreshWatchdog()
	{
		//	Every erased Block stops the CPU for some 10 ms: a running Watchdog (e.g. the one of the Trial) is refreshed
		I_Watchdog* const watchdog = CMOS::get().get_watchdog();
		if(watchdog != nullptr && watchdog->isRunning() == true)
		{
			watchdog->refresh();
		}
	}
};



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback Update::prepareDownload()
{
	//	On Trial the Download Area holds the previous Image for the Rollback: no new Download. An unfinished Cleanup is finished first,
	//	else it would erase the new Download later
	BootControl::s_state state;
	const uint32 control = BootControl::get_active(state);
	if(control != 0 && state.phase == BootControl::c_phaseTrial)
	{
		return(FAIL);
	}
	if(control != 0 && state.phase == BootControl::c_phaseConfirming)
	{
		return(cleanup(state));
	}
	return(OK);
}


feedback Update::cleanup(const BootControl::s_state& state)
{
	//	The previous Image in the Download Area, the Scratch Block and old Code behind the new Image up to the Limit of its Descriptor, then
	//	both Control Blocks. Erased without reading: a Block that a Power Failure left half programmed would cause an ECC Error
	const uint32 numberOfBlocks = BootControl::get_numberOfBlocks(state.size);
	const uint32 limitBlocks = get_limitBlocks(numberOfBlocks);
	bool erased = true;
	BootFlash::unlock();
	for(uint32 block = 0; block < numberOfBlocks && erased == true; block++)
	{
		erased = BootFlash::erase(BootFlash::c_firstDownloadBlock + block);
		refreshWatchdog();
	}
	erased = erased == true && BootFlash::erase(BootFlash::c_scratchBlock) == true;
	for(uint32 block = numberOfBlocks; block < limitBlocks && erased == true; block++)
	{
		erased = BootFlash::erase(BootFlash::c_firstImageBlock + block);
		refreshWatchdog();
	}
	erased = erased == true && BootControl::erase() == true;
	BootFlash::lock();
	if(erased == false)
	{
		return(FAIL);
	}
	return(OK);
}


uint32 Update::get_limitBlocks(uint32 numberOfBlocks) const
{
	//	Blocks up to the Limit of the running Image (Image Descriptor, Tag and Limit in Word 2 and 3), only for a plausible Limit - else 0:
	//	then nothing behind the Image is erased. Data of the Application behind the Limit always stays
	const uint32 start = get_imageAddress();
	const volatile uint32* const descriptor = (const volatile uint32*) (start + BootFlash::c_descriptorOffset);
	const uint32 limit = descriptor[3];
	if(descriptor[0] != c_descriptorMagic || descriptor[2] != BootFlash::c_descriptorLimitTag ||
	   limit <= start + numberOfBlocks * BootFlash::c_blockSize || limit > start + BootFlash::c_numberOfImageBlocks * BootFlash::c_blockSize)
	{
		return(0);
	}
	return((limit - start) / BootFlash::c_blockSize);
}





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

uint32 Update::get_capacity() const
{
	//	Without the Layout of the Bootloader (G474 in Single Bank Mode) or with a Bootloader of another Layout (its Tag) no Update is possible
	if(BootFlash::isUsable() == false || BootControl::isBootloaderUsable() == false)
	{
		return(0);
	}
	return(BootFlash::c_numberOfImageBlocks * BootFlash::c_blockSize);
}


uint32 Update::get_imageAddress() const
{
	return(BootFlash::get_blockAddress(BootFlash::c_firstImageBlock));
}


const uint8* Update::get_download() const
{
	return((const uint8*) BootFlash::get_blockAddress(BootFlash::c_firstDownloadBlock));
}


uint32 Update::get_deviceID() const
{
	return(BootFlash::c_deviceID);
}


uint32 Update::get_descriptorOffset() const
{
	//	Exception Vectors of CMOS (16 Words), then the Interrupt Vectors of this Microcontroller - the Bootloader reads the Descriptor
	//	at the same Offset (bootFlash.hpp)
	static_assert(BootFlash::c_descriptorOffset == 16 * 4 + sizeof(STM32F103C8T6::c_interruptTable), "c_descriptorOffset does not match");
	return(BootFlash::c_descriptorOffset);
}


feedback Update::write(uint32 offset, const uint8* data, uint32 size)
{
	if(data == nullptr || offset % c_writeSize != 0 || size % 8 != 0 || offset + size > get_capacity() || prepareDownload() != OK)
	{
		return(FAIL);
	}
	
	
	//	In Double Words; the first Piece of a Block erases the Block of the Download Area
	feedback result = OK;
	BootFlash::unlock();
	for(uint32 i = 0; i < size && result == OK; i += 8)
	{
		const uint32 position = offset + i;
		const uint32 block = BootFlash::c_firstDownloadBlock + position / BootFlash::c_blockSize;
		if(position % BootFlash::c_blockSize == 0 && BootFlash::erase(block) == false)
		{
			result = FAIL;
		}
		const uint32 word0 = data[i] | (data[i + 1] << 8) | (data[i + 2] << 16) | ((uint32) data[i + 3] << 24);
		const uint32 word1 = data[i + 4] | (data[i + 5] << 8) | (data[i + 6] << 16) | ((uint32) data[i + 7] << 24);
		const uint32 address = BootFlash::get_blockAddress(block) + position % BootFlash::c_blockSize;
		
		
		//	Erased Words need no Programming
		if(result == OK && (word0 != BootFlash::c_erased || word1 != BootFlash::c_erased) && BootFlash::program(address, word0, word1) == false)
		{
			result = FAIL;
		}
	}
	BootFlash::lock();
	return(result);
}


feedback Update::commit(uint32 size, uint32 crc32)
{
	if(size == 0 || size > get_capacity() || prepareDownload() != OK)
	{
		return(FAIL);
	}
	
	
	//	Request for the Mini-Bootloader in the Control Blocks (an incomplete Request is invalid)
	BootFlash::unlock();
	const bool written = BootControl::start(size, crc32);
	BootFlash::lock();
	if(written == false)
	{
		return(FAIL);
	}
	
	
	//	After the Reset the Bootloader swaps the Image in and starts it on Trial
	CMOS::get().reset();
	return(FAIL);
}


feedback Update::confirm()
{
	BootControl::s_state state;
	const uint32 control = BootControl::get_active(state);
	if(control == 0 || (state.phase != BootControl::c_phaseTrial && state.phase != BootControl::c_phaseConfirming))
	{
		return(OK);
	}
	
	
	//	The Trial ends with the Change to "confirming": from here on there is no Rollback, an interrupted Cleanup is finished later
	if(state.phase == BootControl::c_phaseTrial)
	{
		state.phase = BootControl::c_phaseConfirming;
		BootFlash::unlock();
		const bool changed = BootControl::change(control, state);
		BootFlash::lock();
		if(changed == false)
		{
			return(FAIL);
		}
		
		
		//	The Watchdog of the Trial runs until the next Reset: CMOS refreshes it from now on, unless the Application has started it itself
		STM32F103C8T6::get().get_watchdog().handOver();
	}
	return(cleanup(state));
}


I_UpdateMemory::e_imageState Update::get_imageState() const
{
	BootControl::s_state state;
	const uint32 control = BootControl::get_active(state);
	if(control != 0 && state.phase == BootControl::c_phaseTrial)
	{
		return(e_imageState::UNCONFIRMED);
	}
	if(control != 0 && state.phase == BootControl::c_phaseReverted)
	{
		return(e_imageState::REVERTED);
	}
	return(e_imageState::CONFIRMED);
}


uint32 Update::get_startsLeft() const
{
	//	The Bootloader counts every Start on Trial in the Header; after c_maxUnconfirmedStarts it restores the previous Image
	static_assert(BootControl::c_maxStarts == c_maxUnconfirmedStarts, "c_maxStarts does not match");
	BootControl::s_state state;
	const uint32 control = BootControl::get_active(state);
	if(control == 0 || state.phase != BootControl::c_phaseTrial || state.starts > BootControl::c_maxStarts)
	{
		return(0);
	}
	return(BootControl::c_maxStarts - state.starts);
}
