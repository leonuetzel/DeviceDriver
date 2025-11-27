#pragma once

#include "cmos.hpp"





class CAN_2: public I_CAN
{
	public:
		
		static constexpr uint32 numberOfStandardFilterElements = 28;
		static constexpr uint32 numberOfExtendedFilterElements =  8;
		
		
		
		
		
	private:
		
		//	Static Member
		static CAN_2* m_this;
		
		
		//	Non-static Member
		const uint16 m_eventID_frameReadyToRead;
		UniqueArray<e_error> m_errors;
		e_state m_state;
		uint32 m_baudRate;
		Array<s_filterElement> m_standardFilterElements;
		Array<s_filterElement> m_extendedFilterElements;
		
		
		//	Constructor and Destructor
		inline CAN_2();
		CAN_2(const CAN_2& can_2) = delete;
		inline ~CAN_2();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32G474MCT6;
		friend void ISR_FDCAN_2_IT0();
		friend void ISR_FDCAN_2_IT1();
		
		
		
		
		
	public:
		
		feedback init(uint32 baudRate, const Array<s_filterElement>& standardfilterElements, const Array<s_filterElement>& extendedfilterElements);
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

