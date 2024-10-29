#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class ADC
{
	public:
		
		static constexpr uint32 c_numberOfValues	= 11;
		
		enum class e_clockSource : uint8
		{
			HSI_16			= 0x0,
			APB2_DIV_2	= 0x1,
			APB2_DIV_4	= 0x2
		};
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint32 c_clock_max				= 16000000;
		
		
		//	Non-static Member
		uint32 m_calibrationFactor;
		uint32 m_clock;
		uint16* m_value;
		
		
		//	Constructor and Destructor
		constexpr inline ADC();
		ADC(const ADC& adc) = delete;
		inline ~ADC();
		
		
		//	Member Functions
		inline feedback startup();
		
		feedback enable();
		feedback disable();
		
		feedback calibrate();
		
		
		//	Friends
		friend class STM32L010K8T6;
		
		
		
		
		
	public:
		
		feedback init(e_clockSource clockSource, uint16 valueBuffer[c_numberOfValues]);
		
		inline uint16 operator[](uint8 channel);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline ADC::ADC()
	: m_calibrationFactor(0),
		m_clock(0),
		m_value(nullptr)
{
	
}


inline ADC::~ADC()
{
	
}







inline feedback ADC::startup()
{
	//	Create Semaphore
	CMOS::get().semaphore_create(this);
	
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline uint16 ADC::operator[](uint8 channel)
{
	if(channel < c_numberOfValues)
	{
		return(m_value[channel]);
	}
	return(0);
}