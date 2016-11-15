#include "rcc.h"
#include "gpio.h"
#include "flash.h"
#include "timers.h"
#include "usart.h"

static volatile uint32_t ticks;

void SysTick_IRQHandler(void)
{
	ticks++;
}

void HardFault_IRQHandler(void)
{
	USART_Send(USART1, 'x');
	while (1) ;
}

void mdelay(uint32_t ms)
{
	uint32_t start = ticks;
	while (ticks < start + ms) ;
}

int main(void)
{
	uint16_t dat;
	int ret;

	RCC_ClockInit();
	SysTick_Init();

	RCC_APB2Periph_SetEnabled((1 << 14) | (1 << 2) | (1 << 0), 1);

	GPIO_SetPinMode(GPIOA, (1 << 9) | (1 << 10), 0);
	USART_Init(USART1);

	ret = FLASH_WriteHalf((uint16_t *)0x08001032, 0x004F);
	dat = *(uint16_t *)0x08001032;

	USART_Send(USART1, ret + 'O');
	USART_Send(USART1, dat & 0xFF);

	ret = FLASH_ErasePage(0x08001032);
	USART_Send(USART1, ret + 'K');

	/* Should print OOK. */

	while (1) {
		USART_Send(USART1,'.');
		mdelay(1000);
	}
}
