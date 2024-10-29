#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class Flash
{
	public:
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint32 c_pe_key1			= 0x89ABCDEF;
		static constexpr uint32 c_pe_key2			= 0x02030405;
		static constexpr uint32 c_prg_key1		= 0x8C9DAEBF;
		static constexpr uint32 c_prg_key2		= 0x13141516;
		
		
		
		//	Non-static Member
		uint8 m_waitStates;
		
		
		//	Constructor and Destructor
		constexpr inline Flash();
		Flash(const Flash& flash) = delete;
		inline ~Flash();
		
		
		//	Member Functions
		inline feedback startup();
		inline feedback lock_PECR();
		inline feedback unlock_PECR();
		
		
		//	Friends
		friend class STM32L010K8T6;
		
		
		
		
		
	public:
		
		feedback set_waitStates(uint32 clock_ahb);
		feedback write_eeprom(uint8 data, volatile uint8* address);
		feedback write_eeprom(uint16 data, volatile uint16* address);
		feedback write_eeprom(uint32 data, volatile uint32* address);
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


inline feedback Flash::lock_PECR()
{
	//	Check if its unlocked
	if(bit::isCleared(*MCU::FLASH::PECR, 0) == true)
	{
		//	Lock PECR Register by setting PELOCK Bit in FLASH_PECR
		bit::set(*MCU::FLASH::PECR, 0);
	}
	return(OK);
}


inline feedback Flash::unlock_PECR()
{
	//	Wait until no Operation is ongoing
	while(bit::isSet(*MCU::FLASH::SR, 0) == true)
	{
		
	}
	
	
	//	Check if its already unlocked
	if(bit::isCleared(*MCU::FLASH::PECR, 0) == true)
	{
		return(OK);
	}
	
	
	//	Unlock PECR Register by writing two Key Values to FLASH_PEKEYR
	*MCU::FLASH::PE_KEY = c_pe_key1;
	*MCU::FLASH::PE_KEY = c_pe_key2;
	
	
	//	Check if unlock was successful
	if(bit::isCleared(*MCU::FLASH::PECR, 0) == true)
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

