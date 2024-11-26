#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class EXTI
{
	public:
		
		enum class e_edge
		{
			NONE		= 0,
			RISING	= 1,
			FALLING	= 2,
			TOGGLE	= 3			
		};
		
		enum class e_line
		{
			PVD										= 16,
			RTC_ALARM							= 17,
			USB_WAKEUP						= 18,
			ETHERNET_WAKEUP				= 19
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline EXTI();
		EXTI(const EXTI& exti) = delete;
		inline ~EXTI();
		
		
		//	Member Functions
		inline feedback startup();
		void afio_set_extiLine(GPIO::e_pin pin);
		
		
		//	Friends
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		inline feedback init_interrupt_GPIO(GPIO::e_pin pin, e_edge edge);
		inline feedback init_interrupt_internal(e_line line, bool interrupt);
		inline void softwareTrigger(uint32 line);
		
		inline feedback clear_pendingBit(GPIO::e_pin pin);
		inline feedback clear_pendingBit(e_line line);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline EXTI::EXTI()
{
	
}


inline EXTI::~EXTI()
{
	
}







inline feedback EXTI::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline feedback EXTI::init_interrupt_GPIO(GPIO::e_pin pin, e_edge edge)
{
	//	AFIO Pin Selection
	afio_set_extiLine(pin);
	
	
	//	Edge Selection
	const uint32 pinNumber = GPIO::get_pinNumber(pin);
	if(bit::isSet((uint32) edge, 0) == true)
	{
		bit::set(*MCU::EXTI::RTSR, pinNumber);
	}
	else
	{
		bit::clear(*MCU::EXTI::RTSR, pinNumber);
	}
	
	if(bit::isSet((uint32) edge, 1) == true)
	{
		bit::set(*MCU::EXTI::FTSR, pinNumber);
	}
	else
	{
		bit::set(*MCU::EXTI::FTSR, pinNumber);
	}
	
	
	//	Event Masking
	bit::set(*MCU::EXTI::IMR, pinNumber);
	
	
	return(OK);
}


inline feedback EXTI::init_interrupt_internal(e_line line, bool interrupt)
{
	if((uint32) line > 31)
	{
		return(FAIL);
	}
	
	uint32 bit = (uint32) line;
	bit::set(*MCU::EXTI::RTSR, bit);
	bit::clear(*MCU::EXTI::FTSR, bit);
	if(interrupt == true)
	{
		bit::set(*MCU::EXTI::IMR, bit);
	}
	else
	{
		bit::clear(*MCU::EXTI::IMR, bit);
	}
	
	
	return(OK);
}







inline void EXTI::softwareTrigger(uint32 line)
{
	if(line < 20)
	{
		bit::set(*MCU::EXTI::SWIER, line);
	}
}







inline feedback EXTI::clear_pendingBit(GPIO::e_pin pin)
{
	const uint32 pinNumber = GPIO::get_pinNumber(pin);
	
	bit::set(*MCU::EXTI::PR, pinNumber);
	
	return(OK);
}


inline feedback EXTI::clear_pendingBit(e_line line)
{
	if((uint32) line > 32)
	{
		return(FAIL);
	}
	
	uint32 bit = (uint32) line;
	bit::set(*MCU::EXTI::PR, bit);
	
	return(OK);
}