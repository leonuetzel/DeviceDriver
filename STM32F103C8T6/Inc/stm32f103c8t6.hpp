#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "deviceDriverVersion.hpp"

#include "debug.hpp"
#include "pwr.hpp"
#include "flash.hpp"
#include "update.hpp"
#include "rcc.hpp"
#include "watchdog.hpp"
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
extern "C" void __resetHandler__();





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
		
		
		//	Constructor and Destructor
		inline STM32F103C8T6();
		STM32F103C8T6(const STM32F103C8T6& stm32f103c8t6) = delete;
		inline ~STM32F103C8T6();
		
		
		//	Member Functions
		//	Initializes the Core Drivers, only __startup__ calls it - all other Drivers start with the first Call of their Getter
		inline feedback startup();


		//	Peripherals besides the Core are created and started at the first Call of their Getter: a Program links, clocks and creates only the
		//	Drivers it uses. startBegin() returns true for exactly one Caller, who starts the Peripheral and then calls startEnd(); a second
		//	Thread that comes meanwhile waits until it is started. The first Call of a Getter must come from a Thread, not from an Interrupt
		static constexpr uint8 c_notStarted						= 0;
		static constexpr uint8 c_starting							= 1;
		static constexpr uint8 c_started							= 2;
		static bool startBegin(volatile uint8& state);
		static inline void startEnd(volatile uint8& state);
		
		static void copy_flashToRAM(const uint32* src, uint32* dest, uint32 sizeInBytes);
		static void zeroOutRAM(uint32* startAddress, uint32 sizeInBytes);
		
		
		
		//	Friends
		friend void EXCEPTION_RESET();
		friend void __resetHandler__();
		friend uint32 __startup__();
		friend class Update;
		
		
		
		
		
	public:
		
		inline static STM32F103C8T6& get();
		
		
		//	Version of the linked Library - if it differs from DEVICEDRIVER_VERSION_MAJOR/MINOR, Headers and Library do not belong together
		static uint8 get_versionMajor();
		static uint8 get_versionMinor();
		
		
		constexpr inline Flash& get_flash();
		inline Update& get_update();
		constexpr inline RCC& get_rcc();
		constexpr inline Pwr& get_pwr();
		constexpr inline Debug& get_debug();
		constexpr inline GPIO& get_gpio();
		inline Watchdog& get_watchdog();
		constexpr inline AFIO& get_afio();
		inline EXTI& get_exti();
		inline RTC& get_rtc();
		inline Timer_1& get_timer_1();
		inline Timer_3& get_timer_3();
		inline Timer_4& get_timer_4();
		inline DMA& get_dma(uint8 channel);
		inline ADC_1& get_adc_1();
		inline USART_1& get_usart_1();
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
		m_gpio()
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
	
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void STM32F103C8T6::startEnd(volatile uint8& state)
{
	//	The Compiler Barrier keeps the Writes of the Start (Object, Pointer) before the State: a Thread that sees c_started finds them
	asm volatile("" ::: "memory");
	state = c_started;
}


inline STM32F103C8T6& STM32F103C8T6::get()
{
	static STM32F103C8T6 stm32f103c8t6;
	return(stm32f103c8t6);
}







constexpr inline Flash& STM32F103C8T6::get_flash()
{
	return(m_flash);
}


inline Update& STM32F103C8T6::get_update()
{
	//	No Member: the Update Driver is only linked into Programs that use it
	static Update update;
	return(update);
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


inline Watchdog& STM32F103C8T6::get_watchdog()
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


constexpr inline AFIO& STM32F103C8T6::get_afio()
{
	return(m_afio);
}


inline EXTI& STM32F103C8T6::get_exti()
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


inline RTC& STM32F103C8T6::get_rtc()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static RTC* volatile rtc = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static RTC instance;
		instance.startup(m_rcc);
		rtc = &instance;
		startEnd(state);
	}
	return(*rtc);
}


inline Timer_1& STM32F103C8T6::get_timer_1()
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


inline Timer_3& STM32F103C8T6::get_timer_3()
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


inline Timer_4& STM32F103C8T6::get_timer_4()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static Timer_4* volatile timer_4 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Timer_4 instance;
		instance.startup();
		timer_4 = &instance;
		startEnd(state);
	}
	return(*timer_4);
}


inline DMA& STM32F103C8T6::get_dma(uint8 channel)
{
	//	Created and started at the first Call, all at once - for an invalid Number the Replacement Object (the last one): it has no
	//	Hardware, so its Functions return FAIL instead of accessing any Address
	static volatile uint8 state = c_notStarted;
	static DMA* volatile dma = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static DMA instance[DMA::c_channel + 1];
		for(uint32 i = 0; i < DMA::c_channel; i++)
		{
			instance[i].startup(m_rcc, i);
		}
		dma = instance;
		startEnd(state);
	}
	return(dma[(channel < DMA::c_channel) ? channel : DMA::c_channel]);
}


inline ADC_1& STM32F103C8T6::get_adc_1()
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


inline USART_1& STM32F103C8T6::get_usart_1()
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