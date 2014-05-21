#pragma once

#include "../libaem/vec3.hpp"
#include "../libaem/mat4x4.hpp"

namespace aeg {

	class AECamera {

	public:

		AECamera();

		/**
		Returns the current position of the camera.
		*/
		const aem::vec3& position() const;

		/**
		Set the position of the camera.
		*/
		void setPosition(const aem::vec3& position);

		/**
		Offset the position of the camera
		*/
		void offsetPosition(const aem::vec3& position);

		/**
		The vertical viewing angle of the camera, in degrees.
		*/
		float fieldOfView() const;

		/**
		Determines how "wide" the view of the camera is.  Large angles appear to be zoomed out,
		while small values appear to be zoomed in.

		The values must be between 0 and 180, and must never equal the two max values.
		*/
		void setFieldOfView(float fieldOfView);

		/**
		The closest visible distance from the camera.

		Objects that are closer to the camera than the current near plane will not be visible.

		The value of the near plane must be greater than 0.

		If the near plane equals 0, then nothing will appear.
		*/
		float nearPlane() const;

		/**
		The farthest visible distance from the camera.

		Objects that are further away from the far plane will not be visible.

		The value of the far plane must be greater than the value of the near plane.

		Note: Setting a large far plane has a significant impact on rendering performance.
		*/
		float farPlane() const;

		/**
		Sets the near and far plane distances.

		Everything that is located between the near and far planes will be visible.  Everything
		closer than the near plane, or farther than the far plane will not be visible.

		@param nearPlane	Minimum visible distance from the camera.  Must be greater than 0.
		@param farPlane		Maximum visible distance from the camera.  Must be greater than near plane, but less than 180.
		*/
		void setNearAndFarPlane(float nearPlane, float farPlane);

		/**
		A rotation matrix that determines the direction the camera is looking.

		Does not include translation (the camera's position)
		*/
		aem::mat4 orientation() const;

		/**
		Offsets the camera's orientation.

		The vertical angle is constrained to avoid gimbal lock.

		@param verticalAngle	The angle (in degrees) to offset the verticle rotation.
		@param horizantalAngle	The angle (in degrees) to offset the horizantal rotation.
		*/
		void offsetOrientation(float verticalAngle, float horizantalAngle);

		/**
		The width divided by the height of the screen/window/viewport.

		Incorrect values will make the 3D scene look stretched and skewed.
		*/
		float viewportAspectRatio() const;
		void setViewportAspectRatio(float viewportAspectRation);

		/**
		A unit vector representing the direction the camera is facing.
		*/
		aem::vec3 forward() const;

		/**
		A unit vector representing the direction to the right of the camera.
		*/
		aem::vec3 right() const;

		/**
		A unit vector representing the direction out of the top of the camera.
		*/
		aem::vec3 up() const;

		/**
		The combined camera transformation matrix, including the perspective projection.

		This is the complete matrix to use in the vertex shader.
		*/
		aem::mat4 matrix() const;

		/**
		The perspective projection transformation matrix.
		*/
		aem::mat4 projection() const;

		/**
		The translation and rotation matrix of the camera.

		Same as the 'matrix' method, except the return value does not include the projection transformation.
		*/
		aem::mat4 view() const;

	private:

		aem::vec3 mPosition;
		float mHorizantalAngle;
		float mVerticalAngle;
		float mFieldOfView;
		float mNearPlane;
		float mFarPlane;
		float mViewportAspectRatio;
	};
}
