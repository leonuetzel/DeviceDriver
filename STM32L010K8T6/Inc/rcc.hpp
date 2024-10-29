#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "flash.hpp"





class RCC
{
	public:
		
		static constexpr uint32 c_clock_core_max				= 32000000;
		static constexpr uint32 c_clock_ahb_max					= 32000000;
		static constexpr uint32 c_clock_apb1_max				= 32000000;
		static constexpr uint32 c_clock_apb2_max				= 32000000;
		static constexpr uint32 c_clock_hsi_16					= 16000000;
		static constexpr uint32 c_clock_lsi							=    38000;
		static constexpr uint32 c_clock_lse							=    32768;
		static constexpr uint32 c_clock_msi[]						= {65536, 131072, 262144, 524288, 1048000, 2097000, 4194000};
		
		static constexpr uint32 c_clock_pll_input_min		=  2000000;
		static constexpr uint32 c_clock_pll_input_max 	= 24000000;
		static constexpr uint32 c_clock_pll_output_min	=  2000000;
		static constexpr uint32 c_clock_pll_output_max	= 32000000;
		
		static constexpr uint8 c_pll_multiplier[] = {3, 4, 6, 8, 12, 16, 24, 32, 48};
		
		
		enum class e_module : uint16
		{
			//	GPIO
			GPIO_A										= 0x0000,
			GPIO_B										= 0x0001,
			GPIO_C										= 0x0002,
			
			//	AHB
			DMA												= 0x0100,
			MIF												= 0x0108,
			CRC												= 0x010C,
			
			//	APB 2
			SYSCFG										= 0x0200,
			TIMER_21									= 0x0202,
			FW												= 0x0207,
			ADC												= 0x0209,
			SPI_1											= 0x020C,
			DEBUG_MCU									= 0x0216,
			
			//	APB 1
			TIMER_2										= 0x0300,
			WWDG											= 0x030B,
			USART_2										= 0x0311,
			I2C_1											= 0x0315,
			PWR												= 0x031C,
			LP_TIMER_1								= 0x031F
		};
		
		enum class e_clockSource_system : uint8
		{
			MSI						= 0x0,
			HSI_16				= 0x1,
			PLL						= 0x3
		};
		
		enum class e_clockSource_pll : uint8
		{
			HSI_16				= 0x0
		};
		
		enum class e_clockSource_rtc : uint8
		{
			NONE					= 0x0,
			LSE						= 0x1,
			LSI 					= 0x2
		};
		
		enum class e_clockSource_usart_2 : uint8
		{
			BUSCLOCK			= 0x0,
			SYSTEM_CLOCK	= 0x1,
			HSI16					= 0x2,
			LSE						= 0x3
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		Flash& m_flash;
		
		e_clockSource_pll m_clockSource_pll;
		e_clockSource_system m_clockSource_system;
		e_clockSource_rtc m_clockSource_rtc;
		e_clockSource_usart_2 m_clockSource_usart_2;
		
		bool m_MSI_enabled;
		bool m_HSI16_enabled;
		bool m_LSI_enabled;
		bool m_pll_enabled;
		bool m_clock_rtc_enabled;
		
		uint8 m_MSI_range;
		uint32 m_multiplier_pll;
		uint32 m_prescaler_pll_out;
		uint32 m_prescaler_HSI16;
		uint32 m_prescaler_ahb;
		uint32 m_prescaler_apb1;
		uint32 m_prescaler_apb2;
		
		uint32 m_clock_MSI;
		uint32 m_clock_HSI16;
		uint32 m_clock_LSI;
		uint32 m_clock_pll_input;
		uint32 m_clock_pll;
		uint32 m_clock_system;
		uint32 m_clock_ahb;
		uint32 m_clock_apb1;
		uint32 m_clock_apb2;
		uint32 m_clock_apb1_timer;
		uint32 m_clock_apb2_timer;
		uint32 m_clock_rtc;
		uint32 m_clock_usart_2;
		
		
		//	Constructor and Destructor
		constexpr inline RCC(Flash& flash);
		RCC(const RCC& rcc) = delete;
		inline ~RCC();
		
		
		//	Member Functions
		inline feedback startup();
		void calculate_clockTree();
		
		
		//	Friends
		friend class STM32L010K8T6;
		
		
		
		
		
	public:
		
		feedback MSI_init(bool enable, uint32 range = 5);
		feedback HSI16_init(bool enable);
		feedback LSI_init(bool enable);
		
		e_clockSource_system get_clockSource_system();
		feedback set_clockSource(e_clockSource_system clockSource);
		feedback set_clockSource(e_clockSource_pll clockSource);
		feedback pll_init(uint32 clock_out);
		void set_HSI16_prescaler(bool divideBy4);
		feedback set_prescaler_AHB(uint32 prescaler);
		feedback set_prescaler_APB1(uint32 prescaler);
		feedback set_prescaler_APB2(uint32 prescaler);
		
		void clear_resetFlags();
		
		feedback module_clockInit(e_module module, bool enable);
		feedback module_reset(e_module module);
		
		feedback reset_backupDomain();
		feedback set_clockSource(e_clockSource_rtc clockSource, bool enable);
		feedback set_clockSource(e_clockSource_usart_2 clockSource);
		
		constexpr inline uint32 get_clock_HSI16() const;
		constexpr inline uint32 get_clock_pll() const;
		constexpr inline uint32 get_clock_system() const;
		constexpr inline uint32 get_clock_ahb() const;
		constexpr inline uint32 get_clock_apb1() const;
		constexpr inline uint32 get_clock_apb2() const;
		constexpr inline uint32 get_clock_apb1_timer() const;
		constexpr inline uint32 get_clock_apb2_timer() const;
		constexpr inline uint32 get_clock_rtc() const;
		constexpr inline uint32 get_clock_usart_2() const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline RCC::RCC(Flash& flash)
	:	m_flash(flash),
		
		m_clockSource_pll(e_clockSource_pll::HSI_16),
		m_clockSource_system(e_clockSource_system::MSI),
		m_clockSource_rtc(e_clockSource_rtc::NONE),
		m_clockSource_usart_2(e_clockSource_usart_2::BUSCLOCK),
		
		m_MSI_enabled(true),
		m_HSI16_enabled(false),
		m_LSI_enabled(false),
		m_pll_enabled(false),
		m_clock_rtc_enabled(false),
		
		m_MSI_range(5),
		m_multiplier_pll(c_pll_multiplier[0]),
		m_prescaler_pll_out(1),
		m_prescaler_HSI16(1),
		m_prescaler_ahb(1),
		m_prescaler_apb1(1),
		m_prescaler_apb2(1),
		
		m_clock_MSI(c_clock_msi[m_MSI_range]),
		m_clock_HSI16(0),
		m_clock_LSI(0),
		m_clock_pll_input(c_clock_hsi_16),
		m_clock_pll(0),
		m_clock_system(m_clock_MSI),
		m_clock_ahb(m_clock_system / m_prescaler_ahb),
		m_clock_apb1(m_clock_ahb / m_prescaler_apb1),
		m_clock_apb2(m_clock_ahb / m_prescaler_apb2),
		m_clock_apb1_timer(m_clock_apb1),
		m_clock_apb2_timer(m_clock_apb2),
		m_clock_rtc(0),
		m_clock_usart_2(m_clock_apb1)
{
	
}


inline RCC::~RCC()
{
	
}







inline feedback RCC::startup()
{
	//MSI_init(true, m_clock_MSI);
	//set_clockSource(e_clockSource_system::MSI);
	
	if(HSI16_init(true) != OK)
	{
		return(FAIL);
	}
	if(set_clockSource(e_clockSource_system::HSI_16) != OK)
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

constexpr inline uint32 RCC::get_clock_HSI16() const
{
	return(m_clock_HSI16);
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


constexpr inline uint32 RCC::get_clock_rtc() const
{
	return(m_clock_rtc);
}


constexpr inline uint32 RCC::get_clock_usart_2() const
{
	return(m_clock_usart_2);
}