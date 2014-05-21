/*
* Author: Ross O. Mathieu
* Description: Random functions that have no place to go.
*/

#pragma once

//PI
static const float PI = 3.14159265358979323846f;

//PI_OVER_360
static const float PI_OVER_360 = PI / 360.0f;

//#define max(a, b) a > b ? a : b
//#define min(a, b) a < b ? a : b

//Radians to degrees
static inline double radToDeg(const double degrees) {

	return degrees * 180.0f / PI;
}

//Degrees to radians
static inline double degToRad(const double radians) {

	return radians * PI / 180.0f;
}

//Removes quotation marks from a string
static void removeQuotes(std::string& str) {

	size_t i;

	while((i = str.find('\"')) != std::string::npos) str.erase(i, 1);
}

//Get the size of a file in bytes
static int getFileLength(std::istream& file) {

	int pos = file.tellg();
	file.seekg(0, std::ios::end);
	int length = file.tellg();

	//Restore the original position of the file pointer.
	file.seekg(pos);

	return length;
}

