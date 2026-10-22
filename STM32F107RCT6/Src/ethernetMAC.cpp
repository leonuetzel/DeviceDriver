#include "../Inc/stm32f107rct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

//	The Descriptors are shared with the DMA, but their Fields are not volatile: the Compiler may reorder their Stores and move them across
//	the volatile Register Accesses that hand them over (Poll Demand, Start). The Barrier keeps them in Place, and the CPU completes them
//	before the DMA is told (RM0008: the DMA reads a Descriptor as soon as it finds OWN set)
static inline void dmaBarrier()
{
	asm volatile("dmb" ::: "memory");
}


//	Copies a Part of a Frame into a Tx Buffer: Word by Word if both Addresses are aligned to 4 Byte, Half Word by Half Word if to 2 Byte
//	(e.g. the Payload behind a Header of 14 + 20 Byte), else Byte by Byte. may_alias: the Bytes of an Array are read as Words
typedef uint32 __attribute__((may_alias)) uint32_alias;
typedef uint16 __attribute__((may_alias)) uint16_alias;

static void copyToTxBuffer(uint8* destination, const uint8* source, uint32 size)
{
	uint32 i = 0;
	if((((uint32) destination | (uint32) source) & 0x3) == 0)
	{
		for(; i + 4 <= size; i += 4)
		{
			*((uint32_alias*) (destination + i)) = *((const uint32_alias*) (source + i));
		}
	}
	else if((((uint32) destination | (uint32) source) & 0x1) == 0)
	{
		for(; i + 2 <= size; i += 2)
		{
			*((uint16_alias*) (destination + i)) = *((const uint16_alias*) (source + i));
		}
	}
	for(; i < size; i++)
	{
		destination[i] = source[i];
	}
}





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void EthernetMAC::manager()
{
	//	Subscribe to all necessary Events
	CMOS& cmos = CMOS::get();
	cmos.event_subscribe(m_eventID_frameReceived);
	cmos.event_listen(m_eventID_frameReceived);
	
	
	//	Clocks of the MAC, also for MDIO while waiting for the Link
	clockInit();
	
	
	//	Descriptors and Buffers live as long as the Driver, from init() to deinit(): a Link Change keeps them, so a new Link does not depend
	//	on the Heap - with TCP Traffic it can be too fragmented for the Rx Buffers in one Block. Without Memory init() returns FAIL
	if(allocateBuffers() != OK)
	{
		reset();
		return;
	}
	
	
	//	The Network lives as long as the Driver, from init() to deinit(): the Application keeps its Pointer and its Sockets across Link Changes
	//	The Manager creates and deletes it, because its Parts start Threads with the Creator as Parent Thread (thread_shutdown). It counts as
	//	without Link before attach(), so DHCP and IGMP wait for the first Link. init() waits for m_network
	Network* network = new Network(*this);
	if(network == nullptr)
	{
		reset();
		return;
	}
	network->handleLinkChange(false);
	if(network->attach() == Network::networkID_invalid)
	{
		delete network;
		reset();
		return;
	}
	m_network = network;
	
	
	//	State Machine
	bool isInitialized = false;
	uint32 rxIndex = 0;
	uint64 timestampLinkCheck = 0;
	while(1)
	{
		if(isInitialized == false)
		{
			//	Shutdown Request, also between two Attempts
			if(m_shutdownRequested == true)
			{
				reset();
				return;
			}
			
			
			//	Wait for a PHY Link to be established, so that we can read the Duplex Mode and Speed from the PHY
			//	Without a PHY (or without its Clock) MDIO reads 0xFFFF through the Pull-up, which looks like a Link: its Identifier has to be valid first
			//	While waiting only the Link State is read, after the Link is up all Registers once (Speed and Duplex Mode)
			//	MDIO needs only the Clocks of the MAC, clockInit() has switched them on
			m_phy->readLinkStatus();
			while(isPhyPresent() == false || m_phy->isLinkUp() == false)
			{
				if(m_shutdownRequested == true)
				{
					reset();
					return;
				}
				cmos.sleep_ms(50);
				m_phy->readLinkStatus();
			}
			m_phy->readAllRegisters();
			
			
			//	Init the EthernetMAC Block only now: its Reset needs the Clocks of the PHY, which a PHY in Power-down or Reset does not deliver
			//	(see init()). Without a completed Reset a new Attempt follows after 1 s, the Network and the Buffers stay
			if(init() != OK)
			{
				for(uint32 i = 0; i < 20 && m_shutdownRequested == false; i++)
				{
					cmos.sleep_ms(50);
				}
				continue;
			}
			rxIndex = 0;
			
			
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
					//	No valid Speed from the PHY: stop and try again after 100 ms - without the Pause init() and stop() would alternate
					//	without End while the PHY keeps reporting it
					stop();
					cmos.sleep_ms(100);
					continue;
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
			
			
			//	Multicast Frames pass the Hash Filter, its Table holds the Groups from multicast_add (RM0008, ETH_MACFFR HM)
			//	Unicast Frames still have to match the own MAC Address, Broadcast Frames always pass
			//	init() has reset the Hash Table: it is written anew from the Counters before the MAC receives, the Groups of the Network stay
			bit::set(*MCU::ETHERNET::MAC::FFR, 2);
			multicast_restore();
			
			
			//	Receive Checksum Offload (IPCO): the MAC checks the IPv4 Header and the TCP, UDP and ICMP Checksums, RDES0 tells the Result
			//	(RM0008, ETH_MACCR IPCO, Table 214). Frames with a wrong Checksum are not dropped (ETH_DMAOMR DTCEFD), the Manager drops them
			bit::set(*MCU::ETHERNET::MAC::CR, 10);
			
			
			//	Enable the MAC
			bit::set(*MCU::ETHERNET::MAC::CR, 3);
			bit::set(*MCU::ETHERNET::MAC::CR, 2);
			
			
			//	Start the EthernetMAC Tx and Rx DMA
			bit::set(*MCU::ETHERNET::DMA::OMR, 13);
			bit::set(*MCU::ETHERNET::DMA::OMR, 1);
			
			
			//	The Network may transmit again: DHCP checks its Address, IGMP reports its Groups anew
			m_linkUp = true;
			m_network->handleLinkChange(true);
			isInitialized = true;
			timestampLinkCheck = cmos.get_timestamp();
		}
		
		
		constexpr uint32 timeout_ms = 100;
		const uint16 eventID = cmos.sleep_untilEvent(timeout_ms);
		
		
		//	Shutdown Request
		if(m_shutdownRequested == true)
		{
			reset();
			return;
		}
		
		
		//	Check the Link Status after a Timeout (no Frame received) and in any Case every 100 ms: under Load Frames keep arriving
		if(eventID == CMOS::eventID_invalid || cmos.getMilliSecondsSinceTimestamp(timestampLinkCheck) >= timeout_ms)
		{
			timestampLinkCheck = cmos.get_timestamp();
			m_phy->readLinkStatus();
			if(isPhyPresent() == false || m_phy->isLinkUp() == false)
			{
				//	Report the Loss first: without the Clock of the PHY the Tx DMA stands, a Thread waiting in tx() for a Descriptor gives up at
				//	once and returns the Mutex that stop() needs, and the Network stops sending. It stays with its Sockets and Groups
				//	stop() keeps the Descriptors and the Configuration, init() sets them up again as soon as the Link is up
				m_linkUp = false;
				m_network->handleLinkChange(false);
				stop();
				isInitialized = false;
				continue;
			}
		}
				
				
		//	Process the received Frames, also after a Timeout in Case an Event has been missed
		//	The Descriptors are processed in Ring Order as long as they belong to the CPU
		//	A Comparison with the current Descriptor of the DMA (CHRDR) does not work with a full Ring, both Indices are equal then
		bool descriptorsReleased = false;
		while(m_rxDescriptors[rxIndex].isOwnedByDMA() == false)
		{
			//	1.	A Frame starts with its first Descriptor, other Descriptors are discarded
			EthernetDMA_RxDescriptor& descriptor = m_rxDescriptors[rxIndex];
			if(descriptor.isFirstDescriptorOfFrame() == false)
			{
				descriptor.resetStatusBits();
				descriptor.setOwnershipToDMA();
				descriptorsReleased = true;
				rxIndex = (rxIndex + 1) % m_numberOfRxDescriptors;
				continue;
			}
					
					
			//	2.	Find the last Descriptor of the Frame, the DMA marks it also for a truncated Frame
			//		If the DMA still owns a Descriptor before it, the Frame is not complete yet and is processed later
			uint32 numberOfDescriptors = 0;
			bool frameComplete = false;
			bool frameInProgress = false;
			for(uint32 j = 0; j < m_numberOfRxDescriptors; j++)
			{
				const EthernetDMA_RxDescriptor& currentDescriptor = m_rxDescriptors[(rxIndex + j) % m_numberOfRxDescriptors];
				if(currentDescriptor.isOwnedByDMA() == true)
				{
					frameInProgress = true;
					break;
				}
				if(j > 0 && currentDescriptor.isFirstDescriptorOfFrame() == true)
				{
					//	A new Frame starts before the last Descriptor - this Frame is broken
					break;
				}
				numberOfDescriptors++;
				if(currentDescriptor.isLastDescriptorOfFrame() == true)
				{
					frameComplete = true;
					break;
				}
			}
			if(frameInProgress == true)
			{
				break;
			}
					
					
			//	3.	Check all Descriptors of the Frame for Errors, only the last one holds the Frame Length
			const uint32 frameLength = m_rxDescriptors[(rxIndex + numberOfDescriptors - 1) % m_numberOfRxDescriptors].getFrameLength();
			bool frameError = (frameComplete == false || frameLength == 0);
			for(uint32 j = 0; j < numberOfDescriptors; j++)
			{
				const EthernetDMA_RxDescriptor& currentDescriptor = m_rxDescriptors[(rxIndex + j) % m_numberOfRxDescriptors];
				if(currentDescriptor.errorDescriptor() == true || currentDescriptor.errorSummary() == true)
				{
					frameError = true;
				}
			}
					
					
			//	3b.	Checksums of the Receive Checksum Offload, in the last Descriptor: FT (Bit 5), IPHCE (Bit 7) and PCE (Bit 0) together
			//		(RM0008, RDES0 and Table 214): 1/0/0 IPv4/IPv6 with correct Header and Payload Checksum; 0/0/1 correct Header, Payload
			//		not checked (e.g. a Fragment); 1/x/x with an Error: wrong Checksum, the Frame is dropped; everything else (ARP, IEEE 802.3)
			//		is not checked. CMOS checks itself what the Hardware has not verified for this Frame
			const EthernetDMA_RxDescriptor& lastDescriptor = m_rxDescriptors[(rxIndex + numberOfDescriptors - 1) % m_numberOfRxDescriptors];
			const bool frameType = lastDescriptor.isEthernetFrame();
			const bool headerError = lastDescriptor.errorIPHeaderChecksum();
			const bool payloadError = lastDescriptor.errorIPPayloadChecksum();
			uint32 verified = 0;
			if(frameType == true && headerError == false && payloadError == false)
			{
				verified = c_offload_rxIpHeaderChecksum | c_offload_rxPayloadChecksum;
			}
			else if(frameType == false && headerError == false && payloadError == true)
			{
				verified = c_offload_rxIpHeaderChecksum;
			}
			else if(frameType == true)
			{
				frameError = true;
			}
			
			
			//	4.	Collect the Frame Data and process the Frame in the Network Stack
			//		The Frame Length includes the FCS: the DMA has delivered only Frames with a correct FCS (ETH_DMAOMR FEF = 0), it is left out
			//		The Buffers of all but the last Descriptor are full, the last one holds the Rest of the Frame - each is appended as one Block
			if(frameError == false && frameLength > 4)
			{
				const uint32 packetLength = frameLength - 4;
				Array<uint8> frame;
				bool complete = (frame.reserve(packetLength) == OK);
				uint32 bytesCollected = 0;
				for(uint32 j = 0; j < numberOfDescriptors && bytesCollected < packetLength && complete == true; j++)
				{
					const EthernetDMA_RxDescriptor& currentDescriptor = m_rxDescriptors[(rxIndex + j) % m_numberOfRxDescriptors];
					uint32 frameBufferLength = packetLength - bytesCollected;
					if(frameBufferLength > m_rxFrameBufferSize)
					{
						frameBufferLength = m_rxFrameBufferSize;
					}
					complete = (frame.append(currentDescriptor.getBuffer1Address(), frameBufferLength) == OK);
					bytesCollected += frameBufferLength;
				}
				
				
				//	Without Memory for the whole Frame it is dropped, like a lost Frame on the Line - only counted (get_statistics)
				if(complete == true)
				{
					m_network->handlePacket(frame, verified);
				}
				else
				{
					m_statistics.rxDroppedNoMemory++;
				}
			}
					
					
			//	5.	Release all Descriptors of the Frame
			for(uint32 j = 0; j < numberOfDescriptors; j++)
			{
				EthernetDMA_RxDescriptor& currentDescriptor = m_rxDescriptors[(rxIndex + j) % m_numberOfRxDescriptors];
				currentDescriptor.resetStatusBits();
				currentDescriptor.setOwnershipToDMA();
			}
			descriptorsReleased = true;
			rxIndex = (rxIndex + numberOfDescriptors) % m_numberOfRxDescriptors;
		}
				
				
		//	The DMA suspends the Reception while it owns no Descriptor, a Receive Poll Demand resumes it
		if(descriptorsReleased == true)
		{
			dmaBarrier();
			*MCU::ETHERNET::DMA::RPDR = 0;
		}
	}
}







void EthernetMAC::clockInit()
{
	//	MII or RMII: MII_RMII_SEL has to be set before the Clocks of the MAC are switched on (RM0008, AFIO_MAPR)
	RCC& rcc = STM32F107RCT6::get().get_rcc();
	rcc.module_reset(RCC::e_module::ETHERNET_MAC);
	STM32F107RCT6::get().get_afio().set_remap(AFIO::e_remap::ETHERNET_RMII, (m_interface == e_interface::RMII) ? 1 : 0);
	
	
	//	Enable the Clocks of the EthernetMAC Block, reset() switches them off again
	rcc.module_clockInit(RCC::e_module::ETHERNET_MAC,	true);
	rcc.module_clockInit(RCC::e_module::ETHERNET_TX,	true);
	rcc.module_clockInit(RCC::e_module::ETHERNET_RX,	true);
	
	
	//	The Ethernet DMA does not work in Sleep Mode (WFE in the Idle Loop of CMOS) if no other AHB Master has its Clock enabled
	//	Workaround: DMA1 Clock on (ES022 Rev 11, 2.14.11) - the DMA_1 Driver enables it already at Startup and never disables it
	rcc.module_clockInit(RCC::e_module::DMA_1,	true);
}


feedback EthernetMAC::init()
{
	//	Reset the EthernetMAC Block and wait until the Reset has completed in all Clock Domains (RM0008, ETH_DMABMR SR). The Rx and Tx Domains
	//	run with the Clocks of the PHY: without them (PHY in Power-down, e.g. BMCR Bit 11 of the DP83825I, or in Reset) the Reset completes
	//	only when they come back - after DMARDLAR has been written, the Rx DMA then starts with the Descriptor Address 0 and stays suspended
	//	The Manager calls init() only while the PHY reports a Link. The MII Mode in AFIO_MAPR and the Clocks stay (clockInit)
	CMOS& cmos = CMOS::get();
	RCC& rcc = STM32F107RCT6::get().get_rcc();
	rcc.module_reset(RCC::e_module::ETHERNET_MAC);
	bit::set(*MCU::ETHERNET::DMA::BMR, 0);
	const uint64 timestampReset = cmos.get_timestamp();
	while(bit::isSet(*MCU::ETHERNET::DMA::BMR, 0) == true)
	{
		if(cmos.getMilliSecondsSinceTimestamp(timestampReset) > 10)
		{
			return(FAIL);
		}
	}
	
	
	//	Set up all DMA Rx Descriptors anew (allocateBuffers): after a Link Change the Ring starts again with every Descriptor owned by the DMA
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
		
		descriptor.setBuffer1Address((uint32) &m_rxBuffers[i * m_rxFrameBufferSize]);
		descriptor.setBuffer1Size(m_rxFrameBufferSize);
		descriptor.setBuffer2Address(0);
		descriptor.setBuffer2Size(0);
	}
	
	
	//	Set up all DMA Tx Descriptors anew, all owned by the CPU
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
		descriptor.automaticallyGenerateCRC(true);
		descriptor.automaticallyPadPackets(true);
		descriptor.transmitTimeStampsIEEE1588(false);
		descriptor.setCheckSumInsertionControl(EthernetDMA_TxDescriptor::e_checkSumInsertionControl::IP_HEADER_AND_PAYLOAD_AND_PSEUDOHEADER);
		descriptor.secondAddressChained(false);
		descriptor.setBuffer1Address((uint32) &m_txBuffers[i * (c_txBufferSize / 4)]);
		descriptor.setBuffer1Size(0);
		descriptor.setBuffer2Address(0);
		descriptor.setBuffer2Size(0);
	}
	
	
	//	The DMA starts with the first Tx Descriptor
	m_nextTxDescriptorIndex = 0;
	
	
	//	Tell the EthernetMAC DMA where the Descriptors are located
	dmaBarrier();
	*MCU::ETHERNET::DMA::TDLAR = (uint32) m_txDescriptors;
	*MCU::ETHERNET::DMA::RDLAR = (uint32) m_rxDescriptors;
	
	
	//	Disable dropping Frames with CRC Erros detected in the Rx CRC Offload Engine
	bit::set(*MCU::ETHERNET::DMA::OMR, 26);
	
	
	//	Store-and-Forward Mode (means, that the DMA will only start to transfer the Frame from/to the MAC when the complete Frame is received/sent)
	bit::set(*MCU::ETHERNET::DMA::OMR, 21);
	bit::set(*MCU::ETHERNET::DMA::OMR, 25);
	
	
	//	Enable the normal Receive and Transmit Interrupts (RIE, TIE, NISE): tx() sleeps until its Frame is sent
	bit::set(*MCU::ETHERNET::DMA::IER, 6);
	bit::set(*MCU::ETHERNET::DMA::IER, 0);
	bit::set(*MCU::ETHERNET::DMA::IER, 16);
	
	
	NVIC& nvic = CMOS::get().get_nvic();
	nvic.setPriority(Interrupt::ETHERNET, 8);
	nvic.enable(Interrupt::ETHERNET);
	
	
	return(OK);
}


void EthernetMAC::stop()
{
	//	No Transmission meanwhile: tx() uses the Tx Descriptors
	CMOS& cmos = CMOS::get();
	const bool txLocked = (cmos.mutex_lock(&m_txDescriptors) == OK);
	
	
	//	Disable Interrupts
	NVIC& nvic = cmos.get_nvic();
	nvic.disable(Interrupt::ETHERNET);
	
	
	//	Stop the Tx DMA, the MAC and the Rx DMA
	bit::clear(*MCU::ETHERNET::DMA::OMR, 13);
	bit::clear(*MCU::ETHERNET::MAC::CR, 3);
	bit::clear(*MCU::ETHERNET::MAC::CR, 2);
	bit::clear(*MCU::ETHERNET::DMA::OMR, 1);
	
	
	//	The DMA finishes the current Frame first: the Descriptors and Buffers are touched again (init(), freeBuffers()) only once both DMA
	//	Processes are stopped (TPS = RPS = 0). They stay allocated, tx() fails while the Tx DMA is stopped
	const uint64 timestampStart = cmos.get_timestamp();
	while((*MCU::ETHERNET::DMA::SR & 0x007E0000) != 0 && cmos.getMilliSecondsSinceTimestamp(timestampStart) < 10)
	{
		
	}
	
	
	if(txLocked == true)
	{
		cmos.mutex_unlock(&m_txDescriptors);
	}
}


feedback EthernetMAC::allocateBuffers()
{
	//	DMA Descriptors, the Frame Buffers for the Rx Descriptors (one Block) and one Buffer per Tx Descriptor (tx() copies the Frame into it
	//	and returns at once). Once at the Start of the Manager; on a Failure everything allocated here is freed again
	m_txDescriptors = new EthernetDMA_TxDescriptor[m_numberOfTxDescriptors];
	m_rxDescriptors = new EthernetDMA_RxDescriptor[m_numberOfRxDescriptors];
	m_rxBuffers = new uint8[m_numberOfRxDescriptors * m_rxFrameBufferSize];
	m_txBuffers = new uint32[m_numberOfTxDescriptors * (c_txBufferSize / 4)];
	if(m_txDescriptors == nullptr || m_rxDescriptors == nullptr || m_rxBuffers == nullptr || m_txBuffers == nullptr)
	{
		freeBuffers();
		return(FAIL);
	}
	return(OK);
}


void EthernetMAC::freeBuffers()
{
	//	Only with the DMA stopped (stop()): under the Mutex of tx(), which checks m_txDescriptors
	CMOS& cmos = CMOS::get();
	const bool txLocked = (cmos.mutex_lock(&m_txDescriptors) == OK);
	delete[] m_txBuffers;
	delete[] m_rxBuffers;
	delete[] m_rxDescriptors;
	delete[] m_txDescriptors;
	m_txBuffers = nullptr;
	m_rxBuffers = nullptr;
	m_rxDescriptors = nullptr;
	m_txDescriptors = nullptr;
	if(txLocked == true)
	{
		cmos.mutex_unlock(&m_txDescriptors);
	}
}
	
	
void EthernetMAC::reset()
{
	//	Only when the Manager ends (deinit(), no Memory for the Network): detach and delete the Network first, it must not transmit anymore
	m_linkUp = false;
	if(m_network != nullptr)
	{
		m_network->detach();
		delete m_network;
		m_network = nullptr;
	}
	multicast_clear();
	
	
	//	Stop the EthernetMAC Block and free the Descriptors and Buffers
	stop();
	freeBuffers();
	
	
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
}


void EthernetMAC::multicast_clear()
{
	//	The Groups belong to the Network and go with it (reset): a new Network starts without Groups, init() resets the Hash Table of the MAC
	CMOS& cmos = CMOS::get();
	const bool locked = (cmos.mutex_lock(m_multicastHashCounters) == OK);
	for(uint32 i = 0; i < 64; i++)
	{
		m_multicastHashCounters[i] = 0;
	}
	if(locked == true)
	{
		cmos.mutex_unlock(m_multicastHashCounters);
	}
}


void EthernetMAC::multicast_restore()
{
	//	init() resets the Hash Table with the MAC, the Counters keep the Groups of the Network across Link Changes: every Bit with an Address is
	//	set again (RM0008, ETH_MACHTHR/ETH_MACHTLR). Under the Mutex a parallel multicast_add() comes either before (it is in the Counters) or
	//	after (it sets its Bit itself)
	CMOS& cmos = CMOS::get();
	const bool locked = (cmos.mutex_lock(m_multicastHashCounters) == OK);
	uint32 high = 0;
	uint32 low = 0;
	for(uint32 i = 0; i < 64; i++)
	{
		if(m_multicastHashCounters[i] != 0)
		{
			if(i < 32)
			{
				low |= (1U << i);
			}
			else
			{
				high |= (1U << (i - 32));
			}
		}
	}
	*MCU::ETHERNET::MAC::HTHR = high;
	*MCU::ETHERNET::MAC::HTLR = low;
	if(locked == true)
	{
		cmos.mutex_unlock(m_multicastHashCounters);
	}
}


uint8 EthernetMAC::get_multicastHash(const Array<uint8>& macAddress)
{
	//	The MAC forms the Ethernet CRC-32 of the Destination Address (reflected, Start Value 0xFFFFFFFF, inverted at the End)
	//	The Hash is the upper 6 Bits of the bit-reversed CRC (RM0008, ETH_MACHTHR)
	//	Checked with the Examples there: 1F:52:41:9C:B6:AF -> 0x2C, A0:0A:98:00:00:45 -> 0x07
	uint32 crc = 0xFFFFFFFF;
	for(uint32 i = 0; i < 6; i++)
	{
		crc ^= macAddress[i];
		for(uint32 j = 0; j < 8; j++)
		{
			if((crc & 0x00000001) != 0)
			{
				crc = (crc >> 1) ^ 0xEDB88320;
			}
			else
			{
				crc = crc >> 1;
			}
		}
	}
	crc = ~crc;
	
	
	//	The upper 6 Bits of the reversed CRC are its lower 6 Bits in reverse Order
	uint8 hash = 0;
	for(uint32 i = 0; i < 6; i++)
	{
		if(((crc >> i) & 0x00000001) != 0)
		{
			hash |= (1 << (5 - i));
		}
	}
	return(hash);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback EthernetMAC::init(EthernetPHY& phy, uint8 phyAddress, const Array<uint8>& macAddress, uint8 numberOfTxDescriptors, uint8 numberOfRxDescriptors, uint32 rxFrameBufferSize, e_interface interface)
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
	
	
	//	At least one Descriptor each, a MAC Address with 6 Byte and an Rx Buffer Size with 13 Bit (RM0008, RDES1 RBS1)
	if(numberOfTxDescriptors == 0 || numberOfRxDescriptors == 0 || macAddress.get_size() != 6 || rxFrameBufferSize == 0 || rxFrameBufferSize > 8188)
	{
		return(FAIL);
	}
	
	
	//	Mutex for tx(), several Threads transmit, one for the Multicast Hash Table and one for the MDIO Transactions (Key &m_phyAddress,
	//	see readRegister()) - they exist already after a previous init
	CMOS& cmos = CMOS::get();
	cmos.mutex_create(&m_txDescriptors);
	cmos.mutex_create(m_multicastHashCounters);
	cmos.mutex_create(&m_phyAddress);
	
	
	//	Store the Parameters
	m_phy = &phy;
	m_phyAddress = phyAddress;
	m_macAddress = macAddress;
	m_numberOfRxDescriptors = numberOfRxDescriptors;
	m_numberOfTxDescriptors = numberOfTxDescriptors;
	//	The Rx Buffer Size must be a Multiple of 4 (RM0008, RDES1 RBS1), it is rounded up
	m_rxFrameBufferSize = (rxFrameBufferSize + 3) & 0xFFFFFFFC;
	m_interface = interface;
	
	
	
	//	Start Thread to supervise the PHY
	m_threadID = cmos.thread_create(&EthernetMAC::manager, this, "EthernetMAC Manager", 200, 2048);
	if(m_threadID == CMOS::threadID_invalid)
	{
		//	Forget the Parameters, so that the next init is possible
		m_phy = nullptr;
		m_phyAddress = 0;
		m_macAddress.erase();
		m_numberOfRxDescriptors = 0;
		m_numberOfTxDescriptors = 0;
		m_rxFrameBufferSize = 0;
		return(FAIL);
	}
	
	
	//	Wait for the Manager to create the Network: get_network() returns it from now on until deinit(). Without Memory for it the Manager
	//	ends after reset(), which has forgotten the Parameters
	while(m_network == nullptr)
	{
		if(cmos.thread_doesExist(m_threadID) == false)
		{
			m_threadID = CMOS::threadID_invalid;
			return(FAIL);
		}
		cmos.sleep_ms(1);
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
	
	
	//	Invalidate the Thread ID and allow the next init
	m_threadID = CMOS::threadID_invalid;
	m_shutdownRequested = false;
}


Network* EthernetMAC::get_network() const
{
	//	The Network exists from init() to deinit(), also while the Link is down (Network::isLinkUp), before and after that nullptr
	return(m_network);
}


EthernetMAC::s_statistics EthernetMAC::get_statistics() const
{
	//	Each Counter has one Writer at a Time (the Manager Thread, tx() under the Mutex of the Tx Descriptors) and is read as one Word:
	//	no Lock needed, the three Values may stem from slightly different Moments
	return(m_statistics);
}







bool EthernetMAC::isPhyPresent()
{
	//	PHY Identifier 1 and 2 (Registers 2 and 3, IEEE 802.3 Clause 22): a missing PHY reads 0xFFFF through the Pull-up of MDIO, a shorted Line 0x0000
	const uint16 identifier1 = readRegister(2);
	const uint16 identifier2 = readRegister(3);
	if((identifier1 == 0xFFFF && identifier2 == 0xFFFF) || (identifier1 == 0x0000 && identifier2 == 0x0000))
	{
		return(false);
	}
	return(true);
}


feedback EthernetMAC::waitWhileMIIBusy()
{
	//	A Transaction lasts 64 MDC Cycles, about 40 µs at 1.7 MHz MDC (RM0008, ETH_MACMIIAR CR): it is polled without Sleep - a Sleep of 1 ms per
	//	Access stretched the Link Check of the Manager (about 34 Accesses) to some 50 ms, during which no Frame was received
	//	The Limit of 3 Ticks only guards against a MAC that does not run. The Busy Bit is checked before the Time: a Thread that was preempted
	//	meanwhile finds the Transaction finished and does not fail
	CMOS& cmos = CMOS::get();
	const uint64 timestampStart = cmos.get_timestamp();
	while(bit::isSet(*MCU::ETHERNET::MAC::MII_AR, 0) == true)
	{
		if(cmos.get_timestamp() - timestampStart > 3)
		{
			return(bit::isSet(*MCU::ETHERNET::MAC::MII_AR, 0) == true ? FAIL : OK);
		}
	}
	return(OK);
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
	
	
	//	One Transaction at a Time (see readRegister)
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(&m_phyAddress) != OK)
	{
		return(FAIL);
	}
	
	
	//	Wait for the BUSY Bit to be cleared by Hardware, write the Data into the Data Register and then the Address of the Register, which
	//	starts the Write Operation. The MAC clears the BUSY Bit after the Write Operation is completed
	feedback result = waitWhileMIIBusy();
	if(result == OK)
	{
		*MCU::ETHERNET::MAC::MII_DR = data;
		*MCU::ETHERNET::MAC::MII_AR = (m_phyAddress << 11) | (address << 6) | (clockRangeBits << 2) | 0x03;
		result = waitWhileMIIBusy();
	}
	cmos.mutex_unlock(&m_phyAddress);
	return(result);
}


uint16 EthernetMAC::readRegister(uint16 address)
{
	//	Without an Answer the Result is 0xFFFF, as a missing PHY reads through the Pull-up of MDIO
	constexpr uint16 c_noAnswer = 0xFFFF;
	
	
	//	Read the AHB Bus Clock from the RCC to set the MDC Clock properly
	const uint32 clock = STM32F107RCT6::get().get_rcc().get_clock_ahb();
	if(clock < 20000000 || clock > 72000000)
	{
		return(c_noAnswer);
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
	
	
	//	One Transaction at a Time: the Manager Thread reads the Link Status every 100 ms while the Application may access the PHY through
	//	its Driver - a second Transaction would overwrite MACMIIAR/MACMIIDR while the BUSY Bit is set. A Sequence of several Transactions
	//	(e.g. an extended Register through REGCR/ADDAR) has to be locked by the PHY Driver. Before init() the Mutex does not exist: no Answer
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(&m_phyAddress) != OK)
	{
		return(c_noAnswer);
	}
	
	
	//	Wait for the BUSY Bit to be cleared by Hardware, then write the Address of the Register, which starts the Read Operation. The MAC
	//	clears the BUSY Bit when the Value is in the Data Register
	uint16 value = c_noAnswer;
	if(waitWhileMIIBusy() == OK)
	{
		*MCU::ETHERNET::MAC::MII_AR = (m_phyAddress << 11) | (address << 6) | (clockRangeBits << 2) | 0x01;
		if(waitWhileMIIBusy() == OK)
		{
			value = (uint16) *MCU::ETHERNET::MAC::MII_DR;
		}
	}
	cmos.mutex_unlock(&m_phyAddress);
	return(value);
}







feedback EthernetMAC::tx(const Array<uint8>& packet)
{
	return(transmit(packet.get_data(), packet.get_size(), nullptr, 0));
}


feedback EthernetMAC::tx(const Array<uint8>& header, const Array<uint8>& payload)
{
	//	Header and Payload go one behind the other into the Buffer of the Descriptor, CMOS has not joined them (I_PhysicalLayer, CMOS 265)
	return(transmit(header.get_data(), header.get_size(), payload.get_data(), payload.get_size()));
}


feedback EthernetMAC::transmit(const uint8* first, uint32 firstSize, const uint8* second, uint32 secondSize)
{
	//	Several Threads transmit (Manager Thread for ARP and TCP Answers, DHCP Thread, Application): only one at a Time takes a Descriptor
	//	The Manager waits only briefly, for the Mutex and a Descriptor together at most c_managerWait_ms: it has to check the Link and receive
	//	With a Link a Descriptor is free again within about 1 ms. Without one (a PHY in Power-down delivers no Clock, the Tx DMA stands) its
	//	Frame gets FAIL, TCP and ARP repeat it
	constexpr int64 c_managerWait_ms = 10;
	CMOS& cmos = CMOS::get();
	const uint32 size = firstSize + secondSize;
	const bool isManager = (cmos.get_runningThreadID() == m_threadID);
	const uint64 timestampStart = cmos.get_timestamp();
	if(isManager == true)
	{
		while(cmos.mutex_tryLock(&m_txDescriptors) != OK)
		{
			if(cmos.getMilliSecondsSinceTimestamp(timestampStart) >= c_managerWait_ms)
			{
				return(FAIL);
			}
			cmos.sleep_ms(1);
		}
	}
	else if(cmos.mutex_lock(&m_txDescriptors) != OK)
	{
		return(FAIL);
	}
	
	
	//	The Tx DMA has to be running, it is started as soon as the Link is up
	//	A Frame without Bytes must not reach a Descriptor: the DMA would wait for its Status for ever (TPS = 010) and send nothing anymore
	if(m_txDescriptors == nullptr || bit::isCleared(*MCU::ETHERNET::DMA::OMR, 13) == true || size == 0 || size > c_frameSizeMax)
	{
		cmos.mutex_unlock(&m_txDescriptors);
		return(FAIL);
	}
	
	
	//	Take the next Descriptor in Ring Order, the DMA processes the Descriptors in this Order
	//	If the DMA is suspended, it waits for the Descriptor pointed to by CHTDR - but only a Descriptor of the own Ring counts:
	//	CHTDR is 0 until the DMA has fetched its first Descriptor (e.g. without the Clock of the PHY)
	EthernetDMA_TxDescriptor* descriptor = &m_txDescriptors[m_nextTxDescriptorIndex];
	{
		const uint8 status = (*MCU::ETHERNET::DMA::SR >> 20) & 0x07;
		const uint32 current = *MCU::ETHERNET::DMA::CHTDR;
		const uint32 first = (uint32) m_txDescriptors;
		const uint32 ringSize = m_numberOfTxDescriptors * sizeof(EthernetDMA_TxDescriptor);
		if(status == 0x06 && current >= first && current - first < ringSize && (current - first) % sizeof(EthernetDMA_TxDescriptor) == 0)
		{
			descriptor = (EthernetDMA_TxDescriptor*) current;
		}
	}
	//	All Descriptors with the DMA: wait until it has sent a Frame (Transmit Interrupt), at most 1 s - then the Transmit Path is restarted
	//	Without event_listen(): the Manager Thread listens to its Receive Event, a Thread listens to one Event only
	//	An Interrupt that comes before the Sleep is missed - then the Sleep ends after 1 ms and the Descriptor is checked again
	//	A lost Link ends the Wait at once (m_linkUp): the Manager stops the Block, init() sets up the Descriptors again
	if(descriptor->isOwnedByDMA() == true)
	{
		m_statistics.txRingFull++;
		const bool subscribedBefore = cmos.event_isSubscribed(m_eventID_frameTransmitted);
		if(subscribedBefore == false)
		{
			cmos.event_subscribe(m_eventID_frameTransmitted);
		}
		const uint64 timestampWait = (isManager == true) ? timestampStart : cmos.get_timestamp();
		const int64 waitMaximum_ms = (isManager == true) ? c_managerWait_ms : 1000;
		bool timeout = false;
		bool linkLost = false;
		while(descriptor->isOwnedByDMA() == true)
		{
			if(m_linkUp == false)
			{
				linkLost = true;
				break;
			}
			if(cmos.getMilliSecondsSinceTimestamp(timestampWait) > waitMaximum_ms)
			{
				timeout = true;
				break;
			}
			cmos.sleep_untilEvent(m_eventID_frameTransmitted, 1);
		}
		if(subscribedBefore == false)
		{
			cmos.event_unsubscribe(m_eventID_frameTransmitted);
		}
		
		
		//	A lost Link or the short Wait of the Manager: FAIL without a Restart, the Manager checks the Link next
		if(linkLost == true || (timeout == true && isManager == true))
		{
			cmos.mutex_unlock(&m_txDescriptors);
			return(FAIL);
		}
		if(timeout == true)
		{
			//	No Frame leaves: the Descriptors stay with the DMA. The Restart frees them, the next Frame starts at the first Descriptor
			restartTx();
			cmos.mutex_unlock(&m_txDescriptors);
			return(FAIL);
		}
	}
	m_nextTxDescriptorIndex = (uint8) (((descriptor - m_txDescriptors) + 1) % m_numberOfTxDescriptors);
	
	
	//	Copy the Frame into the Buffer of the Descriptor, the second Part directly behind the first: the Packet of the Caller is free again when
	//	tx() returns
	uint32* const buffer = &m_txBuffers[(descriptor - m_txDescriptors) * (c_txBufferSize / 4)];
	copyToTxBuffer((uint8*) buffer, first, firstSize);
	copyToTxBuffer((uint8*) buffer + firstSize, second, secondSize);
	
	
	//	Buffer Address and Size, one Buffer holds every Frame up to c_frameSizeMax (TBS1 has 13 Bit, RM0008 TDES1)
	descriptor->setBuffer1Size(size);
	descriptor->setBuffer1Address((uint32) buffer);
	descriptor->setBuffer2Size(0);
	descriptor->setBuffer2Address(0);
	
	
	//	Descriptor Settings: the MAC appends the FCS and pads short Frames to 60 Byte, the Checksum Offload inserts the IPv4 Header
	//	Checksum and the TCP, UDP and ICMP Checksum with Pseudo Header (CIC = 11, RM0008 TDES0) - it skips Fragments, CMOS has computed
	//	their Checksum. The Transmit FIFO works in Store-and-Forward Mode (TSF), as the Offload requires
	descriptor->firstDescriptorOfFrame(true);
	descriptor->lastDescriptorOfFrame(true);
	descriptor->interruptOnCompletion(true);
	descriptor->automaticallyGenerateCRC(true);
	descriptor->automaticallyPadPackets(true);
	descriptor->transmitTimeStampsIEEE1588(false);
	descriptor->setCheckSumInsertionControl(EthernetDMA_TxDescriptor::e_checkSumInsertionControl::IP_HEADER_AND_PAYLOAD_AND_PSEUDOHEADER);
	descriptor->secondAddressChained(false);
	dmaBarrier();
	descriptor->setOwnershipToDMA();
	dmaBarrier();
	
	
	//	Transmit Poll Demand, also while the DMA runs (RM0008, ETH_DMATPDR): it may have found this Descriptor still with the CPU just before
	//	and suspend now - tx() no longer waits for the Frame, nobody would wake the DMA until the next Frame. First clear TBUS and TUS
	*MCU::ETHERNET::DMA::SR = (1 << 5) | (1 << 2);
	*MCU::ETHERNET::DMA::TPDR = 0;
	
	
	//	The DMA sends the Frame from the own Buffer: no Waiting here, a later tx() waits only if all Descriptors are still with the DMA
	cmos.mutex_unlock(&m_txDescriptors);
	return(OK);
}


void EthernetMAC::restartTx()
{
	//	Restart of the Transmit Path, the Caller holds the Mutex of the Tx Descriptors (RM0008, ETH_DMAOMR ST and FTF, ETH_DMATDLAR):
	//	stop the Tx DMA, flush the Tx FIFO, give all Descriptors back to the CPU and start again at the first Descriptor
	m_statistics.txRestarts++;
	CMOS& cmos = CMOS::get();
	bit::clear(*MCU::ETHERNET::DMA::OMR, 13);
	const uint64 timestampStop = cmos.get_timestamp();
	while(((*MCU::ETHERNET::DMA::SR >> 20) & 0x07) != 0 && cmos.getMilliSecondsSinceTimestamp(timestampStop) < 10)
	{
		
	}
	
	
	//	FTF clears itself when the FIFO is empty, ETH_DMAOMR must not be written meanwhile
	bit::set(*MCU::ETHERNET::DMA::OMR, 20);
	const uint64 timestampFlush = cmos.get_timestamp();
	while(bit::isSet(*MCU::ETHERNET::DMA::OMR, 20) == true && cmos.getMilliSecondsSinceTimestamp(timestampFlush) < 10)
	{
		
	}
	
	
	for(uint32 i = 0; i < m_numberOfTxDescriptors; i++)
	{
		m_txDescriptors[i].setOwnershipToCPU();
	}
	m_nextTxDescriptorIndex = 0;
	dmaBarrier();
	*MCU::ETHERNET::DMA::TDLAR = (uint32) m_txDescriptors;
	*MCU::ETHERNET::DMA::SR = (1 << 5) | (1 << 2) | (1 << 1) | (1 << 0);
	bit::set(*MCU::ETHERNET::DMA::OMR, 13);
}


const Array<uint8>& EthernetMAC::get_macAddress()
{
	return(m_macAddress);
}


uint32 EthernetMAC::get_maximumTransmissionUnit() const
{
	return(1500);
}


uint32 EthernetMAC::get_offloads() const
{
	//	The MAC appends the FCS and pads, the Checksum Offload inserts and checks the IPv4 Header and the TCP, UDP and ICMP Checksums
	//	(not for Fragments: there CMOS computes them), the DMA delivers only Frames with a correct FCS, without it (see manager())
	return(c_offload_txFcs | c_offload_txPadding | c_offload_txIpHeaderChecksum | c_offload_txPayloadChecksum | c_offload_rxFcs |
	       c_offload_rxIpHeaderChecksum | c_offload_rxPayloadChecksum);
}


feedback EthernetMAC::multicast_add(const Array<uint8>& macAddress)
{
	//	Only Group Addresses (Bit 0 of the first Byte set) belong into the Multicast Hash Table
	if(macAddress.get_size() != 6 || (macAddress[0] & 0x01) == 0)
	{
		return(FAIL);
	}
	
	
	//	Several MAC Addresses can share one Bit of the Hash Table: each Bit counts its Addresses and is set with the first one
	//	The Filter is imperfect, Frames of other Groups with the same Hash pass too - the Network Stack checks the Group itself
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(m_multicastHashCounters) != OK)
	{
		return(FAIL);
	}
	const uint8 hash = get_multicastHash(macAddress);
	if(m_multicastHashCounters[hash] == 0xFF)
	{
		cmos.mutex_unlock(m_multicastHashCounters);
		return(FAIL);
	}
	m_multicastHashCounters[hash]++;
	if(m_multicastHashCounters[hash] == 1)
	{
		//	The upper Bit of the Hash selects the Register, the other 5 Bits the Bit in it (RM0008, ETH_MACHTHR)
		if(hash < 32)
		{
			bit::set(*MCU::ETHERNET::MAC::HTLR, hash);
		}
		else
		{
			bit::set(*MCU::ETHERNET::MAC::HTHR, hash - 32);
		}
	}
	cmos.mutex_unlock(m_multicastHashCounters);
	return(OK);
}


feedback EthernetMAC::multicast_remove(const Array<uint8>& macAddress)
{
	if(macAddress.get_size() != 6 || (macAddress[0] & 0x01) == 0)
	{
		return(FAIL);
	}
	
	
	//	The Bit is cleared with the last Address of its Hash, the Caller removes only Addresses it has added
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(m_multicastHashCounters) != OK)
	{
		return(FAIL);
	}
	const uint8 hash = get_multicastHash(macAddress);
	if(m_multicastHashCounters[hash] == 0)
	{
		cmos.mutex_unlock(m_multicastHashCounters);
		return(FAIL);
	}
	m_multicastHashCounters[hash]--;
	if(m_multicastHashCounters[hash] == 0)
	{
		if(hash < 32)
		{
			bit::clear(*MCU::ETHERNET::MAC::HTLR, hash);
		}
		else
		{
			bit::clear(*MCU::ETHERNET::MAC::HTHR, hash - 32);
		}
	}
	cmos.mutex_unlock(m_multicastHashCounters);
	return(OK);
}









void ISR_ETHERNET()
{
	//	Both Flags are read once and cleared together with the Normal Interrupt Summary (RM0008, ETH_DMASR: write 1 to clear)
	const uint32 status = *MCU::ETHERNET::DMA::SR & ((1 << 6) | (1 << 0));
	if(status == 0)
	{
		return;
	}
	*MCU::ETHERNET::DMA::SR = (1 << 16) | status;
	EthernetMAC& ethernet = STM32F107RCT6::get().get_ethernetMAC();
	CMOS& cmos = CMOS::get();
	
	
	//	Receive Interrupt: notify the Manager Thread that a Frame has been received
	if((status & (1 << 6)) != 0)
	{
		cmos.event_emit(ethernet.m_eventID_frameReceived);
	}
	
	
	//	Transmit Interrupt: a Frame has been sent, tx() waits for it
	if((status & (1 << 0)) != 0)
	{
		cmos.event_emit(ethernet.m_eventID_frameTransmitted);
	}
}