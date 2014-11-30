/*
 * breathe.h
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#ifndef BREATHE_H_
#define BREATHE_H_

const uint8_t sin_table[] =
{ 5, 6, 7, 9, 11, 13, 16, 20, 24, 28, 34, 40, 48, 56, 65, 75, 87, 99, 113, 127,
		141, 156, 171, 186, 200, 213, 225, 235, 244, 250, 254, 255, 254, 250,
		244, 235, 225, 213, 200, 186, 171, 156, 141, 127, 113, 99, 87, 75, 65,
		56, 48, 40, 34, 28, 24, 20, 16, 13, 11, 9, 7, 6, 5, 4 };

void update_breathe(uint8_t start, uint8_t end);

#endif /* BREATHE_H_ */
