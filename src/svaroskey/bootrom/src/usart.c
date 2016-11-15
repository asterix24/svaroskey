#include "usart.h"

void USART_Init(struct USART_Periph *USART)
{
	USART->CR1 |= (1 << 13) | (1 << 3);
	USART->BRR = 72000000L / 115200L;
}

void USART_Send(struct USART_Periph *USART, uint8_t ch)
{
	while (!(USART->SR & 0x80)) ;
	USART->DR = ch & 0xFF;
}

