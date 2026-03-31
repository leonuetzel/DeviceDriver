#pragma once

#include "cmos.hpp"





class LTDC	:	public I_DisplayDriver
{
	public:
		
		static constexpr uint32 maximumNumberOfLayers = 2;
		
		
		
		
		
	private:
		
		//	Static Member
		
		
		
		//	Non-static Member
		const uint16 m_eventID;
		uint8 m_fps;
		uint64 m_frameCounter;
		
		s_displayData m_displayData;
		RectGraphic m_layer[maximumNumberOfLayers];
		Color m_colorBackground;
		uint32 m_fifoUnderrunCounter;
		uint32 m_fifoTransmitErrorCounter;
		
		
		//	Constructor and Destructor
		inline LTDC();
		LTDC(const LTDC& ltdc) = delete;
		inline ~LTDC();
		
		
		//	Member Functions
		feedback startup();
		
		
		//	Friends
		friend void ISR_LTDC();
		friend void ISR_LTDC_ERROR();
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
	feedback init(s_displayData displayData)																						override;
	feedback set_layerData(uint32 layerNumber, RectGraphic& layerData)									override;
	
	uint16 get_eventID_vSync()																													override;
	
	feedback start()																																		override;
	feedback stop()																																			override;
	feedback set_layerBuffer(uint32 layer, Color* buffer, bool applyOnNextVsync = true)	override;
	feedback clear(uint32 layer)																												override;
	feedback set_colorBackground(Color color)																						override;
	feedback set_layerAlpha(uint8 layer, uint8 alpha)																		override;
	feedback set_pixel(Vec2& position, Color color, uint32 layer)												override;
	
	s_displayData& get_displayData()																										override;
	Vec2 get_displayDimensions()																												override;
	RectGraphic& get_layerData(uint32 layer)																						override;
	uint32 get_maximumNumberOfLayers()																									override;
	uint32 get_fps()																																		override;
	uint64& get_frameCounter()																													override;
	uint32 get_fifoUnderrunCounter()																										override;
	uint32 get_fifoTransmitErrorCounter()																								override;
	Color get_colorBackground()																													override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

inline LTDC::LTDC()
	:	m_eventID(CMOS::get().event_create()),
		m_fps(0),
		
		m_displayData(),
		m_layer(),
		m_colorBackground(Colors::transparent)
{
	
}


inline LTDC::~LTDC()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

