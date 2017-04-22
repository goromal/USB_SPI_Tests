#ifndef PIN_CONFIG_H
#define	PIN_CONFIG_H

#include <xc.h>
#pragma config ICS = PGx3 // DEBUG
#pragma config OSCIOFNC = OFF // Pin 8 NOT used as clock
#pragma config FNOSC = FRC  // 8e6 hz Timer -> fcy = 4e6 hz
#define FCY                     4000000UL
#include <libpic30.h>       // For __delay functions

#define LED_0                   _LATB15
#define LED_1                   _LATB14
#define LED_2                   _LATB13
#define LED_3                   _LATB12
#define LED_4                   _LATA6
#define LED_5                   _LATB9
#define LED_6                   _LATA0
#define LED_7                   _LATA1
#define LED_8                   _LATB0
#define LED_9                   _LATB1

#define HIGH                    1
#define LOW                     0

void pin_init()
{
    // Configure digital / analog 
    ANSA = 0x00;
    ANSB = 0x00;
    LATA = 0;
    LATB = 0;
    
    // Configure inputs / outputs (unused configured as inputs)
    _TRISA0 = 0;
    _TRISA1 = 0;
    _TRISB0 = 0;
    _TRISB1 = 0;
    _TRISB2 = 1;
    _TRISA2 = 1;
    _TRISA3 = 1;
    _TRISB15 = 0;
    _TRISB14 = 0;
    _TRISB13 = 0;
    _TRISB12 = 0;
    _TRISA6 = 0;
    _TRISB9 = 0;
    _TRISB8 = 1;
    _TRISB7 = 1;
}

#define MAX_TIMER_COUNT     65535   // For 16-bit timer
#define T1_COUNT_MULT       15625   // For chosen oscillator and pre-scale

int timer_1_extra_cycles;

void timer_config()
{
    // TIMER 1
    T1CONbits.TON = 0; // begins off
    T1CONbits.TCS = 0; // internal clock source
    T1CONbits.TCKPS = 11; // 1:256 Pre-scaling
    TMR1 = 0;
    _T1IP = 5;
    _T1IE = 1;
    _T1IF = 0;
}

void initialize() // include all above functions
{
    pin_init();
    timer_config();
}

#endif	/* PIN_CONFIG_H */