#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"





class SYSCFG
{
	public:
		
		
		
		
		
		
		
	private:
		
		constexpr inline SYSCFG();
		SYSCFG(const SYSCFG& syscfg) = delete;
		inline ~SYSCFG();
		
		inline feedback startup(RCC& rcc);
		
		
		friend class STM32F030F4P6;
		
		
		
		
		
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

