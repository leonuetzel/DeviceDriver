#pragma once

#include "cmos.hpp"





class ADC_3
{
	public:
		
		static constexpr uint32 c_valueBufferSize	= 20;
		
		enum class e_clockSource
		{
			KERNEL										= 0x0,
			AHB_DIV_1									= 0x1,
			AHB_DIV_2									= 0x2,
			AHB_DIV_4									= 0x3
		};
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint32 c_clock_max = 50000000;
		static constexpr uint16 c_prescaler[12] = {1, 2, 4, 6, 8, 10, 12, 16, 32, 64, 128, 256};
		
		
		//	Non-static Member
		uint16 m_clock;
		uint16* m_value;
		
		
		//	Constructor and Destructor
		constexpr inline ADC_3();
		ADC_3(const ADC_3& adc_3) = delete;
		inline ~ADC_3();
		
		
		//	Member Functions
		inline feedback startup();
		
		static void callback();
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback init(uint32 clock, uint16 valueBuffer[c_valueBufferSize], e_clockSource clockSource);
		
		inline uint16 operator[](uint8 channel) const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline ADC_3::ADC_3()
	:	m_clock(0),
		m_value(nullptr)
{
	
}


inline ADC_3::~ADC_3()
{
	
}







inline feedback ADC_3::startup()
{
	//	Create Semaphore
	return(CMOS::get().semaphore_create(this));
}


/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline uint16 ADC_3::operator[](uint8 channel) const
{
	if(channel < c_valueBufferSize)
	{
		return(m_value[channel]);
	}
	return(0);
}