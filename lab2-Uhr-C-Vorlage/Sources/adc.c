/*  Lab 2 - Thermo file for Clock program

    Hochschule Esslingen
    Authors:    Enes Coskunyürek, 764552
                Tolgahan Kandemir, 761469
*/

#include <hidef.h>                      // common defines and macros
#include <mc9s12dp256.h>                // derivative information

/* ********** EXTERN GLOBAL VARIABLES **********
 * digitalTemp: digitalTemp represents the value for the measured temperature.
 *              digitalTemp only takes values within the range of 0 - 1023.
 */
extern unsigned int digitalTemp;

/* ********** Interrupt Service Routine (22): adcISR  **********
 * Description: This routine reads the data register 0 and resets the interrupt flag
 * Parameters:  -
 * Return:      -
 */
void interrupt 22 adcISR(void) {  
    // read temperature from ATD0DR0 register 
    digitalTemp = ATD0DR0;

    // reset interrupt flag
    ATD0CTL2 = ATD0CTL2 | 0x01;
}