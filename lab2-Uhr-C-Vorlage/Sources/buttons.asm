;  Lab 2 - button.asm file for buttons
;
;   Hochschule Esslingen
;   Authors:    Enes Coskunyürek, 764552
;               Tolgahan Kandemir, 761469

; Export symbols
        XDEF buttonRoutine

; Import symbols
        XREF button0Pressed, button1Pressed, button2Pressed, button3Pressed

; Include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'

; Defines

; RAM: Variable data section
.data:  SECTION

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init:  SECTION

;**************************************************************
; Description:  buttonRoutine ... checks which buttons have been pressed and calls the associated subroutine
; Returns:      -
; Notes:        The associated subroutines (buttonXPressed) are defined in printDisplay.c
buttonRoutine:
    BRSET PTH, #$01, button0            
    BRSET PTH, #$02, button1 
    BRSET PTH, #$04, button2 
    BRSET PTH, #$08, button3
    BRA end

;**************************************************************
; Description:  button0 ... calls the function button0Pressed, which is defined in printDisplay.c
; Returns:      -
; Notes:        -
button0:
    JSR button0Pressed
    BRA end

;**************************************************************
; Description:  button1 ... calls the function button0Pressed, which is defined in printDisplay.c
; Returns:      -
; Notes:        -
button1:
    JSR button1Pressed
    BRA end

;**************************************************************
; Description:  button2 ... calls the function button0Pressed, which is defined in printDisplay.c
; Returns:      -
; Notes:        -
button2:
    JSR button2Pressed
    BRA end

;**************************************************************
; Description:  button3 ... calls the function button0Pressed, which is defined in printDisplay.c
; Returns:      -
; Notes:        -
button3:
    JSR button3Pressed
    BRA end

end:
    RTS
