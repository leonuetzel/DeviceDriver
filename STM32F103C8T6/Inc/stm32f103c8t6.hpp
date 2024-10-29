#pragma once

#include "registers.hpp"
#include "cmos.hpp"

#include "debug.hpp"
#include "pwr.hpp"
#include "flash.hpp"
#include "rcc.hpp"
#include "gpio.hpp"
#include "rtc.hpp"
#include "afio.hpp"
#include "exti.hpp"
#include "timer_1.hpp"
#include "timer_3.hpp"
#include "timer_4.hpp"
#include "dma.hpp"
#include "adc_1.hpp"
#include "usart_1.hpp"





uint32 __startup__();





class STM32F103C8T6
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
		Flash m_flash;
		RCC m_rcc;
		Pwr m_pwr;
		Debug m_debug;
		GPIO m_gpio;
		AFIO m_afio;
		EXTI m_exti;
		RTC m_rtc;
		Timer_1 m_timer_1;
		Timer_3 m_timer_3;
		Timer_4 m_timer_4;
		DMA m_dma[DMA::c_channel];
		ADC_1 m_adc_1;
		USART_1 m_usart_1;
		
		
		//	Constructor and Destructor
		inline STM32F103C8T6();
		STM32F103C8T6(const STM32F103C8T6& stm32f103c8t6) = delete;
		inline ~STM32F103C8T6();
		
		
		//	Member Functions
		inline feedback startup();
		
		static void copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes);
		static void zeroOutRAM(uint32* startAddress, uint32 sizeInBytes);
		
		
		
		//	Friends
		friend void EXCEPTION_RESET();
		friend uint32 __startup__();
		
		
		
		
		
	public:
		
		inline static STM32F103C8T6& get();
		
		
		constexpr inline Flash& get_flash();
		constexpr inline RCC& get_rcc();
		constexpr inline Pwr& get_pwr();
		constexpr inline Debug& get_debug();
		constexpr inline GPIO& get_gpio();
		constexpr inline AFIO& get_afio();
		constexpr inline EXTI& get_exti();
		constexpr inline RTC& get_rtc();
		constexpr inline Timer_1& get_timer_1();
		constexpr inline Timer_3& get_timer_3();
		constexpr inline Timer_4& get_timer_4();
		constexpr inline DMA& get_dma(uint8 channel);
		constexpr inline ADC_1& get_adc_1();
		constexpr inline USART_1& get_usart_1();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

extern void ISR_WWDG();
extern void ISR_PVD();
extern void ISR_TAMPER();
extern void ISR_RTC();
extern void ISR_FLASH();
extern void ISR_RCC();
extern void ISR_EXTI_0();
extern void ISR_EXTI_1();
extern void ISR_EXTI_2();
extern void ISR_EXTI_3();
extern void ISR_EXTI_4();
extern void ISR_DMA_CH0();
extern void ISR_DMA_CH1();
extern void ISR_DMA_CH2();
extern void ISR_DMA_CH3();
extern void ISR_DMA_CH4();
extern void ISR_DMA_CH5();
extern void ISR_DMA_CH6();
extern void ISR_ADC();
extern void ISR_CAN_TX();
extern void ISR_CAN_RX_0();
extern void ISR_CAN_RX_1();
extern void ISR_CAN_SCE();
extern void ISR_EXTI_9_TO_5();
extern void ISR_TIMER_1_BREAK();
extern void ISR_TIMER_1_UPDATE();
extern void ISR_TIMER_1_TRIGGER_COMMUTATION();
extern void ISR_TIMER_1_CAPTURE_COMPARE();
extern void ISR_TIMER_2();
extern void ISR_TIMER_3();
extern void ISR_TIMER_4();
extern void ISR_I2C_1_EVENT();
extern void ISR_I2C_1_ERROR();
extern void ISR_I2C_2_EVENT();
extern void ISR_I2C_2_ERROR();
extern void ISR_SPI_1();
extern void ISR_SPI_2();
extern void ISR_USART_1();
extern void ISR_USART_2();
extern void ISR_USART_3();
extern void ISR_EXTI_15_TO_10();
extern void ISR_RTC_ALARM_EXTI();



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline STM32F103C8T6::STM32F103C8T6()
	: m_flash(),
		m_rcc(m_flash),
		m_pwr(),
		m_debug(),
		m_gpio(),
		m_exti(),
		m_rtc(),
		m_timer_1(),
		m_timer_3(),
		m_timer_4(),
		m_dma(),
		m_adc_1(),
		m_usart_1()
{
	
}


inline STM32F103C8T6::~STM32F103C8T6()
{
	
}







inline feedback STM32F103C8T6::startup()
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
	if(m_debug.startup() != OK)
	{
		return(FAIL);
	}
	if(m_gpio.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_afio.startup() != OK)
	{
		return(FAIL);
	}
	if(m_exti.startup() != OK)
	{
		return(FAIL);
	}
	if(m_rtc.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_timer_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_3.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_4.startup() != OK)
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
	if(m_adc_1.startup() != OK)
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

inline STM32F103C8T6& STM32F103C8T6::get()
{
	static STM32F103C8T6 stm32f103c8t6;
	return(stm32f103c8t6);
}







constexpr inline Flash& STM32F103C8T6::get_flash()
{
	return(m_flash);
}


constexpr inline RCC& STM32F103C8T6::get_rcc()
{
	return(m_rcc);
}


constexpr inline Pwr& STM32F103C8T6::get_pwr()
{
	return(m_pwr);
}


constexpr inline Debug& STM32F103C8T6::get_debug()
{
	return(m_debug);
}


constexpr inline GPIO& STM32F103C8T6::get_gpio()
{
	return(m_gpio);
}


constexpr inline AFIO& STM32F103C8T6::get_afio()
{
	return(m_afio);
}


constexpr inline EXTI& STM32F103C8T6::get_exti()
{
	return(m_exti);
}


constexpr inline RTC& STM32F103C8T6::get_rtc()
{
	return(m_rtc);
}


constexpr inline Timer_1& STM32F103C8T6::get_timer_1()
{
	return(m_timer_1);
}


constexpr inline Timer_3& STM32F103C8T6::get_timer_3()
{
	return(m_timer_3);
}


constexpr inline Timer_4& STM32F103C8T6::get_timer_4()
{
	return(m_timer_4);
}


constexpr inline DMA& STM32F103C8T6::get_dma(uint8 channel)
{
	if(channel < DMA::c_channel)
	{
		return(m_dma[channel]);
	}
	DMA& fail = (DMA&) *((DMA*) nullptr);
	return(fail);
}


constexpr inline ADC_1& STM32F103C8T6::get_adc_1()
{
	return(m_adc_1);
}


constexpr inline USART_1& STM32F103C8T6::get_usart_1()
{
	return(m_usart_1);
}