;****************** main.s ***************
; Program initially written by: Yerraballi and Valvano
; Author: Adeel Rehman
; Date Created: 1/15/2018 
; Last Modified: 1/30/2020 
; Brief description of the program: Solution to Lab1
; The objective of this system is to implement odd-bit counting system
; Hardware connections: 
;  Output is positive logic, 1 turns on the LED, 0 turns off the LED
;  Inputs are negative logic, meaning switch not pressed is 1, pressed is 0
;    PE0 is an input 
;    PE1 is an input 
;    PE2 is an input 
;    PE3 is the output
; Overall goal: 
;   Make the output 1 if there is an odd number of switches pressed, 
;     otherwise make the output 0

; The specific operation of this system 
;   Initialize Port E to make PE0,PE1,PE2 inputs and PE3 an output
;   Over and over, read the inputs, calculate the result and set the output
; PE2  PE1 PE0  | PE3
; 0    0    0   |  1    odd number of 0’s //not xor? 
; 0    0    1   |  0    even number of 0’s
; 0    1    0   |  0    even number of 0’s
; 0    1    1   |  1    odd number of 0’s
; 1    0    0   |  0    even number of 0’s
; 1    0    1   |  1    odd number of 0’s
; 1    1    0   |  1    odd number of 0’s
; 1    1    1   |  0    even number of 0’s
;There are 8 valid output values for Port E: 0x01,0x02,0x04,0x07,0x08,0x0B,0x0D, and 0x0E. 

; NOTE: Do not use any conditional branches in your solution. 
;       We want you to think of the solution in terms of logical and shift operations

GPIO_PORTE_DATA_R  EQU 0x400243FC
GPIO_PORTE_DIR_R   EQU 0x40024400
GPIO_PORTE_DEN_R   EQU 0x4002451C
SYSCTL_RCGCGPIO_R  EQU 0x400FE608

       THUMB
       AREA    DATA, ALIGN=2
;global variables go here
      ALIGN
      AREA    |.text|, CODE, READONLY, ALIGN=2
      EXPORT  Start
Start
    ;code to run once that initializes PE3,PE2,PE1,PE0
	LDR R0, =SYSCTL_RCGCGPIO_R ;//clock register
	LDRB R1, [R0]
	ORR R1, #0x10
	STRB R1, [R0]
	
	NOP
	NOP
	
	LDR R0, =GPIO_PORTE_DIR_R ;//direction register
	LDRB R1, [R0]
	AND R1, #0xF8
	ORR R1, #0x08 ;//outputs are 1, inputs are 0
	STRB R1, [R0]
	
	LDR R0, =GPIO_PORTE_DEN_R
	LDRB R1, [R0]
	ORR R1, #0xF
	STRB R1, [R0]
	
	LDR R1, =GPIO_PORTE_DATA_R
loop
    ;code that runs over and over
	 ;//pin0
	LDRB R2, [R1]
	AND R2, #0x1
	LDRB R3, [R1] ;//pin1
	LSR R3, #0x1
	AND R3, #0x1
	LDRB R4, [R1] ;//pin2
	LSR R4, #0x2
	AND R4, #0x1
	EOR R2, R3
	EOR R2, R4
	LSL R2, #0x3
	EOR R2, #0x8 ;nots 4th bit
	;LDR R1, =GPIO_PORTE_DATA_R ;pin3
	LDRB R0, [R1]
	AND R0, #0xF7
	ORR R0, R2
	STRB R0, [R1]
    B    loop


    
      ALIGN        ; make sure the end of this section is aligned
      END          ; end of file
          