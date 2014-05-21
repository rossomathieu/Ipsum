/*
 * plane.hpp
 *
 *  Created on: May 20, 2014
 *      Author: ross
 */

#ifndef PLANE_HPP_
#define PLANE_HPP_

#include "vec3.hpp"

namespace aem {
	class plane {

		vec3 p;
		vec3 n;

		plane() {}
		plane(const vec3 &point, const vec3 &normal) : p(point), n(normal) {}

		float distance(const vec3 &p0) const {

			return ((vec3(p - p0)).projected(n).length());
		}

		float angle(const plane &p) const {

			return vec3::angle(n, p.n);
		}
	};
}



#endif /* PLANE_HPP_ */
