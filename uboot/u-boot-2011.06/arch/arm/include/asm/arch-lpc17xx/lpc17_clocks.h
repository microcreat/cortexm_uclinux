#ifndef __LPC17_CLOCKS_H
#define __LPC17_CLOCKS_H

/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx clock control
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

typedef enum {
	LPC17_CLK_LCD = 0,
	LPC17_CLK_TIM0,
	LPC17_CLK_TIM1,
	LPC17_CLK_UART0,
	LPC17_CLK_UART1,
	LPC17_CLK_PWM0,
	LPC17_CLK_PWM1,
	LPC17_CLK_I2C0,
	LPC17_CLK_UART4,
	LPC17_CLK_RTC,
	LPC17_CLK_SSP1,
	LPC17_CLK_EMC,
	LPC17_CLK_ADC,
	LPC17_CLK_CAN1,
	LPC17_CLK_CAN2,
	LPC17_CLK_GPIO,
	LPC17_CLK_RESERVED,
	LPC17_CLK_MCPWM,
	LPC17_CLK_QEI,
	LPC17_CLK_I2C1,
	LPC17_CLK_SSP2,
	LPC17_CLK_SSP0,
	LPC17_CLK_TIM2,
	LPC17_CLK_TIM3,
	LPC17_CLK_UART2,
	LPC17_CLK_UART3,
	LPC17_CLK_I2C2,
	LPC17_CLK_I2S,
	LPC17_CLK_SDC,
	LPC17_CLK_DMA,
	LPC17_CLK_ENET,
	LPC17_CLK_USB
} lpc17xx_clk;

extern unsigned long lpc17_get_pll0_rate(void);
extern unsigned long lpc17_get_pll1_rate(void);
extern unsigned long lpc17_get_cpu_rate(void);
extern unsigned long lpc17_get_usb_rate(void);
extern unsigned long lpc17_get_emc_rate(void);
extern unsigned long lpc17_get_pclk_rate(void);
extern void lpc17_clk_enable(lpc17xx_clk, int enable);
extern void lpc17_setup_clocks(void);

#endif /* __LPC17_CLOCKS_H */
