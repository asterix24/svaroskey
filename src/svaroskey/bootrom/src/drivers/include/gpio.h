#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

/* GPIO peripheral definition */
struct GPIO_Periph {
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
};

/* AFIO peripheral definition */
struct AFIO_Periph {
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t MAPR2;
};

/* GPIO instances */
#define GPIOG   ((struct GPIO_Periph *) (0x40012000))
#define GPIOF   ((struct GPIO_Periph *) (0x40011C00))
#define GPIOE   ((struct GPIO_Periph *) (0x40011800))
#define GPIOD   ((struct GPIO_Periph *) (0x40011400))
#define GPIOC   ((struct GPIO_Periph *) (0x40011000))
#define GPIOB   ((struct GPIO_Periph *) (0x40010C00))
#define GPIOA   ((struct GPIO_Periph *) (0x40010800))

/* AFIO instances */
#define AFIO    ((struct AFIO_Periph *) (0x40010000))

/* GPIO public methods */
void GPIO_SetPinMode(struct GPIO_Periph *GPIO, uint32_t pin, uint8_t mode);

#endif
