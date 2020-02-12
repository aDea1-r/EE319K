;****************** HW2.s ***************
; Program written: Adeel Rehman
; Edit myEID to specify your UT EID
; Date Created: 8/30/2017 
; Last Modified: 1/17/2019

GPIO_PORTB_DATA_R  EQU   0x400053FC
GPIO_PORTB_DIR_R   EQU   0x40005400
GPIO_PORTB_DEN_R   EQU   0x4000551C
SYSCTL_RCGCGPIO_R  EQU   0x400FE608

;-----RAM area----------------        
        THUMB
        AREA    DATA, ALIGN=2
;global variables go here, do not change this four definitions
icount  SPACE 2  ;unsigned
bcount  SPACE 1  ;signed
keepOut SPACE 1  ;this location should not be modified
N       SPACE 4
        EXPORT icount
        EXPORT bcount
        EXPORT keepOut
        EXPORT N

;-----ROM area----------------        
      ALIGN
      AREA    |.text|, CODE, READONLY, ALIGN=2
      EXPORT myEID
myEID DCB "aur228",0  ; edit this with your EID
      ALIGN

; enable clock for Port B and make PB6 output
; must be friendly, leave over clock bits as they are
; only use registers R0,R1,R2,R3,R12
; system will crash if you turn off Port A clock
    EXPORT  InitPB6
InitPB6
; put solution here
	;//init clock
	LDR R0, =SYSCTL_RCGCGPIO_R
	LDRB R1, [R0]
	ORR R1, #0x02
	STRB R1, [R0]
	NOP
	NOP
	
	;//make output
	LDR R0, =GPIO_PORTB_DIR_R 
	LDRB R1, [R0]
	ORR R1, #0x040
	STRB R1, [R0]
	
	;//enable digital
	LDR R0, =GPIO_PORTB_DEN_R
	LDRB R1, [R0]
	ORR R1, #0x040
	STRB R1, [R0]
	
    BX  LR
    
; assuming PB6 is output, make PB6 high
; must be friendly
; only use registers R0,R1,R2,R3,R12
    EXPORT  SetPB6
SetPB6
; put solution here
	
	LDR R0, =GPIO_PORTB_DATA_R
	LDRB R1, [R0]
	ORR R1, #0x040
	STRB R1, [R0]
	
	
    BX  LR

; increment 16-bit unsigned icount
; only use registers R0,R1,R2,R3,R12
    EXPORT  Inc16
Inc16
; put solution here
	
	LDR R0, =icount
	LDRH R1, [R0] 
	ADD R1, R1, #0x01
	STRH R1, [R0] 
	
    BX  LR
 
; decrement 8-bit signed bcount
; only use registers R0,R1,R2,R3,R12
    EXPORT  Dec8
Dec8
; put solution here
	LDR  R0, =bcount
	LDRSB R1, [R0]
	ADD R1, R1, #-1
	STRB R1, [R0] 

    BX  LR 
    
; sets bit 4 and clears bit 28 of a 32-bit global variable named N
; be friendly
; only use registers R0,R1,R2,R3,R12
    EXPORT  Set4Clear28
Set4Clear28
; put solution here
	LDR R0, =N
	LDR R1, [R0]
	ORR R1, #0x010
	AND R1, #0xEFFFFFFF
	STR R1, [R0] 

    BX  LR 
    
    

    ALIGN        ; make sure the end of this section is aligned
    END          ; end of file
		