#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class BackupSRAM
{
	public:
		
		
		
		
		
	private:
		
		RCC& m_rcc;
		
		constexpr inline BackupSRAM(RCC& rcc);
		BackupSRAM(const BackupSRAM& backupSRAM) = delete;
		inline ~BackupSRAM();
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup();
		
		void writeProtection(bool enable);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline BackupSRAM::BackupSRAM(RCC& rcc)
	: m_rcc(rcc)
{
	
}


inline BackupSRAM::~BackupSRAM()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

