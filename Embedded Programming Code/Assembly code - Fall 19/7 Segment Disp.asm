;Use this generic program for Shell
;In Dragon12+ RAM address is from $1000-3FFF 
;We use RAM addresses starting at $1000 for scratch pad (variables) and $3FFF for Stack 

   
  	ABSENTRY Entry        ; for absolute assembly: mark this as application entry point
    
; Include derivative-specific definitions 
	INCLUDE 'mc9s12dp256.inc'     ;CPU used by Dragon12+ board
 
 
;----------------------USE $1000-$2FFF for Scratch Pad 

		ORG $1000
		
COUNT   EQU $21; INTITIALIZE COUNTER VALUE
R1      DS.W 1; MEMORY STORAGE FOR COUNTER
R2      DS.W 1
R3      DS.W 1

;code section
        ORG   $4000     ;Flash ROM address for Dragon12+


Entry:
		LDS     #$4000    ;Stack, the first Stack location is $3FFF
        NOP			;put your code here
        NOP



; ---- SET-UP -------

	MOVB #$FF, DDRB; INITIALIZE PORT B TO OUTPUT (LEDS)
	MOVB #$FF, DDRP; INITIALIZE PORT P TO OUTPUT (7 SEGMENT)
	BCLR PTH, %00000001; INITIALIZE SWITCH 1 FOR INPUT




; ----- MAIN LOOP -----
MAINLOOP:
	

		BRSET PTH, %00000001, ON; BRANCH TO 'ON' IF PIN 0 OF SWITCH IS ON
		BRCLR PTH, %00000001, OFF; BRANCH TO 'OFF' IF PIN O OF SWITCH IS OFF
		
		
		ON:
		
		MOVB #%00000111, PTP; ENABLE RIGHT-MOST DISPLAY
		MOVB #%00000110, PORTB; DISPLAY 'I' ON THE DISPLAY
		
		JSR DELAY;
		
		MOVB #%00001011, PTP; ENABLE THE SECOND FROM THE RIGHT DISPLAY
		MOVB #%01110110, PORTB; DISPLAY 'H' ON THE DISPLAY TO THE RIGHT OF THE RIGHTMOST
		
		JSR DELAY;
		
		
		
		BRA MAINLOOP
		
		
		OFF:
		
		MOVB #%0001111, PTP;
	

		
		;JSR DELAY; DONT NEED THIS!!!
		
		BRA MAINLOOP
		
		
	



; ---- SUBROUTINES ----

DELAY:

	MOVB #COUNT,R1;
L1:
	MOVB #COUNT,R2
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



            
;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry     ;Reset Vector. CPU wakes here and it is sent to start of the code at $4000