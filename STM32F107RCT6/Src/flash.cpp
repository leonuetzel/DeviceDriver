#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

SECTION(bootloader) feedback Flash::lock_FPEC()
{
	//	Check if its unlocked
	if(bit::isCleared(*MCU::FLASH::CR, 7) == true)
	{
		//	Lock FPEC (Flash Programming/Erasing Controller) by setting LOCK Bit in FLASH_CR
		bit::set(*MCU::FLASH::CR, 7);
	}
	return(OK);
}


SECTION(bootloader) feedback Flash::unlock_FPEC()
{
	//	Check if its already unlocked
	if(bit::isCleared(*MCU::FLASH::CR, 7) == true)
	{
		return(OK);
	}
	
	
	//	Unlock FPEC (Flash Programming/Erasing Controller) by writing two Key Values to FLASH_KEYR
	*MCU::FLASH::KEYR = c_key1;
	*MCU::FLASH::KEYR = c_key2;
	
	
	//	Check if unlock was successful
	if(bit::isCleared(*MCU::FLASH::CR, 7) == true)
	{
		return(OK);
	}
	return(FAIL);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback Flash::set_waitStates(uint32 clock_ahb)
{
	uint32 temp = *MCU::FLASH::ACR & 0xFFFFFFF8;
	if(clock_ahb <= 24000000)
	{
		*MCU::FLASH::ACR = temp;
		m_waitStates = 0;
	}
	if(clock_ahb > 24000000 && clock_ahb <= 48000000)
	{
		*MCU::FLASH::ACR = temp | 0x1;
		m_waitStates = 1;
	}
	else
	{
		*MCU::FLASH::ACR = temp | 0x2;
		m_waitStates = 2;
	}
	
	return(OK);
}


feedback Flash::set_prefetchBuffer(bool active)
{
	if(active == true && bit::isCleared(*MCU::FLASH::ACR, 4))
	{
		bit::set(*MCU::FLASH::ACR, 4);
	}
	else
	{
		bit::clear(*MCU::FLASH::ACR, 4);
	}
	
	return(OK);
}


feedback Flash::write(const Array<uint16>& data, volatile uint16* address)
{
	//	Check that Address is in valid Flash Range
	extern uint32 __memory_FLASH_start__;
	extern uint32 __memory_FLASH_size__;
	uint32* const flashStartAddress	= (uint32*) &__memory_FLASH_start__;
	const uint32 flashSize					= (uint32)	&__memory_FLASH_size__;
	
	if(((uint32*) address) < flashStartAddress)
	{
		return(FAIL);
	}
	if(((uint32*) address) >= flashStartAddress + flashSize / 4)
	{
		return(FAIL);
	}
	
	
	//	Check that Address is 16-Bit aligned
	if(bit::isSet((uint32) address, 0) == true)
	{
		return(FAIL);
	}
	
	
	//	Check if write Operation crosses Page Boundaries
	uint32 endAddressRelativeToFlashStart = ((uint32) address) - ((uint32) flashStartAddress) + data.get_size() * 2;
	uint32 endPageNumber = endAddressRelativeToFlashStart / c_pageSizeInBytes;
	
	
	//	Read out Flash Page to be erased
	uint32 addressRelativeToFlashStart = ((uint32) address) - ((uint32) flashStartAddress);
	uint32 pageNumber = addressRelativeToFlashStart / c_pageSizeInBytes;
	
	if(endPageNumber != pageNumber)
	{
		return(FAIL);
	}
	
	uint16* pageStartAddress = (uint16*) (flashStartAddress + pageNumber * c_pageSizeInBytes / 4);
	
	Array<uint16> page(0, c_pageSizeInBytes / 2);
	for(uint32 i = 0; i < c_pageSizeInBytes / 2; i++)
	{
		page[i] = pageStartAddress[i];
	}
	
	
	//	Write new Values to Page
	uint32 addressRelativeToPageStart = ((uint32) address) - ((uint32) pageStartAddress);
	uint32 indexInPageStart = addressRelativeToPageStart / 2;
	for(uint32 i = 0; i < data.get_size(); i++)
	{
		page[indexInPageStart + i] = data[i];
	}
	
	
	//	Erase Address before write, else PGERR bit will be set in FLASH_SR and write wont be performed
	if(erase(pageNumber) != OK)
	{
		return(FAIL);
	}
	
	
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	//	Set Programming Bit
	bit::set(*MCU::FLASH::CR, 0);
	
	
	//	Program
	uint16* writeAddress = pageStartAddress;
	for(auto& i: page)
	{
		//	Write 16-Bit Value
		*writeAddress = i;
		
		
		//	Wait until Writing finished
		while(bit::isSet(*MCU::FLASH::SR, 0) == true)
		{
			
		}
		
		
		//	Verify that correct Value has been written
		if(*writeAddress != i)
		{
			//	Clear Programming Bit
			bit::clear(*MCU::FLASH::CR, 0);
			
			
			//	Lock Access to Flash Registers
			lock_FPEC();
			return(FAIL);
		}
		
		
		//	Increment Address
		writeAddress++;
	}
	
	
	//	Clear Programming Bit
	bit::clear(*MCU::FLASH::CR, 0);
	
	
	//	Lock Access to Flash Registers
	return(lock_FPEC());
}


SECTION(bootloader) feedback Flash::writePage(uint32* data, uint32 pageNumber)
{
	if(pageNumber >= c_numberOfPages || data == nullptr)
	{
		return(FAIL);
	}
	constexpr uint32 numberOfWords = c_pageSizeInBytes / 4;
	
	
	//	Flash Start Address
	extern uint32 __memory_FLASH_start__;
	const uint32 flashStart = (uint32) &__memory_FLASH_start__;
	
	
	
	//	Page Start Address
	volatile uint16* address = (volatile uint16*) (flashStart + pageNumber * c_pageSizeInBytes);
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 0) == true)
	{
		
	}
	
	
	//	Erase Address before write, else PGERR bit will be set in FLASH_SR and write wont be performed
	if(erase(pageNumber) != OK)
	{
		return(FAIL);
	}
	
	
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	//	Set Programming Bit
	bit::set(*MCU::FLASH::CR, 0);
	
	
	for(uint32 i = 0; i < numberOfWords; i++)
	{
		//	Calculate Address to write to
		volatile uint16* addressLowerHalf = address + i * 2;
		volatile uint16* addressUpperHalf = address + i * 2 + 1;
		
		
		//	Calculate Lower and Upper Half of 32-Bit Data Word
		const uint32 dataWord = data[i];
		const uint16 lowerHalf = (uint16) (dataWord & 0x0000FFFF);
		const uint16 upperHalf = (uint16) ((dataWord & 0xFFFF0000) >> 16);
		
		
		//	Write Lower Half of 32-Bit Data Word
		*addressLowerHalf = lowerHalf;
		
		
		//	Wait until Writing finished
		while(bit::isSet(*MCU::FLASH::SR, 0) == true)
		{
			
		}
		
		
		//	Verify that correct Value has been written
		if(*addressLowerHalf != lowerHalf)
		{
			//	Clear Programming Bit
			bit::clear(*MCU::FLASH::CR, 0);
			
			
			//	Lock Access to Flash Registers
			lock_FPEC();
			return(FAIL);
		}
		
		
		//	Write Upper Half of 32-Bit Data Word
		*addressUpperHalf = upperHalf;
		
		
		//	Wait until Writing finished
		while(bit::isSet(*MCU::FLASH::SR, 0) == true)
		{
			
		}
		
		
		//	Verify that correct Value has been written
		if(*addressUpperHalf != upperHalf)
		{
			//	Clear Programming Bit
			bit::clear(*MCU::FLASH::CR, 0);
			
			
			//	Lock Access to Flash Registers
			lock_FPEC();
			return(FAIL);
		}
	}
	
	
	//	Clear Programming Bit
	bit::clear(*MCU::FLASH::CR, 0);
	
	
	//	Lock Access to Flash Registers
	return(lock_FPEC());
}


SECTION(bootloader) feedback Flash::erase(uint32 pageNumber)
{
	if(pageNumber >= c_numberOfPages)
	{
		return(FAIL);
	}
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 0) == true)
	{
		
	}
	
	
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	//	Set Page Erase Bit
	bit::set(*MCU::FLASH::CR, 1);
	
	
	//	Set Page Address to be erased
	extern uint32 __memory_FLASH_start__;
	uint32* const flashStartAddress	= (uint32*) &__memory_FLASH_start__;
	
	uint32* pageStart = flashStartAddress + (c_pageSizeInBytes / 4) * pageNumber;
	*MCU::FLASH::AR = (uint32) pageStart;
	
	
	//	Start Erase
	bit::set(*MCU::FLASH::CR, 6);
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 0) == true)
	{
		
	}
	
	
	//	Verify that Flash Page has been erased
	for(uint32 i = 0; i < c_pageSizeInBytes / 4; i++)
	{
		if(pageStart[i] != 0xFFFFFFFF)
		{
			//	Clear Page Erase Bit
			bit::clear(*MCU::FLASH::CR, 1);
			
			
			//	Lock Access to Flash Registers
			lock_FPEC();
			
			
			return(FAIL);
		}
	}
	
	
	//	Clear Page Erase Bit
	bit::clear(*MCU::FLASH::CR, 1);
	
	
	//	Lock Access to Flash Registers
	return(lock_FPEC());
}


SECTION(bootloader) feedback Flash::erase()
{
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 0) == true)
	{
		
	}
	
	
	//	Unlock Access to Flash Registers
	if(unlock_FPEC() != OK)
	{
		return(FAIL);
	}
	
	
	//	Set Mass Erase Bit
	bit::set(*MCU::FLASH::CR, 2);
	
	
	//	Start Erase
	bit::set(*MCU::FLASH::CR, 6);
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 0) == true)
	{
		
	}
	
	
	//	Verify that Flash Page has been erased
	extern uint32 __memory_FLASH_start__;
	extern uint32 __memory_FLASH_size__;
	uint32* const flashStartAddress	= (uint32*) &__memory_FLASH_start__;
	const uint32 flashSize					= (uint32)	&__memory_FLASH_size__;
	
	for(uint32 i = 0; i < flashSize / 4; i++)
	{
		if(flashStartAddress[i] != 0xFFFFFFFF)
		{
			//	Clear Mass Erase Bit
			bit::clear(*MCU::FLASH::CR, 2);
			
			
			//	Lock Access to Flash Registers
			lock_FPEC();
			
			
			return(FAIL);
		}
	}
	
	
	//	Clear Mass Erase Bit
	bit::clear(*MCU::FLASH::CR, 2);
	
	
	//	Lock Access to Flash Registers
	return(lock_FPEC());
}