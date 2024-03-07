#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class GPIO
{
	public:
		
		enum class e_pin : uint8
		{
			A0	= 0x00,
			A1	= 0x01,
			A2	= 0x02,
			A3	= 0x03,
			A4	= 0x04,
			A5	= 0x05,
			A6	= 0x06,
			A7	= 0x07,
			A8	= 0x08,
			A9	= 0x09,
			A10	= 0x0A,
			A11	= 0x0B,
			A12	= 0x0C,
			A13	= 0x0D,
			A14	= 0x0E,
			A15	= 0x0F,
			
			B0	= 0x10,
			B1	= 0x11,
			
			B3	= 0x13,
			B4	= 0x14,
			B5	= 0x15,
			B6	= 0x16,
			B7	= 0x17,
			
			C14	= 0x2E,
			C15	= 0x2F
		};
		
		enum class e_mode : uint8
		{
			IN,
			OUT_GP_PP,
			OUT_GP_OD,
			AF_PP,
			AF_OD,
			ANALOG
		};
		
		enum class e_speed : uint8
		{
			LOW,
			MEDIUM,
			HIGH,
			VERY_HIGH
		};
		
		enum class e_pupd : uint8
		{
			NONE,
			PULL_UP,
			PULL_DOWN
		};
		
		
		
		
		
		enum class e_AF : uint16
		{
			A0_TIMER2CH1		= 0x002,
			A0_USART2CTS		= 0x004,
			A0_TIMER2ETR		= 0x005,
			
			A1_EVENTOUT			= 0x010,
			A1_TIMER2CH2		= 0x012,
			A1_USART2RTS		= 0x014,
			A1_TIMER21ETR		= 0x015,
			
			A2_TIMER21CH1		= 0x020,
			A2_TIMER2CH3		= 0x022,
			A2_USART2TX			= 0x024,
			
			A3_TIMER21CH2		= 0x030,
			A3_TIMER2CH4		= 0x032,
			A3_USART2RX			= 0x034,
			
			A4_SPI1NSS			= 0x040,
			A4_USART2CK			= 0x044,
			
			A5_SPI1SCK			= 0x050,
			A5_TIMER2ETR		= 0x052,
			A5_TIMER2CH1		= 0x055,
			
			A6_SPI1MISO			= 0x060,
			A6_EVENTOUT			= 0x066,
			
			A7_SPI1MOSI			= 0x070,
			A7_EVENTOUT			= 0x076,
			
			A8_MCO					= 0x080,
			A8_EVENTOUT			= 0x083,
			
			A9_MCO					= 0x090,
			
			A11_SPI1MISO		= 0x0B0,
			A11_EVENTOUT		= 0x0B2,
			
			A12_SPI1MOSI		= 0x0C0,
			A12_EVENTOUT		= 0x0C2,
			
			A13_SWDIO				= 0x0D0,
			
			A14_SWDCLK			= 0x0E0,
			A14_USART2TX		= 0x0E4,
			
			A15_SPI1NSS			= 0x0F0,
			A15_TIMER2ETR		= 0x0F2,
			A15_EVENTOUT		= 0x0F3,
			A15_USART2RX		= 0x0F4,
			A15_TIMER2CH1		= 0x0F5,
			
			
			
			
			
			B0_EVENTOUT			= 0x100,
			
			B2_LPTIMER1OUT	= 0x122,
			
			B3_SPI1SCK			= 0x130,
			B3_TIMER2CH2		= 0x132,
			B3_EVENTOUT			= 0x134,
			
			B4_SPI1MISO			= 0x140,
			B4_EVENTOUT			= 0x142,
			
			B5_SPI1MOSI			= 0x150,
			B5_LPTIMER1IN1	= 0x152,
			B5_I2C1SMBA			= 0x153,
			
			B6_I2C1SCL			= 0x161,
			B6_LPTIMER1ETR	= 0x162,
			
			B7_I2C1SDA			= 0x171,
			B7_LPTIMER1IN2	= 0x172,
			
			B8_I2C1SCL			= 0x184,
			
			B9_EVENTOUT			= 0x192,
			B9_I2C1SDA			= 0x194,
			
			B10_TIMER2CH3		= 0x1A2,
			
			B11_EVENTOUT		= 0x1B0,
			B11_TIMER2CH4		= 0x1B2,
			
			B12_EVENTOUT		= 0x1C6,
			
			B13_TIMER21CH1	= 0x1D6,
			
			B14_RTCOUT			= 0x1E2,
			B14_TIMER21CH2	= 0x1E6,
			
			B15_RTCREFIN		= 0x1F2
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline GPIO();
		GPIO(const GPIO& gpio) = delete;
		inline ~GPIO();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32L010K8T6;
		
		
		
		
		
	public:
		
		feedback init_pin(e_pin pin, e_mode mode, e_speed speed = e_speed::VERY_HIGH, e_pupd pupd = e_pupd::NONE);
		void set_pin(e_pin pin);
		void clear_pin(e_pin pin);
		void toggle_pin(e_pin pin);
		bool get_pinLevel(e_pin pin);
		feedback set_AF(e_AF alternateFunction);
		
		static constexpr inline uint8 get_pinNumber(e_pin pin);
		static constexpr inline uint8 get_portNumber(e_pin pin);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline GPIO::GPIO()
{
	
}


inline GPIO::~GPIO()
{
	
}







inline feedback GPIO::startup(RCC& rcc)
{
	rcc.module_reset(RCC::e_module::GPIO_A);
	rcc.module_clockInit(RCC::e_module::GPIO_A, true);
	
	rcc.module_reset(RCC::e_module::GPIO_B);
	rcc.module_clockInit(RCC::e_module::GPIO_B, true);
	
	rcc.module_reset(RCC::e_module::GPIO_C);
	rcc.module_clockInit(RCC::e_module::GPIO_C, true);
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void GPIO::set_pin(e_pin pin)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	volatile uint32* address = MCU::GPIO_A::BSRR + port * 0x00000100;
	bit::set(*address, pinNumber);
}


inline void GPIO::clear_pin(e_pin pin)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	volatile uint32* address = MCU::GPIO_A::BSRR + port * 0x00000100;
	bit::set(*address, pinNumber + 16);
}


inline void GPIO::toggle_pin(e_pin pin)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	volatile uint32* address = MCU::GPIO_A::ODR + port * 0x00000100;
	if(bit::isSet(*address, pinNumber))
	{
		clear_pin(pin);
	}
	else
	{
		set_pin(pin);
	}
}


inline bool GPIO::get_pinLevel(e_pin pin)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	volatile uint32* address = MCU::GPIO_A::IDR + port * 0x00000100;
	if(bit::isSet(*address, pinNumber))
	{
		return(true);
	}
	return(false);
}


inline feedback GPIO::set_AF(e_AF alternateFunction)
{
	const uint32 port = (((uint32) alternateFunction) & 0x00000F00) >> 8;
	
	uint32 mask = ((uint32) alternateFunction) & 0x000000FF;
	uint8 pin = (mask & 0xF0) >> 4;
	uint32 offset = 0;
	
	if(pin < 8)
	{
		volatile uint32* address = MCU::GPIO_A::AFRL + port * 0x00000100;
		offset = 4 * pin;
		uint32 temp = *address & (0xFFFFFFFF - (0x0000000F << offset));
		*address = temp | ((mask & 0x0F) << offset);
	}
	else
	{
		pin -= 8;
		volatile uint32* address = MCU::GPIO_A::AFRH + port * 0x00000100;
		offset = 4 * pin;
		uint32 temp = *address & (0xFFFFFFFF - (0x0000000F << offset));
		*address = temp | ((mask & 0x0F) << offset);
	}
	
	return(OK);
}







constexpr inline uint8 GPIO::get_pinNumber(e_pin pin)
{
	uint8 number = (uint8) pin;
	return(number & 0x0F);
}


constexpr inline uint8 GPIO::get_portNumber(e_pin pin)
{
	uint8 number = (uint8) pin;
	return((number & 0xF0) >> 4);
}