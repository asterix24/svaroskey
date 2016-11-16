#include "rcc.h"
#include "gpio.h"
#include "flash.h"
#include "timers.h"
#include "usart.h"
#include "io.h"

#define SYN	0xA0
#define ACK	0x0A

void HardFault_IRQHandler(void)
{
	USART_Send(USART1, 'x', 0);
	while (1) ;
}

bool fw_wait_for_flashprog(void)
{
	uint8_t byte;

	/* Listen on USART1 for SYN for 1s */
	byte = USART_Recv(USART1, 1000);

	if (byte != SYN)
		return false;

	/* Reply with ACK */
	USART_Send(USART1, ACK, 1000);

	/* Wait another 1s for SYN+ACK */
	if (USART_Recv(USART1, 1000) != (SYN | ACK))
		return false;

	return true;
}

void hw_init(void)
{
	/* Setup clocks */
	RCC_ClockInit();
	SysTick_Init();

	/* Setup peripherals */
	RCC_APB2Periph_SetEnabled((1 << 14) | (1 << 2) | (1 << 0), 1);
	GPIO_SetPinMode(GPIOA, (1 << 9) | (1 << 10), 0);
	USART_Init(USART1, 115200);
}

int main(void)
{
	uint8_t byte;

	hw_init();

	if (fw_wait_for_flashprog())
		USART_Send(USART1, '!', 0);
	else
		USART_Send(USART1, '?', 0);

	while (1) {
		byte = USART_Recv(USART1, 1000);
		USART_Send(USART1, byte, 0);
	}
}
