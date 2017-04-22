/*
 * File:   main.c
 * Author: Andrew
 *
 * Created on April 21, 2017, 9:14 PM
 */

#include "interrupts.h"

int main(void) {
    initialize();
    set_led_state(LEFT);
    while(1);
    return 0;
}
