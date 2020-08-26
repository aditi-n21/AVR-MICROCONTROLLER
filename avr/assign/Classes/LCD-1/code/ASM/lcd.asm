;W.A.P to display OK in LCD(2 lines & 16 Charac.)


$mod51
lcd equ p2
rs equ p1.0
rw equ p1.1
e equ p1.2
org 00h
	mov a,#38h
	acall comnwrt
	acall delay
	mov a,#0eh
	acall comnwrt
	acall delay
	mov a,#01h
	acall comnwrt
	acall delay
	mov a,#06h
	acall comnwrt
	acall delay
 mov a,#84h
	acall comnwrt
	acall delay
	mov a,#'M'
	acall comndata
	acall delay
	mov a,#'a'
	acall comndata
	acall delay
mov a,#'n'
	acall comndata
	acall delay
mov a,#'o'
	acall comndata
	acall delay
mov a,#'j'
	acall comndata
	acall delay
ag: sjmp ag

comnwrt:
	mov lcd,a
	clr rs
	clr rw
	setb e
	acall delay
	clr e
	ret
comndata:

	mov lcd,a
	setb rs
	clr rw
	setb e
	acall delay
	clr e
	ret

delay:
	mov r7,#255
la2:	mov r6,#0ffh
la1:	djnz r6,la1
	djnz r7,la2
	ret
end



