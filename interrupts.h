#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#include "helper_fns.h"

/*************************************************************************/
/******************** State Diagram Transition Outputs *******************/
/*************************************************************************/

/************************************************************************/
/****************************** Interrupts ******************************/
/************************************************************************/
/*
// TIMER
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    _T1IF = 0;
    if (handle_timer_1() == TRUE)
    {
        handle_transition();
        write_LEDs(current_led);
        _reset_timer_1(SECONDS_DELAY);
    }
}
*/
// SPI
void __attribute__((interrupt, no_auto_psv)) _SPI1Interrupt(void)
{
    _SPI1IF = 0;
    write_LEDs(SPI1BUF);
    __delay_us(16);
}

#endif	/* INTERRUPTS_H */

