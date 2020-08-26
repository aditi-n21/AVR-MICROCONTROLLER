$mod51
org 00h
mov a,#0feh
here: mov p2,a
acall delay
Rl a
sjmp here
delay:

 mov r1,#255
here1: mov r2,#255
here2: djnz r2,here2
   djnz r1, here1
ret
end