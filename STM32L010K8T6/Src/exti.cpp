#include "../Inc/stm32l010k8t6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

feedback EXTI::register_line(uint32 line)
{
	if(line > 15)
	{
		return(FAIL);
	}
	
	
	//	One CMOS Event per Line, created with the first Interrupt of the Line
	CMOS& cmos = CMOS::get();
	if(bit::isCleared(m_eventCreated, line) == true)
	{
		const uint16 eventID = cmos.event_create();
		if(eventID == CMOS::eventID_invalid)
		{
			return(FAIL);
		}
		m_eventID[line] = eventID;
		m_eventCreated = m_eventCreated | (1 << line);
	}
	
	
	//	The Interrupt of the Line Group, its Priority stays as set with the NVIC
	cmos.get_nvic().enable(line < 2 ? Interrupt::EXTI_0_TO_1 : (line < 4 ? Interrupt::EXTI_2_TO_3 : Interrupt::EXTI_4_TO_15));
	return(OK);
}


feedback EXTI::set_callback(MCU::PIN pin, s_callback* callback)
{
	//	The Interrupt reads the Pointer in one Access: the new Callback is complete before, the old one is deleted after the Exchange
	const uint32 line = ((uint32) pin) & 0x0F;
	s_callback* const callbackOld = m_callback[line];
	m_callback[line] = callback;
	delete callbackOld;
	return(OK);
}


void EXTI::dispatch(uint32 firstLine, uint32 lastLine)
{
	//	Pending and enabled Lines of this Interrupt, cleared at once by writing 1
	const uint32 lines = (0xFFFFFFFF >> (31 - lastLine)) & (0xFFFFFFFF << firstLine);
	const uint32 pending = *MCU::EXTI::PR & *MCU::EXTI::IMR & lines;
	*MCU::EXTI::PR = pending;
	
	
	//	Per Line: the CMOS Event, then the Callback
	CMOS& cmos = CMOS::get();
	for(uint32 line = firstLine; line <= lastLine; line++)
	{
		if(bit::isSet(pending, line) == true)
		{
			if(bit::isSet(m_eventCreated, line) == true)
			{
				cmos.event_emit(m_eventID[line]);
			}
			const s_callback* const callback = m_callback[line];
			if(callback != nullptr)
			{
				callback->caller(callback->object, callback->method);
			}
		}
	}
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback EXTI::init_GPIO_interrupt(MCU::PIN pin, e_edge edge)
{
	const uint8 portNumber = (((uint32) pin) >> 4);
	const uint8 pinNumber = (((uint32) pin) & 0x0F);
	
	
	volatile uint32* address = MCU::SYSCFG::EXTI_CR1 + pinNumber / 4;
	uint32 mask = portNumber;
	uint32 bitfield_startBit = 4 * (pinNumber % 4);
	uint32 temp = *address & (0xFFFFFFFF - (0x0F << bitfield_startBit));
	*address = temp | (mask << bitfield_startBit);
	
	switch(edge)
	{
		case e_edge::NONE:
			bit::clear(*MCU::EXTI::RTSR, pinNumber);
			bit::clear(*MCU::EXTI::FTSR, pinNumber);
			break;
			
		case e_edge::RISING:
			bit::set(*MCU::EXTI::RTSR, pinNumber);
			bit::clear(*MCU::EXTI::FTSR, pinNumber);
			break;
			
		case e_edge::FALLING:
			bit::clear(*MCU::EXTI::RTSR, pinNumber);
			bit::set(*MCU::EXTI::FTSR, pinNumber);
			break;
			
		case e_edge::TOGGLE:
			bit::set(*MCU::EXTI::RTSR, pinNumber);
			bit::set(*MCU::EXTI::FTSR, pinNumber);
			break;
			
		default:
			return(FAIL);
	}
	
	bit::set(*MCU::EXTI::IMR, pinNumber);
	
	return(register_line(pinNumber));
}


feedback EXTI::init_interrupt_internal(e_line line, bool interrupt)
{
	if((uint32) line > 31)
	{
		return(FAIL);
	}
	
	uint32 bit = (uint32) line;
	bit::set(*MCU::EXTI::RTSR, bit);
	bit::clear(*MCU::EXTI::FTSR, bit);
	if(interrupt == true)
	{
		bit::set(*MCU::EXTI::IMR, bit);
	}
	else
	{
		bit::clear(*MCU::EXTI::IMR, bit);
	}
	
	return(OK);
}


feedback EXTI::init_event_internal(e_line line, bool event)
{
	if((uint32) line > 31)
	{
		return(FAIL);
	}
	
	uint32 bit = (uint32) line;
	bit::set(*MCU::EXTI::RTSR, bit);
	bit::clear(*MCU::EXTI::FTSR, bit);
	if(event == true)
	{
		bit::set(*MCU::EXTI::EMR, bit);
	}
	else
	{
		bit::clear(*MCU::EXTI::EMR, bit);
	}
	
	return(OK);
}







feedback EXTI::clear_pendingBit(MCU::PIN pin)
{
	*MCU::EXTI::PR = 1 << (((uint32) pin) & 0x0F);							//	Write 1 to this Line only: writing the Register back would also clear the other pending Lines
	
	return(OK);
}


feedback EXTI::clear_pendingBit(e_line line)
{
	if((uint32) line > 32)
	{
		return(FAIL);
	}
	
	uint32 bit = (uint32) line;
	*MCU::EXTI::PR = 1 << bit;							//	Write 1 to this Line only: writing the Register back would also clear the other pending Lines
	
	return(OK);
}


uint16 EXTI::get_eventID(MCU::PIN pin) const
{
	//	Valid after init_GPIO_interrupt() of a Pin with this Line Number
	const uint32 line = ((uint32) pin) & 0x0F;
	if(bit::isCleared(m_eventCreated, line) == true)
	{
		return(CMOS::eventID_invalid);
	}
	return(m_eventID[line]);
}


feedback EXTI::unsubscribe(MCU::PIN pin)
{
	return(set_callback(pin, nullptr));
}







//	GPIO Lines 0 ... 1
void ISR_EXTI_0_TO_1()
{
	STM32L010K8T6::get().get_exti().dispatch(0, 1);
}


//	GPIO Lines 2 ... 3
void ISR_EXTI_2_TO_3()
{
	STM32L010K8T6::get().get_exti().dispatch(2, 3);
}


//	GPIO Lines 4 ... 15
void ISR_EXTI_4_TO_15()
{
	STM32L010K8T6::get().get_exti().dispatch(4, 15);
}
