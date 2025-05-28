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
		UniqueArray<e_error> m_errors;
		e_state m_state;
		uint32 m_baudRate;
		
		
		//	Constructor and Destructor
		inline CAN_2();
		CAN_2(const CAN_2& can_2) = delete;
		inline ~CAN_2();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32H753BIT6;
		friend void ISR_FDCAN_2_INT0();
		
		
		
		
		
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

inline CAN_2::CAN_2()
	:	m_eventID_frameReadyToRead(CMOS::get().event_create()),
		m_errors(),
		m_state(e_state::ERROR_ACTIVE),
		m_baudRate(0)
{
	m_this = this;
}


inline CAN_2::~CAN_2()
{
	
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

