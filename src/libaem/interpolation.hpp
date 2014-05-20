/*
 * interpolation.hpp
 *
 *  Created on: May 17, 2014
 *      Author: ross
 */

#ifndef INTERPOLATION_HPP_
#define INTERPOLATION_HPP_

#include "quaternion.hpp"
#include "vec3.hpp"

namespace aem {

//Linear quaternion interpolation
static quat lerp(const quat &q0, const quat &q1, float interpolate) {

	quat q2 = q0 * (1 - interpolate) + q1 * interpolate;

	return quat::normalize(q2);
}

//Linear vector interpolation
static vec3 lerp(const vec3 &v0, const vec3 &v1, float interpolate) {

	return v0 * (1 - interpolate) + v1 * interpolate;
}

//Spherical linear interpolation
static quat slerp(const quat &q0, const quat &q1, float interpolate) {

	quat q2;
	float dot = quat::dot(q0, q1);

	/*
	 * if (dot < 0) then q0 and q1 are greater than 90 degrees apart.
	 */

	if (dot < 0) {

		dot = -dot;
		q2 = -q1;
	} else {

		q2 = q1;
	}

	if (dot < 0.95f) {

		float angle = acosf(dot);
		return (q0 * sinf(angle * (1 - interpolate))
				+ q2 * sinf(angle * interpolate)) / sinf(angle);
	} else {

		//If the angle is small, use lerp
		return lerp(q0, q2, interpolate);
	}
}

//Spherical linear interpolation without inversion
static quat slerp_no_inversion(const quat &q0, const quat &q1,
		float interpolate) {

	float dot = quat::dot(q0, q1);

	if (dot > -0.95f && dot < 0.95f) {

		float angle = acosf(dot);
		return (q0 * sinf(angle * (1 - interpolate))
				+ q1 * sinf(angle * interpolate)) / sinf(angle);
	} else {

		return lerp(q0, q1, interpolate);
	}
}

//Spherical cubic interpolation
static quat squad(const quat &q0, const quat &q1, const quat &q2,
		const quat &q3, float interpolate) {

	quat a = slerp_no_inversion(q0, q1, interpolate);
	quat b = slerp_no_inversion(q2, q3, interpolate);

	return slerp_no_inversion(a, b, 2 * interpolate * (1 - interpolate));
}

static quat bezier(const quat &q0, const quat &q1, const quat &q2,
		const quat &q3, float interpolate) {

	quat a = slerp_no_inversion(q0, q2, interpolate);
	quat b = slerp_no_inversion(q2, q3, interpolate);
	quat c = slerp_no_inversion(q3, q1, interpolate);

	return slerp_no_inversion(slerp_no_inversion(a, b, interpolate),
			slerp_no_inversion(b, c, interpolate), interpolate);
}
}

#endif /* INTERPOLATION_HPP_ */
