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

#include <common.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include <asm/arch/lpc17_regs.h>
#include <asm/arch/lpc17_iocon.h>

typedef struct {
	u16 grp		: 3;
	u16 pin_start	: 5;
	u16 pin_end	: 5;
	LPC17_IOCON_TYPE iocon_type;
} LPC17_IOCON_RANGE;

/* Set the configuration of a IOCON pin */
void lpc17_iocon_setup(iocon_pin_type *iocon_pin)
{
	u32 regval;

	switch (iocon_pin->iocon_type)
	{
	case IOCON_D_TYPE:
		regval = (u32) (iocon_pin->iocon.d.func |
			(iocon_pin->iocon.d.mode << 3) |
			(iocon_pin->iocon.d.hys << 5) |
			(iocon_pin->iocon.d.inv << 6) | 
			(iocon_pin->iocon.d.slew << 9) |
			(iocon_pin->iocon.d.od << 10));
		break;

	case IOCON_A_TYPE:
		regval = (u32) (iocon_pin->iocon.a.func |
			(iocon_pin->iocon.a.mode << 3) |
			(iocon_pin->iocon.a.hys << 5) |
			(iocon_pin->iocon.a.inv << 6) | 
			(iocon_pin->iocon.a.admode << 7) | 
			(iocon_pin->iocon.a.inv << 6) | 
			(iocon_pin->iocon.a.filter << 8) |
			(iocon_pin->iocon.a.od << 10) |
			(iocon_pin->iocon.a.dacen << 11));
		break;

	case IOCON_U_TYPE:
		regval = (u32) iocon_pin->iocon.u.func;
		break;

	case IOCON_I_TYPE:
		regval = (u32) (iocon_pin->iocon.i.func |
			(iocon_pin->iocon.i.inv << 6) |
			(iocon_pin->iocon.i.hs << 8) |
			(iocon_pin->iocon.i.hidrive << 9));
		break;

	case IOCON_W_TYPE:
		regval = (u32) (iocon_pin->iocon.w.func |
			(iocon_pin->iocon.w.mode << 3) |
			(iocon_pin->iocon.w.hys << 5) |
			(iocon_pin->iocon.w.inv << 6) | 
			(iocon_pin->iocon.w.filter << 8) |
			(iocon_pin->iocon.w.slew << 9) |
			(iocon_pin->iocon.w.od << 10));
		break;

	default:
		return;
	}

	__raw_writel(regval, LPC17_IOCON(iocon_pin->grp, iocon_pin->pin));
}

