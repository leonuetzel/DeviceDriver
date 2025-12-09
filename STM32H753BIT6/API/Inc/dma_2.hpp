#pragma once

#include "cmos.hpp"





class DMA_2: public I_DMA
{
	public:
		
		static constexpr uint8 c_channel = 8;
		
		
		
		
		
	private:
		
		//	Static Member
		static Triplet<uint16, f_callback, bool> m_channelInfo[c_channel];
		
		
		//	Non-static Member
		uint8 m_channel;
		
		
		//	Constructor and Destructor
		constexpr inline DMA_2();
		DMA_2(const DMA_2& dma_2);
		inline ~DMA_2();
		
		
		//	Member Functions
		feedback startup(uint8 channel);
		static void executeCallback(uint8 channel);
		
		
		//	Friends
		friend void ISR_DMA_2_CH0();
		friend void ISR_DMA_2_CH1();
		friend void ISR_DMA_2_CH2();
		friend void ISR_DMA_2_CH3();
		friend void ISR_DMA_2_CH4();
		friend void ISR_DMA_2_CH5();
		friend void ISR_DMA_2_CH6();
		friend void ISR_DMA_2_CH7();
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

constexpr inline DMA_2::DMA_2()
	:	m_channel(c_channel)
{
	
}


inline DMA_2::~DMA_2()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

