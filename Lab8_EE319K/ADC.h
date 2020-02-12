// ADC.h
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 1/17/2020
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
#ifndef ADC_H
#define ADC_H
#include <stdint.h>

// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
void ADC_Init(void);

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
uint32_t ADC_In(void);
#endif
