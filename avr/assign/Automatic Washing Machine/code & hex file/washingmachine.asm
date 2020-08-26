     $mod51
  
        dat equ  p1
        busy equ p1.7  
        rs equ   p3.5
        rw equ p3.4
        en equ p3.3
       bzr equ p0.2
       ledf equ p0.0
       ledb equ p0.1                                             

       
       

        org 0000h                       
        ajmp main

        org 0003h
   test: mov c,p3.2
        jnc halt
        setb p0.2
        reti
    halt:
        clr bzr                 ;till zero blow on the bzr
        ajmp test 
                                  
    main:
        mov ie,#00h
        setb ea
        ;setb ex0
    here:
       mov p2,#00h
       acall ini
       mov dptr,#show0
       acall read
       clr ledf        ;p1.0
       acall delay

       mov a,#01h
       acall command; Now make memory clear cursor home
       mov dptr,#show1
       acall read
       setb ex0        ;#############
       mov a,#0c0h
       acall command
       mov dptr,#show3
       acall read
       acall delay   ;Stopage1 time 3 sec rookee
       acall delay
       clr bzr
       acall delay
       
       mov a,#01h
       acall command
       mov dptr,#show2
       acall read
       mov a,#0c0h
       acall command
       mov dptr,#show4
       acall read
       setb bzr
       acall delay10
       acall stepperf

       mov a,#01h
       acall command
       mov dptr,#show1
       acall read
       mov a,#0c0h
       acall command
       mov dptr,#show4
       acall read
       acall delay   ;Stopage2 time 3 sec shsar
       acall delay
       clr bzr
       acall delay
       
       mov a,#01h
       acall command
       mov dptr,#show2 ;display ne
       acall read
       mov a,#0c0h
       acall command
       mov dptr,#show5
       acall read
       setb bzr
       acall delay10
       acall stepperf

       mov a,#01h
       acall command
       mov dptr,#show1
       acall read
       mov a,#0c0h
       acall command
       mov dptr,#show5
       acall read
       acall delay   ;Stopage2 time 3 sec Meerut
       acall delay
       clr bzr
       acall delay
       
       setb ledf     ; p1.0 ;off led at p1.0 for forward journey
       clr ledb  ;      p1.1 ; 0n Led for back ward journey

      mov a,#01h
      acall command
       mov dptr,#show2 ;display ne    shar
       acall read
       mov a,#0c0h
       acall command
       mov dptr,#show4
       acall read
       setb bzr
       acall delay10
       acall stepperb

       mov a,#01h
       acall command
       mov dptr,#show1
       acall read
       mov a,#0c0h
       acall command
       mov dptr,#show4
       acall read
       acall delay   ;Stopage2 time 3 sec shsar
       acall delay
       clr bzr
       acall delay
      
       mov a,#01h
       acall command
       mov dptr,#show2 ;display ne     roor
       acall read
       mov a,#0c0h
       acall command
       mov dptr,#show3
       acall read     
       setb bzr
       acall delay10
       acall stepperb

       mov a,#01h
       acall command
       mov dptr,#show1
       acall read
       mov a,#0c0h
       acall command
       mov dptr,#show3
       acall read
       setb ledb        ;p1.1
      ljmp here


      ;routine for stepper motor
       ; Delay Routine
     ;one sec delay
      delay:
      push acc
      push 00h
      push 01h
      push p0
      push p1
        mov r0,#0eh
     loopr:
        mov a,#0ffh
     loopb:
        mov b,#0ffh
     loopa: djnz b,loopa
            djnz 0e0h,loopb
            djnz r0,loopr
            pop p1
            pop p0
            pop 01h
            pop 00h
            pop acc
            ret

    ;dlay stepper
     delays:
     push acc
     push 00h 
     push 01h
     push p0
     push p1
      
     mov a,#0ffh
   loopa1:
     mov b,#0fh
   loopb1:
     djnz b,loopb1
     djnz 0e0h,loopa1

            pop p1
            pop p0
         
     pop 01h
     pop 00h
     pop acc
     ret

     delay10:
     mov tmod,#01h
     mov tcon,#00h
     mov tl0,#0f0h
     mov th0,#0f8h
     setb tr0
     no: jnb tf0,no
     clr tr0
     clr tf0
     ret
        ;=============== Routine to read data from prog mem

    read:
     nex:  clr a 
         movc a,@a+dptr
         cjne a,#'0',aga
         sjmp down
    aga: acall display
         inc dptr
         sjmp nex
    down:
         ret
        ;================ stepper routine
                  
  stepperf:
         push acc
         push p1
         mov a,#88h
         mov r1,#04h
    loop1:
         mov r0,#0e0h
    loop: mov p2,a
        acall delays
        rr a 
        djnz r0,loop
        djnz r1,loop1
        pop p1
        pop acc
        ret

 
 stepperb:
          push acc
         push p1
         mov a,#88h
         mov r1,#04h
    loop12:
         mov r0,#0e0h
    loop0: mov p2,a
        acall delays
        rl a 
        djnz r0,loop0
        djnz r1,loop12
    
        pop p1
        pop acc
       
      ret
    ;*******************************************************
    ;LCD strobe subroutines
      ini:
      mov a,#38h
    acall command
     mov a,#38h
    acall command
     mov a,#38h
    acall command
     mov a,#38h
    acall command
    mov a,#0eh
    acall command
    mov a,#06h
    acall command
    mov a,#01h
    acall command
    mov a,#80h
    acall command
    ret

 


 command:
    acall ready
    mov dat,a
    clr rs
    clr rw
    setb en
    clr en
    ret

display:
    acall ready
    mov dat,a
    setb rs
    clr rw
    setb en
    clr en
    ret

ready:
    clr en
    mov dat,#0ffh
    clr rs
    setb rw
wait:
    clr en
    setb en
    jb busy,wait
    clr en
    ret
  org 400h

        show0: db 'Welcome To All','0'
        show1: db 'FILL WATER AND DETERGENT','0'
        show2: db 'SOAK CLOTHES','0'
        show3: db 'RINSE','0'
        show4: db 'WASH','0'
     show5: db 'DRY','0'
    end       


