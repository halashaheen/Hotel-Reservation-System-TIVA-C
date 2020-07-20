
#include <stdint.h>
#include <stdbool.h>
#include "GPIO.h"
#include "keypad_config.h"
#include "keypad.h"
#define KEYPAD_ROW GPIO_PORTE_BASE
#define KEYPAD_COL GPIO_PORTF_BASE

void keypad_init(void)
{   GPIO_clk_enable(keypad_port_clock_row);
    GPIO_clk_enable(keypad_port_clock_col);
    unlock();
    GPIO_Pin_Dir_set(keypad_port_row, R1 | R2 | R3 | R4, OUTPUT);
    GPIO_CONFIG_SET(keypad_port_row, R1 | R2 | R3 | R4,GPIO_PIN_TYPE_OD);
    GPIO_Pin_Dir_set(keypad_port_col , C1 | C2 | C3 | C4 , INPUT );
    GPIO_CONFIG_SET(keypad_port_col , C1 | C2 | C3 | C4 , GPIO_PIN_TYPE_STD_WPU );
}

unsigned char keypad_getkey(void)
{
const unsigned char keymap[4][4] = {
{ '1', '2', '3', 'A'},
{ '4', '5', '6', 'B'},
{ '7', '8', '9', 'C'},
{ '*', '0', '#', 'D'},
};
int row, col;
/* check to see any key pressed first */
GPIO_Pin_Write(keypad_port_row, R1 | R2 | R3 | R4 , 0x00);
col=((GPIO_Pin_Read(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col == 0x0F) return 0; /* no key pressed */
/* If a key is pressed, it gets here to find out which key. */
/* Although it is written as an infinite loop, it will take one of the
breaks or return in one pass.*/
while (1)
{
row = 0;
/* enable row 0 */
GPIO_Pin_Write(keypad_port_row, R1 | R2 | R3 | R4 , 0x1C);
delayUs(2); /* wait for signal to settle */
col=((GPIO_Pin_Read(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col != 0x0F) break;

row = 1;
/* enable row 1 */
GPIO_Pin_Write(keypad_port_row, R1 | R2 | R3 | R4 , 0x1A);
delayUs(2); /* wait for signal to settle */
col=((GPIO_Pin_Read(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col != 0x0F) break;

row = 2;
/* enable row 2 */
GPIO_Pin_Write(keypad_port_row, R1 | R2 | R3 | R4 , 0x16);
delayUs(2); /* wait for signal to settle */
col=((GPIO_Pin_Read(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col != 0x0F) break;

row = 3;
/* enable row 3 */
GPIO_Pin_Write(keypad_port_row, R1 | R2 | R3 | R4 , 0x0E);
delayUs(2); /* wait for signal to settle */
col=((GPIO_Pin_Read(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col != 0x0F) break;
return 0; /* if no key is pressed */
}
/* gets here when one of the rows has key pressed */
if (col == 0x0E) return keymap[row][0]; /* key in column 0 */
if (col == 0x0D) return keymap[row][1]; /* key in column 1 */
if (col == 0x0B) return keymap[row][2]; /* key in column 2 */
if (col == 0x07) return keymap[row][3]; /* key in column 3 */
return 0; /* just to be safe */
}

/* This is a non-blocking function. */
/* If a key is pressed, it returns 1. */
/* Otherwise, it returns a 0 (not ASCII 0).*/
unsigned char keypad_kbhit(void)
{
int col;
/* check to see any key pressed */
/* enable all rows */
GPIO_Pin_Write(keypad_port_row, R1 | R2 | R3 | R4 , 0x00);
/* read all columns */
col=((GPIO_Pin_Read(keypad_port_col, C1 | C2 | C3 | C4 ))&0x0F);
if (col == 0x0F)
return 0; /* no key pressed */
else
return 1; /* a key is pressed */
}











































