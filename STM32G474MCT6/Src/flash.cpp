#include "../Inc/stm32g474mct6.hpp"





/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

feedback Flash::set_waitStates(uint32 clock_ahb, PWR::e_voltageScaling voltageScaling)
{
	typedef struct
	{
		uint32 frequency[5];
	}s_array;
	
	const Pair<PWR::e_voltageScaling, s_array> waitStateMaxFrequencies[3] =
	{
		{PWR::e_voltageScaling::RANGE1_1V28, {34000000, 68000000, 102000000, 136000000, 170000000}},
		{PWR::e_voltageScaling::RANGE1_1V2,  {30000000, 60000000,  90000000, 120000000, 150000000}},
		{PWR::e_voltageScaling::RANGE2_1V0,  {12000000, 24000000,  26000000,  26000000,  26000000}}
	};
	
	
	//	Calculate needed Waitstates
	uint32 waitStates = 4;
	for(auto& i: waitStateMaxFrequencies)
	{
		if(i.first() == voltageScaling)
		{
			const s_array frequencies = i.second();
			for(uint32 j = 0; j < 5; j++)
			{
				const uint32 index = 4 - j;
				if(clock_ahb <= frequencies.frequency[index])
				{
					waitStates = index;
				}
				else
				{
					break;
				}
			}
			break;
		}
	}
	
	
	//	Write Value to Register
	uint32 temp = *MCU::FLASH::ACR & 0xFFFFFFF8;
	*MCU::FLASH::ACR = temp | waitStates;
	
	
	//	Update internal Value
	m_waitStates = waitStates;
	
	
	return(OK);
}