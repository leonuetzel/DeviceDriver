#pragma once

#include "registers.hpp"
#include "cmos.hpp"




class DBG
{
	public:
		
		enum class e_module
		{
			TIMER_3		= 0x0001,
			RTC				= 0x000A,
			WWDG			= 0x000B,
			IWDG			= 0x000C,
			I2C				= 0x0015,
			TIMER_1		= 0x010B,
			TIMER_14	= 0x010F,
			TIMER_16	= 0x0111,
			TIMER_17	= 0x0112
		};
		
		
		
		
		
	private:
		
		//	Static Member
		inline feedback startup();
		inline void freeze_onDebug(e_module module, bool freeze);
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline DBG();
		DBG(const DBG& dbg) = delete;
		inline ~DBG();
		
		
		//	Member Functions
		
		
		
		//	Friends
		friend class STM32C031K6U6;
		
		
		
		
		
	public:
		
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline DBG::DBG()
{
	
}


inline DBG::~DBG()
{
	
}







inline feedback DBG::startup()
{
	freeze_onDebug(e_module::WWDG, true);
	freeze_onDebug(e_module::IWDG, true);
		
	return(OK);
}


inline void DBG::freeze_onDebug(e_module module, bool freeze)
{
	const uint32 bit = ((uint32) module) & 0x001F;
	const uint32 offset = (((uint32) module) & 0xFF00) >> 8;
	
	volatile uint32* reg = MCU::DBG::APB_FZ1 + offset;
	
	
	if(freeze == true)
	{
		bit::set(*reg, bit);
	}
	else
	{
		bit::clear(*reg, bit);
	}
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

