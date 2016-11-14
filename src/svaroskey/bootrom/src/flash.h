#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>
#include <stdbool.h>

/* FLASH peripheral definition */
struct FLASH_Periph {
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t AR;
	volatile uint32_t __reserved1;
	volatile uint32_t OBR;
	volatile uint32_t WRPR;
};

/* FLASH instances */
#define FLASH	((struct FLASH_Periph *)(0x40022000))

/* FLASH public methods */
int FLASH_ErasePage(uint32_t addr);
int FLASH_WriteHalf(uint16_t *addr, uint16_t data);

#endif
