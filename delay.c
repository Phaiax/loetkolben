/*
 * delay.c
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#include "delay.h"


void delay_ms(unsigned int ms) {
	unsigned int i;
	unsigned int j;
	unsigned int k;

	for (i = ms; i; i--) {
		for (j = 17; j; j--) {
			for (k = 10; k; k--) {
				__asm__ volatile("nop");
				// so the endless loop isn't optimized away
			}
		}
	}
}
