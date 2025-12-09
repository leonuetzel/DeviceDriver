#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback SDMMC_1::startup()
{
	return(OK);
}







feedback SDMMC_1::set_clockSpeed(RCC& rcc, uint32 clock)
{
	uint32 clock_in = 0;
	switch(m_clockSource)
	{
		case RCC::e_clockSource_sdmmc::PLL_1_Q:
			clock_in = rcc.get_clock_pll_1_q();
			break;
			
		case RCC::e_clockSource_sdmmc::PLL_2_R:
			clock_in = rcc.get_clock_pll_2_r();
			break;
			
		default:
			return(FAIL);
	}
	
	uint32 prescaler = clock_in / clock;
	if(prescaler % 2 != 0)
	{
		prescaler++;
	}
	m_clock = clock_in / prescaler;
	uint32 temp = *MCU::SDMMC_1::CLKCR & 0xFFFFFC00;
	*MCU::SDMMC_1::CLKCR = temp | (prescaler / 2);
	
	return(OK);
}


feedback SDMMC_1::set_busWidth(e_busWidth busWidth)
{
	if(m_busWidth == busWidth)
	{
		return(OK);
	}
	
	if(busWidth == e_busWidth::BUSWIDTH_8)
	{
		return(FAIL);
	}
	
	uint32 temp = *MCU::SDMMC_1::CLKCR & 0xFFFF3FFF;
	*MCU::SDMMC_1::CLKCR = temp | (((uint32) busWidth) << 14);
	
	m_busWidth = busWidth;
	return(OK);
}


CODE_RAM SDMMC_1::s_response SDMMC_1::send_command(s_commandPath command) const
{
	CMOS& cmos = CMOS::get();
	
	s_response response;
	response.response_127_96 = 0;
	response.response_95_64 = 0;
	response.response_63_32 = 0;
	response.response_31_0 = 0;
	response.success = FAIL;
	
	if(((uint32) command.command & 0xFFFFFCFF) > 0x0000003F)
	{
		return(response);
	}
	
	while(bit::isSet(*MCU::SDMMC_1::STAR, 13))																																										//	Wait for Control Path to be in IDLE State
	{
		cmos.sleep_ms(1);
	}
	
	*MCU::SDMMC_1::ICR = *MCU::SDMMC_1::STAR;																																											//	Clear Flags
	*MCU::SDMMC_1::ARGR = command.argument;																																												//	Set Argument
	
	
	
	if(command.dataTransfer == true)																																															//	Send Command
	{
		*MCU::SDMMC_1::CMDR = 0x00001040 | ((uint32) command.command);
	}
	else
	{
		*MCU::SDMMC_1::CMDR = 0x00001000 | ((uint32) command.command);
	}
	
	while(bit::isSet(*MCU::SDMMC_1::STAR, 13))																																										//	Wait for Command to be transmitted
	{
		cmos.sleep_ms(1);
	}
	while(bit::isSet(*MCU::SDMMC_1::STAR, 12))																																										//	Wait for Data to be transmitted
	{
		cmos.sleep_ms(1);
	}
	
	
	uint32 status = *MCU::SDMMC_1::STAR;
	switch((((uint32) command.command) & 0x00000300) >> 8)
	{
		case 0x0:
			if(bit::isSet(status, 7))
			{
				response.success = OK;
			}
			break;
			
		case 0x1:
			if(bit::isSet(status, 6))
			{
				response.response_31_0 = *MCU::SDMMC_1::RESP_1R;
				response.success = OK;
			}
			break;
			
		case 0x2:
			if(bit::isSet(status, 6))
			{
				response.response_31_0 = *MCU::SDMMC_1::RESP_1R;
				response.success = OK;
			}
			break;
			
		case 0x3:
			if(bit::isSet(status, 6))
			{
				response.response_127_96 = *MCU::SDMMC_1::RESP_1R;
				response.response_95_64 = *MCU::SDMMC_1::RESP_2R;
				response.response_63_32 = *MCU::SDMMC_1::RESP_3R;
				response.response_31_0 = *MCU::SDMMC_1::RESP_4R;
				response.success = OK;
			}
			break;
			
		default:
			break;
	}
	
	if(bit::isSet(status, 1) || bit::isSet(status, 3))
	{
		response.success = FAIL;
	}
	
	
	
	*MCU::SDMMC_1::ICR = status;
	return(response);
}


CODE_RAM void SDMMC_1::setup_dataPath(s_dataPath dataPath) const
{
	*MCU::SDMMC_1::DLENR = dataPath.data_sizeInBytes;
	*MCU::SDMMC_1::DTIMER = dataPath.timeout;
	*MCU::SDMMC_1::DCTRLR = ((uint32) dataPath.blockSize << 4) | ((uint32) dataPath.mode << 2) | ((uint32) dataPath.direction << 1);
}







feedback SDMMC_1::command_reset()
{
	s_commandPath command;
	s_response response;
	
	command.command = e_commandPath_command::ID_0_GO_IDLE_STATE;																																	//	CMD0: Reset SD Card
	command.argument = 0;
	command.dataTransfer = false;
	response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}
	
	return(OK);
}


feedback SDMMC_1::command_operatingConditionValidation()
{
	s_commandPath command;
	s_response response;
	
	command.command = e_commandPath_command::ID_8_SEND_IF_CONDITION;																															//	CMD8: Voltage Range 2,7V - 3,6V, Check Pattern: 0xAA
	command.argument = 0x000001AA;
	command.dataTransfer = false;
	response = send_command(command);
	if(response.success == FAIL || response.response_31_0 != command.argument)
	{
		return(FAIL);
	}
	
	return(OK);
}


feedback SDMMC_1::command_set_operatingCondition()
{
	s_commandPath command;
	s_response response;
	
	uint32 timeout_counter = 0;
	while(1)
	{
		command.command = e_commandPath_command::ID_55_APP_CMD;																																			//	CMD55: Prepare ACMD41
		command.argument = 0;
		command.dataTransfer = false;
		response = send_command(command);
		if(response.success == FAIL || response.response_31_0 != 0x00000120)
		{
			return(FAIL);
		}
		
		
		
		command.command = e_commandPath_command::ID_41_SD_SEND_OPERATION_CONDITION;																									//	ACMD41: Set Maximum Performance, SDHC and all Operating Voltages
		command.argument = 0x50FF8000;
		command.dataTransfer = false;
		response = send_command(command);
		if(response.success == OK && response.response_31_0 == 0xC0FF8000)
		{
			break;
		}
		else
		{
			if(response.success == FAIL)
			{
				return(FAIL);
			}
			timeout_counter++;
			if(timeout_counter > 1000)
			{
				return(FAIL);
			}
		}
	}
	
	return(OK);
}


feedback SDMMC_1::command_request_CID()
{
	s_commandPath command;
	s_response response;
	
	command.command = e_commandPath_command::ID_2_ALL_SEND_CID;																																		//	CMD2: Request CID from Card
	command.argument = 0;
	command.dataTransfer = false;
	response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}																											
	
	m_CID.manufacturer_ID = (uint8) ((response.response_127_96 & 0xFF000000) >> 24);
	m_CID.application_ID[0] = (char) ((response.response_127_96 & 0x00FF0000) >> 16);
	m_CID.application_ID[1] = (char) ((response.response_127_96 & 0x0000FF00) >> 8);
	m_CID.product_name[0] = (char) ((response.response_127_96 & 0x000000FF));
	m_CID.product_name[1] = (char) ((response.response_95_64 & 0xFF000000) >> 24);
	m_CID.product_name[2] = (char) ((response.response_95_64 & 0x00FF0000) >> 16);
	m_CID.product_name[3] = (char) ((response.response_95_64 & 0x0000FF00) >> 8);
	m_CID.product_name[4] = (char) ((response.response_95_64 & 0x000000FF));
	m_CID.product_revision = (uint8) (((response.response_63_32 & 0xF000000) >> 28) * 10 + ((response.response_63_32 & 0x0F000000) >> 24));
	m_CID.serial_number = ((response.response_63_32 & 0x00FFFFFF) << 8) + ((response.response_31_0 & 0xFF000000) >> 24);
	m_CID.manufacturing_year = (uint16) ((response.response_31_0 & 0x000FF000) >> 12) + 2000;
	m_CID.manufacturing_month = (uint8) ((response.response_31_0 & 0x00000F00) >> 8);
	
	return(OK);
}


feedback SDMMC_1::command_publish_newRCA()
{
	s_commandPath command;
	s_response response;
	
	command.command = e_commandPath_command::ID_3_PUBLISH_NEW_RCA;																																//	CMD3: Ask Card to publish new RCA
	command.argument = 0;
	command.dataTransfer = false;
	response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}																																																									
	m_RCA = (uint16) ((response.response_31_0 & 0xFFFF0000) >> 16);
	
	return(OK);
}


feedback SDMMC_1::command_request_CSD()
{
	s_commandPath command;
	s_response response;
	
	command.command = e_commandPath_command::ID_9_SEND_CSD;																																				//	CMD9: Request CSD from Card
	command.argument = m_RCA << 16;
	command.dataTransfer = false;
	response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}																																										
	
	if(bit::isSet(response.response_127_96, 30))
	{
		m_CSD.csd_structure = e_CSD_capacity::SDHC_SDXC;
	}
	else
	{
		m_CSD.csd_structure = e_CSD_capacity::SD;
	}
	
	for(uint32 i = 0; i < 12; i++)
	{
		if(bit::isSet(response.response_95_64, 20 + i))
		{
			m_CSD.command_classes[i] = true;
		}
		else
		{
			m_CSD.command_classes[i] = false;
		}
	}
	
	if(bit::isSet(response.response_95_64, 12))
	{
		m_CSD.driverStage_implemented = true;
	}
	else
	{
		m_CSD.driverStage_implemented = false;
	}
	
	m_CSD.userData_capacity_MByte = (((response.response_95_64 & 0x0000003F) << 16) + ((response.response_63_32 & 0xFFFF0000) >> 16)) / 2;
	
	if(bit::isSet(response.response_31_0, 14))
	{
		m_CSD.copy = true;
	}
	else
	{
		m_CSD.copy = false;
	}
	
	if(bit::isSet(response.response_31_0, 13))
	{
		m_CSD.writeProtection_permanent = true;
	}
	else
	{
		m_CSD.writeProtection_permanent = false;
	}
	
	if(bit::isSet(response.response_31_0, 12))
	{
		m_CSD.writeProtection_temporarily = true;
	}
	else
	{
		m_CSD.writeProtection_temporarily = false;
	}
	
	return(OK);
}


feedback SDMMC_1::command_cardSelect()
{
	s_commandPath command;
	s_response response;
	
	command.command = e_commandPath_command::ID_7_SELECT_DESELECT_CARD;																														//	CMD7: Select Card
	command.argument = m_RCA << 16;
	command.dataTransfer = false;
	response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}
	
	return(OK);
}


feedback SDMMC_1::command_set_busWidth()
{
	s_commandPath command;
	s_response response;
	
	command.command = e_commandPath_command::ID_55_APP_CMD;																																				//	CMD55: Prepare ACMD6
	command.argument = m_RCA << 16;
	command.dataTransfer = false;
	response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}
	
	
	
	command.command = e_commandPath_command::ID_6_SET_BUS_WIDTH;																																	//	ACMD6: Set Bus Width to 4 Lines
	command.argument = 0x00000002;
	command.dataTransfer = false;
	response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}
	
	return(OK);
}


feedback SDMMC_1::command_send_SDStatus()
{
	s_commandPath command;
	s_response response;
	s_dataPath dataPath;
	
	command.command = e_commandPath_command::ID_55_APP_CMD;																																				//	CMD55: Prepare ACMD13
	command.argument = m_RCA << 16;
	command.dataTransfer = false;
	response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}
	
	
	
	uint8* data = new uint8[c_sectorSizeInBytes];
	bit::clear(*MCU::SDMMC_1::IDMA_CTRLR, 0);																																											//	Disable IDMA
	*MCU::SDMMC_1::IDMA_BASE0R = (uint32) data;																																										//	Set IDMA Buffer Address
	bit::set(*MCU::SDMMC_1::IDMA_CTRLR, 0);																																												//	Enable IDMA
	
	
	
	dataPath.blockSize = e_dataPath_blockSize::SIZE_64_BYTE;
	dataPath.mode = e_dataPath_transferMode::BLOCK;
	dataPath.direction = e_dataPath_transferDirection::CARD_TO_HOST;
	dataPath.timeout = 0xFFFFFFFF;
	dataPath.data_sizeInBytes = 64;
	setup_dataPath(dataPath);
	command.command = e_commandPath_command::ID_13_SEND_SD_STATUS;																																//	ACMD13: Ask Card to send SD Status
	command.argument = m_RCA << 16;
	command.dataTransfer = true;
	response = send_command(command);
	
	m_SDStatus.busWidth = (e_SDStatus_busWidth) ((data[0] & 0xC0) >> 6);
	if(bit::isSet(data[0], 5))
	{
		m_SDStatus.secured_mode = true;
	}
	else
	{
		m_SDStatus.secured_mode = false;
	}
	m_SDStatus.cardType = (e_SDStatus_cardType) ((data[2] << 8) + data[3]);
	m_SDStatus.protectedArea_sizeInBytes = (data[4] << 24) + (data[5] << 16) + (data[6] << 8) + data[7];
	m_SDStatus.speedClass = (e_SDStatus_speedClass) data[8];
	m_SDStatus.performanceMove_MBps = data[9];
	
	delete[] data;
	
	return(OK);
}


CODE_RAM feedback SDMMC_1::command_read_singleBlock(uint32 block) const
{
	s_commandPath command;
	s_response response;
	s_dataPath dataPath;
	
	*MCU::SDMMC_1::IDMA_BSIZER = 512;
	dataPath.blockSize = e_dataPath_blockSize::SIZE_512_BYTE;
	dataPath.mode = e_dataPath_transferMode::BLOCK;
	dataPath.direction = e_dataPath_transferDirection::CARD_TO_HOST;
	dataPath.timeout = 0xFFFFFFFF;
	dataPath.data_sizeInBytes = 512;
	setup_dataPath(dataPath);
	command.command = e_commandPath_command::ID_17_READ_SINGLE_BLOCK;																															//	CMD17: Read Single Block
	command.argument = block;
	command.dataTransfer = true;
	response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}
	
	return(OK);
}


CODE_RAM feedback SDMMC_1::command_write_singleBlock(uint32 block) const
{
	s_commandPath command;
	s_response response;
	s_dataPath dataPath;
	
	*MCU::SDMMC_1::IDMA_BSIZER = 512;
	dataPath.blockSize = e_dataPath_blockSize::SIZE_512_BYTE;
	dataPath.mode = e_dataPath_transferMode::BLOCK;
	dataPath.direction = e_dataPath_transferDirection::HOST_TO_CARD;
	dataPath.timeout = 0xFFFFFFFF;
	dataPath.data_sizeInBytes = 512;
	setup_dataPath(dataPath);
	command.command = e_commandPath_command::ID_24_WRITE_BLOCK;																																		//	CMD24: Write Single Block
	command.argument = block;
	command.dataTransfer = true;
	response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}
	
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback SDMMC_1::init(RCC& rcc, RCC::e_clockSource_sdmmc clockSource, f_power power, f_detect detect)
{
	CMOS& cmos = CMOS::get();
	
	m_power = power;
	m_detect = detect;
	
	m_clock = 0;
	m_busWidth = e_busWidth::BUSWIDTH_1;
	m_RCA = 0;
	
	
	disable();
	cmos.sleep_ms(100);
	if(m_detect() == false)
	{
		return(FAIL);
	}
	if(enable() != OK)
	{
		return(FAIL);
	}
	cmos.sleep_ms(100);
	
	
	
	rcc.module_reset(RCC::e_module::SDMMC_1);
	if(rcc.set_clockSource(clockSource) != OK)
	{
		return(FAIL);
	}
	m_clockSource = clockSource;
	rcc.module_clockInit(RCC::e_module::SDMMC_1, true);
	
	if(set_clockSpeed(rcc, 400000) != OK)
	{
		return(FAIL);
	}
	if(set_busWidth(e_busWidth::BUSWIDTH_4) != OK)
	{
		return(FAIL);
	}
	
	*MCU::SDMMC_1::POWER = 0x00000003;																																														//	Put Power to the Card
	bit::set(*MCU::SDMMC_1::CLKCR, 17);																																														//	Enable Hardware Flow Control
	
	
	
	
	
	command_reset();
	if(command_operatingConditionValidation() == FAIL)
	{
		return(FAIL);
	}
	command_set_operatingCondition();
	command_request_CID();
	command_publish_newRCA();
	command_request_CSD();
	command_cardSelect();
	command_set_busWidth();
	command_send_SDStatus();
	set_clockSpeed(rcc, 25000000);
	
	m_changeCounter++;
	
	return(OK);
}







CODE_RAM feedback SDMMC_1::enable()
{
	if(m_power(true) != OK)
	{
		m_enabled = false;
		return(FAIL);
	}
	m_enabled = true;
	return(OK);
}


CODE_RAM feedback SDMMC_1::disable()
{
	if(m_power(false) != OK)
	{
		m_enabled = true;
		return(FAIL);
	}
	m_enabled = false;
	return(OK);
}


CODE_RAM bool SDMMC_1::detect() const
{
	if(m_detect != nullptr)
	{
		return(m_detect());
	}
	return(false);
}


CODE_RAM uint32 SDMMC_1::get_changeStamp() const
{
	return(m_changeCounter);
}


CODE_RAM uint8* SDMMC_1::read(uint32 startSector, uint32 numberOfSectors) const
{
	uint8* data = new uint8[numberOfSectors * c_sectorSizeInBytes];
	/*
	Cache& cache = CMOS::get().get_cache();																																											//	Cache Maintenance
	Thread& self = CMOS::get().get_thread();
	self.set_priviledgeLevel(Thread::e_priviledgeLevel::ADMIN);
	{
		cache.DCache_invalidate((uint32*) data, numberOfSectors * c_sectorSizeInBytes);
	}
	self.set_priviledgeLevel(Thread::e_priviledgeLevel::USER);
	*/
	
	CMOS& cmos = CMOS::get();
	while(m_semaphore.lock() != OK)
	{
		cmos.sleep_100us(1);
	}
	
	for(uint32 i = 0; i < numberOfSectors; i++)
	{
		bit::clear(*MCU::SDMMC_1::IDMA_CTRLR, 0);																																										//	Disable IDMA
		*MCU::SDMMC_1::IDMA_BASE0R = ((uint32) data) + i * c_sectorSizeInBytes;																											//	Set IDMA Buffer Address
		bit::set(*MCU::SDMMC_1::IDMA_CTRLR, 0);																																											//	Enable IDMA
		if(command_read_singleBlock(startSector + i) == FAIL)
		{
			delete[] data;
			m_semaphore.unlock();
			return(nullptr);
		}
	}
	
	m_semaphore.unlock();
	
	return(data);
}


CODE_RAM feedback SDMMC_1::read(uint32 startSector, uint32 numberOfSectors, uint8* target) const
{/*
	Cache& cache = CMOS::get().get_cache();																																											//	Cache Maintenance
	Thread& self = CMOS::get().get_thread();
	self.set_priviledgeLevel(Thread::e_priviledgeLevel::ADMIN);
	{
		cache.DCache_invalidate((uint32*) target, numberOfSectors * c_sectorSizeInBytes);
	}
	self.set_priviledgeLevel(Thread::e_priviledgeLevel::USER);
	*/
	
	CMOS& cmos = CMOS::get();
	while(m_semaphore.lock() != OK)
	{
		cmos.sleep_100us(1);
	}
	
	for(uint32 i = 0; i < numberOfSectors; i++)
	{
		bit::clear(*MCU::SDMMC_1::IDMA_CTRLR, 0);																																										//	Disable IDMA
		*MCU::SDMMC_1::IDMA_BASE0R = ((uint32) target) + i * c_sectorSizeInBytes;																										//	Set IDMA Buffer Address
		bit::set(*MCU::SDMMC_1::IDMA_CTRLR, 0);																																											//	Enable IDMA
		if(command_read_singleBlock(startSector + i) != OK)
		{
			m_semaphore.unlock();
			return(FAIL);
		}
	}
	
	m_semaphore.unlock();
	
	return(OK);
}


CODE_RAM feedback SDMMC_1::write(uint32 startSector, uint32 numberOfSectors, uint8* data) const
{/*
	Cache& cache = CMOS::get().get_cache();																																											//	Cache Maintenance
	Thread& self = CMOS::get().get_thread();
	self.set_priviledgeLevel(Thread::e_priviledgeLevel::ADMIN);
	{
		cache.DCache_clean((uint32*) data, numberOfSectors * c_sectorSizeInBytes);
	}
	self.set_priviledgeLevel(Thread::e_priviledgeLevel::USER);*/
	
	CMOS& cmos = CMOS::get();
	while(m_semaphore.lock() != OK)
	{
		cmos.sleep_100us(1);
	}
	
	for(uint32 i = 0; i < numberOfSectors; i++)
	{
		bit::clear(*MCU::SDMMC_1::IDMA_CTRLR, 0);																																										//	Disable IDMA
		*MCU::SDMMC_1::IDMA_BASE0R = ((uint32) data) + i * c_sectorSizeInBytes;																											//	Set IDMA Buffer Address
		bit::set(*MCU::SDMMC_1::IDMA_CTRLR, 0);																																											//	Enable IDMA
		if(command_write_singleBlock(startSector + i) == FAIL)
		{
			m_semaphore.unlock();
			return(FAIL);
		}
	}
	
	m_semaphore.unlock();
	
	return(OK);
}