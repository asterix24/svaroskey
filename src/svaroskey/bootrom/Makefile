# To be modified according to the project's settings
TARGET = bootrom
PREFIX = arm-none-eabi-

# Verbosity
ifeq ($(V),1)
# Verbose build
Q :=
L := @echo >/dev/null
else
# Quiet build
Q := @
L := @echo
endif

# Toolchain executables
CC      = $(PREFIX)gcc
LD      = $(PREFIX)ld
OBJDUMP = $(PREFIX)objdump
OBJCOPY = $(PREFIX)objcopy

# Toolchain flags
CFLAGS = -std=gnu99 -mcpu=cortex-m3 -O0 -mthumb -mno-thumb-interwork
LDFLAGS = -mcpu=cortex-m3 -Wl,--gc-sections -mthumb -mno-thumb-interwork -nostartfiles -Wl,-dT scripts/stm32f103rb.ld -Wl,-Map=images/svaroskey.map,--cref

# Miscellaneous tools
MKDIR = mkdir -p
ECHO = echo

# Output directories
OBJ_DIR = obj
IMG_DIR = images

# Target objects
TGT_ELF = $(IMG_DIR)/$(TARGET).elf
TGT_BIN = $(IMG_DIR)/$(TARGET).bin

# Source files
ASM_SRC = startup/startup_cm3.S
CXX_SRC = \
	src/main.c \
	src/rcc.c \
	src/gpio.c \
	src/flash.c \
	src/usart.c \
	#

# Object files
CXX_OBJ = $(foreach file,$(CXX_SRC:%.c=%.o),$(OBJ_DIR)/$(TARGET)/$(file))
ASM_OBJ = $(foreach file,$(ASM_SRC:%.S=%.o),$(OBJ_DIR)/$(TARGET)/$(file))
OBJS   := $(CXX_OBJ) $(ASM_OBJ)

#######################################
###            RULES
#######################################

# Default rule
.PHONY: all
all: $(TGT_BIN)

# Cleanup
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/
	rm -rf $(IMG_DIR)/

# Rule for building C sources
$(CXX_OBJ): $(OBJ_DIR)/$(TARGET)/%.o : %.c
	$L "$(TARGET):  Compiling $< (C)"
	@$(MKDIR) $(dir $@)
	$Q $(CC) -c $(CFLAGS) $< -o $@

# Rule for building ASM sources
$(ASM_OBJ): $(OBJ_DIR)/$(TARGET)/%.o : %.S
	$L "$(TARGET):  Compiling $< (S)"
	@$(MKDIR) $(dir $@)
	$Q $(CC) -c $(CFLAGS) $< -o $@

# Rule for linking ELF file
$(TGT_ELF): $(OBJS)
	$L "$(TARGET):  Linking $@"
	@$(MKDIR) $(IMG_DIR)
	$Q $(CC) $(LDFLAGS) $(OBJS) -o $@

# Rule for generating binary object
$(TGT_BIN): $(TGT_ELF)
	$L "$(TARGET):  Generating $@"
	@$(MKDIR) $(IMG_DIR)
	$Q $(OBJCOPY) -O binary $< $@
	
