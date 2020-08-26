$mod51
org 00h
here1: mov dptr,#100h
here: 
clr a
movc a,@a+dptr
mov p2,a
inc dptr
acall delay
cjne a,#0,here
sjmp here1


DELAY:
	MOV	R1,#25
L3:	MOV	R2,#255
L2:	MOV	R3,#255
L1:	DJNZ	R3,L1
	DJNZ	R2,L2
	DJNZ	R1,L3
	RET

org 100h
db 3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh,0
END
