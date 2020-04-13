#include <stdint.h>
#include "song.h" 
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "dac.h"

uint16_t midiReadHalfWord(int* i);
uint32_t midiReadWord(int* i); 
uint32_t readDelta(int* i);

int midiIndex = 0;

int midiInit() {
	
	midiIndex += 4; //skip over header identifier
	midiIndex += 4; //skip over header chunk length
	
	int format = midiReadHalfWord(&midiIndex);
	if (format != 1)
		return 1; //invalid file exception
	
	int chunkCount = midiReadHalfWord(&midiIndex);
	
	int tickdiv = midiReadHalfWord(&midiIndex);
	if ( ~(tickdiv & 0x80))
		return 2; //invalid timing exception
	tickdiv &= 0x7F;
	
	midiIndex += 4; //skip over info track chunk type
	
	int firstChunkLen = midiReadWord(&midiIndex); 
	int firstDelta = readDelta(&midiIndex); 
	
	//decided this reader isn't worth finishing. 
	//Would continue using a timer, and interrupt to read a chunk
	//use chunk data to find reload value, and repeat
	//more interrupts to enable/disable playback (button interface)
	//pickup here when you decide this project is worth it again
	
	return 0; 
}

uint16_t midiReadHalfWord(int* i) {
	return (song[(*i)++] << 8) + song[(*i)++];
}

uint32_t midiReadWord(int* i) {
	return (song[(*i)++] << 24) + (song[(*i)++] << 16) + (song[(*i)++] << 8) + song[(*i)++];
}

uint32_t readDelta(int* i) {
	int contin = 0;
	int data = 0; 
	
	do {
		contin = song[*i] & 0x80; //check if this is final byte to read
		data = data << 7;	//make room for new read
		data |= song[(*i)++] & 0x7F;
	} while (contin);
	
	return data; 
}
