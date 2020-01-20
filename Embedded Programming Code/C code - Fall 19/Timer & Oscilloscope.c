#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

/*
	* Author : Amir Hajjari
	* lab 10 Deliverable
	* Date	: 11-13-19
	* Description	: Generating a 440 HZ square wave using a prescaler of 64
*/

#include <stdio.h>

// Global Variable declaration


// Function protoype section


/*usingTimer_speaker: incorporates internal clock to function as a delay for the speakers
 input: none
 output: wasted clock cycles, which ends once internal clock functions 00FF number of iterations,
 thus triggering the flag, breaking the while loop
*/
void usingTimer_speaker(void); // using the timer for speaker


// ------------- MAIN FUNCTION -----------


void main(void) {


//PORT set-up
DDRB = 0xFF; // LEDS for output
DDRJ = 0xFF; // enable LEDS
PTJ = 0x00; // Ground LED signal to complete circuit
DDRT = 0b00100000; // PIN 5 OF PORT T (SPEAKER) SET TO OUTPUT

// Channel set-up for LEDS
TSCR1 = 0x90;
TSCR2 = 0x06;
TIOS = TIOS | 0b00100000; //SET CHANNEL 5 TO OUTPUT COMPARE
TCTL1 = 0b0000100; // TOGGLE UPON MATCH


  for(;;) {
  
	  usingTimer_speaker();
  
  } 
  
}


// Function def section

void usingTimer_speaker(void) // speaker
{
	
	int timer_compare_value = TCNT; // Read the current timer output value
	timer_compare_value = timer_compare_value + 449;
	
	TC5 = timer_compare_value;
	
	while(!(TFLG1 & TFLG1_C5F_MASK));
}
