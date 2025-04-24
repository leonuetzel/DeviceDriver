#pragma once

#include "registers.hpp"
#include "cmos.hpp"

#include "adc_1.hpp"
#include "dbg.hpp"
#include "crc.hpp"
#include "dma_1.hpp"
#include "dma_2.hpp"
#include "exti.hpp"
#include "flash.hpp"
#include "gpio.hpp"
#include "i2c_1.hpp"
#include "i2c_2.hpp"
#include "i2c_3.hpp"
#include "i2c_4.hpp"
#include "pwr.hpp"
#include "rcc.hpp"
#include "syscfg.hpp"
#include "timer_2.hpp"
#include "timer_3.hpp"
#include "usart_1.hpp"
#include "usart_2.hpp"
#include "usart_3.hpp"
#include "can_1.hpp"





uint32 __startup__();





class STM32L451RET6
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
		DBG m_dbg;
		SYSCFG m_syscfg;
		PWR m_pwr;
		Flash m_flash;
		RCC m_rcc;
		CRC m_crc;
		GPIO m_gpio;
		EXTI m_exti;
		//RTC m_rtc;
		//Timer_2 m_timer_2;
		DMA_1 m_dma_1[DMA_1::c_channel];
		DMA_2 m_dma_2[DMA_2::c_channel];
		ADC_1 m_adc_1;
		I2C_1 m_i2c_1;
		I2C_2 m_i2c_2;
		I2C_3 m_i2c_3;
		I2C_4 m_i2c_4;
		USART_1 m_usart_1;
		USART_2 m_usart_2;
		USART_3 m_usart_3;
		Timer_2 m_timer_2;
		Timer_3 m_timer_3;
		CAN_1 m_can_1;
		//LP_UART_1 m_lpuart_1;
		//I2C_1 m_i2c_1;
		
		
		//	Constructor and Destructor
		inline STM32L451RET6();
		STM32L451RET6(const STM32L451RET6& stm32l010rbt6) = delete;
		inline ~STM32L451RET6();
		
		
		//	Member Functions
		inline feedback startup();
		
		static void copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes);
		static void zeroOutRAM(uint32* startAddress, uint32 sizeInBytes);
		static void preInit();
		
		
		//	Friends
		friend void EXCEPTION_RESET();
		friend uint32 __startup__();
		
		
		
		
		
	public:
		
		static STM32L451RET6& get();
		
		constexpr inline DBG& get_dbg();
		constexpr inline SYSCFG& get_syscfg();
		constexpr inline Flash& get_flash();
		constexpr inline RCC& get_rcc();
		constexpr inline CRC& get_crc();
		constexpr inline PWR& get_pwr();
		constexpr inline GPIO& get_gpio();
		constexpr inline EXTI& get_exti();
		//constexpr inline RTC& get_rtc();
		//constexpr inline Timer_2& get_timer_2();
		constexpr inline DMA_1& get_dma_1(uint8 channel);
		constexpr inline DMA_2& get_dma_2(uint8 channel);
		constexpr inline ADC_1& get_adc_1();
		constexpr inline I2C_1& get_i2c_1();
		constexpr inline I2C_2& get_i2c_2();
		constexpr inline I2C_3& get_i2c_3();
		constexpr inline I2C_4& get_i2c_4();
		constexpr inline USART_1& get_usart_1();
		constexpr inline USART_2& get_usart_2();
		constexpr inline USART_3& get_usart_3();
		constexpr inline Timer_2& get_timer_2();
		constexpr inline Timer_3& get_timer_3();
		constexpr inline CAN_1& get_can_1();
		//constexpr inline LP_UART_1& get_lpuart_1();
		//constexpr inline I2C_1& get_i2c_1();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

extern void ISR_WWDG();
extern void ISR_PVM();
extern void ISR_RTC_TAMPER_STAMP_CSS_LSE();
extern void ISR_WKUP();
extern void ISR_FLASH();
extern void ISR_RCC();
extern void ISR_EXTI_0();
extern void ISR_EXTI_1();
extern void ISR_EXTI_2();
extern void ISR_EXTI_3();
extern void ISR_EXTI_4();
extern void ISR_DMA_1_CH0();
extern void ISR_DMA_1_CH1();
extern void ISR_DMA_1_CH2();
extern void ISR_DMA_1_CH3();
extern void ISR_DMA_1_CH4();
extern void ISR_DMA_1_CH5();
extern void ISR_DMA_1_CH6();
extern void ISR_ADC_1_2();
extern void ISR_CAN_1_TX();
extern void ISR_CAN_1_RX0();
extern void ISR_CAN_1_RX1();
extern void ISR_CAN_1_SCE();
extern void ISR_EXTI_9_TO_5();
extern void ISR_TIMER_1_BREAK_TIMER_15();
extern void ISR_TIMER_1_UPDATE_TIMER_16();
extern void ISR_TIMER_1_TRIGGER_COMMUTATION();
extern void ISR_TIMER_1_CAPTURE_COMPARE();
extern void ISR_TIMER_2();
extern void ISR_TIMER_3();
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
extern void ISR_RTC_ALARM();
extern void ISR_SDMMC_1();
extern void ISR_SPI_3();
extern void ISR_UART_4();
extern void ISR_TIMER_6_DAC_UNDERRUN();
extern void ISR_DMA_2_CH0();
extern void ISR_DMA_2_CH1();
extern void ISR_DMA_2_CH2();
extern void ISR_DMA_2_CH3();
extern void ISR_DMA_2_CH4();
extern void ISR_DFSDM_1_FLT_0();
extern void ISR_DFSDM_1_FLT_1();
extern void ISR_COMP();
extern void ISR_LP_TIMER_1();
extern void ISR_LP_TIMER_2();
extern void ISR_DMA_2_CH5();
extern void ISR_DMA_2_CH6();
extern void ISR_LPUART_1();
extern void ISR_QUADSPI();
extern void ISR_I2C_3_EVENT();
extern void ISR_I2C_3_ERROR();
extern void ISR_SAI_1();
extern void ISR_TSC();
extern void ISR_RNG();
extern void ISR_FPU();
extern void ISR_CRS();
extern void ISR_I2C_4_EVENT();
extern void ISR_I2C_4_ERROR();



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline STM32L451RET6::STM32L451RET6()
	: m_dbg(),
		m_syscfg(),
		m_pwr(),
		m_flash(),
		m_rcc(),
		m_crc(),
		m_gpio(),
		m_exti(),
		//m_rtc(),
		//m_timer_2(m_rcc),
		m_dma_1(),
		m_dma_2(),
		m_adc_1(),
		m_i2c_1(),
		m_i2c_2(),
		m_i2c_3(),
		m_i2c_4(),
		m_usart_1(),
		m_usart_2(),
		m_usart_3(),
		m_timer_2(m_rcc),
		m_timer_3(m_rcc),
		m_can_1()
		//m_lpuart_1(),
		//m_i2c_1()
{
	
}


inline STM32L451RET6::~STM32L451RET6()
{
	
}







inline feedback STM32L451RET6::startup()
{
	if(m_dbg.startup() != OK)
	{
		return(FAIL);
	}
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
	if(m_gpio.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_exti.startup() != OK)
	{
		return(FAIL);
	}/*
	if(m_rtc.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_2.startup() != OK)
	{
		return(FAIL);
	}*/
	for(uint32 i = 0; i < DMA_1::c_channel; i++)
	{
		if(m_dma_1[i].startup(m_rcc, i) != OK)
		{
			return(FAIL);
		}
	}
	for(uint32 i = 0; i < DMA_2::c_channel; i++)
	{
		if(m_dma_2[i].startup(m_rcc, i) != OK)
		{
			return(FAIL);
		}
	}
	if(m_adc_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_i2c_1.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_i2c_2.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_i2c_3.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_i2c_4.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_usart_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_usart_2.startup() != OK)
	{
		return(FAIL);
	}
	if(m_usart_3.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_2.startup() != OK)
	{
		return(FAIL);
	}
	if(m_timer_3.startup() != OK)
	{
		return(FAIL);
	}
	if(m_can_1.startup() != OK)
	{
		return(FAIL);
	}
	/*
	if(m_lpuart_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_i2c_1.startup(m_rcc) != OK)
	{
		return(FAIL);
	}*/
	
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/


constexpr inline DBG& STM32L451RET6::get_dbg()
{
	return(m_dbg);
}


constexpr inline SYSCFG& STM32L451RET6::get_syscfg()
{
	return(m_syscfg);
}


constexpr inline PWR& STM32L451RET6::get_pwr()
{
	return(m_pwr);
}


constexpr inline Flash& STM32L451RET6::get_flash()
{
	return(m_flash);
}


constexpr inline RCC& STM32L451RET6::get_rcc()
{
	return(m_rcc);
}


constexpr inline CRC& STM32L451RET6::get_crc()
{
	return(m_crc);
}


constexpr inline GPIO& STM32L451RET6::get_gpio()
{
	return(m_gpio);
}


constexpr inline EXTI& STM32L451RET6::get_exti()
{
	return(m_exti);
}

/*
constexpr inline RTC& STM32L451RET6::get_rtc()
{
	return(m_rtc);
}


constexpr inline Timer_2& STM32L451RET6::get_timer_2()
{
	return(m_timer_2);
}

*/
constexpr inline DMA_1& STM32L451RET6::get_dma_1(uint8 channel)
{
	if(channel < DMA_1::c_channel)
	{
		return(m_dma_1[channel]);
	}
	DMA_1& fail = (DMA_1&) *((DMA_1*) nullptr);
	return(fail);
}


constexpr inline DMA_2& STM32L451RET6::get_dma_2(uint8 channel)
{
	if(channel < DMA_2::c_channel)
	{
		return(m_dma_2[channel]);
	}
	DMA_2& fail = (DMA_2&) *((DMA_2*) nullptr);
	return(fail);
}


constexpr inline ADC_1& STM32L451RET6::get_adc_1()
{
	return(m_adc_1);
}


constexpr inline I2C_1& STM32L451RET6::get_i2c_1()
{
	return(m_i2c_1);
}


constexpr inline I2C_2& STM32L451RET6::get_i2c_2()
{
	return(m_i2c_2);
}


constexpr inline I2C_3& STM32L451RET6::get_i2c_3()
{
	return(m_i2c_3);
}


constexpr inline I2C_4& STM32L451RET6::get_i2c_4()
{
	return(m_i2c_4);
}


constexpr inline USART_1& STM32L451RET6::get_usart_1()
{
	return(m_usart_1);
}


constexpr inline USART_2& STM32L451RET6::get_usart_2()
{
	return(m_usart_2);
}


constexpr inline USART_3& STM32L451RET6::get_usart_3()
{
	return(m_usart_3);
}


constexpr inline Timer_2& STM32L451RET6::get_timer_2()
{
	return(m_timer_2);
}


constexpr inline Timer_3& STM32L451RET6::get_timer_3()
{
	return(m_timer_3);
}


constexpr inline CAN_1& STM32L451RET6::get_can_1()
{
	return(m_can_1);
}


/*
constexpr inline LP_UART_1& STM32L451RET6::get_lpuart_1()
{
	return(m_lpuart_1);
}


constexpr inline I2C_1& STM32L451RET6::get_i2c_1()
{
	return(m_i2c_1);
}*/