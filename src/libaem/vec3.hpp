#pragma once
/*
* Class: vec3
* Author: Ross O. Mathieu
* Implements: 
* Description: Simple vec3 class.
*/

#include <cmath>
#include <iostream>

namespace aem {
	
	class vec3 {

	public:

		vec3(void) : x(0.0f), y(0.0f), z(0.0f) {};

		vec3(const float x, const float y, const float z) {

			this->x = x;
			this->y = y;
			this->z = z;
		}

		~vec3(void) {}

		float x;
		float y;
		float z;

		void normalize() {

			float length = this->length();

			if (length != 0.0f) {

				length = 1.0f / length;

				x *= length;
				y *= length;
				z *= length;
			}
		}

		void toZero() {

			x = y = z = 0.0f;
		}

		//Correct way to calculate length, but very inefficient...
		//Avoid taking sqrt's if possible
		float length() const {

			return sqrt((x*x) + (y*y) + (z*z));
		}

		void invert() {

			x = -x;
			y = -y;
			z = -z;
		}

		vec3 inverse() const {

			return vec3(-x, -y, -z);
		}

		static float dot(const vec3 &a, const vec3 &b) {

			return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
		}

		static vec3 cross(const vec3 &a, const vec3 &b) {

			return vec3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
		}

		inline friend std::ostream& operator <<(std::ostream& out, const vec3& v) {

			out << "vec3(" << v.x << "," << v.y << "," << v.z << ")" << std::endl;

			return out;
		}

		inline vec3 operator +(const vec3 &a) const {

			return vec3(x + a.x, y + a.y, z + a.z);
		}

		inline vec3 operator -(const vec3 &a) const {

			return vec3(x - a.x, y - a.y, z - a.z);
		}

		inline vec3 operator -() const {

			return vec3(-x, -y, -z);
		}

		inline void operator +=(const vec3 &a) {

			x += a.x;
			y += a.y;
			z += a.z;
		}

		inline void operator -=(const vec3 &a) {

			x -= a.x;
			y -= a.y;
			z -= a.z;
		}

		inline vec3 operator *(const float a) const {

			return vec3(x * a, y * a, z * a);
		}

		inline vec3 operator *(const vec3 &a) const {

			return vec3(x * a.x, y * a.y, z * a.z);
		}

		inline vec3 operator /(const float v) const {

			return vec3(x / v, y / v, z / v);
		}

		inline vec3 operator /(const vec3 &a) const {

			return vec3(x / a.x, y / a.y, z / a.z);
		}

		inline bool operator ==(const vec3 &a) const {

			return (a.x == x && a.y == y && a.z == z) ? true : false;
		}

		inline bool operator !=(const vec3 &a) const {

			return (a.x == x && a.y == y && a.z == z) ? false : true;
		}
	};
}
