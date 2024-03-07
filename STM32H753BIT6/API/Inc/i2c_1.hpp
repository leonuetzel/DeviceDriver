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
		feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback init();
		
		feedback start(uint8 slaveAddress, bool write, uint8 numberOfBytes) override;
		void stop() override;
		feedback tx(uint8 data) override;
		uint8 rx() override;
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



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

