#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback Flash::startup()
{
	enable_ECC();
	return(OK);
}


SECTION(bootloader) void Flash::get_registers(uint32 bank, volatile uint32*& KEYR, volatile uint32*& CR, volatile uint32*& SR, volatile uint32*& CCR)
{
	//	Every Bank has its own Control, Status and Key Registers (RM0433, FLASH_CR1/2, FLASH_SR1/2, FLASH_KEYR1/2, FLASH_CCR1/2)
	KEYR	= (bank == 0) ? MCU::FLASH_1::KEY	: MCU::FLASH_2::KEY;
	CR		= (bank == 0) ? MCU::FLASH_1::CR	: MCU::FLASH_2::CR;
	SR		= (bank == 0) ? MCU::FLASH_1::SR	: MCU::FLASH_2::SR;
	CCR		= (bank == 0) ? MCU::FLASH_1::CCR	: MCU::FLASH_2::CCR;
}


SECTION(bootloader) feedback Flash::unlock(uint32 bank)
{
	volatile uint32* KEYR = nullptr;
	volatile uint32* CR = nullptr;
	volatile uint32* SR = nullptr;
	volatile uint32* CCR = nullptr;
	get_registers(bank, KEYR, CR, SR, CCR);
	
	
	//	An already unlocked Register must not be unlocked again, else it stays locked until the next Reset (RM0433, FLASH configuration protection)
	if(bit::isSet(*CR, 0) == true)
	{
		*KEYR = 0x45670123;
		*KEYR = 0xCDEF89AB;
	}
	if(bit::isSet(*CR, 0) == true)
	{
		return(FAIL);
	}
	
	
	//	Clear the Error Flags of previous Operations: with PGSERR or INCERR set, the next Operation is refused
	*CCR = c_errorFlags | (1 << 16);
	return(OK);
}


SECTION(bootloader) feedback Flash::wait(uint32 bank)
{
	volatile uint32* KEYR = nullptr;
	volatile uint32* CR = nullptr;
	volatile uint32* SR = nullptr;
	volatile uint32* CCR = nullptr;
	get_registers(bank, KEYR, CR, SR, CCR);
	
	
	//	QW: the Operation is in the Queue or running - the Flash finishes it or reports an Error (WRPERR, PGSERR, STRBERR, INCERR, OPERR)
	while(bit::isSet(*SR, 2) == true)
	{
		
	}
	if((*SR & c_errorFlags) != 0)
	{
		*CCR = c_errorFlags;
		return(FAIL);
	}
	return(OK);
}
SECTION(bootloader) void Flash::invalidateCaches(const void* address, uint32 sizeInBytes)
{
	//	Data and Instruction Cache may still hold the old Contents: the Code Region with the Flash is cacheable
	Cache& cache = CMOS::get().get_cache();
	cache.DCache_invalidate(address, sizeInBytes);
	cache.ICache_invalidate(address, sizeInBytes);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

SECTION(bootloader) feedback Flash::writePage(uint32* data, uint32 pageNumber)
{
	//	A Page is a Sector of 128 KByte; it is erased first, as writePage does on all Microcontrollers
	//	Called non-virtually: an In-Application Update erases the V-Table in the Flash, the Function has to work without it
	if(data == nullptr || pageNumber >= c_numberOfPages || Flash::erase(pageNumber) != OK)
	{
		return(FAIL);
	}
	const uint32 bank = pageNumber / c_numberOfSectorsPerBank;
	if(unlock(bank) != OK)
	{
		return(FAIL);
	}
	volatile uint32* KEYR = nullptr;
	volatile uint32* CR = nullptr;
	volatile uint32* SR = nullptr;
	volatile uint32* CCR = nullptr;
	get_registers(bank, KEYR, CR, SR, CCR);
	
	
	//	Programming with Word Parallelism (PSIZE = 2, for VDD 1.62 ... 3.6 V without VPP), one Flash Word of 32 Byte after the other
	*CR = (*CR & 0xFFFFFFC1) | (0x2 << 4) | (1 << 1);
	volatile uint32* const page = (volatile uint32*) (c_flashStartAddress + pageNumber * c_pageSizeInBytes);
	feedback result = OK;
	for(uint32 flashWord = 0; flashWord < c_pageSizeInBytes / 32 && result == OK; flashWord++)
	{
		//	A complete Flash Word has to be written, with 32 Bit Accesses in Order (the ECC covers the whole Word)
		for(uint32 i = 0; i < 8; i++)
		{
			page[8 * flashWord + i] = data[8 * flashWord + i];
		}
		asm volatile("dsb" ::: "memory");
		result = wait(bank);
	}
	
	
	//	End of Programming, lock the Register
	bit::clear(*CR, 1);
	bit::set(*CR, 0);
	
	
	invalidateCaches((const void*) page, c_pageSizeInBytes);
	return(result);
}


SECTION(bootloader) feedback Flash::erase(uint32 pageNumber)
{
	if(pageNumber >= c_numberOfPages)
	{
		return(FAIL);
	}
	const uint32 bank = pageNumber / c_numberOfSectorsPerBank;
	const uint32 sector = pageNumber % c_numberOfSectorsPerBank;
	if(unlock(bank) != OK)
	{
		return(FAIL);
	}
	volatile uint32* KEYR = nullptr;
	volatile uint32* CR = nullptr;
	volatile uint32* SR = nullptr;
	volatile uint32* CCR = nullptr;
	get_registers(bank, KEYR, CR, SR, CCR);
	
	
	//	Sector Erase (SER, SNB) with Word Parallelism, then START
	*CR = (*CR & 0xFFFFF8C1) | (sector << 8) | (0x2 << 4) | (1 << 2);
	bit::set(*CR, 7);
	const feedback result = wait(bank);
	
	
	//	End of the Erase, lock the Register
	bit::clear(*CR, 2);
	bit::set(*CR, 0);
	
	
	invalidateCaches((const void*) (c_flashStartAddress + pageNumber * c_pageSizeInBytes), c_pageSizeInBytes);
	return(result);
}


SECTION(bootloader) feedback Flash::erase()
{
	//	Bank Erase (BER) of both Banks - this also erases the Program
	feedback result = OK;
	for(uint32 bank = 0; bank < 2; bank++)
	{
		if(unlock(bank) != OK)
		{
			return(FAIL);
		}
		volatile uint32* KEYR = nullptr;
		volatile uint32* CR = nullptr;
		volatile uint32* SR = nullptr;
		volatile uint32* CCR = nullptr;
		get_registers(bank, KEYR, CR, SR, CCR);
		*CR = (*CR & 0xFFFFFFC1) | (0x2 << 4) | (1 << 3);
		bit::set(*CR, 7);
		if(wait(bank) != OK)
		{
			result = FAIL;
		}
		bit::clear(*CR, 3);
		bit::set(*CR, 0);
	}
	invalidateCaches((const void*) c_flashStartAddress, c_size);
	return(result);
}


SECTION(bootloader) feedback Flash::write(const uint32* flashWord, uint32 address)
{
	//	One Flash Word of 32 Byte (8 Words with ECC) at an erased, 32 Byte aligned Address
	if(flashWord == nullptr || address < c_flashStartAddress || address >= c_flashStartAddress + c_size || address % 32 != 0)
	{
		return(FAIL);
	}
	const uint32 bank = (address - c_flashStartAddress) / (c_numberOfSectorsPerBank * c_pageSizeInBytes);
	if(unlock(bank) != OK)
	{
		return(FAIL);
	}
	volatile uint32* KEYR = nullptr;
	volatile uint32* CR = nullptr;
	volatile uint32* SR = nullptr;
	volatile uint32* CCR = nullptr;
	get_registers(bank, KEYR, CR, SR, CCR);
	
	
	//	Programming with Word Parallelism (PSIZE = 2): the eighth Word starts the Programming of the Flash Word
	*CR = (*CR & 0xFFFFFFC1) | (0x2 << 4) | (1 << 1);
	volatile uint32* const destination = (volatile uint32*) address;
	for(uint32 i = 0; i < 8; i++)
	{
		destination[i] = flashWord[i];
	}
	asm volatile("dsb" ::: "memory");
	const feedback result = wait(bank);
	
	
	//	End of Programming, lock the Register
	bit::clear(*CR, 1);
	bit::set(*CR, 0);
	invalidateCaches((const void*) address, 32);
	return(result);
}


feedback Flash::swapBanks()
{
	//	Bank Swapping (RM0433, Flash bank and register swapping): SWAP_BANK_OPT inverted in FLASH_OPTSR_PRG, Option Byte Change, then Reset
	//	The Bank at 0x08100000 is mapped to 0x08000000 after the Reset - the Registers of Bank 1 and 2 swap with it
	//	Not on Revision Y and W (REV_ID 0x1003, Errata Sheet ES0392): there the Bank Swapping can make the Flash Interface unpredictable
	if(PWR::isRevisionY() == true)
	{
		return(FAIL);
	}
	if(bit::isSet(*MCU::FLASH_1::OPT_CR, 0) == true)
	{
		*MCU::FLASH_1::OPTKEY = 0x08192A3B;
		*MCU::FLASH_1::OPTKEY = 0x4C5D6E7F;
	}
	if(bit::isSet(*MCU::FLASH_1::OPT_CR, 0) == true)
	{
		return(FAIL);
	}
	
	
	//	New Value of SWAP_BANK_OPT (Bit 31): the Inverse of the current one; OPTCHANGEERR of an earlier Change is cleared
	*MCU::FLASH_1::OPT_CCR = (1u << 30);
	const uint32 swapped = (*MCU::FLASH_1::OPT_SR_CUR & (1u << 31)) ^ (1u << 31);
	*MCU::FLASH_1::OPT_SR_PRG = (*MCU::FLASH_1::OPT_SR_PRG & ~(1u << 31)) | swapped;
	
	
	//	Option Byte Change (OPTSTART), wait for OPT_BUSY
	bit::set(*MCU::FLASH_1::OPT_CR, 1);
	while(bit::isSet(*MCU::FLASH_1::OPT_SR_CUR, 0) == true)
	{
		
	}
	const bool changed = bit::isCleared(*MCU::FLASH_1::OPT_SR_CUR, 30) && (*MCU::FLASH_1::OPT_SR_CUR & (1u << 31)) == swapped;
	bit::set(*MCU::FLASH_1::OPT_CR, 0);
	if(changed == false)
	{
		return(FAIL);
	}
	
	
	//	The Swap takes Effect with the Reset
	CMOS::get().reset();
	return(FAIL);
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
	return(32);
}







feedback Flash::set_waitStates(uint32 clock_ahb, PWR::e_voltageLevel voltageLevel)
{
	uint32 mask_ws = 0;
	uint32 mask_pd = 0;
	if(voltageLevel == PWR::e_voltageLevel::VOS_3)
	{
		if(clock_ahb < 45000000)
		{
			mask_ws = 0x0;
			mask_pd = 0x0;
		}
		else
		{
			if(clock_ahb < 90000000)
			{
				mask_ws = 0x1;
				mask_pd = 0x1;
			}
			else
			{
				if(clock_ahb < 135000000)
				{
					mask_ws = 0x2;
					mask_pd = 0x1;
				}
				else
				{
					if(clock_ahb < 180000000)
					{
						mask_ws = 0x3;
						mask_pd = 0x2;
					}
					else
					{
						if(clock_ahb < 225000000)
						{
							mask_ws = 0x4;
							mask_pd = 0x2;
						}
						else
						{
							return(FAIL);
						}
					}
				}
			}
		}
	}

	if(voltageLevel == PWR::e_voltageLevel::VOS_2)
	{
		if(clock_ahb < 55000000)
		{
			mask_ws = 0x0;
			mask_pd = 0x0;
		}
		else
		{
			if(clock_ahb < 110000000)
			{
				mask_ws = 0x1;
				mask_pd = 0x1;
			}
			else
			{
				if(clock_ahb < 165000000)
				{
					mask_ws = 0x2;
					mask_pd = 0x1;
				}
				else
				{
					if(clock_ahb < 225000000)
					{
						mask_ws = 0x3;
						mask_pd = 0x2;
					}
					else
					{
						return(FAIL);
					}
				}
			}
		}
	}

	if(voltageLevel == PWR::e_voltageLevel::VOS_1 || voltageLevel == PWR::e_voltageLevel::VOS_0)
	{
		if(clock_ahb < 70000000)
		{
			mask_ws = 0x0;
			mask_pd = 0x0;
		}
		else
		{
			if(clock_ahb < 140000000)
			{
				mask_ws = 0x1;
				mask_pd = 0x1;
			}
			else
			{
				if(clock_ahb < 185000000)
				{
					mask_ws = 0x2;
					mask_pd = 0x1;
				}
				else
				{
					if(clock_ahb < 210000000)
					{
						mask_ws = 0x2;
						mask_pd = 0x2;
					}
					else
					{
						if(clock_ahb < 225000000)
						{
							mask_ws = 0x3;
							mask_pd = 0x2;
						}
						else
						{
							if(clock_ahb < 480000000)
							{
								mask_ws = 0x4;
								mask_pd = 0x2;
							}
							else
							{
								return(FAIL);
							}
						}
					}
				}
			}
		}
	}
	
	m_waitStates = mask_ws;
	m_programmingDelay = mask_pd;
	
	//	LATENCY and WRHIGHFREQ in one Write Access: with separate Accesses the CPU would run with 0 Wait States in between
	//	FLASH_ACR is one Register, the Address of Bank 2 (Offset 0x100) is an Alias (RM0433, FLASH_ACR)
	const uint32 acr = (*MCU::FLASH_1::ACR & 0xFFFFFFC0) | (mask_pd << 4) | mask_ws;
	*MCU::FLASH_1::ACR = acr;
	
	
	//	The new Wait States are valid once they can be read back (RM0433, FLASH read Operations)
	uint32 timeout = 1000;
	while((*MCU::FLASH_1::ACR & 0x0000003F) != (acr & 0x0000003F))
	{
		timeout--;
		if(timeout == 0)
		{
			return(FAIL);
		}
	}

	return(OK);
}


void Flash::enable_ECC()
{
	*MCU::FLASH_1::KEY = 0x45670123;																																															//	Unlock FLASH_1_CR
	*MCU::FLASH_1::KEY = 0xCDEF89AB;
	
	bit::set(*MCU::FLASH_1::CR, 26);																																															//	Enable Bank 1 ECC Double Detection Error Interrupt
	bit::set(*MCU::FLASH_1::CR, 25);																																															//	Enable Bank 1 ECC Single Correction Error Interrupt
	
	bit::set(*MCU::FLASH_1::CR, 0);																																																//	Lock FLASH_1_CR
}