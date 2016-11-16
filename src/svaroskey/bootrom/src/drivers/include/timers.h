#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>

/* SYSTICK peripheral definition */
struct SYSTICK_Periph {
	volatile uint32_t CSR;
	volatile uint32_t RVR;
	volatile uint32_t CVR;
	volatile uint32_t CALIB;
};

/* SYSTICK instances */
#define SYSTICK	((struct SYSTICK_Periph *)(0xE000E010))

/* SYSTICK public methods */
void SysTick_Init(void);
void Delay(uint32_t ms);
uint32_t GetTicks(void);

#endif
