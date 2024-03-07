#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





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
		
		RCC& m_rcc;
		
		e_mode m_mode;
		e_voltage m_voltage;
		
		constexpr inline VREFBUF(RCC& rcc);
		VREFBUF(const VREFBUF& vrefbuf) = delete;
		inline ~VREFBUF();
		
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup();
		
		feedback set_mode(e_mode mode);
		feedback set_voltage(e_voltage voltage);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline VREFBUF::VREFBUF(RCC& rcc)
	: m_rcc(rcc),
		m_mode(e_mode::EXTERNAL),
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

