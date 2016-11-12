#include "rcc.h"

void RCC_APB2Periph_SetEnabled(uint32_t mask, uint8_t state)
{
	if (state)
		RCC->APB2ENR |= mask;
	else
		RCC->APB2ENR &= ~mask;
}
