/*
* Class: vec4
* Implements:
* Author: Ross O. Mathieu
* Description: Simple vec4 class.
*/

#pragma once

#include "vec3.hpp"
#include "mat4x4.hpp"

namespace aem {

	class vec4 {

	public:

		vec4(void) : x(1.0f), y(1.0f), z(1.0f), w(1.0f) {}

		vec4(const float x, const float y, const float z, const float w) {

			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		vec4(vec3 in, float w) {

			x = in.x;
			y = in.y;
			z = in.z;
			this->w = w;
		}

		~vec4(void) {}

		void toZero() {

			x = y = z = w = 0.0f;
		}

		float x;
		float y;
		float z;
		float w;
	};
}
