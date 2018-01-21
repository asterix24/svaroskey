#include "keymap.h"

#include "hw/hw_keymap.h"

#include "definitions.h"
#include "globals.h"
#include "keycodes.h"
#include "logical_key.h"

#include <cfg/debug.h>
#define LOG_LEVEL  3
#define LOG_FORMAT 0

#include <cfg/log.h>

typedef struct
{
	size_t num_substituted_keys;
	size_t remaining_custom_keys;
} KeySubstitutionResult;

typedef struct
{
	bool valid;
	size_t layer;
} LayerFetchResult;

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

static void clean_report(void)
{
	usb_report.mods = 0;
	for (int i = 0; i < 6; i++)
	{
		usb_report.codes[i] = 0;
	}
}

void generate_usb_report(size_t layer, size_t num_std_pressed)
{
	size_t i = 0;
	size_t num_key_codes = 0;

	for (i = 0; i < num_std_pressed; i++)
	{
		key_id_t k_id = std_pressed_key_ids[i];

		// modifiers are persisted across layers for usability
		const LogicalKey* mod_lk = get_logical_key(0, k_id);
		if (is_modifier(mod_lk))
		{
			usb_report.mods |= mod_lk->modifiers;
			continue;
		}

		const LogicalKey* lk = get_logical_key(layer, k_id);
		// one *can* define keys on non-base layers as additional
		// modifiers, though the usefulness of that is debatable
		if (is_modifier(lk))
		{
			usb_report.mods |= lk->modifiers;
			continue;
		}

		if (lk->scancode == KEY_NOOP)
		{
			// do not fill the usb report up with useless key codes
			continue;
		}

		if (num_key_codes < 6)
		{
			usb_report.mods |= lk->modifiers;
			usb_report.codes[num_key_codes] = lk->scancode;
			num_key_codes++;
		}
	}

	report_ready = true;
}

static LayerFetchResult layer_value(scancode_t sc) {
	switch(sc) {
	case KEY_LAYER_1: return (LayerFetchResult){true, 1};
	case KEY_LAYER_2: return (LayerFetchResult){true, 2};
	case KEY_LAYER_3: return (LayerFetchResult){true, 3};
	}

	return (LayerFetchResult){false, 0};
}

static size_t calculate_layer(size_t num_substituted_keys, size_t num_custom_keys) {
	/* We check if a layer key is among the substituted ones first.
	 * For example if we defined LAYER1 + LAYER2 to be LAYER3, LAYER1 and
	 * LAYER2 will be removed from `custom_pressed_key_ids` but the logical
	 * LAYER3 key will be placed in `substituted_keys`.
	 *
	 * If no substituted key defines a layer, we see if a layer key is
	 * pressed with no substitution semantics, for example when simply
	 * pressing LAYER1 + <something>, the logical key for <something>
	 * must be fetched from the first layer.
	 *
	 * If no layer key is being pressed, we return 0, which signals the
	 * base layer.
	 */

	size_t i = 0;
	for (i = 0; i < num_substituted_keys; i++) {
		const LogicalKey* lk = substituted_keys[i];
		LayerFetchResult result = layer_value(lk->scancode);
		if (result.valid) return result.layer;
	}

	for (i = 0; i < num_custom_keys; i++) {
		const LogicalKey* lk = get_logical_key(
			0, custom_pressed_key_ids[i]
		);
		LayerFetchResult result = layer_value(lk->scancode);
		if (result.valid) return result.layer;
	}

	return 0; // base layer
}

static KeySubstitutionResult substitute_custom_keys(size_t num_custom_keys) {
	// TODO implement the substitution logic properly
	// as a test, we manually substitute LAYER1 + LAYER2 with LAYER3
	if (num_custom_keys != 2) {
		return (KeySubstitutionResult){0, num_custom_keys};
	}

	const LogicalKey* lk1 = get_logical_key(0, custom_pressed_key_ids[0]);
	const LogicalKey* lk2 = get_logical_key(0, custom_pressed_key_ids[1]);

	if (
		(
			lk1->scancode == KEY_LAYER_1 &&
			lk2->scancode == KEY_LAYER_2
		)
		|| (
			lk1->scancode == KEY_LAYER_2 &&
			lk2->scancode == KEY_LAYER_1
		)
	) {
		substituted_keys[0]->scancode = KEY_LAYER_3;
		substituted_keys[0]->modifiers = 0;
		return (KeySubstitutionResult){1, 0};
	}

	return (KeySubstitutionResult){0, num_custom_keys};
}

size_t keyfetch_algo(size_t num_custom_keys) {
	KeySubstitutionResult result = substitute_custom_keys(num_custom_keys);
	return calculate_layer(
		result.num_substituted_keys,
		result.remaining_custom_keys
	);
}

KeymapScanResult keymap_scan(void)
{
	report_ready = false;
	clean_report();

	size_t std_pressed_keys = 0;
	size_t custom_pressed_keys = 0;
	key_id_t k_id = 0;

	for (k_id = 0; k_id < LAYOUT_SIZE; k_id++) {
		const PhysicalKey* pk = get_physical_key(k_id);

		if (!is_key_down(pk))
			continue;

		const LogicalKey* lk = get_logical_key(0, k_id);
		if (is_custom(lk)) {
			if (custom_pressed_keys >= MAX_CUSTOM_KEYPRESSES) {
				continue;
			}
			custom_pressed_key_ids[custom_pressed_keys] = k_id;
			custom_pressed_keys++;
			continue;
		}

		std_pressed_key_ids[std_pressed_keys] = k_id;
		std_pressed_keys++;
	}

	return (KeymapScanResult){std_pressed_keys, custom_pressed_keys};
}

void keymap_init(void)
{
	// Low-level hardware initialization
	keyboard_init();

	// TODO: initialize layout from EEPROM
}
