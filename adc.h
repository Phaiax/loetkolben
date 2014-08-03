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
#include "trim.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define IS_TEMP 1
#define IS_TRIM 2
#define IS_NET 3
#define IS_INTERNAL_TEMP 4
//#define IS_24V 5
#define IS_FREE 0

#define NUM_VALUES_FOR_MEAN 4

extern uint8_t adc_use;
extern uint16_t adc_array[];
extern uint8_t adc_array_position;


//inline void start_temperature_read();
//inline void start_trim_read();
//inline void init_adc_for_temperature();
//inline void init_adc_for_trim();


inline void _clear_adc_array() {
	for(uint8_t i = 0; i < NUM_VALUES_FOR_MEAN; i++) {
		adc_array[i] = 0;
	}
	adc_array_position = 0;
}




inline void start_temperature_read() {
	if(adc_use == IS_FREE) {
		adc_use = IS_TEMP;

		// single ended input ADC9 -> MUX[5:0]=001001, gain not possible with single ended
		// REFS[2:0]=110 (in ADCSRB and ADMUX) select reference voltage -> 2.56V
		// enable adc via ADEN in ADCSRA
		ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2);
		ADMUX = _BV(REFS1) | _BV(MUX0) | _BV(MUX3); // ADC9
		ADCSRB = _BV(REFS2);
		sbi(DIDR1, ADC9D);

		_clear_adc_array();

		// start single conversion via 1->ADSC
		sbi(ADCSRA, ADSC);
	}
}



inline void start_trim_read() {
	if(adc_use == IS_FREE) {
		adc_use = IS_TRIM;

		ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2); // VCC as reference
		ADMUX = _BV(MUX0) | _BV(MUX1) | _BV(MUX2); // ADC7
		sbi(DIDR1, ADC7D);
		ADCSRB = 0;

		_clear_adc_array();

		// start single conversion via 1->ADSC
		sbi(ADCSRA, ADSC);

	}
}

/*
inline void start_24V_read() {
	if(adc_use == IS_FREE) {
		adc_use = IS_24V;

		ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2); // VCC as reference
		ADMUX = _BV(MUX3); // ADC8
		sbi(DIDR1, ADC8D);
		ADCSRB = 0;

		_clear_adc_array();

		// start single conversion via 1->ADSC
		sbi(ADCSRA, ADSC);

	}
}*/



inline void start_internal_temperature_read() {
	if(adc_use == IS_FREE) {
		adc_use = IS_INTERNAL_TEMP;

		// single ended input ADC11 -> MUX[5:0]=111111, Vref=1.1: REFS[2:0]=010

		ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1);
		ADMUX = _BV(REFS1) | _BV(MUX0) | _BV(MUX1) | _BV(MUX2) | _BV(MUX3) | _BV(MUX4); // ADC9
		ADCSRB =  _BV(MUX5);

		_clear_adc_array();

		// start single conversion via 1->ADSC
		sbi(ADCSRA, ADSC);
	}
}


#endif /* ADC_H_ */
