$mod51
org 00h
s1 equ p1.0
s2 equ p1.1
s3 equ p1.2
s4 equ p1.3
mov p1,#0fh
ag1: jb s1,r11
mov p2,#00000001b    ; left
sjmp ag
r11: jb s2,r22
mov p2,#0ah          ;backward
sjmp ag
r22: jb s3,r33
mov p2,#04h            ; right
sjmp ag
r33: jb s4,r44
mov p2,#05h
sjmp ag
r44: mov p2,#00h
ag: sjmp ag1
END