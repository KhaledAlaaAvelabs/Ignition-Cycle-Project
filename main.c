//*****************************************************************************
//
// uart_echo.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

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
#include "App_function.h"
#include "driverlib/ssi.h"
//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>UART Echo (uart_echo)</h1>
//!
//! This example application utilizes the UART to echo text.  The first UART
//! (connected to the USB debug virtual serial port on the evaluation board)
//! will be configured in 115,200 baud, 8-n-1 mode.  All characters received on
//! the UART are transmitted back to the UART.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************




//*****************************************************************************
//
// This example demonstrates how to send a string of data to the UART.
//
//*****************************************************************************



int main(void)
{
 volatile   uint8_t data=-1;
 volatile   uint8_t duty[3]={0};
 volatile   uint8_t i=0;
 volatile   uint8_t j=100;
 volatile   uint8_t current_state;
 volatile   uint8_t ulDataTx[2];
    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
 //   ROM_FPUEnable();
 //   ROM_FPULazyStackingEnable();

    //
    // Set the clocking to run directly from the crystal.
    //
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);

    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Enable the GPIO pins for the LED (PF2).
    //
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    //
    // Enable the peripherals used by this example.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable processor interrupts.
    //
    ROM_IntMasterEnable();

    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    ROM_UARTConfigSetExpClk(UART0_BASE, ROM_SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
    ROM_IntEnable(INT_UART0);
    ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

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
        /*  if(data==-1)
          {
              GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
              duty[i++]=data;
              data=-1;
          }*/
          //UARTRecstr(duty,3);
          duty[i++]=data;
          if(i==3)break;
       /*   if(duty[0]=='2' && duty[1] =='0' && duty[2]=='0')
                  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);*/
       }
       data=0;

       for(i=0;i<3;i++)
       {
           data= data + ((duty[i]-'0')*j);
           j/=10;
       }

       if(data==50)
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
       data =calc_distance(data);
  //     if(data)
     //       GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
       current_state=CMD(data);//return state current
       current_state -='0';
       show_state (current_state,data);
   //    ulDataTx[0]=current_state;
   //    ulDataTx[1]=data;
   /*    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
       GPIOPinConfigure(GPIO_PA2_SSI0CLK);
       GPIOPinConfigure(GPIO_PA3_SSI0FSS);
       GPIOPinConfigure(GPIO_PA4_SSI0RX);
       GPIOPinConfigure(GPIO_PA5_SSI0TX);
       GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 |
                          GPIO_PIN_2);
       SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                              SSI_MODE_MASTER, 1000000, 8);

       SSIEnable(SSI0_BASE);
       SSIDataPut(SSI0_BASE, current_state);
       SSIDataPut(SSI0_BASE, data);
       while(SSIBusy(SSI0_BASE))*/
          {
          }


     /*  while(SSIDataGetNonBlocking(SSI0_BASE, &ulDataRx[0]))
         {
         }*/

       /*slave*/
     /*  SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
       GPIOPinConfigure(GPIO_PA2_SSI0CLK);
       GPIOPinConfigure(GPIO_PA3_SSI0FSS);
       GPIOPinConfigure(GPIO_PA4_SSI0RX);
       GPIOPinConfigure(GPIO_PA5_SSI0TX);
       GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 |
                                 GPIO_PIN_2);
       SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                                     SSI_MODE_MASTER, 1000000, 8);

        SSIEnable(SSI0_BASE);
        while(SSIDataGetNonBlocking(SSI0_BASE, &ulDataRx[0]))
           {
           }*/

}
