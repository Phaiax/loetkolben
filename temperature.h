/*
 * temperature.h
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include <stdint.h>


extern uint16_t temp_value;
extern uint16_t temp_for_display;
extern uint8_t new_temp_available;

void temperature_update();



#endif /* TEMPERATURE_H_ */
