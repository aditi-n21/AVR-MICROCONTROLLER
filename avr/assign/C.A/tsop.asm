$mod51
org 00h
mov p2,#0ffh
ag: mov a,p2
	anl a,#07h
	cjne a,#01h,la1
	mov p1,#02h
	sjmp ag
la1:
	mov a,p2
	anl a,#07h
	cjne a,#02h,la2
	mov p1,#02h
	sjmp ag
la2:
	mov a,p2
	anl a,#07h
	cjne a,#04h,la3
	mov p1,#02h
	sjmp ag		
la3:
	mov a,p2
	anl a,#07h
	cjne a,#00h,la4
	mov p1,#00010100b
	sjmp ag	
la4:
	mov a,p2
	anl a,#07h
	cjne a,#07h,ag
	mov p1,#0ah
	sjmp ag	
end