# project specific files
SRC = led.c

# Svaroskey board w/ stm32duino bootloader
OPT_DEFS = -DCORTEX_VTOR_INIT=0x2000
BOARD = svaroskey

## chip/board settings
# the next two should match the directories in
#  <chibios>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = STM32
MCU_SERIES = STM32F1xx

# linker script to use
# it should exist either in <chibios>/os/common/ports/ARMCMx/compilers/GCC/ld/
#  or <this_dir>/ld/
MCU_LDSCRIPT = svaroskey

# startup code to use
# is should exist in <chibios>/os/common/ports/ARMCMx/compilers/GCC/mk/
MCU_STARTUP = stm32f1xx

# it should exist either in <chibios>/os/hal/boards/
#  or <this_dir>/boards
# Cortex version
MCU  = cortex-m3
# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 7

BOOTMAGIC_ENABLE = yes  # Virtual DIP switch configuration
CONSOLE_ENABLE = yes    # Console for debug
COMMAND_ENABLE = yes    # Commands for debug and configuration
NKRO_ENABLE = yes       # USB Nkey Rollover
