#pragma once

#include "cmos.hpp"
#include "network/network.hpp"
#include "registers.hpp"
#include "ethernetDMARxDescriptor.hpp"
#include "ethernetDMATxDescriptor.hpp"





class EthernetMAC : public I_MDIO, public I_PhysicalLayer
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		bool m_initialized;
		bool m_shutdownRequested;
		uint8 m_threadID;
		EthernetPHY* m_phy;
		uint8 m_phyAddress;
		Array<uint8> m_macAddress;
		uint8 m_numberOfRxDescriptors;
		uint8 m_numberOfTxDescriptors;
		uint32 m_rxFrameBufferSize;
		EthernetDMA_RxDescriptor* m_rxDescriptors;
		EthernetDMA_TxDescriptor* m_txDescriptors;
		Network* m_network;
		const uint16 m_eventID_frameReceived;
		
		
		//	Constructor and Destructor
		inline EthernetMAC();
		EthernetMAC(const EthernetMAC& ethernet) = delete;
		inline ~EthernetMAC();
		
		
		//	Member Functions
		inline feedback startup();
		
		void manager();
		
		feedback init();
		void reset();
		
		
		//	Friends
		friend class STM32F107RCT6;
		friend void ISR_ETHERNET();
		
		
		
		
		
	public:
		
		feedback init(EthernetPHY& phy, uint8 phyAddress, const Array<uint8>& macAddress, uint8 numberOfTxDescriptors, uint8 numberOfRxDescriptors, uint32 rxFrameBufferSize);
		void deinit();
		Network& get_network() const;
		
		uint16 readRegister(uint16 address) override;
		feedback writeRegister(uint16 address, uint16 data) override;
		
		feedback tx(const Array<uint8>& packet)			override;
		const Array<uint8>& get_macAddress()				override;
		uint32 get_maximumTransmissionUnit() const	override;
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
		m_threadID(CMOS::threadID_invalid),
		m_phy(nullptr),
		m_phyAddress(0),
		m_macAddress(),
		m_numberOfRxDescriptors(0),
		m_numberOfTxDescriptors(0),
		m_rxFrameBufferSize(0),
		m_rxDescriptors(nullptr),
		m_txDescriptors(nullptr),
		m_network(nullptr),
		m_eventID_frameReceived(CMOS::get().event_create())
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

