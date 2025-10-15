#pragma once

#include "registers.hpp"





class DMAMUX
{
	public:
		
		enum class e_input: uint8
		{
			DMAMUX_REQUEST_GENERATOR_0		= 0x01,
			DMAMUX_REQUEST_GENERATOR_1		= 0x02,
			DMAMUX_REQUEST_GENERATOR_2		= 0x03,
			DMAMUX_REQUEST_GENERATOR_3		= 0x04,
			ADC_1													= 0x05,
			DAC_1_CH1											= 0x06,
			DAC_1_CH2											= 0x07,
			TIMER_6_UPDATE								= 0x08,
			TIMER_7_UPDATE								= 0x09,
			SPI_1_RX											= 0x0A,
			SPI_1_TX											= 0x0B,
			SPI_2_RX											= 0x0C,
			SPI_2_TX											= 0x0D,
			SPI_3_RX											= 0x0E,
			SPI_3_TX											= 0x0F,
			I2C_1_RX											= 0x10,
			I2C_1_TX											= 0x11,
			I2C_2_RX											= 0x12,
			I2C_2_TX											= 0x13,
			I2C_3_RX											= 0x14,
			I2C_3_TX											= 0x15,
			I2C_4_RX											= 0x16,
			I2C_4_TX											= 0x17,
			USART_1_RX										= 0x18,
			USART_1_TX										= 0x19,
			USART_2_RX										= 0x1A,
			USART_2_TX										= 0x1B,
			USART_3_RX										= 0x1C,
			USART_3_TX										= 0x1D,
			UART_4_RX											= 0x1E,
			UART_4_TX											= 0x1F,
			UART_5_RX											= 0x20,
			UART_5_TX											= 0x21,
			LPUART_1_RX										= 0x22,
			LPUART_1_TX										= 0x23,
			ADC_2													= 0x24,
			ADC_3													= 0x25,
			ADC_4													= 0x26,
			ADC_5													= 0x27,
			QUADSPI												= 0x28,
			DAC_2_CH1											= 0x29,
			TIMER_1_CH1										= 0x2A,
			TIMER_1_CH2										= 0x2B,
			TIMER_1_CH3										= 0x2C,
			TIMER_1_CH4										= 0x2D,
			TIMER_1_UPDATE								= 0x2E,
			TIMER_1_TRIGGER								= 0x2F,
			TIMER_1_COMMUTATION						= 0x30,
			TIMER_8_CH1										= 0x31,
			TIMER_8_CH2										= 0x32,
			TIMER_8_CH3										= 0x33,
			TIMER_8_CH4										= 0x34,
			TIMER_8_UPDATE								= 0x35,
			TIMER_8_TRIGGER								= 0x36,
			TIMER_8_COMMUTATION						= 0x37,
			TIMER_2_CH1										= 0x38,
			TIMER_2_CH2										= 0x39,
			TIMER_2_CH3										= 0x3A,
			TIMER_2_CH4										= 0x3B,
			TIMER_2_UPDATE								= 0x3C,
			TIMER_3_CH1										= 0x3D,
			TIMER_3_CH2										= 0x3E,
			TIMER_3_CH3										= 0x3F,
			TIMER_3_CH4										= 0x40,
			TIMER_3_UPDATE								= 0x41,
			TIMER_3_TRIGGER								= 0x42,
			TIMER_4_CH1										= 0x43,
			TIMER_4_CH2										= 0x44,
			TIMER_4_CH3										= 0x45,
			TIMER_4_CH4										= 0x46,
			TIMER_4_UPDATE								= 0x47,
			TIMER_5_CH1										= 0x48,
			TIMER_5_CH2										= 0x49,
			TIMER_5_CH3										= 0x4A,
			TIMER_5_CH4										= 0x4B,
			TIMER_5_UPDATE								= 0x4C,
			TIMER_5_TRIGGER								= 0x4D,
			TIMER_15_CH1									= 0x4E,
			TIMER_15_UPDATE								= 0x4F,
			TIMER_15_TRIGGER							= 0x50,
			TIMER_15_COMMUTATION					= 0x51,
			TIMER_16_CH1									= 0x52,
			TIMER_16_UPDATE								= 0x53,
			TIMER_17_CH1									= 0x54,
			TIMER_17_UPDATE								= 0x55,
			TIMER_20_CH1									= 0x56,
			TIMER_20_CH2									= 0x57,
			TIMER_20_CH3									= 0x58,
			TIMER_20_CH4									= 0x59,
			TIMER_20_UPDATE								= 0x5A,
			AES_IN												= 0x5B,
			AES_OUT												= 0x5C,
			TIMER_20_TRIGGER							= 0x5D,
			TIMER_20_COMMUTATION					= 0x5E,
			HRTIMER_MASTER								= 0x5F,
			HRTIMER_A											= 0x60,
			HRTIMER_B											= 0x61,
			HRTIMER_C											= 0x62,
			HRTIMER_D											= 0x63,
			HRTIMER_E											= 0x64,
			HRTIMER_F											= 0x65,
			DAC_3_CH1											= 0x66,
			DAC_3_CH2											= 0x67,
			DAC_4_CH1											= 0x68,
			DAC_4_CH2											= 0x69,
			SPI_4_RX											= 0x6A,
			SPI_4_TX											= 0x6B,
			SAI_1_A												= 0x6C,
			SAI_1_B												= 0x6D,
			FMAC_READ											= 0x6E,
			FMAC_WRITE										= 0x6F,
			CORDIC_READ										= 0x70,
			CORDIC_WRITE									= 0x71,
			UCPD_RX												= 0x72,
			UCPD_TX												= 0x73
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
			DMA_2_CH7	= 0x0F
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline DMAMUX();
		DMAMUX(const DMAMUX& dmamux) = delete;
		inline ~DMAMUX();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32G474MCT6;
		
		
		
		
		
	public:
		
		
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







inline feedback DMAMUX::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

