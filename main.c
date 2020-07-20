

/**
 * main.c
 */

#include <stdbool.h>
#include <stdint.h>
#include "GPIO.h"
#include "uart.h"
#include "keypad_config.h"
#include "keypad.h"

#define N 10
#define password_len 4
#define ROOM_HW 5

enum state{
    unoccupied,
    occupied,
    room_cleaning
};

void LED_config()
{

    GPIO_clk_enable(B);
    GPIO_Pin_Dir_set(GPIO_PORTB_BASE,3,OUTPUT);
    GPIO_CONFIG_SET(GPIO_PORTB_BASE, 3, GPIO_PIN_TYPE_STD);
    GPIO_Port_Write(GPIO_PORTB_BASE,0);
}

uint32_t arrToInt(uint8_t* arr,uint8_t size)
{
    uint8_t i=0;
    uint32_t num=0;
    for(;i<size;i++)
    {
        num=num*10+arr[i];
    }
    return num;

}

bool inArr(uint8_t val,uint8_t* arr,uint8_t size)
{
    uint8_t exist=0;
    uint8_t i=0;
    for(;i<size;i++)
    {
        if(arr[i]==val) return true;
    }
    return false;
}
int main(void)
{
    UART0_INIT();
    keypad_init();
    LED_config();

    uint8_t rooms_Numbers[N]={0}; // assume room no. is 1 digit [ 0 --> 9]
    uint8_t i;
    uint8_t N_rooms=0;
    uint8_t c='/';
    i=0;
    UART0Tx_str((uint8_t *)"Please enter rooms no. : ");
    while(1)
    {
        c=UART0Rx_char();
        if(c!=13)
        {
            UART0Tx_char(c);
            UART0TX_space();
            rooms_Numbers[i]=c-'0';
            i++;
        }
        //if we pressed enter stop taking rooms
        else
        {
            UART0TX_newLine();
            break;

         }
    }
    N_rooms=i;


    UART0Tx_str((uint8_t*)"The Room Connected to the HW is ROOM 5");
    UART0TX_newLine();
    UART0Tx_str((uint8_t*)"NOTICE any entered Room rather than ROOM 5 won't show any Action !!!");
    UART0TX_newLine();


    uint8_t curr_room=0;
    uint8_t room_check=0;
    uint8_t room_status=0;

    uint8_t password_PC_arr[password_len]={0};
    uint32_t password_PC=0;

    /*
    uint8_t password_bluetooth_arr[password_len]={0};
    uint32_t password_bluetooth=0;*/

    uint8_t password_kb_arr[password_len]={0};
    uint32_t password_kb=0;
    uint8_t keypad_status=0;
    uint8_t keypad_flag=0;

    while(1)
    {

        i=0;
        room_status=0;
        keypad_flag=0;
        keypad_status=0;

        UART0TX_newLine();
        UART0Tx_str((uint8_t*)"Please enter Room No. : ");
        c=UART0Rx_char();
        UART0Tx_char(c);
        curr_room=c-'0';
        if(!inArr(curr_room,rooms_Numbers,N_rooms))
        {
            UART0TX_newLine();
            UART0Tx_str((uint8_t*)"This Room N0. doesn't exist in the system");
            UART0TX_newLine();
            GPIO_Port_Write(GPIO_PORTB_BASE,2);//B1 ==> red led
            continue;

        }
        if(curr_room == ROOM_HW) room_check=1;
        else room_check=0;
        UART0TX_newLine();

        UART0Tx_str((uint8_t*)"Please enter Room status : ");

        //enter room status
        room_status=UART0Rx_char();
        UART0Tx_char(room_status);
        room_status-='0';
        UART0TX_newLine();

        switch(room_status)
        {
        case unoccupied:

            if(room_check)
            {
                //green off and red
                GPIO_Port_Write(GPIO_PORTB_BASE,0);
                UART0Tx_str((uint8_t*)"This room is unoccupied");
                UART0TX_newLine();
            }

            break;
        case room_cleaning:

            if(room_check)
            {
                //yellow ON only
                GPIO_Port_Write(GPIO_PORTB_BASE,1);
                UART0Tx_str((uint8_t *)"Its time for Room Cleaning =)");
                UART0TX_newLine();

            }
            break;
        case occupied:

            //let receptionist enter password via PC
             UART0Tx_str((uint8_t*)"PC Room Password :");


             for(i=0;i<password_len;i++)
               {
                 c=UART0Rx_char();
                 UART0Tx_char(c);
                 password_PC_arr[i]=c-'0';
                }

             UART0TX_newLine();
             password_PC=arrToInt(password_PC_arr, i);

            if(room_check)
            {
                // yellow off
                //GPIO_Port_Write(GPIO_PORTB_BASE,0);

                UART0Tx_str((uint8_t*)"Guest Enters the Room Password....");
                UART0TX_newLine();
                UART0Tx_str((uint8_t *)"Keypad Password : ");

                //taking password form keypad
                //Solving Bouncing Problem
                i=0;
                while(i<4)
                {

                  keypad_status=keypad_kbhit();
                  c=keypad_getkey();
                  if((keypad_status==1 && keypad_flag == 0)){
                      keypad_flag = 1;
                      password_kb_arr[i]=c-'0';
                      UART0Tx_char(c);
                      i++;
                      delayMs(5);}

                  else if(keypad_status== 0){
                      keypad_flag = 0;
                      delayMs(5);}
                  }
                UART0TX_newLine();

                password_kb=arrToInt(password_kb_arr,i);


                i=0;
                if(password_kb==password_PC)
                {
                    // yellow ON only
                    GPIO_Port_Write(GPIO_PORTB_BASE,1);
                    UART0Tx_str((uint8_t *)"Dear Guest you entered password correctly =) ");
                    UART0TX_newLine();
                }


                else
                {
                    // red ON
                    GPIO_Port_Write(GPIO_PORTB_BASE,2);
                    UART0Tx_str((uint8_t *)"Incorrect password !!!!");
                    UART0TX_newLine();
                }
            }

            break;

        }


    }

}




/*
 *
#include <stdbool.h>
#include <stdint.h>
#include "GPIO.h"
#include "uart.h"
#include "keypad_config.h"
#include "keypad.h"

void led()
{
    GPIO_clk_enable(B);
    GPIO_Pin_Dir_set(GPIO_PORTB_BASE,7,OUTPUT);
    GPIO_CONFIG_SET(GPIO_PORTB_BASE, 7, GPIO_PIN_TYPE_STD);
    GPIO_Port_Write(GPIO_PORTB_BASE,1);
}

int main(void)
{
    UART0_INIT();
    keypad_init();
    uint8_t c ,keypad_status=0,keypad_flag=0;



    while(1)
                    {

                      keypad_status=keypad_kbhit();
                      c=keypad_getkey();
                      if((keypad_status==1 && keypad_flag == 0)){
                          keypad_flag = 1;
                          UART0Tx_char(c);
                          delayMs(5);}

                      else if(keypad_status== 0){
                          keypad_flag = 0;
                          delayMs(5);}
                      }

}
*/
