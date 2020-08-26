$mod51
org 00h
sw1 equ p1.0
sw2 equ p1.1
led1 equ p2.0
led2 equ p2.1
setb sw1
setb sw2
go: jnb sw1,here
sjmp back
here: clr led1
setb led2

back:jnb sw2,ag 
sjmp go
ag: clr led2
setb led1

sjmp go
END

