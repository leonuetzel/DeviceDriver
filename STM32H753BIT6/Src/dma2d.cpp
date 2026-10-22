#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback DMA2D::startup()
{
	//	Create mutex
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_create(this) != OK)
	{
		return(FAIL);
	}
	
	
	//	Create the event for the end of a transfer
	m_eventID = cmos.event_create();
	
	
	//	Enable clock
	RCC& rcc = STM32H753BIT6::get().get_rcc();
	rcc.module_clockInit(RCC::e_module::DMA2D, true);
	
	
	//	Enable interrupt
	NVIC& nvic = cmos.get_nvic();														
	nvic.setPriority(Interrupt::DMA2D, 14);
	nvic.enable(Interrupt::DMA2D);
	return(OK);
}


void DMA2D::waitForTransfer(bool sleep)
{
	//	The interrupt routine clears the flag at the end of the transfer (also after an error) and emits the event
	//	Large transfers (e.g. a whole framebuffer) let other threads run meanwhile: the thread has subscribed to the event before the start
	//	(executeTransfer), so it cannot miss the end. Small transfers are waited for actively, sleep and wake-up would last longer
	//	The Graphics Manager draws many small rectangles per frame, the frame rate depends on this
	const volatile bool& transferActive = m_transferActive;
	if(sleep == true)
	{
		CMOS& cmos = CMOS::get();
		cmos.sleep_untilEvent(m_eventID);
		cmos.event_unsubscribe(m_eventID);
	}
	while(transferActive == true)
	{
		
	}
}


CODE_RAM uint32 DMA2D::get_areaSizeInBytes(uint32 pixelsPerLine, uint32 numberOfLines, uint32 lineOffset)
{
	//	Bytes from the first to the last pixel of an area: numberOfLines lines of pixelsPerLine pixels, lineOffset pixels between two lines, ARGB8888
	if(pixelsPerLine == 0 || numberOfLines == 0)
	{
		return(0);
	}
	return(((numberOfLines - 1) * (pixelsPerLine + lineOffset) + pixelsPerLine) * 4);
}


CODE_RAM void DMA2D::fillByCPU(Color* output, uint32 pixelsPerLine, uint32 numberOfLines, uint32 outputOffset, Color color)
{
	//	The same Pixels as the DMA2D in Register-to-Memory Mode: with the ARGB8888 Output the Pixel is the Output Color, Color lies in Memory as
	//	ARGB8888 (blue, green, red, alpha). The Values are masked like the Registers of the DMA2D (RM0433, DMA2D_NLR, DMA2D_OOR)
	//	The CPU writes through the Data Cache: no Cache Maintenance, the Graphics Manager of CMOS writes the Cache back before a Buffer Change
	const uint32 pixels = pixelsPerLine & 0x3FFF;
	const uint32 lines = numberOfLines & 0xFFFF;
	const uint32 stride = pixels + (outputOffset & 0x3FFF);
	Color* line = output;
	for(uint32 y = 0; y < lines; y++)
	{
		for(uint32 x = 0; x < pixels; x++)
		{
			line[x] = color;
		}
		line += stride;
	}
}


CODE_RAM void DMA2D::copyByCPU(Color* output, uint32 outputOffset, const Color* foreground, uint32 foregroundOffset, uint32 pixelsPerLine, uint32 numberOfLines)
{
	//	The same Pixels as the DMA2D in Memory-to-Memory Mode without PFC (MODE 000, RM0433): the Foreground Pixels unchanged, Line by Line,
	//	in rising Addresses. The Values are masked like the Registers of the DMA2D
	const uint32 pixels = pixelsPerLine & 0x3FFF;
	const uint32 lines = numberOfLines & 0xFFFF;
	const uint32 strideOutput = pixels + (outputOffset & 0x3FFF);
	const uint32 strideForeground = pixels + (foregroundOffset & 0x3FFF);
	Color* lineOutput = output;
	const Color* lineForeground = foreground;
	for(uint32 y = 0; y < lines; y++)
	{
		for(uint32 x = 0; x < pixels; x++)
		{
			lineOutput[x] = lineForeground[x];
		}
		lineOutput += strideOutput;
		lineForeground += strideForeground;
	}
}


CODE_RAM void DMA2D::executeTransfer(uint32 pixelsPerLine, uint32 numberOfLines, const void* output, uint32 outputOffset, const void* foreground, uint32 foregroundOffset, const void* background, uint32 backgroundOffset)
{
	//	Areas of the transfer: the caller passes them instead of reading them back from the registers over the bus
	const uint32 nlr = (pixelsPerLine << 16) | numberOfLines;
	*MCU::DMA2D::NLR		= nlr;																		//	Number of Lines and Pixels per Line
	*MCU::DMA2D::O_MAR		= (uint32) output;												//	Pixel Data to write to
	*MCU::DMA2D::O_OR		= outputOffset;													//	Offset to add at the End of each Line
	*MCU::DMA2D::FG_MAR	= (uint32) foreground;											//	Foreground Pixel Data
	*MCU::DMA2D::FG_OR		= foregroundOffset;												//	Offset to add at the End of each Line
	*MCU::DMA2D::BG_MAR	= (uint32) background;											//	Background Pixel Data
	*MCU::DMA2D::BG_OR		= backgroundOffset;												//	Offset to add at the End of each Line
	
	
	//	Sizes as the DMA2D uses the values: 14 bits for the pixels per line and the line offsets, 16 bits for the number of lines
	//	(RM0433, DMA2D_NLR, DMA2D_OOR, DMA2D_FGOR, DMA2D_BGOR). An input that the mode does not fetch has no size
	const uint32 pixels = (nlr >> 16) & 0x3FFF;
	const uint32 lines = nlr & 0xFFFF;
	const uint32 outputSize = get_areaSizeInBytes(pixels, lines, outputOffset & 0x3FFF);
	const uint32 foregroundSize = (foreground != nullptr) ? get_areaSizeInBytes(pixels, lines, foregroundOffset & 0x3FFF) : 0;
	const uint32 backgroundSize = (background != nullptr) ? get_areaSizeInBytes(pixels, lines, backgroundOffset & 0x3FFF) : 0;
	
	
	//	Cache maintenance only for cacheable memory written by the CPU (see cacheMaintenance.hpp), only for the lines of the rectangles
	//	The framebuffers in the SDRAM are Write-Back cacheable and need it, images and fonts in the flash are never written by the CPU and need none
	//	Nobody may write the output area while the DMA2D runs
	const uint32 bytesPerLine = pixels * 4;
	const uint32 outputStride = (pixels + (outputOffset & 0x3FFF)) * 4;
	const bool outputMaintained = CacheMaintenance::isRequired(output, outputSize);
	if(CacheMaintenance::isRequired(foreground, foregroundSize) == true)
	{
		CacheMaintenance::beforeRead(foreground, bytesPerLine, lines, (pixels + (foregroundOffset & 0x3FFF)) * 4);
	}
	if(CacheMaintenance::isRequired(background, backgroundSize) == true)
	{
		CacheMaintenance::beforeRead(background, bytesPerLine, lines, (pixels + (backgroundOffset & 0x3FFF)) * 4);
	}
	if(outputMaintained == true)
	{
		CacheMaintenance::beforeWrite(output, bytesPerLine, lines, outputStride);
	}
	
	
	//	Barrier: the stores of the CPU must have reached the memory before the DMA2D starts, also without data cache
	asm volatile("dsb" : : : "memory");
	
	
	//	A thread that sleeps during a large transfer subscribes to the event before the start (see waitForTransfer)
	const bool sleep = (pixels * lines > c_maximumPixelsForActiveWait);
	if(sleep == true)
	{
		CMOS& cmos = CMOS::get();
		cmos.event_subscribe(m_eventID);
		cmos.event_listen(m_eventID);
	}
	
	
	//	Set flag so that we can wait until transfer is complete in the interrupt routine
	m_transferActive = true;
	
	
	//	Start transfer
	bit::set(*MCU::DMA2D::CR, 0);
	
	
	//	Wait until transfer is complete in the interrupt routine
	waitForTransfer(sleep);
	
	
	//	The CPU reads the output only after this
	if(outputMaintained == true)
	{
		CacheMaintenance::afterWrite(output, bytesPerLine, lines, outputStride);
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

CODE_RAM void DMA2D::fillRectangleWithSingleColor(const RectGraphic& output, Color color)
{
	//	Lock mutex to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(this) != OK)
	{
		return;
	}
	
	
	//	Small areas: the CPU writes them, the same pixels without starting the DMA2D (see fillByCPU, copyByCPU)
	//	The mutex is kept also here: no other thread draws meanwhile, and no DMA2D transfer maintains the cache lines the CPU writes
	if((uint32) (output.size.x & 0x3FFF) * (uint32) (output.size.y & 0xFFFF) <= c_maximumPixelsForCPU_fill)
	{
		fillByCPU(output.data, output.size.x, output.size.y, 0, color);
		cmos.mutex_unlock(this);
		return;
	}
	
	
	//	Register-to-memory mode with PFC and blending
	//	No pixel fetch
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00032B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= (color.alpha << 24) | (color.red << 16) | (color.green << 8) | color.blue;													//	Output Color
	
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Start the transfer with cache maintenance and wait until it is complete
	executeTransfer(output.size.x, output.size.y, output.data, 0, nullptr, 0, nullptr, 0);
	
	
	//	Unlock mutex
	cmos.mutex_unlock(this);
}


CODE_RAM void DMA2D::drawfilledRectangleWithSingleColor(const RectGraphic& output, Color color, Rect rectangle)
{
	//	Lock mutex to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(this) != OK)
	{
		return;
	}
	
	
	//	Small areas: the CPU writes them, the same pixels without starting the DMA2D (see fillByCPU, copyByCPU)
	//	The mutex is kept also here: no other thread draws meanwhile, and no DMA2D transfer maintains the cache lines the CPU writes
	if((uint32) (rectangle.size.x & 0x3FFF) * (uint32) (rectangle.size.y & 0xFFFF) <= c_maximumPixelsForCPU_fill)
	{
		fillByCPU(output.get_data(rectangle), rectangle.size.x, rectangle.size.y, output.size.x - rectangle.size.x, color);
		cmos.mutex_unlock(this);
		return;
	}
	
	
	//	Register-to-memory mode with PFC and blending
	//	No pixel fetch
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00032B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= (color.alpha << 24) | (color.red << 16) | (color.green << 8) | color.blue;													//	Output Color
	
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Start the transfer with cache maintenance and wait until it is complete
	executeTransfer(rectangle.size.x, rectangle.size.y, output.get_data(rectangle), output.size.x - rectangle.size.x, nullptr, 0, nullptr, 0);
	
	
	//	Unlock mutex
	cmos.mutex_unlock(this);
}


CODE_RAM void DMA2D::copyForegroundToOutput(const RectGraphic& output, const RectGraphic& foreground, uint8 alphaFactor)
{
	//	Lock mutex to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(this) != OK)
	{
		return;
	}
	
	
	//	Small areas: the CPU writes them, the same pixels without starting the DMA2D (see fillByCPU, copyByCPU)
	//	The mutex is kept also here: no other thread draws meanwhile, and no DMA2D transfer maintains the cache lines the CPU writes
	if(alphaFactor == 0xFF && (uint32) (foreground.size.x & 0x3FFF) * (uint32) (foreground.size.y & 0xFFFF) <= c_maximumPixelsForCPU_copy)
	{
		copyByCPU(output.get_data(foreground), output.size.x - foreground.size.x, foreground.data, 0, foreground.size.x, foreground.size.y);
		cmos.mutex_unlock(this);
		return;
	}
	
	
	//	Memory-to-memory mode (MODE 000), with an alpha factor memory-to-memory with PFC (MODE 001): the PFC multiplies the alpha of every
	//	pixel by the factor (FG_PFC_CR AM = 10, RM0433). Without the PFC the factor would have no effect
	//	Foreground fetch only
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= (alphaFactor == 0xFF) ? 0x00002B00 : 0x00012B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= 0;																																																	//	Output Color
	
	*MCU::DMA2D::FG_PFC_CR	= (alphaFactor << 24) | (0x2 << 16);																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Start the transfer with cache maintenance and wait until it is complete
	executeTransfer(foreground.size.x, foreground.size.y, output.get_data(foreground), output.size.x - foreground.size.x, foreground.data, 0, nullptr, 0);
	
	
	//	Unlock mutex
	cmos.mutex_unlock(this);
}


CODE_RAM void DMA2D::copyForegroundRectangleToOutputPosition(const RectGraphic& output, const RectGraphic& foreground, Rect rectangle, Vec2 position, uint8 alphaFactor)
{
	//	Lock mutex to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(this) != OK)
	{
		return;
	}
	
	
	//	Small areas: the CPU writes them, the same pixels without starting the DMA2D (see fillByCPU, copyByCPU)
	//	The mutex is kept also here: no other thread draws meanwhile, and no DMA2D transfer maintains the cache lines the CPU writes
	if(alphaFactor == 0xFF && (uint32) (rectangle.size.x & 0x3FFF) * (uint32) (rectangle.size.y & 0xFFFF) <= c_maximumPixelsForCPU_copy)
	{
		copyByCPU(output.get_data(Rect(position, rectangle.size)), output.size.x - rectangle.size.x, foreground.get_data(rectangle), foreground.size.x - rectangle.size.x, rectangle.size.x, rectangle.size.y);
		cmos.mutex_unlock(this);
		return;
	}
	
	
	//	Memory-to-memory mode (MODE 000), with an alpha factor memory-to-memory with PFC (MODE 001): the PFC multiplies the alpha of every
	//	pixel by the factor (FG_PFC_CR AM = 10, RM0433). Without the PFC the factor would have no effect
	//	Foreground fetch only
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= (alphaFactor == 0xFF) ? 0x00002B00 : 0x00012B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= 0;																																																	//	Output Color
	
	*MCU::DMA2D::FG_PFC_CR	= (alphaFactor << 24) | (0x2 << 16);																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Start the transfer with cache maintenance and wait until it is complete
	executeTransfer(rectangle.size.x, rectangle.size.y, output.get_data(Rect(position, rectangle.size)), output.size.x - rectangle.size.x, foreground.get_data(rectangle), foreground.size.x - rectangle.size.x, nullptr, 0);
	
	
	//	Unlock mutex
	cmos.mutex_unlock(this);
}


CODE_RAM void DMA2D::blendForegroundAndBackgroundToOutput(const RectGraphic& output, const RectGraphic& foreground, const RectGraphic& background, uint8 alphaFactorForeground, uint8 alphaFactorBackground)
{
	//	Lock mutex to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(this) != OK)
	{
		return;
	}
	
	
	//	Memory-to-memory mode with PFC and blending
	//	Foreground and background fetch
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00022B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;
	
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= 0;																																																	//	Output Color
	
	*MCU::DMA2D::FG_PFC_CR	= (alphaFactorForeground << 24) | (0x2 << 16);																												//	ARGB8888 Pixel Format, Modified Alpha Value, blending: Alpha value of pixels multiplied with alpha factor
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_PFC_CR	= (alphaFactorBackground << 24) | (0x2 << 16);																												//	ARGB8888 Pixel Format, Modified Alpha Value, blending: Alpha value of pixels multiplied with alpha factor
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Start the transfer with cache maintenance and wait until it is complete
	executeTransfer(foreground.size.x, foreground.size.y, output.get_data(foreground), output.size.x - foreground.size.x, foreground.data, 0, background.get_data(foreground), background.size.x - foreground.size.x);
	
	
	//	Unlock mutex
	cmos.mutex_unlock(this);
}


CODE_RAM void DMA2D::blendBackgroundWithConstantForegroundToOutput(const RectGraphic& output, const Rect& foreground, const RectGraphic& background, Color color_foreground)
{
	//	Lock mutex to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(this) != OK)
	{
		return;
	}
	
	
	//	Memory-to-memory mode with PFC and blending
	//	Background fetch only
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00042B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= 0;																																																	//	Output Color
	
	*MCU::DMA2D::FG_PFC_CR	= 0x00010000 | (color_foreground.alpha << 24);																												//	ARGB8888 Pixel Format, Modified Alpha Value
	*MCU::DMA2D::FG_COLR		= (color_foreground.red << 16) | (color_foreground.green << 8) | color_foreground.blue;								//	Foreground Color
	
	*MCU::DMA2D::BG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::BG_COLR		= 0;																																																	//	Background Color
	
	
	//	Start the transfer with cache maintenance and wait until it is complete
	executeTransfer(foreground.size.x, foreground.size.y, output.get_data(foreground), output.size.x - foreground.size.x, nullptr, 0, background.get_data(foreground), background.size.x - foreground.size.x);
	
	
	//	Unlock mutex
	cmos.mutex_unlock(this);
}


CODE_RAM void DMA2D::blendForegroundWithConstantBackgroundToOutput(const RectGraphic& output, const RectGraphic& foreground, const Rect& background, Color color_background)
{
	//	Lock mutex to avoid concurrent access to the DMA2D peripheral
	CMOS& cmos = CMOS::get();
	if(cmos.mutex_lock(this) != OK)
	{
		return;
	}
	
	
	//	Memory-to-memory mode with PFC and blending
	//	Foreground fetch only
	//	Line offset expressed in pixels
	//	Enable all interrupts
	*MCU::DMA2D::CR					= 0x00052B00;
	*MCU::DMA2D::IFCR				= 0x0000003F;																																													//	Clear Interrupt Flags
	
	*MCU::DMA2D::O_PFC_CR		= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::O_COLR			= 0;																																																	//	Output Color
	
	*MCU::DMA2D::FG_PFC_CR	= 0;																																																	//	ARGB8888 Pixel Format
	*MCU::DMA2D::FG_COLR		= 0;																																																	//	Foreground Color
	
	*MCU::DMA2D::BG_PFC_CR	= 0x00010000 | (color_background.alpha << 24);																												//	ARGB8888 Pixel Format, Modified Alpha Value
	*MCU::DMA2D::BG_COLR		= (color_background.red << 16) | (color_background.green << 8) | color_background.blue;								//	Background Color
	
	
	//	Start the transfer with cache maintenance and wait until it is complete
	executeTransfer(foreground.size.x, foreground.size.y, output.get_data(foreground), output.size.x - foreground.size.x, foreground.data, 0, nullptr, background.size.x - foreground.size.x);
	
	
	//	Unlock mutex
	cmos.mutex_unlock(this);
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
	
	
	//	Set transfer active flag to false so that the waiting function can continue, wake up a thread that sleeps during a large transfer
	dma2d.m_transferActive = false;
	CMOS::get().event_emit(dma2d.m_eventID);
}