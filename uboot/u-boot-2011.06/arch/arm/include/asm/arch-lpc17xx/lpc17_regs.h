#ifndef __LPC17XX_REGS_H
#define __LPC17XX_REGS_H

/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx register addresses
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

#include <config.h>

/*
 * LPC17xx regions
 */
#define LPC17_FLASH_BASE		0x00000000
#define LPC17_SRAM1_BASE		0x10000000
#define LPC17_BOOTROM_BASE		0x1FFF0000
#define LPC17_SRAM2_BASE		0x20000000
#define LPC17_AHB_BASE			0x20080000
#define LPC17_APB_BASE			0x40000000
#define LPC17_EMC_STATIC0		0x80000000
#define LPC17_EMC_STATIC1		0x90000000
#define LPC17_EMC_STATIC2		0x98000000
#define LPC17_EMC_STATIC3		0x9C000000
#define LPC17_EMC_DRAM0			0xA0000000
#define LPC17_EMC_DRAM1			0xB0000000
#define LPC17_EMC_DRAM2			0xC0000000
#define LPC17_EMC_DRAM3			0xD0000000
#define LPC17_M3_PRVBUS			0xE0000000

/*
 * APB peripheral register bases
 */
#define LPC17_WDT(x)			(LPC17_APB_BASE + 0x00000000 + (x))
#define LPC17_TIMER0			(LPC17_APB_BASE + 0x00004000)
#define LPC17_TIMER1			(LPC17_APB_BASE + 0x00008000)
#define LPC17_UART0			(LPC17_APB_BASE + 0x0000C000)
#define LPC17_UART1			(LPC17_APB_BASE + 0x00010000)
#define LPC17_PWM0(x)			(LPC17_APB_BASE + 0x00014000 + (x))
#define LPC17_PWM1(x)			(LPC17_APB_BASE + 0x00018000 + (x))
#define LPC17_I2C0(x)			(LPC17_APB_BASE + 0x0001C000 + (x))
#define LPC17_RTC(x)			(LPC17_APB_BASE + 0x00020000 + (x))
#define LPC17_GPIOINTS(x)		(LPC17_APB_BASE + 0x00028000 + (x))
#define LPC17_PINCON(x)			(LPC17_APB_BASE + 0x0002C000 + (x))
#define LPC17_SSP1(x)			(LPC17_APB_BASE + 0x00030000 + (x))
#define LPC17_ADC(x)			(LPC17_APB_BASE + 0x00034000 + (x))
#define LPC17_CANRAM(x)			(LPC17_APB_BASE + 0x00038000 + (x))
#define LPC17_CANREGS(x)		(LPC17_APB_BASE + 0x0003C000 + (x))
#define LPC17_CANCMN(x)			(LPC17_APB_BASE + 0x00040000 + (x))
#define LPC17_CAN1(x)			(LPC17_APB_BASE + 0x00044000 + (x))
#define LPC17_CAN2(x)			(LPC17_APB_BASE + 0x00048000 + (x))
#define LPC17_I2C1(x)			(LPC17_APB_BASE + 0x0005C000 + (x))
#define LPC17_SSP0(x)			(LPC17_APB_BASE + 0x00088000 + (x))
#define LPC17_DAC(x)			(LPC17_APB_BASE + 0x0008C000 + (x))
#define LPC17_TIMER2			(LPC17_APB_BASE + 0x00090000)
#define LPC17_TIMER3			(LPC17_APB_BASE + 0x00094000)
#define LPC17_UART2			(LPC17_APB_BASE + 0x00098000)
#define LPC17_UART3			(LPC17_APB_BASE + 0x0009C000)
#define LPC17_I2C2(x)			(LPC17_APB_BASE + 0x000A0000 + (x))
#define LPC17_UART4			(LPC17_APB_BASE + 0x000A4000)
#define LPC17_I2S(x)			(LPC17_APB_BASE + 0x000A8000 + (x))
#define LPC17_SSP2(x)			(LPC17_APB_BASE + 0x000AC000 + (x))
#define LPC17_MOTORCTL(x)		(LPC17_APB_BASE + 0x000B8000 + (x))
#define LPC17_QEI(x)			(LPC17_APB_BASE + 0x000BC000 + (x))
#define LPC17_SDCARD(x)			(LPC17_APB_BASE + 0x000C0000 + (x))
#define LPC17_SYSCONT(x)		(LPC17_APB_BASE + 0x000FC000 + (x))

/*
 * AHB peripheral register bases
 */
#define LPC17_DMA(x)			(LPC17_AHB_BASE + 0x00000000 + (x))
#define LPC17_ENET(x)			(LPC17_AHB_BASE + 0x00004000 + (x))
#define LPC17_LCD(x)			(LPC17_AHB_BASE + 0x00008000 + (x))
#define LPC17_USB(x)			(LPC17_AHB_BASE + 0x0000C000 + (x))
#define LPC17_CRC(x)			(LPC17_AHB_BASE + 0x00010000 + (x))
#define LPC17_GPIO(x)			(LPC17_AHB_BASE + 0x00018000 + (x))
#define LPC17_EMCREGS(x)		(LPC17_AHB_BASE + 0x0001C000 + (x))

/*
 * System and clock control registers
 */
#define LPC17_SC_FLASHCFG		LPC17_SYSCONT(0x000)
#define LPC17_SC_PLL0CON		LPC17_SYSCONT(0x080)
#define LPC17_SC_PLL0CFG		LPC17_SYSCONT(0x084)
#define LPC17_SC_PLL0STAT		LPC17_SYSCONT(0x088)
#define LPC17_SC_PLL0FEED		LPC17_SYSCONT(0x08C)
#define LPC17_SC_PLL1CON		LPC17_SYSCONT(0x0A0)
#define LPC17_SC_PLL1CFG		LPC17_SYSCONT(0x0A4)
#define LPC17_SC_PLL1STAT		LPC17_SYSCONT(0x0A8)
#define LPC17_SC_PLL1FEED		LPC17_SYSCONT(0x0AC)
#define LPC17_SC_PCON			LPC17_SYSCONT(0x0C0)
#define LPC17_SC_PCONP			LPC17_SYSCONT(0x0C4)
#define LPC17_SC_EMCCLKSEL		LPC17_SYSCONT(0x100)
#define LPC17_SC_CCLKSEL		LPC17_SYSCONT(0x104)
#define LPC17_SC_USBCLKSEL		LPC17_SYSCONT(0x108)
#define LPC17_SC_CLKSRCSEL		LPC17_SYSCONT(0x10C)
#define LPC17_SC_EXTINT			LPC17_SYSCONT(0x140)
#define LPC17_SC_EXTMODE		LPC17_SYSCONT(0x148)
#define LPC17_SC_EXTPOLAR		LPC17_SYSCONT(0x14C)
#define LPC17_SC_RSID			LPC17_SYSCONT(0x180)
#define LPC17_SC_SCS			LPC17_SYSCONT(0x1A0)
#define LPC17_SC_PCLKSEL		LPC17_SYSCONT(0x1A8)
#define LPC17_SC_CLKOUTCFG		LPC17_SYSCONT(0x1C8)
#define LPC17_SC_RSTCON0		LPC17_SYSCONT(0x1CC)
#define LPC17_SC_RSTCON1		LPC17_SYSCONT(0x1D0)
#define LPC17_SC_EMCDLYCTL		LPC17_SYSCONT(0x1DC)
#define LPC17_SC_EMCCAL			LPC17_SYSCONT(0x1E0)

/*
 * IOCON registers
 */
#define __GRPPIN2OFS(grp, pin)		(((grp) * 128) + ((pin) * 4))
#define LPC17_IOCON(grp, pin)		LPC17_PINCON(__GRPPIN2OFS(grp, pin))

/*
 * Fast GPIO registers
 */
#define LPC17_FIODIR(grp)		LPC17_GPIO((0x00 + (grp) * 0x20))
#define LPC17_FIOMASK(grp)		LPC17_GPIO((0x10 + (grp) * 0x20))
#define LPC17_FIOPIN(grp)		LPC17_GPIO((0x14 + (grp) * 0x20))
#define LPC17_FIOSET(grp)		LPC17_GPIO((0x18 + (grp) * 0x20))
#define LPC17_FIOCLR(grp)		LPC17_GPIO((0x1C + (grp) * 0x20))

/*
 * EMC registers
 */
#define LPC17_EMCCTRL			LPC17_EMCREGS(0x000)
#define LPC17_EMCSTS			LPC17_EMCREGS(0x004)
#define LPC17_EMCCFG			LPC17_EMCREGS(0x008)
#define LPC17_EMCDYCTRL			LPC17_EMCREGS(0x020)
#define LPC17_EMCDYRFSH			LPC17_EMCREGS(0x024)
#define LPC17_EMCDYRDCFG		LPC17_EMCREGS(0x028)
#define LPC17_EMCDYTRP			LPC17_EMCREGS(0x030)
#define LPC17_EMCDYRAS			LPC17_EMCREGS(0x034)
#define LPC17_EMCDYSREX			LPC17_EMCREGS(0x038)
#define LPC17_EMCDYAPR			LPC17_EMCREGS(0x03C)
#define LPC17_EMCDYDAL			LPC17_EMCREGS(0x040)
#define LPC17_EMCDYWR			LPC17_EMCREGS(0x044)
#define LPC17_EMCDYRC			LPC17_EMCREGS(0x048)
#define LPC17_EMCDYRFC			LPC17_EMCREGS(0x04C)
#define LPC17_EMCDYXSR			LPC17_EMCREGS(0x050)
#define LPC17_EMCDYRRD			LPC17_EMCREGS(0x054)
#define LPC17_EMCDYMRD			LPC17_EMCREGS(0x058)
#define LPC17_EMCEXWAIT			LPC17_EMCREGS(0x080)
#define LPC17_EMCDDYCFG(x)		LPC17_EMCREGS(0x100 + ((x) * 0x20))
#define LPC17_EMCDYRASCAS(x)		LPC17_EMCREGS(0x104 + ((x) * 0x20))
#define LPC17_EMCSTCFG(x)		LPC17_EMCREGS(0x200 + ((x) * 0x20))
#define LPC17_EMCSTWWEN(x)		LPC17_EMCREGS(0x204 + ((x) * 0x20))
#define LPC17_EMCSTWOEN(x)		LPC17_EMCREGS(0x208 + ((x) * 0x20))
#define LPC17_EMCSTWRD(x)		LPC17_EMCREGS(0x20C + ((x) * 0x20))
#define LPC17_EMCSTWPAGE(x)		LPC17_EMCREGS(0x210 + ((x) * 0x20))
#define LPC17_EMCSTWWR(x)		LPC17_EMCREGS(0x214 + ((x) * 0x20))
#define LPC17_EMCSTWTURN(x)		LPC17_EMCREGS(0x218 + ((x) * 0x20))

/*
 * Timer block registers
 */
#define LPC17_TIMER_IR(x)		((x) + 0x00)
#define LPC17_TIMER_TCR(x)		((x) + 0x04)
#define LPC17_TIMER_TC(x)		((x) + 0x08)
#define LPC17_TIMER_PR(x)		((x) + 0x0C)
#define LPC17_TIMER_PC(x)		((x) + 0x10)
#define LPC17_TIMER_MCR(x)		((x) + 0x14)
#define LPC17_TIMER_MR0(x)		((x) + 0x18)
#define LPC17_TIMER_MR1(x)		((x) + 0x1C)
#define LPC17_TIMER_MR2(x)		((x) + 0x20)
#define LPC17_TIMER_MR3(x)		((x) + 0x24)
#define LPC17_TIMER_CCR(x)		((x) + 0x28)
#define LPC17_TIMER_CR0(x)		((x) + 0x2C)
#define LPC17_TIMER_CR1(x)		((x) + 0x30)
#define LPC17_TIMER_EMR(x)		((x) + 0x3C)
#define LPC17_TIMER_CTCR(x)		((x) + 0x70)

/*
 * UART block registers
 */
#define LPC17_UART_FIFO_DLL(x)		((x) + 0x00)
#define LPC17_UART_IER_DLM(x)		((x) + 0x04)
#define LPC17_UART_FCR_IIR(x)		((x) + 0x08)
#define LPC17_UART_LCR(x)		((x) + 0x0C)
#define LPC17_UART_MCR(x)		((x) + 0x10)
#define LPC17_UART_LSR(x)		((x) + 0x14)
#define LPC17_UART_MSR(x)		((x) + 0x18)
#define LPC17_UART_SCR(x)		((x) + 0x2C)
#define LPC17_UART_ACR(x)		((x) + 0x20)
#define LPC17_UART_FDI(x)		((x) + 0x28)
#define LPC17_UART_TER(x)		((x) + 0x30)




/*
 * LPC17xx internal and set RTC oscillator rate
*/
#define LPC17_INTOSCRATE		12000000
#define LPC17_RTCOSCRATE		32000
#define LPC17_WDTOSCRATE		500000

/*
 * CPU options
 */
#define LPC17_IRAM_SIZE			(64 * 1024)


#endif /* _LPC17XX_REGISTERS_H */
