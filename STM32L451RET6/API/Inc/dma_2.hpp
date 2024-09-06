#pragma once

#include "cmos.hpp"

#include "rcc.hpp"





class DMA_2 : public I_DMA
{
	public:
		
		static constexpr uint32 c_channel = 7;
		
		enum class e_requestMapping : uint8
		{
			CH0_I2C4RX								= 0x00,
			CH0_SAI1A									= 0x01,
			CH0_SPI3RX								= 0x03,
			
			CH1_I2C4TX								= 0x10,
			CH1_SAI1B									= 0x11,
			CH1_SPI3TX								= 0x13,
			
			CH2_ADC1									= 0x20,
			CH2_UART4TX								= 0x22,
			CH2_SPI1RX								= 0x24,
			
			CH3_TIMER6UPDATE_DAC1CH1	= 0x33,
			CH3_SPI1TX								= 0x34,
			CH3_SDMMC1								= 0x37,
			
			CH4_UART4RX								= 0x42,
			CH4_SDMMC1								= 0x47,
			
			CH5_SAI1A									= 0x51,
			CH5_USART1TX							= 0x52,
			CH5_LPUART1TX							= 0x54,
			CH5_I2C1RX								= 0x55,
			
			CH6_SAI1B									= 0x61,
			CH6_USART1RX							= 0x62,
			CH6_QUADSPI								= 0x63,
			CH6_LPUART1RX							= 0x64,
			CH6_I2C1TX								= 0x65
		};
		
		
		
		
		
	private:
		
		//	Static Member
		static Pair<uint16, f_callback> m_channelInfo[c_channel];
		
		
		//	Non-static Member
		uint8 m_channel;
		
		
		
		//	Constructor and Destructor
		constexpr inline DMA_2();
		DMA_2(const DMA_2& dma_2);
		inline ~DMA_2();
		
		
		//	Member Functions
		static void executeCallback(uint8 channel);
		inline feedback startup(RCC& rcc, uint8 channel);
		
		
		//	Friends
		friend void ISR_DMA_2_CH0();
		friend void ISR_DMA_2_CH1();
		friend void ISR_DMA_2_CH2();
		friend void ISR_DMA_2_CH3();
		friend void ISR_DMA_2_CH4();
		friend void ISR_DMA_2_CH5();
		friend void ISR_DMA_2_CH6();
		friend class STM32L451RET6;
		
		
		
		
		
	public:
		
		feedback reset() override;
		feedback transfer(const void* source, const void* destination, e_dataType sourceType, e_dataType destinationType, bool source_inc, bool dest_inc, e_direction direction, bool circularMode, uint16 numberOfItems, e_priority priority = e_priority::LOW, bool waitForTransferEnd = true, f_callback callback = nullptr) override;
		static inline void set_requestMapping(e_requestMapping requestMapping);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline DMA_2::DMA_2()
	:	m_channel(c_channel)
{
	
}


inline DMA_2::~DMA_2()
{
	
}







inline feedback DMA_2::startup(RCC& rcc, uint8 channel)
{
	if(m_channel != c_channel || channel >= c_channel)
	{
		return(FAIL);
	}
	 
	m_channel = channel;
	
	
	//	Create Semaphore
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_create(this) != OK)
	{
		return(FAIL);
	}
	
	
	//	Init Interrupts only once
	if(channel == 0)
	{
		NVIC& nvic = CMOS::get().get_nvic();
		nvic.setPriority(Interrupt::DMA_2_CH0,	10);
		nvic.setPriority(Interrupt::DMA_2_CH1,	10);
		nvic.setPriority(Interrupt::DMA_2_CH2,	10);
		nvic.setPriority(Interrupt::DMA_2_CH3,	10);
		nvic.setPriority(Interrupt::DMA_2_CH4,	10);
		nvic.setPriority(Interrupt::DMA_2_CH5,	10);
		nvic.setPriority(Interrupt::DMA_2_CH6,	10);
		
		
		nvic.enable(Interrupt::DMA_2_CH0);
		nvic.enable(Interrupt::DMA_2_CH1);
		nvic.enable(Interrupt::DMA_2_CH2);
		nvic.enable(Interrupt::DMA_2_CH3);
		nvic.enable(Interrupt::DMA_2_CH4);
		nvic.enable(Interrupt::DMA_2_CH5);
		nvic.enable(Interrupt::DMA_2_CH6);
		
		
		rcc.module_clockInit(RCC::e_module::DMA_2, true);
	}
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void DMA_2::set_requestMapping(e_requestMapping requestMapping)
{
	uint8 channel = (((uint32) requestMapping) & 0x000000F0) >> 4;
	uint8 peripheral = ((uint32) requestMapping) & 0x0000000F;
	
	uint32 bitField_lowestBit = channel * 4;
	
	uint32 CSELR = *MCU::DMA_2::CSELR;
	bit::clear(CSELR, bitField_lowestBit, 4);
	*MCU::DMA_2::CSELR = CSELR | (peripheral << bitField_lowestBit);
}