/*
 * STM32F103 interrupt vector and startup routine
 */

.syntax unified
.thumb

.text
.thumb_func
Default_IRQHandler:
	wfi
	b Default_IRQHandler

.weak NMI_IRQHandler
.set NMI_IRQHandler, Default_IRQHandler

.weak HardFault_IRQHandler
.set HardFault_IRQHandler, Default_IRQHandler

.weak MemMgmFault_IRQHandler
.set MemMgmFault_IRQHandler, Default_IRQHandler

.weak BusFault_IRQHandler
.set BusFault_IRQHandler, Default_IRQHandler

.weak UsageFault_IRQHandler
.set UsageFault_IRQHandler, Default_IRQHandler

.weak SVCall_IRQHandler
.set SVCall_IRQHandler, Default_IRQHandler

.weak PendSV_IRQHandler
.set PendSV_IRQHandler, Default_IRQHandler

.weak SysTick_IRQHandler
.set SysTick_IRQHandler, Default_IRQHandler

.weak WWDG_IRQHandler
.set WWDG_IRQHandler, Default_IRQHandler

.weak PVD_IRQHandler
.set PVD_IRQHandler, Default_IRQHandler

.weak TAMPER_IRQHandler
.set TAMPER_IRQHandler, Default_IRQHandler

.weak RTC_IRQHandler
.set RTC_IRQHandler, Default_IRQHandler

.weak FLASH_IRQHandler
.set FLASH_IRQHandler, Default_IRQHandler

.weak RCC_IRQHandler
.set RCC_IRQHandler, Default_IRQHandler

.weak EXTI0_IRQHandler
.set EXTI0_IRQHandler, Default_IRQHandler

.weak EXTI1_IRQHandler
.set EXTI1_IRQHandler, Default_IRQHandler

.weak EXTI2_IRQHandler
.set EXTI2_IRQHandler, Default_IRQHandler

.weak EXTI3_IRQHandler
.set EXTI3_IRQHandler, Default_IRQHandler

.weak EXTI4_IRQHandler
.set EXTI4_IRQHandler, Default_IRQHandler

.weak DMA1_Channel1_IRQHandler
.set DMA1_Channel1_IRQHandler, Default_IRQHandler

.weak DMA1_Channel2_IRQHandler
.set DMA1_Channel2_IRQHandler, Default_IRQHandler

.weak DMA1_Channel3_IRQHandler
.set DMA1_Channel3_IRQHandler, Default_IRQHandler

.weak DMA1_Channel4_IRQHandler
.set DMA1_Channel4_IRQHandler, Default_IRQHandler

.weak DMA1_Channel5_IRQHandler
.set DMA1_Channel5_IRQHandler, Default_IRQHandler

.weak DMA1_Channel6_IRQHandler
.set DMA1_Channel6_IRQHandler, Default_IRQHandler

.weak DMA1_Channel7_IRQHandler
.set DMA1_Channel7_IRQHandler, Default_IRQHandler

.weak ADC1_2_IRQHandler
.set ADC1_2_IRQHandler, Default_IRQHandler

.weak CAN1_TX_IRQHandler
.set CAN1_TX_IRQHandler, Default_IRQHandler

.weak CAN1_RX0_IRQHandler
.set CAN1_RX0_IRQHandler, Default_IRQHandler

.weak CAN1_RX1_IRQHandler
.set CAN1_RX1_IRQHandler, Default_IRQHandler

.weak CAN1_SCE_IRQHandler
.set CAN1_SCE_IRQHandler, Default_IRQHandler

.weak EXTI9_5_IRQHandler
.set EXTI9_5_IRQHandler, Default_IRQHandler

.weak TIM1_BRK_IRQHandler
.set TIM1_BRK_IRQHandler, Default_IRQHandler

.weak TIM1_UP_IRQHandler
.set TIM1_UP_IRQHandler, Default_IRQHandler

.weak TIM1_TRG_COM_IRQHandler
.set TIM1_TRG_COM_IRQHandler, Default_IRQHandler

.weak TIM1_CC_IRQHandler
.set TIM1_CC_IRQHandler, Default_IRQHandler

.weak TIM2_IRQHandler
.set TIM2_IRQHandler, Default_IRQHandler

.weak TIM3_IRQHandler
.set TIM3_IRQHandler, Default_IRQHandler

.weak TIM4_IRQHandler
.set TIM4_IRQHandler, Default_IRQHandler

.weak I2C1_EV_IRQHandler
.set I2C1_EV_IRQHandler, Default_IRQHandler

.weak I2C1_ER_IRQHandler
.set I2C1_ER_IRQHandler, Default_IRQHandler

.weak I2C2_EV_IRQHandler
.set I2C2_EV_IRQHandler, Default_IRQHandler

.weak I2C2_ER_IRQHandler
.set I2C2_ER_IRQHandler, Default_IRQHandler

.weak SPI1_IRQHandler
.set SPI1_IRQHandler, Default_IRQHandler

.weak SPI2_IRQHandler
.set SPI2_IRQHandler, Default_IRQHandler

.weak USART1_IRQHandler
.set USART1_IRQHandler, Default_IRQHandler

.weak USART2_IRQHandler
.set USART2_IRQHandler, Default_IRQHandler

.weak USART3_IRQHandler
.set USART3_IRQHandler, Default_IRQHandler

.weak EXTI15_10_IRQHandler
.set EXTI15_10_IRQHandler, Default_IRQHandler

.weak RTCAlarm_IRQHandler
.set RTCAlarm_IRQHandler, Default_IRQHandler

.weak OTG_FS_WKUP_IRQHandler
.set OTG_FS_WKUP_IRQHandler, Default_IRQHandler

.weak TIM5_IRQHandler
.set TIM5_IRQHandler, Default_IRQHandler

.weak SPI3_IRQHandler
.set SPI3_IRQHandler, Default_IRQHandler

.weak UART4_IRQHandler
.set UART4_IRQHandler, Default_IRQHandler

.weak UART5_IRQHandler
.set UART5_IRQHandler, Default_IRQHandler

.weak TIM6_IRQHandler
.set TIM6_IRQHandler, Default_IRQHandler

.weak TIM7_IRQHandler
.set TIM7_IRQHandler, Default_IRQHandler

.weak DMA2_Channel1_IRQHandler
.set DMA2_Channel1_IRQHandler, Default_IRQHandler

.weak DMA2_Channel2_IRQHandler
.set DMA2_Channel2_IRQHandler, Default_IRQHandler

.weak DMA2_Channel3_IRQHandler
.set DMA2_Channel3_IRQHandler, Default_IRQHandler

.weak DMA2_Channel4_IRQHandler
.set DMA2_Channel4_IRQHandler, Default_IRQHandler

.weak DMA2_Channel5_IRQHandler
.set DMA2_Channel5_IRQHandler, Default_IRQHandler

.weak ETH_IRQHandler
.set ETH_IRQHandler, Default_IRQHandler

.weak ETH_WKUP_IRQHandler
.set ETH_WKUP_IRQHandler, Default_IRQHandler

.weak CAN2_TX_IRQHandler
.set CAN2_TX_IRQHandler, Default_IRQHandler

.weak CAN2_RX0_IRQHandler
.set CAN2_RX0_IRQHandler, Default_IRQHandler

.weak CAN2_RX1_IRQHandler
.set CAN2_RX1_IRQHandler, Default_IRQHandler

.weak CAN2_SCE_IRQHandler
.set CAN2_SCE_IRQHandler, Default_IRQHandler

.weak OTG_FS_IRQHandler
.set OTG_FS_IRQHandler, Default_IRQHandler


.section .vectors,"ax",%progbits

irq_vectors:
	.word __stack_end		/* Initial stack pointer */
	.word Reset_IRQHandler		/* Reset handler */
	.word NMI_IRQHandler		/* NMI handler */
	.word HardFault_IRQHandler	/* Hard fault handler */
	.word MemMgmFault_IRQHandler	/* Memory management fault handler */
	.word BusFault_IRQHandler	/* Bus fault handler */
	.word UsageFault_IRQHandler	/* Usage fault handler */
	.space 16			/* Reserved */
	.word SVCall_IRQHandler		/* Supervisor call handler */
	.space 8			/* Reserved */
	.word PendSV_IRQHandler		/* PendSV handler */
	.word SysTick_IRQHandler	/* Systick handler */

	.word WWDG_IRQHandler		/* Window Watchdog handler */
	.word PVD_IRQHandler		/* PVD through EXTI Line detection handler */
	.word TAMPER_IRQHandler		/* Tamper handler */
	.word RTC_IRQHandler		/* RTC global handler */
	.word FLASH_IRQHandler		/* Flash global handler */
	.word RCC_IRQHandler		/* RCC global handler */
	.word EXTI0_IRQHandler		/* EXTI Line0 handler */
	.word EXTI1_IRQHandler		/* EXTI Line1 handler */
	.word EXTI2_IRQHandler		/* EXTI Line2 handler */
	.word EXTI3_IRQHandler		/* EXTI Line3 handler */
	.word EXTI4_IRQHandler		/* EXTI Line4 handler */
	.word DMA1_Channel1_IRQHandler	/* DMA1 Channel1 global handler */
	.word DMA1_Channel2_IRQHandler	/* DMA1 Channel2 global handler */
	.word DMA1_Channel3_IRQHandler	/* DMA1 Channel3 global handler */
	.word DMA1_Channel4_IRQHandler	/* DMA1 Channel4 global handler */
	.word DMA1_Channel5_IRQHandler	/* DMA1 Channel5 global handler */
	.word DMA1_Channel6_IRQHandler	/* DMA1 Channel6 global handler */
	.word DMA1_Channel7_IRQHandler	/* DMA1 Channel7 global handler */
	.word ADC1_2_IRQHandler		/* ADC1 and ADC2 global handler */
	.word CAN1_TX_IRQHandler	/* CAN1 TX handler */
	.word CAN1_RX0_IRQHandler	/* CAN1 RX0 handler */
	.word CAN1_RX1_IRQHandler	/* CAN1 RX1 handler */
	.word CAN1_SCE_IRQHandler	/* CAN1 SCE handler */
	.word EXTI9_5_IRQHandler	/* EXTI Line[9:5] handler */
	.word TIM1_BRK_IRQHandler	/* TIM1 Break handler */
	.word TIM1_UP_IRQHandler	/* TIM1 Update handler */
	.word TIM1_TRG_COM_IRQHandler	/* TIM1 Trigger and Commutation handler */
	.word TIM1_CC_IRQHandler	/* TIM1 Capture Compare handler */
	.word TIM2_IRQHandler		/* TIM2 global handler */
	.word TIM3_IRQHandler		/* TIM3 global handler */
	.word TIM4_IRQHandler		/* TIM4 global handler */
	.word I2C1_EV_IRQHandler	/* I2C1 event handler */
	.word I2C1_ER_IRQHandler	/* I2C1 error handler */
	.word I2C2_EV_IRQHandler	/* I2C2 event handler */
	.word I2C2_ER_IRQHandler	/* I2C2 error handler */
	.word SPI1_IRQHandler		/* SPI1 global handler */
	.word SPI2_IRQHandler		/* SPI2 global handler */
	.word USART1_IRQHandler		/* USART1 global handler */
	.word USART2_IRQHandler		/* USART2 global handler */
	.word USART3_IRQHandler		/* USART3 global handler */
	.word EXTI15_10_IRQHandler	/* EXTI Line[15:10] handler */
	.word RTCAlarm_IRQHandler	/* RTC alarm through EXTI line handler */
	.word OTG_FS_WKUP_IRQHandler	/* USB On-The-Go FS Wakeup through EXTI line handler */
	.space 28			/* Reserved */
	.word TIM5_IRQHandler		/* TIM5 global handler */
	.word SPI3_IRQHandler		/* SPI3 global handler */
	.word UART4_IRQHandler		/* UART4 global handler */
	.word UART5_IRQHandler		/* UART5 global handler */
	.word TIM6_IRQHandler		/* TIM6 global handler */
	.word TIM7_IRQHandler		/* TIM7 global handler */
	.word DMA2_Channel1_IRQHandler	/* DMA2 Channel1 global handler */
	.word DMA2_Channel2_IRQHandler	/* DMA2 Channel2 global handler */
	.word DMA2_Channel3_IRQHandler	/* DMA2 Channel3 global handler */
	.word DMA2_Channel4_IRQHandler	/* DMA2 Channel4 global handler */
	.word DMA2_Channel5_IRQHandler	/* DMA2 Channel5 global handler */
	.word ETH_IRQHandler		/* Ethernet global handler */
	.word ETH_WKUP_IRQHandler	/* Ethernet Wakeup through EXTI line handler */
	.word CAN2_TX_IRQHandler	/* CAN2 TX handler */
	.word CAN2_RX0_IRQHandler	/* CAN2 RX0 handler */
	.word CAN2_RX1_IRQHandler	/* CAN2 RX1 handler */
	.word CAN2_SCE_IRQHandler	/* CAN2 SCE handler */
	.word OTG_FS_IRQHandler		/* USB On The Go FS global handler */


.section .init, "ax", %progbits

/*
 * Reset handler
 */
.balign 2
.thumb_func
Reset_IRQHandler:
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
