/*
 * File:   main.c
 * Author: Andrew
 *
 * Created on April 21, 2017, 9:14 PM
 */

#include "interrupts.h"

int main(void) {
    initialize();
    write_LEDs(-1);
    while(1);
    return 0;
}
