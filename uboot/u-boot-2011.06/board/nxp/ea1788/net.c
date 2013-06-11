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

#include <common.h>
#include <command.h>
#include <net.h>
#include <malloc.h>
#include "miiphy.h"
#include <asm/io.h>
#include <asm/arch/hardware.h>
#include <asm/arch/lpc17_regs.h>
#include <asm/arch/lpc17_clocks.h>
#include <asm/arch/lpc17_mac.h>

/* Structure of a TX/RX descriptor */
typedef struct
{
  volatile unsigned long packet;
  volatile unsigned long control;
} TXRX_DESC_T;

/* Structure of a RX status entry */
typedef struct
{
  volatile unsigned long statusinfo;
  volatile unsigned long statushashcrc;
} RX_STATUS_T;

#define USE_PHY_RMII
#define ENET_MAX_TX_PACKETS	8 /* TX locks when using 4 */
#define ENET_MAX_RX_PACKETS	8
#define PHYDEF_PHYADDR		1
#define ENET_MAXF_SIZE		1536
#define DP83848_PHY_STATUS	0x10

/*
 * Buffer storage size, needs space for descriptors, statuses, and data
 * buffers
 */
#define BUFF_SIZE_BYTES		((ENET_MAXF_SIZE * (ENET_MAX_TX_PACKETS + \
				ENET_MAX_RX_PACKETS)) + 512)

static TXRX_DESC_T *pTXDesc;
static unsigned long *pTXStatus;
static unsigned long pTXVBuffs [ENET_MAX_TX_PACKETS];
static TXRX_DESC_T *pRXDesc;
static RX_STATUS_T *pRXStatus;
static unsigned long pRXVBuffs [ENET_MAX_RX_PACKETS];
static unsigned long *ethbuffs;

#define msDelay(x) udelay(x * 1000)

static int lpc17xx_mii_write(long PhyReg, long Value)
{
	long mst = 250;
	int sts = 0;

	/* Write value at PHY address and register */
	__raw_writel((PHYDEF_PHYADDR << 8) | PhyReg, MAC_MADR);
	__raw_writel(Value, MAC_MWTD);

	/* Wait for unbusy status */
	while (mst > 0) {
		if ((__raw_readl(MAC_MIND) & 1) == 0) {
			mst = 0;
			sts = 1;
		} else {
			mst--;
			msDelay(1);
		}
	}

	return sts;
}

static int lpc17xx_mii_read(unsigned long PhyReg, unsigned long *data) 
{
	unsigned long mst = 250;
	int sts = 0;

	/* Read value at PHY address and register */
	__raw_writel((PHYDEF_PHYADDR << 8) | PhyReg, MAC_MADR);
	__raw_writel(1, MAC_MCMD);

	/* Wait for unbusy status */
	while (mst > 0) {
		if ((__raw_readl(MAC_MIND) & 1) == 0) {
			mst = 0;
			*data = __raw_readl(MAC_MRDD);
			sts = 1;
		} else {
			mst--;
			msDelay(1);
		}
	}

	__raw_writel(0, MAC_MCMD);

	return sts;
}

static int lpc17xx_phy_reset(void)
{
	int goodacc;
	unsigned long tmp1, mst;

	/* Reset the PHY and wait for reset to complete */
	goodacc = lpc17xx_mii_write(MII_BMCR, BMCR_RESET);
	if (goodacc == 0)
		return 0;

	mst = 400;
	goodacc = 0;
	while (mst > 0) {
		lpc17xx_mii_read(MII_BMCR, &tmp1);
		if ((tmp1 & BMCR_RESET) == 0) {
			mst = 0;
			goodacc = 1;
		} else {
			mst--;
			msDelay(1);
		}
	}

	return goodacc;
}

static int lpc17xx_phy_get_link_status(void)
{
        unsigned long status;

        /* Status is read once to clear old link state */
        lpc17xx_mii_read(MII_BMSR, &status);

        /*
	 * Wait if the link is up, and autonegotiation is in progress
	 * (ie - we're capable and it's not done)
	 */
        status = 0;
        lpc17xx_mii_read(MII_BMSR, &status);
        if ((status & BMSR_LSTATUS) && (status & BMSR_ANEGCAPABLE)
            && !(status & BMSR_ANEGCOMPLETE)) {
                int i = 0;

                while (!(status & BMSR_ANEGCOMPLETE)) {
                        /* Timeout reached */
                        if (i > 1000) {
                                error("Phy auto-negotiation timeout\n");
                                return 1;
                        }

                        i++;
                        msDelay(1);   /* 1 ms */
                        lpc17xx_mii_read(MII_BMSR, &status);
                }
                return 0;
        } else {
                if (status & BMSR_LSTATUS)
                        return 0;
                else
                        return 1;
        }

        return 1;
}

static int txrx_setup(void)
{
	int idx;
	unsigned long *pTXStatusL, pbase1, pbase2, pbase3;
	TXRX_DESC_T *pTXRXDesc;
	RX_STATUS_T *pRXStatusL;

	/* Get physical address and size of DMA buffers */
	ethbuffs = (unsigned long *) malloc(BUFF_SIZE_BYTES);
	if (!ethbuffs) {
		error("Error allocating MAC buffers\n");
		return 0;
	}

	/* Setup base pointers */
	pbase1 = (unsigned long) ethbuffs; /* Start of descriptors */
	pbase2 = pbase1 + 256;  /* Start of statuses */
	pbase3 = pbase1 + 512; /* Start of buffers */

	/* Setup pointers to TX structures */
	__raw_writel(pbase1, MAC_TXDESC);
	__raw_writel(pbase2, MAC_TXSTATUS);
	__raw_writel(ENET_MAX_TX_PACKETS - 1, MAC_TXDESCNUM);

	/* Save base address of TX descriptor table and TX status */
	pTXRXDesc = (TXRX_DESC_T *) pbase1;
	pTXStatusL = (unsigned long *) pbase2;
	pTXDesc = pTXRXDesc;
	pTXStatus = pTXStatusL;

	/* Build TX descriptors */
	for (idx = 0; idx < ENET_MAX_TX_PACKETS; idx++) {
		pTXRXDesc->packet = pbase3;
		pTXRXDesc->control = 0;

		debug("TX descriptor @ %08x, buffer @ %08x, status @ %08x\n",
			pTXRXDesc, pbase3, pTXStatusL);

		/* Statuses are pre-filled to help with debugging */
		*pTXStatusL = 0xFFFFFFFF;

		/* Save virtual address of buffer */
		pTXVBuffs [idx] = (unsigned long) pbase3;

		/* Next descriptor and status */
		pTXRXDesc++;
		pTXStatusL++;
		pbase3 += ENET_MAXF_SIZE;
	}

	/* Setup pointers to RX structures */
	__raw_writel((long) pTXRXDesc, MAC_RXDESC);
	__raw_writel((long) pTXStatusL, MAC_RXSTATUS);
	__raw_writel(ENET_MAX_RX_PACKETS - 1, MAC_RXDESCNUM);

	/* Save base address of RX descriptor table and RX status */
	pRXDesc = pTXRXDesc;
	pRXStatus = pRXStatusL = (RX_STATUS_T *) pTXStatusL;

	/* Build RX descriptors */
	for (idx = 0; idx < ENET_MAX_TX_PACKETS; idx++) {
		pTXRXDesc->packet = pbase3;
		pTXRXDesc->control = 0x80000000 | (ENET_MAXF_SIZE - 1);

		debug("RX descriptor @ %08x, buffer @ %08x, status @ %08x\n",
			pTXRXDesc, pbase3, pRXStatusL);

		/* Statuses are pre-filled to help with debugging */
		pRXStatusL->statusinfo = 0xFFFFFFFF;
		pRXStatusL->statushashcrc = 0xFFFFFFFF;

		/* Save virtual address of buffer */
		pRXVBuffs [idx] = (unsigned long) pbase3;

		/* Next descriptor and status */
		pTXRXDesc++;
		pRXStatusL++;
		pbase3 += ENET_MAXF_SIZE;
	}

    return 1;
}

int lpc17xx_eth_deinit(void)
{
	/* Reset PHY */
	(void) lpc17xx_phy_reset();

	/* Reset all MAC logic */
	__raw_writel(0xCF00, MAC_MAC1);
	__raw_writel(0x001C, MAC_COMMAND);
	msDelay(2);

	lpc17_clk_enable(LPC17_CLK_ENET, 0);

	free(ethbuffs);

	return 1;
}

int lpc17xx_hw_init(void)
{
	int btemp;
	unsigned int duplex, speed;
	unsigned long tmp1, mst = 250;
	uchar bd_enetaddr[6];

	/* Get MAC address from environment variable */
	eth_getenv_enetaddr("ethaddr", bd_enetaddr);

	/* Enable MII clocking */
	lpc17_clk_enable(LPC17_CLK_ENET, 1);

	/* Set RMII management clock rate */
	__raw_writel((7 << 2), MAC_MCFG);


	/* Reset all MAC logic */
	__raw_writel(0xCF00, MAC_MAC1);
	__raw_writel(0x0038, MAC_COMMAND);
	//__raw_writel(0x0078, MAC_COMMAND);
	msDelay(10);

	/* Initial MAC initialization */
	__raw_writel(0x0002, MAC_MAC1);
	__raw_writel(0x0030, MAC_MAC2);
	__raw_writel(ENET_MAXF_SIZE, MAC_MAXF);

	/* Maximum number of retries, 0x37 collision window, gap */
	__raw_writel(0xF | (0x37 << 8), MAC_CLRT);
	__raw_writel(0x12, MAC_IPGR);

#ifdef USE_PHY_RMII
	/* RMII setup */
	__raw_writel(0x240, MAC_COMMAND);
	__raw_writel(0x000, MAC_SUPP);
	msDelay(10);
#else
	/* MII setup */
	__raw_writel(0x040, MAC_COMMAND);
#endif

	/* Enable rate auto-negotiation for the link */
	if (lpc17xx_mii_write(MII_BMCR,
		(BMCR_SPEED100 | BMCR_ANENABLE)) == 0)
		return 0;
	
	mst = 1000;
        btemp = 1;
        while (mst > 0) {
                /* Wait for Link status to set UP or Timeout */
                if (lpc17xx_phy_get_link_status() == 0) {
                        mst = 0;
                        btemp = 0;
                        debug("ENET: auto-negotiation complete\n");
                } else {
                        mst--;
                        msDelay(1);
                }
        }
		
        if (btemp) {
                debug("ENET: auto-negotiation failed\n");
                return 0;
        }
 
        /* Read PHY Status Register to determine Ethernet Configuration */
        tmp1 = 0;
        //lpc17xx_mii_read(DP83848_PHY_STATUS, &tmp1);
        lpc17xx_mii_read(0x0001, &tmp1);
        duplex = (tmp1 & 0x0004) >> 2;
        speed = (tmp1 & 0x0002) >> 1;

	/* Configure Full/Half Duplex mode */
	if (duplex == 1) {
		/* Full duplex is supported */
		__raw_writel(__raw_readl(MAC_MAC2) | 1, MAC_MAC2);
		__raw_writel(__raw_readl(MAC_COMMAND) | (1 << 10),
			MAC_COMMAND);
		__raw_writel(0x15, MAC_IPGT);
		debug("ENET: Full duplex\n");
	} else {
		__raw_writel(0x12, MAC_IPGT);
		debug("ENET: Half duplex\n");
	}

	/* Configure 100MBit/10MBit mode */
	if (speed == 0) {
		/* 100MBase mode */
		__raw_writel((1 << 8), MAC_SUPP);
		debug("ENET: 100MBaseT\n");
	} else 	{
		/* 10MBase mode */
		__raw_writel(0, MAC_SUPP);
		debug("ENET: 10BaseT\n");
	}

	/* Save station address */
	__raw_writel((unsigned long) (bd_enetaddr[0] |
		(bd_enetaddr[1] << 8)), MAC_SA2);
	__raw_writel((unsigned long) (bd_enetaddr[2] |
		(bd_enetaddr[3] << 8)), MAC_SA1);
	__raw_writel((unsigned long) (bd_enetaddr[4] |
		(bd_enetaddr[5] << 8)), MAC_SA0);

	/* Setup TX and RX descriptors */
	if (!txrx_setup()) {
		error("Error initializing MAC buffers\n");
		lpc17xx_eth_deinit();
		return 0;
	}
    	
	/* Enable broadcast and matching address packets */
	__raw_writel(0x22, MAC_RXFILTCTRL);

	/* Clear and enable interrupts */
	__raw_writel(0xFFFF, MAC_INTCLR);
	__raw_writel(0x0, MAC_INTENAB);

	/* Enable receive and transmit mode of MAC ethernet core */
	__raw_writel(__raw_readl(MAC_COMMAND) | 0x03, MAC_COMMAND);
	__raw_writel(__raw_readl(MAC_MAC1) | 1, MAC_MAC1);

	/*
	 * Perform a 'dummy' send of the first ethernet frame with a size of 4
	 * to 'prime' the MAC.
	 */
	tmp1 = 0;
	eth_send(&tmp1, 4);

	return 1;
}

void eth_halt(void)
{
	lpc17xx_eth_deinit();
}

int eth_init(bd_t *bd)
{
	/* De-init if an error occurred */
	if (lpc17xx_hw_init() == 0) {
		error("ENET init failure\n");
		lpc17xx_eth_deinit();
		return -1;
	}

	return 0;
}

int eth_rx(void)
{
	unsigned long idx, length;

	/* Determine if a frame has been received */
	length = 0;
	idx = __raw_readl(MAC_RXCONSIDX);
	if (__raw_readl(MAC_RXPRODIDX) != idx) {
		/* Clear interrupt */
		__raw_writel((1 << 3), MAC_INTCLR);

		/* Frame received, get size of RX packet */
		length = pRXStatus[idx].statusinfo & 0x7FF;

		/* Pass the packet up to the protocol layer */
		if (length > 0) {
		        memcpy((void *) NetRxPackets[0], (void *) pRXVBuffs [idx], length);
			NetReceive(NetRxPackets[0], (unsigned short) length);
		}

		/* Return DMA buffer */
		idx++;
		if (idx >= ENET_MAX_RX_PACKETS)
			idx = 0;

		__raw_writel(idx, MAC_RXCONSIDX);
	}

	return (int) length;
}

int eth_send(volatile void *packet, int length)
{
	unsigned long idx, cidx, fb;

	/* Determine number of free buffers and wait for a buffer if needed */
	fb = 0;
	while (fb == 0)	{
		idx = __raw_readl(MAC_TXPRODIDX);
		cidx = __raw_readl(MAC_TXCONSIDX);

		if (idx == cidx)
			fb = ENET_MAX_TX_PACKETS;
		else if (cidx > idx)
			fb = (ENET_MAX_TX_PACKETS - 1) -
				((idx + ENET_MAX_TX_PACKETS) - cidx);
		else
			fb = (ENET_MAX_TX_PACKETS - 1) - (cidx - idx);
	}

	/* Update descriptor with new frame size */
	pTXDesc[idx].control = (length | 0x40000000);

	/* Move data to buffer */
	memcpy((void *) pTXVBuffs [idx], (void *)packet, length);

	/* Get next index for transmit data DMA buffer and descriptor */
	idx++;
	if (idx >= ENET_MAX_TX_PACKETS)
		idx = 0;

	__raw_writel(idx, MAC_TXPRODIDX);

	return 0;
}

