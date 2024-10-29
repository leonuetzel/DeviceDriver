#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class I2C_1
{
	public:
		
		enum class e_mode
		{
			STANDARD_100KHZ,
			FAST_400KHZ
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline I2C_1();
		I2C_1(const I2C_1& i2c_1) = delete;
		inline ~I2C_1();
		
		
		//	Member Functions
		inline feedback startup();
		
		feedback start(uint8 slaveAddress, uint32 timeout_ms, bool clearADDR = true);
		inline void stop();
		
		
		//	Friends
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

constexpr inline I2C_1::I2C_1()
{
	
}


inline I2C_1::~I2C_1()
{
	
}







inline feedback I2C_1::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

