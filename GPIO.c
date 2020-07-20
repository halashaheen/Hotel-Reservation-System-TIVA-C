/*
 * GPIO.c
 *
 *  Created on: Jun 2, 2020
 *      Author: moh1969
 */
#include <stdbool.h>
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "GPIO.h"

void GPIO_clk_enable(uint8_t Port)
{
    //enable clock to GPIO at clock gating register
    SYSCTL_RCGCGPIO_R |= Port;
    //check if clock is assigned to GPIO port


}
void GPIO_Pin_Dir_set(uint32_t port_base,uint8_t Pins,uint8_t dir)
{

    if(dir)   HWREG(port_base+GPIO_O_DIR)|=(Pins);
    else      HWREG(port_base+GPIO_O_DIR)&=~(Pins);

    //the Pin is not a peripheral function
    HWREG(port_base + GPIO_O_AFSEL) &=~(Pins);

}
void GPIO_enable_Uart0(){

    GPIO_CONFIG_SET(GPIO_PORTA_BASE, (GPIO_PIN_0|GPIO_PIN_1), GPIO_PIN_TYPE_STD);
    GPIO_aternate_fn(GPIO_PORTA_BASE,(GPIO_PIN_0|GPIO_PIN_1));
    HWREG(GPIO_PORTA_BASE+GPIO_O_PCTL) = 0x11; /* configure PA0 and PA1 for UART */
}

void GPIO_aternate_fn(uint32_t port_base,uint8_t Pins)
{HWREG(port_base+GPIO_O_AFSEL) |=(Pins);}

void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
    for(j = 0; j < 3180; j++)
    {} /* do nothing for 1 ms */
}
/* delay n microseconds (16 MHz CPU clock) */
void delayUs(int n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3; j++)
{} /* do nothing for 1 us */
}

void GPIO_CONFIG_SET(uint32_t Port_Base,uint8_t Pins,uint32_t PinType)
{   //Set the output drive strength to GPIO_STRENGTH_12MA
    HWREG(Port_Base + GPIO_O_DR2R) |= (Pins);
    HWREG(Port_Base + GPIO_O_DR4R) |= (Pins);
    HWREG(Port_Base + GPIO_O_DR8R) |= (Pins);
    HWREG(Port_Base + GPIO_O_SLR) &=~(Pins);
    HWREG(Port_Base + GPIO_O_DR12R) |= (Pins);

    //pintype

    //open drain pin
    if(PinType==GPIO_PIN_TYPE_OD)
     {
        HWREG(Port_Base + GPIO_O_ODR)|=(Pins);
        HWREG(Port_Base + GPIO_O_PDR)&=~(Pins);
        HWREG(Port_Base + GPIO_O_DEN)|=(Pins);
        HWREG(Port_Base + GPIO_O_PUR) &=~(Pins);

     }
     // normal
    else if(PinType==GPIO_PIN_TYPE_STD)
    {
       HWREG(Port_Base + GPIO_O_ODR)&=~(Pins);
       HWREG(Port_Base + GPIO_O_PDR)&=~(Pins);
       HWREG(Port_Base + GPIO_O_DEN)|=(Pins);
       HWREG(Port_Base + GPIO_O_PUR) &=~(Pins);

    }
    else if(PinType==GPIO_PIN_TYPE_STD_WPU)
    {
       HWREG(Port_Base + GPIO_O_ODR)&=~(Pins);
       HWREG(Port_Base + GPIO_O_PDR)&=~(Pins);
       HWREG(Port_Base + GPIO_O_DEN)|=(Pins);
       HWREG(Port_Base + GPIO_O_PUR)|=(Pins);

    }
    else if(PinType==GPIO_PIN_TYPE_STD_WPD)
    {
       HWREG(Port_Base + GPIO_O_ODR)&=~(Pins);
       HWREG(Port_Base + GPIO_O_PDR)|=(Pins);
       HWREG(Port_Base + GPIO_O_DEN)|=(Pins);
       HWREG(Port_Base + GPIO_O_PUR)&=~(Pins);

    }

    // not Analog mode select
    HWREG(Port_Base + GPIO_O_AMSEL) & ~(Pins);

}


void GPIO_Pin_Write(uint32_t Port_base, uint8_t Pins, uint8_t Val)
{HWREG(Port_base + (GPIO_O_DATA + (Pins << 2))) = Val;}


void GPIO_Port_Write(uint32_t Port_base, uint8_t Val)
{ HWREG(Port_base+(0x3FC)) = Val;}

uint32_t GPIO_Pin_Read(uint32_t Port_base, uint8_t Pins){
     return (HWREG(Port_base + (GPIO_O_DATA + (Pins << 2))));
}

uint32_t GPIO_PORT_Read(uint32_t Port_base){
        return HWREG(Port_base+(0x43FC));
}

void unlock()
{

    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY ;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR)=0xFF;
    HWREG(GPIO_PORTE_BASE+GPIO_O_LOCK)=GPIO_LOCK_KEY ;
    HWREG(GPIO_PORTE_BASE+GPIO_O_CR)=0xFF;

}
