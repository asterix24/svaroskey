#ifdef WIN32
	#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <hidapi.h>
#include <string.h>

#define MAX_STR 255
#define USB_BOOT_MSGLEN     (64 - (sizeof(uint32_t) + \
			2*sizeof(uint16_t)))

typedef struct __attribute__((packed)) UsbBootMsg
{
	uint16_t cmd;
	uint16_t crc;
	uint32_t len;
	uint8_t data[USB_BOOT_MSGLEN];
} UsbBootMsg;

int main(int argc, char* argv[])
{
	hid_device *handle;

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
				return 1;
			}
			break;
		}
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);

	printf("Send reports..\n");

	UsbBootMsg msg;
	UsbBootMsg check_msg;

	printf("sizeof %ld macro %ld\n", sizeof(UsbBootMsg), USB_BOOT_MSGLEN);
	memset(&msg, 0, sizeof(msg));
	memset(&check_msg, 0, sizeof(check_msg));

	msg.cmd = 0x1;
	msg.crc = 0x1317;
	msg.len = 64;

	for (int i = 0; i < 10; i++)
	{
		msg.data[0] = i;
		int ret = hid_send_feature_report(handle, (const unsigned char *)&msg, sizeof(msg));
		if (ret < 0)
			printf("Error: [%ls]\n", hid_error(handle));
		else
			printf("ok...round[%d]\n", i);

		ret = hid_get_feature_report(handle, (unsigned char *)&check_msg, sizeof(UsbBootMsg));
		if (ret < 0)
			printf("Error: [%ls]\n", hid_error(handle));
		else
		{
			printf("Read len[%d]:\n", ret);
			printf("cmd     [%d]:\n", check_msg.cmd);
			printf("crc     [%d]:\n", check_msg.crc);
			printf("len     [%d]:\n", check_msg.len);

			//printf("data [%s]\n", check_msg.data);
			printf("data    [\n");
			for(size_t i = 0; i < USB_BOOT_MSGLEN; i++)
				printf("%0x ", check_msg.data[i]);
			printf("       ]\n");

			if (!memcmp(&msg, &check_msg, sizeof(UsbBootMsg)))
				printf("Sync Ok!\n");

		}
	}
	return 0;
}

