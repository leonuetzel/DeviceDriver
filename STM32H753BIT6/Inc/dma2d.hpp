#pragma once

#include "registers.hpp"
#include "cmos.hpp"
#include "rcc.hpp"
#include "ltdc.hpp"

#include "graphics/i_graphicAccelerator.hpp"
#include "i_semaphore.hpp"





class DMA2D: public I_GraphicAccelerator
{
	public:
		
		
		
		
		
		
		
	private:
		
		static I_Semaphore* m_semaphore;
		static f_callback m_callback;
		
		constexpr inline DMA2D(I_Semaphore& semaphore);
		DMA2D(const DMA2D& dma2d) = delete;
		inline ~DMA2D();
		
		void lock();
		
		friend void ISR_DMA2D();
		friend class STM32H753BIT6;
		
		
		
		
		
	public:
		
		feedback startup(RCC& rcc);
		
		bool is_available() const																																																																															override;
		uint16 get_wakeUpInterrupt() const																																																																										override;
		
		void draw_rectangleFull(const RectGraphic& output, Color							color,			f_callback					callback = nullptr)																															override;
		void draw_rectangleFull(const RectGraphic& output, Color							color,			Rect								rectangle,				f_callback	callback = nullptr)																override;
		void draw_rectangleFull(const RectGraphic& output, const RectGraphic& foreground, f_callback					callback = nullptr)																															override;
		void draw_rectangleFull(const RectGraphic& output, const RectGraphic& foreground, const RectGraphic&	background,				f_callback	callback = nullptr)																override;
		void draw_rectangleFull(const RectGraphic& output, const Rect&				foreground, const RectGraphic&	background,				Color				color_foreground,	f_callback callback = nullptr)	override;
		void draw_rectangleFull(const RectGraphic& output, const RectGraphic&	foreground, const Rect&					background,				Color				color_background,	f_callback callback = nullptr)	override;
		
		void cutOut(const RectGraphic& destination, const RectGraphic& source, f_callback callback = nullptr)																																									override;
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

constexpr inline DMA2D::DMA2D(I_Semaphore& semaphore)
{
	m_semaphore = &semaphore;
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

