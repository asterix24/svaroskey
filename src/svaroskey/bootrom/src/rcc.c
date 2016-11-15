#include "rcc.h"
#include "flash.h"

/* RCC CR register bits */
#define RCC_CR_HSION		(1 << 0)
#define RCC_CR_HSIRDY		(1 << 1)
#define RCC_CR_HSEON		(1 << 16)
#define RCC_CR_HSERDY		(1 << 17)
#define RCC_CR_PLLON		(1 << 24)
#define RCC_CR_PLLRDY		(1 << 25)

/* RCC CFGR register bits */
#define RCC_CFGR_SW		(0x3 << 0)
#define RCC_CFGR_HPRE		(0xF << 4)
#define RCC_CFGR_PPRE1		(0x7 << 8)
#define RCC_CFGR_PPRE2		(0x7 << 11)
#define RCC_CFGR_ADCPRE		(0x3 << 14)
#define RCC_CFGR_PLLSRC		(0x1 << 16)
#define RCC_CFGR_PLLXTPRE	(0x1 << 17)
#define RCC_CFGR_PLLMUL		(0x1 << 18)
#define RCC_CFGR_USBPRE		(0x1 << 22)

/* RCC CFGR SW bit field */
#define RCC_CFGR_SW_HSI		(0x0)
#define RCC_CFGR_SW_HSE		(0x1)
#define RCC_CFGR_SW_PLL		(0x2)

/* RCC CFGR PLLMUL bit field */
#define RCC_CFGR_PLLMUL_MSK	(0xF << 18)

static void RCC_SetClockSource(uint32_t source)
{
	uint32_t reg;

	reg = RCC->CFGR & (~RCC_CFGR_SW);
	reg |= source;
	RCC->CFGR = reg;
}

static void RCC_ConfigPLL(uint8_t mul, bool div2)
{
	uint32_t reg;

	reg = RCC->CFGR & (~RCC_CFGR_PLLMUL_MSK);

	if (div2)
		reg |= RCC_CFGR_PLLXTPRE;

	/* Use HSE as PLL input clock */
	reg |= RCC_CFGR_PLLSRC;

	/* Configure multiplier */
	reg |= (mul - 2) << 18;

	/* Apply configuration and enable PLL */
	RCC->CFGR = reg;

	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY)) ;
}

void RCC_ClockInit(void)
{
	/* Enable HSI oscillator */
	RCC->CR |= RCC_CR_HSION;
	while (!(RCC->CR & RCC_CR_HSIRDY)) ;

	/* Enable HSE oscillator */
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY)) ;

	/* Clock the system from HSI */
	RCC_SetClockSource(RCC_CFGR_SW_HSI);

	/* Configure PLL multiplier (x6) with no divider */
	RCC_ConfigPLL(6, false);

	/* Configure USB clock @ 47MHz */
	RCC->CFGR &= ~RCC_CFGR_USBPRE;

	/* Configure AHB clock @ 72MHz */
	RCC->CFGR &= ~RCC_CFGR_HPRE;

	/* Configure APB1 clock @ 36MHz */
	RCC->CFGR &= ~RCC_CFGR_PPRE1;
	RCC->CFGR |= 0x4 << 8;

	/* Configure APB2 clock @ 72MHz */
	RCC->CFGR &= ~RCC_CFGR_PPRE2;

	/* Configure ADC clock @ 9MHz */
	RCC->CFGR |= RCC_CFGR_ADCPRE;

	/* Configure flash to support SYSCLK > 48MHz */
	FLASH_EnablePrefetchBuffer(true);
	FLASH_SetAccessLatency(FLASH_TwoWaitStates);

	/* Set PLL as clock source */
	RCC->CFGR |= RCC_CFGR_SW_PLL;
}

void RCC_APB2Periph_SetEnabled(uint32_t mask, uint8_t state)
{
	if (state)
		RCC->APB2ENR |= mask;
	else
		RCC->APB2ENR &= ~mask;
}
