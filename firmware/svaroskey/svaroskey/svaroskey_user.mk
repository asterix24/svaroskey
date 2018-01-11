#
# User makefile.
# Edit this file to change compiler options and related stuff.
#

# Programmer interface configuration, see http://dev.bertos.org/wiki/ProgrammerInterface for help
svaroskey_PROGRAMMER_TYPE = st-link
svaroskey_PROGRAMMER_PORT = /dev/tty.usbserial-AI04D7T3

# Files included by the user.
svaroskey_USER_CSRC = \
	$(svaroskey_SRC_PATH)/main.c \
	$(svaroskey_SRC_PATH)/globals.c \
	$(svaroskey_SRC_PATH)/keymap.c \
	$(svaroskey_SRC_PATH)/logical_key.c \
	$(svaroskey_SRC_PATH)/physical_key.c \
	common/usbfeature.c \
	common/crc32.c \
	$(svaroskey_HW_PATH)/hw/hw_keymap.c \
	#

# Files included by the user.
svaroskey_USER_PCSRC = \
	#

# Files included by the user.
svaroskey_USER_CPPASRC = \
	#

# Files included by the user.
svaroskey_USER_CXXSRC = \
	#

# Files included by the user.
svaroskey_USER_ASRC = \
	#

# Flags included by the user.
svaroskey_USER_LDFLAGS = \
	#-Wl,-T svaroskey/stm32f103rb_rom.ld \
	#

# Flags included by the user.
svaroskey_USER_CPPAFLAGS = \
	#

# Flags included by the user.
svaroskey_USER_CPPFLAGS = \
	-fno-strict-aliasing \
	-fwrapv \
	-O2 \
	#
