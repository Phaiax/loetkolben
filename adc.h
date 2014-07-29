/*
 * adc.h
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>


#define IS_TEMP 1
#define IS_POTI 2
#define IS_NET 3
#define IS_FREE 0

extern uint8_t adc_use;


void start_temperature_read();
void init_adc_for_temperature();

#endif /* ADC_H_ */
