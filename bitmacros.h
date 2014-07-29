/*
 * bitmacros.h
 *
 *  Created on: 03.02.2014
 *      Author: daniel
 */

#ifndef BITMACROS_H_
#define BITMACROS_H_


#define sbi(ADDRESS,BIT) ((ADDRESS) |= (1<<(BIT)))
#define cbi(ADDRESS,BIT) ((ADDRESS) &= ~(1<<(BIT)))


#endif /* BITMACROS_H_ */
