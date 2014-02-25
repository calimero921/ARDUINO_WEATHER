/*
 * weatherSensors.cpp
 *
 *  Created on: 21 f�vr. 2014
 *      Author: bede6362
 */

#include <weatherSensors.h>
#include <Arduino.h>
#include <Wire.h>

weatherSensors::weatherSensors() {
	//initialisation des communication num�riques
	Serial.begin(9600);
	//activation du barometre
	Baro.init();
	//activation du thermometre
	dht.begin();
}

float weatherSensors::getAltitudeNum() {
	//r�cup�re l'altitude sous forme num�rique
	float result;

	result = Baro.calcAltitude(getPressureNum());
	return result;
}
String weatherSensors::getAltitudeStr() {
	//r�cup�re l'altitude sous forme de chaine
	String result;
	float value;

	value = getAltitudeNum()();
	//r�duction � 0 chiffre apr�s la virgule
	result = String(round(value));
	//ajoute un espace de formatage pour les mesures inf�rieures � 10
	if (value<10) {result += " ";};
	//ajoute un espace de formatage pour les mesures inf�rieures � 100
	if (value<100) {result += " ";};
	//ajoute un espace de formatage pour les mesures inf�rieures � 1000
	if (value<1000) {result += " ";};
	return result;
}
float weatherSensors::getAtmosphereNum() {
	//r�cup�re l'atmosphere sous forme num�rique
	float result;

	result = getPressureNum()/101325;
	return result;
}
String weatherSensors::getAtmosphereStr() {
	//r�cup�re l'atmosphere sous forme de chaine
	String result;
	float value;

	value = getAtmosphereNum()();
	//r�duction � 3 chiffres apr�s la virgule
	result = String(round(value*1000)/1000);
	//ajoute un espace de formatage pour les mesures inf�rieures � 10
	if (value<10) {result += " ";};
	return result;
}
float weatherSensors::getHumidityNum() {
	//r�cup�re l'humidit� sous forme num�rique
	float result;

	result = dht.readHumidity();
	return result;
}
String weatherSensors::getHumidityStr() {
	//r�cup�re l'humidit� sous forme de chaine
	String result;
	float value;

	value = getHumidityNum()();
	//r�duction � 1 chiffre apr�s la virgule
	result = String(round(value*10)/10);
	//ajoute un espace de formatage pour les mesures inf�rieures � 10
	if (value<10) {result += " ";};
	return result;
}
float weatherSensors::getPressureNum() {
	//r�cup�re la pression sous forme num�rique
	float result;

	result = Baro.bmp085GetPressure(Baro.bmp085ReadUP());
	return result;
}
String weatherSensors::getPressureStr() {
	//r�cup�re la pression sous forme de chaine
	String result;
	float value;

	value = getPressureNum();
	//conversion en HectoPascal
	result = String(round(value/100));
	//ajoute un espace de formatage pour les mesures inf�rieures � 1000
	if (value<1000) {result += " ";};
	return result;
}
float weatherSensors::getTemperatureNum() {
	//r�cup�re la pression sous forme num�rique
	float result;

	result = dht.readTemperature();
	return result;
}
String weatherSensors::getTemperatureStr() {
	//r�cup�re la pression sous forme de chaine
	String result;
	float value;
	int unite;
	int decim;

	value = getTemperatureNum();
	unite = int(value);
	decim = round(10 * (value-unite));
	result += String(unite) + "." + String(decim);

	//ajoute un espace de formatage pour les mesures positives
	if (value>=0) {result += " ";};
	//ajoute un espace de formatage pour les mesures inf�rieures � 10
	if (abs(value<10)) {result += " ";};
	return result;
}
