
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
#include <string.h>
#include <time.h>
#include <hidapi.h>

#define FEAT_STATUS          0x0
#define FEAT_NONE            0x1
#define FEAT_ECHO            0x2
#define FEAT_WRITE           0x3
#define FEAT_CHK_WRITE       0x4
#define FEAT_MODE            0x5
#define FEAT_RESET           0x17

#define FEAT_ST_APP         0
#define FEAT_ST_SAFE        1

#define FEAT_REPLY_OK        0
#define FEAT_REPLY_ERR       1
#define FEAT_REPLY_CRC_ERR   2
#define FEAT_REPLY_MBR_ERR   3

#define NO_REPLY            0
#define WAIT_REPLY          1

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

static int sendRecv_msg(char *name, hid_device *handle, UsbFeatureMsg *msg, \
		uint8_t cmd, uint8_t *data, uint32_t len, uint8_t reply)
{
	msg->cmd = cmd;
	msg->len = len;

	if (data)
		memcpy(msg->data, data, len);

	uint8_t tmp[PAYLOAD_LEN + 1];
	memset(tmp, 0x0, PAYLOAD_LEN + 1);
	memcpy(&tmp[1], msg, PAYLOAD_LEN);

	int ret = hid_send_feature_report(handle, tmp, sizeof(tmp));
	printf("%s SEND [%d] %ld\n", name, PAYLOAD_LEN, sizeof(tmp));
	if (ret < 0)
	{
		printf("%s Error SEND: [%ls]\n", name, hid_error(handle));
		return -1;
	}

	if (!reply)
		return 0;

	memset(msg, 0x0, sizeof(UsbFeatureMsg));
	memset(tmp, 0x0, PAYLOAD_LEN + 1);
	ret = hid_get_feature_report(handle, tmp, PAYLOAD_LEN);
	if (ret < 0)
	{
		printf("%s Error GET: [%ls]\n", name, hid_error(handle));
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
		int ret = sendRecv_msg("status", handle, msg, FEAT_STATUS, buff, MSG_PAYLOAD_LEN, WAIT_REPLY);
		if (ret < 0)
			continue;

		if (msg->len > 0)
			return msg->data[0];
	}

	return -1;
}

static int hid_reset(hid_device *handle, UsbFeatureMsg *msg)
{
	return sendRecv_msg("reset", handle, msg, FEAT_RESET, NULL, 0, NO_REPLY);
}

struct WrCheck
{
	uint32_t crc;
	uint32_t fw_index;
	uint32_t fw_lenght;
};

static int hid_check(hid_device *handle, UsbFeatureMsg *msg, struct WrCheck *wr_check)
{
	for (int i = 0; i < 3; i++)
	{
		int ret = sendRecv_msg("check", handle, msg, FEAT_CHK_WRITE, \
				(unsigned char *)wr_check, sizeof(struct WrCheck), WAIT_REPLY);
		if (ret < 0)
			continue;

		printf("%s\n", &msg->data[1]);
		return msg->data[0];
	}

	return -1;
}

static int hid_writeBuff(hid_device *handle, UsbFeatureMsg *msg, uint8_t *buff, size_t len)
{
	for (int i = 0; i < 3; i++)
	{
		int ret = sendRecv_msg("write", handle, msg, FEAT_WRITE, \
				(unsigned char *)buff, len, WAIT_REPLY);
		if (ret < 0)
			continue;

		printf("%s\n", &msg->data[1]);
		return msg->data[0];
	}

	return -1;
}


static int hid_none(hid_device *handle, UsbFeatureMsg *msg, time_t timeout)
{
	time_t start = time(NULL);
	do
	{
		int ret = sendRecv_msg("none", handle, msg, FEAT_NONE, \
				NULL, 0, WAIT_REPLY);
		if (ret < 0)
			continue;
		else
			return 0;

	} while ((time(NULL) - start) < timeout);

	return -1;
}

//static void hid_info(hid_device *hid)
//{
//	printf("Hid Device:\n");
//	printf("\tType: %04hx %04hx\n", hid->vendor_id, hid->product_id);
//	printf("\tPath: %s\n", hid->path);
//	rintf("\tSerial_number: %ls\n", hid->serial_number);
//	printf("\tManufacturer: %ls\n", hid->manufacturer_string);
//	printf("\tProduct:      %ls\n", hid->product_string);
//	printf("\tRelease:      %hx\n", hid->release_number);
//	printf("\tInterface:    %d\n",  hid->interface_number);
//	printf("\n");
//}

static hid_device *register_hid(hid_device *hid)
{
	struct hid_device_info *devs, *cur_dev;
	devs = hid_enumerate(0x0, 0x0);
	cur_dev = devs;
	while (cur_dev)
	{
		if (cur_dev->vendor_id == 0x046d)
		{
			// Open the device using the VID, PID,
			// and optionally the Serial number.
			hid = hid_open_path(cur_dev->path);
			if (!hid)
			{
				printf("Invalid VID or PID\n");
				return NULL;
			}
			break;
		}
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);

	if (!devs || !hid)
	{
		printf("No Hid devices\n");
		return NULL;
	}

	return hid;
}

static UsbFeatureMsg msg;
static uint32_t crc_fw = 0;
static uint8_t buff[MSG_PAYLOAD_LEN];

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("You should specify firmware file.\n");
		return -1;
	}

	if (!argv[1])
	{
		printf("File error.\n");
		return -1;
	}

	hid_device *handle = NULL;
	// Initialize the hidapi library
	if (hid_init())
	{
		printf("Unable to init usb.\n");
		return -1;
	}

	if (!(handle = register_hid(handle)))
		return -1;

	//hid_info(handle);

	printf("Payload size[%lu]\n", sizeof(UsbFeatureMsg));

	printf("Send some NONE cmd to wait board boot..\n");
	if (hid_none(handle, &msg, 5) < 0)
	{
		printf("Unable to talk with board\n");
		return -1;
	}
	printf("Board ready!\n");

	int status = hid_status(handle, &msg);
	if (status < 0)
	{
		printf("Unable to get status\n");
		return -1;
	}

	if (status == FEAT_ST_APP)
	{
		printf("Devise is in app mode..\n");
		printf("Put it in SAFE mode.\n");
		printf("Reset board..\n");
		hid_reset(handle, &msg);

		time_t start = time(NULL);
		do
		{
			if ((time(NULL) - start) > 15)
			{
				printf("Comunnication Timeout\n");
				return -1;
			}

			handle = register_hid(handle);
			if (!handle)
				continue;

			printf("Send some NONE cmd to wait board boot..\n");
			if (hid_none(handle, &msg, 0) == 0)
				break;

		} while (1);
		printf("Board ready!\n");

		status = hid_status(handle, &msg);
		if (status < 0)
		{
			printf("Unable to get status\n");
			return -1;
		}
	}

	printf("Status[%d]\n", status);
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
			int ret = hid_writeBuff(handle, &msg, buff, len);
			if (ret == FEAT_REPLY_OK)
			{
				index++;
				total += len;
				printf("Wrote index[%zu] len[%zu]\n", index, total);
			}
			else
			{
				printf("Write error..\n");
				goto error;
			}

			crc_fw = crc32(buff, len, crc_fw);
			printf("Sent[%zu] bytes[%zu]\n", index, total);

		}

		printf("Sent[%zu] bytes[%zu] crc[%u]\n", index, total, crc_fw);
		struct WrCheck wr_check;
		wr_check.crc = crc_fw;
		wr_check.fw_index = index;
		wr_check.fw_lenght = total;
		ret = hid_check(handle, &msg, &wr_check);
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

			printf("Reset board..\n");
			hid_reset(handle, &msg);
		}
	error:
		fclose(fw);
	}
	return 0;
}


