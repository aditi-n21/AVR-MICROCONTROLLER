$mod51
org 00h
rs equ P2.0
rw equ P2.1
en equ P2.2
mov dptr,#mycmd
back1: clr a
movc a,@a+dptr
acall cmdwrt
acall delay
inc dptr
cjne a,#0,back1
mov dptr,#mydata
back: clr a
movc a,@a+dptr
acall datawrt
acall delay
inc dptr
cjne a,#0,back
here: mov a,#1ch
acall cmdwrt
acall delay
sjmp here
cmdwrt:
mov P1,A
clr rs
clr rw
setb en
acall delay
clr en
ret

datawrt:
mov P1,A
setb rs
clr rw
setb en
acall delay
clr en
ret

delay:
mov r0,#255
ag1: mov r1,#255
ag: djnz r1,ag
 djnz r0,ag1
ret

org 150h
mydata: DB 'Welcome to CETPA',0
mycmd: DB 38h,01h,06h,0eh,80h,0
END