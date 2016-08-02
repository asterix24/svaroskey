#include "hw_keymap.h"

static struct stm32_gpio * const port_mappings[] = {
	((struct stm32_gpio *)GPIOA_BASE),
	((struct stm32_gpio *)GPIOB_BASE),
	((struct stm32_gpio *)GPIOC_BASE),
};

bool KEYMAP_READ(KeyMapping * k) {
	bool ret;

	/* Select row */
	stm32_gpioPinConfig(port_mappings[k->row_port], BV(k->row_pin),
			GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ);
	stm32_gpioPinWrite(port_mappings[k->row_port], BV(k->row_pin), true);
	/* Read column */
	ret = stm32_gpioPinRead(port_mappings[k->col_port], BV(k->col_pin));
	/* Deselect row */
	stm32_gpioPinConfig(port_mappings[k->row_port], BV(k->row_pin),
			GPIO_MODE_IPD, GPIO_SPEED_50MHZ);
	return ret;
}
