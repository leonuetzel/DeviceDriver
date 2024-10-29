#pragma once

#include "registers.hpp"
#include "cmos.hpp"




class Debug
{
	public:
		
		enum class e_module
		{
			IWDG			= 0x08,
			WWDG			= 0x09,
			TIMER_1		= 0x0A,
			TIMER_2		= 0x0B,
			TIMER_3		= 0x0C,
			TIMER_4		= 0x0D,
			CAN				= 0x0E,
			I2C_1			= 0x0F,
			I2C_2			= 0x10
		};
		
		
		
		
		
	private:
		
		//	Static Member
		inline feedback startup();
		inline void freeze_onDebug(e_module module, bool freeze);
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline Debug();
		Debug(const Debug& debug) = delete;
		inline ~Debug();
		
		
		//	Member Functions
		
		
		
		//	Friends
		friend class STM32F103C8T6;
		
		
		
		
		
	public:
		
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Debug::Debug()
{
	
}


inline Debug::~Debug()
{
	
}







inline feedback Debug::startup()
{
	*MCU::DBGMCU::CR = 0;
	
	freeze_onDebug(e_module::WWDG, true);
	freeze_onDebug(e_module::IWDG, true);
		
	return(OK);
}


inline void Debug::freeze_onDebug(e_module module, bool freeze)
{
	uint32 bit = (uint32) module & 0x01F;
	
	if(freeze == true)
	{
		bit::set(*MCU::DBGMCU::CR, bit);
	}
	else
	{
		bit::clear(*MCU::DBGMCU::CR, bit);
	}
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

