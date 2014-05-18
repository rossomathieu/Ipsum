/*
 * Class: quat
 * Implements:
 * Author: Ross O. Mathieu
 * Description: Simple quat class. Quaternions are
 * annoying, yet useful...
 */

#pragma once

#include <iostream>
#include "../libaef/Common.h"
#include "mat4x4.hpp"
#include "vec3.hpp"

namespace aem {

class quat {

public:

	quat(void) : x(0), y(0), z(0), w(0){};
	quat(float x, float y, float z, float w) {

		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	quat(float w, aem::vec3 &v) {

		this->w = w;
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	quat(aem::vec3 &v, float w) {

		this->w = w;
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}

	~quat(void) {};

	float x;
	float y;
	float z;
	float w;

	//Build the 4th compenent from 3 component quats
	static float generateW(quat &q) {

		float w0 = 1.0f - (q.x * q.x) - (q.y * q.y) - (q.z * q.z);

		if (w0 < 0.0f) {

			w0 = 0.0f;
		} else {

			w0 = -sqrt(q.w);
		}

		q.w = w0;

		return w0;
	}

	static quat normalize(quat &q) {

		float magnitude = sqrt(dot(q, q));

		if (magnitude > 0.0f) {

			float t = 1.0f / magnitude;

			q.x *= t;
			q.y *= t;
			q.z *= t;
			q.w *= t;
		}

		return q;
	}

	static float length(const quat &q) {

		return (float) sqrt(dot(q, q));
	}

	static float lengthSqr(const quat &q) {

		return (float) dot(q, q);
	}

	static mat4 mat4_cast(quat const &q) {

		mat4 mat;

		mat.values[0] = 1 - 2 * (q.y * q.y) - 2 * (q.z * q.z);
		mat.values[1] = 2 * (q.x * q.y) + 2 * (q.z * q.w);
		mat.values[2] = 2 * (q.x * q.z) - 2 * (q.y * q.w);

		mat.values[4] = 2 * (q.x * q.y) - 2 * (q.z * q.w);
		mat.values[5] = 1 - 2 * (q.x * q.x) - 2 * (q.z * q.z);
		mat.values[6] = 2 * (q.y * q.z) + 2 * (q.x * q.w);

		mat.values[8] = 2 * (q.x * q.z) + 2 * (q.y * q.w);
		mat.values[9] = 2 * (q.y * q.z) - 2 * (q.x * q.w);
		mat.values[10] = 1 - 2 * (q.x * q.x) - 2 * (q.y * q.y);

		return mat;
	}

	static quat conjugate(quat &q) {

		q.x = -q.x;
		q.y = -q.y;
		q.z = -q.z;

		return q;
	}

	static quat invert(quat &q) {

		return conjugate(q) / lengthSqr(q);

	}

	static float dot(quat const &a, quat const &b) {

		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	}

	static quat eulerAnglesToQuaternion(float pitch, float yaw, float roll) {

		float y0 = (float) degToRad(yaw / 2.0f);
		float p0 = (float) degToRad(pitch / 2.0f);
		float r0 = (float) degToRad(roll / 2.0f);

		float cosy = (float) cos(y0);
		float cosp = (float) cos(p0);
		float cosr = (float) cos(r0);

		float siny = (float) sin(y0);
		float sinp = (float) sin(p0);
		float sinr = (float) sin(r0);

		quat q;

		q.x = cosr * sinp * cosy + sinr * cosp * siny;
		q.y = cosr * cosp * siny - sinr * sinp * cosy;
		q.z = sinr * cosp * cosy - cosr * sinp * siny;
		q.w = cosr * cosp * cosy + sinr * sinp * siny;

		return q;
	}

	static inline quat axisAngleToQuaternion(const aem::vec3 v0, float degrees) {

		float theta = (float) degToRad(degrees);
		float r = (float) sin(theta / 2.0f);

		return quat((float) (v0.x * r), (float) (v0.y * r), (float) (v0.z * r),
				(float) cos(theta / 2.0f));
	}

	static vec3 quaternionToEulerAngles(const quat &q0, bool isHomogenous = true) {

		float w_sq = q0.w * q0.w;
		float x_sq = q0.x * q0.x;
		float y_sq = q0.y * q0.y;
		float z_sq = q0.z * q0.z;

		vec3 euler;

		if(isHomogenous) {

			euler.x = atan2f(2.0f * (q0.x * q0.y + q0.z * q0.w), x_sq - y_sq - z_sq + w_sq);
			euler.y = asinf(-2.0f * (q0.x * q0.z - q0.y * q0.w));
			euler.z = atan2f(2.0f * (q0.y * q0.z + q0.x * q0.w), -x_sq - y_sq + z_sq + w_sq);
		} else {

			euler.x = atan2f(2.0f * (q0.z * q0.y + q0.x * q0.w), 1 - 2 * (x_sq + y_sq));
			euler.y = asinf(-2.0f * (q0.x * q0.z - q0.y * q0.w));
			euler.z = atan2f(2.0f * (q0.x * q0.y + q0.z * q0.w), 1 - 2 * (y_sq + z_sq));
		}

		return euler;
	}

	static quat quat_cast(const mat4 &m) {

		quat q;

		q.w = sqrt(std::max(0.0f, (1.0f + m.values[0] + m.values[5] + m.values[10])))
				/ 2;
		q.x = sqrt(std::max(0.0f, (1.0f + m.values[0] - m.values[5] - m.values[10])))
				/ 2;
		q.y = sqrt(std::max(0.0f, (1.0f - m.values[0] + m.values[5] - m.values[10])))
				/ 2;
		q.z = sqrt(std::max(0.0f, (1.0f - m.values[0] - m.values[5] + m.values[10])))
				/ 2;

		q.x = (float) copysign(q.x, m.values[9] - m.values[6]);
		q.y = (float) copysign(q.y, m.values[2] - m.values[8]);
		q.z = (float) copysign(q.z, m.values[4] - m.values[1]);

		return q;
	}

	quat &operator =(const quat &q) {

		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return *this;
	}

	const quat operator +(const quat &q) const {

		return quat(x + q.x, y + q.y, z + q.z, w + q.w);
	}

	const quat operator -(const quat &q) const {

		return quat(x - q.x, y - q.y, z - q.z, w - q.w);
	}

	const quat operator *(const quat &q) const {

		quat a;

		a.w = (w * q.w) - (x * q.x) - (y * q.y) - (z * q.z);
		a.x = (x * q.w) + (w * q.x) + (y * q.z) - (z * q.y);
		a.y = (y * q.w) + (w * q.y) + (z * q.x) - (x * q.z);
		a.z = (z * q.w) + (w * q.z) + (x * q.y) - (y * q.x);

		return a;
	}

	const quat operator *(const aem::vec3 &v) const {

		quat a;

		a.w = -(x * v.x) - (y * v.y) - (z * v.z);
		a.x = (w * v.x) + (y * v.z) - (z * v.y);
		a.y = (w * v.y) + (z * v.x) - (x * v.z);
		a.z = (w * v.z) + (x * v.y) - (y * v.x);

		return a;
	}

	const quat operator *(float scale) const {

		return quat(x * scale, y * scale, z * scale, w * scale);
	}

	const quat operator /(float scale) const {

		return quat(x / scale, y / scale, z / scale, w / scale);
	}

	const quat operator -() const {

		return quat(-x, -y, -z, -w);
	}

	const quat &operator +=(const quat &q) {

		w += q.w;
		x += q.x;
		y += q.y;
		z += q.z;

		return *this;
	}

	const quat &operator -=(const quat &q) {

		w -= q.w;
		x -= q.x;
		y -= q.y;
		z -= q.z;

		return *this;
	}

	const quat &operator *=(float scale) {

		this->x = x * scale;
		this->y = y * scale;
		this->z = z * scale;
		this->w = w * scale;

		return *this;
	}

	const quat &operator /=(float scale) {

		this->x = x / scale;
		this->y = y / scale;
		this->z = z / scale;
		this->w = w / scale;

		return *this;
	}

	inline friend std::ostream& operator <<(std::ostream& o, const quat &q) {

		o << "Quat(" << q.x << "," << q.y << "," << q.z << "," << q.w << ")"
				<< std::endl;

		return o;
	}

};
}
