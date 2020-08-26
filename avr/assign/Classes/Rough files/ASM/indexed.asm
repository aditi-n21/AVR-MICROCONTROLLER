$mod51
org 00h
back: 
mov dptr,#150h
here: 
mov P1,A
clr a
movc a,@a+dptr
inc dptr
cjne a,#0h,here
sjmp back

org 150h
DB 'MANOJ',0
END