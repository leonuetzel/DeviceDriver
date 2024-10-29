#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class Flash
{
	public:
		
		static constexpr uint32 c_pageSizeInBytes	= 2048;
		static constexpr uint32 c_numberOfPages		= 16;
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint32 c_key1			= 0x45670123;
		static constexpr uint32 c_key2			= 0xCDEF89AB;
		static constexpr uint32 c_optKey1		= 0x08192A3B;
		static constexpr uint32 c_optKey2		= 0x4C5D6E7F;
		
		
		//	Non-static Member
		uint8 m_waitStates;
		
		
		//	Constructor and Destructor
		constexpr inline Flash();
		Flash(const Flash& flash) = delete;
		inline ~Flash();
		
		
		//	Member Functions
		inline feedback startup();
		inline feedback lock_FPEC();
		inline feedback unlock_FPEC();
		
		
		//	Friends
		friend class STM32C031K6U6;
		
		
		
		
		
	public:
		
		inline feedback set_waitStates(uint32 clock_ahb);
		inline feedback set_prefetchBuffer(bool active);
		feedback write(const Array<uint16>& data, volatile uint16* address);
		feedback erase(uint32 pageNumber);
		feedback erase();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Flash::Flash()
	:	m_waitStates(0)
{
	
}


inline Flash::~Flash()
{
	
}







inline feedback Flash::startup()
{
	return(OK);
}


inline feedback Flash::lock_FPEC()
{
	//	Check if its unlocked
	if(bit::isCleared(*MCU::FLASH::CR, 31) == true)
	{
		//	Lock FPEC (Flash Programming/Erasing Controller) by setting LOCK Bit in FLASH_CR
		bit::set(*MCU::FLASH::CR, 31);
	}
	return(OK);
}


inline feedback Flash::unlock_FPEC()
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



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline feedback Flash::set_waitStates(uint32 clock_ahb)
{
	//	Determine Mask to write
	uint32 mask = 0x0;
	if(clock_ahb <= 24000000)
	{
		mask = 0x0;
		m_waitStates = 0;
	}
	else
	{
		mask = 0x1;
		m_waitStates = 1;
	}
	
	
	//	Write new Values
	uint32 temp = *MCU::FLASH::ACR & 0xFFFFFFF8;
	*MCU::FLASH::ACR = temp | mask;
	
	
	//	Wait for new Wait States to become effective
	while((*MCU::FLASH::ACR & 0xFFFFFFF8) != mask)
	{
		
	}
	return(OK);
}


inline feedback Flash::set_prefetchBuffer(bool active)
{
	if(active == true && bit::isCleared(*MCU::FLASH::ACR, 8))
	{
		bit::set(*MCU::FLASH::ACR, 8);
	}
	else
	{
		bit::clear(*MCU::FLASH::ACR, 8);
	}
	
	return(OK);
}