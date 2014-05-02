/*
* Class: vec2
* Implements: 
* Author: Ross O. Mathieu
* Description: Simple 2 dimensional vector class. 
*/

#include <iostream>

namespace aem {
	
	class vec2 {

	public:

		vec2(void) : x(0.0), y(0.0) {};

		vec2(const float x, const float y) {

			this->x = x;
			this->y = y;
		}

		~vec2(void) {}

		float x;
		float y;

		void toZero() {

			x = 0.0f;
			y = 0.0f;
		}

		inline friend std::ostream& operator <<(std::ostream& out, const vec2& v) {

			out << "vec2(" << v.x << "," << v.y << ")" << std::endl;
			return out;
		}

		inline vec2 operator -(const vec2& in) const {

			return vec2(x - in.x, y - in.y);
		}

		inline vec2 operator +(const vec2& in) const {

			return vec2(x + in.x, y + in.x);
		}
	};
}