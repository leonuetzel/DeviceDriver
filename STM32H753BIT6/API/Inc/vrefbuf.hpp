#pragma once

#include "cmos.hpp"





class VREFBUF
{
	public:
		
		enum class e_mode
		{
			OFF 											= 0x0,
			INTERNAL									= 0x1,
			EXTERNAL									= 0x2,
			HOLD											= 0x3
		};
		
		enum class e_voltage
		{
			VOLTAGE_2V5								= 0x0,
			VOLTAGE_2V048							= 0x1,
			VOLTAGE_1V8								= 0x2,
			VOLTAGE_1V5								= 0x3
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		e_mode m_mode;
		e_voltage m_voltage;
		
		
		//	Constructor and Destructor
		constexpr inline VREFBUF();
		VREFBUF(const VREFBUF& vrefbuf) = delete;
		inline ~VREFBUF();
		
		
		//	Member Functions
		feedback startup();
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback set_mode(e_mode mode);
		feedback set_voltage(e_voltage voltage);
		constexpr inline e_mode get_mode() const;
		constexpr inline e_voltage get_voltage() const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline VREFBUF::VREFBUF()
	: m_mode(e_mode::EXTERNAL),
		m_voltage(e_voltage::VOLTAGE_2V5)
{
	
}


inline VREFBUF::~VREFBUF()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

constexpr inline VREFBUF::e_mode VREFBUF::get_mode() const
{
	return(m_mode);
}


constexpr inline VREFBUF::e_voltage VREFBUF::get_voltage() const
{
	return(m_voltage);
}
