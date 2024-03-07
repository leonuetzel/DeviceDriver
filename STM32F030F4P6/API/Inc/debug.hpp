#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class Debug
{
	public:
		
		enum class e_module
		{
			TIMER_3		= 0x001,
			TIMER_14	= 0x008,
			RTC				= 0x00A,
			WWDG			= 0x00B,
			IWDG			= 0x00C,
			I2C1			= 0x015,
			
			TIMER_1		= 0x10B,
			TIMER_16	= 0x111,
			TIMER_17	= 0x112
		};
		
		
		
		
		
	private:
		
		uint16 m_revisionID;
		uint16 m_deviceID;
		
		constexpr inline Debug();
		Debug(const Debug& debug) = delete;
		inline ~Debug();
		
		inline feedback startup(RCC& rcc);
		
		friend class STM32F030F4P6;
		
		
		
		
		
	public:
		
		void freeze_onDebug(e_module module, bool freeze);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Debug::Debug()
	:	m_revisionID(0),
		m_deviceID(0)
{
	
}


inline Debug::~Debug()
{
	
}







inline feedback Debug::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::DEBUG_MCU, true);
	
	*MCU::DBGMCU::APB1_FZ = 0;
	*MCU::DBGMCU::APB2_FZ = 0;
	
	freeze_onDebug(e_module::WWDG, true);
	freeze_onDebug(e_module::IWDG, true);
	freeze_onDebug(e_module::RTC, true);
	
	
	//	Read Device and Revision IDs
	uint32 ID = *MCU::DBGMCU::IDC;
	m_revisionID = (ID >> 16) & 0x0000FFFF;
	m_deviceID = ID & 0x0000FFFF;
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

