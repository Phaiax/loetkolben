/*
 * rotdisplay.c
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */


#include "rotdisplay.h"
#include "display.h"

uint8_t rot_seg1;
uint8_t rot_seg2;
uint8_t rot_seg3;
uint8_t rot_seg4;

uint16_t next_rot_timer = 0;
uint8_t current_rot = 0;

uint8_t is_rotating = 0;

void uint_for_rotation(uint16_t nr) {
	rot_seg4 = nr % 10;
	rot_seg3 = ((nr - rot_seg4)/10) % 10;
	rot_seg2 = ((nr - rot_seg3*10 - rot_seg4)/100) % 10;
	rot_seg1 = ((nr - rot_seg2 * 100 - rot_seg3*10 - rot_seg4)/1000) % 10;
	is_rotating = 1;

}

void stop_rotation() {
	is_rotating = 0;
}


void rotation_update() {
	next_rot_timer ++;
	if(next_rot_timer == 3000) {
		next_rot_timer = 0;

		current_rot++;
		if(current_rot == 2)
			current_rot = 0;

		if(is_rotating == 0)
			return;

		// now toogle

		switch(current_rot){
		case 0:
			nr_seg1 = rot_seg1;
			nr_seg2 = rot_seg2;
			nr_seg3 = rot_seg3;
			break;
		case 1:
			nr_seg1 = rot_seg2;
			nr_seg2 = rot_seg3;
			nr_seg3 = rot_seg4;
			break;
		case 2:
			nr_seg1 = rot_seg3;
			nr_seg2 = rot_seg4;
			nr_seg3 = rot_seg1;
			break;
		case 3:
			nr_seg1 = rot_seg4;
			nr_seg2 = rot_seg1;
			nr_seg3 = rot_seg2;
			break;
		default:
			nr_seg1 = 100;
			nr_seg2 = 100;
			nr_seg3 = 100;
		}
	}
}
