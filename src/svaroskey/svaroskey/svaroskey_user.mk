#
# User makefile.
# Edit this file to change compiler options and related stuff.
#

# Programmer interface configuration, see http://dev.bertos.org/wiki/ProgrammerInterface for help
svaroskey_PROGRAMMER_TYPE = none
svaroskey_PROGRAMMER_PORT = none

# Files included by the user.
svaroskey_USER_CSRC = \
	$(svaroskey_SRC_PATH)/main.c \
	$(svaroskey_SRC_PATH)/keyboard.c \
	$(svaroskey_SRC_PATH)/layout.c \
	$(svaroskey_SRC_PATH)/grid.c \
	$(svaroskey_SRC_PATH)/hw/hw_keyboard.c \
	$(svaroskey_SRC_PATH)/cfg/cfg_keyboard_petroskey.c \
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
