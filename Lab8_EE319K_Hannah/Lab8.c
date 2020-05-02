// Lab8.c
// Runs on LM4F120 or TM4C123
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
// Last Modified: 1/17/2020 

// Specifications:
// Measure distance using slide pot, sample at 10 Hz
// maximum distance can be any value from 1.5 to 2cm
// minimum distance is 0 cm
// Calculate distance in fixed point, 0.01cm
// Analog Input connected to PD2=ADC5
// displays distance on Sitronox ST7735
// PF3, PF2, PF1 are heartbeats (use them in creative ways)
// 

#include <stdint.h>

#include "ST7735.h"
#include "TExaS.h"
#include "ADC.h"
#include "print.h"
#include "../inc/tm4c123gh6pm.h"

//*****the first three main programs are for debugging *****
// main1 tests just the ADC and slide pot, use debugger to see data
// main2 adds the LCD to the ADC and slide pot, ADC data is on ST7735
// main3 adds your convert function, position data is no ST7735

long debugger; // make sure that it's signed between 	-2,147,483,648 to 2,147,483,647 for any values necessary
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
	volatile unsigned long nopLoop;
	SYSCTL_RCGCGPIO_R |= 0x20;
	  for(nopLoop = 0; nopLoop < 100 ; nopLoop++) {
			
		}
		GPIO_PORTF_AMSEL_R &= 0xF1;
		GPIO_PORTF_PCTL_R &= 0xFFFF000F;
		GPIO_PORTF_DIR_R |= 0x0E;
		GPIO_PORTF_AFSEL_R &= 0xF1;
		GPIO_PORTF_DEN_R |= 0x0E;
		
}


void SysTick_Init(uint32_t period) {
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = period-1;
	NVIC_ST_CURRENT_R =0;
	NVIC_SYS_PRI3_R = 0x20000000 | ((0x00FFFFFF) & (NVIC_SYS_PRI3_R)); // set priority to 1
	NVIC_ST_CTRL_R = 0x0007;
}

uint32_t Data;
uint32_t Position;
uint32_t mailbox;
uint32_t stat = 1;

void SysTick_Handler(void) {
	PF1 ^= 0x02;
	Data =ADC_In();
	mailbox = Data;
	stat = 1;
	PF1 ^= 0x02;
}

uint32_t Data;        // 12-bit ADC
uint32_t Position;    // 32-bit fixed-point 0.001 cm

// MAIN 1 FUNCTION 
int main(void){       // single step this program and look at Data
  TExaS_Init();       // Bus clock is 80 MHz 
  ADC_Init();         // turn on ADC, set channel to 5
  while(1){                
    Data = ADC_In();  // sample 12-bit channel 5
  }
}

// MAIN 2 FUNCTION
uint32_t time0,time1,time2,time3;
uint32_t ADCtime,OutDectime; // in usec
uint32_t Data;    	// 12-bit ADC
int main2(void){
  TExaS_Init();   	// Bus clock is 80 MHz
  NVIC_ST_RELOAD_R = 0x00FFFFFF; // maximum reload value
  NVIC_ST_CURRENT_R = 0;      	// any write to current clears it
  NVIC_ST_CTRL_R = 5;
  ADC_Init();     	// turn on ADC, set channel to 5
  ADC0_SAC_R = 4;   // 16-point averaging, move this line into your ADC_Init()
  ST7735_InitR(INITR_REDTAB);
  while(1){       	// use SysTick 
    time0 = NVIC_ST_CURRENT_R;
    Data = ADC_In();  // sample 12-bit channel 5
    time1 = NVIC_ST_CURRENT_R;
    ST7735_SetCursor(0,0);
    time2 = NVIC_ST_CURRENT_R;
    LCD_OutDec(Data);
    ST7735_OutString("	");  // spaces cover up characters from last output
    time3 = NVIC_ST_CURRENT_R;
    ADCtime = ((time0-time1)&0x0FFFFFF)/80;	// usec
    OutDectime = ((time2-time3)&0x0FFFFFF)/80; // usec
  }
}

// Convert Potentiometer to 
uint32_t Convert(uint32_t input){
 // return ((56*(input))+27891)/128; // these are dummy numbers 
}
int main3(void){ 
  TExaS_Init();         // Bus clock is 80 MHz 
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
  ADC_Init();         // turn on ADC, set channel to 5
  while(1){  
    PF2 ^= 0x04;      // Heartbeat
    Data = ADC_In();  // sample 12-bit channel 5
    PF3 = 0x08;       // Profile Convert
    Position = Convert(Data); 
    PF3 = 0;          // end of Convert Profile
    PF1 = 0x02;       // Profile LCD
    ST7735_SetCursor(0,0);
    LCD_OutDec(Data); ST7735_OutString("    "); 
    ST7735_SetCursor(6,0);
    LCD_OutFix(Position);
    PF1 = 0;          // end of LCD Profile
  }
}   
int realmain(void){
  TExaS_Init();
	ST7735_InitR(INITR_REDTAB);
	SysTick_Init(2000000);
	PortF_Init();
	ADC_Init();
	
	
	uint32_t output;
	EnableInterrupts();
  // your Lab 8

  while(1){
		if (stat == 1) {
			output = mailbox;
			stat = 0;
			output = Convert(output);
			debugger = Convert(mailbox); 
			if(output <= 217){
			output = 0; 
			}
			ST7735_SetCursor(0,0);
			LCD_OutFix(output);
			ST7735_OutString("cm ");
		}
  }
}

