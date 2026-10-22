#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class I2C_4: public I_I2C
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline I2C_4();
		I2C_4(const I2C_4& i2c_4) = delete;
		inline ~I2C_4();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		feedback begin(uint8 slaveAddress, bool write, uint8 numberOfBytes, bool autoEnd, uint32 timeout_ms);
		void reset();
		
		
		//	Friends
		friend class STM32G474MCT6;
		
		
		
		
		
	public:
		
		feedback init(e_mode mode = e_mode::FAST_400KHZ, RCC::e_clockSource_i2c_4 clockSource = RCC::e_clockSource_i2c_4::APB1, bool analogFilterEnable = true, uint8 digitalFilterLength = 0);
		
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

constexpr inline I2C_4::I2C_4()
{
	
}


inline I2C_4::~I2C_4()
{
	
}







inline feedback I2C_4::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::I2C_4, true);
	
	
	//	Mutex of the Bus: only the Thread that has locked it with cmos.mutex_lock(&i2c) may transfer
	return(CMOS::get().mutex_create(this));
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

