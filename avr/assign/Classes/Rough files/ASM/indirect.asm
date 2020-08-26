$mod51
org 00h
mov 11h,#02h
mov 12h,#04h
mov 13h,#06h
mov 14h,#08h
mov r0,#11h
mov a,@r0
mov r1,a
inc r0
mov a,@r0
mov r2,a
inc r0
mov a,@r0
mov r3,a
inc r0
mov a,@r0
mov r4,a
inc r0

END