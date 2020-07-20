/*
 * uart.h
 *
 *  Created on: May 26, 2020
 *      Author: moh1969
 */



#define ui32ClockFreq 16000000

#define HWREG(x)                                                              \
        (*((volatile uint32_t *)(x)))

#define CYCLES_FROM_TIME_US(ui32ClockFreq, ui32Time_uS)                       \
    (((ui32Time_uS) == 0) ? 0 :                                               \
    (((ui32ClockFreq) / 1000000) * ((((ui32Time_uS) * 1000) - 1) / 1000)) + 1)

#define UART0_BASE              0x4000C000  // UART0
#define UART_O_CTL              0x00000030  // UART Control
#define UART_O_IBRD             0x00000024  // UART Integer Baud-Rate Divisor
#define UART_O_FBRD             0x00000028  // UART Fractional Baud-Rate
#define UART_O_CC               0x00000FC8  // UART Clock Configuration
#define UART_O_LCRH             0x0000002C  // UART Line Control
#define UART_O_DR               0x00000000  // UART Data
#define UART_O_FR               0x00000018  // UART Flag

#ifndef UART_H_
#define UART_H_
#include <stdbool.h>
#include <stdint.h>
#define ui32ClockFreq 16000000
void UART0_INIT(void);
void UART0Tx_char(uint8_t c);
void UART0Tx_str(uint8_t* str);
void UART0Tx_num(uint32_t num);
uint8_t UART0Rx_char(void);
void UART0TX_newLine(void);
void UART0TX_space(void);
#endif /* UART_H_ */
