// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _weatherDate_H_
#define _weatherDate_H_

#include <Arduino.h>
#include <DS1307.h>

#define SHORTDATE 0
#define LONGDATE 1
#define FULLDATE 2

//add your function definitions for the project weatherDatas here
class date {
private:
	uint16_t lYear;
	uint8_t lMonth;
	uint8_t lDay;

	//activation de l'horloge
	DS1307 clock;

	uint16_t mod(uint16_t value, uint16_t divider);

public:
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
	String getMonthStr(int format);

	void setDay(uint8_t value);
	uint8_t getDay();
	uint8_t getDayOfWeek();
	String getDayOfWeekStr(int format);
};

#endif /* weatherDate_H_ */
