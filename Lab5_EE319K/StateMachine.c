// StateMachine.c
// Runs on TM4C123
// Finite state machine to operate a stepper motor.  
// Adeel Rehman and Zach B
// 3/7/2020

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "StateMachine.h"

//state inputs: take state[x].output[q][w], where q is wiper button, and w is clean button

struct State* DefineStates(void) {
	struct State *states = (struct State*) malloc(numStates * sizeof(struct State) );
		
	//state: washerOff, counting Inflection, cycle 1, currentStep 1
        states[0].motorOutput = 1;
        states[0].pumpOutput = 0;
        states[0].delay = state_delay;
        states[0].output[0][0] = &states[0];
        states[0].output[0][1] = &states[19];
        states[0].output[1][0] = &states[1];
        states[0].output[1][1] = &states[19];

        //state: washerOff, counting Up, cycle 1, currentStep 2
        states[1].motorOutput = 2;
        states[1].pumpOutput = 0;
        states[1].delay = state_delay;
        states[1].output[0][0] = &states[17];
        states[1].output[0][1] = &states[20];
        states[1].output[1][0] = &states[2];
        states[1].output[1][1] = &states[20];

        //state: washerOff, counting Up, cycle 1, currentStep 4
        states[2].motorOutput = 4;
        states[2].pumpOutput = 0;
        states[2].delay = state_delay;
        states[2].output[0][0] = &states[16];
        states[2].output[0][1] = &states[21];
        states[2].output[1][0] = &states[3];
        states[2].output[1][1] = &states[21];

        //state: washerOff, counting Up, cycle 1, currentStep 8
        states[3].motorOutput = 8;
        states[3].pumpOutput = 0;
        states[3].delay = state_delay;
        states[3].output[0][0] = &states[15];
        states[3].output[0][1] = &states[22];
        states[3].output[1][0] = &states[4];
        states[3].output[1][1] = &states[22];

        //state: washerOff, counting Up, cycle 1, currentStep 16
        states[4].motorOutput = 16;
        states[4].pumpOutput = 0;
        states[4].delay = state_delay;
        states[4].output[0][0] = &states[14];
        states[4].output[0][1] = &states[23];
        states[4].output[1][0] = &states[5];
        states[4].output[1][1] = &states[23];

        //state: washerOff, counting Up, cycle 2, currentStep 1
        states[5].motorOutput = 1;
        states[5].pumpOutput = 0;
        states[5].delay = state_delay;
        states[5].output[0][0] = &states[13];
        states[5].output[0][1] = &states[24];
        states[5].output[1][0] = &states[6];
        states[5].output[1][1] = &states[24];

        //state: washerOff, counting Up, cycle 2, currentStep 2
        states[6].motorOutput = 2;
        states[6].pumpOutput = 0;
        states[6].delay = state_delay;
        states[6].output[0][0] = &states[12];
        states[6].output[0][1] = &states[25];
        states[6].output[1][0] = &states[7];
        states[6].output[1][1] = &states[25];

        //state: washerOff, counting Up, cycle 2, currentStep 4
        states[7].motorOutput = 4;
        states[7].pumpOutput = 0;
        states[7].delay = state_delay;
        states[7].output[0][0] = &states[11];
        states[7].output[0][1] = &states[26];
        states[7].output[1][0] = &states[8];
        states[7].output[1][1] = &states[26];

        //state: washerOff, counting Up, cycle 2, currentStep 8
        states[8].motorOutput = 8;
        states[8].pumpOutput = 0;
        states[8].delay = state_delay;
        states[8].output[0][0] = &states[10];
        states[8].output[0][1] = &states[27];
        states[8].output[1][0] = &states[9];
        states[8].output[1][1] = &states[27];

        //state: washerOff, counting Inflection, cycle 2, currentStep 16
        states[9].motorOutput = 16;
        states[9].pumpOutput = 0;
        states[9].delay = state_delay;
        states[9].output[0][0] = &states[10];
        states[9].output[0][1] = &states[28];
        states[9].output[1][0] = &states[10];
        states[9].output[1][1] = &states[28];

        //state: washerOff, counting Down, cycle 3, currentStep 8
        states[10].motorOutput = 8;
        states[10].pumpOutput = 0;
        states[10].delay = state_delay;
        states[10].output[0][0] = &states[11];
        states[10].output[0][1] = &states[29];
        states[10].output[1][0] = &states[11];
        states[10].output[1][1] = &states[29];

        //state: washerOff, counting Down, cycle 3, currentStep 4
        states[11].motorOutput = 4;
        states[11].pumpOutput = 0;
        states[11].delay = state_delay;
        states[11].output[0][0] = &states[12];
        states[11].output[0][1] = &states[30];
        states[11].output[1][0] = &states[12];
        states[11].output[1][1] = &states[30];

        //state: washerOff, counting Down, cycle 3, currentStep 2
        states[12].motorOutput = 2;
        states[12].pumpOutput = 0;
        states[12].delay = state_delay;
        states[12].output[0][0] = &states[13];
        states[12].output[0][1] = &states[31];
        states[12].output[1][0] = &states[13];
        states[12].output[1][1] = &states[31];

        //state: washerOff, counting Down, cycle 3, currentStep 1
        states[13].motorOutput = 1;
        states[13].pumpOutput = 0;
        states[13].delay = state_delay;
        states[13].output[0][0] = &states[14];
        states[13].output[0][1] = &states[32];
        states[13].output[1][0] = &states[14];
        states[13].output[1][1] = &states[32];

        //state: washerOff, counting Down, cycle 3, currentStep 16
        states[14].motorOutput = 16;
        states[14].pumpOutput = 0;
        states[14].delay = state_delay;
        states[14].output[0][0] = &states[15];
        states[14].output[0][1] = &states[33];
        states[14].output[1][0] = &states[15];
        states[14].output[1][1] = &states[33];

        //state: washerOff, counting Down, cycle 4, currentStep 8
        states[15].motorOutput = 8;
        states[15].pumpOutput = 0;
        states[15].delay = state_delay;
        states[15].output[0][0] = &states[16];
        states[15].output[0][1] = &states[34];
        states[15].output[1][0] = &states[16];
        states[15].output[1][1] = &states[34];

        //state: washerOff, counting Down, cycle 4, currentStep 4
        states[16].motorOutput = 4;
        states[16].pumpOutput = 0;
        states[16].delay = state_delay;
        states[16].output[0][0] = &states[17];
        states[16].output[0][1] = &states[35];
        states[16].output[1][0] = &states[17];
        states[16].output[1][1] = &states[35];

        //state: washerOff, counting Down, cycle 4, currentStep 2
        states[17].motorOutput = 2;
        states[17].pumpOutput = 0;
        states[17].delay = state_delay;
        states[17].output[0][0] = &states[0];
        states[17].output[0][1] = &states[18];
        states[17].output[1][0] = &states[0];
        states[17].output[1][1] = &states[18];

        //state: washerOn, counting Up, cycle 1, currentStep 1
        states[18].motorOutput = 1;
        states[18].pumpOutput = 0;
        states[18].delay = state_delay;
        states[18].output[0][0] = &states[0];
        states[18].output[0][1] = &states[19];
        states[18].output[1][0] = &states[1];
        states[18].output[1][1] = &states[19];

        //state: washerOn, counting Up, cycle 1, currentStep 2
        states[19].motorOutput = 2;
        states[19].pumpOutput = 1;
        states[19].delay = state_delay;
        states[19].output[0][0] = &states[16];
        states[19].output[0][1] = &states[20];
        states[19].output[1][0] = &states[2];
        states[19].output[1][1] = &states[20];

        //state: washerOn, counting Up, cycle 1, currentStep 4
        states[20].motorOutput = 4;
        states[20].pumpOutput = 0;
        states[20].delay = state_delay;
        states[20].output[0][0] = &states[15];
        states[20].output[0][1] = &states[21];
        states[20].output[1][0] = &states[3];
        states[20].output[1][1] = &states[21];

        //state: washerOn, counting Up, cycle 1, currentStep 8
        states[21].motorOutput = 8;
        states[21].pumpOutput = 1;
        states[21].delay = state_delay;
        states[21].output[0][0] = &states[14];
        states[21].output[0][1] = &states[22];
        states[21].output[1][0] = &states[4];
        states[21].output[1][1] = &states[22];

        //state: washerOn, counting Up, cycle 1, currentStep 16
        states[22].motorOutput = 16;
        states[22].pumpOutput = 0;
        states[22].delay = state_delay;
        states[22].output[0][0] = &states[13];
        states[22].output[0][1] = &states[23];
        states[22].output[1][0] = &states[5];
        states[22].output[1][1] = &states[23];

        //state: washerOn, counting Up, cycle 2, currentStep 1
        states[23].motorOutput = 1;
        states[23].pumpOutput = 1;
        states[23].delay = state_delay;
        states[23].output[0][0] = &states[12];
        states[23].output[0][1] = &states[24];
        states[23].output[1][0] = &states[6];
        states[23].output[1][1] = &states[24];

        //state: washerOn, counting Up, cycle 2, currentStep 2
        states[24].motorOutput = 2;
        states[24].pumpOutput = 0;
        states[24].delay = state_delay;
        states[24].output[0][0] = &states[11];
        states[24].output[0][1] = &states[25];
        states[24].output[1][0] = &states[7];
        states[24].output[1][1] = &states[25];

        //state: washerOn, counting Up, cycle 2, currentStep 4
        states[25].motorOutput = 4;
        states[25].pumpOutput = 1;
        states[25].delay = state_delay;
        states[25].output[0][0] = &states[10];
        states[25].output[0][1] = &states[26];
        states[25].output[1][0] = &states[8];
        states[25].output[1][1] = &states[26];

        //state: washerOn, counting Up, cycle 2, currentStep 8
        states[26].motorOutput = 8;
        states[26].pumpOutput = 0;
        states[26].delay = state_delay;
        states[26].output[0][0] = &states[9];
        states[26].output[0][1] = &states[27];
        states[26].output[1][0] = &states[9];
        states[26].output[1][1] = &states[27];

        //state: washerOn, counting Inflection, cycle 2, currentStep 16
        states[27].motorOutput = 16;
        states[27].pumpOutput = 1;
        states[27].delay = state_delay;
        states[27].output[0][0] = &states[10];
        states[27].output[0][1] = &states[28];
        states[27].output[1][0] = &states[10];
        states[27].output[1][1] = &states[28];

        //state: washerOn, counting Down, cycle 3, currentStep 8
        states[28].motorOutput = 8;
        states[28].pumpOutput = 0;
        states[28].delay = state_delay;
        states[28].output[0][0] = &states[11];
        states[28].output[0][1] = &states[29];
        states[28].output[1][0] = &states[11];
        states[28].output[1][1] = &states[29];

        //state: washerOn, counting Down, cycle 3, currentStep 4
        states[29].motorOutput = 4;
        states[29].pumpOutput = 1;
        states[29].delay = state_delay;
        states[29].output[0][0] = &states[12];
        states[29].output[0][1] = &states[30];
        states[29].output[1][0] = &states[12];
        states[29].output[1][1] = &states[30];

        //state: washerOn, counting Down, cycle 3, currentStep 2
        states[30].motorOutput = 2;
        states[30].pumpOutput = 0;
        states[30].delay = state_delay;
        states[30].output[0][0] = &states[13];
        states[30].output[0][1] = &states[31];
        states[30].output[1][0] = &states[13];
        states[30].output[1][1] = &states[31];

        //state: washerOn, counting Down, cycle 3, currentStep 1
        states[31].motorOutput = 1;
        states[31].pumpOutput = 1;
        states[31].delay = state_delay;
        states[31].output[0][0] = &states[14];
        states[31].output[0][1] = &states[32];
        states[31].output[1][0] = &states[14];
        states[31].output[1][1] = &states[32];

        //state: washerOn, counting Down, cycle 3, currentStep 16
        states[32].motorOutput = 16;
        states[32].pumpOutput = 0;
        states[32].delay = state_delay;
        states[32].output[0][0] = &states[15];
        states[32].output[0][1] = &states[33];
        states[32].output[1][0] = &states[15];
        states[32].output[1][1] = &states[33];

        //state: washerOn, counting Down, cycle 4, currentStep 8
        states[33].motorOutput = 8;
        states[33].pumpOutput = 1;
        states[33].delay = state_delay;
        states[33].output[0][0] = &states[16];
        states[33].output[0][1] = &states[34];
        states[33].output[1][0] = &states[16];
        states[33].output[1][1] = &states[34];

        //state: washerOn, counting Down, cycle 4, currentStep 4
        states[34].motorOutput = 4;
        states[34].pumpOutput = 0;
        states[34].delay = state_delay;
        states[34].output[0][0] = &states[17];
        states[34].output[0][1] = &states[35];
        states[34].output[1][0] = &states[17];
        states[34].output[1][1] = &states[35];

        //state: washerOn, counting Down, cycle 4, currentStep 2
        states[35].motorOutput = 2;
        states[35].pumpOutput = 1;
        states[35].delay = state_delay;
        states[35].output[0][0] = &states[0];
        states[35].output[0][1] = &states[18];
        states[35].output[1][0] = &states[0];
        states[35].output[1][1] = &states[18];
	
	return states;
}
