/*
 * defines.h
 *
 *  Created on: 01.08.2014
 *      Author: daniel
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define nop() asm volatile("nop")

#define TRIM_MAX_TEMP 400
#define TRIM_MIN_TEMP 200


// Tresholds in adc units, from 0 to 1024

#define TRIM_SWITCH_LOW_TRESHOLD 10
#define TRIM_SWITCH_HIGH_TRESHOLD 1019

extern uint16_t counter;
extern uint16_t timeout_counter;

#define TIMEOUT_TIME 770
#define COUNTER_UPDATE_MODULO 500


#endif /* DEFINES_H_ */
