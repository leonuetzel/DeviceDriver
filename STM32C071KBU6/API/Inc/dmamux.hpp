#pragma once

#include "registers.hpp"
#include "cmos.hpp"





class DMAMUX
{
	public:
		
		enum class e_input: uint8
		{
			DMAMUX_1_REQUEST_GENERATOR_0	= 0x01,
			DMAMUX_1_REQUEST_GENERATOR_1	= 0x02,
			DMAMUX_1_REQUEST_GENERATOR_2	= 0x03,
			DMAMUX_1_REQUEST_GENERATOR_3	= 0x04,
			ADC_DMA												= 0x05,
			I2C_1_RX_DMA									= 0x0A,
			I2C_1_TX_DMA									= 0x0B,
			SPI_1_RX_DMA									= 0x10,
			SPI_1_TX_DMA									= 0x11,
			TIMER_1_CH1										= 0x14,
			TIMER_1_CH2										= 0x15,
			TIMER_1_CH3										= 0x16,
			TIMER_1_CH4										= 0x17,
			TIMER_1_TRIGGER_COMMUTATION		= 0x18,
			TIMER_1_UPDATE								= 0x19,
			TIMER_3_CH1										= 0x20,
			TIMER_3_CH2										= 0x21,
			TIMER_3_CH3										= 0x22,
			TIMER_3_CH4										= 0x23,
			TIMER_3_TRIGGER								= 0x24,
			TIMER_3_UPDATE								= 0x25,
			TIMER_16_CH1									= 0x2C,
			TIMER_16_TRIGGER_COMMUTATION	= 0x2D,
			TIMER_16_UPDATE								= 0x2E,
			TIMER_17_CH1									= 0x2F,
			TIMER_17_TRIGGER_COMMUTATION	= 0x30,
			TIMER_17_UPDATE								= 0x31,
			USART_1_RX_DMA								= 0x32,
			USART_1_TX_DMA								= 0x33,
			USART_2_RX_DMA								= 0x34,
			USART_2_TX_DMA								= 0x35
		};
		
		enum class e_output
		{
			DMA_CH0	= 0x00,
			DMA_CH1	= 0x01,
			DMA_CH2	= 0x02
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline DMAMUX();
		DMAMUX(const DMAMUX& dmamux) = delete;
		inline ~DMAMUX();
		
		
		//	Member Functions
		constexpr inline feedback startup();
		
		
		//	Friends
		friend class STM32C071KBU6;
		
		
		
		
		
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







constexpr inline feedback DMAMUX::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

