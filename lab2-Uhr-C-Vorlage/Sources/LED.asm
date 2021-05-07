;   Lab 1 - Problem 2.1
;   Incrementing a value once per second and binary output to LEDs
;
;   Computerarchitektur / Computer Architecture
;   (C) 2021 J. Friedrich, W. Zimmermann
;   Hochschule Esslingen
;
;   Author:   W.Zimmermann, Feb 28, 2021
;            (based on code provided by J. Friedrich)
;   Modified: by Tolgahan Kandemir and Enes Coskunyürek
;

; export symbols
        XDEF initLED
        XDEF setLED
        XDEF getLED
        XDEF toggleLED

; import symbols


; include derivative specific macros
        INCLUDE 'mc9s12dp256.inc'


; ROM: Code section
.init: SECTION

;**************************************************************
; Description:  initLED ... initilizes all required ports to drive the LEDs on the Board. At the end, all LEDs are turned off
; Parameters:   -
; Returns:      -
; Notes:        -
initLED:
        BSET DDRJ, #2                   ; Bit Set:   Port J.1 as output
        BCLR PTJ,  #2                   ; Bit Clear: J.1=0 --> Activate LEDs

        ifdef SEVEN_SEGS_OFF        
                MOVB #$0F, DDRP         ; Port P.3..0 as outputs (seven segment display control)
                MOVB #$0F, PTP          ; Turn off seven segment display
        endif

        MOVB #$FF, DDRB                 ; $FF -> DDRB:  Port B.7...0 as outputs (LEDs)
        MOVB #0, PORTB
        RTS

;**************************************************************
; Description:  setLED ... This subroutine defines which of the LEDs should be turned off and on
; Parameters:   B .. indicates which of the LEDs should be turned on (1) and turned off(0)
; Returns:      B .. B register indicates the current state of the LEDs
; Notes:        -
setLED:
        STAB PORTB
        RTS

;**************************************************************
; Description:  getLED ... This subroutine returns 8Bit value that indicates the current state of the LEDs
; Parameters:   -
; Returns:      B .. B register indicates the current state of the LEDs
; Notes:        -
getLED:
        LDAB PORTB
        RTS

;**************************************************************
; Description:  toggleLED .. The bits in the parameter define, which of the LEDs should be toggled
; Parameters:   B .. Parameter that defines, which of the LEDs should be toggled
; Returns:      -
; Notes:        -
toggleLED:
        EORB PORTB
        STAB PORTB
        RTS  
        