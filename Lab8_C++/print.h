// print.h
// Runs on LM4F120/TM4C123
// Use SSI0 to send an 8-bit code to the Nokia5110 48x84
// pixel LCD to display text, images, or other information.
// Daniel Valvano
// 1/17/2020

#ifndef PRINT_H
#define PRINT_H
#include <stdint.h>

//-----------------------LCD_OutDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: data is a 32-bit unsigned number
// Output: none
// students implement this as part of Lab 7
extern "C" void LCD_OutDec(uint32_t data);

// -----------------------LCD _OutFix----------------------
// Output characters to LCD display in fixed-point format
// unsigned decimal, resolution 0.01, range 0.000 to 9.99
// Inputs:  unsigned 32-bit number
// Outputs: none
// E.g., data=0,    then output "0.00 "
//       data=3,    then output "0.03 "
//       data=89,   then output "0.89 "
//       data=123,  then output "1.23 "
//       data=999,  then output "9.99 "
//       data>999,  then output "*.** "
// students implement this as part of Lab 7
extern "C" void LCD_OutFix(uint32_t data);

#endif
