// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 1/17/2020 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "../inc/tm4c123gh6pm.h"

// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none
void Sound_Init(void){
  NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000;
	
	DAC_Init(); 
}

// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Play called again
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period to be determined by YOU
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
void Sound_Play(uint32_t period){
	if (period == 0) {
		NVIC_ST_CTRL_R = 0;
		return; 
	}
	NVIC_ST_RELOAD_R = period-1;
	NVIC_ST_CTRL_R = 7;
}

uint8_t i  = 0; //ranges from 0-63
uint8_t SinWave[64] = {32,35,38,41,44,46,49,51,
									     54,56,58,59,61,62,62,63,
							     		 63,63,62,62,61,59,58,56,
											 54,51,49,46,44,41,38,35,
									     32,28,25,22,19,17,14,12,
									     9,7,5,4,2,1,1,0,
									     0,0,1,1,2,4,5,7,
									     9,12,14,17,19,22,25,28};
void SysTick_Handler(void) {
	i++;
	i &= 0x3F;
	DAC_Out(SinWave[i]);
}
