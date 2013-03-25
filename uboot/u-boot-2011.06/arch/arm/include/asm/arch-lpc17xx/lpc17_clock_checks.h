#ifndef __LPC17_CLOCK_CHECKS_H
#define __LPC17_CLOCK_CHECKS_H

/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx clock definition validation
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

#include <config.h>

/*
 * Compile time sanity checks for defined board clock setup
 */
#ifndef CONFIG_LPC17_OSC_RATE
#error CONFIG_LPC17_OSC_RATE is not setup, set to the external osc rate
#endif
#ifndef CONFIG_LPC17_PLL0_USE_EXTOSC
#error CONFIG_LPC17_PLL0_USE_EXTOSC is not setup, must be 0 or 1
#endif
#ifndef CONFIG_LPC17_PLL0_ENABLE
#error CONFIG_LPC17_PLL0_ENABLE is not setup, must be 0 or 1
#endif
#ifndef CONFIG_LPC17_PLL1_ENABLE
#error CONFIG_LPC17_PLL1_ENABLE is not setup, must be 0 or 1
#endif
#ifndef CONFIG_LPC17_PLL0_FOR_CPU
#error CONFIG_LPC17_PLL0_FOR_CPU is not setup, must be 0 or 1
#endif
#ifndef CONFIG_LPC17_CPU_DIV
#error CONFIG_LPC17_CPU_DIV is not setup, must be between 1 and 31
#endif
#ifndef CONFIG_LPC17_USB_DIV
#error CONFIG_LPC17_USB_DIV is not setup, must be 0, 4, or 6
#endif
#ifndef CONFIG_LPC17_EMC_HALFCPU
#error CONFIG_LPC17_EMC_HALFCPU is not setup, must be 0 or 1
#endif
#ifndef CONFIG_LPC17_PCLK_DIV
#error CONFIG_LPC17_PCLK_DIV is not setup, must be between 1 and 31
#endif
#ifndef CONFIG_LPC17_FLASH_CLOCKS
#error CONFIG_LPC17_FLASH_CLOCKS is not setup, must be between 1 and 6
#endif

/* PLL0 checks */
#if CONFIG_LPC17_PLL0_ENABLE==1

#if CONFIG_LPC17_PLL0_USE_EXTOSC==0
/* PLL0 rate based on internal oscillator */
#define PLL0TMPRATE (LPC17_INTOSCRATE * CONFIG_LPC17_PLL0_M)
#else
/* PLL0 rate based on external oscillator */
#define PLL0TMPRATE (CONFIG_LPC17_OSC_RATE * CONFIG_LPC17_PLL0_M)
#endif

#if PLL0TMPRATE < 9750000
#error PLL0 rate is too low
#endif
#if PLL0TMPRATE > 160000000
#error PLL0 rate is too high
#endif
#if (PLL0TMPRATE * 2 * CONFIG_LPC17_PLL0_P) < 156000000
#error PLL0 FCCO rate is too low
#endif
#if (PLL0TMPRATE * 2 * CONFIG_LPC17_PLL0_P) > 320000000
#error PLL0 FCCO rate is too high
#endif
#endif /* CONFIG_LPC17_PLL0_ENABLE==1 */

/* PLL1 checks */
#if CONFIG_LPC17_PLL1_ENABLE==1

/* PLL1 rate based on external oscillator only */
#define PLL1TMPRATE (CONFIG_LPC17_OSC_RATE * CONFIG_LPC17_PLL1_M)

#if PLL1TMPRATE < 9750000
#error PLL1 rate is too low
#endif
#if PLL1TMPRATE > 160000000
#error PLL1 rate is too high
#endif
#if (PLL1TMPRATE * 2 * CONFIG_LPC17_PLL1_P) < 156000000
#error PLL1 FCCO rate is too low
#endif
#if (PLL1TMPRATE * 2 * CONFIG_LPC17_PLL1_P) > 320000000
#error PLL1 FCCO rate is too high
#endif
#endif /* CONFIG_LPC17_PLL1_ENABLE==1 */

/* Verify CPU divider */
#if CONFIG_LPC17_CPU_DIV < 1
#error CONFIG_LPC17_CPU_DIV is too low, 1 is the minimum
#endif
#if CONFIG_LPC17_CPU_DIV > 31
#error CONFIG_LPC17_CPU_DIV is too high, 31 is the maximum
#endif

/* Verify USB divider */
#if CONFIG_LPC17_USB_DIV!= 0
#if CONFIG_LPC17_USB_DIV!=4
#if CONFIG_LPC17_USB_DIV!=6
#error CONFIG_LPC17_USB_DIV must be 0, 4, or 6
#endif
#endif
#endif

/* Verify peripheral divider */
#if CONFIG_LPC17_PCLK_DIV < 1
#error CONFIG_LPC17_PCLK_DIV is too low, 1 is the minimum
#endif
#if CONFIG_LPC17_PCLK_DIV > 31
#error CONFIG_LPC17_PCLK_DIV is too high, 31 is the maximum
#endif

/* Verify FLASH clocks */
#if CONFIG_LPC17_FLASH_CLOCKS < 1
#error CONFIG_LPC17_FLASH_CLOCKS is too low, 1 is the minimum
#endif
#if CONFIG_LPC17_FLASH_CLOCKS > 6
#error CONFIG_LPC17_FLASH_CLOCKS is too high, 6 is the maximum
#endif

#endif /* __LPC17_CLOCK_CHECKS_H */

