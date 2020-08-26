$mod 51
;7-Segment Display
	enableDIGIT3 EQU P3.2
	enableDIGIT4 EQU P3.3

ZERO   EQU  11000000b
ONE    EQU  11111001b
TWO    EQU  10100100b
THREE  EQU  10110000b
FOUR   EQU  10011001b
FIVE   EQU  10010010b
SIX    EQU  10000010b
SEVEN  EQU  11111000b
EIGHT  EQU  10000000b
NINE   EQU  10010000b
DOT    EQU  11111111b

MOV 20h,#ZERO
MOV 21h,#ONE
MOV 22h,#TWO
MOV 23h,#THREE
MOV 24h,#FOUR
MOV 25h,#FIVE
MOV 26h,#SIX
MOV 27h,#SEVEN
MOV 28h,#EIGHT
MOV 29h,#NINE

MOV R0, #20h
MOV R1, #22h

PDATA EQU P2 ; Connect 8 pins here

Start:
        JB P3.1, check1
                SETB 50h
        check1:
        JB P3.0, check2
                SETB 52h
        check2:
                JNB P3.1, cont1
                        JNB 50h, cont1
                                CLR 50h
                                LCALL INC_7SEGMENT     
        cont1:
                JNB P3.0, cont2
                        JNB 52h, cont2
                                CLR 52h
                                LCALL DEC_7SEGMENT
        cont2:
                LCALL SHOW_7SEGMENT
SJMP Start

SHOW_7SEGMENT:
        MOV PDATA,#00h

        setb enableDIGIT3
        MOV     A,@R1
        MOV PDATA,A
        LCALL smallDelay
        clr enableDIGIT3
       
        setb enableDIGIT4
        MOV     A,@R0
        MOV PDATA,A
        LCALL smallDelay        
        clr enableDIGIT4
RET

INC_7SEGMENT:
        CJNE @R1, #TWO, increment
        sjmp doneinc
        increment:
                CJNE @R0, #NINE, incr0
                MOV R0, #20h
                INC R1
                SJMP doneinc
                incr0:
                        INC R0
        doneinc:
RET

DEC_7SEGMENT:
        CJNE @R0, #ZERO, dec0
        CJNE @R1, #ZERO, dec1
        sjmp donedec
        dec1:
                MOV R0, #29h
                DEC R1
                SJMP donedec
        dec0:
                DEC R0
        donedec:
RET
smallDelay:
                CLR TF1
                CLR TR1
                MOV TH1,#76
                MOV TL1,#01
                MOV TMOD,#01
                SETB TR1
                JNB TF1,$
RET

end
