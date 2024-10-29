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
			
			D0	= 0x30,
			D1	= 0x31,
			D2	= 0x32,
			D3	= 0x33,
			D4	= 0x34,
			D5	= 0x35,
			D6	= 0x36,
			D7	= 0x37,
			D8	= 0x38,
			D9	= 0x39,
			D10	= 0x3A,
			D11	= 0x3B,
			D12	= 0x3C,
			D13	= 0x3D,
			D14	= 0x3E,
			D15	= 0x3F,
			
			E0	= 0x40,
			E1	= 0x41,
			E2	= 0x42,
			E3	= 0x43,
			E4	= 0x44,
			E5	= 0x45,
			E6	= 0x46,
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
			F2	= 0x52,
			F3	= 0x53,
			F4	= 0x54,
			F5	= 0x55,
			F6	= 0x56,
			F7	= 0x57,
			F8	= 0x58,
			F9	= 0x59,
			F10	= 0x5A,
			F11	= 0x5B,
			F12	= 0x5C,
			F13	= 0x5D,
			F14	= 0x5E,
			F15	= 0x5F,
			
			G0	= 0x60,
			G1	= 0x61,
			G2	= 0x62,
			G3	= 0x63,
			G4	= 0x64,
			G5	= 0x65,
			G6	= 0x66,
			G7	= 0x67,
			G8	= 0x68,
			G9	= 0x69,
			G10	= 0x6A,
			G11	= 0x6B,
			G12	= 0x6C,
			G13	= 0x6D,
			G14	= 0x6E,
			G15	= 0x6F,
			
			H0	= 0x70,
			H1	= 0x71,
			H2	= 0x72,
			H3	= 0x73,
			H4	= 0x74,
			H5	= 0x75,
			H6	= 0x76,
			H7	= 0x77,
			H8	= 0x78,
			H9	= 0x79,
			H10	= 0x7A,
			H11	= 0x7B,
			H12	= 0x7C,
			H13	= 0x7D,
			H14	= 0x7E,
			H15	= 0x7F,
			
			I0	= 0x80,
			I1	= 0x81,
			I2	= 0x82,
			I3	= 0x83,
			I4	= 0x84,
			I5	= 0x85,
			I6	= 0x86,
			I7	= 0x87,
			I8	= 0x88,
			I9	= 0x89,
			I10	= 0x8A,
			I11	= 0x8B,
			I12	= 0x8C,
			I13	= 0x8D,
			I14	= 0x8E,
			I15	= 0x8F,
			
			J0	= 0x90,
			J1	= 0x91,
			J2	= 0x92,
			J3	= 0x93,
			J4	= 0x94,
			J5	= 0x95,
			J6	= 0x96,
			J7	= 0x97,
			J8	= 0x98,
			J9	= 0x99,
			J10	= 0x9A,
			J11	= 0x9B,
			J12	= 0x9C,
			J13	= 0x9D,
			J14	= 0x9E,
			J15	= 0x9F,
			
			K0	= 0xA0,
			K1	= 0xA1,
			K2	= 0xA2,
			K3	= 0xA3,
			K4	= 0xA4,
			K5	= 0xA5,
			K6	= 0xA6,
			K7	= 0xA7
		};
		
		enum class e_mode
		{
			IN,
			OUT_GP_PP,
			OUT_GP_OD,
			AF_PP,
			AF_OD,
			ANALOG
		};
		
		enum class e_speed
		{
				LOW,
				MEDIUM,
				HIGH,
				VERY_HIGH
		};
		
		enum class e_pupd
		{
			NONE,
			PULL_UP,
			PULL_DOWN
		};
		
		
		enum class e_AF
		{
			A0_TIMER2CH1_TIMER2ETR										= 0x001,
			A0_TIMER5CH1															= 0x002,
			A0_TIMER8ETR															= 0x003,
			A0_TIMER15BKIN														= 0x004,
			A0_USART2CTS_USART2NSS										= 0x007,
			A0_UART4TX																= 0x008,
			A0_SDMMC2CMD															= 0x009,
			A0_SAI2SDB																= 0x00A,
			A0_ETHMIICRS															= 0x00B,
			A0_EVENTOUT																= 0x00F,
			
			A1_TIMER2CH2															= 0x011,
			A1_TIMER5CH2															= 0x012,
			A1_LPTIMER3OUT														= 0x013,
			A1_TIMER5CH1N															= 0x014,
			A1_USART2RTS_USART2DE											= 0x017,
			A1_UART4RX																= 0x018,
			A1_QUADSPIBK1IO3													= 0x019,
			A1_SAI2MCLKB															= 0x01A,
			A1_ETHMIIRXCLK_ETHRMIIREFCLK							= 0x01B,
			A1_LCDR2																	= 0x01E,
			A1_EVENTOUT																= 0x01F,
			
			A2_TIMER2CH3															= 0x021,
			A2_TIMER5CH3															= 0x022,
			A2_LPTIMER4OUT														= 0x023,
			A2_TIMER15CH1															= 0x024,
			A2_USART2TX																= 0x027,
			A2_SAI2SCKB																= 0x028,
			A2_ETHMDIO																= 0x02B,
			A2_MDIOSMDIO															= 0x02C,
			A2_LCDR1																	= 0x02E,
			A2_EVENTOUT																= 0x02F,
			
			A3_TIMER2CH4															= 0x031,
			A3_TIMER5CH4															= 0x032,
			A3_LPTIMER5OUT														= 0x033,
			A3_TIMER15CH2															= 0x034,
			A3_USART2RX																= 0x037,
			A3_LCDB2																	= 0x039,
			A3_USB1ULPID0															= 0x03A,
			A3_ETHMIICOL															= 0x03B,
			A3_LCDB5																	= 0x03E,
			A3_EVENTOUT																= 0x03F,
			
			A4_D1PWREN																= 0x040,
			A4_TIMER5ETR															= 0x042,
			A4_SPI1NSS_I2S1WS													= 0x045,
			A4_SPI3NSS_I2S3WS													= 0x046,
			A4_USART2CK																= 0x047,
			A4_SPI6NSS																= 0x048,
			A4_USB1SOF																= 0x04C,
			A4_DCMIHSYNC															= 0x04D,
			A4_LCDVSYNC																= 0x04E,
			A4_EVENTOUT																= 0x04F,
			
			A5_D2PWREN																= 0x050,
			A5_TIMER2CH1_TIMER2ETR										= 0x051,
			A5_TIMER8CH1N															= 0x053,
			A5_SPI1SCK_I2S1CK													= 0x055,
			A5_SPI6SCK																= 0x058,
			A5_USB1ULPICK															= 0x05A,
			A5_LCDR4																	= 0x05E,
			A5_EVENTOUT																= 0x05F,
			
			A6_TIMER1BKIN															= 0x061,
			A6_TIMER3CH1															= 0x062,
			A6_TIMER8BKIN															= 0x063,
			A6_SPI1MISO_I2S1SDI												= 0x065,
			A6_SPI6MISO																= 0x068,
			A6_TIMER13CH1															= 0x069,
			A6_TIMER8BKINCOMP12												= 0x06A,
			A6_MDIOSMDC																= 0x06B,
			A6_TIMER1BKINCOMP12												= 0x06C,
			A6_DCMIPIXCLK															= 0x06D,
			A6_LCDG2																	= 0x06E,
			A6_EVENTOUT																= 0x06F,
			
			A7_TIMER1CH1N															= 0x071,
			A7_TIMER3CH2															= 0x072,
			A7_TIMER8CH1N															= 0x073,
			A7_SPI1MOSI_I2S1SDO												= 0x075,
			A7_SPI6MOSI																= 0x078,
			A7_TIMER14CH1															= 0x079,
			A7_ETHMIIRXDV_ETHRMIICRSDV								= 0x07B,
			A7_FMCSDNWE																= 0x07C,
			A7_EVENTOUT																= 0x07F,
			
			A8_MCO1 																	= 0x080,
			A8_TIMER1CH1															= 0x081,
			A8_HRTIMERCHB2														= 0x082,
			A8_TIMER8BKIN2 														= 0x083,
			A8_I2C3SCL																= 0x084,
			A8_USART1CK																= 0x087,
			A8_USB2SOF																= 0x08A,
			A8_UART7RX																= 0x08B,
			A8_TIMER8BKIN2COMP12											= 0x08C,
			A8_LCDB3																	= 0x08D,
			A8_LCDR6																	= 0x08E,
			A8_EVENTOUT																= 0x08F,
			
			A9_TIMER1CH2															= 0x091,
			A9_HRTIMERCHC1														= 0x092,
			A9_LPUART1TX															= 0x093,
			A9_I2C2SMBA																= 0x094,
			A9_SPI2SCK_I2S2CK													= 0x095,
			A9_USART1TX																= 0x097,
			A9_FDCAN1RXFDMODE													= 0x099,
			A9_DCMID0																	= 0x09D,
			A9_LCDR5																	= 0x09E,
			A9_EVENTOUT																= 0x09F,
			
			A10_TIMER1CH3															= 0x0A1,
			A10_HRTIMERCHC2														= 0x0A2,
			A10_LPUART1RX															= 0x0A3,
			A10_USART1RX															= 0x0A7,
			A10_FDCAN1TXFDMODE												= 0x0A9,
			A10_USB2ID																= 0x0AA,
			A10_MDIOSMDIO															= 0x0AB,
			A10_LCDB4																	= 0x0AC,
			A10_DCMID1																= 0x0AD,
			A10_LCDB1																	= 0x0AE,
			A10_EVENTOUT															= 0x0AF,
			
			A11_TIMER1CH4															= 0x0B1,
			A11_HRTIMERCHD1														= 0x0B2,
			A11_LPUART1CTS														= 0x0B3,
			A11_SPI2NSS_I2S2WS												= 0x0B5,
			A11_UART4RX																= 0x0B6,
			A11_USART1CTS_USART1NSS										= 0x0B7,
			A11_FDCAN1RX															= 0x0B9,
			A11_USB2DM																= 0x0BA,
			A11_LCDR4																	= 0x0BE,
			A11_EVENTOUT															= 0x0B,
			
			A12_TIMER1ETR															= 0x0C1,
			A12_HRTIMERCHD2														= 0x0C2,
			A12_LPUART1RTS_LPUART1DE									= 0x0C3,
			A12_SPI1SCK_I2S2CK												= 0x0C5,
			A12_UART4TX																= 0x0C6,
			A12_USART1RTS_USART1DE										= 0x0C7,
			A12_SAI2FSB																= 0x0C8,
			A12_FDCAN1TX															= 0x0C9,
			A12_USB2DP																= 0x0CA,
			A12_LCDR5																	= 0x0CE,
			A12_EVENTOUT															= 0x0CF,
			
			A13_JTMS_SWDIO														= 0x0D0,
			A13_EVENTOUT															= 0x0DF,
			
			A14_JTCK_SWCLK														= 0x0E0,
			A14_EVENTOUT															= 0x0EF,
			
			A15_JTDI																	= 0x0F0,
			A15_TIMER2CH1_TIMER2ETR										= 0x0F1,
			A15_HRTIMERFLT1														= 0x0F2,
			A15_CEC																		= 0x0F4,
			A15_SPI1NSS_I2S1WS												= 0x0F5,
			A15_SPI3NSS_I2S3WS												= 0x0F6,
			A15_SPI6NSS																= 0x0F7,
			A15_UART4RTS_UART4DE											= 0x0F8,
			A15_UART7TX																= 0x0FB,
			A15_EVENTOUT															= 0x0FF,
			
			
			
			
			
			
			
			B0_TIMER1CH2N															= 0x101,
			B0_TIMER3CH3															= 0x102,
			B0_TIMER8CH2N															= 0x103,
			B0_DFSDMCKOUT															= 0x106,
			B0_UART4CTS																= 0x108,
			B0_LCDR3																	= 0x109,
			B0_USB1ULPID1															= 0x10A,
			B0_ETHMIIRXD2															= 0x10B,
			B0_LCDG1																	= 0x10E,
			B0_EVENTOUT																= 0x10F,
			
			B1_TIMER1CH3N															= 0x111,
			B1_TIMER3CH4															= 0x112,
			B1_TIMER8CH3N															= 0x113,
			B1_DFSDMDATIN1														= 0x116,
			B1_LCDR6																	= 0x119,
			B1_USB1ULPID2															= 0x11A,
			B1_ETHMIIRXD3															= 0x11B,
			B1_LCDG0																	= 0x11E,
			B1_EVENTOUT																= 0x11F,
			
			B2_RTCOUT																	= 0x120,
			B2_SAI1D1																	= 0x122,
			B2_DFSDMCKIN															= 0x124,
			B2_SAI1SDA																= 0x126,
			B2_SPI3MOSI_I2S3SDO												= 0x127,
			B2_SAI4SDA																= 0x128,
			B2_QUADSPICLK															= 0x129,
			B2_SAI4D1																	= 0x12A,
			B2_EVENTOUT																= 0x12F,
			
			B3_JTDO_TRACESWO													= 0x130,
			B3_TIMER2CH2															= 0x131,
			B3_HRTIMERFLT4														= 0x132,
			B3_SPI1SCK_I2S1CK													= 0x135,
			B3_SPI3SCK_I2S3CK													= 0x136,
			B3_SPI6SCK																= 0x138,
			B3_SDMMC2D2																= 0x139,
			B3_CRSSYNC																= 0x13A,
			B3_UART7RX																= 0x13B,
			B3_EVENTOUT																= 0x13F,
			
			B4_NJTRST																	= 0x140,
			B4_TIMER16BKIN														= 0x141,
			B4_TIMER3CH1															= 0x142,
			B4_HRTIMEREEV6														= 0x143,
			B4_SPI1MISO_I2S1SDI												= 0x145,
			B4_SPI3MISO_I2S3SDI												= 0x146,
			B4_SPI2NSS_I2S2WS													= 0x147,
			B4_SPI6MISO																= 0x148,
			B4_SDMMC2D3																= 0x149,
			B4_UART7TX																= 0x14B,
			B4_EVENTOUT																= 0x14F,
			
			B5_TIMER17BKIN														= 0x151,
			B5_TIMER3CH2															= 0x152,
			B5_HRTIMEREEV7														= 0x153,
			B5_I2C1SMBA																= 0x154,
			B5_SPI1MOSI_I2S1SDO												= 0x155,
			B5_I2C4SMBA																= 0x156,
			B5_SPI3MOSI_I2S3SDO												= 0x157,
			B5_SPI6MOSI																= 0x158,
			B5_FDCAN2RX																= 0x159,
			B5_USB1ULPID7															= 0x15A,
			B5_ETHPPSOUT															= 0x15B,
			B5_FMCSDCKE1															= 0x15C,
			B5_DCMID10																= 0x15D,
			B5_UART5RX																= 0x15E,
			B5_EVENTOUT																= 0x15F,
			
			B6_TIMER16CH1N														= 0x161,
			B6_TIMER4CH1															= 0x162,
			B6_HRTIMEREEV8														= 0x163,
			B6_I2C1SCL																= 0x164,
			B6_CEC																		= 0x165,
			B6_I2C4SCL																= 0x166,
			B6_USART1TX																= 0x167,
			B6_LPUART1TX															= 0x168,
			B6_FDCAN2TX																= 0x169,
			B6_QUADSPIBK1NCS													= 0x16A,
			B6_DFSDMDATIN5														= 0x16B,
			B6_FMCSDNE1																= 0x16C,
			B6_DCMID5																	= 0x16D,
			B6_UART5TX																= 0x16E,
			B6_EVENTOUT																= 0x16F,
			
			B7_TIMER17CH1N														= 0x171,
			B7_TIMER4CH2															= 0x172,
			B7_HRTIMEREEV9														= 0x173,
			B7_I2C1SDA																= 0x174,
			B7_I2C4SDA																= 0x176,
			B7_USART1RX																= 0x177,
			B7_LPUART1RX															= 0x178,
			B7_FDCAN2TXFDMODE													= 0x179,
			B7_DFSDMCKIN5															= 0x17B,
			B7_FCMNL																	= 0x17C,
			B7_DCMIVSYNC															= 0x17D,
			B7_EVENTOUT																= 0x17F,
			
			B8_TIMER16CH1															= 0x181,
			B8_TIMER4CH3															= 0x182,
			B8_DFSDMCKIN7															= 0x183,
			B8_I2C1SCL																= 0x184,
			B8_I2C4SCL																= 0x186,
			B8_SDMMC1CKIN															= 0x187,
			B8_UART4RX																= 0x188,
			B8_FDCAN1RX																= 0x189,
			B8_SDMMC2D4																= 0x18A,
			B8_ETHMIITXD3															= 0x18B,
			B8_SDMMC1D4																= 0x18C,
			B8_DCMID6																	= 0x18D,
			B8_LCDB6																	= 0x18E,
			B8_EVENTOUT																= 0x18F,
			
			B9_TIMER17CH1															= 0x191,
			B9_TIMER4CH4															= 0x192,
			B9_DFSDMDATIN7														= 0x193,
			B9_I2C1SDA																= 0x194,
			B9_SPI2NSS_I2S2WS													= 0x195,
			B9_I2C4SDA																= 0x196,
			B9_SDMMC1CDIR															= 0x197,
			B9_UART4TX																= 0x198,
			B9_FDCAN1TX																= 0x199,
			B9_SDMMC2D5																= 0x19A,
			B9_I2C4SMBA																= 0x19B,
			B9_SDMMC1D5																= 0x19C,
			B9_DMCID7																	= 0x19D,
			B9_LCDB7																	= 0x19E,
			B9_EVENTOUT																= 0x19F,
			
			B10_TIMER2CH3															= 0x1A1,
			B10_HRTIMERSCOUT													= 0x1A2,
			B10_LPTIMER2IN1														= 0x1A3,
			B10_I2C2SCL																= 0x1A4,
			B10_SPI2SCK_I2S2CK												= 0x1A5,
			B10_DFSDMDATIN7														= 0x1A6,
			B10_USART3TX															= 0x1A7,
			B10_QUADSPIBK1NCS													= 0x1A9,
			B10_USB1ULPID3														= 0x1AA,
			B10_ETHMIIRXER														= 0x1AB,
			B10_LCDG4																	= 0x1AE,
			B10_EVENTOUT															= 0x1AF,
			
			B11_TIMER2CH4															= 0x1B1,
			B11_HRTIMERSCIN														= 0x1B2,
			B11_LPTIMER2ETR														= 0x1B3,
			B11_I2C2SDA																= 0x1B4,
			B11_DFSDMCKIN7														= 0x1B6,
			B11_USART3RX															= 0x1B7,
			B11_USB1ULPID4														= 0x1BA,
			B11_ETHMIITXEN_ETHRMIITXEN								= 0x1BB,
			B11_LCDG5																	= 0x1BE,
			B11_EVENTOUT															= 0x1BF,
			
			B12_TIMER1BKIN														= 0x1C1,
			B12_I2C2SMBA															= 0x1C4,
			B12_SPI2NSS_I2S2WS												= 0x1C5,
			B12_DFSDMDATIN1														= 0x1C6,
			B12_USART3CK															= 0x1C7,
			B12_FDCAN2RX															= 0x1C9,
			B12_USB1ULPID5														= 0x1CA,
			B12_ETHMIITXD0_ETHRMIITXD0								= 0x1CB,
			B12_USB1ID																= 0x1CC,
			B12_TIMER1BKINCOMP12											= 0x1CD,
			B12_UART5RX																= 0x1CE,
			B12_EVENTOUT															= 0x1CF,
			
			B13_TIMER1CH1N														= 0x1D1,
			B13_LPTIMER2OUT														= 0x1D3,
			B13_SPI2SCK_I2S2CK												= 0x1D5,
			B13_DFSDMCKIN1														= 0x1D6,
			B13_USART3CTS_USART3NSS										= 0x1D7,
			B13_FDCAN2TX															= 0x1D9,
			B13_USB1ULPID6														= 0x1DA,
			B13_ETHMIITXD1_ETHRMIITXD1								= 0x1DB,
			B13_UART5TX																= 0x1DE,
			B13_EVENTOUT															= 0x1DF,
			
			B14_TIMER1CH2N														= 0x1E1,
			B14_TIMER12CH1														= 0x1E2,
			B14_TIMER8CH2N														= 0x1E3,
			B14_USART1TX															= 0x1E4,
			B14_SPI2MISO_I2S2SDI											= 0x1E5,
			B14_DFSDMDATIN2														= 0x1E6,
			B14_USART3RTS_USART3DE										= 0x1E7,
			B14_UART4RTS_UART4DE											= 0x1E8,
			B14_SDMMC2D0															= 0x1E9,
			B14_USB1DM																= 0x1EC,
			B14_EVENTOUT															= 0x1EF,
			
			B15_RTCREFIN															= 0x1F0,
			B15_TIMER1CH3N														= 0x1F1,
			B15_TIMER12CH2														= 0x1F2,
			B15_TIMER8CH3N														= 0x1F3,
			B15_USART1RX															= 0x1F4,
			B15_SPI2MOSI_I2S2SDO											= 0x1F5,
			B15_DFSDMCKIN2														= 0x1F6,
			B15_UART4CTS															= 0x1F8,
			B15_SDMMC2D1															= 0x1F9,
			B15_USB1DP																= 0x1FC,
			B15_EVENTOUT															= 0x1FF,
			
			
			
			
			
			
			
			C0_DFSDMCKIN0															= 0x203,
			C0_DFSDMDATIN4														= 0x206,
			C0_SAI2FSB																= 0x208,
			C0_USB1ULPISTP														= 0x20A,
			C0_FMCSDNWE																= 0x20C,
			C0_LCDR5																	= 0x20E,
			C0_EVENTOUT																= 0x20F,
			
			C1_TRACED0																= 0x210,
			C1_SAI1D1																	= 0x212,
			C1_DFSDMDATIN0														= 0x213,
			C1_DFSDMCKIN4															= 0x214,
			C1_SPI2MOSI_I2S2SDO												= 0x215,
			C1_SAI1SDA																= 0x216,
			C1_SAI4SDA																= 0x218,
			C1_SDMMC2CK																= 0x219,
			C1_SAI4D1																	= 0x21A,
			C1_ETHMDC																	= 0x21B,
			C1_MDIOSMDC																= 0x21C,
			C1_EVENTOUT																= 0x21F,
			
			C2_CDSLEEP																= 0x220,
			C2_DFSDMCKIN1															= 0x223,
			C2_SPI2MISO_I2S2SDI												= 0x225,
			C2_DFSDMCKOUT															= 0x226,
			C2_USB1ULPIDIR														= 0x22A,
			C2_ETHMIITXD2															= 0x22B,
			C2_FMCSDNE0																= 0x22C,
			C2_EVENTOUT																= 0x22F,
			
			C3_CSLEEP																	= 0x230,
			C3_DFSDMDATIN1														= 0x233,
			C3_SPI2MOSI_I2S2SDO												= 0x235,
			C3_USB1ULPINXT														= 0x23A,
			C3_ETHMIITXCLK														= 0x23B,
			C3_FMCSDCKE0															= 0x23C,
			C3_EVENTOUT																= 0x23F,
			
			C4_DFSDMCKIN2															= 0x243,
			C4_I2S1MCK																= 0x245,
			C4_SPDIFRX1IN3														= 0x249,
			C4_ETHMIIRXD0_ETHRMIIRXD0									= 0x24B,
			C4_FMCSDNE0																= 0x24C,
			C4_EVENTOUT																= 0x24F,
			
			C5_SAI1D3																	= 0x252,
			C5_DFSDMDATIN2														= 0x253,
			C5_SPDIFRX1IN4														= 0x259,
			C5_SAI4D3																	= 0x25A,
			C5_ETHMIIRXD1_ETHRMIIRXD1									= 0x25B,
			C5_FMCSDCKE0															= 0x25C,
			C5_COMP1OUT																= 0x25D,
			C5_EVENTOUT																= 0x25F,
			
			C6_HRTIMERCHA1														= 0x261,
			C6_TIMER3CH1															= 0x262,
			C6_TIMER8CH1															= 0x263,
			C6_DFSDMCKIN3															= 0x264,
			C6_I2S2MCK																= 0x265,
			C6_USART6TX																= 0x267,
			C6_SDMMC1D0DIR														= 0x268,
			C6_FMCNWAIT																= 0x269,
			C6_SDMMC2D6																= 0x26A,
			C6_SDMMC1D6																= 0x26C,
			C6_DCMID0																	= 0x26D,
			C6_LCDHSYNC																= 0x26E,
			C6_EVENTOUT																= 0x26F,
			
			C7_TRGIO																	= 0x270,
			C7_HRTIMERCHA2														= 0x271,
			C7_TIMER3CH2															= 0x272,
			C7_TIMER8CH2															= 0x273,
			C7_DFSDMDATIN3														= 0x274,
			C7_I2S3MCK																= 0x276,
			C7_USART6RX																= 0x277,
			C7_SDMMC1D123DIR													= 0x278,
			C7_FMCNE1																	= 0x279,
			C7_SDMMC2D7																= 0x27A,
			C7_SWPMITX																= 0x27B,
			C7_SDMMC1D7																= 0x27C,
			C7_DCMID1																	= 0x27D,
			C7_LCDG6																	= 0x27E,
			C7_EVENTOUT																= 0x27F,
			
			C8_TRACED1																= 0x280,
			C8_HRTIMERCHB1														= 0x281,
			C8_TIMER3CH3															= 0x282,
			C8_TIMER8CH3															= 0x283,
			C8_USART6CK																= 0x287,
			C8_UART5RTS_UART5DE												= 0x288,
			C8_FMCNE2_FMCNCE													= 0x289,
			C8_SWPMIRX																= 0x28B,
			C8_SDMMC1D0																= 0x28C,
			C8_DCMID2																	= 0x28D,
			C8_EVENTOUT																= 0x28F,
			
			C9_MCO2																		= 0x290,
			C9_TIMER3CH4															= 0x292,
			C9_TIMER8CH4															= 0x293,
			C9_I2C3SDA																= 0x294,
			C9_I2SCKIN																= 0x295,
			C9_UART5CTS																= 0x298,
			C9_QUADSPIBK1IO0													= 0x299,
			C9_LCDG3																	= 0x29A,
			C9_SWPMISUSPEND														= 0x29B,
			C9_SDMMC1D1																= 0x29C,
			C9_DCMID3																	= 0x29D,
			C9_LCDB2																	= 0x29E,
			C9_EVENTOUT																= 0x29F,
			
			C10_HRTIMEREEV1														= 0x2A2,
			C10_DFSDMCKIN5														= 0x2A3,
			C10_SPI3SCK_I2S3CK												= 0x2A6,
			C10_USART3TX															= 0x2A7,
			C10_UART4TX																= 0x2A8,
			C10_QUADSPIBK1IO1													= 0x2A9,
			C10_SDMMC1D2															= 0x2AC,
			C10_DCMID8																= 0x2AD,
			C10_LCDR2																	= 0x2AE,
			C10_EVENTOUT															= 0x2AF,
			
			C11_HRTIMERFLT2														= 0x2B2,
			C11_DFSDMDATIN5														= 0x2B3,
			C11_SPI3MISO_I2S3SDI											= 0x2B6,
			C11_USART3RX															= 0x2B7,
			C11_UART4RX																= 0x2B8,
			C11_QUADSPIBK2NCS													= 0x2B9,
			C11_SDMMC1D3															= 0x2BC,
			C11_DCMID4																= 0x2BD,
			C11_EVENTOUT															= 0x2BF,
			
			C12_TRACED3																= 0x2C0,
			C12_HRTIMEREEV2														= 0x2C2,
			C12_SPI3MOSI_I2S3SDO											= 0x2C6,
			C12_USART3CK															= 0x2C7,
			C12_UART5TX																= 0x2C8,
			C12_SDMMC1CK															= 0x2CC,
			C12_DCMID9																= 0x2CD,
			C12_EVENTOUT															= 0x2CF,
			
			C13_EVENTOUT															= 0x2DF,
			
			C14_EVENTOUT															= 0x2EF,
			
			C15_EVENTOUT															= 0x2FF,
			
			
			
			
			
			
			
			D0_DFSDMCKIN6															= 0x303,
			D0_SAI3SCKA																= 0x306,
			D0_UART4RX																= 0x308,
			D0_FDCAN1RX																= 0x309,
			D0_FMCD2_FMCDA2														= 0x30C,
			D0_EVENTOUT																= 0x30F,
			
			D1_DFSDMDATIN6														= 0x313,
			D1_SAI3SDA																= 0x316,
			D1_UART4TX																= 0x318,
			D1_FDCAN1TX																= 0x319,
			D1_FMCD3_FMCDA3														= 0x31C,
			D1_EVENTOUT																= 0x31F,
			
			D2_TRACED2																= 0x320,
			D2_TIMER3ETR															= 0x322,
			D2_UART5RX																= 0x328,
			D2_SDMMC1CMD															= 0x32C,
			D2_DCMID11																= 0x32D,
			D2_EVENTOUT																= 0x32F,
			
			D3_DFSDMCKOUT															= 0x333,
			D3_SPI2SCK_I2S2CK													= 0x335,
			D3_USART2CTS_USART2NSS										= 0x337,
			D3_FMCCLK																	= 0x33C,
			D3_DCMID5																	= 0x33D,
			D3_LCDG7																	= 0x33E,
			D3_EVENTOUT																= 0x33F,
			
			D4_HRTIMERFLT3														= 0x342,
			D4_SAI3FSA																= 0x346,
			D4_USART2RTS_USART2DE											= 0x347,
			D4_FDCAN1RXFDMODE													= 0x349,
			D4_FMCNOE																	= 0x34C,
			D4_EVENTOUT																= 0x34F,
			
			D5_HRTIMEREEV3														= 0x352,
			D5_USART2TX																= 0x357,
			D5_FDCAN1TXFDMODE													= 0x359,
			D5_FMCNWE																	= 0x35C,
			D5_EVENTOUT																= 0x35F,
			
			D6_SAI1D1																	= 0x362,
			D6_DFSDMCKIN4															= 0x363,
			D6_DFSDMDATIN1														= 0x364,
			D6_SPI3MOSI_I2S3SDO												= 0x365,
			D6_SAI1SDA																= 0x366,
			D6_USART2RX																= 0x367,
			D6_SAI4SDA																= 0x368,
			D6_FDCAN2RXFDMODE													= 0x369,
			D6_SAI4D1																	= 0x36A,
			D6_SDMMC2CK																= 0x36B,
			D6_FMCNWAIT																= 0x36C,
			D6_DCMID10																= 0x36D,
			D6_LCDB2																	= 0x36E,
			D6_EVENTOUT																= 0x36F,
			
			D7_DFSDMDATIN4														= 0x373,
			D7_SPI1MOSI_I2S1SDO												= 0x375,
			D7_DFSDMCKIN1															= 0x376,
			D7_USART2CK																= 0x377,
			D7_SPDIFRXIN1															= 0x379,
			D7_SDMMC2CMD															= 0x37B,
			D7_FMCNE1																	= 0x37C,
			D7_EVENTOUT																= 0x37F,
			
			D8_DFSDMCKIN3															= 0x383,
			D8_SAI3SCKB																= 0x386,
			D8_USART3TX																= 0x387,
			D8_SPDIFRXIN2															= 0x389,
			D8_FMCD13_FMCDA13													= 0x38C,
			D8_EVENTOUT																= 0x38F,
			
			D9_DFSDMDATIN3														= 0x393,
			D9_SAI3SDB																= 0x396,
			D9_USART3RX																= 0x397,
			D9_FDCAN2RXFDMODE													= 0x399,
			D9_FMCD14_FMCDA14													= 0x39C,
			D9_EVENTOUT																= 0x39F,
			
			D10_DFSDMCKOUT														= 0x3A3,
			D10_SAI3FSB																= 0x3A6,
			D10_USART3CK															= 0x3A7,
			D10_FDCAN2TXFDMODE												= 0x3A9,
			D10_FMCD15_FMCDA15												= 0x3AC,
			D10_LCDB3																	= 0x3AE,
			D10_EVENTOUT															= 0x3AF,
			
			D11_LPTIMER2IN2														= 0x3B3,
			D11_I2C4SMBA															= 0x3B4,
			D11_USART3CTS_USART3NSS										= 0x3B7,
			D11_QUADSPIBK1IO0													= 0x3B9,
			D11_SAI2SDA																= 0x3BA,
			D11_FMCA16																= 0x3BC,
			D11_EVENTOUT															= 0x3BF,
			
			D12_LPTIMER1IN1														= 0x3C1,
			D12_TIMER4CH1															= 0x3C2,
			D12_LPTIMER2IN1														= 0x3C3,
			D12_I2C4SCL																= 0x3C4,
			D12_USART3RTS_USART3DE										= 0x3C7,
			D12_QUADSPIBK1IO1													= 0x3C9,
			D12_SAI2FSA																= 0x3CA,
			D12_FMCA17																= 0x3CC,
			D12_EVENTOUT															= 0x3CF,
			
			D13_LPTIMER1OUT														= 0x3D1,
			D13_TIMER4CH2															= 0x3D2,
			D13_I2C4SDA																= 0x3D4,
			D13_QUADSPIBK1IO3													= 0x3D9,
			D13_SAI2SCKA															= 0x3DA,
			D13_FMCA18																= 0x3DC,
			D13_EVENTOUT															= 0x3DF,
			
			D14_TIMER4CH3															= 0x3E2,
			D14_SAI3MCLKB															= 0x3E6,
			D14_UART8CTS															= 0x3E8,
			D14_FMCD0_FMCDA0													= 0x3EC,
			D14_EVENTOUT															= 0x3EF,
			
			D15_TIMER4CH4															= 0x3F2,
			D15_SAI3MCLKA															= 0x3F6,
			D15_UART8RTS_UART8DE											= 0x3F8,
			D15_FMCD1_FMCDA1													= 0x3FC,
			D15_EVENTOUT															= 0x3FF,
			
			
			
			
			
			
			
			E0_LPTIMER1ETR														= 0x401,
			E0_TIMER4ETR															= 0x402,
			E0_HRTIMERSCIN														= 0x403,
			E0_LPTIMER2ETR														= 0x404,
			E0_UART8RX																= 0x408,
			E0_FDCAN1RXFDMODE													= 0x409,
			E0_SAI2MCLKA															= 0x40A,
			E0_FMCNBL0																= 0x40C,
			E0_DCMID2																	= 0x40D,
			E0_EVENTOUT																= 0x40F,
			
			E1_LPTIMER1IN2														= 0x411,
			E1_HRTIMERSCOUT														= 0x413,
			E1_UART8TX																= 0x418,
			E1_FDCAN1TXFDMODE													= 0x419,
			E1_FMCNBL1																= 0x41C,
			E1_DCMID3																	= 0x41D,
			E1_EVENTOUT																= 0x41F,
			
			E2_TRACECLK																= 0x420,
			E2_SAI1CK1																= 0x422,
			E2_SPI4SCK																= 0x425,
			E2_SAI1MCLKA															= 0x426,
			E2_SAI4MCLKA															= 0x428,
			E2_QUADSPIBK1IO2													= 0x429,
			E2_SAI4CK1																= 0x42A,
			E2_ETHMIITXD3															= 0x42B,
			E2_FMCA23																	= 0x42C,
			E2_EVENTOUT																= 0x42F,
			
			E3_TRACED0																= 0x430,
			E3_TIMER15BKIN														= 0x434,
			E3_SAI1SDB																= 0x436,
			E3_SAI4SDB																= 0x438,
			E3_FMCA19																	= 0x43C,
			E3_EVENTOUT																= 0x43F,
			
			E4_TRACED1																= 0x440,
			E4_SAI1D2																	= 0x442,
			E4_DFSDMDATIN3														= 0x443,
			E4_TIMER15CH1N														= 0x444,
			E4_SPI4NSS																= 0x445,
			E4_SAI1FSA																= 0x446,
			E4_SAI4FSA																= 0x448,
			E4_SAI4D2																	= 0x44A,
			E4_FMCA20																	= 0x44C,
			E4_DCMID4																	= 0x44D,
			E4_LCDB0																	= 0x44E,
			E4_EVENTOUT																= 0x44F,
			
			E5_TRACED2																= 0x450,
			E5_SAI1CK2																= 0x452,
			E5_DFSDMCKIN3															= 0x453,
			E5_TIMER15CH1															= 0x454,
			E5_SPI4MISO																= 0x455,
			E5_SAI1SCKA																= 0x456,
			E5_SAI4SCKA																= 0x458,
			E5_SAI4CK2																= 0x45A,
			E5_FMCA21																	= 0x45C,
			E5_DCMID6																	= 0x45D,
			E5_LCDG0																	= 0x45E,
			E5_EVENTOUT																= 0x45F,
			
			E6_TRACED3																= 0x460,
			E6_TIMER1BKIN2														= 0x461,
			E6_SAI1D1																	= 0x462,
			E6_TIMER15CH2															= 0x464,
			E6_SPI4MOSI																= 0x465,
			E6_SAI1SDA																= 0x466,
			E6_SAI4SDA																= 0x468,
			E6_SAI4D1																	= 0x469,
			E6_SAI2MCLKB															= 0x46A,
			E6_TIMER1BKIN2COMP12											= 0x46B,
			E6_FMCA22																	= 0x46C,
			E6_DCMID7																	= 0x46D,
			E6_LCDG1																	= 0x46E,
			E6_EVENTOUT																= 0x46F,
			
			E7_TIMER1ETR															= 0x471,
			E7_DFSDMDATIN2														= 0x473,
			E7_UART7RX																= 0x477,
			E7_QUADSPIBK2IO0													= 0x47A,
			E7_FMCD4_FMCDA4														= 0x47C,
			E7_EVENTOUT																= 0x47F,
			
			E8_TIMER1CH1N															= 0x481,
			E8_DFSDMCKIN2															= 0x483,
			E8_UART7TX																= 0x487,
			E8_QUADSPIBK2IO1													= 0x48A,
			E8_FMCD5_FMCDA5														= 0x48C,
			E8_COMP2OUT																= 0x48D,
			E8_EVENTOUT																= 0x48F,
			
			E9_TIMER1CH1															= 0x491,
			E9_DFSDMCKOUT															= 0x493,
			E9_UART7RTS_UART7DE												= 0x497,
			E9_QUADSPIBK2IO2													= 0x49A,
			E9_FMCD6_FMCDA6														= 0x49C,
			E9_EVENTOUT																= 0x49F,
			
			E10_TIMER1CH2N														= 0x4A1,
			E10_DFSDMDATIN4														= 0x4A3,
			E10_UART7CTS															= 0x4A7,
			E10_QUADSPIBK2IO3													= 0x4AA,
			E10_FMCD7_FMCDA7													= 0x4AC,
			E10_EVENTOUT															= 0x4AF,
			
			E11_TIMER1CH2															= 0x4B1,
			E11_DFSDMCKIN4														= 0x4B3,
			E11_SPI4NSS																= 0x4B5,
			E11_SAI2SDB																= 0x4BA,
			E11_FMCD8_FMCDA8													= 0x4BC,
			E11_LCDG3																	= 0x4BE,
			E11_EVENTOUT															= 0x4BF,
			
			E12_TIMER1CH3N														= 0x4C1,
			E12_DFSDMDATIN5														= 0x4C3,
			E12_SPI4SCK																= 0x4C5,
			E12_SAI2SCKB															= 0x4CA,
			E12_FMCD9_FMCDA9													= 0x4CC,
			E12_COMP1OUT															= 0x4CD,
			E12_LCDB4																	= 0x4CE,
			E12_EVENTOUT															= 0x4CF,
			
			E13_TIMER1CH3															= 0x4D1,
			E13_DFSDMCKIN5														= 0x4D3,
			E13_SPI4MISO															= 0x4D5,
			E13_SAI2FSB																= 0x4DA,
			E13_FMCD10_FMCDA10												= 0x4DC,
			E13_COMP2OUT															= 0x4DD,
			E13_LCDDE																	= 0x4DE,
			E13_EVENTOUT															= 0x4DF,
			
			E14_TIMER1CH4															= 0x4E1,
			E14_SPI4MOSI															= 0x4E5,
			E14_SAI2MCLKB															= 0x4EA,
			E14_FMCD11_FMCDA11												= 0x4EC,
			E14_LCDCLK																= 0x4EE,
			E14_EVENTOUT															= 0x4EF,
			
			E15_TIMER1BKIN														= 0x4F1,
			E15_FMCD12_FMCDA12												= 0x4FC,
			E15_TIMER1BKINCOMP12_COMPTIMER1BKIN				= 0x4FD,
			E15_LCDR7																	= 0x4FE,
			E15_EVENTOUT															= 0x4FF,
			
			
			
			
			
			
			
			F0_I2C2SDA																= 0x504,
			F0_FMCA0																	= 0x50C,
			F0_EVENTOUT																= 0x50F,
			
			F1_I2C2SCL																= 0x514,
			F1_FMCA1																	= 0x51C,
			F1_EVENTOUT																= 0x51F,
			
			F2_I2C2SMBA																= 0x524,
			F2_FMCA2																	= 0x52C,
			F2_EVENTOUT																= 0x52F,
			
			F3_FMCA3																	= 0x53C,
			F3_EVENTOUT																= 0x53F,
			
			F4_FMCA4																	= 0x54C,
			F4_EVENTOUT																= 0x54F,
			
			F5_FMCA5																	= 0x55C,
			F5_EVENTOUT																= 0x55F,
			
			F6_TIMER16CH1															= 0x561,
			F6_SPI5NSS																= 0x565,
			F6_SAI1SDB																= 0x566,
			F6_UART7RX																= 0x567,
			F6_SAI4SDB																= 0x568,
			F6_QUADSPIBK1IO3													= 0x569,
			F6_EVENTOUT																= 0x56F,
			
			F7_TIMER17CH1															= 0x571,
			F7_SPI5SCK																= 0x575,
			F7_SAI1MCLKB															= 0x576,
			F7_UART7TX																= 0x577,
			F7_SAI4MCLKB															= 0x578,
			F7_QUADSPIBK1IO2													= 0x579,
			F7_EVENTOUT																= 0x57F,
			
			F8_TIMER16CH1N														= 0x581,
			F8_SPI5MISO																= 0x585,
			F8_SAI1SCKB																= 0x586,
			F8_UART7RTS_UART7DE												= 0x587,
			F8_SAI4SCKB																= 0x588,
			F8_TIMER13CH1															= 0x589,
			F8_QUADSPIBK1IO0													= 0x58A,
			F8_EVENTOUT																= 0x58F,
			
			F9_TIMER17CH1N														= 0x591,
			F9_SPI5MOSI																= 0x595,
			F9_SAI1FSB																= 0x596,
			F9_UART7CTS																= 0x597,
			F9_SAI4FSB																= 0x598,
			F9_TIMER14CH1															= 0x599,
			F9_QUADSPIBK1IO1													= 0x59A,
			F9_EVENTOUT																= 0x59F,
			
			F10_TIMER16BKIN														= 0x5A1,
			F10_SAI1D3																= 0x5A2,
			F10_QUADSPICLK														= 0x5A9,
			F10_SAI4D3																= 0x5AA,
			F10_DCMID11																= 0x5AD,
			F10_LCDDE																	= 0x5AE,
			F10_EVENTOUT															= 0x5AF,
			
			F11_SPI5MOSI															= 0x5B5,
			F11_SAI2SDB																= 0x5BA,
			F11_FMCSDNRAS															= 0x5BC,
			F11_DCMID12																= 0x5BD,
			F11_EVENTOUT															= 0x5BF,
			
			F12_FMCA6																	= 0x5CC,
			F12_EVENTOUT															= 0x5CF,
			
			F13_DFSDMDATIN6														= 0x5D3,
			F13_I2C4SMBA															= 0x5D4,
			F13_FMCA7																	= 0x5DC,
			F13_EVENTOUT															= 0x5DF,
			
			F14_DFSDMCKIN6														= 0x5E3,
			F14_I2C4SCL																= 0x5E4,
			F14_FMCA8																	= 0x5EC,
			F14_EVENTOUT															= 0x5EF,
			
			F15_I2C4SDA																= 0x5F4,
			F15_FMCA9																	= 0x5FC,
			F15_EVENTOUT															= 0x5FF,
			
			
			
			
			
			
			
			G0_FMCA10																	= 0x60C,
			G0_EVENTOUT																= 0x60F,
			
			G1_FMCA11																	= 0x61C,
			G1_EVENTOUT																= 0x61F,
			
			G2_TIMER8BKIN															= 0x623,
			G2_TIMER8BKINCOMP12												= 0x62B,
			G2_FMCA12																	= 0x62C,
			G2_EVENTOUT																= 0x62F,
			
			G3_TIMER8BKIN2														= 0x633,
			G3_TIMER8BKIN2COMP12											= 0x63B,
			G3_FMCA13																	= 0x63C,
			G3_EVENTOUT																= 0x63F,
			
			G4_TIMER1BKIN2														= 0x641,
			G4_TIMER1BKIN2COMP12											= 0x64B,
			G4_FMCA14_FMCBA0													= 0x64C,
			G4_EVENTOUT																= 0x64F,
			
			G5_TIMER1ETR															= 0x651,
			G5_FMCA15_FMCBA1													= 0x65C,
			G5_EVENTOUT																= 0x65F,
			
			G6_TIMER17BKIN														= 0x661,
			G6_HRTIMERCHE1														= 0x662,
			G6_QUADSPIBK1NCS													= 0x66A,
			G6_FMCNE3																	= 0x66C,
			G6_DCMID12																= 0x66D,
			G6_LCDR7																	= 0x66E,
			G6_EVENTOUT																= 0x66F,
			
			G7_HRTIMERCHE2														= 0x672,
			G7_SAI1MCLKA															= 0x676,
			G7_USART6CK																= 0x677,
			G7_FMCINT																	= 0x67C,
			G7_DCMID13																= 0x67D,
			G7_LCDCLK																	= 0x67E,
			G7_EVENTOUT																= 0x67F,
			
			G8_TIMER8ETR															= 0x683,
			G8_SPI6NSS																= 0x685,
			G8_USART6RTS_USART6DE											= 0x687,
			G8_SPDIFRXIN3															= 0x688,
			G8_ETHPPSOUT															= 0x68B,
			G8_FMCSDCLK																= 0x68C,
			G8_LCDG7																	= 0x68E,
			G8_EVENTOUT																= 0x68F,
			
			G9_SPI1MISO_I2S1SDI												= 0x695,
			G9_USART6RX																= 0x697,
			G9_SPDIFRXIN4															= 0x698,
			G9_QUADSPIBK2IO2													= 0x699,
			G9_SAI2FSB																= 0x69A,
			G9_FMCNE2_FMCNCE													= 0x69C,
			G9_DCMIVSYNC															= 0x69D,
			G9_EVENTOUT																= 0x69F,
			
			G10_HRTIMERFLT5														= 0x6A2,
			G10_SPI1NSS_I2S1WS												= 0x6A5,
			G10_LCDG3																	= 0x6A9,
			G10_SAI2SDB																= 0x6AA,
			G10_FMCNE3																= 0x6AC,
			G10_DCMID2																= 0x6AD,
			G10_LCDB2																	= 0x6AE,
			G10_EVENTOUT															= 0x6AF,
			
			G11_LPTIMER1IN2														= 0x6B1,
			G11_HRTIMEREEV4														= 0x6B2,
			G11_SPI1SCK_I2S1CK												= 0x6B5,
			G11_SPDIFRXIN1														= 0x6B8,
			G11_SDMMC2D2															= 0x6BA,
			G11_ETHMIITXEN_ETHRMIITXEN								= 0x6BB,
			G11_DCMID3																= 0x6BD,
			G11_LCDB3																	= 0x6BE,
			G11_EVENTOUT															= 0x6BF,
			
			G12_LPTIMER1IN1														= 0x6C1,
			G12_HRTIMEREEV5														= 0x6C2,
			G12_SPI6MISO															= 0x6C5,
			G12_USART6RTS_USART6DE										= 0x6C7,
			G12_SPDIFRXIN2														= 0x6C8,
			G12_LCDB4																	= 0x6C9,
			G12_ETHMIITXD1_ETHRMIITXD1								= 0x6CB,
			G12_FMCNE4																= 0x6CC,
			G12_LCDB1																	= 0x6CE,
			G12_EVENTOUT															= 0x6CF,
			
			G13_TRACED0																= 0x6D0,
			G13_LPTIMER1OUT														= 0x6D1,
			G13_HRTIMEREEV10													= 0x6D2,
			G13_SPI6SCK																= 0x6D5,
			G13_USART6CTS_USART6NSS										= 0x6D7,
			G13_ETHMIITXD0_ETHRMIITXD0								= 0x6DB,
			G13_FMCA24																= 0x6DC,
			G13_LCDR0																	= 0x6DE,
			G13_EVENTOUT															= 0x6DF,
			
			G14_TRACED1																= 0x6E0,
			G14_LPTIMER1ETR														= 0x6E1,
			G14_SPI6MOSI															= 0x6E5,
			G14_USART6TX															= 0x6E7,
			G14_QUADSPIBK2IO3													= 0x6E9,
			G14_ETHMIITXD1_ETHRMIITXD1								= 0x6EB,
			G14_FMCA25																= 0x6EC,
			G14_LCDB0																	= 0x6EE,
			G14_EVENTOUT															= 0x6EF,
			
			G15_USART6CTS_USART6NSS										= 0x6F7,
			G15_FMCSDNCAS															= 0x6FC,
			G15_DCMID13																= 0x6FD,
			G15_EVENTOUT															= 0x6FF,
			
			
			
			
			
			
			
			H0_EVENTOUT																= 0x70F,
			
			H1_EVENTOUT																= 0x71F,
			
			H2_LPTIMER1IN2														= 0x721,
			H2_QUADSPIBK2IO0													= 0x729,
			H2_SAI2SCKB																= 0x72A,
			H2_ETHMIICRS															= 0x72B,
			H2_FMCSDCKE0															= 0x72C,
			H2_LCDR0																	= 0x72E,
			H2_EVENTOUT																= 0x72F,
			
			H3_QUADSPIBK2IO1													= 0x739,
			H3_SAI2MCLKB															= 0x73A,
			H3_ETHMIICOL															= 0x73B,
			H3_FMCSDNE0																= 0x73C,
			H3_LCDR1																	= 0x73E,
			H3_EVENTOUT																= 0x73F,
			
			H4_I2C2SCL																= 0x744,
			H4_LCDG5																	= 0x749,
			H4_USB1ULHXT															= 0x74A,
			H4_LCDG4																	= 0x74E,
			H4_EVENTOUT																= 0x74F,
			
			H5_I2C2SDA																= 0x754,
			H5_SPI5NSS																= 0x755,
			H5_FMCSDNWE																= 0x75C,
			H5_EVENTOUT																= 0x75F,
			
			H6_TIMER12CH1															= 0x762,
			H6_I2C2SMBA																= 0x764,
			H6_SPI5SCK																= 0x765,
			H6_ETHMIIRXD2															= 0x76B,
			H6_FMCSDNE1																= 0x76C,
			H6_DCMID8																	= 0x76D,
			H6_EVENTOUT																= 0x76F,
			
			H7_I2C3SCL																= 0x774,
			H7_SPI5MISO																= 0x775,
			H7_ETHMIIRXD3															= 0x77B,
			H7_FMCSDCKE1															= 0x77C,
			H7_DCMID9																	= 0x77D,
			H7_EVENTOUT																= 0x77F,
			
			H8_TIMER5ETR															= 0x782,
			H8_I2C3SDA																= 0x784,
			H8_FMCD16																	= 0x78C,
			H8_DCMIHSYNC															= 0x78D,
			H8_LCDR2																	= 0x78E,
			H8_EVENTOUT																= 0x78F,
			
			H9_TIMER12CH2															= 0x792,
			H9_I2C3SMBA																= 0x794,
			H9_FMCD17																	= 0x79C,
			H9_DCMID0																	= 0x79D,
			H9_LCDR3																	= 0x79E,
			H9_EVENTOUT																= 0x79F,
			
			H10_TIMER5CH1															= 0x7A2,
			H10_I2C4SMBA															= 0x7A4,
			H10_FMCD18																= 0x7AC,
			H10_DCMID1																= 0x7AD,
			H10_LCDR4																	= 0x7AE,
			H10_EVENTOUT															= 0x7AF,
			
			H11_TIMER5CH2															= 0x7B2,
			H11_I2C4SCL																= 0x7B4,
			H11_FMCD19																= 0x7BC,
			H11_DCMID2																= 0x7BD,
			H11_LCDR5																	= 0x7BE,
			H11_EVENTOUT															= 0x7BF,
			
			H12_TIMER5CH3															= 0x7C2,
			H12_I2C4SDA																= 0x7C4,
			H12_FMCD20																= 0x7CC,
			H12_DCMID3																= 0x7CD,
			H12_LCDR6																	= 0x7CE,
			H12_EVENTOUT															= 0x7CF,
			
			H13_TIMER8CH1N														= 0x7D3,
			H13_UART4TX																= 0x7D8,
			H13_FDCAN1TX															= 0x7D9,
			H13_FMCD21																= 0x7DC,
			H13_LCDG2																	= 0x7DE,
			H13_EVENTOUT															= 0x7DF,
			
			H14_TIMER8CH2N														= 0x7E3,
			H14_UART4RX																= 0x7E8,
			H14_FDCAN1RX															= 0x7E9,
			H14_FMCD22																= 0x7EC,
			H14_DCMID4																= 0x7ED,
			H14_LCDG3																	= 0x7EE,
			H14_EVENTOUT															= 0x7EF,
			
			H15_TIMER8CH3N														= 0x7F3,
			H15_FDCAN1TXFDMODE												= 0x7F9,
			H15_FMCD23																= 0x7FC,
			H15_DCMID11																= 0x7FD,
			H15_LCDG4																	= 0x7FE,
			H15_EVENTOUT															= 0x7FF,
			
			
			
			
			
			
			
			I0_TIMER5CH4															= 0x802,
			I0_SPI2NSS_I2S2WS													= 0x805,
			I0_FDCAN1RXFDMODE													= 0x809,
			I0_FMCD24																	= 0x80C,
			I0_DCMID13																= 0x80D,
			I0_LCDG5																	= 0x80E,
			I0_EVENTOUT																= 0x80F,
			
			I1_TIMER8BKIN2														= 0x813,
			I1_SPI2SCK_I2S2CK													= 0x815,
			I1_TIMER8BKIN2COMP12											= 0x81B,
			I1_FMCD25																	= 0x81C,
			I1_DCMID8																	= 0x81D,
			I1_LCDG6																	= 0x81E,
			I1_EVENTOUT																= 0x81F,
			
			I2_TIMER8CH4															= 0x823,
			I2_SPI2MISO_I2S2SDI												= 0x825,
			I2_FMCD26																	= 0x82C,
			I2_DCMID9																	= 0x82D,
			I2_LCDG7																	= 0x82E,
			I2_EVENTOUT																= 0x82F,
			
			I3_TIMER8ETR															= 0x833,
			I3_SPI2MOSI_I2S2SDO												= 0x835,
			I3_FMCD27																	= 0x83C,
			I3_DCMID10																= 0x83D,
			I3_EVENTOUT																= 0x83F,
			
			I4_TIMER8BKIN															= 0x843,
			I4_SAI2MCLKA															= 0x84A,
			I4_TIMER8BKINCOMP12												= 0x84B,
			I4_FMCNBL2																= 0x84C,
			I4_DCMID5																	= 0x84D,
			I4_LCDB4																	= 0x84E,
			I4_EVENTOUT																= 0x84F,
			
			I5_TIMER8CH1															= 0x853,
			I5_SAI2SCKA																= 0x85A,
			I5_FMCNBL3																= 0x85C,
			I5_DCMIVSYNC															= 0x85D,
			I5_LCDB5																	= 0x85E,
			I5_EVENTOUT																= 0x85F,
			
			I6_TIMER8CH2															= 0x863,
			I6_SAI2SDA																= 0x86A,
			I6_FMCD28																	= 0x86C,
			I6_DCMID6																	= 0x86D,
			I6_LCDB6																	= 0x86E,
			I6_EVENTOUT																= 0x86F,
			
			I7_TIMER8CH3															= 0x873,
			I7_SAI2FSA																= 0x87A,
			I7_FMCD29																	= 0x87C,
			I7_DCMID7																	= 0x87D,
			I7_LCDB7																	= 0x87E,
			I7_EVENTOUT																= 0x87F,
			
			I8_EVENTOUT																= 0x88F,
			
			I9_UART4RX																= 0x898,
			I9_FDCAN1RX																= 0x899,
			I9_FMCD30																	= 0x89C,
			I9_LCDVSYNC																= 0x89E,
			I9_EVENTOUT																= 0x89F,
			
			I10_FDCAN1RXFDMODE												= 0x8A9,
			I10_ETHMIIRXER														= 0x8AB,
			I10_FMCD31																= 0x8AC,
			I10_LCDHSYNC															= 0x8AE,
			I10_EVENTOUT															= 0x8AF,
			
			I11_LCDG6																	= 0x8B9,
			I11_USB1ULPIDIR														= 0x8BA,
			I11_EVENTOUT															= 0x8BF,
			
			I12_LCDHSYNC															= 0x8CE,
			I12_EVENTOUT															= 0x8CF,
			
			I13_LCDVSYNC															= 0x8DE,
			I13_EVENTOUT															= 0x8DF,
			
			I14_LCDCLK																= 0x8EE,
			I14_EVENTOUT															= 0x8EF,
			
			I15_LCDG2																	= 0x8F9,
			I15_LCDR0																	= 0x8FE,
			I15_EVENTOUT															= 0x8FF,
			
			
			
			
			
			
			
			J0_LCDR7																	= 0x909,
			J0_LCDR1																	= 0x90E,
			J0_EVENTOUT																= 0x90F,
			
			J1_LCDR2																	= 0x91E,
			J1_EVENTOUT																= 0x91F,
			
			J2_LCDR3																	= 0x92E,
			J2_EVENTOUT																= 0x92F,
			
			J3_LCDR4																	= 0x93E,
			J3_EVENTOUT																= 0x93F,
			
			J4_LCDR5																	= 0x94E,
			J4_EVENTOUT																= 0x94F,
			
			J5_LCDR6																	= 0x95E,
			J5_EVENTOUT																= 0x95F,
			
			J6_TIMER8CH2															= 0x963,
			J6_LCDR7																	= 0x96E,
			J6_EVENTOUT																= 0x96F,
			
			J7_TRGIN																	= 0x970,
			J7_TIMER8CH2N															= 0x973,
			J7_LCDG0																	= 0x97E,
			J7_EVENTOUT																= 0x97F,
			
			J8_TIMER1CH3N															= 0x981,
			J8_TIMER8CH1															= 0x983,
			J8_UART8TX																= 0x988,
			J8_LCDG1																	= 0x98E,
			J8_EVENTOUT																= 0x98F,
			
			J9_TIMER1CH3															= 0x991,
			J9_TIMER8CH1N															= 0x993,
			J9_UART8RX																= 0x998,
			J9_LCDG2																	= 0x99E,
			J9_EVENTOUT																= 0x99F,
			
			J10_TIMER1CH2N														= 0x9A1,
			J10_TIMER8CH2															= 0x9A3,
			J10_SPI5MOSI															= 0x9A5,
			J10_LCDG3																	= 0x9AE,
			J10_EVENTOUT															= 0x9AF,
			
			J11_TIMER1CH2															= 0x9B1,
			J11_TIMER8CH2N														= 0x9B3,
			J11_SPI5MISO															= 0x9B5,
			J11_LCDG4																	= 0x9BE,
			J11_EVENTOUT															= 0x9BF,
			
			J12_TRGOUT																= 0x9C0,
			J12_LCDG3																	= 0x9C9,
			J12_LCDB0																	= 0x9CE,
			J12_EVENTOUT															= 0x9CF,
			
			J13_LCDB4																	= 0x9D9,
			J13_LCDB1																	= 0x9DE,
			J13_EVENTOUT															= 0x9DF,
			
			J14_LCDB2																	= 0x9EE,
			J14_EVENTOUT															= 0x9EF,
			
			J15_LCDB3																	= 0x9FE,
			J15_EVENTOUT															= 0x9FF,
			
			
			
			
			
			
			
			K0_TIMER1CH1N															= 0xA01,
			K0_TIMER8CH3															= 0xA03,
			K0_SPI5SCK																= 0xA05,
			K0_LCDG5																	= 0xA0E,
			K0_EVENTOUT																= 0xA0F,
			
			K1_TIMER1CH1															= 0xA11,
			K1_TIMER8CH3N															= 0xA13,
			K1_SPI5NSS																= 0xA15,
			K1_LCDG6																	= 0xA1E,
			K1_EVENTOUT																= 0xA1F,
			
			K2_TIMER1BKIN															= 0xA21,
			K2_TIMER8BKIN															= 0xA23,
			K2_TIMER8BKINCOMP12												= 0xA2A,
			K2_TIMER1BKINCOMP12												= 0xA2B,
			K2_LCDG7																	= 0xA2E,
			K2_EVENTOUT																= 0xA2F,
			
			K3_LCDB4																	= 0xA3E,
			K3_EVENTOUT																= 0xA3F,
			
			K4_LCDB5																	= 0xA4E,
			K4_EVENTOUT																= 0xA4F,
			
			K5_LCDB6																	= 0xA5E,
			K5_EVENTOUT																= 0xA5F,
			
			K6_LCDB7																	= 0xA6E,
			K6_EVENTOUT																= 0xA6F,
			
			K7_LCDDE																	= 0xA7E,
			K7_EVENTOUT																= 0xA7F
		};
		
		
		
		
		
	private:
		
		constexpr inline GPIO();
		GPIO(const GPIO& gpio) = delete;
		inline ~GPIO();
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup(RCC& rcc);
		
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



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

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