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
			RTC_ALARM							= 17
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
		friend class STM32F103C8T6;
		friend void ISR_EXTI_0();
		friend void ISR_EXTI_1();
		friend void ISR_EXTI_2();
		friend void ISR_EXTI_3();
		friend void ISR_EXTI_4();
		friend void ISR_EXTI_9_TO_5();
		friend void ISR_EXTI_15_TO_10();
	
	
	
	
	
	public:
		
		inline feedback init_GPIO_interrupt(MCU::PIN pin, e_edge edge);
		[[deprecated("use init_GPIO_interrupt")]]
		inline feedback init_interrupt_GPIO(MCU::PIN pin, e_edge edge);
		inline feedback init_interrupt_internal(e_line line, bool interrupt);
		inline void softwareTrigger(uint32 line);
		
		inline feedback clear_pendingBit(uint32 pin);
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

inline feedback EXTI::init_GPIO_interrupt(MCU::PIN pin, e_edge edge)
{
	//	AFIO Pin Selection
	afio_set_extiLine(pin);
	
	
	//	Edge Selection
	const uint32 pinNumber = (((uint32) pin) & 0x0F);
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
		bit::clear(*MCU::EXTI::FTSR, pinNumber);
	}
	
	
	//	Event Masking
	bit::set(*MCU::EXTI::IMR, pinNumber);
	
	
	return(register_line(pinNumber));
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







inline feedback EXTI::clear_pendingBit(uint32 pin)
{
	if(pin > 16)
	{
		return(FAIL);
	}
	
	*MCU::EXTI::PR = 1 << pin;							//	Write 1 to this Line only: writing the Register back would also clear the other pending Lines
	
	return(OK);
}


inline feedback EXTI::clear_pendingBit(e_line line)
{
	if((uint32) line > 32)
	{
		return(FAIL);
	}
	
	uint32 bit = (uint32) line;
	*MCU::EXTI::PR = 1 << bit;							//	Write 1 to this Line only: writing the Register back would also clear the other pending Lines
	
	return(OK);
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
