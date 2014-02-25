// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _weatherDate_H_
#define _weatherDate_H_

//#define SHORTDATE 0
//#define LONGDATE 1
//#define FULLDATE 2

#include <Arduino.h>
#include <DS1307.h>

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
} // extern "C"
#endif

//add your function definitions for the project weatherDatas here
class date {
public:
	const int SHORTDATE = 0;
	const int LONGDATE = 1;
	const int FULLDATE = 2;

	date();
	date(String value);
	date(uint8_t vDay, uint8_t vMonth, uint16_t vYear);
	void setValue(String value);
	void setValue(uint8_t vDay, uint8_t vMonth, uint16_t vYear);
	String getValue(int format);
	String getNow(int format);
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

	//activation de l'horloge
	DS1307 clock;

	String getDayStr(int format);
	String getMonthStr(int format);
	uint16_t mod(uint16_t value, uint16_t divider);
};

#endif /* weatherDate_H_ */
