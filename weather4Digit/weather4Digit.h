// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _WEATHER4DIGIT_H_
#define _WEATHER4DIGIT_H_
#include "Arduino.h"
//add your includes for the project Weather here

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project Weather here
void storeData();
void getData();
void displayDate();
void displayTimeDigit();
void displayTimeLCD();
void displayInformation();

//Do not add code below this line
#endif /* _WEATHER4DIGIT_H_ */
