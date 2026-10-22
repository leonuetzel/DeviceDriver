#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

uint16 SDMMC_2::m_eventID = CMOS::eventID_invalid;





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback SDMMC_2::startup()
{
	//	Event and Interrupt for the End of Commands and Data Transfers (see waitForFlags): the Interrupts are unmasked only while a Thread waits
	CMOS& cmos = CMOS::get();
	m_eventID = cmos.event_create();
	NVIC& nvic = cmos.get_nvic();
	nvic.setPriority(Interrupt::SDMMC_2, 10);
	nvic.enable(Interrupt::SDMMC_2);
	return(OK);
}







feedback SDMMC_2::set_clockSpeed(RCC& rcc, uint32 clock)
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
	
	//	SDMMC_CK = Kernel Clock / (2 x CLKDIV): the Divider is rounded up, so that the Card Clock does not exceed the requested one (RM0433, SDMMC_CLKCR)
	if(clock == 0 || clock_in == 0)
	{
		return(FAIL);
	}
	uint32 prescaler = (clock_in + clock - 1) / clock;
	if(prescaler % 2 != 0)
	{
		prescaler++;
	}
	if(prescaler / 2 > 0x000003FF)
	{
		return(FAIL);
	}
	m_clock = clock_in / prescaler;
	uint32 temp = *MCU::SDMMC_2::CLKCR & 0xFFFFFC00;
	*MCU::SDMMC_2::CLKCR = temp | (prescaler / 2);
	
	return(OK);
}


feedback SDMMC_2::set_busWidth(e_busWidth busWidth)
{
	if(m_busWidth == busWidth)
	{
		return(OK);
	}
	
	if(busWidth == e_busWidth::BUSWIDTH_8)
	{
		return(FAIL);
	}
	
	uint32 temp = *MCU::SDMMC_2::CLKCR & 0xFFFF3FFF;
	*MCU::SDMMC_2::CLKCR = temp | (((uint32) busWidth) << 14);
	
	m_busWidth = busWidth;
	return(OK);
}


SDMMC_2::s_response SDMMC_2::send_command(s_commandPath command) const
{
	s_response response;
	response.response_127_96 = 0;
	response.response_95_64 = 0;
	response.response_63_32 = 0;
	response.response_31_0 = 0;
	response.success = FAIL;
	response.timeout = false;
	
	if(((uint32) command.command & 0xFFFFFCFF) > 0x0000003F)
	{
		return(response);
	}
	
	//	Wait for the Control Path to be idle: send_command() has waited for the End of the previous Command, so this takes a few Cycles at most
	for(uint32 i = 0; bit::isSet(*MCU::SDMMC_2::STAR, 13) == true; i++)
	{
		if(i >= c_activeWaitLoops)
		{
			return(response);
		}
	}
	
	*MCU::SDMMC_2::ICR = *MCU::SDMMC_2::STAR;																																											//	Clear Flags
	*MCU::SDMMC_2::ARGR = command.argument;																																												//	Set Argument
	
	
	
	//	Send the Command: CPSMEN (Bit 12), CMDTRANS (Bit 6) for a Data Transfer, CMDSTOP (Bit 7) for CMD12, which aborts the Data Path
	uint32 cmdr = 0x00001000 | ((uint32) command.command);
	if(command.dataTransfer == true)
	{
		bit::set(cmdr, 6);
	}
	if(command.stopTransmission == true)
	{
		bit::set(cmdr, 7);
	}
	*MCU::SDMMC_2::CMDR = cmdr;
	
	//	Wait for the End of the Command: CMDSENT without a Response, otherwise CMDREND, CCRCFAIL or CTIMEOUT (after 64 Card Clock Cycles)
	waitForFlags(c_flags_commandEnd, 100);
	
	
	//	R1b (e.g. CMD7, CMD12): the Card may signal Busy on D0 after the Response, e.g. while it programs written Data
	//	The DPSM waits for its End (BUSYD0END) or the Data Timer (DTIMEOUT)
	if(command.dataTransfer == false && (((uint32) command.command) & 0x00000300) != 0 && bit::isSet(*MCU::SDMMC_2::STAR, 20) == true)
	{
		waitForFlags(c_flags_busyEnd, 1000);
	}
	
	
	//	Wait for the End of the Data Transfer: DATAEND or an Error, when writing only after the Card has programmed the Data (Busy on D0)
	//	The Data Timer (DTIMER) ends every Block that does not come in Time, so the Timeout here is only a Safety Net
	if(command.dataTransfer == true)
	{
		waitForFlags(c_flags_dataEnd, 1000 + (*MCU::SDMMC_2::DLENR / c_sectorSizeInBytes) * 250);
	}
	
	
	uint32 status = *MCU::SDMMC_2::STAR;
	response.timeout = bit::isSet(status, 2);
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
				response.response_31_0 = *MCU::SDMMC_2::RESP_1R;
				response.success = OK;
			}
			break;
			
		case 0x2:
			if(bit::isSet(status, 6))
			{
				response.response_31_0 = *MCU::SDMMC_2::RESP_1R;
				response.success = OK;
			}
			break;
			
		case 0x3:
			if(bit::isSet(status, 6))
			{
				response.response_127_96 = *MCU::SDMMC_2::RESP_1R;
				response.response_95_64 = *MCU::SDMMC_2::RESP_2R;
				response.response_63_32 = *MCU::SDMMC_2::RESP_3R;
				response.response_31_0 = *MCU::SDMMC_2::RESP_4R;
				response.success = OK;
			}
			break;
			
		default:
			break;
	}
	
	//	Errors: Data CRC (1), Data Timeout (3), Tx FIFO Underrun (4), Rx FIFO Overrun (5) and IDMA Transfer Error (27)
	if(bit::isSet(status, 1) || bit::isSet(status, 3) || bit::isSet(status, 4) || bit::isSet(status, 5) || bit::isSet(status, 27))
	{
		response.success = FAIL;
	}
	
	
	
	*MCU::SDMMC_2::ICR = status;
	return(response);
}


void SDMMC_2::setup_dataPath(s_dataPath dataPath) const
{
	*MCU::SDMMC_2::DLENR = dataPath.data_sizeInBytes;
	*MCU::SDMMC_2::DTIMER = dataPath.timeout;
	*MCU::SDMMC_2::DCTRLR = ((uint32) dataPath.blockSize << 4) | ((uint32) dataPath.mode << 2) | ((uint32) dataPath.direction << 1);
}







feedback SDMMC_2::command_reset()
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


feedback SDMMC_2::command_operatingConditionValidation(bool& version2)
{
	s_commandPath command;
	s_response response;
	
	command.command = e_commandPath_command::ID_8_SEND_IF_CONDITION;																															//	CMD8: Voltage Range 2,7V - 3,6V, Check Pattern: 0xAA
	command.argument = 0x000001AA;
	command.dataTransfer = false;
	response = send_command(command);
	
	
	//	No Answer: a Card of Version 1.x (before 2006) does not know CMD8 and stays idle - it is initialized without High Capacity
	if(response.success == FAIL && response.timeout == true)
	{
		version2 = false;
		return(OK);
	}
	
	
	//	Version 2.00 or later: the Card repeats Voltage Range and Check Pattern, otherwise it can not work with 2.7 ... 3.6 V
	if(response.success == FAIL || response.response_31_0 != command.argument)
	{
		return(FAIL);
	}
	version2 = true;
	return(OK);
}


feedback SDMMC_2::command_set_operatingCondition(bool version2)
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
		//	The Card Status (R1) has to show APP_CMD (Bit 5), the other Bits depend on the Card
		if(response.success == FAIL || bit::isCleared(response.response_31_0, 5) == true)
		{
			return(FAIL);
		}
		
		
		
		command.command = e_commandPath_command::ID_41_SD_SEND_OPERATION_CONDITION;																									//	ACMD41: Set Maximum Performance, SDHC and all Operating Voltages
		//	Version 2: HCS (Bit 30) asks for High Capacity, XPC (Bit 28) for maximum Performance - a Card of Version 1.x needs both 0
		command.argument = (version2 == true) ? 0x50FF8000 : 0x00FF8000;
		command.dataTransfer = false;
		response = send_command(command);
		//	OCR Bit 31: the Card has finished its Power-up; the Voltage Bits depend on the Card
		//	Bit 30 (CCS): 1 = SDHC/SDXC with Block Addresses, 0 = SDSC with Byte Addresses (always for Version 1.x)
		if(response.success == OK && bit::isSet(response.response_31_0, 31) == true)
		{
			m_highCapacity = (version2 == true && bit::isSet(response.response_31_0, 30) == true);
			break;
		}
		else
		{
			if(response.success == FAIL)
			{
				return(FAIL);
			}
			//	The Card may need up to 1 s for its Power-up (SD Specification, ACMD41): asked again every Millisecond, at least 1 s long
			timeout_counter++;
			if(timeout_counter > 1000)
			{
				return(FAIL);
			}
			CMOS::get().sleep_ms(1);
		}
	}
	
	return(OK);
}


feedback SDMMC_2::command_request_CID()
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
	m_CID.product_revision = (uint8) (((response.response_63_32 & 0xF0000000) >> 28) * 10 + ((response.response_63_32 & 0x0F000000) >> 24));
	m_CID.serial_number = ((response.response_63_32 & 0x00FFFFFF) << 8) + ((response.response_31_0 & 0xFF000000) >> 24);
	m_CID.manufacturing_year = (uint16) ((response.response_31_0 & 0x000FF000) >> 12) + 2000;
	m_CID.manufacturing_month = (uint8) ((response.response_31_0 & 0x00000F00) >> 8);
	
	return(OK);
}


feedback SDMMC_2::command_publish_newRCA()
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


feedback SDMMC_2::command_request_CSD()
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
	
	if(m_CSD.csd_structure == e_CSD_capacity::SDHC_SDXC)
	{
		//	CSD Version 2: C_SIZE (Bits 69:48), Capacity = (C_SIZE + 1) x 512 KiB
		m_CSD.userData_capacity_MByte = ((((response.response_95_64 & 0x0000003F) << 16) + ((response.response_63_32 & 0xFFFF0000) >> 16)) + 1) / 2;
	}
	else
	{
		//	CSD Version 1 (SDSC): Capacity = (C_SIZE + 1) x 2^(C_SIZE_MULT + 2) x 2^READ_BL_LEN Byte
		//	C_SIZE: Bits 73:62, C_SIZE_MULT: Bits 49:47, READ_BL_LEN: Bits 83:80 (SD Physical Layer Specification, CSD Version 1.0)
		const uint32 c_size = ((response.response_95_64 & 0x000003FF) << 2) | ((response.response_63_32 & 0xC0000000) >> 30);
		const uint32 c_size_mult = (response.response_63_32 & 0x00038000) >> 15;
		const uint32 read_bl_len = (response.response_95_64 & 0x000F0000) >> 16;
		const uint64 capacity = ((uint64) (c_size + 1)) << (c_size_mult + 2 + read_bl_len);
		m_CSD.userData_capacity_MByte = (uint32) (capacity >> 20);
	}
	
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


feedback SDMMC_2::command_cardSelect()
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


feedback SDMMC_2::command_set_busWidth()
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


feedback SDMMC_2::command_set_blockLength()
{
	//	SDHC/SDXC always use 512 Byte Blocks; for SDSC the Block Length of Reading and Writing is set to 512 Byte (CMD16)
	if(m_highCapacity == true)
	{
		return(OK);
	}
	
	s_commandPath command;
	command.command = e_commandPath_command::ID_16_SET_BLOCK_LENGTH;
	command.argument = c_sectorSizeInBytes;
	command.dataTransfer = false;
	const s_response response = send_command(command);
	if(response.success == FAIL)
	{
		return(FAIL);
	}
	return(OK);
}


feedback SDMMC_2::command_send_SDStatus()
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
	if(data == nullptr)
	{
		return(FAIL);
	}
	CacheMaintenance::beforeWrite(data, 64);																																											//	Cache Maintenance and Barrier: the IDMA writes 64 Byte
	bit::clear(*MCU::SDMMC_2::IDMA_CTRLR, 0);																																											//	Disable IDMA
	*MCU::SDMMC_2::IDMA_BASE0R = (uint32) data;																																										//	Set IDMA Buffer Address
	bit::set(*MCU::SDMMC_2::IDMA_CTRLR, 0);																																												//	Enable IDMA
	
	
	
	dataPath.blockSize = e_dataPath_blockSize::SIZE_64_BYTE;
	dataPath.mode = e_dataPath_transferMode::BLOCK;
	dataPath.direction = e_dataPath_transferDirection::CARD_TO_HOST;
	//	Data Timeout 500 ms in Card Clock Cycles: Reading takes at most 100 ms, Writing 250 ms (SDHC) or 500 ms (SDXC)
	dataPath.timeout = (m_clock != 0) ? m_clock / 2 : 0xFFFFFFFF;
	dataPath.data_sizeInBytes = 64;
	setup_dataPath(dataPath);
	command.command = e_commandPath_command::ID_13_SEND_SD_STATUS;																																//	ACMD13: Ask Card to send SD Status
	command.argument = m_RCA << 16;
	command.dataTransfer = true;
	response = send_command(command);
	CacheMaintenance::afterWrite(data, 64);																																												//	Cache Maintenance: the CPU reads the SD Status only after this
	if(response.success == FAIL)
	{
		delete[] data;
		return(FAIL);
	}
	
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


feedback SDMMC_2::waitForFlags(uint32 flags, uint32 timeout_ms) const
{
	//	Commands and single Blocks end within some ten Microseconds at 25 MHz: they are waited for actively first
	for(uint32 i = 0; i < c_activeWaitLoops; i++)
	{
		if((*MCU::SDMMC_2::STAR & flags) != 0)
		{
			return(OK);
		}
	}
	
	
	//	Longer Transfers (several Blocks, Programming of the Card) let other Threads run: the Interrupt of one of the Flags wakes the Thread up
	//	The Thread listens to the Event before the Interrupt is unmasked, so it cannot miss it. IDMATE has no Interrupt Enable (RM0433, SDMMC_MASKR)
	CMOS& cmos = CMOS::get();
	cmos.event_subscribe(m_eventID);
	cmos.event_listen(m_eventID);
	*MCU::SDMMC_2::MASKR = flags & ~(1u << 27);
	cmos.sleep_untilEvent(m_eventID, timeout_ms);
	*MCU::SDMMC_2::MASKR = 0;
	cmos.event_unsubscribe(m_eventID);
	if((*MCU::SDMMC_2::STAR & flags) != 0)
	{
		return(OK);
	}
	return(FAIL);
}


feedback SDMMC_2::command_read_blocks(uint32 block, uint32 numberOfBlocks) const
{
	//	One Block with CMD17, several with CMD18 as an open-ended Multiple Block Read that CMD12 ends after DATAEND (RM0433, CMD12 use cases)
	//	The IDMA writes the Blocks one after another from IDMA_BASE0R on (single Buffer Mode, set up by the Caller)
	if(numberOfBlocks == 0 || numberOfBlocks > c_maximumBlocksPerCommand)
	{
		return(FAIL);
	}
	const bool multipleBlocks = (numberOfBlocks > 1);
	
	s_dataPath dataPath;
	dataPath.blockSize = e_dataPath_blockSize::SIZE_512_BYTE;
	dataPath.mode = (multipleBlocks == true) ? e_dataPath_transferMode::BLOCK_WITH_STOP : e_dataPath_transferMode::BLOCK;
	dataPath.direction = e_dataPath_transferDirection::CARD_TO_HOST;
	//	Data Timeout 500 ms in Card Clock Cycles, per Block: Reading takes at most 100 ms, Writing 250 ms (SDHC) or 500 ms (SDXC)
	dataPath.timeout = (m_clock != 0) ? m_clock / 2 : 0xFFFFFFFF;
	dataPath.data_sizeInBytes = numberOfBlocks * c_sectorSizeInBytes;
	setup_dataPath(dataPath);
	
	s_commandPath command;
	command.command = (multipleBlocks == true) ? e_commandPath_command::ID_18_READ_MULITPLE_BLOCK : e_commandPath_command::ID_17_READ_SINGLE_BLOCK;
	//	SDHC/SDXC count Blocks, SDSC Bytes
	command.argument = (m_highCapacity == true) ? block : block * c_sectorSizeInBytes;
	command.dataTransfer = true;
	feedback result = send_command(command).success;
	
	
	//	CMD12 also after an Error: it aborts the Transfer, the Card returns to the Transfer State
	if(multipleBlocks == true && command_stopTransmission() != OK)
	{
		result = FAIL;
	}
	return(result);
}


feedback SDMMC_2::command_write_blocks(uint32 block, uint32 numberOfBlocks) const
{
	//	One Block with CMD24, several with CMD25 as an open-ended Multiple Block Write that CMD12 ends after DATAEND (RM0433, CMD12 use cases)
	//	The IDMA reads the Blocks one after another from IDMA_BASE0R on (single Buffer Mode, set up by the Caller)
	if(numberOfBlocks == 0 || numberOfBlocks > c_maximumBlocksPerCommand)
	{
		return(FAIL);
	}
	const bool multipleBlocks = (numberOfBlocks > 1);
	
	s_dataPath dataPath;
	dataPath.blockSize = e_dataPath_blockSize::SIZE_512_BYTE;
	dataPath.mode = (multipleBlocks == true) ? e_dataPath_transferMode::BLOCK_WITH_STOP : e_dataPath_transferMode::BLOCK;
	dataPath.direction = e_dataPath_transferDirection::HOST_TO_CARD;
	//	Data Timeout 500 ms in Card Clock Cycles, per Block: Reading takes at most 100 ms, Writing 250 ms (SDHC) or 500 ms (SDXC)
	dataPath.timeout = (m_clock != 0) ? m_clock / 2 : 0xFFFFFFFF;
	dataPath.data_sizeInBytes = numberOfBlocks * c_sectorSizeInBytes;
	setup_dataPath(dataPath);
	
	s_commandPath command;
	command.command = (multipleBlocks == true) ? e_commandPath_command::ID_25_WRITE_MULTIPLE_BLOCK : e_commandPath_command::ID_24_WRITE_BLOCK;
	//	SDHC/SDXC count Blocks, SDSC Bytes
	command.argument = (m_highCapacity == true) ? block : block * c_sectorSizeInBytes;
	command.dataTransfer = true;
	feedback result = send_command(command).success;
	
	
	//	CMD12 also after an Error: it aborts the Transfer; the Card programs the last Block meanwhile (Busy on D0, see send_command)
	if(multipleBlocks == true && command_stopTransmission() != OK)
	{
		result = FAIL;
	}
	return(result);
}


feedback SDMMC_2::command_stopTransmission() const
{
	//	CMD12 with CMDSTOP: the CPSM signals the Abort to the DPSM, the Card leaves the Data State (RM0433, Block operation and CMD12)
	s_commandPath command;
	command.command = e_commandPath_command::ID_12_STOP_TRANSMISSION;
	command.argument = 0;
	command.dataTransfer = false;
	command.stopTransmission = true;
	return(send_command(command).success);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback SDMMC_2::initCard(RCC& rcc)
{
	//	Supply off and on, then identify and configure the Card from the Start - after disable() it has lost its State
	CMOS& cmos = CMOS::get();
	
	m_clock = 0;
	m_busWidth = e_busWidth::BUSWIDTH_1;
	m_RCA = 0;
	m_highCapacity = false;
	
	
	disable();
	cmos.sleep_ms(100);
	if(m_detect() == false)
	{
		return(FAIL);
	}
	if(m_power(true) != OK)
	{
		return(FAIL);
	}
	cmos.sleep_ms(100);
	
	
	
	rcc.module_reset(RCC::e_module::SDMMC_2);
	if(rcc.set_clockSource(m_clockSource) != OK)
	{
		return(FAIL);
	}
	rcc.module_clockInit(RCC::e_module::SDMMC_2, true);
	
	if(set_clockSpeed(rcc, 400000) != OK)
	{
		return(FAIL);
	}
	if(set_busWidth(e_busWidth::BUSWIDTH_4) != OK)
	{
		return(FAIL);
	}
	
	*MCU::SDMMC_2::POWER = 0x00000003;																																														//	Put Power to the Card
	bit::set(*MCU::SDMMC_2::CLKCR, 17);																																														//	Enable Hardware Flow Control
	
	
	
	
	
	//	Identification and Configuration of the Card: every Step has to succeed
	//	Version 2.00 and later (SDSC, SDHC, SDXC) answer CMD8, Version 1.x (SDSC before 2006) does not
	bool version2 = false;
	if(command_reset() != OK || command_operatingConditionValidation(version2) != OK || command_set_operatingCondition(version2) != OK)
	{
		return(FAIL);
	}
	if(command_request_CID() != OK || command_publish_newRCA() != OK || command_request_CSD() != OK)
	{
		return(FAIL);
	}
	if(command_cardSelect() != OK || command_set_busWidth() != OK || command_set_blockLength() != OK)
	{
		return(FAIL);
	}
	
	
	//	The SD Status (Bus Width, Speed Class, ...) is only informative: if it cannot be read, m_SDStatus keeps its Values
	command_send_SDStatus();
	if(set_clockSpeed(rcc, 25000000) != OK)
	{
		return(FAIL);
	}
	
	m_changeCounter++;
	m_enabled = true;
	
	return(OK);
}







feedback SDMMC_2::init(RCC& rcc, RCC::e_clockSource_sdmmc clockSource, f_power power, f_detect detect)
{
	if(power == nullptr || detect == nullptr)
	{
		return(FAIL);
	}
	m_power = power;
	m_detect = detect;
	m_clockSource = clockSource;
	
	
	return(initCard(rcc));
}







feedback SDMMC_2::enable()
{
	//	I_Drive: enable() switches the Medium on including its Initialization (CMOS, e.g. the Constructor of MasterBootRecord, reads
	//	right afterwards). The Card is ready since init() or the last enable() - after disable() it had no Supply and is initialized again
	if(m_power == nullptr)
	{
		return(FAIL);
	}
	if(m_enabled == true)
	{
		return(OK);
	}
	return(initCard(STM32H753BIT6::get().get_rcc()));
}


feedback SDMMC_2::disable()
{
	if(m_power == nullptr || m_power(false) != OK)
	{
		m_enabled = true;
		return(FAIL);
	}
	m_enabled = false;
	return(OK);
}


bool SDMMC_2::detect() const
{
	if(m_detect != nullptr)
	{
		return(m_detect());
	}
	return(false);
}


uint32 SDMMC_2::get_changeStamp() const
{
	return(m_changeCounter);
}


uint8* SDMMC_2::read(uint32 startSector, uint32 numberOfSectors) const
{
	uint8* data = new uint8[numberOfSectors * c_sectorSizeInBytes];
	if(data == nullptr)
	{
		return(nullptr);
	}
	
	
	//	The Heap has to lie in Memory the IDMA of SDMMC_2 reaches (the Linker Script Template places it in the AXI SRAM)
	if(CacheMaintenance::isReachableBySDMMC_2(data, numberOfSectors * c_sectorSizeInBytes) == false)
	{
		delete[] data;
		return(nullptr);
	}
	
	CMOS& cmos = CMOS::get();
	while(m_mutex.lock() != OK)
	{
		cmos.sleep_ms(1);
	}
	
	
	//	Cache Maintenance and Barrier: the IDMA writes the Buffer (see cacheMaintenance.hpp)
	CacheMaintenance::beforeWrite(data, numberOfSectors * c_sectorSizeInBytes);
	
	//	Several Sectors with one Command (see command_read_blocks and command_write_blocks)
	for(uint32 i = 0; i < numberOfSectors; i += c_maximumBlocksPerCommand)
	{
		const uint32 numberOfBlocks = (numberOfSectors - i < c_maximumBlocksPerCommand) ? numberOfSectors - i : c_maximumBlocksPerCommand;
		bit::clear(*MCU::SDMMC_2::IDMA_CTRLR, 0);																																										//	Disable IDMA
		*MCU::SDMMC_2::IDMA_BASE0R = ((uint32) data) + i * c_sectorSizeInBytes;																											//	Set IDMA Buffer Address
		bit::set(*MCU::SDMMC_2::IDMA_CTRLR, 0);																																											//	Enable IDMA
		if(command_read_blocks(startSector + i, numberOfBlocks) == FAIL)
		{
			CacheMaintenance::afterWrite(data, numberOfSectors * c_sectorSizeInBytes);
			delete[] data;
			m_mutex.unlock();
			return(nullptr);
		}
	}
	
	//	Cache Maintenance: the CPU reads the Buffer only after this
	CacheMaintenance::afterWrite(data, numberOfSectors * c_sectorSizeInBytes);
	
	m_mutex.unlock();
	
	return(data);
}


feedback SDMMC_2::read(uint32 startSector, uint32 numberOfSectors, uint8* target) const
{
	//	The IDMA works with Words: the Buffer Address must be word aligned (RM0433, SDMMC_IDMABASE0R)
	if(((uint32) target & 0x00000003) != 0)
	{
		return(FAIL);
	}
	
	
	//	The IDMA of SDMMC_2 has to reach the Buffer (see cacheMaintenance.hpp): not in the DTCM or ITCM
	if(CacheMaintenance::isReachableBySDMMC_2(target, numberOfSectors * c_sectorSizeInBytes) == false)
	{
		return(FAIL);
	}


	
	CMOS& cmos = CMOS::get();
	while(m_mutex.lock() != OK)
	{
		cmos.sleep_ms(1);
	}
	
	
	//	Cache Maintenance and Barrier: the IDMA writes the Buffer (see cacheMaintenance.hpp)
	CacheMaintenance::beforeWrite(target, numberOfSectors * c_sectorSizeInBytes);
	
	//	Several Sectors with one Command (see command_read_blocks and command_write_blocks)
	for(uint32 i = 0; i < numberOfSectors; i += c_maximumBlocksPerCommand)
	{
		const uint32 numberOfBlocks = (numberOfSectors - i < c_maximumBlocksPerCommand) ? numberOfSectors - i : c_maximumBlocksPerCommand;
		bit::clear(*MCU::SDMMC_2::IDMA_CTRLR, 0);																																										//	Disable IDMA
		*MCU::SDMMC_2::IDMA_BASE0R = ((uint32) target) + i * c_sectorSizeInBytes;																										//	Set IDMA Buffer Address
		bit::set(*MCU::SDMMC_2::IDMA_CTRLR, 0);																																											//	Enable IDMA
		if(command_read_blocks(startSector + i, numberOfBlocks) != OK)
		{
			CacheMaintenance::afterWrite(target, numberOfSectors * c_sectorSizeInBytes);
			m_mutex.unlock();
			return(FAIL);
		}
	}
	
	//	Cache Maintenance: the CPU reads the Buffer only after this
	CacheMaintenance::afterWrite(target, numberOfSectors * c_sectorSizeInBytes);
	
	m_mutex.unlock();
	
	return(OK);
}


feedback SDMMC_2::write(uint32 startSector, uint32 numberOfSectors, uint8* data) const
{
	//	The IDMA works with Words: the Buffer Address must be word aligned (RM0433, SDMMC_IDMABASE0R)
	if(((uint32) data & 0x00000003) != 0)
	{
		return(FAIL);
	}
	
	
	//	The IDMA of SDMMC_2 has to reach the Buffer (see cacheMaintenance.hpp): not in the DTCM or ITCM
	if(CacheMaintenance::isReachableBySDMMC_2(data, numberOfSectors * c_sectorSizeInBytes) == false)
	{
		return(FAIL);
	}


	
	CMOS& cmos = CMOS::get();
	while(m_mutex.lock() != OK)
	{
		cmos.sleep_ms(1);
	}
	
	
	//	Cache Maintenance and Barrier: the IDMA reads the Data written by the CPU (see cacheMaintenance.hpp)
	CacheMaintenance::beforeRead(data, numberOfSectors * c_sectorSizeInBytes);
	
	//	Several Sectors with one Command (see command_read_blocks and command_write_blocks)
	for(uint32 i = 0; i < numberOfSectors; i += c_maximumBlocksPerCommand)
	{
		const uint32 numberOfBlocks = (numberOfSectors - i < c_maximumBlocksPerCommand) ? numberOfSectors - i : c_maximumBlocksPerCommand;
		bit::clear(*MCU::SDMMC_2::IDMA_CTRLR, 0);																																										//	Disable IDMA
		*MCU::SDMMC_2::IDMA_BASE0R = ((uint32) data) + i * c_sectorSizeInBytes;																											//	Set IDMA Buffer Address
		bit::set(*MCU::SDMMC_2::IDMA_CTRLR, 0);																																											//	Enable IDMA
		if(command_write_blocks(startSector + i, numberOfBlocks) == FAIL)
		{
			m_mutex.unlock();
			return(FAIL);
		}
	}
	
	m_mutex.unlock();
	
	return(OK);
}








CODE_RAM void ISR_SDMMC_2()
{
	//	The waiting Thread evaluates the Flags itself (see waitForFlags): the Interrupts are masked again and the Thread is woken up
	*MCU::SDMMC_2::MASKR = 0;
	CMOS::get().event_emit(SDMMC_2::m_eventID);
}
