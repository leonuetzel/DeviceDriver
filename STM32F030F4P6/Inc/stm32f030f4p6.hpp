#pragma once

#include "registers.hpp"
#include "cmos.hpp"

#include "debug.hpp"
#include "syscfg.hpp"
#include "pwr.hpp"
#include "flash.hpp"
#include "rcc.hpp"
#include "gpio.hpp"
#include "exti.hpp"
#include "rtc.hpp"
#include "timer_3.hpp"
#include "dma.hpp"
#include "adc.hpp"
#include "usart_1.hpp"





uint32 __startup__();





class STM32F030F4P6
{
	public:
		
		
		
		
		
		
		
	private:
		
		typedef struct
		{
			uint32 vector[NVIC::c_numberOfInterrupts];
		}s_interruptTable;
		
		
		//	Static Member
		static const s_interruptTable c_interruptTable;
		
		
		//	Non-static Member
		Debug m_debug;
		SYSCFG m_syscfg;
		PWR m_pwr;
		Flash m_flash;
		RCC m_rcc;
		GPIO m_gpio;
		EXTI m_exti;
		RTC m_rtc;
		Timer_3 m_timer_3;
		DMA m_dma[DMA::c_channel];
		ADC m_adc;
		USART_1 m_usart_1;
		
		
		//	Constructor and Destructor
		inline STM32F030F4P6();
		STM32F030F4P6(const STM32F030F4P6& stm32f030f4p6) = delete;
		inline ~STM32F030F4P6();
		
		
		//	Member Functions
		inline feedback startup();
		
		static void copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes);
		static void zeroOutRAM(uint32* startAddress, uint32 sizeInBytes);
		
		
		//	Friends
		friend void EXCEPTION_RESET();
		friend uint32 __startup__();
		
		
		
		
		
	public:
		
		static STM32F030F4P6& get();
		
		constexpr inline Flash& get_flash();
		constexpr inline RCC& get_rcc();
		constexpr inline PWR& get_pwr();
		constexpr inline Debug& get_debug();
		constexpr inline GPIO& get_gpio();
		constexpr inline EXTI& get_exti();
		constexpr inline RTC& get_rtc();
		constexpr inline Timer_3& get_timer_3();
		constexpr inline DMA& get_dma(uint8 channel);
		constexpr inline ADC& get_adc();
		constexpr inline USART_1& get_usart_1();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

extern void ISR_WWDG();
extern void ISR_RTC();
extern void ISR_FLASH();
extern void ISR_RCC();
extern void ISR_EXTI_0_TO_1();
extern void ISR_EXTI_2_TO_3();
extern void ISR_EXTI_4_TO_15();
extern void ISR_DMA_CH0();
extern void ISR_DMA_CH1_CH2();
extern void ISR_DMA_CH3_CH4();
extern void ISR_ADC();
extern void ISR_TIMER_1_BREAK_UPDATE_TRIGGER_COMMUTATION();
extern void ISR_TIMER_1_CAPTURE_COMPARE();
extern void ISR_TIMER_3();
extern void ISR_TIMER_14();
extern void ISR_TIMER_16();
extern void ISR_TIMER_17();
extern void ISR_I2C_1();
extern void ISR_SPI_1();
extern void ISR_USART_1();



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline STM32F030F4P6::STM32F030F4P6()
	: m_debug(),
		m_syscfg(),
		m_pwr(),
		m_flash(),
		m_rcc(m_flash),
		m_gpio(),
		m_exti(),
		m_rtc(),
		m_timer_3(m_rcc),
		m_dma(),
		m_adc(),
		m_usart_1()
{
	
}


inline STM32F030F4P6::~STM32F030F4P6()
{
	
}







inline feedback STM32F030F4P6::startup()
{
	if(m_flash.startup() != OK)
	{
		return(FAIL);
	}
	if(m_rcc.startup() != OK)
	{
		return(FAIL);
	}
	if(m_pwr.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_debug.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_gpio.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_exti.startup() != OK)
	{
		return(FAIL);
	}
	if(m_rtc.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_3.startup() != OK)
	{
		return(FAIL);
	}
	for(uint32 i = 0; i < DMA::c_channel; i++)
	{
		if(m_dma[i].startup(m_rcc, i) != OK)
		{
			return(FAIL);
		}
	}
	if(m_adc.startup() != OK)
	{
		return(FAIL);
	}
	if(m_usart_1.startup() != OK)
	{
		return(FAIL);
	}
	
	
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

constexpr inline PWR& STM32F030F4P6::get_pwr()
{
	return(m_pwr);
}


constexpr inline Flash& STM32F030F4P6::get_flash()
{
	return(m_flash);
}


constexpr inline RCC& STM32F030F4P6::get_rcc()
{
	return(m_rcc);
}


constexpr inline Debug& STM32F030F4P6::get_debug()
{
	return(m_debug);
}


constexpr inline GPIO& STM32F030F4P6::get_gpio()
{
	return(m_gpio);
}


constexpr inline EXTI& STM32F030F4P6::get_exti()
{
	return(m_exti);
}


constexpr inline RTC& STM32F030F4P6::get_rtc()
{
	return(m_rtc);
}


constexpr inline Timer_3& STM32F030F4P6::get_timer_3()
{
	return(m_timer_3);
}


constexpr inline DMA& STM32F030F4P6::get_dma(uint8 channel)
{
	if(channel < DMA::c_channel)
	{
		return(m_dma[channel]);
	}
	DMA& fail = (DMA&) *((DMA*) nullptr);
	return(fail);
}


constexpr inline ADC& STM32F030F4P6::get_adc()
{
	return(m_adc);
}


constexpr inline USART_1& STM32F030F4P6::get_usart_1()
{
	return(m_usart_1);
}