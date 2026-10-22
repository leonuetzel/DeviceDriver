#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback VREFBUF::startup()
{
	RCC& m_rcc = STM32H753BIT6::get().get_rcc();
	m_rcc.module_clockInit(RCC::e_module::VREF, true);
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback VREFBUF::set_mode(e_mode mode)
{
	if(mode == m_mode)
	{
		return(OK);
	}
	
	
	//	ENVR (Bit 0) and HIZ (Bit 1): OFF pulls VREF+ to VSSA, EXTERNAL leaves it to an external Reference (Reset State),
	//	INTERNAL drives it with the Voltage of VRS, HOLD keeps it with the Buffer off (RM0433, VREFBUF)
	const uint32 temp = *MCU::VREF::CSR & 0xFFFFFFFC;
	*MCU::VREF::CSR = temp | (uint32) mode;
	
	
	//	The Buffer is ready when VRR is set (some 100 Microseconds); without a sufficient VDDA it never gets there
	if(mode == e_mode::INTERNAL)
	{
		CMOS& cmos = CMOS::get();
		const uint64 timestampStart = cmos.get_timestamp();
		while(bit::isCleared(*MCU::VREF::CSR, 3))
		{
			if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 10)
			{
				*MCU::VREF::CSR = temp | (uint32) m_mode;
				return(FAIL);
			}
		}
	}
	m_mode = mode;
	return(OK);
}


feedback VREFBUF::set_voltage(e_voltage voltage)
{
	const uint32 mask = (uint32) voltage;
	if(mask > 0x3)
	{
		return(FAIL);
	}
	
	
	//	VRS (Bit 6-4) can be set in every Mode, best before the internal Mode is switched on
	const uint32 temp = *MCU::VREF::CSR & 0xFFFFFF8F;
	*MCU::VREF::CSR = temp | (mask << 4);
	
	
	//	A running Buffer is ready again when VRR is set
	if(m_mode == e_mode::INTERNAL)
	{
		CMOS& cmos = CMOS::get();
		const uint64 timestampStart = cmos.get_timestamp();
		while(bit::isCleared(*MCU::VREF::CSR, 3))
		{
			if(cmos.getMilliSecondsSinceTimestamp(timestampStart) > 10)
			{
				return(FAIL);
			}
		}
	}
	m_voltage = voltage;
	return(OK);
}