#pragma once

#include "cmos.hpp"





class EthernetDMA_RxDescriptor
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		uint32 RDES[4];
		
		
		//	Constructor and Destructor
		
		
		
		//	Member Functions
		
		
		
		//	Friends
		
		
		
		
		
		
	public:
		
		constexpr inline void setOwnershipToDMA();
		constexpr inline void setOwnershipToCPU();
		constexpr inline bool isOwnedByDMA() const;
		
		constexpr inline void resetStatusBits();
		constexpr inline void disableInterruptOnCompletion(bool disable);
		constexpr inline void finalDescriptorOfDescriptorList(bool isFinalDescriptor);
		constexpr inline void secondAddressChained(bool isSecondAddressChained);
		
		constexpr inline bool isFirstDescriptorOfFrame() const;
		constexpr inline bool isLastDescriptorOfFrame() const;
		constexpr inline bool wasDestinationAddressFilterFailed() const;
		constexpr inline bool wasSourceAddressFilterFailed() const;
		constexpr inline bool wasVLANFrame() const;
		constexpr inline bool isEthernetFrame() const;
		constexpr inline uint16 getFrameLength() const;
		
		constexpr inline bool errorSummary() const;
		constexpr inline bool errorIPHeaderChecksum() const;
		constexpr inline bool errorIPPayloadChecksum() const;
		constexpr inline bool errorDescriptor() const;
		constexpr inline bool errorLength() const;
		constexpr inline bool errorOverflow() const;
		constexpr inline bool errorLateCollision() const;
		constexpr inline bool errorReceiveWatchdogTimeout() const;
		constexpr inline bool errorReceive() const;
		constexpr inline bool errorDribbleBit() const;
		constexpr inline bool errorCRC() const;
		
		constexpr inline void setBuffer1Size(uint16 size);
		constexpr inline void setBuffer2Size(uint16 size);
		constexpr inline void setBuffer1Address(uint32 address);
		constexpr inline void setBuffer2Address(uint32 address);
		constexpr inline uint64 getTimeStampCaptured() const;
		
		constexpr inline uint8* getBuffer1Address() const;
		constexpr inline uint8* getBuffer2Address() const;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

constexpr inline void EthernetDMA_RxDescriptor::setOwnershipToDMA()
{
	bit::set(RDES[0], 31);
}


constexpr inline void EthernetDMA_RxDescriptor::setOwnershipToCPU()
{
	bit::clear(RDES[0], 31);
}


constexpr inline bool EthernetDMA_RxDescriptor::isOwnedByDMA() const
{
	return(bit::isSet(RDES[0], 31));
}







constexpr inline void EthernetDMA_RxDescriptor::resetStatusBits()
{
	RDES[0] = 0;
}


constexpr inline void EthernetDMA_RxDescriptor::disableInterruptOnCompletion(bool disable)
{
	if(disable == true)
	{
		bit::set(RDES[1], 31);
	}
	else
	{
		bit::clear(RDES[1], 31);
	}
}


constexpr inline void EthernetDMA_RxDescriptor::finalDescriptorOfDescriptorList(bool isFinalDescriptor)
{
	if(isFinalDescriptor == true)
	{
		bit::set(RDES[1], 15);
	}
	else
	{
		bit::clear(RDES[1], 15);
	}
}


constexpr inline void EthernetDMA_RxDescriptor::secondAddressChained(bool isSecondAddressChained)
{
	if(isSecondAddressChained == true)
	{
		bit::set(RDES[1], 14);
	}
	else
	{
		bit::clear(RDES[1], 14);
	}
}







constexpr inline bool EthernetDMA_RxDescriptor::isFirstDescriptorOfFrame() const
{
	return(bit::isSet(RDES[0], 9));
}


constexpr inline bool EthernetDMA_RxDescriptor::isLastDescriptorOfFrame() const
{
	return(bit::isSet(RDES[0], 8));
}


constexpr inline bool EthernetDMA_RxDescriptor::wasDestinationAddressFilterFailed() const
{
	return(bit::isSet(RDES[0], 30));
}


constexpr inline bool EthernetDMA_RxDescriptor::wasSourceAddressFilterFailed() const
{
	return(bit::isSet(RDES[0], 13));
}


constexpr inline bool EthernetDMA_RxDescriptor::wasVLANFrame() const
{
	return(bit::isSet(RDES[0], 10));
}


constexpr inline bool EthernetDMA_RxDescriptor::isEthernetFrame() const
{
	return(bit::isSet(RDES[0], 5));
}


constexpr inline uint16 EthernetDMA_RxDescriptor::getFrameLength() const
{
	return((RDES[0] & 0x3FFF0000) >> 16);
}







constexpr inline bool EthernetDMA_RxDescriptor::errorSummary() const
{
	return(bit::isSet(RDES[0], 15));
}


constexpr inline bool EthernetDMA_RxDescriptor::errorIPHeaderChecksum() const
{
	return(bit::isSet(RDES[0], 7));
}


constexpr inline bool EthernetDMA_RxDescriptor::errorIPPayloadChecksum() const
{
	return(bit::isSet(RDES[0], 0));
}


constexpr inline bool EthernetDMA_RxDescriptor::errorDescriptor() const
{
	return(bit::isSet(RDES[0], 14));
}


constexpr inline bool EthernetDMA_RxDescriptor::errorLength() const
{
	return(bit::isSet(RDES[0], 12));
}


constexpr inline bool EthernetDMA_RxDescriptor::errorOverflow() const
{
	return(bit::isSet(RDES[0], 11));
}


constexpr inline bool EthernetDMA_RxDescriptor::errorLateCollision() const
{
	return(bit::isSet(RDES[0], 6));
}


constexpr inline bool EthernetDMA_RxDescriptor::errorReceiveWatchdogTimeout() const
{
	return(bit::isSet(RDES[0], 4));
}


constexpr inline bool EthernetDMA_RxDescriptor::errorReceive() const
{
	return(bit::isSet(RDES[0], 3));
}


constexpr inline bool EthernetDMA_RxDescriptor::errorDribbleBit() const
{
	return(bit::isSet(RDES[0], 2));
}


constexpr inline bool EthernetDMA_RxDescriptor::errorCRC() const
{
	return(bit::isSet(RDES[0], 1));
}







constexpr inline void EthernetDMA_RxDescriptor::setBuffer1Size(uint16 size)
{
	uint32 temp = RDES[1] & 0xFFFFE000;
	RDES[1] = temp | (size & 0x1FFF);
}


constexpr inline void EthernetDMA_RxDescriptor::setBuffer2Size(uint16 size)
{
	uint32 temp = RDES[1] & 0xE000FFFF;
	RDES[1] = temp | ((size & 0x1FFF) << 16);
}


constexpr inline void EthernetDMA_RxDescriptor::setBuffer1Address(uint32 address)
{
	RDES[2] = address;
}


constexpr inline void EthernetDMA_RxDescriptor::setBuffer2Address(uint32 address)
{
	RDES[3] = address;
}


constexpr inline uint64 EthernetDMA_RxDescriptor::getTimeStampCaptured() const
{
	return((((uint64) RDES[2]) << 32) | RDES[3]);
}







constexpr inline uint8* EthernetDMA_RxDescriptor::getBuffer1Address() const
{
	return((uint8*) RDES[2]);
}


constexpr inline uint8* EthernetDMA_RxDescriptor::getBuffer2Address() const
{
	return((uint8*) RDES[3]);
}