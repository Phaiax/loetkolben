/*
 * main.c
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#include <avr/io.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "bitmacros.h"

#include "display.h"
#include "rotdisplay.h"
#include "temperature.h"
#include "adc.h"
#include "trim.h"


uint16_t counter = 0;


int main(void) {
	display_init();

	sei(); // enable global interrupts

	uint8_t i = 0; // count up number

	uint16_t test = 1234;
	uint_for_rotation(test);
	stop_rotation();

	//start_temperature_read();
	start_trim_read();
	what_to_display = DISPLAY_TEMP;

	while(1) {

		counter++;
		display_update();
		rotation_update();
		trim_update();
		//temperature_update();


		if(counter % 1000 == 0) {
			i++;



			i = 0;

		}
	}
}
