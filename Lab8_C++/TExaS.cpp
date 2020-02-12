// TExaS.cpp
// Runs on LM4F120/TM4C123
// Periodic timer interrupt data collection
// PLL must be on for ADC to work (turned on in startup)
// ADC1 PD3 Ain4 continuous sampling (turned on in startup)
// EE319K Lab 8
// in general, students should not edit this file

// Uses Timer5A to sample ADC
// Jonathan Valvano
// 1/17/2020

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2018

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

#include "TExaS.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"

// Timer5A periodic interrupt collects data
// ADC1 channel 4 PD3 continuously samples
void ADC1_Init(void);
void UART0_Init(void);
extern "C" void TIMER5A_Handler(void);

// ************TExaS_Init*****************
// Initialize scope, triggered by timer 5A
// This needs to be called once
// Inputs: iport input(s) connected to this port
//         oport output(s) connected to this port
// Outputs: none
void TExaS_Init(void){
  PLL_Init(Bus80MHz);     // ADC needs PLL on to run
  UART0_Init();
  SYSCTL_RCGCTIMER_R |= 0x20;      // 0) activate timer5
  TIMER5_CTL_R = 0x00000000;       // 1) disable timer5A during setup
  TIMER5_CFG_R = 0x00000000;       // 2) configure for 32-bit mode
  TIMER5_TAMR_R = 0x00000002;      // 3) configure for periodic mode, default down-count settings
  TIMER5_TAILR_R = 7999;           // 4) 100us reload value
  TIMER5_TAPR_R = 0;               // 5) bus clock resolution
  TIMER5_ICR_R = 0x00000001;       // 6) clear timer5A timeout flag
  TIMER5_IMR_R = 0x00000001;       // 7) arm timeout interrupt
  NVIC_PRI23_R = (NVIC_PRI23_R&0xFFFFFF00)|0x00000040; // 8) priority 2
// interrupts enabled in the main program after all devices initialized
// vector number 108, interrupt number 92
  NVIC_EN2_R = 0x10000000;         // 9) enable interrupt 92 in NVIC
  TIMER5_CTL_R = 0x00000001;       // 10) enable timer5A

  ADC1_Init();     // called after PLL on

}

// scope occurs in the background
void TIMER5A_Handler(void){ 
  TIMER5_ICR_R = 0x00000001;        // acknowledge timer5A timeout
  UART0_DR_R = (ADC1_SSFIFO3_R>>4); // send ADC to TExaSdisplay
}

// ************TExaS_Stop*****************
// Stop the transfer
// Inputs:  none
// Outputs: none
void TExaS_Stop(void){
  NVIC_DIS2_R = 0x10000000;       // 9) disable interrupt 92 in NVIC
  TIMER5_CTL_R = 0x00000000;      // 10) disable timer5A
}
// start conversions, sample always (continuous)
// ADC1
// PD3 Ain4
// 16-point averaging 125kHz sampling
void ADC1_Init(void){ volatile unsigned long delay;
//  SYSCTL_RCGC2_R |= 0x08;         // 1) activate clock for Port D
  SYSCTL_RCGCGPIO_R |= 0x08;      // 1) activate clock for Port D
  delay = SYSCTL_RCGC2_R;         //    allow time for clock to stabilize
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTD_DIR_R &= ~0x08;      // 2) make PD3 input
  GPIO_PORTD_AFSEL_R |= 0x08;     // 3) enable alternate function on PD3
  GPIO_PORTD_DEN_R &= ~0x08;      // 4) disable digital I/O on PD3
  GPIO_PORTD_AMSEL_R |= 0x08;     // 5) enable analog functionality on PD3
//  SYSCTL_RCGC0_R |= 0x00020000;   // 6) activate ADC1 (legacy code)
  SYSCTL_RCGCADC_R |= 0x02;
  for(delay = 0; delay<20; delay++){};  // allow time for clock to stabilize
//  SYSCTL_RCGC0_R &= ~0x00000C00;  // 7) configure for 125K (legacy code)
  ADC1_PC_R = 0x01;               // 7) 125K rate
  ADC1_SSPRI_R = 0x0123;          // 8) Sequencer 3 is highest priority
  ADC1_ACTSS_R = 0x0000;          // 9) disable sample sequencer 3
  ADC1_EMUX_R |= 0xF000;          // 10) seq3 is always/continuous trigger
  ADC1_SAC_R = 0x04;              //   16-point average 125kHz/16 = 7kHz
  ADC1_SSMUX3_R = 4;              // 11) set channel 4
  ADC1_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
  ADC1_IM_R = 0x0000;             // 13) disable SS3 interrupts
  ADC1_ACTSS_R = 0x0008;          // 14) enable sample sequencer 3
}


//------------UART0_Init------------
// Initialize the UART for 115,200 baud rate (assuming 80 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART0_Init(void){volatile unsigned long delay;
  SYSCTL_RCGCUART_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOA; // activate port A
                                        // wait for clock to stabilize
//  while((SYSCTL_PRUART_R&SYSCTL_PRUART_R0) == 0){};
  delay =SYSCTL_RCGC2_R;
  delay =SYSCTL_RCGC2_R;
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
  UART0_FBRD_R = 26;                    // FBRD = round(0.402778 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CC_R &= ~UART_CC_CS_M;          // clear baud clock control field
  UART0_CC_R |= UART_CC_CS_SYSCLK;      // configure for system clock
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
//  while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R0) == 0){};
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}
