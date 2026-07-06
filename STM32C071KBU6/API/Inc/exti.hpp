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
		void afio_set_extiLine(MCU::PIN pin);
		
		
		//	Friends
		friend class STM32C071KBU6;
		
		
		
		
		
	public:
		
		feedback init_interrupt_GPIO(MCU::PIN pin, e_edge edge);
		inline feedback init_interrupt_internal(e_line line, bool interrupt);
		void softwareTrigger(MCU::PIN pin);
		inline void softwareTrigger(uint32 line);
		
		bool isPendingRisingEdge(MCU::PIN pin);
		inline bool isPendingRisingEdge(e_line line);
		bool isPendingFallingEdge(MCU::PIN pin);
		inline bool isPendingFallingEdge(e_line line);
		inline bool isPending(MCU::PIN pin);
		inline bool isPending(e_line line);
		
		feedback clear_pendingBitRisingEdge(MCU::PIN pin);
		inline feedback clear_pendingBitRisingEdge(e_line line);
		feedback clear_pendingBitFallingEdge(MCU::PIN pin);
		inline feedback clear_pendingBitFallingEdge(e_line line);
		inline feedback clear_pendingBit(MCU::PIN pin);
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







inline bool EXTI::isPendingRisingEdge(e_line line)
{
	if((uint32) line > 31)
	{
		return(false);
	}
	
	return(bit::isSet(*MCU::EXTI::RPR1, (uint32) line));
}


inline bool EXTI::isPendingFallingEdge(e_line line)
{
	if((uint32) line > 31)
	{
		return(false);
	}
	
	return(bit::isSet(*MCU::EXTI::FPR1, (uint32) line));
}


inline bool EXTI::isPending(e_line line)
{
	if(isPendingRisingEdge(line) == true || isPendingFallingEdge(line) == true)
	{
		return(true);
	}
	return(false);
}







inline feedback EXTI::clear_pendingBitRisingEdge(e_line line)
{
	if((uint32) line > 31)
	{
		return(FAIL);
	}
	
	*MCU::EXTI::RPR1 = 1 << ((uint32) line);
	
	return(OK);
}


inline feedback EXTI::clear_pendingBitFallingEdge(e_line line)
{
	if((uint32) line > 31)
	{
		return(FAIL);
	}
	
	*MCU::EXTI::FPR1 = 1 << ((uint32) line);
	
	return(OK);
}


inline feedback EXTI::clear_pendingBit(MCU::PIN pin)
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