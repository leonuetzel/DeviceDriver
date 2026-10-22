#pragma once

#include "registers.hpp"
#include "rcc.hpp"
#include "gpio.hpp"





class PWR
{
	public:
		
		enum class e_voltageScaling
		{
			RANGE1_1V2	= 0x1,
			RANGE2_1V0	= 0x2
		};
		
		//	Wakeup Pins of Standby and Shutdown (RM0394, PWR_CR3 EWUPx)
		enum class e_wakeupPin : uint8
		{
			WKUP_1	= 0,		//	PA0
			WKUP_2	= 1,		//	PC13
			WKUP_3	= 2,		//	PE6, only in Packages with Port E
			WKUP_4	= 3,		//	PA2
			WKUP_5	= 4			//	PC5
		};
		
		//	Edge that wakes the Device (RM0394, PWR_CR4 WPx)
		enum class e_wakeupEdge : uint8
		{
			RISING	= 0,
			FALLING	= 1
		};
		
		//	Pull-up or Pull-down of a Pin in Standby and Shutdown (RM0394, PWR_PUCRx, PWR_PDCRx)
		enum class e_lowPowerPull : uint8
		{
			NONE,
			UP,
			DOWN
		};
		
		//	RTC_BKP0R ... RTC_BKP30R belong to the Application, RTC_BKP31R to the Driver (Exit from Shutdown, see enterShutdown())
		static constexpr uint32 c_numberOfBackupRegisters = 31;
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint32 c_lowPowerMode_standby		= 0x3;					//	PWR_CR1 LPMS (RM0394)
		static constexpr uint32 c_lowPowerMode_shutdown	= 0x4;
		static constexpr uint32 c_shutdownMarker				= 0x53485444;		//	"SHTD" in RTC_BKP31R
		
		
		//	Non-static Member
		e_voltageScaling m_voltageScaling;
		
		//	Wakeup State of the last Start, taken in startup() before it is cleared: PWR_SR1 (SBF, WUFx) and the Shutdown Marker
		uint32 m_wakeupFlags;
		bool m_wakeupFromShutdown;
		
		
		//	Constructor and Destructor
		constexpr inline PWR();
		PWR(const PWR& pwr) = delete;
		inline ~PWR();
		
		
		//	Member Functions
		inline feedback startup(RCC& rcc);
		NORETURN static void enterLowPowerMode(uint32 mode);
		static void disable_rtcOnWakeupPin(uint32 pin);
		
		
		//	Friends
		friend class STM32L451RET6;
		
		
		
		
		
	public:
		
		inline feedback set_backupDomain_writeProtection(bool enable);
		inline feedback set_voltageScaling(e_voltageScaling voltageScaling);
		constexpr inline e_voltageScaling get_voltageScaling() const;
		
		inline feedback voltageScalingIncrease();
		inline feedback voltageScalingDecrease();
		
		//	Backup Registers RTC_BKP0R ... RTC_BKP30R (Backup Domain: they keep their Value in Standby, Shutdown and over Resets)
		uint32 get_backupRegister(uint32 index);
		feedback set_backupRegister(uint32 index, uint32 value);
		
		//	Standby and Shutdown: Wakeup Pins, Pulls of the Pins in the Mode, Entry - call the Entry through CMOS::shutdown(), which stops
		//	the Kernel and the SysTick first: cmos.shutdown(PWR::enterShutdown)
		feedback set_wakeupPin(e_wakeupPin pin, bool enable, e_wakeupEdge edge = e_wakeupEdge::RISING);
		feedback set_lowPowerPull(MCU::PIN pin, e_lowPowerPull pull);
		void clear_lowPowerPulls();
		NORETURN static void enterStandby();
		NORETURN static void enterShutdown();
		
		//	Wakeup State of the last Start: Exit from Standby, Exit from Shutdown, and the Wakeup Pins that woke the Device from Standby
		//	(Bit 0 = WKUP_1; after Shutdown the Hardware has cleared them). RCC::get_resetCause() combines this with the Reset Flags
		constexpr inline bool wasInStandby() const;
		constexpr inline bool wasInShutdown() const;
		constexpr inline uint8 get_wakeupPins() const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline PWR::PWR()
	:	m_voltageScaling(e_voltageScaling::RANGE1_1V2),
		m_wakeupFlags(0),
		m_wakeupFromShutdown(false)
{
	
}


inline PWR::~PWR()
{
	
}







inline feedback PWR::startup(RCC& rcc)
{
	rcc.module_clockInit(RCC::e_module::PWR, true);
	
	
	//	Disable Write Protection of Backup Domain
	set_backupDomain_writeProtection(false);
	
	
	//	Wakeup State: a Snapshot of SBF (Exit from Standby) and WUFx (Wakeup Pins), then cleared, so that the next Start shows only its own
	//	Flags (RM0394, PWR_SR1, PWR_SCR). A System Reset keeps them, only a Power-on Reset clears them
	m_wakeupFlags = *MCU::PWR::SR1 & 0x0000011F;
	*MCU::PWR::SCR = 0x0000011F;
	
	
	//	The Exit from Shutdown is a Brownout Reset (BORRSTF) without SBF, and it resets the PWR Registers: only the Marker that
	//	enterShutdown() leaves in RTC_BKP31R (Backup Domain) tells it from a real Brownout. RCC::startup() clears RCC_CSR later
	rcc.module_clockInit(RCC::e_module::RTC, true);
	if(*MCU::RTC::BKP_31 == c_shutdownMarker)
	{
		m_wakeupFromShutdown = bit::isSet(*MCU::RCC::CSR, 27);
		*MCU::RTC::BKP_31 = 0;
	}
	rcc.module_clockInit(RCC::e_module::RTC, false);
	
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline feedback PWR::set_backupDomain_writeProtection(bool enable)
{
	if(enable == true)
	{
		bit::clear(*MCU::PWR::CR1, 8);
	}
	else
	{
		bit::set(*MCU::PWR::CR1, 8);
	}
	
	return(OK);
}


inline feedback PWR::set_voltageScaling(e_voltageScaling voltageScaling)
{
	const uint32 temp = *MCU::PWR::CR1 & 0xFFFFF9FF;
	const uint32 mask = (uint32) voltageScaling;
	*MCU::PWR::CR1 = temp | (mask << 9);
	m_voltageScaling = voltageScaling;
	
	
	//	Wait until the Regulator has reached the new Level (VOSF, PWR_SR2 Bit 10), before Clocks are raised
	uint32 timeout = 1000000;
	while(bit::isSet(*MCU::PWR::SR2, 10) == true)
	{
		timeout--;
		if(timeout == 0)
		{
			return(FAIL);
		}
	}
	return(OK);
}


constexpr inline PWR::e_voltageScaling PWR::get_voltageScaling() const
{
	return(m_voltageScaling);
}







inline feedback PWR::voltageScalingIncrease()
{
	if(m_voltageScaling == e_voltageScaling::RANGE2_1V0)
	{
		return(set_voltageScaling(e_voltageScaling::RANGE1_1V2));
	}
	return(FAIL);
}


inline feedback PWR::voltageScalingDecrease()
{
	if(m_voltageScaling == e_voltageScaling::RANGE1_1V2)
	{
		return(set_voltageScaling(e_voltageScaling::RANGE2_1V0));
	}
	return(FAIL);
}







constexpr inline bool PWR::wasInStandby() const
{
	return(bit::isSet(m_wakeupFlags, 8));
}


constexpr inline bool PWR::wasInShutdown() const
{
	return(m_wakeupFromShutdown);
}


constexpr inline uint8 PWR::get_wakeupPins() const
{
	return((uint8) (m_wakeupFlags & 0x1F));
}
