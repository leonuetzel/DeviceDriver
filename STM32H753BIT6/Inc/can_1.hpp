#pragma once

#include "cmos.hpp"





class CAN_1: public I_CAN
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		static CAN_1* m_this;
		
		
		//	Non-static Member
		const uint16 m_eventID_frameReadyToRead;
		UniqueArray<e_error> m_errors;
		e_state m_state;
		uint32 m_baudRate;
		
		
		//	Constructor and Destructor
		inline CAN_1();
		CAN_1(const CAN_1& can_1) = delete;
		inline ~CAN_1();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32H753BIT6;
		friend void ISR_FDCAN_1_INT0();
		
		
		
		
		
	public:
		
		feedback init(uint32 baudRate);
		
		feedback tx(const CAN_Frame& canFrame) override;
		feedback rx(CAN_Frame& canFrame) override;
		
		uint32 get_numberOfUnread() const override;
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

inline CAN_1::CAN_1()
	:	m_eventID_frameReadyToRead(CMOS::get().event_create()),
		m_errors(),
		m_state(e_state::ERROR_ACTIVE),
		m_baudRate(0)
{
	m_this = this;
}


inline CAN_1::~CAN_1()
{
	
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

