// Spring 2020 EE319K Homework 3
// Adeel Rehman
// Brief description of the program: Similar to Lab 1
/*
The objective of this system is to implement an odd-bit detection system. 
There are three bits of inputs and one bit of output. 
The output is in positive logic: outputing a 1 will turn on the LED, outputing a 0 will turn off the LED.  
Inputs are positive logic: meaning if the switch pressed is the input is 1, if the switch is not pressed the input is 0.
PE0 is an input 
PE1 is an input 
PE2 is an input 
PB4 is the output 

The specific operation of this system
Initialize Port E to make PE0,PE1,PE2 inputs and PB4 an output
Over and over, read the inputs, calculate the result and set the output

The input/output specification refers to the input, not the switch. 
The following table illustrates the expected behavior relative to output PB4 as a function of inputs PE0,PE1,PE2
PE2  PE1  PE0  PB4
0    0    0    0    even number of 1’s
0    0    1    1    odd number of 1’s
0    1    0    1    odd number of 1’s
0    1    1    0    even number of 1’s
1    0    0    1    odd number of 1’s
1    0    1    0    even number of 1’s
1    1    0    0    even number of 1’s
1    1    1    1    odd number of 1’s
*/
// NOTE: Do not use any conditional branches in your solution. 
//   We want you to think of the solution in terms of logical and shift operations
#include <stdint.h>
#include "HW3Grader.h"
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
#define GPIO_PORTE_DATA_R       (*((volatile uint32_t *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile uint32_t *)0x40024400))
#define GPIO_PORTE_DEN_R        (*((volatile uint32_t *)0x4002451C))
#define GPIO_PORTB_DATA_R       (*((volatile uint32_t *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile uint32_t *)0x40005400))
#define GPIO_PORTB_DEN_R        (*((volatile uint32_t *)0x4000551C))

int main(void){volatile uint32_t delay;
  Grader_Init("aur228","Spring 2020"); // replace JV1234 with your EID
  // put your initialization here
	
	SYSCTL_RCGCGPIO_R |= 0x12; //enable clocks on port E and B
	
	volatile int a = 4;
	volatile int b = 4; 
	
	GPIO_PORTE_DIR_R &= 0xF8; // Set pin 0,1,2 to input
	GPIO_PORTB_DIR_R |= 0x10; //set pin 4 to output
	GPIO_PORTE_DEN_R |= 0x7;	//enable digital for pin 0-2
	GPIO_PORTB_DEN_R |= 0x10; //enable diigtal for pin 4
	

  
  while(1){
  // put your input, calculations, output here
	
		int PE0 = (GPIO_PORTE_DATA_R & 0x01) << 4;
		int PE1 = (GPIO_PORTE_DATA_R & 0x02) << 3; 
		int PE2 = (GPIO_PORTE_DATA_R & 0x04) << 2; 
				
		int out = PE0 ^ PE1 ^ PE2;
		
		int B4 = GPIO_PORTB_DATA_R; 
		
		B4 &= 0xFEF; //clear bit 4
		B4 |= out; //cp bit 4 into B4 var
		
		GPIO_PORTB_DATA_R = B4; 

		
  }
}

