#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class DBG
{
	public:
		
		enum class e_module
		{
			//	APB 1
			TIMER_2			= 0x0000,
			TIMER_6			= 0x0004,
			RTC					= 0x000A,
			WWDG				= 0x000B,
			IWDG				= 0x000C,
			I2C_1				= 0x0015,
			I2C_2				= 0x0016,
			I2C_3				= 0x0017,
			CAN_1				= 0x0019,
			LP_TIMER_1	= 0x001F,
			
			LP_TIMER_2	= 0x0105,
			
			//	APB 2
			TIMER_1			= 0x020B,
			TIMER_15		= 0x0210,
			TIMER_16		= 0x0211
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
		friend class STM32L451RET6;
		
		
		
		
		
	public:
		
		//	Keeps the Debugger connected in Sleep, Stop and Standby/Shutdown - the Clocks keep running there, so the Mode draws more Current
		inline void set_debugInLowPowerModes(bool sleep, bool stop, bool standbyAndShutdown);
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


inline void DBG::set_debugInLowPowerModes(bool sleep, bool stop, bool standbyAndShutdown)
{
	//	DBGMCU_CR DBG_SLEEP, DBG_STOP, DBG_STANDBY (RM0394, DBGMCU) - DBG_STANDBY applies to Shutdown as well
	const uint32 mask = (sleep == true ? 0x1 : 0x0) | (stop == true ? 0x2 : 0x0) | (standbyAndShutdown == true ? 0x4 : 0x0);
	*MCU::DBGMCU::CR = (*MCU::DBGMCU::CR & 0xFFFFFFF8) | mask;
}


inline void DBG::freeze_onDebug(e_module module, bool freeze)
{
	const uint32 bit = ((uint32) module) & 0x001F;
	const uint32 offset = (((uint32) module) & 0xFF00) >> 8;
	
	volatile uint32* reg = MCU::DBGMCU::APB1_FZ1 + offset;
	
	
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

