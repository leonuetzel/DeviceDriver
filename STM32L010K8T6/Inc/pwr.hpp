#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"





class PWR
{
	public:
		
		enum class e_voltageRange : uint8
		{
			R1_1V8	= 0x1,
			R2_1V5	= 0x2,
			R3_1V2	= 0x3
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		e_voltageRange m_voltageRange;
		
		
		//	Constructor and Destructor
		constexpr inline PWR();
		PWR(const PWR& pwr) = delete;
		inline ~PWR();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32L010K8T6;
		
		
		
		
		
	public:
		
		feedback set_voltageRange(e_voltageRange range);
		
		constexpr inline e_voltageRange get_voltageRange() const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline PWR::PWR()
	:	m_voltageRange(e_voltageRange::R2_1V5)
{
	
}


inline PWR::~PWR()
{
	
}







inline feedback PWR::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::PWR, true);
	
	
	//	Disable Write Protection of Backup Domain
	bit::set(*MCU::PWR::CR, 8);
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

constexpr inline PWR::e_voltageRange PWR::get_voltageRange() const
{
	return(m_voltageRange);
}