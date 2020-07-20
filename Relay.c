/*
 * Relay.c
 *
 *  Created on: Jun 4, 2020
 *      Author: moh1969
 */

#include <stdint.h>
#include <stdbool.h>
#include "GPIO.h"
#include "Relay.h"

void Relay_init(void){
    GPIO_clk_enable(B);
    GPIO_Pin_Dir_set(GPIO_PORTB_BASE, GPIO_PIN_0 , OUTPUT);
    GPIO_CONFIG_SET(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_PIN_TYPE_STD);
}
void Relay_vid_close(void){
    GPIO_Pin_Write(GPIO_PORTB_BASE, GPIO_PIN_0, 0x00);
}
void Relay_vid_open(void){
    GPIO_Pin_Write(GPIO_PORTB_BASE, GPIO_PIN_0, 0x01);
}



