#pragma once

#include "cmos.hpp"





class HSEM	:	public I_Semaphore
{
	public:
		
		static constexpr uint8 c_number = 32;
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		uint32 m_number;
		
		
		//	Constructor and Destructor
		constexpr inline HSEM();
		HSEM(const HSEM& hsem) = delete;
		inline ~HSEM();
		
		
		//	Member Functions
		feedback startup(uint8 number);
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		virtual feedback lock()					override;
		virtual feedback unlock()				override;
		virtual feedback force_unlock()	override;
		virtual uint8 get_owner() const	override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline HSEM::HSEM()
	:	m_number(c_number)
{
	
}


inline HSEM::~HSEM()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

