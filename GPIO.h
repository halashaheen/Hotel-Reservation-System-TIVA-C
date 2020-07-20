/*
 * GPIO.h
 *
 *  Created on: Jun 2, 2020
 *      Author: moh1969
 */

#ifndef GPIO_H_
#define GPIO_H_
#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
//PINS
#define GPIO_PIN_0              0x00000001  // GPIO pin 0
#define GPIO_PIN_1              0x00000002  // GPIO pin 1
#define GPIO_PIN_2              0x00000004  // GPIO pin 2
#define GPIO_PIN_3              0x00000008  // GPIO pin 3
#define GPIO_PIN_4              0x00000010  // GPIO pin 4
#define GPIO_PIN_5              0x00000020  // GPIO pin 5
#define GPIO_PIN_6              0x00000040  // GPIO pin 6
#define GPIO_PIN_7              0x00000080  // GPIO pin 7
//port_base
#define GPIO_PORTA_BASE         0x40004000
#define GPIO_PORTB_BASE         0x40005000
#define GPIO_PORTC_BASE         0x40006000
#define GPIO_PORTD_BASE         0x40007000
#define GPIO_PORTE_BASE         0x40024000
#define GPIO_PORTF_BASE         0x40025000
#define GPIO_PORTG_BASE         0x40026000
#define GPIO_PORTH_BASE         0x40027000
//regs offsets
#define GPIO_O_DATA             0x00000000
#define GPIO_O_DIR              0x00000400
#define GPIO_O_AFSEL            0x00000420
#define GPIO_O_DR2R             0x00000500
#define GPIO_O_DR4R             0x00000504
#define GPIO_O_DR8R             0x00000508
#define GPIO_O_DR12R            0x0000053C
#define GPIO_O_ODR              0x0000050C
#define GPIO_O_PUR              0x00000510
#define GPIO_O_PDR              0x00000514
#define GPIO_O_SLR              0x00000518
#define GPIO_O_DEN              0x0000051C
#define GPIO_O_LOCK             0x00000520
#define GPIO_O_CR               0x00000524
#define GPIO_O_AMSEL            0x00000528
#define GPIO_O_PCTL             0x0000052C
//pinType
#define GPIO_PIN_TYPE_STD       0x00000008
#define GPIO_PIN_TYPE_STD_WPU   0x0000000A
#define GPIO_PIN_TYPE_STD_WPD   0x0000000C
#define GPIO_PIN_TYPE_OD        0x00000009
//lock
#define GPIO_LOCK_KEY           0x4C4F434B
//DIR
#define INPUT        0x00000000
#define OUTPUT       0x00000001
//MACRO
#define HWREG(x)                    \
        (*((volatile uint32_t *)(x)))
//port
typedef enum
{
    A = 0x01, B = 0x02,C = 0x04,D = 0x08,E = 0x10,F = 0x20

}ports;

void GPIO_clk_enable(uint8_t port);
void GPIO_Pin_Dir_set(uint32_t port_base,uint8_t Pins,uint8_t dir);
void GPIO_aternate_fn(uint32_t port_base,uint8_t Pins);
void GPIO_enable_Uart0();
void GPIO_CONFIG_SET(uint32_t Port_Base,uint8_t Pins,uint32_t PinType);
void GPIO_Pin_Write(uint32_t Port_base, uint8_t Pins, uint8_t Val);
void GPIO_Port_Write(uint32_t Port_base, uint8_t Val);
uint32_t GPIO_Pin_Read(uint32_t Port_base, uint8_t Pins);
void unlock();
void delayMs(int n);
void delayUs(int n);
#endif /* GPIO_H_ */
