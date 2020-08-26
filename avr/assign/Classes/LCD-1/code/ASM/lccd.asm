;W.A.P to display OK in LCD(2 lines & 16 Charac.)


$mod51
lcd equ p1
rs equ p2.0
rw equ p2.1
e equ p2.2
org 00h
mov dptr,#show1
back1: clr a
movc a,@a+dptr
acall comnwrt
acall delay
inc dptr
cjne a,#0,back1

	
	
 mov dptr,#show
back: clr a
movc a,@a+dptr
acall comndata
acall delay
inc dptr
cjne a,#0,back

ag:  
mov r0,#16
hey: mov a,#1ch
acall comnwrt
acall delay
djnz r0,hey
mov r0,#16
hey1: mov a,#18h
acall comnwrt
acall delay
djnz r0,hey1

sjmp ag

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

Org 150h
show: DB 'AMIT',0
show1: DB 38h,01h,06h,0eh,80h,0
end





