/*
 * display.h
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */



#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include <avr/io.h>


#define DISPLAY_TEMP 1
#define DISPLAY_INTERNAL_TEMP 3
#define DISPLAY_INTERNAL_TEMP_VALUE 5
#define DISPLAY_TRIM 2
#define DISPLAY_OFF 6

extern uint8_t what_to_display;

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
#define ABC_O (SEG_1 | SEG_2 | SEG_3 | SEG_5 | SEG_6 | SEG_7)
#define ABC_F (SEG_1 | SEG_2 | SEG_4 | SEG_5)
#define ABC_U (SEG_2 | SEG_3 | SEG_5 | SEG_6 | SEG_7)


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


/**
 * Sets the 7-segment output pins so that <nr> is displayed
 */
inline void writenr(uint8_t nr) {

	PORTA &= (NR_OFF | SEG_DOT); // all off

	switch (nr) {
	case 0:
		PORTA |= NR_0;
		break;
	case 1:
		PORTA |= NR_1;
		break;
	case 2:
		PORTA |= NR_2;
		break;
	case 3:
		PORTA |= NR_3;
		break;
	case 4:
		PORTA |= NR_4;
		break;
	case 5:
		PORTA |= NR_5;
		break;
	case 6:
		PORTA |= NR_6;
		break;
	case 7:
		PORTA |= NR_7;
		break;
	case 8:
		PORTA |= NR_8;
		break;
	case 9:
		PORTA |= NR_9;
		break;
	case ABC_O:
		PORTA |= ABC_O;
		break;
	case ABC_F:
		PORTA |= ABC_F;
		break;
	case ABC_U:
		PORTA |= ABC_U;
		break;
	}
}


/**
 * Activates or deactivates the dot
 */
inline void writedot(uint8_t dot) {
	if(dot) {
		PORTA |= SEG_DOT;
	} else {
		PORTA &= ~SEG_DOT;
	}
}
#endif /* DISPLAY_H_ */
