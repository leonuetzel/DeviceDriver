#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"





class FMC
{
	public:
		
		enum class e_SDRAM_bank
		{
			BANK_1	= 0x0,
			BANK_2	= 0x1
		};
		
		enum class e_readPipeDelay
		{
			_0	= 0x0,
			_1	= 0x1,
			_2	= 0x2,
		};
		
		enum class e_clockDivision
		{
			NO_CLOCK	= 0x0,
			DIV_2			= 0x2,
			DIV_3			= 0x3
		};
		
		enum class e_CAS_Latency
		{
			_1	= 0x1,
			_2	= 0x2,
			_3	= 0x3
		};
		
		enum class e_numberOfInternalBanks
		{
			_2	= 0x0,
			_4	= 0x1
		};
		
		enum class e_dataBusWidth
		{
			_8_BIT	= 0x0,
			_16_BIT	= 0x1,
			_32_BIT	= 0x2
		};
		
		enum class e_rowAddressBits
		{
			_11	= 0x0,
			_12	= 0x1,
			_13	= 0x2
		};
		
		enum class e_columnAddressBits
		{
			_8	= 0x0,
			_9	= 0x1,
			_10	= 0x2,
			_11	= 0x3
		};
		
		
		
		typedef struct
		{
			e_readPipeDelay readPipeDelay;
			bool readBurst;
			e_clockDivision clockDivision;
			bool writeProtection;
			e_CAS_Latency CAS_Latency;
			e_numberOfInternalBanks numberOfInternalBanks;
			e_dataBusWidth dataBusWidth;
			e_rowAddressBits rowAddressBits;
			e_columnAddressBits columnAddressBits;
			
			uint8 t_RCD_rowToColumnDelay;
			uint8 t_RP_rowPrechargeDelay;
			uint8 t_WR_recoveryDelay;
			uint8 t_RC_rowCycleDelay;
			uint8 t_RAS_selfRefreshTime;
			uint8 t_XSR_exitSelfRefreshDelay;
			uint8 t_MRD_loadModeRegisterToActive;
		}s_SDRAM_config;
		
		
		
		
		
	private:
		
		RCC& m_rcc;
		
		s_SDRAM_config m_sdram_1;
		s_SDRAM_config m_sdram_2;
		
		constexpr inline FMC(RCC& rcc);
		FMC(const FMC& fmc) = delete;
		inline ~FMC();
		
		feedback memory_check(uint32 startAddress, uint32 sizeInBytes, uint32 pattern);
		
		
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup();
		
		feedback init(RCC::e_clockSource_fmc clockSource, e_SDRAM_bank bank, s_SDRAM_config memoryData);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline FMC::FMC(RCC& rcc)
	:	m_rcc(rcc),
		m_sdram_1(),
		m_sdram_2()
{
	
}


inline FMC::~FMC()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

