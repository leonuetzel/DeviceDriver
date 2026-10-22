#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback MDMA::startup()
{
	RCC& rcc = STM32H753BIT6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::MDMA, true);
	return(OK);
}




/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

CODE_RAM feedback MDMA::copy(uint8 channel, uint8* source, uint8* destination, uint16 sizeInBytes)
{
	if(channel > 15)
	{
		return(FAIL);
	}
	
	volatile uint32* reg_cr = MCU::MDMA::CH0_CR + (0x10 * channel);
	
	if(bit::isSet(*reg_cr, 0))
	{
		return(FAIL);
	}
	
	
	
	volatile uint32* reg_tcr = MCU::MDMA::CH0_TCR + (0x10 * channel);
	*reg_tcr = 0x51FC000A;
	
	
	volatile uint32* reg_bndtr = MCU::MDMA::CH0_BNDTR + (0x10 * channel);
	*reg_bndtr = sizeInBytes;
	
	
	volatile uint32* reg_sar = MCU::MDMA::CH0_SAR + (0x10 * channel);
	*reg_sar = (uint32) source;
	
	
	volatile uint32* reg_dar = MCU::MDMA::CH0_DAR + (0x10 * channel);
	*reg_dar = (uint32) destination;
	
	
	volatile uint32* reg_tbr = MCU::MDMA::CH0_TBR + (0x10 * channel);
	//	The TCMs (ITCM 0x00000000 ... 0x0000FFFF, DTCM 0x20000000 ... 0x2001FFFF) are reached over the AHB Bus (DBUS/SBUS = 1),
	//	everything else (e.g. Flash, AXI SRAM, SRAM 1 ... 4) over the AXI Bus (RM0433, MDMA_CxTBR)
	const uint32 address_source = (uint32) source;
	const uint32 address_destination = (uint32) destination;
	const bool source_TCM = address_source < 0x00010000 || (address_source >= 0x20000000 && address_source < 0x20020000);
	const bool destination_TCM = address_destination < 0x00010000 || (address_destination >= 0x20000000 && address_destination < 0x20020000);
	uint32 tbr = 0;
	if(destination_TCM == true)
	{
		bit::set(tbr, 17);
	}
	if(source_TCM == true)
	{
		bit::set(tbr, 16);
	}
	*reg_tbr = tbr;
	
	
	volatile uint32* reg_ifcr = MCU::MDMA::CH0_IFCR + (0x10 * channel);
	*reg_ifcr = 0x0000001F;
	
	
	//	Cache Maintenance and Barrier before the Start (see cacheMaintenance.hpp)
	CacheMaintenance::beforeRead(source, sizeInBytes);
	CacheMaintenance::beforeWrite(destination, sizeInBytes);
	
	
	bit::set(*reg_cr, 4);																																																					//	Enable Block Transfer Complete Interrupt
	bit::set(*reg_cr, 1);																																																					//	Enable Transfer Error Interrupt
	
	bit::set(*reg_cr, 0);																																																					//	Enable Channel
	bit::set(*reg_cr, 16);																																																				//	Software Request
	
	return(OK);
}


CODE_RAM feedback MDMA::copy(uint8 channel, uint16* source, uint16* destination, uint16 sizeInBytes)
{
	if(channel > 15 || sizeInBytes % 2 != 0 || bit::isSet((uint32) destination, 0))
	{
		return(FAIL);
	}
	
	volatile uint32* reg_cr = MCU::MDMA::CH0_CR + (0x10 * channel);
	
	if(bit::isSet(*reg_cr, 0))
	{
		return(FAIL);
	}
	
	
	
	volatile uint32* reg_tcr = MCU::MDMA::CH0_TCR + (0x10 * channel);
	*reg_tcr = 0x51FC055A;
	
	
	volatile uint32* reg_bndtr = MCU::MDMA::CH0_BNDTR + (0x10 * channel);
	*reg_bndtr = sizeInBytes;
	
	
	volatile uint32* reg_sar = MCU::MDMA::CH0_SAR + (0x10 * channel);
	*reg_sar = (uint32) source;
	
	
	volatile uint32* reg_dar = MCU::MDMA::CH0_DAR + (0x10 * channel);
	*reg_dar = (uint32) destination;
	
	
	volatile uint32* reg_tbr = MCU::MDMA::CH0_TBR + (0x10 * channel);
	//	The TCMs (ITCM 0x00000000 ... 0x0000FFFF, DTCM 0x20000000 ... 0x2001FFFF) are reached over the AHB Bus (DBUS/SBUS = 1),
	//	everything else (e.g. Flash, AXI SRAM, SRAM 1 ... 4) over the AXI Bus (RM0433, MDMA_CxTBR)
	const uint32 address_source = (uint32) source;
	const uint32 address_destination = (uint32) destination;
	const bool source_TCM = address_source < 0x00010000 || (address_source >= 0x20000000 && address_source < 0x20020000);
	const bool destination_TCM = address_destination < 0x00010000 || (address_destination >= 0x20000000 && address_destination < 0x20020000);
	uint32 tbr = 0;
	if(destination_TCM == true)
	{
		bit::set(tbr, 17);
	}
	if(source_TCM == true)
	{
		bit::set(tbr, 16);
	}
	*reg_tbr = tbr;
	
	
	volatile uint32* reg_ifcr = MCU::MDMA::CH0_IFCR + (0x10 * channel);
	*reg_ifcr = 0x0000001F;
	
	
	//	Cache Maintenance and Barrier before the Start (see cacheMaintenance.hpp)
	CacheMaintenance::beforeRead(source, sizeInBytes);
	CacheMaintenance::beforeWrite(destination, sizeInBytes);
	
	
	bit::set(*reg_cr, 4);																																																					//	Enable Block Transfer Complete Interrupt
	bit::set(*reg_cr, 1);																																																					//	Enable Transfer Error Interrupt
	
	bit::set(*reg_cr, 0);																																																					//	Enable Channel
	bit::set(*reg_cr, 16);																																																				//	Software Request
	
	return(OK);
}


CODE_RAM feedback MDMA::copy(uint8 channel, uint32* source, uint32* destination, uint16 sizeInBytes)
{
	if(channel > 15 || sizeInBytes % 4 != 0 || (((uint32) destination) & 0x3) != 0)
	{
		return(FAIL);
	}
	
	volatile uint32* reg_cr = MCU::MDMA::CH0_CR + (0x10 * channel);
	
	if(bit::isSet(*reg_cr, 0))
	{
		return(FAIL);
	}
	
	
	
	volatile uint32* reg_tcr = MCU::MDMA::CH0_TCR + (0x10 * channel);
	*reg_tcr = 0x51FC0AAA;
	
	
	volatile uint32* reg_bndtr = MCU::MDMA::CH0_BNDTR + (0x10 * channel);
	*reg_bndtr = sizeInBytes;
	
	
	volatile uint32* reg_sar = MCU::MDMA::CH0_SAR + (0x10 * channel);
	*reg_sar = (uint32) source;
	
	
	volatile uint32* reg_dar = MCU::MDMA::CH0_DAR + (0x10 * channel);
	*reg_dar = (uint32) destination;
	
	
	volatile uint32* reg_tbr = MCU::MDMA::CH0_TBR + (0x10 * channel);
	//	The TCMs (ITCM 0x00000000 ... 0x0000FFFF, DTCM 0x20000000 ... 0x2001FFFF) are reached over the AHB Bus (DBUS/SBUS = 1),
	//	everything else (e.g. Flash, AXI SRAM, SRAM 1 ... 4) over the AXI Bus (RM0433, MDMA_CxTBR)
	const uint32 address_source = (uint32) source;
	const uint32 address_destination = (uint32) destination;
	const bool source_TCM = address_source < 0x00010000 || (address_source >= 0x20000000 && address_source < 0x20020000);
	const bool destination_TCM = address_destination < 0x00010000 || (address_destination >= 0x20000000 && address_destination < 0x20020000);
	uint32 tbr = 0;
	if(destination_TCM == true)
	{
		bit::set(tbr, 17);
	}
	if(source_TCM == true)
	{
		bit::set(tbr, 16);
	}
	*reg_tbr = tbr;
	
	
	volatile uint32* reg_ifcr = MCU::MDMA::CH0_IFCR + (0x10 * channel);
	*reg_ifcr = 0x0000001F;
	
	
	//	Cache Maintenance and Barrier before the Start (see cacheMaintenance.hpp)
	CacheMaintenance::beforeRead(source, sizeInBytes);
	CacheMaintenance::beforeWrite(destination, sizeInBytes);
	
	
	bit::set(*reg_cr, 4);																																																					//	Enable Block Transfer Complete Interrupt
	bit::set(*reg_cr, 1);																																																					//	Enable Transfer Error Interrupt
	
	bit::set(*reg_cr, 0);																																																					//	Enable Channel
	bit::set(*reg_cr, 16);																																																				//	Software Request
	
	return(OK);
}







CODE_RAM feedback MDMA::fill(uint8 channel, uint8 data, uint8* destination, uint16 sizeInBytes)
{
	static uint8 fill_data[16];
	
	if(channel > 15)
	{
		return(FAIL);
	}
	
	volatile uint32* reg_cr = MCU::MDMA::CH0_CR + (0x10 * channel);
	
	if(bit::isSet(*reg_cr, 0))
	{
		return(FAIL);
	}
	
	fill_data[channel] = data;
	
	
	
	volatile uint32* reg_tcr = MCU::MDMA::CH0_TCR + (0x10 * channel);
	*reg_tcr = 0x51FC0008;
	
	
	volatile uint32* reg_bndtr = MCU::MDMA::CH0_BNDTR + (0x10 * channel);
	*reg_bndtr = sizeInBytes;
	
	
	volatile uint32* reg_sar = MCU::MDMA::CH0_SAR + (0x10 * channel);
	*reg_sar = (uint32) &fill_data[channel];
	
	
	volatile uint32* reg_dar = MCU::MDMA::CH0_DAR + (0x10 * channel);
	*reg_dar = (uint32) destination;
	
	
	volatile uint32* reg_tbr = MCU::MDMA::CH0_TBR + (0x10 * channel);
	if((uint32) destination < 0x20020000)
	{
		*reg_tbr = 0x00020000;
	}
	else
	{
		*reg_tbr = 0x00000000;
	}
	
	
	volatile uint32* reg_ifcr = MCU::MDMA::CH0_IFCR + (0x10 * channel);
	*reg_ifcr = 0x0000001F;
	
	
	//	Cache Maintenance and Barrier before the Start (see cacheMaintenance.hpp)
	CacheMaintenance::beforeRead(&fill_data[channel], sizeof(fill_data[channel]));
	CacheMaintenance::beforeWrite(destination, sizeInBytes);
	
	
	bit::set(*reg_cr, 4);																																																					//	Enable Block Transfer Complete Interrupt
	bit::set(*reg_cr, 1);																																																					//	Enable Transfer Error Interrupt
	
	bit::set(*reg_cr, 0);																																																					//	Enable Channel
	bit::set(*reg_cr, 16);																																																				//	Software Request
	
	return(OK);
}


CODE_RAM feedback MDMA::fill(uint8 channel, uint16 data, uint16* destination, uint16 sizeInBytes)
{
	static uint16 fill_data[16];
	
	if(channel > 15 || sizeInBytes % 2 != 0 || bit::isSet((uint32) destination, 0))
	{
		return(FAIL);
	}
	
	volatile uint32* reg_cr = MCU::MDMA::CH0_CR + (0x10 * channel);
	
	if(bit::isSet(*reg_cr, 0))
	{
		return(FAIL);
	}
	
	fill_data[channel] = data;
	
	
	
	volatile uint32* reg_tcr = MCU::MDMA::CH0_TCR + (0x10 * channel);
	*reg_tcr = 0x51FC0458;
	
	
	volatile uint32* reg_bndtr = MCU::MDMA::CH0_BNDTR + (0x10 * channel);
	*reg_bndtr = sizeInBytes;
	
	
	volatile uint32* reg_sar = MCU::MDMA::CH0_SAR + (0x10 * channel);
	*reg_sar = (uint32) &fill_data[channel];
	
	
	volatile uint32* reg_dar = MCU::MDMA::CH0_DAR + (0x10 * channel);
	*reg_dar = (uint32) destination;
	
	
	volatile uint32* reg_tbr = MCU::MDMA::CH0_TBR + (0x10 * channel);
	if((uint32) destination < 0x20020000)
	{
		*reg_tbr = 0x00020000;
	}
	else
	{
		*reg_tbr = 0x00000000;
	}
	
	
	volatile uint32* reg_ifcr = MCU::MDMA::CH0_IFCR + (0x10 * channel);
	*reg_ifcr = 0x0000001F;
	
	
	//	Cache Maintenance and Barrier before the Start (see cacheMaintenance.hpp)
	CacheMaintenance::beforeRead(&fill_data[channel], sizeof(fill_data[channel]));
	CacheMaintenance::beforeWrite(destination, sizeInBytes);
	
	
	bit::set(*reg_cr, 4);																																																					//	Enable Block Transfer Complete Interrupt
	bit::set(*reg_cr, 1);																																																					//	Enable Transfer Error Interrupt
	
	bit::set(*reg_cr, 0);																																																					//	Enable Channel
	bit::set(*reg_cr, 16);																																																				//	Software Request
	
	return(OK);
}


CODE_RAM feedback MDMA::fill(uint8 channel, uint32 data, uint32* destination, uint16 sizeInBytes)
{
	static uint32 fill_data[16];
	
	if(channel > 15 || sizeInBytes % 4 != 0 || (((uint32) destination) & 0x3) != 0)
	{
		return(FAIL);
	}
	
	volatile uint32* reg_cr = MCU::MDMA::CH0_CR + (0x10 * channel);
	
	if(bit::isSet(*reg_cr, 0))
	{
		return(FAIL);
	}
	
	fill_data[channel] = data;
	
	
	
	volatile uint32* reg_tcr = MCU::MDMA::CH0_TCR + (0x10 * channel);
	*reg_tcr = 0x51FC08A8;
	
	
	volatile uint32* reg_bndtr = MCU::MDMA::CH0_BNDTR + (0x10 * channel);
	*reg_bndtr = sizeInBytes;
	
	
	volatile uint32* reg_sar = MCU::MDMA::CH0_SAR + (0x10 * channel);
	*reg_sar = (uint32) &fill_data[channel];
	
	
	volatile uint32* reg_dar = MCU::MDMA::CH0_DAR + (0x10 * channel);
	*reg_dar = (uint32) destination;
	
	
	volatile uint32* reg_tbr = MCU::MDMA::CH0_TBR + (0x10 * channel);
	if((uint32) destination < 0x20020000)
	{
		*reg_tbr = 0x00020000;
	}
	else
	{
		*reg_tbr = 0x00000000;
	}
	
	
	volatile uint32* reg_ifcr = MCU::MDMA::CH0_IFCR + (0x10 * channel);
	*reg_ifcr = 0x0000001F;
	
	
	//	Cache Maintenance and Barrier before the Start (see cacheMaintenance.hpp)
	CacheMaintenance::beforeRead(&fill_data[channel], sizeof(fill_data[channel]));
	CacheMaintenance::beforeWrite(destination, sizeInBytes);
	
	
	bit::set(*reg_cr, 4);																																																					//	Enable Block Transfer Complete Interrupt
	bit::set(*reg_cr, 1);																																																					//	Enable Transfer Error Interrupt
	
	bit::set(*reg_cr, 0);																																																					//	Enable Channel
	bit::set(*reg_cr, 16);																																																				//	Software Request
	
	return(OK);
}