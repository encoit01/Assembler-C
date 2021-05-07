;   Lab 1 - decToASCII
;   converts a 16bit hexadecimal variable val into a null-terminated
;   ASCII string, which represents the signed decimal value
;   Subroutine decToASCII
;
;   Computerarchitektur / Computer Architecture
;   (C) 2021 J. Friedrich, W. Zimmermann
;   Hochschule Esslingen
;
;   Author:   W.Zimmermann, Feb 28, 2021
;            (based on code provided by J. Friedrich)
;   Modified: 05.04.2021 by Tolgahan Kandemir and Enes Coskunyürek
;

; export symbols
        XDEF decToASCII

; Defines

; Defines

; RAM: Variable data section
.data: SECTION

; ROM: Constant data
.const: SECTION

; ROM: Code section
.init: SECTION
H2A: DC.B "0123456789ABCDEF";   Define H2A ROM rable to read digit as index

;**************************************************************
; Description:  decToASCII ... converts a 16bit hexadecimal variable val into a null-terminated
;               ASCII string, which represents the signed decimal value
; Parameters:   X .. Pointer to destination string
;               D .. 16bit dec variable val in register D
; Returns:      (implicitly) ASCII string on destination of Pointer X
; Notes:        
decToASCII:
        PSHY                    ; Save register Y, X, D
        PSHX                    ;
        PSHD                    ;

                                ; Check zero
        CPD #0                  ; Check if val is negative. In case of positive, jump to positive
        BGT positiv             ;
        MOVB #'-', 0,X          ; In case of negative, set negative sign and negate D register
        COMA                    ;
        COMB                    ;
        ADDD #1                 ;
        BRA weiter              ;

positiv:
        MOVB #' ', 0,X          ; Case positve: Set positive sign to indicate positve number
        BRA weiter

weiter:
        TFR X, Y                ; X -> Y 
        MOVB #0, 6,Y            ; set end of String by appending 0

                                ; Divide X register with 10.000. Append integer result to string and 
                                ; transfer rest into D register to use it at the next position
                                ; Add '0' to get the ASCII value
        LDX #10000              ; 
        IDIV                    ; 
        PSHD                    ; 
        TFR X, D                ; 
        ADDD #'0'               ; 
        STAB  1,Y               ; put char into appropriate position

                                ; Divide X register with 1.000. Append integer result to string and 
                                ; transfer rest into D register to use it at the next position
                                ; Add '0' to get the ASCII value
        LDX #1000               ;
        PULD                    ;
        IDIV                    ; 
        PSHD                    ;
        TFR X, D                ;
        ADDD #'0'               ; 
        STAB  2,Y               ; put char into appropriate position

                                ; Divide X register with 100. Append integer result to string and 
                                ; transfer rest into D register to use it at the next position
                                ; Add '0' to get the ASCII value
        LDX #100                ; 
        PULD                    ; 
        IDIV                    ; 
        PSHD                    ; 
        TFR X, D                ; 
        ADDD #'0'               ; 
        STAB  3,Y               ; put char into appropriate position 

                                ; Divide X register with 10. Append integer result to string and 
                                ; transfer rest into D register to use it at the next position
                                ; Add '0' to get the ASCII value
        LDX #10                 ;
        PULD                    ; 
        IDIV                    ; 
        PSHD                    ; 
        TFR X, D                ; 
        ADDD #'0'               ; 
        STAB  4,Y               ; put char into appropriate position 

                                ; No divide needed here, because rest is already in D register.
                                ; Append integer result to string and 
                                ; add '0' to get the ASCII value
        PULD                    ; 
        ADDD #'0'               ; 
        STAB 5,Y                ; put char into appropriate position
                                
        PULD                    ; restore D, X, Y register 
        PULX                    ;
        PULY                    ;
        RTS                     ;
