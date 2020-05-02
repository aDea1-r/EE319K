// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 1/17/2020
// Student names: Alexander Tan at39782	Hannah Saquing HOS252
// Last modification date: 4/20

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
void ADC_Init(void){ 
	volatile unsigned long nopLoop;
	  SYSCTL_RCGCGPIO_R |= 0x10;  // activate clock for Port E
	  for(nopLoop = 0; nopLoop < 100 ; nopLoop++) {
			// time for clock to stabilize
		}
		
	GPIO_PORTD_DIR_R   &= 0xFB; // FB = ~0x04 = 1111 1011
	GPIO_PORTD_AFSEL_R |= 0x04;
	GPIO_PORTD_DEN_R   &= 0xFB;
	GPIO_PORTD_AMSEL_R |= 0x04;
	SYSCTL_RCGCADC_R	 |= 0x01;
		for(nopLoop = 0; nopLoop < 100 ; nopLoop++) {
			
		}
		
	ADC0_PC_R = 0x01;	// configure for 125k ohm resistor
	ADC0_SSPRI_R = 0x0123;	// S3 to highest priority
	ADC0_ACTSS_R &= 0xFFF7; // disable S3 sample
	ADC0_EMUX_R &= 0x0FFF; // S3 is software trigger
	ADC0_SSMUX3_R = 1+(0xFFFFFFFF0 & ADC0_SSMUX3_R); // get PE2
	ADC0_SSCTL3_R = 0x0006;
	ADC0_IM_R &= 0xFFF7;
	ADC0_ACTSS_R |= 0x0008; // enable S3 sample
}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
// measures from PD2, analog channel 5
uint32_t ADC_In(void){  
	unsigned long conversion;
	ADC0_PSSI_R = 0x0008; // initiate SS3
	while((ADC0_RIS_R & 0X08) ==0){
		// wait for conversion
		}
	conversion = ADC0_SSFIFO3_R & 0xFFF; // read result
	ADC0_ISC_R = 0x0008; // acknowledge completion
  return conversion; 
}


