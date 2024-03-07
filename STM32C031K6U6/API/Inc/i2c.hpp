#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class I2C: public I_I2C
{
	public:
		
		enum class e_mode
		{
			STANDARD_100kHz					= 0,
			FAST_MODE_400kHz				= 1,
			FAST_MODE_PLUS_1000kHz	= 2
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline I2C();
		I2C(const I2C& i2c) = delete;
		inline ~I2C();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32C031K6U6;
		
		
		
		
		
	public:
		
		feedback init(RCC::e_clockSource_i2c clockSource = RCC::e_clockSource_i2c::SYSTEM, e_mode mode = e_mode::FAST_MODE_400kHz, bool analogFilterEnable = true, uint8 digitalFilterLength = 0);
		
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

constexpr inline I2C::I2C()
{
	
}


inline I2C::~I2C()
{
	
}







inline feedback I2C::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::I2C, true);
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

