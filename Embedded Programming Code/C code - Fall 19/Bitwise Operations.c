#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


/*
	* Author : Amir Hajjari
	* Lab 8 Deliverable
	* Date	: 10-23-19
	* Description	: Uses SW3 - SW0 & SW7 as control flow determiner to excute either the blink or flash functions
*/


#include <stdio.h>

// Global Variable declaration








// Function protoype section


/* blink: outputs signal on all LEDS and turns on all LEDS at a rate dependent upon the value passed in the delay function
   input: number of oscillations / "blinks" of the signal
   output: singal on and off on LEDS
*/
void blink(unsigned int );




/* delay: wastes clock cycles essentially
   input: number of seconds *1000 to waste clock cycles
   output: none, just wastes clock cycles

*/
void delay(unsigned int );




/* flash: outputs signal on 1 LED at a time, from MSB to LSB, rate dependent on delay function. Shifts bits right one at a time
   input: none
   output: outputs signal on 1 LED at a time, from MSB to LSB

*/
void flash( void );






void main(void) {

DDRB = 0xFF; // LEDS for output
DDRJ = 0xFF; // enable LEDS
PTJ = 0x00; // Ground LED signal to complete circuit
DDRH = 0x00; // initialize switches for input


  for(;;)
   {
  
  
	  if ((PTH & 0x80) != 0) // if the signal on switch 7 is high, do the blink function
	  {
	  	delay(2000); // allows time for user to change 4 LSB bits for number of blinks
	  	blink(PTH & 0x0F); // only allows 4 LSBS to determine number of blinks
	  }
	  
	    
	  else
	  {
	  	flash();
	  }  
	  
	  
	  delay(3000); // allows user time to adjust switches befor next iteration
    
  } 
  
}






// Function def section

void blink(unsigned int numTimes)
{

	unsigned int k ; 
	
	for(k=0; k < numTimes; k++)
	{
		
		PORTB = 0xFF ; // LEDS DISPLAY HIGH SIGNAL ON ALL SWITCHES
		delay(1000); // function to delay for 1 second / 1000 ms
		PORTB = 0x00; // turns off all 8 LEDS
		delay(1000);
		
	}
	
}

void delay(unsigned int t)
{
	
	unsigned int i;
	unsigned int j;
	
	for(i=0; i<t; i++)
		for(j=0; j<2020; j++); // wastes clock cycles essentially
}


void flash()
{
	unsigned int k; // counter variable
	unsigned char initialVal;
	unsigned char nextVal;
	
	initialVal = 0x80; // value is 1000 0000, so turns on only leftmost LED
	
	
	nextVal = initialVal; // initial value of variable is 1000 0000
	
	
	for(k = 0; k < 8; k++ )
	{
		PORTB = nextVal;
	
		nextVal = nextVal >> 1; // have to shift and overwrite previous shift value to ouput correct value for next cycle
		
		delay(500); // delay between each iteration of output value
	}
	
		
}