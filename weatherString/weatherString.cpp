// Do not remove the include below
#include "weatherString.h"

String formatValue(float value, int intMask, int decMask, bool sigMask){
	String result;
	int unite = int(value);

	//ajoute un espace pour se conformer au mask de signe
	if (sigMask && (unite>=0)){result =+ " ";}

	//ajoute des espaces pour se conformer au mask
	for (int cpt = 0; cpt < intMask; cpt++) {
		if (abs(unite)<pow(10,cpt)){result =+ " ";}
	}
	result =+ String(unite);

	//formate en fonction des décimales
	if (decMask > 0) {
		result =+ ".";
		//decoupage des décimales
		int decim = round(pow(10,decMask) * (value-unite));
		if (decim == 0) {

		} else {
			result =+ String(decim);
		}
	}
	return result;
}
String substr(String string, int start, int length) {
	String result;
	int end;

	end = string.length();
	if (end > 0) {
		result = string.substring(start, end);
	} else {
		result = "";
	}
	return result;
}
String substr(String string, int start) {
	String result;
	int end;

	end = start + string.length();
	if (end > 0) {
		result = string.substring(start, end);
	} else {
		result = "";
	}
	return result;
}
int strpos(String string, String needle, int offset) {
	int result;

	result = string.indexOf(needle, offset);
	return result;
}
int strpos(String string, String needle) {
	int result;

	result = string.indexOf(needle);
	return result;
}
int strrpos(String string, String needle, int offset) {
	int result;

	result = string.lastIndexOf(needle, offset);
	return result;
}
int strrpos(String string, String needle) {
	int result;

	result = string.lastIndexOf(needle);
	return result;
}
