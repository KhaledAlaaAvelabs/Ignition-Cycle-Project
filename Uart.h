/*
 * Uart.h
 *
 *  Created on: Jun 27, 2019
 *      Author: AVE-LAP-062
 */

#ifndef UART_H_
#define UART_H_


void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count);
uint8_t  UARTRec(uint32_t ui32Count);
void UARTIntHandler(void);
void  UARTRecstr(uint8_t *pui8Buffer,volatile uint32_t ui32Count);

#endif /* UART_H_ */
