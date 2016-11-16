#include "flash.h"

/* FLASH keys for unlock sequence */
#define FLASH_KEY1	0x45670123
#define FLASH_KEY2	0xCDEF89AB

/* FLASH CR register bits */
#define FLASH_CR_PG		(1 << 0)
#define FLASH_CR_PER		(1 << 1)
#define FLASH_CR_MER		(1 << 2)
#define FLASH_CR_OPTPG		(1 << 4)
#define FLASH_CR_OPTER		(1 << 5)
#define FLASH_CR_STRT		(1 << 6)
#define FLASH_CR_LOCK		(1 << 7)
#define FLASH_CR_OPTWRE		(1 << 9)
#define FLASH_CR_ERRIE		(1 << 10)
#define FLASH_CR_EOPIE		(1 << 12)

/* FLASH SR register bits */
#define FLASH_SR_BSY		(1 << 0)
#define FLASH_SR_PGERR		(1 << 2)
#define FLASH_SR_WRPRTERR	(1 << 4)
#define FLASH_SR_EOP		(1 << 5)

static bool FLASH_Busy(void)
{
	return FLASH->SR & FLASH_SR_BSY;
}

static bool FLASH_Unlock(void)
{
	FLASH->KEYR = FLASH_KEY1;
	FLASH->KEYR = FLASH_KEY2;
	return !(FLASH->CR & FLASH_CR_LOCK);
}

static bool FLASH_Lock(void)
{
	FLASH->CR |= FLASH_CR_LOCK;
	return (FLASH->CR & FLASH_CR_LOCK);
}

int FLASH_ErasePage(uint32_t addr)
{
	uint32_t *page_base = (uint32_t *)(addr & 0xFFFFFC00);
	int i;

	while (FLASH_Busy()) ;

	/* Unlock the flash if locked */
	if (FLASH->CR & FLASH_CR_LOCK) {
		if (!FLASH_Unlock())
			return -1;
	}
	
	/* Set erase bit and page base */
	FLASH->CR |= FLASH_CR_PER;
	FLASH->AR = (uint32_t)page_base;

	/* Trigger erase start */
	FLASH->CR |= FLASH_CR_STRT;

	while (FLASH_Busy()) ;

	/* Unset erase bit */
	FLASH->CR &= ~(FLASH_CR_STRT | FLASH_CR_PER);

	if (!(FLASH->SR & FLASH_SR_EOP))
		return -2;

	/* Verify */
	for (i = 0; i < 256; i++)
		if (*(page_base + i) != 0xFFFFFFFF)
			return -3;

	return 0;
}

int FLASH_WriteHalf(uint32_t addr, uint16_t data)
{
	while (FLASH_Busy()) ;

	/* Unlock the flash if locked */
	if (FLASH->CR & FLASH_CR_LOCK) {
		if (!FLASH_Unlock())
			return -1;
	}
	
	/* Set programming bit and write data */
	FLASH->CR |= FLASH_CR_PG;
	*(uint16_t *)addr = data;

	/* Wait for transfer to finish */
	while (FLASH_Busy()) ;

	/* Unset programming bit */
	FLASH->CR &= ~FLASH_CR_PG;

	/* Check for errors */
	if (FLASH->SR & FLASH_SR_PGERR)
		return -2;

	if (!(FLASH->SR & FLASH_SR_EOP))
		return -3;

	/* Verify */
	if (*(uint16_t *)addr != data)
		return -4;

	return 0;
}

void FLASH_EnablePrefetchBuffer(bool state)
{
	if (state)
		FLASH->ACR |= (1 << 4);
	else
		FLASH->ACR &= ~(1 << 4);
}

void FLASH_SetAccessLatency(enum FLASH_AccessLatency lat)
{
	FLASH->ACR &= ~0x7;
	FLASH->ACR |= lat & 0x7;
}
