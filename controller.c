/*
 * controller.c
 *
 *  Created on: 02.08.2014
 *      Author: daniel
 */

#include "controller.h"
#include "display.h"
#include "bitmacros.h"
#include "defines.h"
#include "temperature.h"
#include "trim.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>



// keep these values low, so there will be no overflow on
// heat_on_cycles_counter  < heat_on_cycles
int8_t heat_max_cycles = 0;
int8_t heat_on_cycles = 0;
int8_t heat_on_cycles_counter = 0;

// wait for interrupt on falling edge
// then wait via timer until wave gets zero
//   turn on trigger pin and stop timer
// heat will stay on the negative half wave
// heat will stay on on positive wave because trigger is still on
// wait for interrupt on rising edge
//   increment cycle counter -> same value now, on falling edge and on timer
//   now a) turn trigger off if heat_on_cycles_counter tells so
//       b) let trigger stay on if heat should continue
// interrupt on falling edge will occour
//   we still can set timer in case b),
//   but the timer will have no effect since trigger is still on


// PIN CHANGE interrupt
ISR(PCINT_vect) {
	if(dot2) { // general enable

		if((PINB & _BV(PINB5))) {  // RISING EDGE

			heat_on_cycles_counter ++;
			if(heat_on_cycles_counter > heat_max_cycles) {
				heat_on_cycles_counter = 0;
			}

			int8_t diff = heat_on_cycles_counter - heat_on_cycles;
			if(diff >= 0) { // off when heat_on_cycles_counter reached (==) heat_on_cycles
				cbi(PORTB, PB3); // switch heat off
			}
			// else: continue with heat on next neg and pos wave


		} else {	// FALLING EDGE


			sbi(TCCR0B, CS00);	// turn TIMER 0 on with no prescaler
		}
	} else {
		cbi(PORTB, PB3);
	}
}

ISR(TIMER0_COMPA_vect) { //TIMER0_OVF // TIMER0_COMPA // TIMER0_COMPB // TIMER0_CAPT
	// stop timer0
	TCCR0B = _BV(PSR0); // clear prescaler (we don't use it, so no problem at all)
						// sets CS00=0 -> also stops counting

	int8_t diff = heat_on_cycles_counter - heat_on_cycles;
	if(diff < 0) {
		sbi(PORTB, PB3); // switch heat on
	}

	// clear timer value
	TCNT0H = 0;
	TCNT0L = 0;
}


void control_init() {
	// TRIAC PIN
	sbi(DDRB, DDB3); // configure as out
	cbi(PORTB, PB3); // switch heat off

	// INTERRUPT for 24V sine wave sync pin
	// Init Pin8 PB5 PCINT13 for interrupt on toggle
	PCMSK0 = 0;
	PCMSK1 = _BV(PCINT13);
	sbi(GIMSK, PCIE1);

	// use timer0 for wait after pin toggle (sin wave sync)
	// INIT TIMER 0
	TCCR0A = _BV(TCW0); // 16 Bit mode
	//TCCR0B = 0;
	// Interrupt time: one LSB = 1e-6 sec, 1 wave @50Hz = 20000
	// one quater: 5000 = 0x1388;
	// from rising edge (2,2V) to point zero (0V): 1D10
	// from falling edge (???V) to point zero (0V): 0850 (timer triggers 99% before 0 is reached)
	OCR0B = 0x08;
	OCR0A = 0x50;

	sbi(TIMSK, OCIE0A); // interrupt if ocr0a is reached
	// to turn on with no prescaler: sbi(TCCR0B, CS00);

}


void control_update() {
	int16_t diff = (int16_t)trim_for_display - (int16_t)temp_for_display;
	if(diff > 20) {
		heat_max_cycles = 5;
		heat_on_cycles = 5;
		heat_on_cycles_counter = 0; // reset
		dot3 = 1;
	} else if(diff > 10) {
		heat_max_cycles = 5;
		heat_on_cycles = 2;
		heat_on_cycles_counter = 0; // reset
		dot3 = 1;
	} else if(diff > 5) {
		heat_max_cycles = 5;
		heat_on_cycles = 1;
		heat_on_cycles_counter = 0; // reset
		dot3 = 1;
	} else if(diff > 0) {
		heat_max_cycles = 20;
		heat_on_cycles = 3;
		heat_on_cycles_counter = 0; // reset
		dot3 = 1;
	} else {
		dot3 = 0;
		heat_max_cycles = 2;
		heat_on_cycles = 0; // off
	}
}
