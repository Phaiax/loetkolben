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
#include "trim.h"
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t adc_use = IS_FREE;

uint16_t adc_array[NUM_VALUES_FOR_MEAN];
uint8_t adc_array_position;




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
			temp_value = tmp / NUM_VALUES_FOR_MEAN;
			new_temp_available = 1;
			break;
		case IS_TRIM:
			trim_value = tmp / NUM_VALUES_FOR_MEAN;
			new_trim_value_available = 1;

			break;
		}


		switch(adc_use) {
		case IS_TEMP:
			adc_use = IS_FREE;
			start_trim_read();
			break;
		case IS_TRIM:
			adc_use = IS_FREE;
			start_temperature_read();
			break;
		}

	}
	else
	{
		sbi(ADCSRA, ADSC);
	}



}
