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

#include <asm/arch/lpc17_iaplib.h>

/* IAP function pointer */
#define IAP_LOCATION	0x1FFF1FF1
typedef void (*lpc178x_iap) (unsigned long *, unsigned long *);
static lpc178x_iap lpc178x_iap_entry;

/* IAP commands */
typedef enum {
	iap_cmd_prep_sectors = 50,
	iap_cmd_ram_to_flash,
	iap_cmd_erase_sectors,
	iap_cmd_blank_check_sectors,
	iap_cmd_read_part_id,
	iap_cmd_read_boot_code_version,
	iap_cmd_read_device_sn,
	iap_cmd_compare,
	iap_cmd_reinvoke_isp
} iap_command;

static unsigned long iap_num_sectors;
static unsigned long iap_flash_size;
static unsigned long iap_clkrate; /* In KHz */

static const lpc17_iap_block_list iap_blocks[] = {
	{0x00000000, 0x00001000},
	{0x00001000, 0x00001000},
	{0x00002000, 0x00001000},
	{0x00003000, 0x00001000},
	{0x00004000, 0x00001000},
	{0x00005000, 0x00001000},
	{0x00006000, 0x00001000},
	{0x00007000, 0x00001000}, /* 32K part ends here */
	{0x00008000, 0x00001000},
	{0x00009000, 0x00001000},
	{0x0000A000, 0x00001000},
	{0x0000B000, 0x00001000},
	{0x0000C000, 0x00001000},
	{0x0000D000, 0x00001000},
	{0x0000E000, 0x00001000},
	{0x0000F000, 0x00001000}, /* 64K part ends here */
	{0x00010000, 0x00008000},
	{0x00018000, 0x00008000}, /* 128K part ends here */
	{0x00020000, 0x00008000},
	{0x00028000, 0x00008000},
	{0x00030000, 0x00008000},
	{0x00038000, 0x00008000}, /* 256K part ends here */
	{0x00040000, 0x00008000},
	{0x00048000, 0x00008000},
	{0x00050000, 0x00008000},
	{0x00058000, 0x00008000},
	{0x00060000, 0x00008000},
	{0x00068000, 0x00008000},
	{0x00070000, 0x00008000},
	{0x00078000, 0x00008000} /* 512K part ends here */
};

/* Device specific ID coding (information only) */
#define LPC1774_DEVID	0x27011132
#define LPC1776_DEVID	0x27191F43
#define LPC1777_DEVID	0x27193747
#define LPC1778_DEVID	0x27193F47
#define LPC1785_DEVID	0x281D1743
#define LPC1786_DEVID	0x281D1F43
#define LPC1787_DEVID	0x281D3747
#define LPC1788_DEVID	0x281D3F47

static unsigned long iap_commands[5];
static unsigned long iap_results[5];

/* Return the number of sectors */
unsigned long lpc17_iap_get_sectors(void)
{
	return iap_num_sectors;
}

/* Return the FLASH size */
unsigned long lpc17_iap_get_size(void)
{
	return iap_flash_size;
}

/* Return a list of block addresses and sizes */
const lpc17_iap_block_list *lpc17_iap_get_block_list(void)
{
	return iap_blocks;
}

/* Prepare sectors for erase or write */
lpc17_iap_status lpc17_iap_prepare_sectors(unsigned long start,
	unsigned long end)
{
	iap_commands[0] = iap_cmd_prep_sectors;
	iap_commands[1] = start;
	iap_commands[2] = end;

	lpc178x_iap_entry(iap_commands, iap_results);

	return iap_results[0];
}

/* Copy RAM to FLASH */
lpc17_iap_status lpc17_iap_ram_to_flash(unsigned long dst, unsigned long src,
	unsigned long bytes)
{
	iap_commands[0] = iap_cmd_ram_to_flash;
	iap_commands[1] = dst;
	iap_commands[2] = src;
	iap_commands[3] = bytes;
	iap_commands[4] = iap_clkrate;

	lpc178x_iap_entry(iap_commands, iap_results);

	return iap_results[0];
}

/* Erase sectors */
lpc17_iap_status lpc17_iap_erase_sectors(unsigned long start,
	unsigned long end)
{
	iap_commands[0] = iap_cmd_erase_sectors;
	iap_commands[1] = start;
	iap_commands[2] = end;
	iap_commands[3] = iap_clkrate;

	lpc178x_iap_entry(iap_commands, iap_results);

	return iap_results[0];
}

/* Blank check sectors */
lpc17_iap_status lpc17_iap_blank_check_sectors(unsigned long start,
	unsigned long end, unsigned long *bad_addr, unsigned long *bad_data)
{
	iap_commands[0] = iap_cmd_blank_check_sectors;
	iap_commands[1] = start;
	iap_commands[2] = end;
	iap_commands[3] = iap_clkrate;

	lpc178x_iap_entry(iap_commands, iap_results);

	*bad_addr = iap_results[1];
	*bad_data = iap_results[2];

	return iap_results[0];
}

/* Read part identification number */
unsigned long lpc17_iap_read_part_id_num(void)
{
	iap_commands[0] = iap_cmd_read_part_id;

	lpc178x_iap_entry(iap_commands, iap_results);

	return iap_results[1];
}

/* Read boot code version */
unsigned long lpc17_iap_read_boot_code_version(void)
{
	iap_commands[0] = iap_cmd_read_boot_code_version;

	lpc178x_iap_entry(iap_commands, iap_results);

	return iap_results[1] & 0xFFFF;
}

/* Read device serial number */
void lpc17_iap_read_serial_num(unsigned long sn[4])
{
	iap_commands[0] = iap_cmd_read_device_sn;

	lpc178x_iap_entry(iap_commands, iap_results);
}

/* Compare data */
lpc17_iap_status iap_compare(unsigned long dst, unsigned long src,
	unsigned long bytes, unsigned long *mis_addr)
{
	iap_commands[0] = iap_cmd_compare;
	iap_commands[1] = dst;
	iap_commands[2] = src;
	iap_commands[3] = bytes;

	lpc178x_iap_entry(iap_commands, iap_results);

	*mis_addr = iap_results[1];

	return iap_results[0];
}

/* Re-invoke ISP */
void lpc17_iap_reinvoke_isp(void)
{
	iap_commands[0] = iap_cmd_reinvoke_isp;

	/* Doesn't return */
	lpc178x_iap_entry(iap_commands, iap_results);
}

/* Initialize IAP library - call this first */
void lpc17_iap_init(unsigned clkrate)
{
	unsigned long val;

	iap_clkrate = clkrate;

	lpc178x_iap_entry = (lpc178x_iap) IAP_LOCATION;

	/* Read part ID first to determine size of FLASH */
	val = lpc17_iap_read_part_id_num();

	/* Decode part ID to get number of sectors and size */
	if ((val & 0x08000000) != 0) {
		/* LPC178x */
		if ((val & 0x00000004) != 0) {
			/* LPC1787, LPC1788 */
			iap_flash_size = 512 * 1024;
			iap_num_sectors = 30;
		} else {
			/* LPC1785, LPC1786 */
			iap_flash_size = 256 * 1024;
			iap_num_sectors = 22;
		}
	} else {
		/* LPC177x */
		if ((val & 0x00000004) != 0) {
			/* LPC1777, LPC1778 */
			iap_flash_size = 512 * 1024;
			iap_num_sectors = 30;
		} else if ((val & 0x00000002) != 0) {
			/* LPC1776 */
			iap_flash_size = 256 * 1024;
			iap_num_sectors = 22;
		} else {
			/* LPC1774 */
			iap_flash_size = 128 * 1024;
			iap_num_sectors = 18;
		}
	}
}

