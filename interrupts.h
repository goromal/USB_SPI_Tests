#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#include "helper_fns.h"

/*************************************************************************/
/******************** State Diagram Transition Outputs *******************/
/*************************************************************************/

typedef enum {LEFT, RIGHT} led_state_t;
led_state_t led_state;

void set_led_state(led_state_t state) // called in the main() function
{
    led_state = state;
    switch(state)
    {
        case LEFT: // Subsystem initializations
            LED_0 = HIGH;
            LED_1 = LOW;
            _reset_timer_1(SECONDS_DELAY);
            break;
        case RIGHT: // Spinning to locate the dispenser
            LED_0 = LOW;
            LED_1 = HIGH;
            _reset_timer_1(SECONDS_DELAY);
            break;
    }
}

/************************************************************************/
/****************************** Interrupts ******************************/
/************************************************************************/

// TIMER
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
    _T1IF = 0;
    switch(led_state)
    {
        case LEFT:
            if (handle_timer_1() == TRUE)
                set_led_state(RIGHT);
            break;
        case RIGHT:
            if (handle_timer_1() == TRUE)
                set_led_state(LEFT);
            break;     
    }
}

#endif	/* INTERRUPTS_H */

