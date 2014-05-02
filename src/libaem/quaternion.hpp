/*
* Class: quat
* Implements:
* Author: Ross O. Mathieu
* Description: Simple quat class. I hate quaternions....
*/

#pragma once

#include <iostream>
#include "Common.h"
#include "mat4x4.hpp"

namespace aem {

	class quat {

	public:

		quat(void);
		quat(float x, float y, float z, float w);

		~quat(void);

		float x;
		float y;
		float z;
		float w;

		static quat normalize(quat const &q);
		static mat4 mat4_cast(quat const &q);
		static quat conjugate(quat const &q);
		static float dot(quat const &a, quat const &b);
	};
}