#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"
#include "gpio.hpp"





class EXTI
{
	public:
		
		enum class e_edge : uint8
		{
			NONE,
			RISING,
			FALLING,
			TOGGLE
		};
		
		enum class e_line : uint8
		{
			PVD									= 16,
			RTC_ALARM						= 17,
			USB_WAKEUP					= 18,
			RTC_TAMPER_CSS_LSE	= 19,
			RTC_WAKEUP					= 20,
			COMP1								= 21,
			COMP2								= 22,
			I2C1_WAKEUP					= 23,
			I2C2_WAKEUP					= 24,
			USART1_WAKEUP				= 25,
			USART2_WAKEUP				= 26,
			I2C3_WAKEUP					= 27,
			USART3_WAKEUP				= 28,
			COMP3								= 29,
			COMP4								= 30,
			COMP5								= 31,
			COMP6								= 32,
			COMP7								= 33,
			UART4								= 34,
			UART5								= 35,
			LPUART1							= 36,
			LPTIMER1						= 37,
			PVM1								= 40,
			PVM2								= 41,
			I2C4								= 42,
			UCPD								= 43
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
		
		
		//	Friends
		friend class STM32G474MCT6;
		friend void ISR_EXTI_0();
		friend void ISR_EXTI_1();
		friend void ISR_EXTI_2();
		friend void ISR_EXTI_3();
		friend void ISR_EXTI_4();
		friend void ISR_EXTI_9_TO_5();
		friend void ISR_EXTI_15_TO_10();
	
	
	
	
	
	public:
		
		feedback init_GPIO_interrupt(MCU::PIN pin, e_edge edge);
		feedback init_interrupt_internal(e_line line, bool interrupt);
		feedback init_event_internal(e_line line, bool event);
		
		feedback clear_pendingBit(MCU::PIN pin);
		feedback clear_pendingBit(e_line line);
		
		bool isPending(MCU::PIN pin);
		bool isPending(e_line line);
		
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
