#include "rcc.h"
#include "gpio.h"
#include "flash.h"
#include "timers.h"
#include "usart.h"

void HardFault_IRQHandler(void)
{
	USART_Send(USART1, 'x');
	while (1) ;
}

void hw_init(void)
{
	/* Setup clocks */
	RCC_ClockInit();
	SysTick_Init();

	/* Setup peripherals */
	RCC_APB2Periph_SetEnabled((1 << 14) | (1 << 2) | (1 << 0), 1);
	GPIO_SetPinMode(GPIOA, (1 << 9) | (1 << 10), 0);
	USART_Init(USART1);
}

int main(void)
{
	uint16_t dat;
	int ret;

	hw_init();

	ret = FLASH_WriteHalf((uint16_t *)0x08001032, 0x004F);
	dat = *(uint16_t *)0x08001032;

	USART_Send(USART1, ret + 'O');
	USART_Send(USART1, dat & 0xFF);

	ret = FLASH_ErasePage(0x08001032);
	USART_Send(USART1, ret + 'K');

	/* Should print OOK. */

	while (1) {
		USART_Send(USART1,'.');
		Delay(1000);
	}
}
