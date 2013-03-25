/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: EA1788 board specific memory interface setup
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

#define msdelay(x) udelay(x * 1000)

/*
 * DRAM initialization procedure re-used from the NXP LPC177x_178x
 * CMSIS software package.
 *
 * 32-bit DRAM configuration
 *
 * IS42S32800D 8Mx32 256Mbit (32MByte device)
 * -7BL part
 * CAS2 <=100MHz, CAS3 > 100MHz
 * 4096 refresh cycles per 16mS
 * 12 rows, 9 cols, 4 banks
 *
 * Based on timing values below from the u-boot config file (ea1788.h)
 * CONFIG_LPC17_OSC_RATE	12000000
 * CONFIG_LPC17_PLL0_USE_EXTOSC	1
 * CONFIG_LPC17_PLL0_ENABLE	1
 * CONFIG_LPC17_PLL0_M		9
 * CONFIG_LPC17_PLL0_P		1
 * CONFIG_LPC17_PLL1_ENABLE	1
 * CONFIG_LPC17_PLL1_M		4
 * CONFIG_LPC17_PLL1_P		2
 * CONFIG_LPC17_PLL0_FOR_CPU	1
 * CONFIG_LPC17_CPU_DIV		1
 * CONFIG_LPC17_USB_DIV		4
 * CONFIG_LPC17_EMC_HALFCPU	1
 * CONFIG_LPC17_PCLK_DIV	2
 *
 * CPU clock = 108MHz
 * Bus clock = 54MHz
 * USB clock = 48MHz
 * Peripheral clock = 52MHz
 */

void ea1788_mem_if(void)
{
	volatile long tmp32;

	/* Enable clock for EMC */
	lpc17_clk_enable(LPC17_CLK_ADC, 1);	

	/* Clock delay */
	__raw_writel(0x1010, LPC17_SC_EMCDLYCTL);

	/* Little endian mode */
	__raw_writel(0x1, LPC17_EMCCTRL);
	__raw_writel(0x0, LPC17_EMCCFG);

	/* 4 banks, 12 rows, 9 cols, 8Mx32 */
	__raw_writel(0x00004480, LPC17_EMCDDYCFG(0));

	/* Timing for 54MHz bus */
	__raw_writel(0x00000202, LPC17_EMCDYRASCAS(0)); /* 2 CAS, 2 RAS */
	__raw_writel(0x00000001, LPC17_EMCDYRDCFG);
	__raw_writel(0x00000000, LPC17_EMCDYTRP);
	__raw_writel(0x00000002, LPC17_EMCDYRAS);
	__raw_writel(0x00000003, LPC17_EMCDYSREX);
	__raw_writel(0x00000001, LPC17_EMCDYAPR);
	__raw_writel(0x00000002, LPC17_EMCDYDAL);
	__raw_writel(0x00000001, LPC17_EMCDYWR);
	__raw_writel(0x00000003, LPC17_EMCDYRC);
	__raw_writel(0x00000003, LPC17_EMCDYRFC);
	__raw_writel(0x00000003, LPC17_EMCDYXSR);
	__raw_writel(0x00000000, LPC17_EMCDYRRD);
	__raw_writel(0x00000000, LPC17_EMCDYMRD);
	msdelay(100);

	/* NOP */
	__raw_writel(0x183, LPC17_EMCDYCTRL);
	msdelay(200);

	/* Pre-charge all with fast refresh */
	__raw_writel(0x103, LPC17_EMCDYCTRL);
	__raw_writel(0x2, LPC17_EMCDYRFSH);
	msdelay(1);

	/* Set refresh period */
	__raw_writel(0x2E, LPC17_EMCDYRFSH);

	/* Load mode word, CAS2, burst of 4 */
	__raw_writel(0x083, LPC17_EMCDYCTRL);
	tmp32 = __raw_readl(PHYS_SDRAM_1 | (0X22 << 13));

	/* Normal mode */
	__raw_writel(0x0, LPC17_EMCDYCTRL);

	/* Enable DRAM buffer */
	__raw_writel(0x00084480, LPC17_EMCDDYCFG(0));

	/* NOR FLASH timing */
	__raw_writel(0x00000081, LPC17_EMCSTCFG(0));
	__raw_writel(0x00000002, LPC17_EMCSTWWEN(0));
	__raw_writel(0x00000002, LPC17_EMCSTWOEN(0));
	__raw_writel(0x0000001F, LPC17_EMCSTWRD(0));
	__raw_writel(0x0000001F, LPC17_EMCSTWPAGE(0));
	__raw_writel(0x0000001F, LPC17_EMCSTWWR(0));
	__raw_writel(0x0000001F, LPC17_EMCSTWTURN(0));

	/* NAND FLASH timing */
	__raw_writel(0x00000080, LPC17_EMCSTCFG(1));
	__raw_writel(0x00000002, LPC17_EMCSTWWEN(1));
	__raw_writel(0x00000002, LPC17_EMCSTWOEN(1));
	__raw_writel(0x0000001F, LPC17_EMCSTWRD(1));
	__raw_writel(0x0000001F, LPC17_EMCSTWPAGE(1));
	__raw_writel(0x0000001F, LPC17_EMCSTWWR(1));
	__raw_writel(0x0000001F, LPC17_EMCSTWTURN(1));
}

