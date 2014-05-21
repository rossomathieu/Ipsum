/*
* Class: mat4
* Implements: 
* Author: Ross O. Mathieu
* Description: Simple 4 by 4 matrix class.
*/

#pragma once

#include <iostream>
#include "vec3.hpp"
#include "vec4.hpp"

namespace aem {
	
	class mat4 {

	public:

		mat4(void){
			toZero();
		};

		//mat4(float elements[16]){};
		~mat4(void){};

		float values[16];

		//Set all matrix values to zero.
		void toZero() {

			for (int i = 0; i < 16; ++i) {

				values[i] = 0.0f;
			}
		}

		//Turns matrix into an indentity matrix
		void toIdentity() {

			toZero();
			values[0] = 1.0f;
			values[5] = 1.0f;
			values[10] = 1.0f;
			values[15] = 1.0f;
		}

		inline mat4 operator *(const mat4 &a) const {

			mat4 out;

			for (unsigned int r = 0; r < 4; ++r) {
				for (unsigned int c = 0; c < 4; ++c) {
					
					out.values[c + (r * 4)] = 0.0f;

					for (unsigned int i = 0; i < 4; ++i) {

						out.values[c + (r * 4)] += this->values[c + (i * 4)] * a.values[(r * 4) + i];
					}
				}
			}

			return out;
		}

		inline vec3 operator *(const vec3 &v) const {

			vec3 vec;
			float temp;

			vec.x = v.x * values[0] + v.y * values[4] + v.z * values[8] + values[12];
			vec.y = v.x * values[1] + v.y * values[5] + v.z * values[9] + values[13];
			vec.z = v.x * values[2] + v.y * values[6] + v.z * values[10] + values[14];

			temp = v.x * values[3] + v.y * values[7] + v.z * values[11] + values[15];

			vec.x = vec.x / temp;
			vec.y = vec.y / temp;
			vec.z = vec.z / temp;

			return vec;
		}

		inline vec4 operator *(const vec4 &v) const {

			return vec4(
				v.x * values[0] + v.y * values[4] + v.z * values[8] + v.w * values[12],
				v.x * values[1] + v.y * values[5] + v.z * values[9] + v.w * values[13],
				v.x * values[2] + v.y * values[6] + v.z * values[10] + v.w * values[14],
				v.x * values[3] + v.y * values[7] + v.z * values[11] + v.w * values[15]
				);
		}

		//String output for the matrix. A little messy, but works when needed.
		inline friend std::ostream& operator <<(std::ostream& out, const mat4 &m) {

			out << "mat4(";
			out << "\t" << m.values[0] << "," << m.values[1] << "," << m.values[2] << "," << m.values[3] << std::endl;
			out << "\t\t" << m.values[4] << "," << m.values[5] << "," << m.values[6] << "," << m.values[7] << std::endl;
			out << "\t\t" << m.values[8] << "," << m.values[9] << "," << m.values[10] << "," << m.values[11] << std::endl;
			out << "\t\t" << m.values[12] << "," << m.values[13] << "," << m.values[14] << "," << m.values[15] << " )" << std::endl;

			return out;
		}
	};
}
