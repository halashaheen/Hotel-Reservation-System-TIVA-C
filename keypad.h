#ifndef KEYPAD_H_
#define KEYPAD_H_
#define CYCLES_FROM_TIME_US(ui32ClockFreq, ui32Time_uS)                       \
    (((ui32Time_uS) == 0) ? 0 :                                               \
    (((ui32ClockFreq) / 1000000) * ((((ui32Time_uS) * 1000) - 1) / 1000)) + 1)
		
#define ui32ClockFreq 16000000		

void keypad_init(void);
unsigned char keypad_getkey(void);
unsigned char keypad_kbhit(void);
#endif /* KEYPAD_H_ */
