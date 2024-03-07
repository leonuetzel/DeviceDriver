#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"
#include "nvic.hpp"





class MDMA
{
	public:
		
		
		
		
		
		
		
	private:
		
		constexpr inline MDMA();
		MDMA(const MDMA& mdma) = delete;
		inline ~MDMA();
		
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup(RCC& rcc);
		
		feedback copy(uint8 channel, uint8* source,	uint8* destination,		uint16 sizeInBytes);
		feedback copy(uint8 channel, uint16* source,	uint16* destination,	uint16 sizeInBytes);
		feedback copy(uint8 channel, uint32* source,	uint32* destination,	uint16 sizeInBytes);
		
		feedback fill(uint8 channel, uint8 data,		uint8* destination,		uint16 sizeInBytes);
		feedback fill(uint8 channel, uint16 data,	uint16* destination,	uint16 sizeInBytes);
		feedback fill(uint8 channel, uint32 data,	uint32* destination,	uint16 sizeInBytes);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline MDMA::MDMA()
{
	
}


inline MDMA::~MDMA()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

