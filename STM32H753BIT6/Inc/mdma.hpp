#pragma once

#include "cmos.hpp"





class MDMA
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline MDMA();
		MDMA(const MDMA& mdma) = delete;
		inline ~MDMA();
		
		
		//	Member Functions
		feedback startup();
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		//	The Transfers run on their own, the Functions return right after the Start
		//	With the Data Cache on, call CacheMaintenance::afterWrite(destination, sizeInBytes) when the Transfer has ended, before the CPU reads the Destination
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

