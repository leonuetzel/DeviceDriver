#include "../Inc/stm32f103c8t6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

void EXTI::afio_set_extiLine(MCU::PIN pin)
{
	STM32F103C8T6::get().get_afio().set_extiExternalInterruptPin(pin);
}


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
	cmos.get_nvic().enable(line <= 4 ? (uint16) (Interrupt::EXTI_0 + line) : (line <= 9 ? Interrupt::EXTI_9_TO_5 : Interrupt::EXTI_15_TO_10));
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







//	GPIO Line 0
void ISR_EXTI_0()
{
	STM32F103C8T6::get().get_exti().dispatch(0, 0);
}


//	GPIO Line 1
void ISR_EXTI_1()
{
	STM32F103C8T6::get().get_exti().dispatch(1, 1);
}


//	GPIO Line 2
void ISR_EXTI_2()
{
	STM32F103C8T6::get().get_exti().dispatch(2, 2);
}


//	GPIO Line 3
void ISR_EXTI_3()
{
	STM32F103C8T6::get().get_exti().dispatch(3, 3);
}


//	GPIO Line 4
void ISR_EXTI_4()
{
	STM32F103C8T6::get().get_exti().dispatch(4, 4);
}


//	GPIO Lines 5 ... 9
void ISR_EXTI_9_TO_5()
{
	STM32F103C8T6::get().get_exti().dispatch(5, 9);
}


//	GPIO Lines 10 ... 15
void ISR_EXTI_15_TO_10()
{
	STM32F103C8T6::get().get_exti().dispatch(10, 15);
}
