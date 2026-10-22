#include "../Inc/stm32g474mct6.hpp"





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
	*MCU::FLASH::KEY = c_key1;
	*MCU::FLASH::KEY = c_key2;
	
	
	//	Check if unlock was successful
	if(bit::isCleared(*MCU::FLASH::CR, 31) == true)
	{
		return(OK);
	}
	return(FAIL);
}







SECTION(bootloader) bool Flash::isDualBank()
{
	//	Option Bit DBANK (FLASH_OPTR Bit 22): two Banks with Pages of 2 KByte (Factory Default), else one Bank with Pages of 4 KByte
	return(bit::isSet(*MCU::FLASH::OPTR, 22));
}


SECTION(bootloader) uint32 Flash::get_pageAddress(uint32 pageNumber)
{
	if(isDualBank() == false)
	{
		return(c_flashStartAddress + pageNumber * 2 * c_pageSizeInBytes);
	}
	
	
	//	Dual Bank Mode: Bank 2 always starts at 0x08040000, also on Devices with 256 KByte (RM0440, Table 7)
	//	Between the End of Bank 1 (0x0801FFFF) and Bank 2 is a Gap of 128 KByte
	if(pageNumber >= c_pagesPerBank)
	{
		return(c_bank2StartAddress + (pageNumber - c_pagesPerBank) * c_pageSizeInBytes);
	}
	return(c_flashStartAddress + pageNumber * c_pageSizeInBytes);
}


SECTION(bootloader) bool Flash::isInFlash(uint32 address)
{
	if(isDualBank() == false)
	{
		return(address >= c_flashStartAddress && address < c_flashStartAddress + c_size);
	}
	if(address >= c_flashStartAddress && address < c_flashStartAddress + c_size / 2)
	{
		return(true);
	}
	return(address >= c_bank2StartAddress && address < c_bank2StartAddress + c_size / 2);
}


SECTION(bootloader) feedback Flash::wait()
{
	//	BSY: the Operation is running - the Flash finishes it or reports an Error
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
	{
		
	}
	if((*MCU::FLASH::SR & c_errorFlags) != 0)
	{
		*MCU::FLASH::SR = c_clearFlags;
		return(FAIL);
	}
	return(OK);
}


SECTION(bootloader) uint32 Flash::disableDataCache()
{
	//	ES0430 2.2.6: in Dual Bank Mode, a Read from one Bank while the other is written can corrupt the Data Cache
	//	It is disabled before every Write and reset afterwards (flushCaches); returns the enabled Caches (ICEN/DCEN Bits 9/10)
	const uint32 enabled = *MCU::FLASH::ACR & ((1 << 9) | (1 << 10));
	bit::clear(*MCU::FLASH::ACR, 10);
	return(enabled);
}


SECTION(bootloader) void Flash::flushCaches(uint32 enabled)
{
	//	Instruction and Data Cache may still hold the Contents of an erased Page (RM0440, Programming and caches)
	//	The Caches can only be reset while they are disabled, then the Caches enabled before (disableDataCache) are enabled again
	constexpr uint32 enableBits = (1 << 9) | (1 << 10);
	constexpr uint32 resetBits = (1 << 11) | (1 << 12);
	*MCU::FLASH::ACR = *MCU::FLASH::ACR & ~enableBits;
	*MCU::FLASH::ACR = *MCU::FLASH::ACR | resetBits;
	*MCU::FLASH::ACR = *MCU::FLASH::ACR & ~resetBits;
	*MCU::FLASH::ACR = *MCU::FLASH::ACR | enabled;
}


SECTION(bootloader) feedback Flash::write2Words(uint32 dataAtAddress, uint32 dataAtAddressPlus4Byte, volatile uint64* address)
{
	//	Check that the Address lies in the Flash and is aligned to a Double Word
	const uint32 addressInt = (uint32) address;
	if(isInFlash(addressInt) == false || (addressInt & 0x7) != 0)
	{
		return(FAIL);
	}
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
	{
		
	}
	
	
	//	Clear EOP and the Error Flags of previous Operations, otherwise the Hardware sets PGSERR and refuses this one
	*MCU::FLASH::SR = c_clearFlags;
	
	
	//	Set Programming Bit, the Data Cache is off while programming (disableDataCache)
	const uint32 caches = disableDataCache();
	bit::set(*MCU::FLASH::CR, 0);
	
	
	//	Program: the first Word at the Double Word Address, the second Word starts the Programming
	volatile uint32* const word = (volatile uint32*) addressInt;
	word[0] = dataAtAddress;
	word[1] = dataAtAddressPlus4Byte;
	const feedback result = wait();
	
	
	//	Clear Programming Bit
	bit::clear(*MCU::FLASH::CR, 0);
	flushCaches(caches);
	
	
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
	//	The Functions are called non-virtually: an In-Application Update erases the V-Table in the Flash, writePage has to work without it
	if(data == nullptr || pageNumber >= Flash::get_numberOfPages())
	{
		return(FAIL);
	}
	const uint32 numberOfWords = Flash::get_pageSize() / 4;
	
	
	//	Page Start Address
	volatile uint64* address = (volatile uint64*) get_pageAddress(pageNumber);
	
	
	//	Erase the Page before writing, as writePage does on all Microcontrollers: a Double Word can only be programmed once after an Erase
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
	if(pageNumber >= Flash::get_numberOfPages())
	{
		return(FAIL);
	}
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
	{
		
	}
	
	
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	//	Clear EOP and the Error Flags of previous Operations, otherwise the Hardware sets PGSERR and refuses this one
	*MCU::FLASH::SR = c_clearFlags;
	
	
	//	Page Erase (PER) of the Page (PNB) in its Bank (BKER) - in Single Bank Mode BKER has to stay cleared
	uint32 bank = 0;
	uint32 pageInBank = pageNumber;
	if(isDualBank() == true)
	{
		bank = pageNumber / c_pagesPerBank;
		pageInBank = pageNumber % c_pagesPerBank;
	}
	constexpr uint32 operationBits = (1 << 15) | (1 << 11) | (0x7F << 3) | 0x7;
	*MCU::FLASH::CR = (*MCU::FLASH::CR & ~operationBits) | (bank << 11) | (pageInBank << 3) | (1 << 1);
	
	
	//	Start Erase, the Data Cache is off meanwhile (disableDataCache)
	const uint32 caches = disableDataCache();
	bit::set(*MCU::FLASH::CR, 16);
	const feedback result = wait();
	
	
	//	Clear Page Erase Bit
	bit::clear(*MCU::FLASH::CR, 1);
	flushCaches(caches);
	
	
	//	Verify that Flash Page has been erased
	const uint32* const pageStart = (const uint32*) get_pageAddress(pageNumber);
	for(uint32 i = 0; i < Flash::get_pageSize() / 4 && result == OK; i++)
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
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
	{
		
	}
	
	
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	//	Clear EOP and the Error Flags of previous Operations, otherwise the Hardware sets PGSERR and refuses this one
	*MCU::FLASH::SR = c_clearFlags;
	
	
	//	Mass Erase: MER1 and MER2 together, in both Modes (with only one of them and DBANK = 0 the Hardware sets PGSERR)
	constexpr uint32 operationBits = (1 << 15) | (1 << 11) | (0x7F << 3) | 0x7;
	*MCU::FLASH::CR = (*MCU::FLASH::CR & ~operationBits) | (1 << 15) | (1 << 2);
	
	
	//	Start Erase, the Data Cache is off meanwhile (disableDataCache)
	const uint32 caches = disableDataCache();
	bit::set(*MCU::FLASH::CR, 16);
	const feedback result = wait();
	
	
	//	Clear Mass Erase Bits
	*MCU::FLASH::CR = *MCU::FLASH::CR & ~((1 << 15) | (1 << 2));
	flushCaches(caches);
	
	
	//	Verify that the Flash has been erased
	for(uint32 page = 0; page < Flash::get_numberOfPages() && result == OK; page++)
	{
		const uint32* const pageStart = (const uint32*) get_pageAddress(page);
		for(uint32 i = 0; i < Flash::get_pageSize() / 4; i++)
		{
			if(pageStart[i] != 0xFFFFFFFF)
			{
				//	Lock Access to Flash Registers
				lock_FPEC();
				return(FAIL);
			}
		}
	}
	
	
	//	Lock Access to Flash Registers
	lock_FPEC();
	return(result);
}







SECTION(bootloader) uint32 Flash::get_pageSize() const
{
	return(isDualBank() == true ? c_pageSizeInBytes : 2 * c_pageSizeInBytes);
}


SECTION(bootloader) uint32 Flash::get_numberOfPages() const
{
	return(c_size / Flash::get_pageSize());
}


SECTION(bootloader) uint32 Flash::get_size() const
{
	return(c_size);
}


SECTION(bootloader) uint32 Flash::get_smallestProgrammableBlockSize() const
{
	return(8);
}







feedback Flash::set_waitStates(uint32 clock_ahb, PWR::e_voltageScaling voltageScaling)
{
	typedef struct
	{
		uint32 frequency[5];
	}s_array;
	
	const Pair<PWR::e_voltageScaling, s_array> waitStateMaxFrequencies[3] =
	{
		{PWR::e_voltageScaling::RANGE1_1V28, {34000000, 68000000, 102000000, 136000000, 170000000}},
		{PWR::e_voltageScaling::RANGE1_1V2,  {30000000, 60000000,  90000000, 120000000, 150000000}},
		{PWR::e_voltageScaling::RANGE2_1V0,  {12000000, 24000000,  26000000,  26000000,  26000000}}
	};
	
	
	//	Calculate needed Waitstates
	uint32 waitStates = 4;
	for(auto& i: waitStateMaxFrequencies)
	{
		if(i.first() == voltageScaling)
		{
			const s_array frequencies = i.second();
			for(uint32 j = 0; j < 5; j++)
			{
				const uint32 index = 4 - j;
				if(clock_ahb <= frequencies.frequency[index])
				{
					waitStates = index;
				}
				else
				{
					break;
				}
			}
			break;
		}
	}
	
	
	//	Write Value to Register
	uint32 temp = *MCU::FLASH::ACR & 0xFFFFFFF8;
	*MCU::FLASH::ACR = temp | waitStates;
	
	
	//	Update internal Value
	m_waitStates = waitStates;
	
	
	return(OK);
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
