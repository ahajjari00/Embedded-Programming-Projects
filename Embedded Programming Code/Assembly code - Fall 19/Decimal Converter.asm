;Use this generic program for Shell
;In Dragon12+ RAM address is from $1000-3FFF 
;We use RAM addresses starting at $1000 for scratch pad (variables) and $3FFF for Stack 

   
        ABSENTRY Entry        ; for absolute assembly: mark this as application entry point
    
; Include derivative-specific definitions 
	INCLUDE 'mc9s12dp256.inc'     ;CPU used by Dragon12+ board
 
 
;----------------------USE $1000-$2FFF for Scratch Pad 



; amir hajjari - 10/9/2019


      ORG $1000
COUNT EQU $7F; FOR SHORTER DELAY
COUNT2 EQU $FF; FOR LONGER DELAY
R1  DS.B 1; SETS ASIDE ONE BYTE OF MEMORY SPACE
R2  DS.B 1
R3  DS.B 1


MYNUM DC.W 254;
MYDEN DC.W 10;
D0  DS.B  1; SETS ASIDE ONE BYTE OF MEMORY SPACE
D1  DS.B  1
D2  DS.B  1


;code section
        ORG   $4000     ;Flash ROM address for Dragon12+
Entry:
	LDS     #$4000    ;Stack, the first Stack location is $3FFF
        NOP			;put your code here
        NOP
        
        
        
 ; ----- SET-UP ----
 
   MOVB #$00, DDRH; MAKE SWITCHES INPUT
   MOVB #$FF, DDRJ; ENABLE LEDS
   MOVB #$FF, DDRB; MAKE ALL SWITCHES AN OUTPUT
   MOVB #$00, PTJ; GROUND LEDS


; ---- MAIN LOOP -----

MAIN:
  LDD PTH; PUT CURRENT VALUES ON SWITHCES IN ACCUMM D
  
  CLRA; SINCE ONLY 8 SWITCHES, WE ONLY CARE ABOUT UP TO 8 BITS, SO WE DO NOT NEED REG A 
  JSR DIVIDE
  
  MOVB D2, PORTB;
  JSR DELAY1
  
  MOVB #$00, PORTB; TO ACCOUNT FOR SWITCHING SIGNAL
  JSR DELAY1
  
  MOVB D1, PORTB;
  JSR DELAY1
  
  MOVB #$00, PORTB;
  JSR DELAY1
  
  MOVB D0, PORTB;
  JSR DELAY1
  
  MOVB #$00, PORTB;
  JSR DELAY2; LONGER DELAY TO SHOW THAT LAST VALUE WAS SHOWN BEFORE BRANCHING BACK TO RE-START
  
  
  BRA MAIN; RE-START PROCESS
  

;-----SUB-ROUTINES-----

  DELAY1:
    MOVB #COUNT, R1
    L1:
        MOVB #COUNT, R2
        L2:
            MOVB #COUNT,R3
            L3:
                  DEC R3
                  BNE L3
            DEC R2
            BNE L2
        DEC R1
    BNE L1
    RTS
    
    
    
  DELAY2:
    MOVB #COUNT2, R1
    L1A:
        MOVB #COUNT2, R2
        L2A:
            MOVB #COUNT2,R3
            L3A:
                  DEC R3
                  BNE L3A
            DEC R2
            BNE L2A
        DEC R1
    BNE L1A
    RTS
  
  
  DIVIDE:
    LDX MYDEN; DENOMINATOR = 10
    IDIV;
    STAB D0;
    XGDX; EXCHANGE D AND X
    LDX MYDEN;
    IDIV;
    STAB D1;
    XGDX; EXCHANGE D AND X
    LDX MYDEN;
    IDIV;
    STAB D2;
    RTS   
     
       
       
;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry     ;Reset Vector. CPU wakes here and it is sent to start of the code at $4000