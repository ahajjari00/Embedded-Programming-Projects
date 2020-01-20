;Use this generic program for Shell
;In Dragon12+ RAM address is from $1000-3FFF 
;We use RAM addresses starting at $1000 for scratch pad (variables) and $3FFF for Stack 

   
        ABSENTRY Entry        ; for absolute assembly: mark this as application entry point
    
; Include derivative-specific definitions 
	INCLUDE 'mc9s12dp256.inc'     ;CPU used by Dragon12+ board
 
 
;----------------------USE $1000-$2FFF for Scratch Pad 


			ORG $1000
			
Count EQU $0F ; initial counter value
R1 DS.W 1 ; memory storage for counter
R2 DS.W 1 ; memory storage for counter
R3 DS.W 1 ; memory storage for counter


;code section
        ORG   $4000;Flash ROM address for Dragon12+
        
        



Entry:
	
	
	;-----SET-UP-----------
	
	LDS #$4000;
	
	BSET DDRT, %00100000; INITIALIZE BIT 5 OF PORT T (SPEAKER) TO OUTPUT
	
	
	
	
	BSET DDRJ, %00000010; INITIALIZE BIT 1 OF PORT J TO OUTPUT (led enable)
	BCLR PTJ, %00000010; SEND 0 TO BIT 1 OF PORT J (GROUND SIGNAL)
	MOVB #$FF, DDRB; PORT B FOR OUTPUT (LEDS)
	
	
	
	
	BCLR DDRH, %00000001; INITIALIZE PIN 0 OF PORT H FOR INPUT (switch)
	
	
	
	
	;-----MAIN-LOOP--------
	
MAINLOOP:
	
	
	BRSET PTH, %00000001, ON; BRANCH TO THE LABEL "ON" IF SWITCH 0 IS ON
	
	BRCLR PTH, %00000001, OFF; BRANCH T0 THE LABEL "OFF" IF SWITCH 0 IS OFF
	
	
	
	ON:
	
	
	MOVB #%11111111, PORTB;
	
	BSET PTT, %00100000; MOVES SPEAKER CONE FORWARD
	
	JSR Delay
	
	BCLR  PTT,%00100000 ; MOVES SPEAKER CONE BACKWARD
	
	

	
	
	JSR Delay
	
	
	BRA MAINLOOP
	

	
	OFF:	
	MOVB #%00000000, PORTB;
	BCLR  PTT,%00100000 ; MOVES SPEAKER CONE BACKWARD
	
	JSR Delay
	
	
	
	
	BRA MAINLOOP
	
	
;------SUBROUTINES-------
Delay:
	MOVB #Count,R1
	L1:
		MOVB #Count,R2
		L2:
			MOVB #Count,R3
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
