;Use this generic program for Shell
;In Dragon12+ RAM address is from $1000-3FFF 
;We use RAM addresses starting at $1000 for scratch pad (variables) and $3FFF for Stack 

   
        ABSENTRY Entry        ; for absolute assembly: mark this as application entry point
    
; Include derivative-specific definitions 
	INCLUDE 'mc9s12dp256.inc'     ;CPU used by Dragon12+ board
	
	
; amir hajjari 10/9/2019
 
 
;----------------------USE $1000-$2FFF for Scratch Pad

		ORG $1000 
D2	DC.B	2
D1	DC.B	5
D0	DC.B	5
CODES	DC.B	$3F, $06, $5B, $4F, $66, $6D, $7D, $07, $7F, $6F

R1 DS.B	1; MEMORY STORAGE FOR TIME DELAY LOOP
R2 DS.B 1
R3 DS.B 1
COUNT EQU 23; FOR DELAY LOOP



;code section
        ORG   $4000     ;Flash ROM address for Dragon12+
Entry:
	LDS     #$4000    ;Stack, the first Stack location is $3FFF
        NOP			;put your code here
        NOP
        
        
; --- SET-UP -------

	MOVB #$FF, DDRB; SET LEDS TO OUTPUT
	MOVB #$FF, DDRP; SET 7 SEGMENT TO OUTPUT
	MOVB #$00, DDRH; MAKE SWITCHES INPUT
	MOVB #$FF, DDRJ; MAKE ALL LEDS AN OUTPUT
	MOVB #$00, PTJ; GROUND LEDS

        
        
; ----- MAIN LOOP ----

MAIN:


	LDD PTH; LOAD INTO ACCUM D WHATEVER SIGNAL IS ON THE SWITCHES AT THIS TIME, ALSO IS INITAL NUMERATOR FOR DIVISION TO GET EACH BASE VALUE TO BE OUTPUTTED
	CLRA;
	JSR DIVISION; CALCULATE DIVISION OF WHATEVER VALUE IS PUT ON THE SWITCHES
		
	LDX #CODES; X STORES INTITIAL LOCATION OF CODES LOOK-UP TABLE
	LDAB D0; B = OFFSET
	LDAA B,X; A NOW HOLDS DISPLAY VALUE OF 2
	MOVB #%00000111, PTP; ENABLE RIGHT MOST DISPLAY
	STAA PORTB; OUTPUT 2 ON THE 7 SEGMENT
	
	JSR DELAY1;
	
	
	
	LDAB D1; B = OFFSET
	LDAA B,X; A NOW HOLDS DISPLAY VALUE OF 2
	MOVB #%00001011, PTP; ENABLE RIGHT MOST -1 DISPLAY
	STAA PORTB; OUTPUT 2 ON THE 7 SEGMENT
	
	JSR DELAY1;
	
	
	LDAB D2; B = OFFSET
	LDAA B,X; A NOW HOLDS DISPLAY VALUE OF 2
	MOVB #%00001101, PTP; ENABLE RIGHT MOST -2 DISPLAY
	STAA PORTB; OUTPUT 2 ON THE 7 SEGMENT
	
	JSR DELAY1;
	
	
	
	BRA MAIN
	

; --- SUB ROUTINES ---

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
    
    
    
 
 DIVISION:
 LDX #10; DENOMINATOR
 IDIV
 STAB D0; HIGHEST BASE
 XGDX
 
 LDX #10;
 IDIV
 STAB D1; MIDDLE BASE
 XGDX
 
 LDX #10
 IDIV
 STAB D2; LOWEST BASE
 
 RTS





            
;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry     ;Reset Vector. CPU wakes here and it is sent to start of the code at $4000
