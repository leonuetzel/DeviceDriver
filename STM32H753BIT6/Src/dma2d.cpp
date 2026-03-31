#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback DMA2D::startup()
{
	//	Create semaphore
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_create(this) != OK)
	{
		return(FAIL);
	}
	
	
	//	Enable clock
	RCC& rcc = STM32H753BIT6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::DMA2D, true);
	
	
	//	Enable interrupt
	NVIC& nvic = cmos.get_nvic();														
	nvic.setPriority(Interrupt::DMA2D, 14);
	nvic.enable(Interrupt::DMA2D);
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

CODE_RAM void DMA2D::fillRectangleWithSingleColor(const RectGraphic& output, Color color)
{
	//	Lock semaphore to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_lock(this) != OK)
	{
		return;
	}
	
	
	//	Register-to-memory mode with PFC and blending
	//	No pixel fetch
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00032B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.data;																																								//	Pixel Data to write to
	*MCU::DMA2D::O_OR				= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= (color.alpha << 24) | (color.red << 16) | (color.green << 8) | color.blue;													//	Output Color
	*MCU::DMA2D::NLR				= (output.size.x << 16) | output.size.y;																															//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR			= 0;																																																	//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR			= 0;																																																	//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Set flag so that we can sleep until transfer is complete in the interrupt routine
	m_transferActive = true;
	
	
	//	Start transfer
	bit::set(*MCU::DMA2D::CR, 0);
	
	
	//	Wait until transfer is complete in the interrupt routine
	while(m_transferActive == true)
	{
		cmos.sleep_100us(1);
	}
	
	
	//	Unlock semaphore
	cmos.semaphore_unlock(this);
}


CODE_RAM void DMA2D::drawfilledRectangleWithSingleColor(const RectGraphic& output, Color color, Rect rectangle)
{
	//	Lock semaphore to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_lock(this) != OK)
	{
		return;
	}
	
	
	//	Register-to-memory mode with PFC and blending
	//	No pixel fetch
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00032B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(rectangle);																																//	Pixel Data to write to
	*MCU::DMA2D::O_OR				= output.size.x - rectangle.size.x;																																		//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= (color.alpha << 24) | (color.red << 16) | (color.green << 8) | color.blue;													//	Output Color
	*MCU::DMA2D::NLR				= (rectangle.size.x << 16) | rectangle.size.y;																												//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR			= 0;																																																	//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR			= 0;																																																	//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Set flag so that we can sleep until transfer is complete in the interrupt routine
	m_transferActive = true;
	
	
	//	Start transfer
	bit::set(*MCU::DMA2D::CR, 0);
	
	
	//	Wait until transfer is complete in the interrupt routine
	while(m_transferActive == true)
	{
		cmos.sleep_100us(1);
	}
	
	
	//	Unlock semaphore
	cmos.semaphore_unlock(this);
}


CODE_RAM void DMA2D::copyForegroundToOutput(const RectGraphic& output, const RectGraphic& foreground, uint8 alphaFactor)
{
	//	Lock semaphore to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_lock(this) != OK)
	{
		return;
	}
	
	
	//	Memory-to-memory mode with PFC and blending
	//	Foreground fetch only
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00002B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(foreground);																																//	Pixel Data to write to
	*MCU::DMA2D::O_OR				= output.size.x - foreground.size.x;																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= 0;																																																	//	Output Color
	*MCU::DMA2D::NLR				= (foreground.size.x << 16) | foreground.size.y;																											//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR			= (uint32) foreground.data;																																						//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= (alphaFactor << 24) | (0x2 << 16);																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR			= 0;																																																	//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Set flag so that we can sleep until transfer is complete in the interrupt routine
	m_transferActive = true;
	
	
	//	Start transfer
	bit::set(*MCU::DMA2D::CR, 0);
	
	
	//	Wait until transfer is complete in the interrupt routine
	while(m_transferActive == true)
	{
		cmos.sleep_100us(1);
	}
	
	
	//	Unlock semaphore
	cmos.semaphore_unlock(this);
}


CODE_RAM void DMA2D::copyForegroundRectangleToOutputPosition(const RectGraphic& output, const RectGraphic& foreground, Rect rectangle, Vec2 position, uint8 alphaFactor)
{
	//	Lock semaphore to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_lock(this) != OK)
	{
		return;
	}
	
	
	//	Memory-to-memory mode with PFC and blending
	//	Foreground fetch only
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00002B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(Rect(position, rectangle.size));																						//	Pixel Data to write to
	*MCU::DMA2D::O_OR				= output.size.x - rectangle.size.x;																																		//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= 0;																																																	//	Output Color
	*MCU::DMA2D::NLR				= (rectangle.size.x << 16) | rectangle.size.y;																												//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR			= (uint32) foreground.get_data(rectangle);																														//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= foreground.size.x - rectangle.size.x;																																//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= (alphaFactor << 24) | (0x2 << 16);																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR			= 0;																																																	//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Set flag so that we can sleep until transfer is complete in the interrupt routine
	m_transferActive = true;
	
	
	//	Start transfer
	bit::set(*MCU::DMA2D::CR, 0);
	
	
	//	Wait until transfer is complete in the interrupt routine
	while(m_transferActive == true)
	{
		cmos.sleep_100us(1);
	}
	
	
	//	Unlock semaphore
	cmos.semaphore_unlock(this);
}


CODE_RAM void DMA2D::blendForegroundAndBackgroundToOutput(const RectGraphic& output, const RectGraphic& foreground, const RectGraphic& background, uint8 alphaFactorForeground, uint8 alphaFactorBackground)
{
	//	Lock semaphore to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_lock(this) != OK)
	{
		return;
	}
	
	
	//	Memory-to-memory mode with PFC and blending
	//	Foreground and background fetch
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00022B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(foreground);																																//	Pixel Data to write to
	*MCU::DMA2D::O_OR				= output.size.x - foreground.size.x;																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= 0;																																																	//	Output Color
	*MCU::DMA2D::NLR				= (foreground.size.x << 16) | foreground.size.y;																											//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR			= (uint32) foreground.data;																																						//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= (alphaFactorForeground << 24) | (0x2 << 16);																												//	ARGB8888 Pixel Format, Modified Alpha Value, blending: Alpha value of pixels multiplied with alpha factor
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR			= (uint32) background.get_data(foreground);																														//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= background.size.x - foreground.size.x;																															//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= (alphaFactorBackground << 24) | (0x2 << 16);																												//	ARGB8888 Pixel Format, Modified Alpha Value, blending: Alpha value of pixels multiplied with alpha factor
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Set flag so that we can sleep until transfer is complete in the interrupt routine
	m_transferActive = true;
	
	
	//	Start transfer
	bit::set(*MCU::DMA2D::CR, 0);
	
	
	//	Wait until transfer is complete in the interrupt routine
	while(m_transferActive == true)
	{
		cmos.sleep_100us(1);
	}
	
	
	//	Unlock semaphore
	cmos.semaphore_unlock(this);
}


CODE_RAM void DMA2D::blendBackgroundWithConstantForegroundToOutput(const RectGraphic& output, const Rect& foreground, const RectGraphic& background, Color color_foreground)
{
	//	Lock semaphore to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_lock(this) != OK)
	{
		return;
	}
	
	
	//	Memory-to-memory mode with PFC and blending
	//	Background fetch only
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00042B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(foreground);																																//	Pixel Data to write to
	*MCU::DMA2D::O_OR				= output.size.x - foreground.size.x;																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= 0;																																																	//	Output Color
	*MCU::DMA2D::NLR				= (foreground.size.x << 16) | foreground.size.y;																											//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR			= 0;																																																	//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0x00010000 | (color_foreground.alpha << 24);																												//	ARGB8888 Pixel Format, Modified Alpha Value
	*MCU::DMA2D::FG_COLR		= (color_foreground.red << 16) | (color_foreground.green << 8) | color_foreground.blue;								//	Foreground Color
	
	*MCU::DMA2D::BG_MAR			= (uint32) background.get_data(foreground);																														//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= background.size.x - foreground.size.x;																															//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Set flag so that we can sleep until transfer is complete in the interrupt routine
	m_transferActive = true;
	
	
	//	Start transfer
	bit::set(*MCU::DMA2D::CR, 0);
	
	
	//	Wait until transfer is complete in the interrupt routine
	while(m_transferActive == true)
	{
		cmos.sleep_100us(1);
	}
	
	
	//	Unlock semaphore
	cmos.semaphore_unlock(this);
}


CODE_RAM void DMA2D::blendForegroundWithConstantBackgroundToOutput(const RectGraphic& output, const RectGraphic& foreground, const Rect& background, Color color_background)
{
	//	Lock semaphore to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.semaphore_lock(this) != OK)
	{
		return;
	}
	
	
	//	Memory-to-memory mode with PFC and blending
	//	Foreground fetch only
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00052B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_MAR			= (uint32) output.get_data(foreground);																																//	Pixel Data to write to
	*MCU::DMA2D::O_OR				= output.size.x - foreground.size.x;																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= 0;																																																	//	Output Color
	*MCU::DMA2D::NLR				= (foreground.size.x << 16) | foreground.size.y;																											//	Number of Lines and Pixels per Line
	
	*MCU::DMA2D::FG_MAR			= (uint32) foreground.data;																																						//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR			= 0;																																																	//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_MAR			= 0;																																																	//	Background Pixel Data
	*MCU::DMA2D::BG_OR			= background.size.x - foreground.size.x;																															//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_PFC_CR	= 0x00010000 | (color_background.alpha << 24);																												//	ARGB8888 Pixel Format, Modified Alpha Value
	*MCU::DMA2D::BG_COLR		= (color_background.red << 16) | (color_background.green << 8) | color_background.blue;								//	Background Color
	
	
	//	Set flag so that we can sleep until transfer is complete in the interrupt routine
	m_transferActive = true;
	
	
	//	Start transfer
	bit::set(*MCU::DMA2D::CR, 0);
	
	
	//	Wait until transfer is complete in the interrupt routine
	while(m_transferActive == true)
	{
		cmos.sleep_100us(1);
	}
	
	
	//	Unlock semaphore
	cmos.semaphore_unlock(this);
}









CODE_RAM void ISR_DMA2D()
{
	//	Copy ISR flags and clear them
	const uint32 isr_flags = *MCU::DMA2D::ISR;
	*MCU::DMA2D::IFCR = 0x0000003F;
	
	
	//	Get the DMA2D instance
	DMA2D& dma2d = STM32H753BIT6::get().get_dma2d();
	
	
	//	Increment the error counters if the corresponding error flags are set
	if(bit::isSet(isr_flags, 0) == true)
	{
		dma2d.m_counterTransferError++;
	}
	if(bit::isSet(isr_flags, 3) == true)
	{
		dma2d.m_counterClutAccessError++;
	}
	if(bit::isSet(isr_flags, 5) == true)
	{
		dma2d.m_counterConfigurationError++;
	}
	
	
	//	Set transfer active flag to false so that the waiting function can continue
	dma2d.m_transferActive = false;
}