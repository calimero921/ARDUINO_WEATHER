// Do not remove the include below
#include <weatherDigit.h>
#include <weatherSensors.h>

#include <TimerOne.h>
#include <DS1307.h>
#include <GD2.h>

#include <Barometer.h>
#include <DHT.h>

#include <EEPROM.h>
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>

//définitions timer
#define ON 1
#define OFF 0

//définitions température & humidité
#define DHTPIN A0        // what pin we're connected to

//formats de date
#define DHTTYPE DHT22    // DHT 22  (AM2302)
#define DATE_LONG 0
#define DATE_COURT 1

//choix des écran
#define MAINSCREEN 0
#define SETTINGS   1

//variables globales
unsigned char update;
boolean started = false;
int nbData = 4;

//gestion du barometre
float barPres;
float barTemp;
float barAtmo;
float barAlti;
Barometer myBarometer;

//gestion du thermometre
float theTemp;
float theHumi;
DHT dht(DHTPIN, DHTTYPE);

weatherSensors sensors;

//gestion de l'horloge
DS1307 clock;

//gestion de l'écran
int displayAction;

//The setup function is called once at startup of the sketch
void setup() {
	started = false;
	GD.begin();
	// set up the LCD's number of columns and rows:
	GD.ClearColorRGB(0x000000);
	GD.Clear();
	GD.cmd_text(0, 0, 26, 0, "Wheather init");
	GD.swap();
	Serial.begin(9600);
	delay(500);

	GD.Clear();
	GD.cmd_text(0, 0, 26, 0, "Barometer init");
	GD.swap();
	myBarometer.init();                         //initialisation du barometre
	delay(500);

	GD.Clear();
	GD.cmd_text(0, 0, 26, 0, "Thermometer init");
	GD.swap();
	dht.begin();
	delay(500);

	GD.Clear();
	GD.cmd_text(0, 0, 26, 0, "Clock init");
	GD.swap();
	clock.begin();
	delay(500);

	GD.Clear();
	GD.cmd_text(0, 0, 26, 0, "Timer init");
	GD.swap();
	//Timer1.initialize(500000);                  //activation du timer pour une interruption chaque seconde
	//Timer1.attachInterrupt(getData);            //appel getData ˆ chaque interruption
  	delay(500);

	GD.Clear();
  	GD.cmd_text(0, 0, 26, 0, "Wheather ready");
	GD.swap();
	delay(500);

	displayAction = MAINSCREEN;
	started = true;
}

// The loop function is called in an endless loop
void loop()
{
	//horloge
	GD.ClearColorRGB(0x103000);
	GD.Clear();

	getData();
	storeData();

	switch (displayAction) {
		case SETTINGS:

			break;
		case MAINSCREEN:
		default:
	    	displayInformation();
			break;
	}

	//affiche l'écran composé
	GD.swap();
    delay(500);
}

void storeData() {
	clock.getTime();
	Serial.print(getDate(DATE_COURT));
	Serial.print(";");
	Serial.print(getTime());
	Serial.print(";");
	Serial.print(barPres);
	Serial.print(";");
	Serial.print(barTemp);
	Serial.print(";");
	Serial.print(barAtmo);
	Serial.print(";");
	Serial.print(barAlti);
	Serial.print(";");
	Serial.print(theTemp);
	Serial.print(";");
	Serial.print(theHumi);
	Serial.println(";");

	update = OFF;
}
void getData() {
	if (started) {
		update = ON;

		barTemp = myBarometer.bmp085GetTemperature(myBarometer.bmp085ReadUT());   //Get the temperature, bmp085ReadUT MUST be called first
		barPres = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());      //Get the pressure
		barAlti = myBarometer.calcAltitude(barPres);                              //Uncompensated caculation - in Meters
		barAtmo = barPres / 101325;

		theTemp = dht.readTemperature();
		theHumi = dht.readHumidity();
	}
}
String getDate(int longueur) {
	String result = "";
	char* Days[]={"---","Lun","Mar","Mer","Jeu","Ven","Sam","Dim"};
	char* Months[]={"---","Jan","Fev","Mar","Avr","Mai","Jun","Jui","Aou","Sep","Oct","Nov","Dec"};

	//date
	clock.getTime();
	switch (longueur) {
		case DATE_LONG:
			result = result + String(Days[clock.dayOfWeek]) + " ";
			result = result + clock.dayOfMonth + " ";
			result = result + String(Months[clock.month]) + " ";
			result = result + "20" + String(clock.year) + "  ";
			break;
		case DATE_COURT:
		default:
			result = result + String(clock.hour) + ":";
			result = result + String(clock.minute) + ":";
			result = result + String(clock.second);
			break;
	}

	return result;
}
String getTime(){
	String result = "";

	//heure
	clock.getTime();
	result = result + String(clock.hour) + ":";
	if (clock.minute<10) {result = result + "0";}
	result = result + String(clock.minute) + ":";
	if (clock.second<10) {result = result + "0";}
	result = result + String(clock.second);

	return result;
}
void displayInformation() {
	String result = "";
	int unite;
	int decim;

	//date
	GD.cmd_text(0, 0, 30, 0, getDate(DATE_LONG).c_str());
	//heure
	GD.cmd_text(0, 35, 28, 0, getTime().c_str());

	//pression
	unite = round(barPres/100);
	//if (unite<1000) {result = result + " ";}
	result = "pres " + String(unite) + "HPa";
	GD.cmd_text(0, 70, 26, 0, result.c_str());

	//altitude
	unite = round(barAlti);
	//if (unite<1000) {result = result + " ";}
	result = "alti " + String(round(barAlti)) + "M";
	GD.cmd_text(0, 90, 26, 0, result.c_str());

	//température
	unite = int(theTemp);
	decim = round(10 * (theTemp-unite));
	//remplace le sugne -
	//if (unite>0) {result = result + " ";}
	//remplace le chiffre des dizaines
	//if (abs(unite)<10) {result = result + " ";}
	result = "temp " + String(unite) + "." + String(decim) + "C";
	GD.cmd_text(0, 110, 26, 0, result.c_str());

	//humidité
	unite = int(theHumi);
	decim = round(10 * (theHumi-unite));
	//remplace le chiffre des dizaines
	result = "humi " + String(unite) + "." + String(decim) + "%";
	GD.cmd_text(0, 130, 26, 0, result.c_str());
}
