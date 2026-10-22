#include "../Inc/stm32c071kbu6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

SECTION(bootloader) feedback Flash::lock_FPEC()
{
	//	Check if its unlocked
	if(bit::isCleared(*MCU::FLASH::CR, 31) == true)
	{
		//	Lock FPEC (Flash Programming/Erasing Controller) by setting LOCK Bit in FLASH_CR
		bit::set(*MCU::FLASH::CR, 31);
	}
	return(OK);
}


SECTION(bootloader) feedback Flash::unlock_FPEC()
{
	//	Check if its already unlocked
	if(bit::isCleared(*MCU::FLASH::CR, 31) == true)
	{
		return(OK);
	}
	
	
	//	Unlock FPEC (Flash Programming/Erasing Controller) by writing two Key Values to FLASH_KEYR
	*MCU::FLASH::KEYR = c_key1;
	*MCU::FLASH::KEYR = c_key2;
	
	
	//	Check if unlock was successful
	if(bit::isCleared(*MCU::FLASH::CR, 31) == true)
	{
		return(OK);
	}
	return(FAIL);
}







SECTION(bootloader) feedback Flash::wait()
{
	//	BSY1: an Operation is running, CFGBSY: its Settings in FLASH_CR are in use - writing FLASH_CR now causes a HardFault (RM0490, FLASH_SR)
	while((*MCU::FLASH::SR & ((1 << 16) | (1 << 18))) != 0)
	{
		
	}
	if((*MCU::FLASH::SR & c_errorFlags) != 0)
	{
		*MCU::FLASH::SR = c_clearFlags;
		return(FAIL);
	}
	return(OK);
}


SECTION(bootloader) void Flash::flushCache()
{
	//	The Instruction Cache may still hold the Contents of an erased Page (RM0490, Programming and cache)
	//	It can only be reset while it is disabled
	const bool enabled = bit::isSet(*MCU::FLASH::ACR, 9);
	bit::clear(*MCU::FLASH::ACR, 9);
	bit::set(*MCU::FLASH::ACR, 11);
	bit::clear(*MCU::FLASH::ACR, 11);
	if(enabled == true)
	{
		bit::set(*MCU::FLASH::ACR, 9);
	}
}


SECTION(bootloader) feedback Flash::write2Words(uint32 dataAtAddress, uint32 dataAtAddressPlus4Byte, volatile uint64* address)
{
	//	Check that the Address lies in the Flash and is aligned to a Double Word
	const uint32 addressInt = (uint32) address;
	if(addressInt < c_flashStartAddress || addressInt >= c_flashStartAddress + c_size || (addressInt & 0x7) != 0)
	{
		return(FAIL);
	}
	
	
	//	Wait until no Operation is running
	while((*MCU::FLASH::SR & ((1 << 16) | (1 << 18))) != 0)
	{
		
	}
	
	
	//	Clear EOP and the Error Flags of previous Operations, otherwise the Hardware sets PGSERR and refuses this one
	*MCU::FLASH::SR = c_clearFlags;
	
	
	//	Set Programming Bit
	bit::set(*MCU::FLASH::CR, 0);
	
	
	//	Program: the first Word at the Double Word Address, the second Word starts the Programming
	volatile uint32* const word = (volatile uint32*) addressInt;
	word[0] = dataAtAddress;
	word[1] = dataAtAddressPlus4Byte;
	const feedback result = wait();
	
	
	//	Clear Programming Bit
	bit::clear(*MCU::FLASH::CR, 0);
	
	
	//	Verify the written Values
	if(result != OK || word[0] != dataAtAddress || word[1] != dataAtAddressPlus4Byte)
	{
		return(FAIL);
	}
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

SECTION(bootloader) feedback Flash::writePage(uint32* data, uint32 pageNumber)
{
	if(data == nullptr || pageNumber >= c_numberOfPages)
	{
		return(FAIL);
	}
	constexpr uint32 numberOfWords = c_pageSizeInBytes / 4;
	
	
	//	Page Start Address
	volatile uint64* address = (volatile uint64*) (c_flashStartAddress + pageNumber * c_pageSizeInBytes);
	
	
	//	Erase the Page before writing, as writePage does on all Microcontrollers: a Double Word can only be programmed once after an Erase
	//	Called non-virtually: an In-Application Update erases the V-Table in the Flash, the Function has to work without it
	if(Flash::erase(pageNumber) != OK)
	{
		return(FAIL);
	}
	
	
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	for(uint32 i = 0; i < numberOfWords / 2; i++)
	{
		if(write2Words(data[2 * i + 0], data[2 * i + 1], address + i) != OK)
		{
			//	Lock Access to Flash Registers
			lock_FPEC();
			return(FAIL);
		}
	}
	
	
	//	Lock Access to Flash Registers
	return(lock_FPEC());
}


SECTION(bootloader) feedback Flash::erase(uint32 pageNumber)
{
	if(pageNumber >= c_numberOfPages)
	{
		return(FAIL);
	}
	
	
	//	Wait until no Operation is running: FLASH_CR must not be written while CFGBSY is set
	while((*MCU::FLASH::SR & ((1 << 16) | (1 << 18))) != 0)
	{
		
	}
	
	
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	//	Clear EOP and the Error Flags of previous Operations, otherwise the Hardware sets PGSERR and refuses this one
	*MCU::FLASH::SR = c_clearFlags;
	
	
	//	Page Erase (PER) of the Page PNB (Bits 8:3)
	constexpr uint32 operationBits = (0x3F << 3) | 0x7;
	*MCU::FLASH::CR = (*MCU::FLASH::CR & ~operationBits) | (pageNumber << 3) | (1 << 1);
	
	
	//	Start Erase (STRT)
	bit::set(*MCU::FLASH::CR, 16);
	const feedback result = wait();
	
	
	//	Clear Page Erase Bit
	bit::clear(*MCU::FLASH::CR, 1);
	flushCache();
	
	
	//	Verify that Flash Page has been erased
	const uint32* const pageStart = (const uint32*) (c_flashStartAddress + pageNumber * c_pageSizeInBytes);
	for(uint32 i = 0; i < c_pageSizeInBytes / 4 && result == OK; i++)
	{
		if(pageStart[i] != 0xFFFFFFFF)
		{
			//	Lock Access to Flash Registers
			lock_FPEC();
			return(FAIL);
		}
	}
	
	
	//	Lock Access to Flash Registers
	lock_FPEC();
	return(result);
}


SECTION(bootloader) feedback Flash::erase()
{
	//	Wait until no Operation is running: FLASH_CR must not be written while CFGBSY is set
	while((*MCU::FLASH::SR & ((1 << 16) | (1 << 18))) != 0)
	{
		
	}
	
	
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	//	Clear EOP and the Error Flags of previous Operations, otherwise the Hardware sets PGSERR and refuses this one
	*MCU::FLASH::SR = c_clearFlags;
	
	
	//	Mass Erase (MER1)
	constexpr uint32 operationBits = (0x3F << 3) | 0x7;
	*MCU::FLASH::CR = (*MCU::FLASH::CR & ~operationBits) | (1 << 2);
	
	
	//	Start Erase (STRT)
	bit::set(*MCU::FLASH::CR, 16);
	const feedback result = wait();
	
	
	//	Clear Mass Erase Bit
	bit::clear(*MCU::FLASH::CR, 2);
	flushCache();
	
	
	//	Verify that the Flash has been erased
	const uint32* const flashStart = (const uint32*) c_flashStartAddress;
	for(uint32 i = 0; i < c_size / 4 && result == OK; i++)
	{
		if(flashStart[i] != 0xFFFFFFFF)
		{
			//	Lock Access to Flash Registers
			lock_FPEC();
			return(FAIL);
		}
	}
	
	
	//	Lock Access to Flash Registers
	lock_FPEC();
	return(result);
}







SECTION(bootloader) uint32 Flash::get_pageSize() const
{
	return(c_pageSizeInBytes);
}


SECTION(bootloader) uint32 Flash::get_numberOfPages() const
{
	return(c_numberOfPages);
}


SECTION(bootloader) uint32 Flash::get_size() const
{
	return(c_size);
}


SECTION(bootloader) uint32 Flash::get_smallestProgrammableBlockSize() const
{
	return(8);
}







SECTION(bootloader) feedback Flash::write(uint32 dataAtAddress, uint32 dataAtAddressPlus4Byte, volatile uint64* address)
{
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	if(write2Words(dataAtAddress, dataAtAddressPlus4Byte, address) != OK)
	{
		//	Lock Access to Flash Registers
		lock_FPEC();
		return(FAIL);
	}
	
	
	//	Lock Access to Flash Registers
	return(lock_FPEC());
}


feedback Flash::write(const Array<uint32>& data, volatile uint64* address)
{
	const uint32 numberOfWords = data.get_size();
	if(numberOfWords % 2 != 0)
	{
		return(FAIL);
	}
	
	
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	for(uint32 i = 0; i < numberOfWords / 2; i++)
	{
		if(write2Words(data[2 * i + 0], data[2 * i + 1], address + i) != OK)
		{
			//	Lock Access to Flash Registers
			lock_FPEC();
			return(FAIL);
		}
	}
	
	
	//	Lock Access to Flash Registers
	return(lock_FPEC());
}
