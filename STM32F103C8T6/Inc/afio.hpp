#pragma once

#include "cmos.hpp"





class AFIO
{
	public:
		
		enum class e_debugConfiguration
		{
			SWD_AND_JTAG								= 0x0,
			SWD_AND_JTAG_WITHOUT_NJTRST	= 0x1,
			SWD													= 0x2,
			NONE												= 0x4
		};
		
		
		
		
		
		//	Remaps of AFIO_MAPR: Bit Position (Bit 4-0) and Number of Bits (Bit 7-5) of the Field (RM0008, AFIO_MAPR for low-, medium-, high- and XL-density Devices)
		enum class e_remap : uint8
		{
			SPI_1		= 0 | (1 << 5),		//	SPI1: PA4 ... PA7 or PA15, PB3 ... PB5
			I2C_1		= 1 | (1 << 5),		//	I2C1: PB6/PB7 or PB8/PB9
			USART_1		= 2 | (1 << 5),		//	USART1: PA9/PA10 or PB6/PB7
			USART_2		= 3 | (1 << 5),		//	USART2: PA0 ... PA4 or PD3 ... PD7
			USART_3		= 4 | (2 << 5),		//	USART3: 0 = PB10 ... PB14, 1 = PC10 ... PC12, PB13/PB14, 3 = PD8 ... PD12
			TIMER_1		= 6 | (2 << 5),		//	TIM1: 0 = no, 1 = partial, 3 = full Remap
			TIMER_2		= 8 | (2 << 5),		//	TIM2: 0 ... 3
			TIMER_3		= 10 | (2 << 5),		//	TIM3: 0 = no, 2 = partial, 3 = full Remap
			TIMER_4		= 12 | (1 << 5),		//	TIM4: PB6 ... PB9 or PD12 ... PD15
			CAN_1		= 13 | (2 << 5),		//	CAN: 0 = PA11/PA12, 2 = PB8/PB9, 3 = PD0/PD1
			PD01		= 15 | (1 << 5),		//	PD0/PD1 on OSC_IN/OSC_OUT
			ADC_1_EXTERNAL_TRIGGER_INJECTED		= 17 | (1 << 5),		//	ADC1 injected Trigger: EXTI15 or TIM8 Channel 4
			ADC_1_EXTERNAL_TRIGGER_REGULAR		= 18 | (1 << 5),		//	ADC1 regular Trigger: EXTI11 or TIM8 TRGO
			ADC_2_EXTERNAL_TRIGGER_INJECTED		= 19 | (1 << 5),		//	ADC2 injected Trigger: EXTI15 or TIM8 Channel 4
			ADC_2_EXTERNAL_TRIGGER_REGULAR		= 20 | (1 << 5)		//	ADC2 regular Trigger: EXTI11 or TIM8 TRGO
		};
		
	private:
		
		//	Static Member
		e_debugConfiguration m_debugConfiguration;
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline AFIO();
		AFIO(const AFIO& afio) = delete;
		inline ~AFIO();
		
		
		//	Member Functions
		inline feedback startup();
		void write_mapr(uint32 mask, uint32 value);
		
		
		//	Friends
		friend class STM32F103C8T6;
		
		
		
		
		
	public:
		
		void set_debugConfiguration(e_debugConfiguration debugConfiguration);
		feedback set_remap(e_remap remap, uint32 value);
		
		void set_extiExternalInterruptPin(MCU::PIN pin);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline AFIO::AFIO()
	:	m_debugConfiguration(e_debugConfiguration::SWD_AND_JTAG)
{
	
}


inline AFIO::~AFIO()
{
	
}







inline feedback AFIO::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/
