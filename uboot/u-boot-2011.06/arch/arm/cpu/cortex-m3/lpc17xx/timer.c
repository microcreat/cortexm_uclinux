/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx timer driver
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

#define TIMER_CLK LPC17_CLK_TIM0
#define UDELAY_CLK LPC17_CLK_TIM1
#define TIMER_BASE LPC17_TIMER0
#define UDELAY_BASE LPC17_TIMER1

void reset_timer(void)
{
	unsigned int clkdlycnt, tbaseclk;

	/* Reset timer */
	__raw_writel(2, LPC17_TIMER_TCR(TIMER_BASE));
	__raw_writel(0, LPC17_TIMER_TCR(TIMER_BASE));
	__raw_writel(0, LPC17_TIMER_TC(TIMER_BASE));

	/* Clear and enable match function */
	__raw_writel(1, LPC17_TIMER_IR(TIMER_BASE));

	/* Count mode is PCLK edge */
	__raw_writel(0, LPC17_TIMER_CTCR(TIMER_BASE));

	/* Set prescale counter */
	tbaseclk = lpc17_get_pclk_rate();
	clkdlycnt = (tbaseclk / CONFIG_SYS_HZ);
	__raw_writel(clkdlycnt, LPC17_TIMER_PR(TIMER_BASE));

	/* Enable the timer */
	__raw_writel(1, LPC17_TIMER_TCR(TIMER_BASE));
}

ulong get_timer(ulong base)
{
	ulong tcr = __raw_readl(LPC17_TIMER_TC(TIMER_BASE));
	return tcr - base;
}

void __udelay(unsigned long usec)
{
	long tbaseclk;

	/* Enable timer system clock */
	lpc17_clk_enable(UDELAY_CLK, 1);

	/* Reset timer */
	__raw_writel(2, LPC17_TIMER_TCR(UDELAY_BASE));
	__raw_writel(0, LPC17_TIMER_TCR(UDELAY_BASE));
	__raw_writel(0, LPC17_TIMER_PC(UDELAY_BASE));
	__raw_writel(0, LPC17_TIMER_PR(UDELAY_BASE));

	/* Clear and enable match function */
	__raw_writel(1, LPC17_TIMER_IR(UDELAY_BASE));

	/* Count mode is PCLK edge */
	__raw_writel(0, LPC17_TIMER_CTCR(UDELAY_BASE));

	/* Set prescale counter value for proper tick rate */
	tbaseclk = lpc17_get_pclk_rate();
	tbaseclk = (tbaseclk / 1000000) - 1;
	__raw_writel(tbaseclk, LPC17_TIMER_PR(UDELAY_BASE));

	/* Set match for number of usecs */
	__raw_writel(usec, LPC17_TIMER_MR0(UDELAY_BASE));

	/* Interrupt on match 0 */
	__raw_writel(1, LPC17_TIMER_MCR(UDELAY_BASE));

	/* Enable the timer */
	__raw_writel(1, LPC17_TIMER_TCR(UDELAY_BASE));

	/* Loop until match occurs */
	while (!(__raw_readl(LPC17_TIMER_IR(UDELAY_BASE)) & 0x1));

	/* Stop timer */
	__raw_writel(0, LPC17_TIMER_TCR(UDELAY_BASE));

	/* Disable timer system clock */
	lpc17_clk_enable(UDELAY_CLK, 0);
}

int timer_init(void)
{
	lpc17_clk_enable(TIMER_CLK, 1);
	reset_timer();

	return 0;
}

