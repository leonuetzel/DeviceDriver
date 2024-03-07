#pragma once

#include "cmos.hpp"

#include "rcc.hpp"





class DMA : public I_DMA
{
	public:
		
		static constexpr uint32 c_channel = 7;
		
		enum class e_requestMapping : uint8
		{
			CH0_ADC									= 0x00,
			CH0_TIMER2CH3						= 0x08,
			
			CH1_ADC									= 0x10,
			CH1_SPI1RX							= 0x11,
			CH1_LPUART1TX						= 0x15,
			CH1_I2C1TX							= 0x16,
			CH1_TIMER2UP						= 0x18,
			
			CH2_SPI1TX							= 0x21,
			CH2_LPUART1RX						= 0x25,
			CH2_I2C1RX							= 0x26,
			CH2_TIMER2CH2						= 0x28,
			
			CH3_USART2TX						= 0x34,
			CH3_TIMER2CH4						= 0x38,
			
			CH4_USART2RX						= 0x44,
			CH4_TIMER2CH1						= 0x48,
			
			CH5_USART2RX						= 0x54,
			CH5_LPUART1RX						= 0x55,
			CH5_I2C1TX							= 0x56,
			
			CH6_USART2TX						= 0x64,
			CH6_LPUART1TX						= 0x65,
			CH6_I2C1RX							= 0x66,
			CH6_TIMER2CH2_TIMER2CH4	= 0x68
		};
		
		
		
		
		
	private:
		
		//	Static Member
		static Triplet<uint16, uint8, f_callback> m_channelInfo[c_channel];
		
		
		//	Non-static Member
		uint8 m_channel;
		
		
		
		//	Constructor and Destructor
		constexpr inline DMA();
		DMA(const DMA& dma);
		inline ~DMA();
		
		
		//	Member Functions
		static void executeCallback(uint8 channel);
		inline feedback startup(RCC& rcc, uint8 channel);
		
		
		//	Friends
		friend void ISR_DMA_CH0();
		friend void ISR_DMA_CH1_CH2();
		friend void ISR_DMA_CH3_TO_CH6();
		friend class STM32L010RBT6;
		
		
		
		
		
	public:
		
		feedback reset() override;
		feedback transfer(const void* source, const void* destination, e_dataType sourceType, e_dataType destinationType, bool source_inc, bool dest_inc, e_direction direction, bool circularMode, uint16 numberOfItems, e_priority priority = e_priority::LOW, bool waitForTransferEnd = true, f_callback callback = nullptr) override;
		inline void set_requestMapping(e_requestMapping requestMapping);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline DMA::DMA()
	:	m_channel(c_channel)
{
	
}


inline DMA::~DMA()
{
	
}







inline feedback DMA::startup(RCC& rcc, uint8 channel)
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
		nvic.setPriority(Interrupt::DMA_CH0,				10);
		nvic.setPriority(Interrupt::DMA_CH1_CH2,		10);
		nvic.setPriority(Interrupt::DMA_CH3_TO_CH6,	10);
		
		nvic.enable(Interrupt::DMA_CH0);
		nvic.enable(Interrupt::DMA_CH1_CH2);
		nvic.enable(Interrupt::DMA_CH3_TO_CH6);
		
		
		
		rcc.module_clockInit(RCC::e_module::DMA, true);
	}
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void DMA::set_requestMapping(e_requestMapping requestMapping)
{
	uint8 channel = (((uint32) requestMapping) & 0x000000F0) >> 4;
	uint8 peripheral = ((uint32) requestMapping) & 0x0000000F;
	
	uint32 bitField_lowestBit = channel * 4;
	
	uint32 CSELR = *MCU::DMA::CSELR;
	bit::clear(CSELR, bitField_lowestBit, 4);
	*MCU::DMA::CSELR = CSELR | (peripheral << bitField_lowestBit);
}