#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"





class PWR
{
	public:
		
		
		
		
		
		
		
	private:
		
		constexpr inline PWR();
		PWR(const PWR& pwr) = delete;
		inline ~PWR();
		
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

constexpr inline PWR::PWR()
{
	
}


inline PWR::~PWR()
{
	
}







inline feedback PWR::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::PWR, true);
	
	
	//	Disable Write Protection of Backup Domain
	bit::set(*MCU::PWR::CR, 8);
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

