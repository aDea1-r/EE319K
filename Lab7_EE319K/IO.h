// IO.h
// This file has interface for IO module
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: March 30, 2018
// Last Modified:  change this line or look silly
// Lab number: 7


#ifndef IO_H
#define IO_H
#include <stdint.h>
//------------IO_Init------------
// Initialize GPIO Port for a switch and an LED
// Input: none
// Output: none
void IO_Init(void);

//------------IO_HeartBeat------------
// Toggle the output state of the  LED.
// Input: none
// Output: none
void IO_HeartBeat(void);


//------------IO_Touch------------
// wait for release and touch of the switch
// Delay to debounce the switch
// Input: none
// Output: none
void IO_Touch(void);

#endif
