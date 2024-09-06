#pragma once

#include "cmos.hpp"

#include "rcc.hpp"





class DMA_1 : public I_DMA
{
	public:
		
		static constexpr uint32 c_channel = 7;
		
		enum class e_requestMapping : uint8
		{
			CH0_ADC1																												= 0x00,
			CH0_TIMER2CH3																										= 0x04,
			
			CH1_SPI1RX																											= 0x11,
			CH1_USART3TX																										= 0x12,
			CH1_I2C3TX																											= 0x13,
			CH1_TIMER2UPDATE																								= 0x14,
			CH1_TIMER3CH3																										= 0x15,
			CH1_TIMER1CH1																										= 0x17,
			
			CH2_SPI1TX																											= 0x21,
			CH2_USART3RX																										= 0x22,
			CH2_I2C3RX																											= 0x23,
			CH2_TIMER16CH1_TIMER16UPDATE																		= 0x24,
			CH2_TIMER3CH4_TIMER3UPDATE																			= 0x25,
			CH2_TIMER6UPDATE_DAC1CH1																				= 0x26,
			CH2_TIMER1CH2																										= 0x27,
			
			CH3_SPI2RX																											= 0x31,
			CH3_USART1TX																										= 0x32,
			CH3_I2C2TX																											= 0x33,
			CH3_TIMER1CH4_TIMER1TRIGGER_TIMER1COMMUTATION										= 0x37,
			
			CH4_DFSDM1FLT1																									= 0x40,
			CH4_SPI2TX																											= 0x41,
			CH4_USART1RX																										= 0x42,
			CH4_I2C2RX																											= 0x43,
			CH4_TIMER2CH1																										= 0x44,
			CH4_QUADSPI																											= 0x45,
			CH4_TIMER15CH1_TIMER15UPDATE_TIMER15TRIGGER_TIMER15COMMUTATION	= 0x47,
			
			CH5_DFSDM1FLT0																									= 0x50,
			CH5_SAI2A																												= 0x51,
			CH5_USART2RX																										= 0x52,
			CH5_I2C1TX																											= 0x53,
			CH5_TIMER16CH1_TIMER16UPDATE																		= 0x54,
			CH5_TIMER3CH1_TIMER3TRIGGER																			= 0x55,
			CH5_TIMER1UPDATE																								= 0x57,
			
			CH6_SAI2B																												= 0x61,
			CH6_USART2TX																										= 0x62,
			CH6_I2C1RX																											= 0x63,
			CH6_TIMER2CH2_TIMER2CH4																					= 0x64,
			CH6_TIMER3CH3																										= 0x67
		};
		
		
		
		
		
	private:
		
		//	Static Member
		static Pair<uint16, f_callback> m_channelInfo[c_channel];
		
		
		//	Non-static Member
		uint8 m_channel;
		
		
		
		//	Constructor and Destructor
		constexpr inline DMA_1();
		DMA_1(const DMA_1& dma_1);
		inline ~DMA_1();
		
		
		//	Member Functions
		static void executeCallback(uint8 channel);
		inline feedback startup(RCC& rcc, uint8 channel);
		
		
		//	Friends
		friend void ISR_DMA_1_CH0();
		friend void ISR_DMA_1_CH1();
		friend void ISR_DMA_1_CH2();
		friend void ISR_DMA_1_CH3();
		friend void ISR_DMA_1_CH4();
		friend void ISR_DMA_1_CH5();
		friend void ISR_DMA_1_CH6();
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

constexpr inline DMA_1::DMA_1()
	:	m_channel(c_channel)
{
	
}


inline DMA_1::~DMA_1()
{
	
}







inline feedback DMA_1::startup(RCC& rcc, uint8 channel)
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
		nvic.setPriority(Interrupt::DMA_1_CH0,	10);
		nvic.setPriority(Interrupt::DMA_1_CH1,	10);
		nvic.setPriority(Interrupt::DMA_1_CH2,	10);
		nvic.setPriority(Interrupt::DMA_1_CH3,	10);
		nvic.setPriority(Interrupt::DMA_1_CH4,	10);
		nvic.setPriority(Interrupt::DMA_1_CH5,	10);
		nvic.setPriority(Interrupt::DMA_1_CH6,	10);
		
		
		nvic.enable(Interrupt::DMA_1_CH0);
		nvic.enable(Interrupt::DMA_1_CH1);
		nvic.enable(Interrupt::DMA_1_CH2);
		nvic.enable(Interrupt::DMA_1_CH3);
		nvic.enable(Interrupt::DMA_1_CH4);
		nvic.enable(Interrupt::DMA_1_CH5);
		nvic.enable(Interrupt::DMA_1_CH6);
		
		
		rcc.module_clockInit(RCC::e_module::DMA_1, true);
	}
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void DMA_1::set_requestMapping(e_requestMapping requestMapping)
{
	uint8 channel = (((uint32) requestMapping) & 0x000000F0) >> 4;
	uint8 peripheral = ((uint32) requestMapping) & 0x0000000F;
	
	uint32 bitField_lowestBit = channel * 4;
	
	uint32 CSELR = *MCU::DMA_1::CSELR;
	bit::clear(CSELR, bitField_lowestBit, 4);
	*MCU::DMA_1::CSELR = CSELR | (peripheral << bitField_lowestBit);
}