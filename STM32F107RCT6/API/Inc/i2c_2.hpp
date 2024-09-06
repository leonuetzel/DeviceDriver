#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class I2C_2
{
	public:
		
		enum class e_mode
		{
			STANDARD_100KHZ,
			FAST_400KHZ
		};
		
		enum class e_error
		{
			ACKNOWLEDGE_FAILURE,
			ARBITRATION_LOST,
			BUS_ERROR
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		const uint8 m_eventID_TxE;
		const uint8 m_eventID_RxNE;
		const uint8 m_eventID_error;
		
		UniqueArray<e_error> m_errors;
		
		
		//	Constructor and Destructor
		inline I2C_2();
		I2C_2(const I2C_2& i2c_2) = delete;
		inline ~I2C_2();
		
		
		//	Member Functions
		inline feedback startup();
		
		feedback start(uint8 slaveAddress, uint32 timeout_ms, bool clearADDR = true);
		inline void stop();
		
		
		//	Friends
		friend void ISR_I2C_2_EVENT();
		friend void ISR_I2C_2_ERROR();
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		feedback init(e_mode mode);
		
		feedback tx(uint8 slaveAddress, uint8 data, uint32 timeout_ms = 100);
		feedback tx(uint8 slaveAddress, const Array<uint8>& data, uint32 timeout_ms = 100);
		Array<uint8> rx(uint8 slaveAddress, uint32 numberOfByte, uint32 timeout_ms = 100);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline I2C_2::I2C_2()
	:	m_eventID_TxE(CMOS::get().event_create()),
		m_eventID_RxNE(CMOS::get().event_create()),
		m_eventID_error(CMOS::get().event_create())
{
	
}


inline I2C_2::~I2C_2()
{
	
}







inline feedback I2C_2::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

