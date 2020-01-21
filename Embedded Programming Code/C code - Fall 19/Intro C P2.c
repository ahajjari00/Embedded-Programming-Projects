#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


/*
	* Author : Amir Hajjari
	* Date	: 10-16-19
	* Description	: using delay and blink functions to show signal for differing time intervals
*/


#include <stdio.h>

// Global Variable declaration






// Function protoype section

void blink(unsigned int ); // number of times for LEDS to blink in a given time frame(delay)
void delay(unsigned int); // time gap inbetween ON signal of LEDS





void main(void) {
  
	DDRB = 0xFF; // LEDS for output
	DDRJ = 0xFF; // enable LEDS
	PTJ = 0x00; // Ground LED signal to complete circuit
	


  for(;;) {
  
  blink(5); // repeats signal 5 times;
  
  delay(5000); //longer delay to signify that one iteration of blink was completed before re-starting
  
  
  
  
     
  } 
  
}






// Function def section


void delay(unsigned int t)
{
	
	unsigned int i;
	unsigned int j;
	
	for(i=0; i<t; i++)
		for(j=0; j<2020; j++); // wastes clock cycles essentially
}

void blink(unsigned int numTimes)
{

	unsigned int k ; 
	
	for(k=0; k < numTimes; k++)
	{
		
		PORTB = 0xFF; // turns on all 8 LEDS
		delay(1000); // function to delay for 1 second / 1000 ms
		PORTB = 0x00; // turns of all 8 LEDS
		delay(1000);
		
	}
	
}

