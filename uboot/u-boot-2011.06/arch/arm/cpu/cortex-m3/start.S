/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: armboot - Startup Code for Cortex M3 (Boot from 0x0 only)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * This code always assumes it's running from address 0x0.
 */

#include <asm-offsets.h>
#include <config.h>
#include <version.h>

.extern	lpc17_board_init
.extern red_LED_on
.extern red_LED_off
.extern udelay
.extern mpu_init
.extern mpu_enable
#ifdef CONFIG_USE_BOARD_MPU_TABLE
.extern board_mpu_table
#endif

/*************************************************************************
 *
 * M3 vector table and reset
 *
 * The M3 uses a small structure that contains the initial stack pointer,
 * reset vector, NMI ISR vector, and hard fault vector. This structure is
 * read at reset and used to jump to the reset code, setup the initial
 * stack, and setup the NMI and hard fault ISR vectors in the NVIC.
 *
 *************************************************************************/
	.globl _start
_start:
	.word	CONFIG_SYS_INIT_SP_ADDR
	.word	(reset - _start) | 0x1
	.word	(nmitrap_handler - _start) | 0x1
	.word	(hardfault_handler - _start) | 0x1
	.word	(mpufault_handler - _start) | 0x1
	.word	(busfault_handler - _start) | 0x1
	.word	(usagefault_handler - _start) | 0x1

/*
 * This word is the checksum of the first 7 words. After u-boot is built,
 * run lpc17_fcg on the binary to compute and insert the checksum into
 * the binary image. Be sure it's inserted before making the hex file
 * for burning into FLASH.
 */
	.word	0 

/*
 * 5 more CM3 reserved vectors
 */
	.word 0, 0, 0, 0, 0

/*
 * Up to 64 device specific vectors
 */
	.rept 64
	.word 0
	.endr

/*************************************************************************
 *
 * Various traps
 *
 * Early crashes prior to code execution in DRAM may not work
 *
 *************************************************************************/
nmitrap_handler:
	ldr	r0, =1000*1000/20 /* About 10Hz */
	B	deadloop_toggle_led
hardfault_handler:
	ldr	r0, =1000*1000/10 /* About 5Hz */
	B	deadloop_toggle_led
mpufault_handler:
	ldr	r0, =1000*1000/4 /* About 2Hz */
	B	deadloop_toggle_led
busfault_handler:
	ldr	r0, =1000*1000/2 /* About 1Hz */
	B	deadloop_toggle_led
usagefault_handler:
	ldr	r0, =1000*1000 /* About 0.5Hz */
	B	deadloop_toggle_led

/*
 * GNU seems to have a problem with generating PC relative address using
 * the ADR command on CM3. As a workaround, the relocation code will have to
 * do some math to generate the addresses for the information below.
 */

offsets_rel:
/*
 * Needed by board_init_f to identify load/run area
 */
.globl _TEXT_BASE
_TEXT_BASE:
	.word	CONFIG_SYS_TEXT_BASE

.globl _bss_start_ofs
_bss_start_ofs:
	.word __bss_start - _start
.globl _bss_end_ofs
_bss_end_ofs:
	.word __bss_end__ - _start
.globl _end_ofs
_end_ofs:
	.word _end - _start

#ifdef CONFIG_USE_BOARD_MPU_TABLE
_board_mpu_table_offs:
	.word board_mpu_table - CONFIG_SYS_TEXT_BASE
#endif
/*
 * These may not be needed
 */
/*
_rel_dyn_start_ofs:
	.word __rel_dyn_start - CONFIG_SYS_TEXT_BASE
_rel_dyn_end_ofs:
	.word __rel_dyn_end - CONFIG_SYS_TEXT_BASE
_dynsym_start_ofs:
	.word __dynsym_start - CONFIG_SYS_TEXT_BASE
*/

/* IRQ stack memory + 8 bytes */
.globl IRQ_STACK_START_IN
IRQ_STACK_START_IN:
	.word	0x0badc0de

/*************************************************************************
 *
 * Startup Code (reset vector)
 *
 * Call low level CPU/board initialization
 * Branch (one way) to the board initialization (board_init_f)
 * Note: stack is initialized as part of M3 reset/boot
 *
 *************************************************************************/
reset:

	mov	r0, pc
	ldr	r1, =offset_mark
offset_mark:
	ldr	r2, =offsets_rel
	sub	r1, r1, r2
	sub	r4, r0, r1
	mov	r9, r4 /* R9 has address to offset_rel */

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
	/* Low level init */
	bl	cpu_init_crit
#endif

	/* Relocate data now or hope something doesn't break in all
	 * the 'relative' code and data elsewhere.
	 */
	bl	relocate_pre

/* call board_init_f, absolute jump without return */
call_board_init_f:
	ldr	r0, =board_init_f
	bx	r0

/*************************************************************************
 *
 * void relocate_pre(void)
 *
 * Early code relocation to RAM - this may not be 'proper'
 *
 *************************************************************************/
relocate_pre:
	push	{lr}

	mov	r4, r9

	/* Get destination start and end addresses */
	ldr	r1, [r4, #(_TEXT_BASE - offsets_rel)]
	ldr	r2, [r4, #(_end_ofs - offsets_rel)]
	add	r2, r2, r1

	/* Copy everything */
	ldr	r0, =_start
pre_copy_loop:
	cmp	r1, r2
	beq	pre_copy_loop_exit
	ldr	r3, [r0]
	add	r0, r0, #4
	str	r3, [r1]
	add	r1, r1, #4
	B	pre_copy_loop

pre_copy_loop_exit:
	/* Clear BSS */
	ldr	r3, [r4, #(_TEXT_BASE - offsets_rel)]
	ldr	r1, [r4, #(_bss_start_ofs - offsets_rel)]
	ldr	r2, [r4, #(_bss_end_ofs - offsets_rel)]
	add	r1, r1, r3
	add	r2, r2, r3
	mov	r3, #0

clear_bss:
	str	r3, [r1]
	add	r1, r1, #4
	cmp	r1, r2
	bne	clear_bss

	pop	{pc}

/*************************************************************************
 *
 * void relocate_code (addr_sp, gd, addr_moni)
 *
 * This "function" does not return, instead it continues in RAM
 * after relocating the monitor code. Called from board_init_f().
 *
 *************************************************************************/
	.align 3 /* Align for C to assembly call */
.globl	relocate_code
relocate_code:
	/* Setup new stack */
	mov	sp, r0

/*
 * We are done. Do not return, instead branch to second part of board
 * initialization, now running from RAM.
 */
jump_2_ram:
	ldr	r3, =board_init_r
	/* setup parameters for board_init_r */
	mov	r0, r1		/* gd_t */
	mov	r1, r2		/* dest_addr */
	/* jump to it ... */
	bx	r3

/*************************************************************************
 *
 * CPU_init_critical registers
 *
 * Save link register
 * Call lowlevel_init function for board specific setup
 *
 *************************************************************************/
cpu_init_crit:
	push	{lr}

	/* Setup MPU */
#ifdef CONFIG_USE_BOARD_MPU_TABLE
	mov	r4, r9
	ldr	r0, [r4, #(_board_mpu_table_offs - offsets_rel)]
#else
	mov	r0, #0
#endif
	bl	mpu_init
	mov	r0, #1
	bl	mpu_enable

	/* Jump to board specific initialization */
	bl	lpc17_board_init

	pop	{pc}

/*************************************************************************
 *
 * deadloop_toggle_led(unsigned rate)
 *
 * Called when an error occurs in u-boot. Will toggle an LED
 *
 *************************************************************************/
deadloop_toggle_led:
	ldr	r2, =CONFIG_SYS_INIT_SP_ADDR
	mov	sp, r2
	mov	r4, r0
deadloop_toggle_led_loop:
	bl	red_LED_on
	mov	r0, r4
	bl	udelay
	bl	red_LED_off
	mov	r0, r4
	bl	udelay
	B	deadloop_toggle_led_loop

