#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback SPI_3::init(uint32 frequency, bool cpol, bool cpha)
{
	//	Enable SPI Bus Clock
	RCC& rcc = STM32F107RCT6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::SPI_3, true);
	
	
	//	Disable SPI
	bit::clear(*MCU::SPI_3::CR1, 6);
	
	
	//	Reset SPI
	rcc.module_reset(RCC::e_module::SPI_3);
	
	
	//	Set SPI Clock
	//	SPI_3 is located on APB1
	const uint32 clock_apb1 = rcc.get_clock_apb1();
	const uint32 divider = clock_apb1 / frequency;
	const uint32 bitMask = Math::log2(divider) - 1;
	if(bitMask > 0x7)
	{
		return(FAIL);
	}
	const uint32 spi_cr1 = *MCU::SPI_3::CR1 & 0xFFFFFFC7;
	*MCU::SPI_3::CR1 = spi_cr1 | (bitMask << 3);
	
	
	//	Enable Software NSS
	bit::set(*MCU::SPI_3::CR1, 9);
	
	
	//	CPOL
	if(cpol == true)
	{
		bit::set(*MCU::SPI_3::CR1, 1);
	}
	else
	{
		bit::clear(*MCU::SPI_3::CR1, 1);
	}
	
	
	//	CPHA
	if(cpha == true)
	{
		bit::set(*MCU::SPI_3::CR1, 0);
	}
	else
	{
		bit::clear(*MCU::SPI_3::CR1, 0);
	}
	
	
	//	SPI Master Mode
	bit::set(*MCU::SPI_3::CR1, 2);
	
	
	//	NSS Internal needed High in Master Mode
	bit::set(*MCU::SPI_3::CR1, 8);
	
	
	//	Enable SPI
	bit::set(*MCU::SPI_3::CR1, 6);
	
	
	return(OK);
}







uint8 SPI_3::operator()(uint8 data)
{
	//	Send Byte
	*MCU::SPI_3::DR = data;
	while(bit::isCleared(*MCU::SPI_3::SR, 0))
	{
		
	}
	
	
	//	Receive Byte
	const uint8 rxByte = *MCU::SPI_3::DR;
	
	
	return(rxByte);
}


Array<uint8> SPI_3::operator()(const Array<uint8>& data)
{
	//	Send Data bytewise
	Array<uint8> rxData = 0;
	for(auto& i: data)
	{
		//	Send Byte
		*MCU::SPI_3::DR = i;
		while(bit::isCleared(*MCU::SPI_3::SR, 0))
		{
			
		}
		
		
		//	Receive Byte
		rxData += *MCU::SPI_3::DR;
	}
	
	
	return(rxData);
}