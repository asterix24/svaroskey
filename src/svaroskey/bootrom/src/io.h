#ifndef IO_H
#define IO_H

#include <stdint.h>

int FLASH_WriteBlock(uint32_t dst, const void *src, int count);

#endif
