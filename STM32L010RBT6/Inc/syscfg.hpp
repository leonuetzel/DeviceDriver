#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"





class SYSCFG
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline SYSCFG();
		SYSCFG(const SYSCFG& syscfg) = delete;
		inline ~SYSCFG();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32L010RBT6;
		
		
		
		
		
	public:
		
		
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline SYSCFG::SYSCFG()
{
	
}


inline SYSCFG::~SYSCFG()
{
	
}







inline feedback SYSCFG::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::SYSCFG, true);
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

