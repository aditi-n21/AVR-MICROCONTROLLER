$mod51
org 00h
here: 
mov P1,#55h
acall delay
mov P1,#0aah
acall delay

sjmp here

delay:
mov r0,#255
ag1: mov r1,#50
ag2: mov r3,#10
ag: djnz r3,ag
djnz r1,ag2
djnz r0,ag1
ret
end