#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "deviceDriverVersion.hpp"

#include "adc.hpp"
#include "dbg.hpp"
#include "pwr.hpp"
#include "flash.hpp"
#include "update.hpp"
#include "rcc.hpp"
#include "watchdog.hpp"
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
extern "C" void __resetHandler__();





class STM32C071KBU6
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
		PWR m_pwr;
		DBG m_dbg;
		GPIO m_gpio;
		
		
		//	Constructor and Destructor
		inline STM32C071KBU6();
		STM32C071KBU6(const STM32C071KBU6& stm32c071kbu6) = delete;
		inline ~STM32C071KBU6();
		
		
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
		static void preInit();
		
		
		
		//	Friends
		friend void EXCEPTION_RESET();
		friend void __resetHandler__();
		friend uint32 __startup__();
		friend class Update;
		
		
		
		
		
	public:
		
		inline static STM32C071KBU6& get();
		
		
		//	Version of the linked Library - if it differs from DEVICEDRIVER_VERSION_MAJOR/MINOR, Headers and Library do not belong together
		static uint8 get_versionMajor();
		static uint8 get_versionMinor();
		
		
		constexpr inline Flash& get_flash();
		inline Update& get_update();
		constexpr inline RCC& get_rcc();
		inline CRC& get_crc();
		inline DMA& get_dma(uint8 channel);
		inline DMAMUX& get_dmamux();
		inline ADC& get_adc();
		constexpr inline PWR& get_pwr();
		constexpr inline DBG& get_dbg();
		constexpr inline GPIO& get_gpio();
		inline Watchdog& get_watchdog();
		inline EXTI& get_exti();
		inline Timer_17& get_timer_17();
		inline I2C_1& get_i2c_1();
		inline USART_1& get_usart_1();
		inline USART_2& get_usart_2();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

extern void ISR_WWDG();
extern void ISR_RTC();
extern void ISR_FLASH();
extern void ISR_RCC_CRS();
extern void ISR_EXTI_0_TO_1();
extern void ISR_EXTI_2_TO_3();
extern void ISR_EXTI_4_TO_15();
extern void ISR_USB();
extern void ISR_DMA1_CH0();
extern void ISR_DMA1_CH1_CH2();
extern void ISR_DMA1_CH3_CH4_DMAMUX();
extern void ISR_ADC();
extern void ISR_TIMER_1_BREAK_UPDATE_TRIGGER_COMMUTATION();
extern void ISR_TIMER_1_CAPTURE_COMPARE();
extern void ISR_TIMER_2();
extern void ISR_TIMER_3();
extern void ISR_TIMER_14();
extern void ISR_TIMER_16();
extern void ISR_TIMER_17();
extern void ISR_I2C_1();
extern void ISR_I2C_2();
extern void ISR_SPI_1();
extern void ISR_SPI_2();
extern void ISR_USART_1();
extern void ISR_USART_2();



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline STM32C071KBU6::STM32C071KBU6()
	: m_flash(),
		m_rcc(m_flash),
		m_pwr(),
		m_dbg(),
		m_gpio()
{
	
}


inline STM32C071KBU6::~STM32C071KBU6()
{
	
}







inline feedback STM32C071KBU6::startup()
{
	if(m_rcc.startup() != OK)
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
	
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void STM32C071KBU6::startEnd(volatile uint8& state)
{
	//	The Compiler Barrier keeps the Writes of the Start (Object, Pointer) before the State: a Thread that sees c_started finds them
	asm volatile("" ::: "memory");
	state = c_started;
}


inline STM32C071KBU6& STM32C071KBU6::get()
{
	static STM32C071KBU6 stm32;
	return(stm32);
}







constexpr inline Flash& STM32C071KBU6::get_flash()
{
	return(m_flash);
}


inline Update& STM32C071KBU6::get_update()
{
	//	No Member: the Update Driver is only linked into Programs that use it
	static Update update;
	return(update);
}


constexpr inline RCC& STM32C071KBU6::get_rcc()
{
	return(m_rcc);
}


inline CRC& STM32C071KBU6::get_crc()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static CRC* volatile crc = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static CRC instance;
		instance.startup(m_rcc);
		crc = &instance;
		startEnd(state);
	}
	return(*crc);
}


inline DMA& STM32C071KBU6::get_dma(uint8 channel)
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


inline DMAMUX& STM32C071KBU6::get_dmamux()
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


inline ADC& STM32C071KBU6::get_adc()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static ADC* volatile adc = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static ADC instance;
		instance.startup();
		adc = &instance;
		startEnd(state);
	}
	return(*adc);
}


constexpr inline PWR& STM32C071KBU6::get_pwr()
{
	return(m_pwr);
}


constexpr inline DBG& STM32C071KBU6::get_dbg()
{
	return(m_dbg);
}


constexpr inline GPIO& STM32C071KBU6::get_gpio()
{
	return(m_gpio);
}


inline Watchdog& STM32C071KBU6::get_watchdog()
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


inline EXTI& STM32C071KBU6::get_exti()
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


inline Timer_17& STM32C071KBU6::get_timer_17()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static Timer_17* volatile timer_17 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static Timer_17 instance(m_rcc);
		instance.startup();
		timer_17 = &instance;
		startEnd(state);
	}
	return(*timer_17);
}


inline I2C_1& STM32C071KBU6::get_i2c_1()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static I2C_1* volatile i2c_1 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static I2C_1 instance;
		instance.startup(m_rcc);
		i2c_1 = &instance;
		startEnd(state);
	}
	return(*i2c_1);
}


inline USART_1& STM32C071KBU6::get_usart_1()
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


inline USART_2& STM32C071KBU6::get_usart_2()
{
	//	Created and started at the first Call (startBegin): a Program that never calls it links nothing of the Driver
	static volatile uint8 state = c_notStarted;
	static USART_2* volatile usart_2 = nullptr;
	if(state != c_started && startBegin(state) == true)
	{
		static USART_2 instance;
		instance.startup();
		usart_2 = &instance;
		startEnd(state);
	}
	return(*usart_2);
}