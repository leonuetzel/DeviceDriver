#pragma once

#include "cmos.hpp"





class Flash
{
	public:
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		uint8 m_waitStates;
		uint8 m_programmingDelay;
		
		
		//	Constructor and Destructor
		constexpr inline Flash();
		Flash(const Flash& flash) = delete;
		inline ~Flash();
		
		
		//	Member Functions
		feedback startup();
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
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

