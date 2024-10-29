#pragma once

#include "cmos.hpp"
#include "rcc.hpp"





class DMA_2 : public I_DMA
{
	public:
		
		static constexpr uint32 c_channel = 5;
		
		
		
		
		
	private:
		
		//	Static Member
		static Pair<uint16, f_callback> m_channelInfo[c_channel];
		
		
		//	Non-static Member
		uint8 m_channel;
		
		
		//	Constructor and Destructor
		constexpr inline DMA_2();
		DMA_2(const DMA_2& dma_2) = delete;
		inline ~DMA_2();
		
		
		//	Member Functions
		static void executeCallback(uint8 channel);
		inline feedback startup(RCC& rcc, uint8 channel);
		
		
		//	Friends
		friend void ISR_DMA2_CH0();
		friend void ISR_DMA2_CH1();
		friend void ISR_DMA2_CH2();
		friend void ISR_DMA2_CH3();
		friend void ISR_DMA2_CH4();
		friend class STM32F107RCT6;
		
		
		
		
		
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

constexpr inline DMA_2::DMA_2()
	:	m_channel(c_channel)
{
	
}


inline DMA_2::~DMA_2()
{
	
}







inline feedback DMA_2::startup(RCC& rcc, uint8 channel)
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
	
	
	//	Init Interrupts and Events only once
	if(channel == 0)
	{
		for(auto& i: m_channelInfo)
		{
			i.first() = cmos.event_create();
		}
		
		
		NVIC& nvic = cmos.get_nvic();
		nvic.setPriority(Interrupt::DMA2_CH0, 10);
		nvic.setPriority(Interrupt::DMA2_CH1, 10);
		nvic.setPriority(Interrupt::DMA2_CH2, 10);
		nvic.setPriority(Interrupt::DMA2_CH3, 10);
		nvic.setPriority(Interrupt::DMA2_CH4, 10);
		
		nvic.enable(Interrupt::DMA2_CH0);
		nvic.enable(Interrupt::DMA2_CH1);
		nvic.enable(Interrupt::DMA2_CH2);
		nvic.enable(Interrupt::DMA2_CH3);
		nvic.enable(Interrupt::DMA2_CH4);
		
		
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

