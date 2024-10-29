#include "../Inc/flash.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback Flash::startup()
{
	enable_ECC();
	return(OK);
}







feedback Flash::set_waitStates(uint32 clock_ahb, PWR::e_voltageLevel voltageLevel)
{
	uint32 mask_ws = 0;
	uint32 mask_pd = 0;
	if(voltageLevel == PWR::e_voltageLevel::VOS_3)
	{
		if(clock_ahb < 45000000)
		{
			mask_ws = 0x0;
			mask_pd = 0x0;
		}
		else
		{
			if(clock_ahb < 90000000)
			{
				mask_ws = 0x1;
				mask_pd = 0x1;
			}
			else
			{
				if(clock_ahb < 135000000)
				{
					mask_ws = 0x2;
					mask_pd = 0x1;
				}
				else
				{
					if(clock_ahb < 180000000)
					{
						mask_ws = 0x3;
						mask_pd = 0x2;
					}
					else
					{
						if(clock_ahb < 225000000)
						{
							mask_ws = 0x4;
							mask_pd = 0x2;
						}
						else
						{
							return(FAIL);
						}
					}
				}
			}
		}
	}

	if(voltageLevel == PWR::e_voltageLevel::VOS_2)
	{
		if(clock_ahb < 55000000)
		{
			mask_ws = 0x0;
			mask_pd = 0x0;
		}
		else
		{
			if(clock_ahb < 110000000)
			{
				mask_ws = 0x1;
				mask_pd = 0x1;
			}
			else
			{
				if(clock_ahb < 165000000)
				{
					mask_ws = 0x2;
					mask_pd = 0x1;
				}
				else
				{
					if(clock_ahb < 225000000)
					{
						mask_ws = 0x3;
						mask_pd = 0x2;
					}
					else
					{
						return(FAIL);
					}
				}
			}
		}
	}

	if(voltageLevel == PWR::e_voltageLevel::VOS_1 || voltageLevel == PWR::e_voltageLevel::VOS_0)
	{
		if(clock_ahb < 70000000)
		{
			mask_ws = 0x0;
			mask_pd = 0x0;
		}
		else
		{
			if(clock_ahb < 140000000)
			{
				mask_ws = 0x1;
				mask_pd = 0x1;
			}
			else
			{
				if(clock_ahb < 185000000)
				{
					mask_ws = 0x2;
					mask_pd = 0x1;
				}
				else
				{
					if(clock_ahb < 210000000)
					{
						mask_ws = 0x2;
						mask_pd = 0x2;
					}
					else
					{
						if(clock_ahb < 225000000)
						{
							mask_ws = 0x3;
							mask_pd = 0x2;
						}
						else
						{
							if(clock_ahb < 480000000)
							{
								mask_ws = 0x4;
								mask_pd = 0x2;
							}
							else
							{
								return(FAIL);
							}
						}
					}
				}
			}
		}
	}
	
	m_waitStates = mask_ws;
	m_programmingDelay = mask_pd;
	
	*MCU::FLASH_1::ACR &= 0xFFFFFFC0;
	*MCU::FLASH_1::ACR |= (mask_pd << 4);
	*MCU::FLASH_1::ACR |= mask_ws;

	*MCU::FLASH_2::ACR &= 0xFFFFFFC0;
	*MCU::FLASH_2::ACR |= (mask_pd << 4);
	*MCU::FLASH_2::ACR |= mask_ws;

	return(OK);
}


void Flash::enable_ECC()
{
	*MCU::FLASH_1::KEY = 0x45670123;																																															//	Unlock FLASH_1_CR
	*MCU::FLASH_1::KEY = 0xCDEF89AB;
	
	bit::set(*MCU::FLASH_1::CR, 26);																																															//	Enable Bank 1 ECC Double Detection Error Interrupt
	bit::set(*MCU::FLASH_1::CR, 25);																																															//	Enable Bank 1 ECC Single Correction Error Interrupt
	
	bit::set(*MCU::FLASH_1::CR, 0);																																																//	Lock FLASH_1_CR
}