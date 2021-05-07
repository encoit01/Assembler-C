/*  Lab 2 - Thermo file for Clock program

    Hochschule Esslingen
    Authors:    Enes Coskunyürek, 764552
                Tolgahan Kandemir, 761469
*/

#include "wrapper.h"
#include <mc9s12dp256.h> 

/* ********** GLOBAL VARIABLES **********
 * clockMode:   This global variable represents the actual mode of the clock.
 *              1 = NORMAL MODE; 0 = SET MODE;
 * counter:     This global variable is used to determine how many senconds a button is pressed.
 *              Have a look to the explanation in function button3Pressed().
 * timeMode:    This global variable represents the actual time mode of the clock.
 *              0 = 24 hour mode; 1 = 12h mode;  
 */
char clockMode = 1; 
char counter = 0;
char timeMode = 0;

/* ********** EXTERN GLOBAL VARIABLES **********
 * These are the global variables that have already been defined in the clock.c file. 
 * overflowed:  Since our clock is operated in a 12-hour mode by default, the variable overflowed
 *              is used to determine whether the current time is am or pm.
 *              0 = pm; 1 = am;
 * hours:       Extern global variable hours represent the hours of the clock.
 * minutes:     Extern gloabl variable minutes represent the minutes of the clock.
 * seconds:     Extern global variable seconds represent the seconds of the clock.
 */
extern unsigned char overflowed;
extern unsigned char hours;
extern unsigned char minutes;
extern unsigned char seconds;

/* ********** GLOBAL VARIABLES **********
 * Global Variabeles for the time converted into ASCII. Theoretically, you could only define a
 * single array and gradually convert the numbers to ASCII and read them out. For legible reasons
 * we decided against it:
 * hoursInASCII:    Represent the hours converted into ASCII.
 * minutesInASCII:  Represent the minutes converted into ASCII.
 * secondsInASCII:  Represent the seconds converted into ASCII.
 */
char secondsInASCII[7];
char minutesInASCII[7];
char hoursInASCII[7];

/* ********** GLOBAL VARIABLES **********
 * These are the two buffers for the LCD display, which are shown on the display.
 * buffer0:     This represents the first line of the display. The first line will contain the current
 *              time, 24/12 hour-mode and the current ambient temperature e.g.:
 *              24H mode:   13:56:05    30°C
 *              12H mode:   03:43:09pm -10°C  
 * buffer1:     This represents the seconds line of the display. The second line shows the 
                follwing output periodically every 10 seconds:
                "Enes.C + Tolga.K"
                "(C) IT 2020"
 */
char buffer0[17];
char buffer1[17];

/* ********** GLOBAL VARIABLES **********
 * Extern global Variabele for the temperature converted into ASCII. 
 * temp:        contains temperature converted into ASCII characters.
 */
extern char temp[7];


/* ********** FUNCTION HEADER DEFINITIONS **********
 * In this case we could use header files however, due to time and effort we decided against it 
 */
char* strcpy(char* destination, char* source);
void showDisplay();
void fillBuffer0();
void fillBuffer1();
void showBuffer0();
void showBuffer1();
void checkButtons();
void toggleUsMode();

/* ********** Function: strcpy() **********
 * Description: The string copy function copies the string from the second parameter into the first pointer.
 *              It returns a char pointer to the new string.
 * Parameters:  char* destination   - pointer to destination string
 *              char* source        - pointer to source string
 * Return:      char* start         - poiner to first position of new string
 */
char* strcpy(char* destination, char* source) {
    char* start = destination;

    while(*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';
    return start;
}

/* ********** Function: showDisplay() **********
 * Description: Entry function. Check which buttons are pressed in order to differenciate in which mode
                the clock is operating. In NORMAL_MODE let the clock tick, update the Temperature and fill
                the buffers in order to output them in the first and seconds row of the display
 * Parameters:  -
 * Return:      -
 */
void showDisplay() {
    checkButtons();
    if(clockMode) {
        // NORMAL_MODE
        tickClock();
        updateThermo();
        fillBuffer0();
        fillBuffer1();
        showBuffer0();
        showBuffer1();
    } else {
        // SET_MODE
        fillBuffer0();
        showBuffer0();
    }
}

/* ********** Function: showBuffer0() **********
 * Description: Writes buffer0 onto the display on line0 with help of WriteLine_Wrapper() function.
 * Parameters:  -
 * Return:      -
 */
void showBuffer0() {
    WriteLine_Wrapper(buffer0, 0);
}

/* ********** Function: showBuffer1() **********
 * Description: Writes buffer1 onto the display on line1 with help of WriteLine_Wrapper() function.
 * Parameters:  -
 * Return:      -
 */
void showBuffer1() {
    WriteLine_Wrapper(buffer1, 1);
}

/* ********** Function: fillBuffer0() **********
 * Description: This function fills the buffer of the first line.
 *              The time and the temperature will be written into the buffer. 
 * Parameters:  -
 * Return:      -
 */
void fillBuffer0() {
    // convert seconds, minutes and hours into ASCII characters
    decToASCII_Wrapper(secondsInASCII, seconds);
    decToASCII_Wrapper(minutesInASCII, minutes);
    if(!timeMode) {
        decToASCII_Wrapper(hoursInASCII, hours + 12 * overflowed);
    } else {
        if(!hours) {
            decToASCII_Wrapper(hoursInASCII, (char) 12);
        } else {
            decToASCII_Wrapper(hoursInASCII, hours);
        }
    }

    // fill the first positions with the time. Remember that the required ASCII caracters
    // are at positions 4 and 5 in the associated arrays
    buffer0[0] = *(hoursInASCII + 4);
    buffer0[1] = *(hoursInASCII + 5);
    buffer0[2] = ':';
    buffer0[3] = *(minutesInASCII + 4);
    buffer0[4] = *(minutesInASCII + 5);
    buffer0[5] = ':';
    buffer0[6] = *(secondsInASCII + 4);
    buffer0[7] = *(secondsInASCII + 5);

    // Depending on the the time mode append am/pm to the time
    if(!timeMode) {
        buffer0[8] = ' ';
        buffer0[9] = ' ';
    } else {
        if(overflowed) {
            buffer0[8] = 'p';
            buffer0[9] = 'm';
        } else {
            buffer0[8] = 'a';
            buffer0[9] = 'm';
        }
    }

    //Write the temperature in celsius right justified into the buffer
    buffer0[10] = ' ';
    buffer0[11] = *(temp);
    buffer0[12] = *(temp + 4);
    buffer0[13] = *(temp + 5);
    buffer0[14] = 0xB0;
    buffer0[15] = 'C';
    buffer0[16] = '\0';
}

/* ********** Function: fillBuffer1() **********
 * Description: This function fills the buffer1 with the names of the authors of the lab or IT 2020
 * Parameters:  -
 * Return:      -
 */
void fillBuffer1() {
    // The display in buffer 1 changes every 10 seconds.
    // Determine the phase using an integer division.
    int temp = (int)seconds;
    temp = (int)temp / 10;
    if(temp % 2) {
        strcpy(buffer1, "Enes.C + Tolga.K");
    } else {
        strcpy(buffer1, "(C) IT 2020");
    }
}

/* ********** Function: checkButtons() **********
 * Description: This functions calls the buttonRoutine in decToASCII.asm every second.
 * Parameters:  -
 * Return:      -
 */
void checkButtons() {
    buttonRoutine();
}

/* ********** Function: button0Pressed() **********
 * Description: This function is called, when PTH.0 is triggered. This button has 2 different tasks:
 *                  - If the clock operates in NORMAL_MODE, then only the am/pm indicator should be triggered on the display.
 *                  - If the clock operated in SET_MODE, then the seconds should be incremented.
 * Parameters:  -
 * Return:      -
 */
void button0Pressed() {
    if(clockMode) {
        // Trigger AM/PM view
        timeMode = (timeMode) ? 0 : 1;
    } else {
        // Increment Seconds and refresh the display view
        incSeconds();
        fillBuffer0();
        showBuffer0();
    }
}

/* ********** Function: button1Pressed() **********
 * Description: This function is called, when PTH.1 is triggered.
 *              It increments the minutes of the clock if it operates in SET_MODE
 * Parameters:  -
 * Return:      -
 */
void button1Pressed() {
    // increment min
    if(!clockMode) {
        incMinutes();
        fillBuffer0();
        showBuffer0();
    }
}

/* ********** Function: button2Pressed() **********
 * Description: This function is called, when PTH.2 is triggered.
 * Description: This function increments the hours if the clock operates SET_MODE
 * Parameters:  -
 * Return:      -
 */
void button2Pressed() {
    if(!clockMode) {
        incHours();
        fillBuffer0();
        showBuffer0();
    }
}

/* ********** Function: button3Pressed() **********
 * Description: This function switches the clock modes if the button on PTH.3 is pressed for 2 seconds.
 * Parameters:  -
 * Return:      -
 */
void button3Pressed() {
    // To determine 2 seconds, use a counter variable, that will be incremented in every clock-cycle.
    counter++;
    if(counter == 2) {
        clockMode = (clockMode) ? 0 : 1;
        toggleLED_Wrapper(0x80);
        counter = 0;
    }
}