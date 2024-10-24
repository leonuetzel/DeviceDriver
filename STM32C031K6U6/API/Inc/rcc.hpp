#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "flash.hpp"





class RCC
{
	public:
		
		static constexpr uint32 c_clock_core_max					= 48000000;
		static constexpr uint32 c_clock_ahb_max						= 48000000;
		static constexpr uint32 c_clock_apb_max						= 48000000;
		static constexpr uint32 c_clock_hsi								= 48000000;
		static constexpr uint32 c_clock_lsi								=    32000;
		
		
		enum class e_module
		{
			//	IOP
			GPIO_A										= 0x0000,
			GPIO_B										= 0x0001,
			GPIO_C										= 0x0002,
			GPIO_F										= 0x0005,
			
			
			//  AHB
			DMA												= 0x0100,
			FLASH											= 0x0108,
			CRC												= 0x010C,
			
			
			//	APB
			TIMER_3										= 0x0201,
			RTC 											= 0x020A,
			WWDG 											= 0x020B,
			USART_2										= 0x0211,
			I2C												= 0x0215,
			DBG												= 0x021B,
			PWR												= 0x021C,
			
			SYSCFG										= 0x0300,
			TIMER_1 									= 0x030B,
			SPI 											= 0x030C,
			USART_1 									= 0x030E,
			TIMER_14 									= 0x030F,
			TIMER_16 									= 0x0311,
			TIMER_17 									= 0x0312,
			ADC 											= 0x0314
		};
		
		enum class e_clockSource_system: uint8
		{
			HSI = 0x0,
			HSE = 0x1,
			LSI	= 0x3,
			LSE	= 0x4
		};
		
		enum class e_prescaler_hsiSystem
		{
			DIV_1		= 0x0,
			DIV_2		= 0x1,
			DIV_4		= 0x2,
			DIV_8		= 0x3,
			DIV_16	= 0x4,
			DIV_32	= 0x5,
			DIV_64	= 0x6,
			DIV_128	= 0x7,
		};
		
		enum class e_prescaler_hsiKernel
		{
			DIV_1	= 0x0,
			DIV_2	= 0x1,
			DIV_3	= 0x2,
			DIV_4	= 0x3,
			DIV_5	= 0x4,
			DIV_6	= 0x5,
			DIV_7	= 0x6,
			DIV_8	= 0x7,
		};
		
		enum class e_clockSource_mco: uint8
		{
			NONE		= 0x0,
			SYSTEM	= 0x1,
			HSI			= 0x3,
			HSE			= 0x4,
			LSI			= 0x6,
			LSE			= 0x7
		};
		
		enum class e_prescaler_mco: uint8
		{
			DIV_1		= 0x0,
			DIV_2		= 0x1,
			DIV_4		= 0x2,
			DIV_8		= 0x3,
			DIV_16	= 0x4,
			DIV_32	= 0x5,
			DIV_64	= 0x6,
			DIV_128	= 0x7
		};
		
		enum class e_clockSource_i2c
		{
			APB					= 0x0,
			SYSTEM			= 0x1,
			HSI_KERNEL	= 0x2
		};
		
		enum class e_clockSource_adc
		{
			SYSTEM			= 0x0,
			HSI_KERNEL	= 0x2
		};
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint16 c_prescaler_ahb[] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 4, 8, 16, 64, 128, 256, 512};
		static constexpr uint8 c_prescaler_apb[] = {1, 1, 1, 1, 2, 4, 8, 16};
		static constexpr uint8 c_prescaler_hsiSystem[] = {1, 2, 4, 8, 16, 32, 64, 128};
		static constexpr uint8 c_prescaler_hsiKernel[] = {1, 2, 3, 4, 5, 6, 7, 8};
		
		
		//	Non-static Member
		Flash& m_flash;
		
		uint32 c_clock_hse;
		uint32 c_clock_lse;
		
		e_clockSource_system m_clockSource_system;
		e_clockSource_i2c m_clockSource_i2c;
		e_clockSource_adc m_clockSource_adc;
		
		bool m_hse_enabled;
		bool m_hsi_enabled;
		bool m_lse_enabled;
		bool m_lsi_enabled;
		
		uint8 m_prescaler_hsiSystem;
		uint8 m_prescaler_hsiKernel;
		uint16 m_prescaler_ahb;
		uint8 m_prescaler_apb;
		
		uint32 m_clock_hse;
		uint32 m_clock_hsi;
		uint32 m_clock_hsiSystem;
		uint32 m_clock_hsiKernel;
		uint32 m_clock_lse;
		uint32 m_clock_lsi;
		uint32 m_clock_system;
		uint32 m_clock_ahb;
		uint32 m_clock_apb;
		uint32 m_clock_apb_timer;
		
		
		//	Constructor and Destructor
		constexpr inline RCC(Flash& flash);
		RCC(const RCC& rcc) = delete;
		inline ~RCC();
		
		
		//	Member Functions
		inline feedback startup();
		void calculate_clockTree();
		
		feedback autoAdjust_AHB_APB_prescaler();
		
		
		//	Friends
		friend class STM32C031K6U6;
		
		
		
		
		
	public:
		
		feedback init_hse(bool enable);
		feedback init_hsi(bool enable);
		feedback init_lse(bool enable);
		feedback init_lsi(bool enable);
		
		feedback set_hsiSystem_prescaler(e_prescaler_hsiSystem prescaler);
		feedback set_hsiKernel_prescaler(e_prescaler_hsiKernel prescaler);
		
		inline e_clockSource_system get_clockSource_system();
		feedback set_clockSource(e_clockSource_system clockSource);
		void init_mco(e_clockSource_mco clockSource, e_prescaler_mco prescaler);
		void init_mco2(e_clockSource_mco clockSource, e_prescaler_mco prescaler);
		
		inline void clear_resetFlags();
		
		feedback module_clockInit(e_module module, bool enable);
		feedback module_reset(e_module module);
		
		feedback reset_backupDomain();
		
		void set_clock_hse(uint32 clock);
		
		void set_clockSource(e_clockSource_i2c clockSource);
		feedback set_clockSource(e_clockSource_adc clockSource);
		
		constexpr inline uint32 get_clock_hse() const;
		constexpr inline uint32 get_clock_hsi() const;
		constexpr inline uint32 get_clock_lse() const;
		constexpr inline uint32 get_clock_lsi() const;
		constexpr inline uint32 get_clock_system() const;
		constexpr inline uint32 get_clock_ahb() const;
		constexpr inline uint32 get_clock_apb() const;
		constexpr inline uint32 get_clock_apb_timer() const;
		constexpr inline uint32 get_clock_hsiKernel() const;
		constexpr inline uint32 get_clock_adc() const;
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
		c_clock_lse(0),
		
		m_clockSource_system(e_clockSource_system::HSI),
		m_clockSource_i2c(e_clockSource_i2c::APB),
		m_clockSource_adc(e_clockSource_adc::SYSTEM),
		
		m_hse_enabled(false),
		m_hsi_enabled(true),
		m_lse_enabled(false),
		m_lsi_enabled(false),
		
		m_prescaler_hsiSystem(4),
		m_prescaler_hsiKernel(3),
		m_prescaler_ahb(c_prescaler_ahb[0]),
		m_prescaler_apb(c_prescaler_apb[0]),
		
		m_clock_hse(0),
		m_clock_hsi(c_clock_hsi),
		m_clock_hsiSystem(m_clock_hsi / m_prescaler_hsiSystem),
		m_clock_hsiKernel(m_clock_hsi / m_prescaler_hsiKernel),
		m_clock_lse(0),
		m_clock_lsi(0),
		m_clock_system(m_clock_hsiSystem),
		m_clock_ahb(m_clock_system / m_prescaler_ahb),
		m_clock_apb(m_clock_ahb / m_prescaler_apb),
		m_clock_apb_timer(m_clock_apb)
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
	uint32 mask = (*MCU::RCC::CFGR & 0x00000038) >> 3;
	return((e_clockSource_system) mask);
}







inline void RCC::clear_resetFlags()
{
	bit::set(*MCU::RCC::CSR2, 23);
}







constexpr inline uint32 RCC::get_clock_hse() const
{
	return(m_clock_hse);
}


constexpr inline uint32 RCC::get_clock_hsi() const
{
	return(m_clock_hsi);
}


constexpr inline uint32 RCC::get_clock_lse() const
{
	return(m_clock_lse);
}


constexpr inline uint32 RCC::get_clock_lsi() const
{
	return(m_clock_lsi);
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


constexpr inline uint32 RCC::get_clock_apb_timer() const
{
	return(m_clock_apb_timer);
}


constexpr inline uint32 RCC::get_clock_hsiKernel() const
{
	return(m_clock_hsiKernel);
}


constexpr inline uint32 RCC::get_clock_adc() const
{
	switch(m_clockSource_adc)
	{
		case e_clockSource_adc::SYSTEM:
		{
			return(m_clock_system);
		}
		break;
		
		case e_clockSource_adc::HSI_KERNEL:
		{
			return(m_clock_hsiKernel);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
}