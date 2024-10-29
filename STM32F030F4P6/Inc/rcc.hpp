#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "flash.hpp"





class RCC
{
	public:
		
		static constexpr uint32 c_clock_pll_max					= 48000000;
		static constexpr uint32 c_clock_core_max				= 48000000;
		static constexpr uint32 c_clock_ahb_max					= 48000000;
		static constexpr uint32 c_clock_apb1_max				= 48000000;
		static constexpr uint32 c_clock_apb2_max				= 48000000;
		static constexpr uint32 c_clock_hsi_14					= 14000000;
		static constexpr uint32 c_clock_hsi_8						=  8000000;
		static constexpr uint32 c_clock_csi							=  4000000;
		static constexpr uint32 c_clock_lsi							=    40000;
		static constexpr uint32 c_clock_lse							=    32768;
		
		static constexpr uint32 c_clock_pll_input_min		=  1000000;
		static constexpr uint32 c_clock_pll_input_max 	= 24000000;
		static constexpr uint32 c_clock_pll_output_min	= 16000000;
		static constexpr uint32 c_clock_pll_output_max	= 48000000;
		static constexpr uint32 c_clock_HSE_min					=  1000000;
		static constexpr uint32 c_clock_HSE_max					= 32000000;
		
		enum class e_module : uint16
		{
			//	AHB
			DMA												= 0x0000,
			CRC												= 0x0006,
			GPIO_A										= 0x0011,
			GPIO_B										= 0x0012,
			GPIO_F										= 0x0016,
			
			//	APB 2
			SYSCFG										= 0x0100,
			ADC												= 0x0109,
			TIMER_1										= 0x010B,
			SPI_1											= 0x010C,
			USART_1										= 0x010E,
			TIMER_16									= 0x0111,
			TIMER_17									= 0x0112,
			DEBUG_MCU									= 0x0116,
			
			//	APB 1
			TIMER_3										= 0x0201,
			TIMER_14									= 0x0208,
			WWDG											= 0x020B,
			I2C_1											= 0x0215,
			PWR												= 0x021C
		};
		
		enum class e_clockSource_system
		{
			HSI_8					= 0x0,
			HSE						= 0x1,
			PLL						= 0x2
		};
		
		enum class e_clockSource_pll
		{
			HSI_DIV2			= 0x0,
			HSE						= 0x1
		};
		
		enum class e_clockSource_rtc
		{
			NONE					= 0x0,
			LSE						= 0x1,
			LSI 					= 0x2,
			HSE_DIV32			= 0x3
		};
		
		enum class e_clockSource_usart_1
		{
			BUSCLOCK			= 0x0,
			SYSTEM_CLOCK	= 0x1,
			LSE						= 0x2,
			HSI						= 0x3
		};
		
		
		
		
		
	private:
		
		Flash& m_flash;
		
		e_clockSource_pll m_clockSource_pll;
		e_clockSource_system m_clockSource_system;
		e_clockSource_rtc m_clockSource_rtc;
		e_clockSource_usart_1 m_clockSource_usart_1;
		
		bool m_HSE_enabled;
		bool m_HSI8_enabled;
		bool m_HSI14_enabled;
		bool m_pll_enabled;
		bool m_clock_rtc_enabled;
		
		uint32 m_multiplier_pll;
		uint32 m_prescaler_HSE_pll;
		uint32 m_prescaler_ahb;
		uint32 m_prescaler_apb;
		
		uint32 m_clock_HSE;
		uint32 m_clock_pll_input;
		uint32 m_clock_pll;
		uint32 m_clock_system;
		uint32 m_clock_ahb;
		uint32 m_clock_apb;
		uint32 m_clock_rtc;
		uint32 m_clock_usart_1;
		
		constexpr inline RCC(Flash& flash);
		RCC(const RCC& rcc) = delete;
		inline ~RCC();
		
		inline feedback startup();
		void calculate_clockTree();
		
		friend class STM32F030F4P6;
		
		
		
		
		
	public:
		
		feedback HSE_init(bool enable);
		feedback HSI8_init(bool enable);
		feedback HSI14_init(bool enable);
		
		e_clockSource_system get_clockSource_system();
		feedback set_clockSource(e_clockSource_system clockSource);
		feedback set_clockSource(e_clockSource_pll clockSource);
		feedback set_prescaler_HSE_pll(uint32 prescaler);
		feedback pll_init(uint32 clock_out);
		feedback set_prescaler_AHB(uint32 prescaler);
		feedback set_prescaler_APB(uint32 prescaler);
		
		void clear_resetFlags();
		
		feedback module_clockInit(e_module module, bool enable);
		feedback module_reset(e_module module);
		
		feedback reset_backupDomain();
		feedback set_clockSource(e_clockSource_rtc clockSource, bool enable);
		feedback set_clockSource(e_clockSource_usart_1 clockSource);
		
		feedback set_clock_HSE(uint32 clock);
		
		constexpr inline uint32 get_clock_HSE() const;
		constexpr inline uint32 get_clock_pll() const;
		constexpr inline uint32 get_clock_system() const;
		constexpr inline uint32 get_clock_ahb() const;
		constexpr inline uint32 get_clock_apb() const;
		constexpr inline uint32 get_clock_rtc() const;
		constexpr inline uint32 get_clock_usart_1() const;
		constexpr inline uint32 get_clock_apb_timer() const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline RCC::RCC(Flash& flash)
	:	m_flash(flash),
		
		m_clockSource_pll(e_clockSource_pll::HSI_DIV2),
		m_clockSource_system(e_clockSource_system::HSI_8),
		m_clockSource_rtc(e_clockSource_rtc::NONE),
		m_clockSource_usart_1(e_clockSource_usart_1::BUSCLOCK),
		
		m_HSE_enabled(false),
		m_HSI8_enabled(true),
		m_HSI14_enabled(false),
		m_pll_enabled(false),
		m_clock_rtc_enabled(false),
		
		m_multiplier_pll(2),
		m_prescaler_HSE_pll(1),
		m_prescaler_ahb(1),
		m_prescaler_apb(1),
		
		m_clock_HSE(0),
		m_clock_pll_input(c_clock_hsi_8 / 2),
		m_clock_pll(m_multiplier_pll * m_clock_pll_input),
		m_clock_system(c_clock_hsi_8),
		m_clock_ahb(m_clock_system / m_prescaler_ahb),
		m_clock_apb(m_clock_ahb / m_prescaler_apb),
		m_clock_rtc(0),
		m_clock_usart_1(m_clock_apb)
{
	
}


inline RCC::~RCC()
{
	
}







inline feedback RCC::startup()
{
	HSI8_init(true);
	set_clockSource(e_clockSource_system::HSI_8);
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

constexpr inline uint32 RCC::get_clock_HSE() const
{
	return(m_clock_HSE);
}


constexpr inline uint32 RCC::get_clock_pll() const
{
	return(m_clock_pll);
}


constexpr inline uint32 RCC::get_clock_system() const
{
	return(m_clock_system);
}


constexpr inline uint32 RCC::get_clock_ahb() const
{
	return(m_clock_ahb);
}


constexpr inline uint32 RCC::get_clock_apb() const
{
	return(m_clock_apb);
}


constexpr inline uint32 RCC::get_clock_rtc() const
{
	return(m_clock_rtc);
}


constexpr inline uint32 RCC::get_clock_usart_1() const
{
	return(m_clock_usart_1);
}


constexpr inline uint32 RCC::get_clock_apb_timer() const
{
	if(m_prescaler_apb == 1)
	{
		return(m_clock_apb);
	}
	return(2 * m_clock_apb);
}