#ifndef RCC_H
#define RCC_H

#include <stdint.h>

/* RCC peripheral definition */
struct RCC_Periph {
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
};

/* RCC instances */
#define RCC	((struct RCC_Periph *)(0x40021000))

/* RCC public methods */
void RCC_ClockInit(void);
void RCC_APB2Periph_SetEnabled(uint32_t mask, uint8_t state);

#endif
