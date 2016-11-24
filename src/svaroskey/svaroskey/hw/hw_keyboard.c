#include "hw_keyboard.h"
#include <cfg/cfg_keyboard.h>

#include <drv/timer.h>

#include <io/stm32.h>
#include <drv/gpio_stm32.h>
#include <drv/clock_stm32.h>

#ifdef CONFIG_INVERT_LAYOUT
	#define KEY_COL_GPIO_BASE ((struct stm32_gpio *)GPIOB_BASE)
	#define KEY_COL_PINS      (0x73FB)

	#define KEY_ROW_GPIO_BASE ((struct stm32_gpio *)GPIOC_BASE)
	#define KEY_ROW_PINS      (0x17FF)
#else
	#define KEY_ROW_GPIO_BASE ((struct stm32_gpio *)GPIOB_BASE)
	#define KEY_ROW_PINS      (0x73FB)

	#define KEY_COL_GPIO_BASE ((struct stm32_gpio *)GPIOC_BASE)
	#define KEY_COL_PINS      (0x17FF)
#endif

static struct stm32_gpio * const port_mappings[] = {
	((struct stm32_gpio *)GPIOA_BASE),
	((struct stm32_gpio *)GPIOB_BASE),
	((struct stm32_gpio *)GPIOC_BASE),
};

void KEYBOARD_INIT(void) {
	/* Enable clocking on GPIOA, GPIOB */
	RCC->APB2ENR |= RCC_APB2_GPIOB | RCC_APB2_GPIOC;

#ifdef CONFIG_INVERT_LAYOUT
	/* Configure the key pins as GPIO */
	stm32_gpioPinConfig(KEY_COL_GPIO_BASE, KEY_COL_PINS, GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ);
	stm32_gpioPinConfig(KEY_ROW_GPIO_BASE, KEY_ROW_PINS, GPIO_MODE_IPD, GPIO_SPEED_50MHZ);
#else
	/* Configure the key pins as GPIO */
	stm32_gpioPinConfig(KEY_ROW_GPIO_BASE, KEY_ROW_PINS, GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ);
	stm32_gpioPinConfig(KEY_COL_GPIO_BASE, KEY_COL_PINS, GPIO_MODE_IPD, GPIO_SPEED_50MHZ);
#endif

	/* Deselect all rows */
	stm32_gpioPinWrite(KEY_ROW_GPIO_BASE, KEY_ROW_PINS, false);
}

bool KEYBOARD_READ_CELL(struct Cell *cell) {
	struct stm32_gpio *wPort, *rPort;
	int wPin, rPin;
	bool ret;

#ifdef CONFIG_INVERT_LAYOUT
	wPort = port_mappings[cell->col.port];
	rPort = port_mappings[cell->row.port];
	wPin = BV(cell->col.pin);
	rPin = BV(cell->row.pin);
#else
	wPort = port_mappings[cell->row.port];
	rPort = port_mappings[cell->col.port];
	wPin = BV(cell->row.pin);
	rPin = BV(cell->col.pin);
#endif

	/* Select row */
	stm32_gpioPinWrite(wPort, wPin, true);

	timer_udelay(2);

	/* Read column */
	ret = stm32_gpioPinRead(rPort, rPin);

	/* Deselect row */
	stm32_gpioPinWrite(wPort, wPin, false);

	return ret;
}
