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
		
		
		
		//	Constructor and Destructor
		constexpr inline I2C_2();
		I2C_2(const I2C_2& i2c_2) = delete;
		inline ~I2C_2();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback init();
		
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

constexpr inline I2C_2::I2C_2()
{
	
}


inline I2C_2::~I2C_2()
{
	
}







inline feedback I2C_2::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::I2C_2, true);
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

