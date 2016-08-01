#ifndef HW_KEYMAP_H
#define HW_KEYMAP_H

#include <io/stm32.h>

#include <drv/gpio_stm32.h>

#define KEY_ROW_PINS      (0xE7F3)
#define KEY_COL_PINS      (0x73F3)
#define KEY_ROW_GPIO_BASE ((struct stm32_gpio *)GPIOA_BASE)
#define KEY_COL_GPIO_BASE ((struct stm32_gpio *)GPIOB_BASE)

INLINE uint16_t KEYMAP_READ(uint16_t row, uint16_t col) {
	/* Select row */
	stm32_gpioPinConfig(KEY_ROW_GPIO_BASE, BV(row),
			GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ);
	stm32_gpioPinWrite(KEY_ROW_GPIO_BASE, BV(row), true);
	/* Read column */
	return stm32_gpioPinRead(KEY_COL_GPIO_BASE, BV(col));
}

#define KEYMAP_INIT()                                               \
	do {                                                            \
		/* Enable clocking on GPIOA, GPIOB */                       \
		RCC->APB2ENR |= RCC_APB2_GPIOA | RCC_APB2_GPIOB;            \
		/* Configure the key pins as GPIO */                        \
		stm32_gpioPinConfig(KEY_ROW_GPIO_BASE, KEY_ROW_PINS,        \
				GPIO_MODE_IPD, GPIO_SPEED_50MHZ);                   \
		stm32_gpioPinConfig(KEY_COL_GPIO_BASE, KEY_COL_PINS,        \
				GPIO_MODE_IPD, GPIO_SPEED_50MHZ);                   \
	} while(0)

#endif /* HW_KEYMAP_H */
