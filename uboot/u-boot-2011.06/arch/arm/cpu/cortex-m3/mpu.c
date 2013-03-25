/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: Cortex M3 MPU initialization code
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

#include "asm/arch-cortex-m3/cortex-m3.h"

static void cm3_add_mpu_region(unsigned long region, unsigned long address,
	unsigned long control)
{
	volatile unsigned long *pmpu = (unsigned long *) CM3_MPU_REGBASE;

	*(pmpu + 2) = region;
	*(pmpu + 3) = address;
	*(pmpu + 4) = control;
	*(pmpu + 4) = control | 0x1;
}

void mpu_init(const unsigned long *init_table)
{
	unsigned long rbar, region = 0;

	if (init_table == (unsigned long *) 0x00000000) {
		/* Open all of memory */
		cm3_add_mpu_region(0, 0x00000000, CM3_MPU_DATA_RW_RW |
			CM3_MPU_SIZE_4GB | CM3_MPU_ENABLE);
	} else {
		/* Use passed table */
		while (*init_table != 0xFFFFFFFF) {
			rbar = *init_table;
			rbar |= region | (1 << 4);
			cm3_add_mpu_region(region, rbar,
				*(init_table + 1));
			init_table += 2;
			region++;
		}
	}
}

void mpu_enable(int enable)
{
	unsigned long *pmpu = (unsigned long *) CM3_MPU_REGBASE;

	if (enable)
		*(pmpu + 1) = 0x7;
	else
		*(pmpu + 1) = 0x0;
}

