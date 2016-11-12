#include "gpio.h"

void GPIO_SetPinMode(struct GPIO_Periph *GPIO, uint32_t pin, uint8_t mode)
{
	GPIO->CRH |= 0x04B0;
}
