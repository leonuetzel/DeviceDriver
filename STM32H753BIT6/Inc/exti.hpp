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
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline EXTI();
		EXTI(const EXTI& exti) = delete;
		inline ~EXTI();
		
		
		//	Member Functions
		feedback startup();
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback init_GPIO_interrupt(MCU::PIN pin, e_edge edge);
		feedback set_GPIO_interrupt_state(MCU::PIN pin, bool enable);
		void softwareTrigger(uint32 eventNumber);
		inline void softwareTrigger(MCU::PIN pin);
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

inline void EXTI::softwareTrigger(MCU::PIN pin)
{
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	softwareTrigger(pinNumber);
}