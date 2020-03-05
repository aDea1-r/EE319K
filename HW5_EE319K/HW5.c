// This HW5
// Jonathan Valvano
// Spring 2020 EE319K
// You will implement the mode function
#include <stdint.h>
#include <string.h>
char myEID[]="aur228"; // edit this line with your student EID
char Semester[]="Spring 2020";


char mode(const char string[30]){ 
// write this function
	int count[26];
	for (int i=0; i<26; i++) {
		count[i] = 0; 
	}
  for (int i=0; i < 30; i++) {
		count[ string[i] - 97] ++; 
	}
	int maxIndex = 0;
	for (int i=1; i<26; i++) {
		if (count[i] > count[maxIndex])
			maxIndex = i;
	}
	return maxIndex + 97; 
}




