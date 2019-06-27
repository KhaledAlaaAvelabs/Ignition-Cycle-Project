/*
 * App_function.c
 *
 *  Created on: Jun 27, 2019
 *      Author: AVE-LAP-062
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include<stdio.h>

#define FREQ 6700
#define CONVERT_TO_CM    58.1
#define CYCLE_PER_USec   SysCtlClockGet()/1000000
uint8_t distance_calc(volatile uint8_t dutyCycle)
{
   volatile float ton;
   volatile float distance;
    ton=(dutyCycle*1000000/(FREQ * 100));
    distance= ton/(CONVERT_TO_CM * CYCLE_PER_USec);
    distance/=1000000;
    return distance;
}


uint8_t calc_distance(volatile uint8_t dutyCycle)
{
    volatile uint8_t distance;
    distance= (float)dutyCycle * 2.5;

    return distance;
}

enum state {ON =1, inc, dec, brake, maintain, airbag};



uint8_t CMD (uint8_t distance)
{
 volatile   uint8_t x;
  //  uint8_t buffur[50];
    if (distance >0 && distance <= 5)
    {
        UARTSend((uint8_t *)"\033 airbag speed", 16);
        x = airbag+'0';
    }
    else if (distance > 5 && distance <= 20)
    {
        UARTSend((uint8_t *)"\033 brake speed", 16);
        x = brake+'0';
    }
    else if (distance >20  && distance <=90)
    {
        UARTSend((uint8_t *)"\033 Decrease speed", 16);

        x = dec+'0';
    }
    else if (distance > 90 && distance <=160)
    {
        UARTSend((uint8_t *)"\033 maintain speed", 16);
        x = maintain+'0';
    }
    else if (distance > 160 && distance <= 255)
    {
        UARTSend((uint8_t *)"\033 inc speed", 16);
        x = inc+'0';
    }

   //    sprintf(buffur,"Distance is %d ",distance);
     //  UARTSend(x,1);
       return x;
}





void show_state (uint8_t currState, uint8_t distance)
{
    switch (currState)
    {
        case inc:
            UARTSend("Increase Speed");
            break;

        case dec:
            UARTSend("Decrease Speed");
            break;

        case maintain:
            UARTSend("Maintain Speed");
            break;

        case brake:
            UARTSend("Brake");
            break;

        case airbag:
            UARTSend("Airbag");
            break;

        default:
            break;
    }
   // sprintf(buffur,"Distance is %d ",distance);
    UARTSend(distance);
}
