#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void EthernetMAC::manager()
{
	//	Subscribe to all necessary Events
	CMOS& cmos = CMOS::get();
	cmos.event_subscribe(m_eventID_frameReceived);
	cmos.event_listen(m_eventID_frameReceived);
	
	
	//	State Machine
	bool isInitialized = false;
	uint32 nextRxDescriptorIndexBeforeSleep = 0;
	while(1)
	{
		if(isInitialized == false)
		{
			//	Init the EthernetMAC Block
			if(init() != OK)
			{
				reset();
				return;
			}
			
			
			//	Wait for a PHY Link to be established, so that we can read the Duplex Mode and Speed from the PHY
			m_phy->readAllRegisters();
			while(m_phy->isLinkUp() == false)
			{
				if(m_shutdownRequested == true)
				{
					reset();
					return;
				}
				cmos.sleep_ms(50);
				m_phy->readAllRegisters();
			}
			
			
			//	Set Duplex Mode
			{
				const EthernetPHY::e_duplexMode duplexMode = m_phy->getDuplexMode();
				if(duplexMode == EthernetPHY::e_duplexMode::HALF)
				{
					bit::clear(*MCU::ETHERNET::MAC::CR, 11);
				}
				else
				{
					bit::set(*MCU::ETHERNET::MAC::CR, 11);
				}
			}
			
			
			//	Set EthernetMAC Speed
			{
				const EthernetPHY::e_speed speed = m_phy->getSpeed();
				if(speed != EthernetPHY::e_speed::_100M && speed != EthernetPHY::e_speed::_10M)
				{
					reset();
					return;
				}
				if(speed == EthernetPHY::e_speed::_10M)
				{
					bit::clear(*MCU::ETHERNET::MAC::CR, 14);
				}
				else
				{
					bit::set(*MCU::ETHERNET::MAC::CR, 14);
				}
			}
			
			
			//	Test: Receive all Frames
			//bit::set(*MCU::ETHERNET::MAC::FFR, 31);
			
			
			//	Set the MAC Address
			*MCU::ETHERNET::MAC::A0HR = (m_macAddress[5] <<  8) | (m_macAddress[4]);
			*MCU::ETHERNET::MAC::A0LR = (m_macAddress[3] << 24) | (m_macAddress[2] << 16) | (m_macAddress[1] << 8) | (m_macAddress[0]);
			
			
			//	Enable the MAC
			bit::set(*MCU::ETHERNET::MAC::CR, 3);
			bit::set(*MCU::ETHERNET::MAC::CR, 2);
			
			
			//	Start the EthernetMAC Tx and Rx DMA
			bit::set(*MCU::ETHERNET::DMA::OMR, 13);
			bit::set(*MCU::ETHERNET::DMA::OMR, 1);
			
			
			//	Create a new Network and attach it to the CMOS Network Stack
			Network* network = new Network(*this);
			network->attach();
			m_network = network;
			
			
			isInitialized = true;
		}
		
		
		constexpr uint32 timeout_ms = 100;
		const uint16 eventID = cmos.sleep_untilEvent(timeout_ms);
		
		
		//	Timeout - that means there was no Frame-Received Event - check Link Status
		if(eventID == CMOS::eventID_invalid)
		{
			m_phy->readAllRegisters();
			if(m_phy->isLinkUp() == false)
			{
				reset();
				m_network->detach();
				delete m_network;
				m_network = nullptr;
				isInitialized = false;
				continue;
			}
		}
		
		
		//	Shutdown Request
		if(m_shutdownRequested == true)
		{
			reset();
			return;
		}
		
		
		//	Frame received
		if(eventID == m_eventID_frameReceived)
		{
			while(1)
			{
				//	Calculate the next Rx Descriptor Index and the Number of Descriptors that have been updated
				const uint32 nextRxDescriptorIndexAfterSleep = (*MCU::ETHERNET::DMA::CHRDR - *MCU::ETHERNET::DMA::RDLAR) / sizeof(EthernetDMA_RxDescriptor);
				const uint32 numberOfUpdatedRxDescriptors = ((nextRxDescriptorIndexAfterSleep + m_numberOfRxDescriptors) - nextRxDescriptorIndexBeforeSleep) % m_numberOfRxDescriptors;
				
				
				//	Process all updated Rx Descriptors
				while(nextRxDescriptorIndexBeforeSleep != nextRxDescriptorIndexAfterSleep)
				{
					EthernetDMA_RxDescriptor& descriptor = m_rxDescriptors[nextRxDescriptorIndexBeforeSleep];
					
					
					//	1.	Check if the Descriptor is owned by the CPU
					if(descriptor.isOwnedByDMA() == true)
					{
						nextRxDescriptorIndexBeforeSleep = (nextRxDescriptorIndexBeforeSleep + 1) % m_numberOfRxDescriptors;
						continue;
					}
					
					
					//	2.	Check for Errors and if the Descriptor is the first Descriptor of a Frame
					if(descriptor.errorDescriptor() == true || descriptor.errorSummary() == true || descriptor.isFirstDescriptorOfFrame() == false)
					{
						//	There are Errors in the Frame or this Descriptor isnt the first Descriptor of a Frame - discard it
						descriptor.resetStatusBits();
						descriptor.setOwnershipToDMA();
						nextRxDescriptorIndexBeforeSleep = (nextRxDescriptorIndexBeforeSleep + 1) % m_numberOfRxDescriptors;
						continue;
					}
					
					
					//	3.	Find the corresponding last Descriptor of that Frame
					uint32 lastDescriptorIndex = m_numberOfRxDescriptors;
					for(uint32 j = 0; j < numberOfUpdatedRxDescriptors; j++)
					{
						const uint32 index = (nextRxDescriptorIndexBeforeSleep + j) % m_numberOfRxDescriptors;
						EthernetDMA_RxDescriptor& lastDescriptor = m_rxDescriptors[index];
						if(lastDescriptor.isLastDescriptorOfFrame() == true)
						{
							//	Found the last Descriptor of the Frame
							lastDescriptorIndex = index;
							break;
						}
					}
					if(lastDescriptorIndex == m_numberOfRxDescriptors)
					{
						//	No last Descriptor found - discard the Frame
						descriptor.resetStatusBits();
						descriptor.setOwnershipToDMA();
						nextRxDescriptorIndexBeforeSleep = (nextRxDescriptorIndexBeforeSleep + 1) % m_numberOfRxDescriptors;
						continue;
					}
					
					
					//	4.	Count the Number of Descriptors that are Part of the Frame
					const uint32 numberOfDescriptors = (((lastDescriptorIndex + m_numberOfRxDescriptors) - nextRxDescriptorIndexBeforeSleep) % m_numberOfRxDescriptors) + 1;
					
					
					//	5. Check all Descriptors for Errors
					bool frameError = false;
					for(uint32 j = 0; j < numberOfDescriptors; j++)
					{
						const uint32 index = (nextRxDescriptorIndexBeforeSleep + j) % m_numberOfRxDescriptors;
						EthernetDMA_RxDescriptor& currentDescriptor = m_rxDescriptors[index];
						
						if(currentDescriptor.errorDescriptor() == true || currentDescriptor.errorSummary() == true)
						{
							frameError = true;
							
							
							//	There are Errors in the Frame - release all Descriptors that are Part of the Frame
							for(uint32 k = 0; k < numberOfDescriptors; k++)
							{
								const uint32 index = (nextRxDescriptorIndexBeforeSleep + k) % m_numberOfRxDescriptors;
								EthernetDMA_RxDescriptor& descriptor = m_rxDescriptors[index];
								
								descriptor.resetStatusBits();
								descriptor.setOwnershipToDMA();
							}
							break;
						}
					}
					if(frameError == true)
					{
						nextRxDescriptorIndexBeforeSleep = (nextRxDescriptorIndexBeforeSleep + numberOfDescriptors) % m_numberOfRxDescriptors;
						continue;
					}
					
					
					//	6.	Read the Length of the whole Frame from the last Descriptor
					const uint32 frameLength = m_rxDescriptors[lastDescriptorIndex].getFrameLength();
					
					
					//	7.	Collect the Frame Data from all Descriptors
					Array<uint8> frame(0, frameLength);
					uint32 bytesCollected = 0;
					for(uint32 j = 0; j < numberOfDescriptors; j++)
					{
						const uint32 index = (nextRxDescriptorIndexBeforeSleep + j) % m_numberOfRxDescriptors;
						EthernetDMA_RxDescriptor& currentDescriptor = m_rxDescriptors[index];
						
						const uint8* frameBuffer = currentDescriptor.getBuffer1Address();
						const uint32 frameBufferLength = currentDescriptor.getFrameLength();
						
						for(uint32 k = 0; k < frameBufferLength; k++)
						{
							frame[bytesCollected + k] = frameBuffer[k];
						}
						bytesCollected = frameBufferLength;
					}
					
					
					//	8.	Process the Frame in the Network Stack
					m_network->handlePacket(frame);
					
					
					//	9.	Release all Descriptors
					for(uint32 j = 0; j < numberOfDescriptors; j++)
					{
						const uint32 index = (nextRxDescriptorIndexBeforeSleep + j) % m_numberOfRxDescriptors;
						EthernetDMA_RxDescriptor& currentDescriptor = m_rxDescriptors[index];
						
						currentDescriptor.resetStatusBits();
						currentDescriptor.setOwnershipToDMA();
					}
					
					
					//	10.	Calculate the next Descriptor Index
					nextRxDescriptorIndexBeforeSleep = (nextRxDescriptorIndexBeforeSleep + numberOfDescriptors) % m_numberOfRxDescriptors;
				}
				
				
				//	Check for new Frames from the DMA while we were processing the previous Frames (if there are some, we possibly missed the Event Wakeup from the DMA)
				//	Quit this while Loop if there are no new Frames to get woken up by the next Event
				const uint32 nextRxDescriptorIndexBeforeSleepNew = (*MCU::ETHERNET::DMA::CHRDR - *MCU::ETHERNET::DMA::RDLAR) / sizeof(EthernetDMA_RxDescriptor);
				if(nextRxDescriptorIndexBeforeSleep == nextRxDescriptorIndexBeforeSleepNew)
				{
					break;
				}
			}
		}
	}
}







feedback EthernetMAC::init()
{
	//	Reset the EthernetMAC Block
	RCC& rcc = STM32F107RCT6::get().get_rcc();
	rcc.module_reset(RCC::e_module::ETHERNET_MAC);
	
	
	//	Enable the Clocks of the EthernetMAC Block
	rcc.module_clockInit(RCC::e_module::ETHERNET_MAC,	true);
	rcc.module_clockInit(RCC::e_module::ETHERNET_TX,	true);
	rcc.module_clockInit(RCC::e_module::ETHERNET_RX,	true);
	
	
	//	Allocate DMA Descriptors
	m_txDescriptors = new EthernetDMA_TxDescriptor[m_numberOfTxDescriptors];
	if(m_txDescriptors == nullptr)
	{
		return(FAIL);
	}
	m_rxDescriptors = new EthernetDMA_RxDescriptor[m_numberOfRxDescriptors];
	if(m_rxDescriptors == nullptr)
	{
		delete[] m_txDescriptors;
		return(FAIL);
	}
	
	
	//	Allocate the Frame Buffers for the Rx Descriptors (not for the Tx Descriptors, because the Tx Buffers are provided by the Application)
	uint8* rxFrameBuffers = new uint8[m_numberOfRxDescriptors * m_rxFrameBufferSize];
	if(rxFrameBuffers == nullptr)
	{
		delete[] m_rxDescriptors;
		delete[] m_txDescriptors;
		return(FAIL);
	}
	
	
	//	Set up the DMA Rx Descriptors
	for(uint32 i = 0; i < m_numberOfRxDescriptors; i++)
	{
		bool isFinalDescriptor = false;
		if(i == (uint32) (m_numberOfRxDescriptors - 1))
		{
			isFinalDescriptor = true;
		}
		
		
		EthernetDMA_RxDescriptor& descriptor = m_rxDescriptors[i];
		
		descriptor.setOwnershipToDMA();
		descriptor.disableInterruptOnCompletion(false);
		
		descriptor.finalDescriptorOfDescriptorList(isFinalDescriptor);
		descriptor.secondAddressChained(false);
		
		descriptor.setBuffer1Address((uint32) &rxFrameBuffers[i * m_rxFrameBufferSize]);
		descriptor.setBuffer1Size(m_rxFrameBufferSize);
		descriptor.setBuffer2Address(0);
		descriptor.setBuffer2Size(0);
	}
	
	
	//	Set up the DMA Tx Descriptors
	for(uint32 i = 0; i < m_numberOfTxDescriptors; i++)
	{
		bool isFinalDescriptor = false;
		if(i == (uint32) (m_numberOfTxDescriptors - 1))
		{
			isFinalDescriptor = true;
		}
		
		
		EthernetDMA_TxDescriptor& descriptor = m_txDescriptors[i];
		
		descriptor.setOwnershipToCPU();
		descriptor.interruptOnCompletion(false);
		
		descriptor.finalDescriptorOfDescriptorList(isFinalDescriptor);
		descriptor.automaticallyGenerateCRC(false);
		descriptor.automaticallyPadPackets(false);
		descriptor.transmitTimeStampsIEEE1588(false);
		descriptor.setCheckSumInsertionControl(EthernetDMA_TxDescriptor::e_checkSumInsertionControl::DISABLED);
		descriptor.secondAddressChained(false);
	}
	
	
	//	Tell the EthernetMAC DMA where the Descriptors are located
	*MCU::ETHERNET::DMA::TDLAR = (uint32) m_txDescriptors;
	*MCU::ETHERNET::DMA::RDLAR = (uint32) m_rxDescriptors;
	
	
	//	Disable dropping Frames with CRC Erros detected in the Rx CRC Offload Engine
	bit::set(*MCU::ETHERNET::DMA::OMR, 26);
	
	
	//	Store-and-Forward Mode (means, that the DMA will only start to transfer the Frame from/to the MAC when the complete Frame is received/sent)
	bit::set(*MCU::ETHERNET::DMA::OMR, 21);
	bit::set(*MCU::ETHERNET::DMA::OMR, 25);
	
	
	//	Enable the normal Receive Interrupts
	bit::set(*MCU::ETHERNET::DMA::IER, 6);
	bit::set(*MCU::ETHERNET::DMA::IER, 16);
	
	
	NVIC& nvic = CMOS::get().get_nvic();
	nvic.setPriority(Interrupt::ETHERNET, 8);
	nvic.enable(Interrupt::ETHERNET);
	
	
	return(OK);
}


void EthernetMAC::reset()
{
	if(m_rxDescriptors != nullptr)
	{
		const uint8* rxFrameBuffer = m_rxDescriptors[0].getBuffer1Address();
		delete[] rxFrameBuffer;
		delete[] m_rxDescriptors;
	}
	if(m_txDescriptors != nullptr)
	{
		for(uint8 i = 0; i < m_numberOfTxDescriptors; i++)
		{
			const uint8* txFrameBuffer1 = m_txDescriptors[i].getBuffer1Address();
			if(txFrameBuffer1 != nullptr)
			{
				delete[] txFrameBuffer1;
			}
			
			
			const uint8* txFrameBuffer2 = m_txDescriptors[i].getBuffer2Address();
			if(txFrameBuffer2 != nullptr)
			{
				delete[] txFrameBuffer2;
			}
		}
		delete[] m_txDescriptors;
	}
	
	
	//	Disable Interrupts
	NVIC& nvic = CMOS::get().get_nvic();
	nvic.disable(Interrupt::ETHERNET);
	
	
	//	Disable the EthernetMAC DMA
	bit::clear(*MCU::ETHERNET::DMA::OMR, 1);
	bit::clear(*MCU::ETHERNET::DMA::OMR, 13);
	
	
	//	Disable the MAC
	bit::clear(*MCU::ETHERNET::MAC::CR, 2);
	bit::clear(*MCU::ETHERNET::MAC::CR, 3);
	
	
	//	Disable the Clocks of the EthernetMAC Block
	RCC& rcc = STM32F107RCT6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::ETHERNET_MAC,	false);
	rcc.module_clockInit(RCC::e_module::ETHERNET_TX,	false);
	rcc.module_clockInit(RCC::e_module::ETHERNET_RX,	false);
	
	
	//	Reset all Variables to their default values
	m_initialized = false;
	m_phy = nullptr;
	m_phyAddress = 0;
	m_macAddress.erase();
	m_numberOfRxDescriptors = 0;
	m_numberOfTxDescriptors = 0;
	m_rxFrameBufferSize = 0;
	m_rxDescriptors = nullptr;
	m_txDescriptors = nullptr;
	m_network = nullptr;
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback EthernetMAC::init(EthernetPHY& phy, uint8 phyAddress, const Array<uint8>& macAddress, uint8 numberOfTxDescriptors, uint8 numberOfRxDescriptors, uint32 rxFrameBufferSize)
{
	//	Check that the EthernetMAC is not already initialized
	if(m_initialized == true)
	{
		return(FAIL);
	}
	if(m_numberOfRxDescriptors != 0 || m_numberOfTxDescriptors != 0)
	{
		return(FAIL);
	}
	if(m_rxDescriptors != nullptr || m_txDescriptors != nullptr)
	{
		return(FAIL);
	}
	if(m_phyAddress != 0)
	{
		return(FAIL);
	}
	
	
	//	Store the Parameters
	m_phy = &phy;
	m_phyAddress = phyAddress;
	m_macAddress = macAddress;
	m_numberOfRxDescriptors = numberOfRxDescriptors;
	m_numberOfTxDescriptors = numberOfTxDescriptors;
	m_rxFrameBufferSize = rxFrameBufferSize;
	
	
	
	//	Start Thread to supervise the PHY
	m_threadID = CMOS::get().thread_create(&EthernetMAC::manager, this, "EthernetMAC Manager", 200, 2048);
	if(m_threadID == CMOS::threadID_invalid)
	{
		return(FAIL);
	}
	return(OK);
}


void EthernetMAC::deinit()
{
	//	Request Shutdown
	m_shutdownRequested = true;
	
	
	//	Wait for the Manager to reset the EthernetMAC Block and return
	CMOS& cmos = CMOS::get();
	while(cmos.thread_doesExist(m_threadID) == true)
	{
		cmos.sleep_ms(1);
	}
	
	
	//	Invalidate the Thread ID
	m_threadID = CMOS::threadID_invalid;
}


Network& EthernetMAC::get_network() const
{
	return(*m_network);
}







feedback EthernetMAC::writeRegister(uint16 address, uint16 data)
{
	//	Read the AHB Bus Clock from the RCC to set the MDC Clock properly
	const uint32 clock = STM32F107RCT6::get().get_rcc().get_clock_ahb();
	if(clock < 20000000 || clock > 72000000)
	{
		return(FAIL);
	}
	
	uint8 clockRangeBits = 0;
	if(clock >= 20000000 && clock < 35000000)
	{
		clockRangeBits = 0x2;
	}
	if(clock >= 35000000 && clock < 60000000)
	{
		clockRangeBits = 0x3;
	}
	if(clock >= 60000000 && clock <= 72000000)
	{
		clockRangeBits = 0x0;
	}
	
	
	//	Wait for the BUSY Bit to be cleared by Hardware
	while(bit::isSet(*MCU::ETHERNET::MAC::MII_AR, 0) == true)
	{
		CMOS::get().sleep_ms(1);
	}
	
	
	//	Write the Data to be written into the Data Register
	*MCU::ETHERNET::MAC::MII_DR = data;
	
	
	//	Write the Address of the Register to be written to and start the Write Operation
	*MCU::ETHERNET::MAC::MII_AR = (m_phyAddress << 11) | (address << 6) | (clockRangeBits << 2) | 0x03;
	
	
	//	Wait for Busy Flag to clear - this is done by the MAC after the Write Operation is completed
	while(bit::isSet(*MCU::ETHERNET::MAC::MII_AR, 0) == true)
	{
		CMOS::get().sleep_ms(1);
	}
	
	
	return(OK);
}


uint16 EthernetMAC::readRegister(uint16 address)
{
	//	Read the AHB Bus Clock from the RCC to set the MDC Clock properly
	const uint32 clock = STM32F107RCT6::get().get_rcc().get_clock_ahb();
	if(clock < 20000000 || clock > 72000000)
	{
		return(FAIL);
	}
	
	uint8 clockRangeBits = 0;
	if(clock >= 20000000 && clock < 35000000)
	{
		clockRangeBits = 0x2;
	}
	if(clock >= 35000000 && clock < 60000000)
	{
		clockRangeBits = 0x3;
	}
	if(clock >= 60000000 && clock <= 72000000)
	{
		clockRangeBits = 0x0;
	}
	
	
	//	Wait for the BUSY Bit to be cleared by Hardware
	while(bit::isSet(*MCU::ETHERNET::MAC::MII_AR, 0) == true)
	{
		CMOS::get().sleep_ms(1);
	}
	
	
	//	Write the Address of the Register to be read and start the Read Operation
	*MCU::ETHERNET::MAC::MII_AR = (m_phyAddress << 11) | (address << 6) | (clockRangeBits << 2) | 0x01;
	
	
	//	Wait for Busy Flag to clear - this is done by the MAC after the Read Operation is completed
	while(bit::isSet(*MCU::ETHERNET::MAC::MII_AR, 0) == true)
	{
		CMOS::get().sleep_ms(1);
	}
	
	
	//	Return the read Value
	return(*MCU::ETHERNET::MAC::MII_DR);
}







feedback EthernetMAC::tx(const Array<uint8>& packet)
{
	if(m_txDescriptors == nullptr || packet.get_size() > 2 * 8191)
	{
		return(FAIL);
	}
	
	
	//	Find a free Tx Descriptor
	EthernetDMA_TxDescriptor* descriptor = nullptr;
	
	
	//	1.	Check if EthernetMAC DMA is in Suspended State - that means we have to take the Descriptor that the DMA currently is waiting for
	{
		//	Check EthernetMAC DMA Status
		const uint8 status = (*MCU::ETHERNET::DMA::SR >> 20) & 0x07;
		if(status == 0x06)
		{
			//	Status: Suspended - Transmit Descriptor unavailable or Transmit Buffer Underflow
			//	The Descriptor the DMA is currently waiting for is the one pointed to by the CHTDR
			descriptor = (EthernetDMA_TxDescriptor*) *MCU::ETHERNET::DMA::CHTDR;
		}
	}
	
	
	//	2.	Search for a free Descriptor, if the Descriptor hasnt been set yet
	if(descriptor == nullptr)
	{
		for(uint32 i = 0; i < m_numberOfTxDescriptors; i++)
		{
			if(m_txDescriptors[i].isOwnedByDMA() == false)
			{
				descriptor = &m_txDescriptors[i];
				break;
			}
		}
	}
	
	
	//	No free Descriptor found
	if(descriptor == nullptr)
	{
		return(FAIL);
	}
	
	
	//	Set the Buffer Address and Size
	if(packet.get_size() < 8192)
	{
		//	Only one Buffer is needed
		descriptor->setBuffer1Size(packet.get_size());
		descriptor->setBuffer1Address((uint32) packet.get_data());
		descriptor->setBuffer2Size(0);
		descriptor->setBuffer2Address(0);
	}
	else
	{
		//	Two Buffers are needed
		descriptor->setBuffer1Size(8191);
		descriptor->setBuffer1Address((uint32) packet.get_data());
		descriptor->setBuffer2Size(packet.get_size() - 8191);
		descriptor->setBuffer2Address((uint32) packet.get_data() + 8191);
	}
	
	
	//	Descriptor Settings
	descriptor->firstDescriptorOfFrame(true);
	descriptor->lastDescriptorOfFrame(true);
	descriptor->automaticallyGenerateCRC(false);
	descriptor->automaticallyPadPackets(false);
	descriptor->transmitTimeStampsIEEE1588(false);
	descriptor->setCheckSumInsertionControl(EthernetDMA_TxDescriptor::e_checkSumInsertionControl::DISABLED);
	descriptor->secondAddressChained(false);
	descriptor->setOwnershipToDMA();
	
	
	//	Check EthernetMAC DMA Status
	const uint8 status = (*MCU::ETHERNET::DMA::SR >> 20) & 0x07;
	if(status == 0x06)
	{
		//	Status: Suspended - Transmit Descriptor unavailable or Transmit Buffer Underflow
		//	Clear Interrupt Flags
		*MCU::ETHERNET::DMA::SR = (1 << 5) | (1 << 2);
		
		
		//	Issue a Transmit Poll Demand by writing to the Transmit Poll Demand Register
		*MCU::ETHERNET::DMA::TPDR = 0;
	}
	
	
	//	Wait for the Frame to be transmitted
	CMOS& cmos = CMOS::get();
	while(descriptor->isOwnedByDMA() == true)
	{
		cmos.sleep_ms(1);
	}
	return(OK);
}


const Array<uint8>& EthernetMAC::get_macAddress()
{
	return(m_macAddress);
}


uint32 EthernetMAC::get_maximumTransmissionUnit() const
{
	return(1500);
}









void ISR_ETHERNET()
{
	//	Receive Interrupt
	if(bit::isSet(*MCU::ETHERNET::DMA::SR, 6) == true)
	{
		//	Reset the Receive Interrupt Flag and the Normal Interrupt Summary Flag
		*MCU::ETHERNET::DMA::SR = (1 << 16) | (1 << 6);
		
		
		//	Notify the Manager Thread that a Frame has been received
		EthernetMAC& ethernet = STM32F107RCT6::get().get_ethernetMAC();
		CMOS& cmos = CMOS::get();
		cmos.event_emit(ethernet.m_eventID_frameReceived);
	}
}