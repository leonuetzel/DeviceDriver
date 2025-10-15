#include "../Inc/stm32l451ret6.hpp"





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
	
	
	//	Wait a short time to ensure that the unlock is processed
	for(uint32 i = 0; i < 100; i++)
	{
		asm volatile("nop");
	}
	
	
	//	Check if unlock was successful
	if(bit::isCleared(*MCU::FLASH::CR, 31) == true)
	{
		return(OK);
	}
	return(FAIL);
}







SECTION(bootloader) feedback Flash::write2Words(uint32 dataAtAddress, uint32 dataAtAddressPlus4Byte, volatile uint64* address)
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
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
	{
		
	}
	
	
	//	Enable End of Operation Interrupt
	//	This is necessary for EOP Bit to be set after a Programming Operation (we dont use the Interrupt)
	bit::set(*MCU::FLASH::CR, 24);
	
	
	//	Set Programming Bit
	bit::set(*MCU::FLASH::CR, 0);
	
	
	//	Program
	const uint32 addressInt = (uint32) address;
	uint32* const addressPlus0 = (uint32*) (addressInt + 0);
	uint32* const addressPlus4 = (uint32*) (addressInt + 4);
	
	*addressPlus0 = dataAtAddress;
	*addressPlus4 = dataAtAddressPlus4Byte;
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
	{
		
	}
	
	
	//	Check that Programming Operation succeeded by reading EOP Bit in SR
	if(bit::isSet(*MCU::FLASH::SR, 0) == false)
	{
		//	Clear Programming Bit
		bit::clear(*MCU::FLASH::CR, 0);
		return(FAIL);
	}
	
	
	//	Reset EOP Bit
	bit::set(*MCU::FLASH::SR, 0);
	
	
	//	Clear Programming Bit
	bit::clear(*MCU::FLASH::CR, 0);
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback Flash::set_waitStates(uint32 clock_ahb, PWR::e_voltageScaling voltageScaling)
{
	typedef struct
	{
		uint32 frequency[5];
	}s_array;
	
	const Pair<PWR::e_voltageScaling, s_array> waitStateMaxFrequencies[2] =
	{
		{PWR::e_voltageScaling::RANGE1_1V2, {16000000, 32000000, 48000000, 64000000, 80000000}},
		{PWR::e_voltageScaling::RANGE2_1V0, { 6000000, 12000000, 18000000, 26000000, 26000000}}
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
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
	{
		
	}
	
	
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
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
	{
		
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


SECTION(bootloader) feedback Flash::writePage(uint32* data, uint32 pageNumber)
{
	if(pageNumber >= c_numberOfPages || data == nullptr)
	{
		return(FAIL);
	}
	constexpr uint32 numberOfWords = c_pageSizeInBytes / 4;
	
	
	//	Flash Start Address
	extern uint32 __memory_FLASH_start__;
	const uint32 flashStart	= (uint32) &__memory_FLASH_start__;
	
	
	//	Page Start Address
	volatile uint64* address = (volatile uint64*) (flashStart + pageNumber * c_pageSizeInBytes);
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
	{
		
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
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
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
	
	const uint32 temp = *MCU::FLASH::CR & 0xFFFFF807;
	*MCU::FLASH::CR = temp | (pageNumber << 3);
	
	
	//	Start Erase
	bit::set(*MCU::FLASH::CR, 16);
	
	
	//	Wait for Busy-Flag to be reset
	while(bit::isSet(*MCU::FLASH::SR, 16) == true)
	{
		
	}
	
	
	//	Verify that Flash Page has been erased
	uint32* pageStart = flashStartAddress + (c_pageSizeInBytes / 4) * pageNumber;
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