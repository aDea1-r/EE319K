// StepperTestMain.c
// Runs on LM4F120/TM4C123
// FSM control of stepper
// 5-phase stepper motor, about 70 steps/rotation
// Input operation
// 00    stop
// 01    clockwise 1,2,4,8,16,...
// 10    counterclockwise 16,8,4,2,1,...
// 11    stop
// Daniel and Jonathan Valvano
// November 15, 2018

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2018
   Example 4.1, Programs 4.4, 4.5, and 4.6
   Hardware circuit diagram Figure 4.27

 Copyright 2018 by Jonathan W. Valvano, valvano@mail.utexas.edu
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
// PC6 connected to switch input
// PC5 connected to switch input
// PB4 connected to driver for stepper motor coil phase 1
// PB3 connected to driver for stepper motor coil phase 2
// PB2 connected to driver for stepper motor coil phase 3
// PB1 connected to driver for stepper motor coil phase 4
// PB0 connected to driver for stepper motor coil phase 5
#include <stdint.h>
#include "systick.h"
#include "TExaS.h"
#include "../inc/tm4c123gh6pm.h"
#define T1sec 1000   
#define T100ms 100   
#define T10ms 10      
struct State{
  char Name[4];    // 1,2 or 3 character string
  uint8_t Out;     // 5-bit output to stepper      
  uint32_t Delay;  // in 1ms units
  const struct State *Next[4]; 
};
typedef const struct State StateType;
#define P1  &fsm[0]
#define P2  &fsm[1]
#define P3  &fsm[2]
#define P4  &fsm[3]
#define P5  &fsm[4]
StateType fsm[5]={
  {"P1", 1, T10ms, P1, P2, P5, P1}, //220mA
  {"P2", 2, T10ms, P2, P3, P1, P2},
  {"P3", 4, T10ms, P3, P4, P2, P3},
  {"P4", 8, T10ms, P4, P5, P3, P4},
  {"P5",16, T10ms, P5, P1, P4, P5}
//	{"P1", 3, T10ms, P1, P2, P5, P1}, // 380mA
//  {"P2",  6, T10ms, P2, P3, P1, P2},
//  {"P3", 12, T10ms, P3, P4, P2, P3},
//  {"P4", 24, T10ms, P4, P5, P3, P4},
//  {"P5", 17, T10ms, P5, P1, P4, P5}
//	{"P1", 7, T10ms, P1, P2, P5, P1}, //510mA
//  {"P2",14, T10ms, P2, P3, P1, P2},
//  {"P3",28, T10ms, P3, P4, P2, P3},
//  {"P4",25, T10ms, P4, P5, P3, P4},
//  {"P5",19, T10ms, P5, P1, P4, P5}
};
const struct State *Pt;  // Current State
// old Port B definitions in=PB6,5, out=PB4-0
// Port B definitions in=PC6,5, out=PB4-0
#define STEPPER (*((volatile uint32_t *)0x4000507C))
#define SHIFT 5
#define INPUT   (*((volatile uint32_t *)0x40006180))
//#define INPUT   (*((volatile uint32_t *)0x40005180))
//#define STEPPER  (*((volatile uint32_t *)0x4000703C))
//#define INPUT  (*((volatile uint32_t *)0x40007300))
uint32_t Input;
int main(void){
  TExaS_Init(1);           // 80 MHz, Port B logic analyzer
  SysTick_Init();          // Program 4.7
  SYSCTL_RCGCGPIO_R |= 0x04;  // 1) port C clock enabled
  SYSCTL_RCGCGPIO_R |= 0x02;  // 1) port B clock enabled
  Pt = P1;               
  GPIO_PORTB_AMSEL_R &= ~0x7F;      // 3) disable analog function
  GPIO_PORTB_PCTL_R &= ~0x0FFFFFFF; // 4) GPIO
  GPIO_PORTB_DIR_R |= 0x1F;   // 5) make PB4-0
 // GPIO_PORTB_DIR_R &= ~0x60;  //    make PB6-5 input
 // GPIO_PORTB_PDR_R |= 0x60;   //    make PB6-5 pull down
  GPIO_PORTB_AFSEL_R &= ~0x7F;// 6) disable alt func on PB6-0
  GPIO_PORTB_DR8R_R |= 0x1F;  // enable 8 mA drive on PB4-0
  GPIO_PORTB_DEN_R |= 0x1F;   // 7) enable digital I/O on PB5-0
  GPIO_PORTC_DIR_R &= ~0x60;  //    make PC6-5 input
  GPIO_PORTC_DEN_R |= 0x60;   // 7) enable digital I/O on PC6-5
  GPIO_PORTC_PDR_R |= 0x60;   //    make PC6-5 pull down
//	while(1){
//		for(int i=0;i<132;i++){
//      STEPPER = Pt->Out;           // Output 5 bits to stepper
//      SysTick_Wait1ms(Pt->Delay);  // Wait for this state
//      Pt = Pt->Next[1];        // Next   
//		}
//		while(INPUT == 0){}
//	}

			
  while(1){
    STEPPER = Pt->Out;           // Output 5 bits to stepper
    SysTick_Wait1ms(Pt->Delay);  // Wait for this state
    Input = (INPUT>>SHIFT);      // Input 2 bits from switches 0,1,2,3
    Pt = Pt->Next[Input];        // Next   
  }
}
