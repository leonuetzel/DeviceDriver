#pragma once

#include "cmos.hpp"





//	Cache Maintenance for the Bus Masters of the STM32H753 (DMA_1, DMA_2, MDMA, DMA2D, SDMMC_1, SDMMC_2) with the Data Cache of the Cortex-M7
//	CMOS switches the Data Cache on at Startup (Cache::startup, if Start and Block Size of the Heap are multiples of 32 Byte), see cache.hpp of CMOS
//	The Application can switch it off with CMOS::get().get_cache().DCache_setState(false)
//	The Drivers call these Functions themselves, an Application only needs them for a Bus Master it starts directly (e.g. after an MDMA Transfer)
//	-	beforeRead: a Bus Master is going to read Memory written by the CPU, dirty Cache Lines are written back
//	-	beforeWrite: a Bus Master is going to write Memory, dirty Cache Lines are written back and discarded - the CPU must not access the Memory until the Transfer has ended
//	-	afterWrite: a Bus Master has written Memory and the CPU is going to read it, the Cache Lines are discarded
//	Memory written by a Bus Master should own its Cache Lines of 32 Byte: Start and Size are multiples of 32, e.g. with alignas(32) or from the Heap of CMOS
//	afterWrite keeps the Data of Neighbours in a partial Line at the Start or End: that Line is written back before it is discarded,
//	which is correct as long as the CPU does not write the Neighbours during the Transfer
//	beforeRead and beforeWrite end with a Barrier also without Data Cache: the Stores of the CPU must have reached the Memory before a Bus Master is started
//	From c_wholeCache_lines Cache Lines on (e.g. a large Part of a Framebuffer), the whole Cache is maintained by Set/Way in one Pass instead of
//	Line by Line. Never only invalidated: the dirty Lines of other Memory (Stacks, Heap in the AXI SRAM, Write-Back) would be lost
//	The Rectangle Variants maintain only the Lines of a Rectangle in an Image (e.g. for the DMA2D), not the whole Span between its first and last Byte
class CacheMaintenance
{
	public:

		static inline void beforeRead(const void* address, uint32 sizeInBytes);
		static inline void beforeWrite(const void* address, uint32 sizeInBytes);
		static inline void afterWrite(const void* address, uint32 sizeInBytes);
		
		//	The same for a Rectangle: numberOfLines Lines of bytesPerLine Bytes, stride Bytes from the Start of one Line to the next
		static inline void beforeRead(const void* address, uint32 bytesPerLine, uint32 numberOfLines, uint32 stride);
		static inline void beforeWrite(const void* address, uint32 bytesPerLine, uint32 numberOfLines, uint32 stride);
		static inline void afterWrite(const void* address, uint32 bytesPerLine, uint32 numberOfLines, uint32 stride);

		//	true if the Memory needs Maintenance: the Data Cache is on, the Memory is cacheable (MPU or Default Memory Map) and not in the Code Region (Flash, ITCM)
		static inline bool isRequired(const void* address, uint32 sizeInBytes);

		//	true if a Bus Master can write the Memory without Risk for other Data: the Data Cache is off, the Memory is not cacheable,
		//	or Start and Size are multiples of the Cache Line Size
		static inline bool ownsCacheLines(const void* address, uint32 sizeInBytes);
		
		//	true if a Bus Master reaches the whole Memory (RM0433, Table 3 Bus-master-to-bus-slave interconnect)
		//	DMA_1, DMA_2 and SDMMC_2: Flash, AXI SRAM, SRAM1 ... SRAM4, QUADSPI and FMC - not the ITCM and the DTCM of the Core
		//	SDMMC_1 (D1 Domain): only Flash, AXI SRAM, QUADSPI and FMC
		static inline bool isReachableByDMA(const void* address, uint32 sizeInBytes);
		static inline bool isReachableBySDMMC_1(const void* address, uint32 sizeInBytes);
		static inline bool isReachableBySDMMC_2(const void* address, uint32 sizeInBytes);
		
	private:
		
		//	From this Number of Cache Lines on, one Pass over the whole Cache is faster: measured on the H753 (HMI, 2026-10-16), Set/Way over the
		//	whole Cache 21 µs, by Address about 15 ns per Line of 32 Byte - the Break-even is at about 1400 Lines (45 KB)
		static constexpr uint32 c_wholeCache_lines = 1400;
		
		//	true if Memory of this Size or a Rectangle with this Size is maintained over the whole Cache - at most one more Line per Image Line for an
		//	unaligned Start
		static inline bool isMaintainedWhole(const Cache& cache, uint32 bytesPerLine, uint32 numberOfLines);
		
		static inline bool isInside(const void* address, uint32 sizeInBytes, uint32 regionStart, uint32 regionEnd);
};



/*****************************************************************************/
/*                    Globals and Static Initialization					 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Private	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      					Protected	  			 						 						 */
/*****************************************************************************/





/*****************************************************************************/
/*                      						Public	  			 						 						 */
/*****************************************************************************/

inline void CacheMaintenance::beforeRead(const void* address, uint32 sizeInBytes)
{
	Cache& cache = CMOS::get().get_cache();
	if(cache.DCache_isEnabled() == true && sizeInBytes > 0)
	{
		if(isMaintainedWhole(cache, sizeInBytes, 1) == true)
		{
			cache.DCache_clean();
		}
		else
		{
			cache.DCache_clean(address, sizeInBytes);
		}
	}
	asm volatile("dsb" : : : "memory");
}


inline void CacheMaintenance::beforeWrite(const void* address, uint32 sizeInBytes)
{
	Cache& cache = CMOS::get().get_cache();
	if(cache.DCache_isEnabled() == true && sizeInBytes > 0)
	{
		if(isMaintainedWhole(cache, sizeInBytes, 1) == true)
		{
			cache.DCache_cleanAndInvalidate();
		}
		else
		{
			cache.DCache_cleanAndInvalidate(address, sizeInBytes);
		}
	}
	asm volatile("dsb" : : : "memory");
}


inline void CacheMaintenance::afterWrite(const void* address, uint32 sizeInBytes)
{
	Cache& cache = CMOS::get().get_cache();
	if(cache.DCache_isEnabled() == false || sizeInBytes == 0)
	{
		return;
	}
	
	
	//	Large Memory: the whole Cache is written back and discarded - the CPU has not written the Memory during the Transfer, so no Line of it is dirty
	if(isMaintainedWhole(cache, sizeInBytes, 1) == true)
	{
		cache.DCache_cleanAndInvalidate();
		return;
	}


	//	Lines completely inside the Memory are discarded, a partial Line at the Start or End is written back before, so the Data of its Neighbours is kept
	const uint32 lineSize = cache.get_DCacheLineSize();
	const uint32 start = (uint32) address;
	const uint32 end = start + sizeInBytes;
	const uint32 fullLines_start = (start + lineSize - 1) & ~(lineSize - 1);
	const uint32 fullLines_end = end & ~(lineSize - 1);
	if(fullLines_start >= fullLines_end)
	{
		cache.DCache_cleanAndInvalidate(address, sizeInBytes);
		return;
	}
	if(start < fullLines_start)
	{
		cache.DCache_cleanAndInvalidate(address, fullLines_start - start);
	}
	cache.DCache_invalidate((const void*) fullLines_start, fullLines_end - fullLines_start);
	if(fullLines_end < end)
	{
		cache.DCache_cleanAndInvalidate((const void*) fullLines_end, end - fullLines_end);
	}
}


inline void CacheMaintenance::beforeRead(const void* address, uint32 bytesPerLine, uint32 numberOfLines, uint32 stride)
{
	//	Lines without Gap are one Memory, a large Rectangle is maintained over the whole Cache, otherwise Line by Line
	Cache& cache = CMOS::get().get_cache();
	if(stride == bytesPerLine || numberOfLines <= 1)
	{
		beforeRead(address, bytesPerLine * numberOfLines);
		return;
	}
	if(cache.DCache_isEnabled() == true && bytesPerLine > 0)
	{
		if(isMaintainedWhole(cache, bytesPerLine, numberOfLines) == true)
		{
			cache.DCache_clean();
		}
		else
		{
			for(uint32 i = 0; i < numberOfLines; i++)
			{
				cache.DCache_clean((const uint8*) address + i * stride, bytesPerLine);
			}
		}
	}
	asm volatile("dsb" : : : "memory");
}


inline void CacheMaintenance::beforeWrite(const void* address, uint32 bytesPerLine, uint32 numberOfLines, uint32 stride)
{
	Cache& cache = CMOS::get().get_cache();
	if(stride == bytesPerLine || numberOfLines <= 1)
	{
		beforeWrite(address, bytesPerLine * numberOfLines);
		return;
	}
	if(cache.DCache_isEnabled() == true && bytesPerLine > 0)
	{
		if(isMaintainedWhole(cache, bytesPerLine, numberOfLines) == true)
		{
			cache.DCache_cleanAndInvalidate();
		}
		else
		{
			for(uint32 i = 0; i < numberOfLines; i++)
			{
				cache.DCache_cleanAndInvalidate((const uint8*) address + i * stride, bytesPerLine);
			}
		}
	}
	asm volatile("dsb" : : : "memory");
}


inline void CacheMaintenance::afterWrite(const void* address, uint32 bytesPerLine, uint32 numberOfLines, uint32 stride)
{
	//	Every Line like a Memory of its own: its partial Cache Lines at the Start and End keep the Data of the Neighbours (see above)
	Cache& cache = CMOS::get().get_cache();
	if(stride == bytesPerLine || numberOfLines <= 1)
	{
		afterWrite(address, bytesPerLine * numberOfLines);
		return;
	}
	if(cache.DCache_isEnabled() == false || bytesPerLine == 0)
	{
		return;
	}
	if(isMaintainedWhole(cache, bytesPerLine, numberOfLines) == true)
	{
		cache.DCache_cleanAndInvalidate();
		return;
	}
	for(uint32 i = 0; i < numberOfLines; i++)
	{
		afterWrite((const uint8*) address + i * stride, bytesPerLine);
	}
}


inline bool CacheMaintenance::isMaintainedWhole(const Cache& cache, uint32 bytesPerLine, uint32 numberOfLines)
{
	const uint32 lineSize = cache.get_DCacheLineSize();
	if(lineSize == 0)
	{
		return(false);
	}
	const uint32 cacheLinesPerLine = (bytesPerLine + lineSize - 1) / lineSize + ((numberOfLines > 1) ? 1 : 0);
	return((uint64) cacheLinesPerLine * numberOfLines >= c_wholeCache_lines);
}


inline bool CacheMaintenance::isRequired(const void* address, uint32 sizeInBytes)
{
	//	The Code Region below 0x20000000 holds the Flash, which the CPU never writes, and the ITCM, which is never cached
	if(CMOS::get().get_cache().DCache_isEnabled() == false || sizeInBytes == 0 || ((uint32) address) < 0x20000000)
	{
		return(false);
	}
	return(Cache::isCacheable(address, sizeInBytes));
}


inline bool CacheMaintenance::ownsCacheLines(const void* address, uint32 sizeInBytes)
{
	Cache& cache = CMOS::get().get_cache();
	if(cache.DCache_isEnabled() == false || Cache::isCacheable(address, sizeInBytes) == false)
	{
		return(true);
	}
	const uint32 lineSize = cache.get_DCacheLineSize();
	return(((uint32) address) % lineSize == 0 && sizeInBytes % lineSize == 0);
}


inline bool CacheMaintenance::isInside(const void* address, uint32 sizeInBytes, uint32 regionStart, uint32 regionEnd)
{
	//	The Memory from address to address + sizeInBytes lies completely in the Region from regionStart to regionEnd (End excluded)
	const uint32 start = (uint32) address;
	return(start >= regionStart && start < regionEnd && sizeInBytes <= regionEnd - start);
}


inline bool CacheMaintenance::isReachableBySDMMC_1(const void* address, uint32 sizeInBytes)
{
	//	Flash (2 MB), AXI SRAM (512 KB), FMC (NOR/PSRAM/NAND and SDRAM Banks) and QUADSPI
	return(isInside(address, sizeInBytes, 0x08000000, 0x08200000) || isInside(address, sizeInBytes, 0x24000000, 0x24080000) ||
				 isInside(address, sizeInBytes, 0x60000000, 0x80000000) || isInside(address, sizeInBytes, 0x90000000, 0xA0000000) ||
				 isInside(address, sizeInBytes, 0xC0000000, 0xE0000000));
}


inline bool CacheMaintenance::isReachableBySDMMC_2(const void* address, uint32 sizeInBytes)
{
	//	Additionally to SDMMC_1: SRAM1 ... SRAM3 (D2 Domain, 288 KB) and SRAM4 (D3 Domain, 64 KB)
	return(isReachableBySDMMC_1(address, sizeInBytes) || isInside(address, sizeInBytes, 0x30000000, 0x30048000) ||
				 isInside(address, sizeInBytes, 0x38000000, 0x38010000));
}


inline bool CacheMaintenance::isReachableByDMA(const void* address, uint32 sizeInBytes)
{
	//	DMA_1 and DMA_2 reach the same Memories as SDMMC_2
	return(isReachableBySDMMC_2(address, sizeInBytes));
}
