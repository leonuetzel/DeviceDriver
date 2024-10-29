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
			RTC										= 19,
			I2C_1_WAKEUP					= 23,
			USART_1_WAKEUP				= 25,
			LSE_CSS								= 31
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
		friend class STM32C071KBU6;
		
		
		
		
		
	public:
		
		inline feedback init_interrupt_GPIO(GPIO::e_pin pin, e_edge edge);
		inline feedback init_interrupt_internal(e_line line, bool interrupt);
		inline void softwareTrigger(uint32 line);
		inline void softwareTrigger(GPIO::e_pin pin);
		
		inline feedback clear_pendingBitRisingEdge(uint32 pin);
		inline feedback clear_pendingBitRisingEdge(e_line line);
		inline feedback clear_pendingBitFallingEdge(uint32 pin);
		inline feedback clear_pendingBitFallingEdge(e_line line);
		inline feedback clear_pendingBit(uint32 pin);
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
	const uint32 port = GPIO::get_portNumber(pin);
	const uint32 pinNumber = GPIO::get_pinNumber(pin);
	
	
	//	Pin Selection
	volatile uint32* address = MCU::EXTI::EXTI_CR1 + pinNumber / 4;
	uint32 mask = (uint32) port;
	uint32 bitfield_startBit = 8 * (pinNumber % 4);
	uint32 temp = *address & (0xFFFFFFFF - (0x0F << bitfield_startBit));
	*address = temp | (mask << bitfield_startBit);
	
	
	//	Edge Selection
	if(bit::isSet((uint32) edge, 0) == true)
	{
		bit::set(*MCU::EXTI::RTSR1, pinNumber);
	}
	else
	{
		bit::clear(*MCU::EXTI::RTSR1, pinNumber);
	}
	
	if(bit::isSet((uint32) edge, 1) == true)
	{
		bit::set(*MCU::EXTI::FTSR1, pinNumber);
	}
	else
	{
		bit::clear(*MCU::EXTI::FTSR1, pinNumber);
	}
	
	
	//	Event Masking
	bit::set(*MCU::EXTI::IMR1, pinNumber);
	
	
	return(OK);
}


inline feedback EXTI::init_interrupt_internal(e_line line, bool interrupt)
{
	if((uint32) line > 31)
	{
		return(FAIL);
	}
	
	uint32 bit = (uint32) line;
	bit::set(*MCU::EXTI::RTSR1, bit);
	bit::clear(*MCU::EXTI::FTSR1, bit);
	if(interrupt == true)
	{
		bit::set(*MCU::EXTI::IMR1, bit);
	}
	else
	{
		bit::clear(*MCU::EXTI::IMR1, bit);
	}
	
	
	return(OK);
}







inline void EXTI::softwareTrigger(uint32 line)
{
	if(line < 20)
	{
		bit::set(*MCU::EXTI::SWIER1, line);
	}
}


inline void EXTI::softwareTrigger(GPIO::e_pin pin)
{
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	softwareTrigger(pinNumber);
}







inline feedback EXTI::clear_pendingBitRisingEdge(uint32 pin)
{
	if(pin > 15)
	{
		return(FAIL);
	}
	
	*MCU::EXTI::RPR1 = 1 << pin;
	
	return(OK);
}


inline feedback EXTI::clear_pendingBitRisingEdge(e_line line)
{
	if((uint32) line > 32)
	{
		return(FAIL);
	}
	
	*MCU::EXTI::RPR1 = 1 << ((uint32) line);
	
	return(OK);
}


inline feedback EXTI::clear_pendingBitFallingEdge(uint32 pin)
{
	if(pin > 15)
	{
		return(FAIL);
	}
	
	*MCU::EXTI::FPR1 = 1 << pin;
	
	return(OK);
}


inline feedback EXTI::clear_pendingBitFallingEdge(e_line line)
{
	if((uint32) line > 32)
	{
		return(FAIL);
	}
	
	*MCU::EXTI::FPR1 = 1 << ((uint32) line);
	
	return(OK);
}


inline feedback EXTI::clear_pendingBit(uint32 pin)
{
	if(clear_pendingBitRisingEdge(pin) != OK)
	{
		return(FAIL);
	}
	return(clear_pendingBitFallingEdge(pin));
}


inline feedback EXTI::clear_pendingBit(e_line line)
{
	if(clear_pendingBitRisingEdge(line) != OK)
	{
		return(FAIL);
	}
	return(clear_pendingBitFallingEdge(line));
}