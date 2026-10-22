#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

namespace
{
	void refreshWatchdog()
	{
		//	Erasing a Sector takes up to some Seconds: a running Watchdog (e.g. the one of the Trial) is refreshed
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

constexpr inline uint32 Update::descriptorOffset()
{
	//	Exception Vectors of CMOS (16 Words), then the Interrupt Vectors of the H753
	return(16 * 4 + sizeof(STM32H753BIT6::c_interruptTable));
}


void Update::countStart()
{
	//	Called by STM32H753BIT6::startup(). An Image on Trial counts its Starts in RTC_BKP31R: the Counter survives every Reset, also one of
	//	the Watchdog (without VBAT not a Power Cycle - then it starts at 0 again, the Image stays on Trial). After c_maxUnconfirmedStarts
	//	Starts the Banks are swapped back to the previous Image. Every Start on Trial runs with the IWDG at its longest Timeout (Prescaler
	//	256, Reload 0xFFF): an Image that hangs restarts and is counted. The Image confirms itself or refreshes the IWDG within it
	if(PWR::isRevisionY() == true || isTrial() == false)
	{
		return;
	}
	const uint32 value = readState();
	const uint32 starts = ((value >> 16) == c_stateMagic && ((value >> 8) & 0xFF) == c_stateTrial) ? (value & 0xF) : 0;
	if(starts >= c_maxUnconfirmedStarts)
	{
		writeState(c_stateReverted, 0);
		STM32H753BIT6::get().get_flash().swapBanks();
		return;
	}
	writeState(c_stateTrial, starts + 1);
	*MCU::IWDG::KR = 0xCCCC;
	*MCU::IWDG::KR = 0x5555;
	*MCU::IWDG::PR = 6;
	*MCU::IWDG::RLR = 0xFFF;
	for(uint32 i = 0; i < 100000 && (*MCU::IWDG::SR & 0x7) != 0; i++)
	{
		
	}
	*MCU::IWDG::KR = 0xAAAA;
}


bool Update::isProgrammed(uint32 address)
{
	//	A Power Failure while a Flash Word is programmed leaves a double ECC Error, and reading it causes a Bus Error (RM0433, Error correction
	//	code error). With FAULTMASK and BFHFNMIGN (CCR Bit 8) the Core ignores Data Bus Faults (ARMv7-M, Configuration and Control Register):
	//	the Read delivers some Value, DBECCERR (FLASH_SR Bit 26) shows the Error. A half programmed Flash Word counts as programmed
	//	Approved Exception to "no Interrupt Lock": BFHFNMIGN works only at Priority -1 (FAULTMASK), the Lock lasts some Flash Reads (< 0.5 µs)
	volatile uint32* const CCR = (volatile uint32*) 0xE000ED14;
	volatile uint32* const CFSR = (volatile uint32*) 0xE000ED28;
	volatile uint32* const SR = (address >= c_bank2Address) ? MCU::FLASH_2::SR : MCU::FLASH_1::SR;
	volatile uint32* const clear = (address >= c_bank2Address) ? MCU::FLASH_2::CCR : MCU::FLASH_1::CCR;
	const volatile uint32* const word = (const volatile uint32*) address;
	uint32 value = 0xFFFFFFFF;
	asm volatile("cpsid f" ::: "memory");
	*CCR = *CCR | (1u << 8);
	asm volatile("dsb\n\tisb" ::: "memory");
	for(uint32 i = 0; i < 8; i++)
	{
		value &= word[i];
	}
	asm volatile("dsb" ::: "memory");
	*CCR = *CCR & ~(1u << 8);
	asm volatile("isb" ::: "memory");
	asm volatile("cpsie f" ::: "memory");
	const bool error = bit::isSet(*SR, 26);
	if(error == true)
	{
		//	CLR_DBECCERR, and the BusFault Status the ignored Fault has set
		*clear = (1u << 26);
		*CFSR = 0x0000FF00;
	}
	return(error == true || value != 0xFFFFFFFF);
}


bool Update::isTrial()
{
	//	The running Image carries T and C, T is programmed (installed by an Update) and C is not (not confirmed yet)
	const uint32 descriptor = c_bank1Address + descriptorOffset();
	return(*((const volatile uint32*) (descriptor + c_flagTagOffset)) == c_flagTag && isProgrammed(descriptor + c_flagTrialOffset) == true &&
	       isProgrammed(descriptor + c_flagConfirmedOffset) == false);
}


uint32 Update::readState()
{
	//	RTC_BKP31R needs the Clock of the RTC Interface (RTCAPBEN)
	STM32H753BIT6::get().get_rcc().module_clockInit(RCC::e_module::RTC, true);
	return(*MCU::RTC::BKP31);
}


void Update::writeState(uint32 state, uint32 starts)
{
	//	The Backup Domain is write protected (DBP in PWR_CR1): lifted for the Access and restored afterwards
	STM32H753BIT6::get().get_rcc().module_clockInit(RCC::e_module::RTC, true);
	const bool writeProtected = bit::isCleared(*MCU::PWR::CR1, 8);
	bit::set(*MCU::PWR::CR1, 8);
	while(bit::isCleared(*MCU::PWR::CR1, 8))
	{
		
	}
	*MCU::RTC::BKP31 = (state == 0) ? 0 : ((c_stateMagic << 16) | (state << 8) | starts);
	if(writeProtected == true)
	{
		bit::clear(*MCU::PWR::CR1, 8);
	}
}


feedback Update::prepareDownload()
{
	//	On Trial the other Bank holds the previous Image for the Rollback: no new Download. An unfinished Cleanup is finished first
	if(isTrial() == true)
	{
		return(FAIL);
	}
	const uint32 value = readState();
	if((value >> 16) == c_stateMagic && ((value >> 8) & 0xFF) == c_stateConfirming)
	{
		return(eraseOtherBank());
	}
	return(OK);
}


feedback Update::eraseOtherBank()
{
	//	The previous Image: every Sector of the other Bank that is not erased (checked with the protected Read, a Sector may hold a half
	//	programmed Flash Word). The CPU keeps running, it executes from this Bank. The State "confirming" lets the next confirm() finish it
	writeState(c_stateConfirming, 0);
	Flash& flash = STM32H753BIT6::get().get_flash();
	for(uint32 sector = 0; sector < c_bankSize / c_sectorSize; sector++)
	{
		const uint32 address = c_bank2Address + sector * c_sectorSize;
		bool programmed = false;
		for(uint32 offset = 0; offset < c_sectorSize && programmed == false; offset += 32)
		{
			programmed = isProgrammed(address + offset);
		}
		if(programmed == true && flash.erase(8 + sector) != OK)
		{
			return(FAIL);
		}
		refreshWatchdog();
	}
	writeState(0, 0);
	return(OK);
}





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

uint32 Update::get_capacity() const
{
	//	One Bank of 8 Sectors - not on Revision Y and W (REV_ID 0x1003): there the Bank Swapping can make the Flash Interface unpredictable
	//	(Errata Sheet ES0392, Flash memory bank swapping), so every Update is refused
	if(PWR::isRevisionY() == true)
	{
		return(0);
	}
	return(c_bankSize);
}


uint32 Update::get_imageAddress() const
{
	//	The Image runs in the Bank that the Swap maps to 0x08000000
	return(c_bank1Address);
}


const uint8* Update::get_download() const
{
	//	The Bank that does not run: always mapped at 0x08100000
	return((const uint8*) c_bank2Address);
}


uint32 Update::get_deviceID() const
{
	return(c_deviceID);
}


uint32 Update::get_descriptorOffset() const
{
	//	T and C have to be Flash Words of their own (32 Bytes, aligned)
	static_assert((descriptorOffset() + c_flagTrialOffset) % 32 == 0 && (descriptorOffset() + c_flagConfirmedOffset) % 32 == 0,
	              "T and C are not aligned to Flash Words");
	return(descriptorOffset());
}


feedback Update::write(uint32 offset, const uint8* data, uint32 size)
{
	if(data == nullptr || offset % c_writeSize != 0 || size % 32 != 0 || offset + size > get_capacity() ||
	   (offset == 0 && prepareDownload() != OK))
	{
		return(FAIL);
	}
	
	
	//	In Flash Words of 32 Byte; the first Piece of a Sector (128 KByte) erases the Sector of the other Bank (Pages 8 … 15)
	Flash& flash = STM32H753BIT6::get().get_flash();
	for(uint32 i = 0; i < size; i += 32)
	{
		const uint32 position = offset + i;
		if(position % c_sectorSize == 0 && flash.erase(8 + position / c_sectorSize) != OK)
		{
			return(FAIL);
		}
		uint32 flashWord[8];
		for(uint32 j = 0; j < 8; j++)
		{
			const uint8* const bytes = data + i + 4 * j;
			flashWord[j] = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | ((uint32) bytes[3] << 24);
		}
		
		
		//	Flash Words of only 0xFF stay erased: T and C of the Image Descriptor must stay programmable
		bool erased = true;
		for(uint32 j = 0; j < 8; j++)
		{
			erased = erased == true && flashWord[j] == 0xFFFFFFFF;
		}
		if(erased == false && flash.write(flashWord, c_bank2Address + position) != OK)
		{
			return(FAIL);
		}
	}
	return(OK);
}


feedback Update::commit(uint32 size, uint32 crc32)
{
	//	The Updater has checked the Image: T marks it as installed by an Update (on Trial), the Banks are swapped, the Reset starts it
	//	(returns only on Failure). An Image without T and C (Tag) is refused: it could not be confirmed
	(void) crc32;
	const uint32 descriptor = c_bank2Address + descriptorOffset();
	if(size == 0 || size > get_capacity() || size < descriptorOffset() + c_flagTagOffset + 4 || prepareDownload() != OK ||
	   *((const volatile uint32*) (descriptor + c_flagTagOffset)) != c_flagTag)
	{
		return(FAIL);
	}
	const uint32 flashWord[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	Flash& flash = STM32H753BIT6::get().get_flash();
	if(isProgrammed(descriptor + c_flagTrialOffset) == true || flash.write(flashWord, descriptor + c_flagTrialOffset) != OK)
	{
		return(FAIL);
	}
	writeState(c_stateTrial, 0);
	return(flash.swapBanks());
}


feedback Update::confirm()
{
	if(isTrial() == false)
	{
		//	An interrupted Cleanup of an earlier confirm() is finished
		const uint32 value = readState();
		if((value >> 16) == c_stateMagic && ((value >> 8) & 0xFF) == c_stateConfirming)
		{
			return(eraseOtherBank());
		}
		return(OK);
	}
	
	
	//	C in the running Bank ends the Trial: from here on there is no Rollback. The Watchdog of the Trial runs until the next Reset: CMOS
	//	refreshes it from now on, unless the Application has started it itself. Then the previous Image in the other Bank is erased
	const uint32 flashWord[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	if(STM32H753BIT6::get().get_flash().write(flashWord, c_bank1Address + descriptorOffset() + c_flagConfirmedOffset) != OK)
	{
		return(FAIL);
	}
	STM32H753BIT6::get().get_watchdog().handOver();
	return(eraseOtherBank());
}


I_UpdateMemory::e_imageState Update::get_imageState() const
{
	if(isTrial() == true)
	{
		return(e_imageState::UNCONFIRMED);
	}
	
	
	//	After the Rollback until the next commit() - without VBAT until the next Power Cycle
	const uint32 value = readState();
	if((value >> 16) == c_stateMagic && ((value >> 8) & 0xFF) == c_stateReverted)
	{
		return(e_imageState::REVERTED);
	}
	return(e_imageState::CONFIRMED);
}


uint32 Update::get_startsLeft() const
{
	if(isTrial() == false)
	{
		return(0);
	}
	const uint32 value = readState();
	const uint32 starts = ((value >> 16) == c_stateMagic && ((value >> 8) & 0xFF) == c_stateTrial) ? (value & 0xF) : 0;
	if(starts >= c_maxUnconfirmedStarts)
	{
		return(0);
	}
	return(c_maxUnconfirmedStarts - starts);
}
