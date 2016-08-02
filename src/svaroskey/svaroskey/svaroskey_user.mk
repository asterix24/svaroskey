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
	$(svaroskey_SRC_PATH)/keymap.c \
	$(svaroskey_SRC_PATH)/layouts.c \
	$(svaroskey_SRC_PATH)/mappings.c \
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
