/*
 * trim.h
 *
 *  Created on: 01.08.2014
 *      Author: daniel
 */

#ifndef TRIM_H_
#define TRIM_H_

#include <stdint.h>

extern uint16_t trim_for_display;

extern uint16_t trim_value;
extern uint8_t new_trim_value_available;


void trim_update();

#endif /* TRIM_H_ */
