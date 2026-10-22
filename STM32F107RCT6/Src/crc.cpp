#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void CRC::switchToSoftware()
{
	//	The Data Register holds the current CRC (not reversed): CRC_Software continues with it and the same Settings
	if(m_hardware == true)
	{
		CMOS& cmos = CMOS::get();
		cmos.mutex_lock(&m_software);
		m_software.init(*MCU::CRC::DR, c_polynomial, m_reverseOutputData, m_reverseInputData);
		cmos.mutex_unlock(&m_software);
		m_hardware = false;
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback CRC::init(uint8 initialValue, uint8 polynomial, bool reverseOutputData, bool reverseInputData)
{
	//	CRC-8: only in Software
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	m_hardware = false;
	cmos.mutex_lock(&m_software);
	const feedback result = m_software.init(initialValue, polynomial, reverseOutputData, reverseInputData);
	cmos.mutex_unlock(&m_software);
	return(result);
}


feedback CRC::init(uint16 initialValue, uint16 polynomial, bool reverseOutputData, bool reverseInputData)
{
	//	CRC-16: only in Software
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	m_hardware = false;
	cmos.mutex_lock(&m_software);
	const feedback result = m_software.init(initialValue, polynomial, reverseOutputData, reverseInputData);
	cmos.mutex_unlock(&m_software);
	return(result);
}


feedback CRC::init(uint32 initialValue, uint32 polynomial, bool reverseOutputData, bool reverseInputData)
{
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(FAIL);
	}
	m_reverseOutputData = reverseOutputData;
	m_reverseInputData = reverseInputData;
	
	
	//	The CRC Unit knows only one Polynomial and one Start Value, other Settings are calculated in Software
	if(initialValue != c_initialValue || polynomial != c_polynomial)
	{
		m_hardware = false;
		cmos.mutex_lock(&m_software);
		const feedback result = m_software.init(initialValue, polynomial, reverseOutputData, reverseInputData);
		cmos.mutex_unlock(&m_software);
		return(result);
	}
	
	
	//	RESET sets the Data Register to 0xFFFFFFFF (RM0008, CRC_CR)
	m_hardware = true;
	bit::set(*MCU::CRC::CR, 0);
	return(OK);
}


I_CRC& CRC::operator<<(uint8 data)
{
	if(CMOS::get().mutex_isOwnedByRunningThread(this) == false)
	{
		return(*this);
	}
	
	
	//	The CRC Unit only takes Words of 32 Bit: from now on the Software calculates
	switchToSoftware();
	CMOS& cmos = CMOS::get();
	cmos.mutex_lock(&m_software);
	m_software << data;
	cmos.mutex_unlock(&m_software);
	return(*this);
}


I_CRC& CRC::operator<<(uint16 data)
{
	if(CMOS::get().mutex_isOwnedByRunningThread(this) == false)
	{
		return(*this);
	}
	
	
	//	The CRC Unit only takes Words of 32 Bit: from now on the Software calculates
	switchToSoftware();
	CMOS& cmos = CMOS::get();
	cmos.mutex_lock(&m_software);
	m_software << data;
	cmos.mutex_unlock(&m_software);
	return(*this);
}


I_CRC& CRC::operator<<(uint32 data)
{
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(*this);
	}
	if(m_hardware == false)
	{
		cmos.mutex_lock(&m_software);
		m_software << data;
		cmos.mutex_unlock(&m_software);
		return(*this);
	}
	
	
	//	The Unit divides the Word with the most significant Bit first; reversed Input is reversed before
	*MCU::CRC::DR = (m_reverseInputData == true) ? reverse(data) : data;
	return(*this);
}


uint32 CRC::operator()() const
{
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_isOwnedByRunningThread(this) == false)
	{
		return(0);
	}
	if(m_hardware == false)
	{
		cmos.mutex_lock(&m_software);
		const uint32 result = m_software();
		cmos.mutex_unlock(&m_software);
		return(result);
	}
	
	
	//	The Data Register holds the CRC after the last Word, without a final XOR
	const uint32 value = *MCU::CRC::DR;
	return((m_reverseOutputData == true) ? reverse(value) : value);
}
