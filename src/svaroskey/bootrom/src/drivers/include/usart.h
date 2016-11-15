#ifndef USART_H
#define USART_H

#include <stdint.h>

/* USART peripheral definition */
struct USART_Periph {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
};

/* USART instances */
#define USART1	((struct USART_Periph *)(0x40013800))

/* USART public methods */
void USART_Init(struct USART_Periph *USART);
void USART_Send(struct USART_Periph *USART, uint8_t ch);

#endif