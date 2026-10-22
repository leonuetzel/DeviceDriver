#pragma once

#include "i_flash.hpp"





class Flash: public I_Flash
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint32 c_pageSizeInBytes	= 128 * 1024;
		static constexpr uint32 c_numberOfPages		= 16;
		static constexpr uint32 c_size						= c_pageSizeInBytes * c_numberOfPages;
		static constexpr uint32 c_numberOfSectorsPerBank	= 8;
		static constexpr uint32 c_flashStartAddress			= 0x08000000;
		//	Error Flags of FLASH_SR1/2: WRPERR, PGSERR, STRBERR, INCERR, OPERR - the same Bits in FLASH_CCR1/2 clear them
		static constexpr uint32 c_errorFlags							= (1 << 17) | (1 << 18) | (1 << 19) | (1 << 21) | (1 << 22);
		
		
		//	Non-static Member
		uint8 m_waitStates;
		uint8 m_programmingDelay;
		
		
		//	Constructor and Destructor
		constexpr inline Flash();
		Flash(const Flash& flash) = delete;
		inline ~Flash();
		
		
		//	Member Functions
		feedback startup();
		static void get_registers(uint32 bank, volatile uint32*& KEYR, volatile uint32*& CR, volatile uint32*& SR, volatile uint32*& CCR);
		static feedback unlock(uint32 bank);
		static feedback wait(uint32 bank);
		static void invalidateCaches(const void* address, uint32 sizeInBytes);
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		virtual feedback writePage(uint32* data, uint32 pageNumber) override;
		virtual feedback erase(uint32 pageNumber) override;
		virtual feedback erase() override;
		feedback write(const uint32* flashWord, uint32 address);
		feedback swapBanks();
		
		virtual uint32 get_pageSize() const override;
		virtual uint32 get_numberOfPages() const override;
		virtual uint32 get_size() const override;
		virtual uint32 get_smallestProgrammableBlockSize() const override;
		
		feedback set_waitStates(uint32 clock_ahb, PWR::e_voltageLevel voltageLevel);
		void enable_ECC();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Flash::Flash()
	:	m_waitStates(7),
		m_programmingDelay(3)
{
	
}


inline Flash::~Flash()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

