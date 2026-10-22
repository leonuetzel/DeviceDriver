#include "../Inc/stm32l010k8t6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback Flash::set_waitStates(uint32 clock_ahb)
{
	PWR::e_voltageRange voltageRange = STM32L010K8T6::get().get_pwr().get_voltageRange();
	
	//	Maximum Frequency without Wait State: 16 MHz in Range 1, 8 MHz in Range 2, 4.2 MHz in Range 3 (RM0451, Table 10)
	//	Above 16 MHz there is always a Wait State, independent of the Range
	uint32 waitStates = 0;
	if(clock_ahb > 16000000)
	{
		waitStates = 1;
	}
	else if(voltageRange == PWR::e_voltageRange::R2_1V5 && clock_ahb > 8000000)
	{
		waitStates = 1;
	}
	else if(voltageRange == PWR::e_voltageRange::R3_1V2 && clock_ahb > 4200000)
	{
		waitStates = 1;
	}
	
	if(waitStates == 1)
	{
		bit::set(*MCU::FLASH::ACR, 0);
	}
	else
	{
		bit::clear(*MCU::FLASH::ACR, 0);
	}
	
	m_waitStates = waitStates;
	return(OK);
}


feedback Flash::write_eeprom(uint8 data, volatile uint8* address)
{
	//	Get 32-Bit aligned Address
	const uint32* baseAddress = (uint32*) (((uint32) address) & 0xFFFFFFFC);
	
	
	//	Get Byte Index
	const uint32 byteIndex = ((uint32) address) - ((uint32) baseAddress);
	
	
	//	Read out old Data
	const uint32 data_old = *baseAddress;
	
	
	//	Modify Data
	union array
	{
		uint32 word;
		uint8 byte[4];
	};
	
	array data_new;
	data_new.word = data_old;
	data_new.byte[byteIndex] = data;
	
	
	//	Write to EEPROM
	return(write_eeprom(data_new.word, (volatile uint32*) baseAddress));
}


feedback Flash::write_eeprom(uint16 data, volatile uint16* address)
{
	//	Check for Alignment
	if(bit::isSet((uint32) address, 0) == true)
	{
		return(FAIL);
	}
	
	
	//	Get 32-Bit aligned Address
	const uint32* baseAddress = (uint32*) (((uint32) address) & 0xFFFFFFFC);
	
	
	//	Get Byte Index
	const uint32 halfWordIndex = (((uint32) address) - ((uint32) baseAddress)) / 2;
	
	
	//	Read out old Data
	const uint32 data_old = *baseAddress;
	
	
	//	Modify Data
	union array
	{
		uint32 word;
		uint16 halfword[2];
	};
	
	array data_new;
	data_new.word = data_old;
	data_new.halfword[halfWordIndex] = data;
	
	
	//	Write to EEPROM
	return(write_eeprom(data_new.word, (volatile uint32*) baseAddress));
}


feedback Flash::write_eeprom(uint32 data, volatile uint32* address)
{
	//	Check that Address is in valid EEPROM Range
	extern uint32 __memory_EEPROM_start__;
	extern uint32 __memory_EEPROM_size__;
	uint32* const eepromStartAddress	= (uint32*) &__memory_EEPROM_start__;
	const uint32 eepromSize						= (uint32)	&__memory_EEPROM_size__;
	
	if(((uint32*) address) < eepromStartAddress)
	{
		return(FAIL);
	}
	if(((uint32*) address) >= eepromStartAddress + eepromSize / 4)
	{
		return(FAIL);
	}
	
	
	//	Check that Address is 32-Bit aligned
	if(bit::isSet((uint32) address, 0) == true || bit::isSet((uint32) address, 1) == true)
	{
		return(FAIL);
	}
	
	
	//	Unlock PECR
	if(unlock_PECR() != OK)
	{
		return(FAIL);
	}
	
	
	//	Unselect Flash Memory
	bit::clear(*MCU::FLASH::PECR, 3);
	
	
	//	Select Data EEPROM
	bit::set(*MCU::FLASH::PECR, 4);
	
	
	//	Erase EEPROM before write Operation only if it isnt 0
	bit::clear(*MCU::FLASH::PECR, 8);
	
	
	//	No Erase Operation requested
	bit::clear(*MCU::FLASH::PECR, 9);
	
	
	//	Disable Half Page Programming
	bit::clear(*MCU::FLASH::PECR, 10);
	
	
	//	Reset EOP (End of Programming) and the Error Flags of an earlier Operation, all are cleared by writing 1 (RM0451, FLASH_SR)
	*MCU::FLASH::SR = 0x00032F02;
	
	
	//	Write Data
	*address = data;
	
	
	//	Wait for Programming to finish: EOP is set at the End, an Error stops the Operation without EOP
	//	A Word takes some Milliseconds with Erase, the Timeout is far above
	uint32 timeout = 1000000;
	while(bit::isCleared(*MCU::FLASH::SR, 1) == true && (*MCU::FLASH::SR & 0x00032F00) == 0 && timeout > 0)
	{
		timeout--;
	}
	const bool programmingFailed = (bit::isCleared(*MCU::FLASH::SR, 1) == true);
	
	
	//	Lock PECR Register
	if(lock_PECR() != OK || programmingFailed == true)
	{
		return(FAIL);
	}
	
	
	//	Check for correct Programming
	if(*address != data)
	{
		return(FAIL);
	}
	return(OK);
}