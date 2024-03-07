#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "flash.hpp"





class RCC
{
	public:
		
		static constexpr uint32 c_clock_core_max					= 72000000;
		static constexpr uint32 c_clock_ahb_max						= 72000000;
		static constexpr uint32 c_clock_apb1_max					= 36000000;
		static constexpr uint32 c_clock_apb2_max					= 72000000;
		static constexpr uint32 c_clock_hsi								=  8000000;
		static constexpr uint32 c_clock_lsi								=    40000;
		static constexpr uint32 c_clock_lse								=    32768;
		
		static constexpr uint32 c_clock_pll_1_input_min		=  3000000;
		static constexpr uint32 c_clock_pll_1_input_max		= 12000000;
		static constexpr uint32 c_clock_pll_1_output_min	= 18000000;
		static constexpr uint32 c_clock_pll_1_output_max	= 72000000;
		static constexpr uint32 c_clock_pll_2_3_input_min	=  3000000;
		static constexpr uint32 c_clock_pll_2_3_input_max	=  5000000;
		static constexpr uint32 c_clock_pll_2_output_min	= 40000000;
		static constexpr uint32 c_clock_pll_2_output_max	= 74000000;
		static constexpr uint32 c_clock_pll_3_output_min	= 40000000;
		static constexpr uint32 c_clock_pll_3_output_max	= 74000000;
		
		enum class e_module
		{
			//  AHB
			DMA_1											= 0x0000,
			DMA_2											= 0x0001,
			SRAM											= 0x0002,
			FLASH											= 0x0004,
			CRC												= 0x0006,
			USB_OTG										= 0x000C,
			ETHERNET_MAC							= 0x000E,
			ETHERNET_TX								= 0x000F,
			ETHERNET_RX								= 0x0010,
			
			
			//	APB2
			AFIO											= 0x0100,
			GPIO_A										= 0x0102,
			GPIO_B										= 0x0103,
			GPIO_C										= 0x0104,
			GPIO_D										= 0x0105,
			ADC_1											= 0x0109,
			ADC_2											= 0x010A,
			TIMER_1										= 0x010B,
			SPI_1											= 0x010C,
			USART_1										= 0x010E,
			
			
			//	APB1
			TIMER_2										= 0x0200,
			TIMER_3										= 0x0201,
			TIMER_4										= 0x0202,
			TIMER_5										= 0x0203,
			TIMER_6										= 0x0204,
			TIMER_7										= 0x0205,
			WWDG											= 0x020B,
			SPI_2											= 0x020E,
			SPI_3											= 0x020F,
			USART_2										= 0x0211,
			USART_3										= 0x0212,
			UART_4										= 0x0213,
			UART_5										= 0x0214,
			I2C_1											= 0x0215,
			I2C_2											= 0x0216,
			CAN_1											= 0x0219,
			CAN_2											= 0x021A,
			BKP												= 0x021B,
			PWR												= 0x021C,
			DAC												= 0x021D
		};
		
		enum class e_clockSource_system: uint8
		{
			HSI						= 0x0,
			HSE						= 0x1,
			PLL_1					= 0x2
		};
		
		enum class e_clockSource_pll_1: uint8
		{
			HSI_DIV2			= 0x0,
			HSE						= 0x1,
			PLL2					= 0x3,
		};
		
		enum class e_clockSource_mco: uint8
		{
			NONE											= 0x0,
			SYSTEM										= 0x4,
			HSI												= 0x5,
			HSE												= 0x6,
			PLL_1_DIV2								= 0x7,
			PLL_2											= 0x8,
			PLL_3_DIV2								= 0x9,
			OSC_IN_PIN_FOR_ETHERNET		= 0xA,
			PLL_3_FOR_ETHERNET				= 0xB
		};
		
		enum class e_clockSource_rtc: uint8
		{
			NONE					= 0x0,
			LSE						= 0x1,
			LSI						= 0x2,
			HSE_DIV128		= 0x3
		};
		
		enum class e_prescaler_adc
		{
			DIV_2					= 0x0,
			DIV_4					= 0x1,
			DIV_6					= 0x2,
			DIV_8					= 0x3
		};
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint8 c_prescaler_pll_1_input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		static constexpr uint8 c_prescaler_pll_2_3_input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		
		static constexpr float c_multiplier_pll_1[] = {0, 0, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 6.5};
		static constexpr uint8 c_multiplier_pll_2[] = {0, 0, 0, 0, 0, 0, 8, 9, 10, 11, 12, 13, 14, 0, 16, 20};
		static constexpr uint8 c_multiplier_pll_3[] = {0, 0, 0, 0, 0, 0, 8, 9, 10, 11, 12, 13, 14, 0, 16, 20};
		
		static constexpr uint16 c_prescaler_ahb[] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 4, 8, 16, 64, 128, 256, 512};
		static constexpr uint8 c_prescaler_apb1[] = {1, 1, 1, 1, 2, 4, 8, 16};
		static constexpr uint8 c_prescaler_apb2[] = {1, 1, 1, 1, 2, 4, 8, 16};
		
		
		//	Non-static Member
		Flash& m_flash;
		
		uint32 c_clock_hse;
		
		e_clockSource_system m_clockSource_system;
		e_clockSource_pll_1 m_clockSource_pll_1;
		
		bool m_hse_enabled;
		bool m_hsi_enabled;
		bool m_lsi_enabled;
		bool m_pll_1_enabled;
		bool m_pll_2_enabled;
		bool m_pll_3_enabled;
		bool m_clock_rtc_enabled;
		
		uint8 m_prescaler_pll_1_input;
		uint8 m_prescaler_pll_2_3_input;
		float m_multiplier_pll_1;
		uint8 m_multiplier_pll_2;
		uint8 m_multiplier_pll_3;
		uint16 m_prescaler_ahb;
		uint8 m_prescaler_apb1;
		uint8 m_prescaler_apb2;
		
		uint32 m_clock_hse;
		uint32 m_clock_hsi;
		uint32 m_clock_lsi;
		uint32 m_clock_pll_1_input;
		uint32 m_clock_pll_2_3_input;
		uint32 m_clock_pll_1;
		uint32 m_clock_pll_2;
		uint32 m_clock_pll_3;
		uint32 m_clock_system;
		uint32 m_clock_ahb;
		uint32 m_clock_apb1;
		uint32 m_clock_apb2;
		uint32 m_clock_apb1_timer;
		uint32 m_clock_apb2_timer;
		
		
		//	Constructor and Destructor
		constexpr inline RCC(Flash& flash);
		RCC(const RCC& rcc) = delete;
		inline ~RCC();
		
		
		//	Member Functions
		inline feedback startup();
		void calculate_clockTree();
		
		feedback autoAdjust_AHB_APB1_APB2_prescaler();
		
		
		//	Friends
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		feedback init_hse(bool enable);
		feedback init_hsi(bool enable);
		feedback init_lsi(bool enable);
		
		inline e_clockSource_system get_clockSource_system();
		feedback set_clockSource(e_clockSource_system clockSource);
		feedback set_clockSource(e_clockSource_pll_1 clockSource);
		void set_clockSource(e_clockSource_mco clockSource);
		feedback init_pll_1(uint32 clock_out);
		feedback init_pll_2_3(uint32 clock_out_pll2, uint32 clock_out_pll3);
		
		inline void clear_resetFlags();
		
		feedback module_clockInit(e_module module, bool enable);
		feedback module_reset(e_module module);
		
		feedback reset_backupDomain();
		feedback set_rtc_clock(bool enable);
		feedback set_clockSource(e_clockSource_rtc clockSource);
		feedback set_prescaler(e_prescaler_adc prescaler);
		
		void set_clock_hse(uint32 clock);
		
		constexpr inline uint32 get_clock_hse() const;
		constexpr inline uint32 get_clock_hsi() const;
		constexpr inline uint32 get_clock_lsi() const;
		constexpr inline uint32 get_clock_pll_1_input() const;
		constexpr inline uint32 get_clock_pll_2_3_input() const;
		constexpr inline uint32 get_clock_pll_1() const;
		constexpr inline uint32 get_clock_pll_2() const;
		constexpr inline uint32 get_clock_pll_3() const;
		constexpr inline uint32 get_clock_system() const;
		constexpr inline uint32 get_clock_ahb() const;
		constexpr inline uint32 get_clock_apb1() const;
		constexpr inline uint32 get_clock_apb2() const;
		constexpr inline uint32 get_clock_apb1_timer() const;
		constexpr inline uint32 get_clock_apb2_timer() const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline RCC::RCC(Flash& flash)
	:	m_flash(flash),
		
		c_clock_hse(0),
		
		m_clockSource_system(e_clockSource_system::HSI),
		m_clockSource_pll_1(e_clockSource_pll_1::HSI_DIV2),
		
		m_hse_enabled(false),
		m_hsi_enabled(true),
		m_lsi_enabled(false),
		m_pll_1_enabled(false),
		m_pll_2_enabled(false),
		m_pll_3_enabled(false),
		m_clock_rtc_enabled(false),
		
		m_prescaler_pll_1_input(c_prescaler_pll_1_input[0]),
		m_prescaler_pll_2_3_input(c_prescaler_pll_2_3_input[0]),
		m_multiplier_pll_1(c_multiplier_pll_1[0]),
		m_multiplier_pll_2(c_multiplier_pll_2[0]),
		m_multiplier_pll_3(c_multiplier_pll_3[0]),
		m_prescaler_ahb(c_prescaler_ahb[0]),
		m_prescaler_apb1(c_prescaler_apb1[0]),
		m_prescaler_apb2(c_prescaler_apb2[0]),
		
		m_clock_hse(0),
		m_clock_hsi(c_clock_hsi),
		m_clock_lsi(0),
		m_clock_pll_1_input(m_clock_hsi / 2),
		m_clock_pll_2_3_input(m_clock_hse / m_prescaler_pll_2_3_input),
		m_clock_pll_1(0),
		m_clock_pll_2(0),
		m_clock_pll_3(0),
		m_clock_system(m_clock_hsi),
		m_clock_ahb(m_clock_system / m_prescaler_ahb),
		m_clock_apb1(m_clock_ahb / m_prescaler_apb1),
		m_clock_apb2(m_clock_ahb / m_prescaler_apb2),
		m_clock_apb1_timer(m_clock_apb1),
		m_clock_apb2_timer(m_clock_apb2)
{
	
}


inline RCC::~RCC()
{
	
}







inline feedback RCC::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline RCC::e_clockSource_system RCC::get_clockSource_system()
{
	uint32 mask = (*MCU::RCC::CFGR & 0x0000000C) >> 2;
	return((e_clockSource_system) mask);
}







inline void RCC::clear_resetFlags()
{
	bit::set(*MCU::RCC::CSR, 24);
}







constexpr inline uint32 RCC::get_clock_hse() const
{
	return(m_clock_hse);
}


constexpr inline uint32 RCC::get_clock_hsi() const
{
	return(m_clock_hsi);
}


constexpr inline uint32 RCC::get_clock_lsi() const
{
	return(m_clock_lsi);
}


constexpr inline uint32 RCC::get_clock_pll_1_input() const
{
	return(m_clock_pll_1_input);
}


constexpr inline uint32 RCC::get_clock_pll_2_3_input() const
{
	return(m_clock_pll_2_3_input);
}


constexpr inline uint32 RCC::get_clock_pll_1() const
{
	return(m_clock_pll_1);
}


constexpr inline uint32 RCC::get_clock_pll_2() const
{
	return(m_clock_pll_2);
}


constexpr inline uint32 RCC::get_clock_pll_3() const
{
	return(m_clock_pll_3);
}


constexpr inline uint32 RCC::get_clock_system() const
{
	return(m_clock_system);
}


constexpr inline uint32 RCC::get_clock_ahb() const
{
	return(m_clock_ahb);
}


constexpr inline uint32 RCC::get_clock_apb1() const
{
	return(m_clock_apb1);
}


constexpr inline uint32 RCC::get_clock_apb2() const
{
	return(m_clock_apb2);
}


constexpr inline uint32 RCC::get_clock_apb1_timer() const
{
	return(m_clock_apb1_timer);
}


constexpr inline uint32 RCC::get_clock_apb2_timer() const
{
	return(m_clock_apb2_timer);
}