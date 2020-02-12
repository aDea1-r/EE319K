;****************** main.s ***************
; Program written by: Valvano
; Date Created: 8/25/2013 
; Last Modified: 1/18/2019 
; Section 1-2pm     TA: Saugata Bhattacharyya
; Class example  PE1 = NOT(PE0)
; Brief description of the program
; The overall objective of this system is a digital NOT gate
; Hardware connections
;  PE0 is switch input  (0 means false, 1 means true)
;  PE1 is LED output (0 means false, 1 means true) 

GPIO_PORTE_DATA_R       EQU   0x400243FC
GPIO_PORTE_DIR_R        EQU   0x40024400
GPIO_PORTE_AFSEL_R      EQU   0x40024420
GPIO_PORTE_DEN_R        EQU   0x4002451C
GPIO_PORTE_AMSEL_R      EQU   0x40024528
GPIO_PORTE_PCTL_R       EQU   0x4002452C
SYSCTL_RCGCGPIO_R       EQU   0x400FE608
;EE319K is about I/O
;software
; initialization
;   clock
;   direction Pin input/output
;   enable
; Input
;   Read entire port
;   Mask, AND to select
; Output PE1 =1
;   Write all bits of a GPIO_PORTE_DATA_R=0x02;
; 0x02 00000010
;   Read all of it
;   Clear/set bits
;   Write all bits
   AREA  DATA,ALIGN=2
Data SPACE 4       
   AREA    |.text|, CODE, READONLY, ALIGN=2
   THUMB
SetDataTo5
   LDR  R0,=Data
   MOV  R1,#5 ; dollars
   STR  R1,[R0] ; initialize Data
   BX   LR
 ;AND ORR EOR BIC
InitF

   ; input
   ; read all, mask 0x11
   ; output?
   ;   1 read all
   ;   2set bits ORR
   ;    3 clear bit BIC
   ;    4 write all back
   EXPORT  Start
Start
   BL  SetDataTo5
   ;BL  InitF

   LDR R0,=SYSCTL_RCGCGPIO_R  ; R0 points to SYSCTL_RCGCGPIO_R
   LDR R1,[R0]    ; read SYSCTL_RCGCGPIO_R into R1
   ORR R1,#0x10   ;turn on clock Bin: 00010000
   STR R1,[R0]    ; write back to SYSCTL_RCGCGPIO_R
   NOP            ; wait for clock to stabilize
   NOP
   LDR R0,=GPIO_PORTE_DIR_R
   MOV R1,#0x02   ;PE1 output, PE0 input
   STR R1,[R0]
   LDR R0,=GPIO_PORTE_DEN_R
   MOV R1,#0x03   ;enable PE1,PE0
   STR R1,[R0]
   
   LDR R0,=GPIO_PORTE_DATA_R  ;R0 = 0x400243FC
loop
   LDR R1,[R0]   ;Read Port E
   AND R1,#1     ;mask, select PE0
   EOR R1,#1     ;NOT
   LSL R1,R1,#1  ;move to bit 1
   STR R1,[R0]   ;write Port E, sets PE1

   B   loop


   ALIGN        ; make sure the end of this section is aligned
   END          ; end of file
   