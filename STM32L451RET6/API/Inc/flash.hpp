#pragma once

#include "pwr.hpp"
#include "i_flash.hpp"





class Flash: public I_Flash
{
	public:
		
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint32 c_pageSizeInBytes	= 2048;
		static constexpr uint32 c_numberOfPages		= 256;
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
		feedback write2Words(uint32 dataAtAddress, uint32 dataAtAddressPlus4Byte, volatile uint64* address);
		
		
		//	Friends
		friend class STM32L451RET6;
		
		
		
		
		
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

