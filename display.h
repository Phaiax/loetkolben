/*
 * display.h
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */



#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>


#define SEG_4 0x01
#define SEG_2 0x02
#define SEG_5 0x04
#define SEG_7 0x08
#define SEG_6 0x10
#define SEG_1 0x20
#define SEG_3 0x40
#define SEG_DOT 0x80
//#define SEG_NUMMASK 0xEF

/*#define SEG_4 0x08
#define SEG_2 0x08
#define SEG_1 0x08
#define SEG_3 0x08
#define SEG_DOT 0x80
#define SEG_6 0x08
#define SEG_7 0x08
#define SEG_5 0x08
//#define SEG_NUMMASK 0xEF
*/


/*
 # 1 #
 2   3
 # 4 #
 5   6
 # 7 #  DOT */

#define NR_OFF 0x00
#define NR_1 (SEG_3 | SEG_6)
#define NR_2 (SEG_1 | SEG_3 | SEG_4 | SEG_5 | SEG_7)
#define NR_3 (SEG_1 | SEG_3 | SEG_4 | SEG_6 | SEG_7)
#define NR_4 (SEG_2 | SEG_3 | SEG_4 | SEG_6)
#define NR_5 (SEG_1 | SEG_2 | SEG_4 | SEG_6 | SEG_7)
#define NR_6 (SEG_1 | SEG_2 | SEG_4 | SEG_5 | SEG_6 | SEG_7)
#define NR_7 (SEG_1 | SEG_3 | SEG_6)
#define NR_8 (SEG_1 | SEG_2 | SEG_3 | SEG_4 | SEG_5 | SEG_6 | SEG_7)
#define NR_9 (SEG_1 | SEG_2 | SEG_3 | SEG_4 | SEG_6 | SEG_7)
#define NR_0 (SEG_1 | SEG_2 | SEG_3 | SEG_5 | SEG_6 | SEG_7)

// private: void writenr(uint8_t nr);
// private: void writedot(uint8_t dot);

// call during main loop
void display_update();
void display_init();

void uint_for_display();

/**
 * Write to these variables to set the displayed value
 *
 * (in rotation mode, write instead to rot_seg1 and so on)
 */
extern uint8_t nr_seg1;
extern uint8_t nr_seg2;
extern uint8_t nr_seg3;

extern uint8_t dot1;
extern uint8_t dot2;
extern uint8_t dot3;




#endif /* DISPLAY_H_ */
