/*
 * adc.c
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */


#include "adc.h"
#include "temperature.h"
#include "bitmacros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t adc_use = IS_FREE;

void init_adc_for_temperature() {
	// INIT ADC
	// REFS[2:0]=011 (in ADCSRB and ADMUX) select reference voltage -> 1.1V
	// Select differential with AGND as pos, ADC9 (=PB6) as neg (NOT POSSIBLE)
	// select gain via MUX[5:0] in ADMUX and GSEL in ADCSRB.
	// enable adc via ADEN in ADCSRA

	// single ended input ADC9 -> MUX[5:0]=001001, gain not possible with single ended

	ADCSRA = _BV(ADEN) | _BV(ADIE);
	ADMUX = _BV(REFS1) | _BV(MUX0) | _BV(MUX3);
	// DIGITAL INPUT DISABLE REGISTER: disable digital input for pin PB6
	//sbi(0x22, 0x06); //sbi(DIDR1, ADC9D);

}

void start_temperature_read() {
	if(adc_use == IS_FREE) {
		adc_use = IS_TEMP;

		init_adc_for_temperature();

		// start single conversion via 1->ADSC
		sbi(ADCSRA, ADSC);
	}
}



ISR(ADC_vect){
	// adc complete

	switch(adc_use) {
	case IS_TEMP:
		// result in ADCH and ADCL (ADCL must be read first)
		temp = ADCL;
		temp += ADCH * 0xFF;
		new_temp_available = 1;
		adc_use = IS_FREE;

		break;
	}

}
