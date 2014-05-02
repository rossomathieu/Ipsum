/*
* Author: Ross O. Mathieu
* Description: Random functions that have no place to go.
*/

#pragma once

//PI
static const float PI = 3.14159265358979323846f;

//PI_OVER_360
static const float PI_OVER_360 = PI / 360.0f;

//Radians to degrees
static inline double radToDeg(const double degrees) {

	return degrees * 180.0f / PI;
}

//Degrees to radians
static inline double degToRad(const double radians) {

	return radians * PI / 180.0f;
}

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))