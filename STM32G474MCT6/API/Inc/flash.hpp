#pragma once

#include "registers.hpp"
#include "pwr.hpp"
#include "i_flash.hpp"





class Flash: public I_Flash
{
	public:
		
		//	Page Size and Number of Pages in Dual Bank Mode (Option Bit DBANK = 1, the Factory Default)
		//	get_pageSize() and get_numberOfPages() return the Values of the current Mode (Single Bank: 64 Pages of 4 KByte)
		static constexpr uint32 c_pageSizeInBytes	= 2048;
		static constexpr uint32 c_numberOfPages		= 128;
	
	
	
	
	
	private:
		
		//	Static Member
		static constexpr uint32 c_key1			= 0x45670123;
		static constexpr uint32 c_key2			= 0xCDEF89AB;
		
		static constexpr uint32 c_size									= 262144;
		static constexpr uint32 c_flashStartAddress			= 0x08000000;
		static constexpr uint32 c_bank2StartAddress			= 0x08040000;
		static constexpr uint32 c_pagesPerBank					= c_size / 2 / c_pageSizeInBytes;
		
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
		static bool isDualBank();
		static uint32 get_pageAddress(uint32 pageNumber);
		static bool isInFlash(uint32 address);
		feedback wait();
		uint32 disableDataCache();
		void flushCaches(uint32 enabled);
		feedback write2Words(uint32 dataAtAddress, uint32 dataAtAddressPlus4Byte, volatile uint64* address);
		
		
		//	Friends
		friend class STM32G474MCT6;
	
	
	
	
	
	public:
		
		virtual feedback writePage(uint32* data, uint32 pageNumber) override;
		virtual feedback erase(uint32 pageNumber) override;
		virtual feedback erase() override;
		
		virtual uint32 get_pageSize() const override;
		virtual uint32 get_numberOfPages() const override;
		virtual uint32 get_size() const override;
		virtual uint32 get_smallestProgrammableBlockSize() const override;
		
		feedback set_waitStates(uint32 clock_ahb, PWR::e_voltageScaling voltageScaling);
		
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

