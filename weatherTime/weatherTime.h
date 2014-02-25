// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _weatherTime_H_
#define _weatherTime_H_
#include "Arduino.h"
//add your includes for the project weatherDatas here
#include <DS1307.h>

//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
} // extern "C"
#endif

#define SHORTTIME 0
#define LONGTIME 1

//add your function definitions for the project weatherDatas here
class time {
public:
	time();
	time(String value);
	time(uint8_t vHour, uint8_t vMinute, uint8_t vSecond);
	void setValue(String value);
	void setValue(uint8_t vHour, uint8_t vMinute, uint8_t vSecond);
	String getValue(int format);
	String getNow(int format);
	void setHour(uint8_t value);
	uint8_t getHour();
	void setMinute(uint8_t value);
	uint8_t getMinute();
	void setSecond(uint8_t value);
	uint8_t getSecond();

private:
	uint8_t lHour;
	uint8_t lMinute;
	uint8_t lSecond;

	//activation de l'horloge
	DS1307 clock;
};

#endif /* weatherTime_H_ */
