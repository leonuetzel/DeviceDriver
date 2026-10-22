#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "i_flash.hpp"





class Flash: public I_Flash
{
	public:
		
		static constexpr uint32 c_pageSizeInBytes	= 2048;
		static constexpr uint32 c_numberOfPages		= 16;
	
	
	
	
	
	private:
		
		//	Static Member
		static constexpr uint32 c_key1			= 0x45670123;
		static constexpr uint32 c_key2			= 0xCDEF89AB;
		
		static constexpr uint32 c_size									= c_pageSizeInBytes * c_numberOfPages;
		static constexpr uint32 c_flashStartAddress			= 0x08000000;
		
		//	Flags of FLASH_SR cleared before each Operation: EOP, OPERR, PROGERR, WRPERR, PGAERR, SIZERR, PGSERR, MISSERR, FASTERR, RDERR, OPTVERR
		static constexpr uint32 c_clearFlags						= 0x0000C3FB;
		//	Errors of a Programming or Erase Operation: OPERR, PROGERR, WRPERR, PGAERR, SIZERR, PGSERR, MISSERR, FASTERR
		static constexpr uint32 c_errorFlags						= 0x000003FA;
		
		
		//	Non-static Member
		uint8 m_waitStates;
		
		
		//	Constructor and Destructor
		constexpr inline Flash();
		Flash(const Flash& flash) = delete;
		inline ~Flash();
		
		
		//	Member Functions
		inline feedback startup();
		feedback lock_FPEC();
		feedback unlock_FPEC();
		feedback wait();
		void flushCache();
		feedback write2Words(uint32 dataAtAddress, uint32 dataAtAddressPlus4Byte, volatile uint64* address);
		
		
		//	Friends
		friend class STM32C031K6U6;
	
	
	
	
	
	public:
		
		virtual feedback writePage(uint32* data, uint32 pageNumber) override;
		virtual feedback erase(uint32 pageNumber) override;
		virtual feedback erase() override;
		
		virtual uint32 get_pageSize() const override;
		virtual uint32 get_numberOfPages() const override;
		virtual uint32 get_size() const override;
		virtual uint32 get_smallestProgrammableBlockSize() const override;
		
		inline feedback set_waitStates(uint32 clock_ahb);
		inline feedback set_prefetchBuffer(bool active);
		
		feedback write(uint32 dataAtAddress, uint32 dataAtAddressPlus4Byte, volatile uint64* address);
		feedback write(const Array<uint32>& data, volatile uint64* address);
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
	
	
	//	Wait for new Wait States to become effective: LATENCY (Bits 2:0) reads back the new Value
	while((*MCU::FLASH::ACR & 0x00000007) != mask)
	{
		
	}
	return(OK);
}


inline feedback Flash::set_prefetchBuffer(bool active)
{
	if(active == true)
	{
		bit::set(*MCU::FLASH::ACR, 8);
	}
	else
	{
		bit::clear(*MCU::FLASH::ACR, 8);
	}
	
	return(OK);
}
