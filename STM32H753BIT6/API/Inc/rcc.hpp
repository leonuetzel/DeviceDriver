#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "pwr.hpp"
#include "flash.hpp"





class RCC
{
	public:
		
		static constexpr uint32 c_clock_pll_1_max = 960000000;
		static constexpr uint32 c_clock_core_max =  480000000;
		static constexpr uint32 c_clock_ahb_max =   240000000;
		static constexpr uint32 c_clock_apb1_max =  120000000;
		static constexpr uint32 c_clock_apb2_max =  120000000;
		static constexpr uint32 c_clock_apb3_max =  120000000;
		static constexpr uint32 c_clock_apb4_max =  120000000;
		static constexpr uint32 c_clock_hsi =        64000000;
		static constexpr uint32 c_clock_csi =         4000000;
		static constexpr uint32 c_clock_lsi = 					32000;
		static constexpr uint32 c_clock_hse = 				8000000;
		static constexpr uint32 c_clock_lse = 							0;
		
		
		
		enum class e_module : uint16
		{
			//	AHB 3
			MDMA											= 0x0000,
			DMA2D											= 0x0004,
			JPEG											= 0x0005,
			FMC												= 0x000C,
			QUADSPI										= 0x000E,
			SDMMC_1										= 0x0010,
			
			
			//	AHB 1
			DMA_1											= 0x0100,
			DMA_2											= 0x0101,
			ADC_1_2										= 0x0105,
			ETH_MAC										= 0x010F,
			ETH_TX										= 0x0110,
			ETH_RX										= 0x0111,
			USB_2_ULPI								= 0x0112,
			USB_1											= 0x0119,
			USB_1_ULPI								= 0x011A,
			USB_2											= 0x011B,
			
			
			//	AHB 2
			DCMI											= 0x0200,
			CRYPTO										= 0x0204,
			HASH											= 0x0205,
			RNG												= 0x0206,
			SDMMC_2										= 0x0209,
			SRAM_1										= 0x021D,
			SRAM_2										= 0x021E,
			SRAM_3										= 0x021F,
			
			
			//	AHB 4
			GPIO_A										= 0x0300,
			GPIO_B										= 0x0301,
			GPIO_C										= 0x0302,
			GPIO_D										= 0x0303,
			GPIO_E										= 0x0304,
			GPIO_F										= 0x0305,
			GPIO_G										= 0x0306,
			GPIO_H										= 0x0307,
			GPIO_I										= 0x0308,
			GPIO_J										= 0x0309,
			GPIO_K										= 0x030A,
			CRC												= 0x0313,
			BDMA											= 0x0315,
			ADC_3											= 0x0318,
			HSEM											= 0x0319,
			BKP_RAM										= 0x031C,
			
			
			//	APB 3
			LTDC											= 0x0403,
			WWDG											= 0x0406,	
			
			
			//	APB 1
			TIMER_2										= 0x0500,
			TIMER_3										= 0x0501,
			TIMER_4										= 0x0502,
			TIMER_5										= 0x0503,
			TIMER_6										= 0x0504,
			TIMER_7										= 0x0505,
			TIMER_12									= 0x0506,
			TIMER_13									= 0x0507,
			TIMER_14									= 0x0508,
			LP_TIMER_1								= 0x0509,
			SPI_2											= 0x050E,
			SPI_3											= 0x050F,
			SPDIFRX										= 0x0510,
			USART_2										= 0x0511,
			USART_3										= 0x0512,
			UART_4										= 0x0513,
			UART_5										= 0x0514,
			I2C_1											= 0x0515,
			I2C_2											= 0x0516,
			I2C_3											= 0x0517,
			HDMI_CEC									= 0x051B,
			DAC												= 0x051D,
			UART_7										= 0x051E,
			UART_8										= 0x051F,
			
			CRS												= 0x0601,
			SWPMI											= 0x0602,
			OP												= 0x0604,
			MDIOS											= 0x0605,
			FDCAN											= 0x0608,
			
			
			//	APB 2
			TIMER_1										= 0x0700,
			TIMER_8										= 0x0701,
			USART_1										= 0x0704,
			USART_6										= 0x0705,
			SPI_1											= 0x070C,
			SPI_4											= 0x070D,
			TIMER_15									= 0x0710,
			TIMER_16									= 0x0711,
			TIMER_17									= 0x0712,
			SPI_5											= 0x0714,
			SAI_1											= 0x0716,
			SAI_2											= 0x0717,
			SAI_3											= 0x0718,
			DFSDM											= 0x071C,
			HR_TIMER									= 0x071D,
			
			
			//	APB 4
			SYSCFG										= 0x0801,
			LP_UART										= 0x0803,
			SPI_6											= 0x0805,
			I2C_4											= 0x0807,
			LP_TIMER_2								= 0x0809,
			LP_TIMER_3								= 0x080A,
			LP_TIMER_4								= 0x080B,
			LP_TIMER_5								= 0x080C,
			COMP_1_2									= 0x080E,
			VREF											= 0x080F,
			RTC												= 0x0810,
			SAI_4											= 0x0815
		};
		
		enum class e_clockSource_mco_1
		{
			HSI												= 0x0,
			LSE												= 0x1,
			HSE												= 0x2,
			PLL1Q											= 0x3,
			HSI48											= 0x4
		};
		
		enum class e_clockSource_mco_2
		{
			SYSTEMCLOCK								= 0x0,
			PLL2P											= 0x1,
			HSE												= 0x2,
			PLL1P											= 0x3,
			CSI												= 0x4,
			LSI												= 0x5
		};
		
		enum class e_clockSource_system
		{
			HSI												= 0x0,
			CSI												= 0x1,
			HSE												= 0x2,
			PLL1											= 0x3
		};
		
		enum class e_clockSource_perck
		{
			HSI,
			CSI,
			HSE
		};
		
		enum class e_clockSource_pll
		{
			HSI												= 0x0,
			CSI												= 0x1,
			HSE												= 0x2,
			NONE											= 0x3
		};
		
		enum class e_pll_range
		{
			MEDIUM,
			WIDE
		};
		
		enum class e_clockSource_adc
		{
			PLL_2_P										= 0x0,
			PLL_3_R										= 0x1,
			PERCK											= 0x2
		};
		
		enum class e_clockSource_sdmmc
		{
			PLL_1_Q										= 0x0,
			PLL_2_R										= 0x1
		};
		
		enum class e_clockSource_uart
		{
			BUS_CLOCK									= 0x0,
			PLL_2_Q										= 0x1,
			PLL_3_Q										= 0x2,
			HSI												= 0x3,
			CSI												= 0x4,
			LSE												= 0x5
		};
		
		enum class e_clockSource_fmc
		{
			BUS_CLOCK		= 0x0,
			PLL_1_Q			= 0x1,
			PLL_2_R			= 0x2,
			PERCK				= 0x3
		};
		
		enum class e_resetReason
		{
			NONE,
			ILLEGAL_D1DSTANDBY_OR_CPUCSTOP,
			WWDG,
			IWDG,
			CPU_FLAG,
			POWER_ON_OFF,
			PIN,
			BROWNOUT,
			D2_POWERSWITCH_FLAG,
			D1_POWERSWITCH_FLAG,
			CPU
		};
		
		
		
		
		
	private:
		
		PWR& m_pwr;
		Flash& m_flash;
		
		e_clockSource_mco_1 m_clockSource_mco_1;
		e_clockSource_mco_2 m_clockSource_mco_2;
		e_clockSource_system m_clockSource_system;
		e_clockSource_pll m_clockSource_pll;
		e_clockSource_perck m_clockSource_perck;
		e_clockSource_adc m_clockSource_adc;
		e_clockSource_sdmmc m_clockSource_sdmmc;
		e_clockSource_uart m_clockSource_uart_1_6;
		e_clockSource_uart m_clockSource_uart_234578;
		e_clockSource_fmc m_clockSource_fmc;
		
		e_pll_range m_pll_1_range;
		e_pll_range m_pll_2_range;
		e_pll_range m_pll_3_range;
		
		
		
		uint32 m_clock_pll_1;
		uint32 m_clock_pll_2;
		uint32 m_clock_pll_3;
		uint32 m_clock_system;
		uint32 m_clock_core;
		uint32 m_clock_ahb;
		uint32 m_clock_apb1;
		uint32 m_clock_apb2;
		uint32 m_clock_apb3;
		uint32 m_clock_apb4;
		uint32 m_clock_apb1_timer;
		uint32 m_clock_apb2_timer;
		uint32 m_clock_perck;
		
		uint8 m_divider_hsi;
		uint32 m_divider_pll_1_p;
		uint32 m_divider_pll_1_q;
		uint32 m_divider_pll_1_r;
		uint32 m_divider_pll_2_p;
		uint32 m_divider_pll_2_q;
		uint32 m_divider_pll_2_r;
		uint32 m_divider_pll_3_p;
		uint32 m_divider_pll_3_q;
		uint32 m_divider_pll_3_r;
		uint32 m_divider_mco_1;
		uint32 m_divider_mco_2;
		uint32 m_divider_core;
		uint32 m_divider_ahb;
		uint32 m_divider_apb1;
		uint32 m_divider_apb2;
		uint32 m_divider_apb3;
		uint32 m_divider_apb4;
		
		
		constexpr inline RCC(PWR& pwr, Flash& flash);
		RCC(const RCC& rcc) = delete;
		inline ~RCC();
		
		feedback set_busPrescaler(uint32 newClock);
		
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup();
		
		feedback HSE_init(bool enable);
		feedback HSI_init(bool enable, uint8 divider);
		
		feedback set_clockSource_pll(e_clockSource_pll clockSource);
		feedback pll_1_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r);
		feedback pll_2_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r);
		feedback pll_3_init(uint32 clock_out, uint32 divider_p, uint32 divider_q, uint32 divider_r);
		
		e_clockSource_system get_clockSource_system();
		feedback set_clockSource_system(e_clockSource_system clockSource);
		
		e_resetReason check_resetReason();
		
		feedback mco_1_init(e_clockSource_mco_1 clockSource, uint32 divider);
		feedback mco_2_init(e_clockSource_mco_2 clockSource, uint32 divider);
		
		feedback module_clockInit(e_module module, bool enable);
		feedback module_reset(e_module module);
		
		feedback set_clockSource(e_clockSource_perck clockSource);
		feedback set_clockSource(e_clockSource_adc clockSource);
		feedback set_clockSource(e_clockSource_sdmmc clockSource);
		feedback set_clockSource(e_clockSource_uart clockSource, uint32 uartNumber);
		feedback set_clockSource(e_clockSource_fmc clockSource);
		
		constexpr inline e_clockSource_perck get_clockSource_perck();
		constexpr inline e_clockSource_adc get_clockSource_adc();
		constexpr inline e_clockSource_sdmmc get_clockSource_sdmmc();
		constexpr inline e_clockSource_uart get_clockSource_uart_1_6();
		constexpr inline e_clockSource_uart get_clockSource_uart_234578();
		constexpr inline e_clockSource_fmc get_clockSource_fmc();
		
		constexpr inline uint32 get_clock_pll_1();
		constexpr inline uint32 get_clock_pll_2();
		constexpr inline uint32 get_clock_pll_3();
		constexpr inline uint32 get_clock_system();
		constexpr inline uint32 get_clock_core();
		constexpr inline uint32 get_clock_ahb();
		constexpr inline uint32 get_clock_apb1();
		constexpr inline uint32 get_clock_apb2();
		constexpr inline uint32 get_clock_apb3();
		constexpr inline uint32 get_clock_apb4();
		constexpr inline uint32 get_clock_apb1_timer();
		constexpr inline uint32 get_clock_apb2_timer();
		constexpr inline uint32 get_clock_perck();
		
		constexpr inline uint32 get_clock_pll_1_p();
		constexpr inline uint32 get_clock_pll_1_q();
		constexpr inline uint32 get_clock_pll_1_r();
		constexpr inline uint32 get_clock_pll_2_p();
		constexpr inline uint32 get_clock_pll_2_q();
		constexpr inline uint32 get_clock_pll_2_r();
		constexpr inline uint32 get_clock_pll_3_p();
		constexpr inline uint32 get_clock_pll_3_q();
		constexpr inline uint32 get_clock_pll_3_r();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline RCC::RCC(PWR& pwr, Flash& flash)
	: m_pwr(pwr),
		m_flash(flash),
		
		m_clockSource_mco_1(e_clockSource_mco_1::HSI),
		m_clockSource_mco_2(e_clockSource_mco_2::SYSTEMCLOCK),
		m_clockSource_system(e_clockSource_system::HSI),
		m_clockSource_pll(e_clockSource_pll::HSI),
		m_clockSource_perck(e_clockSource_perck::HSI),
		m_clockSource_adc(e_clockSource_adc::PLL_2_P),
		m_clockSource_sdmmc(e_clockSource_sdmmc::PLL_1_Q),
		m_clockSource_uart_1_6(e_clockSource_uart::BUS_CLOCK),
		m_clockSource_uart_234578(e_clockSource_uart::BUS_CLOCK),
		m_clockSource_fmc(e_clockSource_fmc::BUS_CLOCK),
		
		m_pll_1_range(e_pll_range::WIDE),
		m_pll_2_range(e_pll_range::WIDE),
		m_pll_3_range(e_pll_range::WIDE),
		
		m_clock_pll_1(0),
		m_clock_pll_2(0),
		m_clock_pll_3(0),
		m_clock_system(c_clock_hsi),
		m_clock_core(m_clock_system),
		m_clock_ahb(m_clock_core),
		m_clock_apb1(m_clock_ahb),
		m_clock_apb2(m_clock_ahb),
		m_clock_apb3(m_clock_ahb),
		m_clock_apb4(m_clock_ahb),
		m_clock_apb1_timer(m_clock_apb1),
		m_clock_apb2_timer(m_clock_apb2),
		m_clock_perck(c_clock_hsi),
		
		m_divider_hsi(1),
		m_divider_pll_1_p(2),
		m_divider_pll_1_q(2),
		m_divider_pll_1_r(2),
		m_divider_pll_2_p(2),
		m_divider_pll_2_q(2),
		m_divider_pll_2_r(2),
		m_divider_pll_3_p(2),
		m_divider_pll_3_q(2),
		m_divider_pll_3_r(2),
		m_divider_mco_1(0),
		m_divider_mco_2(0),
		m_divider_core(1),
		m_divider_ahb(1),
		m_divider_apb1(1),
		m_divider_apb2(1),
		m_divider_apb3(1),
		m_divider_apb4(1)
{
	
}


inline RCC::~RCC()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

constexpr inline RCC::e_clockSource_perck RCC::get_clockSource_perck()
{
	return(m_clockSource_perck);
}


constexpr inline RCC::e_clockSource_adc RCC::get_clockSource_adc()
{
	return(m_clockSource_adc);
}


constexpr inline RCC::e_clockSource_sdmmc RCC::get_clockSource_sdmmc()
{
	return(m_clockSource_sdmmc);
}


constexpr inline RCC::e_clockSource_uart RCC::get_clockSource_uart_1_6()
{
	return(m_clockSource_uart_1_6);
}


constexpr inline RCC::e_clockSource_uart RCC::get_clockSource_uart_234578()
{
	return(m_clockSource_uart_234578);
}


constexpr inline RCC::e_clockSource_fmc RCC::get_clockSource_fmc()
{
	return(m_clockSource_fmc);
}







constexpr inline uint32 RCC::get_clock_pll_1()
{
	return(m_clock_pll_1);
}


constexpr inline uint32 RCC::get_clock_pll_2()
{
	return(m_clock_pll_2);
}


constexpr inline uint32 RCC::get_clock_pll_3()
{
	return(m_clock_pll_3);
}


constexpr inline uint32 RCC::get_clock_system()
{
	return(m_clock_system);
}


constexpr inline uint32 RCC::get_clock_core()
{
	return(m_clock_core);
}


constexpr inline uint32 RCC::get_clock_ahb()
{
	return(m_clock_ahb);
}


constexpr inline uint32 RCC::get_clock_apb1()
{
	return(m_clock_apb1);
}


constexpr inline uint32 RCC::get_clock_apb2()
{
	return(m_clock_apb2);
}


constexpr inline uint32 RCC::get_clock_apb3()
{
	return(m_clock_apb3);
}


constexpr inline uint32 RCC::get_clock_apb4()
{
	return(m_clock_apb4);
}


constexpr inline uint32 RCC::get_clock_apb1_timer()
{
	return(m_clock_apb1_timer);
}


constexpr inline uint32 RCC::get_clock_apb2_timer()
{
	return(m_clock_apb2_timer);
}


constexpr inline uint32 RCC::get_clock_perck()
{
	return(m_clock_perck);
}







constexpr inline uint32 RCC::get_clock_pll_1_p()
{
	return(m_clock_pll_1 / m_divider_pll_1_p);
}


constexpr inline uint32 RCC::get_clock_pll_1_q()
{
	return(m_clock_pll_1 / m_divider_pll_1_q);
}


constexpr inline uint32 RCC::get_clock_pll_1_r()
{
	return(m_clock_pll_1 / m_divider_pll_1_r);
}


constexpr inline uint32 RCC::get_clock_pll_2_p()
{
	return(m_clock_pll_2 / m_divider_pll_2_p);
}


constexpr inline uint32 RCC::get_clock_pll_2_q()
{
	return(m_clock_pll_2 / m_divider_pll_2_q);
}


constexpr inline uint32 RCC::get_clock_pll_2_r()
{
	return(m_clock_pll_2 / m_divider_pll_2_r);
}


constexpr inline uint32 RCC::get_clock_pll_3_p()
{
	return(m_clock_pll_3 / m_divider_pll_3_p);
}


constexpr inline uint32 RCC::get_clock_pll_3_q()
{
	return(m_clock_pll_3 / m_divider_pll_3_q);
}


constexpr inline uint32 RCC::get_clock_pll_3_r()
{
	return(m_clock_pll_3 / m_divider_pll_3_r);
}