// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _weatherData_H_
#define _weatherData_H_
#include "Arduino.h"
//add your includes for the project weatherDatas here
#include "weatherDate.h"
#include "weatherTime.h"
//end of add your includes here

//add your function definitions for the project weatherDatas here
class weatherData {
public:
	weatherData();
	weatherData(String value);
	weatherData(String vDate, String vTime, uint16_t vPressure, float vIntTemp, float vIntHumi, float vExtTemp, float vExtHumi);

	void  setValue(String value);
	String getValue();

	void setDate(String value);
	String getDate();

	void setTime(String value);
	String getTime();

	void setPressure(uint16_t value);
	uint16_t getPressure();

	void setIntTemperature(float value);
	float getIntTemperature();

	void setIntHumidity(float value);
	float getExtHumidity();

	void setExtTemperature(float value);
	float getIntTemperature();

	void setExtHumidity(float value);
	float getExtHumidity();

private:
	const char sep = ";";
	date lDate;
	time lTime;
	uint16_t lPressure;
	float lIntTemp;
	float lIntHumi;
	float lExtTemp;
	float lExtHumi;
};
//Do not add code below this line
#endif /* _weatherData_H_ */
