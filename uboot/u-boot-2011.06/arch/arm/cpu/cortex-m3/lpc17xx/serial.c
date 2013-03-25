/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx serial port functions
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include <asm/arch/lpc17_regs.h>
#include <asm/arch/lpc17_clocks.h>

#if CONFIG_LPC17_UART_BOOT == 0
#define UART_BASE LPC17_UART0
#define UART_CLK LPC17_CLK_UART0
#endif
#if CONFIG_LPC17_UART_BOOT == 1
#define UART_BASE LPC17_UART1
#define UART_CLK LPC17_CLK_UART1
#endif
#if CONFIG_LPC17_UART_BOOT == 2
#define UART_BASE LPC17_UART2
#define UART_CLK LPC17_CLK_UART2
#endif
#if CONFIG_LPC17_UART_BOOT == 3
#define UART_BASE LPC17_UART3
#define UART_CLK LPC17_CLK_UART3
#endif
#if CONFIG_LPC17_UART_BOOT == 4
#define UART_BASE LPC17_UART4
#define UART_CLK LPC17_CLK_UART4
#endif

DECLARE_GLOBAL_DATA_PTR;

void serial_setbrg(void)
{
	long div, clkrate;

	clkrate = lpc17_get_pclk_rate();
	div = clkrate / (gd->baudrate * 16);

	__raw_writel(__raw_readl(LPC17_UART_LCR(UART_BASE)) | 0x80,
		LPC17_UART_LCR(UART_BASE));
	__raw_writel(div & 0xFF, LPC17_UART_FIFO_DLL(UART_BASE));
	__raw_writel((div >> 8) & 0xFF, LPC17_UART_IER_DLM(UART_BASE));
	__raw_writel(__raw_readl(LPC17_UART_LCR(UART_BASE)) & ~0x80,
		LPC17_UART_LCR(UART_BASE));
}

/*
 * it is the responsiblity of the board code to setup the proper pin
 * muxing for the selected UART
 */
int serial_init(void)
{
	volatile unsigned int tmp32;

	/* Enable UART clock */
	lpc17_clk_enable(UART_CLK, 1);

	/* set baudrate */
	gd->baudrate = CONFIG_BAUDRATE;
	serial_setbrg();

	/* Setup default UART state for N81 with FIFO mode */
	__raw_writel(0x3, LPC17_UART_LCR(UART_BASE));

	/* Clear FIFOs and set FIFO level */
	__raw_writel(0x7, LPC17_UART_FCR_IIR(UART_BASE));
	tmp32 = __raw_readl(LPC17_UART_FCR_IIR(UART_BASE));
	tmp32 = __raw_readl(LPC17_UART_LSR(UART_BASE));

	return 0;
}

int serial_getc(void)
{
	/* Wait for a character from the UART */
	while (!(__raw_readl(LPC17_UART_LSR(UART_BASE)) & (1 << 0)));

	return (int) (__raw_readl(LPC17_UART_FIFO_DLL(UART_BASE)) & 0xFF);
}

void serial_putc(const char c)
{
	/* Wait for FIFO to become empty */
	while (!(__raw_readl(LPC17_UART_LSR(UART_BASE)) & (1 << 5)));

	__raw_writel((long) c, LPC17_UART_FIFO_DLL(UART_BASE));

	/* If \n, also do \r */
	if (c == '\n')
		serial_putc('\r');
}

int serial_tstc(void)
{
	/* Test for a character from the UART */
	if (!(__raw_readl(LPC17_UART_LSR(UART_BASE)) & 1))
		return 0;

	return 1;
}

void serial_puts(const char *s)
{
	while (*s)
		serial_putc (*s++);
}

