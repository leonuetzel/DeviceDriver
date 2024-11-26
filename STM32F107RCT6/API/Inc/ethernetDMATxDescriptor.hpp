#pragma once

#include "cmos.hpp"





class EthernetDMA_TxDescriptor
{
	public:
		
		enum class e_checkSumInsertionControl: uint8
		{
			DISABLED																= 0x00,
			IP_HEADER_ONLY													= 0x01,
			IP_HEADER_AND_PAYLOAD_ONLY							= 0x02,
			IP_HEADER_AND_PAYLOAD_AND_PSEUDOHEADER	= 0x03
		};
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		uint32 TDES[4];
		
		
		//	Constructor and Destructor
		
		
		
		//	Member Functions
		
		
		
		//	Friends
		
		
		
		
		
		
	public:
		
		constexpr inline void setOwnershipToDMA();
		constexpr inline void setOwnershipToCPU();
		constexpr inline bool isOwnedByDMA() const;
		
		constexpr inline void interruptOnCompletion(bool enable);
		constexpr inline void firstDescriptorOfFrame(bool isFirstDescriptor);
		constexpr inline void lastDescriptorOfFrame(bool isLastDescriptor);
		constexpr inline void finalDescriptorOfDescriptorList(bool isFinalDescriptor);
		constexpr inline void automaticallyGenerateCRC(bool enable);
		constexpr inline void automaticallyPadPackets(bool enable);
		constexpr inline void transmitTimeStampsIEEE1588(bool enable);
		constexpr inline void setCheckSumInsertionControl(e_checkSumInsertionControl checkSumInsertionControl);
		constexpr inline void secondAddressChained(bool isSecondAddressChained);
		
		constexpr inline bool wasTimeStampCaptured() const;
		constexpr inline bool frameFlushedBySoftwareCommand() const;
		constexpr inline bool wasVLANFrame() const;
		constexpr inline uint8 getCollisionCounter() const;
		
		constexpr inline bool errorSummary() const;
		constexpr inline bool errorIPHeaderChecksum() const;
		constexpr inline bool errorIPPayloadChecksum() const;
		constexpr inline bool errorJabberTimeout() const;
		constexpr inline bool errorLossOfCarrier() const;
		constexpr inline bool errorNoCarrier() const;
		constexpr inline bool errorLateCollision() const;
		constexpr inline bool errorExcessiveCollision() const;
		constexpr inline bool errorExcessiveDeferral() const;
		constexpr inline bool errorUnderflow() const;
		constexpr inline bool errorDeferredTransmission() const;
		
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

constexpr inline void EthernetDMA_TxDescriptor::setOwnershipToDMA()
{
	bit::set(TDES[0], 31);
}


constexpr inline void EthernetDMA_TxDescriptor::setOwnershipToCPU()
{
	bit::clear(TDES[0], 31);
}


constexpr inline bool EthernetDMA_TxDescriptor::isOwnedByDMA() const
{
	return(bit::isSet(TDES[0], 31));
}







constexpr inline void EthernetDMA_TxDescriptor::interruptOnCompletion(bool enable)
{
	if(enable == true)
	{
		bit::set(TDES[0], 30);
	}
	else
	{
		bit::clear(TDES[0], 30);
	}
}


constexpr inline void EthernetDMA_TxDescriptor::firstDescriptorOfFrame(bool isFirstDescriptor)
{
	if(isFirstDescriptor == true)
	{
		bit::set(TDES[0], 28);
	}
	else
	{
		bit::clear(TDES[0], 28);
	}
}


constexpr inline void EthernetDMA_TxDescriptor::lastDescriptorOfFrame(bool isLastDescriptor)
{
	if(isLastDescriptor == true)
	{
		bit::set(TDES[0], 29);
	}
	else
	{
		bit::clear(TDES[0], 29);
	}
}


constexpr inline void EthernetDMA_TxDescriptor::finalDescriptorOfDescriptorList(bool isFinalDescriptor)
{
	if(isFinalDescriptor == true)
	{
		bit::set(TDES[0], 21);
	}
	else
	{
		bit::clear(TDES[0], 21);
	}
}


constexpr inline void EthernetDMA_TxDescriptor::automaticallyGenerateCRC(bool enable)
{
	if(enable == false)
	{
		bit::set(TDES[0], 27);
	}
	else
	{
		bit::clear(TDES[0], 27);
	}
}


constexpr inline void EthernetDMA_TxDescriptor::automaticallyPadPackets(bool enable)
{
	if(enable == false)
	{
		bit::set(TDES[0], 26);
	}
	else
	{
		bit::clear(TDES[0], 26);
	}
}


constexpr inline void EthernetDMA_TxDescriptor::transmitTimeStampsIEEE1588(bool enable)
{
	if(enable == true)
	{
		bit::set(TDES[0], 25);
	}
	else
	{
		bit::clear(TDES[0], 25);
	}
}


constexpr inline void EthernetDMA_TxDescriptor::setCheckSumInsertionControl(e_checkSumInsertionControl checkSumInsertionControl)
{
	uint32 temp = (TDES[0] & 0xFF3FFFFF);
	TDES[0] = temp | (((uint32) checkSumInsertionControl) << 22);
}


constexpr inline void EthernetDMA_TxDescriptor::secondAddressChained(bool isSecondAddressChained)
{
	if(isSecondAddressChained == true)
	{
		bit::set(TDES[0], 20);
	}
	else
	{
		bit::clear(TDES[0], 20);
	}
}







constexpr inline bool EthernetDMA_TxDescriptor::wasTimeStampCaptured() const
{
	return(bit::isSet(TDES[0], 17));
}


constexpr inline bool EthernetDMA_TxDescriptor::frameFlushedBySoftwareCommand() const
{
	return(bit::isSet(TDES[0], 13));
}


constexpr inline bool EthernetDMA_TxDescriptor::wasVLANFrame() const
{
	return(bit::isSet(TDES[0], 7));
}


constexpr inline uint8 EthernetDMA_TxDescriptor::getCollisionCounter() const
{
	return((TDES[0] & 0x00000078) >> 3);
}







constexpr inline bool EthernetDMA_TxDescriptor::errorSummary() const
{
	return(bit::isSet(TDES[0], 15));
}


constexpr inline bool EthernetDMA_TxDescriptor::errorIPHeaderChecksum() const
{
	return(bit::isSet(TDES[0], 16));
}


constexpr inline bool EthernetDMA_TxDescriptor::errorIPPayloadChecksum() const
{
	return(bit::isSet(TDES[0], 12));
}


constexpr inline bool EthernetDMA_TxDescriptor::errorJabberTimeout() const
{
	return(bit::isSet(TDES[0], 14));
}


constexpr inline bool EthernetDMA_TxDescriptor::errorLossOfCarrier() const
{
	return(bit::isSet(TDES[0], 11));
}


constexpr inline bool EthernetDMA_TxDescriptor::errorNoCarrier() const
{
	return(bit::isSet(TDES[0], 10));
}


constexpr inline bool EthernetDMA_TxDescriptor::errorLateCollision() const
{
	return(bit::isSet(TDES[0], 9));
}


constexpr inline bool EthernetDMA_TxDescriptor::errorExcessiveCollision() const
{
	return(bit::isSet(TDES[0], 8));
}


constexpr inline bool EthernetDMA_TxDescriptor::errorExcessiveDeferral() const
{
	return(bit::isSet(TDES[0], 2));
}


constexpr inline bool EthernetDMA_TxDescriptor::errorUnderflow() const
{
	return(bit::isSet(TDES[0], 1));
}


constexpr inline bool EthernetDMA_TxDescriptor::errorDeferredTransmission() const
{
	return(bit::isSet(TDES[0], 0));
}







constexpr inline void EthernetDMA_TxDescriptor::setBuffer1Size(uint16 size)
{
	uint32 temp = TDES[1] & 0xFFFFE000;
	TDES[1] = temp | (size & 0x00001FFF);
}


constexpr inline void EthernetDMA_TxDescriptor::setBuffer2Size(uint16 size)
{
	uint32 temp = TDES[1] & 0xE000FFFF;
	TDES[1] = temp | ((size & 0x00001FFF) << 16);
}


constexpr inline void EthernetDMA_TxDescriptor::setBuffer1Address(uint32 address)
{
	TDES[2] = address;
}


constexpr inline void EthernetDMA_TxDescriptor::setBuffer2Address(uint32 address)
{
	TDES[3] = address;
}


constexpr inline uint64 EthernetDMA_TxDescriptor::getTimeStampCaptured() const
{
	return((((uint64) TDES[3]) << 32) | TDES[2]);
}







constexpr inline uint8* EthernetDMA_TxDescriptor::getBuffer1Address() const
{
	return((uint8*) TDES[2]);
}


constexpr inline uint8* EthernetDMA_TxDescriptor::getBuffer2Address() const
{
	return((uint8*) TDES[3]);
}