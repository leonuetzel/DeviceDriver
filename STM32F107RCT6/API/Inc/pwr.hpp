#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class PWR
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline PWR();
		PWR(const PWR& pwr) = delete;
		inline ~PWR();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		inline feedback set_backupDomain_writeProtection(bool enable);
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

inline feedback PWR::set_backupDomain_writeProtection(bool enable)
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