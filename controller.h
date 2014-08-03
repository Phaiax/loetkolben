/*
 * controller.h
 *
 *  Created on: 02.08.2014
 *      Author: daniel
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdint.h>


// with those two vars its possible to define how many percent of cycles the heat will be turned on
// typical values: 10%: heat_max_cycle_count=10, heat_on_cycle_count= 1;
// typical values: 50%: heat_max_cycle_count=2, heat_on_cycle_count= 1;
extern int8_t heat_max_cycles;
extern int8_t heat_on_cycles_counter;

void control_init();
void control_update();

#endif /* CONTROLLER_H_ */
