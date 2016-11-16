#include "usart.h"

/* USART SR register bits */
#define USART_SR_PE		(0x1 << 0)
#define USART_SR_FE		(0x1 << 1)
#define USART_SR_NE		(0x1 << 2)
#define USART_SR_ORE		(0x1 << 3)
#define USART_SR_IDLE		(0x1 << 4)
#define USART_SR_RXNE		(0x1 << 5)
#define USART_SR_TC		(0x1 << 6)
#define USART_SR_TXE		(0x1 << 7)
#define USART_SR_LBD		(0x1 << 8)
#define USART_SR_CTS		(0x1 << 9)

/* USART CR1 register bits */
#define USART_CR1_SBK		(0x1 << 0)
#define USART_CR1_RWU		(0x1 << 1)
#define USART_CR1_RE		(0x1 << 2)
#define USART_CR1_TE		(0x1 << 3)
#define USART_CR1_IDLEIE	(0x1 << 4)
#define USART_CR1_RXNEIE	(0x1 << 5)
#define USART_CR1_TCIE		(0x1 << 6)
#define USART_CR1_TXEIE		(0x1 << 7)
#define USART_CR1_PEIE		(0x1 << 8)
#define USART_CR1_PS		(0x1 << 9)
#define USART_CR1_PCE		(0x1 << 10)
#define USART_CR1_WAKE		(0x1 << 11)
#define USART_CR1_M		(0x1 << 12)
#define USART_CR1_UE		(0x1 << 13)

void USART_Init(struct USART_Periph *USART, uint32_t baud)
{
	USART->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
	USART->BRR = 72000000L / baud;
}

void USART_Send(struct USART_Periph *USART, uint8_t ch)
{
	while (!(USART->SR & USART_SR_TXE)) ;
	USART->DR = ch & 0xFF;
}

uint8_t USART_Recv(struct USART_Periph *USART)
{
	while (!(USART->SR & USART_SR_RXNE)) ;
	return USART->DR;
}

