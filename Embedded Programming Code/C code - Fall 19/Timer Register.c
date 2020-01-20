#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


/*
	* Author : Amir Hajjari
	* lab 9 deliverable
	* Date	: 11-06-19
	* Description	: Using internal clock of HCS12 hardware to function as timing mechanisim to light up LEDS and speakers respectively.
*/


#include <stdio.h>

// Global Variable declaration


// Function protoype section


/*usingTimer: incorporates internal clock to function as a delay for the LEDs
 input: none
 output: wasted clock cycles, which ends once internal clock functions FFFF number of iterations, thus triggering the flag, breaking the while loop
*/
void usingTimer(void); // using the timer for LEDS



/*usingTimer_speaker: incorporates internal clock to function as a delay for the speakers
 input: none
 output: wasted clock cycles, which ends once internal clock functions 00FF number of iterations, thus triggering the flag, breaking the while loop
*/
void usingTimer_speaker(void); // using the timer for speaker




// ------------- MAIN FUNCTION -----------





void main(void) {



// used for while loop to signal LEDS 7 times
const byte Count = 7;
int R0;
R0 = Count; // initialize the counter



//PORT set-up
DDRB = 0xFF; // LEDS for output
DDRJ = 0xFF; // enable LEDS
PTJ = 0x00; // Ground LED signal to complete circuit
DDRT = 0b00100000; // PIN 5 OF PORT T (SPEAKER) SET TO OUTPUT

// Channel set-up for LEDS
TSCR1 = 0x90;
TSCR2 = 0x07;
TIOS = TIOS | 0b00000001; //SET CHANNEL ZERO TO OUTPUT COMPARE
TCTL2 = 0b00000000; // NO ACTION UPON MATCH


// turns LEDS on and off total of 7 times
while(R0-- != 0)
{
	PORTB = 0xFF;
	usingTimer();
	PORTB = 0x00;
	usingTimer();
}




// Channel set-up for speaker sounding
TIOS = TIOS | 0b00100000; //SET CHANNEL 5 TO OUTPUT COMPARE
TCTL1 = 0b00000100; // toggle UPON MATCH

  for(;;) {
  
	  usingTimer_speaker();
	  PTT = 0b00100000; // moves speaker cone forward
	  usingTimer_speaker();
	  PTT = 0x00; // moves speaker cone backward
  
  } 
  
}





// Function def section


void usingTimer(void) // LEDS
{
	
	int timer_compare_value = TCNT; // Read the current timer output value
	timer_compare_value = timer_compare_value + 0xFFFF;
	
	TC0 = timer_compare_value;
	
	while(!(TFLG1 & 0b00000001));
}


void usingTimer_speaker(void) // speaker
{
	
	int timer_compare_value = TCNT; // Read the current timer output value
	timer_compare_value = timer_compare_value + 0x00FF;
	
	TC5 = timer_compare_value;
	
	while(!(TFLG1 & 0b00100000));
}

