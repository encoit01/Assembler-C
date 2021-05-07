/*  Lab 2 - Thermo file for Clock program

    Hochschule Esslingen
    Authors:    Enes Coskunyürek, 764552
                Tolgahan Kandemir, 761469
*/

#include <hidef.h>                      // common defines and macros
#include <mc9s12dp256.h>                // derivative information

/* ********** GLOBAL VARIABLES **********
 * These are the global variables for the file termo.c.
 * digitalTemp: digitalTemp represents the value for the measured temperature.
 *              digitalTemp only takes  values within the range of 0 - 1023.
 * temp:        temp represents the temperature converted to ASCII.
 */
unsigned int digitalTemp;
char temp[7];

/* ********** EXTERN GLOBAL VARIABLES **********
 * celsius:     celsius represents the temperature, which was calculated using the variable digitalTemp.
                For calculating celsius we use divide.asm
 */
extern unsigned int celsius;

// ********** FUNCTION HEADER DEFINITIONS **********
void initThermo();
void updateThermo();

/* ********** Function: initThermo() **********
 * Description: initTermo initializes the ADC converter and sets all necessary 
 *              bits to the corresponding control variables.
 * Parameters:  -
 * Return:      -
 */
void initThermo() {
    // Enable ATD0 and allow interrupts.
    ATD0CTL2 = 0b11000010;

    // Set Sequence count to single measurment
    ATD0CTL3 = 0b00001000;

    // Clock divider
    ATD0CTL4 = 0b00000101;
}

/* ********** Function: updateThermo() **********
 * Description: This function starts the measurment on channel 7. After reading the value 
                we call the divide function that calculates the calsius value and converts
                it into the ASCII representation. 
 * Parameters:  -
 * Return:      -
 */
void updateThermo() {
    // start the single measurment on channel 7
    ATD0CTL5 = 0b10000111;

    // convert analog value into digital 
    divide();

    // temporare = (char)((analogTemp * 100) / 1023);
    // temporare = temporare - 30;
    decToASCII_Wrapper(temp, (char)celsius);
}