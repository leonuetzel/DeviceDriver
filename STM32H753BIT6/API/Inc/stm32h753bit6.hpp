#pragma once

#include "registers.hpp"
#include "cmos.hpp"

#include "debug.hpp"
#include "syscfg.hpp"
#include "pwr.hpp"
#include "flash.hpp"
#include "rcc.hpp"
#include "backupSRAM.hpp"
#include "gpio.hpp"
#include "hsem.hpp"
#include "rtc.hpp"

#include "exti.hpp"
#include "vrefbuf.hpp"

#include "dma2d.hpp"
#include "mdma.hpp"
#include "dmamux.hpp"
#include "dma_1.hpp"
#include "dma_2.hpp"

#include "adc_1.hpp"
#include "adc_2.hpp"
#include "adc_3.hpp"

#include "timer_1.hpp"
#include "timer_2.hpp"
#include "timer_3.hpp"
#include "timer_12.hpp"
#include "timer_13.hpp"
#include "timer_15.hpp"
#include "timer_16.hpp"
#include "timer_17.hpp"

#include "usart_1.hpp"
#include "uart_5.hpp"
#include "uart_7.hpp"

#include "fmc.hpp"
#include "ltdc.hpp"

#include "i2c_1.hpp"
#include "i2c_2.hpp"

#include "sdmmc_1.hpp"
#include "sdmmc_2.hpp"

#include "can_1.hpp"
#include "can_2.hpp"





uint32 __startup__();





class STM32H753BIT6
{
	public:
		
		
		
		
		
		
		
	private:
		
		typedef struct
		{
			uint32 vector[NVIC::c_numberOfInterrupts];
		}s_interruptTable;
		
		static const s_interruptTable c_interruptTable;
		
		Debug m_debug;
		SYSCFG m_syscfg;
		PWR m_pwr;
		Flash m_flash;
		RCC m_rcc;
		BackupSRAM m_backupSRAM;
		GPIO m_gpio;
		HSEM m_hsem[HSEM::c_number];
		RTC m_rtc;
		
		EXTI m_exti;
		VREFBUF m_vrefbuf;
		
		DMA2D m_dma2d;
		MDMA m_mdma;
		DMAMUX m_dmamux;
		DMA_1 m_dma_1[DMA_1::c_channel];
		DMA_2 m_dma_2[DMA_2::c_channel];
		
		ADC_1 m_adc_1;
		ADC_2 m_adc_2;
		ADC_3 m_adc_3;
		
		Timer_1 m_timer_1;
		Timer_2 m_timer_2;
		Timer_3 m_timer_3;
		Timer_12 m_timer_12;
		Timer_13 m_timer_13;
		Timer_15 m_timer_15;
		Timer_16 m_timer_16;
		Timer_17 m_timer_17;
		
		USART_1 m_usart_1;
		UART_5 m_uart_5;
		UART_7 m_uart_7;
		
		FMC m_fmc;
		LTDC m_ltdc;
		
		I2C_1 m_i2c_1;
		I2C_2 m_i2c_2;
		
		SDMMC_1 m_sdmmc_1;
		SDMMC_2 m_sdmmc_2;
		
		CAN_1 m_can_1;
		CAN_2 m_can_2;
		
		
		inline STM32H753BIT6();
		STM32H753BIT6(const STM32H753BIT6& stm32h753bit6) = delete;
		inline ~STM32H753BIT6();
		
		
		static void copy_flashToRAM(const uint32* const src, uint32* const dest, uint32 sizeInBytes);
		static void zeroOutRAM(uint32* const startAddress, uint32 sizeInBytes);
		
		friend void EXCEPTION_RESET();
		
		
		
		
		
	public:
		
		inline static STM32H753BIT6& get();
		feedback startup();
		
		
		constexpr inline Debug& get_debug();
		constexpr inline PWR& get_pwr();
		constexpr inline Flash& get_flash();
		constexpr inline RCC& get_rcc();
		constexpr inline BackupSRAM& get_backupSRAM();
		constexpr inline GPIO& get_gpio();
		constexpr inline HSEM& get_hsem(uint8 number);
		constexpr inline RTC& get_rtc();
		
		constexpr inline EXTI& get_exti();
		constexpr inline VREFBUF& get_vrefbuf();
		
		constexpr inline DMA2D& get_dma2d();
		constexpr inline MDMA& get_mdma();
		constexpr inline DMAMUX& get_dmamux();
		constexpr inline DMA_1& get_dma_1(uint8 channel);
		constexpr inline DMA_2& get_dma_2(uint8 channel);
		
		constexpr inline ADC_1& get_adc_1();
		constexpr inline ADC_2& get_adc_2();
		constexpr inline ADC_3& get_adc_3();
		
		constexpr inline Timer_1& get_timer_1();
		constexpr inline Timer_2& get_timer_2();
		constexpr inline Timer_3& get_timer_3();
		constexpr inline Timer_12& get_timer_12();
		constexpr inline Timer_13& get_timer_13();
		constexpr inline Timer_15& get_timer_15();
		constexpr inline Timer_16& get_timer_16();
		constexpr inline Timer_17& get_timer_17();
		
		constexpr inline USART_1& get_usart_1();
		constexpr inline UART_5& get_uart_5();
		constexpr inline UART_7& get_uart_7();
		
		constexpr inline FMC& get_fmc();
		constexpr inline LTDC& get_ltdc();
		
		constexpr inline I2C_1& get_i2c_1();
		constexpr inline I2C_2& get_i2c_2();
		
		constexpr inline SDMMC_1& get_sdmmc_1();
		constexpr inline SDMMC_2& get_sdmmc_2();
		
		constexpr inline CAN_1& get_can_1();
		constexpr inline CAN_2& get_can_2();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

extern void ISR_WWDG();
extern void ISR_PVD_PVM();
extern void ISR_RTC_TAMPER_CSSLSE();
extern void ISR_RTC_WAKEUP();
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
extern void ISR_FDCAN_1_INT0();
extern void ISR_FDCAN_2_INT0();
extern void ISR_FDCAN_1_INT1();
extern void ISR_FDCAN_2_INT1();
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
extern void ISR_TIMER_8_BREAK_AND_TIMER_12();
extern void ISR_TIMER_8_UPDATE_AND_TIMER_13();
extern void ISR_TIMER_8_TRIGGER_COMMUTATION_AND_TIMER_14();
extern void ISR_TIMER_8_CAPTURE_COMPARE();
extern void ISR_DMA_1_CH7();
extern void ISR_FMC();
extern void ISR_SDMMC_1();
extern void ISR_TIMER_5();
extern void ISR_SPI_3();
extern void ISR_UART_4();
extern void ISR_UART_5();
extern void ISR_TIMER_6_AND_DAC();
extern void ISR_TIMER_7();
extern void ISR_DMA_2_CH0();
extern void ISR_DMA_2_CH1();
extern void ISR_DMA_2_CH2();
extern void ISR_DMA_2_CH3();
extern void ISR_DMA_2_CH4();
extern void ISR_ETHERNET();
extern void ISR_ETHERNET_WAKEUP();
extern void ISR_FDCAN_CALIBRATION();
extern void ISR_ARM_CORTEX_M7_SEND_EVEN();
extern void ISR_DMA_2_CH5();
extern void ISR_DMA_2_CH6();
extern void ISR_DMA_2_CH7();
extern void ISR_USART_6();
extern void ISR_I2C_3_EVENT();
extern void ISR_I2C_3_ERROR();
extern void ISR_USB_HS_EP1_OUT();
extern void ISR_USB_HS_EP1_IN();
extern void ISR_USB_HS_WAKEUP();
extern void ISR_USB_HS();
extern void ISR_DCMI();
extern void ISR_CRYPTO();
extern void ISR_HASH_RNG();
extern void ISR_FPU();
extern void ISR_UART_7();
extern void ISR_UART_8();
extern void ISR_SPI_4();
extern void ISR_SPI_5();
extern void ISR_SPI_6();
extern void ISR_SAI_1();
extern void ISR_LTDC();
extern void ISR_LTDC_ERROR();
extern void ISR_DMA2D();
extern void ISR_SAI_2();
extern void ISR_QUADSPI();
extern void ISR_LP_TIMER_1();
extern void ISR_HDMI_CEC();
extern void ISR_I2C_4_EVENT();
extern void ISR_I2C_4_ERROR();
extern void ISR_SPDIF();
extern void ISR_USB_FS_EP1_OUT();
extern void ISR_USB_FS_EP1_IN();
extern void ISR_USB_FS_WAKEUP();
extern void ISR_USB_FS();
extern void ISR_DMAMUX_1_OVERRUN();
extern void ISR_HR_TIMER_MASTER();
extern void ISR_HR_TIMER_A();
extern void ISR_HR_TIMER_B();
extern void ISR_HR_TIMER_C();
extern void ISR_HR_TIMER_D();
extern void ISR_HR_TIMER_E();
extern void ISR_HR_TIMER_FAULT();
extern void ISR_DFSDM_FILTER_0();
extern void ISR_DFSDM_FILTER_1();
extern void ISR_DFSDM_FILTER_2();
extern void ISR_DFSDM_FILTER_3();
extern void ISR_SAI_3();
extern void ISR_SWPMI();
extern void ISR_TIMER_15();
extern void ISR_TIMER_16();
extern void ISR_TIMER_17();
extern void ISR_MDIOS_WAKEUP();
extern void ISR_MDIOS();
extern void ISR_JPEG();
extern void ISR_MDMA();
extern void ISR_SDMMC_2();
extern void ISR_HSEM();
extern void ISR_ADC_3();
extern void ISR_DMAMUX_2_OVERRUN();
extern void ISR_BDMA_CH0();
extern void ISR_BDMA_CH1();
extern void ISR_BDMA_CH2();
extern void ISR_BDMA_CH3();
extern void ISR_BDMA_CH4();
extern void ISR_BDMA_CH5();
extern void ISR_BDMA_CH6();
extern void ISR_BDMA_CH7();
extern void ISR_COMP_1_2();
extern void ISR_LP_TIMER_2();
extern void ISR_LP_TIMER_3();
extern void ISR_LP_TIMER_4();
extern void ISR_LP_TIMER_5();
extern void ISR_LP_UART();
extern void ISR_WWDG_RESET();
extern void ISR_CRS();
extern void ISR_RAM_ECC();
extern void ISR_SAI_4();
extern void ISR_WAKEUP_PIN_0_TO_5();




/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline STM32H753BIT6::STM32H753BIT6()
	: m_debug(),
		m_syscfg(),
		m_pwr(m_syscfg),
		m_flash(),
		m_rcc(m_pwr, m_flash),
		m_backupSRAM(m_rcc),
		m_gpio(),
		m_hsem(),
		m_rtc(m_rcc),
		
		m_exti(),
		m_vrefbuf(m_rcc),
		
		m_dma2d(m_hsem[16]),
		m_mdma(),
		m_dmamux(),
		m_dma_1(),
		m_dma_2(),
		
		m_adc_1(),
		m_adc_2(),
		m_adc_3(),
		
		m_timer_1(m_rcc),
		m_timer_2(m_rcc),
		m_timer_3(m_rcc),
		m_timer_12(m_rcc),
		m_timer_13(m_rcc),
		m_timer_15(m_rcc),
		m_timer_16(m_rcc),
		m_timer_17(m_rcc),
		
		m_usart_1(),
		m_uart_5(),
		m_uart_7(),
		
		m_fmc(m_rcc),
		m_ltdc(),
		
		m_i2c_1(),
		m_i2c_2(),
		
		m_sdmmc_1(m_hsem[17]),
		m_sdmmc_2(m_hsem[18]),
		
		m_can_1(),
		m_can_2()
{
	
}


inline STM32H753BIT6::~STM32H753BIT6()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline STM32H753BIT6& STM32H753BIT6::get()
{
	static STM32H753BIT6 stm32h753bit6;
	return(stm32h753bit6);
}







constexpr inline Debug& STM32H753BIT6::get_debug()
{
	return(m_debug);
}


constexpr inline PWR& STM32H753BIT6::get_pwr()
{
	return(m_pwr);
}


constexpr inline Flash& STM32H753BIT6::get_flash()
{
	return(m_flash);
}


constexpr inline RCC& STM32H753BIT6::get_rcc()
{
	return(m_rcc);
}


constexpr inline BackupSRAM& STM32H753BIT6::get_backupSRAM()
{
	return(m_backupSRAM);
}


constexpr inline GPIO& STM32H753BIT6::get_gpio()
{
	return(m_gpio);
}


constexpr inline HSEM& STM32H753BIT6::get_hsem(uint8 number)
{
	if(number < HSEM::c_number)
	{
		return(m_hsem[number]);
	}
	HSEM& fail = (HSEM&) *((HSEM*) nullptr);
	return(fail);
}


constexpr inline RTC& STM32H753BIT6::get_rtc()
{
	return(m_rtc);
}







constexpr inline EXTI& STM32H753BIT6::get_exti()
{
	return(m_exti);
}


constexpr inline VREFBUF& STM32H753BIT6::get_vrefbuf()
{
	return(m_vrefbuf);
}







constexpr inline DMA2D& STM32H753BIT6::get_dma2d()
{
	return(m_dma2d);
}


constexpr inline MDMA& STM32H753BIT6::get_mdma()
{
	return(m_mdma);
}


constexpr inline DMAMUX& STM32H753BIT6::get_dmamux()
{
	return(m_dmamux);
}


constexpr inline DMA_1& STM32H753BIT6::get_dma_1(uint8 channel)
{
	if(channel < DMA_1::c_channel)
	{
		return(m_dma_1[channel]);
	}
	DMA_1& fail = (DMA_1&) *((DMA_1*) nullptr);
	return(fail);
}


constexpr inline DMA_2& STM32H753BIT6::get_dma_2(uint8 channel)
{
	if(channel < DMA_2::c_channel)
	{
		return(m_dma_2[channel]);
	}
	DMA_2& fail = (DMA_2&) *((DMA_2*) nullptr);
	return(fail);
}







constexpr inline ADC_1& STM32H753BIT6::get_adc_1()
{
	return(m_adc_1);
}


constexpr inline ADC_2& STM32H753BIT6::get_adc_2()
{
	return(m_adc_2);
}


constexpr inline ADC_3& STM32H753BIT6::get_adc_3()
{
	return(m_adc_3);
}







constexpr inline Timer_1& STM32H753BIT6::get_timer_1()
{
	return(m_timer_1);
}


constexpr inline Timer_2& STM32H753BIT6::get_timer_2()
{
	return(m_timer_2);
}


constexpr inline Timer_3& STM32H753BIT6::get_timer_3()
{
	return(m_timer_3);
}


constexpr inline Timer_12& STM32H753BIT6::get_timer_12()
{
	return(m_timer_12);
}


constexpr inline Timer_13& STM32H753BIT6::get_timer_13()
{
	return(m_timer_13);
}


constexpr inline Timer_15& STM32H753BIT6::get_timer_15()
{
	return(m_timer_15);
}


constexpr inline Timer_16& STM32H753BIT6::get_timer_16()
{
	return(m_timer_16);
}


constexpr inline Timer_17& STM32H753BIT6::get_timer_17()
{
	return(m_timer_17);
}







constexpr inline USART_1& STM32H753BIT6::get_usart_1()
{
	return(m_usart_1);
}


constexpr inline UART_5& STM32H753BIT6::get_uart_5()
{
	return(m_uart_5);
}


constexpr inline UART_7& STM32H753BIT6::get_uart_7()
{
	return(m_uart_7);
}







constexpr inline FMC& STM32H753BIT6::get_fmc()
{
	return(m_fmc);
}


constexpr inline LTDC& STM32H753BIT6::get_ltdc()
{
	return(m_ltdc);
}







constexpr inline I2C_1& STM32H753BIT6::get_i2c_1()
{
	return(m_i2c_1);
}


constexpr inline I2C_2& STM32H753BIT6::get_i2c_2()
{
	return(m_i2c_2);
}







constexpr inline SDMMC_1& STM32H753BIT6::get_sdmmc_1()
{
	return(m_sdmmc_1);
}


constexpr inline SDMMC_2& STM32H753BIT6::get_sdmmc_2()
{
	return(m_sdmmc_2);
}







constexpr inline CAN_1& STM32H753BIT6::get_can_1()
{
	return(m_can_1);
}


constexpr inline CAN_2& STM32H753BIT6::get_can_2()
{
	return(m_can_2);
}