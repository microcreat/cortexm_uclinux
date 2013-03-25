#ifndef __LPC17_GPIO_H
#define __LPC17_GPIO_H

/*
 * Copyright (C) 2011 by NXP Semiconductors
 * All rights reserved.
 *
 * @Author: Kevin Wells
 * @Descr: LPC17xx GPIO functions
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

/* Set a GPIO as an input */
void lpc17xx_gpio_set_input(unsigned char grp, unsigned char pin);

/* Set a GPIO as an output */
void lpc17xx_gpio_set_output(unsigned char grp,unsigned char pin);

/* Set a output GPIO to a specific state */
void lpc17xx_gpio_set_state(unsigned char grp, unsigned char pin, int st);

/* Return the state of an input GPIO */
int lpc17xx_gpio_get_state(unsigned char grp, unsigned char pin);

#endif /* __LPC17_GPIO_H */

