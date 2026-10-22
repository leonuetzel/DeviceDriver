#include "../Inc/stm32l451ret6.hpp"





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


CODE_RAM void EXTI::dispatch(uint32 firstLine, uint32 lastLine)
{
	//	Pending and enabled Lines of this Interrupt, cleared at once by writing 1
	const uint32 lines = (0xFFFFFFFF >> (31 - lastLine)) & (0xFFFFFFFF << firstLine);
	const uint32 pending = *MCU::EXTI::PR1 & *MCU::EXTI::IMR1 & lines;
	*MCU::EXTI::PR1 = pending;
	
	
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
	GPIO& gpio = STM32L451RET6::get().get_gpio();
	const uint8 portNumber = gpio.get_portNumber(pin);
	const uint8 pinNumber = gpio.get_pinNumber(pin);
	
	
	volatile uint32* address = MCU::SYSCFG::EXTI_CR1 + pinNumber / 4;
	uint32 mask = portNumber;
	uint32 bitfield_startBit = 4 * (pinNumber % 4);
	uint32 temp = *address & (0xFFFFFFFF - (0x0F << bitfield_startBit));
	*address = temp | (mask << bitfield_startBit);
	
	switch(edge)
	{
		case e_edge::NONE:
			bit::clear(*MCU::EXTI::RTSR1, pinNumber);
			bit::clear(*MCU::EXTI::FTSR1, pinNumber);
			break;
			
		case e_edge::RISING:
			bit::set(*MCU::EXTI::RTSR1, pinNumber);
			bit::clear(*MCU::EXTI::FTSR1, pinNumber);
			break;
			
		case e_edge::FALLING:
			bit::clear(*MCU::EXTI::RTSR1, pinNumber);
			bit::set(*MCU::EXTI::FTSR1, pinNumber);
			break;
			
		case e_edge::TOGGLE:
			bit::set(*MCU::EXTI::RTSR1, pinNumber);
			bit::set(*MCU::EXTI::FTSR1, pinNumber);
			break;
			
		default:
			return(FAIL);
	}
	
	bit::set(*MCU::EXTI::IMR1, pinNumber);
	
	return(register_line(pinNumber));
}


feedback EXTI::init_interrupt_internal(e_line line, bool interrupt)
{
	//	Boundary check
	if((uint32) line > 40)
	{
		return(FAIL);
	}
	
	
	//	Get Registers
	const uint32 registerOffset = ((uint32) line) / 32;
	const uint32 bit = ((uint32) line) % 32;
	
	
	//	The Registers for the Lines 32 and above follow 0x20 Byte (8 Words) behind those for the Lines 0 to 31
	volatile uint32* const RTSR	= MCU::EXTI::RTSR1	+ 8 * registerOffset;
	volatile uint32* const FTSR	= MCU::EXTI::FTSR1	+ 8 * registerOffset;
	volatile uint32* const IMR		= MCU::EXTI::IMR1		+ 8 * registerOffset;
	
	
	//	Configure
	bit::set(*RTSR, bit);
	bit::clear(*FTSR, bit);
	
	if(interrupt == true)
	{
		bit::set(*IMR, bit);
	}
	else
	{
		bit::clear(*IMR, bit);
	}
	
	return(OK);
}


feedback EXTI::init_event_internal(e_line line, bool event)
{
	//	Boundary check
	if((uint32) line > 40)
	{
		return(FAIL);
	}
	
	
	//	Get Registers
	const uint32 registerOffset = ((uint32) line) / 32;
	const uint32 bit = ((uint32) line) % 32;
	
	
	//	The Registers for the Lines 32 and above follow 0x20 Byte (8 Words) behind those for the Lines 0 to 31
	volatile uint32* const RTSR	= MCU::EXTI::RTSR1	+ 8 * registerOffset;
	volatile uint32* const FTSR	= MCU::EXTI::FTSR1	+ 8 * registerOffset;
	volatile uint32* const EMR		= MCU::EXTI::EMR1		+ 8 * registerOffset;
	
	
	//	Configure
	bit::set(*RTSR, bit);
	bit::clear(*FTSR, bit);
	
	if(event == true)
	{
		bit::set(*EMR, bit);
	}
	else
	{
		bit::clear(*EMR, bit);
	}
	
	return(OK);
}







feedback EXTI::clear_pendingBit(MCU::PIN pin)
{
	GPIO& gpio = STM32L451RET6::get().get_gpio();
	*MCU::EXTI::PR1 = 1 << gpio.get_pinNumber(pin);
	return(OK);
}


feedback EXTI::clear_pendingBit(e_line line)
{
	//	Boundary Check
	if((uint32) line > 40)
	{
		return(FAIL);
	}
	
	
	//	Get Register
	const uint32 registerOffset = ((uint32) line) / 32;
	const uint32 bit = ((uint32) line) % 32;
	
	
	//	The Registers for the Lines 32 and above follow 0x20 Byte (8 Words) behind those for the Lines 0 to 31
	volatile uint32* const PR = MCU::EXTI::PR1 + 8 * registerOffset;
	
	
	//	Clear pending Bit by writing 1 to it
	*PR = 1 << bit;
	
	return(OK);
}


bool EXTI::isPending(MCU::PIN pin)
{
	GPIO& gpio = STM32L451RET6::get().get_gpio();
	return(bit::isSet(*MCU::EXTI::PR1, gpio.get_pinNumber(pin)));
}


bool EXTI::isPending(e_line line)
{
	//	Boundary Check
	if((uint32) line > 40)
	{
		return(false);
	}
	
	
	//	Get Register
	const uint32 registerOffset = ((uint32) line) / 32;
	const uint32 bit = ((uint32) line) % 32;
	
	
	//	The Registers for the Lines 32 and above follow 0x20 Byte (8 Words) behind those for the Lines 0 to 31
	volatile uint32* const PR = MCU::EXTI::PR1 + 8 * registerOffset;
	
	
	//	Check pending Bit
	return(bit::isSet(*PR, bit));
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







//	GPIO Line 0
CODE_RAM void ISR_EXTI_0()
{
	STM32L451RET6::get().get_exti().dispatch(0, 0);
}


//	GPIO Line 1
CODE_RAM void ISR_EXTI_1()
{
	STM32L451RET6::get().get_exti().dispatch(1, 1);
}


//	GPIO Line 2
CODE_RAM void ISR_EXTI_2()
{
	STM32L451RET6::get().get_exti().dispatch(2, 2);
}


//	GPIO Line 3
CODE_RAM void ISR_EXTI_3()
{
	STM32L451RET6::get().get_exti().dispatch(3, 3);
}


//	GPIO Line 4
CODE_RAM void ISR_EXTI_4()
{
	STM32L451RET6::get().get_exti().dispatch(4, 4);
}


//	GPIO Lines 5 ... 9
CODE_RAM void ISR_EXTI_9_TO_5()
{
	STM32L451RET6::get().get_exti().dispatch(5, 9);
}


//	GPIO Lines 10 ... 15
CODE_RAM void ISR_EXTI_15_TO_10()
{
	STM32L451RET6::get().get_exti().dispatch(10, 15);
}
