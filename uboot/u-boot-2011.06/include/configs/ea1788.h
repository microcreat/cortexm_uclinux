#ifndef __EA1788_H
#define __EA1788_H

/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: Board specific u-boot configuration for the EA1788 board
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

//#define DEBUG 

/*
 * Embed the calculated checksum into the U-Boot image
 * (needed for execution of images from LPC178x eNVM).
*/
#define CONFIG_LPC178X_FCG

/*
 * This should be setup to the board specific rate for the external oscillator
 */
#define CONFIG_LPC17_OSC_RATE		12000000

/*
 * SYSCLK setup. Set the CONFIG_LPC17_PLL0_USE_EXTOSC define to 1 to
 * use the external oscillator for the SYSCLK rate. Otherwise, the internal
 * oscillator is used as SYSCLK.
 */
#define CONFIG_LPC17_PLL0_USE_EXTOSC	1

/*
 * Set CONFIG_LPC17_PLL0_ENABLE to 1 to enable PLL0. If PLL0 is enabled,
 * the values of CONFIG_LPC17_PLL0_M and CONFIG_LPC17_PLL0_P must also
 * be setup to configure the PLL0 rate based on the selected input clock.
 * See the LCP177x/lpc178x User's Manual for information on setting these
 * values correctly. SYSCLK is used as the PLL0 input clock.
 * 
 * If CONFIG_LPC17_PLL0_USE_EXTOSC==1
 *  PLL0_CLK_OUT = CONFIG_LPC17_PLL0_M * CONFIG_LPC17_OSC_RATE
 * else
 *  PLL0_CLK_OUT = CONFIG_LPC17_PLL0_M * 12000000 (internal oscillator)
 * 
 * PLL0_FCCO mist be between 156MHz and 320MHz
 *  where PLL0_FFC0 = PLL0_CLK_OUT * 2 * CONFIG_LPC17_PLL0_P
 * PLL0_CLK_OUT must be between 9.75MHz and 160MHz
 */
#define CONFIG_LPC17_PLL0_ENABLE	1
#define CONFIG_LPC17_PLL0_M		9
#define CONFIG_LPC17_PLL0_P		1

/*
 * Set CONFIG_LPC17_PLL1_ENABLE to 1 to enable PLL1. If PLL1 is enabled,
 * the values of CONFIG_LPC17_PLL1_M and CONFIG_LPC17_PLL1_P must also
 * be setup to configure the PLL1 rate based on the selected input clock.
 * 
 * PLL1_CLK_OUT = CONFIG_LPC17_PLL1_M * CONFIG_LPC17_OSC_RATE
 * PLL1_FFC0 = PLL1_CLK_OUT * 2 * CONFIG_LPC17_PLL1_P
 * 
 * PLL1_FCCO mist be between 156MHz and 320MHz
 * PLL1_CLK_OUT must be between 9.75MHz and 160MHz
 *  48MHz for USB, or anything if routed to the CLKOUT pin
 */
#define CONFIG_LPC17_PLL1_ENABLE	1
#define CONFIG_LPC17_PLL1_M		4
#define CONFIG_LPC17_PLL1_P		2

/*
 * Set CONFIG_LPC17_PLL0_FOR_CPU to 1 to use the PLL0 out for the CPU divider
 * clock. If not set, SYSCLK is used as the CPU divider clock. Select a value
 * between 1 and 31 for the CONFIG_LPC17_CPU_DIV value. The CPU clock will be
 * either the PLL0 clock or the SYSCLK divided by the divider.
 */
#define CONFIG_LPC17_PLL0_FOR_CPU	1
#define CONFIG_LPC17_CPU_DIV		1

/*
 * If using USB, PLL1 is used for the USB clock and needs to be 48MHz. Set
 * this value to the divider from the PLL1 clock rate to get 48MHz. If not
 * using USB, set this to 0. Only dividers of 4 and 6 are supported, which
 * map to PLL1 rates of 192MHz and 288MHz, respectively.
 */
#define CONFIG_LPC17_USB_DIV		4

/*
 * The EMC clock is at the CPU rate or 1/2 the CPU rate. Set this value to 1
 * to use half the CPU clock for the EMC rate
*/
#define CONFIG_LPC17_EMC_HALFCPU	1

/*
 * Peripheral clock selector. This divider, between 1 and 31, is used to
 * generate the clock to the peripherals. The rate is divided from the CPU
 * clock.
 */
#define CONFIG_LPC17_PCLK_DIV		2

/*
 * Number of FLASH clocks for the FLASH accelerator, must be between 1 and
 * 6. See the User's Manual for the correct setting based on your CPU clock
 * rate.
 */
#define CONFIG_LPC17_FLASH_CLOCKS	6

/*
 * select the UART used on the board. Five UARTs are available labelled
 * UART0 to UART4. Select 0 to 4 for the UART used for uboot.
 */
#define CONFIG_LPC17_UART_BOOT		0

/*
 * Linux machine type, reuse the 24xx machine ID
 */
#define CONFIG_LPC17XX_MACHID		MACH_TYPE_LPC1788

/*
 * LPC1788 built-in FLASH
 */
#define CONFIG_CHIP_FLASH	
#define CONFIG_CMD_CHIP_FLASH	        
#define CONFIG_SYS_MAX_FLASH_BANKS      2
#define CONFIG_CHIP_FLASH_BANKS	        1
#define CONFIG_CHIP_FLASH_ID	        0 
#define CONFIG_CHIP_FLASH_FLASH_SECT    32
#define CONFIG_SYS_FLASH_BASE		    0x00000000

/* 
 * norflash S29GL128N 
 */
/* lpc17xx     S29GL128N
    addr1 ===> addr0 */ 
//#define CONFIG_CMD_NORFLASH	
//#define CONFIG_NORFLASH
#define CONFIG_NORFLASH_BANKS	        1
#define CONFIG_ADDR0_OFF                1    
#define CONFIG_S29GL128N                1  
#define CONFIG_NORFLASH_ID	            1
#define CONFIG_NORFLASH_BASE           0x80000000
#define CONFIG_NORFLASH_SIZE           0x01000000
#define CONFIG_NORFLASH_MAX_FLASH_SECT 128  

#define CONFIG_SYS_MAX_FLASH_SECT      CONFIG_CHIP_FLASH_FLASH_SECT

/*
 * CPU options
 */
#define CONFIG_ARM_THUMB		1
#define CONFIG_LPC17XX
#define CONFIG_SYS_NO_ICACHE		1
#define CONFIG_SYS_NO_DCACHE		1

/*
 * If the CONFIG_USE_BOARD_MPU_TABLE is defined, a MPU setup table needs
 * to be setup for the board that initializes the MPU permissions. If
 * this is undefined, the MPU will be setup with RW for the entire address
 * range.
 */
#define CONFIG_USE_BOARD_MPU_TABLE

/*
 * Needed for board init
 */
#undef CONFIG_SKIP_LOWLEVEL_INIT

/*
 * Use red LED for status
 */
#define STATUS_LED_RED

/*
 * SDRAM physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM_1			0xA0000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE		0x02000000 /* 32 MB SDRAM */
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1

/*
 * 2KHz clock tick
 */
#define	CONFIG_SYS_HZ			1000
#define CONFIG_SYS_SYS_CLK_FREQ		CONFIG_SYSPLL_CLK_RATE

/*
 * Address and size of stored environment Data, the environment
 */
#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_ADDR			(CONFIG_SYS_FLASH_BASE + 0x068000)
#define CONFIG_ENV_SIZE			0x018000

//#define CONFIG_BOOTARGS		"mem=32M console=ttyS0,115200"
//#define CONFIG_BOOTARGS		"lpc178x_platform=ea-lpc1788 console=ttyS0,115200 panic=10 ip=10.1.10.214:::ea-lpc1788:eth0:off mem=16M ethaddr=C0:B1:3C:88:88:88"

//#define CONFIG_BOOTARGS		"init=/bin/sh console=ttyS0,115200 mem=32M"
//#define CONFIG_BOOTCOMMAND  "cp.w 80000000 a0000100 0x140000;" \ 
//	                        "bootm a0000100"

//#define CONFIG_BOOTARGS		"mem=32M console=ttyS0,115200 init=/dev/mtdblock1 rootfstype=jffs2 rw"
#define CONFIG_BOOTARGS		"mem=32M console=ttyS0,115200 root=/dev/mtdblock1 init=linuxrc rootfstype=jffs2 rw"
#define CONFIG_BOOTCOMMAND  "tftp a0000100 uImage;" \ 
	                        "bootm a0000100"

/*
 * Area and size for malloc
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 1024 * 1024)

/*
 * No support for IRQs
 */
#undef CONFIG_USE_IRQ

/*
 * Stack size and global data size
 */
#define CONFIG_STACKSIZE		(32 * 1024)
#define CONFIG_SYS_GBL_DATA_SIZE	128

/*
 * ATAG support
 */
#define CONFIG_CMDLINE_TAG		1
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_INITRD_TAG		1

/*
 * System UART selection, valid selections include 0, 1, 2, 3
 */
#define CONFIG_LPC17XX_UART		0 /* 0 - 3 */
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{9600, 19200, 38400, 57600, 115200}

/*
 * Default load address for programs
 */
#define CONFIG_SYS_LOAD_ADDR		0xA0100000

/*
 * Default boot delay is 3 seconds
 */
#define CONFIG_BOOTDELAY		3
#define CONFIG_ZERO_BOOTDELAY_CHECK

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

/*
 * Prompt and command buffer setup
 */
#define CONFIG_SYS_LONGHELP
#define	CONFIG_SYS_CBSIZE		256
#define	CONFIG_SYS_PROMPT		"uboot> "
#define	CONFIG_SYS_PBSIZE      (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
#define	CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

/*
 * Default range for the memory tests
 */
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		(PHYS_SDRAM_1 + 0x01000000)

/*
 * Support for NAND FLASH
 */
//#define CONFIG_CMD_NAND
//#define CONFIG_SYS_MAX_NAND_DEVICE	1
//#define CONFIG_SYS_NAND_BASE		0x90000000

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/*
 * Support for various capabilities
 */
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMDLINE_EDITING
#define CONFIG_SYS_LOADS_BAUD_CHANGE

/*
 * Network setup
 */
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.1.149
#define CONFIG_SERVERIP		192.168.1.101
#define CONFIG_GATEWAYIP	192.168.1.1
#define CONFIG_ETHADDR		00:E0:0C:00:00:01

#define CONFIG_BOOTFILE		uImage
//#define CONFIG_LOADADDR		0xA0100000
#define CONFIG_LOADADDR		0xA0008000
#define CONFIG_ROOTPATH		/home/user/dev/rootfs

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTFILESIZE

/*
 * Other commands
 */
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ENV
#define CONFIG_CMD_ECHO
#define CONFIG_CMD_RUN
#define CONFIG_CMD_LOADB
#define CONFIG_CMD_LOADS
#define CONFIG_CMD_SAVES
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_PING
#define CONFIG_CMD_NET
#define CONFIG_CMD_SAVEENV
#define CONFIG_CMD_ELF
#undef CONFIG_CMD_MISC
#define CONFIG_MISC_INIT_R

/*
 * Initial data areas
 */
#define CONFIG_SYS_INIT_RAM_ADDR 0x10000000
#define CONFIG_SYS_INIT_RAM_SIZE 0x10000
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - \
					GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR	(CONFIG_SYS_INIT_RAM_ADDR + \
	CONFIG_SYS_GBL_DATA_OFFSET)

/*
 * Misc
 */
#define CONFIG_DISPLAY_CPUINFO

#endif /* __EA1788_H */
