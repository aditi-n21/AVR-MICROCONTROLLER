$mod51
org 00h
mov a,#0feh
here: mov P1,A
acall delay
RR A
sjmp here


delay:
mov r0,#255
ag1: mov r1,#255
ag2: mov r3,#10
ag: djnz r3,ag
djnz r1,ag2
djnz r0,ag1
ret

END