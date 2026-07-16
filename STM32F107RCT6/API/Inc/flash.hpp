#pragma once

#include "i_flash.hpp"





class Flash: public I_Flash
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint32 c_pageSizeInBytes	= 2 * 1024;
		static constexpr uint32 c_numberOfPages		= 128;
		static constexpr uint32 c_size						= c_pageSizeInBytes * c_numberOfPages;
		
		static constexpr uint16 c_key_RDPRT	= 0x00A5;
		static constexpr uint32 c_key1			= 0x45670123;
		static constexpr uint32 c_key2			= 0xCDEF89AB;
		
		
		//	Non-static Member
		uint8 m_waitStates;
		
		
		//	Constructor and Destructor
		constexpr inline Flash();
		Flash(const Flash& flash) = delete;
		inline ~Flash();
		
		
		//	Member Functions
		constexpr inline feedback startup();
		feedback lock_FPEC();
		feedback unlock_FPEC();
		
		
		//	Friends
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		virtual feedback writePage(uint32* data, uint32 pageNumber) override;
		virtual feedback erase(uint32 pageNumber) override;
		virtual feedback erase() override;
		
		virtual uint32 get_pageSize() const override;
		virtual uint32 get_numberOfPages() const override;
		virtual uint32 get_size() const override;
		virtual uint32 get_smallestProgrammableBlockSize() const override;
		
		feedback set_waitStates(uint32 clock_ahb);
		feedback set_prefetchBuffer(bool active);
		feedback write(const Array<uint16>& data, volatile uint16* address);
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







constexpr inline feedback Flash::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

