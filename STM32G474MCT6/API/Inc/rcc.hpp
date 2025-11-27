#pragma once

#include "registers.hpp"





class RCC
{
	public:
		
		typedef struct
		{
			uint32 c_clock_hse_max;
			
			uint32 c_clock_pll_vco_min;
			uint32 c_clock_pll_vco_max;
			uint32 c_clock_pll_p_min;
			uint32 c_clock_pll_p_max;
			uint32 c_clock_pll_q_min;
			uint32 c_clock_pll_q_max;
			uint32 c_clock_pll_r_min;
			uint32 c_clock_pll_r_max;
		}s_clockBoundaries;
		
		static constexpr uint32 c_clock_hsi_16							= 16000000;
		static constexpr uint32 c_clock_hsi_48							= 48000000;
		static constexpr uint32 c_clock_lsi									=    32000;
		
		static constexpr uint32 c_clock_ahb_max							= 80000000;
		static constexpr uint32 c_clock_apb1_max						= 80000000;
		static constexpr uint32 c_clock_apb2_max						= 80000000;
		
		static constexpr uint32 c_clock_hse_min							=  4000000;
		static constexpr uint32 c_clock_lse_max							=  1000000;
		static constexpr uint32 c_clock_pll_input_min				=  4000000;
		static constexpr uint32 c_clock_pll_input_max				= 16000000;
		
		enum class e_module
		{
			//  AHB1
			DMA_1											= 0x0000,
			DMA_2											= 0x0001,
			DMAMUX										= 0x0002,
			CORDIC										= 0x0003,
			FMAC											= 0x0004,
			FLASH											= 0x0008,
			CRC												= 0x000C,
			
			
			//	AHB2
			GPIO_A										= 0x0100,
			GPIO_B										= 0x0101,
			GPIO_C										= 0x0102,
			GPIO_D										= 0x0103,
			GPIO_E										= 0x0104,
			GPIO_F										= 0x0105,
			GPIO_G										= 0x0106,
			ADC_1_2										= 0x010D,
			ADC_3_4_5									= 0x010E,
			DAC_1											= 0x0110,
			DAC_2											= 0x0111,
			DAC_3											= 0x0112,
			DAC_4											= 0x0113,
			AES												= 0x0118,
			RNG												= 0x011A,
			
			
			//	AHB3
			FSMC											= 0x0200,
			QUADSPI										= 0x0208,
			
			
			//	APB1
			TIMER_2										= 0x0400,
			TIMER_3										= 0x0401,
			TIMER_4										= 0x0402,
			TIMER_5										= 0x0403,
			TIMER_6										= 0x0404,
			TIMER_7										= 0x0405,
			CRS												= 0x0408,
			RTC												= 0x040A,
			WWDG											= 0x040B,
			SPI_2											= 0x040E,
			SPI_3											= 0x040F,
			USART_2										= 0x0411,
			USART_3										= 0x0412,
			UART_4										= 0x0413,
			UART_5										= 0x0414,
			I2C_1											= 0x0415,
			I2C_2											= 0x0416,
			USB												= 0x0417,
			FDCAN_1_2_3								= 0x0419,
			PWR												= 0x041C,
			I2C_3											= 0x041E,
			LP_TIMER_1								= 0x041F,
			
			LP_UART_1									= 0x0500,
			I2C_4											= 0x0501,
			UCPD											= 0x0508,
			
			
			//	APB2
			SYSCFG										= 0x0600,
			TIMER_1										= 0x060B,
			SPI_1											= 0x060C,
			TIMER_8										= 0x060D,
			USART_1										= 0x060E,
			SPI_4											= 0x060F,
			TIMER_15									= 0x0610,
			TIMER_16									= 0x0611,
			TIMER_17									= 0x0612,
			TIMER_20									= 0x0614,
			SAI_1											= 0x0615,
			HR_TIMER									= 0x061A
		};
		
		enum class e_clockSource_system: uint8
		{
			HSI16					= 0x1,
			HSE						= 0x2,
			PLL_R					= 0x3
		};
		
		enum class e_clockSource_pll: uint8
		{
			NONE					= 0x0,
			HSI16					= 0x2,
			HSE						= 0x3
		};
		
		enum class e_clockSource_mco: uint8
		{
			NONE											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x3,
			HSE												= 0x4,
			PLL_R											= 0x5,
			LSI												= 0x6,
			LSE												= 0x7,
			HSI48											= 0x8
		};
		
		enum class e_clockSource_adc12: uint8
		{
			NONE											= 0x0,
			PLL_P											= 0x1,
			SYSTEM										= 0x2
		};
		
		enum class e_clockSource_adc345: uint8
		{
			NONE											= 0x0,
			PLL_P											= 0x1,
			SYSTEM										= 0x2
		};
		
		enum class e_clockSource_usart_1: uint8
		{
			APB2											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x2,
			LSE												= 0x3
		};
		
		enum class e_clockSource_usart_2: uint8
		{
			APB1											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x2,
			LSE												= 0x3
		};
		
		enum class e_clockSource_usart_3: uint8
		{
			APB1											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x2,
			LSE												= 0x3
		};
		
		enum class e_clockSource_uart_4: uint8
		{
			APB1											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x2,
			LSE												= 0x3
		};
		
		enum class e_clockSource_uart_5: uint8
		{
			APB1											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x2,
			LSE												= 0x3
		};
		
		enum class e_clockSource_lpuart_1: uint8
		{
			APB1											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x2,
			LSE												= 0x3
		};
		
		enum class e_clockSource_i2c_1: uint8
		{
			APB1											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x2
		};

		enum class e_clockSource_i2c_2: uint8
		{
			APB1											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x2
		};

		enum class e_clockSource_i2c_3: uint8
		{
			APB1											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x2
		};

		enum class e_clockSource_i2c_4: uint8
		{
			APB1											= 0x0,
			SYSTEM										= 0x1,
			HSI16											= 0x2
		};
		
		enum class e_clockSource_can: uint8
		{
			HSE												= 0x0,
			PLL_Q											= 0x1,
			APB1											= 0x2
		};
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint8 c_prescaler_pll_input[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
		
		static constexpr uint32 c_pll_multiplier_min						=  8;
		static constexpr uint32 c_pll_multiplier_max						= 127;
		
		static constexpr uint16 c_prescaler_ahb[] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 4, 8, 16, 64, 128, 256, 512};
		static constexpr uint8 c_prescaler_apb1[] = {1, 1, 1, 1, 2, 4, 8, 16};
		static constexpr uint8 c_prescaler_apb2[] = {1, 1, 1, 1, 2, 4, 8, 16};
		
		
		//	Non-static Member
		uint32 c_clock_hse;
		uint32 c_clock_lse;
		
		e_clockSource_system m_clockSource_system;
		e_clockSource_pll m_clockSource_pll;
		e_clockSource_adc12 m_clockSource_adc12;
		e_clockSource_adc345 m_clockSource_adc345;
		e_clockSource_usart_1 m_clockSource_usart_1;
		e_clockSource_usart_2 m_clockSource_usart_2;
		e_clockSource_usart_3 m_clockSource_usart_3;
		e_clockSource_uart_4 m_clockSource_uart_4;
		e_clockSource_uart_5 m_clockSource_uart_5;
		e_clockSource_lpuart_1 m_clockSource_lpuart_1;
		e_clockSource_i2c_1 m_clockSource_i2c_1;
		e_clockSource_i2c_2 m_clockSource_i2c_2;
		e_clockSource_i2c_3 m_clockSource_i2c_3;
		e_clockSource_i2c_4 m_clockSource_i2c_4;
		e_clockSource_can m_clockSource_can;
		
		bool m_hsi16_enabled;
		bool m_hsi48_enabled;
		bool m_lsi_enabled;
		bool m_lse_enabled;
		bool m_hse_enabled;
		bool m_pll_enabled;
		
		uint8 m_prescaler_pll_input;
		float m_multiplier_pll;
		uint8 m_prescaler_pll_p;
		uint8 m_prescaler_pll_q;
		uint8 m_prescaler_pll_r;
		uint16 m_prescaler_ahb;
		uint8 m_prescaler_apb1;
		uint8 m_prescaler_apb2;
		
		uint32 m_clock_hsi16;
		uint32 m_clock_hsi48;
		uint32 m_clock_lsi;
		uint32 m_clock_lse;
		uint32 m_clock_hse;
		uint32 m_clock_pll_input;
		uint32 m_clock_pll;
		uint32 m_clock_system;
		uint32 m_clock_ahb;
		uint32 m_clock_apb1;
		uint32 m_clock_apb2;
		uint32 m_clock_apb1_timer;
		uint32 m_clock_apb2_timer;
		
		
		//	Constructor and Destructor
		constexpr inline RCC();
		RCC(const RCC& rcc) = delete;
		inline ~RCC();
		
		
		//	Member Functions
		inline feedback startup();
		void calculate_clockTree();
		
		feedback autoAdjust_AHB_APB1_APB2_prescaler();
		
		
		//	Friends
		friend class STM32G474MCT6;
		
		
		
		
		
	public:
		
		feedback init_hsi16(bool enable);
		feedback init_hsi48(bool enable);
		feedback init_lsi(bool enable);
		feedback init_lse(bool enable);
		feedback init_hse(bool enable);
		
		inline e_clockSource_system get_clockSource_system();
		feedback set_clockSource(e_clockSource_system clockSource);
		feedback set_clockSource(e_clockSource_pll clockSource);
		inline feedback set_clockSource(e_clockSource_mco clockSource);
		inline feedback set_clockSource(e_clockSource_adc12 clockSource);
		inline feedback set_clockSource(e_clockSource_adc345 clockSource);
		inline feedback set_clockSource(e_clockSource_usart_1 clockSource);
		inline feedback set_clockSource(e_clockSource_usart_2 clockSource);
		inline feedback set_clockSource(e_clockSource_usart_3 clockSource);
		inline feedback set_clockSource(e_clockSource_uart_4 clockSource);
		inline feedback set_clockSource(e_clockSource_uart_5 clockSource);
		inline feedback set_clockSource(e_clockSource_lpuart_1 clockSource);
		inline void set_clockSource(e_clockSource_i2c_1 clockSource);
		inline void set_clockSource(e_clockSource_i2c_2 clockSource);
		inline void set_clockSource(e_clockSource_i2c_3 clockSource);
		inline void set_clockSource(e_clockSource_i2c_4 clockSource);
		inline void set_clockSource(e_clockSource_can clockSource);
		
		feedback init_pll(uint32 clock_out, uint32 prescaler_p, uint32 prescaler_q, uint32 prescaler_r);
		
		inline void clear_resetFlags();
		
		feedback module_clockInit(e_module module, bool enable);
		feedback module_reset(e_module module);
		
		feedback reset_backupDomain();
		
		feedback set_clock_lse(uint32 clock);
		feedback set_clock_hse(uint32 clock);
		
		constexpr inline uint32 get_clock_hsi16() const;
		constexpr inline uint32 get_clock_hsi48() const;
		constexpr inline uint32 get_clock_lsi() const;
		constexpr inline uint32 get_clock_lse() const;
		constexpr inline uint32 get_clock_hse() const;
		constexpr inline uint32 get_clock_pll_input() const;
		constexpr inline uint32 get_clock_pll_p() const;
		constexpr inline uint32 get_clock_pll_q() const;
		constexpr inline uint32 get_clock_pll_r() const;
		constexpr inline uint32 get_clock_system() const;
		constexpr inline uint32 get_clock_ahb() const;
		constexpr inline uint32 get_clock_apb1() const;
		constexpr inline uint32 get_clock_apb2() const;
		constexpr inline uint32 get_clock_apb1_timer() const;
		constexpr inline uint32 get_clock_apb2_timer() const;
		constexpr inline uint32 get_clock_adc12() const;
		constexpr inline uint32 get_clock_adc345() const;
		constexpr inline uint32 get_clock_usart_1() const;
		constexpr inline uint32 get_clock_usart_2() const;
		constexpr inline uint32 get_clock_usart_3() const;
		constexpr inline uint32 get_clock_uart_4() const;
		constexpr inline uint32 get_clock_uart_5() const;
		constexpr inline uint32 get_clock_lpuart_1() const;
		constexpr inline uint32 get_clock_can() const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline RCC::RCC()
	:	c_clock_hse(0),
		c_clock_lse(0),
		
		m_clockSource_system(e_clockSource_system::HSI16),
		m_clockSource_pll(e_clockSource_pll::NONE),
		m_clockSource_adc12(e_clockSource_adc12::NONE),
		m_clockSource_adc345(e_clockSource_adc345::NONE),
		m_clockSource_usart_1(e_clockSource_usart_1::APB2),
		m_clockSource_usart_2(e_clockSource_usart_2::APB1),
		m_clockSource_usart_3(e_clockSource_usart_3::APB1),
		m_clockSource_uart_4(e_clockSource_uart_4::APB1),
		m_clockSource_uart_5(e_clockSource_uart_5::APB1),
		m_clockSource_lpuart_1(e_clockSource_lpuart_1::APB1),
		m_clockSource_i2c_1(e_clockSource_i2c_1::APB1),
		m_clockSource_i2c_2(e_clockSource_i2c_2::APB1),
		m_clockSource_i2c_3(e_clockSource_i2c_3::APB1),
		m_clockSource_i2c_4(e_clockSource_i2c_4::APB1),
		m_clockSource_can(e_clockSource_can::HSE),
		
		m_hsi16_enabled(true),
		m_hsi48_enabled(false),
		m_lsi_enabled(false),
		m_lse_enabled(false),
		m_hse_enabled(false),
		m_pll_enabled(false),
		
		m_prescaler_pll_input(1),
		m_multiplier_pll(16),
		m_prescaler_pll_p(7),
		m_prescaler_pll_q(2),
		m_prescaler_pll_r(2),
		m_prescaler_ahb(c_prescaler_ahb[0]),
		m_prescaler_apb1(c_prescaler_apb1[0]),
		m_prescaler_apb2(c_prescaler_apb2[0]),
		
		m_clock_hsi16(c_clock_hsi_16),
		m_clock_hsi48(0),
		m_clock_lsi(0),
		m_clock_lse(0),
		m_clock_hse(0),
		m_clock_pll_input(0),
		m_clock_pll(0),
		m_clock_system(c_clock_hsi_16),
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







inline feedback RCC::set_clockSource(e_clockSource_mco clockSource)
{
	const uint32 temp = *MCU::RCC::CFGR & 0xF0FFFFFF;
	*MCU::RCC::CFGR = temp | (((uint32) clockSource) << 24);
	
	return(OK);
}


inline feedback RCC::set_clockSource(e_clockSource_adc12 clockSource)
{
	const uint32 temp = *MCU::RCC::CCIPR & 0xCFFFFFFF;
	*MCU::RCC::CCIPR = temp | ((uint32) clockSource << 28);
	
	m_clockSource_adc12 = clockSource;
	
	return(OK);
}


inline feedback RCC::set_clockSource(e_clockSource_adc345 clockSource)
{
	const uint32 temp = *MCU::RCC::CCIPR & 0x3FFFFFFF;
	*MCU::RCC::CCIPR = temp | ((uint32) clockSource << 30);
	
	m_clockSource_adc345 = clockSource;
	
	return(OK);
}





inline feedback RCC::set_clockSource(e_clockSource_usart_1 clockSource)
{
	const uint32 temp = *MCU::RCC::CCIPR & 0xFFFFFFFC;
	*MCU::RCC::CCIPR = temp | ((uint32) clockSource << 0);
	
	m_clockSource_usart_1 = clockSource;
	
	return(OK);
}


inline feedback RCC::set_clockSource(e_clockSource_usart_2 clockSource)
{
	const uint32 temp = *MCU::RCC::CCIPR & 0xFFFFFFF3;
	*MCU::RCC::CCIPR = temp | ((uint32) clockSource << 2);
	
	m_clockSource_usart_2 = clockSource;
	
	return(OK);
}


inline feedback RCC::set_clockSource(e_clockSource_usart_3 clockSource)
{
	const uint32 temp = *MCU::RCC::CCIPR & 0xFFFFFFCF;
	*MCU::RCC::CCIPR = temp | ((uint32) clockSource << 4);
	
	m_clockSource_usart_3 = clockSource;
	
	return(OK);
}


inline feedback RCC::set_clockSource(e_clockSource_uart_4 clockSource)
{
	const uint32 temp = *MCU::RCC::CCIPR & 0xFFFFFF3F;
	*MCU::RCC::CCIPR = temp | ((uint32) clockSource << 6);
	
	m_clockSource_uart_4 = clockSource;
	
	return(OK);
}


inline feedback RCC::set_clockSource(e_clockSource_uart_5 clockSource)
{
	const uint32 temp = *MCU::RCC::CCIPR & 0xFFFFFCFF;
	*MCU::RCC::CCIPR = temp | ((uint32) clockSource << 8);
	
	m_clockSource_uart_5 = clockSource;
	
	return(OK);
}


inline feedback RCC::set_clockSource(e_clockSource_lpuart_1 clockSource)
{
	const uint32 temp = *MCU::RCC::CCIPR & 0xFFFFF3FF;
	*MCU::RCC::CCIPR = temp | ((uint32) clockSource << 10);
	
	m_clockSource_lpuart_1 = clockSource;
	
	return(OK);
}


inline void RCC::set_clockSource(e_clockSource_i2c_1 clockSource)
{
	const uint32 mask = (uint32) clockSource;
	
	uint32 temp = *MCU::RCC::CCIPR & 0xFFFFCFFF;
	*MCU::RCC::CCIPR = temp | (mask << 12);
	
	m_clockSource_i2c_1 = clockSource;
}


inline void RCC::set_clockSource(e_clockSource_i2c_2 clockSource)
{
	const uint32 mask = (uint32) clockSource;
	
	uint32 temp = *MCU::RCC::CCIPR & 0xFFFF3FFF;
	*MCU::RCC::CCIPR = temp | (mask << 14);
	
	m_clockSource_i2c_2 = clockSource;
}


inline void RCC::set_clockSource(e_clockSource_i2c_3 clockSource)
{
	const uint32 mask = (uint32) clockSource;
	
	uint32 temp = *MCU::RCC::CCIPR & 0xFFFCFFFF;
	*MCU::RCC::CCIPR = temp | (mask << 16);
	
	m_clockSource_i2c_3 = clockSource;
}


inline void RCC::set_clockSource(e_clockSource_i2c_4 clockSource)
{
	const uint32 mask = (uint32) clockSource;
	
	uint32 temp = *MCU::RCC::CCIPR2 & 0xFFFFFFFC;
	*MCU::RCC::CCIPR2 = temp | (mask << 0);
	
	m_clockSource_i2c_4 = clockSource;
}


inline void RCC::set_clockSource(e_clockSource_can clockSource)
{
	const uint32 mask = (uint32) clockSource;
	
	uint32 temp = *MCU::RCC::CCIPR & 0xFCFFFFFF;
	*MCU::RCC::CCIPR = temp | (mask << 24);
	
	m_clockSource_can = clockSource;
}







inline void RCC::clear_resetFlags()
{
	bit::set(*MCU::RCC::CSR, 24);
}







constexpr inline uint32 RCC::get_clock_hsi16() const
{
	return(m_clock_hsi16);
}


constexpr inline uint32 RCC::get_clock_hsi48() const
{
	return(m_clock_hsi48);
}


constexpr inline uint32 RCC::get_clock_lsi() const
{
	return(m_clock_lsi);
}


constexpr inline uint32 RCC::get_clock_lse() const
{
	return(m_clock_lse);
}


constexpr inline uint32 RCC::get_clock_hse() const
{
	return(m_clock_hse);
}


constexpr inline uint32 RCC::get_clock_pll_input() const
{
	return(m_clock_pll_input);
}


constexpr inline uint32 RCC::get_clock_pll_p() const
{
	return(m_clock_pll / m_prescaler_pll_p);
}


constexpr inline uint32 RCC::get_clock_pll_q() const
{
	return(m_clock_pll / m_prescaler_pll_q);
}


constexpr inline uint32 RCC::get_clock_pll_r() const
{
	return(m_clock_pll / m_prescaler_pll_r);
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


constexpr inline uint32 RCC::get_clock_adc12() const
{
	switch(m_clockSource_adc12)
	{
		case e_clockSource_adc12::NONE:
		{
			return(0);
		}
		break;
		
		case e_clockSource_adc12::PLL_P:
		{
			return(m_clock_pll / m_prescaler_pll_p);
		}
		break;
		
		case e_clockSource_adc12::SYSTEM:
		{
			return(m_clock_system);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
	return(0);
}


constexpr inline uint32 RCC::get_clock_adc345() const
{
	switch(m_clockSource_adc345)
	{
		case e_clockSource_adc345::NONE:
		{
			return(0);
		}
		break;
		
		case e_clockSource_adc345::PLL_P:
		{
			return(m_clock_pll / m_prescaler_pll_p);
		}
		break;
		
		case e_clockSource_adc345::SYSTEM:
		{
			return(m_clock_system);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
	return(0);
}


constexpr inline uint32 RCC::get_clock_usart_1() const
{
	switch(m_clockSource_usart_1)
	{
		case e_clockSource_usart_1::APB2:
		{
			return(m_clock_apb2);
		}
		break;
		
		case e_clockSource_usart_1::SYSTEM:
		{
			return(m_clock_system);
		}
		break;
		
		case e_clockSource_usart_1::HSI16:
		{
			return(m_clock_hsi16);
		}
		break;
		
		case e_clockSource_usart_1::LSE:
		{
			return(m_clock_lse);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
	return(0);
}


constexpr inline uint32 RCC::get_clock_usart_2() const
{
	switch(m_clockSource_usart_2)
	{
		case e_clockSource_usart_2::APB1:
		{
			return(m_clock_apb1);
		}
		break;
		
		case e_clockSource_usart_2::SYSTEM:
		{
			return(m_clock_system);
		}
		break;
		
		case e_clockSource_usart_2::HSI16:
		{
			return(m_clock_hsi16);
		}
		break;
		
		case e_clockSource_usart_2::LSE:
		{
			return(m_clock_lse);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
	return(0);
}


constexpr inline uint32 RCC::get_clock_usart_3() const
{
	switch(m_clockSource_usart_3)
	{
		case e_clockSource_usart_3::APB1:
		{
			return(m_clock_apb1);
		}
		break;
		
		case e_clockSource_usart_3::SYSTEM:
		{
			return(m_clock_system);
		}
		break;
		
		case e_clockSource_usart_3::HSI16:
		{
			return(m_clock_hsi16);
		}
		break;
		
		case e_clockSource_usart_3::LSE:
		{
			return(m_clock_lse);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
	return(0);
}


constexpr inline uint32 RCC::get_clock_uart_4() const
{
	switch(m_clockSource_uart_4)
	{
		case e_clockSource_uart_4::APB1:
		{
			return(m_clock_apb1);
		}
		break;
		
		case e_clockSource_uart_4::SYSTEM:
		{
			return(m_clock_system);
		}
		break;
		
		case e_clockSource_uart_4::HSI16:
		{
			return(m_clock_hsi16);
		}
		break;
		
		case e_clockSource_uart_4::LSE:
		{
			return(m_clock_lse);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
	return(0);
}


constexpr inline uint32 RCC::get_clock_uart_5() const
{
	switch(m_clockSource_uart_5)
	{
		case e_clockSource_uart_5::APB1:
		{
			return(m_clock_apb1);
		}
		break;
		
		case e_clockSource_uart_5::SYSTEM:
		{
			return(m_clock_system);
		}
		break;
		
		case e_clockSource_uart_5::HSI16:
		{
			return(m_clock_hsi16);
		}
		break;
		
		case e_clockSource_uart_5::LSE:
		{
			return(m_clock_lse);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
	return(0);
}


constexpr inline uint32 RCC::get_clock_lpuart_1() const
{
	switch(m_clockSource_lpuart_1)
	{
		case e_clockSource_lpuart_1::APB1:
		{
			return(m_clock_apb1);
		}
		break;
		
		case e_clockSource_lpuart_1::SYSTEM:
		{
			return(m_clock_system);
		}
		break;
		
		case e_clockSource_lpuart_1::HSI16:
		{
			return(m_clock_hsi16);
		}
		break;
		
		case e_clockSource_lpuart_1::LSE:
		{
			return(m_clock_lse);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
	return(0);
}


constexpr inline uint32 RCC::get_clock_can() const
{
	switch(m_clockSource_can)
	{
		case e_clockSource_can::HSE:
		{
			return(m_clock_hse);
		}
		break;
		
		case e_clockSource_can::PLL_Q:
		{
			return(m_clock_pll / m_prescaler_pll_q);
		}
		break;
		
		case e_clockSource_can::APB1:
		{
			return(m_clock_apb1);
		}
		break;
		
		default:
		{
			return(0);
		}
		break;
	}
	return(0);
}