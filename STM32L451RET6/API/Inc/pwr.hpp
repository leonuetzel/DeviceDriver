#pragma once

#include "registers.hpp"
#include "rcc.hpp"





class PWR
{
	public:
		
		enum class e_voltageScaling
		{
			RANGE1_1V2	= 0x1,
			RANGE2_1V0	= 0x2
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		e_voltageScaling m_voltageScaling;
		
		
		//	Constructor and Destructor
		constexpr inline PWR();
		PWR(const PWR& pwr) = delete;
		inline ~PWR();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32L451RET6;
		
		
		
		
		
	public:
		
		inline feedback set_backupDomain_writeProtection(bool enable);
		inline feedback set_voltageScaling(e_voltageScaling voltageScaling);
		constexpr inline e_voltageScaling get_voltageScaling() const;
		
		inline feedback voltageScalingIncrease();
		inline feedback voltageScalingDecrease();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline PWR::PWR()
	:	m_voltageScaling(e_voltageScaling::RANGE1_1V2)
{
	
}


inline PWR::~PWR()
{
	
}







inline feedback PWR::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::PWR, true);
	
	
	//	Disable Write Protection of Backup Domain
	set_backupDomain_writeProtection(false);
	
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
		bit::clear(*MCU::PWR::CR1, 8);
	}
	else
	{
		bit::set(*MCU::PWR::CR1, 8);
	}
	
	return(OK);
}


inline feedback PWR::set_voltageScaling(e_voltageScaling voltageScaling)
{
	const uint32 temp = *MCU::PWR::CR1 & 0xFFFFF9FF;
	const uint32 mask = (uint32) voltageScaling;
	*MCU::PWR::CR1 = temp | (mask << 9);
	return(OK);
}


constexpr inline PWR::e_voltageScaling PWR::get_voltageScaling() const
{
	return(m_voltageScaling);
}







inline feedback PWR::voltageScalingIncrease()
{
	if(m_voltageScaling == e_voltageScaling::RANGE2_1V0)
	{
		return(set_voltageScaling(e_voltageScaling::RANGE1_1V2));
	}
	return(FAIL);
}


inline feedback PWR::voltageScalingDecrease()
{
	if(m_voltageScaling == e_voltageScaling::RANGE1_1V2)
	{
		return(set_voltageScaling(e_voltageScaling::RANGE2_1V0));
	}
	return(FAIL);
}