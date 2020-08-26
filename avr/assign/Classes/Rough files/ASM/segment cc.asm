
$mod51
org 00h
clr a
here1:
mov dptr, #150h
here: 
mov P1, a
clr a
movc a,@a+dptr
inc dptr
acall delay
cjne a,#0,here
sjmp here1
delay:
mov r0,#255
ag2: mov r1,#255
ag1: mov r2,#25
ag: djnz r2,ag
djnz r1,ag1
djnz r0,ag2
ret

org 150h
DB 0c0h,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh,0
END

