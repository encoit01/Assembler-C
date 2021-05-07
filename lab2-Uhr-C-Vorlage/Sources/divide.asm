;  Lab 2 - Thermo file for Clock program
;
;   Hochschule Esslingen
;   Authors:    Enes Coskunyürek, 764552
;               Tolgahan Kandemir, 761469


; Export symbols
    XDEF divide
    XDEF celsius

; Import symbols
    XREF digitalTemp

; Include derivative specific macros
    INCLUDE 'mc9s12dp256.inc'

; RAM: Variable data section
.data:  SECTION
    celsius:  DS.W 1 

; ROM: Constant data
.const: SECTION
    
; ROM: Code section
.init:  SECTION

; ********** divide **********
; Description:  To convert the digitalTemp into a celsius temperature with range from -30 to 70 degrees, we first
;               need to multiply the value with 100 and then divide it threw 1023. After that we subtract 30 of it
;               and write the into celsius converted value into the variable "celsius".
;* Parameters:  -
;* Return:      -
;*/
divide:
    PSHD                ; save all registers
    PSHX                ;
    PSHY                ;

    LDD digitalTemp     ; load variable digitalTemp into D register
    LDY #100            ; 
    EMUL                ; digitalTemp (D-Reg.) * 100(Y-Reg.)
    
    LDX #1023           ; Y-D register as 32 Bit value represents the digital Value * 100
    EDIV                ; Now, we divide this 32 Bit value threw 1023

    CPD #512            ; Round the result by incrementing the Y register, if the remainder is higher or equal to 512.
    BLO END
    INY

END:                    ; After the division subtract the celsius value with 30 and store the final celsius value into celsius
    STY celsius         ;
    LDD celsius         ;
    SUBD #30            ;
    STD celsius         ;

    PULY                ; pull registers and return
    PULX                ;
    PULD                ;
    RTS                 ;

