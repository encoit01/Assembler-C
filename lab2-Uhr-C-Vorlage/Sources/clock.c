/*  Lab 2 - Thermo file for Clock program

    Hochschule Esslingen
    Authors:    Enes Coskunyürek, 764552
                Tolgahan Kandemir, 761469
*/

/* ********** GLOBAL VARIABLES **********
 * These are the global variables for the clock itself. 
 * overflowed:  Since our clock is operated in a 12-hour mode by default, the variable overflowed
 *              is used to determine whether the current time is am or pm.
 *              0 = pm; 1 = am;
 * hours:       Global variable hours represent the hours of the clock.
 * minutes:     Gloabl variable minutes represent the minutes of the clock.
 * seconds:     Global variable seconds represent the seconds of the clock.
 */
unsigned char overflowed;
unsigned char hours;
unsigned char minutes;
unsigned char seconds;

/* ********** EXTERN GLOBAL VARIABLES **********
 * To differentiate whether the clock is in normal or set mode, we have to access the global variables of printDisplay.c.
 * clockMode:   This extern global variable represents the actual mode of the clock.
 *              1 = NORMAL MODE; 0 = SET MODE;
 * timeMode:    This extern global variable represents the actual time mode of the clock.
 *              0 = 24 hour mode; 1 = 12h mode;  
 */
extern char clockMode; 
extern char timeMode;

// ********** FUNCTION HEADER DEFINITIONS **********
void initClock();
void incSeconds();
void incMinutes();
void incHours();

/* ********** Function: initClock() **********
 * Description: Function that initializes the clock with the time of 11:59:45.
 * Parameters:  
 * Return:
 */
void initClock() {
    overflowed = 0;
    hours = 11;
    minutes = 59;
    seconds = 45;
}

/* ********** Function: incSeconds() **********
 * Description: Function that increments the seconds of the clock.
 * Parameters:  -
 * Return:      -
 */
void incSeconds() {
    seconds = (unsigned char)((seconds+1) % 60);
}

/* ********** Function: incMinutes() **********
 * Description: Function that increments the minutes of the clock.
 * Parameters:  -
 * Return:      -
 */
void incMinutes() {
    minutes = (unsigned char)((minutes+1) % 60);
}

/* ********** Function: incHours() **********
 * Description: Function that increments the hours of the clock. Due to the fact
 *              that the clock only works in the 12-hour mode, the number of hours
 *              must be reset when it reaches 12. To document this overflow, we
 *              trigger the overflowed variable
 * Parameters:  -
 * Return:      -
 */
void incHours() {
    hours = hours + 1;
    if(hours == 12) {
        hours = 0;
        overflowed = (overflowed) ? 0 : 1;
    }    
}

/* ********** Function: tickClock() **********
 * Description: function with which the clock is counted up. 
 *              Notice that the clock is only counted up when the clock is in NORMAL_MODE
 * Parameters:  -
 * Return:      -
 */
void tickClock() {
    if(clockMode) {
        incSeconds();
        if(!seconds) {
            incMinutes();
            if(!minutes) {
                incHours();
            }
        }
    }
}

