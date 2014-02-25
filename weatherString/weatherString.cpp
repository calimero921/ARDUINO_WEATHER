// Do not remove the include below
#include "weatherString.h"

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
