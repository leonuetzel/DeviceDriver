#include "../Inc/stm32l451ret6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/

NORETURN void PWR::enterLowPowerMode(uint32 mode)
{
	//	Shutdown: the Marker in RTC_BKP31R tells the next Start that the Brownout Reset is the Exit from Shutdown (see startup()) - the Backup
	//	Domain keeps it, the PWR Registers do not
	STM32L451RET6& stm32 = STM32L451RET6::get();
	stm32.get_rcc().module_clockInit(RCC::e_module::RTC, true);
	stm32.get_pwr().set_backupDomain_writeProtection(false);
	if(mode == c_lowPowerMode_shutdown)
	{
		*MCU::RTC::BKP_31 = c_shutdownMarker;
	}


	//	The Entry needs a Core without pending Interrupt (RM0394, Standby and Shutdown mode entry): CMOS::shutdown() has stopped the SysTick,
	//	here all Peripheral Interrupts are disabled and their pending Bits cleared. Nothing runs afterwards - the Wakeup is a Reset
	for(uint32 i = 0; i < 8; i++)
	{
		*(CORE::NVIC::ICER + i) = 0xFFFFFFFF;
		*(CORE::NVIC::ICPR + i) = 0xFFFFFFFF;
	}


	//	Pull-ups and Pull-downs of set_lowPowerPull(): APC applies them at once, also in Run Mode, so it is set only here (RM0394, PWR_CR3)
	bit::set(*MCU::PWR::CR3, 10);


	//	The Entry also needs all WUFx cleared: those of Pins that are not enabled, and SBF of an earlier Standby. A WUFx of an enabled Pin
	//	means that its Wakeup Event has happened meanwhile - then the Device restarts below as if it had woken up
	const uint32 enabledPins = *MCU::PWR::CR3 & 0x1F;
	*MCU::PWR::SCR = (~enabledPins & 0x1F) | (1 << 8);


	//	Low-power Mode (LPMS) and Deep Sleep of the Core, the Dummy Read waits until the Write has reached the PWR
	*MCU::PWR::CR1 = (*MCU::PWR::CR1 & 0xFFFFFFF8) | mode;
	bit::set(*CORE::SCB::SCR, 2);
	(void) *MCU::PWR::CR1;


	while(true)
	{
		if((*MCU::PWR::SR1 & enabledPins) != 0)
		{
			*MCU::RTC::BKP_31 = 0;
			CMOS::get().reset();
		}
		asm volatile("dsb" ::: "memory");
		asm volatile("wfi");
	}
}


void PWR::disable_rtcOnWakeupPin(uint32 pin)
{
	//	The RTC can use the Pins of WKUP_1 (PA0 = RTC_TAMP2), WKUP_2 (PC13 = RTC_TAMP1, RTC_TS, RTC_OUT) and WKUP_3 (PE6 = RTC_TAMP3), it
	//	would override the Wakeup Function (RM0394, RTC: RTC_TAMPCR TAMPxE, RTC_CR TSE, COE, OSEL; RTC_OR RTC_OUT_RMP moves RTC_OUT to PB2)
	//	These Settings survive Resets in the Backup Domain, so they are switched off here - only if set, an unused RTC is not touched
	uint32 mask_tampcr = 0;
	uint32 mask_cr = 0;
	switch(pin)
	{
		case 0:
			mask_tampcr = 1 << 3;
			break;

		case 1:
			mask_tampcr = 1 << 0;
			mask_cr = 1 << 11;
			if(bit::isCleared(*MCU::RTC::OR, 1) == true)
			{
				mask_cr |= (1 << 23) | (0x3 << 21);
			}
			break;

		case 2:
			mask_tampcr = 1 << 5;
			break;

		default:
			return;
	}
	if((*MCU::RTC::TAMPCR & mask_tampcr) == 0 && (*MCU::RTC::CR & mask_cr) == 0)
	{
		return;
	}


	//	Unlock the Write Protection of the RTC (RM0394, RTC_WPR), afterwards lock it again
	*MCU::RTC::WPR = 0xCA;
	*MCU::RTC::WPR = 0x53;
	*MCU::RTC::TAMPCR &= ~mask_tampcr;
	*MCU::RTC::CR &= ~mask_cr;
	*MCU::RTC::WPR = 0xFF;
}



/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

uint32 PWR::get_backupRegister(uint32 index)
{
	if(index >= c_numberOfBackupRegisters)
	{
		return(0);
	}


	//	The Backup Registers belong to the RTC and need its Bus Clock (RTCAPBEN)
	STM32L451RET6::get().get_rcc().module_clockInit(RCC::e_module::RTC, true);
	return(*(MCU::RTC::BKP_0 + index));
}


feedback PWR::set_backupRegister(uint32 index, uint32 value)
{
	if(index >= c_numberOfBackupRegisters)
	{
		return(FAIL);
	}


	//	Bus Clock of the RTC and Write Access to the Backup Domain (DBP)
	STM32L451RET6::get().get_rcc().module_clockInit(RCC::e_module::RTC, true);
	set_backupDomain_writeProtection(false);
	*(MCU::RTC::BKP_0 + index) = value;
	return(OK);
}


feedback PWR::set_wakeupPin(e_wakeupPin pin, bool enable, e_wakeupEdge edge)
{
	const uint32 number = (uint32) pin;
	if(number > 4)
	{
		return(FAIL);
	}
	if(enable == false)
	{
		bit::clear(*MCU::PWR::CR3, number);
		*MCU::PWR::SCR = 1 << number;
		return(OK);
	}


	//	The RTC must not use the Pin
	STM32L451RET6::get().get_rcc().module_clockInit(RCC::e_module::RTC, true);
	set_backupDomain_writeProtection(false);
	disable_rtcOnWakeupPin(number);


	//	Polarity, then enable the Pin (RM0394, PWR_CR4 WPx, PWR_CR3 EWUPx)
	if(edge == e_wakeupEdge::FALLING)
	{
		bit::set(*MCU::PWR::CR4, number);
	}
	else
	{
		bit::clear(*MCU::PWR::CR4, number);
	}
	bit::set(*MCU::PWR::CR3, number);


	//	Enabling the Pin or changing its Polarity can set WUFx at once: clear it afterwards, otherwise the Device would wake up at once
	*MCU::PWR::SCR = 1 << number;
	return(OK);
}


feedback PWR::set_lowPowerPull(MCU::PIN pin, e_lowPowerPull pull)
{
	//	PWR_PUCRx and PWR_PDCRx exist for the Ports A, B, C, D and H, 8 Bytes apart (PWR_PUCRH at 0x58 = 0x20 + 7 * 8, RM0394)
	const uint32 port = ((uint32) pin & 0xF0) >> 4;
	const uint32 number = (uint32) pin & 0x0F;
	if(port > 3 && port != 7)
	{
		return(FAIL);
	}


	//	Reserved Bits (RM0394): no Pull-up on PA14, no Pull-down on PA13, PA15 and PB4 (their Debug Pulls), Port H only PH0, PH1, PH3
	if((pull == e_lowPowerPull::UP && port == 0 && number == 14)
		|| (pull == e_lowPowerPull::DOWN && ((port == 0 && (number == 13 || number == 15)) || (port == 1 && number == 4)))
		|| (port == 7 && number != 0 && number != 1 && number != 3))
	{
		return(FAIL);
	}


	volatile uint32* const pullUp = MCU::PWR::PUCRA + 2 * port;
	volatile uint32* const pullDown = MCU::PWR::PDCRA + 2 * port;
	switch(pull)
	{
		case e_lowPowerPull::NONE:
			bit::clear(*pullUp, number);
			bit::clear(*pullDown, number);
			break;

		case e_lowPowerPull::UP:
			bit::clear(*pullDown, number);
			bit::set(*pullUp, number);
			break;

		case e_lowPowerPull::DOWN:
			bit::clear(*pullUp, number);
			bit::set(*pullDown, number);
			break;

		default:
			return(FAIL);
	}
	return(OK);
}


void PWR::clear_lowPowerPulls()
{
	//	Ports A, B, C, D, H; APC off, so the Pulls of the GPIO apply in Run Mode
	bit::clear(*MCU::PWR::CR3, 10);
	for(uint32 port = 0; port < 8; port++)
	{
		if(port > 3 && port != 7)
		{
			continue;
		}
		*(MCU::PWR::PUCRA + 2 * port) = 0;
		*(MCU::PWR::PDCRA + 2 * port) = 0;
	}
}


NORETURN void PWR::enterStandby()
{
	enterLowPowerMode(c_lowPowerMode_standby);
}


NORETURN void PWR::enterShutdown()
{
	enterLowPowerMode(c_lowPowerMode_shutdown);
}

