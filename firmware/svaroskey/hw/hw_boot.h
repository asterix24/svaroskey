/**
 * \file
 * <!--
 * This file is part of BeRTOS.
 *
 * Bertos is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As a special exception, you may use this file as part of a free software
 * library without restriction.  Specifically, if other files instantiate
 * templates or use macros or inline functions from this file, or you compile
 * this file and link it with other files to produce an executable, this
 * file does not by itself cause the resulting executable to be covered by
 * the GNU General Public License.  This exception does not however
 * invalidate any other reasons why the executable file might be covered by
 * the GNU General Public License.
 *
 * Copyright 2009 Develer S.r.l. (http://www.develer.com/)
 * All Rights Reserved.
 * -->
 *
 * \brief Bootloader hardware specific definition.
 *
 * \author Daniele Basile <asteix@develer.com>
 */

#ifndef HW_BOOT_H
#define HW_BOOT_H

#include <io/cm3.h>

typedef struct BootMBR
{
	uint32_t key;
	uint32_t mode;
	uint32_t len;
	uint32_t crc;
} BootMBR;

#define BOOTKEY              0xDEADBEEF
#define BOOT_SAFEMODE        0
#define BOOT_APPMODE         1
#define BOOT_MBR_TABLE_OFF   sizeof(BootMBR)


#define FLASH_BOOT_SIZE  (64 * 1024)
#define BOOT_PAGE_SIZE   (FLASH_PAGE_SIZE)
#define TRIM_START       (FLASH_BOOT_SIZE / FLASH_PAGE_SIZE)

void (*rom_start)(void) NORETURN;
#define START_APP() rom_start()

// load traget address from reset vector (4 bytes offset, BootMBR)
#define JUMP_APP_ADDR  (FLASH_BOOT_SIZE + 4 + sizeof(BootMBR) + 1)

#endif /*  HW_BOOT_H */
