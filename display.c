/*
 * display.c
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#include "display.h"
#include <avr/io.h>

uint8_t nr_seg1;
uint8_t nr_seg2;
uint8_t nr_seg3;

uint8_t dot1;
uint8_t dot2;
uint8_t dot3;


uint8_t nextsegtimer = 0;
uint8_t currentseg = 0;

/**
 * Sets the 7-segment output pins so that <nr> is displayed
 */
void writenr(uint8_t nr) {

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
void writedot(uint8_t dot) {
	if(dot) {
		PORTA |= SEG_DOT;
	} else {
		PORTA &= ~SEG_DOT;
	}
}


void display_init() {
	// PORTA is completely connected to the 7-segment displays, so set it as output
	DDRA = 0xFF;
	PORTA = 0;

	DDRB = _BV(DDB0) | _BV(DDB1) | _BV(DDB2);   // selectors for multiplexing 7 segment displays
	PORTB &= ~(_BV(PB0) | _BV(PB2) | _BV(PB2)); // switch all displays of
	// ## !! each PIN can deliver a current of 40mA. One segment draws 20mA
	//       so never switch on all 3 segments together
}

/**
 * Multiplexes the 3 seven segment displays
 */
void display_update() {
	nextsegtimer++;
	if(nextsegtimer == 5) {
		nextsegtimer = 0;
		currentseg = (currentseg + 1) % 3;
		switch(currentseg) {
		case 0:
			PORTB &= ~(_BV(PB0) | _BV(PB2) | _BV(PB2)); // switch of displays
			writenr(nr_seg1);
			writedot(dot1);
			PORTB |= _BV(PB0); // switch on display 1
			break;
		case 1:
			PORTB &= ~(_BV(PB0) | _BV(PB2) | _BV(PB2)); // switch of displays
			writenr(nr_seg2);
			writedot(dot2);
			PORTB |= _BV(PB1); // switch on display 2
			break;
		case 2:
			PORTB &= ~(_BV(PB0) | _BV(PB2) | _BV(PB2)); // switch of displays
			writenr(nr_seg3);
			writedot(dot3);
			PORTB |= _BV(PB2); // switch on display 3
			break;
		}
	}
}
