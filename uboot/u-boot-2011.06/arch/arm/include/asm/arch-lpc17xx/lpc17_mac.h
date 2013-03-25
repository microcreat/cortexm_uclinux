#ifndef __LPC17_MAC_H
#define __LPC17_MAC_H

/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx MAC (ethernet) support
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

/*
 * MAC block registers
 */
#define MAC_MAC1		LPC17_ENET(0x000)
#define MAC_MAC2		LPC17_ENET(0x004)
#define MAC_IPGT		LPC17_ENET(0x008)
#define MAC_IPGR		LPC17_ENET(0x00C)
#define MAC_CLRT		LPC17_ENET(0x010)
#define MAC_MAXF		LPC17_ENET(0x014)
#define MAC_SUPP		LPC17_ENET(0x018)
#define MAC_TEST		LPC17_ENET(0x01C)
#define MAC_MCFG		LPC17_ENET(0x020)
#define MAC_MCMD		LPC17_ENET(0x024)
#define MAC_MADR		LPC17_ENET(0x028)
#define MAC_MWTD		LPC17_ENET(0x02C)
#define MAC_MRDD		LPC17_ENET(0x030)
#define MAC_MIND		LPC17_ENET(0x034)
#define MAC_SA0			LPC17_ENET(0x040)
#define MAC_SA1			LPC17_ENET(0x044)
#define MAC_SA2			LPC17_ENET(0x048)
#define MAC_COMMAND		LPC17_ENET(0x100)
#define MAC_STATUS		LPC17_ENET(0x104)
#define MAC_RXDESC		LPC17_ENET(0x108)
#define MAC_RXSTATUS		LPC17_ENET(0x10C)
#define MAC_RXDESCNUM		LPC17_ENET(0x110)
#define MAC_RXPRODIDX		LPC17_ENET(0x114)
#define MAC_RXCONSIDX		LPC17_ENET(0x118)
#define MAC_TXDESC		LPC17_ENET(0x11C)
#define MAC_TXSTATUS		LPC17_ENET(0x120)
#define MAC_TXDESCNUM		LPC17_ENET(0x124)
#define MAC_TXPRODIDX		LPC17_ENET(0x128)
#define MAC_TXCONSIDX		LPC17_ENET(0x12C)
#define MAC_TSV0		LPC17_ENET(0x158)
#define MAC_TSV1		LPC17_ENET(0x15C)
#define MAC_RSV			LPC17_ENET(0x160)
#define MAC_FLOWCTRLCNTR	LPC17_ENET(0x170)
#define MAC_FLOWCTRLSTS		LPC17_ENET(0x174)
#define MAC_RXFILTCTRL		LPC17_ENET(0x200)
#define MAC_RXFILTWOLSTS	LPC17_ENET(0x204)
#define MAC_TXFILTWOLCLR	LPC17_ENET(0x208)
#define MAC_HASHFLTRL		LPC17_ENET(0x210)
#define MAC_HASHFLTRH		LPC17_ENET(0x214)
#define MAC_INTSTAT		LPC17_ENET(0xFE0)
#define MAC_INTENAB		LPC17_ENET(0xFE4)
#define MAC_INTCLR		LPC17_ENET(0xFE8)
#define MAC_INTSET		LPC17_ENET(0xFEC)
#define MAC_POWERDOWN		LPC17_ENET(0xFF4)
#define MAC_MODULEID		LPC17_ENET(0xFFC)

#endif /* __LPC17_MAC_H */

