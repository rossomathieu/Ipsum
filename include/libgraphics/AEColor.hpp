/*
 * AEColor.hpp
 *
 *  Created on: Apr 27, 2014
 *      Author: ross
 */

#ifndef AECOLOR_HPP_
#define AECOLOR_HPP_

namespace aeg {

	class AEColor {

	public:

		AEColor(void) : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}

		AEColor(float red, float green, float blue, float alpha = 1.0f) {

			this->r = red;
			this->g = green;
			this->b = blue;
			this->a = alpha;
		}

		~AEColor(void) {}

		void setColor(float red, float green, float blue, float alpha) {

			this->r = red;
			this->g = green;
			this->b = blue;
			this->a = alpha;
		}

		float r;
		float g;
		float b;
		float a;
	};
}

#endif /* AECOLOR_HPP_ */
