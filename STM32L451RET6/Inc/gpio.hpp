#pragma once

#include "registers.hpp"
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
			H1	= 0x71,
			H3	= 0x73,
		};
		
		enum class e_mode
		{
			IN					= 0x0,
			OUT_GP_PP		= 0x2,
			OUT_GP_OD		= 0x3,
			AF_PP				= 0x4,
			AF_OD				= 0x5,
			ANALOG			= 0x6
		};
		
		enum class e_speed
		{
			LOW					= 0x0,
			MEDIUM			= 0x1,
			HIGH				= 0x2,
			VERY_HIGH		= 0x3
		};
		
		enum class e_pupd
		{
			NONE				= 0x0,
			PULL_UP			= 0x1,
			PULL_DOWN		= 0x2
		};
		
		
		enum class e_AF
		{
			A0_TIMER2CH1										= 0x001,
			A0_USART2CTS										= 0x007,
			A0_UART4TX											= 0x008,
			A0_COMP1OUT											= 0x00C,
			A0_SAI1EXTCLK										= 0x00D,
			A0_TIMER2ETR										= 0x00E,
			A0_EVENTOUT											= 0x00F,
			
			A1_TIMER2CH2										= 0x011,
			A1_I2C1SMBA											= 0x014,
			A1_SPI1SCK											= 0x015,
			A1_USART2RTSDE									= 0x017,
			A1_UART4RX											= 0x018,
			A1_TIMER15CH1N									= 0x01E,
			A1_EVENTOUT											= 0x01F,
			
			A2_TIMER2CH3										= 0x021,
			A2_USART2TX											= 0x027,
			A2_LPUART1TX										= 0x028,
			A2_QUADSPIBK1NCS								= 0x02A,
			A2_COMP2OUT											= 0x02C,
			A2_TIMER15CH1										= 0x02E,
			A2_EVENTOUT											= 0x02F,
			
			A3_TIMER2CH4										= 0x031,
			A3_USART2RX											= 0x037,
			A3_LPUART1RX										= 0x038,
			A3_QUADSPICLK										= 0x03A,
			A3_SAI1MCLKA										= 0x03D,
			A3_TIMER15CH2										= 0x03E,
			A3_EVENTOUT											= 0x03F,
			
			A4_SPI1NSS											= 0x045,
			A4_SPI3NSS											= 0x046,
			A4_USART2CK											= 0x047,
			A4_SAI1FSB											= 0x04D,
			A4_LPTIMER2OUT									= 0x04E,
			A4_EVENTOUT											= 0x04F,
			
			A5_TIMER2CH1										= 0x051,
			A5_TIMER2ETR										= 0x052,
			A5_SPI1SCK											= 0x055,
			A5_DFSDM1CKOUT									= 0x056,
			A5_LPTIMER2ETR									= 0x05E,
			A5_EVENTOUT											= 0x05F,
			
			A6_TIMER1BKIN										= 0x061,
			A6_TIMER3CH1										= 0x062,
			A6_SPI1MISO											= 0x065,
			A6_COMP1OUT											= 0x066,
			A6_USART3CTS										= 0x067,
			A6_LPUART1CTS										= 0x068,
			A6_QUADSPIBK1IO3								= 0x06A,
			A6_TIMER1BKINCOMP2							= 0x06C,
			A6_TIMER16CH1										= 0x06E,
			A6_EVENTOUT											= 0x06F,
			
			A7_TIMER1CH1N										= 0x071,
			A7_TIMER3CH2										= 0x072,
			A7_I2C3SCL											= 0x074,
			A7_SPI1MOSI											= 0x075,
			A7_DFSDM1DATIN0									= 0x076,
			A7_QUADSPIBK1IO2								= 0x07A,
			A7_COMP2OUT											= 0x07C,
			A7_EVENTOUT											= 0x07F,
			
			A8_MCO													= 0x080,
			A8_TIMER1CH1										= 0x081,
			A8_DFSDM1CKIN1									= 0x086,
			A8_USART1CK											= 0x087,
			A8_SAI1SCKA											= 0x08D,
			A8_LPTIMER2OUT									= 0x08E,
			A8_EVENTOUT											= 0x08F,
			
			A9_TIMER1CH2										= 0x091,
			A9_I2C1SCL											= 0x094,
			A9_DFSDM1_DATIN1								= 0x096,
			A9_USART1TX											= 0x097,
			A9_SAI1FSA											= 0x09D,
			A9_TIMER15BKIN									= 0x09E,
			A9_EVENTOUT											= 0x09F,
			
			A10_TIMER1CH3										= 0x0A1,
			A10_I2C1SDA											= 0x0A4,
			A10_USART1RX										= 0x0A7,
			A10_SAI1SDA											= 0x0AD,
			A10_EVENTOUT										= 0x0AF,
			
			A11_TIMER1CH4										= 0x0B1,
			A11_TIMER1BKIN2									= 0x0B2,
			A11_SPI1MISO										= 0x0B5,
			A11_COMP1OUT										= 0x0B6,
			A11_USART1CTS										= 0x0B7,
			A11_CAN1RX											= 0x0B9,
			A11_TIMER1BKIN2COMP1						= 0x0BC,
			A11_EVENTOUT										= 0x0BF,
			
			A12_TIMER1ETR										= 0x0C1,
			A12_SPI1MOSI										= 0x0C5,
			A12_USART1RTSDE									= 0x0C7,
			A12_CAN1TX											= 0x0C9,
			A12_EVENTOUT										= 0x0CF,
			
			A13_JTMS_SWDAT									= 0x0D0,
			A13_IROUT												= 0x0D1,
			A13_SAI1SDB											= 0x0DD,
			A13_EVENTOUT										= 0x0DF,
			
			A14_JTCK_SWCLK									= 0x0E0,
			A14_LPTIMER1OUT									= 0x0E1,
			A14_I2C1SMBA										= 0x0E4,
			A14_I2C4SMBA										= 0x0E5,
			A14_SAI1FSB											= 0x0ED,
			A14_EVENTOUT										= 0x0EF,
			
			A15_JTDI												= 0x0F0,
			A15_TIMER2CH1										= 0x0F1,
			A15_TIMER2ETR										= 0x0F2,
			A15_USART2RX										= 0x0F3,
			A15_SPI1NSS											= 0x0F5,
			A15_SPI3NSS											= 0x0F6,
			A15_USART3RTSDE									= 0x0F7,
			A15_UART4RTSDE									= 0x0F8,
			A15_TSCG3IO1										= 0x0F9,
			A15_EVENTOUT										= 0x0FF,
			
			
			
			
			
			
			
			B0_TIMER1CH2N										= 0x101,
			B0_TIMER3CH3										= 0x102,
			B0_SPI1NSS											= 0x105,
			B0_DFSDM1CKIN0									= 0x106,
			B0_USART3CK											= 0x107,
			B0_QUADSPIBK1IO1								= 0x10A,
			B0_COMP1OUT											= 0x10C,
			B0_SAI1EXTCLK										= 0x10D,
			B0_EVENTOUT											= 0x10F,
			
			B1_TIMER1CH3N										= 0x111,
			B1_TIMER3CH4										= 0x112,
			B1_DFSDM1DATIN0									= 0x116,
			B1_USART3RTSDE									= 0x117,
			B1_LPUART1RTSDE									= 0x118,
			B1_QUADSPIBK1IO0								= 0x11A,
			B1_LPTIMER2IN1									= 0x11E,
			B1_EVENTOUT											= 0x11F,
			
			B2_RTCOUT												= 0x120,
			B2_LPTIMER1OUT									= 0x121,
			B2_I2C3SMBA											= 0x124,
			B2_DFSDM1CKIN0									= 0x126,
			B2_EVENTOUT											= 0x12F,
			
			B3_JTDO_TRACESWO								= 0x130,
			B3_TIMER2CH2										= 0x131,
			B3_SPI1SCK											= 0x135,
			B3_SPI3SCK											= 0x136,
			B3_USART1RTSDE									= 0x137,
			B3_SAI1SCKB											= 0x13D,
			B3_EVENTOUT											= 0x13F,
			
			B4_NJTRST												= 0x140,
			B4_TIMER3CH1										= 0x142,
			B4_I2C3SDA											= 0x144,
			B4_SPI1MISO											= 0x145,
			B4_SPI3MISO											= 0x146,
			B4_USART1CTS										= 0x147,
			B4_TSCG2IO1											= 0x149,
			B4_SAI1MCLKB										= 0x14D,
			B4_EVENTOUT											= 0x14F,
			
			B5_LPTIMER1IN1									= 0x151,
			B5_TIMER3CH2										= 0x152,
			B5_CAN1RX												= 0x153,
			B5_I2C1SMBA											= 0x154,
			B5_SPI1MOSI											= 0x155,
			B5_SPI3MOSI											= 0x156,
			B5_USART1CK											= 0x157,
			B5_TSCG2IO2											= 0x159,
			B5_COMP2OUT											= 0x15C,
			B5_SAI1SDB											= 0x15D,
			B5_TIMER16BKIN									= 0x15E,
			B5_EVENTOUT											= 0x15F,
			
			B6_LPTIMER1ETR									= 0x161,
			B6_I2C1SCL											= 0x164,
			B6_I2C4SCL											= 0x165,
			B6_USART1TX											= 0x167,
			B6_CAN1TX												= 0x168,
			B6_TSCG2IO3											= 0x169,
			B6_SAI1FSB											= 0x16D,
			B6_TIMER16CH1N									= 0x16E,
			B6_EVENTOUT											= 0x16F,
			
			B7_LPTIMER1IN2									= 0x171,
			B7_I2C1SDA											= 0x174,
			B7_I2C4SDA											= 0x175,
			B7_USART1RX											= 0x177,
			B7_UART4CTS											= 0x178,
			B7_TSCG2IO4											= 0x179,
			B7_EVENTOUT											= 0x17F,
			
			B8_I2C1SCL											= 0x184,
			B8_CAN1RX												= 0x189,
			B8_SDMMC1D4											= 0x18C,
			B8_SAI1MCLKA										= 0x18D,
			B8_TIMER16CH1										= 0x18E,
			B8_EVENTOUT											= 0x18F,
			
			B9_IROUT												= 0x191,
			B9_I2C1SDA											= 0x194,
			B9_SPI2NSS											= 0x195,
			B9_CAN1TX												= 0x199,
			B9_SDMMC1D5											= 0x19C,
			B9_SAI1FSA											= 0x19D,
			B9_EVENTOUT											= 0x19F,
			
			B10_TIMER2CH3										= 0x1A1,
			B10_I2C4SCL											= 0x1A3,
			B10_I2C2SCL											= 0x1A4,
			B10_SPI2SCK											= 0x1A5,
			B10_USART3TX										= 0x1A7,
			B10_LPUART1RX										= 0x1A8,
			B10_TSCSYNC											= 0x1A9,
			B10_QUADSPICLK									= 0x1AA,
			B10_COMP1OUT										= 0x1AC,
			B10_SAI1SCKA										= 0x1AD,
			B10_EVENTOUT										= 0x1AF,
			
			B11_TIMER2CH4										= 0x1B1,
			B11_I2C4SDA											= 0x1B3,
			B11_I2C2SDA											= 0x1B4,
			B11_USART3RX										= 0x1B7,
			B11_LPUART1TX										= 0x1B8,
			B11_QUADSPIBK1NCS								= 0x1BA,
			B11_COMP2OUT										= 0x1BC,
			B11_EVENTOUT										= 0x1BF,
			
			B12_TIMER1BKIN									= 0x1C1,
			B12_TIMER1BKINCOMP2							= 0x1C3,
			B12_I2C2SMBA										= 0x1C4,
			B12_SPI2NSS											= 0x1C5,
			B12_DFSDM1DATIN1								= 0x1C6,
			B12_USART3CK										= 0x1C7,
			B12_LPUART1RTSDE								= 0x1C8,
			B12_TSCG1IO1										= 0x1C9,
			B12_CAN1RX											= 0x1CA,
			B12_SAI1FSA											= 0x1CD,
			B12_TIMER15BKIN									= 0x1CE,
			B12_EVENTOUT										= 0x1CF,
			
			B13_TIMER1CH1N									= 0x1D1,
			B13_I2C2SCL											= 0x1D4,
			B13_SPI2SCK											= 0x1D5,
			B13_DFSDM1CKIN1									= 0x1D6,
			B13_USART3CTS										= 0x1D7,
			B13_LPUART1CTS									= 0x1D8,
			B13_TSCG1IO2										= 0x1D9,
			B13_CAN1TX											= 0x1DA,
			B13_SAI1SCKA										= 0x1DD,
			B13_TIMER15CH1N									= 0x1DE,
			B13_EVENTOUT										= 0x1DF,
			
			B14_TIMER1CH2N									= 0x1E1,
			B14_I2C2SDA											= 0x1E4,
			B14_SPI2MISO										= 0x1E5,
			B14_DFSDM1DATIN2								= 0x1E6,
			B14_USART3RTSDE									= 0x1E7,
			B14_TSCG1IO3										= 0x1E9,
			B14_SAI1MCLKA										= 0x1ED,
			B14_TIMER15CH1									= 0x1EE,
			B14_EVENTOUT										= 0x1EF,
			
			B15_RTCREFIN										= 0x1F0,
			B15_TIMER1CH3N									= 0x1F1,
			B15_SPI2MOSI										= 0x1F5,
			B15_DFSDM1CKIN2									= 0x1F6,
			B15_TCSG1IO4										= 0x1F9,
			B15_SAI1SDA											= 0x1FD,
			B15_TIMER15CH2									= 0x1FE,
			B15_EVENTOUT										= 0x1FF,
			
			
			
			
			
			
			
			C0_LPTIMER1IN1									= 0x201,
			C0_I2C4SCL											= 0x202,
			C0_I2C3SCL											= 0x204,
			C0_LPUART1RX										= 0x208,
			C0_LPTIMER2IN1									= 0x20E,
			C0_EVENTOUT											= 0x20F,
			
			C1_TRACED0											= 0x210,
			C1_LPTIMER1OUT									= 0x211,
			C1_I2C4SDA											= 0x212,
			C1_I2C3SDA											= 0x214,
			C1_LPUART1TX										= 0x218,
			C1_EVENTOUT											= 0x21F,
			
			C2_LPTIMER1IN2									= 0x221,
			C2_SPI2MISO											= 0x225,
			C2_DFSDM1CKOUT									= 0x226,
			C2_EVENTOUT											= 0x22F,
			
			C3_LPTIMER1ETR									= 0x231,
			C3_SPI2MOSI											= 0x235,
			C3_SAI1SDA											= 0x23D,
			C3_LPTIMER2ETR									= 0x23E,
			C3_EVENTOUT											= 0x23F,
			
			C4_USART3TX											= 0x247,
			C4_EVENTOUT											= 0x24F,
			
			C5_USART3RX											= 0x257,
			C5_EVENTOUT											= 0x25F,
			
			C6_TIMER3CH1										= 0x262,
			C6_DFSDM1CKIN3									= 0x266,
			C6_TSCG4IO1											= 0x269,
			C6_SDMMC1D6											= 0x26C,
			C6_EVENTOUT											= 0x26F,
			
			C7_TIMER3CH2										= 0x272,
			C7_DFSDM1DATIN3									= 0x276,
			C7_TSCG4IO2											= 0x279,
			C7_SDMMC1D7											= 0x27C,
			C7_EVENTOUT											= 0x27F,
			
			C8_TIMER3CH3										= 0x282,
			C8_TSCG4IO3											= 0x289,
			C8_SDMMC1D0											= 0x28C,
			C8_EVENTOUT											= 0x28F,
			
			C9_TIMER3CH4										= 0x292,
			C9_TSCG4IO4											= 0x299,
			C9_SDMMC1D1											= 0x29C,
			C9_EVENTOUT											= 0x29F,
			
			C10_TRACED1											= 0x2A0,
			C10_SPI3SCK											= 0x2A6,
			C10_USART3TX										= 0x2A7,
			C10_UART4TX											= 0x2A8,
			C10_TSCG3IO2										= 0x2A9,
			C10_SDMMC1D2										= 0x2AC,
			C10_EVENTOUT										= 0x2AF,
			
			C11_SPI3MISO										= 0x2B6,
			C11_USART3RX										= 0x2B7,
			C11_TSCG3IO3										= 0x2B8,
			C11_UART4RX											= 0x2B9,
			C11_SDMMC1D3										= 0x2BC,
			C11_EVENTOUT										= 0x2BF,
			
			C12_TRACED3											= 0x2C0,
			C12_SPI3MOSI										= 0x2C6,
			C12_USART3CK										= 0x2C7,
			C12_TSCG3IO4										= 0x2C9,
			C12_SDMMC1CK										= 0x2CC,
			C12_EVENTOUT										= 0x2CF,
			
			C13_EVENTOUT										= 0x2DF,
			
			C14_EVENTOUT										= 0x2EF,
			
			C15_EVENTOUT										= 0x2FF,
			
			
			
			
			
			
			
			D2_TRACED2											= 0x320,
			D2_TIMER3ETR										= 0x322,
			D2_USART3RTSDE									= 0x327,
			D2_TSCSYNC											= 0x329,
			D2_SDMMC1CMD										= 0x32C,
			D2_EVENTOUT											= 0x32F,
			
			
			
			
			
			
			
			H0_EVENTOUT											= 0x70F,
			
			H1_EVENTOUT											= 0x71F,
			
			H3_EVENTOUT											= 0x73F
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
		friend class STM32L451RET6;
		
		
		
		
		
	public:
		
		feedback init_pin(e_pin pin, e_mode mode, e_speed speed = e_speed::HIGH, e_pupd pupd = e_pupd::NONE);
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
	const uint32 port = ((uint32) pin) >> 4;
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	
	volatile uint32* address = MCU::GPIO_A::BSRR + port * 0x00000100;
	bit::set(*address, pinNumber);
}


inline void GPIO::clear_pin(e_pin pin)
{
	const uint32 port = ((uint32) pin) >> 4;
	const uint32 pinNumber = ((uint32) pin) & 0x0000000F;
	
	volatile uint32* address = MCU::GPIO_A::BSRR + port * 0x00000100;
	bit::set(*address, pinNumber + 16);
}


inline void GPIO::toggle_pin(e_pin pin)
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


inline bool GPIO::get_pinLevel(e_pin pin)
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


inline feedback GPIO::set_AF(e_AF alternateFunction)
{
	const uint32 port = (((uint32) alternateFunction) & 0x00000F00) >> 8;
	
	const  uint32 mask = ((uint32) alternateFunction) & 0x000000FF;
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