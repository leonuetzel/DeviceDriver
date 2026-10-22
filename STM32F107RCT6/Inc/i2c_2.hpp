#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class I2C_2: public I_I2C
{
	public:
	
	
	
	
	
	
	
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		e_mode m_mode;
		uint8 m_remaining;						//	Bytes of the running Transfer, that tx() or rx() still have to transfer
		bool m_read;
		bool m_autoEnd;
		bool m_active;								//	A Transfer has been started and no Stop Condition requested yet
		bool m_pendingValid;
		uint8 m_pending;							//	Received Byte that the End of a Reception had to read early (ES022 2.8.2)
		
		
		//	Constructor and Destructor
		constexpr inline I2C_2();
		I2C_2(const I2C_2& i2c_2) = delete;
		inline ~I2C_2();
		
		
		//	Member Functions
		inline feedback startup();
		feedback begin(uint8 slaveAddress, bool write, uint8 numberOfBytes, bool autoEnd, uint32 timeout_ms);
		feedback wait(uint32 bitNumber, uint64 timestampStart, uint32 timeout_ms);
		void end();
		
		
		//	Friends
		friend class STM32F107RCT6;
	
	
	
	
	
	public:
		
		feedback init(e_mode mode = e_mode::FAST_400KHZ);
		
		feedback start(uint8 slaveAddress, bool write, uint8 numberOfBytes = 0, uint32 timeout_ms = 100) override;
		feedback start_withoutStop(uint8 slaveAddress, bool write, uint8 numberOfBytes, uint32 timeout_ms = 100) override;
		void stop() override;
		feedback tx(uint8 data, uint32 timeout_ms = 100) override;
		uint8 rx(uint32 timeout_ms = 100) override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline I2C_2::I2C_2()
	:	m_mode(e_mode::FAST_400KHZ),
		m_remaining(0),
		m_read(false),
		m_autoEnd(true),
		m_active(false),
		m_pendingValid(false),
		m_pending(0)
{
	
}


inline I2C_2::~I2C_2()
{
	
}







inline feedback I2C_2::startup()
{
	//	Mutex of the Bus: only the Thread that has locked it with cmos.mutex_lock(&i2c) may transfer
	return(CMOS::get().mutex_create(this));
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

