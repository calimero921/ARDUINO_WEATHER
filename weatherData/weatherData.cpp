// Do not remove the include below
#include "weatherData.h"
#include "weatherDate.h"
#include "weatherTime.h"

weatherData::weatherData() {
	setPressure(0);
	setIntTemperature(0);
	setIntHumidity(0);
	setExtTemperature(0);
	setExtHumidity(0);
}
weatherData::weatherData(String value) {
	setValue(value);
}
weatherData::weatherData(String vDate, String vTime, uint16_t vPressure, float vIntTemp, float vIntHumi, float vExtTemp, float vExtHumi) {
	setDate(vDate);
	setTime(vTime);
	setPressure(vPressure);
	setIntTemperature(vIntTemp);
	setIntHumidity(vIntHumi);
	setExtTemperature(vExtTemp);
	setExtHumidity(vExtHumi);
}

void  weatherData::setValue(String value) {
	uint8_t str = 0;
	uint8_t end = 0;
	uint8_t pos = 0;
	String dec;

	end = value.indexOf(sep, str);
	while (end > 0) {
		dec = value.substring(str, end);
		switch (pos) {
			case 0:
				setDate(dec);
				break;
			case 1:
				setTime(dec);
			case 2:
				setPressure(int(dec));
			case 3:
				setIntTemperature(float(dec));
			case 4:
				setIntHumidity(float(dec));
			case 5:
				setExtTemperature(float(dec));
			case 6:
				setExtHumidity(float(dec));
			default:
				break;
		}
		pos++;
		str = end++;
		if (str > value.length()) {end = 0;} else {end = value.indexOf(sep, str);}
	}
}
String weatherData::getValue() {
	String result = "";

	result += getDate() + sep;
	result += getTime() + sep;
	result += String(lPressure) + sep;
	result += String(lIntTemp) + sep;
	result += String(lIntHumi) + sep;
	result += String(lExtTemp) + sep;
	result += String(lExtHumi) + sep;
	return result;
}

void weatherData::setDate(String value) {
	lDate.setValue(value);
}
String weatherData::getDate() {
	return lDate.getValue(SHORTDATE);
}


void weatherData::setTime(String value) {
	lTime.setValue(value);
}
String weatherData::getTime(){
	return lTime.getValue(SHORTTIME);
}

void weatherData::setPressure(uint16_t value) {
	lPressure = value;
}
uint16_t weatherData::getPressure() {
	return lPressure;
}

void weatherData::setIntTemperature(float value) {
	lIntTemp = value;
}
float weatherData::getIntTemperature() {
	return lIntTemp;
}

void weatherData::setIntHumidity(float value) {
	lIntHumi = value;
}
float weatherData::getExtHumidity() {
	return lIntHumi;
}

void weatherData::setExtTemperature(float value) {
	lExtTemp = value;
}
float weatherData::getIntTemperature() {
	return lExtTemp;
}

void weatherData::setExtHumidity(float value) {
	lExtHumi = value;
}
float weatherData::getExtHumidity() {
	return lExtHumi;
}
