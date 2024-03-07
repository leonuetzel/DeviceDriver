#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class ADC_1
{
	public:
		
		static constexpr uint32 c_numberOfValues	= 18;
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint32 c_clock_max = 14000000;
		
		
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
		
		inline feedback enable();
		inline feedback disable();
		inline feedback start();
		inline feedback calibrate();
		
		
		//	Friends
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		feedback init(uint32 clock, uint16 valueBuffer[c_numberOfValues]);
		
		inline uint16 operator[](uint8 channel);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline ADC_1::ADC_1()
	:	m_calibrationFactor(0),
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
	return(CMOS::get().semaphore_create(this));
}







inline feedback ADC_1::enable()
{
	//	Enable ADC
	bit::set(*MCU::ADC_1::CR2, 0);
	
	return(OK);
}


inline feedback ADC_1::disable()
{
	//	Disable ADC
	bit::clear(*MCU::ADC_1::CR2, 0);
	
	
	//	Wait for ADC to be disabled
	while(bit::isSet(*MCU::ADC_1::CR2, 0))
	{
		
	}
	
	return(OK);
}


inline feedback ADC_1::start()
{
	if(bit::isCleared(*MCU::ADC_1::CR2, 0))
	{
		return(FAIL);
	}
	
	bit::set(*MCU::ADC_1::CR2, 0);
	
	return(OK);
}


inline feedback ADC_1::calibrate()
{
	//	ADC must be enabled for at least 2 Cycles (ADEN = 1) for Calibration
	if(bit::isCleared(*MCU::ADC_1::CR2, 0))
	{
		return(FAIL);
	}
	
	
	//  Reset Calibration
	bit::set(*MCU::ADC_1::CR2, 3);
	
	
	//  Wait for Calibration Reset to be finished
	while(bit::isSet(*MCU::ADC_1::CR2, 3))
	{

	}
	
	
	//	Start Calibration
	bit::set(*MCU::ADC_1::CR2, 2);
	
	
	//	Wait for Calibration to finish
	while(bit::isSet(*MCU::ADC_1::CR2, 2))
	{
		
	}
	
	
	//	Store Calibration Factor
	m_calibrationFactor = *MCU::ADC_1::DR & 0x0000FFFF;
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