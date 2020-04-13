// StateMachine.h
// Runs on TM4C123
// Provide functions and structs for state machine
// Adeel Rehman and Zach B
// 3/7/2020

#define numStates 36
#define state_delay 100

#include <stdint.h>
#include <stdbool.h>

struct State {
	//outputs
	uint8_t motorOutput;
	bool pumpOutput;
	
	//delay
	uint32_t delay;
	
	//next state
	struct State *output[2][2];
	//state inputs: take state[x].output[q][w], where q is wiper button, and w is clean/wash button
};



//returns array containing all possible states
struct State* DefineStates(void);
