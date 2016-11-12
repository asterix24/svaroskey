/*
 * STM32F103 interrupt vector and startup routine
 */

.syntax unified
.thumb

.text
.thumb_func
default_isr:
	wfi
	b default_isr

.section .vectors,"ax",%progbits

irq_vectors:
	.word __stack_end	/* Initial stack pointer */
	.word __reset_handler	/* Reset handler */
	.word default_isr	/* NMI handler */
	.word default_isr	/* Hard fault handler */
	.word default_isr	/* Memory management fault handler */
	.word default_isr	/* Bus fault handler */
	.word default_isr	/* Usage fault handler */
	.space 16		/* Reserved */
	.word default_isr	/* Supervisor call handler */
	.space 8		/* Reserved */
	.word default_isr	/* PendSV handler */
	.word default_isr	/* Systick handler */
	.space 272              /* STM32F103 IRQs */

.section .init, "ax", %progbits

/*
 * Reset handler
 */
.balign 2
.thumb_func
__reset_handler:
	/* Disable IRQs */
	cpsid i

	/* Copy the data segment initializers from flash to SRAM */
	ldr r0, =__text_end
	ldr r1, =__data_start
	ldr r2, =__data_end
data_loop:
	cmp r1, r2
	ittt lo
	ldrlo r3, [r0], #4
	strlo r3, [r1], #4
	blo data_loop

	/* Zero fill the bss segment */
	ldr r1, =__bss_start
	ldr r2, =__bss_end
	mov r0, #0
bss_loop:
	cmp r1, r2
	itt lo
	strlo r0, [r1], #4
	blo bss_loop

	/* Call the application's entry point */
	cpsie i
	mov r0, #0
	mov r1, #0
	bl main
end:
	wfi
	b end
