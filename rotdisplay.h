/*
 * rotdisplay.h
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#ifndef ROTDISPLAY_H_
#define ROTDISPLAY_H_

#include <stdint.h>

/**
 * Set number to display via rotation
 */
void uint_for_rotation(uint16_t nr);

/**
 * Call this in main loop
 */
void rotation_update();

/**
 * Alternatively set these variables to the numbers to display
 */
extern uint8_t rot_seg1;
extern uint8_t rot_seg2;
extern uint8_t rot_seg3;
extern uint8_t rot_seg4;

extern uint16_t next_rot_timer;
extern uint8_t current_rot;



#endif /* ROTDISPLAY_H_ */
