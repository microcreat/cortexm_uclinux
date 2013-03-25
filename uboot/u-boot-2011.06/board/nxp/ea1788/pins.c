/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: EA1788 board specific pin (IOCON) setup
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
#include <asm/arch/lpc17_iocon.h>

extern void _start(void);

/*
 * This array maps the LPC1788 pins to the function they are used for on
 * the EA1788 board. Only pins that change from the default functions are
 * in this array. To save memory, the array structures are bit packed in
 * the structure definition. Each entry should only use 32-bits.
 *
 */
const iocon_pin_type ea1788_iocon_pins[] = {
	{
		/* P0.0 (D) = CAN_RD1 */
		0, 0, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.1 (D) = CAN_TD1 */
		0, 1, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.2 (D) = UART0 TXD */
		0, 2, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.3 (D) = UART0 RXD */
		0, 3, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.4 (D) = I2S RX clock (alternate LCD D0 when bpp > 16) */
		0, 4, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.5 (D) = I2S RX WS (alternate LCD D1 when bpp > 16) */
		0, 5, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.6 (D) = I2S RX SDA (alternate LCD D8 when bpp > 16) */
		0, 6, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.10 (D) = U2_TXD */
		0, 10, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.11 (D) = U2_RXD */
		0, 11, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.14 (D) = (USB_CONNECT2) USB2 device pullup */
		0, 14, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 3,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.15 (D) = SSP0_CLK */
		0, 15, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.16 (D) = SSP0_SSEL */
		0, 16, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.17 (D) = SSP0_MISO */
		0, 17, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.18 (D) = SSP0_MOSI */
		0, 18, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.19 (D) = LCD SPI CS (GPO) */
		0, 19, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.20 (D) = Touchscreen SPI CS (GPO) */
		0, 20, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.21 (D) = GPIO */
		0, 21, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.22 (D) = GPIO */
		0, 22, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.0 (D) = RMII ENET_TXD0 */
		1, 0, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P1.1 (D) = RMII ENET_TXD1 */
		1, 1, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P1.2 (D) = SD_CLK */
		1, 2, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 2,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.3 (D) = SD_CMD */
		1, 3, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 2,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.4 (D) = RMII ENET_TX_EN */
		1, 4, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P1.5 (D) = SD_PWR */
		1, 5, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 2,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.6 (D) = SD_DAT0 */
		1, 6, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 2,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.7 (D) = SD_DAT1 */
		1, 7, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 2,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.8 (D) = RMII CRS */
		1, 8, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P1.9 (D) = RMII RXD0 */
		1, 9, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P1.10 (D) = RMII RXD1 */
		1, 10, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P1.11 (D) = SD_DAT2 */
		1, 11, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 2,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.12 (D) = SD_DAT3 */
		1, 12, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 2,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.13 (D) = GPIO */
		1, 13, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.14 (D) = RMII RXER */
		1, 14, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.15 (D) = RMII CLK */
		1, 15, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.16 (D) = RMII MCD */
		1, 16, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.17 (D) = RMII MDIO */
		1, 17, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.18 (D) = GPIO */
		1, 18, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.19 (D) = USB1-PWREN */
		1, 19, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 2,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.20 (D) = LCD D10 */
		1, 20, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.21 (D) = LCD D11 */
		1, 21, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.22 (D) = LCD D12 */
		1, 22, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.23 (D) = LCD D13 */
		1, 23, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.24 (D) = LCD D14 */
		1, 24, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.25 (D) = LCD D15 */
		1, 25, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.26 (D) = LCD D20 */
		1, 26, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.27 (D) = USB transceiver INT (MIC2555) */
		1, 27, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.28 (D) = USB I2C SCL */
		1, 28, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P1.29 (D) = USB I2C SDA */
		1, 29, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.0 (D) = LCDPWR */
		2, 0, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.1 (D) = LCDLE */
		2, 1, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.2 (D) = LCDDCLK */
		2, 2, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.3 (D) = LCDFP */
		2, 3, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.4 (D) = LCDENAB */
		2, 4, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.5 (D) = LCDLP */
		2, 5, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.6 (D) = LCD D4 */
		2, 6, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.7 (D) = LCD D5 */
		2, 7, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.8 (D) = LCD D6 */
		2, 8, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0, IOCON_D_TYPE,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.9 (D) = LCD D7 */
		2, 9, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.10 (D) = GPIO (LED and SW6) */
		2, 10, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.11 (D) = LCD clock in */
		2, 11, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.12 (D) = LCD D18 */
		2, 12, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.13 (D) = LCD D19 */
		2, 13, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 7,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.14 (D) = GPIO */
		2, 14, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.15 (D) = GPIO */
		2, 15, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.16 (D) = EMC CAS */
		2, 16, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P2.17 (D) = EMC RAS */
		2, 17, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P2.18 (D) = EMC CLK0 */
		2, 18, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P2.19 (D) = GPIO */
		2, 19, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.20 (D) = EMC DYCS0 */
		2, 20, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P2.21 (D) = GPIO */
		2, 21, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.22 (D) = GPI 5-key joystick */
		2, 22, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.23 (D) = GPI 5-key joystick */
		2, 23, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.24 (D) = EMC CKE0 */
		2, 24, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P2.25 (D) = GPI 5-key joystick */
		2, 25, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.26 (D) = GPI 5-key joystick */
		2, 26, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.27 (D) = GPI 5-key joystick */
		2, 27, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P2.28 (D) = DQM0 */
		2, 28, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P2.29 (D) = DQM1 */
		2, 29, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P2.30 (D) = DQM2 */
		2, 30, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P2.31 (D) = DQM3 */
		2, 31, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	},
	{
		/* P5.0 (D) = GPIO */
		5, 0, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P5.1 (D) = GPIO */
		5, 1,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P5.2 (I) = GPIO */
		5, 2, IOCON_I_TYPE,
		.iocon.i = {
			.func	= 0,
			.inv	= 0,
			.hs	= 0,
			.hidrive = 0,
		}
	},
	{
		/* P5.3 (I) = GPIO */
		5, 3, IOCON_I_TYPE,
		.iocon.i = {
			.func	= 0,
			.inv	= 0,
			.hs	= 0,
			.hidrive = 0,
		}
	},
	{
		/* P5.4 (D) = GPIO */
		5, 4, IOCON_D_TYPE,
		.iocon.d = {
			.func	= 0,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.7 (W) = I2S TX SCK */
		0, 7, IOCON_W_TYPE,
		.iocon.w = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.filter	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.8 (W) = I2S TX WS */
		0, 8, IOCON_W_TYPE,
		.iocon.w = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.filter	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.9 (W) = I2S TX SDA */
		0, 9, IOCON_W_TYPE,
		.iocon.w = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.filter	= 0,
			.slew	= 0,
			.od	= 0
		}
	},
	{
		/* P0.12 (A) = USB2 PWREN */
		0, 12, IOCON_A_TYPE,
		.iocon.a = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.admode = 0,
			.filter	= 0,
			.od	= 0,
			.dacen	= 0
		}
	},
	{
		/* P0.13 (A) = USB2 UPLED */
		0, 13, IOCON_A_TYPE,
		.iocon.a = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.admode = 0,
			.filter	= 0,
			.od	= 0,
			.dacen	= 0
		}
	},
	{
		/* P0.23 (A) = GPIO or AIN0 */
		0, 23, IOCON_A_TYPE,
		.iocon.a = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.admode = 1,
			.filter	= 0,
			.od	= 0,
			.dacen	= 0
		}
	},
	{
		/* P0.24 (A) = GPIO or AIN1 */
		0, 24, IOCON_A_TYPE,
		.iocon.a = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.admode = 1,
			.filter	= 0,
			.od	= 0,
			.dacen	= 0
		}
	},
	{
		/* P0.25 (A) = GPIO or AIN2 */
		0, 25, IOCON_A_TYPE,
		.iocon.a = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.admode = 1,
			.filter	= 0,
			.od	= 0,
			.dacen	= 0
		}
	},
	{
		/* P0.26 (A) = GPO or AOUT */
		0, 26, IOCON_A_TYPE,
		.iocon.a = {
			.func	= 2,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.admode = 1,
			.filter	= 0,
			.od	= 0,
			.dacen	= 1
		}
	},
	{
		/* P0.27 (I) = I2C SCL */
		0, 27, IOCON_I_TYPE,
		.iocon.i = {
			.func	= 1,
			.inv	= 0,
			.hs	= 1,
			.hidrive = 1,
		}
	},
	{
		/* P0.28 (I) = I2C SDA */
		0, 28, IOCON_I_TYPE,
		.iocon.i = {
			.func	= 1,
			.inv	= 0,
			.hs	= 1,
			.hidrive = 1,
		}
	},
	{
		/* P0.29 (U) = USB1 DP */
		0, 29, IOCON_U_TYPE,
		.iocon.u = {
			.func	= 1,
		}
	},
	{
		/* P0.30 (U) = USB2 DP */
		0, 30, IOCON_U_TYPE,
		.iocon.u = {
			.func	= 1,
		}
	},
	{
		/* P0.31 (U) = USB1 DM */
		0, 31, IOCON_U_TYPE,
		.iocon.u = {
			.func	= 1,
		}
	},
	{
		/* P1.30 (D) = USB2 VBUS */
		0, 30, IOCON_D_TYPE,
		.iocon.a = {
			.func	= 2,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.admode = 0,
			.filter	= 0,
			.od	= 0,
			.dacen	= 0
		}
	},
	{
		/* P1.31 (D) = USB2 OVRCR */
		0, 31, IOCON_D_TYPE,
		.iocon.a = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.admode = 0,
			.filter	= 0,
			.od	= 0,
			.dacen	= 0
		}
	}
};

void ea1788_setup_pins(void)
{
	int idx;
	u16 pin, grp;
	iocon_pin_type *pi, ea1788_addr_data_pin = {
		0, 0,
		.iocon.d = {
			.func	= 1,
			.mode	= LPC17_NO_PULLUP,
			.hys	= 0,
			.inv	= 0,
			.slew	= 1,
			.od	= 0
		}
	};

	/* Setup data, address, and EMC control pins */
	for (grp = 3; grp <= 4; grp++) {
		for (pin = 0; pin <= 31; pin++) {
			ea1788_addr_data_pin.grp = grp;
			ea1788_addr_data_pin.pin = pin;
			lpc17_iocon_setup(&ea1788_addr_data_pin);
		}
	}

	/*
	 * The pointer to the pin setup table may be in RAM, but we might be
	 * running from FLASH. Manually fixup the pointer to the table to
	 * point to the relative location to the start of code (_start)
	 */
	pi = (iocon_pin_type *) ((u32) ea1788_iocon_pins -
		(u32) _start);

	for (idx = 0; idx < ARRAY_SIZE(ea1788_iocon_pins); idx++)
		lpc17_iocon_setup(&pi[idx]);
}

