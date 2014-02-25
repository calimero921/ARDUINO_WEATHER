// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _weatherLCD_H_
#define _weatherLCD_H_
#include "Arduino.h"
#include "weatherSensors.h"
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
void displayDate();
String getTime();
String getDate(int ln);
void displayInformation();

//Do not add code below this line
#endif /* _weatherLCD_H_ */
