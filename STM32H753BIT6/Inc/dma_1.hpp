#pragma once

#include "cmos.hpp"





class DMA_1: public I_DMA
{
	public:
		
		static constexpr uint8 c_channel = 8;
		
		
		
		
		
	private:
		
		//	Static Member
		static Triplet<uint16, f_callback, bool> m_channelInfo[c_channel];
		
		//	Memory written by the Channel, invalidated in the Data Cache when a Transfer has ended (see cacheMaintenance.hpp)
		static Pair<const void*, uint32> m_writtenMemory[c_channel];
		
		//	A Transfer has ended with a Transfer Error (TEIF), noted by the Interrupt Routine
		static volatile bool m_transferError[c_channel];
		
		//	ES0392 2.20.4 applies (all Revisions but Y), read once by startup(): Transfers with an USART use the alternative Protocol
		static bool m_usartWorkaround;
		
		//	TEIF of the Streams 0 ... 3 (4 ... 7) in DMA_LISR (DMA_HISR): Bits 3, 9, 19 and 25 (RM0433)
		static constexpr uint32 c_transferErrorFlags = 0x02080208;
		
		
		//	Non-static Member
		uint8 m_channel;
		
		
		//	Constructor and Destructor
		constexpr inline DMA_1();
		DMA_1(const DMA_1& dma_1);
		inline ~DMA_1();
		
		
		//	Member Functions
		feedback startup(uint8 channel);
		static void executeCallback(uint8 channel, bool transferError);
		
		
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
		bool is_busy() const override;
		uint16 get_eventID() const override;
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



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

