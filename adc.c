/*
 * adc.c
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */


#include "adc.h"
#include "temperature.h"
#include "bitmacros.h"
#include "rotdisplay.h"
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t adc_use = IS_FREE;

uint16_t adc_array[NUM_VALUES_FOR_MEAN];
uint8_t adc_array_position;

uint16_t trim_value;
uint8_t new_trim_available;

void init_adc_for_temperature() {
	// INIT ADC
	// REFS[2:0]=110 (in ADCSRB and ADMUX) select reference voltage -> 2.56V
	// Select differential with AGND as pos, ADC9 (=PB6) as neg (NOT POSSIBLE)
	// select gain via MUX[5:0] in ADMUX and GSEL in ADCSRB.
	// enable adc via ADEN in ADCSRA

	// single ended input ADC9 -> MUX[5:0]=001001, gain not possible with single ended

	ADCSRA = _BV(ADEN) | _BV(ADIE);
	ADMUX = _BV(REFS1) | _BV(MUX0) | _BV(MUX3); // ADC9
	ADCSRB = _BV(REFS2);
	// DIGITAL INPUT DISABLE REGISTER: disable digital input for pin PB6
	//sbi(0x22, 0x06); //sbi(DIDR1, ADC9D);

}


void _clear_adc_array() {
	for(int i = 0; i < NUM_VALUES_FOR_MEAN; i++) {
		adc_array[i] = 0;
	}
	adc_array_position = 0;
}

void start_temperature_read() {
	if(adc_use == IS_FREE) {
		adc_use = IS_TEMP;

		init_adc_for_temperature();
		_clear_adc_array();

		// start single conversion via 1->ADSC
		sbi(ADCSRA, ADSC);
	}
}

void init_adc_for_trim() {
	ADCSRA = _BV(ADEN) | _BV(ADIE); // VCC as reference
	ADMUX = _BV(MUX0) | _BV(MUX1) | _BV(MUX2); // ADC7
	ADCSRB = 0;
}


void start_trim_read() {
	if(adc_use == IS_FREE) {
		adc_use = IS_TRIM;

		init_adc_for_trim();
		_clear_adc_array();

		// start single conversion via 1->ADSC
		sbi(ADCSRA, ADSC);
	}
}


ISR(ADC_vect){
	// adc complete
	uint16_t tmp;

	// result in ADCH and ADCL (ADCL must be read first)
	tmp = ADCL;
	tmp += ADCH * 0xFF;
	adc_array[adc_array_position] = tmp;

	adc_array_position++;
	//uint_for_rotation(adc_array_position);

	if(adc_array_position == NUM_VALUES_FOR_MEAN) {

		tmp = 0;
		for(int i = 0; i < NUM_VALUES_FOR_MEAN; i++) {
			tmp += adc_array[i];
		}

		switch(adc_use) {
		case IS_TEMP:

			temp = tmp / NUM_VALUES_FOR_MEAN;

			new_temp_available = 1;
			break;
		case IS_TRIM:

			trim_value = tmp / NUM_VALUES_FOR_MEAN;

			new_trim_available = 1;
			break;
		}


		adc_use = IS_FREE;

	}
	else
	{
		sbi(ADCSRA, ADSC);
	}



}
