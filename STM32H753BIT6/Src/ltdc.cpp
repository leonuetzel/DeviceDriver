#include "../Inc/stm32h753bit6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback LTDC::startup()
{
	RCC& rcc = STM32H753BIT6::get().get_rcc();
	rcc.module_reset(RCC::e_module::LTDC);
	rcc.module_clockInit(RCC::e_module::LTDC, true);
	
	return(OK);
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback LTDC::init(s_displayData displayData)
{
	//	Initialize layer data with default values
	for(uint32 i = 0; i < maximumNumberOfLayers; i++)
	{
		m_layer[i] = RectGraphic();
	}
	
	
	//	Set display timings
	*MCU::LTDC::SSCR = ((displayData.h_syncwidth - 1) << 16)																																							| (displayData.v_syncwidth - 1);
	*MCU::LTDC::BPCR = ((displayData.h_syncwidth + displayData.h_backporch - 1) << 16)																										| (displayData.v_syncwidth + displayData.v_backporch - 1);
	*MCU::LTDC::AWCR = ((displayData.h_syncwidth + displayData.h_backporch + displayData.h_active - 1) << 16)															| (displayData.v_syncwidth + displayData.v_backporch + displayData.v_active - 1);
	*MCU::LTDC::TWCR = ((displayData.h_syncwidth + displayData.h_backporch + displayData.h_active + displayData.h_frontporch - 1) << 16)	| (displayData.v_syncwidth + displayData.v_backporch + displayData.v_active + displayData.v_frontporch - 1);
	
	
	//	Set background color to black
	*MCU::LTDC::BCCR = 0x00000000;
	
	
	//	Disable all layers
	for(uint32 i = 0; i < maximumNumberOfLayers; i++)
	{
		//	Disable Layer
		uint32* reg_cr = ((uint32*) MCU::LTDC::L1_CR) + i * 0x20;
		bit::clear(*reg_cr, 0);
	}
	
	
	//	Reload shadow registers on next vsync
	bit::set(*MCU::LTDC::SRCR, 1);
	
	
	//	Enable:
	//	-	register reload interrupt
	//	-	FIFO underrun interrupt
	//	-	FIFO transmit error interrupt
	bit::set(*MCU::LTDC::IER, 1);
	bit::set(*MCU::LTDC::IER, 2);
	bit::set(*MCU::LTDC::IER, 3);
	
	
	//	Prioritize LTDC accesses on the AXI bus matrix to avoid stuttering and tearing effects on the display
	*MCU::GPV::INI6_READ_QOS	= 0x0000000F;
	*MCU::GPV::INI6_WRITE_QOS	= 0x0000000F;
	
	
	m_fifoUnderrunCounter = 0;
	m_fifoTransmitErrorCounter = 0;
	
	
	CMOS& cmos = CMOS::get();
	NVIC& nvic = cmos.get_nvic();																																																
	nvic.setPriority(Interrupt::LTDC, 14);
	nvic.setPriority(Interrupt::LTDC_ERROR, 14);
	nvic.enable(Interrupt::LTDC);
	nvic.enable(Interrupt::LTDC_ERROR);
	
	
	m_displayData = displayData;
	return(OK);
}


feedback LTDC::set_layerData(uint32 layerNumber, RectGraphic& layer)
{
	//	Boundary check
	if(layerNumber >= maximumNumberOfLayers)
	{
		return(FAIL);
	}
	
	
	if(layer.position.x >= m_displayData.h_active || layer.position.y >= m_displayData.v_active)
	{
		return(FAIL);
	}
	if(layer.get_topRightCorner().x >= m_displayData.h_active || layer.get_topRightCorner().y >= m_displayData.v_active)
	{
		return(FAIL);
	}
	if(layer.get_topRightCorner().x < layer.position.x || layer.get_topRightCorner().y < layer.position.y)
	{
		return(FAIL);
	}
	if(layer.size.x < 1 || layer.size.y < 1)
	{
		return(FAIL);
	}
	
	
	//	Calculate register addresses for layer
	uint32* reg_cr			= ((uint32*) MCU::LTDC::L1_CR)			+ layerNumber * 0x20;
	uint32* reg_whpcr		= ((uint32*) MCU::LTDC::L1_WHPCR)		+ layerNumber * 0x20;
	uint32* reg_wvpcr		= ((uint32*) MCU::LTDC::L1_WVPCR)		+ layerNumber * 0x20;
	uint32* reg_pfcr		= ((uint32*) MCU::LTDC::L1_PFCR)		+ layerNumber * 0x20;
	uint32* reg_cacr		= ((uint32*) MCU::LTDC::L1_CACR)		+ layerNumber * 0x20;
	uint32* reg_cfbar		= ((uint32*) MCU::LTDC::L1_CFBAR)		+ layerNumber * 0x20;
	uint32* reg_cfblr		= ((uint32*) MCU::LTDC::L1_CFBLR)		+ layerNumber * 0x20;
	uint32* reg_cfblnr	= ((uint32*) MCU::LTDC::L1_CFBLNR)	+ layerNumber * 0x20;
	
	
	//	Convert positions from bottom-up to top-down format (inverted y-axis)
	int16 y_end		= m_displayData.v_active - layer.position.y;
	int16 y_start	= y_end - layer.size.y;
	
	
	//	Set window horizontal position
	*reg_whpcr	= ((m_displayData.h_syncwidth + m_displayData.h_backporch + layer.get_topRightCorner().x) << 16) | (m_displayData.h_syncwidth + m_displayData.h_backporch + layer.position.x);
	
	
	//	Set window vertical position
	*reg_wvpcr	= ((m_displayData.v_syncwidth + m_displayData.v_backporch + y_end - 1) << 16) | (m_displayData.v_syncwidth + m_displayData.v_backporch + y_start);
	
	
	//	Set layer pixel format to ARGB8888
	*reg_pfcr		= 0x00000000;
	
	
	//	Set alpha value to 255 = not transparent
	*reg_cacr		= 0x000000FF;
	
	
	//	Set pixel buffer address
	*reg_cfbar	= (uint32) layer.data;
	
	
	//	Set pixel buffer pitch and line length
	*reg_cfblr	= ((layer.size.x * 4) << 16) | (layer.size.x * 4 + 7);
	
	
	//	Set buffer line number
	*reg_cfblnr	= layer.size.y;
	
	
	//	Enable layer
	bit::set(*reg_cr, 0);
	
	
	//	Reload shadow registers on next vsync
	bit::set(*MCU::LTDC::SRCR, 1);
	
	
	//	Save layer data
	m_layer[layerNumber] = layer;
	return(OK);
}







uint16 LTDC::get_eventID_vSync()
{
	return(m_eventID);
}







feedback LTDC::start()
{
	bit::set(*MCU::LTDC::GCR, 0);
	return(OK);
}


feedback LTDC::stop()
{
	bit::clear(*MCU::LTDC::GCR, 0);
	return(OK);
}


CODE_RAM feedback LTDC::set_layerBuffer(uint32 layer, Color* buffer, bool applyOnNextVsync)
{
	if(layer < maximumNumberOfLayers)
	{
		m_layer[layer].data = buffer;
		
		//	Set pixel buffer address
		uint32* reg_cfbar		= ((uint32*) MCU::LTDC::L1_CFBAR)	+ layer * 0x20;
		*reg_cfbar = (uint32) m_layer[layer].data;
		
		
		//	Reload shadow registers on next vsync if "applyOnNextVsync" is true, otherwise reload immediately
		if(applyOnNextVsync == true)
		{
			bit::set(*MCU::LTDC::SRCR, 1);
		}
		else
		{
			bit::set(*MCU::LTDC::SRCR, 0);
		}
		return(OK);
	}
	return(FAIL);
}


CODE_RAM feedback LTDC::clear(uint32 layer)
{
	if(layer > maximumNumberOfLayers)
	{
		return(FAIL);
	}
	
	uint32 surface = m_layer[layer].get_surface();
	for(uint32 i = 0; i < surface; i++)
	{
		*(m_layer[layer].data + i) = Colors::transparent;
	}
	
	return(OK);
}


CODE_RAM feedback LTDC::set_colorBackground(Color color)
{
	*MCU::LTDC::BCCR = (color.red << 16) | (color.green << 8) | color.blue;
	m_colorBackground = color;
	return(OK);
}


CODE_RAM feedback LTDC::set_layerAlpha(uint8 layer, uint8 alpha)
{
	if(layer >= maximumNumberOfLayers)
	{
		return(FAIL);
	}
	
	uint32* CACR = ((uint32*) MCU::LTDC::L1_CACR) + layer * 0x20;
	
	uint32 temp = *CACR & 0xFFFFFF00;
	*CACR = temp | alpha;
	return(OK);
}


CODE_RAM feedback LTDC::set_pixel(Vec2& position, Color color, uint32 layer)
{
	if(position.x < m_layer[layer].size.x || position.x >= m_layer[layer].size.x || position.y < m_layer[layer].size.y || position.y >= m_layer[layer].size.y)
	{
		return(FAIL);
	}
	
	position.y = m_layer[layer].size.y - position.y - 1;
	
	Color* pixel = m_layer[layer].data + position.y * m_layer[layer].size.x + position.x;
	*pixel = color;
	
	return(OK);
}







CODE_RAM LTDC::s_displayData& LTDC::get_displayData()
{
	return(m_displayData);
}


CODE_RAM Vec2 LTDC::get_displayDimensions()
{
	return(Vec2(m_displayData.h_active, m_displayData.v_active));
}


CODE_RAM RectGraphic& LTDC::get_layerData(uint32 layer)
{
	return(m_layer[layer]);
}


CODE_RAM uint32 LTDC::get_maximumNumberOfLayers()
{
	return(maximumNumberOfLayers);
}


CODE_RAM uint32 LTDC::get_fps()
{
	return(m_fps);
}


CODE_RAM uint64& LTDC::get_frameCounter()
{
	return(m_frameCounter);
}


CODE_RAM uint32 LTDC::get_fifoUnderrunCounter()
{
	return(m_fifoUnderrunCounter);
}


CODE_RAM uint32 LTDC::get_fifoTransmitErrorCounter()
{
	return(m_fifoTransmitErrorCounter);
}


CODE_RAM Color LTDC::get_colorBackground()
{
	return(m_colorBackground);
}









CODE_RAM void ISR_LTDC()
{
	static uint8 counter;
	static uint8 second;
	
	
	if(bit::isSet(*MCU::LTDC::ISR, 3) == true)
	{
		LTDC& ltdc = STM32H753BIT6::get().get_ltdc();
		CMOS& cmos = CMOS::get();
		
		uint8 second_new = cmos.get_time().second;
		if(second != second_new)
		{
			ltdc.m_fps = counter;
			second = second_new;
			counter = 0;
		}
		else
		{
			counter++;
			ltdc.m_frameCounter++;
		}
		
		
		//	Clear Register Reload Flag
		*MCU::LTDC::ICR = 1 << 3;
		
		
		//	Reload Shadow Registers
		bit::set(*MCU::LTDC::SRCR, 1);
		
		
		//	Wakeup Thread
		cmos.event_emit(ltdc.m_eventID);
	}
	
	
	if(bit::isSet(*MCU::LTDC::ISR, 0) == true)
	{
		*MCU::LTDC::ICR = 1 << 0;
	}
}


CODE_RAM void ISR_LTDC_ERROR()
{
	if(bit::isSet(*MCU::LTDC::ISR, 1))
	{
		*MCU::LTDC::ICR = 1 << 1;
		STM32H753BIT6::get().get_ltdc().m_fifoUnderrunCounter++;
	}
	if(bit::isSet(*MCU::LTDC::ISR, 2))
	{
		*MCU::LTDC::ICR = 1 << 2;
		STM32H753BIT6::get().get_ltdc().m_fifoTransmitErrorCounter++;
	}
}