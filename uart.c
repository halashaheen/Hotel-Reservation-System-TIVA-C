/*
 * uart.c
 *
 *  Created on: May 26, 2020
 *      Author: moh1969
 */
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "uart.h"


void UART0_INIT(void)
{
    SYSCTL_RCGCUART_R |= 1; /* provide clock to UART0 */
    GPIO_clk_enable(A);

    /* UART0 initialization */
    HWREG(UART0_BASE+UART_O_CTL) = 0; /* disable UART0 */

    //SETTING BAUD RATE TO 9600
    HWREG(UART0_BASE+UART_O_IBRD) = 104;//104; /* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
    HWREG(UART0_BASE+UART_O_FBRD) = 11;//11; /* fraction part, see Example 4-4 */

    HWREG(UART0_BASE+UART_O_CC) = 0; /* use system clock */
    HWREG(UART0_BASE+UART_O_LCRH) = 0x60; /* 8-bit, no parity, 1-stop bit, no FIFO */
    HWREG(UART0_BASE+UART_O_CTL) = 0x301; /* enable UART0, TXE, RXE */

    /* UART0 TX0 and RX0 use PA0 and PA1. Set them up. */
    GPIO_enable_Uart0();

    delayMs(1);

}

/* UART0 Transmit */
/* This function waits until the transmit buffer is available then */
/* writes the character in the transmit buffer. It does not wait */
/* for transmission to complete. */

void UART0Tx_char(uint8_t c)
{
    while((HWREG(UART0_BASE+UART_O_FR) & 0x20) != 0); /* wait until Tx buffer not full */
    HWREG(UART0_BASE+UART_O_DR) = c; /* before giving it another byte */
}

void UART0TX_newLine(void)
{
    UART0Tx_char(13);
    UART0Tx_char('\n');
}
void UART0TX_space(void)
{
    UART0Tx_char(' ');
}
void UART0_take_enter_action()
{
    uint8_t c;
    //press enter
    c=UART0Rx_char();
    UART0Tx_char(c);
    UART0Tx_char('\n');
}
void UART0Tx_str(uint8_t* str)
{
    uint8_t i=0;
    while(str[i]!='\0')
    {
        UART0Tx_char(str[i]);
        i++;
    }

}

uint32_t invert(uint32_t num)
{
    uint32_t inverted_num=0;
    uint8_t last_digit=num%10;
    while(num>0)
    {
        inverted_num=inverted_num*10+(last_digit);
        num/=10;
        last_digit=num%10;
    }
    return inverted_num;
}

void UART0Tx_num(uint32_t num)
{
    uint32_t inverted_num;
    uint8_t last_digit;
    if(num==0)
    {
        UART0Tx_char('0');
        return;
    }
    if(num%10==0)
    {
       num=num*10+1;
       inverted_num=invert(num);
       last_digit=inverted_num%10;
       while(inverted_num>1)
       {
          UART0Tx_char(last_digit+'0');
          inverted_num/=10;
          last_digit=inverted_num%10;
       }

    }

    else
    {

        inverted_num=invert(num);
        last_digit=inverted_num%10;
        while(inverted_num>0)
        {
           UART0Tx_char(last_digit+'0');
           inverted_num/=10;
           last_digit=inverted_num%10;
        }

    }


}

/* UART0 Receive */
/* This function waits until a character is received then returns it. */

uint8_t UART0Rx_char(void)
{
    uint8_t c;
    while((HWREG(UART0_BASE+UART_O_FR) & 0x10) != 0); /* wait until the buffer is not empty */
    c = HWREG(UART0_BASE+UART_O_DR); /* read the received data */
    return c;
}









