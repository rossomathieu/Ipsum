#include <assert.h>
#include "AECamera.h"
#include "../libaem/matrix_transform.hpp"

using namespace aeg;

static const float maxVerticalAngle = 85.0f; //To avoid gimbal lock.

AECamera::AECamera() : mPosition(0.0f, 0.0f, 1.0f), mHorizantalAngle(0.0f), mVerticalAngle(0.0f), mFieldOfView(90.0f), mNearPlane(0.01f), mFarPlane(100.0f), mViewportAspectRatio(16.0f / 9.0f) {

}

const aem::vec3& AECamera::position() const {

	return mPosition;
}

void AECamera::setPosition(const aem::vec3& position) {

	mPosition = position;
}

void AECamera::offsetPosition(const aem::vec3& offset) {

	mPosition += offset;
}

float AECamera::fieldOfView() const {

	return mFieldOfView;
}

void AECamera::setNearAndFarPlane(float nearPlane, float farPlane) {

	assert(nearPlane > 0.0f);
	assert(farPlane > nearPlane);

	mNearPlane = nearPlane;
	mFarPlane = farPlane;
}

aem::mat4 AECamera::orientation() const {

	aem::mat4 orientation;

	orientation = aem::rotate(mVerticalAngle, aem::vec3(1, 0, 0));
	orientation = aem::rotate(mHorizantalAngle, aem::vec3(0, 1, 0));

	return orientation;
}

void AECamera::offsetOrientation(float verticalAngle, float horizantalAngle) {

	mHorizantalAngle += horizantalAngle;
	while (mHorizantalAngle > 360.0f) mHorizantalAngle -= 360.0f;
	while (mHorizantalAngle < 0.0f) mHorizantalAngle += 360.0f;

	mVerticalAngle += verticalAngle;
	if (mVerticalAngle > maxVerticalAngle) mVerticalAngle = maxVerticalAngle;
	if (mVerticalAngle < -maxVerticalAngle) mVerticalAngle = -maxVerticalAngle;
}

float AECamera::viewportAspectRatio() const {

	return mViewportAspectRatio;
}

void AECamera::setViewportAspectRatio(float viewportAspectRatio) {

	assert(viewportAspectRatio > 0.0f);
	mViewportAspectRatio = viewportAspectRatio;
}

