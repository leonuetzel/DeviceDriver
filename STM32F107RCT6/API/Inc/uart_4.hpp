#pragma once

#include "cmos.hpp"





class UART_4 : public UART
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		I_DMA* m_dma_rx;
		
		
		//	Constructor and Destructor
		inline UART_4();
		UART_4(const UART_4& uart_4) = delete;
		inline ~UART_4();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend void ISR_UART_4();
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		feedback init(uint32 baud, e_databits databits, e_stopbits stopbits, e_parity parity, uint8* rxBuffer, uint32 rxBufferSize, uint8* txBuffer, uint32 txBufferSize) override;
		feedback deinit() override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline UART_4::UART_4()
	:	UART((void*) MCU::UART_4::DR),
		m_dma_rx(nullptr)
{
	
}


inline UART_4::~UART_4()
{
	deinit();
}







inline feedback UART_4::startup()
{
	//	Create Semaphore
	return(CMOS::get().semaphore_create(this));
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

