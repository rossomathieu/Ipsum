#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4x4.hpp"
#include "../libaef/Common.h"

namespace aem {

	//Creates a rotation matrix that rotates in 'degrees' around an 'axis
	//Mimics functionality of deprectated glRotatef function
	static mat4 rotate(float degrees, const vec3 &axis) {

		mat4 temp;

		vec3 m_axis = axis;

		m_axis.normalize();

		float c = cos((float)degToRad(degrees));
		float s = sin((float)degToRad(degrees));

		temp.values[0] = (axis.x * axis.x) * (1.0f - c) + c;
		temp.values[1] = (axis.y * axis.x) * (1.0f - c) + (axis.z * s);
		temp.values[2] = (axis.z * axis.x) * (1.0f - c) - (axis.y * s);

		temp.values[4] = (axis.x * axis.y) * (1.0f - c) - (axis.z * s);
		temp.values[5] = (axis.y * axis.y) * (1.0f - c) + c;
		temp.values[6] = (axis.z * axis.y) * (1.0f - c) + (axis.x * s);

		temp.values[8] = (axis.x * axis.z) * (1.0f - c) + (axis.y * s);
		temp.values[9] = (axis.y * axis.z) * (1.0f - c) - (axis.x * s);
		temp.values[10] = (axis.z * axis.z) * (1.0f - c) + c;

		return temp;
	}

	//Creates a scaling matrix.  Mimics functionality of glScalef
	static mat4 scale(const vec3 &scale) {

		mat4 temp;

		temp.values[0] = scale.x;
		temp.values[5] = scale.y;
		temp.values[10] = scale.z;

		return temp;
	}

	//Creates a translation matrix. Mimics functionality of glTranslatef
	static mat4 translate(const vec3 &translation) {

		mat4 temp;

		temp.values[12] = translation.x;
		temp.values[13] = translation.y;
		temp.values[14] = translation.z;

		return temp;
	}

	//Creates a perspective matrix, with 'znear' and 'zfar' as the near and
	//far planes, 'aspect' and 'fov' as the aspect ratio and field of view.
	static mat4 perspective(float znear, float zfar, float aspect, float fov) {

		mat4 temp;

		const float h = 1.0f / tan(fov * PI_OVER_360);
		float negative_depth = znear - zfar;

		temp.values[0] = h / aspect;
		temp.values[5] = h;
		temp.values[10] = (zfar + znear) / negative_depth;
		temp.values[11] = -1.0f;
		temp.values[14] = 2.0f * (znear * zfar) / negative_depth;
		temp.values[15] = 0.0f;

		return temp;
	}

	//Creates a orthographic matrix with 'znear' and 'zfar' as the near and far
	//planes.
	static mat4 ortho(float znear, float zfar, float left, float right, float top, float bottom) {

		mat4 temp;

		temp.values[0] = 2.0f / (right - left);
		temp.values[5] = 2.0f / (top - bottom);
		temp.values[10] = -2.0f / (zfar - znear);
		temp.values[12] = -(right + left) / (right - left);
		temp.values[13] = -(zfar + znear) / (zfar - znear);
		temp.values[15] = 1.0f;

		return temp;
 	}

	//Builds a view matrix which can be sent directly to a shader.
	//Puts the camera at 'center', looking at 'eye', with 'up' as the up axis
	static mat4 lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) {

		mat4 r;

		r.values[12] = -center.x;
		r.values[13] = -center.y;
		r.values[14] = -center.z;

		mat4 m;
		vec3 f = (eye - center);
		f.normalize();

		vec3 s = vec3::cross(f, up);
		vec3 u = vec3::cross(s, f);

		m.values[0] = s.x;
		m.values[4] = s.y;
		m.values[8] = s.z;

		m.values[1] = u.x;
		m.values[5] = u.y;
		m.values[9] = u.z;

		m.values[2] = -f.x;
		m.values[6] = -f.y;
		m.values[10] = -f.z;

		return m * r;
	}
}
