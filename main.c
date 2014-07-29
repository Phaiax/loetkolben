/*
 * main.c
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#include <avr/io.h>
#include <avr/power.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "bitmacros.h"


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

#define SEG_4 0x01
#define SEG_2 0x02
#define SEG_1 0x04
#define SEG_3 0x08
#define SEG_DOT 0x10
#define SEG_6 0x20
#define SEG_7 0x40
#define SEG_5 0x80
#define SEG_NUMMASK 0xEF

/*
 # 1 #
 2   3
 # 4 #
 5   6
 # 7 #  DOT */

#define NR_OFF 0x00
#define NR_1 (SEG_3 | SEG_6)
#define NR_2 (SEG_1 | SEG_3 | SEG_4 | SEG_5 | SEG_7)
#define NR_3 (SEG_1 | SEG_3 | SEG_4 | SEG_6 | SEG_7)
#define NR_4 (SEG_2 | SEG_3 | SEG_4 | SEG_6)
#define NR_5 (SEG_1 | SEG_2 | SEG_4 | SEG_6 | SEG_7)
#define NR_6 (SEG_1 | SEG_2 | SEG_4 | SEG_5 | SEG_6 | SEG_7)
#define NR_7 (SEG_1 | SEG_3 | SEG_6)
#define NR_8 (SEG_1 | SEG_2 | SEG_3 | SEG_4 | SEG_5 | SEG_6 | SEG_7)
#define NR_9 (SEG_1 | SEG_2 | SEG_3 | SEG_4 | SEG_6 | SEG_7)
#define NR_0 (SEG_1 | SEG_2 | SEG_3 | SEG_5 | SEG_6 | SEG_7)

/**
 * Sets the 7-segment output pins so that <nr> is displayed
 */
void setnr(uint8_t nr) {

	PORTA &= (NR_OFF | SEG_DOT); // all off

	switch (nr) {
	case 0:
		PORTA |= NR_0;
		break;
	case 1:
		PORTA |= NR_1;
		break;
	case 2:
		PORTA |= NR_2;
		break;
	case 3:
		PORTA |= NR_3;
		break;
	case 4:
		PORTA |= NR_4;
		break;
	case 5:
		PORTA |= NR_5;
		break;
	case 6:
		PORTA |= NR_6;
		break;
	case 7:
		PORTA |= NR_7;
		break;
	case 8:
		PORTA |= NR_8;
		break;
	case 9:
		PORTA |= NR_9;
		break;
	}
}

/**
 * Activates or deactivates the dot
 */
void setdot(uint8_t dot) {
	if(dot) {
		PORTA |= SEG_DOT;
	} else {
		PORTA &= ~SEG_DOT;
	}
}

uint8_t nr_seg1;
uint8_t nr_seg2;
uint8_t nr_seg3;

uint8_t dot1;
uint8_t dot2;
uint8_t dot3;


uint8_t nextsegtimer = 0;
uint8_t currentseg = 0;
/**
 * Multiplexes the 3 seven segment displays
 */
void updateseg() {
	nextsegtimer++;
	if(nextsegtimer == 5) {
		nextsegtimer = 0;
		currentseg = (currentseg + 1) % 3;
		switch(currentseg) {
		case 0:
			PORTB &= ~(_BV(PB0) | _BV(PB2) | _BV(PB2)); // switch of displays
			setnr(nr_seg1);
			setdot(dot1);
			PORTB |= _BV(PB0); // switch on display 1
			break;
		case 1:
			PORTB &= ~(_BV(PB0) | _BV(PB2) | _BV(PB2)); // switch of displays
			setnr(nr_seg2);
			setdot(dot2);
			PORTB |= _BV(PB1); // switch on display 2
			break;
		case 2:
			PORTB &= ~(_BV(PB0) | _BV(PB2) | _BV(PB2)); // switch of displays
			setnr(nr_seg3);
			setdot(dot3);
			PORTB |= _BV(PB2); // switch on display 3
			break;
		}
	}
}

uint8_t rot_seg1;
uint8_t rot_seg2;
uint8_t rot_seg3;

uint16_t nextrottimer = 0;
uint8_t currentrot = 0;

void rotate() {
	nextrottimer ++;
	if(nextrottimer == 1000) {
		nextrottimer = 0;
		currentrot++;
		if(currentrot == 5)
			currentrot = 0;

		switch(currentrot){
		case 0:
			nr_seg1 = rot_seg1;
			nr_seg2 = rot_seg2;
			nr_seg3 = rot_seg3;
			break;
		case 1:
			nr_seg1 = rot_seg2;
			nr_seg2 = rot_seg3;
			nr_seg3 = rot_seg1;
			break;
		case 2:
			nr_seg1 = rot_seg3;
			nr_seg2 = rot_seg1;
			nr_seg3 = rot_seg2;
			break;
		default:
			nr_seg1 = 100;
			nr_seg2 = 100;
			nr_seg3 = 100;
		}
	}
}

uint16_t counter = 0;

int main(void) {
	// PORTA is completely connected to the 7-segment displays, so set it as output
	DDRA = 0xFF;
	PORTA = 0;

	DDRB = _BV(DDB0) | _BV(DDB1) | _BV(DDB2);   // selectors for multiplexing 7 segment displays
	PORTB &= ~(_BV(PB0) | _BV(PB2) | _BV(PB2)); // switch all displays of
	// ## !! each PIN can deliver a current of 40mA. One segment draws 20mA
	//       so never switch on all 3 segments together

	uint8_t i = 0; // count up number

	int test = 391;

	rot_seg3 = test % 10;
	rot_seg2 = ((test - nr_seg1)/10) % 10;
	rot_seg1 = ((test - nr_seg2*10 - nr_seg1)/100) % 10;

	while(1) {

		counter++;
		updateseg();
		rotate();

		if(counter % 1000 == 0) {
			i++;
			if(i == 4){
				i = 0;
			}

		}
	}
}
