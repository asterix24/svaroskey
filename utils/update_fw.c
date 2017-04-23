
/**
 * \file
 * <!--
 * This file is part of Svaroskey.
 *
 * Svaroskey is free software; you can redistribute it and/or modify
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
 * Copyright 2017 Daniele Basile <asterix24@gmail.com>
 *
 * -->
 *
 * \author Daniele Basile <asterix24@gmail.com>
 *
 * \brief hid utils
 */

#include "crc32.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <hidapi.h>

#include <string.h>

#define FEAT_ERR             0xFF
#define FEAT_STATUS          0x0
#define FEAT_NONE            0x1
#define FEAT_ECHO            0x2
#define FEAT_WRITE           0x3
#define FEAT_CHK_WRITE       0x4
#define FEAT_RESET           0x17

#define FEAT_ST_APP         0
#define FEAT_ST_SAFE        1

#define PAYLOAD_LEN         64
#define MSG_PAYLOAD_LEN     (PAYLOAD_LEN - \
                            (sizeof(uint32_t) + \
                             sizeof(uint8_t)))

typedef struct __attribute__((packed)) UsbFeatureMsg
{
	uint8_t cmd;
	uint32_t len;
	uint8_t data[MSG_PAYLOAD_LEN];
} UsbFeatureMsg;

#define FEAT_ST_WRITE_OK 0
#define FEAT_ST_WRITE_ERR 1

struct WrStatus
{
	uint8_t status;
	uint32_t blk_index;
	uint32_t wrote_len;
};

static int sendRecv_msg(hid_device *handle, UsbFeatureMsg *msg, uint8_t cmd, uint8_t *data, uint32_t len)
{
	msg->cmd = cmd;
	msg->len = len;
	memcpy(msg->data, data, len);

	uint8_t tmp[PAYLOAD_LEN + 1];
	memset(tmp, 0x0, PAYLOAD_LEN + 1);
	memcpy(&tmp[1], msg, PAYLOAD_LEN);

	int ret = hid_send_feature_report(handle, tmp, sizeof(tmp));
	printf("send [%d] %ld\n", PAYLOAD_LEN, sizeof(tmp));
	if (ret < 0)
	{
		printf("Send Error: [%ls]\n", hid_error(handle));
		return -1;
	}

	memset(msg, 0x0, sizeof(UsbFeatureMsg));
	memset(tmp, 0x0, PAYLOAD_LEN + 1);
	ret = hid_get_feature_report(handle, tmp, PAYLOAD_LEN);
	if (ret < 0)
	{
		printf("Get Error: [%ls]\n", hid_error(handle));
		return -1;
	}

	memcpy(msg, tmp, PAYLOAD_LEN);

	return 0;
}

static int hid_status(hid_device *handle, UsbFeatureMsg *msg)
{
	uint8_t buff[MSG_PAYLOAD_LEN];
	for (int i = 0; i < 3; i++)
	{
		int ret = sendRecv_msg(handle, msg, FEAT_STATUS, buff, MSG_PAYLOAD_LEN);
		if (ret < 0)
			continue;

		if (msg->len > 0)
			return msg->data[0];
	}

	return -1;
}

static int hid_check(hid_device *handle, UsbFeatureMsg *msg, uint32_t crc32)
{
	for (int i = 0; i < 3; i++)
	{
		int ret = sendRecv_msg(handle, msg, FEAT_CHK_WRITE, (unsigned char *)&crc32, sizeof(crc32));
		if (ret < 0)
			continue;

		return msg->data[0];
	}

	return -1;
}

static UsbFeatureMsg msg;
static uint32_t crc_fw = 0;
static uint8_t buff[MSG_PAYLOAD_LEN];

int main(int argc, char* argv[])
{
	printf("%lu\n", sizeof(UsbFeatureMsg));
	if (argc < 2)
	{
		printf("You should specify firmware file.");
		return -1;
	}

	if (!argv[1])
	{
		printf("File error.");
		return -1;
	}

	hid_device *handle = NULL;
	// Initialize the hidapi library
	if (hid_init())
	{
		printf("Unable to init usb.");
		return -1;
	}

	struct hid_device_info *devs, *cur_dev;
	devs = hid_enumerate(0x0, 0x0);
	cur_dev = devs;
	while (cur_dev) {
		if (cur_dev->vendor_id == 0x046d)
		{
			printf("Device Found\n");
			printf("type: %04hx %04hx\n", cur_dev->vendor_id, cur_dev->product_id);
			printf("path: %s\n", cur_dev->path);
			printf("serial_number: %ls\n", cur_dev->serial_number);
			printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
			printf("  Product:      %ls\n", cur_dev->product_string);
			printf("  Release:      %hx\n", cur_dev->release_number);
			printf("  Interface:    %d\n",  cur_dev->interface_number);
			printf("\n");

			// Open the device using the VID, PID,
			// and optionally the Serial number.
			handle = hid_open_path(cur_dev->path);
			if (!handle)
			{
				printf("Invalid VID or PID");
				return -1;
			}
			break;
		}
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);

	printf("Get status..%lu %lu\n", MSG_PAYLOAD_LEN, sizeof(UsbFeatureMsg));
	memset(buff, 0xCC, MSG_PAYLOAD_LEN);
	int status = hid_status(handle, &msg);
	if (status < 0)
	{
		printf("Unable to get status\n");
		return -1;
	}

	if (status == FEAT_ST_SAFE)
	{
		printf("Status is SAFE MODE [%d]\n", status);
		printf("Start to uploard fw..\n");

		FILE *fw = fopen(argv[1], "r");
		printf("%s\n", argv[1]);
		printf("%d\n", ferror(fw));

		int ret = 0;
		size_t total = 0;
		size_t index = 0;
		while (1)
		{
			if (feof(fw))
				break;

			size_t len = fread(buff, 1, MSG_PAYLOAD_LEN, fw);
			unsigned send_ok = 0;
			int retry = 0;
			do {
				if (retry > 2)
				{
					printf("Unable to send msg max retry[%d]..exit\n", retry);
					goto error;
				}
				retry++;

				ret = sendRecv_msg(handle, &msg, FEAT_WRITE, buff, len);
				if (ret < 0)
				{
					printf("Error while send data block ret[%d]\n", ret);
					continue;
				}
				else
				{
					if (msg.len > 0)
					{
						struct WrStatus wr;
						memcpy(&wr, msg.data, msg.len);
						if (wr.status == FEAT_ST_WRITE_OK)
						{
							printf("Wrote index[%d] len[%d]\n", wr.blk_index, wr.wrote_len);
							send_ok = 1;
						}
						else
							printf("Write error..[%d]\n", wr.status);
					}
				}
			} while (!send_ok);

			index++;
			total += len;

			crc_fw = crc32(buff, len, crc_fw);
			printf("Sent[%zu] bytes[%zu]\n", index, total);

		}

		printf("Sent[%zu] bytes[%zu] crc[%u]\n", index, total, crc_fw);
		ret = hid_check(handle, &msg, crc_fw);
		if (ret > 0)
			printf("Write check fail!..\n");
		else
		{
			printf("\n");
			printf("Firmware wrote update correctly!\n");
			printf("File name: %s\n", argv[1]);
			printf("Wrote size: %zu\n", total);
			printf("Blk num: %zu\n", index);
			printf("crc32: %u\n", crc_fw);
		}
	error:
		fclose(fw);
	}
	return 0;
}


