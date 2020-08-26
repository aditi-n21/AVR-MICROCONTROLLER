$mod51
org 00h
here: setb P1.0
ACALL Delay
Clr P1.0
ACALL Delay
Sjmp here

Delay: Mov r0,#5
ag: djnz r0,ag
ret
end
