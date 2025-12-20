#pragma once

#include "cmos.hpp"





class CAN_1: public I_CAN
{
	public:
		
		static constexpr uint32 numberOfStandardFilterElements = 14;
		static constexpr uint32 numberOfExtendedFilterElements = 14;
		
		
		
		
		
	private:
		
		//	Static Member
		static CAN_1* m_this;
		
		
		//	Non-static Member
		const uint16 m_eventID_frameReadyToRead;
		bool m_txISR_active;
		RingbufferDynamic<CAN_Frame>* m_rxBuffer;
		RingbufferDynamic<CAN_Frame>* m_txBuffer;
		UniquePairArray<e_error, bool> m_errors;
		e_state m_state;
		uint32 m_baudRate;
		Array<s_filterElement> m_standardFilterElements;
		Array<s_filterElement> m_extendedFilterElements;
		bool m_silentMode;
		
		
		//	Constructor and Destructor
		inline CAN_1();
		CAN_1(const CAN_1& can_1) = delete;
		inline ~CAN_1();
		
		
		//	Member Functions
		inline feedback startup();
		feedback extractFrame(CAN_Frame& canFrame, uint32 RI, uint32 RDT, uint32 RDL, uint32 RDH);
		
		feedback writeToTxMailbox(const CAN_Frame& canFrame);
		
		
		//	Friends
		friend class STM32L451RET6;
		friend void ISR_CAN_1_TX();
		friend void ISR_CAN_1_RX0();
		friend void ISR_CAN_1_RX1();
		friend void ISR_CAN_1_SCE();
		
		
		
		
		
	public:
		
		feedback init(uint32 baudRate, const Array<s_filterElement>& standardfilterElements, const Array<s_filterElement>& extendedfilterElements, bool silentMode, uint32 rxBufferSize = 32, uint32 txBufferSize = 32);
		feedback stop() override;
		
		feedback tx(const CAN_Frame& canFrame) override;
		feedback rx(CAN_Frame& canFrame, uint32 fifoID = 0) override;
		
		uint32 get_numberOfUnread(uint32 fifoID = 0) const override;
		bool is_dataAvailable() const override;
		
		uint16 get_eventID() override;
		I_CAN::e_state get_state() override;
		const UniquePairArray<e_error, bool>& get_errors() const override;
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

inline CAN_1::CAN_1()
	:	m_eventID_frameReadyToRead(CMOS::get().event_create()),
		m_rxBuffer(nullptr),
		m_txBuffer(nullptr),
		m_errors(),
		m_state(e_state::ERROR_ACTIVE),
		m_baudRate(0)
{
	m_this = this;
}


inline CAN_1::~CAN_1()
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







inline feedback CAN_1::startup()
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

