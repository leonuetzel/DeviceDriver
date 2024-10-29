#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class DMAMUX
{
	public:
		
		enum class e_input
		{
			DMAMUX_1_REQUEST_GENERATOR_0	= 0x001,
			DMAMUX_1_REQUEST_GENERATOR_1	= 0x002,
			DMAMUX_1_REQUEST_GENERATOR_2	= 0x003,
			DMAMUX_1_REQUEST_GENERATOR_3	= 0x004,
			DMAMUX_1_REQUEST_GENERATOR_4	= 0x005,
			DMAMUX_1_REQUEST_GENERATOR_5	= 0x006,
			DMAMUX_1_REQUEST_GENERATOR_6	= 0x007,
			DMAMUX_1_REQUEST_GENERATOR_7	= 0x008,
			ADC_1_DMA											= 0x009,
			ADC_2_DMA											= 0x00A,
			TIMER_1_CH1										= 0x00B,
			TIMER_1_CH2										= 0x00C,
			TIMER_1_CH3										= 0x00D,
			TIMER_1_CH4										= 0x00E,
			TIMER_1_UPDATE								= 0x00F,
			TIMER_1_TRIGGER								= 0x010,
			TIMER_1_COMMUTATE							= 0x011,
			TIMER_2_CH1										= 0x012,
			TIMER_2_CH2										= 0x013,
			TIMER_2_CH3										= 0x014,
			TIMER_2_CH4										= 0x015,
			TIMER_2_UPDATE								= 0x016,
			TIMER_3_CH1										= 0x017,
			TIMER_3_CH2										= 0x018,
			TIMER_3_CH3										= 0x019,
			TIMER_3_CH4										= 0x01A,
			TIMER_3_UPDATE								= 0x01B,
			TIMER_3_TRIGGER								= 0x01C,
			TIMER_4_CH1										= 0x01D,
			TIMER_4_CH2										= 0x01E,
			TIMER_4_CH3										= 0x01F,
			TIMER_4_UPDATE								= 0x020,
			I2C_1_RX_DMA									= 0x021,
			I2C_1_TX_DMA									= 0x022,
			I2C_2_RX_DMA									= 0x023,
			I2C_2_TX_DMA									= 0x024,
			SPI_1_RX_DMA									= 0x025,
			SPI_1_TX_DMA									= 0x026,
			SPI_2_RX_DMA									= 0x027,
			SPI_2_TX_DMA									= 0x028,
			USART_1_RX_DMA								= 0x029,
			USART_1_TX_DMA								= 0x02A,
			USART_2_RX_DMA								= 0x02B,
			USART_2_TX_DMA								= 0x02C,
			USART_3_RX_DMA								= 0x02D,
			USART_3_TX_DMA								= 0x02E,
			TIMER_8_CH1										= 0x02F,
			TIMER_8_CH2										= 0x030,
			TIMER_8_CH3										= 0x031,
			TIMER_8_CH4										= 0x032,
			TIMER_8_UPDATE								= 0x033,
			TIMER_8_TRIGGER								= 0x034,
			TIMER_8_COMMUTATE							= 0x035,
			
			TIMER_5_CH1										= 0x037,
			TIMER_5_CH2										= 0x038,
			TIMER_5_CH3										= 0x039,
			TIMER_5_CH4										= 0x03A,
			TIMER_5_UPDATE								= 0x03B,
			TIMER_5_TRIGGER								= 0x03C,
			SPI_3_RX_DMA									= 0x03D,
			SPI_3_TX_DMA									= 0x03E,
			UART_4_RX_DMA									= 0x03F,
			UART_4_TX_DMA									= 0x040,
			UART_5_RX_DMA									= 0x041,
			UART_5_TX_DMA									= 0x042,
			DAC_1_CH1_DMA									= 0x043,
			DAC_1_CH2_DMA									= 0x044,
			TIMER_6_UPDATE								= 0x045,
			TIMER_7_UPDATE								= 0x046,
			USART_6_RX_DMA								= 0x047,
			USART_6_TX_DMA								= 0x048,
			I2C_3_RX_DMA									= 0x049,
			I2C_3_TX_DMA									= 0x04A,
			DCMI_DMA											= 0x04B,
			CRYP_IN_DMA										= 0x04C,
			CRYP_OUT_DMA									= 0x04D,
			HASH_IN_DMA										= 0x04E,
			UART_7_RX_DMA									= 0x04F,
			UART_7_TX_DMA									= 0x050,
			UART_8_RX_DMA									= 0x051,
			UART_8_TX_DMA									= 0x052,
			SPI_4_RX_DMA									= 0x053,
			SPI_4_TX_DMA									= 0x054,
			SPI_5_RX_DMA									= 0x055,
			SPI_5_TX_DMA									= 0x056,
			SAI_1_A_DMA										= 0x057,
			SAI_1_B_DMA										= 0x058,
			SAI_2_A_DMA										= 0x059,
			SAI_2_B_DMA										= 0x05A,
			SWPMI_RX_DMA									= 0x05B,
			SWPMI_TX_DMA									= 0x05C,
			SPDIFRX_DAT_DMA								= 0x05D,
			SPDIFRX_CTRL_DMA							= 0x05E,
			HR_REQ_1											= 0x05F,
			HR_REQ_2											= 0x060,
			HR_REQ_3											= 0x061,
			HR_REQ_4											= 0x062,
			HR_REQ_5											= 0x063,
			HR_REQ_6											= 0x064,
			DFSDM_DMA_0										= 0x065,
			DFSDM_DMA_1										= 0x066,
			DFSDM_DMA_2										= 0x067,
			DFSDM_DMA_3										= 0x068,
			TIMER_15_CH1									= 0x069,
			TIMER_15_UPDATE								= 0x06A,
			TIMER_15_TRIGGER							= 0x06B,
			TIMER_15_COMMUTATE						= 0x06C,
			TIMER_16_CH1									= 0x06D,
			TIMER_16_UPDATE								= 0x06E,
			TIMER_17_CH1									= 0x06F,
			TIMER_17_UPDATE								= 0x070,
			SAI_3_A_DMA										= 0x071,
			SAI_3_B_DMA										= 0x072,
			ADC_3_DMA											= 0x073,
			
			
			
			DMAMUX_2_REQUEST_GENERATOR_0	= 0x101,
			DMAMUX_2_REQUEST_GENERATOR_1	= 0x102,
			DMAMUX_2_REQUEST_GENERATOR_2	= 0x103,
			DMAMUX_2_REQUEST_GENERATOR_3	= 0x104,
			DMAMUX_2_REQUEST_GENERATOR_4	= 0x105,
			DMAMUX_2_REQUEST_GENERATOR_5	= 0x106,
			DMAMUX_2_REQUEST_GENERATOR_6	= 0x107,
			DMAMUX_2_REQUEST_GENERATOR_7	= 0x108,
			LP_UART_RX_DMA								= 0x109,
			LP_UART_TX_DMA								= 0x10A,
			SPI_6_RX_DMA									= 0x10B,
			SPI_6_TX_DMA									= 0x10C,
			I2C_4_RX_DMA									= 0x10D,
			I2C_4_TX_DMA									= 0x10E,
			SAI_4_A_DMA										= 0x10F,
			SAI_4_B_DMA										= 0x110,
			ADC_3_DMA_DMAMUX_2						= 0x111
		};
		
		enum class e_output
		{
			DMA_1_CH0	= 0x00,
			DMA_1_CH1	= 0x01,
			DMA_1_CH2	= 0x02,
			DMA_1_CH3	= 0x03,
			DMA_1_CH4	= 0x04,
			DMA_1_CH5	= 0x05,
			DMA_1_CH6	= 0x06,
			DMA_1_CH7	= 0x07,
			DMA_2_CH0	= 0x08,
			DMA_2_CH1	= 0x09,
			DMA_2_CH2	= 0x0A,
			DMA_2_CH3	= 0x0B,
			DMA_2_CH4	= 0x0C,
			DMA_2_CH5	= 0x0D,
			DMA_2_CH6	= 0x0E,
			DMA_2_CH7	= 0x0F,
			BDMA_CH0	= 0x10,
			BDMA_CH1	= 0x11,
			BDMA_CH2	= 0x12,
			BDMA_CH3	= 0x13,
			BDMA_CH4	= 0x14,
			BDMA_CH5	= 0x15,
			BDMA_CH6	= 0x16,
			BDMA_CH7	= 0x17
		};
		
		
		
		
		
	private:
		
		constexpr inline DMAMUX();
		DMAMUX(const DMAMUX& dmamux) = delete;
		inline ~DMAMUX();
		
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup();
		
		feedback map(e_input input, e_output output);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline DMAMUX::DMAMUX()
{
	
}


inline DMAMUX::~DMAMUX()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

