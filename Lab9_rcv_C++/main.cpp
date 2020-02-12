// main.cpp
// Runs on LM4F120 or TM4C123
// Created: 1/16/2020 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

// Analog Input connected to PD2=ADC5 on the other computer
// displays on Sitronox ST7735 of this computer
// PF3, PF2, PF1 are heartbeats

// Simplex communication
// EE319K Lab 9 hardware
// Use PC5 38 kHz modulated light output
// System xmt                        System rcv
//   PC5 --IR LED--> light >--IR sensor--- PC4
//   Gnd --------- not connected --------- Gnd

// main1 Understand UART interrupts
// main2 Implement and test the FIFO class on the receiver end 
//   import ST7735 code from Lab 7,8
// main3 convert UART0 to UART1, implement busy-wait on transmission
// final main for Lab 9
//   Figure out what to do in UART1_Handler ISR (receive message)
//   Figure out what to do in main (LCD output)


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "ST7735.h"
#include "PLL.h"
#include "print.h"
#include "UART.h"
#include "FIFO.h"

extern "C" void DisableInterrupts(void);
extern "C" void EnableInterrupts(void);
extern "C" void SysTick_Handler(void);

// PF1 should be toggled in UART ISR (receive data)
// PF2 should be toggled in SysTick ISR (60 Hz sampling)
#define PF1  (*((volatile uint32_t *)0x40025008))
#define PF2  (*((volatile uint32_t *)0x40025010))
#define PF3  (*((volatile uint32_t *)0x40025020))
#define PF4  (*((volatile uint32_t *)0x40025040))


// Initialize Port F so PF1, PF2 and PF3 are heartbeats
void PortF_Init(void){
  
}

// main1 is used to run initial code with UART0
// this code should run without changing 
// and interact with serial terminal on PC
int main1(void){  // run this program and look at Data
char letter;
  DisableInterrupts();
  PLL_Init(Bus80MHz);     // set system clock to 80 MHz
  PortF_Init();
  UART_Init();   // enable UART
  EnableInterrupts();
  UART_OutString((char *)"1234567890\n\r");
  UART_OutString((char *)"abcdefghij\n\r");
  UART_OutUDec(12345); UART_OutChar(LF); UART_OutChar(CR);
  while(1){   
    letter = UART_InChar();
    UART_OutChar(letter);    
  }
}

// step two, implement the FIFO class
// FIFO.h is prototype
// FIFO.cpp is implementation
// main2 program will test FIFO
Queue FIFO;
int main2(void){
  char data = 0; char out;
  DisableInterrupts();
  PLL_Init(Bus80MHz);     // set system clock to 80 MHz
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
  
  while(1){
    int count=0;
    for(int i=0; i<10; i++){
      if(FIFO.Put(data)){
        count++;
        data++;
      }
    }
    FIFO.Print();
    for(int i=0; i<count; i++){
      FIFO.Get(&out);
    }   
    PF2 ^= 0x04;   
  }
}

// step 3
// Convert UART0 to UART1
// Move PA1,PA0 to PC5, PC4
// Use queue class in receiver interrupt
// change receiver interrupt to 1/2 full only
// change transmitter to busy wait
// PF1 toggles in UART ISR
// PF2 toggles in main
int main3(void){
  char OutData = 'A'; 
  char InData;
  int count = 0;
  uint32_t time=0;
  DisableInterrupts();
  PLL_Init(Bus80MHz);     // set system clock to 80 MHz
  ST7735_InitR(INITR_REDTAB); 
  PortF_Init();
  UART_Init();       // enable UART
  EnableInterrupts();
  while(1){           
    time++;
    if((time%100000)==0){
      UART_OutChar(OutData);
      if(OutData == 'Z'){
        OutData = 'A';
      }else{
        OutData++;
      }
    }
    if(UART_InStatus()){
      InData = UART_InChar();
      ST7735_OutChar(InData);
      count++;
      if((count%16)==0){
        ST7735_OutChar('\n');
      }
      PF2 ^= 0x04;
    }
  }
}


// final main program for simplex communication
// Sender is the other computer
// This is the receiver using UART1 interrupts
int main(void){  
// initialize UART1, must match baud rate from sender
  while(1){ 

  }
}


