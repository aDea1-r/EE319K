; Print.s
; Student names: Zachary Bouthillette and Adeel Rehman
; Last modification date: 4/15/20
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 

    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB

  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
; Lab 7 requirement is for at least one local variable on the stack with symbolic binding
LCD_OutDec
	
	MOV R3, #10
	UDIV R1, R0, R3 ;find remaining digits to print
	
	MUL R2, R1, R3 ;find calculate digit to print (put in R0)
	SUB R0, R0, R2
	
	PUSH {R0, LR}
	MOVS R0, R1
	BEQ af
	BL LCD_OutDec
af	POP {R0, LR}
	
	ADD R0, R0, #0x30
	PUSH {R0, LR}
	BL ST7735_OutChar
	POP {R0, LR}

      BX  LR
	
;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.01, range 0.00 to 9.99
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.00 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.89 "
;       R0=123,  then output "1.23 "
;       R0=999,  then output "9.99 "
;       R0>999,  then output "*.** "
; Invariables: This function must not permanently modify registers R4 to R11
; Lab 7 requirement is for at least one local variable on the stack with symbolic binding
LCD_OutFix
dec0    EQU 0
int 	EQU 4
dec1	EQU 8
Link	EQU 12
		ADD SP, SP, #16
		MOV R11, SP
		STR LR, [R11,#Link]
		
		LDR R1, =999
		CMP R0, R1
		BHI overflow
		
		MOV R1, #10
		PUSH {R0, R1}
		BL MOD
		STR R0, [R11, #dec0]
		POP {R0, R1}
		PUSH {R0, R1}
		UDIV R0, R0, R1
		BL MOD
		STR R0, [R11, #dec1]
		POP {R0, R1}
		MOV R1, #100
		UDIV R0, R0, R1
		STR R0, [R11, #int]
		
		LDR R0, [R11, #int]
		BL LCD_OutDec
		MOV R0, #'.'
		BL ST7735_OutChar
		LDR R0, [R11, #dec1]
		BL LCD_OutDec
		LDR R0, [R11, #dec0]
		BL LCD_OutDec
		
		B done
overflow
		MOV R0, #'*'
		BL ST7735_OutChar
		MOV R0, #'.'
		BL ST7735_OutChar
		MOV R0, #'*'
		BL ST7735_OutChar
		MOV R0, #'*'
		BL ST7735_OutChar
		
done	LDR LR, [R11, #Link]
		SUB SP, SP, #16

		BX   LR
		
MOD
	UDIV R2, R0, R1
	MUL R2, R2, R1
	SUB R0, R0, R2
	BX LR
 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN          ; make sure the end of this section is aligned
     END            ; end of file
