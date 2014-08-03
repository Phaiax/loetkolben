/*
 * temperature.c
 *
 *  Created on: 29.07.2014
 *      Author: daniel
 */

#include "temperature.h"

uint16_t temp_value = 0;
uint8_t new_temp_available = 0;
uint16_t temp_for_display;

uint16_t internal_temp_value;
uint16_t internal_temp_for_display;
uint8_t new_internal_temp_available;


void temperature_update() {
	if(new_temp_available) {
		new_temp_available = 0;
		temp_for_display = temp_value;
		// the problem is, that the Attiny gets much warmer than the opamp chip
		// so we can't use the internal temperature to compensate the offset of
		// the opamp input

		// opamp offset calibration is now calibrated to 25°C

		//temp_for_display = temp_value * 0.3571
		// 				   = temp_value * (0.3571*2^7 / 2^7);
		//				  ~= temp_value * 46 / 128


		// if we use uint32 here, it will eat 20% of flash

		temp_for_display = (temp_value * 46);
		temp_for_display = temp_for_display >> 7;
		temp_for_display = temp_for_display + 32; // thermoelement only returns delta t to room temp

		// curr: 60°C 120 -> 212ADC , good would be 78.4ADC, so

		// measurements:
		// ADC      Temp
		// 15   	30
		// 34,33	38
		// 42       42
		//*120		75
		// 249		120
		// 260		126
		//*400		175

		// T = m*ADC + b
		// m = (175-75) / (400-120) = 1/2.8 = 0.3571
		// m2 = (175-75) / (400-120) = 1/2.8 = 0.3571
		// b = 175 - m*400 = 32.14
		// b2 = 30 - 15*m = 24.64
		// b3 = 42 - 42*m = 27

		// with m=1/2.24
		// b3 = 23.25
		// b2 = 23.30
		// b = -3.57

		// it gets a little bit nonlinear but i think b is the best value


	}

	if(new_internal_temp_available) {
		// doc: 25°C = 300ADC , 85°C = 370ADC
		// 70 Steps for 60K -> m = 1.1666 Steps/K (we don't correct gradient)
		// my calibration: 33°C = 318ADC
		//                 36°C = 323ADC
		//                 42°C = 330ADC (-> m = (330-320)/(42-33) = 0.3333 Steps/K
		//                               (->0°C = 326-30m = 316)

		internal_temp_for_display = internal_temp_value - 316;

		// now every step represents 3 degrees
		// (abuse new_internal_temp_available  variable)
		//new_internal_temp_available = internal_temp_for_display * 3;

		internal_temp_for_display = internal_temp_for_display * 3;

		new_internal_temp_available = 0;

	}

}

