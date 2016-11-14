#include "rcc.h"
#include "gpio.h"
#include "flash.h"
#include "usart.h"

int main(void)
{
	uint16_t dat;
	int ret;

	RCC_APB2Periph_SetEnabled((1 << 14) | (1 << 2) | (1 << 0), 1);

	GPIO_SetPinMode(GPIOA, (1 << 9) | (1 << 10), 0);
	USART_Init(USART1);

	USART_Send(USART1, '?');

	ret = FLASH_WriteHalf((uint16_t *)0x08001032, 0x004F);
	dat = *(uint16_t *)0x08001032;
	USART_Send(USART1, dat & 0xFF);

	ret = FLASH_ErasePage(0x08001032);
	USART_Send(USART1, ret + 'K');

	USART_Send(USART1, '!');

	while (1)
		;
}
