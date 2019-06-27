/*
 * App_function.h
 *
 *  Created on: Jun 27, 2019
 *      Author: AVE-LAP-062
 */

#ifndef APP_FUNCTION_H_
#define APP_FUNCTION_H_

uint8_t distance_calc(volatile uint8_t dutyCycle);
uint8_t calc_distance(volatile uint8_t dutyCycle);

uint8_t CMD (uint8_t distance);
void show_state (uint8_t currState, uint8_t distance);

#endif /* APP_FUNCTION_H_ */
