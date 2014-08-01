/*
 * adc.h
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
#include "temperature.h"
#include "bitmacros.h"
#include "rotdisplay.h"
#include "trim.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define IS_TEMP 1
#define IS_TRIM 2
#define IS_NET 3
#define IS_FREE 0

#define NUM_VALUES_FOR_MEAN 4

extern uint8_t adc_use;
extern uint16_t adc_array[];
extern uint8_t adc_array_position;


//inline void start_temperature_read();
//inline void start_trim_read();
//inline void init_adc_for_temperature();
//inline void init_adc_for_trim();

inline void init_adc_for_temperature() {
	// INIT ADC
	// REFS[2:0]=110 (in ADCSRB and ADMUX) select reference voltage -> 2.56V
	// Select differential with AGND as pos, ADC9 (=PB6) as neg (NOT POSSIBLE)
	// select gain via MUX[5:0] in ADMUX and GSEL in ADCSRB.
	// enable adc via ADEN in ADCSRA

	// single ended input ADC9 -> MUX[5:0]=001001, gain not possible with single ended

	ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2);
	ADMUX = _BV(REFS1) | _BV(MUX0) | _BV(MUX3); // ADC9
	ADCSRB = _BV(REFS2);
	// DIGITAL INPUT DISABLE REGISTER: disable digital input for pin PB6
	//sbi(0x22, 0x06); //sbi(DIDR1, ADC9D);

}


inline void _clear_adc_array() {
	for(int i = 0; i < NUM_VALUES_FOR_MEAN; i++) {
		adc_array[i] = 0;
	}
	adc_array_position = 0;
}

inline void start_temperature_read() {
	if(adc_use == IS_FREE) {
		adc_use = IS_TEMP;

		init_adc_for_temperature();
		_clear_adc_array();

		// start single conversion via 1->ADSC
		sbi(ADCSRA, ADSC);
	}
}

inline void init_adc_for_trim() {
	ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2); // VCC as reference
	ADMUX = _BV(MUX0) | _BV(MUX1) | _BV(MUX2); // ADC7
	ADCSRB = 0;
}


inline void start_trim_read() {
	if(adc_use == IS_FREE) {
		adc_use = IS_TRIM;

		init_adc_for_trim();
		_clear_adc_array();

		// start single conversion via 1->ADSC
		sbi(ADCSRA, ADSC);

	}
}


inline void _clear_adc_array();

#endif /* ADC_H_ */
