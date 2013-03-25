#ifndef __LPC17_IOCON_H
#define __LPC17_IOCON_H

/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx IOCON setup support functions
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

/* Function mode for pins */
typedef enum {
	LPC17_NO_PULLUP	= 0,
	LPC17_PULLDOWN	= 1,
	LPC17_PULLUP	= 2,
	LPC17_REPEATER	= 3
} lpc17_mode;

/*
 * Structure for setting up IOCON type D pins. See the User manual for setup.
 */
typedef struct {
	u16 func	: 3;
	u16 mode	: 2;
	u16 hys		: 1; /* true to enable hysteresis */
	u16 inv		: 1; /* true to invert signal */
	u16 slew	: 1; /* true to enable fast slew */
	u16 od		: 1; /* true to enable simulated open drain */
} lpc17_iocon_d_setup;

/*
 * Structure for setting up IOCON type A pins. See the User manual for setup.
 */
typedef struct {
	u16 func	: 3;
	u16 mode	: 2;
	u16 hys		: 1; /* true to enable hysteresis */
	u16 inv		: 1; /* true to invert signal */
	u16 admode	: 1; /* true for digital, false for analog */
	u16 filter	: 1; /* true to disable glitch filter */
	u16 od		: 1; /* true to enable simulated open drain */
	u16 dacen	: 1; /* true to enable DAC */
} lpc17_iocon_a_setup;

/*
 * Structure for setting up IOCON type U pins. See the User manual for setup.
 */
typedef struct {
	u16 func	: 3;
} lpc17_iocon_u_setup;

/*
 * Structure for setting up IOCON type I pins. See the User manual for setup.
 */
typedef struct {
	u16 func	: 3;
	u16 inv		: 1; /* true to invert signal */
	u16 hs		: 1; /* true to disable glitch filter */
	u16 hidrive	: 1; /* true to enable 20mA sink */
} lpc17_iocon_i_setup;

/*
 * Structure for setting up IOCON type W pins. See the User manual for setup.
 */
typedef struct {
	u16 func	: 3;
	u16 mode	: 2;
	u16 hys		: 1; /* true to enable hysteresis */
	u16 inv		: 1; /* true to invert signal */
	u16 filter	: 1; /* true to disable glitch filter */
	u16 slew	: 1; /* true to enable fast slew */
	u16 od		: 1; /* true to enable simulated open drain */
} lpc17_iocon_w_setup;

typedef enum {
	IOCON_D_TYPE = 0,
	IOCON_A_TYPE,
	IOCON_U_TYPE,
	IOCON_I_TYPE,
	IOCON_W_TYPE
} LPC17_IOCON_TYPE;

typedef struct {
	u16 grp		: 3;
	u16 pin		: 5;
	u16 iocon_type	: 3;
	union {
		lpc17_iocon_d_setup d;
		lpc17_iocon_a_setup a;
		lpc17_iocon_u_setup u;
		lpc17_iocon_i_setup i;
		lpc17_iocon_w_setup w;
	} iocon;
} iocon_pin_type;

/* Set the configuration of a IOCON pin */
void lpc17_iocon_setup(iocon_pin_type *iocon_pin);

#endif /* __LPC17_IOCON_H */
