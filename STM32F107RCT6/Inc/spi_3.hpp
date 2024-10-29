#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class SPI_3: public I_SPI
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline SPI_3();
		SPI_3(const SPI_3& spi_3) = delete;
		inline ~SPI_3();
		
		
		//	Member Functions
		inline feedback startup();
		
		
		//	Friends
		friend class STM32F107RCT6;
		
		
		
		
		
	public:
		
		feedback init(uint32 frequency, bool cpol, bool cpha);
		
		uint8 operator()(uint8 data) override;
		Array<uint8> operator()(const Array<uint8>& data) override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline SPI_3::SPI_3()
{
	
}


inline SPI_3::~SPI_3()
{
	
}







inline feedback SPI_3::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

