// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: Adeel R and Zach B
// Date Created: 3/6/17 
// Last Modified: 3/24/2020 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********
// PORTB 0-5: DAC output (lowest bit to lowest pin)
// PORTE 0-3: PIANO INPUT

#define noTest


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "dac.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

uint32_t beat = 0; 
void Heartbeat(void)
{
	beat++;
	if (beat & 0x00010000)
		GPIO_PORTF_DATA_R ^= 0x02;
}

//define frequencies of notes to impliment. 
//predefined lookup table is faster at runtime than decoding button presses
int freqTable[16] = {0, 392, 440, 494, 494, 523, 523, 523, 523, 523, 523, 523, 523, 523, 523, 523}; 


#ifdef noTest
 int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init();
  // other initialization
	SYSCTL_RCGCGPIO_R |= 0x20;
	__asm__ {
		NOP
		NOP
	}
	GPIO_PORTF_DIR_R |= 0x02;
	GPIO_PORTF_DEN_R |= 0x02;
	
	//convert freq table to period table
	for (int i=0; i<16; i++) {
		freqTable[i] = 1250000 / freqTable[i]; 
	}
	
  EnableInterrupts();
  while(1){ 
		Heartbeat();
		int buttons = Piano_In();
		Sound_Play(freqTable[buttons]); 
  }    
} 

#endif
#ifdef dacTest

int main(void){ 
	uint32_t data = 0; // 0 to 15 DAC output
  //PLL_Init();    // like Program 4.6 in the book, 80 MHz
  DAC_Init();
  for(;;) {
    DAC_Out(data);
    data = 0x3F&(data+1); // 0,1,2...,14,15,0,1,2,...
		for (int i=0; i<10000000; i++);
  }
}

#endif
