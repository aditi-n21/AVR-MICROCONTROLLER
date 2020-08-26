$mod51
lcd equ p2
rs equ p1.0
rw equ p1.1
e equ p1.2
org 00h

	acall lcdini
	mov dptr,#show1
	acall comndata
ag:	sjmp ag


lcdini:
	mov a,#38h
	acall comnwrt
	acall delay
	mov a,#0eh
	acall comnwrt
	acall delay
	mov a,#01h
	acall comnwrt
	mov a,#06h
	acall comnwrt
	acall delay
	mov a,#80h
	acall comnwrt
	acall delay
	ret
comnwrt:
	mov lcd,a
	clr rs
	clr rw
	setb e
	acall delay
	clr e
	ret
comndata:
nxt:	
	clr a
	movc a,@a+dptr
	cjne a,#00h,in
	sjmp out
in:	mov lcd,a
	setb rs
	clr rw
	setb e
	acall delay
	clr e
	inc dptr
	acall delay
	sjmp nxt
out:	ret

delay:
	mov r7,#255
la2:	mov r6,#0ffh
la1:	djnz r6,la1
	djnz r7,la2
	ret

org 200h
show1: db 'WelCome To CETPA',0

end
