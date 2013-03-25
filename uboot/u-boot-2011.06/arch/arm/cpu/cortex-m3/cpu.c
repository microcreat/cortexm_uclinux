/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: Cortex M3 CPU functions
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>
#include <asm/hardware.h>
#include <asm/system.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include "asm/arch-cortex-m3/cortex-m3.h"

/*
 * Cortex M3 reset at core
 */
void cm3_reset_cpu(ulong addr)
{
	unsigned long *paircr = (unsigned long *) CM3_AIRCR;

	asm volatile ("dsb");
	*paircr = (*paircr & (7 << 8)) | 1 << 2 | 0x5FA << 16;
	asm volatile ("dsb");

	while (1);
}

int cleanup_before_linux (void)
{
	return 0;
}
