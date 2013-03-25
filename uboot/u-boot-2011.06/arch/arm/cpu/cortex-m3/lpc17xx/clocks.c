/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx clock control driver
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
#include <asm/arch/lpc17_clock_checks.h>

#if CONFIG_LPC17_PLL0_USE_EXTOSC==1
#define LPC17_SYSCLK CONFIG_LPC17_OSC_RATE
#else
#define LPC17_SYSCLK LPC17_INTOSCRATE
#endif

unsigned long lpc17_get_pll0_rate(void)
{
#if CONFIG_LPC17_PLL0_ENABLE==0
	return 0;
#else
	return LPC17_SYSCLK * CONFIG_LPC17_PLL0_M;
#endif
}

unsigned long lpc17_get_pll1_rate(void)
{
#if CONFIG_LPC17_PLL1_ENABLE==0
	return 0;
#else
	return CONFIG_LPC17_OSC_RATE * CONFIG_LPC17_PLL1_M;
#endif
}

unsigned long lpc17_get_cpu_rate(void)
{
#if CONFIG_LPC17_PLL0_FOR_CPU==1
	return lpc17_get_pll0_rate() / CONFIG_LPC17_CPU_DIV;
#else
	return LPC17_SYSCLK / CONFIG_LPC17_CPU_DIV;
#endif
}

unsigned long lpc17_get_usb_rate(void)
{
	return lpc17_get_pll1_rate() / CONFIG_LPC17_USB_DIV;
}

unsigned long lpc17_get_emc_rate(void)
{
#if CONFIG_LPC17_PLL0_FOR_CPU==1
	return lpc17_get_pll0_rate() / (1 + CONFIG_LPC17_EMC_HALFCPU);
#else
	return LPC17_SYSCLK / (1 + CONFIG_LPC17_EMC_HALFCPU);
#endif
}

unsigned long lpc17_get_pclk_rate(void)
{
#if CONFIG_LPC17_PLL0_FOR_CPU==1
	return lpc17_get_pll0_rate() / CONFIG_LPC17_PCLK_DIV;
#else
	return LPC17_SYSCLK / CONFIG_LPC17_PCLK_DIV;
#endif
}

void lpc17_clk_enable(lpc17xx_clk clk, int enable)
{
	if (enable)
		__raw_writel(__raw_readl(LPC17_SC_PCONP) | (1 << (int) clk),
			LPC17_SC_PCONP);
	else
		__raw_writel(__raw_readl(LPC17_SC_PCONP) & ~(1 << (int) clk),
			LPC17_SC_PCONP);
}

#if CONFIG_LPC17_PLL0_ENABLE==1
static inline void lpc17_pll0_latch(long pllcon)
{
	__raw_writel(pllcon, LPC17_SC_PLL0CON);
	__raw_writel(0xAA, LPC17_SC_PLL0FEED);
	__raw_writel(0x55, LPC17_SC_PLL0FEED);
}
#endif

#if CONFIG_LPC17_PLL1_ENABLE==1
static inline void lpc17_pll1_latch(long pllcon)
{
	__raw_writel(pllcon, LPC17_SC_PLL1CON);
	__raw_writel(0xAA, LPC17_SC_PLL1FEED);
	__raw_writel(0x55, LPC17_SC_PLL1FEED);
}
#endif

/*
 * Sets up system clocking from the various CONFIG_ values in the
 * u-boot board config file.
 */
void lpc17_setup_clocks(void)
{
	long reg;

#if CONFIG_LPC17_PLL0_USE_EXTOSC==1
	/* Enable oscillator and wait for it to become ready */
#if CONFIG_LPC17_OSC_RATE > 15000000
	__raw_writel(__raw_readl(LPC17_SC_SCS) | (1 << 5) | (1 << 4),
		LPC17_SC_SCS);
#else
	__raw_writel(__raw_readl(LPC17_SC_SCS) | (1 << 5), LPC17_SC_SCS);
#endif
	while (!(__raw_readl(LPC17_SC_SCS) & (1 << 6)));

	/* Switch PLL0 and SYSCLK to the external oscillator */
	__raw_writel(0x1, LPC17_SC_CLKSRCSEL);
#endif

#if CONFIG_LPC17_PLL0_ENABLE==1
	/* PLL0 setup */
	__raw_writel((CONFIG_LPC17_PLL0_M - 1) | CONFIG_LPC17_PLL0_P << 5,
		LPC17_SC_PLL0CFG);
	lpc17_pll0_latch(1);

	/* Wait for lock */
	while (!(__raw_readl(LPC17_SC_PLL0STAT) & (1 << 10)));
#endif

#if CONFIG_LPC17_PLL1_ENABLE==1
	/* PLL1 setup */
	__raw_writel((CONFIG_LPC17_PLL1_M - 1) | CONFIG_LPC17_PLL1_P << 5,
		LPC17_SC_PLL1CFG);
	lpc17_pll1_latch(1);

	/* Wait for lock */
	while (!(__raw_readl(LPC17_SC_PLL1STAT) & (1 << 10)));
#endif

	/* CPU clock */
#if CONFIG_LPC17_PLL0_FOR_CPU==1
	__raw_writel((1 << 8) | CONFIG_LPC17_CPU_DIV, LPC17_SC_CCLKSEL);
#else
	__raw_writel(CONFIG_LPC17_CPU_DIV, LPC17_SC_CCLKSEL);
#endif

	/* USB clock */
	__raw_writel((0x20 << 8) | CONFIG_LPC17_USB_DIV, LPC17_SC_USBCLKSEL);

	/* EMC clock */
	__raw_writel(CONFIG_LPC17_EMC_HALFCPU, LPC17_SC_EMCCLKSEL);

	/* Peripheral clock */
	__raw_writel(CONFIG_LPC17_PCLK_DIV, LPC17_SC_PCLKSEL);

	/* Flash accelerator */
	__raw_writel((CONFIG_LPC17_FLASH_CLOCKS - 1) << 12 | 0x3A,
		LPC17_SC_FLASHCFG);

	/* Setup CLKOUT for CPU rate divided by 16 */
	__raw_writel(0 | 16 << 4 | 0x100, LPC17_SC_CLKOUTCFG);
}

