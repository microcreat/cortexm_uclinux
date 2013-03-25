/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: EA1788 specific MPU setup
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

/*
 * Each entry is a region mapped as address/control
 * Table ends with (-1)
 */
const unsigned long board_mpu_table[] = {
#if 0 /* Just open everything up */
	0x00000000, CM3_MPU_DATA_RW_RW | CM3_MPU_SHARED | CM3_MPU_SIZE_4GB,

#else /* Limit permissions to regions, but only 8 regions */
	/* FLASH, IRAM, boot ROM */
	0x00000000, CM3_MPU_DATA_RW_RW | CM3_MPU_SHARED | CM3_MPU_SIZE_512MB,

	/* On-chip peripheral SRAM banks 0 and 1, AHB and APB peripherals */
	0x20000000, CM3_MPU_DATA_RW_RW | CM3_MPU_SHARED | CM3_MPU_SIZE_1GB,

	/* NOR and NAND FLASH, DRAM */
	0x80000000, CM3_MPU_DATA_RW_RW | CM3_MPU_SHARED | CM3_MPU_SIZE_1GB,

	/* Cortex M3 private bus */
	0xE0000000, CM3_MPU_DATA_RW_RW | CM3_MPU_SHARED | CM3_MPU_SIZE_1MB |
		CM3_MPU_DIS_INST_FETCHES,
#endif
	/* End of table */
	0xFFFFFFFF
};

