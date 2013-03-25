/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx FLASH support for u-boot
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
#include <asm/arch/lpc17_iaplib.h>
#include <asm/arch/lpc17_clocks.h>

#define PROGRAM_TIMEOUT 0x80

/*
 * Note this driver uses a small 256 byte region at the start of IRAM for
 * loacl buffer storage.
 */

flash_info_t flash_info[CONFIG_SYS_MAX_FLASH_BANKS];
static const lpc17_iap_block_list *pbl;
unsigned long board_flash_id[CONFIG_SYS_MAX_FLASH_BANKS];

/*
 * Initialize FLASH
 */
ulong chip_flash_init (void)
{
	int i, mb;

	/* Clock in is CPU in KHz */
	lpc17_iap_init(lpc17_get_cpu_rate() / 1000);
	mb = lpc17_iap_get_sectors();
	if (mb > CONFIG_CHIP_FLASH_FLASH_SECT) {
		printf("CONFIG_SYS_MAX_FLASH_SECT too small (%d)!\n",
			CONFIG_CHIP_FLASH_FLASH_SECT);
		printf("%d sectors detected\n", mb);
		return 0;
	}

	/* Only 1 bank with multiple sectors */
	flash_info[0].size = lpc17_iap_get_size();
	flash_info[0].flash_id = lpc17_iap_read_part_id_num() &
		FLASH_VENDMASK;
	flash_info[0].sector_count = lpc17_iap_get_sectors();
	memset(flash_info[0].protect, 0, mb);

	/* chip flash */
	pbl = lpc17_iap_get_block_list();
	for (i = 0; i < mb; i++) {
		flash_info[0].start[i] = CONFIG_SYS_FLASH_BASE +
			pbl[i].offset;
	}

	return lpc17_iap_get_size();
}

ulong flash_init (void)
{
    int i, mb;
	unsigned long type_id,vendor_id,flash_id;

	mb = CONFIG_NORFLASH_MAX_FLASH_SECT;
	
#ifdef CONFIG_S29GL128N    /* NOR FLASH */	
    __raw_writew(0x00aa, (CONFIG_NORFLASH_BASE | (0x555 << 1)));	
    __raw_writew(0x0055, (CONFIG_NORFLASH_BASE | (0x2AA << 1)));	
    __raw_writew(0x0090, (CONFIG_NORFLASH_BASE | (0x555 << 1)));	
    type_id = __raw_readw((CONFIG_NORFLASH_BASE | (0x0001 << 1)));	
    vendor_id = __raw_readw((CONFIG_NORFLASH_BASE | (0x000E << 1)));	
    __raw_writew(0x00aa, (CONFIG_NORFLASH_BASE | (0x555 << 1)));	
    __raw_writew(0x0055, (CONFIG_NORFLASH_BASE | (0x2AA << 1)));	
    __raw_writew(0x00f0, (CONFIG_NORFLASH_BASE | (0x555 << 1)));	
    flash_id = (type_id << 16) | vendor_id;	
    if( !( 0x227e2221 == flash_id) )		
	    printf("nor flash id is erro!\n");	
    else        
	    {  
	    flash_info[CONFIG_NORFLASH_ID].flash_id = flash_id & FLASH_VENDMASK;
	    flash_info[CONFIG_NORFLASH_ID].size = CONFIG_NORFLASH_SIZE;        
	    flash_info[CONFIG_NORFLASH_ID].sector_count = CONFIG_NORFLASH_MAX_FLASH_SECT;		
	    }
#endif
    memset(flash_info[CONFIG_NORFLASH_ID].protect, 0, mb);

    for (i = 0; i < mb; i++) 
		{		
		flash_info[CONFIG_NORFLASH_ID].start[i] = CONFIG_NORFLASH_BASE + i*0x10000;	
		}

    return flash_info[CONFIG_NORFLASH_ID].size;
}

/*
 * Display FLASH info
 */
 
void chip_flash_print_info (flash_info_t *info)
{
	int i;
	unsigned long sn[4];

    printf("NXP LPC17xx internal FLASH\n");

    printf ("  %ld KB in %d Sectors\n", info->size >> 10,
	    info->sector_count);

    printf ("  LPC17 Part ID: %08x\n",
	    (int) lpc17_iap_read_part_id_num());

    lpc17_iap_read_serial_num(sn);
    printf ("  LPC17 Unique ID: %08x%08x%08x%08x\n", (int) sn[0],
	    (int) sn[1], (int) sn[2], (int) sn[3]);

    printf ("  Sector Start Addresses:");
    for (i = 0; i < info->sector_count; i++) {
	    if ((i % 5) == 0) {
		    printf ("\n   ");
	    }
	    printf (" %08lX%s", info->start[i],
		    info->protect[i] ? " (RO)" : "     ");
    	}

	printf ("\n");
}

void flash_print_info (flash_info_t *info)
{
    int i;
	
	if(flash_info[CONFIG_NORFLASH_ID].flash_id == info->flash_id)
	    {
	    printf("NOR FLASH\n");

        printf ("  %ld KB in %d Sectors\n", info->size >> 10,
	        info->sector_count);

        printf ("  NOR FLASH Part ID: %08x\n",(unsigned int)(info->flash_id));

        printf ("  Sector Start Addresses:");
        for (i = 0; i < info->sector_count; i++) {
	        if ((i % 5) == 0) {
		        printf ("\n   ");
	        }
	        printf (" %08lX%s", info->start[i],
		        info->protect[i] ? " (RO)" : "     ");
    	    }

	    printf ("\n");
    	}
}
/*
 * Erase FLASH sectors
 */
int chip_flash_erase (flash_info_t *info, int s_first, int s_last)
{
	unsigned long badaddr, baddata;
	unsigned long first = (unsigned long) s_first;
	unsigned long last = (unsigned long) s_last;

	if ((first < 0) || (first >= flash_info[0].sector_count) ||
		(last < first) || (last >= flash_info[0].sector_count)) {
		printf("Invalid sector range, allowed 0 to %d\n",
			flash_info[0].sector_count - 1);
		return ERR_NOT_ERASED;
	}

	printf ("Erasing %d sectors starting at sector %2d.\n",
		s_last - s_first + 1, s_first);

	if (lpc17_iap_prepare_sectors(first, last) != iap_cmd_success) {
		printf("Error perparing erase\n");
		return ERR_NOT_ERASED;
	}

	if (lpc17_iap_erase_sectors(first, last) != iap_cmd_success) {
		printf("Error erasing FLASH\n");
		return ERR_NOT_ERASED;
	}

	if (lpc17_iap_blank_check_sectors(first, last, &badaddr, &baddata) ==
		iap_sector_not_blank) {
		printf("Error validating erase\n");
		return ERR_NOT_ERASED;
	}

	return ERR_OK;
}

int flash_erase (flash_info_t *info, int s_first, int s_last)
{
    unsigned long flash_base,cnt;
	unsigned long first = (unsigned long) s_first;	
	unsigned long last = (unsigned long) s_last;
	unsigned long sector_num = s_last - s_first + 1;

	printf("erase nor flash!\n");

	if ((first < 0) || (first >= flash_info[CONFIG_NORFLASH_ID].sector_count) ||		
		(last < first) || (last >= flash_info[CONFIG_NORFLASH_ID].sector_count)) 
		{		
		printf("Invalid sector range, allowed 0 to %d\n",			
			flash_info[CONFIG_NORFLASH_ID].sector_count - 1);		
		return ERR_NOT_ERASED;	
		}	

	if( ((last > CONFIG_NORFLASH_MAX_FLASH_SECT) && 		
		(first < CONFIG_NORFLASH_MAX_FLASH_SECT)))	
		{	    
		printf("Invalid sector range, allowed 0 to 128\n"); 		
		printf("Is not support 0 to 40 or 20 to 120\n");		
		return ERR_NOT_ERASED;	
		}	

	printf ("Erasing %d sectors starting at sector %2d.\n",		
		s_last - s_first + 1, s_first);
		
	printf("section is %d\n",(int)(sector_num));		
	for(cnt = 0; cnt < sector_num; cnt++)			
		{			
		flash_base = cnt * 0x10000;						
		__raw_writew(0x00aa, (CONFIG_NORFLASH_BASE | (0x555 << 1)));		    
		__raw_writew(0x0055, (CONFIG_NORFLASH_BASE | (0x2AA << 1)));		    
		__raw_writew(0x0080, (CONFIG_NORFLASH_BASE | (0x555 << 1)));			
		__raw_writew(0x00aa, (CONFIG_NORFLASH_BASE | (0x555 << 1)));		    
		__raw_writew(0x0055, (CONFIG_NORFLASH_BASE | (0x2AA << 1)));			
		__raw_writew(0x0030, (CONFIG_NORFLASH_BASE | flash_base));			
		udelay(500000);			
		printf(".");
		}

	return ERR_OK;
}
	
	

static unsigned long chip_find_sector(unsigned long address) {
	int i = 0;

	while (i < flash_info[0].sector_count) {
		if ((address >= flash_info[0].start[i]) &&
			(address < (flash_info[0].start[i] + pbl[i].size)))
			return (unsigned long) i;
		else
			i++;
	}

	return -1;
}

/*
 * Copy memory buffer to FLASH
 */
int chip_write_buff (flash_info_t *info, uchar *src, ulong addr, ulong cnt)
{
	uchar *pdst, *psrc;
	ulong bytes = cnt;
	unsigned long sect;
	lpc17_iap_status st;
	void *ilcl = (void *) 0x10000000;

	/* Write size must be on a 256 byte boundary */
	if (cnt % 256) {
		printf ("FLASH destination address must be 256 byte "
			"aligned\n");
		return ERR_PROG_ERROR;
	}

	if (((ulong) addr % 256) != 0) {
		printf ("Destination address must be 256 byte aligned\n");
		return ERR_PROG_ERROR;
	}

	if (((ulong) src & 0x3) != 0) {
		printf ("Source address must be 32-bit aligned\n");
		return ERR_PROG_ERROR;
	}

	if (addr > flash_info[0].size - cnt) {
		printf ("Write range exceeds end of FLASH\n");
		return ERR_PROG_ERROR;
	}

	/* Check that area is erased */
	pdst = (uchar *) addr;
	while (bytes-- > 0) {
		if (*pdst != 0xFF) {
			printf("FLASH is not blank\n");
			return ERR_NOT_ERASED;
		}

		pdst++;
	}

	bytes = cnt;
	pdst = (uchar *) addr;
	psrc = src;

	printf("Writing %d bytes from %x to %x, please be patient...\n",
		(int) bytes, (unsigned int) src, (unsigned int) addr);

	/* Write data in 256 byte chunks */
	while (bytes > 0) {
		sect = chip_find_sector(addr);

		if (lpc17_iap_prepare_sectors(sect, sect) !=
			iap_cmd_success) {
			printf ("Error preparing FLASH for word write\n");
			return ERR_PROG_ERROR;
		}

		/* Copy RAM to FLASH */
		memcpy(ilcl, (void *) src, 256);
		st = lpc17_iap_ram_to_flash(addr, (unsigned long ) ilcl, 256);
		if (st != iap_cmd_success) {
			printf ("Error writing word to FLASH (%d)\n", st);
			return ERR_PROG_ERROR;
		}

		bytes -= 256;
		src += 256;
		addr += 256;
	}

	/* Verify */
	while (cnt-- > 0) {
		if (*psrc != *pdst) {
			printf ("Write error in FLASH validation\n");
			return ERR_PROG_ERROR;
		}

		psrc++;
		pdst++;
	}

	return 0;
}

int write_buff (flash_info_t *info, uchar *src, ulong addr, ulong cnt)
{
	uint32_t *base, *end;    
	uint16_t *p, *s;  
	ulong bytes = cnt;
	uint16_t word, status, status1;	
	uint32_t time_out;
	
	//if(flash_info[CONFIG_NORFLASH_ID].flash_id == info->flash_id)		
		{		
		printf ("nor flash write!\n");		
		printf("Writing %d bytes from %x to %x, please be patient...\n",		
			(int) bytes, (unsigned int) src, (unsigned int) addr);		

		if (addr < info->start[0]	    
			|| (addr + cnt) > (info->start[0] + info->size)	    
			|| (addr + cnt) < addr) 
			{		    
			printf("Error: invalid address range\n");		    
			return ERR_INVAL;	    
			}	    

		if (addr & 1 || cnt & 1 || (unsigned int)src & 1) 
			{		    
			printf("Error: misaligned source, destination or count\n");		    
			return ERR_ALIGN;	    
			}        

                addr -= CONFIG_NORFLASH_BASE;
		end = (uint32_t *)(addr + cnt);		        
		for (p = (uint16_t *)(addr), s = (uint16_t *)(src); p < end; p++, s++) 			
			{		    
			word = *s;		 
			__raw_writew(0x00aa, (CONFIG_NORFLASH_BASE | (0x555 << 1)));              
			__raw_writew(0x0055, (CONFIG_NORFLASH_BASE | (0x2aa << 1)));              
			__raw_writew(0x00a0, (CONFIG_NORFLASH_BASE | (0x555 << 1)));  			
			__raw_writew(word,   (CONFIG_NORFLASH_BASE | (uint32_t)p));						
			time_out = PROGRAM_TIMEOUT;			
			while( time_out-- > 0 )				
				{				
				status  = __raw_readw(CONFIG_NORFLASH_BASE | (uint32_t)p);				
				status1 = __raw_readw(CONFIG_NORFLASH_BASE | (uint32_t)p);								
				if ( (status == status1) && (status == word) )					
					{
					time_out = 0;
					}			
				}
			}						
		}
	return 0;
}
