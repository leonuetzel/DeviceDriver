#pragma once

#include "cmos.hpp"





class DMA2D: public I_GraphicAccelerator
{
	public:
		
		
		
		
		
		
		
	private:
		
		//	Static Member
		bool m_transferActive;
		uint32 m_counterConfigurationError;
		uint32 m_counterClutAccessError;
		uint32 m_counterTransferError;
		
		
		//	Non-static Member
		
		
		
		//	Constructor and Destructor
		constexpr inline DMA2D();
		DMA2D(const DMA2D& dma2d) = delete;
		inline ~DMA2D();
		
		
		//	Member Functions
		feedback startup();
		
		
		//	Friends
		friend void ISR_DMA2D();
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		//	Colors the whole output buffer with a single color
		void fillRectangleWithSingleColor(const RectGraphic& output, Color color) override;
		
		//	Colors a rectangle with dimensions "rectangle" in the output buffer with a single color
		//	The position of the rectangle is related to the output buffers coordinate system
		void drawfilledRectangleWithSingleColor(const RectGraphic& output, Color color, Rect rectangle) override;
		
		//	Copies the whole foreground buffer to the output buffer by placing the foreground rectangle inside the output rectangle
		//	The position of the foreground rectangle is related to the output buffers coordinate system
		void copyForegroundToOutput(const RectGraphic& output, const RectGraphic& foreground, uint8 alphaFactor = 0xFF) override;
		
		//	Copies the specified rectangle from the foreground buffer to the specified position in the output buffer
		//	The position of the foreground rectangle and the position in the output buffer is related to the output buffers coordinate system
		void copyForegroundRectangleToOutputPosition(const RectGraphic& output, const RectGraphic& foreground, Rect rectangle, Vec2 position, uint8 alphaFactor = 0xFF) override;
		
		//	Blends the foreground buffer with the background buffer and copies the result to the output buffer
		//	The alpha factors can be used to set the transparency of the foreground and background buffers. 0xFF means fully opaque, 0x00 means fully transparent.
		//	The position of the foreground and background rectangles is related to the output buffers coordinate system
		void blendForegroundAndBackgroundToOutput(const RectGraphic& output, const RectGraphic& foreground, const RectGraphic& background, uint8 alphaFactorForeground = 0xFF, uint8 alphaFactorBackground = 0xFF) override;
		
		//	Blends the foreground rectangle (constant color) with the background buffer and copies the result to the output buffer
		//	The position of the foreground and background rectangles is related to the output buffers coordinate system
		void blendBackgroundWithConstantForegroundToOutput(const RectGraphic& output, const Rect& foreground, const RectGraphic& background, Color color_foreground) override;
		
		//	Blends the foreground buffer with the background rectangle (constant color) and copies the result to the output buffer
		//	The position of the foreground and background rectangles is related to the output buffers coordinate system
		void blendForegroundWithConstantBackgroundToOutput(const RectGraphic& output, const RectGraphic& foreground, const Rect& background, Color color_background) override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline DMA2D::DMA2D()
	: m_transferActive(false),
		m_counterConfigurationError(0),
		m_counterClutAccessError(0),
		m_counterTransferError(0)
{
	
}


inline DMA2D::~DMA2D()
{
	
}



/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

