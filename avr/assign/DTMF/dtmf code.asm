$mod51
org 00h
mov p1,#0ffh
mov p2,#00h
mov a,p1
ag: cjne a,#0f7h,la1   
setb p2.0               ;1st d on
la1: mov a,p1
cjne a,#0fbh,la2
setb p2.1               ;2nd d on
la2: mov a,p1
cjne a,#0f3h,la3
setb p2.2               ;3rd d on
la3: mov a,p1
cjne a,#0fdh,la4
setb p2.3               ;4th d on
la4: mov a,p1
cjne a,#0f5h,la5 
mov p2,#0ffh            ;all on
la5: mov a,p1
cjne a,#0fah,la6
mov p2,#00h             ;all off
la6: sjmp ag
end

