// Random number generator;
// Linear congruential generator 
// from Numerical Recipes by Press et al.
// Jonathan Valvano 1/17/2020

// How to use: 
// 1) call Random_Init once with a seed
//     Random_Init(1);
// or    Random_Init(NVIC_CURRENT_R);
// 2) call Random over and over to get a new random number
//   n = Random();    // 8 bit number
//   m = (Random32()>>24)%60; // a number from 0 to 59
#include <stdint.h>
      

// initialize random number generator
// the generator cycles through all 32-bit values, seed is the place to start
// input: any 32-bit number
// output: none
void Random_Init(uint32_t seed);

//------------Random32------------
// Return 32-bit random number
// Linear congruential generator 
// from Numerical Recipes by Press et al.
// Input: none
// Output: random number
// warning: the bottom bits are not that randome
//          bit 0 oscillates 0,1,0,1,...
//          bit n cycles through a sequence of length n+1
uint32_t Random32(void);

//------------Random------------
// Return random number, 0 to 255
// Linear congruential generator 
// from Numerical Recipes by Press et al.
// Input: none
// Output: random number
uint8_t Random (void);
