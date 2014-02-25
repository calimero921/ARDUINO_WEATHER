/*
 * weatherSensors.cpp
 *
 *  Created on: 21 févr. 2014
 *      Author: bede6362
 */

#include <weatherSensors.h>
#include <Arduino.h>
#include <Wire.h>

weatherSensors::weatherSensors() {
	//initialisation des communication numériques
	Serial.begin(9600);
	//activation du barometre
	Baro.init();
	//activation du thermometre
	dht.begin();
}

float weatherSensors::getAltitudeNum() {
	//récupère l'altitude sous forme numérique
	float result;

	result = Baro.calcAltitude(getPressureNum());
	return result;
}
String weatherSensors::getAltitudeStr() {
	//récupère l'altitude sous forme de chaine
	String result;
	float value;

	value = getAltitudeNum()();
	//réduction à 0 chiffre après la virgule
	result = String(round(value));
	//ajoute un espace de formatage pour les mesures inférieures à 10
	if (value<10) {result += " ";};
	//ajoute un espace de formatage pour les mesures inférieures à 100
	if (value<100) {result += " ";};
	//ajoute un espace de formatage pour les mesures inférieures à 1000
	if (value<1000) {result += " ";};
	return result;
}
float weatherSensors::getAtmosphereNum() {
	//récupère l'atmosphere sous forme numérique
	float result;

	result = getPressureNum()/101325;
	return result;
}
String weatherSensors::getAtmosphereStr() {
	//récupère l'atmosphere sous forme de chaine
	String result;
	float value;

	value = getAtmosphereNum()();
	//réduction à 3 chiffres après la virgule
	result = String(round(value*1000)/1000);
	//ajoute un espace de formatage pour les mesures inférieures à 10
	if (value<10) {result += " ";};
	return result;
}
float weatherSensors::getHumidityNum() {
	//récupère l'humidité sous forme numérique
	float result;

	result = dht.readHumidity();
	return result;
}
String weatherSensors::getHumidityStr() {
	//récupère l'humidité sous forme de chaine
	String result;
	float value;

	value = getHumidityNum()();
	//réduction à 1 chiffre après la virgule
	result = String(round(value*10)/10);
	//ajoute un espace de formatage pour les mesures inférieures à 10
	if (value<10) {result += " ";};
	return result;
}
float weatherSensors::getPressureNum() {
	//récupère la pression sous forme numérique
	float result;

	result = Baro.bmp085GetPressure(Baro.bmp085ReadUP());
	return result;
}
String weatherSensors::getPressureStr() {
	//récupère la pression sous forme de chaine
	String result;
	float value;

	value = getPressureNum();
	//conversion en HectoPascal
	result = String(round(value/100));
	//ajoute un espace de formatage pour les mesures inférieures à 1000
	if (value<1000) {result += " ";};
	return result;
}
float weatherSensors::getTemperatureNum() {
	//récupère la pression sous forme numérique
	float result;

	result = dht.readTemperature();
	return result;
}
String weatherSensors::getTemperatureStr() {
	//récupère la pression sous forme de chaine
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
	//ajoute un espace de formatage pour les mesures inférieures à 10
	if (abs(value<10)) {result += " ";};
	return result;
}
