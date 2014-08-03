/*
 * trim.c
 *
 *  Created on: 01.08.2014
 *      Author: daniel
 */

#include "trim.h"
#include "defines.h"
#include "display.h"

uint16_t trim_for_display;
uint16_t new_trim_for_display = 0;

uint16_t trim_value;
uint8_t new_trim_value_available;

uint16_t time_to_display_trim;

void trim_update() {
	if(new_trim_value_available) {

		new_trim_value_available = 0;
		if(trim_value <= TRIM_SWITCH_LOW_TRESHOLD) {
			// SWITCH LOW
			dot2 = 0;
			what_to_display = DISPLAY_INTERNAL_TEMP_VALUE;
		}
		else if(trim_value >= TRIM_SWITCH_HIGH_TRESHOLD)
		{
			dot2 = 1;
			what_to_display = DISPLAY_INTERNAL_TEMP;
		}
		else
		{
			new_trim_for_display = (trim_value - TRIM_SWITCH_LOW_TRESHOLD);

			new_trim_for_display /= (TRIM_SWITCH_HIGH_TRESHOLD - TRIM_SWITCH_LOW_TRESHOLD)
							   / (TRIM_MAX_TEMP - TRIM_MIN_TEMP);
			new_trim_for_display += TRIM_MIN_TEMP;


			int16_t diff;
			if(new_trim_for_display > trim_for_display) {
				diff = new_trim_for_display - trim_for_display;
			}
			else
			{
				diff = trim_for_display - new_trim_for_display;
			}

			if( diff > 2) {
				trim_for_display = new_trim_for_display;
				time_to_display_trim = 5;
				timeout_counter = 0;
			}
		}
	}

	if(time_to_display_trim > 0) {
		time_to_display_trim--;
		if(time_to_display_trim == 0){
			what_to_display = DISPLAY_TEMP;
			dot1 = 0;
		}
		else
		{
			what_to_display = DISPLAY_TRIM;
			dot1 = 1;
		}
	}

}
