/*
 * Linker script for STM32103RB microcontroller
 */

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/*
 * Stack size
 */
STACK_SIZE = 0x1000; /* 4KB */

/*
 * Memory configuration
 */
MEMORY
{
	rom(rx) : org = 0x00000000, len = 128k
	ram(rwx) : org = 0x20000000, len = 20k
}

/*
 * Allocate section memory
 */
SECTIONS
{
	.text :
	{
		KEEP(*(.vectors));
		. = ALIGN (4);
		KEEP(*(.init));
		. = ALIGN (4);
		*(.rodata .rodata.*);
		. = ALIGN (4);
		*(.text .text.*);
		. = ALIGN (4);
		*(.glue_7t);
		. = ALIGN(4);
		*(.glue_7);
		. = ALIGN(4);
	} > rom

	__text_end = .;
	PROVIDE (__text_end = .);

	.data : AT (__text_end)
	{
		PROVIDE (__data_start = .);
		. = ALIGN (4);
		*(.data .data.*)
		. = ALIGN (4);
		_edata = .;
		PROVIDE (__data_end = .);
	} > ram

	.bss :
	{
		PROVIDE (__bss_start = .);
		*(.bss .bss.*)
		. = ALIGN(4);
		*(COMMON)
		. = ALIGN(4);
		PROVIDE (__bss_end = .);
	} > ram

	/*
	 * Allocated stack at the end of bss section.
	 * Data heap is allocate at end of stack.
	 */
	PROVIDE (__stack_start = .);
	. = ALIGN(8);
	. += STACK_SIZE;
	PROVIDE (__stack_end = .);

	PROVIDE (__heap_start = .);
	. = ALIGN(8);
}
