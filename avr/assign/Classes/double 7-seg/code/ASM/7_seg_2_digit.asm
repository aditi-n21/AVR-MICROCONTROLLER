;WAP to display value from 0 to 99 with a proper delay.


	$MOD51
	ORG 00H
AG:	MOV	P1,#0C0H
	LCALL	DIGIT
	MOV	P1,#0F9H
	LCALL	DIGIT
	MOV	P1,#0A4H
	LCALL	DIGIT
	MOV	P1,#0B0H
	LCALL	DIGIT
	MOV	P1,#99H
	LCALL	DIGIT
	MOV	P1,#92H
	LCALL	DIGIT
	MOV	P1,#82H
	LCALL	DIGIT
	MOV	P1,#0F8H
	LCALL	DIGIT
	MOV	P1,#80H
	LCALL	DIGIT
	MOV	P1,#98H
	LCALL	DIGIT
	LJMP	AG
DIGIT:
	MOV	P0,#0C0H
	ACALL	DELAY
	MOV	P0,#0F9H
	ACALL	DELAY
	MOV	P0,#0A4H
	ACALL	DELAY
	MOV	P0,#0B0H
	ACALL	DELAY
	MOV	P0,#99H
	ACALL	DELAY
	MOV	P0,#92H
	ACALL	DELAY
	MOV	P0,#82H
	ACALL	DELAY
	MOV	P0,#0F8H
	ACALL	DELAY
	MOV	P0,#80H
	ACALL	DELAY
	MOV	P0,#98H
	ACALL	DELAY
	RET

DELAY:
	MOV	R1,#25
L3:	MOV	R2,#255
L2:	MOV	R3,#255
L1:	DJNZ	R3,L1
	DJNZ	R2,L2
	DJNZ	R1,L3
	RET
	END

