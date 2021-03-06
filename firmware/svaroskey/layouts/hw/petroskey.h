/**
 * \file
 * <!--
 * Copyright 2018 Daniele Basile <asterix24@gmail.com>
 * All Rights Reserved.
 * -->
 *
 * \brief Some ADC utilis.
 *
 * \author Daniele Basile <asterix24@gmail.com>
 */


#ifndef HW_PETROSKEY_H
#define HW_PETROSKEY_H

/*
#define KEYMAP_COL_PINS_PORTA (\
	BV(COL1) | BV(COL1)| BV(COL2)  | BV(COL3) \
	BV(COL4) | BV(COL5)| BV(COL6)  | BV(COL7) \
	BV(COL8) | BV(COL9)| BV(COL10) | BV(COL11) | BV(COL12) \
	)

#define KEYMAP_ROW_PINS_PORTA(\
	BV(ROW1) | BV(ROW1)| BV(ROW2)  | BV(ROW3) \
	BV(ROW4) | BV(ROW5)| BV(ROW6)  | BV(ROW7) \
	BV(ROW8) | BV(ROW9)| BV(ROW10) | BV(ROW11) | BV(ROW12) \
	)

#define KEYMAP_COL_PINS_PORTB (\
	BV(COL1) | BV(COL1)| BV(COL2)  | BV(COL3) \
	BV(COL4) | BV(COL5)| BV(COL6)  | BV(COL7) \
	BV(COL8) | BV(COL9)| BV(COL10) | BV(COL11) | BV(COL12) \
	)

#define KEYMAP_ROW_PINS_PORTB (\
	BV(ROW1) | BV(ROW1)| BV(ROW2)  | BV(ROW3) \
	BV(ROW4) | BV(ROW5)| BV(ROW6)  | BV(ROW7) \
	BV(ROW8) | BV(ROW9)| BV(ROW10) | BV(ROW11) | BV(ROW12) \
	)

#define KEYMAP_COL_PINS_PORTC (\
	BV(COL1) | BV(COL1)| BV(COL2)  | BV(COL3) \
	BV(COL4) | BV(COL5)| BV(COL6)  | BV(COL7) \
	BV(COL8) | BV(COL9)| BV(COL10) | BV(COL11) | BV(COL12) \
	)

#define KEYMAP_ROW_PINS_PORTC (\
	BV(ROW1) | BV(ROW1)| BV(ROW2)  | BV(ROW3) \
	BV(ROW4) | BV(ROW5)| BV(ROW6)  | BV(ROW7) \
	BV(ROW8) | BV(ROW9)| BV(ROW10) | BV(ROW11) | BV(ROW12) \
	)

	RCC->APB2ENR |= RCC_APB2_GPIOA | RCC_APB2_GPIOB | RCC_APB2_GPIOC; \
	stm32_gpioPinConfig(port_mappings[PORTA], KEYMAP_COL_PINS_PORTA, \
			GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ); \
	stm32_gpioPinConfig(port_mappings[PORTB], KEYMAP_COL_PINS_PORTB, \
			GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ); \
	stm32_gpioPinConfig(port_mappings[PORTC], KEYMAP_COL_PINS_PORTC, \
			GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ); \
	stm32_gpioPinConfig(KEY_COL_GPIO_BASE, KEY_COL_PINS, GPIO_MODE_IPD, GPIO_SPEED_50MHZ); \
	stm32_gpioPinConfig(port_mappings[PORTA], KEYMAP_ROW_PINS_PORTA, \
			GPIO_MODE_OUT_IPD, GPIO_SPEED_50MHZ); \
	stm32_gpioPinConfig(port_mappings[PORTB], KEYMAP_ROW_PINS_PORTB, \
			GPIO_MODE_OUT_IPD, GPIO_SPEED_50MHZ); \
	stm32_gpioPinConfig(port_mappings[PORTC], KEYMAP_ROW_PINS_PORTC, \
			GPIO_MODE_OUT_IPD, GPIO_SPEED_50MHZ); \
	stm32_gpioPinWrite(port_mappings[PORTA], KEYMAP_ROW_PINS_PORTA, false); \
	stm32_gpioPinWrite(port_mappings[PORTB], KEYMAP_ROW_PINS_PORTB, false); \
	stm32_gpioPinWrite(port_mappings[PORTC], KEYMAP_ROW_PINS_PORTC, false); \
	stm32_gpioPinWrite(port_mappings[PORTA], KEYMAP_COL_PINS_PORTA, false); \
	stm32_gpioPinWrite(port_mappings[PORTB], KEYMAP_COL_PINS_PORTB, false); \
	stm32_gpioPinWrite(port_mappings[PORTC], KEYMAP_COL_PINS_PORTC, false); \
*/

/*
 * Define column and rows for matrix keys.
 * Column should be place to power supply, and row to ground.
 */

#define COL0   0  //PB0
#define COL1   1  //PB1
#define COL2   3  //PB3
#define COL3   4  //PB4
#define COL4   5  //PB5
#define COL5   6  //PB6
#define COL6   7  //PB7
#define COL7   8  //PB8
#define COL8   9  //PB9
#define COL9  12 //PB12
#define COL10  13 //PB13
#define COL11  14 //PB14

#define KEYMAP_COL_PINS_PORTB (\
	BV(COL0) | BV(COL1)| BV(COL2)  | BV(COL3) | \
	BV(COL4) | BV(COL5)| BV(COL6)  | BV(COL7) | \
	BV(COL8) | BV(COL9)| BV(COL10) | BV(COL11) \
	)

#define KEYMAP_COL_MASK KEYMAP_COL_PINS_PORTB

#define ROW0   0   //PC0
#define ROW1   1   //PC1
#define ROW2   2   //PC2
#define ROW3   3   //PC3
#define ROW4   4   //PC4
#define ROW5   5   //PC5

#define KEYMAP_ROW_PINS_PORTC (\
	BV(ROW0) | BV(ROW1)| BV(ROW2)  | BV(ROW3) | \
	BV(ROW4) | BV(ROW5) \
	)

#define KEYMAP_ROW_MASK KEYMAP_ROW_PINS_PORTC

#define KEYBOARD_DISABLE_COL() \
	do { \
		stm32_gpioPinWrite(port_mappings[KEY_PORTB], KEYMAP_COL_MASK, 0); \
	} while (0)

#define KEYBOARD_DISABLE_ROW() \
	do { \
		stm32_gpioPinConfig(port_mappings[KEY_PORTC], KEYMAP_ROW_MASK, GPIO_MODE_OUT_PP, \
				GPIO_SPEED_50MHZ); \
		stm32_gpioPinWrite(port_mappings[KEY_PORTC], KEYMAP_ROW_MASK, 0); \
	} while (0)

#define KEYBOARD_INIT_COLUMNS() \
	do { \
		RCC->APB2ENR |= RCC_APB2_GPIOB; \
		stm32_gpioPinConfig(port_mappings[KEY_PORTB], KEYMAP_COL_PINS_PORTB, \
				GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ); \
		stm32_gpioPinWrite(port_mappings[KEY_PORTB], KEYMAP_COL_PINS_PORTB, 0); \
	} while (0)

#define KEYBOARD_INIT_ROWS() \
	do { \
		RCC->APB2ENR |= RCC_APB2_GPIOC; \
		stm32_gpioPinConfig(port_mappings[KEY_PORTC], KEYMAP_ROW_PINS_PORTC, \
				GPIO_MODE_OUT_PP, GPIO_SPEED_50MHZ); \
		stm32_gpioPinWrite(port_mappings[KEY_PORTC], KEYMAP_ROW_PINS_PORTC, 0); \
	} while (0)


#define KEYBOARD_LAYOUT_NUM_KEYS  65


#endif /* HW_PETROSKEY_H */

