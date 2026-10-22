#pragma once

#include "cmos.hpp"
#include "i_updateMemory.hpp"
#include "bootControl.hpp"





//	Memory of the Firmware Update (I_UpdateMemory of CMOS) with Mini-Bootloader and Rollback: Layout and Flash Functions in bootFlash.hpp,
//	State of the Update in the Control Blocks (bootControl.hpp). The Driver reads only their Headers
class Update: public I_UpdateMemory
{
	public:
	
	
	
	
	
	
	
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline Update();
		Update(const Update& update) = delete;
		inline ~Update();
		
		
		//	Member Functions
		inline feedback startup();
		feedback prepareDownload();
		feedback cleanup(const BootControl::s_state& state);
		uint32 get_limitBlocks(uint32 numberOfBlocks) const;
		
		
		//	Friends
		friend class STM32G474MCT6;
	
	
	
	
	
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

