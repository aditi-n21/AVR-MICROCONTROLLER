$mod51
row0 equ p2.0
row1 equ p2.1
row2 equ p2.2
col0 equ p2.5
col1 equ p2.6
col2 equ p2.7
org 00h
	mov p2,#07h
ag1:	clr col0
	setb col1
	setb col2
	jb row0,r11
	mov p1,#0f9h
	sjmp ag
r11:	jb row1,r22
	mov p1,#99h
	sjmp ag
r22:	jb row2,r33
	mov p1,#0f8h
	sjmp ag
r33:	setb col0
	clr col1
	setb col2
	jb row0,r44
	mov p1,#0a4h
	sjmp ag
r44:	jb row1,r55
	mov p1,#092h
	sjmp ag
r55:	jb row2,r66
	mov p1,#80h
	sjmp ag
r66:	setb col0
	setb col1
	clr col2
	jb row0,r77
	mov p1,#0b0h
	sjmp ag
r77:	jb row1,r88
	mov p1,#82h
	sjmp ag
r88:	jb row2,ag1
	mov p1,#90h
	sjmp ag
ag:	sjmp ag1
	end
