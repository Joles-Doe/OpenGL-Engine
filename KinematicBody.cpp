#include "KinematicBody.h"

KinematicBody::KinematicBody(std::shared_ptr<Transform> _transform) : mElasticity(1.0f)
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