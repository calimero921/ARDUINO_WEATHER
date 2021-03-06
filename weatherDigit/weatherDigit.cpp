// Do not remove the include below
#include <weatherDigit.h>
#include <weatherSensors.h>
#include <weatherDate.h>
#include <weatherTime.h>

#include <TimerOne.h>
#include <DS1307.h>
#include <GD2.h>

#include <Barometer.h>
#include <DHT.h>

#include <EEPROM.h>
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>

//formats de date
#define DATE_LONG 0
#define DATE_COURT 1

//choix des �cran
#define MAINSCREEN 0
#define SETTINGS   1

//variables globales
int nbData = 4;

weatherSensors sensors;

//gestion de l'horloge
DS1307 clock;
date lDate;
time lTime;

//gestion de l'�cran
int displayAction;

//The setup function is called once at startup of the sketch
void setup() {
	GD.begin();
	GD.ClearColorRGB(0x000000);
	GD.Clear();
	GD.cmd_text(0, 0, 26, 0, "Wheather init");
	GD.swap();
	Serial.begin(9600);
	//delay(500);

	GD.Clear();
	GD.cmd_text(0, 0, 26, 0, "Clock init");
	GD.swap();
	clock.begin();
	//delay(500);

	//GD.Clear();
	//GD.cmd_text(0, 0, 26, 0, "Timer init");
	//GD.swap();
	//Timer1.initialize(500000);                  //activation du timer pour une interruption chaque seconde
	//Timer1.attachInterrupt(getData);            //appel getData � chaque interruption
  	//delay(500);

	GD.Clear();
  	GD.cmd_text(0, 0, 26, 0, "Wheather ready");
	GD.swap();
	//delay(500);

	displayAction = MAINSCREEN;
}

// The loop function is called in an endless loop
void loop()
{
	//horloge
	GD.ClearColorRGB(0x103000);
	GD.Clear();

	storeData();

	switch (displayAction) {
		case SETTINGS:

			break;
		case MAINSCREEN:
		default:
	    	displayInformation();
			break;
	}

	//affiche l'�cran compos�
	GD.swap();
    delay(500);
}

void storeData() {
	//clock.getTime();
	Serial.print(getDate(DATE_COURT));
	Serial.print(lDate.getNow(SHORTDATE));
	Serial.print(";");
	Serial.print(lTime.getNow(SHORTTIME));
	Serial.print(";");
	Serial.print(sensors.getPressureStr());
	Serial.print(";");
	Serial.print(sensors.getAtmosphereStr());
	Serial.print(";");
	Serial.print(sensors.getAltitudeStr());
	Serial.print(";");
	Serial.print(sensors.getTemperatureStr());
	Serial.print(";");
	Serial.print(sensors.getHumidityStr());
	Serial.println(";");
}
void displayInformation() {
	String result = "";
	int unite;
	int decim;

	//date
	GD.cmd_text(0, 0, 30, 0, lDate.getNow(LONGDATE).c_str());
	//heure
	GD.cmd_text(0, 35, 28, 0, lTime.getNow(LONGTIME).c_str());

	//pression
	result = "pres " + sensors.getPressureStr() + "HPa";
	GD.cmd_text(0, 70, 26, 0, result.c_str());

	//altitude
	result = "alti " + sensors.getAltitudeStr() + "M";
	GD.cmd_text(0, 90, 26, 0, result.c_str());

	//temp�rature
	result = "temp " + sensors.getTemperatureStr() + "C";
	GD.cmd_text(0, 110, 26, 0, result.c_str());

	//humidit�
	result = "humi " + sensors.getHumidityStr() + "%";
	GD.cmd_text(0, 130, 26, 0, result.c_str());
}
