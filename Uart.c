
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
#include "Uart.h"



//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        ROM_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}
//uint8_t* // uint8_t *pui8Buffer,
uint8_t  UARTRec(uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
   volatile uint8_t data=0;
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        while(!ROM_UARTCharsAvail(UART0_BASE))
        {
        }
       data= ROM_UARTCharGetNonBlocking(UART0_BASE);

    }
    return data;
}




void UARTIntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART0_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(UART0_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(ROM_UARTCharsAvail(UART0_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        ROM_UARTCharPutNonBlocking(UART0_BASE,
                                   ROM_UARTCharGetNonBlocking(UART0_BASE));

        //
        // Blink the LED to show a character transfer is occuring.
        //
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

        //
        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
        //
        SysCtlDelay(SysCtlClockGet() / (1000 * 3));

        //
        // Turn off the LED
        //
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);

    }
}


void  UARTRecstr(uint8_t *pui8Buffer,volatile uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
   volatile uint8_t data=0; volatile uint8_t i=0;
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        while(!ROM_UARTCharsAvail(UART0_BASE))
        {
        }
       data= ROM_UARTCharGetNonBlocking(UART0_BASE);

           pui8Buffer[i++]= data;


    }

}
