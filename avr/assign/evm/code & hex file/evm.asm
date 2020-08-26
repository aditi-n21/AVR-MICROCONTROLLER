$mod51
in equ p0
scl bit p2.4
sda bit p2.5
org 0h
ljmp main1
org 0003h
ljmp intrupt
org 0020h
main1: setb p3.2
mov ie,#81h
setb tcon.0
mov tmod,#20h
mov scon,#50h
mov th1,#-3
setb tr1
setb scl
setb sda
setb p2.6 
mov r5,#00h
mov r6,#00h
mov r7,#00h
main: mov in,#11111110b
mov a,in
anl a,#11111110b
cjne a,#11111110b,j
sjmp main
j: mov a,in
jb acc.1,j2
inc r5
clr  p2.6
acall delay1
acall delay1
setb p2.6
busy1: jnb p0.1,busy1
ljmp eewrite
sjmp main
j2: jb acc.2,j3
inc r6
clr  p2.6
acall delay1
acall delay1
setb p2.6
busy2: jnb p0.2,busy2
ljmp Iewrite
sjmp main
j3: jb acc.3,j4
inc r7
clr  p2.6
acall delay1
acall delay1
setb p2.6
busy3: jnb p0.3,busy3
ljmp IIwrite
j4: sjmp main
intrupt: 
mov dptr,#mydata0
acall routs
acall delay_15ms
mov r1,#05h
acall step
mov dptr,#mydata1
acall routs
acall delay_15ms
mov r1,#06h
acall step
mov dptr,#mydata2
acall routs
acall delay_15ms
mov r1,#07h
acall step
reti
eewrite: mov a,#10100000b
acall i2cstart
acall i2cwrite    
mov a,#05h
mov 30h,a
acall i2cwrite
mov a,r5
acall i2cwrite
acall i2cstop
acall jkl
ljmp main
Iewrite: mov a,#10100000b
acall i2cstart
acall i2cwrite    
mov a,#06h
mov 30h,a
acall i2cwrite
mov a,r6
acall i2cwrite
acall i2cstop
acall jkl 
ljmp main
IIwrite: mov a,#10100000b
acall i2cstart
acall i2cwrite    
mov a,#07h
mov 30h,a
acall i2cwrite
mov a,r7
acall i2cwrite
acall i2cstop
acall jkl 
ljmp main
i2cstart: setb sda
acall delay
setb scl
acall delay
clr sda
clr scl
ret
i2cstop: clr scl
clr sda
setb scl
acall delay
setb sda
mov c,sda
ret
i2cwrite: mov r0,#08h
i2cwrite_loop: rlc a
mov sda,c
setb scl
acall delay
clr scl
djnz r0,i2cwrite_loop	
mov c,sda
setb scl
acall delay             
clr scl
ret	
i2cread: mov c,sda
mov r0,#8
rlc a
i2cread_loop: setb scl
mov c,sda
rlc a
acall delay
clr scl
djnz r0,i2cread_loop
ret	
delay: mov r4,#100
loop: djnz r4,loop
ret
delay1: mov r4,#0ffh
jll: mov r1,#0ffh
jl: djnz r1,jl
djnz r4,jll
ret
jkl: mov a,#10100000b
acall i2cstart
acall i2cwrite
mov a,#00h
acall i2cwrite
acall i2cread
acall i2cstop
ret
mydata0: db 'VOTER NO.1=',0
mydata1: db ' VOTER NO.2=',0
mydata2: db ' VOTER NO.3=',0

routs: clr a
movc a,@a+dptr
jz here
acall display
inc dptr
sjmp routs
here: acall delay_15ms
ret
delay_15ms: mov r3,#4h
loop14: mov r2,#0ffh
loop1: djnz r2,loop1
djnz r3,loop14
ret
display: mov sbuf,a
loopi: jnb ti,loopi
clr ti
ret
step: mov a,#10100000b
acall i2cstart
acall i2cwrite
mov a,r1
acall i2cwrite
acall i2cstop
acall i2cstart
mov a,#10100001b
acall i2cwrite
acall i2cread
acall i2cstop
mov 33h,a
mov a,r1
cjne a,#05h,kl
mov 34h,33h
mov a,33h
acall sett
ret
kl: cjne a,#06h,kl1
mov 35h,33h
mov a,33h
acall sett
ret
kl1: mov 36h,33h
mov a,33h
acall sett
ret
sett: da a
mov 37h,a
anl a,#0f0h
swap a
add a,#30h
mov 50h,a
acall display
mov a,37h
anl a,#0fh
add a,#30h
mov 51h,a
acall display
ret
end

