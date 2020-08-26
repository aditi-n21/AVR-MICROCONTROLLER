$mod51
org 00h
here: mov P1,#00000000b
mov P3,#00000000b
mov P2,#00000000b
acall delay
mov P1,#0ffh
mov P3,#0ffh
mov P2,#0ffh
acall delay
sjmp here

delay: 
mov r0,#255
back2: mov r1,#225
back1: mov r2,#10
back: djnz r2,back
djnz r1, back1
djnz r0, back2
ret
end