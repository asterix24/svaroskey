#ifndef KBD_DEFINITIONS_H
#define KBD_DEFINITIONS_H

#define CONFIG_MAPPING_LATEST_REVISION 1

#ifdef SVAROSKEY
	#define CONFIG_LAYOUT_REVISION   1
	#define CONFIG_MAPPING_REVISION  1
	#define CONFIG_INVERT_LAYOUT
	#define LAYOUT_SIZE 106
#else
	#define CONFIG_LAYOUT_REVISION   0
	#define CONFIG_MAPPING_REVISION  0
	#define LAYOUT_SIZE 65
#endif

#define KEYBOARD_PORT_A 0
#define KEYBOARD_PORT_B 1
#define KEYBOARD_PORT_C 2
#define KEYBOARD_PORT_D 3

#endif // KBD_DEFINITIONS_H