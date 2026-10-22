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
		//	Callback of a GPIO Line: Object and Member Function, called by call<T>(), which knows the Class (see subscribe)
		typedef struct
		{
			void (*caller)(void* object, const uint8* method);
			void* object;
			uint8 method[8];
		}s_callback;
		
		
		
		//	Non-static Member
		uint16 m_eventCreated;									//	Bit per GPIO Line: its CMOS Event exists
		uint16 m_eventID[16];
		s_callback* m_callback[16];								//	nullptr: no Callback
		
		
		
		//	Constructor and Destructor
		constexpr inline EXTI();
		EXTI(const EXTI& exti) = delete;
		inline ~EXTI();
		
		
		//	Member Functions
		inline feedback startup();
		feedback register_line(uint32 line);
		void dispatch(uint32 firstLine, uint32 lastLine);
		feedback set_callback(MCU::PIN pin, s_callback* callback);
		template<typename T>
		static void call(void* object, const uint8* method);
		void afio_set_extiLine(MCU::PIN pin);
		
		
		//	Friends
		friend class STM32C071KBU6;
		friend void ISR_EXTI_0_TO_1();
		friend void ISR_EXTI_2_TO_3();
		friend void ISR_EXTI_4_TO_15();
	
	
	
	
	
	public:
		
		feedback init_GPIO_interrupt(MCU::PIN pin, e_edge edge);
		[[deprecated("use init_GPIO_interrupt")]]
		inline feedback init_interrupt_GPIO(MCU::PIN pin, e_edge edge);
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
		
		//	GPIO Lines: the Driver owns their Interrupts, emits the CMOS Event of the Line and calls an optional Callback
		uint16 get_eventID(MCU::PIN pin) const;
		template<typename T>
		feedback subscribe(MCU::PIN pin, void (T::*method)(), T* object);
		feedback unsubscribe(MCU::PIN pin);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline EXTI::EXTI()
	:	m_eventCreated(0),
		m_eventID(),
		m_callback()
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


inline bool EXTI::isPending(MCU::PIN pin)
{
	if(isPendingRisingEdge(pin) == true || isPendingFallingEdge(pin) == true)
	{
		return(true);
	}
	return(false);
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


inline feedback EXTI::init_interrupt_GPIO(MCU::PIN pin, e_edge edge)
{
	return(init_GPIO_interrupt(pin, edge));
}



template<typename T>
inline feedback EXTI::subscribe(MCU::PIN pin, void (T::*method)(), T* object)
{
	//	The Member Function Pointer is kept as Bytes, call<T>() knows its Type again; the Callback runs in the Interrupt
	static_assert(sizeof(method) <= sizeof(s_callback::method), "Member Function Pointer does not fit");
	if(method == nullptr || object == nullptr)
	{
		return(FAIL);
	}
	s_callback* const callback = new s_callback;
	if(callback == nullptr)
	{
		return(FAIL);
	}
	callback->caller = &call<T>;
	callback->object = object;
	__builtin_memcpy(callback->method, &method, sizeof(method));
	return(set_callback(pin, callback));
}


template<typename T>
inline void EXTI::call(void* object, const uint8* method)
{
	void (T::*function)() = nullptr;
	__builtin_memcpy(&function, method, sizeof(function));
	(static_cast<T*>(object)->*function)();
}
