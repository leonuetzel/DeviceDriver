#pragma once

#include "cmos.hpp"





class SYSCFG
{
	public:
		
		enum class e_package
		{
			LQFP100							= 0x0,
			TQFP144							= 0x2,
			TQFP176_UFBGA176		= 0x4,
			LQFP208_TFBGA240		= 0x8
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		bool m_overdriveEnabled;
		e_package m_package;
		
		
		
		//	Constructor and Destructor
		constexpr inline SYSCFG();
		SYSCFG(const SYSCFG& syscfg) = delete;
		inline ~SYSCFG();
		
		
		//	Member Functions
		feedback startup();
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback set_overdrive(bool enable);
		bool get_overdriveEnabled();
		e_package get_package();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline SYSCFG::SYSCFG()
	:	m_overdriveEnabled(false),
		m_package(e_package::LQFP100)
{
	
}


inline SYSCFG::~SYSCFG()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

