#pragma once

#include "cmos.hpp"





class PWR
{
	public:
		
		enum class e_voltageLevel
		{
			VOS_0											= 0x4,
			VOS_1											= 0x3,
			VOS_2 										= 0x2,
			VOS_3 										= 0x1
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		e_voltageLevel m_voltageLevel;
		
		
		//	Constructor and Destructor
		constexpr inline PWR();
		PWR(const PWR& pwr) = delete;
		inline ~PWR();
		
		
		//	Member Functions
		feedback startup();
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback set_voltageLevel(e_voltageLevel voltageLevel);
		e_voltageLevel get_voltageLevel();
		e_voltageLevel get_requiredVoltageLevel(uint32 divider_pll_1_p, uint32 divider_pll_1_q, uint32 divider_pll_1_r, uint32 clock_pll_1, bool pll_1_range_wide);
		void enable_ECC();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline PWR::PWR()
	:	m_voltageLevel(e_voltageLevel::VOS_3)
{
	
}


inline PWR::~PWR()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

