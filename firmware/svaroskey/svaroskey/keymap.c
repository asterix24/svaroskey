#include "keymap.h"

#include "hw/hw_keymap.h"

#include "definitions.h"
#include "keycodes.h"
#include "layouts.h"
#include "mappings.h"

#include <cfg/debug.h>
#define LOG_LEVEL  3
#define LOG_FORMAT 0

#include <cfg/log.h>

typedef struct
{
	int chosen_layer;
} KeypressesInfo;
static KeypressesInfo kp_info;

static UsbKbdEvent usb_report = {
	.mods = 0,
	.codes = { 0 }
};

static bool report_ready = false;

UsbKbdEvent* get_usb_report()
{
	if (report_ready) {
		report_ready = false;
		return &usb_report;
	}
	return NULL;
}

static void clean_keypresses_info(void)
{
	kp_info.chosen_layer = 0;
}

static void generate_keypresses_info(int num_pressed)
{
	clean_keypresses_info();

	int i = 0;
	for (i = 0; i < num_pressed; i++)
	{
		// layer keys are only supported on the base layer.
		// TODO decide whether we want this limitation
		key_id_t k_id = pressed_key_ids[i];
		const LogicalKey* lk = get_logical_key(0, k_id);

		if (!is_custom(lk))
		{
			continue;
		}

		// TODO if we want a different layer when pressing two
		// layer keys down, we must rework the way we calculate
		// the layer
		if (lk->scancode == KEY_LAYER_1) {
			kp_info.chosen_layer = 1;
			break;
		}
	}
}

static void clean_report(void)
{
	usb_report.mods = 0;
	for (int i = 0; i < 6; i++)
	{
		usb_report.codes[i] = 0;
	}
}

static void generate_usb_report(int num_pressed)
{
	generate_keypresses_info(num_pressed);

	int i = 0;
	int num_key_codes = 0;
	for (i = 0; i < num_pressed; i++)
	{
		key_id_t k_id = pressed_key_ids[i];
		const LogicalKey* lk = get_logical_key(
			kp_info.chosen_layer,
			k_id
		);

		if (is_modifier(lk))
		{
			usb_report.mods |= lk->modifiers;
			continue;
		}

		if (is_custom(lk))
		{
			// custom keys are only used to select the layout layer
			continue;
		}

		if (num_key_codes < 5)
		{
			usb_report.mods |= lk->modifiers;
			usb_report.codes[num_key_codes] = lk->scancode;
			num_key_codes++;
		}
	}

	report_ready = true;
}

void keymap_scan(void)
{
	report_ready = false;
	clean_report();

	int num_pressed_keys = 0;
	key_id_t k_id = 0;
	for (k_id = 0; k_id < LAYOUT_SIZE; k_id++) {
		const PhysicalKey* pk = get_physical_key(k_id);

		if (!is_key_down(pk))
			continue;

		pressed_key_ids[num_pressed_keys] = k_id;
		num_pressed_keys++;
	}

	generate_usb_report(num_pressed_keys);
}

void keymap_init(void)
{
	// Low-level hardware initialization
	keyboard_init();

	// TODO: initialize layout from EEPROM
}
