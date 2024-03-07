#pragma once

#include "registers.hpp"
#include "cmos.hpp"

#include "dbg.hpp"
#include "pwr.hpp"
#include "flash.hpp"
#include "rcc.hpp"
#include "crc.hpp"
#include "gpio.hpp"
#include "timer_17.hpp"
#include "i2c.hpp"





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
		PWR m_pwr;
		DBG m_dbg;
		GPIO m_gpio;
		Timer_17 m_timer_17;
		I2C m_i2c;
		
		
		//	Constructor and Destructor
		inline STM32C031K6U6();
		STM32C031K6U6(const STM32C031K6U6& stm32c031k6u6) = delete;
		inline ~STM32C031K6U6();
		
		
		//	Member Functions
		inline feedback startup();
		
		static void copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes);
		static void zeroOutRAM(uint32* startAddress, uint32 sizeInBytes);
		
		
		
		//	Friends
		friend void EXCEPTION_RESET();
		friend uint32 __startup__();
		
		
		
		
		
	public:
		
		inline static STM32C031K6U6& get();
		
		
		constexpr inline Flash& get_flash();
		constexpr inline RCC& get_rcc();
		constexpr inline CRC& get_crc();
		constexpr inline PWR& get_pwr();
		constexpr inline DBG& get_dbg();
		constexpr inline GPIO& get_gpio();
		constexpr inline Timer_17& get_timer_17();
		constexpr inline I2C& get_i2c();
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
		m_pwr(),
		m_dbg(),
		m_gpio(),
		m_timer_17(m_rcc),
		m_i2c()
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
	if(m_timer_17.startup() != OK)
	{
		return(FAIL);
	}
	if(m_i2c.startup(m_rcc) != OK)
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
	static STM32C031K6U6 stm32f107rct6;
	return(stm32f107rct6);
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


constexpr inline Timer_17& STM32C031K6U6::get_timer_17()
{
	return(m_timer_17);
}


constexpr inline I2C& STM32C031K6U6::get_i2c()
{
	return(m_i2c);
}