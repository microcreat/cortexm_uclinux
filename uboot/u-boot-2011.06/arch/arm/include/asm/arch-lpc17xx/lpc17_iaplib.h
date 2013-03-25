#ifndef __LPC17_IAPLIB_H
#define __LPC17_IAPLIB_H

/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx FLASH IAP interface library
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

/* IAP statuses */
typedef enum {
	iap_cmd_success = 0,
	iap_invalid_command,
	iap_src_addr_error,
	iap_dst_addr_error,
	iap_src_addr_not_mapped,
	iap_dst_addr_not_mapped,
	iap_count_error,
	iap_invalid_sector,
	iap_sector_not_blank,
	iap_sector_not_prepared,
	iap_compare_error,
	iap_busy
} lpc17_iap_status;

typedef struct {
	unsigned long offset;
	unsigned long size;
} lpc17_iap_block_list;

/* Return the number of sectors */
unsigned long lpc17_iap_get_sectors(void);

/* Return the FLASH size */
unsigned long lpc17_iap_get_size(void);

/* Return a list of block addresses and sizes */
const lpc17_iap_block_list *lpc17_iap_get_block_list(void);

/* Prepare sectors for erase or write */
lpc17_iap_status lpc17_iap_prepare_sectors(unsigned long start,
	unsigned long end);

/* Copy RAM to FLASH */
lpc17_iap_status lpc17_iap_ram_to_flash(unsigned long dst,
	unsigned long src, unsigned long bytes);

/* Erase sectors */
lpc17_iap_status lpc17_iap_erase_sectors(unsigned long start,
	unsigned long end);

/* Blank check sectors */
lpc17_iap_status lpc17_iap_blank_check_sectors(unsigned long start,
	unsigned long end, unsigned long *bad_addr, unsigned long *bad_data);

/* Read part identification number */
unsigned long lpc17_iap_read_part_id_num(void);

/* Read boot code version */
unsigned long lpc17_iap_read_boot_code_version(void);

/* Read device serial number */
void lpc17_iap_read_serial_num(unsigned long sn[4]);

/* Compare data */
lpc17_iap_status lpc17_iap_compare(unsigned long dst, unsigned long src,
	unsigned long bytes, unsigned long *mis_addr);

/* Re-invoke ISP */
void lpc17_iap_reinvoke_isp(void);

/* Initialize IAP library - call this first */
void lpc17_iap_init(unsigned clkrate);

#endif /* __LPC17_IAPLIB_H */

