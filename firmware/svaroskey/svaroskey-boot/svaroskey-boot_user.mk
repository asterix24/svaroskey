#
# User makefile.
# Edit this file to change compiler options and related stuff.
#

# Programmer interface configuration, see http://dev.bertos.org/wiki/ProgrammerInterface for help
svaroskey-boot_PROGRAMMER_TYPE = none
svaroskey-boot_PROGRAMMER_PORT = none

# Files included by the user.
svaroskey-boot_USER_CSRC = \
	$(svaroskey-boot_SRC_PATH)/main.c \
	common/usbfeature.c \
	common/crc32.c \
	#

# Files included by the user.
svaroskey-boot_USER_PCSRC = \
	#

# Files included by the user.
svaroskey-boot_USER_CPPASRC = \
	#

# Files included by the user.
svaroskey-boot_USER_CXXSRC = \
	#

# Files included by the user.
svaroskey-boot_USER_ASRC = \
	#

# Flags included by the user.
svaroskey-boot_USER_LDFLAGS = \
	#

# Flags included by the user.
svaroskey-boot_USER_CPPAFLAGS = \
	#

# Flags included by the user.
svaroskey-boot_USER_CPPFLAGS = \
	-fno-strict-aliasing \
	-fwrapv \
	#
