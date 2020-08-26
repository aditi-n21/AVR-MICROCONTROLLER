$mod51
scl equ p2.1
sda equ p2.2
org 00h
	clr p2.0
	mov r7,#80h
	mov r6,#0f2h
	acall i2cstart
	mov a,#10100000b
	acall i2cstart
	acall i2cwrite
	mov a,r7                     ;location from 03 to 07.
	acall i2cwrite
	mov a,r6
	acall i2cwrite
	acall i2cstop
;&&&&&&&&&&&&&&&&&&&&&&&&&
	acall i2cstart
	mov a,#10100000b
	acall i2cstart
	acall i2cwrite
	mov a,r7
	acall i2cwrite
	acall i2cstart
	mov a,#10100001b
	acall i2cwrite
	acall i2cread
	mov b,a 
	acall delayone
	acall i2cstop
	sjmp $

i2cstart:	
	setb sda
	acall delayone
	setb scl
	acall delayone
	clr sda
	clr scl
	ret

i2cstop:
	clr scl
	clr sda
	setb scl
	acall delayone
	setb sda
	mov c,sda
	ret
;=======================
i2cwrite:
	mov r0,#08h
i2cwrite_loop:
	rlc a
	mov sda,c
	setb scl
	acall delayone
	clr scl
	djnz r0,i2cwrite_loop	
	mov c,sda
	setb scl
	acall delayone             
	clr scl
	ret	
;=======================

i2cread:

	mov r0,#8
	;rlc a
i2cread_loop:
	setb scl
	mov c,sda
	rlc a
	acall delayone
	clr scl
	djnz r0,i2cread_loop
	ret	

 delayone:	
	mov r1,#100
      loopa: 
	djnz r1,loopa
	ret 
end