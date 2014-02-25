// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _weatherDate_H_
#define _weatherDate_H_
#include "Arduino.h"
//add your includes for the project weatherDatas here


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project weatherDatas here
class date {
public:
	date();
	date(String value);
	date(uint8_t vDay, uint8_t vMonth, uint16_t vYear);
	void setValue(String value);
	void setValue(uint8_t vDay, uint8_t vMonth, uint16_t vYear);
	String getValue();
	void setYear(uint16_t value);
	uint16_t getYear();
	void setMonth(uint8_t value);
	uint8_t getMonth();
	void setDay(uint8_t value);
	uint8_t getDay();

private:
	uint16_t lYear;
	uint8_t lMonth;
	uint8_t lDay;
};

#endif /* weatherDate_H_ */
