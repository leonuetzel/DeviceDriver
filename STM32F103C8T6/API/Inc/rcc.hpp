#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "flash.hpp"





class RCC
{
	public:
		
		static constexpr uint32 c_clock_pll_max		= 72000000;
		static constexpr uint32 c_clock_core_max	= 72000000;
		static constexpr uint32 c_clock_ahb_max		= 72000000;
		static constexpr uint32 c_clock_apb1_max	= 36000000;
		static constexpr uint32 c_clock_apb2_max	= 72000000;
		static constexpr uint32 c_clock_hsi				=  8000000;
		static constexpr uint32 c_clock_hse				=  8000000;
		static constexpr uint32 c_clock_lsi				=    40000;
		static constexpr uint32 c_clock_lse				=    32768;
		
		enum class e_module
		{
			DMA												= 0x0000,                                                                       								//  AHB
			
			AFIO											= 0x0100,																																												//	APB2
			GPIO_A										= 0x0102,
			GPIO_B										= 0x0103,
			GPIO_C										= 0x0104,
			GPIO_D										= 0x0105,
			ADC												= 0x0109,
			TIMER_1										= 0x010B,
			SPI_1											= 0x010C,
			USART_1										= 0x010E,
			
			TIMER_2										= 0x0200,																																												//	APB1
			TIMER_3										= 0x0201,
			TIMER_4										= 0x0202,
			WWDG											= 0x020B,
			SPI_2											= 0x020E,
			USART_2										= 0x0211,
			USART_3										= 0x0212,
			I2C_1											= 0x0215,
			I2C_2											= 0x0216,
			CAN												= 0x0219,
			BKP												= 0x021B,
			PWR												= 0x021C
		};
		
		enum class e_clockSource_system
		{
			HSI						= 0x0,
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
			LSI						= 0x2,
			HSE_DIV128		= 0x3
		};
		
		enum class e_prescaler_adc
		{
			_2						= 0x0,
			_4						= 0x1,
			_6						= 0x2,
			_8						= 0x3
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		Flash& m_flash;
		
		e_clockSource_system m_clockSource_system;
		e_clockSource_pll m_clockSource_pll;
		
		uint32 m_clock_pll;
		uint32 m_clock_system;
		uint32 m_clock_ahb;
		uint32 m_clock_apb1;
		uint32 m_clock_apb1_timer;
		uint32 m_clock_apb2;
		uint32 m_clock_apb2_timer;
		
		uint32 m_divider_hse;
		
		
		//	Constructor and Destructor
		constexpr inline RCC(Flash& flash);
		RCC(const RCC& rcc) = delete;
		inline ~RCC();
		
		
		//	Member Functions
		inline feedback startup();
		feedback set_busPrescaler();
		
		
		//	Friends
		friend class STM32F103C8T6;
		
		
		
		
		
	public:
		
		feedback HSE_init(bool enable);
		feedback HSI_init(bool enable);
		feedback LSI_init(bool enable);
		
		inline e_clockSource_system get_clockSource_system();
		feedback set_clockSource(e_clockSource_system clockSource);
		feedback set_clockSource(e_clockSource_pll clockSource);
		feedback pll_set_HSE_DIV(uint32 divider);
		feedback pll_init(uint32 clock_out);
		
		inline void clear_resetFlags();
		
		feedback module_clockInit(e_module module, bool enable);
		feedback module_reset(e_module module);
		
		feedback reset_backupDomain();
		feedback set_rtc_clock(bool enable);
		feedback set_clockSource(e_clockSource_rtc clockSource);
		feedback set_prescaler(e_prescaler_adc prescaler);
		
		constexpr inline uint32 get_clock_pll();
		constexpr inline uint32 get_clock_system();
		constexpr inline uint32 get_clock_ahb();
		constexpr inline uint32 get_clock_apb1();
		constexpr inline uint32 get_clock_apb2();
		constexpr inline uint32 get_clock_apb1_timer();
		constexpr inline uint32 get_clock_apb2_timer();
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline RCC::RCC(Flash& flash)
	:	m_flash(flash),
		
		m_clockSource_system(e_clockSource_system::HSI),
		m_clockSource_pll(e_clockSource_pll::HSI_DIV2),
		
		m_clock_pll(0),
		m_clock_system(c_clock_hsi),
		m_clock_ahb(c_clock_hsi),
		m_clock_apb1(c_clock_hsi),
		m_clock_apb1_timer(c_clock_hsi),
		m_clock_apb2(c_clock_hsi),
		m_clock_apb2_timer(c_clock_hsi),
		
		m_divider_hse(1)
{
	
}


inline RCC::~RCC()
{
	
}







inline feedback RCC::startup()
{
	set_clockSource(e_clockSource_pll::HSI_DIV2);
	pll_init(64000000);
	set_clockSource(e_clockSource_system::PLL);
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







constexpr inline uint32 RCC::get_clock_pll()
{
	return(m_clock_pll);
}


constexpr inline uint32 RCC::get_clock_system()
{
	return(m_clock_system);
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


constexpr inline uint32 RCC::get_clock_apb1_timer()
{
	return(m_clock_apb1_timer);
}


constexpr inline uint32 RCC::get_clock_apb2_timer()
{
	return(m_clock_apb2_timer);
}