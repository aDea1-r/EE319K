// IRtranmission.cpp
// Runs on LM4F120/TM4C123
// This code runs on PC5 GPIO output
// EE319K tasks
// 1) Run transmitter with blind cycle synchronization
// Created: 1/16/2020 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

// Simplex communication
// EE319K Lab 9 hardware
// Use PC5 38 kHz modulated light output
// System xmt                        System rcv
//   PC5 --IR LED--> light >--IR sensor--- PC4
//   Gnd --------- not connected --------- Gnd
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

#include "IRtranmission.h"

#define PC5  (*((volatile uint32_t *)0x40006080))

// Initialize GPIO on PC5
// Baud rate should divide evenly into 38,000
// 38 kHz is 26.3us period
// 38 kHz wave is on for 13.16us, off for 13.16us
// Lab 9
// For example baud=2375 is 38000/2375=16 pulses per bit time
void IRtranmission_Init(uint32_t baud){
// in lab 9 write this
}
// to get  38kHz wave, look at output on scope and 
// adjust the constant IRPULSE to get 38kHz output on PC5 
#define IRPULSE 171
void Clock_Delay(uint32_t ulCount){
  while(ulCount){
    ulCount--;
  }
}

// output ASCII character to IR transmitter
// blind cycle synchronization
// in Lab 9 this will wait until tranmission is done
// start=0,bit0,bit1,bit2,bit2,bit4,bit5,bit6,bit7,stop=1
// 0 means 30 kHz pulse for 1 bit time
// 1 means no pulses for 1 bit time
void IRtranmission_OutChar(char data){
// in lab 9 write this

}



