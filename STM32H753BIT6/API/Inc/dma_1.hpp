#pragma once

#include "cmos.hpp"
#include "rcc.hpp"





class DMA_1: public I_DMA
{
	public:
		
		static constexpr uint8 c_channel = 8;
		
		
		
		
		
	private:
		
		//	Static Member
		static Triplet<uint16, f_callback, bool> m_channelInfo[c_channel];
		
		
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
		friend void ISR_DMA_1_CH7();
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback reset() override;
		feedback transfer(const void* source, const void* destination, e_dataType sourceType, e_dataType destinationType, bool source_inc, bool dest_inc, e_direction direction, bool circularMode, uint16 numberOfItems, e_priority priority = e_priority::LOW, bool waitForTransferEnd = true, f_callback callback = nullptr) override;
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
	//	Check Channel Boundaries
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
	
	
	//	Create Event
	auto& channelInfo = m_channelInfo[m_channel];
	channelInfo.first() = cmos.event_create();
	
	
	//	Init Interrupts only once
	if(channel == 0)
	{
		NVIC& nvic = cmos.get_nvic();
		nvic.setPriority(Interrupt::DMA_1_CH0, 10);
		nvic.setPriority(Interrupt::DMA_1_CH1, 10);
		nvic.setPriority(Interrupt::DMA_1_CH2, 10);
		nvic.setPriority(Interrupt::DMA_1_CH3, 10);
		nvic.setPriority(Interrupt::DMA_1_CH4, 10);
		nvic.setPriority(Interrupt::DMA_1_CH5, 10);
		nvic.setPriority(Interrupt::DMA_1_CH6, 10);
		nvic.setPriority(Interrupt::DMA_1_CH7, 10);
		
		nvic.enable(Interrupt::DMA_1_CH0);
		nvic.enable(Interrupt::DMA_1_CH1);
		nvic.enable(Interrupt::DMA_1_CH2);
		nvic.enable(Interrupt::DMA_1_CH3);
		nvic.enable(Interrupt::DMA_1_CH4);
		nvic.enable(Interrupt::DMA_1_CH5);
		nvic.enable(Interrupt::DMA_1_CH6);
		nvic.enable(Interrupt::DMA_1_CH7);
		
		
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

