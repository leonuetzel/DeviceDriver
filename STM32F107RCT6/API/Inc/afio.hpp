#pragma once

#include "cmos.hpp"





class AFIO
{
	public:
		
		enum class e_debugConfiguration
		{
			SWD_AND_JTAG								= 0x0,
			SWD_AND_JTAG_WITHOUT_NJTRST	= 0x1,
			SWD													= 0x2,
			NONE												= 0x4
		};
		
		
		
		
		
	private:
		
		//	Static Member
		e_debugConfiguration m_debugConfiguration;
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline AFIO();
		AFIO(const AFIO& afio) = delete;
		inline ~AFIO();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		void set_debugConfiguration(e_debugConfiguration debugConfiguration);
		void set_extiExternalInterruptPin(MCU::PIN pin);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline AFIO::AFIO()
	:	m_debugConfiguration(e_debugConfiguration::SWD_AND_JTAG)
{
	
}


inline AFIO::~AFIO()
{
	
}







inline feedback AFIO::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

