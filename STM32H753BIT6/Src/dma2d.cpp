#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/

I_Semaphore* DMA2D::m_semaphore;
I_GraphicAccelerator::f_callback DMA2D::m_callback;



/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback DMA2D::startup()
{
	RCC& rcc = STM32H753BIT6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::DMA2D, true);
	return(OK);
}


CODE_RAM void DMA2D::lock()
{
	CMOS& cmos = CMOS::get();
	
	while(1)
	{
		if(is_available() == true)
		{
			if(m_semaphore->lock() == OK)
			{
				return;
			}
		}
		cmos.sleep_100us(1);
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

CODE_RAM bool DMA2D::is_available() const
{
	if(bit::isSet(*MCU::DMA2D::CR, 0))
	{
		return(false);
	}
	return(true);
}


uint16 DMA2D::get_wakeUpInterrupt() const
{
	return(Interrupt::DMA2D);
}







CODE_RAM void DMA2D::draw_rectangleFull(const RectGraphic& output, Color color, f_callback callback)
{
	lock();
	m_callback = callback;
	
	/* Register-to-Memory Mode, Line Offset expressed in Pixels, TC and TE Interrupt enabled */
	*MCU::DMA2D::CR				= 0x00030300;
	*MCU::DMA2D::IFCR			= 0x0000003F;																																														//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.data;																																								//	Pixel Data to write to
	*MCU::DMA2D::O_OR			= 0;																																																		//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR	= 0;																																																		//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR		= (color.alpha << 24) | (color.red << 16) | (color.green << 8) | color.blue;														//	Output Color
	*MCU::DMA2D::NLR				= (output.size.x << 16) | output.size.y;																															//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR		= 0;																																																		//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR		= 0;																																																		//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	bit::set(*MCU::DMA2D::CR, 0);																																																	//	Start Drawing
}


CODE_RAM void DMA2D::draw_rectangleFull(const RectGraphic& output, Color color, Rect rectangle, f_callback callback)
{
	lock();
	m_callback = callback;
	
	/* Register-to-Memory Mode, Line Offset expressed in Pixels, TC and TE Interrupt enabled */
	*MCU::DMA2D::CR				= 0x00030300;
	*MCU::DMA2D::IFCR			= 0x0000003F;																																														//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(rectangle);																																//	Pixel Data to write to
	*MCU::DMA2D::O_OR			= output.size.x - rectangle.size.x;																																			//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR	= 0;																																																		//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR		= (color.alpha << 24) | (color.red << 16) | (color.green << 8) | color.blue;														//	Output Color
	*MCU::DMA2D::NLR				= (rectangle.size.x << 16) | rectangle.size.y;																												//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR		= 0;																																																		//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR		= 0;																																																		//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	bit::set(*MCU::DMA2D::CR, 0);																																																	//	Start Drawing
}


CODE_RAM void DMA2D::draw_rectangleFull(const RectGraphic& output, const RectGraphic& foreground, f_callback callback)
{
	lock();
	m_callback = callback;
	
	/* Memory-to-Memory Mode with Foreground Fetch only, Line Offset expressed in Pixels, TC and TE Interrupt enabled */
	*MCU::DMA2D::CR				= 0x00000300;
	*MCU::DMA2D::IFCR			= 0x0000003F;																																														//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(foreground);																																//	Pixel Data to write to
	*MCU::DMA2D::O_OR			= output.size.x - foreground.size.x;																																		//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR	= 0;																																																		//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR		= 0;																																																		//	Output Color
	*MCU::DMA2D::NLR				= (foreground.size.x << 16) | foreground.size.y;																											//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR		= (uint32) foreground.data;																																							//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR		= 0;																																																		//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	bit::set(*MCU::DMA2D::CR, 0);																																																	//	Start Drawing
}


CODE_RAM void DMA2D::draw_rectangleFull(const RectGraphic& output, const RectGraphic& foreground, const RectGraphic& background, f_callback callback)
{
	lock();
	m_callback = callback;
	
	/* Memory-to-Memory Mode with PFC and Blending - Foreground and Background Fetch, Line Offset expressed in Pixels, TC and TE Interrupt enabled */
	*MCU::DMA2D::CR				= 0x00020300;
	*MCU::DMA2D::IFCR			= 0x0000003F;																																														//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(foreground);																																//	Pixel Data to write to
	*MCU::DMA2D::O_OR			= output.size.x - foreground.size.x;																																		//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR	= 0;																																																		//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR		= 0;																																																		//	Output Color
	*MCU::DMA2D::NLR				= (foreground.size.x << 16) | foreground.size.y;																											//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR		= (uint32) foreground.data;																																							//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR		= (uint32) background.get_data(foreground);																															//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= background.size.x - foreground.size.x;																															//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	bit::set(*MCU::DMA2D::CR, 0);																																																	//	Start Drawing
}


CODE_RAM void DMA2D::draw_rectangleFull(const RectGraphic& output, const Rect& foreground, const RectGraphic& background, Color color_foreground, f_callback callback)
{
	lock();
	m_callback = callback;
	
	/* Memory-to-Memory Mode with PFC and Blending - Background Fetch only - Foreground Fixed Color, Line Offset expressed in Pixels, TC and TE Interrupt enabled */
	*MCU::DMA2D::CR				= 0x00040300;
	*MCU::DMA2D::IFCR			= 0x0000003F;																																														//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(foreground);																																//	Pixel Data to write to
	*MCU::DMA2D::O_OR			= output.size.x - foreground.size.x;																																		//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR	= 0;																																																		//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR		= 0;																																																		//	Output Color
	*MCU::DMA2D::NLR				= (foreground.size.x << 16) | foreground.size.y;																											//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR		= 0;																																																		//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0x00010000 | (color_foreground.alpha << 24);																												//	ARGB8888 Pixel Format, Modified Alpha Value
	*MCU::DMA2D::FG_COLR		= (color_foreground.red << 16) | (color_foreground.green << 8) | color_foreground.blue;								//	Foreground Color
	
	*MCU::DMA2D::BG_MAR		= (uint32) background.get_data(foreground);																															//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= background.size.x - foreground.size.x;																															//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	bit::set(*MCU::DMA2D::CR, 0);																																																	//	Start Drawing
}


CODE_RAM void DMA2D::draw_rectangleFull(const RectGraphic& output, const RectGraphic& foreground, const Rect& background, Color color_background, f_callback callback)
{
	lock();
	m_callback = callback;
	
	/* Memory-to-Memory Mode with PFC and Blending - Foreground Fetch only - Background Fixed Color, Line Offset expressed in Pixels, TC and TE Interrupt enabled */
	*MCU::DMA2D::CR				= 0x00050300;
	*MCU::DMA2D::IFCR			= 0x0000003F;																																														//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(foreground);																																//	Pixel Data to write to
	*MCU::DMA2D::O_OR			= output.size.x - foreground.size.x;																																		//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR	= 0;																																																		//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR		= 0;																																																		//	Output Color
	*MCU::DMA2D::NLR				= (foreground.size.x << 16) | foreground.size.y;																											//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR		= (uint32) foreground.data;																																							//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR		= 0;																																																		//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= background.size.x - foreground.size.x;																															//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0x00010000 | (color_background.alpha << 24);																												//	ARGB8888 Pixel Format, Modified Alpha Value
	*MCU::DMA2D::BG_COLR		= (color_background.red << 16) | (color_background.green << 8) | color_background.blue;								//	Background Color
	
	bit::set(*MCU::DMA2D::CR, 0);																																																	//	Start Drawing
}







CODE_RAM void DMA2D::cutOut(const RectGraphic& destination, const RectGraphic& source, f_callback callback)
{
	lock();
	m_callback = callback;
	
	/* Memory-to-Memory Mode with Foreground Fetch only, Line Offset expressed in Pixels, TC and TE Interrupt enabled */
	*MCU::DMA2D::CR				= 0x00000300;
	*MCU::DMA2D::IFCR			= 0x0000003F;																																														//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) destination.data;																																					//	Pixel Data to write to
	*MCU::DMA2D::O_OR			= 0;																																																		//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR	= 0;																																																		//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR		= 0;																																																		//	Output Color
	*MCU::DMA2D::NLR				= (destination.size.x << 16) | destination.size.y;																										//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR		= (uint32) source.get_data(destination);																																//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= source.size.x - destination.size.x;																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR		= 0;																																																		//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	bit::set(*MCU::DMA2D::CR, 0);																																																	//	Start Drawing
}









CODE_RAM void ISR_DMA2D()
{
	*MCU::DMA2D::IFCR = 0x0000003F;
	
	DMA2D::m_semaphore->force_unlock();
	if(DMA2D::m_callback != nullptr)
	{
		DMA2D::m_callback();
	}
}