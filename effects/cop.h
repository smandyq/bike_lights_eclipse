/*
 * cop.h
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#ifndef COP_H_
#define COP_H_

#include "../bike_lights.h"

const uint8_t cop_table[] = { 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void update_cop(uint8_t start, uint8_t end);

#endif /* COP_H_ */
