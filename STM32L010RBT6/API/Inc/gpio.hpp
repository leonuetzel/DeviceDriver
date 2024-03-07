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
			B2	= 0x12,
			B3	= 0x13,
			B4	= 0x14,
			B5	= 0x15,
			B6	= 0x16,
			B7	= 0x17,
			B8	= 0x18,
			B9	= 0x19,
			B10	= 0x1A,
			B11	= 0x1B,
			B12	= 0x1C,
			B13	= 0x1D,
			B14	= 0x1E,
			B15	= 0x1F,
			
			C0	= 0x20,
			C1	= 0x21,
			C2	= 0x22,
			C3	= 0x23,
			C4	= 0x24,
			C5	= 0x25,
			C6	= 0x26,
			C7	= 0x27,
			C8	= 0x28,
			C9	= 0x29,
			C10	= 0x2A,
			C11	= 0x2B,
			C12	= 0x2C,
			C13	= 0x2D,
			C14	= 0x2E,
			C15	= 0x2F,
			
			D2	= 0x32,
			
			H0	= 0x70,
			H1	= 0x71
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
			A2_LPUART1TX		= 0x026,
			
			A3_TIMER21CH2		= 0x030,
			A3_TIMER2CH4		= 0x032,
			A3_USART2RX			= 0x034,
			A3_LPUART1RX		= 0x036,
			
			A4_SPI1NSS			= 0x040,
			A4_USART2CK			= 0x044,
			A4_TIMER22ETR		= 0x045,
			
			A5_SPI1SCK			= 0x050,
			A5_TIMER2ETR		= 0x052,
			A5_TIMER2CH1		= 0x055,
			
			A6_SPI1MISO			= 0x060,
			A6_LPUART1CTS		= 0x064,
			A6_TIMER22CH1		= 0x065,
			A6_EVENTOUT			= 0x066,
			
			A7_SPI1MOSI			= 0x070,
			A7_TIMER22CH2		= 0x075,
			A7_EVENTOUT			= 0x076,
			
			A8_MCO					= 0x080,
			A8_EVENTOUT			= 0x083,
			
			A9_MCO					= 0x090,
			A9_I2C1SCL			= 0x096,
			
			A10_I2C1SDA			= 0x0A6,
			
			A11_SPI1MISO		= 0x0B0,
			A11_EVENTOUT		= 0x0B2,
			
			A12_SPI1MOSI		= 0x0C0,
			A12_EVENTOUT		= 0x0C2,
			
			A13_SWDIO				= 0x0D0,
			A13_LPUART1RX		= 0x0D6,
			
			A14_SWDCLK			= 0x0E0,
			A14_USART2TX		= 0x0E4,
			A14_LPUART1TX		= 0x0E6,
			
			A15_SPI1NSS			= 0x0F0,
			A15_TIMER2ETR		= 0x0F2,
			A15_EVENTOUT		= 0x0F3,
			A15_USART2RX		= 0x0F4,
			A15_TIMER2CH1		= 0x0F5,
			
			
			
			
			
			B0_EVENTOUT			= 0x100,
			
			B1_LPUART1RTS		= 0x114,
			
			B2_LPTIMER1OUT	= 0x122,
			
			B3_SPI1SCK			= 0x130,
			B3_TIMER2CH2		= 0x132,
			B3_EVENTOUT			= 0x134,
			
			B4_SPI1MISO			= 0x140,
			B4_TIMER22CH1		= 0x144,
			
			B5_SPI1MOSI			= 0x150,
			B5_LPTIMER1IN1	= 0x152,
			B5_I2C1SMBA			= 0x153,
			B5_TIMER22CH2		= 0x154,
			
			B6_I2C1SCL			= 0x161,
			B6_LPTIMER1ETR	= 0x162,
			
			B7_I2C1SDA			= 0x171,
			B7_LPTIMER1IN2	= 0x172,
			
			B8_I2C1SCL			= 0x184,
			
			B9_EVENTOUT			= 0x192,
			B9_I2C1SDA			= 0x194,
			
			B10_TIMER2CH3		= 0x1A2,
			B10_LPUART1TX		= 0x1A4,
			B10_LPUART1RX		= 0x1A7,
			
			B11_EVENTOUT		= 0x1B0,
			B11_TIMER2CH4		= 0x1B2,
			B11_LPUART1RX		= 0x1B4,
			B11_LPUART1TX		= 0x1B7,
			
			B12_LPUART1RTS	= 0x1C2,
			B12_EVENTOUT		= 0x1C6,
			
			B13_MCO					= 0x1D2,
			B13_LPUART1CTS	= 0x1D4,
			B13_TIMER21CH1	= 0x1D6,
			
			B14_RTCOUT			= 0x1E2,
			B14_LPUART1RTS	= 0x1E4,
			B14_TIMER21CH2	= 0x1E6,
			
			B15_RTCREFIN		= 0x1F2,
			
			
			
			
			
			C0_LPTIMER1IN1	= 0x200,
			C0_EVENTOUT			= 0x202,
			C0_LPUART1RX		= 0x206,
			
			C1_LPTIMER1OUT	= 0x210,
			C1_EVENTOUT			= 0x212,
			C1_LPUART1TX		= 0x216,
			
			C2_LPTIMER1IN2	= 0x220,
			
			C3_LPTIMER1ETR	= 0x230,
			
			C4_EVENTOUT			= 0x240,
			C4_LPUART1TX		= 0x242,
			
			C5_LPUART1RX		= 0x252,
			
			C6_TIMER22CH1		= 0x260,
			
			C7_TIMER22CH2		= 0x270,
			
			C8_TIMER22ETR		= 0x280,
			
			C9_TIMER21ETR		= 0x290,
			
			C10_LPUART1TX		= 0x2A0,
			
			C11_LPUART1RX		= 0x2B0,
			
			
			
			
			
			D2_LPUART1RTS		= 0x320
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
		friend class STM32L010RBT6;
		
		
		
		
		
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
	
	rcc.module_reset(RCC::e_module::GPIO_D);
	rcc.module_clockInit(RCC::e_module::GPIO_D, true);
	
	rcc.module_reset(RCC::e_module::GPIO_H);
	rcc.module_clockInit(RCC::e_module::GPIO_H, true);
	
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