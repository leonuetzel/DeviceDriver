#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "deviceDriverVersion.hpp"
#include "cacheMaintenance.hpp"

#include "debug.hpp"
#include "syscfg.hpp"
#include "pwr.hpp"
#include "flash.hpp"
#include "update.hpp"
#include "rcc.hpp"
#include "watchdog.hpp"
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
extern "C" void __resetHandler__();





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
		
		
		inline STM32H753BIT6();
		STM32H753BIT6(const STM32H753BIT6& stm32h753bit6) = delete;
		inline ~STM32H753BIT6();
		
		
		static void copy_flashToRAM(const uint32* const src, uint32* const dest, uint32 sizeInBytes);
		static void zeroOutRAM(uint32* const startAddress, uint32 sizeInBytes);
		
		friend void EXCEPTION_RESET();
		friend void __resetHandler__();
		friend uint32 __startup__();
		friend class Update;
		
		//	Initializes the Core Drivers, only __startup__ calls it - all other Drivers start with the first Call of their Getter
		feedback startup();


		//	Peripherals besides the Core are created and started at the first Call of their Getter: a Program links, clocks and creates only the
		//	Drivers it uses. startBegin() returns true for exactly one Caller, who starts the Peripheral and then calls startEnd(); a second
		//	Thread that comes meanwhile waits until it is started. The first Call of a Getter must come from a Thread, not from an Interrupt
		static constexpr uint8 c_notStarted						= 0;
		static constexpr uint8 c_starting							= 1;
		static constexpr uint8 c_started							= 2;
		static bool startBegin(volatile uint8& state);
		static inline void startEnd(volatile uint8& state);
		
		
		
		
		
	public:
		
		inline static STM32H753BIT6& get();
		
		
		//	Version of the linked Library - if it differs from DEVICEDRIVER_VERSION_MAJOR/MINOR, Headers and Library do not belong together
		static uint8 get_versionMajor();
		static uint8 get_versionMinor();
		
		
		constexpr inline Debug& get_debug();
		constexpr inline SYSCFG& get_syscfg();
		constexpr inline PWR& get_pwr();
		constexpr inline Flash& get_flash();
		inline Update& get_update();
		constexpr inline RCC& get_rcc();
		constexpr inline BackupSRAM& get_backupSRAM();
		constexpr inline GPIO& get_gpio();
		inline Watchdog& get_watchdog();
		inline HSEM& get_hsem(uint8 number);
		inline RTC& get_rtc();
		
		inline EXTI& get_exti();
		inline VREFBUF& get_vrefbuf();
		
		inline DMA2D& get_dma2d();
		inline MDMA& get_mdma();
		inline DMAMUX& get_dmamux();
		inline DMA_1& get_dma_1(uint8 channel);
		inline DMA_2& get_dma_2(uint8 channel);
		
		inline ADC_1& get_adc_1();
		inline ADC_2& get_adc_2();
		inline ADC_3& get_adc_3();
		
		inline Timer_1& get_timer_1();
		inline Timer_2& get_timer_2();
		inline Timer_3& get_timer_3();
		inline Timer_12& get_timer_12();
		inline Timer_13& get_timer_13();
		inline Timer_15& get_timer_15();
		inline Timer_16& get_timer_16();
		inline Timer_17& get_timer_17();
		
		inline USART_1& get_usart_1();
		inline UART_5& get_uart_5();
		inline UART_7& get_uart_7();
		
		inline FMC& get_fmc();
		inline LTDC& get_ltdc();
		
		inline I2C_1& get_i2c_1();
		inline I2C_2& get_i2c_2();
		
		inline SDMMC_1& get_sdmmc_1();
		inline SDMMC_2& get_sdmmc_2();
		
		inline CAN_1& get_can_1();
		inline CAN_2& get_can_2();
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
		m_pwr(),
		m_flash(),
		m_rcc(),
		m_backupSRAM(),
		m_gpio()
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

inline void STM32H753BIT6::startEnd(volatile uint8& state)
{
	//	The Compiler Barrier keeps the Writes of the Start (Object, Pointer) before the State: a Thread that sees c_started finds them
	asm volatile("" ::: "memory");
	state = c_started;
}


inline STM32H753BIT6& STM32H753BIT6::get()
{
	static STM32H753BIT6 stm32h753bit6;
	return(stm32h753bit6);
}







constexpr inline Debug& STM32H753BIT6::get_debug()
{
	return(m_debug);
}


constexpr inline SYSCFG& STM32H753BIT6::get_syscfg()
{
	return(m_syscfg);
}


constexpr inline PWR& STM32H753BIT6::get_pwr()
{
	return(m_pwr);
}


constexpr inline Flash& STM32H753BIT6::get_flash()
{
	return(m_flash);
}


inline Update& STM32H753BIT6::get_update()
{
	//	No Member: the Update Driver is only linked into Programs that use it
	static Update update;
	return(update);
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


inline Watchdog& STM32H753BIT6::get_watchdog()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver. The Start registers
	//	the Watchdog at CMOS (CMOS::get_watchdog()) but does not start it - a hardware Watchdog (Option Bit) runs from the Reset on
	static volatile uint8 state = c_notStarted;
	static Watchdog* volatile watchdog = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Watchdog instance;
		instance.startup(m_rcc);
		watchdog = &instance;
		startEnd(state);
	}
	return(*watchdog);
}


inline HSEM& STM32H753BIT6::get_hsem(uint8 number)
{
	//	Created and started at the first Call, all at once - for an invalid Number the Replacement Object (the last one): it has no
	//	Hardware, so its Functions return FAIL instead of accessing any Address
	static volatile uint8 state = c_notStarted;
	static HSEM* volatile hsem = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static HSEM instance[HSEM::c_number + 1];
		for(uint32 i = 0; i < HSEM::c_number; i++)
		{
			instance[i].startup(i);
		}
		hsem = instance;
		startEnd(state);
	}
	return(hsem[(number < HSEM::c_number) ? number : HSEM::c_number]);
}


inline RTC& STM32H753BIT6::get_rtc()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static RTC* volatile rtc = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static RTC instance;
		instance.startup();
		rtc = &instance;
		startEnd(state);
	}
	return(*rtc);
}







inline EXTI& STM32H753BIT6::get_exti()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static EXTI* volatile exti = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static EXTI instance;
		instance.startup();
		exti = &instance;
		startEnd(state);
	}
	return(*exti);
}


inline VREFBUF& STM32H753BIT6::get_vrefbuf()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static VREFBUF* volatile vrefbuf = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static VREFBUF instance;
		instance.startup();
		vrefbuf = &instance;
		startEnd(state);
	}
	return(*vrefbuf);
}







inline DMA2D& STM32H753BIT6::get_dma2d()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static DMA2D* volatile dma2d = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static DMA2D instance;
		instance.startup();
		dma2d = &instance;
		startEnd(state);
	}
	return(*dma2d);
}


inline MDMA& STM32H753BIT6::get_mdma()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static MDMA* volatile mdma = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static MDMA instance;
		instance.startup();
		mdma = &instance;
		startEnd(state);
	}
	return(*mdma);
}


inline DMAMUX& STM32H753BIT6::get_dmamux()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static DMAMUX* volatile dmamux = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static DMAMUX instance;
		instance.startup();
		dmamux = &instance;
		startEnd(state);
	}
	return(*dmamux);
}


inline DMA_1& STM32H753BIT6::get_dma_1(uint8 channel)
{
	//	Created and started at the first Call, all at once - for an invalid Number the Replacement Object (the last one): it has no
	//	Hardware, so its Functions return FAIL instead of accessing any Address
	static volatile uint8 state = c_notStarted;
	static DMA_1* volatile dma_1 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static DMA_1 instance[DMA_1::c_channel + 1];
		for(uint32 i = 0; i < DMA_1::c_channel; i++)
		{
			instance[i].startup(i);
		}
		dma_1 = instance;
		startEnd(state);
	}
	return(dma_1[(channel < DMA_1::c_channel) ? channel : DMA_1::c_channel]);
}


inline DMA_2& STM32H753BIT6::get_dma_2(uint8 channel)
{
	//	Created and started at the first Call, all at once - for an invalid Number the Replacement Object (the last one): it has no
	//	Hardware, so its Functions return FAIL instead of accessing any Address
	static volatile uint8 state = c_notStarted;
	static DMA_2* volatile dma_2 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static DMA_2 instance[DMA_2::c_channel + 1];
		for(uint32 i = 0; i < DMA_2::c_channel; i++)
		{
			instance[i].startup(i);
		}
		dma_2 = instance;
		startEnd(state);
	}
	return(dma_2[(channel < DMA_2::c_channel) ? channel : DMA_2::c_channel]);
}







inline ADC_1& STM32H753BIT6::get_adc_1()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static ADC_1* volatile adc_1 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static ADC_1 instance;
		instance.startup();
		adc_1 = &instance;
		startEnd(state);
	}
	return(*adc_1);
}


inline ADC_2& STM32H753BIT6::get_adc_2()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static ADC_2* volatile adc_2 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static ADC_2 instance;
		instance.startup();
		adc_2 = &instance;
		startEnd(state);
	}
	return(*adc_2);
}


inline ADC_3& STM32H753BIT6::get_adc_3()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static ADC_3* volatile adc_3 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static ADC_3 instance;
		instance.startup();
		adc_3 = &instance;
		startEnd(state);
	}
	return(*adc_3);
}







inline Timer_1& STM32H753BIT6::get_timer_1()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static Timer_1* volatile timer_1 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Timer_1 instance;
		instance.startup();
		timer_1 = &instance;
		startEnd(state);
	}
	return(*timer_1);
}


inline Timer_2& STM32H753BIT6::get_timer_2()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static Timer_2* volatile timer_2 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Timer_2 instance;
		instance.startup();
		timer_2 = &instance;
		startEnd(state);
	}
	return(*timer_2);
}


inline Timer_3& STM32H753BIT6::get_timer_3()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static Timer_3* volatile timer_3 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Timer_3 instance;
		instance.startup();
		timer_3 = &instance;
		startEnd(state);
	}
	return(*timer_3);
}


inline Timer_12& STM32H753BIT6::get_timer_12()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static Timer_12* volatile timer_12 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Timer_12 instance;
		instance.startup();
		timer_12 = &instance;
		startEnd(state);
	}
	return(*timer_12);
}


inline Timer_13& STM32H753BIT6::get_timer_13()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static Timer_13* volatile timer_13 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Timer_13 instance;
		instance.startup();
		timer_13 = &instance;
		startEnd(state);
	}
	return(*timer_13);
}


inline Timer_15& STM32H753BIT6::get_timer_15()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static Timer_15* volatile timer_15 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Timer_15 instance;
		instance.startup();
		timer_15 = &instance;
		startEnd(state);
	}
	return(*timer_15);
}


inline Timer_16& STM32H753BIT6::get_timer_16()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static Timer_16* volatile timer_16 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Timer_16 instance;
		instance.startup();
		timer_16 = &instance;
		startEnd(state);
	}
	return(*timer_16);
}


inline Timer_17& STM32H753BIT6::get_timer_17()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static Timer_17* volatile timer_17 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Timer_17 instance;
		instance.startup();
		timer_17 = &instance;
		startEnd(state);
	}
	return(*timer_17);
}







inline USART_1& STM32H753BIT6::get_usart_1()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static USART_1* volatile usart_1 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static USART_1 instance;
		instance.startup();
		usart_1 = &instance;
		startEnd(state);
	}
	return(*usart_1);
}


inline UART_5& STM32H753BIT6::get_uart_5()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static UART_5* volatile uart_5 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static UART_5 instance;
		instance.startup();
		uart_5 = &instance;
		startEnd(state);
	}
	return(*uart_5);
}


inline UART_7& STM32H753BIT6::get_uart_7()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static UART_7* volatile uart_7 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static UART_7 instance;
		instance.startup();
		uart_7 = &instance;
		startEnd(state);
	}
	return(*uart_7);
}







inline FMC& STM32H753BIT6::get_fmc()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static FMC* volatile fmc = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static FMC instance;
		instance.startup();
		fmc = &instance;
		startEnd(state);
	}
	return(*fmc);
}


inline LTDC& STM32H753BIT6::get_ltdc()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static LTDC* volatile ltdc = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static LTDC instance;
		instance.startup();
		ltdc = &instance;
		startEnd(state);
	}
	return(*ltdc);
}







inline I2C_1& STM32H753BIT6::get_i2c_1()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static I2C_1* volatile i2c_1 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static I2C_1 instance;
		instance.startup();
		i2c_1 = &instance;
		startEnd(state);
	}
	return(*i2c_1);
}


inline I2C_2& STM32H753BIT6::get_i2c_2()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static I2C_2* volatile i2c_2 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static I2C_2 instance;
		instance.startup();
		i2c_2 = &instance;
		startEnd(state);
	}
	return(*i2c_2);
}







inline SDMMC_1& STM32H753BIT6::get_sdmmc_1()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static SDMMC_1* volatile sdmmc_1 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static SDMMC_1 instance(get_hsem(17));
		instance.startup();
		sdmmc_1 = &instance;
		startEnd(state);
	}
	return(*sdmmc_1);
}


inline SDMMC_2& STM32H753BIT6::get_sdmmc_2()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static SDMMC_2* volatile sdmmc_2 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static SDMMC_2 instance(get_hsem(18));
		instance.startup();
		sdmmc_2 = &instance;
		startEnd(state);
	}
	return(*sdmmc_2);
}







inline CAN_1& STM32H753BIT6::get_can_1()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static CAN_1* volatile can_1 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static CAN_1 instance;
		instance.startup();
		can_1 = &instance;
		startEnd(state);
	}
	return(*can_1);
}


inline CAN_2& STM32H753BIT6::get_can_2()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static CAN_2* volatile can_2 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static CAN_2 instance;
		instance.startup();
		can_2 = &instance;
		startEnd(state);
	}
	return(*can_2);
}