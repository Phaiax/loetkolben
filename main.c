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


uint16_t counter = 0;


int main(void) {
	display_init();

	sei(); // enable global interrupts

	uint8_t i = 0; // count up number

	uint16_t test = 391;
	uint_for_rotation(test);

	start_temperature_read();

	while(1) {

		counter++;
		display_update();
		rotation_update();

		if(counter % 1000 == 0) {
			i++;
			if(current_rot == 4){

				if(new_temp_available) {
					new_temp_available = 0;
					uint_for_rotation(temp);
					start_temperature_read();

				}
				i = 0;
			}

		}
	}
}
