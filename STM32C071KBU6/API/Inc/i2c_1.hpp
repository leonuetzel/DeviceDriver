#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class I2C_1: public I_I2C
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline I2C_1();
		I2C_1(const I2C_1& i2c_1) = delete;
		inline ~I2C_1();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32C071KBU6;
		
		
		
		
		
	public:
		
		feedback init(e_mode mode = e_mode::FAST_400KHZ, RCC::e_clockSource_i2c clockSource = RCC::e_clockSource_i2c::APB, bool analogFilterEnable = true, uint8 digitalFilterLength = 0);
		
		feedback start(uint8 slaveAddress, bool write, uint8 numberOfBytes = 0, uint32 timeout_ms = 100) override;
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

constexpr inline I2C_1::I2C_1()
{
	
}


inline I2C_1::~I2C_1()
{
	
}







inline feedback I2C_1::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::I2C_1, true);
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

