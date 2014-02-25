/*
 * weatherDate.cpp
 *
 *  Created on: 24 févr. 2014
 *      Author: bede6362
 */
#include <weatherTime.h>

time::time() {
	setValue(0, 0, 0);
}
time::time(String value) {
	setValue(value);
}
time::time(uint8_t vHour, uint8_t vMinute, uint8_t vSecond) {
	setValue(vHour, vMinute, vSecond);
}
void time::setValue(String value) {
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
	setHour(int(val1));
	setMinute(int(val2));
	setSecond(int(val3));
}
void time::setValue(uint8_t vHour, uint8_t vMinute, uint8_t vSecond) {
	setHour(vHour);
	setMinute(vMinute);
	setSecond(vSecond);
}
String time::getValue() {
	return String(getHour()) + ":" + String(getMinute()) + ":" + String(getSecond());
}
void time::setHour(uint8_t value) {
	lHour = value;
}
uint8_t time::getHour() {
	return lHour;
}
void time::setMinute(uint8_t value) {
	lMinute = value;
}
uint8_t time::getMinute() {
	return lMinute;
}
void time::setSecond(uint8_t value) {
	lSecond = value;
}
uint8_t time::getSecond() {
	return lSecond;
}
