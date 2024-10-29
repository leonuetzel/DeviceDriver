#pragma once

#include "registers.hpp"
#include "cmos.hpp"

#include "debug.hpp"
#include "syscfg.hpp"
#include "pwr.hpp"
#include "flash.hpp"
#include "rcc.hpp"
#include "crc.hpp"
#include "gpio.hpp"
#include "exti.hpp"
#include "rtc.hpp"
#include "timer_2.hpp"
#include "dma.hpp"
#include "adc.hpp"
#include "usart_2.hpp"
#include "lpuart1.hpp"
#include "i2c_1.hpp"





uint32 __startup__();





class STM32L010RBT6
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
		CRC m_crc;
		GPIO m_gpio;
		EXTI m_exti;
		RTC m_rtc;
		Timer_2 m_timer_2;
		DMA m_dma[DMA::c_channel];
		ADC m_adc;
		USART_2 m_usart_2;
		LP_UART_1 m_lpuart_1;
		I2C_1 m_i2c_1;
		
		
		//	Constructor and Destructor
		inline STM32L010RBT6();
		STM32L010RBT6(const STM32L010RBT6& stm32l010rbt6) = delete;
		inline ~STM32L010RBT6();
		
		
		//	Member Functions
		inline feedback startup();
		
		static void copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes);
		static void zeroOutRAM(uint32* startAddress, uint32 sizeInBytes);
		
		
		//	Friends
		friend void EXCEPTION_RESET();
		friend uint32 __startup__();
		
		
		
		
		
	public:
		
		static STM32L010RBT6& get();
		
		constexpr inline Flash& get_flash();
		constexpr inline RCC& get_rcc();
		constexpr inline CRC& get_crc();
		constexpr inline PWR& get_pwr();
		constexpr inline Debug& get_debug();
		constexpr inline GPIO& get_gpio();
		constexpr inline EXTI& get_exti();
		constexpr inline RTC& get_rtc();
		constexpr inline Timer_2& get_timer_2();
		constexpr inline DMA& get_dma(uint8 channel);
		constexpr inline ADC& get_adc();
		constexpr inline USART_2& get_usart_2();
		constexpr inline LP_UART_1& get_lpuart_1();
		constexpr inline I2C_1& get_i2c_1();
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
extern void ISR_DMA_CH3_TO_CH6();
extern void ISR_ADC();
extern void ISR_LP_TIMER_1();
extern void ISR_TIMER_2();
extern void ISR_TIMER_21();
extern void ISR_TIMER_22();
extern void ISR_I2C_1();
extern void ISR_SPI_1();
extern void ISR_USART_2();
extern void ISR_LPUART_1();



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline STM32L010RBT6::STM32L010RBT6()
	: m_debug(),
		m_syscfg(),
		m_pwr(),
		m_flash(),
		m_rcc(m_flash),
		m_crc(),
		m_gpio(),
		m_exti(),
		m_rtc(),
		m_timer_2(m_rcc),
		m_dma(),
		m_adc(),
		m_usart_2(),
		m_lpuart_1(),
		m_i2c_1()
{
	
}


inline STM32L010RBT6::~STM32L010RBT6()
{
	
}







inline feedback STM32L010RBT6::startup()
{
	if(m_syscfg.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_pwr.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_flash.startup() != OK)
	{
		return(FAIL);
	}
	if(m_rcc.startup() != OK)
	{
		return(FAIL);
	}
	if(m_crc.startup(m_rcc) != OK)
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
	if(m_timer_2.startup() != OK)
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
	if(m_usart_2.startup() != OK)
	{
		return(FAIL);
	}
	if(m_lpuart_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_i2c_1.startup(m_rcc) != OK)
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

constexpr inline PWR& STM32L010RBT6::get_pwr()
{
	return(m_pwr);
}


constexpr inline Flash& STM32L010RBT6::get_flash()
{
	return(m_flash);
}


constexpr inline RCC& STM32L010RBT6::get_rcc()
{
	return(m_rcc);
}


constexpr inline CRC& STM32L010RBT6::get_crc()
{
	return(m_crc);
}


constexpr inline Debug& STM32L010RBT6::get_debug()
{
	return(m_debug);
}


constexpr inline GPIO& STM32L010RBT6::get_gpio()
{
	return(m_gpio);
}


constexpr inline EXTI& STM32L010RBT6::get_exti()
{
	return(m_exti);
}


constexpr inline RTC& STM32L010RBT6::get_rtc()
{
	return(m_rtc);
}


constexpr inline Timer_2& STM32L010RBT6::get_timer_2()
{
	return(m_timer_2);
}


constexpr inline DMA& STM32L010RBT6::get_dma(uint8 channel)
{
	if(channel < DMA::c_channel)
	{
		return(m_dma[channel]);
	}
	DMA& fail = (DMA&) *((DMA*) nullptr);
	return(fail);
}


constexpr inline ADC& STM32L010RBT6::get_adc()
{
	return(m_adc);
}


constexpr inline USART_2& STM32L010RBT6::get_usart_2()
{
	return(m_usart_2);
}


constexpr inline LP_UART_1& STM32L010RBT6::get_lpuart_1()
{
	return(m_lpuart_1);
}


constexpr inline I2C_1& STM32L010RBT6::get_i2c_1()
{
	return(m_i2c_1);
}