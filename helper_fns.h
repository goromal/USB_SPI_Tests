#ifndef HELPER_FNS_H
#define	HELPER_FNS_H

#include "pin_config.h"

/***********************************************************************/
/************************** Tunable Constants **************************/
/***********************************************************************/

#define SECONDS_DELAY       2.5

/************************************************************************/
/********************* Helper Function Declarations *********************/
/************************************************************************/

typedef enum {TRUE, FALSE} my_bool;

void _reset_timer_1(float count);
my_bool handle_timer_1();

/************************************************************************/
/**************** Subsystem State Transition Definitions ****************/
/************************************************************************/



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

#endif	/* HELPER_FNS_H */

