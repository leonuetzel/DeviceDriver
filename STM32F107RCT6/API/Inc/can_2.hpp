#pragma once

#include "cmos.hpp"





class CAN_2: public I_CAN
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		static CAN_2* m_this;
		
		
		//	Non-static Member
		const uint16 m_eventID_frameReadyToRead;
		RingbufferDynamic<CAN_Frame>* m_rxBuffer;
		RingbufferDynamic<CAN_Frame>* m_txBuffer;
		UniqueArray<e_error> m_errors;
		e_state m_state;
		uint32 m_baudRate;
		
		
		//	Constructor and Destructor
		inline CAN_2();
		CAN_2(const CAN_2& can_2) = delete;
		inline ~CAN_2();
		
		
		//	Member Functions
		inline feedback startup();
		feedback extractFrame(CAN_Frame& canFrame, uint32 RI, uint32 RDT, uint32 RDL, uint32 RDH);
		
		feedback writeToTxMailbox(const CAN_Frame& canFrame);
		
		
		//	Friends
		friend class STM32F107RCT6;
		friend void ISR_CAN2_TX();
		friend void ISR_CAN2_RX_0();
		friend void ISR_CAN2_RX_1();
		friend void ISR_CAN2_SCE();
		
		
		
		
		
	public:
		
		feedback init(uint32 baudRate, uint32 rxBufferSize = 32, uint32 txBufferSize = 32);
		feedback stop() override;
		
		feedback tx(const CAN_Frame& canFrame) override;
		feedback rx(CAN_Frame& canFrame, uint32 fifoID = 0) override;
		
		uint32 get_numberOfUnread(uint32 fifoID = 0) const override;
		bool is_dataAvailable() const override;
		
		uint16 get_eventID() override;
		I_CAN::e_state get_state() override;
		const UniqueArray<e_error>& get_errors() const override;
		void clearErrors() override;
		
		uint32 get_baudRate() const override;
		
		feedback recoverFromBusOffState() override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline CAN_2::CAN_2()
	:	m_eventID_frameReadyToRead(CMOS::get().event_create()),
		m_rxBuffer(nullptr),
		m_txBuffer(nullptr),
		m_errors(),
		m_state(e_state::ERROR_ACTIVE),
		m_baudRate(0)
{
	m_this = this;
}


inline CAN_2::~CAN_2()
{
	CMOS& cmos = CMOS::get();
	
	
	//	Rx Buffer
	if(m_rxBuffer != nullptr)
	{
		//	Free Memory of the Buffer itself
		delete m_rxBuffer;
		
		
		//	Delete the corresponding Semaphore (needs to be locked by this Thread to erase)
		cmos.semaphore_lock(m_rxBuffer);
		cmos.semaphore_erase(m_rxBuffer);
	}
	m_rxBuffer = nullptr;
	
	
	//	Tx Buffer
	if(m_txBuffer != nullptr)
	{
		//	Free Memory of the Buffer itself
		delete m_txBuffer;
		
		
		//	Delete the corresponding Semaphore (needs to be locked by this Thread to erase)
		cmos.semaphore_lock(m_txBuffer);
		cmos.semaphore_erase(m_txBuffer);
	}
	m_txBuffer = nullptr;
}







inline feedback CAN_2::startup()
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

