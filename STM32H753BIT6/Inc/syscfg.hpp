#pragma once

#include "registers.hpp"
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
		
		bool m_overdriveEnabled;
		e_package m_package;
		
		constexpr inline SYSCFG();
		SYSCFG(const SYSCFG& syscfg) = delete;
		inline ~SYSCFG();
		
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup();
		
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

