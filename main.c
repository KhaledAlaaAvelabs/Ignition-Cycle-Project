
/**
* main.c
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

#include "UART.h"


int main(void)
{
   uint8_t data=0;
   //

   //
   // Prompt for text to be entered.
   //
   UARTSend((uint8_t *)"\033[2JEnter text: ", 16);

      //
      // Loop forever echoing data through the UART.
      //
      while(1)
      {
         data= UARTRec(1);
         if(data=='o')
         {
             GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
         }
      }

return 0;
}
