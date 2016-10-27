#include "hw_keymap.h"

#include <drv/timer.h>

#include <io/stm32.h>
#include <drv/gpio_stm32.h>
#include <drv/clock_stm32.h>

#define KEY_ROW_GPIO_BASE ((struct stm32_gpio *)GPIOB_BASE)
#define KEY_ROW_PINS      (0x73FB)

#define KEY_COL_GPIO_BASE ((struct stm32_gpio *)GPIOC_BASE)
#define KEY_COL_PINS      (0x17FF)

static struct stm32_gpio * const port_mappings[] = {
	((struct stm32_gpio *)GPIOA_BASE),
	((struct stm32_gpio *)GPIOB_BASE),
	((struct stm32_gpio *)GPIOC_BASE),
};

void KEYMAP_INIT(void) {
	/* Enable clocking on GPIOA, GPIOB */
	RCC->APB2ENR |= RCC_APB2_GPIOB | RCC_APB2_GPIOC;

	/* Configure the key pins as GPIO */
	stm32_gpioPinConfig(KEY_ROW_GPIO_BASE, KEY_ROW_PINS, GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ);
	stm32_gpioPinConfig(KEY_COL_GPIO_BASE, KEY_COL_PINS, GPIO_MODE_IPD, GPIO_SPEED_50MHZ);

	/* Deselect all rows */
	stm32_gpioPinWrite(KEY_ROW_GPIO_BASE, KEY_ROW_PINS, false);
}

bool KEYMAP_READ(KeyMapping * k) {
	bool ret;

	/* Select row */
	stm32_gpioPinWrite(port_mappings[k->row_port], BV(k->row_pin), true);
	timer_udelay(2);

	/* Read column */
	ret = stm32_gpioPinRead(port_mappings[k->col_port], BV(k->col_pin));

	/* Deselect row */
	stm32_gpioPinWrite(port_mappings[k->row_port], BV(k->row_pin), false);

	return ret;
}
