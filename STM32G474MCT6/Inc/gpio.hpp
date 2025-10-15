#pragma once

#include "registers.hpp"
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
		D2	= 0x32,
		D8	= 0x38,
		D9	= 0x39,
		D10	= 0x3A,
		
		E7	= 0x47,
		E8	= 0x48,
		E9	= 0x49,
		E10	= 0x4A,
		E11	= 0x4B,
		E12	= 0x4C,
		E13	= 0x4D,
		E14	= 0x4E,
		E15	= 0x4F,
		
		F0	= 0x50,
		F1	= 0x51,
		
		G10	= 0x6A
	};
	
	enum class AF: uint16
	{
		A0_TIMER2CH1										= 0x001,
		A0_TIMER5CH1										= 0x002,
		A0_USART2CTS										= 0x007,
		A0_COMP1OUT											= 0x008,
		A0_TIMER8BKIN										= 0x009,
		A0_TIMER8ETR										= 0x00A,
		A0_TIMER2ETR										= 0x00E,
		A0_EVENTOUT											= 0x00F,
		
		A1_RTCREFIN											= 0x010,
		A1_TIMER2CH2										= 0x011,
		A1_TIMER5CH2										= 0x012,
		A1_USART2RTSDE									= 0x017,
		A1_TIMER15CH1N									= 0x019,
		A1_EVENTOUT											= 0x01F,
		
		A2_TIMER2CH3										= 0x021,
		A2_TIMER5CH3										= 0x022,
		A2_USART2TX											= 0x027,
		A2_COMP2OUT											= 0x028,
		A2_TIMER15CH1										= 0x029,
		A2_QUADSPIBK1NCS								= 0x02A,
		A2_LPUART1TX										= 0x02C,
		A2_UCPDFRSTX										= 0x02E,
		A2_EVENTOUT											= 0x02F,
		
		A3_TIMER2CH4										= 0x031,
		A3_TIMER5CH4										= 0x032,
		A3_SAI1CK1											= 0x033,
		A3_USART2RX											= 0x037,
		A3_TIMER15CH2										= 0x039,
		A3_QUADSPICLK										= 0x03A,
		A3_LPUART1RX										= 0x03C,
		A3_SAIMCLKA											= 0x03D,
		A3_EVENTOUT											= 0x03F,
		
		A4_TIMER3CH2										= 0x042,
		A4_SPI1NSS											= 0x045,
		A4_SPI3NSS											= 0x046,
		A4_USART2CK											= 0x047,
		A4_SAI1FSB											= 0x04D,
		A4_EVENTOUT											= 0x04F,
		
		A5_TIMER2CH1										= 0x051,
		A5_TIMER2ETR										= 0x052,
		A5_SPI1SCK											= 0x055,
		A5_UCPDFRSTX										= 0x05E,
		A5_EVENTOUT											= 0x05F,
		
		A6_TIMER16CH1										= 0x061,
		A6_TIMER3CH1										= 0x062,
		A6_TIMER8BKIN										= 0x064,
		A6_SPI1MISO											= 0x065,
		A6_TIMER1BKIN										= 0x066,
		A6_COMP1OUT											= 0x068,
		A6_QUADSPIBK1IO3								= 0x06A,
		A6_LPUART1CTS										= 0x06C,
		A6_EVENTOUT											= 0x06F,
		
		A7_TIMER1CH1										= 0x071,
		A7_TIMER3CH2										= 0x072,
		A7_TIMER8CH1N										= 0x074,
		A7_SPI1MOSI											= 0x075,
		A7_TIMER1CH1N										= 0x076,
		A7_COMP2OUT											= 0x078,
		A7_QUADSPIBK1IO2								= 0x07A,
		A7_UCPDFRSTX										= 0x07E,
		A7_EVENTOUT											= 0x07F,
		
		A8_MCO													= 0x080,
		A8_I2C3SCL											= 0x082,
		A8_I2C2SDA											= 0x084,
		A8_I2S2MCK											= 0x085,
		A8_TIMER1CH1										= 0x086,
		A8_USART1CK											= 0x087,
		A8_COMP7OUT											= 0x088,
		A8_TIMER4ETR										= 0x08A,
		A8_FDCAN3RX											= 0x08B,
		A8_SAI1CK2											= 0x08C,
		A8_HRTIMERCHA1									= 0x08D,
		A8_SAI1SCKA											= 0x08E,
		A8_EVENTOUT											= 0x08F,
		
		A9_I2C3SMBA											= 0x092,
		A9_I2C2SCL											= 0x094,
		A9_I2S3MCK											= 0x095,
		A9_TIMER1CH2										= 0x096,
		A9_USART1TX											= 0x097,
		A9_COMP5OUT											= 0x098,
		A9_TIMER15BKIN									= 0x099,
		A9_TIMER2CH3										= 0x09A,
		A9_HRTIMERCHA2									= 0x09D,
		A9_SAI1FSA											= 0x09E,
		A9_EVENTOUT											= 0x09F,
		
		A10_TIMER17BKIN									= 0x0A1,
		A10_USBCRSSYNC									= 0x0A3,
		A10_I2C2SMBA										= 0x0A4,
		A10_SPI2MISO										= 0x0A5,
		A10_TIMER1CH3										= 0x0A6,
		A10_USART1RX										= 0x0A7,
		A10_COMP6OUT										= 0x0A8,
		A10_TIMER2CH4										= 0x0AA,
		A10_TIMER8BKIN									= 0x0AB,
		A10_SAI1D1											= 0x0AC,
		A10_HRTIMERCHB1									= 0x0AD,
		A10_SAI1SDA											= 0x0AE,
		A10_EVENTOUT										= 0x0AF,
		
		A11_SPI2MOSI										= 0x0B5,
		A11_TIMER1CH1N									= 0x0B6,
		A11_USART1CTS										= 0x0B7,
		A11_COMP1OUT										= 0x0B8,
		A11_FDCAN1RX										= 0x0B9,
		A11_TIMER4CH1										= 0x0BA,
		A11_TIMER1CH4										= 0x0BB,
		A11_TIMER1BKIN2									= 0x0BC,
		A11_HRTIMERCHB2									= 0x0BD,
		A11_EVENTOUT										= 0x0BF,
		
		A12_TIMER16CH1									= 0x0C1,
		A12_I2SCKIN											= 0x0C5,
		A12_TIMER1CH2N									= 0x0C6,
		A12_USART1RTSDE									= 0x0C7,
		A12_COMP2OUT										= 0x0C8,
		A12_FDCAN1TX										= 0x0C9,
		A12_TIMER4CH2										= 0x0CA,
		A12_TIMER1ETR										= 0x0CB,
		A12_HRTIMERFLT1									= 0x0CD,
		A12_EVENTOUT										= 0x0CF,
		
		A13_SWDIO_JTMS									= 0x0D0,
		A13_TIMER16CH1N									= 0x0D1,
		A13_I2C4SCL											= 0x0D3,
		A13_I2C1SCL											= 0x0D4,
		A13_IROUT												= 0x0D5,
		A13_USART3CTS										= 0x0D7,
		A13_TIMER4CH3										= 0x0DA,
		A13_SAI1SDB											= 0x0DD,
		A13_EVENTOUT										= 0x0DF,
		
		A14_SWCLK_JTCK									= 0x0E0,
		A14_LPTIMER1OUT									= 0x0E1,
		A14_I2C4SMBA										= 0x0E3,
		A14_I2C1SDA											= 0x0E4,
		A14_TIMER8CH2										= 0x0E5,
		A14_TIMER1BKIN									= 0x0E6,
		A14_USART2TX										= 0x0E7,
		A14_SAI1FSB											= 0x0ED,
		A14_EVENTOUT										= 0x0EF,
		
		A15_JTDI												= 0x0F0,
		A15_TIMER2CH1										= 0x0F1,
		A15_TIMER8CH1										= 0x0F2,
		A15_I2C1SCL											= 0x0F4,
		A15_SPI1NSS											= 0x0F5,
		A15_SPI3NSS											= 0x0F6,
		A15_USART2RX										= 0x0F7,
		A15_UART4RTSDE									= 0x0F8,
		A15_TIMER1BKIN									= 0x0F9,
		A15_FDCAN3TX										= 0x0FA,
		A15_HRTIMERFLT2									= 0x0FD,
		A15_TIMER2ETR										= 0x0FE,
		A15_EVENTOUT										= 0x0FF,
		
		
		
		
		
		
		
		B0_TIMER3CH3										= 0x102,
		B0_TIMER8CH2N										= 0x104,
		B0_TIMER1CH2N										= 0x106,
		B0_QUADSPIBK1IO1								= 0x10A,
		B0_HRTIMERFLT5									= 0x10D,
		B0_UCPDFRSTX										= 0x10E,
		B0_EVENTOUT											= 0x10F,
		
		B1_TIMER3CH4										= 0x112,
		B1_TIMER8CH3N										= 0x114,
		B1_TIMER1CH3N										= 0x116,
		B1_COMP4OUT											= 0x118,
		B1_QUADSPIBK1IO0								= 0x11A,
		B1_LPUART1RTSDE									= 0x11C,
		B1_HRTIMERSCOUT									= 0x11D,
		B1_EVENTOUT											= 0x11F,
		
		B2_RTCOUT												= 0x120,
		B2_LPTIMER1OUT									= 0x121,
		B2_TIMER5CH1										= 0x122,
		B2_TIMER20CH1										= 0x123,
		B2_I2C3SMBA											= 0x124,
		B2_QUADSPIBK2IO1								= 0x12A,
		B2_HRTIMERSCIN									= 0x12D,
		B2_EVENTOUT											= 0x12F,
		
		B3_JTDO_TRACESWO								= 0x130,
		B3_TIMER2CH2										= 0x131,
		B3_TIMER4ETR										= 0x132,
		B3_USBCRSSYNC										= 0x133,
		B3_TIMER8CH1N										= 0x134,
		B3_SPI1SCK											= 0x135,
		B3_SPI3SCK											= 0x136,
		B3_USART2TX											= 0x137,
		B3_TIMER3ETR										= 0x13A,
		B3_FDCAN3RX											= 0x13B,
		B3_HRTIMERSCOUT									= 0x13C,
		B3_HRTIMEREEV9									= 0x13D,
		B3_SAI1SCKB											= 0x13E,
		B3_EVENTOUT											= 0x13F,
		
		B4_NJTRST												= 0x140,
		B4_TIMER16CH1										= 0x141,
		B4_TIMER3CH1										= 0x142,
		B4_TIMER8CH2N										= 0x144,
		B4_SPI1MISO											= 0x145,
		B4_SPI3MISO											= 0x146,
		B4_USART2RX											= 0x147,
		B4_UART5RTSDE										= 0x148,
		B4_TIMER17BKIN									= 0x14A,
		B4_FDCAN3TX											= 0x14B,
		B4_HRTIMEREEV7									= 0x14D,
		B4_SAI1MCLKB										= 0x14E,
		B4_EVENTOUT											= 0x14F,
		
		B5_TIMER16BKIN									= 0x151,
		B5_TIMER3CH2										= 0x152,
		B5_TIMER8CH3N										= 0x153,
		B5_I2C1SMBA											= 0x154,
		B5_SPI1MOSI											= 0x155,
		B5_SPI3MOSI											= 0x156,
		B5_USART2CK											= 0x157,
		B5_I2C3SDA											= 0x158,
		B5_FDCAN2RX											= 0x159,
		B5_TIMER17CH1										= 0x15A,
		B5_LPTIMER1IN1									= 0x15B,
		B5_SAI1SDB											= 0x15C,
		B5_HRTIMEREEV6									= 0x15D,
		B5_UART5CTS											= 0x15E,
		B5_EVENTOUT											= 0x15F,
		
		B6_TIMER16CH1N									= 0x161,
		B6_TIMER4CH1										= 0x162,
		B6_TIMER8CH1N										= 0x165,
		B6_TIMER8ETR										= 0x166,
		B6_USART1TX											= 0x167,
		B6_COMP4OUT											= 0x168,
		B6_FDCAN2TX											= 0x169,
		B6_TIMER8BKIN2									= 0x16A,
		B6_LPTIMER1ETR									= 0x16B,
		B6_HRTIMERSCIN									= 0x16C,
		B6_HRTIMEREEV4									= 0x16D,
		B6_SAI1FSB											= 0x16E,
		B6_EVENTOUT											= 0x16F,
		
		B7_TIMER17CH1N									= 0x171,
		B7_TIMER4CH2										= 0x172,
		B7_I2C4SDA											= 0x173,
		B7_I2C1SDA											= 0x174,
		B7_TIMER8BKIN										= 0x175,
		B7_USART1RX											= 0x177,
		B7_COMP3OUT											= 0x178,
		B7_TIMER3CH4										= 0x17A,
		B7_LPTIMER1IN2									= 0x17B,
		B7_HRTIMEREEV3									= 0x17D,
		B7_UART4CTS											= 0x17E,
		B7_EVENTOUT											= 0x17F,
		
		B8_TIMER16CH1										= 0x181,
		B8_TIMER4CH3										= 0x182,
		B8_SAI1CK1											= 0x183,
		B8_I2C1SCL											= 0x184,
		B8_USART3RX											= 0x187,
		B8_COMP1OUT											= 0x188,
		B8_FDCAN1RX											= 0x189,
		B8_TIMER8CH2N										= 0x18A,
		B8_TIMER1BKIN										= 0x18C,
		B8_HRTIMEREEV8									= 0x18D,
		B8_SAI1MCLKA										= 0x18E,
		B8_EVENTOUT											= 0x18F,
		
		B9_TIMER17CH1										= 0x191,
		B9_TIMER4CH4										= 0x192,
		B9_SAI1D2												= 0x193,
		B9_I2C1SDA											= 0x194,
		B9_IROUT												= 0x196,
		B9_USART3TX											= 0x197,
		B9_COMP2OUT											= 0x198,
		B9_FDCAN1TX											= 0x199,
		B9_TIMER8CH3N										= 0x19A,
		B9_TIMER1CH3N										= 0x19C,
		B9_HRTIMEREEV5									= 0x19D,
		B9_SAI1FSA											= 0x19E,
		B9_EVENTOUT											= 0x19F,
		
		B10_TIMER2CH3										= 0x1A1,
		B10_USART3TX										= 0x1A7,
		B10_LPUART1RX										= 0x1A8,
		B10_QUADSPICLK									= 0x1AA,
		B10_TIMER1BKIN									= 0x1AC,
		B10_HRTIMERFLT3									= 0x1AD,
		B10_SAI1SCKA										= 0x1AE,
		B10_EVENTOUT										= 0x1AF,
		
		B11_TIMER2CH4										= 0x1B1,
		B11_USART3RX										= 0x1B7,
		B11_LPUART1TX										= 0x1B8,
		B11_QUADSPIBK1NCS								= 0x1BA,
		B11_HRTIMERFLT4									= 0x1BD,
		B11_EVENTOUT										= 0x1BF,
		
		B12_TIMER5ETR										= 0x1C2,
		B12_I2C2SMBA										= 0x1C4,
		B12_SPI2NSS											= 0x1C5,
		B12_TIMER1BKIN									= 0x1C6,
		B12_USART3CK										= 0x1C7,
		B12_LPUART1RTSDE								= 0x1C8,
		B12_FDCAN2RX										= 0x1C9,
		B12_HRTIMERCHC1									= 0x1CD,
		B12_EVENTOUT										= 0x1CF,
		
		B13_SPI2SCK											= 0x1D5,
		B13_TIMER1CH1N									= 0x1D6,
		B13_USART3CTS										= 0x1D7,
		B13_LPUART1CTS									= 0x1D8,
		B13_FDCAN2TX										= 0x1D9,
		B13_HRTIMERCHC2									= 0x1DD,
		B13_EVENTOUT										= 0x1DF,
		
		B14_TIMER15CH1									= 0x1E1,
		B14_SPI2MISO										= 0x1E5,
		B14_TIMER1CH2N									= 0x1E6,
		B14_USART3RTSDE									= 0x1E7,
		B14_COMP4OUT										= 0x1E8,
		B14_HRTIMERCHD1									= 0x1ED,
		B14_EVENTOUT										= 0x1EF,
		
		B15_RTCREFIN										= 0x1F0,
		B15_TIMER15CH2									= 0x1F1,
		B15_TIMER15CH1N									= 0x1F2,
		B15_COMP3OUT										= 0x1F3,
		B15_TIMER1CH3N									= 0x1F4,
		B15_SPI2MOSI										= 0x1F5,
		B15_HRTIMERCHD2									= 0x1FD,
		B15_EVENTOUT										= 0x1FF,
		
		
		
		
		
		
		
		C0_LPTIMER1IN1									= 0x201,
		C0_TIMER1CH1										= 0x202,
		C0_LPUART1RX										= 0x208,
		C0_EVENTOUT											= 0x20F,
		
		C1_LPTIMER1OUT									= 0x211,
		C1_TIMER1CH2										= 0x212,
		C1_LPUART1TX										= 0x218,
		C1_QUADSPIBK2IO0								= 0x21A,
		C1_SAI1SDA											= 0x21D,
		C1_EVENTOUT											= 0x21F,
		
		C2_LPTIMER1IN2									= 0x221,
		C2_TIMER1CH3										= 0x222,
		C2_COMP3OUT											= 0x223,
		C2_TIMER20CH2										= 0x226,
		C2_QUADSPIBK2IO1								= 0x22A,
		C2_EVENTOUT											= 0x22F,
		
		C3_LPTIMER1ETR									= 0x231,
		C3_TIMER1CH4										= 0x232,
		C3_SAI1D1												= 0x233,
		C3_TIMER1BKIN2									= 0x236,
		C3_QUADSPIBK2IO2								= 0x23A,
		C3_SAI1SDA											= 0x23D,
		C3_EVENTOUT											= 0x23F,
		
		C4_TIMER1ETR										= 0x242,
		C4_I2C2SCL											= 0x244,
		C4_USART1TX											= 0x247,
		C4_QUADSPIBK2IO3								= 0x24A,
		C4_EVENTOUT											= 0x24F,
		
		C5_TIMER15BKIN									= 0x252,
		C5_SAI1D3												= 0x253,
		C5_TIMER4CH4N										= 0x256,
		C5_USART1RX											= 0x257,
		C5_HRTIMER1EEV10								= 0x25D,
		C5_EVENTOUT											= 0x25F,
		
		C6_TIMER3CH1										= 0x262,
		C6_HRTIMEREEV10									= 0x263,
		C6_TIMER8CH1										= 0x264,
		C6_I2S2MCK											= 0x266,
		C6_COMP6OUT											= 0x267,
		C6_I2C4SCL											= 0x268,
		C6_HRTIMERCHF1									= 0x26D,
		C6_EVENTOUT											= 0x26F,
		
		C7_TIMER3CH2										= 0x272,
		C7_HRTIMERFLT5									= 0x273,
		C7_TIMER8CH2										= 0x274,
		C7_I2S3MCK											= 0x276,
		C7_COMP5OUT											= 0x277,
		C7_I2C4SDA											= 0x278,
		C7_HRTIMERCHF2									= 0x27D,
		C7_EVENTOUT											= 0x27F,
		
		C8_TIMER3CH3										= 0x282,
		C8_HRTIMERCHE1									= 0x283,
		C8_TIMER8CH3										= 0x284,
		C8_TIMER20CH3										= 0x286,
		C8_COMP7OUT											= 0x287,
		C8_I2C3SCL											= 0x288,
		C8_EVENTOUT											= 0x28F,
		
		C9_TIMER3CH4										= 0x292,
		C9_HRTIMERCHE2									= 0x293,
		C9_TIMER8CH4										= 0x294,
		C9_I2SCKIN											= 0x295,
		C9_TIMER8BKIN2									= 0x296,
		C9_I2C3SDA											= 0x298,
		C9_EVENTOUT											= 0x29F,
		
		C10_TIMER8CH1N									= 0x2A4,
		C10_UART4TX											= 0x2A5,
		C10_SPI3SCK											= 0x2A6,
		C10_USART3TX										= 0x2A7,
		C10_HRTIMERFLT6									= 0x2AD,
		C10_EVENTOUT										= 0x2AF,
		
		C11_HRTIMEREEV2									= 0x2B3,
		C11_TIMER8CH2N									= 0x2B4,
		C11_UART4RX											= 0x2B5,
		C11_SPI3MISO										= 0x2B6,
		C11_USART3RX										= 0x2B7,
		C11_I2C3SDA											= 0x2B8,
		C11_EVENTOUT										= 0x2BF,
		
		C12_TIMER5CH2										= 0x2C1,
		C12_HRTIMEREEV1									= 0x2C3,
		C12_TIMER8CH3N									= 0x2C4,
		C12_UART5TX											= 0x2C5,
		C12_SPI3MOSI										= 0x2C6,
		C12_USART3CK										= 0x2C7,
		C12_UCPDFRSTX										= 0x2CE,
		C12_EVENTOUT										= 0x2CF,
		
		C13_TIMER1BKIN2									= 0x2D2,
		C13_TIMER1CH1N									= 0x2D4,
		C13_TIMER8CH4N									= 0x2D6,
		C13_EVENTOUT										= 0x2DF,
		
		C14_EVENTOUT										= 0x2EF,
		
		C15_EVENTOUT										= 0x2FF,
		
		
		
		
		
		
		
		D0_TIMER8CH4N										= 0x306,
		D0_FDCAN1RX											= 0x309,
		D0_EVENTOUT											= 0x30F,
		
		D1_TIMER8CH4										= 0x314,
		D1_TIMER8BKIN2									= 0x316,
		D1_FDCAN1TX											= 0x319,
		D1_EVENTOUT											= 0x31F,
		
		D2_TIMER3ETR										= 0x322,
		D2_TIMER8BKIN										= 0x324,
		D2_UART5RX											= 0x325,
		D2_EVENTOUT											= 0x32F,
		
		D8_USART3TX											= 0x387,
		D8_EVENTOUT											= 0x38F,
		
		D9_USART3RX											= 0x397,
		D9_EVENTOUT											= 0x39F,
		
		D10_USART3CK										= 0x3A7,
		D10_EVENTOUT										= 0x3AF,
		
		
		
		
		
		
		
		E7_TIMER1ETR										= 0x472,
		E7_SAI1SDB											= 0x47D,
		E7_EVENTOUT											= 0x47F,
		
		E8_TIMER5CH3										= 0x481,
		E8_TIMER1CH1N										= 0x482,
		E8_SAI1SCKB											= 0x48D,
		E8_EVENTOUT											= 0x48F,
		
		E9_TIMER5CH4										= 0x491,
		E9_TIMER1CH1										= 0x492,
		E9_SAI1FSB											= 0x49D,
		E9_EVENTOUT											= 0x49F,
		
		E10_TIMER1CH2N									= 0x4A2,
		E10_QUADSPICLK									= 0x4AA,
		E10_SAI1MCLKB										= 0x4AD,
		E10_EVENTOUT										= 0x4AF,
		
		E11_TIMER1CH2										= 0x4B2,
		E11_SPI4NSS											= 0x4B5,
		E11_QUADSPIBK1NCS								= 0x4BA,
		E11_EVENTOUT										= 0x4BF,
		
		E12_TIMER1CH3N									= 0x4C2,
		E12_SPI4SCK											= 0x4C5,
		E12_QUADSPIBK1IO0								= 0x4CA,
		E12_EVENTOUT										= 0x4CF,
		
		E13_TIMER1CH3										= 0x4D2,
		E13_SPI4MISO										= 0x4D5,
		E13_QUADSPIBK1IO1								= 0x4DA,
		E13_EVENTOUT										= 0x4DF,
		
		E14_TIMER1CH4										= 0x4E2,
		E14_SPI4MOSI										= 0x4E5,
		E14_TIMER1BKIN2									= 0x4E6,
		E14_QUADSPIBK1IO2								= 0x4EA,
		E14_EVENTOUT										= 0x4EF,
		
		E15_TIMER1BKIN									= 0x4F2,
		E15_TIMER1CH4N									= 0x4F6,
		E15_USART3RX										= 0x4F7,
		E15_QUADSPIBK1IO3								= 0x4FA,
		E15_EVENTOUT										= 0x4FF,
		
		
		
		
		
		
		
		F0_I2C2SDA											= 0x504,
		F0_SPI2NSS											= 0x505,
		F0_TIMER1CH3N										= 0x506,
		F0_EVENTOUT											= 0x50F,
		
		F1_SPI2SCK											= 0x515,
		F1_EVENTOUT											= 0x51F,
		
		
		
		
		
		
		
		G10_MCO													= 0x6A0,
		G10_EVENTOUT										= 0x6AF
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
		friend class STM32G474MCT6;
		
		
		
		
		
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
	
	rcc.module_reset(RCC::e_module::GPIO_E);
	rcc.module_clockInit(RCC::e_module::GPIO_E, true);
	
	rcc.module_reset(RCC::e_module::GPIO_F);
	rcc.module_clockInit(RCC::e_module::GPIO_F, true);
	
	rcc.module_reset(RCC::e_module::GPIO_G);
	rcc.module_clockInit(RCC::e_module::GPIO_G, true);
	
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