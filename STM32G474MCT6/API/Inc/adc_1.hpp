#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class ADC_1
{
	public:
		
		static constexpr uint32 c_numberOfValues	= 19;
		
		static constexpr uint16 c_prescaler[] = {1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256};
		
		enum class e_clockSource : uint8
		{
			PLL_P						= 0x10,
			SYSTEM					= 0x20,
			AHB2_DIV_1			= 0x01,
			AHB2_DIV_2			= 0x02,
			AHB2_DIV_4			= 0x03
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		uint32 m_calibrationFactor;
		uint32 m_clock;
		uint16* m_value;
		
		
		//	Constructor and Destructor
		constexpr inline ADC_1();
		ADC_1(const ADC_1& adc_1) = delete;
		inline ~ADC_1();
		
		
		//	Member Functions
		inline feedback startup();
		
		static void callback();
		
		feedback enable();
		feedback disable();
		
		feedback calibrateForSingleEnded();
		feedback calibrateForDifferential();
		
		
		//	Friends
		friend class STM32G474MCT6;
		
		
		
		
		
	public:
		
		feedback init(e_clockSource clockSource, uint16 valueBuffer[c_numberOfValues], uint8 prescalerIndex = 0);
		
		inline uint16 operator[](uint8 channel);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline ADC_1::ADC_1()
	: m_calibrationFactor(0),
		m_clock(0),
		m_value(nullptr)
{
	
}


inline ADC_1::~ADC_1()
{
	
}







inline feedback ADC_1::startup()
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

inline uint16 ADC_1::operator[](uint8 channel)
{
	if(channel < c_numberOfValues)
	{
		return(m_value[channel]);
	}
	return(0);
}