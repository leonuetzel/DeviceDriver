#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"





class CRC: public I_CRC
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline CRC();
		CRC(const CRC& crc) = delete;
		inline ~CRC();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		
		
		//	Friends
		friend class STM32C031K6U6;
		
		
		
		
		
	public:
		
		feedback init(uint8 initialValue, uint8 polynomial, bool reverseOutputData = false, bool reverseInputData = false) override;
		feedback init(uint16 initialValue, uint16 polynomial, bool reverseOutputData = false, bool reverseInputData = false) override;
		feedback init(uint32 initialValue, uint32 polynomial, bool reverseOutputData = false, bool reverseInputData = false) override;
		
		CRC& operator<<(uint8 data) override;
		CRC& operator<<(uint16 data) override;
		CRC& operator<<(uint32 data) override;
		
		uint32 operator()() const override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline CRC::CRC()
{
	
}


inline CRC::~CRC()
{
	
}







inline feedback CRC::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::CRC, true);
	
	
	//	Create Semaphore
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_create(this) != OK)
	{
		return(FAIL);
	}
	
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

