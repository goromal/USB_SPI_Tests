#ifndef HELPER_FNS_H
#define	HELPER_FNS_H

#include "pin_config.h"

/***********************************************************************/
/************************** Tunable Constants **************************/
/***********************************************************************/

#define SECONDS_DELAY       0.08

/************************************************************************/
/********************* Helper Function Declarations *********************/
/************************************************************************/

typedef enum {TRUE, FALSE} my_bool;

void _reset_timer_1(float count);
my_bool handle_timer_1();
void write_LEDs(int active_LED);

/**************************************************************************/
/**************************** Helper Functions ****************************/
/**************************************************************************/

void _reset_timer_1(float seconds) // Reset timer with specific period
{
    // Truncates to integer
    timer_1_extra_cycles = 1.0 * T1_COUNT_MULT * seconds / MAX_TIMER_COUNT;
    
    TMR1 = 0;
    // Set count for the first cycle (the only non-full cycle if extra_cycles >= 1)
    PR1 = T1_COUNT_MULT * seconds - timer_1_extra_cycles * MAX_TIMER_COUNT;
    _T1IE = 1;
    T1CONbits.TON = 1; // Only turning off is necessary outside of this function
}

my_bool handle_timer_1()
{
    if (timer_1_extra_cycles > 0)
    {
        timer_1_extra_cycles--;
        return FALSE;
    }
    else
    {
        T1CONbits.TON = 0;
        TMR1 = 0;
        _T1IE = 0;
        return TRUE;
    }
}

// active LED should come directly down the SPI line
void write_LEDs(int active_LED)
{
    switch (active_LED)
    {
        case 0:
            LED_0 = HIGH;
            LED_1 = LOW;
            LED_2 = LOW;
            LED_3 = LOW;
            LED_4 = LOW;
            LED_5 = LOW;
            LED_6 = LOW;
            LED_7 = LOW;
            LED_8 = LOW;
            LED_9 = LOW;
            break;
        case 1:
            LED_0 = LOW;
            LED_1 = HIGH;
            LED_2 = LOW;
            LED_3 = LOW;
            LED_4 = LOW;
            LED_5 = LOW;
            LED_6 = LOW;
            LED_7 = LOW;
            LED_8 = LOW;
            LED_9 = LOW;
            break;
        case 2:
            LED_0 = LOW;
            LED_1 = LOW;
            LED_2 = HIGH;
            LED_3 = LOW;
            LED_4 = LOW;
            LED_5 = LOW;
            LED_6 = LOW;
            LED_7 = LOW;
            LED_8 = LOW;
            LED_9 = LOW;
            break;
        case 3:
            LED_0 = LOW;
            LED_1 = LOW;
            LED_2 = LOW;
            LED_3 = HIGH;
            LED_4 = LOW;
            LED_5 = LOW;
            LED_6 = LOW;
            LED_7 = LOW;
            LED_8 = LOW;
            LED_9 = LOW;
            break;
        case 4:
            LED_0 = LOW;
            LED_1 = LOW;
            LED_2 = LOW;
            LED_3 = LOW;
            LED_4 = HIGH;
            LED_5 = LOW;
            LED_6 = LOW;
            LED_7 = LOW;
            LED_8 = LOW;
            LED_9 = LOW;
            break;
        case 5:
            LED_0 = LOW;
            LED_1 = LOW;
            LED_2 = LOW;
            LED_3 = LOW;
            LED_4 = LOW;
            LED_5 = HIGH;
            LED_6 = LOW;
            LED_7 = LOW;
            LED_8 = LOW;
            LED_9 = LOW;
            break;
        case 6:
            LED_0 = LOW;
            LED_1 = LOW;
            LED_2 = LOW;
            LED_3 = LOW;
            LED_4 = LOW;
            LED_5 = LOW;
            LED_6 = HIGH;
            LED_7 = LOW;
            LED_8 = LOW;
            LED_9 = LOW;
            break;
        case 7:
            LED_0 = LOW;
            LED_1 = LOW;
            LED_2 = LOW;
            LED_3 = LOW;
            LED_4 = LOW;
            LED_5 = LOW;
            LED_6 = LOW;
            LED_7 = HIGH;
            LED_8 = LOW;
            LED_9 = LOW;
            break;
        case 8:
            LED_0 = LOW;
            LED_1 = LOW;
            LED_2 = LOW;
            LED_3 = LOW;
            LED_4 = LOW;
            LED_5 = LOW;
            LED_6 = LOW;
            LED_7 = LOW;
            LED_8 = HIGH;
            LED_9 = LOW;
            break;
        case 9:
            LED_0 = LOW;
            LED_1 = LOW;
            LED_2 = LOW;
            LED_3 = LOW;
            LED_4 = LOW;
            LED_5 = LOW;
            LED_6 = LOW;
            LED_7 = LOW;
            LED_8 = LOW;
            LED_9 = HIGH;
            break;
        default:
            LED_0 = LOW;
            LED_1 = LOW;
            LED_2 = LOW;
            LED_3 = LOW;
            LED_4 = LOW;
            LED_5 = LOW;
            LED_6 = LOW;
            LED_7 = LOW;
            LED_8 = LOW;
            LED_9 = LOW;
            break;
    }
}

#endif	/* HELPER_FNS_H */

