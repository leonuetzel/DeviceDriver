#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"





class CRC
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline CRC();
		CRC(const CRC& crc) = delete;
		inline ~CRC();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline CRC::CRC()
{
	
}


inline CRC::~CRC()
{
	
}







inline feedback CRC::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::CRC, true);
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

