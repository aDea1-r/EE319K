// PeriodicSysTickInts.c
// Runs on LM4F120
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano
// March 7, 2016

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015

   Program 5.12, section 5.7

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// oscilloscope or LED connected to PF2 for period measurement
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

#include "SysTickInts.h"
#include "PLL.h"


#define PF2     (*((volatile uint32_t *)0x40025010))
#define PF3     (*((volatile uint32_t *)0x40025020))


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
volatile uint32_t Counts = 0;

int main(void){
  PLL_Init(Bus80MHz);         // bus clock at 80 MHz
  SYSCTL_RCGCGPIO_R |= 0x20;  // activate port F
  Counts = 0;
  GPIO_PORTF_DIR_R |= 0x0C;   // make PF2,PF3 output (PF2,PF3 built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x0C;// disable alt funct on PF2,PF3
  GPIO_PORTF_DEN_R |= 0x0C;   // enable digital I/O on PF2,PF3
                              // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFF00FF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;     // disable analog functionality on PF,PF3
  SysTick_Init(80000);        // initialize SysTick timer
  EnableInterrupts();

  while(1){                   // interrupts every 1ms, 500 Hz flash
    PF3 ^= 0x08;                // toggle PF3
  }
}

// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
  PF2 ^= 0x04;                // toggle PF2
  PF2 ^= 0x04;                // toggle PF2
  Counts = Counts + 1;
  PF2 ^= 0x04;                // toggle PF2
}

uint8_t Duty; // 1 to 99
#define PB0 (*((volatile uint32_t *)0x40005004))
#define CAL 25   // cycles to service interrupt
void Init2(void){
  NVIC_ST_RELOAD_R = 16000*Duty-CAL;   // reload value for high
  NVIC_ST_CTRL_R = 7;               // activate and enable interrupts
  PB0 = 0x01;
  EnableInterrupts();         // I = 0
}
void SysTick_Handler2(void){
  if(PB0){        // end of high pulse
    PB0 = 0x00;   // make it low
    NVIC_ST_RELOAD_R = 16000*(100-Duty)-CAL; // reload value for low
  }else{          // end of low pulse
    PB0 = 0x01;   // now high
    NVIC_ST_RELOAD_R = 16000*Duty-CAL;       // reload value for high
  }
}
int main2(void){
  PLL_Init(Bus16MHz);         // bus clock at 16 MHz
  SYSCTL_RCGCGPIO_R |= 0x02;  // activate port B
  Duty=25;
  Init2();
  GPIO_PORTB_DIR_R |= 0x01;   // make PB0 output 
  GPIO_PORTB_AFSEL_R &= ~0x01;// disable alt funct on PB0
  GPIO_PORTB_DEN_R |= 0x01;   // enable digital I/O on PB0
  while(1);
}









