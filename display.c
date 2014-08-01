/*
 * display.c
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#include "display.h"
#include "temperature.h"
#include "trim.h"
#include "bitmacros.h"
#include <avr/interrupt.h>


uint8_t nr_seg1;
uint8_t nr_seg2;
uint8_t nr_seg3;

uint8_t dot1;
uint8_t dot2;
uint8_t dot3;

uint8_t what_to_display = DISPLAY_OFF;

uint8_t nextsegtimer = 0;
uint8_t currentseg = 0;


uint16_t currval = 65000;
void uint_for_display(uint16_t nr) {
	if(nr != currval) {
		nr_seg3 = nr % 10;
		nr_seg2 = ((nr - nr_seg3)/10) % 10;
		nr_seg1 = ((nr - nr_seg2*10 - nr_seg3)/100) % 10;
		uint8_t thousands = ((nr - nr_seg1 * 100 - nr_seg2*10 - nr_seg3)/1000) % 10;
		dot1 = thousands;
		currval = nr;
	}
}






void display_init() {
	// PORTA is completely connected to the 7-segment displays, so set it as output
	DDRA = 0xFF;
	PORTA = 0;

	DDRB = _BV(DDB0) | _BV(DDB1) | _BV(DDB2);   // selectors for multiplexing 7 segment displays
	PORTB &= ~(_BV(PB0) | _BV(PB1) | _BV(PB2)); // switch all displays of
	// ## !! each PIN can deliver a current of 40mA. One segment draws 20mA
	//       so never switch on all 3 segments together

	// TC1H : 9,10th bit of all following values (write first, read after)
	// TCNT1 = 0; // actual timer value
	TC1H = 0;
	OCR1A = 85;
	TC1H = 0;
	OCR1B = 170;
	TC1H = 0;
	OCR1C = 255; // represents timers TOP value, so will be set to zero after this
	TC1H = 0;
	OCR1D = 254; // use this for third, because C has no interrupt

	// Interrupts (use sbi, because TIMSK is shared with Timer0):
	sbi(TIMSK, OCIE1A);
	sbi(TIMSK, OCIE1B);
	sbi(TIMSK, OCIE1D);


	// Using Timer/Counter 1 (TC1) to generate Interrupts to switch between segments
	TCCR1A = 0; // no pin use by TC1
	TCCR1B = _BV(CS12) | _BV(CS11) ;//| _BV(CS10); // Prescaler: /64 and start timer

	// TCCR1C = 0; // no pin use by TC1
	// TCCR1D = 0; // no fault protection, normal mode
	// TCCR1E = 0;
	// PLLCSR = 0; // cpu clk as clk source


}

void auto_value() {
	switch(what_to_display) {
	case DISPLAY_OFF:
		nr_seg1 = ABC_O;
		nr_seg2 = ABC_F;
		nr_seg3 = ABC_F;
		currval = 65000;
		break;
	case DISPLAY_TEMP:
		uint_for_display(temp_for_display);
		break;
	case DISPLAY_TRIM:
		uint_for_display(trim_for_display);
		break;
	}
}

/**
 * Multiplexes the 3 seven segment displays
 */
void display_update() {
	auto_value();
	return;
	nextsegtimer++;
	if(nextsegtimer == 5) {
		nextsegtimer = 0;
		currentseg = (currentseg + 1) % 3;
		switch(currentseg) {
		case 0:
			PORTB &= ~(_BV(PB0) | _BV(PB1) | _BV(PB2)); // switch of displays
			writenr(nr_seg1);
			writedot(dot1);
			PORTB |= _BV(PB1); // switch on display 1
			break;
		case 1:
			PORTB &= ~(_BV(PB0) | _BV(PB1) | _BV(PB2)); // switch of displays
			writenr(nr_seg2);
			writedot(dot2);
			PORTB |= _BV(PB0); // switch on display 2
			break;
		case 2:
			PORTB &= ~(_BV(PB0) | _BV(PB1) | _BV(PB2)); // switch of displays
			writenr(nr_seg3);
			writedot(dot3);
			PORTB |= _BV(PB2); // switch on display 3
			break;
		}
	}
}


ISR(TIMER1_COMPA_vect) {
	PORTB &= ~(_BV(PB0) | _BV(PB1) | _BV(PB2)); // switch of displays
	writenr(nr_seg1);
	writedot(dot1);
	PORTB |= _BV(PB1); // switch on display 1
}

ISR(TIMER1_COMPB_vect) {
	PORTB &= ~(_BV(PB0) | _BV(PB1) | _BV(PB2)); // switch of displays
	writenr(nr_seg2);
	writedot(dot2);
	PORTB |= _BV(PB0); // switch on display 2
}

ISR(TIMER1_COMPD_vect) {
	PORTB &= ~(_BV(PB0) | _BV(PB1) | _BV(PB2)); // switch of displays
	writenr(nr_seg3);
	writedot(dot3);
	PORTB |= _BV(PB2); // switch on display 3
}
