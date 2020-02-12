// main.cpp
// Runs on LM4F120 or TM4C123
// Created: 1/16/2020 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly


// Analog Input connected to PD2=ADC5

// PF3, PF2, PF1 are heartbeats
// Simplex communication
// EE319K Lab 9 hardware
// Use PC5 38 kHz modulated light output
// System xmt                        System rcv
//   PC5 --IR LED--> light >--IR sensor--- PC4
//   Gnd --------- not connected --------- Gnd

// main1 Test IRtranmission_Init and IRtranmission_OutChar
// final main for Lab 9
//   Import SlidePot and ADC code from Lab8. 
//   Figure out what to do in SysTickHandler (sample, convert, transmit message)

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "SlidePot.h"
#include "IRtranmission.h"

SlidePot my(150,0);

extern "C" void DisableInterrupts(void);
extern "C" void EnableInterrupts(void);
extern "C" void SysTick_Handler(void);

// PF1 could be toggled in main program
// PF2 could be toggled in SysTick ISR (10 Hz sampling)
#define PF1  (*((volatile uint32_t *)0x40025008))
#define PF2  (*((volatile uint32_t *)0x40025010))
#define PF3  (*((volatile uint32_t *)0x40025020))
#define PF4  (*((volatile uint32_t *)0x40025040))

// **************SysTick_Init*********************
// Initialize Systick periodic interrupts
// Input: interrupt period
//        Units of period are 12.5ns
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR
// Output: none
void SysTick_Init(unsigned long period){
  
}

// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
  
}

// main1 is used to run initial code with IRtranmission
int main1(void){  // run this program and look at signals on PC5
  DisableInterrupts();
  PLL_Init(Bus80MHz);     // set system clock to 80 MHz
  PortF_Init();
  IRtranmission_Init(2375);    // initialize transmitter, baud rate is 2375 bits/sec
  while(1){   
    IRtranmission_OutChar(0x5A);
    for(int i=0;i<100000;i++){};    
  }
}

// final main program for simplex communication
// Sender sends using SysTick Interrupt
int main(void){  // valvano version
  PLL_Init(Bus80MHz);       // Bus clock is 80 MHz 
  ADC_Init();    // initialize to sample ADC
  PortF_Init();
  IRtranmission_Init(2375);    // initialize transmitter, baud rate is 2375 bits/sec
//Enable SysTick Interrupt by calling SysTick_Init()
  SysTick_Init(80000000/10); // Interrupt at 10Hz
  EnableInterrupts();
  while(1){ // runs every 100 ms
    PF1 ^= 0x02;  // Heartbeat
  }
}

void SysTick_Handler(void){ // every 100 ms
//Similar to Lab8 except rather than grab sample,
// form a message, transmit 

  PF2 ^= 0x04;  // Heartbeat
  PF2 ^= 0x04;  // Heartbeat
  // you write this
  PF2 ^= 0x04;  // Heartbeat
}

