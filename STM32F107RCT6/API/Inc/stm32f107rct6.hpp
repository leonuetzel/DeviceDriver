#pragma once

#include "registers.hpp"
#include "cmos.hpp"

#include "debug.hpp"
#include "pwr.hpp"
#include "flash.hpp"
#include "rcc.hpp"
#include "crc.hpp"
#include "gpio.hpp"
#include "rtc.hpp"
#include "afio.hpp"
#include "exti.hpp"
#include "timer_1.hpp"
#include "timer_3.hpp"
#include "timer_4.hpp"
#include "dma_1.hpp"
#include "dma_2.hpp"
#include "adc_1.hpp"
#include "usart_1.hpp"
#include "usart_2.hpp"
#include "usart_3.hpp"
#include "uart_4.hpp"
#include "uart_5.hpp"
#include "i2c_1.hpp"
#include "i2c_2.hpp"
#include "can_1.hpp"
#include "can_2.hpp"
#include "spi_3.hpp"





uint32 __startup__();





class STM32F107RCT6
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
		CRC m_crc;
		PWR m_pwr;
		Debug m_debug;
		GPIO m_gpio;
		AFIO m_afio;
		EXTI m_exti;
		RTC m_rtc;
		Timer_1 m_timer_1;
		Timer_3 m_timer_3;
		Timer_4 m_timer_4;
		DMA_1 m_dma_1[DMA_1::c_channel];
		DMA_2 m_dma_2[DMA_2::c_channel];
		ADC_1 m_adc_1;
		USART_1 m_usart_1;
		USART_2 m_usart_2;
		USART_3 m_usart_3;
		UART_4 m_uart_4;
		UART_5 m_uart_5;
		I2C_1 m_i2c_1;
		I2C_2 m_i2c_2;
		CAN_1 m_can_1;
		CAN_2 m_can_2;
		SPI_3 m_spi_3;
		
		
		//	Constructor and Destructor
		inline STM32F107RCT6();
		STM32F107RCT6(const STM32F107RCT6& stm32f107rct6) = delete;
		inline ~STM32F107RCT6();
		
		
		//	Member Functions
		inline feedback startup();
		
		static void copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes);
		static void zeroOutRAM(uint32* startAddress, uint32 sizeInBytes);
		static void preInit();
		
		
		
		//	Friends
		friend void EXCEPTION_RESET();
		friend uint32 __startup__();
		
		
		
		
		
	public:
		
		inline static STM32F107RCT6& get();
		
		
		constexpr inline Flash& get_flash();
		constexpr inline RCC& get_rcc();
		constexpr inline CRC& get_crc();
		constexpr inline PWR& get_pwr();
		constexpr inline Debug& get_debug();
		constexpr inline GPIO& get_gpio();
		constexpr inline AFIO& get_afio();
		constexpr inline EXTI& get_exti();
		constexpr inline RTC& get_rtc();
		constexpr inline Timer_1& get_timer_1();
		constexpr inline Timer_3& get_timer_3();
		constexpr inline Timer_4& get_timer_4();
		constexpr inline DMA_1& get_dma_1(uint8 channel);
		constexpr inline DMA_2& get_dma_2(uint8 channel);
		constexpr inline ADC_1& get_adc_1();
		constexpr inline USART_1& get_usart_1();
		constexpr inline USART_2& get_usart_2();
		constexpr inline USART_3& get_usart_3();
		constexpr inline UART_4& get_uart_4();
		constexpr inline UART_5& get_uart_5();
		constexpr inline I2C_1& get_i2c_1();
		constexpr inline I2C_2& get_i2c_2();
		constexpr inline CAN_1& get_can_1();
		constexpr inline CAN_2& get_can_2();
		constexpr inline SPI_3& get_spi_3();
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
extern void ISR_DMA1_CH0();
extern void ISR_DMA1_CH1();
extern void ISR_DMA1_CH2();
extern void ISR_DMA1_CH3();
extern void ISR_DMA1_CH4();
extern void ISR_DMA1_CH5();
extern void ISR_DMA1_CH6();
extern void ISR_ADC();
extern void ISR_CAN1_TX();
extern void ISR_CAN1_RX_0();
extern void ISR_CAN1_RX_1();
extern void ISR_CAN1_SCE();
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
extern void ISR_USB_OTG_WAKEUP();
extern void ISR_TIMER_5();
extern void ISR_SPI_3();
extern void ISR_UART_4();
extern void ISR_UART_5();
extern void ISR_TIMER_6();
extern void ISR_TIMER_7();
extern void ISR_DMA2_CH0();
extern void ISR_DMA2_CH1();
extern void ISR_DMA2_CH2();
extern void ISR_DMA2_CH3();
extern void ISR_DMA2_CH4();
extern void ISR_ETHERNET();
extern void ISR_ETHERNET_WAKEUP();
extern void ISR_CAN2_TX();
extern void ISR_CAN2_RX_0();
extern void ISR_CAN2_RX_1();
extern void ISR_CAN2_SCE();
extern void ISR_USB_OTG();




/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline STM32F107RCT6::STM32F107RCT6()
	: m_flash(),
		m_rcc(m_flash),
		m_crc(),
		m_pwr(),
		m_debug(),
		m_gpio(),
		m_exti(),
		m_rtc(),
		m_timer_1(),
		m_timer_3(),
		m_timer_4(),
		m_dma_1(),
		m_adc_1(),
		m_usart_1(),
		m_usart_2(),
		m_usart_3(),
		m_i2c_1(),
		m_i2c_2(),
		m_can_1(),
		m_can_2(),
		m_spi_3()
{
	
}


inline STM32F107RCT6::~STM32F107RCT6()
{
	
}







inline feedback STM32F107RCT6::startup()
{
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
	if(m_uart_4.startup() != OK)
	{
		return(FAIL);
	}
	if(m_uart_5.startup() != OK)
	{
		return(FAIL);
	}
	if(m_i2c_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_i2c_2.startup() != OK)
	{
		return(FAIL);
	}
	if(m_can_1.startup() != OK)
	{
		return(FAIL);
	}
	if(m_can_2.startup() != OK)
	{
		return(FAIL);
	}
	if(m_spi_3.startup() != OK)
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

inline STM32F107RCT6& STM32F107RCT6::get()
{
	static STM32F107RCT6 stm32f107rct6;
	return(stm32f107rct6);
}







constexpr inline Flash& STM32F107RCT6::get_flash()
{
	return(m_flash);
}


constexpr inline RCC& STM32F107RCT6::get_rcc()
{
	return(m_rcc);
}


constexpr inline CRC& STM32F107RCT6::get_crc()
{
	return(m_crc);
}


constexpr inline PWR& STM32F107RCT6::get_pwr()
{
	return(m_pwr);
}


constexpr inline Debug& STM32F107RCT6::get_debug()
{
	return(m_debug);
}


constexpr inline GPIO& STM32F107RCT6::get_gpio()
{
	return(m_gpio);
}


constexpr inline AFIO& STM32F107RCT6::get_afio()
{
	return(m_afio);
}


constexpr inline EXTI& STM32F107RCT6::get_exti()
{
	return(m_exti);
}


constexpr inline RTC& STM32F107RCT6::get_rtc()
{
	return(m_rtc);
}


constexpr inline Timer_1& STM32F107RCT6::get_timer_1()
{
	return(m_timer_1);
}


constexpr inline Timer_3& STM32F107RCT6::get_timer_3()
{
	return(m_timer_3);
}


constexpr inline Timer_4& STM32F107RCT6::get_timer_4()
{
	return(m_timer_4);
}


constexpr inline DMA_1& STM32F107RCT6::get_dma_1(uint8 channel)
{
	if(channel < DMA_1::c_channel)
	{
		return(m_dma_1[channel]);
	}
	DMA_1& fail = (DMA_1&) *((DMA_1*) nullptr);
	return(fail);
}


constexpr inline DMA_2& STM32F107RCT6::get_dma_2(uint8 channel)
{
	if(channel < DMA_2::c_channel)
	{
		return(m_dma_2[channel]);
	}
	DMA_2& fail = (DMA_2&) *((DMA_2*) nullptr);
	return(fail);
}


constexpr inline ADC_1& STM32F107RCT6::get_adc_1()
{
	return(m_adc_1);
}


constexpr inline USART_1& STM32F107RCT6::get_usart_1()
{
	return(m_usart_1);
}


constexpr inline USART_2& STM32F107RCT6::get_usart_2()
{
	return(m_usart_2);
}


constexpr inline USART_3& STM32F107RCT6::get_usart_3()
{
	return(m_usart_3);
}


constexpr inline UART_4& STM32F107RCT6::get_uart_4()
{
	return(m_uart_4);
}


constexpr inline UART_5& STM32F107RCT6::get_uart_5()
{
	return(m_uart_5);
}


constexpr inline I2C_1& STM32F107RCT6::get_i2c_1()
{
	return(m_i2c_1);
}


constexpr inline I2C_2& STM32F107RCT6::get_i2c_2()
{
	return(m_i2c_2);
}


constexpr inline CAN_1& STM32F107RCT6::get_can_1()
{
	return(m_can_1);
}


constexpr inline CAN_2& STM32F107RCT6::get_can_2()
{
	return(m_can_2);
}


constexpr inline SPI_3& STM32F107RCT6::get_spi_3()
{
	return(m_spi_3);
}