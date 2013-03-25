/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: EA1788 board specific setup for u-boot
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include <asm/arch/lpc17_regs.h>
#include <asm/arch/lpc17_clocks.h>
#include <asm/arch/lpc17_gpio.h>

DECLARE_GLOBAL_DATA_PTR;

extern void ea1788_setup_pins(void);
extern void ea1788_mem_if(void);

extern void cm3_reset_cpu(ulong addr);
#if 0
/*
 * Reset command causes a crash on unmodified u-boot code, use
 * cm_reset instead.
 */
void reset_cpu(ulong addr)
{
	cm3_reset_cpu(0x0);

}
#else
void reset_cpu(ulong addr)
{
	cm3_reset_cpu(0x0);
}

int cm_reset(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	puts ("resetting ...\n");

	udelay (50000);				/* wait 50 ms */

	disable_interrupts();
	cm3_reset_cpu(0x0);

	/*NOTREACHED*/
	return 0;
}

U_BOOT_CMD(
	cmreset, 1, 0,	cm_reset,
	"Perform RESET of the CPU",
	""
);
#endif

void red_LED_on(void)
{
	lpc17xx_gpio_set_output(2, 26);
	lpc17xx_gpio_set_state(2, 26, 0);
}

void red_LED_off(void)
{
	lpc17xx_gpio_set_output(2, 26);
	lpc17xx_gpio_set_state(2, 26, 1);
}

void lpc17_board_init(void)
{
	/* Board specific pin setup */
	ea1788_setup_pins();

	/* Setup system clocking (CPU setup from CONFIG_ values) */
	lpc17_setup_clocks();

	/* Board specific setup memory */
	ea1788_mem_if();
}

int board_init(void)
{
	gd->bd->bi_arch_number = CONFIG_LPC17XX_MACHID;

	/* location of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

	return 0;
}

int misc_init_r(void)
{
	return 0;
}

int dram_init(void)
{
	gd->ram_size = PHYS_SDRAM_1_SIZE;

	return (0);
}

/*
 * Test program for LED only
 */
int cmd_led(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	if (strcmp (argv[1], "on") == 0) {
		red_LED_on();
	} else if (strcmp (argv[1], "off") == 0) {
		red_LED_off();
	} else {
		printf ("Usage:\nled on/off\n");
		return 1;
	}

	return 0;
}

U_BOOT_CMD(
	led ,	2,	1,	cmd_led,
	"switch status LED on or off",
	"on/off"
);

