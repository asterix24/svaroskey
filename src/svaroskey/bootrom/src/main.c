#include "rcc.h"
#include "gpio.h"
#include "usart.h"

int main(void)
{
	RCC_APB2Periph_SetEnabled((1 << 14) | (1 << 2) | (1 << 0), 1);

	GPIO_SetPinMode(GPIOA, (1 << 9) | (1 << 10), 0);
	USART_Init(USART1);

	USART_Send(USART1, 'A');

	while (1)
		;
}
