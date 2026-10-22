#pragma once

#include "cmos.hpp"
#include "network/network.hpp"
#include "registers.hpp"
#include "ethernetDMARxDescriptor.hpp"
#include "ethernetDMATxDescriptor.hpp"





class EthernetMAC : public I_MDIO, public I_PhysicalLayer
{
	public:
		
		//	Connection to the PHY: MII (16 Signals, 25 MHz) or RMII (9 Signals, 50 MHz Reference Clock), AFIO_MAPR MII_RMII_SEL
		enum class e_interface : uint8
		{
			MII		= 0,
			RMII	= 1
		};
		
		
		//	Diagnostic Counters since the Start of the Program, see get_statistics(): never reset, they wrap around after 2^32
		struct s_statistics
		{
			uint32 rxDroppedNoMemory;		//	Received Frames dropped because the Heap had no Memory for them
			uint32 txRingFull;						//	Calls of tx() that waited because all Tx Descriptors were still with the DMA
			uint32 txRestarts;						//	Restarts of the Transmit Path after 1 s without a sent Frame
		};
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		//	Longest Frame tx() accepts: 1514 Byte without the FCS, which the MAC appends (get_offloads), 4 Byte more with a VLAN Tag
		//	(IEEE 802.3, no Jumbo Frames)
		static constexpr uint32 c_frameSizeMax = 1518;
		
		//	Every Tx Descriptor has its own Buffer for one Frame, a Multiple of 4 Byte (Word Copy)
		static constexpr uint32 c_txBufferSize = 1536;
		
		
		//	Non-static Member
		bool m_initialized;
		bool m_shutdownRequested;
		volatile bool m_linkUp;						//	Link up and the Block running, written by the Manager: tx() stops waiting when it turns false
		uint8 m_threadID;
		EthernetPHY* m_phy;
		uint8 m_phyAddress;
		Array<uint8> m_macAddress;
		uint8 m_numberOfRxDescriptors;
		uint8 m_numberOfTxDescriptors;
		uint32 m_rxFrameBufferSize;
		e_interface m_interface;
		EthernetDMA_RxDescriptor* m_rxDescriptors;
		EthernetDMA_TxDescriptor* m_txDescriptors;
		uint8* m_rxBuffers;
		uint32* m_txBuffers;
		uint8 m_nextTxDescriptorIndex;
		Network* m_network;
		const uint16 m_eventID_frameReceived;
		const uint16 m_eventID_frameTransmitted;
		uint8 m_multicastHashCounters[64];		//	Number of MAC Addresses from multicast_add per Bit of the Hash Table
		s_statistics m_statistics;
		
		
		//	Constructor and Destructor
		inline EthernetMAC();
		EthernetMAC(const EthernetMAC& ethernet) = delete;
		inline ~EthernetMAC();
		
		
		//	Member Functions
		inline feedback startup();
		
		void manager();
		
		void clockInit();
		feedback init();
		void stop();
		feedback allocateBuffers();
		void freeBuffers();
		bool isPhyPresent();
		static feedback waitWhileMIIBusy();
		void restartTx();
		feedback transmit(const uint8* first, uint32 firstSize, const uint8* second, uint32 secondSize);
		void reset();
		void multicast_clear();
		void multicast_restore();
		static uint8 get_multicastHash(const Array<uint8>& macAddress);
		
		
		//	Friends
		friend class STM32F107RCT6;
		friend void ISR_ETHERNET();
		
		
		
		
		
	public:
		
		feedback init(EthernetPHY& phy, uint8 phyAddress, const Array<uint8>& macAddress, uint8 numberOfTxDescriptors, uint8 numberOfRxDescriptors, uint32 rxFrameBufferSize, e_interface interface = e_interface::MII);
		void deinit();
		Network* get_network() const;
		s_statistics get_statistics() const;
		
		uint16 readRegister(uint16 address) override;
		feedback writeRegister(uint16 address, uint16 data) override;
		
		feedback tx(const Array<uint8>& packet)			override;
		feedback tx(const Array<uint8>& header, const Array<uint8>& payload) override;
		const Array<uint8>& get_macAddress()				override;
		uint32 get_maximumTransmissionUnit() const	override;
		uint32 get_offloads() const								override;
		feedback multicast_add(const Array<uint8>& macAddress)		override;
		feedback multicast_remove(const Array<uint8>& macAddress)	override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline EthernetMAC::EthernetMAC()
	:	m_initialized(false),
		m_shutdownRequested(false),
		m_linkUp(false),
		m_threadID(CMOS::threadID_invalid),
		m_phy(nullptr),
		m_phyAddress(0),
		m_macAddress(),
		m_numberOfRxDescriptors(0),
		m_numberOfTxDescriptors(0),
		m_rxFrameBufferSize(0),
		m_interface(e_interface::MII),
		m_rxDescriptors(nullptr),
		m_txDescriptors(nullptr),
		m_rxBuffers(nullptr),
		m_txBuffers(nullptr),
		m_nextTxDescriptorIndex(0),
		m_network(nullptr),
		m_eventID_frameReceived(CMOS::get().event_create()),
		m_eventID_frameTransmitted(CMOS::get().event_create()),
		m_multicastHashCounters(),
		m_statistics()
{
	
}


inline EthernetMAC::~EthernetMAC()
{
	deinit();
}






inline feedback EthernetMAC::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

