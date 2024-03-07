#pragma once

#include "cmos.hpp"





class CAN_1: public I_CAN
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		static CAN_1* m_this;
		
		
		//	Non-static Member
		RingbufferDynamic<CAN_Frame*>* m_rxBuffer;
		RingbufferDynamic<CAN_Frame*>* m_txBuffer;
		UniqueArray<e_error> m_errors;
		e_state m_state;
		uint32 m_baudRate;
		
		
		//	Constructor and Destructor
		constexpr inline CAN_1();
		CAN_1(const CAN_1& can_1) = delete;
		inline ~CAN_1();
		
		
		//	Member Functions
		inline feedback startup();
		
		feedback writeToTxMailbox(const CAN_Frame& packet);
		
		
		//	Friends
		friend class STM32F107RCT6;
		friend void ISR_CAN1_TX();
		friend void ISR_CAN1_RX_0();
		friend void ISR_CAN1_RX_1();
		friend void ISR_CAN1_SCE();
		
		
		
		
		
	public:
		
		feedback init(uint32 baudRate, uint32 rxBufferSize = 32, uint32 txBufferSize = 32);
		
		I_CAN& operator<<(const CAN_Frame& packet) override;
		I_CAN& operator>>(CAN_Frame*& packet) override;
		
		uint32 get_numberOfUnread() const override;
		bool is_dataAvailable() const override;
		
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

constexpr inline CAN_1::CAN_1()
	:	m_rxBuffer(nullptr),
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
		//	Free Memory of all Packets in Buffer
		const uint32 numberOfPackets = m_rxBuffer->get_numberOfUnread();
		for(uint32 i = 0; i < numberOfPackets; i++)
		{
			delete m_rxBuffer->read();
		}
		
		
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
		//	Free Memory of all Packets in Buffer
		const uint32 numberOfPackets = m_txBuffer->get_numberOfUnread();
		for(uint32 i = 0; i < numberOfPackets; i++)
		{
			delete m_txBuffer->read();
		}
		
		
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

