$ MOD51

ORG 0000H
       
 	   MOV P1,#00H
	   MOV A,#55H
	   MOV 32H,#20

loop:	   MOV P1,A
	   LCALL DELAY
       CPL A
	   DJNZ 32H,loop
	  
    ORG 300H                          ;---------- this is delay subroutine ------------                    ;put DELAY at address 300H
DELAY: MOV R5,#10
  third: MOV R6,#200
  second: MOV R7,#200
 DJNZ R7,$
 DJNZ R6,second
 DJNZ R5,third

 RET
	
END