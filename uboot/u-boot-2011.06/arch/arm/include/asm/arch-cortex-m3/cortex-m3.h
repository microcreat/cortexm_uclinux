#ifndef __CORTEX_M3_H
#define __CORTEX_M3_H

/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: Cortex M3 common definitions
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

#define CM3_AIRCR		0xE000ED0C
#define CM3_MPU_REGBASE		0xE000ED90

#define CM3_MPU_DIS_INST_FETCHES	(1 << 28)
#define CM3_MPU_DATA_NO_NO		(0 << 24)
#define CM3_MPU_DATA_RW_NO		(1 << 24)
#define CM3_MPU_DATA_RW_RO		(2 << 24)
#define CM3_MPU_DATA_RW_RW		(3 << 24)
#define CM3_MPU_DATA_RO_NO		(5 << 24)
#define CM3_MPU_DATA_RO_RO		(6 << 24)
#define CM3_MPU_SHARED			(1 << 18)
#define CM3_MPU_CACHABLE		(1 << 17)
#define CM3_MPU_BUFFERABLE		(1 << 16)
#define CM3_MPU_SIZE_32B		(4 << 1)
#define CM3_MPU_SIZE_64B		(5 << 1)
#define CM3_MPU_SIZE_128B		(6 << 1)
#define CM3_MPU_SIZE_256B		(7 << 1)
#define CM3_MPU_SIZE_512B		(8 << 1)
#define CM3_MPU_SIZE_1KB		(9 << 1)
#define CM3_MPU_SIZE_2KB		(10 << 1)
#define CM3_MPU_SIZE_4KB		(11 << 1)
#define CM3_MPU_SIZE_8KB		(12 << 1)
#define CM3_MPU_SIZE_16KB		(13 << 1)
#define CM3_MPU_SIZE_32KB		(14 << 1)
#define CM3_MPU_SIZE_64KB		(15 << 1)
#define CM3_MPU_SIZE_128KB		(16 << 1)
#define CM3_MPU_SIZE_256KB		(17 << 1)
#define CM3_MPU_SIZE_512KB		(18 << 1)
#define CM3_MPU_SIZE_1MB		(19 << 1)
#define CM3_MPU_SIZE_2MB		(20 << 1)
#define CM3_MPU_SIZE_4MB		(21 << 1)
#define CM3_MPU_SIZE_8MB		(22 << 1)
#define CM3_MPU_SIZE_16MB		(23 << 1)
#define CM3_MPU_SIZE_32MB		(24 << 1)
#define CM3_MPU_SIZE_64MB		(25 << 1)
#define CM3_MPU_SIZE_128MB		(26 << 1)
#define CM3_MPU_SIZE_256MB		(27 << 1)
#define CM3_MPU_SIZE_512MB		(28 << 1)
#define CM3_MPU_SIZE_1GB		(29 << 1)
#define CM3_MPU_SIZE_2GB		(30 << 1)
#define CM3_MPU_SIZE_4GB		(31 << 1)
#define CM3_MPU_ENABLE			(1 << 0)

/* Initialize Cortex M3 MPU */
void mpu_init(const unsigned long *init_table);

void mpu_enable(int enable);

#endif /* __CORTEX_M3_H */
