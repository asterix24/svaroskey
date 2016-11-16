#include "io.h"
#include "flash.h"

#define PAGE_BASE(addr)	(addr & (~(FLASH_PAGE_SIZE - 1)))

int FLASH_WriteBlock(uint32_t dst, const void *src, int count)
{
	uint16_t *data;
	uint32_t addr, end;
	int num_pages;

	if (count <= 0)
		return 0;

	data = (uint16_t *)src;
	addr = dst;
	end = dst + count;

	/* Erase all the destination pages */
	while (PAGE_BASE(addr) <= PAGE_BASE(end)) {
		FLASH_ErasePage(addr);
		addr += FLASH_PAGE_SIZE;
	}

	/* Half-word access whenever possible */
	for (addr = dst; addr <= (end - 2); addr += 2) {
		FLASH_WriteHalf(addr, *data++);
	}

	/* There is still one byte left to write */
	if (addr < end) {
		FLASH_WriteHalf(addr, (*data) & 0x00FF);	
	}

	return 0;
}
