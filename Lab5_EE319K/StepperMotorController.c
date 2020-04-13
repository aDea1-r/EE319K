// StepperMotorController.c starter file EE319K Lab 5
// Runs on TM4C123
// Finite state machine to operate a stepper motor.  
// Jonathan Valvano
// 1/17/2020

// Hardware connections (External: two input buttons and four outputs to stepper motor)
//  PA5 is Wash input  (1 means pressed, 0 means not pressed)
//  PA4 is Wiper input  (1 means pressed, 0 means not pressed)
//  PE5 is Water pump output (toggle means washing)
//  PE4-0 are stepper motor outputs 
//  **PF1** PF2 or PF3 control the LED on Launchpad used as a heartbeat
//  PB6 is LED output (1 activates external LED on protoboard)

#include "SysTick.h"
#include "TExaS.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "StateMachine.h"

void EnableInterrupts(void);
// edit the following only if you need to move pins from PA4, PE3-0      
// logic analyzer on the real board
#define PA4       (*((volatile unsigned long *)0x40004040))
#define PE50      (*((volatile unsigned long *)0x400240FC))
void SendDataToLogicAnalyzer(void){
  UART0_DR_R = 0x80|(PA4<<2)|PE50;
}

void Heartbeat(void)
{
	GPIO_PORTF_DATA_R ^= 0x02;
}

int main(void){ 
  TExaS_Init(&SendDataToLogicAnalyzer);    // activate logic analyzer and set system clock to 80 MHz
  SysTick_Init();   
// you initialize your system here
	
	SYSCTL_RCGCGPIO_R |= 0x33; 
	
	volatile int a = 0;
	volatile int b = 0;
	
	GPIO_PORTA_DEN_R |= 0x30;
	GPIO_PORTE_DEN_R |= 0x3F;
	GPIO_PORTF_DEN_R |= 0x02;
	GPIO_PORTB_DEN_R |= 0x40;
	
	GPIO_PORTA_DIR_R &= 0xCF;
	GPIO_PORTE_DIR_R &= 0xDF;
	GPIO_PORTE_DIR_R |= 0x3F;
	GPIO_PORTF_DIR_R |= 0x02;
	GPIO_PORTB_DIR_R |= 0x40;
	
	struct State *states = DefineStates();
	struct State *currentStatePtr = &states[0];
	
  EnableInterrupts();   
  while(1){
// output
		GPIO_PORTE_DATA_R &= 0xC0;
		GPIO_PORTE_DATA_R |= currentStatePtr->motorOutput;
		GPIO_PORTE_DATA_R |= currentStatePtr->pumpOutput << 5;

// wait
		Heartbeat();
		SysTick_Wait1ms(currentStatePtr->delay);
// input
		uint8_t wash = (GPIO_PORTA_DATA_R >> 5) & 0x01;
		uint8_t wiper = (GPIO_PORTA_DATA_R >> 4) & 0x01;
// next	
		currentStatePtr = currentStatePtr->output[wiper][wash];
		volatile int c = 0;
  }
}
