#pragma once

#include "cmos.hpp"





class EXTI
{
	public:
		
		enum class e_edge
		{
			NONE,
			RISING,
			FALLING,
			TOGGLE
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
		feedback startup();
		feedback register_line(uint32 line);
		void dispatch(uint32 firstLine, uint32 lastLine);
		feedback set_callback(MCU::PIN pin, s_callback* callback);
		template<typename T>
		static void call(void* object, const uint8* method);
		
		
		//	Friends
		friend class STM32H753BIT6;
		friend void ISR_EXTI_0();
		friend void ISR_EXTI_1();
		friend void ISR_EXTI_2();
		friend void ISR_EXTI_3();
		friend void ISR_EXTI_4();
		friend void ISR_EXTI_9_TO_5();
		friend void ISR_EXTI_15_TO_10();
	
	
	
	
	
	public:
		
		feedback init_GPIO_interrupt(MCU::PIN pin, e_edge edge);
		feedback set_GPIO_interrupt_state(MCU::PIN pin, bool enable);
		void softwareTrigger(uint32 eventNumber);
		inline void softwareTrigger(MCU::PIN pin);
		
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



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void EXTI::softwareTrigger(MCU::PIN pin)
{
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	softwareTrigger(pinNumber);
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
