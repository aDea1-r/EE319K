// Lab8.cpp
// Runs on LM4F120 or TM4C123
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
// Last Modified: 1/17/2020 

// Specifications:
// Measure distance using slide pot, sample at 60 Hz
// maximum distance can be any value from 1.5 to 2cm
// minimum distance is 0 cm
// Calculate distance in fixed point, 0.01cm
// Analog Input connected to PD2=ADC5
// displays distance on Sitronox ST7735
// PF3, PF2, PF1 are heartbeats (use them in creative ways)
// must include at least one class used in an appropriate way

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "ST7735.h"
#include "TExaS.h"
#include "PLL.h"
#include "SlidePot.h"
#include "print.h"

SlidePot Sensor(150,0);

extern "C" void DisableInterrupts(void);
extern "C" void EnableInterrupts(void);
extern "C" void SysTick_Handler(void);

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
#define PF4       (*((volatile uint32_t *)0x40025040))
// **************SysTick_Init*********************
// Initialize Systick periodic interrupts
// Input: interrupt period
//        Units of period are 12.5ns
//        Maximum is 2^24-1
//        Minimum is determined by length of ISR
// Output: none
void SysTick_Init(unsigned long period){
  //*** students write this ******
}

// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
  //*** students write this ******

}
uint32_t Data;      // 12-bit ADC
uint32_t Position;  // 32-bit fixed-point 0.01 cm
int main1(void){      // single step this program and look at Data
  DisableInterrupts();
  TExaS_Init();      // start scope set system clock to 80 MHz
  ADC_Init();        // turn on ADC, PD2, set channel to 5
  EnableInterrupts();
  while(1){                
    Data = ADC_In();  // sample 12-bit channel 5, PD2
  }
}

int main2(void){
  DisableInterrupts();
  TExaS_Init();       // Bus clock is 80 MHz 
  ADC_Init();        // turn on ADC, PD2, set channel to 5
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
  EnableInterrupts();
  while(1){           // use scope to measure execution time for ADC_In and LCD_OutDec           
    PF2 = 0x04;       // Profile ADC
    Data = ADC_In();  // sample 12-bit channel 5, PD2
    PF2 = 0x00;       // end of ADC Profile
    ST7735_SetCursor(0,0);
    PF1 = 0x02;       // Profile LCD
    LCD_OutDec(Data); 
    ST7735_OutString("    ");  // these spaces are used to coverup characters from last output
    PF1 = 0;          // end of LCD Profile
  }
}



int main3(void){ 
  DisableInterrupts();
  TExaS_Init();         // Bus clock is 80 MHz 
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
  ADC_Init();        // turn on ADC, PD2, set channel to 5
  EnableInterrupts();
  while(1){  
    PF2 ^= 0x04;      // Heartbeat
    Data = ADC_In();  // sample 12-bit channel 5, PD2
    PF3 = 0x08;       // Profile Convert
    Position = Sensor.Convert(Data); 
    PF3 = 0;          // end of Convert Profile
    PF1 = 0x02;       // Profile LCD
    ST7735_SetCursor(0,0);
    LCD_OutDec(Data); ST7735_OutString("    "); 
    ST7735_SetCursor(6,0);
    LCD_OutFix(Position);
    PF1 = 0;          // end of LCD Profile
  }
}   


// final main program to create distance meter
int main(void){ 
    //*** students write this ******

  DisableInterrupts();
  TExaS_Init();    // bus clock at 80 MHz
  ST7735_InitR(INITR_REDTAB); 
  ADC_Init();        // turn on ADC, PD2, set channel to 5
  PortF_Init();

  // more initializations
  EnableInterrupts();

  while(1){
    Sensor.Sync(); // wait for semaphore
    // can call Sensor.ADCsample, Sensor.Distance, Sensor.Convert as needed 
      
  }
}
void SysTick_Handler(void){ // every sample
    //*** students write this ******
// should call ADC_In() and Sensor.Save
  Sensor.Save(ADC_In());
}
