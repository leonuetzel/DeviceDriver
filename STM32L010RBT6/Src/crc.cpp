#include "../Inc/stm32l010rbt6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

void CRC::init(uint8 initialValue, uint8 polynomial, bool reverseOutputData, bool reverseInputData)
{
	//	CRC Initial Value
	*MCU::CRC::INIT = initialValue;
	
	
	//	Reset CRC Unit
	bit::set(*MCU::CRC::CR, 0);
	while(bit::isSet(*MCU::CRC::CR, 0) == true)
	{
		
	}
	
	
	//	CRC Settings
	uint32 CRC_CR = 0x00000010;
	if(reverseOutputData == true)
	{
		bit::set(CRC_CR, 7);
	}
	if(reverseInputData == true)
	{
		bit::set(CRC_CR, 5);
	}
	*MCU::CRC::CR = CRC_CR;
	
	
	//	Polynomial
	*MCU::CRC::POL = polynomial;
}


void CRC::init(uint16 initialValue, uint16 polynomial, bool reverseOutputData, bool reverseInputData)
{
	//	CRC Initial Value
	*MCU::CRC::INIT = initialValue;
	
	
	//	Reset CRC Unit
	bit::set(*MCU::CRC::CR, 0);
	while(bit::isSet(*MCU::CRC::CR, 0) == true)
	{
		
	}
	
	
	//	CRC Settings
	uint32 CRC_CR = 0x00000008;
	if(reverseOutputData == true)
	{
		bit::set(CRC_CR, 7);
	}
	if(reverseInputData == true)
	{
		bit::set(CRC_CR, 6);
	}
	*MCU::CRC::CR = CRC_CR;
	
	
	//	Polynomial
	*MCU::CRC::POL = polynomial;
}


void CRC::init(uint32 initialValue, uint32 polynomial, bool reverseOutputData, bool reverseInputData)
{
	//	CRC Initial Value
	*MCU::CRC::INIT = initialValue;
	
	
	//	Reset CRC Unit
	bit::set(*MCU::CRC::CR, 0);
	while(bit::isSet(*MCU::CRC::CR, 0) == true)
	{
		
	}
	
	
	//	CRC Settings
	uint32 CRC_CR = 0x00000000;
	if(reverseOutputData == true)
	{
		bit::set(CRC_CR, 7);
	}
	if(reverseInputData == true)
	{
		bit::set(CRC_CR, 5);
		bit::set(CRC_CR, 6);
	}
	*MCU::CRC::CR = CRC_CR;
	
	
	//	Polynomial
	*MCU::CRC::POL = polynomial;
}







CRC& CRC::operator<<(uint8 data)
{
	//	Explicit 8-Bit Write Access
	volatile uint8* const DR = (volatile uint8* const) MCU::CRC::DR;
	*DR = data;
	return(*this);
}


CRC& CRC::operator<<(uint16 data)
{
	//	Explicit 16-Bit Write Access
	volatile uint16* const DR = (volatile uint16* const) MCU::CRC::DR;
	*DR = data;
	return(*this);
}


CRC& CRC::operator<<(uint32 data)
{
	//	Explicit 32-Bit Write Access
	volatile uint32* const DR = (volatile uint32* const) MCU::CRC::DR;
	*DR = data;
	return(*this);
}







uint32 CRC::operator()() const
{
	return(*MCU::CRC::DR);
}