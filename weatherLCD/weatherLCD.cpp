// Do not remove the include below
#include <weatherLCD.h>
#include <weatherSensors.h>

#include <TimerOne.h>
#include <DS1307.h>
#include <rgb_lcd.h>

#include <Arduino.h>
#include <Wire.h>

//définitions timer
#define ON 1
#define OFF 0

//formats de date
#define DATE_LONG 0
#define DATE_COURT 1

//variables globales
unsigned char update;
boolean started = false;
int nbData = 4;

//objet capteurs
weatherSensors sensors;

//gestion de l'horloge
DS1307 clock;

//gestion du LCD
rgb_lcd lcd;

//couleur du rétro eclairage : blanc
const int colorR = 255;
const int colorG = 64;
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
	lcd.println("Clock init      ");
	clock.begin();
	delay(200);

	//lcd.setCursor(0,0);
	//lcd.println("Timer init      ");
	//Timer1.initialize(500000);                  //activation du timer pour une interruption chaque seconde
	//Timer1.attachInterrupt(getData);            //appel getData ˆ chaque interruption
  	//delay(200);

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
	lcd.setCursor(0,0);
	lcd.print(getDate(DATE_LONG));

   	//informations
   	storeData();
   	displayInformation();

   	//attente d'une demi seconde
   	delay(500);
}

void storeData() {
	clock.getTime();
	Serial.print(getDate(DATE_COURT));
	Serial.print(";");
	Serial.print(getTime());
	Serial.print(";");
	Serial.print(sensors.getPressureNum());
	Serial.print(";");
	Serial.print(sensors.getTemperatureNum());
	Serial.print(";");
	Serial.print(sensors.getAtmosphereNum());
	Serial.print(";");
	Serial.print(sensors.getAltitudeNum());
	Serial.print(";");
	Serial.print(sensors.getHumidityNum());
	Serial.println(";");

	update = OFF;
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

	//selection en fonction de la seconde en cours
	switch (int(clock.second/int(60/(nbData*2)))) {
		case 0:
			//pression
			result = "pres " + sensors.getPressureStr() + "HPa";
			break;
		case 2:
			//altitude
			result = "alti " + sensors.getAltitudeStr() + "M";
			break;
		case 4:
			//température
			result = "temp " + sensors.getTemperatureStr() + "C";
			break;
		case 6:
			//humidité
			result = "humi "+ sensors.getHumidityStr() + "%";
			break;
		default:
			//heure
			result = "    " + getTime();
	}

	//remplissage pour la fin de ligne
	result = result + "                ";

	//affichage du résultat
	lcd.setCursor(0,1);
	lcd.print(result);
}
