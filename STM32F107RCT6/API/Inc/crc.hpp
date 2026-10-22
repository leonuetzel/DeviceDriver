#pragma once

#include "cmos.hpp"

#include "registers.hpp"
#include "rcc.hpp"





//	CRC Unit of the F1 Series: only CRC-32 with the Polynomial 0x04C11DB7, the Start Value 0xFFFFFFFF and Data Words of 32 Bit
//	(RM0008, CRC calculation unit). Everything else - other Polynomials, Start Values or Widths, Bytes and Half Words - is calculated by
//	CRC_Software of CMOS; the Hardware hands over its intermediate Value when a Byte or Half Word comes
class CRC : public I_CRC
{
	public:
		
		static constexpr uint32 c_polynomial		= 0x04C11DB7;
		static constexpr uint32 c_initialValue	= 0xFFFFFFFF;
	
	
	
	
	
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		bool m_hardware;
		bool m_reverseOutputData;
		bool m_reverseInputData;
		CRC_Software m_software;
		
		
		//	Constructor and Destructor
		constexpr inline CRC();
		CRC(const CRC& crc) = delete;
		inline ~CRC();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		static inline uint32 reverse(uint32 value);
		void switchToSoftware();
		
		
		//	Friends
		friend class STM32F107RCT6;
	
	
	
	
	
	public:
		
		feedback init(uint8 initialValue, uint8 polynomial, bool reverseOutputData = false, bool reverseInputData = false) override;
		feedback init(uint16 initialValue, uint16 polynomial, bool reverseOutputData = false, bool reverseInputData = false) override;
		feedback init(uint32 initialValue, uint32 polynomial, bool reverseOutputData = false, bool reverseInputData = false) override;
		I_CRC& operator<<(uint8 data) override;
		I_CRC& operator<<(uint16 data) override;
		I_CRC& operator<<(uint32 data) override;
		uint32 operator()() const override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline CRC::CRC()
	:	m_hardware(false),
		m_reverseOutputData(false),
		m_reverseInputData(false),
		m_software()
{
	
}


inline CRC::~CRC()
{
	
}


inline feedback CRC::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::CRC, true);
	
	
	//	Mutex of the Driver (the Application locks it) and of the Software Calculation (the Driver locks it for every Access)
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_create(this) != OK || cmos.mutex_create(&m_software) != OK)
	{
		return(FAIL);
	}
	return(OK);
}


inline uint32 CRC::reverse(uint32 value)
{
	//	Bit Order reversed: Bit 0 becomes Bit 31 (RBIT of the Cortex-M3)
	uint32 result = 0;
	asm volatile
	(
		"rbit %[out], %[in]"
			: [out] "=r" (result)
			: [in] "r" (value)
			:
	);
	return(result);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/
