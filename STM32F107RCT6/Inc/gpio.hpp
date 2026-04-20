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
		
		D0	= 0x30,
		D1	= 0x31,
		D2	= 0x32
	};
	
	enum class AF: uint16
	{
		
	};
	
	enum class PORT : uint8
	{
		A = 0,
		B = 1,
		C = 2,
		D = 3
	};
};





class GPIO: public I_GPIO
{
	public:
		/*
		enum class e_speed
		{
			MEDIUM										= 0x1,
			LOW												= 0x2,
			HIGH											= 0x3
		};
		*/
		
		
		
		
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
		friend class STM32F107RCT6;
		
		
		
		
		
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
	
	rcc.module_reset(RCC::e_module::GPIO_C);
	rcc.module_clockInit(RCC::e_module::GPIO_C, true);
	
	rcc.module_reset(RCC::e_module::GPIO_D);
	rcc.module_clockInit(RCC::e_module::GPIO_D, true);
	
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
	const uint32 port = ((uint32) pin) >> 4;
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	
	volatile uint32* address = MCU::GPIO_A::BSRR + port * 0x00000100;
	bit::set(*address, pinNumber);
}


inline void GPIO::clear_pin(MCU::PIN pin)
{
	const uint32 port = ((uint32) pin) >> 4;
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	
	volatile uint32* address = MCU::GPIO_A::BSRR + port * 0x00000100;
	bit::set(*address, pinNumber + 16);
}


inline void GPIO::toggle_pin(MCU::PIN pin)
{
	const uint32 port = ((uint32) pin) >> 4;
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	
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
	const uint32 port = ((uint32) pin) >> 4;
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	
	volatile uint32* address = MCU::GPIO_A::IDR + port * 0x00000100;
	if(bit::isSet(*address, pinNumber))
	{
		return(true);
	}
	return(false);
}


inline feedback GPIO::set_AF(MCU::AF alternateFunction)
{
	//	Not available for STM32F107RCT6 - alternate functions are hardwired
	return(FAIL);
}







inline feedback GPIO::init_portAsInput(MCU::PORT port)
{
	volatile uint32* CRL = MCU::GPIO_A::CRL + ((uint32) port) * 0x00000100;
	volatile uint32* CRH = MCU::GPIO_A::CRH + ((uint32) port) * 0x00000100;
	*CRL = 0x44444444;
	*CRH = 0x44444444;
	return(OK);
}


inline feedback GPIO::init_portAsOutput(MCU::PORT port)
{
	volatile uint32* CRL = MCU::GPIO_A::CRL + ((uint32) port) * 0x00000100;
	volatile uint32* CRH = MCU::GPIO_A::CRH + ((uint32) port) * 0x00000100;
	*CRL = 0x33333333;
	*CRH = 0x33333333;
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