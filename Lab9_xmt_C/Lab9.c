// Lab9.c
// Runs on LM4F120 or TM4C123
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
// Last Modified: 1/17/2020

// Analog Input connected to PD2=ADC0 channel 5
// On other computer the results are displayed on Sitronox ST7735
// PF3, PF2, PF1 are heartbeats

// Simplex communication
// EE319K Lab 9 hardware
// Use PC5 38 kHz modulated light output
// System xmt                        System rcv
//   PC5 --IR LED--> light >--IR sensor--- PC4
//   Gnd --------- not connected --------- Gnd
// * Start with where you left off in Lab8. 
// * Get Lab8 code working in this project.
// * Rewrite the SysTickHandler
// Lab 9 will not run in the simulator

#include <stdint.h>

#include "PLL.h"
#include "ADC.h"
#include "IRtranmission.h"
#include "../inc/tm4c123gh6pm.h"


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
uint32_t Data;      // 12-bit ADC
uint32_t Position;  // 32-bit fixed-point 0.01 cm


// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
// Intialize PortF for hearbeat
}

void SysTick_Init(void){
}
// Get fit from excel and code the convert routine with the constants
// from the curve-fit
uint32_t Convert(uint32_t input){
  return 0; //replace with your calibration code from Lab 8
}


// final main program for simplex communication
// Sender sends using SysTick Interrupt
// Receiver receives using RX
int main(void){ 
  DisableInterrupts(); // complete initialization first
  PLL_Init(Bus80MHz);     // Bus clock is 80 MHz 
  ADC_Init();    // initialize to sample ADC
  PortF_Init();
  IRtranmission_Init(2375); // initialize IR transmitter

  SysTick_Init();
  EnableInterrupts();
  while(1){
    //--UUU--Complete this  - see lab manual
  }
}

/* SysTick ISR
*/
void SysTick_Handler(void){ // at 10 Hz
 //Sample ADC, convert to distance, create 8-byte message, send message out IR LED

}

