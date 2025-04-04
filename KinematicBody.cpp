#include "KinematicBody.h"

KinematicBody::KinematicBody(std::shared_ptr<Transform> _transform)
{
	mTransform = _transform;

	mVelocity = glm::vec3(0.0f);
	mAcceleration = glm::vec3(0.0f);
}

void KinematicBody::Update(float _deltaTime)
{
	glm::vec3 currentPosition = mTransform->Position();
	currentPosition += mVelocity * _deltaTime + 0.5f * mAcceleration * (_deltaTime * _deltaTime);
	
	glm::vec3 currentVelocity = glm::vec3(0.0f);
}

void KinematicBody::Velocity(glm::vec3 _vel)
{
	mVelocity = _vel;
}

glm::vec3 KinematicBody::Velocity()
{
	return mVelocity;
}

void KinematicBody::Acceleration(glm::vec3 _accel)
{
	mAcceleration = _accel;
}

glm::vec3 KinematicBody::Acceleration()
{
	return mAcceleration;
}
