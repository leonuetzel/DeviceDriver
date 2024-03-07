#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class Pwr
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline Pwr();
		Pwr(const Pwr& pwr) = delete;
		inline ~Pwr();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32F103C8T6;
		
		
		
		
		
	public:
		
		inline feedback set_backupDomain_writeProtection(bool enable);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Pwr::Pwr()
{
	
}


inline Pwr::~Pwr()
{
	
}







inline feedback Pwr::startup(RCC& rcc)
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

inline feedback Pwr::set_backupDomain_writeProtection(bool enable)
{
	if(enable == true)
	{
		bit::clear(*MCU::PWR::CR, 8);
	}
	else
	{
		bit::set(*MCU::PWR::CR, 8);
	}
	
	return(OK);
}