$mod51
org 00h
mov p1,#0ffh
ag: mov a,p1
	anl a,#0fh
	cjne a,#00001011b,la1
	mov p2,#11111010b
	sjmp ag
la1:
	mov a,p1
	anl a,#0fh
	cjne a,#00001101b,la2
	mov p2,#11110010b
	sjmp ag
la2:
	mov a,p1
	anl a,#0fh
	cjne a,#00001001b,la3
	mov p2,#11111000b
	sjmp ag		
la3:
	mov a,p1
	anl a,#0fh
	cjne a,#00001110b,la4
	mov p2,#11110101b
	sjmp ag	
la4:
	mov a,p1
	anl a,#0fh
	cjne a,#00000101b,la5
	mov p2,#11110000b
	sjmp ag
la5:
	mov a,p1
	anl a,#0fh
	cjne a,#00001111b,ag
	mov p2,#11110000b
	sjmp ag



end	

