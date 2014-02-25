// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _weatherString_H_
#define _weatherString_H_
#include "Arduino.h"
//add your includes for the project weatherString here


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project weatherString here
String formatValue(float value, int intMask = 1, int decMask = 0, bool sigMask = false);
String substr(String string, int start, int length);
String substr(String string, int start);
int strpos(String string, String needle, int offset);
int strpos(String string, String needle);
int strrpos(String string, String needle, int offset);
int strrpos(String string, String needle);

//Do not add code below this line
#endif /* _weatherString_H_ */
