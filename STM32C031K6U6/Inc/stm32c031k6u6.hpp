#pragma once

#include "registers.hpp"
#include "cmos.hpp"

#include "adc.hpp"
#include "dbg.hpp"
#include "pwr.hpp"
#include "flash.hpp"
#include "rcc.hpp"
#include "crc.hpp"
#include "dma.hpp"
#include "dmamux.hpp"
#include "gpio.hpp"
#include "exti.hpp"
#include "timer_17.hpp"
#include "i2c_1.hpp"
#include "usart_1.hpp"
#include "usart_2.hpp"





uint32 __startup__();





class STM32C031K6U6
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
		DMA m_dma[DMA::c_channel];
		DMAMUX m_dmamux;
		ADC m_adc;
		PWR m_pwr;
		DBG m_dbg;
		GPIO m_gpio;
		EXTI m_exti;
		Timer_17 m_timer_17;
		I2C_1 m_i2c_1;
		USART_1 m_usart_1;
		USART_2 m_usart_2;
		
		
		//	Constructor and Destructor
		inline STM32C031K6U6();
		STM32C031K6U6(const STM32C031K6U6& stm32c031k6u6) = delete;
		inline ~STM32C031K6U6();
		
		
		//	Member Functions
		inline feedback startup();
		
		static void copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes);
		static void zeroOutRAM(uint32* startAddress, uint32 sizeInBytes);
		static void preInit();
		
		
		
		//	Friends
		friend void EXCEPTION_RESET();
		friend uint32 __startup__();
		
		
		
		
		
	public:
		
		inline static STM32C031K6U6& get();
		
		
		constexpr inline Flash& get_flash();
		constexpr inline RCC& get_rcc();
		constexpr inline CRC& get_crc();
		constexpr inline DMA& get_dma(uint8 channel);
		constexpr inline DMAMUX& get_dmamux();
		constexpr inline ADC& get_adc();
		constexpr inline PWR& get_pwr();
		constexpr inline DBG& get_dbg();
		constexpr inline GPIO& get_gpio();
		constexpr inline EXTI& get_exti();
		constexpr inline Timer_17& get_timer_17();
		constexpr inline I2C_1& get_i2c_1();
		constexpr inline USART_1& get_usart_1();
		constexpr inline USART_2& get_usart_2();
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
extern void ISR_DMA1_CH0();
extern void ISR_DMA1_CH1_CH2();
extern void ISR_DMAMUX();
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
extern void ISR_USART_2();



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline STM32C031K6U6::STM32C031K6U6()
	: m_flash(),
		m_rcc(m_flash),
		m_crc(),
		m_dma(),
		m_dmamux(),
		m_pwr(),
		m_dbg(),
		m_gpio(),
		m_exti(),
		m_timer_17(m_rcc),
		m_i2c_1(),
		m_usart_1(),
		m_usart_2()
{
	
}


inline STM32C031K6U6::~STM32C031K6U6()
{
	
}







inline feedback STM32C031K6U6::startup()
{
	if(m_rcc.startup() != OK)
	{
		return(FAIL);
	}
	if(m_crc.startup(m_rcc) != OK)
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
	if(m_dmamux.startup() != OK)
	{
		return(FAIL);
	}
	if(m_adc.startup() != OK)
	{
		return(FAIL);
	}
	if(m_pwr.startup(m_rcc) != OK)
	{
		return(FAIL);
	}
	if(m_dbg.startup() != OK)
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
	if(m_timer_17.startup() != OK)
	{
		return(FAIL);
	}
	if(m_i2c_1.startup(m_rcc) != OK)
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
	
	
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline STM32C031K6U6& STM32C031K6U6::get()
{
	static STM32C031K6U6 stm32;
	return(stm32);
}







constexpr inline Flash& STM32C031K6U6::get_flash()
{
	return(m_flash);
}


constexpr inline RCC& STM32C031K6U6::get_rcc()
{
	return(m_rcc);
}


constexpr inline CRC& STM32C031K6U6::get_crc()
{
	return(m_crc);
}


constexpr inline DMA& STM32C031K6U6::get_dma(uint8 channel)
{
	if(channel < DMA::c_channel)
	{
		return(m_dma[channel]);
	}
	DMA& fail = (DMA&) *((DMA*) nullptr);
	return(fail);
}


constexpr inline DMAMUX& STM32C031K6U6::get_dmamux()
{
	return(m_dmamux);
}


constexpr inline ADC& STM32C031K6U6::get_adc()
{
	return(m_adc);
}


constexpr inline PWR& STM32C031K6U6::get_pwr()
{
	return(m_pwr);
}


constexpr inline DBG& STM32C031K6U6::get_dbg()
{
	return(m_dbg);
}


constexpr inline GPIO& STM32C031K6U6::get_gpio()
{
	return(m_gpio);
}


constexpr inline EXTI& STM32C031K6U6::get_exti()
{
	return(m_exti);
}


constexpr inline Timer_17& STM32C031K6U6::get_timer_17()
{
	return(m_timer_17);
}


constexpr inline I2C_1& STM32C031K6U6::get_i2c_1()
{
	return(m_i2c_1);
}


constexpr inline USART_1& STM32C031K6U6::get_usart_1()
{
	return(m_usart_1);
}


constexpr inline USART_2& STM32C031K6U6::get_usart_2()
{
	return(m_usart_2);
}