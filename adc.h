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
#define IS_TRIM 2
#define IS_NET 3
#define IS_FREE 0

#define NUM_VALUES_FOR_MEAN 4

extern uint8_t adc_use;
extern uint16_t adc_array[];
extern uint8_t adc_array_position;

extern uint16_t trim_value;
extern uint8_t new_trim_available;

void start_temperature_read();
void start_trim_read();
void init_adc_for_temperature();
void init_adc_for_trim();



void _clear_adc_array();

#endif /* ADC_H_ */
