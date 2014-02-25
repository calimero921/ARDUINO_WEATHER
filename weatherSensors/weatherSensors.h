// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _weatherSensors_H_
#define _weatherSensors_H_

//add your includes for the project weatherDatas here
#include <Arduino.h>
#include <Wire.h>
#include <Barometer.h>
#include <DHT.h>


//end of add your includes here
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
} // extern "C"
#endif

//définitions
#define DHTPIN A0     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

Barometer Baro;
DHT dht(DHTPIN, DHTTYPE);

//add your function definitions for the project weatherDatas here
class weatherSensors {
public:
	weatherSensors();

	float getAltitudeNum();
	String getAltitudeStr();
	float getAtmosphereNum();
	String getAtmosphereStr();
	float getHumidityNum();
	String getHumidityStr();
	float getPressureNum();
	String getPressureStr();
	float getTemperatureNum();
	String getTemperatureStr();

private :
	String formatValue(float value, int intMask = 1, int decMask = 0, bool sigMask = false);
};

#endif /* weatherSensors_H_ */
