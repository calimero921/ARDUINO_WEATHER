// Do not remove the include below

#include "weather4Digit.h"

#include <TimerOne.h>
#include <DS1307.h>
#include <rgb_lcd.h>
#include <Barometer.h>
#include <DHT.h>
#include <TM1637.h>

#include <Arduino.h>
#include <Wire.h>

//définitions timer
#define ON 1
#define OFF 0

//définitions afficheur
//pins definitions for TM1637 and can be changed to other ports
#define CLK 2           //prise D2
#define DIO 3			//prise D3

//définitions température & humidité
#define DHTPIN A0        // what pin we're connected to
#define DHTTYPE DHT22    // DHT 22  (AM2302)

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
//gestion de l'horloge
DS1307 clock;
//gestion de l'afficheur
TM1637 tm1637(CLK,DIO);
//gestion du LCD
rgb_lcd lcd;
//couleur du rétro eclairage : blanc
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

//The setup function is called once at startup of the sketch
void setup() {
	started = false;

	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	lcd.setRGB(colorR, colorG, colorB);
	lcd.clear();

	lcd.setCursor(0,0);
	lcd.println("Wheather init   ");
	Serial.begin(9600);
	delay(200);

	lcd.setCursor(0,0);
	lcd.println("Display init    ");
	tm1637.set();                              //activation de l'afficheur
	tm1637.init();                             //Initialisation de l'afficheur
	delay(200);

	lcd.setCursor(0,0);
	lcd.println("Barometer init  ");
	myBarometer.init();                         //initialisation du barometre
	delay(200);

	lcd.setCursor(0,0);
	lcd.println("Thermometer init");
	dht.begin();
	delay(200);

	lcd.setCursor(0,0);
	lcd.println("Clock init      ");
	clock.begin();
	delay(200);

	lcd.setCursor(0,0);
	lcd.println("Timer init      ");
	//Timer1.initialize(500000);                  //activation du timer pour une interruption chaque seconde
	//Timer1.attachInterrupt(getData);            //appel getData ˆ chaque interruption
  	delay(200);

	lcd.setCursor(0,0);
	lcd.println("Wheather ready  ");
	delay(200);
	lcd.clear();
	started = true;
}

// The loop function is called in an endless loop
void loop()
{
	//horloge
	displayDate();
	displayTimeDigit();

	//if (update == ON) {
    	//informations
    	getData();
    	storeData();
    	displayInformation();
    //}
    delay(500);
}

void storeData() {
	clock.getTime();
	Serial.print(clock.year);
	Serial.print(":");
	Serial.print(clock.month);
	Serial.print(":");
	Serial.print(clock.dayOfMonth);
	Serial.print(";");
	Serial.print(clock.hour);
	Serial.print(":");
	Serial.print(clock.minute);
	Serial.print(":");
	Serial.print(clock.second);
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
void displayDate() {
	clock.getTime();
	lcd.setCursor(1,0);
	switch (clock.dayOfWeek) {
    	case 1:
    		lcd.print("Lun");
    		break;
    	case 2:
    		lcd.print("Mar");
    		break;
    	case 3:
    		lcd.print("Mer");
    		break;
    	case 4:
    		lcd.print("Jeu");
    		break;
    	case 5:
    		lcd.print("Ven");
    		break;
    	case 6:
    		lcd.print("Sam");
    		break;
    	case 7:
    		lcd.print("Dim");
    		break;
    	default:
    		lcd.print("---");
	}
	lcd.print(" ");
	lcd.print(clock.dayOfMonth);
	lcd.print(" ");
	switch (clock.month) {
    	case 1:
    		lcd.print("Jan");
    		break;
    	case 2:
    		lcd.print("Fev");
    		break;
    	case 3:
    		lcd.print("Mar");
    		break;
    	case 4:
    		lcd.print("Avr");
    		break;
    	case 5:
    		lcd.print("Mai");
    		break;
    	case 6:
    		lcd.print("Jun");
    		break;
    	case 7:
    		lcd.print("Jui");
    		break;
    	case 8:
    		lcd.print("Aou");
    		break;
    	case 9:
    		lcd.print("Sep");
      	  	  break;
    	case 10:
    		lcd.print("Oct");
    		break;
    	case 11:
    		lcd.print("Nov");
    		break;
    	case 12:
    		lcd.print("Dec");
    		break;
    	default:
    		lcd.print("---");
	}
	lcd.print(" ");
	lcd.print("20");
	lcd.print(clock.year);
	lcd.print("  ");
}
void displayTimeDigit() {
	int8_t TimeDisp[4];
	clock.getTime();

	TimeDisp[0] = clock.hour / 10;
	TimeDisp[1] = clock.hour % 10;
	TimeDisp[3] = clock.minute % 10;
	TimeDisp[2] = clock.minute / 10;
    tm1637.display(TimeDisp);
}
void displayTimeLCD(){
	clock.getTime();

	lcd.setCursor(0,1);
	//heure
	lcd.print("    ");
	lcd.print(clock.hour);
	lcd.print(":");
	if (clock.minute<10) {lcd.print("0");}
	lcd.print(clock.minute);
	lcd.print(":");
	if (clock.second<10) {lcd.print("0");}
	lcd.print(clock.second);
}
void displayInformation() {
	float value;
	lcd.setCursor(0,1);
	switch (int(clock.second/int(60/(nbData*2)))) {
		case 0:
			//pression
			value = int(barPres/100);
			lcd.print("pres ");
			if (value<1000) {lcd.print(" ");}
			lcd.print(value);
			lcd.print("HPa");
			break;
		case 2:
			//altitude
			value = int(barAlti);
			lcd.print("alti ");
			if (value<1000) {lcd.print(" ");}
			lcd.print(value);
			lcd.print("M");
			break;
		case 4:
			//température
			value = int(theTemp*10)/10;
			lcd.print("temp ");
			if (value>0) {lcd.print(" ");}
			if (abs(value)<10) {lcd.print(" ");}
			lcd.print(value);
			lcd.print("C");
			break;
		case 6:
			//humidité
			value = int(theHumi*10)/10;
			lcd.print("humi ");
			if (value<100) {lcd.print(" ");}
			lcd.print(value);
			lcd.print("%");
			break;
		default:
			//heure
			displayTimeLCD();
	}
	//remplissage pour la fin de ligne
	lcd.print("                ");
}
