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
			
			C6	= 0x26,
			C14	= 0x2E,
			C15	= 0x2F,
			
			F2	= 0x52
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
			A0_USART2CTS			= 0x001,
			A0_TIMER16CH1			= 0x002,
			A0_USART1TX				= 0x004,
			A0_TIMER1CH1			= 0x005,
			
			A1_SPISCK					= 0x010,
			A1_USART2RTSDECK	= 0x011,
			A1_TIMER17CH1			= 0x012,
			A1_USART1RX				= 0x014,
			A1_TIMER1CH2			= 0x015,
			A1_I2CSMBA				= 0x016,
			A1_EVENTOUT				= 0x017,
			
			A2_SPIMOSI				= 0x020,
			A2_USART2TX				= 0x021,
			A2_TIMER16CH1N		= 0x022,
			A2_TIMER3ETR			= 0x023,
			A2_TIMER1CH3			= 0x025,
			
			A3_USART2RX				= 0x031,
			A3_TIMER1CH1N			= 0x032,
			A3_TIMER1CH4			= 0x035,
			A3_EVENTOUT				= 0x037,
			
			A4_SPINSS					= 0x040,
			A4_USART2TX				= 0x041,
			A4_TIMER1CH2N			= 0x042,
			A4_TIMER14CH1			= 0x044,
			A4_TIMER17CH1N		= 0x045,
			A4_EVENTOUT				= 0x047,
			
			A5_SPISCK					= 0x050,
			A5_USART2RX				= 0x051,
			A5_TIMER1CH3N			= 0x052,
			A5_TIMER1CH1			= 0x055,
			A5_EVENTOUT				= 0x057,
			
			A6_SPIMISO				= 0x060,
			A6_TIMER3CH1			= 0x061,
			A6_TIMER1BKIN			= 0x062,
			A6_TIMER16CH1			= 0x065,
			
			A7_SPIMOSI				= 0x070,
			A7_TIMER3CH2			= 0x071,
			A7_TIMER1CH1N			= 0x072,
			A7_TIMER14CH1			= 0x074,
			A7_TIMER17CH1			= 0x075,
			
			A8_MCO						= 0x080,
			A8_USART2TX				= 0x081,
			A8_TIMER1CH1			= 0x082,
			A8_EVENTOUT				= 0x087,
			A8_SPINSS					= 0x088,
			A8_TIMER1CH2N			= 0x089,
			A8_TIMER1CH3N			= 0x08A,
			A8_TIMER3CH3			= 0x08B,
			A8_TIMER3CH4			= 0x08C,
			A8_TIMER14CH1			= 0x08D,
			A8_USART1RX				= 0x08E,
			A8_MCO2						= 0x08F,
			
			A9_MCO						= 0x090,
			A9_USART1TX				= 0x091,
			A9_TIMER1CH2			= 0x092,
			A9_TIMER3ETR			= 0x093,
			A9_I2CSCL					= 0x096,
			A9_EVENTOUT				= 0x097,
			
			A10_USART1RX			= 0x0A1,
			A10_TIMER1CH3			= 0x0A2,
			A10_MCO2					= 0x0A3,
			A10_TIMER17BKIN		= 0x0A5,
			A10_I2CSDA				= 0x0A6,
			A10_EVENTOUT			= 0x0A7,
			
			A11_SPIMISO				= 0x0B0,
			A11_USART1CTS			= 0x0B1,
			A11_TIMER1CH4			= 0x0B2,
			A11_TIMER1BKIN2		= 0x0B5,
			
			A12_SPIMOSI				= 0x0C0,
			A12_USART1RTSDECK	= 0x0C1,
			A12_TIMER1ETR			= 0x0C2,
			A12_I2SCKIN				= 0x0C5,
			
			A13_SWDIO					= 0x0D0,
			A13_IROUT					= 0x0D1,
			A13_TIMER3ETR			= 0x0D3,
			A13_USART2RX			= 0x0D4,
			A13_EVENTOUT			= 0x0D7,
			
			A14_SWDCLK				= 0x0E0,
			A14_USART2TX			= 0x0E1,
			A14_EVENTOUT			= 0x0E7,
			A14_SPINSS				= 0x0E8,
			A14_USART2RX			= 0x0E9,
			A14_TIMER1CH1			= 0x0EA,
			A14_MCO2					= 0x0EB,
			A14_USART1RTSDECK	= 0x0EC,
			
			A15_SPINSS				= 0x0F0,
			A15_USART2RX			= 0x0F1,
			A15_TIMER1CH1			= 0x0F2,
			A15_MCO2					= 0x0F3,
			A15_USART1RTSDECK	= 0x0F4,
			A15_EVENTOUT			= 0x0F7,
			
			
			
			
			
			B0_SPINSS					= 0x100,
			B0_TIMER3CH3			= 0x101,
			B0_TIMER1CH2N			= 0x102,
			
			B1_TIMER14CH1			= 0x110,
			B1_TIMER3CH4			= 0x111,
			B1_TIMER1CH3N			= 0x112,
			B1_TIMER1CH2N			= 0x115,
			B1_EVENTOUT				= 0x117,
			
			B2_USART1RX				= 0x120,
			B2_MCO2						= 0x123,
			B2_EVENTOUT				= 0x127,
			
			B3_SPISCK					= 0x130,
			B3_TIMER1CH2			= 0x131,
			B3_TIMER3CH2			= 0x133,
			B3_USART1RTSDECK	= 0x134,
			B3_EVENTOUT				= 0x137,
			
			B4_SPIMISO				= 0x140,
			B4_TIMER3CH1			= 0x141,
			B4_USART1CTS			= 0x144,
			B4_TIMER17BKIN		= 0x145,
			B4_EVENTOUT				= 0x147,
			
			B5_SPIMOSI				= 0x150,
			B5_TIMER3CH2			= 0x151,
			B5_TIMER16_BKIN		= 0x152,
			B5_TIMER3CH3			= 0x153,
			B5_I2CSMBA				= 0x156,
			
			B6_USART1TX				= 0x160,
			B6_TIMER1CH3			= 0x161,
			B6_TIMER16CH1N		= 0x162,
			B6_TIMER3CH3			= 0x163,
			B6_USART1RTSDECK	= 0x164,
			B6_USART1CTS			= 0x165,
			B6_I2CSCL					= 0x166,
			B6_I2CSMBA				= 0x167,
			B6_SPIMOSI				= 0x168,
			B6_SPIMISO				= 0x169,
			B6_SPISCK					= 0x16A,
			B6_TIMER1CH2			= 0x16B,
			B6_TIMER3CH1			= 0x16C,
			B6_TIMER3CH2			= 0x16D,
			B6_TIMER16BKIN		= 0x16E,
			B6_TIMER17BKIN		= 0x16F,
			
			B7_USART1RX				= 0x170,
			B7_TIMER1CH4			= 0x171,
			B7_TIMER17CH1N		= 0x172,
			B7_TIMER3CH4			= 0x173,
			B7_I2CSDA					= 0x176,
			B7_EVENTOUT				= 0x177,
			B7_USART2CTS			= 0x179,
			B7_TIMER16CH1			= 0x17A,
			B7_TIMER3CH1			= 0x17B,
			B7_I2CSCL					= 0x17E,
			
			B8_USART2CTS			= 0x181,
			B8_TIMER16CH1			= 0x182,
			B8_TIMER3CH1			= 0x183,
			B8_IC2SCL					= 0x186,
			B8_EVENTOUT				= 0x187,
			
			B9_IROUT					= 0x190,
			B9_USART2RTSDECK	= 0x191,
			B9_TIMER17CH1			= 0x192,
			B9_TIMER3CH2			= 0x193,
			B9_I2CSDA					= 0x196,
			B9_EVENTOUT				= 0x197,
			
			B12_TIMER1BKIN2		= 0x1C1,
			B12_TIMER1BKIN		= 0x1C2,
			B12_EVENTOUT			= 0x1C7,
			
			B13_TIMER1CH1N		= 0x1D2,
			B13_EVENTOUT			= 0x1D7,
			
			B14_TIMER1CH2N		= 0x1E2,
			B14_EVENTOUT			= 0x1E7,
			
			B15_TIMER1CH3N		= 0x1F2,
			B15_EVENTOUT			= 0x1F7,
			
			
			
			
			
			C6_TIMER3CH1			= 0x261,
			
			C14_USART1TX			= 0x2E0,
			C14_TIMER1ETR			= 0x2E1,
			C14_TIMER1BKIN2		= 0x2E2,
			C14_IROUT					= 0x2E8,
			C14_USART2RTSDECK	= 0x2E9,
			C14_TIMER17CH1		= 0x2EA,
			C14_TIMER3CH2			= 0x2EB,
			C14_I2CSDA				= 0x2EE,
			C14_EVENTOUT			= 0x2EF,
			
			C15_OSC32EN				= 0x2F0,
			C15_OSCEN					= 0x2F1,
			C15_TIMER1ETR			= 0x2F2,
			C15_TIMER3CH3			= 0x2F3,
			
			
			
			
			
			F2_MCO						= 0x520,
			F2_TIMER1CH4			= 0x521
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
		friend class STM32C031K6U6;
		
		
		
		
		
	public:
		
		feedback init_pin(e_pin pin, e_mode mode, e_speed speed = e_speed::VERY_HIGH, e_pupd pupd = e_pupd::NONE);
		inline void set_pin(e_pin pin);
		inline void clear_pin(e_pin pin);
		inline void toggle_pin(e_pin pin);
		inline bool get_pinLevel(e_pin pin);
		inline feedback set_AF(e_AF alternateFunction);
		
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
	
	rcc.module_reset(RCC::e_module::GPIO_F);
	rcc.module_clockInit(RCC::e_module::GPIO_F, true);
	
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