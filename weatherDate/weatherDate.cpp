/*
 * weatherDate.cpp
 *
 *  Created on: 24 févr. 2014
 *      Author: bede6362
 */
#include <weatherdate.h>

date::date() {
	setValue(0, 0, 0);
}
date::date(String value) {
	setValue(value);
}
date::date(uint8_t vDay, uint8_t vMonth, uint16_t vYear) {
	setValue(vDay, vMonth, vYear);
}
void date::setValue(String value) {
	char sep = "/";
	String val1;
	String val2;
	String val3;
	uint16_t sep1;
	uint16_t sep2;

	sep1 = value.indexOf(sep);
	sep2 = value.lastIndexOf(sep);
	val1 = value.substring(0, sep1);
	val1 = value.substring(sep1, sep2);
	val1 = value.substring(sep2);
	if (val1.length()<4) {setDay(int(val1));} else {setYear(int(val1));}
	setMonth(int(val2));
	if (val3.length()<4) {setDay(int(val3));} else {setYear(int(val3));}
}
void date::setValue(uint8_t vDay, uint8_t vMonth, uint16_t vYear) {
	setYear(vYear);
	setMonth(vMonth);
	setDay(vDay);
}
String date::getValue(int format) {
	String result;
	switch (format) {
		case LONGDATE:
		case FULLDATE:
			result = getDayStr(format) + " " + String(getDay()) + " " + getMonthStr(format) + " " + String(getYear());
			break;
		case SHORTDATE:
		default:
			result = String(getDay()) + "/" + String(getMonth()) + "/" + String(getYear());
			break;
	}
	return result;
}
String date::getNow(int format) {
	clock.getTime();
	setDay(clock.dayOfMonth);
	setMonth(clock.month);
	setYear(clock.year);
	return getValue(format);
}
void date::setYear(uint16_t value) {
	lYear = value;
}
uint16_t date::getYear() {
	return lYear;
}
void date::setMonth(uint8_t value) {
	lMonth = value;
}
uint8_t date::getMonth() {
	return lMonth;
}
void date::setDay(uint8_t value) {
	lDay = value;
}
uint8_t date::getDay() {
	return lDay;
}

String date::getDayStr(int format) {
	String result;
	char* ShortDays[]={"---","Lun","Mar","Mer","Jeu","Ven","Sam","Dim"};
	char* LongDays[]={"---","Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samdi","Dimanche"};

	int dayOfWeek = mod ((uint16_t) (getDay() + getYear() + int(getYear()/4) - int(getYear()/100) + int(getYear()/400) + int((31*getMonth())/12)),7);

	//date
	switch (format) {
		case FULLDATE:
			result = String(LongDays[dayOfWeek]);
			break;
		case LONGDATE:
		default:
			result = String(ShortDays[dayOfWeek]);
			break;
	}
	return result;
}
String date::getMonthStr(int format) {
	String result;
	char* ShortMonths[]={"---","Jan","Fév","Mar","Avr","Mai","Jun","Jui","Aou","Sep","Oct","Nov","Dec"};
	char* LongMonths[]={"---","Janvier","Février","Mars","Avril","Mai","Juin","Juillet","Aout","Septembre","Octobre","Novembre","Decembre"};

	//date
	switch (format) {
		case FULLDATE:
			result = String(LongMonths[getMonth()]);
			break;
		case LONGDATE:
		default:
			result = String(ShortMonths[getMonth()]);
			break;
	}
	return result;
}
uint16_t mod(uint16_t value, uint16_t divider) {
	uint16_t result;
	uint16_t divide;

	divide = int(value/divider);
	result = value - (divide * divider);
	return result;
}
