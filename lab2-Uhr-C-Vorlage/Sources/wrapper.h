/*  Wrappers for assembler functions in LCD.asm and decToASCII.asm

    Computerarchitektur / Computer Architecture
    (C) 2021 J. Friedrich, W. Zimmermann
    Hochschule Esslingen

    Author:  W.Zimmermann, Feb 28, 2021
    Modified by:    Enes Coskunyürek, 764552
                    Tolgahan Kandemir, 761469
*/


#ifndef __wrapper__
#define __wrapper__

/* ********** FUNCTION HEADER DEFINITIONS **********
 * Notice: initLCD, delay_10ms, buttonRoutine, initLED can called without Wrapper functions as they don't have parameters and return values
 */
void initLCD(void);
void delay_10ms(void);
void buttonRoutine();
void initLED(void);

void toggleLED(void);
void toggleLED_Wrapper(char value);
void decToASCII(void);
void decToASCII_Wrapper(char *txt, int val);
void writeLine(void);
void WriteLine_Wrapper(char *text, char line);
void setLED(void);
void setLED_Wrapper(char value);


/* ********** Function: decToASCII_Wrapper() **********
 * Description: decToASCII_Wrapper loads the X-Register with the pointer where the ASCII Values should be written into.
 *              The value that should be converted into ASCII will be loaded into the D register
 * Parameters:  char *txt   Pointer to memory where ASCII characters should be written into
 *              int val     Value that should be converted into ASCII
 * Return:      -
 */
void decToASCII_Wrapper(char *txt, int val) {   
    asm {
        LDX txt
        LDD val
    }
    decToASCII();
}

/* ********** Function: WriteLine_Wrapper() **********
 * Description: WriteLine_Wrapper loads into the X-register the pointer of the buffer that will be written to the display.
 *              To determine the line that should be written, we load the line number into the B-register.
 * Parameters:  char *txt   Pointer to the buffer, that should be written onto the display
 *              char line   Line specification in which the buffer should be written.
 * Return:      -
 */
void WriteLine_Wrapper(char *text, char line) {
    asm {	
        LDX text
        LDAB line
    }
    writeLine();
}

/* ********** Function: setLED_Wrapper() **********
 * Description: setLED_Wrapper loads into the B-register the pins that should be switched ON.
 *              After that the LEDs will be switched ON by calling setLED from LED.asm
 * Parameters:  char value  Load the 8 bit value into the B-register
 * Return:      -
 */
void setLED_Wrapper(char value) {
    asm {
        LDAB value
    }
    setLED();
}

/* ********** Function: toggleLED_Wrapper() **********
 * Description: toggleLED_Wrapper loads into the B-register the pins that should be toggled.
 *              After that the LEDs will be toggled by calling toggleLED from LED.asm
 * Parameters:  char value  Load the 8 bit value into the B-register
 * Return:      -
 */
void toggleLED_Wrapper(char value) {
    asm {
        LDAB value
    }
    toggleLED();
}

#endif