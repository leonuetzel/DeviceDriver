#pragma once

#include "cmos.hpp"
#include "i_updateMemory.hpp"





//	Memory of the Firmware Update (I_UpdateMemory of CMOS) with Bank Swap: the new Image goes into the Bank at 0x08100000,
//	the Swap (SWAP_BANK_OPT) maps it to 0x08000000 with the next Reset. No Bootloader is needed.
//	Rollback: the new Image runs on Trial until confirm() (Flash Words T and C in its Image Descriptor); its Starts are counted in
//	RTC_BKP31R, which belongs to the Update. After c_maxUnconfirmedStarts Starts the Banks are swapped back to the previous Image.
class Update: public I_UpdateMemory
{
	public:
		
		//	Device Identifier (DBGMCU_IDCODE DEV_ID, RM0433) and the two Banks of 8 Sectors of 128 KByte
		static constexpr uint32 c_deviceID						= 0x450;
		static constexpr uint32 c_bank1Address				= 0x08000000;
		static constexpr uint32 c_bank2Address				= 0x08100000;
		static constexpr uint32 c_bankSize						= 0x00100000;
		static constexpr uint32 c_sectorSize					= 0x00020000;
		
		//	Image Descriptor (imageDescriptor.cpp): Magic and Device Identifier, then T and C on Flash Words of their own (32 Bytes), then the
		//	Tag "TCV2" - Offsets from the Start of the Descriptor
		static constexpr uint32 c_flagTrialOffset			= 32;
		static constexpr uint32 c_flagConfirmedOffset	= 64;
		static constexpr uint32 c_flagTagOffset				= 96;
		static constexpr uint32 c_flagTag						= 0x32564354;			//	"TCV2"
	
	
	
	
	
	
	
	private:
		
		//	Static Member
		static constexpr uint32 c_stateMagic					= 0x5550;					//	Bits 31:16 of RTC_BKP31R: "UP"
		static constexpr uint32 c_stateTrial					= 1;
		static constexpr uint32 c_stateReverted				= 2;
		static constexpr uint32 c_stateConfirming			= 3;
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline Update();
		Update(const Update& update) = delete;
		inline ~Update();
		
		
		//	Member Functions
		inline feedback startup();
		static constexpr inline uint32 descriptorOffset();
		static void countStart();
		static bool isProgrammed(uint32 address);
		static bool isTrial();
		static uint32 readState();
		static void writeState(uint32 state, uint32 starts);
		feedback prepareDownload();
		feedback eraseOtherBank();
		
		
		//	Friends
		friend class STM32H753BIT6;
	
	
	
	
	
	public:
		
		uint32 get_capacity() const override;
		uint32 get_imageAddress() const override;
		const uint8* get_download() const override;
		uint32 get_deviceID() const override;
		uint32 get_descriptorOffset() const override;
		feedback write(uint32 offset, const uint8* data, uint32 size) override;
		feedback commit(uint32 size, uint32 crc32) override;
		feedback confirm() override;
		e_imageState get_imageState() const override;
		uint32 get_startsLeft() const override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline Update::Update()
{
	
}


inline Update::~Update()
{
	
}







inline feedback Update::startup()
{
	return(OK);
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

