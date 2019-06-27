


#ifndef ADAPTIVE_H_
#define ADAPTIVE_H_


#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"

void show_state (uint8_t currState, uint8_t distance);
uint8_t CMD (uint8_t distance);

#endif /* ADAPTIVE_H_ */
