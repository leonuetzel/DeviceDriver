#include "../Inc/stm32f103c8t6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

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


feedback Flash::erase(uint32 pageNumber)
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


feedback Flash::erase()
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