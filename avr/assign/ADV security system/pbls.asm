$mod51
lcd  equ p1
rs   equ p3.0
rw   equ p3.1
en   equ p3.2
org 00h
mov lcd,#00h
mov a,#38h
acall comnwrt
acall delay
mov a,#0eh
acall comnwrt
acall delay
mov a,#06h
acall comnwrt 
acall delay
mov a,#01h
acall comnwrt
acall delay
mov dptr,#dat
acall lcd1
mov dptr,#dat1
acall lcd2
mov a,#01h
acall comnwrt
acall delay
mov dptr,#dat2
acall lcd1
mov dptr,#dat3
acall lcd2
mov a,#01h
acall comnwrt
acall delay
mov dptr,#dat4
acall lcd1 
sjmp $

lcd1:
mov a,#80h
acall comnwrt
acall delay
back: clr a
movc a,@a+dptr
cjne a,#00h,in
sjmp out
in: acall datawrt
acall delay
inc dptr
sjmp back
out:
ret
 
 
lcd2:
mov a,#0c0h
acall comnwrt
acall delay
back1: clr a
movc a,@a+dptr
cjne a,#00h,in1
sjmp out1
in1: acall datawrt
acall delay
inc dptr
sjmp back1
out1: 
ret



;MTRF:
      mov p2,#00h
      clr a  
ag:   mov p2,#0f1h
      acall delay
      mov p2,#0f2h
      acall delay
      mov p2,#0f4h
      acall delay
      mov p2,#0f8h
      acall delay
      inc a
      cjne a,#20,ag
      ret

;MTRR:
      clr a
ag1:  mov p2,#0f8h
      acall delay
      mov p2,#0f4h
      acall delay
      mov p2,#0f2h
      acall delay
      mov p2,#0f1h
      acall delay
      inc a
      cjne a,#20,ag1 
      ret

comnwrt:
      mov   lcd,a
      clr   rs
      clr   rw
      setb  en
      acall delay
      clr   en
      ret

datawrt:
      mov   lcd,a
      setb  rs
      clr   rw
      setb  en
      acall delay
      clr   en
      ret

delay:
      mov r0,#10
 la3: mov r1,#255
 la2: mov r2,#255
 la1: djnz r2,la1 
      djnz r1,la2
      djnz r0,la3   
      ret

dat:   db 'welcome 2 you ON',00h
dat1:  db 'password based',00h
dat2:  db 'security system',00h
dat3:  db 'using card',00h
dat4:  db 'insert card',00h
dat5:  db 'enter password',00h
dat6:  db 'correct password',00h
dat7:  db 'wrong password',00h
dat8:  db 'enter it again',00h 
dat9:  db 'welcome to amit',00h
dat10: db 'welcome to akash',00h
dat11: db 'opening door',00h
dat12: db 'closing door',00h 

      end