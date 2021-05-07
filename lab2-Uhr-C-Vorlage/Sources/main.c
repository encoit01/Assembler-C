/*  Lab 2 - Main C file for Clock program

    Computerarchitektur / Computer Architecture
    (C) 2021 J. Friedrich, W. Zimmermann
    Hochschule Esslingen

    Author:  W.Zimmermann, Feb 28, 2021
    Co-Authors: Enes Coskunyürek, 764552
                Tolgahan Kandemir, 761469
*/

#include <hidef.h>                              // Common defines
#include <mc9s12dp256.h>                        // CPU specific defines

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

// Global variables
unsigned char clockEvent = 0;

// main call
void main(void) 
{   EnableInterrupts;                               // Global interrupt enable

    initLED();                    		            // Initialize the LEDs
    initTicker();                                   // Initialize the time ticker
    initLCD();                    		            // Initialize the LCD
    initClock();                                    // Initialize the clock
    initThermo();                                   // initialize Thermo

    for(;;) {   
        if (clockEvent) {
            showDisplay();                           // have a look in the showDisplay function, which is located in the printDisplay.c                          
            clockEvent = 0;
    	}
    }
}