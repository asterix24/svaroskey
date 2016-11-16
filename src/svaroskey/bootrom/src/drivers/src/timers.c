#include "timers.h"

/* SYSTICK CSR register bits */
#define SYSTICK_CSR_ENABLE	(0x1 << 0)
#define SYSTICK_CSR_TICKINT	(0x1 << 1)
#define SYSTICK_CSR_CLKSOURCE	(0x1 << 2)
#define SYSTICK_CSR_COUNTFLAG	(0x1 << 16)

/* SYSTICK RVR register bits */
#define SYSTICK_RVR_RELOAD	(0xFFFFFF << 0)

/* SYSTICK CVR register bits */
#define SYSTICK_CVR_CURRENT	(0xFFFFFF << 0)

static volatile uint32_t ticks;

void SysTick_IRQHandler(void)
{
	ticks++;
}

void SysTick_Init(void)
{
	/* Clear current value */
	SYSTICK->CVR &= ~SYSTICK_CVR_CURRENT;

	/* Set reload value (@ 72MHz, 1ms) */
	SYSTICK->RVR = 71999 & SYSTICK_RVR_RELOAD;

	/* Start counting */
	SYSTICK->CSR |= SYSTICK_CSR_CLKSOURCE |
			SYSTICK_CSR_TICKINT |
			SYSTICK_CSR_ENABLE;
}

void Delay(uint32_t ms)
{
	uint32_t start = ticks;
	while (ticks < start + ms) ;
}

uint32_t GetTicks(void)
{
	return ticks;
}
