#ifndef SVAROSKEY_KEYSCAN_H
#define SVAROSKEY_KEYSCAN_H

/** @file */

/**
 * @addtogroup free_functions Free Functions
 * @{
 * 
 * @name Key Scanning Functions
 * @{
 */

/**
 * @brief Whether the last scan was different from the previous.
 */
int keyscan_changed(void);

/**
 * @brief Performs a scan on the physical keys.
 *
 * The result of the scan is saved in config memory, since it is dependent on
 * the maximum number of physical keys read, which is a config parameter.
 *
 * eeprom->pressed_keys[]
 * eeprom->pressed_keys_num
 */
void keyscan_scan(void);

/**
 * @brief Performs any initialization of the physical keys reading system.
 */
void keyscan_init(void);

/// @}
/// @}

#endif
