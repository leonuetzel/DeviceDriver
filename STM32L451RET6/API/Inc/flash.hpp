#pragma once

#include "registers.hpp"
#include "pwr.hpp"





class Flash
{
	public:
		
		static constexpr uint32 c_pageSizeInBytes	= 2048;
		static constexpr uint32 c_numberOfPages		= 256;
		
		
		
		
		
	private:
		
		//	Static Member
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
		inline feedback startup();
		feedback lock_FPEC();
		feedback unlock_FPEC();
		feedback write2Words(uint32 dataAtAddress, uint32 dataAtAddressPlus4Byte, volatile uint64* address);
		
		
		//	Friends
		friend class STM32L451RET6;
		
		
		
		
		
	public:
		
		feedback set_waitStates(uint32 clock_ahb, PWR::e_voltageScaling voltageScaling);
		
		feedback write(uint32 dataAtAddress, uint32 dataAtAddressPlus4Byte, volatile uint64* address);
		feedback write(const Array<uint32>& data, volatile uint64* address);
		feedback writePage(uint32* data, uint32 pageNumber);
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



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

