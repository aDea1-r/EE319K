// SlidePot.cpp
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Created: 1/16/2020 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "SlidePot.h"
#include "../inc/tm4c123gh6pm.h"


// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
void ADC_Init(void){ volatile uint32_t delay;
  
  // you write this

}

//------------ADCIn------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
uint32_t ADC_In(void){  
  // you write this

  return 0; // remove this, replace with real code
}

// constructor, invoked on creation of class
// m and b are linear calibration coeffients 
SlidePot::SlidePot(uint32_t m, uint32_t b){
  // you write this

}

void SlidePot::Save(uint32_t n){
  // you write this

}
uint32_t SlidePot::Convert(uint32_t n){
    // you write this

  return 0; // replace this line with real code
}

void SlidePot::Sync(void){
  // you write this

}

uint32_t SlidePot::ADCsample(void){ // return ADC sample value (0 to 4095)
    // you write this

  return data;
}

uint32_t SlidePot::Distance(void){  // return distance value (0 to 2000), 0.001cm
  return distance;
}
