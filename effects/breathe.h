/*
 * breathe.h
 *
 *  Created on: Nov 30, 2014
 *      Author: sam
 */

#ifndef BREATHE_H_
#define BREATHE_H_

const uint8_t sin_table[] =
{31,35,38,43,48,53,59,65,72,79,87,95,104,113,123,133,144,154,165,176,186,196,206,215,224,232,239,244,249,252,254,255,254,252,249,244,239,232,224,215,206,196,186,176,165,154,144,133,123,113,104,95,87,79,72,65,59,53,48,43,38,35,31,28};

void update_breathe(uint8_t start, uint8_t end);

#endif /* BREATHE_H_ */
