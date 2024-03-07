#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class Flash
{
	public:
		
		
		
		
		
	private:
		
		uint8 m_waitStates;
		
		constexpr inline Flash();
		Flash(const Flash& flash) = delete;
		inline ~Flash();
		
		inline feedback startup();
		
		friend class STM32F030F4P6;
		
		
		
		
		
	public:
		
		feedback set_waitStates(uint32 clock_ahb);
		feedback set_prefetchBuffer(bool active);
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

