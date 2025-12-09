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

feedback LTDC::init(s_displayData displayData, Array<RectGraphic> layer)
{
	const uint32 c_numberOfLayer = layer.get_size();
	if(c_numberOfLayer > c_layer_number)
	{
		return(FAIL);
	}
	
	
	
	for(uint32 i = 0; i < c_numberOfLayer; i++)
	{
		if(layer[i].position.x >= displayData.h_active || layer[i].position.y >= displayData.v_active)
		{
			return(FAIL);
		}
		if(layer[i].get_topRightCorner().x >= displayData.h_active || layer[i].get_topRightCorner().y >= displayData.v_active)
		{
			return(FAIL);
		}
		if(layer[i].get_topRightCorner().x < layer[i].position.x || layer[i].get_topRightCorner().y < layer[i].position.y)
		{
			return(FAIL);
		}
		if(layer[i].size.x < 1 || layer[i].size.y < 1)
		{
			return(FAIL);
		}
	}
	
	
	for(uint32 i = 0; i < c_numberOfLayer; i++)
	{
		m_layer[i] = layer[i];
	}
	for(uint32 i = c_numberOfLayer; i < c_layer_number; i++)
	{
		m_layer[i] = RectGraphic();
	}
	
	
	
	
	
	*MCU::LTDC::SSCR = ((displayData.h_syncwidth - 1) << 16)																																							| (displayData.v_syncwidth - 1);
	*MCU::LTDC::BPCR = ((displayData.h_syncwidth + displayData.h_backporch - 1) << 16)																										| (displayData.v_syncwidth + displayData.v_backporch - 1);
	*MCU::LTDC::AWCR = ((displayData.h_syncwidth + displayData.h_backporch + displayData.h_active - 1) << 16)															| (displayData.v_syncwidth + displayData.v_backporch + displayData.v_active - 1);
	*MCU::LTDC::TWCR = ((displayData.h_syncwidth + displayData.h_backporch + displayData.h_active + displayData.h_frontporch - 1) << 16)	| (displayData.v_syncwidth + displayData.v_backporch + displayData.v_active + displayData.v_frontporch - 1);
	
	*MCU::LTDC::BCCR = 0x00000000;																																																//	Set Background Color to Black
	
	
	
	
	
	for(uint32 i = 0; i < c_numberOfLayer; i++)
	{
		uint32* reg_cr			= ((uint32*) MCU::LTDC::L1_CR)			+ i * 0x20;
		uint32* reg_whpcr		= ((uint32*) MCU::LTDC::L1_WHPCR)	+ i * 0x20;
		uint32* reg_wvpcr		= ((uint32*) MCU::LTDC::L1_WVPCR)	+ i * 0x20;
		//uint32* reg_ckcr		= ((uint32*) MCU::LTDC::L1_CKCR)		+ i * 0x20;
		uint32* reg_pfcr		= ((uint32*) MCU::LTDC::L1_PFCR)		+ i * 0x20;
		uint32* reg_cacr		= ((uint32*) MCU::LTDC::L1_CACR)		+ i * 0x20;
		//uint32* reg_dccr		= ((uint32*) MCU::LTDC::L1_DCCR)		+ i * 0x20;
		//uint32* reg_bfcr		= ((uint32*) MCU::LTDC::L1_BFCR)		+ i * 0x20;
		uint32* reg_cfbar		= ((uint32*) MCU::LTDC::L1_CFBAR)	+ i * 0x20;
		uint32* reg_cfblr		= ((uint32*) MCU::LTDC::L1_CFBLR)	+ i * 0x20;
		uint32* reg_cfblnr	= ((uint32*) MCU::LTDC::L1_CFBLNR)	+ i * 0x20;
		//uint32* reg_clutwr	= ((uint32*) MCU::LTDC::L1_CLUTWR)	+ i * 0x20;
		
		
		//	Convert Positions from Bottom-Up to Top-Down Format
		int16 y_end		= displayData.v_active - layer[i].position.y;
		int16 y_start	= y_end - layer[i].size.y;
		
		
		
		
		
		//	Set Window Horizontal Position
		*reg_whpcr	= ((displayData.h_syncwidth + displayData.h_backporch + layer[i].get_topRightCorner().x	) << 16) | (displayData.h_syncwidth + displayData.h_backporch + layer[i].position.x	);
		
		
		//	Set Window Vertical Position
		*reg_wvpcr	= ((displayData.v_syncwidth + displayData.v_backporch + y_end) << 16) | (displayData.v_syncwidth + displayData.v_backporch + y_start);
		
		
		//	Set Layer Pixel Format to ARGB8888
		*reg_pfcr		= 0x00000000;
		
		
		//	Set Alpha Value 255 = not transparent
		*reg_cacr		= 0x000000FF;
		
		
		//	Set Buffer Address
		*reg_cfbar	= (uint32) layer[i].data;
		
		
		//	Set Buffer Pitch and Line Length
		*reg_cfblr	= ((layer[i].size.x * 4) << 16) | (layer[i].size.x * 4 + 7);
		
		
		//	Set Buffer Line Number
		*reg_cfblnr	= layer[i].size.y;
		
		
		//	Enable Layer
		bit::set(*reg_cr, 0);
	}
	
	
	for(uint32 i = c_numberOfLayer; i < c_layer_number; i++)
	{
		//	Disable Layer
		uint32* reg_cr = ((uint32*) MCU::LTDC::L1_CR) + i * 0x20;
		bit::clear(*reg_cr, 0);
	}
	
	
	//	Reload Shadow Registers
	bit::set(*MCU::LTDC::SRCR, 1);
	
	
	//	Enable Register Reload Interrupt
	bit::set(*MCU::LTDC::IER, 3);
	
	
	CMOS& cmos = CMOS::get();
	NVIC& nvic = cmos.get_nvic();																																																
	nvic.setPriority(Interrupt::LTDC, 14);
	nvic.enable(Interrupt::LTDC);
	
	
	m_displayData = displayData;
	m_layerNumber = c_numberOfLayer;
	return(OK);
}







uint16 LTDC::get_eventID_frameFinished()
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


CODE_RAM feedback LTDC::set_layerBuffer(uint32 layer, Color* buffer)
{
	if(layer < c_layer_number)
	{
		m_layer[layer].data = buffer;
		
		uint32* reg_cr			= ((uint32*) MCU::LTDC::L1_CR)		+ layer * 0x20;
		uint32* reg_cfbar		= ((uint32*) MCU::LTDC::L1_CFBAR)	+ layer * 0x20;
		
		bit::clear(*reg_cr, 0);
		*reg_cfbar = (uint32) m_layer[layer].data;
		bit::set(*reg_cr, 0);
		
		return(OK);
	}
	return(FAIL);
}


CODE_RAM feedback LTDC::clear(uint32 layer)
{
	if(layer > c_layer_number)
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


CODE_RAM feedback LTDC::set_colorBackground(uint8 red, uint8 green, uint8 blue)
{
	*MCU::LTDC::BCCR = (red << 16) | (green << 8) | blue;
	
	m_colorBackground.red = red;
	m_colorBackground.green = green;
	m_colorBackground.blue = blue;
	
	return(OK);
}


CODE_RAM feedback LTDC::set_layerAlpha(uint8 layer, uint8 alpha)
{
	if(layer >= m_layerNumber)
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


CODE_RAM uint32 LTDC::get_numberOfLayers()
{
	return(m_layerNumber);
}


CODE_RAM uint32 LTDC::get_fps()
{
	return(m_fps);
}


CODE_RAM Color LTDC::get_colorBackground()
{
	return(m_colorBackground);
}









CODE_RAM void ISR_LTDC()
{
	static uint8 counter;
	static uint8 second;
	
	
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
	}
	
	
	//	Clear Register Reload Flag
	bit::set(*MCU::LTDC::ICR, 3);
	
	
	//	Reload Shadow Registers
	bit::set(*MCU::LTDC::SRCR, 1);
	
	
	//	Wakeup Thread
	cmos.event_emit(ltdc.m_eventID);
}