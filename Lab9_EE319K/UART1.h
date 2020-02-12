// UART1.h
// Runs on LM4F120/TM4C123
// Provides Prototypes for functions implemented in UART1.c
// Last Modified: 1/17/2020 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

// This U0Rx PC4 (in) is connected to other LaunchPad PC5 (out)
// This U0Tx PC5 (out) is connected to other LaunchPad PC4 (in)
// This ground is connected to other LaunchPad ground

// UART1 initialization function 
// Input: none
// Output: none
void UART1_Init(void);

//------------UART1_InChar------------
// Wait for new input,
// then return ASCII code
// Input: none
// Output: char read from UART
// Receiver is interrupt driven
char UART1_InChar(void);

//------------UART1_InMessage------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until ETX is typed
//    or until max length of the string is reached.
// Input: pointer to empty buffer of 8 characters
// Output: Null terminated string
// THIS FUNCTION IS OPTIONAL
void UART1_InMessage(char *bufPt);

//------------UART_OutChar------------
// Wait for new input,
// then return ASCII code
// Input: none
// Output: char read from UART
// Transmitter is busywait
void UART1_OutChar(char data);
