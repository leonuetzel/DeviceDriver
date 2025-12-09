#pragma once

#include "cmos.hpp"





class SDMMC_1: public I_Drive
{
	public:
		
		typedef feedback (*f_power)(bool enable);
		typedef bool (*f_detect)();
		
		
		
		
		
	private:
		
		//	Static Member
		static constexpr uint32 c_sectorSizeInBytes = 512;
		
		enum class e_busWidth
		{
			BUSWIDTH_1								= 0x0,
			BUSWIDTH_4								= 0x1,
			BUSWIDTH_8								= 0x2
		};
		
		
		
		/* Control Path */
		
		enum class e_commandPath_response
		{
			NONE											= 0,
			SHORT_WITH_CRC						= 1,
			SHORT_NO_CRC							= 2,
			LONG											= 3
		};
		
		enum class e_commandPath_command
		{
			ID_0_GO_IDLE_STATE												=  0 | ((uint32) e_commandPath_response::NONE						<< 8),
			
			ID_2_ALL_SEND_CID													=  2 | ((uint32) e_commandPath_response::LONG 					<< 8),
			ID_3_PUBLISH_NEW_RCA											=  3 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_4_SET_DSR															=  4 | ((uint32) e_commandPath_response::NONE 					<< 8),
			
			ID_6_SET_BUS_WIDTH												=  6 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_7_SELECT_DESELECT_CARD									=  7 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_8_SEND_IF_CONDITION										=  8 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_9_SEND_CSD															=  9 | ((uint32) e_commandPath_response::LONG 					<< 8),
			ID_10_SEND_CID														= 10 | ((uint32) e_commandPath_response::LONG 					<< 8),
			ID_11_VOLTAGE_SWITCH											= 11 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_12_STOP_TRANSMISSION										= 12 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_13_SEND_SD_STATUS											= 13 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			
			ID_15_GO_INACTIVE_STATE										= 15 | ((uint32) e_commandPath_response::NONE 					<< 8),
			ID_16_SET_BLOCK_LENGTH										= 16 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_17_READ_SINGLE_BLOCK										= 17 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_18_READ_MULITPLE_BLOCK									= 18 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_19_SEND_TUNING_BLOCK										= 19 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_20_SPEED_CLASS_CONTROL									= 20 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			
			ID_22_SEND_NUM_OF_WRITTEN_BLOCKS					= 22 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_23_SET_BLOCK_COUNT											= 23 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_24_WRITE_BLOCK													= 24 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_25_WRITE_MULTIPLE_BLOCK								= 25 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			
			ID_27_PROGRAM_CSD													= 27 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_28_SET_WRITE_PROTECTION								= 28 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_29_CLEAR_WRITE_PROTECTION							= 29 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_30_SEND_WRITE_PROTECTION								= 30 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			
			ID_32_ERASE_WRITE_BLOCK_START							= 32 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_33_ERASE_WRITE_BLOCK_END								= 33 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			
			
			
			
			ID_38_ERASE																= 38 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			
			ID_40_SINGLE_BLOCK_READ_TYPE							= 40 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_41_SD_SEND_OPERATION_CONDITION					= 41 | ((uint32) e_commandPath_response::SHORT_NO_CRC 	<< 8),
			ID_42_SET_CLEAR_CARD_DETECT								= 42 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_42_LOCK_UNLOCK													= 42 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_43_QUEUE_MANAGEMENT										= 43 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_44_QUEUE_TASK_INFO_A										= 44 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_45_QUEUE_TASK_INFO_B										= 45 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_46_QUEUE_TASK_READ_OPERATION						= 46 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_47_QUEUE_TASK_WRITE_OPERATION					= 47 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_48_READ_EXTR_SINGLE										= 48 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_49_WRITE_EXTR_SINGLE										= 49 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			
			ID_51_SEND_SCR														= 51 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			
			
			
			ID_55_APP_CMD															= 55 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_56_GEN_CMD															= 56 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			
			ID_58_READ_EXTR_MULTIPLE									= 58 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8),
			ID_59_WRITE_EXTR_MULTIPLE									= 59 | ((uint32) e_commandPath_response::SHORT_WITH_CRC << 8)
		};
		
		typedef struct
		{
			e_commandPath_command command;
			uint32 argument;
			bool dataTransfer;
		}s_commandPath;
		
		
		
		/* Data Path */
		
		enum class e_dataPath_blockSize
		{
			SIZE_1_BYTE								= 0,
			SIZE_2_BYTE								= 1,
			SIZE_4_BYTE								= 2,
			SIZE_8_BYTE								= 3,
			SIZE_16_BYTE							= 4,
			SIZE_32_BYTE							= 5,
			SIZE_64_BYTE							= 6,
			SIZE_128_BYTE							= 7,
			SIZE_256_BYTE							= 8,
			SIZE_512_BYTE							= 9,
			SIZE_1024_BYTE						= 10,
			SIZE_2048_BYTE						= 11,
			SIZE_4096_BYTE						= 12,
			SIZE_8192_BYTE						= 13,
			SIZE_16384_BYTE						= 14
		};
		
		enum class e_dataPath_transferMode
		{
			BLOCK											= 0,
			SDIO_MULTIBYTE						= 1,
			EMMC_STREAM								= 2,
			BLOCK_WITH_STOP						= 3
		};
		
		enum class e_dataPath_transferDirection
		{
			HOST_TO_CARD							= 0,
			CARD_TO_HOST							= 1
		};
		
		typedef struct
		{
			e_dataPath_blockSize blockSize;
			e_dataPath_transferMode mode;
			e_dataPath_transferDirection direction;
			uint32 data_sizeInBytes;
			uint32 timeout;
		}s_dataPath;
		
		
		
		/* Response */
		
		typedef struct
		{
			feedback success;
			uint32 response_127_96;
			uint32 response_95_64;
			uint32 response_63_32;
			uint32 response_31_0;
		}s_response;
		
		
		
		
		
		/* CID */
		
		typedef struct
		{
			uint8 manufacturer_ID;
			char application_ID[2];
			char product_name[5];
			uint8 product_revision;
			uint32 serial_number;
			uint16 manufacturing_year;
			uint8 manufacturing_month;
		}s_CID;
		
		
		
		/* CSD */
		
		enum class e_CSD_capacity
		{
			SD												= 0,
			SDHC_SDXC									= 1
		};
		
		typedef struct
		{
			e_CSD_capacity csd_structure;
			bool command_classes[12];
			bool driverStage_implemented;
			uint32 userData_capacity_MByte;
			bool copy;
			bool writeProtection_permanent;
			bool writeProtection_temporarily;
		}s_CSD;
		
		
		
		/* SD Status */
		
		enum class e_SDStatus_busWidth
		{
			BUSWIDTH_1								= 0,
			BUSWIDTH_4								= 2,
		};
		
		enum class e_SDStatus_cardType
		{
			REGULAR										= 0,
			ROM												= 1,
			OTP												= 2
		};
		
		enum class e_SDStatus_speedClass
		{
			SPEEDCLASS_0							= 0,
			SPEEDCLASS_2							= 1,
			SPEEDCLASS_4							= 2,
			SPEEDCLASS_6							= 3,
			SPEEDCLASS_10							= 4
		};
		
		typedef struct
		{
			e_SDStatus_busWidth busWidth;
			bool secured_mode;
			e_SDStatus_cardType cardType;
			uint32 protectedArea_sizeInBytes;
			e_SDStatus_speedClass speedClass;
			uint8 performanceMove_MBps;
		}s_SDStatus;
		
		
		//	Non-static Member
		I_Semaphore& m_semaphore;
		f_power m_power;
		f_detect m_detect;
		uint32 m_changeCounter;
		
		
		bool m_enabled;
		RCC::e_clockSource_sdmmc m_clockSource;
		uint32 m_clock;
		e_busWidth m_busWidth;
		uint16 m_RCA;
		s_CID m_CID;
		s_CSD m_CSD;
		s_SDStatus m_SDStatus;
		
		
		//	Constructor and Destructor
		constexpr inline SDMMC_1(I_Semaphore& semaphore);
		SDMMC_1(const SDMMC_1& sdmmc_1) = delete;
		inline ~SDMMC_1();
		
		
		//	Member Functions
		feedback startup();
		
		feedback set_clockSpeed(RCC& rcc, uint32 clock);
		feedback set_busWidth(e_busWidth busWidth);
		s_response send_command(s_commandPath command) const;
		void setup_dataPath(s_dataPath dataPath) const;
		
		feedback command_reset();
		feedback command_operatingConditionValidation();
		feedback command_set_operatingCondition();
		feedback command_request_CID();
		feedback command_publish_newRCA();
		feedback command_request_CSD();
		feedback command_cardSelect();
		feedback command_set_busWidth();
		feedback command_send_SDStatus();
		feedback command_read_singleBlock(uint32 block) const;
		feedback command_write_singleBlock(uint32 block) const;
		
		
		//	Friends
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback init(RCC& rcc, RCC::e_clockSource_sdmmc clockSource, f_power power, f_detect detect);
		
		feedback enable()																																override;
		feedback disable()																															override;
		bool detect() const																															override;
		uint32 get_changeStamp() const																									override;
		uint8* read(uint32 startSector, uint32 numberOfSectors) const										override;
		feedback read(uint32 startSector, uint32 numberOfSectors, uint8* target) const	override;
		feedback write(uint32 startSector, uint32 numberOfSectors, uint8* data) const		override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline SDMMC_1::SDMMC_1(I_Semaphore& semaphore)
	:	m_semaphore(semaphore),
		m_power(nullptr),
		m_detect(nullptr),
		m_changeCounter(0),
		
		m_enabled(false),
		m_clockSource(RCC::e_clockSource_sdmmc::PLL_1_Q),
		m_clock(0),
		m_busWidth(e_busWidth::BUSWIDTH_1),
		m_RCA(0),
		m_CID(),
		m_CSD(),
		m_SDStatus()
{
	
}


inline SDMMC_1::~SDMMC_1()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

