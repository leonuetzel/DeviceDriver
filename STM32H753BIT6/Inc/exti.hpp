#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "gpio.hpp"





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
		
		constexpr inline EXTI();
		EXTI(const EXTI& exti) = delete;
		inline ~EXTI();
		
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup();
		
		feedback init_GPIO_interrupt(GPIO::e_pin pin, e_edge edge);
		feedback set_GPIO_interrupt_state(GPIO::e_pin pin, bool enable);
		void softwareTrigger(uint32 eventNumber);
		inline void softwareTrigger(GPIO::e_pin pin);
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



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void EXTI::softwareTrigger(GPIO::e_pin pin)
{
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	softwareTrigger(pinNumber);
}