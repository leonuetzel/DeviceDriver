#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "graphics/i_displayDriver.hpp"
#include "rcc.hpp"





class LTDC	:	public I_DisplayDriver
{
	public:
		
		static constexpr uint32 c_layer_number = 2;
		
		
		
		
		
	private:
		
		static uint8 m_fps;
		static uint8 m_thread;
		
		s_displayData m_displayData;
		RectGraphic m_layer[c_layer_number];
		uint32 m_layerNumber;
		Color m_colorBackground;
		
		constexpr inline LTDC();
		LTDC(const LTDC& ltdc) = delete;
		inline ~LTDC();
		
		friend void ISR_LTDC();
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup(RCC& rcc);
		feedback init(s_displayData displayData, Array<RectGraphic> layer);
		
		
		
		feedback set_thread()																							override;
		uint16 get_wakeUpInterrupt()																			override;
		
		feedback start()																									override;
		feedback stop()																										override;
		feedback set_layerBuffer(uint32 layer, Color* buffer)							override;
		feedback clear(uint32 layer)																			override;
		feedback set_colorBackground(uint8 red, uint8 green, uint8 blue)	override;
		feedback set_layerAlpha(uint8 layer, uint8 alpha)									override;
		feedback set_pixel(Vec2& position, Color color, uint32 layer)			override;
		
		s_displayData& get_displayData()																	override;
		Vec2 get_displayDimensions()																			override;
		RectGraphic& get_layerData(uint32 layer)													override;
		uint32 get_numberOfLayers()																				override;
		uint32 get_fps()																									override;
		Color get_colorBackground()																				override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline LTDC::LTDC()
	:	m_displayData(),
		m_layer(),
		m_layerNumber(),
		m_colorBackground(Colors::transparent)
{
	m_thread = 0xFF;
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

