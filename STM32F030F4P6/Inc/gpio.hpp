#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





namespace MCU
{
	enum class PIN : uint8
	{
		A0	= 0x00,
		A1	= 0x01,
		A2	= 0x02,
		A3	= 0x03,
		A4	= 0x04,
		A5	= 0x05,
		A6	= 0x06,
		A7	= 0x07,
		
		A9	= 0x09,
		A10	= 0x0A,
		
		
		A13	= 0x0D,
		A14	= 0x0E,
		
		
		
		B1	= 0x11,
		
		F0	= 0x50,
		F1	= 0x51
	};
	
	enum class AF : uint16
	{
		A0_USART1CTS		= 0x001,
		
		A1_EVENTOUT			= 0x010,
		A1_USART1RTS		= 0x011,
		
		A2_USART1TX			= 0x021,
		
		A3_USART1RX			= 0x031,
		
		A4_SPI1NSS			= 0x040,
		A4_USART1CK			= 0x041,
		A4_TIMER14CH1		= 0x044,
		
		A5_SPI1SCK			= 0x050,
		
		A6_SPI1MISO			= 0x060,
		A6_TIMER3CH1		= 0x061,
		A6_TIMER1BKIN		= 0x062,
		A6_TIMER16CH1		= 0x065,
		
		A7_SPI1MOSI			= 0x070,
		A7_TIMER3CH2		= 0x071,
		A7_TIMER1CH1N		= 0x072,
		A7_TIMER14CH1		= 0x074,
		A7_TIMER17CH1		= 0x075,
		A7_EVENTOUT			= 0x076,
		
		A8_MCO					= 0x080,
		A8_USART1CK			= 0x081,
		A8_TIMER1CH1		= 0x082,
		A8_EVENTOUT			= 0x083,
		
		A9_USART1TX			= 0x091,
		A9_TIMER1CH2		= 0x092,
		A9_I2C1SCL			= 0x094,
		
		A10_TIMER17BKIN	= 0x0A0,
		A10_USART1RX		= 0x0A1,
		A10_TIMER1CH3		= 0x0A2,
		A10_I2C1SDA			= 0x0A4,
		
		
		
		
		
		
		
		B1_TIMER14CH1		= 0x110,
		B1_TIMER3CH4		= 0x111,
		B1_TIMER1CH3N		= 0x112
	};
	
	enum class PORT : uint8
	{
		A = 0,
		B = 1,
		F = 5
	};
};





class GPIO: public I_GPIO
{
	public:
	
	
	
	
	
	
	
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
		friend class STM32F030F4P6;
	
	
	
	
	
	public:
	
	feedback init_pin(MCU::PIN pin, e_mode mode, e_speed speed = e_speed::HIGH, e_pupd pupd = e_pupd::NONE) override;
	inline void set_pin(MCU::PIN pin) override;
	inline void clear_pin(MCU::PIN pin) override;
	inline void toggle_pin(MCU::PIN pin) override;
	inline bool get_pinLevel(MCU::PIN pin) override;
	inline feedback set_AF(MCU::AF alternateFunction) override;
	
	inline feedback init_portAsInput(MCU::PORT port) override;
	inline feedback init_portAsOutput(MCU::PORT port) override;
	inline void write_port(MCU::PORT port, uint32 data) override;
	inline uint32 read_port(MCU::PORT port) override;
	
	inline uint8 get_pinNumber(MCU::PIN pin) override;
	inline uint8 get_portNumber(MCU::PIN pin) override;
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

inline void GPIO::set_pin(MCU::PIN pin)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	volatile uint32* address = MCU::GPIO_A::BSRR + port * 0x00000100;
	bit::set(*address, pinNumber);
}


inline void GPIO::clear_pin(MCU::PIN pin)
{
	const uint32 port = get_portNumber(pin);
	const uint32 pinNumber = get_pinNumber(pin);
	
	volatile uint32* address = MCU::GPIO_A::BSRR + port * 0x00000100;
	bit::set(*address, pinNumber + 16);
}


inline void GPIO::toggle_pin(MCU::PIN pin)
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


inline bool GPIO::get_pinLevel(MCU::PIN pin)
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


inline feedback GPIO::set_AF(MCU::AF alternateFunction)
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







inline feedback GPIO::init_portAsInput(MCU::PORT port)
{
	volatile uint32* address = MCU::GPIO_A::MODE + ((uint32) port) * 0x00000100;
	*address = 0x00000000;
	return(OK);
}


inline feedback GPIO::init_portAsOutput(MCU::PORT port)
{
	volatile uint32* address = MCU::GPIO_A::MODE + ((uint32) port) * 0x00000100;
	*address = 0x55555555;
	return(OK);
}


inline void GPIO::write_port(MCU::PORT port, uint32 data)
{
	volatile uint32* address = MCU::GPIO_A::ODR + ((uint32) port) * 0x00000100;
	*address = (uint16) data;
}


inline uint32 GPIO::read_port(MCU::PORT port)
{
	volatile uint32* address = MCU::GPIO_A::IDR + ((uint32) port) * 0x00000100;
	return(*address & 0x0000FFFF);
}







inline uint8 GPIO::get_pinNumber(MCU::PIN pin)
{
	uint8 number = (uint8) pin;
	return(number & 0x0F);
}


inline uint8 GPIO::get_portNumber(MCU::PIN pin)
{
	uint8 number = (uint8) pin;
	return((number & 0xF0) >> 4);
}