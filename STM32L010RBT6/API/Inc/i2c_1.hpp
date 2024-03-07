#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class I2C_1
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
		friend class STM32L010RBT6;
		
		
		
		
		
	public:
		
		feedback init();
		
		feedback start(uint8 slaveAddress, bool write, uint8 numberOfBytes);
		void stop();
		feedback tx(uint8 data);
		uint8 rx();
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

