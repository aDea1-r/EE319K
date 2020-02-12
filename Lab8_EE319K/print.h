// Print.h
// This software has interface for printing
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 9/2/2019
// Last Modified:  1/17/2020
// Lab number: 7

#ifndef PRINT_H
#define PRINT_H
#include <stdint.h>

//-----------------------LCD_OutDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: data
// Output: none
void LCD_OutDec(uint32_t data);

//-----------------------LCD_OutFix-----------------------
// Output a 32-bit number in unsigned fixed-point format
// resolution is 0.01
// Input: data
// Output: none
// E.g., data=0,    then output "0.00 "
//       data=3,    then output "0.03 "
//       data=89,   then output "0.89 "
//       data=123,  then output "1.23 "
//       data=999,  then output "9.99 "
//       data>999,  then output "*.** "
void LCD_OutFix(uint32_t data);

#endif
