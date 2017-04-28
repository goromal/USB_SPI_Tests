#ifndef PIN_CONFIG_H
#define	PIN_CONFIG_H

#include <xc.h>
#pragma config ICS = PGx3 // DEBUG
#pragma config OSCIOFNC = OFF // Pin 8 NOT used as clock
#pragma config FNOSC = FRC  // 8e6 hz Timer -> fcy = 4e6 hz
#define FCY                     4000000UL
#include <libpic30.h>       // For __delay functions

#define LED_0                   _LATA0
#define LED_1                   _LATA1
#define LED_2                   _LATB0
#define LED_3                   _LATB1
#define LED_4                   _LATB2
#define LED_5                   _LATA2
#define LED_6                   _LATA6
#define LED_7                   _LATB9
#define LED_8                   _LATB8
#define LED_9                   _LATB7

#define HIGH                    1
#define LOW                     0

void pin_init()
{
    // Configure digital / analog 
    ANSA = 0x00;
    ANSB = 0x00;
    LATA = 0;
    LATB = 0;
    
    // Configure inputs / outputs 
    _TRISA0 = 0;
    _TRISA1 = 0;
    _TRISB0 = 0;
    _TRISB1 = 0;
    _TRISB2 = 0;
    _TRISA2 = 0;
    
    _TRISA6 = 0;
    _TRISB9 = 0;
    _TRISB8 = 0;
    _TRISB7 = 0;
}

#define MAX_TIMER_COUNT     65535   // For 16-bit timer
#define T1_COUNT_MULT       15625   // For chosen oscillator and pre-scale

int timer_1_extra_cycles;

void config_timer()
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

void config_SPI() // Datasheet, pg 161
{
    /*
     * Required pins (2-pin mode):
     *      - Pin 17 Serial Data Input
     *      - Pin 15 Shift Clock Input
     */
    SPI1BUF = 0x00;     // Clear buffer
    _SPI1IF = 0;        // Clear bit for interrupt
    _SPI1IE = 1;        // Set bit for interrupt
    _SPI1IP = 0b111;    // Interrupt is priority 7 (highest) (pg 99)
    
    // SPI1CON1 (pg 166), SPI1CON2 (pg 167) =========================
    
    _DISSDO = 1;        // SDO pin 16 functions as normal I/O
    _MODE16 = 0;        // 8-bit communication
    _SMP = 0;           // cleared in slave mode
    _CKE = 0;           // change on transition from IDLE CLOCK
                        // to ACTIVE CLOCK
    //_SSEN not used in 2-pin mode
    _CKP = 0;           // IDLE = clock LOW, ACTIVE = clock HIGH
    _MSTEN = 0;         // slave mode
    _SPRE = 0b110;      // Secondary prescale 2:1
    _PPRE = 0b10;       // Primary prescale 4:1
    _FRMEN = 0;         // Framed SPI support disabled
    _SPIBEN = 0;        // Enhanced buffer mode disabled
    
    // SPI1STAT Register (Register 16-1)
    _SPIROV = 0;        // Clear overflow flag
    _SPIEN = 1;         // Enable SPI module
}

void initialize() // include all above functions
{
    pin_init();
    config_timer();
    config_SPI();
}

#endif	/* PIN_CONFIG_H */