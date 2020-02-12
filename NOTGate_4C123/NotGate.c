/*Runs on TM4C123
 Implements a NOT gate described in class
 PE1 is an output to LED, Positive logic
 PE0 is an input from switch, Positive logic
 Switch pressed causes LED to go OFF and 
 release causes LED to go ON.
 EE319K in class example

*/
#include <stdint.h>

#include "tm4c123gh6pm.h"
uint32_t In,Out; // globals added to assist debugging (should have been locals)
int main(void){    volatile unsigned long delay;
// running at 16 MHz without PLL
// one time initialization goes here
  SYSCTL_RCGCGPIO_R |= 0x10;	 // Turn clock on PortE
  delay = 100;				      	 // Wait
  GPIO_PORTE_DIR_R |= 0x02;    // PE1 out
  GPIO_PORTE_DIR_R &= ~(0x01); // PE0 input
  GPIO_PORTE_DEN_R |= 0x03;    // digital enable on PE1,PE0
  while(1){
// operations to be executed over and over go here
    In = GPIO_PORTE_DATA_R & 0x01; // input in bit 0
    Out = ~In;                     // perform NOT in bit 0
    Out = Out<<1;                  // shift signal into bit 1
    GPIO_PORTE_DATA_R = Out;       // output bit 1
  }
}
