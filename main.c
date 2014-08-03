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
#include "temperature.h"
#include "adc.h"
#include "trim.h"
#include "defines.h"
#include "controller.h"


uint16_t counter = 0;
uint16_t timeout_counter = 0;

int main(void) {
	display_init();
	control_init();


	sei(); // enable global interrupts


	//start_temperature_read();
	start_trim_read();
	what_to_display = DISPLAY_TEMP;

	while(1) {

		counter++;


		if(counter % COUNTER_UPDATE_MODULO == 0) {

			trim_update();
			temperature_update();
			control_update();
			display_update();

			timeout_counter++;
			if(timeout_counter == TIMEOUT_TIME) {
				dot2 = 0;
			}

		}
	}
}
