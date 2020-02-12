// SlidePot.h
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0 and use a slide pot to measure distance
// Created: 3/28/2018 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly


#ifndef SLIDEPOT_H
#define SLIDEPOT_H
#include <stdint.h>

class SlidePot{ private:
  uint32_t data;     // raw ADC value
  int32_t flag;      // 0 if data is not valid, 1 if valid
  uint32_t distance; // distance in 0.001cm

// distance = (slope*data+offset)/4096
  uint32_t slope;    // calibration coeffients
  uint32_t offset;
public:
  SlidePot(uint32_t m, uint32_t b); // initialize slide pot
  void Save(uint32_t n);        // save ADC, set semaphore
  void Sync(void);              // wait for semaphore
  uint32_t Convert(uint32_t n); // convert ADC to raw sample
  uint32_t ADCsample(void);     // return ADC sample value (0 to 4095)
  uint32_t Distance(void);      // return distance value (0 to 2000), 0.001cm
};

// ADC initialization function, channel 5, PD2
// Input: none
// Output: none
void ADC_Init(void);

//------------ADC_In------------
// Busy-wait Analog to digital conversion, channel 5, PD2
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_In(void);

#endif
