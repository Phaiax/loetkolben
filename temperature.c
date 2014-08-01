/*
 * temperature.c
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#include "temperature.h"

uint16_t temp_value = 0;
uint8_t new_temp_available = 0;
uint16_t temp_for_display;


void temperature_update() {
	if(new_temp_available) {
		new_temp_available = 0;
		temp_for_display = temp_value;
	}
}
