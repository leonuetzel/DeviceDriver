#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "i_semaphore.hpp"
#include "rcc.hpp"




class HSEM	:	public I_Semaphore
{
	public:
		
		static constexpr uint8 c_number = 32;
		
		
		
		
		
	private:
		
		uint32 m_number;
		
		constexpr inline HSEM();
		HSEM(const HSEM& hsem) = delete;
		inline ~HSEM();
		
		friend void ISR_HSEM();
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup(RCC& rcc, uint8 number);
		
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

